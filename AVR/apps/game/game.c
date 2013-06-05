/** @file   game.c
    @author Ashok Fernandez, Darren O'Neill
    @date   11 Oct 2011
    @brief  Main file of the crazy pong game developed for the UCFK4
            microcontroller board. Handles all the task scheduling to 
            run the game.
    @version 1.0
*/


#include "system.h"
#include "navswitch.h"
#include "ir_uart.h"
#include "task.h"
#include "../fonts/font3x5_1.h"
#include "game_object_display.h"
#include "paddle.h"
#include "ball.h"
#include "player.h"
#include "IR_comms.h"
#include "crazy_pong.h"


/** Text scrolling rate in chars per 10s and menu text. Menu text has a few 
    spaces at the start to make it appear to scroll in from off the screen*/
#define SCROLL_RATE 25
#define MENU_TEXT "  CRAZYPONG: PRESS START!"

/** Experiementally determined time (in seconds) to display the score and
    gameover messages */
#define GAMEOVER_DISPLAY_TIME 7
#define SCORE_DISPLAY_TIME 3

/** Polling rates in Hz */
enum {DISPLAY_RATE = 1000};
enum {IR_CHECK_RATE = 100};
enum {NAVSWITCH_RATE = 100};
enum {GAME_RATE = 7}; /* Speed of the ball */

/** Game states */
typedef enum {STATE_INIT, STATE_MENU, STATE_PLAYER_CONNECT, STATE_GAME_INIT,
            STATE_PLAYING} state_t;

/** Define the initial state of the game */
static state_t state = STATE_INIT;


/** Initialises the game objects and puts them on the display */
void init_game(void)
{
    /* Initialise game objects*/
    ball_init ();
    paddle_init ();

    /* Clear menu text and initialise the game objects on the display*/
    tinygl_clear();
    ball_display_init();
    paddle_display_init ();
}

/** Initialises the menu text on the display */
void init_menu_display(void)
{
    tinygl_text_mode_set (TINYGL_TEXT_MODE_SCROLL);
    tinygl_text_dir_set (TINYGL_TEXT_DIR_ROTATE);
    tinygl_font_set (&font3x5_1);
    tinygl_text_speed_set (SCROLL_RATE);
    tinygl_text (MENU_TEXT);
}

/** Returns the amount of time that the current game message should be
   displayed for
   @return counter value the game to wait until the game should resume*/
uint16_t message_timeout_value(void)
{
    uint16_t time = DISPLAY_RATE;
    if(game_over())
        time *= GAMEOVER_DISPLAY_TIME;
    else
        time *= SCORE_DISPLAY_TIME;

    return time;
}

/** Runs the timer to check that whether a game message should still be
    displaying.
    @return True if the game message is finished displaying */
bool finished_displaying_message(void)
{
    bool finished_displaying = FALSE;
    static uint16_t message_display_timer = 0;
    static uint16_t message_display_timeout = 0;

    /* Get counter value to wait until */
    message_display_timeout = message_timeout_value();

    /* Wait until counter is reached */
    if(message_display_timer < message_display_timeout)
        message_display_timer++;
    else
    {
        /* Reset counter and resume the game */
        message_display_timer = 0;
        finished_displaying = TRUE;
        game_resume_gameplay();
    }

    return finished_displaying;
}

/** Checks if the game is over and reboots the program if it is */
void check_game_reset(void)
{
    /* Check the game isnt over */
    if(game_over())
    {
        game_reset();
        state = STATE_INIT; /* Restart the program */
    }
}

/** Handler to move the paddle when the navswitch is pressed. Blocks
    navswitch input when the game is displaying the score */
void navswitch_paddle_handler(void)
{
    if(!game_displaying_message())
    {
        if (navswitch_release_event_p(NAVSWITCH_SOUTH))
                paddle_move_left();

        if (navswitch_release_event_p(NAVSWITCH_NORTH))
                paddle_move_right();
    }
}

/** Handles the display task actions during gameplay */
void gameplay_display_handler(void)
{
    if(game_displaying_message())
    {
        if(finished_displaying_message())
            check_game_reset();
    }
    else
        paddle_display_refresh();
}



/** Task scheduler task to send and receive IR messages */
static void IR_task (__unused__ void *data)
{
    switch(state)
    {
        case STATE_PLAYING:
            if(!player_has_ball())
                IR_receive_transmission();
            else
                IR_i_have_the_ball();
            break;

        /* You're player one, tell the other board */
        case STATE_PLAYER_CONNECT:
            IR_send_player_info();
            state = STATE_GAME_INIT;
            break;

        /* Check if the other player is player one */
        case STATE_MENU:
            if(IR_receive_player_info())
            {
                player_two_init();
                state = STATE_GAME_INIT;
            }
            break;

        default:
            break;
    }
}

/** Task scheduler task to check and respond to the navswitch */
static void navswitch_task (__unused__ void *data)
{
    /* Update navswitch state and do actions according to game state */
    navswitch_update();

    switch(state)
    {
        case STATE_PLAYING:
            navswitch_paddle_handler();
            break;

        case STATE_MENU:
            /* Navswitch push in the menu sets you as player one */
            if (navswitch_release_event_p(NAVSWITCH_PUSH))
            {
                player_one_init();
                state = STATE_PLAYER_CONNECT;
            }
            break;

        default:
            break;
    }
}


/** Task scheduler task to drive the display during the game */
static void display_task (__unused__ void *data)
{
    switch(state)
    {
        case STATE_PLAYING:
            gameplay_display_handler();
            break;

        case STATE_INIT:
            init_menu_display();
            state = STATE_MENU;
            break;

        default:
            break;
    }

    tinygl_update ();
}


static void game_task (__unused__ void *data)
{
    switch(state)
    {
        case STATE_PLAYING:
            if (!game_over())
                game_update();
            break;

        case STATE_GAME_INIT:
            init_game();
            state = STATE_PLAYING;
            break;

        default:
            break;
    }
}


int main (void)
{
    /* Initialise things */
    system_init ();
    ir_uart_init ();
    navswitch_init ();
    tinygl_init (DISPLAY_RATE);

    /* Define the tasks */
    task_t tasks[] =
    {
        {
            .func = display_task,
            .period = TASK_RATE / DISPLAY_RATE,
            .data = 0
        },
        {
            .func = IR_task,
            .period = TASK_RATE / IR_CHECK_RATE,
            .data = 0
        },
        {
            .func = navswitch_task,
            .period = TASK_RATE / NAVSWITCH_RATE,
            .data = 0
        },
        {
            .func = game_task,
            .period = TASK_RATE / GAME_RATE,
            .data = 0
        },

    };

    /* Run the game */
    task_schedule (tasks, ARRAY_SIZE (tasks));
    return 0;
}

/** @file   crazy_pong.c
    @author Ashok Fernandez, Darren O'Neill
    @date   3 Oct 2011
    @brief  Set of funtions to relevant to a pong type game on the UCFK4
            microcontroller board
*/


#include "crazy_pong.h"
#include <stdlib.h>
#include "system.h"
#include "ball.h"
#include "paddle.h"
#include "player.h"
#include "tinygl.h"
#include "game_object_display.h"
#include "IR_comms.h"
#include <string.h>


#define BUFFER_LEN 3
#define SCORE_DISPLAY_LEN 20
#define GAMEOVER_MESSAGE_LEN 11
/** Padded out with spaces at the end so they're the same length and will
    jump back to the menu at the same time*/
#define WIN_MESSAGE "YOU WIN!  "
#define LOSE_MESSAGE "YOU LOOSE!"


/** Used to keep track of the amount of time the score has been displayed */
static bool game_message_displaying = FALSE;
static bool game_is_over = FALSE;


/** Sets the flag to say the other player has lost
 *  GAME OVER MAN, GAME OVER! */
void game_over_man(void)
{
    game_is_over = TRUE;
}

/** Checks to see if the game is over
    @return True if the game is over */
bool game_over(void)
{
    /* You have no lives or the other player is dead */
    return (game_is_over || !player_lives_get());
}

/** Returns whether the game is being played or the score is being displayed
   @return true if the game is dislpaying the score.*/
bool game_displaying_message(void)
{
    return game_message_displaying;
}

/** Resumes the game after a message has been displayed */
void game_resume_gameplay(void)
{
    /* Clear the message from the screen and reset the ball to player 1 */
    tinygl_clear();
    player_has_ball_reset();
    /* Re-init a new ball and paddle since the old ones were destroyed */
    paddle_init();
    ball_init();
    paddle_display_init();
    ball_display_init();
    game_message_displaying = FALSE;
}


/** Displays the players current amount of lives */
void game_display_score(void)
{
    tinygl_clear();
    game_message_displaying = TRUE;

    /* Create a string with 3 spaces and then the lives so it appears that
     * the lives scroll in from off the screen*/
    char display[SCORE_DISPLAY_LEN] = "   ";
    char buffer[BUFFER_LEN] = {'\0'};
    itoa(player_lives_get(), buffer, 10);
    strncat(display, buffer, sizeof(char));

    /*put the score on the display */
    tinygl_text(display);

}

void game_reset(void)
{
    game_message_displaying = FALSE;
    game_is_over = FALSE;
    player_number_set(0); /* Reset player numbers to 0 */
    ball_display_off();
    paddle_display_off();
    tinygl_clear();
}

/** Displays gameover message */
void game_display_gameover(void)
{
    tinygl_clear();
    game_message_displaying = TRUE;

    /* Create a string with 3 spaces and then the gameover message*/
    char display[SCORE_DISPLAY_LEN] = "   ";
    char gameover[GAMEOVER_MESSAGE_LEN] = {'\0'};
    if(player_lives_get() == 0)
        strncat(gameover, LOSE_MESSAGE, sizeof(char)*GAMEOVER_MESSAGE_LEN-1);
    else
        strncat(gameover, WIN_MESSAGE, sizeof(char)*GAMEOVER_MESSAGE_LEN-1);

    strncat(display, gameover, sizeof(char)*GAMEOVER_MESSAGE_LEN-1);
    tinygl_text(display);
}


/** Updates the state of the game */
void game_update(void)
{
    lives_t lives_before_game = 0;
    lives_t lives_after_game = 0;

    lives_before_game = player_lives_get();

    /* If the player still has lives */
    if(lives_before_game && !game_message_displaying)
    {
        /* Update the ball and check if they lost a life */
        ball_update ();
        lives_after_game = player_lives_get();

        if(lives_after_game == 0)
        {
            IR_gameover();
            game_display_gameover();
        }

        else if(lives_after_game < lives_before_game)
        {
            IR_lost_a_life();
            game_display_score();
        }
    }
}

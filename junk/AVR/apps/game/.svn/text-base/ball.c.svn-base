/** @file   ball.c
    @author Ashok Fernandez, Darren O'Neill
    @date   1st Oct 2011
    @brief  Implementation of a ping-pong ball object for the UCFK4
            developement board
*/


#include "ball.h"
#include "crazy_pong.h"
#include "system.h"
#include "game_object_display.h"
#include "boundaries.h"
#include "player.h"
#include "paddle.h"
#include "IR_comms.h"


/** Specify the initial postion of the ball. */
#define BALL_INIT_X 1
#define BALL_INIT_Y 3
#define BALL_INIT_DIR BALL_DIR_S

/** Ball object for the game */
static ball_t ball = {
    .pos = {BALL_INIT_X, BALL_INIT_Y},
    .dir = BALL_INIT_DIR
};

/** Flags to state whether the ball should be destroyed in the next
    update. Death row flag if a point was scored and outbox flag if it
    should be transmitted to the other board */
static bool ball_on_death_row = 0;
static bool ball_in_outbox = 0;


/** Returns the current state of the ball
    @return ball state */
ball_t ball_get_state(void)
{
    return ball;
}

/** Sets the flag to kill the ball in the next update*/
void ball_should_die(void)
{
    ball_on_death_row = 1;
}

/** Sets the ball to the initial position defined at the top of
    this file */
void ball_init(void)
{
    if (player_number_get() == PLAYER_ONE)
    {
        ball.pos = tinygl_point (BALL_INIT_X, BALL_INIT_Y),
        ball.dir = BALL_INIT_DIR;
    }
    ball_in_outbox = 0;
    ball_on_death_row = 0;
}

/** Makes the ball dissappear off the display and resets the destroy
    flag so the ball is will not be destroyed next move */
void ball_destroy(void)
{
    ball_display_off();
    player_has_ball_set(FALSE);
    /* Reset flags that got the ball killed */
    ball_on_death_row = 0;
    ball_in_outbox = 0;
}

/** Takes a direction and assigns that as the new direction of the ball */
void ball_set_direction(boing_dir_t direction)
{
    ball.dir = direction;
}

/** Takes a position for the ball and sets it as the current ball position */
void ball_set_position(tinygl_point_t position)
{
    ball.pos = position;
}

/** Handles the ball if it hit the scoring line by incrementing the score
 * and resetting the game */
void ball_hit_scoring_wall(void)
{
    ball_should_die();
}

/** Calculates the next position and direction of the ball taking into
    account reflections off walls */
void ball_bounce(void)
{
    ball = boing_update(ball);
}

/** Calculated the new position and direction of the ball if it is about
    to hit the paddle*/
void ball_paddle_bounce(void)
{
    paddle_t paddle = paddle_get();
    tinygl_point_t ball_pos = ball_next_position();

    /* If the ball hits the left paddle rebound to the left */
    if (ball_pos.y == paddle.left)
        ball_set_direction(BALL_DIR_NW);
    /* If it hits the right paddle, rebound to the right */
    else if (ball_pos.y == paddle.right)
        ball_set_direction(BALL_DIR_NE);
    /* Otherwise send it straight forward */
    else
        ball_set_direction(BALL_DIR_N);

    ball_bounce();
}

/** Reverse the direction of a ball relative to our coordinate system */
void ball_reverse (void)
{
    boing_dir_t newdir[] = {BALL_DIR_E, BALL_DIR_NE, BALL_DIR_N,
                            BALL_DIR_NW, BALL_DIR_W, BALL_DIR_SW,
                            BALL_DIR_S, BALL_DIR_SE};

    ball.dir = newdir[ball.dir];
}

/** Translates the state of the ball so that the ball is in the
   correct position and heading in the right direction when it is
   transferred to the other players board */
void ball_translate(void)
{
    /* If the ball is travelling diagonally into the corner, flip its
     * direction so it appears to have bounced off the wall when it
     * enters the other players screen */
    bool ball_on_edge = ((ball.pos.y == 0) || (ball.pos.y == (LEDMAT_ROWS_NUM-1)));
    if ((ball.dir != BALL_DIR_N) && ball_on_edge)
    {
        if (ball.dir == BALL_DIR_NW)
            ball.dir = BALL_DIR_NE;
        else
            ball.dir = BALL_DIR_NW;
    }

    /* Change the y coordinate of the ball so it appears to have moved
     * onto the other players screen */
    if (ball.dir == BALL_DIR_NW)
            ball.pos.y++;
    else if (ball.dir == BALL_DIR_NE)
            ball.pos.y--;

    /* Reverse the balls direction and translate its position so the
     * ball is now travelling relative to the other players
     * coordinate system */
    ball.pos.y = (LEDMAT_ROWS_NUM-1) - ball.pos.y;
    ball_reverse();
}

/** Calculates the next position of the ball. Returns only the coordinates
    of where the ball will be.
    @return co-ordinates of where the ball will be in the next loop */
tinygl_point_t ball_next_position(void)
{
    /* Get the position that the ball will be in on the next loop */
    ball_t ball_next = boing_update(ball);
    /*Extract just the coordinates of the ball */
    tinygl_point_t ball_next_position = {ball_next.pos.x, ball_next.pos.y};

    return ball_next_position;
}

/** Moves the ball to its new postion and checks the boundary cases */
void ball_move(void)
{
    /* Check for boundary conditions */
    if (boundary_scoring_line())
        ball_hit_scoring_wall();

    else if (boundary_hit_paddle())
        ball_paddle_bounce();

    else if (boundary_tx_edge())
        ball_in_outbox = 1;

    /* Otherwise the ball has hit the side wall */
    else
        ball_bounce();
}

/** Handles the actions of the ball taking into consideration all the
    different paramaters the ball has */
void ball_action_handler(void)
{
        /* Check the ball isnt scheduled to be destroyed */
        if (ball_on_death_row)
        {
            ball_destroy();
            player_lose_life();
        }

        else if (ball_in_outbox)
        {
            ball_display_off();
            ball_translate();
            IR_send_ball();
            ball_destroy();
        }

        /* If the player didn't have ball and now they do */
        else if (player_has_ball() > player_had_ball())
        {
            ball_display_on();
            /* Reset the had_ball flag to TRUE so had_ball is now true
             * and this condition doesnt trigger next loop around */
            player_has_ball_set(TRUE);
        }
        else
        {
            ball_move();
            ball_display_on();
        }
}

/** Updates the state of the ball and refreshes it on the display */
void ball_update(void)
{
    ball_display_off();
    if (player_has_ball())
    {
        ball_action_handler();
    }
}






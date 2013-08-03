/** @file   boundaries.c
    @author Ashok Fernandez, Darren O'Neill
    @date   2 Oct 2011
    @brief  Set of funtions to handle boundary conditions related to the
            ball and paddle of the ping-pong game on the ucfk4 board.
            Handles scoring, reflections off the paddle and transmitting
            and receving the ball via IR.
*/


#include "boundaries.h"
#include "crazy_pong.h"
#include "tinygl.h"
#include "paddle.h"
#include "ball.h"


/** Checks if the next position of the ball is on the bottom of the
    screen, i.e the line where the paddle and scoring line are.
    @return True if the ball if the ball will be on the bottom of
            the screen in the next turn of the screen otherwise False */
bool boundary_scoring_line(void)
{
    ball_t ball = ball_get_state();

    return (ball.pos.x == PADDLE_X);
}

/** Checks if the balls next position is the paddle
    @return True if the ball if the ball will hit the paddle in the
            next turn of the screen otherwise False */
bool boundary_hit_paddle(void)
{
    bool hit_paddle = FALSE;
    /* Get the next position of the ball and the current paddle position */
    tinygl_point_t ball_pos = ball_next_position();
    paddle_t paddle = paddle_get();

    /* Check if the ball is on the paddle line and in the paddle bounds*/
    if (ball_pos.x == PADDLE_X)
    {
        hit_paddle = ((ball_pos.y <= paddle.left) &&
                      (ball_pos.y >= paddle.right));
    }

    return hit_paddle;
}

/** Checks if the balls next position is the top of the screen and
    therefore the ball must be transmitted to the other board
    @return True if the ball if the ball will be on transmitted in
            the next turn of the screen otherwise False */
bool boundary_tx_edge(void){
    ball_t ball = ball_get_state();
    /* Check the ball is heading out (i.e hasnt just been received) */
    bool outgoing = ((ball.dir == BALL_DIR_N) || (ball.dir == BALL_DIR_NW)
                     || (ball.dir == BALL_DIR_NE));

    return ((ball.pos.x == 0) && outgoing);
}





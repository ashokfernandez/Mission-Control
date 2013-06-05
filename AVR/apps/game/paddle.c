/** @file   paddle.c
    @author Ashok Fernandez, Darren O'Neill
    @date   29 Sept 2011
    @brief  Inplementation of a ping-pong paddle object for the UCFK4
            developement board
*/


#include "system.h"
#include "crazy_pong.h"
#include "paddle.h"
#include "game_object_display.h"


/** Deifining the start position and length. The paddle number should
    ideally be even/odd to match the even/odd-ness of the number of rows.
    This ensures it will always fit symmetricaly. It should also be
    no larger than the number max number of rows / 2 */
#define PADDLE_LENGTH 3
#define PADDLE_START_POSITION ((LEDMAT_ROWS_NUM/2) + (PADDLE_LENGTH/2))

/** Computes the right point of the paddle given the left point */
#define PADDLE_RIGHT(LEFT) (LEFT - (PADDLE_LENGTH - 1))

/** The display is orientated so that moving left is an increase in
    y-value and vice-versa for right */
#define LEFT 1
#define RIGHT -1

/** The left and right points in which the paddle can move */
#define MAX_LEFT (LEDMAT_ROWS_NUM - 1)
#define MAX_RIGHT 0


/** Paddle for the board */
static paddle_t paddle = {
    .left = PADDLE_START_POSITION,
    .right = PADDLE_RIGHT(PADDLE_START_POSITION)
};


/** Initialises the paddle position to the centre of the display and
   draws it on the display.*/
void paddle_init(void)
{
    paddle.left = PADDLE_START_POSITION;
    paddle.right = PADDLE_RIGHT(PADDLE_START_POSITION);
}

/** Reset the paddle on the centre of the display for a new game */
void paddle_destroy(void)
{
    paddle_init();
}


/** Checks if the paddle is able to move within the display constraints
    @return True or False  */
bool paddle_can_move(int8_t direction)
{
    bool can_move = TRUE;

    /* Check the paddle isn't trying to move outside the display bounds */
    if ((paddle.left + direction) > MAX_LEFT)
        can_move = FALSE;
    else if ((paddle.right + direction) <  MAX_RIGHT)
        can_move = FALSE;

    return can_move;
}

/** Move the paddle in the given direction */
void paddle_move(int8_t direction)
{
    paddle_display_off();

    if (paddle_can_move(direction))
    {
        paddle.left += direction;
        paddle.right += direction;
    }

    paddle_display_on();
}

/** Move the paddle one space to the left */
void paddle_move_left(void)
{
    paddle_move(LEFT);
}

/** Move the paddle one space to the right */
void paddle_move_right(void)
{
    paddle_move(RIGHT);
}

/** Returns the current paddle struct with the left and right boundaries
    of the paddle
    @return paddle object  */
paddle_t paddle_get(void)
{
    return paddle;
}

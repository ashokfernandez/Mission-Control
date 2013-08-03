/** @file   paddle.h
    @author Ashok Fernandez, Darren O'Neill
    @date   29 Sept 2011
    @brief  Specifications of a ping-pong paddle object for the UCFK4
            developement board
*/

#include "tinygl.h"


#ifndef PADDLE_H
#define PADDLE_H


/** The paddle is always in the column closest to the navswitch */
#define PADDLE_X 4


/** Paddle structure that contains the left and right ends of the paddle */
typedef struct Paddle
{
    tinygl_coord_t left;
    tinygl_coord_t right;
} paddle_t;


/** Initialises the paddle and draws it on the display */
void paddle_init(void);

/** Clears the current instance of the paddle and reinitialise it to its
 * inital position */
void paddle_destroy(void);

/** Move the paddle one space to the left */
void paddle_move_left(void);

/** Move the paddle one space to the right */
void paddle_move_right(void);

/** Returns the current paddle struct with the left and right boundaries
    of the paddle
    @return paddle object  */
paddle_t paddle_get(void);

#endif /* PADDLE_H */

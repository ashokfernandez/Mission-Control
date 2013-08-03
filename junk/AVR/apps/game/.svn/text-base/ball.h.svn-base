/** @file   ball.h
    @author Ashok Fernandez, Darren O'Neill
    @date   1 Oct 2011
    @brief  Specifications of a ball object for a ping-pong game on the
            UCFK4 developement board
*/

#include "boing.h"
#include "tinygl.h"

#ifndef BALL_H
#define BALL_H


/** Define direction of ball relative to screen, ie the south side is
 * where the paddle is.  */
#define BALL_DIR_W DIR_N
#define BALL_DIR_NW DIR_NW
#define BALL_DIR_N DIR_W
#define BALL_DIR_NE DIR_SW
#define BALL_DIR_E DIR_S
#define BALL_DIR_SE DIR_SE
#define BALL_DIR_S DIR_E
#define BALL_DIR_SW DIR_NE


/** Renaming boing_state_t ball_t to make it more relavant to the game.
    Has propeties postion of type tinygl_point_t and dir of type
    boing_dir_t*/
typedef boing_state_t ball_t;


/** Updates the balls state (postion and direction) and refreshes the
 * ball on the display */
void ball_init(void);

/** Updates the balls state (postion and direction) and refreshes the
 * ball on the display */
void ball_update(void);

/** Returns the current state of the ball
    @return ball state */
ball_t ball_get_state(void);

/** Calculates the next position of the ball. Returns only the coordinates
    of where the ball will be.
    @return co-ordinates of where the ball will be in the next loop */
tinygl_point_t ball_next_position(void);

/** Sets the direciton of the ball
    @param ball direction */
void ball_set_direction(boing_dir_t direction);

/** Set the current ball position
    @param ball position */
void ball_set_position(tinygl_point_t position);

#endif /* BALL_H */

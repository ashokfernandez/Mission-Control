/** @file   boundaries.h
    @author Ashok Fernandez, Darren O'Neill
    @date   2 Oct 2011
    @brief  Set of funtions to handle boundary conditions related to the
            ball and paddle of the ping-pong game on the ucfk4 board.
            Handles scoring, reflections off the paddle and transmitting
            and receving the ball via IR.
*/


#include "system.h"


#ifndef BOUNDARIES_H
#define BOUNDARIES_H

/** Checks if the next position of the ball is on the bottom of the
    screen, i.e the line where the paddle and scoring line are.
    @return 1 if the ball if the ball will be on the bottom of
            the screen in the next turn of the screen otherwise 0 */
bool boundary_scoring_line(void);

/** Checks if the balls next position is the paddle
    @return 1 if the ball if the ball will hit the paddle in the
            next turn of the screen otherwise 0 */
bool boundary_hit_paddle(void);

/** Checks if the balls next position is the top of the screen and
    therefore the ball must be transmitted to the other board
    @return 1 if the ball if the ball will be on transmitted in
            the next turn of the screen otherwise 0 */
bool boundary_tx_edge(void);

#endif /* BOUNDARIES_H */

/** @file   error_check.h
    @author Ashok Fernandez, Darren O'Neill
    @date   7 Oct 2011
    @brief  Set of functions to check the received IR messages on the
            ping-pong game for the UCFK4 board are correct
*/

#include "ball.h"
#include "system.h"

#ifndef ERROR_CHECK_H
#define ERROR_CHECK_H

/** Checks that the received balls position and direction are both
    valid for an incomming ball over IR
    @param ball received over IR
    @return 1 if the position and direction are valid otherwise 0 */
bool check_ball_valid(ball_t ball);

/** Checks that the encoded ball received over IR has no errors. The code
    checks that the first bit is zero if it is a ball, then checks that
    the player number (last bit) is correct and then checks that the
    direction/position specified is valid.
    @param encoded ball received over IR
    @return True if there are no errors otherwise False */
bool check_no_errors(uint8_t encoded_ball);

#endif /* ERROR_CHECK_H */

/** @file   error_check.c
    @author Ashok Fernandez, Darren O'Neill
    @date   7 Oct 2011
    @brief  Set of functions to check the received IR messages on the
            ping-pong game for the UCFK4 board are correct
*/


#include "error_check.h"
#include "crazy_pong.h"
#include "tinygl.h"
#include "player.h"
#include "IR_comms.h"


/** Checks the last bit of the encoded message and checks that is
   set right so that it is from the other player. This is to help fight
   the issue where the board was reading its own messages
   @param encoded message
   @return True is the message was from the other player*/
bool check_from_other_player(uint8_t encoded_message)
{
    bool check_ok = FALSE;
    /* Get the state of the last bit */
    bool last_is_one = (encoded_message & LAST_IS_ONE);

    if((player_number_get() == PLAYER_ONE) && !last_is_one)
        check_ok = TRUE;
    else if ((player_number_get() == PLAYER_TWO) && last_is_one)
        check_ok = TRUE;

    return check_ok;
}

/** Checks that messages received are from the other player and they are
    valid messages
    @return True if the message is OK */
bool check_valid_message(uint8_t encoded_message)
{
    bool check_ok = TRUE; /* Message is correct until proven otherwise */

    /* Check the messages are from the other player and they are valid */
    if(player_number_get() == PLAYER_ONE)
    {
        switch(encoded_message)
        {
            case MESSAGE_PLAYER_2_LOST_LIFE:
            case MESSAGE_PLAYER_2_LOST_GAME:
                break;
            default:
                check_ok = FALSE;
                break;
        }
    }

    else /* player is player 2 so check the messages are from player 1 */
    {
        switch(encoded_message)
        {
            case MESSAGE_PLAYER_1_LOST_LIFE:
            case MESSAGE_PLAYER_1_LOST_GAME:
                break;
            default:
                check_ok = FALSE;
                break;
        }
    }

    return check_ok;
}

/** Checks that the encoded ball received over IR has no errors. The code
    checks that the first bit is zero if it is a ball, then checks that
    the player number (last bit) is correct and then checks that the
    direction/position specified is valid.
    @param encoded ball received over IR
    @return True if there are no errors otherwise False */
bool check_no_errors(uint8_t encoded_message)
{
    bool check_ok = FALSE;
    bool from_other_player = FALSE;

    /* Get the state of the first bit */
    bool first_is_zero = !(encoded_message & FIRST_IS_ZERO);

    /* Check that the message was from the other player */
    from_other_player = check_from_other_player(encoded_message);

    if(from_other_player)
    {
        if (first_is_zero)  /* Then it is a ball object */
            check_ok = TRUE;


        else /* Its a message */
        {
            if(check_valid_message(encoded_message))
                check_ok = TRUE;
        }
    }

    return check_ok;
}

/** Checks the receieved position is valid.
   @param recevied ball position
   @return 1 if the position is valid otherwise 0 */
bool check_position(tinygl_coord_t position)
{
    bool valid_pos = TRUE;
    if((position < 0) || (position > (TINYGL_HEIGHT - 1)))
        valid_pos = FALSE;

    return valid_pos;
}

/** Checks the receieved direction is valid.
   @param recevied ball direction
   @return 1 if the position is valid or 0 otherwise */
bool check_direction(boing_dir_t direction)
{
    bool valid_dir = TRUE;
    switch(direction)
    {
        /* If the ball direction is valid do nothing */
        case BALL_DIR_SW:
        case BALL_DIR_SE:
        case BALL_DIR_S:
            break;
        /* Otherwise set return value to error */
        default:
            valid_dir = FALSE;
            break;
    }
    return valid_dir;
}

/** Checks that the received balls position and direction are both
    valid for an incomming ball over IR
    @param ball received over IR
    @return 1 if the position and direction are valid otherwise 0 */
bool check_ball_valid(ball_t ball)
{
    return(check_position(ball.pos.y) && check_direction(ball.dir));
}

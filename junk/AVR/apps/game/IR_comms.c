/** @file   IR_comms.c
    @author Ashok Fernandez, Darren O'Neill
    @date   1 Oct 2011
    @brief  Functions to communicatio information for a ping-pong game
            on the UCFK4 developement board
*/


#include "IR_comms.h"
#include "error_check.h"
#include "player.h"
#include "ball.h"
#include "tinygl.h"
#include "boing.h"
#include "ir_uart.h"
#include "crazy_pong.h"


/* The ball will always be on the top of the screen when it arrives */
#define INCOMING_X 0

/* Macros to extract the first and last four bits of the ball info */
#define FIRST_FOUR_BITS(X) (X & 0xF0)
#define LAST_FOUR_BITS(X) (X & 0x0F)

/* Amount to shift the ball info by when encoding/decoding the ball */
#define POS_SHIFT_AMOUNT 4
#define DIR_SHIFT_AMOUNT 1

/* Amount of times to repeat the broadcast when sending information */
#define SEND_TOLERANCE 10


/** Encodes the ball position and direction into an 8-bit binary string
    where the first 4 bytes are the position and the last 4 bytes is
    the direction (as specified in boing.h). This will only work given
    the direction and position values are less than 15.
    @param ball position
    @param ball direction
    @return 8-bit binary of position and direction */
uint8_t IR_ball_encode(ball_t ball)
{
    /* Assign the y position and direction to 8-bit ints*/
    uint8_t ball_info = ball.dir;
    uint8_t position = ball.pos.y;

    /* Shift the direction position number to the left */
    ball_info <<= DIR_SHIFT_AMOUNT;
    position <<= POS_SHIFT_AMOUNT;

    /* Combine the two into one number */
    ball_info |= position;

    /* Mask the first bit to be 0 and the last to be 1 if player one is
     * sending the message*/
    ball_info &= ~FIRST_IS_ZERO;
    if(player_number_get() == PLAYER_ONE)
    {
        ball_info |= LAST_IS_ONE;
    }
    else
    {
        ball_info &= ~LAST_IS_ONE;
    }

    return ball_info;
}

/** Decodes the received ball information and returns a ball with position
    and direction set to the recieved information
    @param encoded ball information
    @return ball with position and direction set from IR info */
ball_t IR_ball_decode(uint8_t ball_info)
{
    ball_t received_ball;

    /* Extract the direction and assign it to the new ball */
    received_ball.dir = (LAST_FOUR_BITS(ball_info) >> 1);

    /* Extract the position and shift back to the correct place */
    tinygl_coord_t y_position = FIRST_FOUR_BITS(ball_info);
    y_position >>= POS_SHIFT_AMOUNT;
    received_ball.pos = tinygl_point(INCOMING_X, y_position);

    return received_ball;
}

/** Connects the two players. Called when the button is pushed and player
    one is established to tell the other board they are player two */
void IR_send_player_info(void)
{
    while(!ir_uart_putc(MESSAGE_TO_PLAYER_TWO));
}

/** Checks the IR register to see if the other player has pushed their
 * switch to become player one.
   @return true if a player one message is received*/
bool IR_receive_player_info(void)
{
    bool info_received = FALSE;
    if(ir_uart_read_ready_p())
        /* Typecast to keep compiler happy */
        info_received = (ir_uart_getc() == (int8_t)MESSAGE_TO_PLAYER_TWO);

    return info_received;
}

/** Sends a message to the other player which tells them that you have
    the ball*/
void IR_i_have_the_ball(void)
{
    if(ir_uart_write_ready_p())
    {
        ir_uart_putc(MESSAGE_HAVE_BALL);
    }
}

/** Sends an 8-bit number over IR */
void IR_transmit(uint8_t eight_bit_value)
{
    uint8_t count = 0;
    while(count < SEND_TOLERANCE)
    {
        if(ir_uart_write_ready_p())
        {
            ir_uart_putc(eight_bit_value);
        }
        count++;
    }
}

/** Sends the y-position and direction of the ball to the other player*/
void IR_send_ball(void)
{
    ball_t ball = ball_get_state();
    uint8_t encoded_ball = IR_ball_encode(ball);
    IR_transmit(encoded_ball);
}

/** Tells the other board that I just lost a life */
void IR_lost_a_life(void)
{
    if((player_number_get() == PLAYER_ONE))
        IR_transmit(MESSAGE_PLAYER_1_LOST_LIFE);
    else
        IR_transmit(MESSAGE_PLAYER_2_LOST_LIFE);

}

/** Tells the other board that I just lost a life */
void IR_gameover(void)
{
    if((player_number_get() == PLAYER_ONE))
        IR_transmit(MESSAGE_PLAYER_1_LOST_GAME);
    else
        IR_transmit(MESSAGE_PLAYER_2_LOST_GAME);


}

/** Takes an encoded ball, decodes it, checks it has no errors, a valid
    direction and position and assigns it to the player. */
void IR_assign_ball(uint8_t encoded)
{
    ball_t ball = IR_ball_decode(encoded);
    if(check_ball_valid(ball))
        {
            ball_set_position(ball.pos);
            ball_set_direction(ball.dir);
            player_has_ball_set(TRUE);
        }
}

/** Returns true if the received ball is a message, else check if its a ball */
bool IR_message(uint8_t encoded_message)
{
    bool is_message = FALSE;
    bool first_is_one = (encoded_message & FIRST_IS_ZERO);

    /* other player lost a life */
    if(!game_displaying_message() && first_is_one)
    {

        encoded_message >>= 1; /* Shifted to check the message */
        switch(encoded_message)
        {
            case MESSAGE_HAVE_BALL:
                is_message = TRUE;
                break;

            case MESSAGE_LOST_LIFE:
                game_display_score();
                is_message = TRUE;
                break;

            case MESSAGE_GAMEOVER:
                game_over_man();
                game_display_gameover();
                is_message = TRUE;
                break;

            default:
                break; /* its not a message */
        }
    }

    return is_message;
}

/** Receieves the ball from the other player */
void IR_receive_transmission(void)
{
    /* 255 is never used in the game so if it is received as the first
       value it must be bogus */
    static uint8_t encoded = 0;
    static uint8_t previous = 255;

   /* Read in a new ball */
    if (ir_uart_read_ready_p())
    {
        encoded = ir_uart_getc();
    }

    /* If the new one and the old one are the same, process the code */
    if((previous == encoded) && check_no_errors(encoded))
    {
        /* If its not a message it must be a ball */
        if(!IR_message(encoded))
        {
            IR_assign_ball(encoded);
        }
    }
    previous = encoded;
}



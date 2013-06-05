/** @file   IR_comms.h
    @author Ashok Fernandez, Darren O'Neill
    @date   1 Oct 2011
    @brief  Functions to communicatio information for a ping-pong game
            on the UCFK4 developement board


    The rules of the code for the messages between the board are as
    follows
        1) The left most bit is a 1 if the code is a message and
           a 0 if it is ball information


        2) If it sent from player one the right most bit will be a 1
           otherwise it will be a 0 if it is from player two

        3) If it is a ball the next three bits are the y-corrdinate
           for the incomming balls position and three bits after
           that is the direction number

        4) Each message has two codes, the individual code with the
           rightmost bit set depending on the player number and then
           a global message code; which is the individual code shifted
           one place to the right to clobber the player bit.
           (i.e message codes are the same for both players except for
           the rightmost bit)


        Example:

        00100100 = A ball from player two with position 2 and direction 2
        10000111 = Message to from player one that saying hes lost
        01000011 = Global message if someone has lost


*/


#include "system.h"


#ifndef IR_COMMS_H
#define IR_COMMS_H

/* Bitmasks to check that the first bit is a zero and the last bit is a 1 */
#define FIRST_IS_ZERO 0x80
#define LAST_IS_ONE 0x01

/* Messages that can be sent between the boards */
#define MESSAGE_TO_PLAYER_TWO 0x89
#define MESSAGE_PLAYER_1_LOST_GAME 0x87
#define MESSAGE_PLAYER_2_LOST_GAME 0x86
#define MESSAGE_GAMEOVER 0x43
#define MESSAGE_PLAYER_1_LOST_LIFE 0x83
#define MESSAGE_PLAYER_2_LOST_LIFE 0x82
#define MESSAGE_LOST_LIFE 0x41
#define MESSAGE_HAVE_BALL 0x81


/** Sends the y-position and direction of the ball to the other player*/
void IR_send_ball(void);

/** Receieves the information transmitted by the other player*/
void IR_receive_transmission(void);

/** Connects the two players. Called when the button is pushed and player
    one is established to tell the other board they are player two */
void IR_send_player_info(void);

/** Checks the IR register to see if the other player has pushed their
    switch to become player one.
    @return true if a player one message is received*/
bool IR_receive_player_info(void);

/** Sends a message to the other player which tells them that you have
    the ball*/
void IR_i_have_the_ball(void);

/** Tells the other board that I just lost a life */
void IR_lost_a_life(void);

/** Tells the other board that I just lost the game */
void IR_gameover(void);

#endif /* IR_COMMS */

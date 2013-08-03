/** @file   player.h
    @author Ashok Fernandez, Darren O'Neill
    @date   3 Oct 2011
    @brief  Set of funtions to keep track of the player information in
            a ping-pong type game on the UCFK4 microcontroller board
*/


#include "system.h"


#ifndef PLAYER_H
#define PLAYER_H


#define INITIAL_LIVES 5


/** Defines the values representing which player is which */
typedef enum {PLAYER_ONE = 1, PLAYER_TWO} player_number_t;

/** Keeps track of how many lives the player has left */
typedef int8_t lives_t;

/** Stores information about the current player. Contains the players
   number, how many lives they have and a queue of info about whether
   they have the ball*/
typedef struct player {
    player_number_t player_number;
    lives_t lives;
    bool has_ball;
    bool had_ball;
} player_t;



/** Sets the player number */
void player_number_set(player_number_t number);

/** Tells external modules which player you are
 * @return players number*/
player_number_t player_number_get(void);

/** Gives the amount of lives the player has left.
    @return number of lives player has left */
lives_t player_lives_get(void);

/** Decrements the players life by one */
void player_lose_life(void);

/** Lets other modules know if the player has the ball or not
    @return if the player has the ball */
bool player_has_ball(void);

/** Lets other modules know if the player had the ball or in the last
    turn
    @return if the player previously had the ball */
bool player_had_ball(void);

/** Toggles whether the player has the ball or not */
void player_has_ball_set(bool player_ball_state);

/** Resets the has_ball value to the initial value relevant to the
   player number. Used to initialise the players and to reset the players
   after a point is scored */
void player_has_ball_reset(void);

/** Initialise the player as player one */
void player_one_init(void);

/** Initialises the player as player two.  */
void player_two_init(void);

#endif /* PLAYER_H */

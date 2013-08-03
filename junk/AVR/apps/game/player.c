/** @file   player.c
    @author Ashok Fernandez, Darren O'Neill
    @date   3 Oct 2011
    @brief  Set of funtions to keep track of the player information in
            a ping-pong type game on the UCFK4 microcontroller board
*/


#include "player.h"
#include "crazy_pong.h"


/** Keeps track of player information.  Player number is initialised
   to zero and set when the players are established in STATE_PLAYER_INIT */
static player_t player = {
    .player_number = 0,
    .lives = INITIAL_LIVES,
    .has_ball = 0,
    .had_ball = 0
};


/** Gives the amount of lives the player has left.
    @return number of lives player has left */
lives_t player_lives_get(void)
{
    return player.lives;
}

/** Sets the player number */
void player_number_set(player_number_t number)
{
    player.player_number =  number;
}

/** Tells external modules which player you are
 * @return players number*/
player_number_t player_number_get(void)
{
    return player.player_number;
}

/** Decrements the players life by one */
void player_lose_life(void)
{
    player.lives--;
}

/** Lets other modules know if the player has the ball or not
    @return if the player has the ball */
bool player_has_ball(void)
{
    return player.has_ball;
}

/** Lets other modules know if the player had the ball or in the last
    turn
    @return if the player previously had the ball */
bool player_had_ball(void)
{
    return player.had_ball;
}

/** Updates the flag stating whether or not the player previously had
    the ball */
void player_had_ball_update(void)
{
    player.had_ball = player.has_ball;
}

/** Toggles whether the player has the ball or not */
void player_has_ball_set(bool player_ball_state)
{
    player_had_ball_update();
    player.has_ball = player_ball_state;
}

/** Resets the has_ball value to the initial value relevant to the
   player number. Used to initialise the players and to reset the players
   after a point is scored */
void player_has_ball_reset(void)
{
    /* Player one starts with the ball */
    if(player_number_get() == PLAYER_ONE)
    {
        player.has_ball = TRUE;
        player.had_ball = TRUE;
    }
    else
    {
        player.has_ball = FALSE;
        player.had_ball = FALSE;
    }
}

/** Initialises a player */
void player_init(player_number_t number)
{
    player.player_number = number;
    player.lives = INITIAL_LIVES;
    player_has_ball_reset();
}

/** Initialise the player as player one */
void player_one_init(void)
{
    player_init(PLAYER_ONE);
}

/** Initialises the player as player two.  */
void player_two_init(void)
{
    player_init(PLAYER_TWO);
}

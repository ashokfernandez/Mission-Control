/** @file   crazy_pong.h
    @author Ashok Fernandez, Darren O'Neill
    @date   3 Oct 2011
    @brief  Set of funtions to relevant to a pong type game on the UCFK4
            microcontroller board
*/


#include "system.h"


/** Common True and False values for better code readability and consistancy */
#define TRUE 1
#define FALSE 0


#ifndef CRAZY_PONG_H
#define CRAZY_PONG_H

/** Checks to see if the game is over
    @return True if the game is over */
bool game_over(void);

/** Sets the flag to say the other player has lost
 *  GAME OVER MAN, GAME OVER! */
void game_over_man(void);

/** Updates the state of the game */
void game_update(void);

/** Gets the current value of whether the game is being played or the
 * score is being displayed
   @return true if the game is dislpaying the score.*/
bool game_displaying_message(void);

/** Displays the current score on screen */
void game_display_score(void);

/** Displays gameover message */
void game_display_gameover(void);

/** Resumes the game after a message has been displayed */
void game_resume_gameplay(void);

/** Resets the game variables when a game is finished for the next game*/
void game_reset(void);


#endif /* CRAZY_PONG_H */

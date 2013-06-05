/** @file   game_object_display.h
    @author Ashok Fernandez, Darren O'Neill
    @date   29 Sept 2011
    @brief  Set of routines to update the display of the ping-pong game
            objects using the tinygl library
*/


#ifndef GAME_OBJECT_DISPLAY_H
#define GAME_OBJECT_DISPLAY_H


/** Defines the pixel values for tinygl to turn the pixels on off */
#define DISPLAY_ON 1
#define DISPLAY_OFF 0


/** Initialise the paddle on the display */
void paddle_display_init(void);

/** Turns the paddle on on the display */
void paddle_display_on(void);

/** Turns the paddle off on the display */
void paddle_display_off(void);

/** Turns the paddle off and then on again, incase something has turned
    off one of the lights that was in the line that formed the paddle */
void paddle_display_refresh(void);

/** Initialise the ball on the display if the player is player one*/
void ball_display_init(void);

/** Turns the point that the ball is at on */
void ball_display_on(void);

/** Turns the point that the ball is at off */
void ball_display_off(void);


#endif /* GAME_OBJECT_DISPLAY_H */

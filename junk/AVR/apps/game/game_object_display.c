/** @file   game_object_display.c
    @author Ashok Fernandez, Darren O'Neill
    @date   29 Sept 2011
    @brief  Set of routines to update the display of the ping-pong game
            objects using the tinygl library
*/


#include "game_object_display.h"
#include "tinygl.h"
#include "paddle.h"
#include "ball.h"
#include "player.h"


/** Initialise the paddle on the display */
void paddle_display_init(void)
{
    paddle_t paddle = paddle_get();
    tinygl_draw_line(tinygl_point(PADDLE_X, paddle.left),
                     tinygl_point(PADDLE_X, paddle.right), DISPLAY_ON);
}

/** Initialise the paddle on the display
    @param either DISPLAY_ON or DISPLAY_OFF */
void paddle_display_update(tinygl_pixel_value_t pixel_state)
{
    paddle_t paddle = paddle_get();

    tinygl_draw_line(tinygl_point(PADDLE_X, paddle.left),
                     tinygl_point(PADDLE_X, paddle.right), pixel_state);

}

/** Turns the paddle on on the display */
void paddle_display_off(void)
{
    paddle_display_update(DISPLAY_OFF);
}

/** Turns the paddle off on the display */
void paddle_display_on(void)
{
    paddle_display_update(DISPLAY_ON);
}

/** Turns the paddle off and then on again, incase something has turned
    off one of the lights that was in the line that formed the paddle */
void paddle_display_refresh(void)
{
    paddle_display_off();
    paddle_display_on();
}

/** Initialise the ball on the display if the player is player one */
void ball_display_init (void)
{
    if (player_number_get() == PLAYER_ONE)
    {
        ball_t ball = ball_get_state();
        tinygl_draw_point(ball.pos, DISPLAY_ON);
    }
}

/** Turns the point that the ball is at on or off depending on the given
   pixel state
        @param either DISPLAY_ON or DISPLAY_OFF */
void ball_display_update(tinygl_pixel_value_t pixel_state)
{
    ball_t ball = ball_get_state();
    tinygl_draw_point(ball.pos, pixel_state);
}

/** Turns the point that the ball is at on */
void ball_display_on(void)
{
    ball_display_update(DISPLAY_ON);
}

/** Turns the point that the ball is at off */
void ball_display_off(void)
{
    ball_display_update(DISPLAY_OFF);
}




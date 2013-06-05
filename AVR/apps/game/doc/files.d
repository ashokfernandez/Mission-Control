../../drivers/avr/timer.h: 

../../utils/task.h: ../../drivers/avr/timer.h

../../utils/task.c: ../../utils/task.h ../../drivers/avr/timer.h

../../utils/task.o: ../../utils/task.c

../../drivers/ledmat.h: 

../../drivers/display.h: 

../../drivers/display.c: ../../drivers/ledmat.h ../../drivers/display.h

../../drivers/display.o: ../../drivers/display.c

../../utils/font.h: 

../../utils/tinygl.h: ../../drivers/display.h ../../utils/font.h

../../utils/tinygl.c: ../../utils/tinygl.h ../../drivers/display.h ../../utils/font.h

../../utils/tinygl.o: ../../utils/tinygl.c

../../utils/boing.h: ../../utils/tinygl.h

ball.h: ../../utils/boing.h ../../utils/tinygl.h

crazy_pong.h: 

game_object_display.h: 

boundaries.h: 

player.h: 

paddle.h: ../../utils/tinygl.h

IR_comms.h: 

ball.c: ball.h crazy_pong.h game_object_display.h boundaries.h player.h paddle.h IR_comms.h

ball.o: ball.c

player.c: player.h crazy_pong.h

player.o: player.c

../../drivers/avr/ir_uart.h: 

../../drivers/avr/usart1.h: 

../../drivers/avr/timer0.h: 

../../drivers/avr/pio.h: 

../../drivers/avr/ir_uart.c: ../../drivers/avr/ir_uart.h ../../drivers/avr/usart1.h ../../drivers/avr/timer0.h ../../drivers/avr/pio.h

../../drivers/avr/ir_uart.o: ../../drivers/avr/ir_uart.c

../../drivers/avr/usart1.c: ../../drivers/avr/usart1.h

../../drivers/avr/usart1.o: ../../drivers/avr/usart1.c

../../drivers/avr/prescale.h: 

../../drivers/avr/prescale.c: ../../drivers/avr/prescale.h

../../drivers/avr/prescale.o: ../../drivers/avr/prescale.c

crazy_pong.c: crazy_pong.h ball.h paddle.h player.h game_object_display.h IR_comms.h

crazy_pong.o: crazy_pong.c

error_check.h: ball.h

IR_comms.c: IR_comms.h error_check.h player.h ball.h ../../utils/tinygl.h ../../utils/boing.h ../../drivers/avr/ir_uart.h crazy_pong.h

IR_comms.o: IR_comms.c

../../drivers/navswitch.h: 

../../fonts/font3x5_1.h: ../../utils/font.h

../../utils/pacer.h: 

game.c: ../../utils/tinygl.h ../../drivers/navswitch.h ../../utils/task.h ../../fonts/font3x5_1.h game_object_display.h paddle.h ../../utils/pacer.h ball.h ../../utils/boing.h boundaries.h player.h ../../drivers/avr/ir_uart.h ../../drivers/avr/timer0.h IR_comms.h error_check.h crazy_pong.h

game.o: game.c

../../drivers/avr/pio.c: ../../drivers/avr/pio.h

../../drivers/avr/pio.o: ../../drivers/avr/pio.c

../../drivers/avr/system.c: 

../../drivers/avr/system.o: ../../drivers/avr/system.c

../../utils/font.c: ../../utils/font.h

../../utils/font.o: ../../utils/font.c

../../drivers/ledmat.c: ../../drivers/avr/pio.h

../../drivers/ledmat.o: ../../drivers/ledmat.c

../../drivers/avr/bits.h: 

../../drivers/avr/timer0.c: ../../drivers/avr/timer0.h ../../drivers/avr/bits.h ../../drivers/avr/prescale.h

../../drivers/avr/timer0.o: ../../drivers/avr/timer0.c

error_check.c: error_check.h crazy_pong.h ../../utils/tinygl.h player.h IR_comms.h

error_check.o: error_check.c

game_object_display.c: game_object_display.h ../../utils/tinygl.h paddle.h ball.h player.h

game_object_display.o: game_object_display.c

paddle.c: crazy_pong.h paddle.h game_object_display.h

paddle.o: paddle.c

boundaries.c: boundaries.h crazy_pong.h ../../utils/tinygl.h paddle.h ball.h

boundaries.o: boundaries.c

../../drivers/avr/timer.c: ../../drivers/avr/timer.h

../../drivers/avr/timer.o: ../../drivers/avr/timer.c

../../drivers/avr/delay.h: 

../../drivers/navswitch.c: ../../drivers/navswitch.h ../../drivers/avr/delay.h ../../drivers/avr/pio.h

../../drivers/navswitch.o: ../../drivers/navswitch.c

../../utils/boing.c: ../../utils/boing.h

../../utils/boing.o: ../../utils/boing.c

../../utils/pacer.c: ../../drivers/avr/timer.h ../../utils/pacer.h

../../utils/pacer.o: ../../utils/pacer.c

game.out: ../../utils/task.o ../../drivers/display.o ../../utils/tinygl.o ball.o player.o ../../drivers/avr/ir_uart.o ../../drivers/avr/usart1.o ../../drivers/avr/prescale.o crazy_pong.o IR_comms.o game.o ../../drivers/avr/pio.o ../../drivers/avr/system.o ../../utils/font.o ../../drivers/ledmat.o ../../drivers/avr/timer0.o error_check.o game_object_display.o paddle.o boundaries.o ../../drivers/avr/timer.o ../../drivers/navswitch.o ../../utils/boing.o ../../utils/pacer.o


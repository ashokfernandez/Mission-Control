system.h: 

debugLed.h: 

lineSensors.h: 

motors.h: 

lcd.h: system.h

lcdText.h: 

mazeRobot.c: system.h debugLed.h lineSensors.h motors.h lcd.h lcdText.h

mazeRobot.o: mazeRobot.c

lcdText.c: lcd.h lcdText.h

lcdText.o: lcdText.c

pwm.h: 

motors.c: system.h motors.h pwm.h

motors.o: motors.c

pwm.c: system.h pwm.h

pwm.o: pwm.c

lcd.c: lcd.h

lcd.o: lcd.c

adc.h: system.h

adc.c: adc.h

adc.o: adc.c

lineSensors.c: system.h adc.h lineSensors.h debugLed.h lcdText.h

lineSensors.o: lineSensors.c

mazeRobot.out: mazeRobot.o lcdText.o motors.o pwm.o lcd.o adc.o lineSensors.o


env = Environment()
 
mcu = 'atmega32u2'
programmer = 'amkii'
if len(COMMAND_LINE_TARGETS):
	Target = COMMAND_LINE_TARGETS[0]
else:
	Target = ''
 
# Optimization level, can be [0, 1, 2, 3, s].
opt = "2"
 
env['CC'] = 'avr-gcc -mmcu='+mcu+' -O'+opt
env.Append(CCFLAGS = "-Wall")
#env.Append(CPPPATH = 'EPS_Library')
 
# Make elf
env.Program(Target+'.elf', [Glob('Library/*/*.c'), 'Tests/'+Target+'.c'])
 
# Make hex
env.Command(Target+".hex", Target+".elf", 'avr-objcopy -j .text -j .data -O ihex $SOURCE $TARGET')
 
# Show memory usage
env.Command(None, Target+".hex", "avr-size $SOURCE")
 
# Program the thing
env.Command(None, Target+".hex", 'sudo avrdude -c dragon_jtag -P usb -p m1280 -u -U flash:w:$SOURCE')
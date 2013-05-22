from Tkinter import *

VERSION = "0.1"
NUM_ANALOG_CHANNELS = 8
NUM_DIGITAL_CHANNELS = 8


class HardwareEmulator(object):
	name = ""
	value = None
	TkinterRoot = None
	GUI = None # Implemented by the subclasses

	def __init__(self, name):
		self.name = name


# Emulates an 8-ADC channel on a MCU and provides a slider widget to change the value of the ADC module
class ADC(HardwareEmulator):
	resolution = 10

	def __init__(self, TkinterRoot, name):
		# Save the name of the slider
		super(ADC, self).__init__(name)

		# Initiliase the slider widget
		self.value = IntVar(0)
		maxVal = (2 ** self.resolution) - 1
		self.GUI = Scale( TkinterRoot, label=self.name, variable = self.value, command=self.moved, from_=maxVal, to=0 )
		
	def moved(self, newVal):
		print self.name + " set to " + newVal

# Emulates a GPIO pin on a MCU that is connected to a push button
class GPIO_BUTTON(HardwareEmulator):
	
	def __init__(self, TkinterRoot, name):
		# Save the name of the slider
		super(GPIO_BUTTON, self).__init__(name)
		
		# Initiliase the button widget
		self.value = BooleanVar(False)
		self.GUI = Checkbutton( TkinterRoot, text=self.name, variable = self.value, onvalue=True, offvalue=False, command=self.click)

	def click(self):
		if(self.value.get()):
			clicked = "clicked"
		else:
			clicked = "released"
		
		print self.name + " " + clicked


# Create a Tkinter root variable and name the main window
root = Tk()
root.wm_title("Mission Control Hardware Emulator v" + VERSION)

# Add a big table at the top
title = Label(root, text="Mission Control | Hardware Emulator", font=("Helvetica", 18), anchor=NW, justify=LEFT)
title.grid(row=0, columnspan=8, pady=(15,20))

# Create an ADC objects to emulate a set of analog inputs
ANALOG = []
for i in range(NUM_ANALOG_CHANNELS):
	name = "Analog %i" % i
	adcObject = ADC(root, name)

	# Append the object to the list of objects and pack it into the container
	adcObject.GUI.grid(row=1, column=i, sticky=NW)
	ANALOG.append(adcObject)
	

# Create an array of GPIO objects to emulate a set of digital inputs
DIGITAL = []
for i in range(NUM_DIGITAL_CHANNELS):
	name = "Digital %i" % i
	gpioObject = GPIO_BUTTON(root, name)
	
	# Append the object to the list and pack it into the container
	gpioObject.GUI.grid(row=2, column=i, sticky=NW, pady=(20, 30))
	DIGITAL.append(gpioObject)




# var = "junk"
# scale = Scale( root, variable = var )
# 

# button = Button(root, text="Get Scale Value", command=sel)
# button.pack(anchor=CENTER)

# label = Label(root)
# label.pack()

root.mainloop()
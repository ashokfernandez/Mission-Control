from Tkinter import *
import socket
import sys

# Create a socket to send data down
try:
	s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
	s.connect(("localhost", 1414)) # SMTP
	socketConnected = True
except:
	print "\nemulator_gui.py: Could not connect to GUI server\n"
	sys.exit(0)



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
	resolution = 7

	def __init__(self, TkinterRoot, name):
		# Save the name of the slider
		super(ADC, self).__init__(name)

		# Initiliase the slider widget
		self.value = IntVar(0)
		maxVal = (2 ** self.resolution) - 1
		self.GUI = Scale( TkinterRoot, label=self.name, variable = self.value, command=self.moved, from_=maxVal, to=0 )
		
	def moved(self, newVal):
		s.send("-"+self.name +"-"+ newVal + "-\n")

# Emulates a GPIO pin on a MCU that is connected to a push button
class GPIO_BUTTON(HardwareEmulator):
	
	def __init__(self, TkinterRoot, name):
		# Save the name of the slider
		super(GPIO_BUTTON, self).__init__(name)
		
		# Initiliase the button widget
		self.value = BooleanVar(False)
		self.GUI = Button( TkinterRoot, text=self.name, command=self.click) #onvalue=True, offvalue=False, variable = self.value, 

	def click(self):
		if(self.value.get()):
			self.value.set(False)
			clicked = '1'
		else:
			self.value.set(True)
			clicked = '0'
		
		s.send("-"+self.name+"-"+ clicked + "-\n")


# Create a Tkinter root variable and name the main window
root = Tk()
root.wm_title("Mission Control Hardware Emulator v" + VERSION)

# Add a big table at the top
title = Label(root, text="Mission Control | Hardware Emulator", font=("Helvetica", 18), anchor=NW, justify=LEFT)
title.grid(row=0, columnspan=8, pady=(15,20))

# Create an ADC objects to emulate a set of analog inputs
ANALOG = []
for i in range(NUM_ANALOG_CHANNELS):
	name = "A-%i" % i
	adcObject = ADC(root, name)

	# Append the object to the list of objects and pack it into the container
	adcObject.GUI.grid(row=1, column=i, sticky=NW)
	ANALOG.append(adcObject)
	

# Create an array of GPIO objects to emulate a set of digital inputs
DIGITAL = []
for i in range(NUM_DIGITAL_CHANNELS):
	name = "D-%i" % i
	gpioObject = GPIO_BUTTON(root, name)
	
	# Append the object to the list and pack it into the container
	gpioObject.GUI.grid(row=2, column=i, sticky=NW, pady=(20, 30))
	DIGITAL.append(gpioObject)


def handler():
	try:
		# Send a close signal down the socket and wait for confirmation
		s.send('-X-\n')
		signal = s.read(100)

		# Check if the server has closed nicely
		if signal == "__CloseSocket":
			print "Closing connection with server"
			s.close()
			print "Server connection closed, closing GUI"

	except:
		# Catches the race condition if the server closes before the GUI
		print "Server connection closed, closing GUI"


	# Quit the program	
	root.quit()
	sys.exit(0)

# Add a handler for when the window is closed
root.protocol("WM_DELETE_WINDOW", handler)

# Enter the main loop
root.mainloop()
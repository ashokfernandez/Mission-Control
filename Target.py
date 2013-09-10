import bs4
import Pin

class Target(object):
	''' Class to encapsulate the properties of different target boards '''

	def __init__(self, name):
		self.name = name
		# self.architecture = architecture

		self.pins = {}
		self.mcu = None
		self.__nDigitalPins = 0
		self.__nAnaloguePins = 0

	def addPin(self, pin):
		''' Adds a pin to the instances list of avaliable pins'''
		# TODO: Find a better way to do this, this couples the target class too heavily with the
		# pin subclasses
		if isinstance(pin, Pin.AnaloguePin):
			self.__nAnaloguePins += 1
			self.pins[pin.name] = pin
		elif isinstance(pin, Pin.DigitalPin):
			self.__nDigitalPins += 1
			self.pins[pin.name] = pin
		else:
			raise Pin.InvalidPinTypeError("Pin %s is not valid, cannot add to Target %s" % (pin, self))
		

	def parseXML(self, filename):
		''' Parses the .xml file given in the filename and populates the fields of the target object'''
		
		# Open the xml file
		targetFile = open(filename, 'r')
		targetFileText = ''
		
		# Read the file
		for line in targetFile.readlines():
			targetFileText += line.strip()

		# Convert the file to a beautiful soup object
		targetXML = bs4.BeautifulSoup(targetFileText)

		# Get the mcu name
		self.mcu = targetXML.mcu.getText()
		
		# Add all the digital pins
		for pin in targetXML.pins.findAll('analogue'):
			NAME = pin['name']
			PORT = pin.port.getText()
			PIN = pin.pin.getText()
			CHANNEL = pin.channel.getText()
			aPin = Pin.AnaloguePin(NAME, PORT, PIN, CHANNEL)
			self.addPin(aPin)

		# Add all the digital pins
		for pin in targetXML.pins.findAll('digital'):
			NAME = pin['name']
			PORT = pin.port.getText()
			PIN = pin.pin.getText()
			dPin = Pin.DigitalPin(NAME, PORT, PIN)
			self.addPin(dPin)

	def hasPin(self, pinName):
		''' Returns true if the pin is part of the target, otherwise false'''
		return pinName in self.pins.keys()

		
	def getPin(self, pinName):
		''' Return the given pin, if it doesn't exist then None is returned'''
		pin = None
		try:
			pin = self.pins[pinName]
		except:
			print "Warning: Pin '%s' is not part of recipe %s" % (pinName, self.name)

		return pin




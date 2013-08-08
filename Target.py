import Pin

class Target(object):
	''' Class to encapsulate the properties of different target boards '''

	def __init__(self, name, architecture):
		self.name = name
		self.architecture = architecture

		self.pins = []

		self.__nDigitalPins = 0
		self.__nAnaloguePins = 0

	def addPin(self, pin):
		''' Adds a pin to the instances list of avaliable pins'''
		# TODO: Find a better way to do this, this couples the target class too heavily with the
		# pin subclasses
		if isinstance(pin, Pin.AnaloguePin):
			self.__nAnaloguePins += 1
			self.pins.append(pin)
		elif isinstance(pin, Pin.DigitalPin):
			self.__nDigitalPins += 1
			self.pins.append(pin)
		else:
			raise Pin.InvalidPinTypeError("Pin %s is not valid, cannot add to Target %s" % (pin, self))
		




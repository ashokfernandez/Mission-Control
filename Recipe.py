import bs4
import Pin

class Recipe(object):
	def __init__(self,name):
		self.name = name
		self.pins = []

	def parseXML(self, filename):
		# Open the xml file
		recipeFile = open(filename, 'r')
		recipeFileText = ''
		
		# Read the file
		for line in recipeFile.readlines():
			recipeFileText += line.strip()

		# Convert the file to a beautiful soup object
		recipeXML = bs4.BeautifulSoup(recipeFileText)

		# Loop through the pins and add them to the object
		for pin in recipeXML.findAll('pin'):
			if pin['type'] == "analogue":
				# Create a dummy pin with the name given in the recipie
				aPin = Pin.AnaloguePin(pin.getText(), 'FOO', -1, -1)
				self.pins.append(aPin)

			elif pin['type'] == "digital":
				# Create a dummy pin with the name given in the recipie
				dPin = Pin.DigitalPin(pin.getText(), 'FOO', -1)
				self.pins.append(dPin)

	def hasPin(self, pinName):
		''' Returns true if the pin is part of the recipe, otherwise false'''
		return pinName in self.pins.keys()

	def getPin(self, pinName):
		''' Return the given pin, if it doesn't exist then None is returned'''
		pin = None
		
		for p in self.pins:
			if p.name == pinName:
				pin = p

		if pin == None:
			print "Warning: Pin '%s' is not part of recipe %s" % (pinName, self.name)

		return pin

	def getPins(self):
		''' Returns a list of pins belonging to the recipe'''
		return self.pins
		

	def getConnections(self):
		''' Returns a list of pins connected to the recipe'''
		connections = []
		for pin in self.pins:
			connections.append(pin.getConnection())

		return connections
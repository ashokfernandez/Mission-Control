# SCONS BUILD SCRIPT
# ENEL400 Project
# Author: Ashok Fernandez (azf10@uclive.ac.nz)
# Date: 15/4/2013

inputFilename = "demo.xml"
outputFilename = "demoMain.c"

import shutil
from string import Template
import glob
import bs4
import sys
import Target
import Recipe

# Define the base directory for the source code and driver code
dir_Hal = "./HAL"
dir_Targets = dir_Hal + '/targets'
dir_Include = dir_Hal + '/include'
dir_Source = dir_Hal + '/src'
dir_Recipes = './recipes'
dir_Output = './generated'

# Original copy folder
dir_AVR8_src = dir_Source + '/AVR8/'
HAL_SOURCE = ['Analogue_AVR8.c', 'Digital_AVR8.c', 'Descriptors.c', 'USB_AVR8.c', 'USBMIDI_AVR8.c']

# Storage for source files
source = []
headers = []

# Error Strings
errorPrefix = "Error: "
error = {
	'no design tag' : errorPrefix + "The specified design file is invalid, no design tags were found",
	'no target board' : errorPrefix + "The design doesn't specify a target board",
	'target not matched' : errorPrefix + "Matching target file %s.xml could not be found",
	'no recipe tag' : errorPrefix + "A design must contain at least one recipe",
	'invalid pin' : errorPrefix + "Pin '%s' not found on target %s",
	'recipe not found' : errorPrefix + "Source for recipe '%s' couldn't be found"
}

# Open the design file and convert it to a BeautifulSoup object
designFile = open(inputFilename, 'r')
designFileText = ''
for line in designFile.readlines():
	designFileText += line.strip()

designXML = bs4.BeautifulSoup(designFileText)


# Check that the design file has a design in it
if designXML.design == None:
	sys.exit(error['no design tag'])
else:
	print "Checking design file..."

# Check that a target is specified for the design
if designXML.design.target  == None:
	sys.exit(error['no target board'])
else:
	print "Searching for target: %s..." % designXML.design.target.getText()

# Search the target folder for a matching target file
targets = glob.glob(dir_Targets + '/*.xml')
targetMatch = None

for target in targets:
	if target.find(designXML.design.target.getText()) > -1:
		targetMatch = target

# Check if a target match was found
if targetMatch == None:
	sys.exit(error['target not matched'] % designXML.design.target.getText())
else:
	print "Target file %s.xml found!" % designXML.design.target.getText()



# Check the design has recipes
if designXML.design.recipe == None:
	sys.exit(error['no recipe tag'])
else:
	print "Validating design..."

# Create the model of the target
targetModel = Target.Target(designXML.design.target.getText())
targetModel.parseXML(targetMatch)

recipes = []

# Validate the design by checking the pins in the design exist on the target and that the recipies exist
for recipe in designXML.findAll('recipe'):
	
	# Check the recipe exists
	recipeSource = glob.glob(dir_Recipes + '/' + recipe['name'] + '*.c')
	recipeHeader = glob.glob(dir_Recipes + '/' + recipe['name'] + '*.h')
	recipeXML    = glob.glob(dir_Recipes + '/' + recipe['name'] + '*.xml')
	
	# Print an error if it doesn't, otherwise add it to the list of source files
	if len(recipeSource) != 1 or len(recipeHeader) != 1 or len(recipeXML) != 1:
		sys.exit(error['recipe not found'] % recipe['name'])
	else:
		source.append(recipeSource[0])
		headers.append(recipeHeader[0])

	# Extract the recipe information
	recipeObject = Recipe.Recipe(recipe['name'])
	recipeObject.parseXML(recipeXML[0])
	recipes.append(recipeObject)

	# Check the connections required by the recipie actually exist on the target board
	for connection in recipe.findAll('connection'):
		validPin = targetModel.hasPin(connection.pin.getText())
		if not validPin:
			sys.exit(error['invalid pin'] % (connection.pin.getText(), targetModel.name))
		else:
			# Connect the design to the recipie pin
			recipeObject.getPin(connection['name']).connectTo(targetModel.getPin(connection.pin.getText()))


# If we've made it this far, the design must be ok
print "Design validated OK!"




# Generating code
print "Generating code output..."

# Open the template file and read it to a string
templateMain = open('main.c.template', 'r')
templateMainText = ''

for line in templateMain.readlines():
	templateMainText += line

# Create a template object from the main.c template
mainTemplate = Template(templateMainText)


# Generate the header string for the template
headerString = ''
for header in headers:
	headerBits = header.split('/')
	headerString += '#include "%s"\n' % headerBits[-1]

# Generate the pin string for the template that initilises the pins to use
pinString = ''
taskString = ''
for recipe in recipes:
	# Get all the connections to the recipie
	connections = recipe.getConnections()
	
	# Create the run function
	taskString += recipe.name + "("
	
	# Iterate over all the pins and render the connections to the pin and task strings
	for connection in connections:
		# Render the pin's initialiser and check if it's already in the pin string
		pinRender = connection.renderString()
		if pinString.find(pinRender) > -1:
			print "Warning: pin %s is connected to more than one recipe"
		else:
			pinString += pinRender

		# Add the parameter to the task function call
		taskString += connection.name + ','

	# Shave off the last comma and close the task string
	taskString = taskString[:-1]
	taskString += ");\n"


# Render the template
mainCode = mainTemplate.substitute(recipe_headers=headerString,
							 	   pins=pinString,
							       tasks=taskString)
# Write to a file
mainFile = open(dir_Output + '/' + outputFilename, 'w')
mainFile.write(mainCode)
mainFile.close()

# Generate addition to the makefile
makeString = 'SRC += '
makeSourcePrefix = '$(RECIPES_DIR)/'
for files in source:
	filename = files.split('/')[-1]
	makeString += makeSourcePrefix + filename + " "

# Write makefile addon
makeAddon = open(dir_Output + '/generated_source.mk', 'w')
makeAddon.write(makeString)
makeAddon.close()

# Copy HAL source files to the generated directory
for s in HAL_SOURCE:
	shutil.copy(dir_AVR8_src + '/' + s, dir_Output + '/')

print "Code generated OK!"


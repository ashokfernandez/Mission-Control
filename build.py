# SCONS BUILD SCRIPT
# ENEL400 Project
# Author: Ashok Fernandez (azf10@uclive.ac.nz)
# Date: 15/4/2013


# Define the base directory for the source code and driver code
dir_Source = "./src"
dir_HAL = dir_Source + "/HAL/"

class physicalTarget(name):
	self.name = name
	self.libs = []

	def setName(name):
		self.name = name

	def getName():
		return self.name

	def addLibrary(lib):
		self.libs.append(lib)

dir_EmulatorSource = dir_Source + dir_HAL + "Emulator/"
Emulator = physicalTarget("Emulator")
Emulator.addLibrary(Library('USB', [dir_EmulatorSource + "USB.c"]))

physicalTargets = {
	"EMULATOR" : Emulator,
	"OLIMEX32U4" : "Olimex32u4"
}

# Find the command line args that are valid build targets
validTargets = set(COMMAND_LINE_TARGETS).intersection(physicalTargets.keys())
validTargets = list(validTargets) # Convert set back to a list

# If there were no valid targets found, print an error message along with a list of valid targets then exit
if validTargets == []:
	print "\nNo valid targets supplied, please specify a target in the command line.\n"
	print "Valid targets are"
	for target in physicalTargets.keys():
		print "\t" + target
	print "\n"
	Exit(1)

# Otherwise create an environment variable for each target and specify the appropriate include paths for each target
targets = []

for target in validTargets:
	includePath = dir_Source + dir_HAL + physicalTargets[validTargets].getName + '/'
	targets.append(Environment(CPPPATH = includePath))





src_Lib = [ "junk" ]

# Append the directory and filetype to source files
src_Lib = [(src_Directory + x + src_FileType) for x in src_Lib]
print src_Lib

# Define the junk target
test = env.Program(target = 'junk', source = ['./src/hello.c'], LIBS=['junk'])

# Define the junk library
junkLib = env.Library('junk', src_Lib)

#Default(test) # Specify test as the default target

# C FLAGS
#env.Append(CCFLAGS='-O3')

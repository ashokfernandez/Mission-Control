import Utils


# Describes a processor architecture
class Architecture(object):
	''' Object to represent a processor family or architecture. An family of processors (such as AVR or ARM)
	will share a compiler, which is the main element of the architecture as far as the programmer is concerned'''
	def __init__(self, name):
		self.name = name
		self.compiler = None

	def __eq__(self, other):
		''' Checks to see if two architecture's are equal. Overloads the "==" operator'''
		return isinstance(other, self.__class__) and self.__dict__ == other.__dict__
		
	def getName(self):
		''' Returns the name of the architecture'''
		return self.name

	def setCompiler(self, compiler):
		''' Sets the compiler name for the architecture. Will check that the compiler is installed using the 'which {compiler}'
		command and will raise an error if it does not exist'''
		try:
			Utils.which(compiler)
			self.compiler = compiler
		except Utils.LocateExecutableError as e:
			print "Compiler '%s' couldn't be located. Check it is installed and on the system path"



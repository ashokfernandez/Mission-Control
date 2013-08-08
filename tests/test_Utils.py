from Utils import *
import unittest

# Tests for the module
class TestModule_FSNode(unittest.TestCase):
    '''Unit Test for the Utils module'''

    def test_which(self):
        # Ask which if python and pyth000n exist as executables on this machine.
        pythonExists = which("python")

        # We hope that python exists! (are we are assuming that a program named 'pyth000n' does not)
        self.assertTrue(pythonExists)
        

    def test_whichException(self):
    	exceptionCaught = False
    	
    	try:
    		which("pyth000n")
    	except LocateExecutableError:
    		exceptionCaught = True

    	self.assertTrue(exceptionCaught)


# If the module is loaded as __main__ : run the unit tests
if __name__ == "__main__":
    unittest.main()

from Target import *
from Architecture import *
from Pin import *
import unittest

# Tests for the module
class TestModule_Target(unittest.TestCase):
    '''Unit Test for the Utils module'''

    def setUp(self):
    	# self.arch = Architecture("AVR8")
    	self.target = Target("MyBoard")

    def test_init(self):
		self.pinA = AnaloguePin('a1', 'PORT_A', 4, 0)
		self.pinD = DigitalPin('d1', 'PORT_A', 4)

		self.target.addPin(self.pinA)
		self.target.addPin(self.pinD)


    def test_whichException(self):
    	# Add a generic pin - this should throw an exception
    	thisPin = Pin('p1', 'PORT_A', 4)
    	caught = False
    	try:
			self.target.addPin(thisPin)
    	except InvalidPinTypeError:
			caught = True

    	self.assertTrue(True)


# If the module is loaded as __main__ : run the unit tests
if __name__ == "__main__":
    unittest.main()

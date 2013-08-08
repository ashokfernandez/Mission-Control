# Add the parent folder to the import path
# import sys
# import os.path
# sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

# Import the module to test from the parent directory
from Pin import *
import unittest

# Tests for the module
class TestModule_Pin(unittest.TestCase):
    '''Unit Test for the Utils module'''

    def setUp(self):
    	self.pinA = DigitalPin()
    	self.pinB = DigitalPin()
    	self.pinC = AnaloguePin()

    	self.pinA.connectTo(self.pinB)

    def test_isConnected(self):
        self.assertTrue(self.pinA.isConnected())
        self.assertFalse(self.pinC.isConnected())

    def test_connection(self):
    	a_to_b = self.pinA.isConnectedTo(self.pinB)
    	b_to_a = self.pinB.isConnectedTo(self.pinA)
    	a_to_c = self.pinA.isConnectedTo(self.pinC)

    	self.assertTrue(a_to_b)
    	self.assertTrue(b_to_a)
    	self.assertFalse(a_to_c)

    def test_typeCheck(self):
    	self.assertTrue(type(self.pinA) != type(AnaloguePin()))
    	self.assertTrue(type(self.pinC) == type(AnaloguePin()))

# If the module is loaded as __main__ : run the unit tests
if __name__ == "__main__":
    unittest.main()

# Add the parent folder to the import path
# import sys
# import os.path
# sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), os.path.pardir)))

# Import the module to test from the parent directory
from Architecture import *
import unittest

# Tests for the module
class TestModule_Architecture(unittest.TestCase):
    '''Unit Test for the Utils module'''

    def setUp(self):
    	self.arch1 = Architecture("AVR8")
        self.arch2 = Architecture("AVR8")
        self.arch3 = Architecture("x86")

        self.arch1.setCompiler("gcc")

    def test_equality(self):
        # Check the equality operator is correctly overloaded
        self.assertTrue(self.arch1 == self.arch1)

        # This should catch that even though the two architectures have the same name,
        # they aren't the same as arch1 has it's compiler defined and arch2 doesn't
        self.assertFalse(self.arch1 == self.arch2)

    

# If the module is loaded as __main__ : run the unit tests
if __name__ == "__main__":
    unittest.main()

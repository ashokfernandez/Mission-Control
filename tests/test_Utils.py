from Utils import *
import unittest

# Tests for the module
class TestModule_FSNode(unittest.TestCase):
    '''Unit Test for the Utils module'''

    def test_which(self):
        # Ask which if python and pyth000n exist as executables on this machine.
        pythonExists = which("python")
        pyth000nExists = which("pyth000n")

        # We hope that python exists! (are we are assuming that a program named 'pyth000n' does not)
        self.assertTrue(pythonExists)
        self.assertFalse(pyth000nExists)


# If the module is loaded as __main__ : run the unit tests
if __name__ == "__main__":
    unittest.main()

from FSNode import *
import unittest


# Tests for the module
class TestModule_FSNode(unittest.TestCase):
    '''Unit Test for the FSNode module'''

    def setUp(self):
        # Name of the tester folder, location of the folder and a dummy architecture name
        name = "moduleTesterFiles"
        location = os.path.join(os.getcwd(), "tests", name)
        architecture = "foo"

        # First check that the test files path exists. Should be a folder with two files in
        # it; foo.c and foo.h
        self.assertTrue(os.path.isdir(location))

        # Instantiate an object of each type
        self.Api = Api(name, location)
        self.Implementation = Implementation(name, location, architecture)

    def test_api_h_files(self):
        # Check that the list of h files in the api is correct
        hFiles = self.Api.getHFiles()
        self.assertEqual(len(hFiles), 1)

        # Check the filename is right
        hFilePath = hFiles[0].split(os.sep)
        self.assertIn("foo.h", hFilePath)

    def test_implementation_h_files(self):
        # Check that the list of c files in the implementation is correct
        hFiles = self.Implementation.getHFiles()
        self.assertEqual(len(hFiles), 1)

        # Check the filename is right
        hFilePath = hFiles[0].split(os.sep)
        self.assertIn("foo.h", hFilePath)

    def test_implementation_c_files(self):
        # Check that the list of h files in the implementation is correct
        cFiles = self.Implementation.getCFiles()
        self.assertEqual(len(cFiles), 1)

        # Check the filename is right
        cFilePath = cFiles[0].split(os.sep)
        self.assertIn("foo.c", cFilePath)


# If the module is loaded as __main__ : run the unit tests
if __name__ == "__main__":
    unittest.main()

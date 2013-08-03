import os
from fnmatch import fnmatch


# Abstract base class for a file system node
class FSNode(object):
    def __init__(self, name, location):
        '''Root class for source files in the file system - File System Node (FSNode). Contains
        a name for the node, a location which is the absolute path to the node and dictionary
        to store the relevant file names for the node.

        Node metadata such as the name, location (and any subclass specific data e.g architecture)
        MUST be filled out when the node is instantiated - this is a defensive notion to stop incomplete
        being created, and gurantees that all methods which rely on that meta data will not fail.'''
        self.__name = name
        self.__location = location
        self.__files = {}

    # -----------------------------------------------------------------------------
    # --------------------------------------------------------------------- PRIVATE
    # -----------------------------------------------------------------------------

    def findFiles(self, pattern):
        '''Traverses the filesystem at the node's location looking for files matching a given pattern.
        Returns a list of strings containing the absolute path to the files that match'''

        matchingFiles = []

        # Walk the file system at the given location
        for self.__location, subdirs, files in os.walk(self.__location):
            for name in files:
                # If a file matches, add it to the list of matching files
                if fnmatch(name, pattern):
                    matchingFiles.append(os.path.join(self.__location, name))

        return matchingFiles

    # -----------------------------------------------------------------------------
    # ---------------------------------------------------------------------- PUBLIC
    # -----------------------------------------------------------------------------

    def setName(self, name):
        '''Sets the name of the file system node'''
        self.__name = name

    def setLocation(self, location):
        '''Sets the location (absolute path) of the file system node'''
        self.__location = location

    def getName(self):
        '''Returns the name of the file system node'''
        return self.__name

    def getLocation(self):
        '''Returns the location of the file system node'''
        return self.__location


# File system node which contains interface .h files for an API
class Api(FSNode):
    def __init__(self, name, location):
        '''Apis contain only a list of .h files which provice a interface to a module. In order to compile
        a corrosponding implementation must be matched to the api.'''

        # Initialise the fields specified in the base class constructor
        super(Api, self).__init__(name, location)

        # Add all the .h files in the current directory and all sub-directories to the files list
        self.__files = {
            'h': self.findFiles("*.h")
        }

    def getHFiles(self):
        '''Returns a list of the absolute paths to the .h files belonging to the node'''
        return self.__files['h']


# File system node which contains an implementation of an API
class Implementation(FSNode):
    def __init__(self, name, location, architecture):
        '''Implementations contain the name of the architecture that is being implemented, and the
        associated .c and .h files that belong to that Implementation'''

        # Initialise the fields specified in the base class constructor
        super(Implementation, self).__init__(name, location)

        # Add the architecture name to the object's properties
        self.__architecture = architecture

        # Add all the .h and .c files in the current directory and all sub-directories to the files list
        self.__files = {
            'c': self.findFiles("*.c"),
            'h': self.findFiles("*.h")
        }

    def getHFiles(self):
        '''Returns a list of the absolute paths to the .h files belonging to the node'''
        return self.__files['h']

    def getCFiles(self):
        '''Returns a list of the absolute paths to the .c files belonging to the node'''
        return self.__files['c']

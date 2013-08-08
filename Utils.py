import os
import unittest

# Exception class for when an executable is not found
class LocateExecutableError(Exception):
    ''' Exception thats thrown when the which command fails to find the requested executable'''
    def __init__(self, requestedExecutable):
        self.requestedExecutable = requestedExecutable



# Adapted from http://stackoverflow.com/questions/377017/test-if-executable-exists-in-python
def which(program):
    ''' Mimicks the function of the "which" utility on Unix like operating systems.
        Returns None of the executable does not exist, otherwise returns the absoulte
        path to the executable that would be executed if "program" was typed into the
        command line.
    '''

    def is_exe(fpath):
        ''' Inline function which returns True if a file is an executable, otherwise
            False is returned'''
        return os.path.isfile(fpath) and os.access(fpath, os.X_OK)

    pathToExecutable = None
    fpath, fname = os.path.split(program)

    if fpath:
        if is_exe(program):
            pathToExecutable = program
    else:
        for path in os.environ["PATH"].split(os.pathsep):
            path = path.strip('"')
            exe_file = os.path.join(path, program)
            if is_exe(exe_file):
                pathToExecutable = exe_file

    # If the executable wasn't found, raise an exception
    if pathToExecutable == None:
        raise LocateExecutableError("Unable to find an executable named '%s'. Make sure it is on the system path." % program)
    
    return pathToExecutable


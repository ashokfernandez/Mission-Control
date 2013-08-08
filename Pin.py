class InvalidPinTypeError(Exception):
    ''' Exception to handle a pin of an invalid type being handled by another object
    that doesn't know what to do with it'''

    def __init__(self, message):
        # Call the base class constructor with the parameters it needs
        Exception.__init__(self, message)


class Pin(object):

    def __init__(self):
        self.connectedTo = None

    def __connectTo(self, pin):
        self.connectedTo = pin

    def connectTo(self, pin):
        self.connectedTo = pin
        pin.__connectTo(self)

    def isConnected(self):
        return (self.connectedTo != None)

    def isConnectedTo(self, pin):
        return (self.connectedTo is pin)


class AnaloguePin(Pin):
    pass

class DigitalPin(Pin):
    pass


    


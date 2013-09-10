class InvalidPinTypeError(Exception):
    ''' Exception to handle a pin of an invalid type being handled by another object
    that doesn't know what to do with it'''

    def __init__(self, message):
        # Call the base class constructor with the parameters it needs
        Exception.__init__(self, message)


class Pin(object):

    def __init__(self, name, port, pin):
        self.name = name
        self.connectedTo = None
        self.port = str(port)
        self.pin = int(pin)

    def __connectTo(self, pin):
        self.connectedTo = pin

    def connectTo(self, pin):
        self.connectedTo = pin
        pin.__connectTo(self)

    def isConnected(self):
        return (self.connectedTo != None)

    def isConnectedTo(self, pin):
        return (self.connectedTo is pin)

    def getConnection(self):
        return self.connectedTo


class AnaloguePin(Pin):
    def __init__(self, name, port, pin, channel):
        super(AnaloguePin, self).__init__(name, port, pin)
        self.channel = int(channel)

    def renderString(self):
        ''' Returns a string which represents the pin and an initilised Pin_Analogue_t in C '''
        render = "static Pin_Analogue_t %s = {%s, %i, %i};\n" % (self.name, self.port, self.pin, self.channel)
        return render

class DigitalPin(Pin):
    def renderString(self):
        ''' Returns a string which represents the pin and an initilised Pin_Digital_t in C '''
        render = "static Pin_Digital_t %s = {%s, %i};\n" % (self.name, self.port, self.pin)
        return render

    


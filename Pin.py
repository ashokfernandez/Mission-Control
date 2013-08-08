
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


    


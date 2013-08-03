#include "DataTypes.h"
#include <stdbool.h>

void PyGuiBindings_update(void);

// Initialises a socket and waits for the GUI to connect
bool PyGuiBindings_initConnection(void);

// Closes the connection with the GUI over the given socket
void PyGuiBindings_closeConnection(void);

int PyGuiBindings_getDigital(Pin_analogue_t pin);
int PyGuiBindings_getDigital(Pin_digital_t pin);
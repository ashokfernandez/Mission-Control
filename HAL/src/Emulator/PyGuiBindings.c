/**
 * @file    PyBuiBindings.c
 * @author  Ashok Fernandez <azf10@uclive.ac.nz>
 * @date    23-05-2013
 * @breif   Simple TCP/IP server to connect bind the hardware abstraction layer to a Python GUI
 * 
 * Allows a server to be setup which the Python GUI can connect to to share information about the
 * the GUI. Calls to update should be made regularly
 * 
*/

////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// ------------------------------------------------------------------------ INCLUDES
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Library includes
#include <sys/socket.h>     // Socket definitions
#include <sys/types.h>      // Socket types
#include <sys/fcntl.h>      // Allows the socket to be set to non-blocking
#include <arpa/inet.h>      // inet (3) funtions
#include <unistd.h>         // Misc. UNIX functions
#include <errno.h>          // Error numbers
#include <stdlib.h>         // Basic functions
#include <string.h>         // String processing
#include <stdio.h>          // IO functions
#include <stdbool.h>         // True / False definitions

// Mission Control includes
#include "MessageStrings.h"        // Info and error message strings
#include "PyGuiBindings.h"  // Include function declarations
#include "DataTypes.h"      // Mission Control datatypes
#include "Target_Emulator.h" // Defines the amount of analogue and digital pins avaliable


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- DEFINITIONS
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Port to bind to
#define ECHO_PORT   (1414)

// Backlog for listen()
#define LISTENQ        (1024)

// Size of text buffer to store input
#define BUFFER_SIZE (1000)

// Input format i.e input that changes analogue channel 3 to value 123 would look like -A-3-123-
#define ANALOGUE_TOKEN 'A'
#define DIGITAL_TOKEN 'D'
#define INPUT_DELIMITER  "-"

// Token that the client sends if it wants the socket to close
#define SOCKET_CLOSE_TOKEN 'X'

// Signal to send down the socket to confirm the close
#define SOCKET_CLOSE_SIGNAL "__CloseSocket"



////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------------- DEFINITIONS
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Char buffer to store strings in
static char buffer[BUFFER_SIZE] = {'\0'};

// Store values for all the analogue and digital inputs on the GUI
static int ANALOGUE[NUM_ANALOGUE_PINS] = {0};
static int DIGITAL[NUM_ANALOGUE_PINS] = {0};

// Stores the reference to the connected socket
static int connection_socket;


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// --------------------------------------------------------------- PRIVATE FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

/** Writes a close signal to the socket to allow the client to end nicely
 * @param [buffer] input read from socket
 * @return false if an error occured, otherwise true
 */

int Socket_sendCloseSingal(void) {
    char    *closeSignal = SOCKET_CLOSE_SIGNAL;     // Message to send down the socket on close
    int nWritten;                                   // Number of chars written to the socket
    int nLeft;                                      // Number of chars left to write down the socket
    
    
    nLeft  = strlen(closeSignal);

    while ( nLeft > 0 ) {
        
        // Write the signal to the socket
        nWritten = write(connection_socket, buffer, nLeft);
        
        // Check if the write operation suceeded
        if ( nWritten <= 0 ) {
            if ( errno == EINTR )
                nWritten = 0;
            else
                return false;
        }
        
        // Mark of the chars sent and move the pointer forward if more chars need to be sent
        nLeft  -= nWritten;
        closeSignal += nWritten;
    }

    return true;
}

/** Processes captured strings and updates the values of analogue and digital pins that have changed
 * @param [buffer] input read from socket
 * @return false if an error occured, otherwise true
 */
int ProcessInput(char *buffer) {
    int          val, index;        // Index and value of data read from string
    int         *storageArray;      // Pointer to the array to store the read data
    char        *token;             // Tokens read from the input string
    
    // Spilt the tokens in the input string around the delimiter.
    token = strtok(buffer, INPUT_DELIMITER);
    
    // Check if a token was found 
    if (token != NULL)
    {
        // If the first charater is A it is an analogue channel followed by its new value
        if(*token == ANALOGUE_TOKEN){
            storageArray = ANALOGUE;
        }
        // If the first charater is A it is an analogue channel followed by its new value
        else if(*token == DIGITAL_TOKEN){
            storageArray = DIGITAL;
        }
        // Otherwise if the client was trying to close the socket
        else if(*token == SOCKET_CLOSE_TOKEN){
            PyGuiBindings_closeConnection();
            return false;
        }

        // Otherwise an error occured, return -1
        else{
            return false;
        }

        // Get the index value from the next token
        token = strtok (NULL, INPUT_DELIMITER);
        index = atoi(token);

        // Get the value from the next token
        token = strtok (NULL, INPUT_DELIMITER);
        val = atoi(token);

        // Store the value at the given index in the appropriate storage array
        *(storageArray+index) = val;
    }

    return true;
}


/**
 * Reads up to maxlen amount of input from the given socket into the buffer
 * @param   [socket] ID of the socket to read
 * @param   [buffer] buffer to read text into
 * @param   [maxlen] maximum amount characters to read
 * @return  number of characters read
 */
int Socket_readInput(char *buffer, size_t maxlen) {
    int     i;              // Counts how many chars were read from the socket
    int     numCharsRead;   // Number of characters read from read()
    char    c;              // Character read

    // Iterate over the input range and read charaters from the socket
    for ( i = 1; i < maxlen; i++ ) {
        
        // Read a character from the socket
        if ( (numCharsRead = read(connection_socket, &c, 1)) == 1 ) {
            // Save the charater to the given buffer 
            *buffer++ = c;
            // if its the end of the line stop reading
            if ( c == '\n' )
                break;
        }
        
        // If the character was a null byte stop reading characters
        else if ( numCharsRead == 0 ) {
            break;
        }

        // Else and error occurred, return -1
        else {
            if ( errno == EINTR )
                continue;
            return -1;
        }
    }

    // Increment i to account for the fact that we started counting at 0
    i++;

    // Return the number of chars read
    return i;
}


////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////
// ---------------------------------------------------------------- PUBLIC FUNCTIONS
////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////

// Checks the socket for input, and processes it for new information from the GUI
void PyGuiBindings_update(void){
    int         numCharsRead;       // Number of characters read from the socket

    // If a valid socket is open, try to read the input
    if(connection_socket > 0){
        // Check for some input
        numCharsRead = Socket_readInput(buffer, BUFFER_SIZE);

        // Keep reading the input socket to clear any backlog that may still exist
        while(numCharsRead > 0){
            ProcessInput(buffer);    
            numCharsRead = Socket_readInput(buffer, BUFFER_SIZE);
        }    
    }
    else{
        printf(PYGUIBINDINGS_INFO__UPDATE_WHEN_NO_CONNECTION);
    }
}

// Initialises a socket and waits for the GUI to connect
bool PyGuiBindings_initConnection(void) {
    int         listening_socket;       //  listening socket
    int         result;                 //  result of function calls, used for error checking
    short int   port;                   //  port number
    struct      sockaddr_in servaddr;   //  socket address structure


    //  Set the port number
    port = ECHO_PORT;
	
    //  Create the listening socket 
    listening_socket = socket(AF_INET, SOCK_STREAM, 0);
    if ( listening_socket < 0 ) {
        fprintf(stderr, PYGUIBINDINGS_ERROR__LISTENING_SOCKET_CREATE);
        exit(EXIT_FAILURE);
    }

    //  Set all bytes in socket address structure to zero, and fill in the relevant data members
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family      = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port        = htons(port);


    //  Bind our socket addresss to the listening socket, and call listen()
    result = bind(listening_socket, (struct sockaddr *) &servaddr, sizeof(servaddr));
    if ( result  < 0 ) {
        fprintf(stderr, PYGUIBINDINGS_ERROR__BIND_CALL_FAILED);
        exit(EXIT_FAILURE);
    }


    result = listen(listening_socket, LISTENQ);
    if ( result  < 0 ) {
        fprintf(stderr, PYGUIBINDINGS_ERROR__LISTEN_CALL_FAILED);
        exit(EXIT_FAILURE);
    }

    
    // Wait for a connection, then accept() it
    connection_socket = accept(listening_socket, NULL, NULL);
    if ( connection_socket  < 0 ) {
        fprintf(stderr, PYGUIBINDINGS_ERROR__ACCEPT_CALL_FAILED);
        exit(EXIT_FAILURE);
    }

    // Set the socket to be non-blocking on read calls
    fcntl(connection_socket, F_SETFL, O_NONBLOCK); 

    // Return the socketID so the caller can reference the created socket
    return true;
}

// Closes the connection with the GUI over the given socket
void PyGuiBindings_closeConnection(void){
    int     closeResult;        // Stores the result of the call to close

    // Write a close signal to let the client know the socket is closing
    Socket_sendCloseSingal();

    // Try to close the socket
    closeResult = close(connection_socket);

    // Check the close went OK
    if ( closeResult< 0 ) {
        fprintf(stderr, PYGUIBINDINGS_ERROR__CLOSE_CALL_FAILED);
        exit(EXIT_FAILURE);
    }

    printf(PYGUIBINDINGS_INFO__CLIENT_CONNECTION_LOST);
    connection_socket = -1;
}

int PyGuiBindings_getAnalogue(Pin_analogue_t pin){
    // Check the requested pin is in the bounds
    if(pin > -1 && pin < NUM_ANALOGUE_PINS){
        return ANALOGUE[pin];
    }

    // Invalid pin requested
    else{
        fprintf(stderr, PYGUIBINDINGS_ERROR__INVALID_ANALOGUE_PIN);
        return -1;
    }
}

int PyGuiBindings_getDigital(Pin_digital_t pin){
    // Check the requested pin is in the bounds
    if(pin > -1 && pin < NUM_DIGITAL_PINS){
        return DIGITAL[pin];
    }

    // Invalid pin requested
    else{
        fprintf(stderr, PYGUIBINDINGS_ERROR__INVALID_DIGITAL_PIN);
        return -1;
    }
}


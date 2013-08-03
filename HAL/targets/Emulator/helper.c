/*

  HELPER.C
  ========
  (c) Paul Griffiths, 1999
  Email: mail@paulgriffiths.net

  Implementation of sockets helper functions.

  Many of these functions are adapted from, inspired by, or 
  otherwise shamelessly plagiarised from "Unix Network 
  Programming", W Richard Stevens (Prentice Hall).

*/

#include "helper.h"
#include <sys/socket.h>
#include <unistd.h> 
#include <string.h>
#include <stdio.h>
#include <errno.h>

static int ANALOG[8] = {0};
static int DIGITAL[8] = {0};


/*  Read a line from a socket  */

ssize_t Readline(int sockd, void *vptr, size_t maxlen) {
    ssize_t n, rc;
    char    c, *buffer;

    buffer = vptr;

    for ( n = 1; n < maxlen; n++ ) {
	
		if ( (rc = read(sockd, &c, 1)) == 1 ) {
		    *buffer++ = c;
		    if ( c == '\n' )
				break;
		}
		else if ( rc == 0 ) {
		    if ( n == 1 )
				return 0;
		    else
				break;
		}
		else {
		    if ( errno == EINTR )
				continue;
		    return -1;
		}
    }

    *buffer = 0;
    return n;
}


/*  Write a line to a socket  */

ssize_t Writeline(int sockd, const void *vptr, size_t n) {
    size_t      nleft;
    ssize_t     nwritten;
    const char *buffer;

    buffer = vptr;
    nleft  = n;

    while ( nleft > 0 ) {
		if ( (nwritten = write(sockd, buffer, nleft)) <= 0 ) {
		    if ( errno == EINTR )
			nwritten = 0;
		    else
			return -1;
		}
			nleft  -= nwritten;
			buffer += nwritten;
    }

    return n;
}



/*  Write back to stdin  */

ssize_t ProcessInput(int sockd, char *buffer, size_t n) {
    size_t      nleft;
    ssize_t     nwritten;
    //char *buffer;
    int val, index;
    int stringLength;
    int *storageArray;

	char *pch = strtok (buffer,"-");
	if (pch != NULL)
	{
		if(*pch == 'A'){
			printf("ANALOGUE \n");
			storageArray = ANALOG;
		}
		else{
			printf("DIGITAL \n");
			storageArray = DIGITAL;
		}

		// Get the index
		pch = strtok (NULL, "-");
		index = atoi(pch);

		// Get the value
		pch = strtok (NULL, "-");
		val = atoi(pch);

		// Store the value at the given index
		*(storageArray+index) = val;
		printf("%i %i %i\n",index,val, *(storageArray+index) );

	}


			// nleft = -1;
		// }
		// else{
			// nwritten = 1;
			// buffer++;
		// }
			

		// nleft  -= nwritten;
    // }
    
    return n;
}


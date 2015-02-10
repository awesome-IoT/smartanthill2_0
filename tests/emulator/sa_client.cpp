/*******************************************************************************
    Copyright (c) 2015, OLogN Technologies AG. All rights reserved.
    Redistribution and use of this file in source and compiled
    forms, with or without modification, are permitted
    provided that the following conditions are met:
        * Redistributions in source form must retain the above copyright
          notice, this list of conditions and the following disclaimer.
        * Redistributions in compiled form must reproduce the above copyright
          notice, this list of conditions and the following disclaimer in the
          documentation and/or other materials provided with the distribution.
        * Neither the name of the OLogN Technologies AG nor the names of its
          contributors may be used to endorse or promote products derived from
          this software without specific prior written permission.
    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
    ARE DISCLAIMED. IN NO EVENT SHALL OLogN Technologies AG BE LIABLE FOR ANY
    DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
    (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
    LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
    OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
    DAMAGE
*******************************************************************************/


#include "sa-commlayer.h"
#include <stdio.h> 
#include <string.h> // TODO: remove asap (reason: used onle because of strlen() needed to construct an initial example)

#define BUF_SIZE 512


int main(int argc, char *argv[])
{
	printf("starting CLIENT...\n");
	printf("==================\n\n");

	char* msg = "Default message from client.";

	bool   fSuccess = false;

	if (argc > 1)
		msg = argv[1];

	// Try to open a named pipe; wait for it, if necessary. 

	fSuccess = communicationInitializeAsClient();
	if (!fSuccess)
		return -1;


	do
	{
		// Send a message to the pipe server. 
		int msgSize = strlen(msg) + 1;

		printf("Sending %d byte message: \"%s\"\n", msgSize, msg);

		fSuccess = sendMessage((unsigned char *)msg, msgSize);

		if (!fSuccess)
		{
			return -1;
		}

		printf("\nMessage sent to server, receiving reply as follows:\n");

		unsigned char rwBuff[BUF_SIZE];
		msgSize = getMessage(rwBuff, BUF_SIZE);

		if (!fSuccess)
		{
			return -1;
		}

		printf("\n<End of message, press X+ENTER to terminate connection and exit or ENTER to continue>");
		char c = getchar();
		if (c == 'x' || c == 'X')
			break;
	} while (1);

	communicationTerminate();

	return 0;
}


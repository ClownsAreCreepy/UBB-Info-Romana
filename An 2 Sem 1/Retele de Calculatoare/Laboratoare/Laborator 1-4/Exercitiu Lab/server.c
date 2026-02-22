/*
 * main.c
 *
 *  Created on: Nov 6, 2023
 *      Author: kiralycraft
 */
#include "modloader_meta.h"
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>        // For time()

static modloader_meta_t currentModule;
int init=0;

char theText[] = "Stefan cel Mare este considerat o personalitate marcanta a istoriei Romaniei, inzestrata cu mari calitati de om de stat, diplomat si conducator militar. Aceste calitati i-au permis sa treaca cu bine peste momentele de criza majora, generate fie de interventiile militare ale statelor vecine fie de incercari, din interior sau sprijinite din exteriorul tarii, de indepartare a sa de la domnie. In timpul domniei sale Moldova atinge apogeul dezvoltarii sale statale, cunoscand o perioada indelungata de stabilitate interna, prosperitate economica si liniste sociala.";


uint8_t modloader_handleFunction(float* __gradeAddress, int __peerConnection,void (*__loggingFunction)(const char*))
{
	uint16_t descLength = strlen(currentModule.moduleDesc); //Send without terminating ZERO
	uint16_t networkDescLength = htons(descLength);
	send(__peerConnection, &networkDescLength, sizeof(networkDescLength), 0);
	send(__peerConnection, currentModule.moduleDesc, descLength, 0);

	*__gradeAddress = 1.0;

	//===== LUNGIME ENUNT =====
	uint16_t _receivedEnuntLength;
	if (recv(__peerConnection,&_receivedEnuntLength, sizeof(_receivedEnuntLength),MSG_WAITALL) <= 0)
	{
		return 0;
	}

	*__gradeAddress = 3.0; // Managed to connect and send *something*

	if (ntohs(_receivedEnuntLength) == descLength)
	{
		*__gradeAddress = 5.0;
	}
	else
	{
		printf("%s received %d for enunt length but expected %d\n",currentModule.moduleName,ntohs(_receivedEnuntLength),descLength);
		return 0;
	}

	//==== SIRUL DE CARACTERE ====
	// Seed the random number generator

	// Calculate the description length without the terminating zero
	uint16_t textLength = strlen(theText);
	uint16_t totalSent = 0;
	uint16_t offset = 0;

	while (1)
	{
	    // Generate a random number between 1 and 5
	    uint8_t N = (rand() % 5) + 1;

	    // Adjust N if the remaining data is less than N
	    if (N >= (textLength - totalSent))
	        N = textLength - totalSent;

	    // Send N as a single byte to indicate the length of the upcoming snippet
	    ssize_t sentBytes = send(__peerConnection, &N, sizeof(N), 0);
	    if (sentBytes != sizeof(N)) {
	        // Handle send error
	        break;
	    }

	    if (N == 0)
	    {
	    	break;
	    }

	    // Send N bytes from moduleDesc starting at the current offset
	    sentBytes = send(__peerConnection, theText + offset, N, 0);
	    if (sentBytes != N)
	    {
	        // Handle send error
	        break;
	    }

	    // Update the total bytes sent and the offset
	    totalSent += N;
	    offset += N;
	}
	//======= LUNGIME SIR DE CARACTERE ========
	printf("%s sent %d bytes in total for the random text\n",currentModule.moduleName,textLength);
	uint16_t _receivedTextLength;
	if (recv(__peerConnection,&_receivedTextLength, sizeof(_receivedTextLength),MSG_WAITALL) <= 0)
	{
		return 0;
	}

	*__gradeAddress = 5.25; //Received something but incorrect

	if (ntohs(_receivedTextLength) == textLength)
	{
		*__gradeAddress = 7.0;
	}
	else
	{
		printf("%s received %d for text length but expected %d\n",currentModule.moduleName,ntohs(_receivedTextLength),textLength);
		return 0;
	}

	//======= SUMA POZITIILE LUI A ========
	uint32_t _sum_of_indices = 0;

	for (int i = 0; theText[i] != '\0'; i++)
	{
		if ((theText[i] >= 'a' && theText[i] <= 'z') || (theText[i] >= 'A' && theText[i] <= 'Z'))
		{
			_sum_of_indices += i;
		}
	}

	uint32_t _receivedPositionSum;
	if (recv(__peerConnection,&_receivedPositionSum, sizeof(_receivedPositionSum),MSG_WAITALL) <= 0)
	{
		return 0;
	}

	*__gradeAddress = 7.5;

	if (ntohl(_receivedPositionSum) == _sum_of_indices)
	{
		*__gradeAddress = 10.0;
		return 1;
	}
	else
	{
		printf("%s received %d for indices sum but expected %d\n",currentModule.moduleName,ntohl(_receivedPositionSum),_sum_of_indices);
		return 0;
	}

    return 1;
}

modloader_meta_t* modloader_main()
{
	if (init == 0)
	{
		currentModule.moduleAuthor = "Alex :)";
		currentModule.moduleDesc =
				"Serverul va trimite acest enunt. Serverul asteapta apoi un numar care reprezinta lungimea enuntului. "
				"Apoi, pe aceeasi conexiune, serverul trimite un sir de caractere pe bucati. Fiecare bucata are maxim 255 de caractere, dar minimul nu este garantat. "
				"Dupa ce serverul a trimis tot sirul de caractere dorit, asteapta sa primeasca un numar care reprezinta lungimea totala a sirului trimis. Odata confirmat, "
				"serverul asteapta suma pozitiilor absolute din sir unde se gasesc litere mici sau mari.\0";
		currentModule.moduleName = "Character frenzy\0";
		currentModule.moduleTopic = "TCP";
		currentModule.handleFunction = &modloader_handleFunction;
		init = 1;
	}

	return &currentModule;
}



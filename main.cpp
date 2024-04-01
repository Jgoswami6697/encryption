/*
* FILE : main.c
* PROJECT : SENG2030 - Assignment #1
* PROGRAMMER : Keval Patel
* FIRST VERSION : 15-01-2024
* DESCRIPTION : This main.c file works in conjunction with the cryptographic functions declared in cryptoFunction.h and defined in cryptoFunction.c.
*/
#include <stdio.h>
#include <string.h>
#include "cryptoFunction.h"

int main(int argc, char* argv[])
{

	if (argc == 2 || argc == 3)
	{
		char* filename = argv[argc - 1];

		//Check for switch specified 
		if (argc == 2 || (argc == 3 && strcmp(argv[1], "-encrypt") == 0 || strcmp(argv[1], "") == 0))
		{
			encryptFile(filename);
		}
		else if (strcmp(argv[1], "-decrypt") == 0)
		{
			decryptFile(filename);
		}
		else
		{
			printf("Invalid switch specified.\n");
		}
	}
	else
	{
		printf("Usage: %s [-encrypt / -decrypt] file_name \n", argv[0]);
	}

	return 0;
}


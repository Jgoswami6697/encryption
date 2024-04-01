/*
* FILE : cryptoFunction.c
* PROJECT : SENG2030 - Assignment #1
* PROGRAMMER : 
* FIRST VERSION : 15-01-2024
* DESCRIPTION : This file contains the essential code for encrypting and decrypting files, following the specific cryptographic schemes outlined in the assignment.
*/

#include <stdio.h>
#include <string.h>
#include "cryptoFunction.h"

#pragma warning(disable: 4996)

/*
* FUNCTION: encryptFile(const char* filename)
* DESCRIPTION: The encryptFile function processes a given input file, encrypts its content based on a specified cryptographic scheme, and creates a new ".crp" file with the encrypted content. The encryption involves replacing tabs with "TT," adjusting character values, and converting the result to hexadecimal format.
* PARAMETERS: const char* filename
* RETURNS: It does not return any value
*/
void encryptFile(const char* filename)
{
	char record[MAX_SIZE] = { 0 };

	//Change extension to .crp
	char new_filename[100];
	strcpy(new_filename, filename);
	char* period = strrchr(new_filename, '.');			//Look for the period. strrchr will return a NULL value if it does not find "."

	if (period != NULL)
	{
		strcpy(period + 1, "crp");					//Replace the file extension with crp
	}
	else
	{
		strcat(new_filename, ".crp");
	}

	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	if ((inputFile = fopen(filename, "r")) == NULL)		//Read each line from the input files
	{
		printf("Error opening the file \n");
	}

	if ((outputFile = fopen(new_filename, "w")) == NULL)		//Read each line from the input files
	{
		printf("Error creating the encrypted file \n");
	}

	while (fgets(record, sizeof(record), inputFile) != NULL)
	{
		for (int i = 0; i < strlen(record); i++)
		{
			if (record[i] == '\t')
			{
				fputs("TT", outputFile); // TAB encryption
			}
			else if (record[i] == '\n' || record[i] == '\r')
			{
				fputc(record[i], outputFile); // Write newline and carriage return characters directly
			}
			else
			{
				int outChar = (int)record[i] - 16;
				if (outChar < 32)
				{
					outChar = (outChar - 32) + 144;
				}
				fprintf(outputFile, "%02X", outChar);
			}
		}

		fputc('\n', outputFile);		//Add a new line at the end of each line.
	}

	if (fclose(inputFile) && fclose(outputFile) != 0)
	{
		printf("Error closing the files");
	}
}

/*
* FUNCTION: decryptFile(const char* filename)
* DESCRIPTION: The decryptFile function takes the filename of an encrypted file, decrypts its content based on the specified scheme, and creates a new * ".txt" file with the decrypted content. It handles special cases like "TT" for tabs and adjusts characters accordingly.
* PARAMETERS: const char* filename
* RETURNS: It does not return any value
*/
void decryptFile(const char* filename)
{
	char record[MAX_ASCII_SIZE];

	//Change extension to .txt
	char new_txtFile[100];
	strcpy(new_txtFile, filename);
	char* period = strrchr(new_txtFile, '.');			//Look for the period. strrchr will return a NULL value if it does not find "."

	if (period != NULL)
	{
		strcpy(period + 1, "txt");					//Replace the file extension with crp
	}
	else
	{
		strcat(new_txtFile, ".txt");
	}

	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	if ((inputFile = fopen(filename, "r")) == NULL)
	{
		printf("Error opening the encrypted file \n");
	}

	if ((outputFile = fopen(new_txtFile, "w")) == NULL)
	{
		printf("Error creating the decrypted file \n");
	}

	while (fgets(record, sizeof(record), inputFile) != NULL)
	{
		for (int i = 0; i < strlen(record); i += 2)
		{
			if (record[i] == 'T' && record[i + 1] == 'T')
			{
				int tab = 9;
				char cTab = tab;
				fputc(cTab, outputFile);
			}
			else if (record[i] == '\n' || record[i] == '\r')
			{
				fputc(record[i], outputFile);
			}
			else
			{
				int faceValue = (record[i] >= 'A' && record[i] <= 'F') ? (record[i] - 'A' + 10) : (record[i] - '0');
				int secondChar = (record[i + 1] >= 'A' && record[i + 1] <= 'F') ? (record[i + 1] - 'A' + 10) : (record[i + 1] - '0');
				int outChar = (faceValue * 16) + secondChar + 16;

				if (outChar > 127)
				{
					outChar = (outChar - 144) + 32;
				}

				fprintf(outputFile, "%c", outChar);
			}
		}

		fputc('\n', outputFile);		//Add a new line at the end of each line.
	}

	if (fclose(inputFile) && fclose(outputFile) != 0)
	{
		printf("Error closing the files");
	}
}

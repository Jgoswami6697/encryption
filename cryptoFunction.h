/*
* FILE : cryptoFunction.h
* PROJECT : SENG2030 - Assignment #1
* PROGRAMMER : Keval Patel
* FIRST VERSION : 15-01-2024
* DESCRIPTION : It includes constant definitions for MAX_SIZE and MAX_ASCII_SIZE and declares two functions, encryptFile and decryptFile, which are defined * in the implementation files
*/

#ifndef CRYPTOFUNCTIONS_H
#define CRYPTOFUNCTIONS_H

#define MAX_SIZE 120
#define MAX_ASCII_SIZE 255

void encryptFile(const char* filename);
void decryptFile(const char* filename);

#endif


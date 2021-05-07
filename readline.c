
/*
    Name: readline.c
    Purpose: Defines read_line function for clearing character streams
    Author: grivera64
    Date: 04/07/2021

*/

#include <stdio.h>
#include <ctype.h>
#include "readline.h"

/*

Reads in a String (char array of size n) from the terminal
and stores it inside of the provided char array

*/

int read_line(char str[], int n)
{

    //local variables
    int ch, i = 0;

    //Skips the white-spaces characters
    //at the beginning of the user defined input
    while (isspace(ch = getchar()));

    while (ch != '\n' && ch != EOF)
    {

        if (i < n)
        {

            str[i++] = ch;

        }

        ch = getchar();

    }

    str[i] = '\0';
    return i;

} //end of read_line
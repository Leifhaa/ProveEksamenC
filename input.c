//
// Created by Leifh on 31/10/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/input.h"
#include "include/inputParser.h"
#define MAX_INPUT_SZ 256




//Retrieve a int val from the user which is within range
int getInputInRange(int minVal, int maxVal){
    char    cBuff[MAX_INPUT_SZ];
    int     tmpInput;

    for (; ;){
        printf("Please enter a integer from %d to %d\r\n", minVal, maxVal);
        fgets(cBuff, sizeof(cBuff), stdin);
        /* Remove trailing newline, if there. */
        if ((strlen(cBuff) > 0) && (cBuff[strlen (cBuff) - 1] == '\n')){
            cBuff[strlen (cBuff) - 1] = '\0';
        }


        if (tryParseInt(cBuff, &tmpInput)){
            //Valid int input. Check in range
            if (minVal <= tmpInput && tmpInput <= maxVal){
                break;
            }
        }
        printf("Invalid integer input!\r\n");
    }
    return tmpInput;
}

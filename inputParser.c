//
// Created by Leifh on 31/10/2020.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "include/input.h"
#define MAX_NAME_SZ 256

//Inspired by: https://stackoverflow.com/questions/14176123/correct-usage-of-strtol (but not equal)
int tryParseInt(const char *cInput, int *parsed){
    char    *endPtr;
    *parsed = strtol(cInput, &endPtr, 0);
    if (endPtr == cInput || *endPtr != '\0'){
        return 0;
    }
    if ((parsed == INT_MAX || parsed == INT_MIN) && errno == ERANGE)
    {
        return 0;
    }
    return 1;
}
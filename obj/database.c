//
// Created by Leifh on 27/10/2020.
//
#include <stdio.h>
#include "../include/database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#define MAX_NAME_SZ 256



typedef struct _NODE{
    struct _NODE *pNext;
    struct _NODE *pPrev;
    char szName[80];
} NODE;

typedef struct _DATABASE{
    struct _NODE *pHead;
    struct _NODE *pTail;
    long iSize;
} DATABASE;

int PrintMe(){
    printf("Hello from database!");
}

int CreateDatabase(int *iDbHwnd)
{
    printf("Created database!");
    DATABASE *newDb = malloc(sizeof(DATABASE));
    if (newDb == NULL){
        printf("Failed to malloc database");
        return 0;
    }
    newDb->pHead = NULL;
    newDb->pTail = NULL;
    newDb->iSize = 0;
    //Casting to an int as main doesn't know the database struct.
    *iDbHwnd = (int)newDb;
    return 1;
}


int AddEntry(int iDbHwnd){
    //See: https://stackoverflow.com/questions/13542055/how-to-do-scanf-for-single-char-in-c
    char name[MAX_NAME_SZ];
    printf("Enter name: ");
    fgets(name, MAX_NAME_SZ, stdin);
    /* Remove trailing newline, if there. */
    if ((strlen(name) > 0) && (name[strlen (name) - 1] == '\n')){
        name[strlen (name) - 1] = '\0';
    }
    printf("Your name is %s.", name);

    DATABASE* dbHandle = (DATABASE*)iDbHwnd;
    NODE *pNewNode = malloc(sizeof(NODE));
    if (pNewNode == NULL){
        printf("Failed to malloc new entry");
        return 0;
    }
    strcpy(pNewNode->szName, name);
    if (dbHandle->pHead == NULL){
        //First entry
        dbHandle->pHead = pNewNode;
        dbHandle->pTail = pNewNode;

        pNewNode->pPrev = NULL;
        pNewNode->pNext = NULL;
    }
    else{
        dbHandle->pTail->pNext = pNewNode;
        pNewNode->pPrev = dbHandle->pTail;
        dbHandle->pTail = pNewNode;
        pNewNode->pNext = NULL;
    }
    dbHandle->iSize++;
    return 1;
}

int CountRecords(int iDbHwnd){
    DATABASE* dbHandle = (DATABASE*)iDbHwnd;
    return dbHandle->iSize;
}

void PrintDatabase(int iDbHwnd){
    DATABASE* dbHandle = (DATABASE*)iDbHwnd;
    int index = 0;
    NODE *pTmp = dbHandle->pHead;
    while (pTmp != NULL){
        index++;
        printf("[%d] - %s \r\n", index, pTmp->szName);
        pTmp = pTmp->pNext;
    }
}

//Inspired by: https://stackoverflow.com/questions/14176123/correct-usage-of-strtol (but not equal)
int parseLong(const char *cInput, int *parsed){
    char *endPtr;
    *parsed = strtol(cInput, &endPtr, 0);
    if (endPtr == cInput || *endPtr != '\0'){
        return 0;
    }
    if ((parsed == LONG_MAX || parsed == LONG_MIN) && errno == ERANGE)
    {
        return 0;
    }
    return 1;
}

void DeleteRecord(int iDbHwnd){
    printf("Enter a index record to delete\r\n");
    PrintDatabase(iDbHwnd);
    DATABASE* dbHandle = (DATABASE*)iDbHwnd;
    char cInput[10];
    int iInput = -1;

    while (iInput < 0 || iInput > dbHandle->iSize){
        printf("Enter a number between 1-5:");
        fgets(cInput, sizeof(cInput), stdin);
        /* Remove trailing newline, if there. */
        if ((strlen(cInput) > 0) && (cInput[strlen (cInput) - 1] == '\n')){
            cInput[strlen (cInput) - 1] = '\0';
        }
        int tmpInput = 0;
        if (parseLong(cInput,&tmpInput)){
            iInput = tmpInput;
        }
    }

    
}





//
// Created by Leifh on 27/10/2020.
//
#include <stdio.h>
#include "../include/database.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

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

}


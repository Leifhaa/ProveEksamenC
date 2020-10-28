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
} DATABASE;

int PrintMe(){
    printf("Hello from database!");
}

int CreateDatabase()
{
    printf("Created database!");
    DATABASE *newDb = malloc(sizeof(DATABASE));
    if (newDb == NULL){
        printf("Failed to malloc database");
        return 0;
    }
    newDb->pHead = NULL;
    newDb->pTail = NULL;
    //Casting to an int as main doesn't know the database struct.
    return (int)newDb;
}


int AddEntry(int iDbHwnd, char *szName){
    //Todo: free it.
    char *name = malloc(MAX_NAME_SZ);
    if (name == NULL){
        printf("Out of memory\r\n");
        return 1;
    }
    printf("Enter name: ");
    fgets(name, MAX_NAME_SZ, stdin);
    /* Remove trailing newline, if there. */
    if ((strlen(name) > 0) && (name[strlen (name) - 1] == '\n'))
        name[strlen (name) - 1] = '\0';

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
    }
    else{
        dbHandle->pTail->pNext = pNewNode;
        pNewNode->pPrev = dbHandle->pTail;
        dbHandle->pTail = pNewNode;
    }
    return 1;
}


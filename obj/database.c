//
// Created by Leifh on 27/10/2020.
//
#include <stdio.h>
#include "../include/database.h"
#include "../include/input.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
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
        printf("[%d] - %s \r\n", index, pTmp->szName);
        index++;
        pTmp = pTmp->pNext;
    }
}


void DeleteRecord(int iDbHwnd){
    //If no records, return already
    DATABASE*   dbHandle = (DATABASE*)iDbHwnd;
    if (dbHandle->iSize == 0){
        printf("No records in database yet!\r\n");
        return;
    }
    PrintDatabase(iDbHwnd);
    printf("Enter a index record to delete\r\n");

    int iInput = getInputInRange(0, dbHandle->iSize - 1);
    NODE *tmpNode = dbHandle->pHead;
    for (int i = 0; i < iInput; i++){
        assert(tmpNode->pNext != NULL);
        tmpNode = tmpNode->pNext;
    }
    if (dbHandle->pHead == dbHandle->pTail){
        //Only one record
        dbHandle->pHead = NULL;
        dbHandle->pTail = NULL;
    }
    else {
        //Database has multiple records
        if (tmpNode == dbHandle->pHead){
            //Deleting head
            tmpNode->pNext->pPrev = NULL;
            dbHandle->pHead = tmpNode->pNext;
        }
        else if (tmpNode == dbHandle->pTail){
            //Deleting tail
            tmpNode->pPrev->pNext = NULL;
            dbHandle->pTail = tmpNode->pPrev;
        }
        else{
            //Deleting body
            tmpNode->pPrev->pNext = tmpNode->pNext;
            tmpNode->pNext->pPrev = tmpNode->pPrev;
        }
    }
    free(tmpNode);
    tmpNode = NULL;
    dbHandle->iSize--;
}





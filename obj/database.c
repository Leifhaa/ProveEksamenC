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
#include <stdio.h>
#include <stdlib.h>
#define MAX_NAME_SZ 256
#define dbFileName "db.dat"



typedef struct _NODE{
    struct _NODE *pNext;
    struct _NODE *pPrev;
    char szName[MAX_NAME_SZ];
} NODE;

typedef struct _DATABASE{
    struct _NODE *pHead;
    struct _NODE *pTail;
    long iSize;
} DATABASE;


int CreateDatabase(int *iDbHwnd)
{
    printf("Created database!\r\n");
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

int inputRecord(int iDbHwnd){
    char name[MAX_NAME_SZ];
    printf("Enter name: ");
    fgets(name, MAX_NAME_SZ, stdin);
    createRecord(iDbHwnd, name);
}

int createRecord(int iDbHwnd, char *name){
    //See: https://stackoverflow.com/questions/13542055/how-to-do-scanf-for-single-char-in-c
    /* Remove trailing newline, if there. */
    if ((strlen(name) > 0) && (name[strlen (name) - 1] == '\n')){
        name[strlen (name) - 1] = '\0';
    }

    NODE *pNewNode = malloc(sizeof(NODE));
    if (pNewNode == NULL){
        printf("Failed to malloc new entry");
        return 0;
    }
    strcpy(pNewNode->szName, name);
    saveRecord(iDbHwnd, (int) pNewNode);
    return 1;
}

int saveRecord(int iDbHwnd, int iNode){
    DATABASE* dbHandle = (DATABASE*)iDbHwnd;
    NODE* pNode =(NODE *)iNode;
    if (dbHandle->pHead == NULL){
        //First entry
        dbHandle->pHead = pNode;
        dbHandle->pTail = pNode;

        pNode->pPrev = NULL;
        pNode->pNext = NULL;
    }
    else{
        dbHandle->pTail->pNext = pNode;
        pNode->pPrev = dbHandle->pTail;
        dbHandle->pTail = pNode;
        pNode->pNext = NULL;
    }
    dbHandle->iSize++;
}



int CountRecords(int iDbHwnd){
    DATABASE* dbHandle = (DATABASE*)iDbHwnd;
    return dbHandle->iSize;
}

void PrintAllRecords(int iDbHwnd){
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
    PrintAllRecords(iDbHwnd);
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


int deleteDatabase(int idbHwnd){
    DATABASE*   dbHandle = (DATABASE*)idbHwnd;
    if (dbHandle->iSize != 0){
        //Has records
        while (dbHandle->pHead != dbHandle->pTail){
            dbHandle->pHead = dbHandle->pHead->pNext;
            free(dbHandle->pHead->pPrev);
            dbHandle->pHead->pPrev = NULL;
            dbHandle->iSize--;
        }
        //Head is equal to tail
        free(dbHandle->pHead);
        dbHandle->pHead = NULL;
        dbHandle->pTail = NULL;
        dbHandle->iSize--;
    }
    free(dbHandle);
    dbHandle = NULL;
    printf("Deleted\r\n");
}

int printNode(int iDbHwnd){
    DATABASE*   dbHandle = (DATABASE*)iDbHwnd;
    if (dbHandle->iSize == 0){
        printf("Database is empty!\r\n");
        return 0;
    }
    int iInput = getInputInRange(0, dbHandle->iSize - 1);
    NODE *pTmpNode = dbHandle->pHead;;
    for (int i = 0; i < iInput; i++){
        pTmpNode = pTmpNode->pNext;
    }
    printf("Node text: %s\r\n", pTmpNode->szName);
}

int writeToDisk(int dbHwnd){
    DATABASE*   dbHandle = (DATABASE*)dbHwnd;
    FILE        *fp;
    fp = fopen(dbFileName, "wb");

    if (fp != NULL){
        NODE *pTmpNode = dbHandle->pHead;
        while (pTmpNode != NULL){
            fprintf(fp, "%s\n", pTmpNode->szName);
            pTmpNode = pTmpNode->pNext;
        }
        fclose(fp);
    }
}

int readFromDisk(int dbHwnd){
    //Todo: Add debugger with proper errno.
    DATABASE*   dbHandle = (DATABASE*)dbHwnd;
    FILE        *fp;

    fp = fopen(dbFileName, "rb");
    if (fp != NULL){
        //Set the file position of the stream to offset end file.
        char cBuff[MAX_NAME_SZ];
        while (fgets(cBuff, MAX_NAME_SZ, fp)){
            //Read from current file position
            createRecord(dbHwnd, cBuff);
        }
        fclose(fp);
    }
}




#include <stdio.h>
#include <stdlib.h>
#include "../include/database.h"
#include "../include/input.h"

void printMenu(){
    printf("Welcome to main menu! Please enter a number between [1-5]\r\n");
    printf("[1] - Add element to database\r\n");
    printf("[2] - Find element in database\r\n");
    printf("[3] - Count number of elements in database\r\n");
    printf("[4] - Delete element from database\r\n");
    printf("[5] - Exit\r\n");
    printf("[6] - Delete database\r\n");

}


int main() {
    setbuf(stdout, 0);
    int iInput = 0;
    int dbHwnd = 0;

    int iOk = CreateDatabase(&dbHwnd);
    if (iOk == 0){
        printf("Failed to initialize database");
    }
    else{
        readFromDisk(dbHwnd);
        while (iInput != 5){
            printMenu();
            iInput = getInputInRange(1,6);
            printf("Input selected(%d)\r\n",iInput);
            switch(iInput){
                case 1:
                    printf("Add element selected\r\n");
                    inputRecord(dbHwnd);
                    break;
                case 2:
                    printf("Find element selected\r\n");
                    printNode(dbHwnd);
                    break;
                case 3:
                    printf("Count elements selected\r\n");
                    int dbSize = CountRecords(dbHwnd);
                    printf("Size is: %d\r\n", dbSize);
                    break;
                case 4:
                    printf("Delete element selected\r\n");
                    DeleteRecord(dbHwnd);
                    break;
                case 5:
                    printf("Exit selected\r\n");
                    writeToDisk(dbHwnd);
                    break;
                case 6:
                    printf("Deleting database\r\n");
                    deleteDatabase(dbHwnd);
                    break;
            }
        }
        //Todo: Free memory.
    }
    return 0;
}



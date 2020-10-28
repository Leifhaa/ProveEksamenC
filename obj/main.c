#include <stdio.h>
#include <stdlib.h>
#include "../include/database.h"

void printMenu(){
    printf("Welcome to main menu! Please enter a number between [1-5]\r\n");
    printf("[1] - Add element to database\r\n");
    printf("[2] - Find element in database\r\n");
    printf("[3] - Count number of elements in database\r\n");
    printf("[4] - Delete element from database\r\n");
    printf("[5] - Exit\r\n");
}

void getUserInput(int *tmpInput){
    char line[256];
    int iNew = 0;

    while (iNew < 1 || iNew > 5){
        printf("Enter a number between 1-5:");
        fgets(line, sizeof(line), stdin);
        iNew = atoi(line);
        //int iOk = scanf("%d", &iNew);
        //if (iOk == 0){
        //    //https://stackoverflow.com/questions/5087062/how-can-i-get-an-int-from-stdio-in-c
        //    //Allowing user to input string without breaking program.
        //    while (fgetc(stdin) != '\n');
        //}
    }
    *tmpInput = iNew;
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
        while (iInput != 5){
            printMenu();
            getUserInput(&iInput);
            printf("Input selected(%d)\r\n",iInput);
            switch(iInput){
                case 1:
                    printf("Add element selected\r\n");
                    AddEntry(dbHwnd);
                    break;
                case 2:
                    printf("Find element selected\r\n");
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
                    break;
            }
        }
        //Todo: Free memory.
    }
    return 0;
}



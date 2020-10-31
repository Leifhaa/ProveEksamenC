//
// Created by Leifh on 27/10/2020.
//

#ifndef PROVEEKSAMEN_DATABASE_H
#define PROVEEKSAMEN_DATABASE_H


int CreateDatabase(int *iDbHwnd);
int createRecord(int iDbHwnd);
int saveRecord(int iDbHwnd, int iNode);
int CountRecords(int iDbHwnd);
void PrintAllRecords(int iDbHwnd);
void DeleteRecord(int iDbHwnd);
int deleteDatabase(int iDbHwnd);
int printNode(int iDbHwnd);
int writeToDisk(int dbHwnd);

#endif //PROVEEKSAMEN_DATABASE_H

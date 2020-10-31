//
// Created by Leifh on 27/10/2020.
//

#ifndef PROVEEKSAMEN_DATABASE_H
#define PROVEEKSAMEN_DATABASE_H


int CreateDatabase(int *iDbHwnd);
int AddEntry(int iDbHwnd);
int CountRecords(int iDbHwnd);
void PrintDatabase(int iDbHwnd);
void DeleteRecord(int iDbHwnd);
int deleteDatabase(int iDbHwnd);
int printNode(int iDbHwnd);

#endif //PROVEEKSAMEN_DATABASE_H

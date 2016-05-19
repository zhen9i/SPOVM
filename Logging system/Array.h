#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include "Log.h"
//да, могу
int** AllocatingMemory(int, int);
int* AllocatingMemory(int);
int GenerateArray(int**,int,int);
int WriteToFile(int*,int);
int ReadFromFile(int*);
int PrintArray(int**, int, int);
int FreeMemory(int**, int);
int DefineLength();
void Sorting(int*, int);


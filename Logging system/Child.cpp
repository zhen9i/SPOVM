#include "Array.h"

int main(int argc, char* argv[])
{
	int length;
	int* array;
	length = DefineLength();
	array = AllocatingMemory(length);
	ReadFromFile(array);
	Sorting(array, length);
	WriteToFile(array, length);
	free(array);
	return 0;
}

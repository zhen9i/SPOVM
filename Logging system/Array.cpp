#include "Array.h"

int** AllocatingMemory(int amount, int length)
{
	LOG_TRACE("Function AllocatingMemort start");
	int** array;
	int i;
	array = (int**)malloc(amount * sizeof(int*));
	if(!array)
	{
		LOG_DEBUG("Can't allocate memory");
		return NULL;
	}
	for(i = 0; i < amount; i++)
	{
		array[i] = (int*)malloc(sizeof(int)*length);
		if(!array[i])
		{
			LOG_DEBUG("Can't allocate memory");
			return NULL;
		}
	}
	LOG_TRACE("Function AllocatingMemort finish");
	return array;
}

int* AllocatingMemory(int length)
{
	LOG_TRACE("Function AllocatingMemort start");
	int* array;
	array = (int*)malloc(length * sizeof(int));
	if(!array)
	{
		LOG_DEBUG("Can't allocate memory");
		return NULL;
	}
	LOG_TRACE("Function AllocatingMemort finish");
	return array;
}

int GenerateArray(int** array, int amount, int length)
{
	LOG_TRACE("Function GenerateMemory start");
	int i; 
	int j;
	for(i = 0; i < amount; i++)
	{
		for(j = 0; j < length; j++)
		{
			array[i][j] = rand() % 1000;
		}
	}
	LOG_TRACE("Function GenerateMemory finish");
	return 0;
}

int WriteToFile(int* array,int length)
{
	LOG_TRACE("Function WriteToFile start");
	FILE* my_file;
	int i;
	my_file = fopen("my_array.txt", "wb");
	if(!my_file)
	{
		LOG_ERROR("File not found");
		return -1;
	}
	fprintf(my_file, "%d ", length);
	for(i = 0; i < length; i++)
	{
		fprintf(my_file, "%d ", array[i]);
	}
	fclose(my_file);
	LOG_TRACE("Function WriteToFile finish");
	return 0;
}

int ReadFromFile(int* array)
{
	LOG_TRACE("Function ReadFromFile start");
	FILE* my_file;
	int i;
	int length;
	my_file = fopen("my_array.txt", "rb");
	if(!my_file)
	{
		LOG_ERROR("File can't be open/created");
		return -1;
	}
	fscanf(my_file, "%d", &length);
	for(i = 0; i < length; i++)
	{
		fscanf(my_file, "%d", &array[i]);
	}
	fclose(my_file);
	LOG_TRACE("Function ReadFromFile finish");
	return 0;
}

int PrintArray(int** array, int amount, int length)
{
	LOG_TRACE("Function PrintArray start");
	int i;
	int j;
	for(i = 0; i < amount;i++)
	{
		printf("Array[%d]: ", i + 1);
		for(j = 0; j < length; j++)
		{		
			printf("%d ", array[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	LOG_TRACE("Function PrintArray finish");
	return 0;
}

int FreeMemory(int** array, int amount)
{
	LOG_TRACE("Function FreeMemory start");
	int i;
	for(i = 0; i < amount;  i++)
	{
		free(array[i]);
	}
	free(array);
	LOG_TRACE("Function FreeMemory finish");
	return 0;
}

int DefineLength()
{
	LOG_TRACE("Function DefineLength start");
	FILE* my_file;
	int length;
	my_file = fopen("my_array.txt", "rb");
	if(!my_file)
	{
		LOG_TRACE("File not found");
		return -1;
	}
	fscanf(my_file, "%d", &length);
	fclose(my_file);
	LOG_TRACE("Function DefineLength start");
	return length;
}

void Sorting(int* array, int length)
{
	LOG_TRACE("Function Sorting start");
	int i;
	int j;
	for(i = 0; i < length - 1; i++)
	{
		for(j = i + 1; j < length; j++)
		{
			if(array[i] > array[j])
			{
				int tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
		}
	}
	LOG_TRACE("Function Sorting finish");
}
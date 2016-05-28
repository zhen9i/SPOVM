#include "Log.h"

int WriteLog(const char* text)
{
	FILE* my_file;
	my_file = fopen(filename, "a");
	if(!my_file)
	{
		return -1;
	}
	fprintf(my_file, "%s\n", text);
	fclose(my_file);
	return 0;
}

void LevelUp(int a)
{
	if(current_log_level >= CRITICAL && current_log_level < TRACE)
	{
		current_log_level++;
		printf("Log level was increased. Current log level: %d\n", current_log_level);
	}
	else
	{
		printf("Max log level - %d\n", TRACE);
	}
}

void LevelDown(int a)
{
	if(current_log_level > CRITICAL && current_log_level <= TRACE)
	{
		current_log_level--;
		printf("Log level was decreased. Current log level: %d\n", current_log_level);
	}
	else
	{
		printf("Min log level - %d\n", CRITICAL);
	}
}

void SetFileName(const char* name)
{
	strcpy(filename,name);
}
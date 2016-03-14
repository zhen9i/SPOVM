#include "Array.h"
#ifdef _MSC_VER
#include <Windows.h>
#include <process.h>
#else
#include <getopt.h>
#include <stdio_ext.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>
#endif

#ifdef _MSC_VER
#define FLUSH fflush(stdin)
#else
#define FLUSH __fpurge(stdin)
#endif

#ifdef _MSC_VER
HANDLE increment, decrement,thread_inc, thread_dec;
void Increment(void* pParams);
void Decrement(void* pParams);
#endif
void WorkArray(int**, int, int);
void GetSize(int&, int&, int, char**);

int main(int argc, char* argv[])
{
	int amount = 0;
	int length = 0;
	int** my_array = NULL;
	GetSize(amount, length, argc, argv);
	my_array = AllocatingMemory(amount, length);
	do
	{
		GenerateArray(my_array, amount, length);
		PrintArray(my_array, amount, length);
		WorkArray(my_array, amount, length);
		printf("\t\tAfter sorting\n");
		PrintArray(my_array, amount, length);
		printf("q to exit:\n");
		FLUSH;
	} while (getchar() != 'q');
	FreeMemory(my_array, amount);
	return 0;
}

#ifdef _MSC_VER
void GetSize(int& amount, int& length, int argc, char** argv)
{
	increment = CreateEvent(NULL, TRUE, FALSE, (LPCWSTR)"Increment");
	decrement = CreateEvent(NULL, TRUE, FALSE, (LPCWSTR)"Decrement");
	_beginthread(Increment, 0, NULL);
	_beginthread(Decrement, 0, NULL);
	if (argc < 3)
	{
		LOG_ERROR("Few arguments");
		return;
	}
	amount = atoi(argv[1]);
	length = atoi(argv[2]);
}

void Increment(void* pParams)
{
	while (TRUE)
	{
		WaitForSingleObject(increment, INFINITE);
		LevelUp(0);
	}
}

void Decrement(void* pParams)
{
	while (TRUE)
	{
		WaitForSingleObject(decrement, INFINITE);
		LevelDown(0);
	}
}
#else
void GetSize(int& amount, int& length, int argc, char** argv)
{
	int opt;
	signal(SIGUSR1, LevelUp);
	signal(SIGUSR2, LevelDown);
	while((opt = getopt(argc, argv, "n:l:p:")) != -1)
	{
		switch(opt)
		{
			case 'n':
			{
				amount = atoi(optarg);
				break;
			}
			case 'l':
			{
				length = atoi(optarg);
				break;
			}
			case 'p':
			{
				SetFileName(optarg);
				break;
			}
			default:
			{
				LOG_CRIT("Try to call unknown function");
			}
		}
	}
	if(length == 0)
	{
		length = amount;
	}
	if(amount == 0)
	{
		amount = length;
	}
}
#endif

#ifdef _MSC_VER
void WorkArray(int** my_array, int amount,int length)
{
	LOG_TRACE("Function WorkArray start");
	int i;
	for(i = 0; i < amount; i++)
	{
		WriteToFile(my_array[i], length);
		STARTUPINFO cif;
		PROCESS_INFORMATION pi;
		ZeroMemory(&cif, sizeof(STARTUPINFO));
		cif.cb = sizeof(cif);
		ZeroMemory(&pi, sizeof(pi));
		TCHAR ChildProcess[] = TEXT("ChildProcess.exe");
		CreateProcess(NULL, ChildProcess,
			NULL, NULL, FALSE, 0, NULL, NULL, &cif, &pi);
		while (WaitForSingleObject(pi.hProcess, 100))
		{
			if (WaitForSingleObject(pi.hProcess, 100) == 0)
				break;
		}
		ReadFromFile(my_array[i]);
	}
	LOG_TRACE("Function WorkArray finish");
}
#else
void WorkArray(int** my_array, int amount,int length)
{
	LOG_TRACE("Function WorkArray start");
	int i;
	int status;
	for(i = 0; i < amount; i++)
	{
		WriteToFile(my_array[i], length);
		pid_t pid = fork();
		if(pid < 0)
		{
			LOG_DEBUG("Fork failed in function WorkArray");
		}
		else if(pid == 0)
		{
			execl("Child", "", NULL, NULL);
		}
		else if(waitpid (pid, &status, 0) != pid)
		{
			LOG_DEBUG("WaitPid failed in function WorkArray");
		}
		ReadFromFile(my_array[i]);
	}
	LOG_TRACE("Function WorkArray finish");
}
#endif

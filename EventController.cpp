#include <stdio.h>
#include <Windows.h>

#define PRINT printf("+ - increment level\n");\
printf("- - decrement level\n");\
printf("Another to quit\n")

int main()
{
	HANDLE event1 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"Decrement");
	HANDLE event2 = OpenEvent(EVENT_ALL_ACCESS, FALSE, (LPCWSTR)"Increment");
	char c;
	PRINT;
	while (c = getchar())
	{
		printf("+ - increment level\n");
		printf("- - decrement level\n");
		printf("Another to quit\n");
		fflush(stdin);
		switch (c)
		{
		case '+':
			PulseEvent(event2);
			break;
		case '-':
			PulseEvent(event1);
			break;
		default:
			return 0;
		}
	}
	return 0;
}
#include <stdio.h>
#include <string.h>

#define FILENAME_LENGTH 100
#define CRITICAL 1
#define ERROR 2
#define DEBUG 3
#define TRACE 4

static char filename[FILENAME_LENGTH] = "Logs.txt";
static int current_log_level = TRACE;

#define LOG_CRIT(text)\
do\
{\
	if(current_log_level >= CRITICAL)\
	{\
		WriteLog(text); \
	}\
} while(0)

#define LOG_ERROR(text)\
do\
{\
	if(current_log_level >= ERROR)\
	{\
		WriteLog(text); \
	}\
} while(0)

#define LOG_DEBUG(text)\
do\
{\
	if(current_log_level >= DEBUG)\
	{\
		WriteLog(text); \
	}\
} while(0)

#define LOG_TRACE(text)\
do\
{\
	if(current_log_level == TRACE)\
	{\
		WriteLog(text); \
	}\
} while(0)

void SetFileName(const char*);
int WriteLog(const char*);
void LevelUp(int);
void LevelDown(int);
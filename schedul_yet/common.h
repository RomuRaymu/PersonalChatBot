#ifndef _common_h
#define _common_h

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <cstring>

using namespace std;

#define STRING_MAX 3000
#define SCHEDULERFILENAME "schedule.txt"

enum
{
	FALSE ,
	TRUE
};

typedef struct _DATE{
	int m_nYear;
	int m_nMonth;
	int m_nDay;
	int m_nHour;
	int m_nMinute;
}DATE;

typedef struct _SCHEDULE {
    DATE mDate;
    char mText[STRING_MAX];

    struct _SCHEDULE *next;
} SCHEDULE;

#endif

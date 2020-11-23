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

//data 구조체 년, 월, 일, 시간
typedef struct _DATE{
	int m_nYear;
	int m_nMonth;
	int m_nDay;
	int m_nHour;
}DATE;

//Schedule 구조체 Date와 그날 일정 계산
typedef struct _SCHEDULE {
    DATE mDate;
    char mText[STRING_MAX];

    struct _SCHEDULE *next;
} SCHEDULE;

#endif

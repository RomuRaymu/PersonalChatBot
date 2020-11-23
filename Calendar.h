#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include "common.h"
#include "Daters.h"
#include "Schedulers.h"

int GetLastDayByMonthAndYear ( int nYear , int nMonth ); //해당 달 일수 받아오는 함수
void DrawCalendar ( SCHEDULE *pHead , DATE date ); //달력 그려주는 함수

#endif


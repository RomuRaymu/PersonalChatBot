#ifndef __CALENDAR_H__
#define __CALENDAR_H__

#include "common.h"
#include "Daters.h"
#include "Schedulers.h"

int GetLastDayByMonthAndYear ( int nYear , int nMonth );
void DrawCalendar ( SCHEDULE *pHead , DATE date );

#endif


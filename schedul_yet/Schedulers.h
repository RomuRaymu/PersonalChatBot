#ifndef __SCHEDULERS_H__
#define __SCHEDULERS_H__

#include "common.h"
#include "Daters.h"

void KillAllScheduleNode ( SCHEDULE *pHead );
void AddScheduleNode ( SCHEDULE *pHead , SCHEDULE schedule );
void PrintAllSchedule ( SCHEDULE *pHead );
void PrintScheduleByDate ( SCHEDULE *pHead , DATE date );
void DeleteScheduleByDateAndTime ( SCHEDULE *pHead , DATE date );   
void ChangeScheduleByDateAndTime ( SCHEDULE *pHead , SCHEDULE schedule);

void LoadScheduleFromFile ( SCHEDULE *pHead , const char* szFileName );
void SaveScheduleToFile ( SCHEDULE *pHead , const char* szFileName );

SCHEDULE *InitScheduleHead ( void );
SCHEDULE *GetSchedulePointerByDate ( SCHEDULE *pHead , DATE date ); 
SCHEDULE *GetSchedulePointerByDateAndTime ( SCHEDULE *pHead , DATE date );
SCHEDULE InputSchedule ( SCHEDULE *pHead );

void DrawCalendar ( SCHEDULE *pHead , DATE date );
void ShowAllScheduleByDay ( SCHEDULE *pHead , DATE date );
void DeleteSchedule ( SCHEDULE *pHead );
void AddSchedule ( SCHEDULE *pHead );
void Changeschedule ( SCHEDULE *pHead );
int GetLastDayByMonthAndYear ( int nYear , int nMonth );
void DrawCalendar ( SCHEDULE *pHead , DATE date );
#endif


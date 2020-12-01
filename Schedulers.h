#ifndef __SCHEDULERS_H__
#define __SCHEDULERS_H__

#include "common.h"
#include "Daters.h"
#include "Calendar.h"

void KillAllScheduleNode ( SCHEDULE *pHead ); //모든 스케줄 제거
void AddScheduleNode ( SCHEDULE *pHead , SCHEDULE schedule ); //시간까지 찾아서 그것보다 더 큰거에 입력
void PrintAllSchedule ( SCHEDULE *pHead ); //모든 스케줄 출력
void PrintScheduleByDate ( SCHEDULE *pHead , DATE date ); //받은 스케줄 
void DeleteScheduleByDateAndTime ( SCHEDULE *pHead , DATE date );  //해당 스케줄 삭제
void ChangeScheduleByDateAndTime ( SCHEDULE *pHead , SCHEDULE schedule); //해당 시간 스케줄 바꿈

void LoadScheduleFromFile ( SCHEDULE *pHead , const char* szFileName ); //파일 읽어서 내용 읽기
void SaveScheduleToFile ( SCHEDULE *pHead , const char* szFileName ); //파일 읽어서 내용 저장

SCHEDULE *InitScheduleHead ( void ); //처음 schedule만들기
SCHEDULE *GetSchedulePointerByDate ( SCHEDULE *pHead , DATE date );  //해당 일 할일 찾기
SCHEDULE *GetSchedulePointerByDateAndTime ( SCHEDULE *pHead , DATE date ); //해당 할 일 받기
SCHEDULE InputSchedule ( SCHEDULE *pHead ); //스케줄.txt에 입력

void DrawCalendar ( SCHEDULE *pHead , DATE date ); // 그 시간에 스케줄 없으면 추가 있으면 있다는 메세지 출력
void ShowAllScheduleByDay ( SCHEDULE *pHead , DATE date ); //date 일로 가서 해당 스케줄 확인
void DeleteSchedule ( SCHEDULE *pHead ); //스케줄 삭제
void AddSchedule ( SCHEDULE *pHead ); // 스케줄 추가
void Changeschedule ( SCHEDULE *pHead ); //스케줄 수정

char GetSelectedMenu(void); //메뉴부분 출력
int ScheduleMain(string name); //name에 GetUserDirectory()를 보내주세요
//메뉴
enum MENU
{
	PREV_MONTH = 'a' ,
	NEXT_MONTH = 'd' ,
	PREV_DAY = 'w' ,
	NEXT_DAY = 's' ,
	ADD_SCHEDULE = '1' ,
	DELETE_SCHEDULE = '2' ,
	CHANGE_SCHEDULE = '3' ,
	QUIT = 'q'
};

#endif
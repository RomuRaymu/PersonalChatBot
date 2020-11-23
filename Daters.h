#ifndef __DATERS_H__
#define __DATERS_H__

#include "common.h"

void PrintDate ( DATE date ); //년 월 일 시간 출력
void ModifyMonth ( DATE *pDate , int nMonth ); // 12월 넘거나 1월 전으로 갈때 다음 해, 전 해로 넘어가는 함수
void ModifyDay ( DATE *pDate , int nDay ); //해당 달 체크후 다음 달, 전 달 넘어갈지 확인

int CompareDate ( DATE target , DATE compare ); //년,월,일 비교후 작으면 전이면 -1 후면 +1 같으면 0 반환합니다.
int CompareDateAndTime ( DATE target , DATE compare ); //CompareDate + 시간 체크

DATE InputDate ( void ); //년 월 일 시간 입력받기
DATE GetToday ( void ); //현재 시간 받기


#endif

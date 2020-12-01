#include "Schedulers.h"


SCHEDULE *InitScheduleHead ( void )
{
	SCHEDULE *pRet;

	pRet = (SCHEDULE *) malloc ( sizeof(SCHEDULE) );
	pRet->next = NULL;

	return pRet;
}

SCHEDULE *GetSchedulePointerByDate ( SCHEDULE *pHead , DATE date )
{
	SCHEDULE *pFind = pHead->next;

	while ( pFind != NULL )
	{
		if ( CompareDate ( pFind->mDate , date ) == 0 )
		{
			return pFind;
		}

		pFind = pFind->next;
	}

	return NULL;
}

SCHEDULE *GetSchedulePointerByDateAndTime ( SCHEDULE *pHead , DATE date )
{
	SCHEDULE *pFind = pHead->next;

	while ( pFind != NULL ) //할 일 찾기
	{
		if ( CompareDateAndTime ( pFind->mDate , date ) == 0 )
		{
			return pFind;
		}

		pFind = pFind->next;
	}

	return NULL;
}

void AddScheduleNode ( SCHEDULE *pHead , SCHEDULE schedule )
{
	SCHEDULE *pPrev = pHead;
	SCHEDULE *pFind = pHead->next;
	SCHEDULE *pNew;

	pNew = (SCHEDULE *) malloc ( sizeof(SCHEDULE) );
	*pNew = schedule;
	
	while ( pFind != NULL )
	{
		if ( CompareDateAndTime ( schedule.mDate , pFind->mDate ) == -1 ) //해당 요일 계속 찾는 과정
		{
			pPrev = pPrev->next;
			pFind = pFind->next;
		}
		else
		{
			break;
		}
	}

	pPrev->next = pNew;
	pNew->next = pFind;
}

void DeleteScheduleByDateAndTime ( SCHEDULE *pHead , DATE date )
{
	SCHEDULE *pPrev = pHead;
	SCHEDULE *pFind = pHead->next;
	SCHEDULE *pTemp;

	while ( pFind != NULL )
	{
		if ( CompareDateAndTime ( pFind->mDate , date ) == 0 )
		{
			pTemp = pFind;
			pPrev->next = pFind->next;
			free ( pTemp );
			break;
		}

		pFind = pFind->next;
		pPrev = pPrev->next;
	}
}

void ChangeScheduleByDateAndTime ( SCHEDULE *pHead, SCHEDULE schedule )
{
	SCHEDULE *pFind = pHead->next;
	SCHEDULE *pTemp;

	while ( pFind != NULL )
	{
		if (CompareDateAndTime ( pFind->mDate , schedule.mDate ) == 0)
		{
			pTemp = pFind;
			scanf("%s", pTemp->mText);
			break;
		}
	}

}

void KillAllScheduleNode ( SCHEDULE *pHead )
{
	SCHEDULE *pFind = pHead->next;
	SCHEDULE *pPrev = pHead;

	while ( pFind != NULL )
	{
		pFind = pPrev->next;

		free ( pPrev );

		pPrev = pFind;
		pFind = pFind->next;
	}
}

void PrintAllSchedule ( SCHEDULE *pHead )
{
	SCHEDULE *pFind = pHead->next;

	while ( pFind != NULL ) //스케줄 체크
	{
		printf ( "%s\n" , pFind->mText );
		PrintDate ( pFind->mDate );

		pFind = pFind->next;
	}
}

void LoadScheduleFromFile ( SCHEDULE *pHead ,  const char* szFileName )
{	
	SCHEDULE news;
	FILE *fp;
	int nCnt = 0;
	char szBuf[STRING_MAX];

	fp = fopen ( szFileName , "r" ); //file 읽기

	if ( fp == NULL )
	{
		fp = fopen ( szFileName , "w" );
		fclose ( fp );

		return;
	}

	while ( !feof(fp) )
	{		
		fscanf ( fp , "%s" , szBuf );

		switch ( nCnt ) //연 초 일 시간, 할일 까지 순서대로 입력 받음 숫자는 atoi 함수 통해 숫자로 변경
		{
			case 0:
				news.mDate.m_nYear = atoi ( szBuf );
				break;

			case 1:
				news.mDate.m_nMonth = atoi ( szBuf );
				break;

			case 2:
				news.mDate.m_nDay = atoi ( szBuf );
				break;

			case 3:
				news.mDate.m_nHour = atoi ( szBuf );
				break;

			case 4:
				strcpy ( news.mText , szBuf );
				break;
		}

		nCnt++;

		if ( nCnt == 5 )
		{
			AddScheduleNode ( pHead , news );
			nCnt = 0;
		}
	}

	fclose ( fp );
}

void SaveScheduleToFile ( SCHEDULE *pHead , const char * szFileName )
{
	FILE *fp;
	SCHEDULE *pFind = pHead->next;
 
	fp = fopen ( szFileName , "w" );//파일 내용 전부 추가

	while ( pFind != NULL )
	{
		fprintf ( fp , "%d %d %d %d %s\n" ,  pFind->mDate.m_nYear , pFind->mDate.m_nMonth ,pFind->mDate.m_nDay , pFind->mDate.m_nHour , pFind->mText);	

		pFind = pFind->next;
	}

	fclose ( fp );
}

SCHEDULE InputSchedule ( SCHEDULE *pHead )
{
	SCHEDULE ret;
	DATE current;
	current = GetToday ();

	system ("clear");
	DrawCalendar ( pHead , current );
	ShowAllScheduleByDay ( pHead , current );

	while ( TRUE )
	{
		printf ("     년, 월, 일, 시, 할 일을 적어주세요 \n");
		printf ("     (ex)2020 11 20 18 축제           \n");;
		printf ("	 >> ");

		scanf ( "%d %d %d %d %s" , &ret.mDate.m_nYear ,	&ret.mDate.m_nMonth , &ret.mDate.m_nDay , &ret.mDate.m_nHour , ret.mText );

		if ( GetSchedulePointerByDateAndTime ( pHead , ret.mDate ) == NULL ) // 스케줄 확인해서 없으면 추가 있으면 넣어줍니다.
		{
			break;
		}
		
		printf ("  이미 그 시간에 할 일이 존재합니다 \n");

	}
	system ("clear");
	return ret;
}

void ShowAllScheduleByDay ( SCHEDULE *pHead , DATE date )
{
	SCHEDULE *pFind = pHead->next;

	printf ( "\n" );
	printf ( "              *  %d/%d/%d에 할 일? *\n" , date.m_nYear ,date.m_nMonth ,date.m_nDay );
	
	printf ( "------------------------------------------------------------------------------\n" );

	while ( pFind != NULL )
	{
		if ( CompareDate ( pFind->mDate , date ) == 0 ) 
		{
			printf ( ">>%d 시 : %s\n" , pFind->mDate.m_nHour , pFind->mText );
		}

		pFind = pFind->next;
	}

	printf ( "------------------------------------------------------------------------------\n\n" );
}

void DeleteSchedule ( SCHEDULE *pHead )
{
	DATE date;
	DATE current;
	current = GetToday ();

	system ("clear");
	DrawCalendar ( pHead , current ); //해당 달 입력 받기
	ShowAllScheduleByDay ( pHead , current );
		printf ("   지울 스케줄 년, 월, 일, 시간을 적어주세요 \n");
		printf ("   |  (ex)2020 11 20 17                 |\n");
		printf ("	 >> ");

	scanf ( "%d %d %d %d" ,&date.m_nYear , &date.m_nMonth , &date.m_nDay ,&date.m_nHour );

	DeleteScheduleByDateAndTime ( pHead , date );
	system ("clear");
}

void AddSchedule ( SCHEDULE *pHead )
{
	SCHEDULE schedule;

	schedule = InputSchedule ( pHead );

	AddScheduleNode ( pHead , schedule );
}

void Changeschedule ( SCHEDULE *pHead )
{
	SCHEDULE ret;
	DATE current;
	current = GetToday (); //현재 요일 받기

	system ("clear");
	DrawCalendar ( pHead , current ); //해당 달 보여주기
	ShowAllScheduleByDay ( pHead , current );

		printf ("   수정할 년, 월 ,일 , 시간을 적어주세요 \n");
		printf ("   |  (ex)2020 11 20 17                |\n");
		printf ("	 >> ");
		scanf ( "%d %d %d %d" , &ret.mDate.m_nYear ,&ret.mDate.m_nMonth ,&ret.mDate.m_nDay ,&ret.mDate.m_nHour);
		printf ("   수정할 일정 입력 \n           >>");

	ChangeScheduleByDateAndTime ( pHead, ret );
	system ("clear");

}

/*
int ScheduleMain(string name) //name에 GetUserDirectory()를 보내주세요
{
	name.append("/");
	name.append(SCHEDULERFILENAME);
	int check=name.length();
	char * scFileName;
	SCHEDULE *pHead;
	DATE current;
	pHead = InitScheduleHead ();
	for(int i=0;i<check;i++) {
		scFileName[i]=name[i];
	}
	LoadScheduleFromFile ( pHead , scFileName );

	current = GetToday ();
	system ("clear");

	while ( 1 )
	{
		char ch;

		DrawCalendar ( pHead , current );
		ShowAllScheduleByDay ( pHead , current );

		ch = GetSelectedMenu ();

		if ( ch == MENU::QUIT )
		{
			break;
		}

		switch ( ch ) //메뉴에 따라 해당 달로이동
		{
			case PREV_MONTH:
				ModifyMonth ( &current , -1 );
				break;

			case NEXT_MONTH:
				ModifyMonth ( &current , 1 );
				break;

			case PREV_DAY:
				ModifyDay ( &current , -1 );
				break;

			case NEXT_DAY:
				ModifyDay ( &current , 1 );
				break;

			case ADD_SCHEDULE:
				AddSchedule ( pHead );
				break;

			case DELETE_SCHEDULE:
				DeleteSchedule ( pHead );
				break;

			case CHANGE_SCHEDULE:
				Changeschedule ( pHead );
				break;
		}

		system ("clear");
	}


	SaveScheduleToFile ( pHead , scFileName );
	KillAllScheduleNode ( pHead );
}

char GetSelectedMenu ( void )
{
	char ch;

	printf ("          ----------------------------\n");
	printf ("          |          MENU            |\n");
	printf ("          |  d : 다음달 보기         |\n");
	printf ("          |  a : 전 달 보기          |\n");
	printf ("          |  s : 다음날보기          |\n");
	printf ("          |  w : 어제 보기           |\n");
	printf ("          |  1 : 스케줄 추가하기     |\n");
	printf ("          |  2 : 스케줄 지우기       |\n");
	printf ("          |  3 : 스케줄 바꾸기       |\n");
	printf ("          |  q : 채팅 봇으로 돌아가기|\n");
	printf ("          --------------------------\n\n");
	printf ("           메뉴 고르시오 >> ");
	ch = getchar ();
	printf("\n");
	return ch;
}
*/
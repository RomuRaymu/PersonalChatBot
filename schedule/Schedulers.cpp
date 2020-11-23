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

	while ( pFind != NULL )
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
		if ( CompareDateAndTime ( schedule.mDate , pFind->mDate ) == -1 )
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

	while ( pFind != NULL )
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

	fp = fopen ( szFileName , "r" );

	if ( fp == NULL )
	{
		fp = fopen ( szFileName , "w" );
		fclose ( fp );

		return;
	}

	while ( !feof(fp) )
	{		
		fscanf ( fp , "%s" , szBuf );

		switch ( nCnt )
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

void SaveScheduleToFile ( SCHEDULE *pHead , const char* szFileName )
{
	FILE *fp;
	SCHEDULE *pFind = pHead->next;

	fp = fopen ( szFileName , "w" );

	while ( pFind != NULL )
	{
		fprintf ( fp , "%d %d %d %d %s\n" , 
				pFind->mDate.m_nYear ,
				pFind->mDate.m_nMonth ,
				pFind->mDate.m_nDay ,
				pFind->mDate.m_nHour ,
				pFind->mText
				);	

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
		printf ("     write Year, Mon, Day, Hour, active \n");
		printf ("     (ex)2017 10 31 18 festival           \n");;
		printf ("	 >> ");

		scanf ( "%d %d %d %d %s" , 
				&ret.mDate.m_nYear ,
				&ret.mDate.m_nMonth ,
				&ret.mDate.m_nDay ,
				&ret.mDate.m_nHour ,
				ret.mText );

		if ( GetSchedulePointerByDateAndTime ( pHead , ret.mDate ) == NULL )
		{
			break;
		}

		printf ("  already worke to do at the same time \n");

	}
	system ("clear");
	return ret;
}

void ShowAllScheduleByDay ( SCHEDULE *pHead , DATE date )
{
	SCHEDULE *pFind = pHead->next;

	printf ( "\n" );
	printf ( "              *  %d/%d/%d to do? *\n" , date.m_nYear ,
			date.m_nMonth ,
			date.m_nDay );
	
	printf ( "------------------------------------------------------------------------------\n" );

	while ( pFind != NULL )
	{
		if ( CompareDate ( pFind->mDate , date ) == 0 )
		{
			printf ( ">>%d Hour : %s\n" , 
					pFind->mDate.m_nHour ,
					pFind->mText );
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
	DrawCalendar ( pHead , current );
	ShowAllScheduleByDay ( pHead , current );
		printf ("   Please write year, month, day, hour \n");
		printf ("   |  (ex)2020 11 20 17                 |\n");
		printf ("	 >> ");

	scanf ( "%d %d %d %d" ,
			&date.m_nYear ,
			&date.m_nMonth ,
			&date.m_nDay ,
			&date.m_nHour );

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
	current = GetToday ();

	system ("clear");
	DrawCalendar ( pHead , current );
	ShowAllScheduleByDay ( pHead , current );

		printf ("   Please write year, month, day, hour \n");
		printf ("   |  (ex)2020 11 20 17                |\n");
		printf ("	 >> ");
		scanf ( "%d %d %d %d" , &ret.mDate.m_nYear ,&ret.mDate.m_nMonth ,&ret.mDate.m_nDay ,&ret.mDate.m_nHour);
		printf ("   wrtie down the revision \n           >>");

	ChangeScheduleByDateAndTime ( pHead, ret );
		system ("clear");

}


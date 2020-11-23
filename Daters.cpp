#include "Daters.h"
#include "Calendar.h"

int CompareDate ( DATE target , DATE compare )
{
	int nTargetSum = 0;
	int nCompareSum = 0;

	if ( target.m_nYear > compare.m_nYear )
	{
		return -1;
	}
	else if ( target.m_nYear < compare.m_nYear )
	{
		return 1;
	}

	if ( target.m_nMonth > compare.m_nMonth )
	{
		return -1;
	}
	else if ( target.m_nMonth < compare.m_nMonth )
	{
		return 1;
	}

	if ( target.m_nDay > compare.m_nDay )
	{
		return -1;
	}
	else if ( target.m_nDay < compare.m_nDay )
	{
		return 1;
	}
	
	return 0;
}

int CompareDateAndTime ( DATE target , DATE compare )
{
	int check=CompareDate(target,compare);
	if(check!=0) 
	{
		return check;
	}
	if ( target.m_nHour > compare.m_nHour )
	{
		return -1;
	}
	else if ( target.m_nHour < compare.m_nHour )
	{
		return 1;
	}
	
	return 0;
}

void PrintDate ( DATE date )
{
	printf( "%d년 %d월 %d일 %d시\n" , date.m_nYear , date.m_nMonth , date.m_nDay , date.m_nHour );
}

DATE InputDate ( void )
{
	DATE ret;

	printf ( "년 : " );
	scanf ( "%d" , &ret.m_nYear );

	printf ( "월 : " );
	scanf ( "%d" , &ret.m_nMonth );

	printf ( "일 : " );
	scanf ( "%d" , &ret.m_nDay );

	printf ( "시 : " );
	scanf ( "%d" , &ret.m_nHour );

	return ret;
}

DATE GetToday ( void )
{
	DATE ret;
	time_t ltime;
	struct tm *today;

	time ( &ltime );
	today = localtime ( &ltime );

	ret.m_nYear = today->tm_year + 1900;
	ret.m_nMonth = today->tm_mon + 1;
	ret.m_nDay = today->tm_mday;

	ret.m_nHour = today->tm_hour;

	return ret;
}

void ModifyMonth ( DATE *pDate , int nMonth )
{
	if ( nMonth > 0 )
	{
		if ( pDate->m_nMonth + nMonth > 12 )
		{
			pDate->m_nMonth = pDate->m_nMonth + nMonth - 12;
			pDate->m_nYear = pDate->m_nYear + 1;
			return;
		}
	}
	else if ( nMonth < 0 )
	{
		if ( pDate->m_nMonth + nMonth < 1 )
		{
			pDate->m_nMonth = 12 + ( nMonth + 1 );
			pDate->m_nYear = pDate->m_nYear - 1;
			return;
		}
	}
	
	pDate->m_nMonth = pDate->m_nMonth + nMonth;
}

void ModifyDay ( DATE *pDate , int nDay )
{
	int nMaxDay = GetLastDayByMonthAndYear ( pDate->m_nYear , pDate->m_nMonth );
	int nPrevMaxDay = GetLastDayByMonthAndYear ( pDate->m_nYear , pDate->m_nMonth - 1 ); 

	if ( nDay > 0 )
	{
		if ( pDate->m_nDay + nDay > nMaxDay )
		{
			pDate->m_nDay = 1;
			ModifyMonth ( pDate , 1 );
			return;
		}
	}

	else if ( nDay < 0 )
	{
		if ( pDate->m_nDay + nDay < 1 )
		{
			pDate->m_nDay = nPrevMaxDay;
			ModifyMonth ( pDate , -1 );
			return;
		}
	}

	pDate->m_nDay = pDate->m_nDay + nDay;
}
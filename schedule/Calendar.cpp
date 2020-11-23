#include "Calendar.h"

int GetLastDayByMonthAndYear ( int nYear , int nMonth )
{
	int nLastDay;

	if ( nMonth == 1 || 
			nMonth == 3 || 
			nMonth == 5 || 
			nMonth == 7 ||
			nMonth == 8 ||
			nMonth ==10 ||
			nMonth == 12 )
	{
		nLastDay = 31;
	}
	else if ( nMonth == 4 ||
			nMonth == 6 ||
			nMonth == 9 ||
			nMonth==11 )
	{
		nLastDay = 30;
	}

	if ( nMonth == 2 )
	{
		nLastDay = 28;
	}

	if ( nMonth == 2 && ( nYear % 4 ) == 0 && ( nYear % 100 != 0 ) || ( nYear % 400 == 0 ) )
	{
		nLastDay=29;
	}

	return nLastDay;
}

void DrawCalendar ( SCHEDULE *pHead , DATE date )
{
	char szBuf[STRING_MAX];

	int nYear;
	int nMonth;
	int nLastDay;
	int nTh;
	int nDay;
	int nDate;
	int nX;
	int nZ;
	int count=0;

	nYear = date.m_nYear;
	nMonth = date.m_nMonth;
	nLastDay = GetLastDayByMonthAndYear ( nYear , nMonth );

	
	if(nMonth > 9)
	printf("---------------  %dyear %dmonth  ---------------\n", nYear , nMonth );
	else
	printf("---------------  %dyear %dmonth  ---------------\n", nYear , nMonth );
	printf ("|  %6s%6s%6s%6s%6s%6s%6s    |\n", "Sun" ,"Mon" ,"Tue" ,"Wed" ,"Thu" ,"Fri" ,"Sat" );

	nDate = 1 ,nX = 0 , nZ = 0;

	while ( nX <= 6 )
	{
		nX = nX + 1;
		nTh = nYear / 100;          
		nYear = nYear % 100;   
		nDay = ( (21 * nTh / 4 ) +
				( 5 * nYear / 4 ) + ( 26 * (nMonth + 1 ) / 10 ) + nDate - 1 ) % 7;
		printf("|");
        while ( nZ < 7 )
		{
			if ( nX == 1 && nZ < nDay )
			{
				printf ( "%6s" , " " );
			}
			else 
			{
				DATE temp;
				temp = date;

				temp.m_nDay = nDate;

				if ( CompareDate ( date , temp ) == 0 )
				{
					sprintf ( szBuf , "[%d]" , nDate );
					printf ( "%6s" , szBuf );
				}
				else if ( GetSchedulePointerByDate ( pHead , temp )
					!= NULL )
				{
					sprintf ( szBuf , "*%d" , nDate );
					printf ( "%6s" , szBuf );
				}
				else
				{
					count++;
					printf ( "%6d" , nDate );
				}

				if ( nDate < nLastDay )
				{
					nDate = nDate + 1;
				}
				else if ( nDate >= nLastDay )
				{
					break;
				}
			}

			nZ = nZ + 1;
		}
		if(nZ==0)
		printf ( "\t\t\t\t\t\t|\n" );
		else if(nZ==1)
		printf ( "\t\t\t\t\t |\n" );
		else if(nZ==2)
		printf ( "\t\t\t\t |\n" );
		else if(nZ==3)
		printf ( "\t\t\t |\n" );
		else if(nZ==4)
		printf ( "\t\t |\n" );
		else if(nZ==5)
		printf ( "\t\t |\n" );
		else
		printf ( "\t |\n" );

		if ( nDate >= nLastDay )
		{
			break;
		}
		
		nZ = 0;
	}
	printf("|                                                |\n");
	printf("------------------------------------------------\n\n");

}
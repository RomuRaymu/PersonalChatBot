#include "common.h"
#include "Daters.h"
#include "Schedulers.h"
#include "Calendar.h"

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


char GetSelectedMenu(void);

int main(void)
{
	SCHEDULE *pHead;
	DATE current;
	pHead = InitScheduleHead ();
	LoadScheduleFromFile ( pHead , SCHEDULERFILENAME );

	current = GetToday ();
	system ("clear");

	while ( 1 )
	{
		char ch;

		DrawCalendar ( pHead , current );
		ShowAllScheduleByDay ( pHead , current );

		ch = GetSelectedMenu ();

		if ( ch == QUIT )
		{
			break;
		}

		switch ( ch )
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


	SaveScheduleToFile ( pHead , SCHEDULERFILENAME );
	KillAllScheduleNode ( pHead );
}

char GetSelectedMenu ( void )
{
	char ch;

	printf ("          ----------------------------\n");
	printf ("          |          MENU            |\n");
	printf ("          |  d : next month          |\n");
	printf ("          |  a : last month          |\n");
	printf ("          |  s : next day            |\n");
	printf ("          |  w : yesterday           |\n");
	printf ("          |  1 : add schedule        |\n");
	printf ("          |  2 : delete schedule     |\n");
	printf ("          |  3 : change schedule     |\n");
	printf ("          |  q : end schedule process|\n");
	printf ("          --------------------------\n\n");
	printf ("           choose menu >> ");
	ch = getchar ();
	return ch;
}


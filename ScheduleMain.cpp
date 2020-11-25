#include "common.h"
#include "Daters.h"
#include "Schedulers.h"
#include "Calendar.h"

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


char GetSelectedMenu(void); //메뉴부분 출력

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

		if ( ch == QUIT )
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

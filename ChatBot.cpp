#include "ChatBot.h"

using namespace std;

/*
    activate when scan "계산" and request formula
    */
void ChatBot::cal_start() {
    string formula;
    double result;

    cout << "식을 입력해주세요.\n" << ">>";
    getline(cin, formula);
    switch (Calculator::CalculateFormula(formula, result)) {
	case 0:
		cout << "계산 식이 올바르지 않습니다!!" << endl;
		break;
	case 1:
		cout << "계산한 결과 : " << result << endl;
		break;
	}
}

/*
    activate when sacn "스케쥴" or "일정" and start Scheduler
    */
void ChatBot::schedule_start() {
    
	char * scFileName;
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

		if ( ch == QUIT_ )
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

/*
    activate when scan "지뢰" and start MineSweeper
    */
int ChatBot::mine_start() {
    class MineSweeper ms;
    ms.StartMineSweeper();

    return 0;
}

/*
    open text file and select random line in answer text file
    (now, "this fuction" only print frist line or 'two' lines <- doesnt mean 'second' line)
    (need to change)
    */
void ChatBot::answer_phase(string dir) {
    ifstream readFile;
    readFile.open(dir);

    if(readFile.is_open()) {
        // make 0 - 4 random number
        random_device rd;
        mt19937 mer(rd());
        uniform_int_distribution<> line(0, 4);
        //

        while(!readFile.eof()) {
            string answer;
            for(size_t i = 0; i <= line(mer); i++) {
                getline(readFile, answer);
            }
            cout << answer << endl; 
        }
        readFile.close();
    }
}

/*
	* -1 : Cannot scan correct word
	*  0 : Success to Scan for chat
	*  1 : move to Calculate
    *  2 : move to MineSweeper
    *  3 : move to Alarm
	*  4 : move to Schedule
    */
int ChatBot::chat_check(string question) {
    ifstream readFile;
    readFile.open(WORD_GROUP);

    if(question.find(QUIT) != string::npos) { 
        cout << "프로그램을 종료합니다." << endl;
        _exit(0);
    } else if(question.find(CALCULATOR) != string::npos) {
        cal_start();
        return 1;
    } else if(question.find(MINE) != string::npos) {
        mine_start();
        return 2;
    } else if(question.find(ALARM) != string::npos) {
        alarm_start();
        return 3;
    } else if(question.find(SCHEDULERS_1) != string::npos || question.find(SCHEDULERS_2) != string::npos) {
        schedule_start();
        return 4;
    }

    if(readFile.is_open()) {
        while(!readFile.eof()) {
            string line, word, rep_word;
            getline(readFile, line);
            stringstream ss(line);
            ss >> word;
            rep_word = word;
            do {
                if(question.find(word) == string::npos) continue;
                else {
                    string dir = DIR_FOREHEAD;
                    dir.append(rep_word);
                    dir.append(TXT);
                    answer_phase(dir);
                    return 0;
                }
            } while(ss >> word);
        }
        readFile.close();
    }
    return -1;
}

/*
    start Chat Bot
    */
void ChatBot::chat_body() {
    cout << "어서오세요 회원님." << endl;
    while(1) {
        string question;
        cout << ">> ";
        getline(cin, question);
        if(chat_check(question) == -1) {
            cout << "이해할 수 없는 말입니다." << endl;
        }
    }
}

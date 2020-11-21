#include "ChatBot.h"

using namespace std;

/*
    activate when scan "cal" and request formula
    */
void ChatBot::cal_start() {
    string formula;
    double result;

    cout << "Write your formula.\n" << ">>";
    getline(cin, formula);
    switch (Calculator::CalculateFormula(formula, result)) {
	case -1:
		cout << "Err" << endl;
		break;
	case 0:
		cout << "Formula Err" << endl;
		break;
	case 1:
		cout << "Answer is " << result << endl;
		break;
	}
}

/*
    activate when scan "지뢰" and start MineSweeper
    */
int ChatBot::mine_start() {
    class MineSweeper ms;

    while (1) {
        cout << "1. Start Mine Sweeper" << endl;
        cout << "2. Exit" << endl;

        int num = 0;
        cout << ">> ";
        cin >> num;

        if (num == 1) {
            cout << "Start Mine Sweeper" << endl;
            ms.StartMineSweeper();
            cout << "End Mine Sweeper" << endl;
        } else if (num == 2) {
            break;
        }

        cout << endl;
    }

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
	*/
int ChatBot::chat_check(string question) {
    ifstream readFile;
    readFile.open(WORD_GROUP);

    if(question.find(QUIT) != string::npos) { 
        cout << "Shutting down Program." << endl;
        _exit(0);
    } else if(question.find(CALCULATOR) != string::npos) {
        cal_start();
        return 1;
    } else if(question.find(MINE) != string::npos) {
        mine_start();
        return 2;
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
    cout << "Welcome." << endl;
    while(1) {
        string question;
        cout << ">> ";
        getline(cin, question);
        if(chat_check(question) == -1) {
            cout << "Cannot understand" << endl;
        }
    }
}

#include "ChatBot.h"

using namespace std;

void ChatBot::cal_start() {
    string formula;
    double result;

    cout << "Write your formula.\n" << ">>";
    getline(cin, formula);
    Calculator::CalculateFormula(formula, result);

    cout << "Answer is " << result << endl;
}

/*
    open text file and select random line in answer text file 
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
	*/
int ChatBot::chat_check(string question) {
    ifstream readFile;
    readFile.open(WORD_GROUP);

    if(question.find(QUIT) != string::npos) { 
        cout << "Shutting down Program." << endl;
        _exit(0);
    } else if(question.find("cal") != string::npos) {
        cal_start();
        return 1;
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
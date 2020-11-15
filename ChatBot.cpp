#include "ChatBot.h"

using namespace std;

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

void ChatBot::chat_check(string question) {
    ifstream readFile;
    readFile.open(WORD_GROUP);

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
                    break;
                }
            } while(ss >> word);

        }
        readFile.close();
    }
}

void ChatBot::chat_body() {
    cout << "어서오세요. 회원님." << endl;
    while(1) {
        string question;
        cout << ">> ";
        cin >> question;
        chat_check(question);
    }
}
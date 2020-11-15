#include "ChatBot.h"

using namespace std;

void chat_check(string question) {
    ifstream readFile;
    readFile.open("./texts/words.txt");

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
                    
                }
            } while(ss >> word);

        }
        readFile.close();
    }
}
void chat_body() {
    cout << "어서오세요. 회원님." << endl;
    while(1) {
        string question;
        cin >> question;
        chat_check(question);
    }
}
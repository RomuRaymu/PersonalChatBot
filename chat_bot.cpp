#include "chat_bot.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void chat_body() {
    ifstream readFile;
    readFile.open("./texts/words.txt");

    if(readFile.is_open()) {
        while(!readFile.eof()) {
            string str;
            getline(readFile, str);
            cout << str << endl;
        }
        readFile.close();
    }
}
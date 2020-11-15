#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>

#define DIR_FOREHEAD "./texts/"
#define TXT ".txt"

#define WORD_GROUP "./texts/words.txt"

class ChatBot {
    private:
        static void answer_phase(std::string dir);
        static void chat_check(std::string question);
    public:
        static void chat_body();
};
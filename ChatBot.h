#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <cstdlib>

#include "Calculator.h"

// define for special word
#define QUIT "exit"
#define CALCULATOR "계산"

// define for selected file name
#define DIR_FOREHEAD "./texts/"
#define TXT ".txt"
#define WORD_GROUP "./texts/words.txt"

class ChatBot {
    private:
        static void answer_phase(std::string dir);
        static int chat_check(std::string question);
        static void cal_start();
    public:
        static void chat_body();
};
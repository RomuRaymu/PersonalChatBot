#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <sstream>
#include <cstdlib>

// calculator header
#include "Calculator.h"

// minesweeper header
#include "MineSweeper.h"

// scheduler header
#include "common.h"
#include "Daters.h"
#include "Schedulers.h"
#include "Calendar.h"

// alarm header
#include "Alarm.h"


// define for special word
#define ALARM "알람"
#define QUIT "종료"
#define CALCULATOR "계산"
#define MINE "지뢰"
#define SCHEDULERS_1 "일정"
#define SCHEDULERS_2 "스케쥴"

// define for selected file name
#define DIR_FOREHEAD "./texts/"
#define TXT ".txt"
#define WORD_GROUP "./texts/words.txt"

class ChatBot {
    private:
        static void answer_phase(std::string dir);
        static int chat_check(std::string question);
        static void cal_start();
        static int mine_start();
        static void alarm_start();
    public:
        static void chat_body();
};
#ifndef __ALARM_H__
#define __ALARM_H__

#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <mutex> 

using namespace std;

class Alarm
{
private:
    int min; 
    int hr; 
    int hr2;
    int min2;
    int sec;
    string insert;
    int total;
    time_t now_time; 
    struct tm *now_date; 
    char buf[100];
    int str_cnt;
    string str_arr[1000];
    char *str_buff = new char[1000];
public:
    char *Alarm_path;
    void Nowtime();// 현재시간 구하는 함수
    int Alarm_function();// 알람시계 메인 구동함수
    int Time_cal();// 입럭 값 Sleep()으로 보내기 위한 시간 변환 함수
    int Time_inputstring();// 사용자 원하는 시간 입력값 String Parsing 처리 함수
};

#endif
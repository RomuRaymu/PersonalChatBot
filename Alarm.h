#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <ctime>
#include <cstring>

class Alarm
{
private:
    int min; 
    int hr; 
    int hr2;
    int min2;
    int sec;
    char insert[100]; 
    int total;
    time_t now_time; 
    struct tm *now_date; 
    char buf[100];
public:
    char *Alarm_path;
    void Nowtime();// 현재시간 구하는 함수
    void Alarm_function();// 알람시계 메인 구동함수
    int Time_cal();// 입럭 값 Sleep()으로 보내기 위한 시간 변환 함수
};

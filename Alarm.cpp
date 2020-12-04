#include "Alarm.h"


// 현재시각
void Alarm::Nowtime()
{
    time_t curr_time;
    struct tm *curr_tm;

    curr_time = time(NULL);

    curr_tm = localtime(&curr_time);

    cout << "현재시각: " << curr_tm->tm_year + 1900 << "년 " << curr_tm->tm_mon + 1 << "일 " << curr_tm->tm_mday << "일" ;
    cout << curr_tm->tm_hour << "시 " << curr_tm->tm_min << "분 " << curr_tm->tm_sec << "초" << '\n';

}

int Alarm::Time_cal(){
    hr2=hr*3600;
    min2=min*60;
    sec;
    total=hr2+min2+sec;
    return total;

}

void Alarm::Time_inputstring(){
    strcpy(str_buff, insert.c_str());

    char *tok = strtok(str_buff, " ");

    str_cnt = 0;
    while (tok != nullptr) {
        str_arr[str_cnt++] = string(tok);
        tok = strtok(nullptr, " ");
    }

    string strhr=str_arr[0];
    string strmin=str_arr[1];
    string strsec=str_arr[2];

    hr = stoi(strhr);
    min = stoi(strmin);
    sec = stoi(strsec);
}

void Alarm::Alarm_function()
{
    while (1)
    {
        Nowtime();

        cout<<"설정 시간을 입력해주세요 ['시간' '분' '초' 자릿수를 모두 입력해주세요. (ex.4초 = 0시간 0분 4초 타이머 설정해줘)] >> ";

        getline(cin,insert);

        Time_inputstring();

        unsigned int timeVal = Time_cal();

        pthread_t tid = 0;
        pthread_create(&tid, NULL, StartTimer, (void *)&timeVal);
        cout << hr << "시간 " << min << "분 " << sec << "초 타이머를 설정했어요!"<<endl;

        char input = 0;
        while (1){
            cout << "알람 기능을 계속 수행할까요? (y: 계속 | n: 종료)" << endl << ">> ";
            cin >> input;
            if (input=='y' || input=='Y'){
                break;
            }
            else if (input=='n' || input=='N' )
            {
                cout << "알람 도움이 필요하면 언제든지 불러주세요." << endl;
                return;

            }
            else{
                cout << "다시 입력해주세요!" << endl;
            }
        }

        while(getchar() != '\n');
    }
}

void *StartTimer(void *timeVal) {
    unsigned int time = *(unsigned int *)timeVal;

    sleep(time);

    int sec = time % 60;
    time /= 60;
    int min = time % 60;
    time /= 60;
    int hr = time;

    cout << hr << "시간 " << min << "분 " << sec << "초 타이머가 종료되었습니다." << endl << ">> ";
    cout.flush();
    pthread_exit(NULL);
}

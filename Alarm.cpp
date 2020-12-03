#include "Alarm.h"


using namespace std;

// 현재시각
void Alarm::Nowtime()
{
    time_t curr_time;
 
    // 시간 표시를 위한 구조체를 선언합니다.
    struct tm *curr_tm;
 
    // time 함수는 1970년 1월 1일 이후 몇초가 지났는지를 계산합니다. NULL을 인자로 사용합니다.
    curr_time = time(NULL);
 
    // 지역 시간을 기준으로 변환 및 출력 편의를 위하여 tm 구조체에 저장합니다.(포맷팅)
    curr_tm = localtime(&curr_time);
 
    //출력 예제
    std::cout << "현재시각: " << curr_tm->tm_year + 1900 << "년 " << curr_tm->tm_mon + 1 << "일 " << curr_tm->tm_mday << "일" ;     
    std::cout << curr_tm->tm_hour << "시 " << curr_tm->tm_min << "분 " << curr_tm->tm_sec << "초" << '\n';

}

int Alarm::Time_cal(){
    hr2=hr*3600;
    min2=min*60;
    sec;
    total=hr2+min2+sec;
    return total;

}

int Alarm::Time_inputstring(){


    strcpy(str_buff, insert.c_str());

    char *tok = strtok(str_buff, " ");
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

    return hr, min, sec;


}




int Alarm::Alarm_function()
{

    
    while (1)
    {
        Nowtime();
       
        std::cout<<"설정 시간을 입력해주세요 ['시간' '분' '초' 자릿수를 모두 입력해주세요. (ex.4초 = 0시간 0분 4초 타이머 설정해줘)] ";
        std::cout<<">>";
        getline(cin,insert);

        Time_inputstring();

        Time_cal();

        std::cout << hr <<"시간"<< min<<"분"<<sec<< "초 타이머를 설정했어요!"<<'\n';
        Nowtime();


        std::this_thread::yield();
        
        std::this_thread::sleep_for(std::chrono::seconds(total));
        

                
       
    
        std::cout << hr<<"시간"<< min<<"분"<<sec<< "초 타이머가 종료되었습니다."<<'\n';
        Nowtime();
        char input;

        cout << "알람 기능을 계속 수행할까요? (y: 계속 | n: 종료) " << endl;
        cin >> input;
        if (input=='y' || input=='Y'){
            continue;       
        }
        else if (input=='n' || input=='N' )
        {
            cout << "알람 도움이 필요하면 언제든지 불러주세요.";
            cout << endl;
            break;
            
        }
        else{
            cout << "다시 입력해주세요!";
        }
        

    }
    return 0;
    
    


}

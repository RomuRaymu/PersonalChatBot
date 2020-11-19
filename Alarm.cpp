#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void timeover(int signum)
{
    printf("\n\ntime over !! \n\n");
    exit(0);
}

 
int main()
{
    while (1)
    {
        int timelimit;
        int timelimit1;
        int min;
        int hr;
        int test;

        int getYesNoKey(void);
        int getYesNoCancelKey(void);

        time_t now_time;
        struct tm *now_date;
        char buf[100];
        printf("알람기능을 실행했어요.\n");
    
        printf("몇 초로 설정할까요? (초단위)\n");
        scanf("%d",&timelimit);// 설정 시간 받기
 
        min = timelimit / 60;
        timelimit1 = timelimit % 60;
    
        hr = min / 60;
        min = min % 60;
        // 시간 시분초 구분 출력



    
        printf("%d시 %d분 %d초 타이머를 설정했어요!\n>", hr, min, timelimit1);
        
        time(&now_time); //현재 시각을 구한다.
    
        now_date = localtime(&now_time);//초 단위 값을 지역 시각(DateTime)을 구한다.
        strcpy(buf,asctime(now_date));//버퍼에 현재 시각을 출력
        puts(buf);    //표준 출력 스트림에 출력
        // 타임슬립 구현
        sleep(timelimit);
        //타임 슬립 'timelimit' 만큼 후
        
        
        printf("%d시 %d분 %d초 타이머가 종료되었습니다.\n>", hr, min, timelimit1);

        time(&now_time); //현재 시각을 구한다.
    
        now_date = localtime(&now_time);//초 단위 값을 지역 시각(DateTime)을 구한다.
        strcpy(buf,asctime(now_date));//버퍼에 현재 시각을 출력
        puts(buf);    //표준 출력 스트림에 출력
        printf("계속 진행할까요?(Y/N)\n");     
        char ch;
        getchar();
        scanf("%c",&ch);
        
        if(ch=='y'||ch=='Y'){// 사용자의 입력 받음
            printf("네. 계속 할게요.\n");            
        }
        else if (ch=='n'||ch=='N'){
            
            printf("타이머를 종료했어요.\n");
            exit(0); // 여기부터 챗봇으로 연결하는 코드 구현 하면 될 것 같습니다.
            
        }
    }
    

    

 
}
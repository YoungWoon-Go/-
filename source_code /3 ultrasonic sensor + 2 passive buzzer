#include <wiringPi.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <sys/time.h>   // <sys/time.h> 헤더 파일 추가
#include <softTone.h>


// 왼쪽 초음파
#define TRIGGER_LEFT 27
#define ECHO_LEFT 28
// 가운데 초음파
#define TRIGGER_MIDDLE 10
#define ECHO_MIDDLE 11
// 오른쪽 초음파
#define TRIGGER_RIGHT 15
#define ECHO_RIGHT 16

// buzzer 왼쪽, 오른쪽
#define LEFT_BUZZER_PIN 30
#define RIGHT_BUZZER_PIN 8

// 40cm 이내부터 buzzer 작동
#define TRIGGER_THRESHOLD 40

// 거리에 따라 delay (가까울수록 빨리) -> 이 함수를 사용하는 순간 부저 작동X
void delayByDistance(double distance)
{
    int delayTime = (int)distance / 100;
    delay(delayTime);
}
// 부저 울리기
void playBuzzer(int buzzerPin, double distance) {
    int frequency;
    int delaytime;
    // int delaytime = (int)distance/100;

    if (distance <= 40 && distance > 25) {
        frequency = 700;
        delaytime = 300;
    } else if (distance <= 25 && distance > 10) {
        frequency = 1000;
        delaytime = 150;
    } else if (distance <= 10) {
        frequency = 3000;
        delaytime = 50;
    } else {
        frequency = 0;
        delaytime = 0;
    }

	// softToneWrite(gpio pin num, 주파수 톤(숫자))
	
    softToneWrite(buzzerPin, frequency);
    delay(delaytime);	// 소리 길이
    //delayByDistance(distance);
    
    softToneWrite(buzzerPin, 0);
    delay(delaytime);
    //delayByDistance(distance);
}
int main(void)
{
	/* -----set up----- */
	
    if (wiringPiSetup() == -1) {
        return 1;
    }
	
	if (softToneCreate(LEFT_BUZZER_PIN) != 0 || softToneCreate(RIGHT_BUZZER_PIN) != 0) {
        return 1;
    }
	
    pinMode(TRIGGER_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIGGER_MIDDLE, OUTPUT);
    pinMode(ECHO_MIDDLE, INPUT);
    pinMode(TRIGGER_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);
  
    while(1){
		/* -----거리 측정----- */
		
		// 왼쪽 초음파 센서 측정
		digitalWrite(TRIGGER_LEFT, LOW);
		usleep(10);
		digitalWrite(TRIGGER_LEFT, HIGH);
		usleep(10);
		digitalWrite(TRIGGER_LEFT, LOW);

		struct timeval start, stop;
		while (digitalRead(ECHO_LEFT) == 0) {	// 펄스 발생
			gettimeofday(&start, NULL);
		}
		while (digitalRead(ECHO_LEFT) == 1) {	// 펄스 돌아옴
			gettimeofday(&stop, NULL);
		}
		// 리턴 투 타임 = (end시간 - start시간)
		double elapsedTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
		// 왼쪽 초음파의 거리 값
		double distance_left = elapsedTime * (34000.0 / 2.0) / 1000000.0;  // 속도를 cm/us로 변환
		
		/* -----부저 발생----- */
		
		// 왼쪽 buzzer 울리기
		playBuzzer(LEFT_BUZZER_PIN, distance_left);

		//sleep(1);
		//usleep(1000000);  // 1초 대기
		
		/* -----거리 측정----- */
		
		// 가운데 초음파 센서 측정
		digitalWrite(TRIGGER_MIDDLE, LOW);
		usleep(10);
		digitalWrite(TRIGGER_MIDDLE, HIGH);
		usleep(10);
		digitalWrite(TRIGGER_MIDDLE, LOW);

		while (digitalRead(ECHO_MIDDLE) == 0) {
			gettimeofday(&start, NULL);
		}
		while (digitalRead(ECHO_MIDDLE) == 1) {
			gettimeofday(&stop, NULL);
		}
		elapsedTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
		double distance_middle = elapsedTime * (34000.0 / 2.0) / 1000000.0;  // 속도를 cm/us로 변환
		
		/* -----부저 발생----- */
		
		// 왼쪽, 오른쪽 buzzer 울리기
		playBuzzer(LEFT_BUZZER_PIN, distance_middle);
		playBuzzer(RIGHT_BUZZER_PIN, distance_middle);

		/* -----거리 측정----- */
		
		// 오른쪽 초음파 센서 측정
		digitalWrite(TRIGGER_RIGHT, LOW);
		usleep(10);
		digitalWrite(TRIGGER_RIGHT, HIGH);
		usleep(10);
		digitalWrite(TRIGGER_RIGHT, LOW);

		while (digitalRead(ECHO_RIGHT) == 0) {
			gettimeofday(&start, NULL);
		}
		while (digitalRead(ECHO_RIGHT) == 1) {
			gettimeofday(&stop, NULL);
		}
		elapsedTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
		double distance_right = elapsedTime * (34000.0 / 2.0) / 1000000.0;  // 속도를 cm/us로 변환
		
		/* -----부저 발생----- */
		
		// 오른쪽 buzzer 울리기
		playBuzzer(RIGHT_BUZZER_PIN, distance_right);


		// 1초마다 거리값 측정 및 갱신
		sleep(0.05);
		// 실시간으로 거리 측정 출력
		printf("-----Distance----- \nLeft: %.2f cm \nMiddle: %.2f cm \nRight: %.2f cm\n\n", distance_left, distance_middle, distance_right);

	}

    
    return 0;
}

#include <wiringPi.h>
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
#define LEFT_BUZZER_PIN 8
#define RIGHT_BUZZER_PIN 20

// 40cm 이내부터 buzzer 작동
#define TRIGGER_THRESHOLD 40

/*
void setup()
{
	wiringPiSetup();
	
	if (softToneCreate(LEFT_BUZZER_PIN) != 0 || softToneCreate(RIGHT_BUZZER_PIN) != 0) {
        return 1;
    }
	
    pinMode(TRIGGER_LEFT, OUTPUT);
    pinMode(ECHO_LEFT, INPUT);
    pinMode(TRIGGER_MIDDLE, OUTPUT);
    pinMode(ECHO_MIDDLE, INPUT);
    pinMode(TRIGGER_RIGHT, OUTPUT);
    pinMode(ECHO_RIGHT, INPUT);
    
    //pinMode(LEFT_BUZZER_PIN, OUTPUT);
    //pinMode(RIGHT_BUZZER_PIN, OUTPUT);
}
*/

// 초음파 센서를 통해 거리 구하기
double getDistance(int triggerPin, int echoPin)
{
    digitalWrite(triggerPin, LOW);
    delayMicroseconds(2);	//usleep(10)
    digitalWrite(triggerPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(triggerPin, LOW);

    //unsigned long pulseTime = pulseIn(echoPin, HIGH);
    //double distance = pulseTime / 58.0;
    struct timeval start, stop;
    while (digitalRead(ECHO_LEFT) == 0) {
        gettimeofday(&start, NULL);
    }
    while (digitalRead(ECHO_LEFT) == 1) {
        gettimeofday(&stop, NULL);
    }
    
	double elapsedTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
    double distance = elapsedTime * (34000.0 / 2.0) / 1000000.0;  // 속도를 cm/us로 변환

    return distance;
}

// 거리에 따라 delay (가까울수록 빨리)
void delayByDistance(double distance)
{
    int delayTime = distance / 100;
    delay(delayTime);
}

// 부저 울리기
void playBuzzer(int pin, double distance) {
    int frequency;
    //int delaytime;

    if (distance <= 40 && distance > 25) {
        frequency = 2000;
        //delaytime = 1000;
    } else if (distance <= 25 && distance > 10) {
        frequency = 3000;
        //delaytime = 100;
    } else if (distance <= 10) {
        frequency = 4000;
        //delaytime = 10;
    } else {
        frequency = 0;
    }

	// softToneWrite(gpio pin num, 주파수 톤(숫자))
	
    softToneWrite(pin, frequency);
    //delay(100);	// 소리 길이
    delayByDistance(distance);
    
    softToneWrite(pin, 0);
    //delay(100);
    delayByDistance(distance);
}

int main(void)
{
    // setup();
    /*
    함수
	
	void setup()
    double getDistance(int triggerPin, int echoPin)
    void delayByDistance(double distance) 
    void playBuzzer(int pin, double distance) 
     */

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
    
    while (1)
    {
        double distL = getDistance(TRIGGER_LEFT, ECHO_LEFT);
        double distM = getDistance(TRIGGER_MIDDLE, ECHO_MIDDLE);
        double distR = getDistance(TRIGGER_RIGHT, ECHO_RIGHT);
        
        if(distL <= TRIGGER_THRESHOLD)
        {
			playBuzzer(TRIGGER_LEFT, distL);
		}
		else if (distR <= TRIGGER_THRESHOLD)
		{
			playBuzzer(TRIGGER_RIGHT, distR);
		}
		else if (distM <= TRIGGER_THRESHOLD)
		{
			playBuzzer(TRIGGER_LEFT, distM);
			playBuzzer(TRIGGER_RIGHT, distM);
		}

/*
        if ((distL <= TRIGGER_THRESHOLD && distR <= TRIGGER_THRESHOLD) || distM <= TRIGGER_THRESHOLD)
        {
            delayByDistance(fmin(distL, distR));
            
        }
        else if (distL <= TRIGGER_THRESHOLD)
        {
            playPiezoTone(LEFT_BUZZER_PIN, 262, 500);
            delayByDistance(distL);
        }
        else if (distR <= TRIGGER_THRESHOLD)
        {
            playPiezoTone(RIGHT_BUZZER_PIN, 262, 500);
            delayByDistance(distR);
        }
        else
        {
            delay(500);
        }
*/
    }

    return 0;
}

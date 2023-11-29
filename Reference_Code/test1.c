// 사물이 가까워지는 초음파의 위치에 따라 그와 동일한 부저가 울리도록 함. 가운데 위치한 초음파 센서에 가까워지면 양쪽 부저가 동시에 울리는 코드.
// by chat GPT
#include <stdio.h>
#include <wiringPi.h>
#include <unistd.h>
#include <sys/time.h>
#include <softTone.h>

#define TRIGGER_LEFT 27     // 왼쪽 초음파 센서의 Trigger 핀 번호
#define ECHO_LEFT 28        // 왼쪽 초음파 센서의 Echo 핀 번호
#define TRIGGER_MIDDLE 10   // 가운데 초음파 센서의 Trigger 핀 번호
#define ECHO_MIDDLE 11      // 가운데 초음파 센서의 Echo 핀 번호
#define TRIGGER_RIGHT 15    // 오른쪽 초음파 센서의 Trigger 핀 번호
#define ECHO_RIGHT 16       // 오른쪽 초음파 센서의 Echo 핀 번호
#define LEFT_BUZZER_PIN 8   // 왼쪽 부저의 핀 번호
#define RIGHT_BUZZER_PIN 20 // 오른쪽 부저의 핀 번호

void playBuzzer(int pin, int frequency) {
    softToneWrite(pin, frequency);
    delay(100);     // 소리 길이
    softToneWrite(pin, 0);
    delay(100);
}

int main(void) {
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
   
    while (1) {
        // 왼쪽 초음파 센서 측정
        digitalWrite(TRIGGER_LEFT, LOW);
        usleep(10);
        digitalWrite(TRIGGER_LEFT, HIGH);
        usleep(10);
        digitalWrite(TRIGGER_LEFT, LOW);

        struct timeval start, stop;
        while (digitalRead(ECHO_LEFT) == 0) {
            gettimeofday(&start, NULL);
        }
        while (digitalRead(ECHO_LEFT) == 1) {
            gettimeofday(&stop, NULL);
        }
        double elapsedTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec);
        double distance_left = elapsedTime * (34000.0 / 2.0) / 1000000.0;  // 속도를 cm/us로 변환

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

        printf("Distance - Left: %.2f cm, Middle: %.2f cm, Right: %.2f cm\n", distance_left, distance_middle, distance_right);

        // 부저 울리기
        if (distance_middle <= 40 && distance_middle > 25) {
            playBuzzer(LEFT_BUZZER_PIN, 2000);
            playBuzzer(RIGHT_BUZZER_PIN, 2000);
        } else if (distance_middle <= 25 && distance_middle > 10) {
            playBuzzer(LEFT_BUZZER_PIN, 3000);
            playBuzzer(RIGHT_BUZZER_PIN, 3000);
        } else if (distance_middle <= 10) {
            playBuzzer(LEFT_BUZZER_PIN, 4000);
            playBuzzer(RIGHT_BUZZER_PIN, 4000);
        } else {
            playBuzzer(LEFT_BUZZER_PIN, 0);
            playBuzzer(RIGHT_BUZZER_PIN, 0);
        }

        usleep(1000000);  // 1초 대기
    }

    return 0;
}

# 라즈베리파이를 활용한 스포츠 스마트 고글 구현

## Introduction
* 자전거를 타는 라이더나 마라톤을 하는 러너들은 체력의 한계치에서 주위의 다른 이들과 경쟁
* 체력의 한계 상황에서 외부 정보들을 수집하는 것에 둔해지는 우리 몸의 감각
* 현재 상용화 되어 있는 스마트 워치의 경우 운동 중에 시선을 이동시키기 때문에 경기력과 안전에 영향을 끼침
* 이를 대신할 보조 감각으로 스마트 고글을 고안



## Concept
* 자동차 후방 감지 센서를 바탕으로 고안
* 초음파 센서를 이용하여 거리를 측정
* 측정한 거리를 바탕으로 충돌을 방지하기 위해 소리(Buzzer)를 제공
* 카메라를 이용하여 사물을 인식
* 인식한 사물을 스피커를 통해 음성 안내

![image](https://github.com/YoungWoon-Go/OSS_project/assets/144092472/fa77f2cd-0df5-4759-971d-76dcc207f814)

## Description
* 초음파 센서 3개를 왼쪽, 오른쪽, 가운데에 위치하여 각각 거리를 측정하도록 함
* 사물이 가까워질수록 passive buzzer 2개에서 소리가 빨라짐
* 체력에 따라 저하되는 시각 인지 기능을 대신 할 라즈베리파이 카메라 모듈을 사용
* 사물을 인식하여 해당 객체가 무엇인지 음성으로 출력하여 안내

  [image](https://github.com/YoungWoon-Go/OSS_project/assets/144092472/ca0bfbd0-d041-4f17-9f08-5192dead4661)
  * RED: 초음파 커리 측정 센서
  * BLUE: 피에조 부저 모듈

## Result
### 초음파 센서와 부저

### 카메라와 음성 안내


## References
* https://andjjip.tistory.com/242 (라즈베리파이 PWM, 초음파센서, 후방감지센서 구현)
* https://m.blog.naver.com/rldhkstopic/221516784267 (라즈베리파이 초음파 센서 3개 이용하기)
* https://m.blog.naver.com/roboholic84/221623436924 (라즈베리파이와 피에조 부저 사용하기)
* https://www.raspberrypi.com/documentation/computers/camera_software.html
  (Camera software Introducing the Raspberry Pi Cameras)
* https://www.dexterindustries.com/howto/use-google-cloud-vision-on-the-raspberry-pi/
  (Use Google Cloud Vision On the Raspberry Pi and GoPiGo)

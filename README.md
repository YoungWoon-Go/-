# 라즈베리파이를 활용한 스포츠 스마트 고글 기술 구현

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





## Estimated result design

![image](https://github.com/YoungWoon-Go/sports-smart-goggles-using-raspberry-pie/assets/144092472/54dc556d-42d0-4d4a-9ae5-c9f0ff96bbfe)



## Tools used



* Rasberry Pi 3

![image](https://github.com/YoungWoon-Go/sports-smart-goggles-using-raspberry-pie/assets/144092472/51283e18-b8b3-4678-8dc3-f121c378cc27)


* 초음파 거리 측정 센서 X3

![image](https://github.com/YoungWoon-Go/sports-smart-goggles-using-raspberry-pie/assets/144092472/6cfdf3fb-75f5-4317-bb1b-597f2004f854)



* Passive Buzzer X2

![image](https://github.com/YoungWoon-Go/sports-smart-goggles-using-raspberry-pie/assets/144092472/9eec9001-aa38-4640-8ffc-f0d21bd8558a)


* Pi Camera

![image](https://github.com/YoungWoon-Go/sports-smart-goggles-using-raspberry-pie/assets/144092472/db4a1d04-6869-46e6-977e-03fa46de12b4)



 




## Description

### 장애물 감지 및 부저 알림
* 초음파 센서 3개를 왼쪽, 오른쪽, 가운데에 위치하여 각각 거리를 측정하도록 함
* 사물이 가까워질수록 passive buzzer 2개에서 소리가 빨라짐

  ![스크린샷 2023-11-25 오후 3 44 30](https://github.com/YoungWoon-Go/OSS_project/assets/144092472/7e25a499-70c0-4764-949a-06651f2559ac)
  * RED: 초음파 거리 측정 센서
  * BLUE: 피에조 부저 모듈



### 카메라를 통해 사물을 인식하고 알림
* 체력에 따라 저하되는 시각 인지 기능을 대신하기 위해 라즈베리파이 카메라 모듈을 사용하여 Google Cloud Vision API를 활용한다. Google Cloud Vision API란 구글에서 제공해주는 머신러닝 기반의 이미지 분석 API이다.
* 사물을 인식하여 해당 객체가 무엇인지에 대한 정보를 바탕으로 음성으로 출력하여 안내하기 위해서는 텍스트를 음성으로 변환하는 파이썬 라이브러리인 Google의 Text-to-Speech API인 gTTS를 사용한다.





## Result
### 초음파 센서와 부저

🔊🔊🔊


https://github.com/YoungWoon-Go/OSS_project/assets/144092472/9bfed4c2-ca12-4fa8-ae06-918ab32e483b



### 카메라와 음성 안내
![image](https://github.com/YoungWoon-Go/OSS_project/assets/144092472/6498b4e4-b209-4694-ad60-e01316eac236)
![image](https://github.com/YoungWoon-Go/OSS_project/assets/144092472/5d7400d0-88ee-4fd6-abb9-605acf522cf1)
<img width="791" alt="스크린샷 2023-11-28 오후 10 47 54" src="https://github.com/YoungWoon-Go/OSS_project/assets/144092472/e863945d-881f-4c67-a3a2-f1251a56b1a0">

![image](https://github.com/YoungWoon-Go/OSS_project/assets/144092472/d2d42765-a37c-494f-803a-0f39678f1458)

<img width="791" alt="스크린샷 2023-11-28 오후 10 49 14" src="https://github.com/YoungWoon-Go/OSS_project/assets/144092472/d7ad32e0-3070-4e35-a8b6-dd9248a037f1">

![image](https://github.com/YoungWoon-Go/sports-smart-goggles-using-raspberry-pie/assets/144092472/87fc6ab9-f555-4cd2-8020-d28667ca000f)
<img width="839" alt="스크린샷 2023-11-28 오후 10 50 29" src="https://github.com/YoungWoon-Go/OSS_project/assets/144092472/00a82631-d92a-4a82-b94f-0c4f737fbd03">





## References
* https://andjjip.tistory.com/242 (라즈베리파이 PWM, 초음파센서, 후방감지센서 구현)
* https://m.blog.naver.com/rldhkstopic/221516784267 (라즈베리파이 초음파 센서 3개 이용하기)
* https://m.blog.naver.com/roboholic84/221623436924 (라즈베리파이와 피에조 부저 사용하기)
* https://www.raspberrypi.com/documentation/computers/camera_software.html
  (Camera software Introducing the Raspberry Pi Cameras)
* https://www.dexterindustries.com/howto/use-google-cloud-vision-on-the-raspberry-pi/
  (Use Google Cloud Vision On the Raspberry Pi and GoPiGo)
* https://neosarchizo.gitbooks.io/raspberrypiforsejonguniv/content/chapter4.html (Pi camera)

digitalWrite(TRIGGER, LOW); 
usleep(10); 
digitalWrite(TRIGGER, HIGH); 
usleep(10); 
digitalWrite(TRIGGER, LOW); 

struct timeval start, stop; 
while (digitalRead(ECHO) == 0) {	 	// 펄스 발생
	gettimeofday(&start, NULL); 
} 
while (digitalRead(ECHO) == 1) {	 	// 펄스 돌아옴 
	gettimeofday(&stop, NULL); 
}

 // 리턴 투 타임 = (end시간 - start시간) 
double elapsedTime = (stop.tv_sec - start.tv_sec) * 1000000 + (stop.tv_usec - start.tv_usec); 
// 초음파의 거리 값 
double distance = elapsedTime * (34000.0 / 2.0) / 1000000.0; // 속도를 cm/us로 변환 

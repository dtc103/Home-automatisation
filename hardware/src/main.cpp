#include <Arduino.h>
#include <Matrix.h>

Matrix matrix(20000, 20000);

//TaskHandle_t Task1;
//void Task1Code(void *parameter);

void setup() {
	Serial.begin(115200);
  	// put your setup code here, to run once:
	/*
	xTaskCreatePinnedToCore(
		Task1Code,
		"Task1",
		10000,
		NULL,
		0,
		&Task1,
		1
	);*/
}

void loop() {
  	// put your main code here, to run repeatedly:
	//Serial.print(xPortGetCoreID());
	Serial.println("----------------------------------------------------------------------------------------------------------------------------------------");
}

void Task1Code(void *parameter){
	//Serial.print(xPortGetCoreID());
}

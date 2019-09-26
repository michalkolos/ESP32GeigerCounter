#include <Arduino.h>

TaskHandle_t taskAltLoop;
void altLoop(void * parameter);

void setup() {
	Serial.begin(115200);

	Serial.print("setup() running on core ");
	Serial.println(xPortGetCoreID());

	xTaskCreatePinnedToCore(
    	altLoop, /* Function to implement the task */
    	"altLoop", /* Name of the task */
    	10000,  /* Stack size in words */
    	NULL,  /* Task input parameter */
    	0,  /* Priority of the task */
    	&taskAltLoop,  /* Task handle. */
    	0); /* Core where the task should run */
}



void loop() {
    Serial.print("loop() running on core ");
	Serial.println(xPortGetCoreID());

	delay(1000);
}




void altLoop(void * parameter){
	while(1){

		Serial.print("altLoop() running on core ");
		Serial.println(xPortGetCoreID());
		
		delay(1100);

	}

	vTaskDelete(taskAltLoop);
}
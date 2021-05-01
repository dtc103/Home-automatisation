#include <Arduino.h>
#include <Matrix.h>
#include <Adafruit_NeoPixel.h>
#include <color_effects.h>


Panel p(2, 12, 20);
Panel_Effect pe(p);

void interrupt_handler(){
	
	
}

void setup() {
	attachInterrupt(digitalPinToInterrupt(2), interrupt_handler, RISING);
	Serial.begin(9600);
	pe.begin();
	pe.start();
}

void loop() {
	Serial.println(pe.is_running());
	Serial.print("asdf");
	delay(500);
}

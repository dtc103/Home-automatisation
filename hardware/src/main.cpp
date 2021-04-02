#include <Arduino.h>
#include <WiFi.h>
#include <panel/panel.h>
#include <panel/effects/color_effects/color_effects.h>

const char* ssid = "FRITZ!Box 6490 Cable";
const char* password = "97445628199902922569";

const char* host = "192.168.178.20";
const int port = 3000;

Panel p(13, 12, 20);

void setup() {
  // put your setup code here, to run once:
    p.begin();
    p.clear();
}

void loop() {
    // put your main code here, to run repeatedly:
    //Color_Effects::drops(p);
    //Color_Effects_Dynamic::color_lane(p, 20);
    Color_Effects_Static::fill(p, 255, 255, 255, 255);
}
#include <Arduino.h>
#include <PanelServer.h>
#include <PanelDefinitions.h>

//#define CHECK_AP 1

PanelServer server(80);

#ifdef CHECK_AP
char ssid[] = "devicenetwork";
char pw[] = "6C-ji40a";
#else
char ssid[] = "FRITZ!Box 6490 Cable";
char pw[] = "97445628199902922569";
#endif

void setup() {
    Serial.begin(9600);
	server.begin(ssid, pw);
    //server.authenticate(ACCESS_POINT_NAME, ACCESS_POINT_PORT, DEVICE_NAME);
}

void loop() {

}
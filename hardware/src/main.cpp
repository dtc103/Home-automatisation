#include <Arduino.h>
#include <PanelServer.h>
#include <PanelDefinitions.h>

PanelServer server(80);

char ssid[] = "devicenetwork";
char pw[] = "923492760463546739763524";

void setup() {
    Serial.begin(9600);
	server.begin(ssid, pw);
    //server.authenticate(ACCESS_POINT_NAME, ACCESS_POINT_PORT, DEVICE_NAME);
}

void loop() {

}
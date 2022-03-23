#include <PanelServer.h>


void PanelServer::begin(const char* ssid, const char* pass){
    //begin server at port 80
    this->server = WiFiServer(this->port);
    
    //connect to access point
    if(String(pass) == String("")){
        WiFi.begin(ssid);
    }else{
        WiFi.begin(ssid, pass);
    }

    while(WiFi.status() != WL_CONNECTED);

    //if connected to the access point, start the server
    if(WiFi.status() == WL_CONNECTED){
        this->server.begin();
        Serial.println("Connected to wifi");
    }
}

bool PanelServer::authenticate(const char* servername, int port, const char* own_device_name){
    WiFiClient client;

    String post_req = String(
        "{"
        "\"devicename\" : \"" + String(own_device_name) + "\",\n"
        "\"mac\" : \"" + WiFi.macAddress() + "\",\n"
        "\"ip\" : \""+ WiFi.localIP().toString() + "\",\n"
        "\"port\" : \"" + this->port + "\"\n"
        "}"
    );

    if(client.connect(servername, port)){
        Serial.println("connected to server");

        //send device name and ip to server
        client.println("POST /authenticate HTTP/1.1\n"
        "Host: " + String(servername) + "\n"
        "Content-type: application/json\n"
        "Content-Length: " + String(post_req).length() + "\n"
        "\n"
        + post_req);
    }

    while(client.available() == 0);

    if(client.available()){
        Serial.println(client.readString());
    }

    client.stop();

    return true;
}
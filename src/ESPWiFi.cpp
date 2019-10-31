#include <Arduino.h>
#include "WiFi.h"
//#include "Drone.h"
#include "AsyncUDP.h"
#include <string.h>

using namespace std;

    const char * ssid = "flexlab2";
    const char * password = "flexiwifi";
    const int udpPort = 1995;

    AsyncUDP udp;
    WiFiUDP udpSender;

    void sendMessage(String ip, int port, String message){
        udpSender.beginPacket(ip.c_str(), port);
        udpSender.printf(message.c_str());
        udpSender.endPacket();  
    }

    void setup() {
        Serial.begin(9600);
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid, password);
        if (WiFi.waitForConnectResult() != WL_CONNECTED) {
            Serial.println("WiFi Failed");
            while(1) {
                delay(1000);
            }
        }
        if(udp.listen(udpPort)) {
            Serial.print("UDP Listening on IP: ");
            Serial.println(WiFi.localIP());
            udp.onPacket([](AsyncUDPPacket packet) {
                Serial.print("UDP Packet Type: ");
                Serial.print(packet.isBroadcast()?"Broadcast":packet.isMulticast()?"Multicast":"Unicast");
                Serial.print(", From: ");
                Serial.print(packet.remoteIP());
                Serial.print(":");
                Serial.print(packet.remotePort());
                Serial.print(", To: ");
                Serial.print(packet.localIP());
                Serial.print(":");
                Serial.print(packet.localPort());
                Serial.print(", Length: ");
                Serial.print(packet.length());
                Serial.print(", Data: ");
                Serial.write(packet.data(), packet.length());
                Serial.println();
                //reply to the client
                packet.printf("Got %u bytes of data", packet.length());

                //send reply
                sendMessage(packet.remoteIP().toString(), udpPort, "reply from esp32");
            });
        }
    }

    void loop()
    {
        delay(5000);
        //Send broadcast
        udp.broadcast("Hej Ebbe!!!!! DET MIG LAARS");

        Serial.print("Giv Lars noget kage Please! ");
        Serial.print(WiFi.localIP());
        Serial.print(" on port: ");
        Serial.println(udpPort);
    } 

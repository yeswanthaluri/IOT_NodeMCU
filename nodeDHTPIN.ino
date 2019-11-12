// Hardware: NodeMCU,DHT11

#include <DHT.h>  // Including library for dht

#include <ESP8266WiFi.h>
 
String apiKey = "kZ2772LJA165KP6U0";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "yesh";     // replace with your wifi ssid and wpa2 key
const char *pass =  "ABCD#123";
const char* server = "api.thingspeak.com";

#define DHTPIN D5          //pin where the dht11 is connected
 
DHT dht(DHTPIN, DHT11);
int level=0;
WiFiClient client;
 
void setup() 
{
       Serial.begin(115200);
       delay(10);
       dht.begin();
 
  pinMode(D1, INPUT);
  pinMode(D2,INPUT );
  pinMode(D3, INPUT);
  pinMode(D7,OUTPUT );
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 
void loop() 
{
  
      float l1 = digitalRead(D1);
      float l2 = digitalRead(D2);
      
      float l3 = digitalRead(D3);
      if(l1==LOW)
      level=1;
      else
      level=level;
      if(l2==LOW)
      level=2;
      else
      level=level;
    if(l3==LOW)
      level=3;
      else
      level=level;
                Serial.println(level);
             if(level==3)
                    {
                                      Serial.println("Motor Off");
                                      digitalWrite(D7,HIGH);
                    }
                    else
                    {
                      Serial.println("Motor On");
                                      digitalWrite(D7,LOW);
                      }

             
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(level);
                     
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
//                             Serial.print("Fire: ");
//                             Serial.print(t);
//                             Serial.print("  Gas: ");
//                             Serial.print(h);
//                             Serial.print("     IR:      ");
//                             Serial.print(ir);
                             Serial.println("%. Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates, i've set it to 30 seconds
  delay(10000);
}

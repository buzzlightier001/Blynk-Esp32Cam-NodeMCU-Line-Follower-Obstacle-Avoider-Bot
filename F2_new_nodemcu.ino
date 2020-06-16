#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SoftwareSerial.h>

SoftwareSerial serial; // Tx(NODEMCU) to Rx(arduino), and Rx(NODEMCU) to TX(arduino)
 
int pinValue1;
int pinValue2;
int pinValue3;
int pinValue4;
int pinValue5;
int pinValue6;
 
String v2arduino; // values to arduino
 
char auth[] = "TGbsv44VAn_AHy7wX3Xpnce_fQykv6gD";
 
// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "IITRPR";
char pass[] = "9810762494";
 
void setup(){
  // Debug console
  Serial.begin(9600);
  serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}
 
void loop(){

  Blynk.run();
  toarduino();
  if (serial.available()>0){
    serial.print(v2arduino);// here it's writing to arduino
  }
}

BLYNK_WRITE(V10){
   pinValue1 = param.asInt(); // assigning incoming value from pin V10 to a variable
  
} 
BLYNK_WRITE(V11){
   pinValue2 = param.asInt(); // assigning incoming value from pin V11 to a variable
 
} 
BLYNK_WRITE(V12){
   pinValue3 = param.asInt(); // assigning incoming value from pin V12 to a variable
 
}
BLYNK_WRITE(V13){
   pinValue4 = param.asInt(); // assigning incoming value from pin V13 to a variable
 
}
BLYNK_WRITE(V14){
   pinValue5 = param.asInt(); // assigning incoming value from pin V14 to a variable
  
}
BLYNK_WRITE(V15){
   pinValue6 = param.asInt(); //line follower switch.
  
}


void toarduino(){
v2arduino = v2arduino + pinValue1 + "," + pinValue2 + "," + pinValue3 +"," + pinValue4 + "," + pinValue5 + "," + pinValue6 ; 
Serial.println(v2arduino); 
delay(100); 
v2arduino = ""; 
}

#include <SoftwareSerial.h>
SoftwareSerial nodemcu(0,1);

#include<NewPing.h>
 
long int data1; 
int firstVal, secondVal, thirdVal, fourthVal, fifthVal, Switch;
  
String myString; // complete message from arduino, which consistors of snesors data
char rdata; // received charactors
String cdata; // complete data

#define left A0
#define center A4
#define right A1
#define echo A2
#define trig A3

int M_A1=2;
int M_A2=3;
int M_B1=4;
int M_B2=5;
int S_A=9;
int S_B=10;

long distance;
long duration;
int set = 30;
 
void setup(){
  Serial.begin(9600); 
  nodemcu.begin(9600);
  
  pinMode(left,INPUT);
  pinMode(center,INPUT);
  pinMode(right,INPUT);
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  

  pinMode(M_B1,OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(S_B, OUTPUT);
  pinMode(S_A, OUTPUT);
  
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println();
  distance=data();
  delay(100);
  distance=data();
  delay(100);
  distance=100;

  analogWrite(S_A, 150);
  analogWrite(S_B, 150);
  delay(100);
}
 
void loop(){  
  if(nodemcu.available() == 0 ){
    delay(100); // 100 milli seconds
//    Serial.println("1");
//          Serial.println("");
//    Driver();
  }
 
  if ( nodemcu.available() > 0 ){
    rdata = nodemcu.read(); 
    myString = myString+ rdata; 
  
    if( rdata == '\n'){
      Serial.println(myString);
      String l = getValue(myString, ',', 0);
      String m = getValue(myString, ',', 1);
      String n = getValue(myString, ',', 2); 
      String o = getValue(myString, ',', 3);
      String p = getValue(myString, ',', 4); 
      String q = getValue(myString, ',', 5);
 
      firstVal = l.toInt(); // forward
      secondVal = m.toInt(); // reverse
      thirdVal = n.toInt(); // left
      fourthVal = o.toInt(); // right
      fifthVal = p.toInt(); // stop
      Switch = q.toInt();// line follower
 
      myString = "";
      distance=data();
      if ( fifthVal == 1 || distance < set){ // stop
          Serial.println("Rest");
          Serial.println("");
           
          Stop(); 
      }else if(Switch == 0){        
         if ( firstVal == 1 ){// forward
           Serial.println("Forward");
           Serial.println("");
           
           Forward();           
         }else if ( secondVal == 1 ){ // reverse direction
           Serial.println("Backward");
           Serial.println("");
           
           Backward();
         }else if ( thirdVal == 1 ){// Right
           Serial.println("Left");
           Serial.println("");

           Left();            
         } else if ( fourthVal == 1 ){// left
           Serial.println("Right");
           Serial.println("");

           Right();
         }
      }else{
        
          Serial.println("Linefollower");
        Serial.println("");
        
        Driver();
      }
    }
  }else{
     
      Serial.println("Linefollower");
      Serial.println("");
      Driver();
  } 
}
 
String getValue(String data1, char separator, int index){
    int found = 0;
    int strIndex[] = { 0, -1 };
    int maxIndex = data1.length() - 1;
 
    for (int i = 0; i <= maxIndex && found <= index; i++) {
        if (data1.charAt(i) == separator || i == maxIndex) {
            found++;
            strIndex[0] = strIndex[1] + 1;
            strIndex[1] = (i == maxIndex) ? i+1 : i;
        }
    }
    return found > index ? data1.substring(strIndex[0], strIndex[1]) : "";
}

void Driver(){
  distance=data();
  Serial.print("distance: ");
  Serial.print(distance);
  Serial.println();
  if(distance > set){
  
        if(digitalRead(left)==0 && !digitalRead(center)==0 && digitalRead(right)==0){//line detected by both
          Serial.println("Forward");
          Serial.println("");
          
          Forward();
  }else if(digitalRead(left)==0 && !digitalRead(center)==0 && !analogRead(right)==0){//line detected by right sensor
          Serial.println("Right");
          Serial.println("");
          Right();
  }else if(digitalRead(left)==0 && digitalRead(center)==0 && !analogRead(right)==0){//line detected by right sensor
          Serial.println("Right");
          Serial.println("");
          Right();
  }else if(!digitalRead(left)==0 && !digitalRead(center)==0 && digitalRead(right)==0){//line detected by left sensor
          Serial.println("Left");
          Serial.println("");
          Left();
  }else if(!digitalRead(left)==0 && digitalRead(center)==0 && digitalRead(right)==0){//line detected by left sensor
          Serial.println("Left");
          Serial.println("");
          Left();
  }else if(!digitalRead(left)==0 && !digitalRead(center)==0 && !digitalRead(right)==0){//line detected by none
          Serial.println("Stop");
          Serial.println("");
          Stop(); 
  }else if( digitalRead(left)==0 && digitalRead(center)==0 && digitalRead(right)==0){//line detected by none
          Serial.println("Stop");
          Serial.println("");
          Stop(); 
  }
  }else{
    Stop(); 
  } 
}

long data(){
  digitalWrite(trig, LOW);
   delayMicroseconds(2);
   digitalWrite(trig, HIGH);
   delayMicroseconds(10);
   digitalWrite(trig, LOW);
   pinMode(echo, INPUT);
   duration = pulseIn(echo, HIGH);
  return duration / 29 / 2;
}

void Forward(){
//    motor1.run(FORWARD);
//    motor1.setSpeed(180);
//    motor2.run(FORWARD);
//    motor2.setSpeed(180);
//    motor3.run(FORWARD);
//    motor3.setSpeed(180);
//    motor4.run(FORWARD);
//    motor4.setSpeed(180);
    analogWrite(S_A, 130); 
    analogWrite(S_B, 130);
    digitalWrite(M_A1, HIGH);
    digitalWrite(M_A2, LOW);
    digitalWrite(M_B1, HIGH);
    digitalWrite(M_B2, LOW);

}

void Backward(){
//    motor1.run(BACKWARD);
//    motor1.setSpeed(180);
//    motor2.run(BACKWARD);
//    motor2.setSpeed(180);
//    motor3.run(BACKWARD);
//    motor3.setSpeed(180);
//    motor4.run(BACKWARD);
//    motor4.setSpeed(180);
    analogWrite(S_A, 140); 
    analogWrite(S_B, 140);
    digitalWrite(M_A1, LOW);
    digitalWrite(M_A2, HIGH);
    digitalWrite(M_B1, LOW);
    digitalWrite(M_B2, HIGH);


}

void Left(){
//    motor1.run(FORWARD);
//    motor1.setSpeed(180);
//    motor2.run(FORWARD);
//    motor2.setSpeed(180);
//    motor3.run(BACKWARD);
//    motor3.setSpeed(180);
//    motor4.run(BACKWARD);
//    motor4.setSpeed(180);
    analogWrite(S_A, 255); 
    analogWrite(S_B, 255);  
    digitalWrite(M_A1, LOW);
    digitalWrite(M_A2, HIGH);
    digitalWrite(M_B1, HIGH);
    digitalWrite(M_B2, LOW); 
    
}

void Right(){
//    motor1.run(BACKWARD);
//    motor1.setSpeed(180);
//    motor2.run(BACKWARD);
//    motor2.setSpeed(180);
//    motor3.run(FORWARD);
//    motor3.setSpeed(180);
//    motor4.run(FORWARD);
//    motor4.setSpeed(180);
    analogWrite(S_A, 255); 
    analogWrite(S_B, 255);
    digitalWrite(M_A1, HIGH);
    digitalWrite(M_A2, LOW);
    digitalWrite(M_B1, LOW);
    digitalWrite(M_B2, HIGH);
}
   
void Stop(){
//    motor1.run(RELEASE);
//    motor1.setSpeed(0);
//    motor2.run(RELEASE);
//    motor2.setSpeed(0);
//    motor3.run(RELEASE);
//    motor3.setSpeed(0);
//    motor4.run(RELEASE);
//    motor4.setSpeed(0);
    analogWrite(S_A, 0); 
    analogWrite(S_B, 0);
    digitalWrite(M_A1, LOW);
    digitalWrite(M_A2, LOW);
    digitalWrite(M_B1, LOW);
    digitalWrite(M_B2, LOW);
}

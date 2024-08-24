#include "Arduino.h"
#include "uRTCLib.h"
#include <SoftwareSerial.h>

SoftwareSerial BTSerial(9, 8); // RX, TX
uRTCLib rtc(0x68);
int state;
int rt;
int h;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  URTCLIB_WIRE.begin();
  //rtc.set(0, 00, 20, 5, 13, 1, 22);// rtc.set(second, minute, hour, dayOfWeek, dayOfMonth, month, year)
  pinMode(11,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(11,1);
  digitalWrite(10,1);
  //Serial.println("Ready...");
  BTSerial.write("TO-SNK: snk->\n");
  BTSerial.write("TO-0/1: alon/alof\n");
  BTSerial.write("TO-TIM: rtc\n");
  delay(2000);
}

void loop() {
  rtc.refresh();
  if (BTSerial.available()) {
    String receivedString = BTSerial.readStringUntil('\n');
    receivedString.trim();
    //Serial.print("Received: ");
    //Serial.println(receivedString);
    rt = 4;//alarm set
    else if(receivedString.equals("snk")){
            rtc.set(00, 00, 20, 5, 13, 1, 22);
            BTSerial.write("snk-ok\n");
    }//snk rtc
    else if(receivedString.equals("rtc")){
      BTSerial.print(h);
      BTSerial.write("\n");
    }
     else if (receivedString.equals("alon")) {
      state = 1;
      BTSerial.write("alon-ok\n");
    }
    else if (receivedString.equals("alof")) {
      state = 0;
      BTSerial.write("alof-ok\n");
    }
    if(state==1){
      if(rtc.hour() == rt){
        //Serial.println("ALARM IS ONN");
        digitalWrite(11,0);
        digitalWrite(10,0);
      }
      else{
        digitalWrite(11,1);
        digitalWrite(10,1);
      }
    }
      else if(state==0){
        //Serial.println("ALARM OFF");
        digitalWrite(11,1);
        digitalWrite(10,1);
      }
  }
  h = rtc.hour();
}

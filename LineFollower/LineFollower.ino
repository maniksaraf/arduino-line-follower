#include "Button.h"
#include <config.h>
#include <engine.h>
#include <navigation.h>
#include <PololuQTRSensors.h>

PololuQTRSensorsRC qtr((unsigned char[]) {2,4,5,6,7,8}, 6);

void setup(){
  Serial.begin(115200);
  engineSetup();
  calibrate(&qtr);
  delay(2000);
  motor(MotorA,FORWARD_MAX);
  motor(MotorB,FORWARD_MAX);
}
void loop(){
  int pos = readLine(&qtr);
if (pos != LINE_LOST){
    if (pos == EDGE_RIGHT){
      Serial.println("right works");
      motor(MotorA,255);
      motor(MotorB,150);
    }else if (pos == EDGE_LEFT){
      Serial.println("left works");
      motor(MotorA,150);
      motor(MotorB,255);
    }else{
      Serial.println("error");
      int error = pos - MIDDLE_POS;
      int m1Speed = 255;
      int m2Speed = 255;
      if (error < 0)
 m1Speed = map(error,-MIDDLE_POS,0,255,255);
      else
 m2Speed = map(error,0,MIDDLE_POS,255,255);
      Serial.print(error);   
      Serial.print(" ");
      Serial.print(m1Speed);
      Serial.print(" ");
      Serial.println(m2Speed);
      motor(MotorA,m1Speed);
      motor(MotorB,m2Speed);
    }
}else{
  Serial.println("error happened?");
}
}


#include <SoftwareSerial.h>
#include <Servo.h>
#define BT_TX 7
#define BT_RX 6
#define LED1 10
#define LED2 9
#define LED3 8
#define TRIG 2
#define ECHO 3
#define SERVO 5
#include <LiquidCrystal.h>

LiquidCrystal lcd(A0,A1,A2,A3,A4,A5);

SoftwareSerial BTSerial(BT_TX, BT_RX);
Servo myservo;
int cl = 0;
void setup(){
  BTSerial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  lcd.begin(16,2);
  myservo.attach(5);
}

void loop(){
  if(BTSerial.available()){
    char cData = BTSerial.read();
    if('1'==cData){
      for(int i = 0 ; i<99999;i++){
      digitalWrite(TRIG, HIGH);
      delayMicroseconds(10);
      digitalWrite(TRIG, LOW);
      
      int duration = pulseIn(ECHO,HIGH);
      int distance = duration/29/2;
	  
      
      lcd.setCursor(0,0);
      lcd.print("Door : ");
      lcd.setCursor(5,1);
      
      if(distance <= 15 && distance >=0){
        
        digitalWrite(LED1,OUTPUT);
        digitalWrite(LED2,LOW);
        digitalWrite(LED3,LOW);
        cl = 90;
        lcd.print("open!");
        delay(500);
        }
      else if(distance <= 30 && distance >= 16){
        digitalWrite(LED2,OUTPUT);
        digitalWrite(LED1,LOW);
        digitalWrite(LED3,LOW);      
        cl = 0;
        lcd.print("close");
        delay(500);
        }
      else if(distance <= 45 && distance >= 31){
        digitalWrite(LED3,OUTPUT);
        digitalWrite(LED1,LOW);
        digitalWrite(LED2,LOW);
        cl = 0;
        lcd.print("close");
        delay(500);
        }myservo.write(cl);
      }
        
      }
        
    }
}

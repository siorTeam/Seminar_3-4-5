
#include <SoftwareSerial.h>  //bluetooth library

#include <Servo.h>  //Servo motor library

#include <Wire.h>  //LCD display library
#include <LiquidCrystal_I2C.h>

SoftwareSerial BTSerial(3,2);  //bluetooth instance
LiquidCrystal_I2C lcd(0x27, 16, 2); //LCD display instance
Servo myServo;  //Servo motor instance

int motorPinNum = 9;  //Servo motor pwm pin
int col = 0;
int row = 0;

void setup(){
  myServo.attach(motorPinNum);
  Serial.begin(9600);  //Serial monitor
  BTSerial.begin(9600);  
  Serial.print(" Hello \n");
  
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Hello, world!");
  delay(2000);
  lcd.clear();
}

void loop(){

  if(Serial.available()){
    if (BTSerial.available()){
      int data = BTSerial.parseInt();
      Serial.println(data);
      myServo.write(data);
      lcd.print(data, DEC);
      delay(15); 
      col += 4;
      if (col >= 16){
        if (row == 0)
            row = 1;
        else
        {    row = 0;
            lcd.clear();
        }
      }
      col = col % 16;
      lcd.setCursor(col, row);
      
    }
  }
}

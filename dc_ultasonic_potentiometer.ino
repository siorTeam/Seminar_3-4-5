#define TRIG 7 //TRIG 핀 설정 (초음파 보내는 핀)
#define ECHO 6 //ECHO 핀 설정 (초음파 받는 핀)

int ENA = 10;
int INA1 = 9;
int INA2 = 8;
int pot = A0;

void setup()
{
  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
  pinMode(ENA, OUTPUT);
  pinMode(INA1, OUTPUT);
  pinMode(INA2, OUTPUT);
  pinMode(pot, INPUT);
  
  digitalWrite(ENA, LOW);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);

  Serial.println("DC motor test");

  Serial.println("Forward ");
  digitalWrite(ENA, HIGH);
  digitalWrite(INA1, HIGH);
  digitalWrite(INA2, LOW);
  delay(1000);
  
  Serial.println("Backward");
  digitalWrite(ENA, HIGH);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, HIGH);
  delay(1000);
  
  Serial.println("stop");
  digitalWrite(ENA, LOW);
  digitalWrite(INA1, LOW);
  digitalWrite(INA2, LOW);
  delay(2000);
}

void loop()
{
  long duration, distance;
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);

  duration = pulseIn (ECHO, HIGH); 

  distance = duration * 17 / 1000; //초음파의 반사 시간을 거리로 환산
  Serial.print("\nDistance : ");
  Serial.print(distance); //측정된 물체로부터 거리값(cm값)을 보여줍니다.
  Serial.println(" cm");
  if (distance<= 10){//거리가 10이하라면
    Serial.println("stop");
    digitalWrite(ENA, LOW);
    digitalWrite(INA1, LOW);
    digitalWrite(INA2, LOW);
    delay(1000);
  }
  else{
    Serial.println("Forward-PWM");
    int resistance = analogRead(pot);
    int motor = map(resistance, 0, 1023, 0, 255);
    analogWrite(ENA, motor);
    digitalWrite(INA1, HIGH);
    digitalWrite(INA2, LOW);
    delay(500);
  }
}

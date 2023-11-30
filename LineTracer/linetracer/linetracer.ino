int AIN1 = 4;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           //kanan
int AIN2 = 2;
int BIN1 = 7; //kiri
int BIN2 = 8;
int STBY = 9;
int PWMA = 3; //kanan
int PWMB = 5; //kiri
float skiri = 163;
float skanan = 150;
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2);

int num_sensor = 5;
int sensorvalue[num_sensor]={A0,A1,A2,A3,A6};
int baca[num_sensor];

void setup(){
  Serial.begin(9600);
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);
  pinMode(BIN1,OUTPUT);
  pinMode(BIN2,OUTPUT);
  pinMode(STBY,OUTPUT);
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  lcd.init();
  for(int i=0;i<num_sensor;i++){
    pinMode(sensorvalue[i],OUTPUT);
  }
}

void loop(){
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    int distance1 = data.substring(0, data.indexOf(',')).toInt();
    int distance2 = data.substring(data.indexOf(',') + 1, data.lastIndexOf(',')).toInt();
    int distance3 = data.substring(data.lastIndexOf(',') + 1).toInt();

    lcd.setCursor(0,0);
    lcd.print(distance1);
    lcd.setCursor(0,4);
    lcd.print(distance2);
    lcd.setCursor(0,8);
    lcd.print(distance3);
    // Check the conditions and control the motor
    if (distance1 >= 20) {
      maju();
    } else if(distance2<=5 && distance1<=5) {
      kanan();
    }else if(distance3<=5 && distance1<=5) {
      kiri();
    }else if(distance1<=5){
      stopp();
    }
  } 
}

void bacasensor(){
  for(int i=0;i<num_sensor;i++){
    baca[num_sensor]=digitalRead(sensorvalue[i]);
  }

  for(int i=0;i<num_sensor;i++){
    Serial.print(baca[i]);
  }
  Serial.println(" ");
}

void maju(){
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  digitalWrite(STBY,HIGH);
  analogWrite(PWMA,skanan);
  analogWrite(PWMB,skiri);
}

void mundur(){
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  analogWrite(PWMA,skanan);
  analogWrite(PWMB,skiri);
}

void kanan(){
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,HIGH);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,HIGH);
  digitalWrite(STBY,HIGH);
  analogWrite(PWMA,skanan);
  analogWrite(PWMB,skiri);
}

void kiri(){
  digitalWrite(AIN1,HIGH);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,HIGH);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,HIGH);
  analogWrite(PWMA,skanan);
  analogWrite(PWMB,skiri);
}

void stopp(){
  digitalWrite(AIN1,LOW);
  digitalWrite(AIN2,LOW);
  digitalWrite(BIN1,LOW);
  digitalWrite(BIN2,LOW);
  digitalWrite(STBY,LOW);
  analogWrite(PWMA,0);
  analogWrite(PWMB,0);
}

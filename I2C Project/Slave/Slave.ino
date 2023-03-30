//slave code(LED만 키는 놈 인줄 알았는데 adc까지 보내야 하는 놈)

#include <Wire.h>

#define Slave 0x04

#define LED1 12
#define LED2 11
#define LED3 10
#define LED4 9
#define LED5 8
#define LED6 7
#define LED7 6
#define LED8 5

byte rec[256]={0,};
int button_data[8]={0,};
int ADC_data=0;
int adc1;
int adc2;
void setup() {
  // put your setup code here, to run once:
  Wire.begin(Slave);
  Serial.begin(115200);
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(LED8,OUTPUT);
}

void record(int receiveNum){
  for(int i=0; i<receiveNum; i++){
    rec[i] = Wire.read();
    }
  }

void button_data_index(int data){
  for(int i=0; i<8; i++){
    button_data[i]=(int)((data>>i)&0x01);
    }
  }

void sendToMaster(){
  for(int i=0; i<1; i++) Wire.write(rec[0]);
  Wire.write(adc1);
  Wire.write(adc2);
  }
  
void read_data_I2C(){
  Wire.onReceive(record);
  //Serial.println(rec[0]);
  Wire.onRequest(sendToMaster);
  }

void LED(void){
     if(button_data[0]==1) digitalWrite(LED1,HIGH);
     else digitalWrite(LED1,LOW);
     if(button_data[1]==1) digitalWrite(LED2,HIGH);
     else digitalWrite(LED2,LOW);
     if(button_data[2]==1) digitalWrite(LED3,HIGH);
     else digitalWrite(LED3,LOW);
     if(button_data[3]==1) digitalWrite(LED4,HIGH);
     else digitalWrite(LED4,LOW);
     if(button_data[4]==1) digitalWrite(LED5,HIGH);
     else digitalWrite(LED5,LOW);
     if(button_data[5]==1) digitalWrite(LED6,HIGH);
     else digitalWrite(LED6,LOW);
     if(button_data[6]==1) digitalWrite(LED7,HIGH);
     else digitalWrite(LED7,LOW);
     if(button_data[7]==1) digitalWrite(LED8,HIGH);
     else digitalWrite(LED8,LOW);
  }



void loop() {
  // put your main code here, to run repeatedly:
  ADC_data=analogRead(A0);
  adc1=ADC_data/100;
  adc2=ADC_data%100;
  Serial.println(ADC_data);
  read_data_I2C();
  button_data_index(rec[0]);
  LED();
}

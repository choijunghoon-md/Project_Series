//master code(데이터 처리)
#include <MsTimer2.h>
#include <Wire.h>
typedef unsigned char BYTE_t;
#define Slave   0x04 //서버 주소

#define button1 9
#define button2 8
#define button3 7
#define button4 6
#define button5 5
#define button6 4
#define button7 3
#define button8 2
int button_data[8]={0,};
BYTE_t return_data[11]={0,};
int processing_data[8]={0,};
int chang_data[8]={0,};
int flag=0;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); //서버용 I2C통신 라이브러이 초기화
  Serial.begin(115200);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
  pinMode(button6,INPUT);
  pinMode(button7,INPUT);
  pinMode(button8,INPUT);
  MsTimer2::set(20, all);
  MsTimer2::start();
}

void send_data_I2C(int data){//I2C 데이터를 서버로 보내는 함수 
  Wire.beginTransmission(Slave);
  Wire.write(data);
  Wire.endTransmission();
  }

void button_data_index(){
  if(digitalRead(button1)==HIGH) button_data[0]=0;
  else button_data[0]=1;
  if(digitalRead(button2)==HIGH) button_data[1]=0;
  else button_data[1]=1;
  if(digitalRead(button3)==HIGH) button_data[2]=0;
  else button_data[2]=1;
  if(digitalRead(button4)==HIGH) button_data[3]=0;
  else button_data[3]=1;
  if(digitalRead(button5)==HIGH) button_data[4]=0;
  else button_data[4]=1;
  if(digitalRead(button6)==HIGH) button_data[5]=0;
  else button_data[5]=1;
  if(digitalRead(button7)==HIGH) button_data[6]=0;
  else button_data[6]=1;
  if(digitalRead(button8)==HIGH) button_data[7]=0;
  else button_data[7]=1;
  }


int button_data_bite(){
  int data=0;
  for(int i=0; i<8; i++){
    data += (chang_data[i]<<i);
    }
  return data;
 }

void read_processing(){
  char processing=0;
  processing=Serial.read();
  for(int i=0; i<8; i++){
    processing_data[i]=(int)((processing>>i)&0x01);
    }
  }

void chang_button_data(){
  for(int i=0; i<8; i++){
    if(processing_data[i]==1 && button_data[i]==1)chang_data[i]=1;
    else chang_data[i]=0;
    }
  }


void all(){
  if(Serial.available()){
    read_processing();
  }
  button_data_index();
  chang_button_data();
  processing_send();
  if(flag==0)flag=1;
  else flag=0;
  }




void loop() {

  if(flag==0){//타이머로 200msec마다 데이터를 전송하는 함수
    send_data_I2C(button_data_bite());
    }
  if(flag==1){
    i2c_communication();
    }

}

void i2c_communication() {
  Wire.requestFrom(Slave, 3);
  int data_a[3]={0,};
  for(int i=0; i<3; i++){
    data_a[i] = Wire.read();
  }
  return_data[8]=data_a[1]/10;
  return_data[9]=data_a[1]%10;
  return_data[10]=data_a[2];
  for(int i=0; i<8; i++){
    return_data[i]=(int)((data_a[0]>>i)&0x01);
    }
}
void processing_send(){
  for(int i=0; i<11; i++){
    Serial.write(return_data[i]);
    }
  Serial.println('\n');
}

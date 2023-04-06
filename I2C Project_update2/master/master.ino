//master code(데이터 처리)
#include <MsTimer2.h>
#include <Wire.h>
#include <avr/wdt.h>
typedef unsigned char BYTE_t;
#define Slave   0x07 //서버 주소

#define button1 9
#define button2 8
#define button3 7
#define button4 6
#define button5 5
#define button6 4
#define button7 3
#define button8 2
#define WDO 22
#define WDI 11
#define RING_BUFFER_SIZE 9
#define TEMP_BUFFER_SIZE 9

static char ring_buff[RING_BUFFER_SIZE]={0,};
static int data = 0;
int button_data[8]={0,};
BYTE_t return_data[11]={0,};
int processing_data[8]={0,};
int chang_data[8]={0,};
int flag=0;
byte data_a[3]={0,};
int a=HIGH;
int checking=0;
int changing[11]={0,};
int checking_OUT=LOW;
int checking2=0;
BYTE_t sending_crc_check[7]={0,};

union
{
  unsigned short check_sum;
  unsigned char b[2];
} crc_16_val;

int CRC16_MODBUS(const uint8_t *nData, uint16_t wLength)
{

  static const uint16_t wCRCTable[] = { 0X0000, 0XC0C1, 0XC181, 0X0140, 0XC301, 0X03C0, 0X0280, 0XC241, 0XC601, 0X06C0, 0X0780,
    0XC741, 0X0500, 0XC5C1, 0XC481, 0X0440, 0XCC01, 0X0CC0, 0X0D80, 0XCD41, 0X0F00, 0XCFC1,
    0XCE81, 0X0E40, 0X0A00, 0XCAC1, 0XCB81, 0X0B40, 0XC901, 0X09C0, 0X0880, 0XC841, 0XD801,
    0X18C0, 0X1980, 0XD941, 0X1B00, 0XDBC1, 0XDA81, 0X1A40, 0X1E00, 0XDEC1, 0XDF81, 0X1F40,
    0XDD01, 0X1DC0, 0X1C80, 0XDC41, 0X1400, 0XD4C1, 0XD581, 0X1540, 0XD701, 0X17C0, 0X1680,
    0XD641, 0XD201, 0X12C0, 0X1380, 0XD341, 0X1100, 0XD1C1, 0XD081, 0X1040, 0XF001, 0X30C0,
    0X3180, 0XF141, 0X3300, 0XF3C1, 0XF281, 0X3240, 0X3600, 0XF6C1, 0XF781, 0X3740, 0XF501,
    0X35C0, 0X3480, 0XF441, 0X3C00, 0XFCC1, 0XFD81, 0X3D40, 0XFF01, 0X3FC0, 0X3E80, 0XFE41,
    0XFA01, 0X3AC0, 0X3B80, 0XFB41, 0X3900, 0XF9C1, 0XF881, 0X3840, 0X2800, 0XE8C1, 0XE981,
    0X2940, 0XEB01, 0X2BC0, 0X2A80, 0XEA41, 0XEE01, 0X2EC0, 0X2F80, 0XEF41, 0X2D00, 0XEDC1,
    0XEC81, 0X2C40, 0XE401, 0X24C0, 0X2580, 0XE541, 0X2700, 0XE7C1, 0XE681, 0X2640, 0X2200,
    0XE2C1, 0XE381, 0X2340, 0XE101, 0X21C0, 0X2080, 0XE041, 0XA001, 0X60C0, 0X6180, 0XA141,
    0X6300, 0XA3C1, 0XA281, 0X6240, 0X6600, 0XA6C1, 0XA781, 0X6740, 0XA501, 0X65C0, 0X6480,
    0XA441, 0X6C00, 0XACC1, 0XAD81, 0X6D40, 0XAF01, 0X6FC0, 0X6E80, 0XAE41, 0XAA01, 0X6AC0,
    0X6B80, 0XAB41, 0X6900, 0XA9C1, 0XA881, 0X6840, 0X7800, 0XB8C1, 0XB981, 0X7940, 0XBB01,
    0X7BC0, 0X7A80, 0XBA41, 0XBE01, 0X7EC0, 0X7F80, 0XBF41, 0X7D00, 0XBDC1, 0XBC81, 0X7C40,
    0XB401, 0X74C0, 0X7580, 0XB541, 0X7700, 0XB7C1, 0XB681, 0X7640, 0X7200, 0XB2C1, 0XB381,
    0X7340, 0XB101, 0X71C0, 0X7080, 0XB041, 0X5000, 0X90C1, 0X9181, 0X5140, 0X9301, 0X53C0,
    0X5280, 0X9241, 0X9601, 0X56C0, 0X5780, 0X9741, 0X5500, 0X95C1, 0X9481, 0X5440, 0X9C01,
    0X5CC0, 0X5D80, 0X9D41, 0X5F00, 0X9FC1, 0X9E81, 0X5E40, 0X5A00, 0X9AC1, 0X9B81, 0X5B40,
    0X9901, 0X59C0, 0X5880, 0X9841, 0X8801, 0X48C0, 0X4980, 0X8941, 0X4B00, 0X8BC1, 0X8A81,
    0X4A40, 0X4E00, 0X8EC1, 0X8F81, 0X4F40, 0X8D01, 0X4DC0, 0X4C80, 0X8C41, 0X4400, 0X84C1,
    0X8581, 0X4540, 0X8701, 0X47C0, 0X4680, 0X8641, 0X8201, 0X42C0, 0X4380, 0X8341, 0X4100,
    0X81C1, 0X8081, 0X4040 };

  uint8_t nTemp;
  uint16_t wCRCWord = 0xFFFF;

  while (wLength--)
  {
    nTemp = *nData++ ^ wCRCWord;
    wCRCWord >>= 8;
    wCRCWord ^= wCRCTable[nTemp];
  }

  return wCRCWord;
}

void setup() {
  // put your setup code here, to run once:
  Wire.begin(); //서버용 I2C통신 라이브러이 초기화
  Serial.begin(115200);
  wdt_disable();
  wdt_enable(WDTO_15MS);
  pinMode(button1,INPUT);
  pinMode(button2,INPUT);
  pinMode(button3,INPUT);
  pinMode(button4,INPUT);
  pinMode(button5,INPUT);
  pinMode(button6,INPUT);
  pinMode(button7,INPUT);
  pinMode(button8,INPUT);
  pinMode(24,OUTPUT);
  pinMode(WDO,OUTPUT);
  pinMode(WDI,INPUT);
  MsTimer2::set(14, all);
  MsTimer2::start();
  //Serial.println("start");
}

void send_data_I2C(int data){//I2C 데이터를 서버로 보내는 함수
  sending_crc_check[0]=174;
  sending_crc_check[1]=184;
  sending_crc_check[2]='I';
  sending_crc_check[3]=1;
  sending_crc_check[4]=data;
  crc_16_val.check_sum = CRC16_MODBUS(sending_crc_check, 5);
  sending_crc_check[5]=crc_16_val.b[0];
  sending_crc_check[6]=crc_16_val.b[1];
  
  Wire.beginTransmission(Slave);
  for(int i=0; i<7; i++){
    Wire.write(sending_crc_check[i]);
  }
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
  //pinMode(WDO,OUTPUT);
  digitalWrite(WDO,checking_OUT);
  /*if(a==HIGH){a=LOW;}
  else a=HIGH;*/
  if(Serial.available()){
    read_processing();
  }
  button_data_index();
  chang_button_data();
  processing_send();
  if(flag==3)flag=1;
  else flag=0;
  }


void loop() {
  if(flag==0){//타이머로 200msec마다 데이터를 전송하는 함수
    send_data_I2C(button_data_bite());
    flag=3;
    checking_OUT = !checking_OUT;
    }
  if(flag==1){
    checking_OUT = !checking_OUT;
    Ring_buff();
    extractData();
    if(checking==1){
      i2c_communication();
    }
    flag=4;
    }
  if(digitalRead(WDI)==LOW){
    wdt_reset();
    }
    //digitalWrite(WDO,checking_OUT);
}

void i2c_communication() {
  return_data[8]=data_a[5]/10;
  return_data[9]=data_a[5]%10;
  return_data[10]=data_a[6];
  for(int i=0; i<8; i++){
    return_data[i]=(int)((data_a[4]>>i)&0x01);
    }
}
void processing_send(){
    for(int i=0; i<11; i++){
     Serial.write(return_data[i]);
     }
    Serial.println('\n');
}

 void Ring_buff(){
    Wire.requestFrom(Slave, 9);
    char read_temp[TEMP_BUFFER_SIZE];
    byte leng = Wire.readBytes(read_temp,TEMP_BUFFER_SIZE);
    digitalWrite(24,HIGH);
    //delay(2);
    for(int i=0; i<RING_BUFFER_SIZE; i++){
     ring_buff[i]=0;
     }
    for(int i=0; i<leng; i++){
      ring_buff[data] = read_temp[i];
      data++;
      if(data>=RING_BUFFER_SIZE){
        data = 0;
       }
    }
 }

 void extractData() {
  data_a[0] = ring_buff[(data + RING_BUFFER_SIZE - 9) % RING_BUFFER_SIZE];
  data_a[1]=  ring_buff[(data + RING_BUFFER_SIZE - 8) % RING_BUFFER_SIZE];
  data_a[2] = ring_buff[(data + RING_BUFFER_SIZE - 7) % RING_BUFFER_SIZE];
  data_a[3] = ring_buff[(data + RING_BUFFER_SIZE - 6) % RING_BUFFER_SIZE];
  data_a[4]=  ring_buff[(data + RING_BUFFER_SIZE - 5) % RING_BUFFER_SIZE];
  data_a[5] = ring_buff[(data + RING_BUFFER_SIZE - 4) % RING_BUFFER_SIZE];
  data_a[6] = ring_buff[(data + RING_BUFFER_SIZE - 3) % RING_BUFFER_SIZE];
  data_a[7]=  ring_buff[(data + RING_BUFFER_SIZE - 2) % RING_BUFFER_SIZE];
  data_a[8] = ring_buff[(data + RING_BUFFER_SIZE - 1) % RING_BUFFER_SIZE];
  if(data_a[0]==174 && data_a[1]==184 && data_a[2]=='P' && data_a[3]==3){
    crc_16_val.check_sum = CRC16_MODBUS(data_a, 7);
    if(crc_16_val.b[0]==data_a[7] && crc_16_val.b[1]==data_a[8]){
       checking=1;
      }
    else checking=0;
    }
   else checking=0;
}

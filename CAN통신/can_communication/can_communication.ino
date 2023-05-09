// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>
#include <MsTimer2.h>

long unsigned int receive_Id;
unsigned char send_stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};
unsigned char receive_len = 0;
unsigned char receive_stmp[8];

int flag = HIGH;

MCP_CAN CAN0(10);                                      // Set CS to pin 10

void setup()
{
  Serial.begin(115200);
  if(CAN0.begin(CAN_500KBPS,MCP_8MHz) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
  MsTimer2::set(500,Can);
  MsTimer2::start();
}

void loop()
{
  
}
void Can(){
  flag = !flag;
  if(flag==HIGH){
    receive_can();
    }
  else{
    Send_can();
    }
  }

void Send_can(){
  CAN0.sendMsgBuf(0x00, 0, 8, send_stmp);
  }

void receive_can(){
  CAN0.readMsgBuf(&receive_len, receive_stmp);
  receive_Id = CAN0.getCanId();
  Serial.print("ID: ");
  Serial.print(receive_Id, HEX);
  for(int i = 0; i<receive_len; i++){                // Print each byte of the data
      Serial.print(receive_stmp[i], HEX);
      Serial.print(" ");
     }
     Serial.println();
   }

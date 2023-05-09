#include <mcp_can.h>
#include <SPI.h>
#include <MsTimer2.h>

long unsigned int receive_Id;
unsigned char receive_len = 0;
unsigned char receive_stmp[8];

MCP_CAN CAN0(10);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  if(CAN0.begin(CAN_500KBPS,MCP_8MHz) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
  MsTimer2::set(1000,receive_can);
  MsTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:

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

// demo: CAN-BUS Shield, send data
#include <mcp_can.h>
#include <SPI.h>
#include <MsTimer2.h>

unsigned char send_stmp[8] = {0, 1, 2, 3, 4, 5, 6, 7};


MCP_CAN CAN0(10);                                      // Set CS to pin 10

void setup()
{
  Serial.begin(115200);
  if(CAN0.begin(CAN_500KBPS,MCP_8MHz) == CAN_OK) Serial.print("can init ok!!\r\n");
  else Serial.print("Can init fail!!\r\n");
  MsTimer2::set(1000,Send_can);
  MsTimer2::start();
}

void loop()
{
  
}

void Send_can(){
  CAN0.sendMsgBuf(0x00, 0, 8, send_stmp);
  }

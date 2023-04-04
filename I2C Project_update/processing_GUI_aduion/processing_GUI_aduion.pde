import processing.serial.*;
int[] indata_a = {0,0,0,0,0,0,0,0};
int[] outdata = {0,0,0,0,0,0,0,0};
int inData=0;
Serial port;  // Create object from Serial class
int val;        // Data received from the serial port
int processing_button_data=0;
int adc_data=0;
int b1=0;
int b3=0;
int b2=0;
char aaa=0;

void setup() 
{
  size(1400,800);
  smooth();
  String portName ;
  println(Serial.list());
  port = new Serial(this,"COM11",115200); 
  port.bufferUntil('\n');
}


void serialEvent(Serial port)
{
 byte[] in_buff = port.readBytesUntil('\n');  // 프로세싱을 사용하려 경우 TC275의 송신 프로토콜에 마지막에 '\n'을 반드시 추가해서 넣을 것
 int byte_length = 0;
 int[] input_io_data = new int[8];
 int i;
 
 if(in_buff != null)
  {
    byte_length = in_buff.length;
    print("Data length :  ");
    println(byte_length);
    
      for(i=0;i<byte_length;i++)
      {
          print( (in_buff[i]+256)%256);  // byte의 범위가 -127+256이므로
          print("   ");
      }
   // println(hex(in_buff[0]));
   // println(in_buff[0]+256);
   // println(in_buff[1]+256);  
     println();
     if(byte_length > 9){
       for(i=0; i<8; i++){
           outdata[i] =in_buff[i];
       }
       b3=in_buff[8];
       b1=in_buff[9];
       b2=in_buff[10];
    }
  }
}


  
 /*
void serialEvent(Serial port)
{
 byte[] in_buff = port.readBytesUntil('\n');  // 프로세싱을 사용하려 경우 TC275의 송신 프로토콜에 마지막에 '\n'을 반드시 추가해서 넣을 것
 int byte_length = 0;
 int[] input_io_data = new int[8];
 int i;
 
 if(in_buff != null)
  {
    byte_length = in_buff.length;
    print("Data length :  ");
    println(byte_length);
    
      for(i=0;i<12;i++)
      {
          print( (in_buff[i]+256)%256);  // byte의 범위가 -127+256이므로
          print("   ");
      }
     println();
     
     for(i=0; i<8; i++){
       input_io_data[i]=in_buff[i];
     }
     b1=in_buff[8];
    }
    
   for(i=0; i<8; i++){
      if(input_io_data[i]==1 && indata_a[i]==1){
        outdata[i]=1;
      }
      else{
        outdata[i]=0;
      }
    }
    
}
*/

void draw() {
  int i=0;
  background(50);
  fill(0,26,51);
  rect(50,210,100,500);
  //fill(255,26,51);
  rect(350,210,100,500);
   
  for( i=0; i<8; i++){
   noStroke(); 
   fill(80,188,223);
   ellipse(90,250+60*i,40,40);
   ellipse(110,250+60*i,40,40);
   rect(90,230+60*i,20,40);
   strokeWeight(10);
   
   if(indata_a[i]==0){
      fill(255);
      ellipse(90,250+60*i,40,40);
    } else{
      fill(255);
      ellipse(110,250+60*i,40,40);
    }
   
   if(indata_a[i]==0){
      if((mouseX-90)*(mouseX-90)+(mouseY-250-60*i)*(mouseY-250-60*i)<=400){
        if(mousePressed){
          indata_a[i]=1;
          delay(150);
        }
      }
    } else{
      if((mouseX-110)*(mouseX-110)+(mouseY-250-60*i)*(mouseY-250-60*i)<=400){
        if(mousePressed){
          indata_a[i]=0;
          delay(150);
        }
      }
    }
    
    
   /*if(indata_a[i]==0){
      outdata[i]=0;
    } else {
      outdata[i]=1;
    }*/
    
    
   if(outdata[i]==0){
        fill(255);
      } else{
        fill(80,188,223);
      }
      ellipse(400,250+60*i,40,40);
    }
    
    
    processing_button_data=0;
   
    for(i=0; i<8; i++){
      processing_button_data += (indata_a[i]<<i);
    }
    aaa=(char)processing_button_data;
    port.write(aaa);
   // delay(100);
    fill(255);
    textSize(50);
    if(b1<0)b1=10;
    if((b1*100+b2+b3*1000)>1023){adc_data=1023;}
    else if((b1*100+b2+b3*1000)<0){adc_data=0;}
    else{adc_data=b1*100+b2+b3*1000;}
    //text(b1,100,600);
    text(adc_data,1000,700);
    text("ADC_Data",1000,650);
    text("button1",170,270);
    text("button2",170,270+60);
    text("button3",170,270+60*2);
    text("button4",170,270+60*3);
    text("button5",170,270+60*4);
    text("button6",170,270+60*5);
    text("button7",170,270+60*6);
    text("button8",170,270+60*7);
    fill(0,26,51);
    rect(1070-200,600+110,80,-500);
    fill(80,188,223);
    rect(1080-200,590+110,60,(-adc_data/10)*4);
    fill(255);
    rect(1080-200,110+110,60,490-(adc_data/10)*4);
     text("LED1",470,270);
    text("LED2",470,270+60);
    text("LED3",470,270+60*2);
    text("LED4",470,270+60*3);
    text("LED5",470,270+60*4);
    text("LED6",470,270+60*5);
    text("LED7",470,270+60*6);
    text("LED8",470,270+60*7);
    text("INPUT Data",50,170);
    text("OUTPUT Data",350,170);
}

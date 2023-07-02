import processing.serial.*;
Serial port;  // Create object from Serial class
int val;        // Data received from the serial port

int speed=3200;
int pulse=3200;
int return_pulse=-pulse;
int S_V=625;
int P_V=625;
int old_pulse=0;
int time=505;
int a=0;

void setup() 
{
  size(1400,700);
  smooth();
  String portName ;
  println(Serial.list());
  port = new Serial(this,"COM18",115200); 
  port.bufferUntil('\n');
}

void draw() {
  background(100);
  fill(0,26,51);
  rect(20,100,150,120);
  rect(220,100,150,120);
  rect(1050,500,120,120);
  rect(1200,500,140,120);
  rect(1075,300,220,120);
  rect(20,300,270,100);
  rect(20,500,270,100);
  fill(255);
  rect(1060,510,100,100);
  rect(1210,510,120,100);
  rect(1085,310,200,100);
  rect(30,110,130,100);
  rect(230,110,130,100);
  rect(30,310,250,80);
  rect(30,510,250,80);
  textSize(40);
  fill(0);
  rect(500,140,700,30);
  rect(300,340,700,30);
  rect(300,540,700,30);
  text(speed+" r/min",75,365);
  text(pulse+" number",40,565);
  text("Emergenct\n       Stop",1090,340);
  text("Start",1069,570);
  text("Return",1215,570);
  textSize(20);
  text("Velocity\n Control \n   Mode",60,135);
  text("Position\n Control \n   Mode",260,135);
  textSize(30);
  fill(255);
   if((mouseX)>=505 && (mouseX)<=1145 && (mouseY)>=140 && (mouseY)<=170 && (mousePressed)){
    time=mouseX;
    a=time;
    port.write(8);
    delay(10);
    port.write(0);
    delay(10);
    port.write(time/1000);
    delay(10);
    port.write((time/100-(time/1000)*10));
    delay(10);
    port.write((time/10-(time/100)*10));
    delay(10);
    port.write(time%10);
    delay(10);
    port.write(0);
    delay(10);
    port.write(0);
    delay(10);
  }
  rect(time,145,50,20);
  text(time-505 + "ms",time,120);
  text("    acceleration time\nand deceleration time",time-95,40);
  if((mouseX)>=305 && (mouseX)<=945 && (mouseY)>=340 && (mouseY)<=370 && (mousePressed)){
    S_V=mouseX;
    if(speed>=0){
      a=speed;
      port.write(5);
      delay(10);
      port.write(0);
      delay(10);
      port.write(speed/1000);
      delay(10);
      port.write((speed/100-(speed/1000)*10));
      delay(10);
      port.write((speed/10-(speed/100)*10));
      delay(10);
      port.write(a%10);
      delay(10);
      port.write(0);
      delay(10);
      port.write(0);
      delay(10);
    }
    else{
      a=-speed;
      port.write(6);
      delay(10);
      port.write(0);delay(10);
      port.write(-(speed/1000));delay(10);
      port.write(-((speed/100-(speed/1000)*10)));delay(10);
      port.write(-((speed/10-(speed/100)*10)));delay(10);
      port.write(-speed%10);delay(10);
      port.write(0);delay(10);
      port.write(0);delay(10);
    }
  }
  if((S_V-625)>300){
    S_V=925;
  }
  else if((S_V-625)<-300){
    S_V=325;
  }
  speed=(S_V-625);
  rect(S_V,345,50,20);
  if((mouseX)>=305 && (mouseX)<=945 && (mouseY)>=540 && (mouseY)<=570 && (mousePressed)){
    P_V=mouseX;
    if(pulse>=0){
      a=pulse;
      port.write(2)
      ;delay(10);
      port.write(2);
      delay(10);
      port.write(a/1000)
      ;delay(10);
      port.write((a/100-(a/1000)*10));
      delay(10);
      port.write((a/10-(a/100)*10));
      delay(10);
      port.write(a%10);
      delay(10);
      port.write(0);
      delay(10);
      port.write(0);
      delay(10);
    }
    else{
      a=-pulse;
      port.write(7);
      delay(10);
      port.write(7);
      delay(10);
      port.write(a/1000);
      delay(10);
      port.write((a/100-(a/1000)*10))
      ;delay(10);
      port.write((a/10-(a/100)*10));
      delay(10);
      port.write(a%10);
      delay(10);
      port.write(0);
      delay(10);
      port.write(0);
      delay(10);
    }
  }
  pulse=(P_V-625)*10;
  rect(P_V,545,50,20);
  fill(255);
  text("SPEED",S_V-15,320);
  text("SPEED",130,290);
  text("Encoder Value",P_V,520);
  text("Encoder Value",90,490);
  if((mouseX)>20 && (mouseX)<170 && (mouseY)>100 && (mouseY)<220 && (mousePressed)){
    port.write(3);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    }
if((mouseX)>220 && (mouseX)<370 && (mouseY)>100 && (mouseY)<220 && (mousePressed)){
    port.write(1);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    }
if((mouseX)>1075 && (mouseX)<1295 && (mouseY)>300 && (mouseY)<420 && (mousePressed)){
    port.write(5);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    }
if((mouseX)>1050 && (mouseX)<1170 && (mouseY)>500 && (mouseY)<620 && (mousePressed)){
    port.write(4);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    port.write(0);delay(10);
    old_pulse=pulse;
    }
 if((mouseX)>1200 && (mouseX)<1340 && (mouseY)>500 && (mouseY)<620 && (mousePressed)){
    if(old_pulse>=0){
      a=old_pulse;
      port.write(7);delay(10);
      port.write(0);delay(10);
      port.write(a/1000);delay(10);
      port.write((a/100-(a/1000)*10));delay(10);
      port.write((a/10-(a/100)*10));delay(10);
      port.write(a%10);delay(10);
      port.write(0);delay(10);
      port.write(0);delay(10);
    }
    else{
      a=-old_pulse;
      port.write(2);delay(10);
      port.write(0);delay(10);
      port.write(a/1000);delay(10);
      port.write((a/100-(a/1000)*10));delay(10);
      port.write((a/10-(a/100)*10));delay(10);
      port.write(a%10);delay(10);
      port.write(0);delay(10);
      port.write(0);delay(10);
    }
  }
}

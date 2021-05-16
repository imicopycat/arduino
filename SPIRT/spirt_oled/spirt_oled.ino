#include <SSD1306.h>
#define MQ2pin (0)


SSD1306 screen(0x3c, 5, 4);
int bar_pos,delaytime;
float sensorValue;

void drawProgressBar() {

  // for debug
  // Serial.print(">> ");
  // Serial.println(bar_pos);
   
  // progress bar function
  /*
   * drawProgressBar(x, y, width, height, value);
    parametros (p):
      p1: x       --> X
      p2: y       --> Y
      p3: width   --> width
      p4: height  --> height
      p5: value   --> position
     
  */
  screen.drawProgressBar(10, 32, 100, 10, bar_pos);
 
  // text under progress bar center align
  screen.setTextAlignment(TEXT_ALIGN_CENTER);
   
  // text percent of progress bar
  /*
   * drawString(x,y,text);
    parametros (p):
     p1: x      --> X
     p2: y      --> Y
     p3: string --> text
  */
  screen.drawString(64, 15, String(bar_pos) + "%");
 
  //0 minimum
  if(bar_pos == 0){
    screen.drawString(64, 45, "Minimal value");
  }
  // 100 maximum
  else if(bar_pos == 100){
    screen.drawString(64, 45, "Maximum value");
  }
  delay(delaytime);
}

void setup() {
  // init device
screen.init();
screen.flipScreenVertically();
screen.setFont(ArialMT_Plain_10);

pinMode(MQ2pin,INPUT);

//warm up spirt ensor

  delaytime = 200;

    for (int i=0 ; i<101; i++)
      {
        bar_pos = i;
        screen.clear();
        drawProgressBar();
        screen.drawString(64, 45, "WARM UP SENSOR !!!");
        screen.display();
      }
 delay(1000);
 screen.clear();
 screen.drawString(64, 25, "READY :)");
 screen.display();
 delay(1000);
 screen.clear();
 screen.drawString(64, 25, "START FLOW");
 screen.display();
 screen.clear();
 Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  delaytime = 20;
  sensorValue = analogRead(MQ2pin);
  Serial.println(sensorValue);

  bar_pos = map(sensorValue, 0, 4095, 0, 100);
  screen.clear();
  drawProgressBar();
  screen.drawString(64, 45, String(sensorValue)+"promile.");
  screen.display();
  //delay(10);
}

#include <SPI.h>
#include <DMD2.h>
#include <fonts/Arial_Black_16_big.h>

#define secButtonPin 5
#define minButtonPin 4
#define hourButtonPin 3
#define stButtonPin 2

int h = 0;
int m = 0;
int s = 0;

unsigned long actualTime;
unsigned long lastTimeIncrement = 0;
unsigned long lastTimeButtons = 0;
unsigned long timeDiffIncrement;
unsigned long timeDiffButton;

SoftDMD dmd(2,1);  
void setup() {
  pinMode(secButtonPin, INPUT);
  pinMode(minButtonPin, INPUT);
  pinMode(hourButtonPin, INPUT);
  pinMode(stButtonPin, INPUT);
  digitalWrite(secButtonPin, HIGH);
  digitalWrite(minButtonPin, HIGH);
  digitalWrite(hourButtonPin, HIGH);
  digitalWrite(stButtonPin, HIGH);

  Serial.begin(9600);

  Serial.println(analogRead(3)/4);
  dmd.setBrightness(analogRead(3)/4);
  dmd.selectFont(digit_16);
  dmd.begin();
  draw();
}

void loop() {

  actualTime = millis();
  timeDiffIncrement = actualTime - lastTimeIncrement;
  timeDiffButton = actualTime - lastTimeButtons;

  if (timeDiffButton >= 100UL){
      checkButtons();
        Serial.println(analogRead(3)/4);
  dmd.setBrightness(analogRead(3)/4);
      lastTimeButtons = actualTime;
  }

  if (timeDiffIncrement >= 1000UL) {
    Serial.println(timeDiffIncrement);
    lastTimeIncrement = actualTime;
    if(digitalRead(stButtonPin) == HIGH){
      timeIncrement();
      draw();
    }
  }
}


void draw(){
 dmd.drawString(53,0,String(s%10));
 dmd.drawString(42,0,String(s/10));
 dmd.drawString(38,0,String(":"));
 
 dmd.drawString(27,0,String(m%10));
 dmd.drawString(16,0,String(m/10));
 dmd.drawString(12,0,String(":"));

 dmd.drawString(1,0,String(h)); 
}

void timeIncrement(){
  s++;
  if(s>= 60){
    s=0;
    m++;
  }
  if(m>=60){
    m = 0;
    h++;
  }
  if(h >= 10){
    h = 0;
  }
}

void checkButtons(){
      if(digitalRead(secButtonPin) == LOW){
      s++;
      draw();
    }
    if(digitalRead(minButtonPin) == LOW){
      m++;
      draw();
    }
    if(digitalRead(hourButtonPin) == LOW){
      h++;
      draw();
    }    
}

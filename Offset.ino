#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

unsigned long currentTime;
unsigned long tempTime;

unsigned long stopPulseHighTime;
unsigned long stopPulseLowTime;

int delayTime = 2000;
int offsetTime = 250;
int pulseWidth = 500;

volatile bool stopPulseTriggered;

int startPin = 2;
int stopPin = 3;

void setup() 
{
  pinMode(startPin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  CircuitPlayground.begin();
  CircuitPlayground.strip.begin();\
  stopPulseTriggered = false;
}

void loop()
{
  currentTime = millis();
  
  
  if (currentTime - tempTime >= delayTime)
  {
    tempTime = currentTime;
    CircuitPlayground.setPixelColor(0, 0,127,0);
    stopPulseTriggered = true;
    digitalWrite(startPin, HIGH);
  }

  if (stopPulseTriggered == true && currentTime - tempTime >= offsetTime)
  {   
    stopPulseHighTime = currentTime;
    digitalWrite(stopPin, HIGH);
    CircuitPlayground.setPixelColor(9, 0, 0, 127);
    stopPulseTriggered = false;
  }

  if (currentTime - tempTime >= pulseWidth)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    digitalWrite(startPin, LOW);
  }

  if(stopPulseTriggered == false && currentTime - stopPulseHighTime >= pulseWidth)
  {
    CircuitPlayground.setPixelColor(9, 0, 0, 0);
    digitalWrite(stopPin, LOW);
  } 
}


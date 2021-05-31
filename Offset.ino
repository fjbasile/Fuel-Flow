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
  
  //time delay for the first pulse
  if (currentTime - tempTime >= delayTime) 
  {
    tempTime = currentTime; //log the time at which the start pulse triggered high
    CircuitPlayground.setPixelColor(0, 0,127,0);
    stopPulseTriggered = true;
    digitalWrite(startPin, HIGH);
  }

  //if the stop pulse has been enabled and it has met the offset time requirements then it pulses high
  if (stopPulseTriggered == true && currentTime - tempTime >= offsetTime)
  {   
    stopPulseHighTime = currentTime; //log the time of the stop pulse going high
    digitalWrite(stopPin, HIGH);
    CircuitPlayground.setPixelColor(9, 0, 0, 127);
    stopPulseTriggered = false; //disable the stop pulse so we don't inadvertently re-enter this condition
  }

  //tempTime was updated during the start pulse firing. When it's on longer than pulse width, it goes low
  if (currentTime - tempTime >= pulseWidth)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    digitalWrite(startPin, LOW); 
  }

  //if the stop pulse is deactivated and it has pulsed higher for the right duration, stop pulse goes low
  if(stopPulseTriggered == false && currentTime - stopPulseHighTime >= pulseWidth)
  {
    CircuitPlayground.setPixelColor(9, 0, 0, 0);
    digitalWrite(stopPin, LOW);
  } 
}


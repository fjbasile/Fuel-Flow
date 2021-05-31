#include <Adafruit_CircuitPlayground.h>
#include <Adafruit_Circuit_Playground.h>

unsigned long currentTime;
unsigned long tempTime;

unsigned long stopPulseHighTime;
unsigned long stopPulseLowTime;

int sensorPin = A1;
int sensorValue = 0;

int delayTime = 2000;
int offsetTime = 250;
int pulseWidth = 500;

volatile bool stopPulseEnabled;

int startPin = 2;
int stopPin = 3;

void setup() 
{
  pinMode(startPin, OUTPUT);
  pinMode(stopPin, OUTPUT);
  CircuitPlayground.begin();
  CircuitPlayground.strip.begin();\
  stopPulseEnabled = false;
  //Serial.begin(9600); //for debugging
}

void loop()
{
  //reads the value from the rheostat
  sensorValue = analogRead(sensorPin);
  //Serial.println(sensorValue); //for debugging
  offsetTime = sensorValue / 5.0; //adjusts the offset time based on voltage input
  
  currentTime = millis();
  
  //time delay for the first pulse
  if (currentTime - tempTime >= delayTime) 
  {
    tempTime = currentTime; //log the time at which the start pulse triggered high
    CircuitPlayground.setPixelColor(0, 0,127,0);
    stopPulseEnabled = true;
    digitalWrite(startPin, HIGH);
  }

  //if the stop pulse has been enabled and it has met the offset time requirements then it pulses high
  if (stopPulseEnabled == true && currentTime - tempTime >= offsetTime)
  {   
    stopPulseHighTime = currentTime; //log the time of the stop pulse going high
    digitalWrite(stopPin, HIGH);
    CircuitPlayground.setPixelColor(9, 0, 0, 127);
    stopPulseEnabled = false; //disable the stop pulse so we don't inadvertently re-enter this condition
  }

  //tempTime was updated during the start pulse firing. When it's on longer than pulse width, it goes low
  if (currentTime - tempTime >= pulseWidth)
  {
    CircuitPlayground.setPixelColor(0, 0, 0, 0);
    digitalWrite(startPin, LOW); 
  }

  //if the stop pulse is deactivated and it has pulsed higher for the right duration, stop pulse goes low
  if(stopPulseEnabled == false && currentTime - stopPulseHighTime >= pulseWidth)
  {
    CircuitPlayground.setPixelColor(9, 0, 0, 0);
    digitalWrite(stopPin, LOW);
  } 
}


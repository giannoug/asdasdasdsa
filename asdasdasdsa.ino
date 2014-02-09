#include <Multiplex7Seg.h>
#include "DHT.h"

byte digitPins[] = {
  A4, A5};
byte segmentPins[] = {
  2, A1, 4, A2, A3, 7, 8};

// Uncomment whatever type you're using!
//#define DHTTYPE DHT11   // DHT 11 
#define DHTTYPE DHT22   // DHT 22  (AM2302)
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

#define DHTPIN A0

DHT dht(DHTPIN, DHTTYPE);

boolean showTemp = true;
unsigned long prev_time = 0;

void setup()
{
  Multiplex7Seg::set(0, 2, digitPins, segmentPins);
  dht.begin();
}

void loop()
{ 
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (millis() - prev_time >= 5000) {
    prev_time = millis();
    showTemp = !showTemp;
  }

  //if (isnan(t)) {
  if (showTemp) {
    Multiplex7Seg::loadValue(t);
  }
  else {
    Multiplex7Seg::loadValue(h);
  }
  //}
  //else {
  //  Multiplex7Seg::loadValue(77);
  //}

  delay(500);
}

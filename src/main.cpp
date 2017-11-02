#include <Arduino.h>

#include <SimpleBeacon.h>

SimpleBeacon beacon;

#define LED_BUILTIN 5
#define SLEEP_SECS 4

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    if (beacon.begin())
    {
        Serial.println("Beacon active");
    }
    else
    {
        Serial.println("Beacon failed");
    }

    delay(4000);
}
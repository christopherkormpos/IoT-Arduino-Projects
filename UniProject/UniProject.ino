/*
  Sketch generated by the Arduino IoT Cloud Thing "First Project"
  https://create.arduino.cc/cloud/things/ffc19b68-bbf7-4eea-b812-552fe25f3fdb

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing
  float boardHUMID;
  float boardTEMP;
  bool blueLED;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"
// DHT sensor library - Version: Latest 
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN 7
#define DHTTYPE DHT11

DHT dht(DHTPIN,DHTTYPE);

int myLED = 8;
int volt5 = 2;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);

  // Defined in thingProperties.h
  initProperties();

  digitalWrite(volt5, HIGH);
  pinMode(myLED, OUTPUT);
  
  dht.begin();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  
  delay(2000);
  boardTEMP = dht.readTemperature();
  boardHUMID = dht.readHumidity();
  
  if(boardHUMID >= 60){           //If humidity value is greater than 60 blink three times
    for(int i=0; i<4; i++){
        digitalWrite(myLED, HIGH);
        delay(200);
        digitalWrite(myLED, LOW);
        delay(200);
    }
  }

}



/*
  Since BlueLED is READ_WRITE variable, onBlueLEDChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onBlueLEDChange()  {
  Serial.println(blueLED);

  if (blueLED) {
    digitalWrite(myLED, HIGH);
  }
  else {
    digitalWrite(myLED, LOW);
  }
}
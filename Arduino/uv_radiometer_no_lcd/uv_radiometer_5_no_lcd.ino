/* 
 UV Radiometer for UV SLA Resins based on DLP Projectors
 By Shane Graber
 Vitrify3D LLC
 Date: August 28, 2014 
 
 This sensor detects 280-390nm light most effectively, but does absorb out to 
 ~450nm, similar to many photoinitiators used for UV SLA resins. Handy for 
 dialing in DLP projector-based SLA printers.
*/

// Library for calculating moving averages based on Gaussian smoothing and are
// required for the GaussianAverage function
// download from:
// https://github.com/ivanseidel/LinkedList
// https://github.com/ivanseidel/Gaussian
#include <LinkedList.h>
#include <Gaussian.h>
#include <GaussianAverage.h>

// NOTE: i tried moving averages before the above GaussianAverage class,
// and while my readings were relatively stable, the readings were VERY
// slow to change due to all the smoothing going on. The code was REALLY
// nasty too. GaussianAverage is much Much MUch MUCh MUCH faster and easier
// to implement.

//Hardware pin definitions for UV breakout board
int UVOUT = A0 ; //Output from the sensor
int REF_3V3 = A1 ; //3.3V power on the Arduino board

// running averages for our sensor and define containers for them
// picked these values through trial and error!
#define num 50
GaussianAverage runningAverage(num);
GaussianAverage refAverage(num/10);
GaussianAverage uvIrradianceAverage(num/2);

// variable 'm' to slow down updates in our loop()
#define m 20
byte n = m;

// git'er goin'
void setup() {
  Serial.begin(115200);
  Serial.println("UV Radiometer for DLP Printers");
  Serial.println("STARTING...\n");
  
  // set our pins for the UV sensor
  pinMode(UVOUT, INPUT);
  pinMode(REF_3V3, INPUT);
  
  // populate the array with data initially
  for (byte foo = 0; foo < num*5; foo++) {
    runningAverage.add( Gaussian(analogRead(UVOUT), 1) );
    delay(10); // slow it down a bit; DO NOT CHANGE. you will have a bad time
  }
  
}

// weeeeeeeeeeeee a loop the loop!
void loop() {
  
  // add data to our gaussian averages
  // specifying ", 1" in the .add function is very important as it 
  // restricts the bell curve
  // NOTE: this loop is REQUIRED for our final UV output reading 
  // stability. without it, values range +/- 0.8 mW/cm^2
  // with it, values range +/- 0.1 mW/cm^2
  for (byte foo = 0; foo < num; foo++) {
    runningAverage.add( Gaussian(analogRead(UVOUT), 1) );
    refAverage.add( Gaussian(analogRead(REF_3V3), 1) );
    delay(1);  // slow down our reading a tiny bit
  }

  // find the gaussian average for both the UV sensor and our 3.3V reference   
  // 3.3V reference doesn't fluctuate much, but hey, why not...
  float uvLevel = runningAverage.process().mean;
  float refLevel = refAverage.process().mean;

  // calculate our UV sensor output voltage
  // and map it to a given UV irradiance in mW/cm^2
  // see: https://cdn.sparkfun.com/datasheets/Sensors/LightImaging/ML8511_3-8-13.pdf
  float outputVoltage = 3.30 / refLevel * uvLevel;
  float uvIntensity = mapfloat(outputVoltage, 1.00, 2.80, 0.00, 15.00);
  
  // use another gaussian average for our final output reading stability
  uvIrradianceAverage.add( Gaussian(uvIntensity, 2));
  float uvIrradiance = uvIrradianceAverage.process().mean;
  
  // only update every N times through the loop
  // otherwise it flickers too much
  if (n == m) {
    n = 0;
    Serial.print(abs(uvIrradiance), 1);
    Serial.println(" mJ/cm^2");
  } else {
    n = n + 1;
  }
}

//The Arduino Map function but for floats
//From: http://forum.arduino.cc/index.php?topic=3922.0
float mapfloat(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

/*
This sketch uses the serial monitor and an MSP432F5529 with the
TMP36 to report temperature in degrees Celsius.

The TMP36 is a low voltage, temperature sensor that provides
an analog signal that is linearly proportional to the
temperature.  Accuracy is said to be ±1°C at +25°C and ±2°C
over the −40°C to +125°C temperature range. It provides for
single-supply operation from 2.7 V to 5.5 V maximum. The supply
current runs below 50 μA.

Looking at the flat side of the TMP36 the pins are as follows:
Left    Vs   (+2.7 to 5.5V)
Center  Vout (analog output)
Right   GND

The datasheet calls for a 0.1 μF bypass capacitor on the input
(i.e between Vs on the TMP36 and GND). It specifies a ceramic 
type with short leads and located as close as possible to the 
temperature sensor supply pin. 

Circuit

TMP 36    MSP430F5529
------    ---------------------------------------------------
Vs        3.3V
Vs        0.1uF capacitor to GND
Vout      Pin 23  This must be an analog read pin
GND       GND

Frank Milburn 3 April 2015
*/

const int TMP36Pin = 23;    // pin sensor is connected to
const int analogRes = 4095; // A/D resolution

void setup()
{
  Serial.begin(9600);
  Serial.println("Starting temperature readings...");
}

void loop()
{
  // Get the output from the sensor and multiply it by
  // 3.3V / resolution to get the voltage.  Note that
  // I am using 3.24V since that is what I read on my DMM.

  float voltage = (analogRead(TMP36Pin) * 3.24 / analogRes);
  
  // TMP36 datasheet provides the conversion formula
  float degC = (voltage - 0.5) * 100.0;
  
  // and if fahrenheit is desired
  float degF = (degC * 1.8) + 32.0;

  // Now the serial output...
  Serial.println("___________________________________________");
  Serial.print("Voltage:         "); Serial.println(voltage,3);
  Serial.print("Temperature (C): "); Serial.println(degC,1);
  Serial.print("Temperature (F): "); Serial.println(degF,1);

  delay(1000); 
}

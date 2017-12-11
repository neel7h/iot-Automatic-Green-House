#include <DHT.h>;
#include "MQ135.h"

//Constants
#define DHTPIN 7     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE); //// Initialize DHT sensor for normal 16mhz Arduino
#define PIN_MQ135 A3
MQ135 mq135_sensor = MQ135(PIN_MQ135);
int chk;
float hum;  //Stores humidity value
float temp; //Stores temperature value


int obstaclePin = 6;  // This is our input pin
int hasObstacle = HIGH;  // HIGH MEANS NO OBSTACLE


const int sensor_pin = A0;  /* Soil moisture sensor O/P pin */
 float moisture_percentage;
  int sensor_analog;
  int val;
int nRainIn = A1;
int nRainDigitalIn = 2;
int nRainVal;
boolean bIsRaining = false;
String strRaining;


void setup() {
  
  Serial.begin(9600);
    dht.begin();

    pinMode(8,OUTPUT);
    pinMode(2,INPUT);
    pinMode(obstaclePin, INPUT);

    pinMode(13,OUTPUT);
/* Define baud rate for serial communication */
}

void loop() {
 soil_water();
 rain();
 tempe();
 intruder();
}

void soil_water()
{
  val=digitalRead(8);
  
if(val==LOW)
   {
    digitalWrite(13,LOW);
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
    Serial.print("%\n");

  Serial.print("Soil Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n");
  delay(1000);

   }
   else
   {
    digitalWrite(13,HIGH);
  sensor_analog = analogRead(sensor_pin);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  Serial.print("Soil Moisture Percentage = ");
  Serial.print(moisture_percentage);
  Serial.print("%\n\n");
  delay(1000);
   }
}


void rain(){
 nRainVal = analogRead(nRainIn);
  bIsRaining = !(digitalRead(nRainDigitalIn));
  
  if(bIsRaining){
    strRaining = "YES";
  }
  else{
    strRaining = "NO";
  }
  
  Serial.print("Raining?: ");
  Serial.print(strRaining);  
  Serial.print("\t Moisture Level: ");
  Serial.println(nRainVal);
  
  delay(1000);

}

void tempe(){
  //Read data and store it to variables hum and temp
    hum = dht.readHumidity();
    temp= dht.readTemperature();
     float rzero = mq135_sensor.getRZero();
  float correctedRZero = mq135_sensor.getCorrectedRZero(temp, hum);
  float resistance = mq135_sensor.getResistance();
     float ppm = mq135_sensor.getPPM();
  float correctedPPM = mq135_sensor.getCorrectedPPM(temp, hum);

    //Print temp and humidity values to serial monitor
    Serial.print("Humidity: ");
    Serial.print(hum);
    Serial.print(" %, Temp: ");
    Serial.print(temp);
    Serial.println(" Celsius");
    Serial.print("PPM: ");
    Serial.print(ppm);
    Serial.print("\t Corrected PPM: ");
    Serial.print(correctedPPM);
        Serial.print("\n ");

    delay(1000); //Delay 2 sec.
}


void intruder()
{
  hasObstacle = digitalRead(obstaclePin); //Reads the output of the obstacle sensor from the 7th PIN of the Digital section of the arduino
  if (hasObstacle == LOW) //LOW means something is ahead, so illuminates the 13th Port connected LED
  {
    Serial.println("Stop something is ahead!!");
  }
  else
  {
    Serial.println("Path is clear");
  }
  delay(200);
}


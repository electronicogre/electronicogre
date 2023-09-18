int analogPin = PA1; // water sensor connected to the analog port 1
int led = PB9; // LEd connected to the digital mouth 12
int led1 = PB11;
int led2 = PB1;
int val = 0; // definition variable val initial value as 0
//int data = 0; // definition variable data initial value as 0
void setup ()
{
pinMode(analogPin, INPUT_ANALOG);
pinMode (led, OUTPUT);
pinMode (led1, OUTPUT);// definition led as output pin
pinMode (led2, OUTPUT);
Serial.begin(9600); // set the baud rate as 9600
digitalWrite (led, LOW);
digitalWrite (led1, LOW);
digitalWrite (led2, LOW);

}
void loop ()
{
//data = val; // variable val assignment to variable data

 // read the simulation value and send to variable val
if (val>1300 && val<2600) {// judgment variable val is whether more than 700 or not
digitalWrite (led, HIGH);
digitalWrite (led1, LOW);
digitalWrite (led2, LOW);

// variable val greater than 700, LED on
}
else if(val > 800 && val<1300) {
digitalWrite (led1, HIGH);
digitalWrite (led, LOW);
digitalWrite (led2, LOW);


// variable val less than 700, LED off
}
else if(val > 300&&  val<800) {
digitalWrite (led2, HIGH);
digitalWrite (led, LOW);
digitalWrite (led1, LOW);

// variable val less than 700, LED off
}

val = analogRead(analogPin);
Serial. println (val,DEC); // serial print variable data
delay (500);

}
/*
// Sensor pins
#define sensorPower PB6
#define sensorPin PA0

// Value for storing water level
int val = 0;

void setup() {
  // Set D7 as an OUTPUT
  pinMode(sensorPower, OUTPUT);
  
  // Set to LOW so no power flows through the sensor
  digitalWrite(sensorPower, LOW);
  
  Serial.begin(9600);
}

void loop() {
  //get the reading from the function below and print it
  int level = readSensor();
  
  Serial.print("Water level: ");
  Serial.println(level);
  
  delay(1000);
}

//This is a function used to get the reading
int readSensor() {
  digitalWrite(sensorPower, HIGH);  // Turn the sensor ON
  delay(10);              // wait 10 milliseconds
  val = analogRead(sensorPin);    // Read the analog value form sensor
  digitalWrite(sensorPower, LOW);   // Turn the sensor OFF
  return val;             // send current reading
}*/

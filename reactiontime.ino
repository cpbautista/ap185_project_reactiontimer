/*
  Reaction Time Sensor
  by Chris Dion Bautista*, Viron Gil Estrada, Jireh Vera Cruz
  National Institute of Physics, University of the Philippines
  Corresponding author: cpbautista@up.edu.ph

  Submitted as part of the course requirements in Applied Physics 185.
  Presented on: 19 May 2019

  Modified from:
  Ultrasonic Sensor HC-SR04 and Arduino Tutorial
  by Dejan Nedelkovski,
  www.HowToMechatronics.com
*/

// defines pins numbers
const int ledPin = 8; // Blue LED
const int trigPin = 9; //Trigger pin of the sensor
const int echoPin = 10; //Echo pin of the sensor
const int signalPin = 12; //Yellow LED

// defines variables
long trigger;
boolean hand;
long duration;
int distance;
unsigned long startTime;
unsigned long endTime;
unsigned long reactionTime;

void setup() {
  pinMode(ledPin, OUTPUT); // Sets the ledPin as an Output
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  pinMode(signalPin, OUTPUT); // Sets the signalPin as an Output
  Serial.begin(9600); // Starts the serial communication
}

void loop() {
  //Resets the values.
  trigger = random(1500, 5000); //Sets the time until the blue LED turns on
  hand = false; //Clears the detection condition.
  distance = 100; //Clears the distance value.

  //Signals to "get ready" using the yellow LED.
  digitalWrite(signalPin, HIGH);
  delay(2500);
  digitalWrite(signalPin, LOW);

  //Turns on the blue LED after a number of seconds.
  delay(trigger);
  digitalWrite(ledPin, HIGH);

  /*
     Right after the blue LED turns on, the device starts timing until
     an obstacle is placed in front of the sensor. The blue LED turns
     off afterwards.
  */
  startTime = millis();
  hand = myReadDistanceFunction();
  endTime = millis();
  digitalWrite(ledPin, LOW);

  // The reaction time is calculated and is sent to the serial monitor.
  reactionTime = endTime - startTime;
  Serial.print("Reaction Time (ms): ");
  Serial.println(reactionTime);

  delay(1000);
}


/*
    The following function prompts the sensor to collect a distance measurement.
    The sensor keeps making distance measurements until it is less than a specified
    value. Here, that threshold is set at 8 cm.
*/
boolean myReadDistanceFunction() {
  while (distance >  8) {
    // Clears the trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);

    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);

    // Calculating the distance
    distance = duration * 0.034 / 2;

    //Uncomment the following two lines to display the distance in the serial monitor.
    //Serial.print("Distance: ");
    //Serial.println(distance);
  }

  return true;
}

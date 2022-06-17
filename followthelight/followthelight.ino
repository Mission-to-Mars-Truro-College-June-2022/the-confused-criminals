#include <NewPing.h>

#define fTRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define fECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define bTRIGGER_PIN  13 // Arduino bottom trigger pin
#define bECHO_PIN     17 // Arduino bottom echo pin

NewPing fSonar(fTRIGGER_PIN, fECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing bSonar(bTRIGGER_PIN, bECHO_PIN, MAX_DISTANCE);

int fSensorPin = A6;    // select the input pin for the potentiometer
int lSensorPin = A7;
int rSensorPin = A2;
int ledPin = 8;      // select the pin for the LED
int fSensorVal = 0;
int lSensorVal = 0;
int rSensorVal = 0;
int rmForward = 7;
int rmReverse = 8;
int rmEnabled = 9;
int lmForward = 11;
int lmReverse = 12;
int lmEnabled = 10;
int fPingDis = 0;
int bPingDis = 0;
int brightestValue = 2000;
int startMilli = 0;
int endMilli = 0;
int originalSensorVal = 50;
const int leftFeedback = 2;
const int rightFeedback = 3;
volatile int leftcounter = 0;
volatile int rightcounter = 0;
  
void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200); 
  pinMode(rmForward, OUTPUT);
  pinMode(rmReverse, OUTPUT);
  pinMode(rmEnabled, OUTPUT);
  pinMode(lmForward, OUTPUT);
  pinMode(lmReverse, OUTPUT);
  pinMode(lmEnabled, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  fSonar.ping_cm();
  bSonar.ping_cm();
}

void cancel(){
  digitalWrite(rmForward, LOW);
  digitalWrite(lmForward, LOW);
  digitalWrite(rmReverse, LOW);
  digitalWrite(lmReverse, LOW);
  digitalWrite(rmEnabled, LOW);
  digitalWrite(lmEnabled, LOW);
}

void speedSteering(int lSpeed, int rSpeed, bool lForward, bool rForward){
  // left motor controls
  if (lForward){
    digitalWrite(lmForward, HIGH);
    digitalWrite(lmReverse, LOW);
  }
  else
  {
    digitalWrite(lmForward, LOW);
    digitalWrite(lmReverse, HIGH);
  }
  // right motor controls
  if (rForward){
    digitalWrite(rmForward, HIGH);
    digitalWrite(rmReverse, LOW);
  }
  else
  {
    digitalWrite(rmForward, LOW);
    digitalWrite(rmReverse, HIGH);
  }
  
  analogWrite(rmEnabled, rSpeed);
  analogWrite(lmEnabled, lSpeed);
}


void loop() {
  speedSteering(180, 180, false, true);
  startMilli = millis();
  while(millis() <= 3400){
    fSensorVal = analogRead(fSensorPin);
    rSensorVal = analogRead(rSensorPin);
    lSensorVal = analogRead(lSensorPin);
  
    if (lSensorVal < brightestValue){
      brightestValue = lSensorVal;
      endMilli = millis();
    }
  
    if (rSensorVal < brightestValue){
      brightestValue = rSensorVal;
      endMilli = millis();
    }
  
    if (fSensorVal < brightestValue){
      brightestValue = fSensorVal;
      endMilli = millis();
    }
  }
  cancel();
  delay(1000);
  speedSteering(180, 180, false, true);
  delay((endMilli - startMilli));
  speedSteering(150, 150, true, true);
  while(true){
    fSensorVal = analogRead(fSensorPin);
    rSensorVal = analogRead(rSensorPin);
    lSensorVal = analogRead(lSensorPin);
    if ((lSensorVal < fSensorVal) and (lSensorVal < rSensorVal)){
      speedSteering(0, 255, true, true);
    }
    else if ((fSensorVal < lSensorVal) and (fSensorVal < rSensorVal)){
      speedSteering(100, 100, true, true);
    }
    else if ((rSensorVal < lSensorVal) and (rSensorVal < fSensorVal)){
      speedSteering(255, 0, true, true);
    }
    bPingDis = bSonar.ping_cm();
    delay(35); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  
    if (bPingDis > 14){
      cancel();
      delay(100);
      speedSteering(100, 100, false, false);
      delay(1000);
      cancel();
      delay(500);
      exit(0);
    }
  }
}

void collisionSteering() {
  while(true){
    speedSteering(170, 170, true, true);
    delay(50);                // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
    fPingDis = fSonar.ping_cm();
    Serial.print("Ping: ");
    Serial.print(fPingDis); // Send ping, get distance in cm and print result (0 = outside set distance range)
    Serial.println("cm");
    
    if (fPingDis > 0 and fPingDis <= 12){
      cancel();
      delay(250);
      exit(0);
    }
  }
}

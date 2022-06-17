#include <NewPing.h>

#define fTRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define fECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define bTRIGGER_PIN  13 // Arduino bottom trigger pin
#define bECHO_PIN     17 // Arduino bottom echo pin

NewPing fSonar(fTRIGGER_PIN, fECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing bSonar(bTRIGGER_PIN, bECHO_PIN, MAX_DISTANCE);

//declaring useful variables and naming the pins
int fSensorPin = A6; 
int lSensorPin = A7;
int rSensorPin = A2;
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
int lBarrierDis = 0;
int rBarrierDis = 0;
const int leftFeedback = 2;
const int rightFeedback = 3;
volatile int leftcounter = 0;
volatile int rightcounter = 0;

// the cancel function dissables the left and right motors and turns them off

void cancel(){
  digitalWrite(rmForward, LOW);
  digitalWrite(lmForward, LOW);
  digitalWrite(rmReverse, LOW);
  digitalWrite(lmReverse, LOW);
  digitalWrite(rmEnabled, LOW);
  digitalWrite(lmEnabled, LOW);
}

// the speedSteering function powers the motors based on the parametres given
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

// the setup function gets processed once at the start of the progam
void setup() {
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

// loop it describes its self (loops that section of code over and over till the program ends)
void loop() {
  speedSteering(150, 150, true, true);
  fPingDis = fSonar.ping_cm();
  delay(35);
  if (fPingDis <= 20){
    speedSteering(150, 150, false, true);
    delay(900);
    cancel();
    lBarrierDis = fSonar.ping_cm();
    delay(35);
    speedSteering(170, 150, true, false);
    delay(1800);        //double 1800
    rBarrierDis = fSonar.ping_cm();
    delay(35);
    if ((lBarrierDis >= rBarrierDis) or (lBarrierDis = 0)){
      speedSteering(160, 150, false, true);
      delay(1800);        //double 1800
    }
  }
}

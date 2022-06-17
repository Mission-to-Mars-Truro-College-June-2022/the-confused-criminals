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
int lCounter = 0;
int rCounter = 0;
bool runTime = true;
const int leftFeedback = 2;
const int rightFeedback = 3;
volatile int leftcounter = 0;
volatile int rightcounter = 0;

// the cancel function disables the left and right motors and turns them off

void cancel() {
  digitalWrite(rmForward, LOW);
  digitalWrite(lmForward, LOW);
  digitalWrite(rmReverse, LOW);
  digitalWrite(lmReverse, LOW);
  digitalWrite(rmEnabled, LOW);
  digitalWrite(lmEnabled, LOW);
}

// the speedSteering function powers the motors based on the parametres given
void speedSteering(int lSpeed, int rSpeed, bool lForward, bool rForward) {
  // left motor controls
  if (lForward) {
    digitalWrite(lmForward, HIGH);
    digitalWrite(lmReverse, LOW);
  }
  else
  {
    digitalWrite(lmForward, LOW);
    digitalWrite(lmReverse, HIGH);
  }
  // right motor controls
  if (rForward) {
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
void mazeSolver() {
  speedSteering(150, 150, true, true); //starts going forward
  fPingDis = fSonar.ping_cm(); //pings sonar
  delay(35); //delay for the sonar
  if (fPingDis <= 20) { //if object infront of sonar 20cm away
    speedSteering(160, 160, false, true); //turns left
    delay(1000); //for a second
    cancel();
    lBarrierDis = fSonar.ping_cm(); //checks left hand side
    delay(35);
    speedSteering(170, 170, true, false); //turns 180 degrees
    delay(2000);        //double 1800
    rBarrierDis = fSonar.ping_cm(); //checks right hand side
    delay(35);
    if ((lBarrierDis >= rBarrierDis) or (lBarrierDis = 0)) { //if the left hand side is futher away
      speedSteering(170, 170, false, true); //turn 180 to face the left
      delay(2000);        //double 1800
      lCounter ++; //increase left counter
    }
    else {
      rCounter ++; //increases the right counter as it's facing right
    }
  }
  if (((rCounter + 2) == lCounter) or (lCounter + 2) == rCounter) { // if it's facing backwards
    speedSteering(170, 170, false, true); //turns left
    delay(900);
    runTime = true;
    do {
      if ((rCounter + 2) == lCounter) { 
        speedSteering(150, 150, true, true); //goes forward
      }
      else if ((lCounter + 2) == rCounter) {
        speedSteering(150, 150, false, false); //goes backward
      }
      delay(1000);
      speedSteering(160, 160, false, true); //moves to the left
      delay(900);
      cancel(); //stops the movement
      fPingDis = fSonar.ping_cm(); //checks the left
      delay(35);
      if ((fPingDis >= 20) or (fPingDis == 0)) { //if left is free
        break;
      }
      else {
        speedSteering(160, 160, true, false); //turn to the right
        delay(900);
      }
    } while (runTime = true);
    rCounter = 0; //resets the counters
    lCounter = 0;
  }
}

void slideLeft(){
  speedSteering(150, 150, false, true);
  delay(1000);
  speedSteering(150, 150, false, false);
  delay(500);
  speedSteering(150, 150, true, false);
  delay(1000);
  cancel();
  delay(500);
}
  
void slideRight(){
  speedSteering(150, 150, true, false);
  delay(1000);
  speedSteering(150, 150, false, false);
  delay(500);
  speedSteering(150, 150, false, true);
  delay(1000);
}
  
void chaChaSlide(){
  speedSteering(150, 150, false, false);
  delay(1000);
  speedSteering(150, 150, true, true);
  delay(1000);
  speedSteering(150, 150, false, false);
  delay(1000);
  speedSteering(150, 150, true, true);
  delay(1000);
}

void clapSpoons(){
  speedSteering(150, 150, false, false);
  delay(150);
  speedSteering(150, 150, true, true);
  delay(150);
  speedSteering(150, 150, false, false);
  delay(150);
  speedSteering(150, 150, true, true);
  delay(150);
}

void crissCross(){
  speedSteering(255, 255, true, false);
  delay(400);
  speedSteering(255, 255, false, true);
  delay(800);
  speedSteering(255, 255, true, false);
  delay(300);
  cancel();
  delay(500);
}

void reverse(){
  speedSteering(150, 150, false, false);
  delay(1000);
}

void rStomp(){
  speedSteering(255, 255, false, true);
  delay(300);
  cancel();
  delay(100);
  speedSteering(255, 255, true, false);
  delay(300);
  cancel();
  delay(500);
}

void lStomp(){
  speedSteering(255, 255, true, false);
  delay(300);
  cancel();
  delay(100);
  speedSteering(255, 255, false, true);
  delay(250);
  cancel();
  delay(500);
}

void hop(){
  speedSteering(255, 255, true, true);
  delay(200);
}

void chaChaSlideDance(){
  speedSteering(255, 255, true, false);
  delay(24000);
  clapSpoons();   //10 second delay
  slideLeft();
  delay(300);
  reverse();
  delay(750);
  hop();
  delay(750);
  rStomp();
  delay(200);
  lStomp();
  delay(1000);
  chaChaSlide();
}

void loop(){
  speedSteering(100, 100, true, true);
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

  fPingDis = fSonar.ping_cm();
  delay(35);

  if ((fPingDis <= 10) and (fPingDis >= 0)){
    cancel();
    delay(100);
    while(true){
      mazeSolver();
    }
  }
  
}

// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define fTRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define fECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define bTRIGGER_PIN  13 // Arduino bottom trigger pin
#define bECHO_PIN     17 // Arduino bottom echo pin

NewPing fSonar(fTRIGGER_PIN, fECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
NewPing bSonar(bTRIGGER_PIN, bECHO_PIN, MAX_DISTANCE);

int rmForward = 7;
int rmReverse = 8;
int rmEnabled = 9;
int lmForward = 11;
int lmReverse = 12;
int lmEnabled = 10;
int fPingDis = 0;
int bPingDis = 0;
const int leftFeedback = 2;
const int rightFeedback = 3;
volatile int leftcounter = 0;
volatile int rightcounter = 0;

void forwards(bool forward){
  if (forward) {
    digitalWrite(rmForward, HIGH);
    digitalWrite(lmForward, HIGH);
    digitalWrite(lmReverse, LOW);
    digitalWrite(rmReverse, LOW);

    }
  else {
    digitalWrite(rmForward, LOW);
    digitalWrite(lmForward, LOW);
    digitalWrite(lmReverse, HIGH);
    digitalWrite(rmReverse, HIGH);

  }
    digitalWrite(rmEnabled, HIGH);
    digitalWrite(lmEnabled, HIGH);
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

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.

  fSonar.ping_cm();
  bSonar.ping_cm();

  pinMode(rmForward, OUTPUT);
  pinMode(rmReverse, OUTPUT);
  pinMode(rmEnabled, OUTPUT);
  pinMode(lmForward, OUTPUT);
  pinMode(lmReverse, OUTPUT);
  pinMode(lmEnabled, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void loop() {
  bPingDis = bSonar.ping_cm();
  delay(35); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  speedSteering(100, 100, true, true);
  
  if (bPingDis > 14){
    cancel();
    delay(100);
    forwards(false);
    delay(450);
    cancel();
    delay(500);
    exit(0);
  }
  
}

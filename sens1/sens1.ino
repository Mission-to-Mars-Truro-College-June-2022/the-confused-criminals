// ---------------------------------------------------------------------------
// Example NewPing library sketch that does a ping about 20 times per second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define TRIGGER_PIN  4  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     5  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 200 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

int rmForward = 7;
int rmReverse = 8;
int rmEnabled = 9;
int lmForward = 11;
int lmReverse = 12;
int lmEnabled = 10;
int pingDis = 0;
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

  sonar.ping_cm();

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
  speedSteering(170, 170, true, true);
  pingDis = sonar.ping_cm();
  delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Ping: ");
  Serial.print(pingDis); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

  
  
  if (pingDis > 0 and pingDis <= 20){
    cancel();
    delay(250);
    speedSteering(225, 225, false, true);
    delay(750);
    cancel();
    delay(500);
  }
}

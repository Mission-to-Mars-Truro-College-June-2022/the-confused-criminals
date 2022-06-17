//variable declarations
int rmForward = 7;
int rmReverse = 8;
int rmEnabled = 9;
int lmForward = 11;
int lmReverse = 12;
int lmEnabled = 10;
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

void reverse(){
  digitalWrite(rmEnabled, HIGH);
  digitalWrite(lmEnabled, HIGH);
  digitalWrite(rmReverse, HIGH);
  digitalWrite(lmReverse, HIGH);
}


void speedSteering(int lSpeed, int rSpeed, bool forward){
  if (forward){
    digitalWrite(rmForward, HIGH);
    digitalWrite(lmForward, HIGH);
    digitalWrite(rmReverse, LOW);
    digitalWrite(lmReverse, LOW);
  }
  else
  {
  digitalWrite(rmForward, LOW);
  digitalWrite(lmForward, LOW);
  digitalWrite(rmReverse, HIGH);
  digitalWrite(lmReverse, HIGH);
  }

  analogWrite(rmEnabled, rSpeed);
  analogWrite(lmEnabled, lSpeed);
}

void setup() {
  Serial.begin(115200);
  attachInterrupt(digitalPinToInterrupt(leftFeedback), LeftMotorISR, RISING);
  attachInterrupt(digitalPinToInterrupt(rightFeedback), RightMotorISR, RISING);

  pinMode(rmForward, OUTPUT);
  pinMode(rmReverse, OUTPUT);
  pinMode(rmEnabled, OUTPUT);
  pinMode(lmForward, OUTPUT);
  pinMode(lmReverse, OUTPUT);
  pinMode(lmEnabled, OUTPUT);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
}

void straight(){
  speedSteering(170, 170, true);

  if (leftcounter < rightcounter) {
    speedSteering(255, 170, true);
  }
  else if (rightcounter < leftcounter) {
    speedSteering(170, 255, true);
    
  }
}

void loop() {

  delay(1000);
  
  //Moves the rover in a square, forwards, turning left 
  forwards(true);
  delay(500);
  speedSteering(0, 190, true);
  delay(1850);
  forwards(true);
  delay(450);
  speedSteering(0, 190, true);
  delay(1850);
  forwards(true);
  delay(325);
  speedSteering(0, 190, true);
  delay(1750);
  forwards(true);
  delay(1500);

  
  //Moves the rover in a square, forwards, turning right
  
  speedSteering(255,0,true);
  delay(1900);
  forwards(true);
  delay(500);
  speedSteering(245, 0, true);
  delay(1900);
  forwards(true);
  delay(450);
  speedSteering(245, 0,true);
  delay(2000);
  forwards(true);
  delay(850);
  cancel();
  delay(2000);
  
  
  //Moves the rover in a square, backwards, turning left 
  forwards(false);
  delay(1000);
  speedSteering(230, 0, false);
  delay(1850);
  forwards(false);
  delay(500);
  speedSteering(230, 0, false);
  delay(1850);
  forwards(false);
  delay(675);
  speedSteering(230, 0, false);
  delay(1750);
  forwards(false);
  delay(1625);
  
  //Moves the rover in a square, backwards, turning right
  
  speedSteering(0, 210, false);
  delay(2100);
  forwards(false);
  delay(500);
  speedSteering(0, 210, false);
  delay(1800);
  forwards(false);
  delay(425);
  speedSteering(0, 220, false);
  delay(1800);
  forwards(false);
  delay(775);

  
  cancel();
  delay(5000);
  exit(0);
}

void LeftMotorISR(){
  leftcounter++;
}

void RightMotorISR(){
  rightcounter++;
}

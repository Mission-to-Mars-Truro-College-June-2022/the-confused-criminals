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

void forwards(){
  digitalWrite(rmForward, HIGH);
  digitalWrite(lmForward, HIGH);
  digitalWrite(rmEnabled, HIGH);
  digitalWrite(lmEnabled, HIGH);
}

void reverse(){
  digitalWrite(rmEnabled, HIGH);
  digitalWrite(lmEnabled, HIGH);
  digitalWrite(rmReverse, HIGH);
  digitalWrite(lmReverse, HIGH);
}

void cancel(){
  digitalWrite(rmForward, LOW);
  digitalWrite(lmForward, LOW);
  digitalWrite(rmReverse, LOW);
  digitalWrite(lmReverse, LOW);
  digitalWrite(rmEnabled, LOW);
  digitalWrite(lmEnabled, LOW);
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
 
   //Moves the rover in a square, turning left 
  forwards();
  delay(1000);
  speedSteering(0, 180, true);
  delay(1800);
  forwards();
  delay(1000);
  speedSteering(0, 200, true);
  delay(1800);
  forwards();
  delay(900);
  speedSteering(0, 190, true);
  delay(1750);
  forwards();
  delay(3000);

  
  //Moves the rover in a square turning right
  
  speedSteering(255,0,true);
  delay(2050);
  forwards();
  delay(1000);
  speedSteering(255, 0, true);
  delay(2025);
  forwards();
  delay(1050);
  speedSteering(255, 0,true);
  delay(2050);
  forwards();
  delay(1750);

  
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

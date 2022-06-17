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

void speedSteering(int lSpeed, int rSpeed){
  digitalWrite(rmForward, HIGH);
  digitalWrite(lmForward, HIGH);
  digitalWrite(rmReverse, LOW);
  digitalWrite(lmReverse, LOW);
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
  speedSteering(170, 170);

  if (leftcounter < rightcounter) {
    speedSteering(255, 170);
  }
  else if (rightcounter < leftcounter) {
    speedSteering(170, 255);
    
  }
}


void LeftMotorISR(){
  leftcounter++;
}

void RightMotorISR(){
  rightcounter++;
}


void loop() {
  straight();
  if (leftcounter > 900 and rightcounter > 900){
    cancel();
    delay(2000);
    exit(0);
  }
}

int EN  = 2+9;
int DIR = 3+9; //define Direction pin
int PUL = 4+9; //define Pulse pin

void setup() {
  pinMode (EN, OUTPUT);
  pinMode (DIR, OUTPUT);
  pinMode (PUL, OUTPUT);
  digitalWrite(EN, LOW);
}

int t1 = 250;
int t2 = t1;
void loop() {
  for (int i = 0; i < 640 * 10; i++) //Forward 5000 steps
  {
    digitalWrite(DIR, LOW);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL, LOW);
    delayMicroseconds(t2);
  }
  delay(1000);
  for (int i = 0; i < 640 * 10; i++) //Backward 5000 steps
  {
    digitalWrite(DIR, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL, LOW);
    delayMicroseconds(t2);
  }
  delay(1000);
}

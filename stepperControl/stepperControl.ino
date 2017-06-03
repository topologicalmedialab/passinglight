#include <SerialCommand.h>

SerialCommand command;

int EN [] = {2, 5,  8, 11};
int DIR[] = {3, 6,  9, 12}; //define Direction pin
int PUL[] = {4, 7, 10, 13}; //define Pulse pin

void setup() {
  Serial.begin(115200);
  command.addCommand("TEST", rotate);

  for (int i = 0; i < 4; i++) {
    pinMode (EN[i], OUTPUT);
    pinMode (DIR[i], OUTPUT);
    pinMode (PUL[i], OUTPUT);

    digitalWrite(EN[i], LOW);
  }
}

void loop() {
  command.readSerial();
}

int t1 = 250;
int t2 = t1;

void rotate() {
  char *arg;
  arg = command.next();
  Serial.println(arg);

  if (arg == NULL) {
    Serial.println("usage: TEST n");
    return;
  }

  int id = atoi(arg);

  digitalWrite(EN[id], HIGH);

  for (int i = 0; i < 640 * 10; i++) //Forward 5000 steps
  {
    digitalWrite(DIR[id], LOW);
    digitalWrite(PUL[id], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[id], LOW);
    delayMicroseconds(t2);
  }
  delay(1000);
  for (int i = 0; i < 640 * 10; i++) //Backward 5000 steps
  {
    digitalWrite(DIR[id], HIGH);
    digitalWrite(PUL[id], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[id], LOW);
    delayMicroseconds(t2);
  }
  digitalWrite(EN[id], LOW);
}


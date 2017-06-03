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

    digitalWrite(EN[i], HIGH);
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
  int counterId = (id + 2) % 4;

  //digitalWrite(EN[id], HIGH);
  //digitalWrite(EN[counterId], HIGH);

  digitalWrite(DIR[id], HIGH);
  digitalWrite(DIR[counterId], LOW);
  for (int i = 0; i < 640 * 7; i++)
  {
    digitalWrite(PUL[id], HIGH);
    digitalWrite(PUL[counterId], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[id], LOW);
    digitalWrite(PUL[counterId], LOW);
    delayMicroseconds(t2);
  }
  delay(2000);

  digitalWrite(DIR[id], LOW);
  digitalWrite(DIR[counterId], HIGH);
  for (int i = 0; i < 640 * 7; i++)
  {
    digitalWrite(PUL[id], HIGH);
    digitalWrite(PUL[counterId], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[id], LOW);
    digitalWrite(PUL[counterId], LOW);
    delayMicroseconds(t2);
  }
  //digitalWrite(EN[id], LOW);
  //digitalWrite(EN[counterId], LOW);
}


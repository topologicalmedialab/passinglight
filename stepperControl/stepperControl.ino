#include <SerialCommand.h>

SerialCommand command;

int EN [] = {2, 5,  8, 11};
int DIR[] = {3, 6,  9, 12}; //define Direction pin
int PUL[] = {4, 7, 10, 13}; //define Pulse pin

void setup() {
  Serial.begin(115200);
  command.addCommand("TEST", rotate);
  command.addCommand("ENABLE", enable);
  command.addCommand("DISABLE", disable);

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

int t1 = 250 * 1.5;
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
  int id2 = (id + 1) % 4;
  int counterId = (id + 2) % 4;
  int counterId2 = (id + 2 + 1) % 4;

  //digitalWrite(EN[id], HIGH);
  //digitalWrite(EN[counterId], HIGH);

  digitalWrite(DIR[id], HIGH);
  digitalWrite(DIR[id2], HIGH);
  digitalWrite(DIR[counterId], LOW);
  digitalWrite(DIR[counterId2], LOW);
  for (int i = 0; i < 640 * 8; i++)
  {
    digitalWrite(PUL[id], HIGH);
    digitalWrite(PUL[id2], HIGH);
    digitalWrite(PUL[counterId], HIGH);
    digitalWrite(PUL[counterId2], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[id], LOW);
    digitalWrite(PUL[id2], LOW);
    digitalWrite(PUL[counterId], LOW);
    digitalWrite(PUL[counterId2], LOW);
    delayMicroseconds(t2);
  }
  delay(3000);

  digitalWrite(DIR[id], LOW);
  digitalWrite(DIR[id2], LOW);
  digitalWrite(DIR[counterId], HIGH);
  digitalWrite(DIR[counterId2], HIGH);
  for (int i = 0; i < 640 * 8; i++)
  {
    digitalWrite(PUL[id], HIGH);
    digitalWrite(PUL[id2], HIGH);
    digitalWrite(PUL[counterId], HIGH);
    digitalWrite(PUL[counterId2], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[id], LOW);
    digitalWrite(PUL[id2], LOW);
    digitalWrite(PUL[counterId], LOW);
    digitalWrite(PUL[counterId2], LOW);
    delayMicroseconds(t2);
  }
  //digitalWrite(EN[id], LOW);
  //digitalWrite(EN[counterId], LOW);
}

void enable() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(EN[i], HIGH);
  }
}

void disable() {
  for (int i = 0; i < 4; i++) {
    digitalWrite(EN[i], LOW);
  }
}


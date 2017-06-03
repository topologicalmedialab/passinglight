int EN [] = {2, 5,  8, 11};
int DIR[] = {3, 6,  9, 12}; //define Direction pin
int PUL[] = {4, 7, 10, 13}; //define Pulse pin

void setup() {
  Serial.begin(115200);
  for(int i = 0; i < 4; i++) {
    pinMode (EN[i], OUTPUT);
    pinMode (DIR[i], OUTPUT);
    pinMode (PUL[i], OUTPUT);

    digitalWrite(EN[i], LOW);
  }
}

char command = 255;

int count = 0;

int t1 = 250;
int t2 = t1;
void loop() {
  int id = (int)command - (int)'1';
  if(command == '1' ||command == '2' ||command == '3' ||command == '4') {
  } else {
    delay(10);
    return;
  }

  count = id;

  digitalWrite(EN[count], HIGH);

  for (int i = 0; i < 640 * 10; i++) //Forward 5000 steps
  {
    digitalWrite(DIR[count], LOW);
    digitalWrite(PUL[count], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[count], LOW);
    delayMicroseconds(t2);
  }
  delay(1000);
  for (int i = 0; i < 640 * 10; i++) //Backward 5000 steps
  {
    digitalWrite(DIR[count], HIGH);
    digitalWrite(PUL[count], HIGH);
    delayMicroseconds(t1);
    digitalWrite(PUL[count], LOW);
    delayMicroseconds(t2);
  }
  digitalWrite(EN[count], LOW);

  count = (count + 1) % 4;
  command = 255;

  delay(1000);
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    command = (char)Serial.read();
    Serial.println(command);
  }
}


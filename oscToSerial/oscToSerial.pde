import processing.serial.*;

Serial serial;

void setup() 
{
  size(200, 200);
  println((Object[])Serial.list());
  String portName = Serial.list()[2];
  serial = new Serial(this, portName, 115200);
}

void draw() {
  background(255);
}

void mousePressed() {
  serial.write("TEST 1\n");
}
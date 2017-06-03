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
  float x = mouseX - width/2;
  float y = height/2 - mouseY;
  float angle = atan2(y, x) / PI * 2;
  if (angle < 0) angle += 4;

  int id = (int)floor(angle);
  serial.write("TEST " + str(id) + "\n");
}
import processing.serial.*;
import oscP5.*;
import netP5.*;

OscP5 oscP5;

Serial serial;

int lastMoved = -100000;
int intervalMoved = 18 * 1000;

void setup() 
{
  size(200, 200);
  println((Object[])Serial.list());
  String portName = Serial.list()[4];
  serial = new Serial(this, portName, 115200);

  oscP5 = new OscP5(this, 5005);
}

void draw() {
  background(255);
}

void keyPressed() {
  if (key == 'e') serial.write("ENABLE\n");
  if (key == 'd') serial.write("DISABLE\n");
}

void mousePressed() {
  float x = mouseX - width/2;
  float y = height/2 - mouseY;
  float angle = atan2(y, x) / PI * 2;
  if (angle < 0) angle += 4;

  int id = (int)floor(angle);
  if (millis() - lastMoved > intervalMoved) {
    serial.write("TEST " + str(id * 2) + "\n");
    lastMoved = millis();
  }
}

void oscEvent(OscMessage theOscMessage) {
  /* check if theOscMessage has the address pattern we are looking for. */

  if (theOscMessage.checkAddrPattern("/passing/plate/tip")==true) {
    int id = theOscMessage.get(0).intValue();
    if(id < 0 || 3 < id) return;
    if (millis() - lastMoved > intervalMoved) {
      serial.write("TEST " + str(id * 2) + "\n");
      lastMoved = millis();
    }
  }
}
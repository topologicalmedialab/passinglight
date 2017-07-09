#include "ofApp.h"

#include "ofxNI2.h"

//#include <omp.h>

class SayThread : public ofThread {
public:
    string s;
    void threadedFunction() {
//        system((string("say ") + s).c_str());
        stopThread();
    }
};
SayThread sayThread;

class TipThread : public ofThread {
public:
    int n;
    ofApp* app;
    void threadedFunction() {
        {
            ofxOscMessage m;
            m.setAddress("/passing/vvvv/tip");
            m.addIntArg(n);
            app->sender.sendMessage(m, false);

            sayThread.s = ofToString(n);
            sayThread.startThread(true);
        }
        ofSleepMillis(10 * 1000);
        {
            ofxOscMessage m;
            m.setAddress("/passing/vvvv/tip");
            m.addIntArg(0);
            app->sender.sendMessage(m, false);
            
            sayThread.s = "zero";
            sayThread.startThread(true);
        }
    }
};
TipThread tipThread;

ofxNI2::Device *device;
ofxNI2::IrStream ir;
ofxNI2::ColorStream color;
ofxNI2::DepthStream depth;

//--------------------------------------------------------------
void ofApp::setup()
{
    tipThread.app = this;

    ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	
    sender.setup("10.115.131.197", 15005);
    bSent = false;
    sentTime = -100;

    device = new ofxNI2::Device;
	device->setup();

	if (depth.setup(*device))
	{
		depth.setSize(640, 480);
		depth.setFps(30);
		depth.start();
	}

	//if (ir.setup(*device)) // only for xtion device (OpenNI2-FreenectDriver issue)
	//{
	//	ir.setSize(320, 240);
	//	ir.setFps(30);
	//	ir.start();
	//}
	
	if (color.setup(*device)) // only for kinect device
	{
		color.setSize(640, 480);
		color.setFps(30);
		color.start();
	}
	device->setEnableRegistration();

	mesh.setMode(OF_PRIMITIVE_POINTS);
	for (int i = 0; i < depth.getHeight(); i++) {
		for (int j = 0; j < depth.getWidth(); j++) {
			mesh.addVertex(ofVec3f());
		}
	}
}

void ofApp::exit()
{
	device->exit();
	delete device;
}

//--------------------------------------------------------------
void ofApp::update()
{
}

//--------------------------------------------------------------
void ofApp::draw()
{
    int count = 0;
    float weight = 0;
	//#pragma omp parallel for
	for (int i = 0; i < depth.getHeight(); i+=2) {
		for (int j = 0; j < depth.getWidth(); j+=2) {
			auto v = depth.getWorldCoordinateAt(j, i);
            
            if(v.z > 5000.0f * 0.6f) v.z = 1000000;
            else if (v.z > 0) {
                if(v.x < 0) {
                    count++;
                    if(v.y > 200)
                        weight += 1;
                    else if(v.y < -200)
                        weight += -1;
                    else
                        weight += 0;
                }
            }
            v.z *= -1;
            v.x *= -1;
			mesh.setVertex(i * depth.getWidth() + j, v);
		}
	}
    if(count > 0) weight = weight / count;
    
    if(bSent == false) {
        if(count > 1500 && ofGetElapsedTimef() - sentTime > 10) {
            if(weight < -0.2)
                tipThread.n = 1;
            else if(weight > 0.2)
                tipThread.n = 3;
            else
                tipThread.n = 4;
            tipThread.startThread(true);
            
            bSent = true;
            sentTime = ofGetElapsedTimef();
        }
    }
    else {
        if(ofGetElapsedTimef() - sentTime > 10) {
        }
        if(count < 1000) {
            bSent = false;
            sayThread.s = "reset";
            sayThread.startThread(true);
        }
    }
    
    ofBackground(ofMap(count, 0, 2000, 0, 255, true));
    //ofBackground(ofMap(weight, -2000, 2000, 0, 255, true));
    cam.begin();
    ofScale(2, 2);
    //ofRotateY(ofGetElapsedTimef() * 5);
	mesh.draw();
	cam.end();

	if (ofGetKeyPressed('s')) {
		ofSaveScreen(ofToDataPath(ofGetTimestampString() + ".png"));
		mesh.save(ofToDataPath(ofGetTimestampString()+".ply"));
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if (key == 'f') {
		ofToggleFullscreen();
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y)
{

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h)
{

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg)
{

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo)
{

}
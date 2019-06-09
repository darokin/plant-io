#include <iostream>
#include <vector>
//#include <strstream>

using namespace std;

#include "ofApp.h"
#include "Spectrum.h"

#define NB_CHANNELS_SEND	1

Spectrum* spectrum[NB_CHANNELS_SEND];
bool bDemo = false;

// == READ from arduino et PUSH dans l'ArrayList freqs
void feed() {
/*
  //for (int i = 0; i < NB_CHANNELS; i++)
  while (ser.available() > 0) {
    //str = str(ser.read());
    str = ser.readStringUntil('/');
    if (str != null) {
      str = str.substring(0, str.length() - 1);
	  //val = Integer.parseInt(str);
      val = abs(int(str))*2;
      //print("str = '" + str + "'\n");
      //print("val = " + val + "'\n");
      addFreq(val);
    }
    else {
      //print("noread");
    }
  }
*/
}

inline bool isInteger(const std::string & s) {
   if(s.empty() || (!isdigit(s[0]) && s[0] != '-')) return false;

   char* p;
   strtol(s.c_str(), &p, 10);

   return (*p == 0);
}

void split(const string &chaine, char delimiteur, vector<string> &elements)
{
	stringstream ss(chaine);
 	string sousChaine;
 	while (getline(ss, sousChaine, delimiteur))
 	{
 		elements.push_back(sousChaine);
 	}
}

void ofApp::readSerial(string& message) {
	//cout << "onNewMessage, message: '" << message << "'\n";

  if ((message[0] == '-' && message.size() > 6) || (isdigit(message[0]) && message.size() > 5)) {
		cout << "ERROR (integer too big) : '" << message << "'" << endl;
		return;
	}

	if (!isInteger(message)) {
		cout << "ERROR (value not integer) : '" << message << "'" << endl;
		return;
	}

	int msgChannel = 0;
	int msgValue = stoi(message);
	spectrum[msgChannel]->addData(msgValue);

	if (msgValue < valueMin) {
		valueMin = msgValue;
		cout << "New MIN value = '" << valueMin << "'\n";
	} else if (msgValue > valueMax) {
		valueMax = msgValue;
		cout << "New MAX value = '" << valueMax << "'\n";
	}


}

//--------------------------------------------------------------
void ofApp::setup(){
	//ofSetVerticalSync(true);
	ofBackground(0, 0, 0);
	//ofEnableSmoothing();
  //ofEnableAlphaBlending();
	ofSetWindowTitle("Spectrum example");

  ofSetRectMode(OF_RECTMODE_CORNER);//OF_RECTMODE_CENTER);

	ofSetFrameRate(120); // if vertical sync is off, we can go a bit fast... this caps the framerate at 60fps.

	// == Serial
	//serial.listDevices();
	//serial.setup(0, 9600);
	if (!bDemo) {
		serial.setup("/dev/ttyACM0", 9600);
		serial.startContinuousRead();
		ofAddListener(serial.NEW_MESSAGE, this, &ofApp::readSerial);
	}

	valueMin = 0;
	valueMax = 0;

	// == Spectrum
	spectrum[0] = new Spectrum(0, 0, 720, 550, 4, ofColor(124, 124, 124), 125);
	//spectrum[1] = new Spectrum(0, 200, 600, 200, 4, ofColor(124, 0, 88), 228);
	//spectrum[2] = new Spectrum(0, 400, 600, 200, 4, ofColor(211, 211, 211), 45);
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	int randval;
	for (int i = 0; i < NB_CHANNELS_SEND; i++) {
		if (bDemo) {
			randval = int(ofRandom(-MAX_VAL, MAX_VAL));
			cout << "RAND = '" << randval << "''" << endl;
			spectrum[i]->addData(randval);
		}
		spectrum[i]->drawGraph();
	}
	//cout << "Draw...." << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	// todo r1 et r2 pr avoir des ranges random et pas 1024..
	/*
	for (int i = 0; i < 512; i++) {
		spectrum[0]->addData(int(ofRandom(1024, 1128)));
		spectrum[1]->addData(int(ofRandom(1024, 1128)));
	}
	*/
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    //ofGetWidth();
    //ofGetHeight();
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}

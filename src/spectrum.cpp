#include "ofApp.h"
#include "spectrum.h"

/* ******************************************
SPECTRUM class - by Darokin (Adrien Rebuzzi)
made for graphing data from ECG/EKG or else
v0.1 08/06/2019
 *******************************************/

spectrum::spectrum(int _x, int _y, int _tx, int _ty, int _w, ofColor _colBG, int _colBar) {
	this->startX = _x;
	this->startY = _y;
	this->totalWidth = _tx;
	this->totalHeight = _ty;
	this->barWidth = _w;
	this->colBG = _colBG;
	this->tintBars = _colBar;

	this->totalWidth = (this->barWidth + BAR_SPACING) * NB_DATA;

	cout << "SPECTRUM [" << this->barWidth << " sur " << this->totalWidth << "]\t" << endl;
}

void spectrum::addData(int val) {
	this->freqs.insert(this->freqs.begin(), val);
	if (this->freqs.size() > NB_DATA) {
		this->freqs.pop_back();
	}
}

void spectrum::drawGraph() {
	ofSetColor(this->colBG);
	ofDrawRectangle(this->startX, this->startY, this->totalWidth, this->totalHeight);

	int tmpFreq;
	int tmpX;
	float tmpHeight;
	int col255;
	for (uint i = 0; i < this->freqs.size(); i++) {
		tmpFreq = this->freqs.at(i);
		tmpX = this->startX + ((this->barWidth+BAR_SPACING) * i);
		tmpHeight = int(float(abs(tmpFreq)) / float(MAX_VAL) * float(this->totalHeight/2 - BAR_SPACING));
		col255 = int(float(abs(tmpFreq)) / float(MAX_VAL) * float(255));
		ofSetColor(ofColor::fromHsb(tintBars, col255, 255));//ofMap(mouseX, 0, ofGetWidth(), 0, 255),
		if (tmpFreq > 0)
			ofDrawRectangle(tmpX, this->startY + (this->totalHeight/2) - tmpHeight, this->barWidth, tmpHeight);
		else
			ofDrawRectangle(tmpX, this->startY + (this->totalHeight/2), this->barWidth, tmpHeight);
	}
	ofDrawLine(this->startX, this->startY + (this->totalHeight/2), this->startX + this->barWidth, this->startY + (this->totalHeight/2));
}

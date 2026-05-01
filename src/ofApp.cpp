#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->noise_param = ofRandom(1000);
}
//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_param += ofMap(ofGetFrameNum() % 50, 0, 25, 0.1, 0.005);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int deg = 0; deg < 360; deg += 2) {

		float  radius = 200;
		auto target_radius = ofMap(ofNoise(cos(deg * DEG_TO_RAD) * 5, sin(deg * DEG_TO_RAD) * 5, this->noise_param), 0, 1, radius - 120, radius + 120);	
		auto target_location = glm::vec2(target_radius * cos(deg * DEG_TO_RAD), target_radius * sin(deg * DEG_TO_RAD));

		ofPushMatrix();
		ofTranslate(target_location);
		ofRotate(deg);

		ofDrawRectangle(glm::vec2(), 150, 8);

		ofPopMatrix();
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 500;
	if (ofGetFrameNum() > start) {

		std::ostringstream os;
		os << std::setw(4) << std::setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
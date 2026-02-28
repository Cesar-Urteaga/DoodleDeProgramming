#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 60;
	int param = ofGetFrameNum() % 50;
	int deg = param < 25 ? 0 : ofMap(param, 25, 50, 0, 90);

	for (int y = span * 0.5; y < ofGetWindowHeight(); y += span * 2) {

		for (int x = span * 0.5; x < ofGetWindowWidth(); x += span * 2) {

			ofPushMatrix();
			ofTranslate(x, y);

			ofRotate(deg);

			ofDrawRectangle(glm::vec2(), span, span);

			ofPopMatrix();

			ofPushMatrix();
			ofTranslate(x + span, y + span);

			ofRotate(deg);

			ofDrawRectangle(glm::vec2(), span, span);

			ofPopMatrix();

		}
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
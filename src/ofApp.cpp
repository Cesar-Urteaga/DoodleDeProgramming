#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int x = -300; x <= 300; x += 30) {

		for (int y = -300; y <= 300; y += 30) {

			ofPushMatrix();
			ofTranslate(x, y);

			ofNoFill();
			ofDrawRectangle(0, 0, 30, 30);

			auto distance = glm::distance(glm::vec2(), glm::vec2(x, y));

			int deg_x = ofMap(ofNoise(distance * 0.005 + ofGetFrameNum() * 0.025), 0, 1, -360, 360);
			int deg_y = ofMap(ofNoise(distance * 0.005 + ofGetFrameNum() * 0.025), 0, 1, -360, 360);

			ofRotateY(deg_y);
			ofRotateX(deg_x);

			ofFill();
			ofDrawCircle(0, 0, 10, 10);

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
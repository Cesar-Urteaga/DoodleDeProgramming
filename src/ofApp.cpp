#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(0);
	ofEnableDepthTest();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int x = -300; x <= 300; x += 20) {

		for (int y = -300; y <= 300; y += 20) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto distance = glm::distance(glm::vec2(), glm::vec2(x, y));

			int deg_x = ofMap(ofNoise(distance * 0.005 + ofGetFrameNum() * 0.025), 0, 1, -360, 360);
			int deg_y = ofMap(ofNoise(distance * 0.005 + ofGetFrameNum() * 0.025), 0, 1, -360, 360);

			deg_x = (deg_x / 45) * 45;
			deg_y = (deg_y / 45) * 45;

			ofRotateY(deg_y);
			ofRotateX(deg_x);

			ofNoFill();
			ofDrawRectangle(0, 0, 20, 20);

			ofFill();
			ofDrawRectangle(0, 0, 13, 13);

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
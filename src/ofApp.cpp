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

	this->noise_param += 0.005;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int deg = 0; deg < 360; deg += 8) {

		for (int len = 50; len <= 150; len += 50) {

			float  radius = 200;
			int width = ofMap(len, 50, 150, 3, 10);
			auto target_radius = ofMap(ofNoise(cos(deg * DEG_TO_RAD) * 3, sin(deg * DEG_TO_RAD) * 3, len * 0.015 + this->noise_param), 0, 1, radius - 80, radius + 80);
			auto target_location = glm::vec2(target_radius * cos(deg * DEG_TO_RAD), target_radius * sin(deg * DEG_TO_RAD));

			ofPushMatrix();
			ofTranslate(target_location);
			ofRotate(deg);

			len == 50 ? ofFill() : ofNoFill();

			ofDrawRectangle(glm::vec2(), len, width);

			ofPopMatrix();
		}
	}

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
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
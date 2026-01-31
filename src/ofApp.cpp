#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.01;
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 0; x < ofGetWindowWidth(); x += 1) {

		for (int y = 0; y < ofGetWindowHeight(); y += 1) {

			auto location = glm::vec2(x, y);
			auto noise_value = ofNoise(x * 0.0075, y * 0.0075, this->noise_param );

			if ((noise_value > 0.32 && noise_value < 0.38) || (noise_value > 0.62 && noise_value < 0.68)) {

				ofSetColor(0);
				ofDrawRectangle(location, 1, 1);
			}
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
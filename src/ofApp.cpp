#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.002;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofColor color;
	for (int x = 0; x < ofGetWindowWidth(); x += 1) {

		for (int y = 0; y < ofGetWindowHeight(); y += 1) {

			auto location = glm::vec2(x, y);
			auto noise_value = ofNoise(x * 0.004, y * 0.004, this->noise_param);

			for (float i = 0; i < 10; i += 1) {

				if (noise_value > i * 0.1 + 0.042 && noise_value < i * 0.1 + 0.058) {

					ofSetColor(239);

					ofDrawRectangle(location, 1, 1);
				}
			}
		}
	}

	for (int x = 0; x < ofGetWindowWidth(); x += 1) {

		for (int y = 0; y < ofGetWindowHeight(); y += 1) {

			auto location = glm::vec2(x, y);
			auto noise_value = ofNoise(x * 0.004, y * 0.004, this->noise_param);

			for (float i = 0; i < 10; i += 1) {

				if (noise_value > i * 0.1 + 0.048 && noise_value < i * 0.1 + 0.052) {

					color.setHsb(ofMap(i, 0, 10, 0, 255), 255, 255);
					ofSetColor(color);

					ofDrawRectangle(location, 1, 1);
				}
			}
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 5;
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
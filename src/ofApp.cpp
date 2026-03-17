#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSetRandomSeed(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int span = 2;
	auto seed = ofRandom(1000);
	ofColor color;

	for (int i = 0; i < 5; i++) {

		seed += 0.05;
		color.setHsb(ofMap(i, 0, 5, 0, 255), 255, 255, 64);
		ofSetColor(color);

		for (int x = 0; x < ofGetWidth(); x += span) {

			for (int y = 0; y < ofGetHeight(); y += span) {

				auto noise_value = ofNoise(seed, x * 0.01, y * 0.0025 + ofGetFrameNum() * 0.035);

				if (y > ofGetHeight() * 0.85) {

					noise_value += ofMap(y, ofGetHeight() * 0.85, ofGetHeight(), 0.25, 1);
				}
				else if (y > ofGetHeight() * 0.65) {

					noise_value += ofMap(y, ofGetHeight() * 0.65, ofGetHeight() * 0.85, 0, 0.25);
				}
				else if (y < ofGetHeight() * 0.45) {

					noise_value += ofMap(y, 0, ofGetHeight() * 0.45, -0.65, 0);
				}

				if (noise_value > 0.35) {

					ofDrawRectangle(glm::vec2(x, y), span, span);
				}
			}
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 30;
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
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	int size = 10;
	for (int x = -150; x <= 150; x += size) {

		for (int y = -400; y <= 400; y += size) {

			for (int z = -150; z <= 150; z += size) {

				auto noise_value = ofNoise(x * 0.003, y * 0.003, z * 0.003, ofGetFrameNum() * 0.03);
				if (0.45 <= noise_value && noise_value <= 0.55) {

					ofSetColor(39);
					ofFill();
					ofDrawBox(glm::vec3(x, y, z), size * 0.95);

					ofSetColor(139, 139, 239);
					ofNoFill();
					ofDrawBox(glm::vec3(x, y, z), size * 0.95);
				}
			}
		}
	}

	ofSetColor(239);
	ofDrawBox(300 + size, 800 + size, 300 + size);

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 250;
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
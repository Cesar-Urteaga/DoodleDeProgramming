#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto numberOfActor = 120;

	auto noise_param = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < numberOfActor; i++) {

		ofPushMatrix();

		auto rotate_deg = ofMap(ofNoise(noise_param.x, i * 0.01 - ofGetFrameNum() * 0.025), 0, 1, -20, 20);
		ofRotateY(rotate_deg);

		auto radius = 50 + i * 10;
		auto deg = ofMap(ofNoise(noise_param.y, i * 0.1 + ofGetFrameNum() * 0.0025), 0, 1, 0, 1440);
		auto len = 150;

		ofSetColor(255);
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(radius * cos((deg + k * 0.25) * DEG_TO_RAD), radius * sin((deg + k * 0.25) * DEG_TO_RAD));
			ofDrawCircle(location, 7);
		}

		ofSetColor(0);
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(radius * cos((deg + k * 0.25) * DEG_TO_RAD), radius * sin((deg + k * 0.25) * DEG_TO_RAD));
			ofDrawCircle(location, 5);
		}

		ofPopMatrix();
	}

	this->cam.end();

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
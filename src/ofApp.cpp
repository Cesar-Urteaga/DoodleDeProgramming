#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	auto numberOfActor = 80;

	for (int i = 0; i < numberOfActor; i++) {

		ofPushMatrix();
		ofRotateY(ofRandom(-20, 20));

		auto radius = 50 + i * 5;
		auto speed = ofRandom(1, 2);
		speed *= ofRandom(1) < 0.5 ? 1 : -1;
		auto deg = ofRandom(360) + ofGetFrameNum() * speed;
		auto len = ofRandom(150, 500);

		ofSetColor(0, 0, 255);
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(radius * cos((deg + k * 0.25) * DEG_TO_RAD), radius * sin((deg + k * 0.25) * DEG_TO_RAD));
			ofDrawCircle(location, 3);
		}

		ofSetColor(255);
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(radius * cos((deg + k * 0.25) * DEG_TO_RAD), radius * sin((deg + k * 0.25) * DEG_TO_RAD));
			ofDrawCircle(location, 2);
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
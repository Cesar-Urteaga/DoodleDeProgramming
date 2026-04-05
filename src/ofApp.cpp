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

	ofTranslate(ofGetWindowSize() * 0.5);

	auto numberOfActor = 120;
	auto len = 100;

	for (int i = 0; i < numberOfActor; i++) {

		auto radius = 100 + i * 2;
		auto speed = ofRandom(1, 2);
		speed *= ofRandom(1) < 0.5 ? 1 : -1;
		auto deg = i + ofGetFrameNum() * speed;

		ofSetColor(239);
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(radius * cos((deg + k * 0.5) * DEG_TO_RAD), radius * sin((deg + k * 0.5) * DEG_TO_RAD));
			ofDrawCircle(location, 10);
		}

		ofColor color;
		i % 2 == 0 ? color.setHsb(0, 130, 255) : color.setHsb(180, 200, 255);

		ofSetColor(color);
		for (int k = 0; k < len; k++) {

			auto location = glm::vec2(radius * cos((deg + k * 0.5) * DEG_TO_RAD), radius * sin((deg + k * 0.5) * DEG_TO_RAD));
			ofDrawCircle(location, 8);
		}
	}

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
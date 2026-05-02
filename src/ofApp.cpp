#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);

	this->noise_param = ofRandom(1000);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	if (ofGetFrameNum() % 50 < 25) {

		//this->noise_param += ofMap(ofGetFrameNum() % 50, 0, 25, 0.1, 0.005);
	}

	this->noise_param += 0.01;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));

	for (int deg = 0; deg < 360; deg += 2) {

		float  radius = 200;
		auto target_radius = ofMap(ofNoise(deg % 4 == 0 ? noise_seed.x : noise_seed.y, cos(deg * DEG_TO_RAD) * 0.8, sin(deg * DEG_TO_RAD) * 0.8, this->noise_param), 0, 1, radius - 80, radius + 80);	
		auto target_location = glm::vec2(target_radius * cos(deg * DEG_TO_RAD), target_radius * sin(deg * DEG_TO_RAD));

		ofPushMatrix();
		ofTranslate(target_location);
		ofRotate(deg);

		ofDrawRectangle(glm::vec2(), 120, 2);

		ofPopMatrix();
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
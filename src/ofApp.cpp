#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto radius = 250;
	ofColor color;
	for (int k = 0; k < 180; k++) {

		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto max_size = ofMap(k, 0, 180, 12, 12);

		ofSetColor(239);
		for (int i = 0; i < 25; i++) {

			auto deg = (ofGetFrameNum() + i) * 0.36 + k * 2;
			auto base_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

			auto location = glm::vec2(
				ofMap(ofNoise(noise_seed.x, k + ofGetFrameNum() * 0.035 + i * 0.03), 0, 1, -40, 40),
				ofMap(ofNoise(noise_seed.y, k + ofGetFrameNum() * 0.035 + i * 0.03), 0, 1, -40, 40));

			location += base_location;
			auto size = ofMap(i, 0, 25, 3, max_size + 3); 

			ofDrawCircle(location, size);
		}

		color.setHsb(ofMap(k, 0, 180, 0, 255), 255, 255);

		ofSetColor(color);
		for (int i = 0; i < 25; i++) {

			auto deg = (ofGetFrameNum() + i) * 0.36 + k * 2;
			auto base_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

			auto location = glm::vec2(
				ofMap(ofNoise(noise_seed.x, k + ofGetFrameNum() * 0.035 + i * 0.03), 0, 1, -40, 40),
				ofMap(ofNoise(noise_seed.y, k + ofGetFrameNum() * 0.035 + i * 0.03), 0, 1, -40, 40));

			location += base_location;
			auto size = ofMap(i, 0, 25, 1, max_size);

			ofDrawCircle(location, size);
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 770;
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
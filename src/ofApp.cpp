#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(255);
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	float start_radius = 0;
	float end_radius = 600;
	float noise_gap = ofMap(ofNoise(39, ofGetFrameNum() * 0.005), 0, 1, 0, 0.1);

	for (float deg = 0; deg < 360; deg += 0.25) {

		for (float radius = start_radius; radius < end_radius; radius += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec4(noise_location * 5, radius * 0.003, ofGetFrameNum() * 0.05));

			if (noise_value > 0.5 - noise_gap && noise_value < 0.5 + noise_gap) {

				ofDrawCircle(location, 1);
			}
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 10;
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
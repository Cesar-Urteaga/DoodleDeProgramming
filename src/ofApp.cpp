#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(39);
	ofSetCircleResolution(60);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->noise_step += 0.25;
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	float start_radius = 5;
	float end_radius = 600;

	ofFill();
	ofSetColor(39, 39, 239);
	ofSeedRandom(39);
	for (float deg = 0; deg < 360; deg += 5) {

		auto scale = ofRandom(0.01, 2);

		for (float radius = start_radius; radius < end_radius; radius += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_location * 10, radius * 0.025 + this->noise_step * scale));

			if (noise_value < 0.4) {

				ofDrawCircle(location, 5);
			}
		}
	}

	for (float deg = 0; deg < 360; deg += 0.5) {

		ofDrawCircle(glm::vec2((start_radius - 8) * cos(deg * DEG_TO_RAD), (start_radius - 8) * sin(deg * DEG_TO_RAD)), 3);
	}

	ofSetColor(255);
	ofSeedRandom(39);
	for (float deg = 0; deg < 360; deg += 5) {

		auto scale = ofRandom(0.01, 2);

		for (float radius = start_radius; radius < end_radius; radius += 1) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_location * 10, radius * 0.025 + this->noise_step * scale));

			if (noise_value < 0.4) {

				ofDrawCircle(location, 1);
			}
		}
	}

	for (float deg = 0; deg < 360; deg += 0.5) {

		ofDrawCircle(glm::vec2((start_radius - 8) * cos(deg * DEG_TO_RAD), (start_radius - 8) * sin(deg * DEG_TO_RAD)), 1);
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 50;
	if (ofGetFrameNum() > start) {

		std::ostringstream  os;
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
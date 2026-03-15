#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(1.25);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofRotate(45);

	ofColor color;
	for (int k = 0; k < 360; k++) {

		auto radius = 350;
		auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
		auto deg = ofGetFrameNum() * 0.72 + k;
		auto base_location = this->make_point(radius, deg);

		auto location = glm::vec2(
			ofMap(ofNoise(noise_seed.x, (k + ofGetFrameNum()) * 0.005), 0, 1, -40, 40),
			ofMap(ofNoise(noise_seed.y, (k + ofGetFrameNum()) * 0.005), 0, 1, -40, 40));

		location += base_location;

		color.setHsb(ofMap(k, 0, 360, 0, 255), 130, 255);
		auto size = ofMap(k, 0, 360, 0, 25);

		ofSetColor(ofColor(39));
		ofFill();
		ofDrawCircle(location, size);

		ofSetColor(color);
		ofNoFill();
		ofDrawCircle(location, size);
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
glm::vec2 ofApp::make_point(int radius, int deg) {

	deg = deg % 360;

	int deg_a = (deg / 90) * 90;
	int deg_b = deg_a + 90;

	int remainder = deg % 90;
	int diff = deg - deg_a;

	auto point_a = glm::vec2(radius * cos(deg_a * DEG_TO_RAD), radius * sin(deg_a * DEG_TO_RAD));
	auto point_b = glm::vec2(radius * cos(deg_b * DEG_TO_RAD), radius * sin(deg_b * DEG_TO_RAD));
	auto distance = point_b - point_a;

	return point_a + (distance / 90) * diff;
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
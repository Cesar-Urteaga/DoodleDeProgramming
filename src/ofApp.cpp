#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
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

	auto small_radius = 0.f;
	auto noise_seed = glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000));
	for (auto radius = 50; radius <= 360; radius += small_radius * 2) {

		auto deg_span = 10;
		small_radius = (radius * 2 * PI) / 360 * deg_span * 0.5;
		auto size = (small_radius * 2) / sqrt(3);
		auto deg_start = 0;

		for (int deg = deg_start; deg < deg_start + 360; deg += deg_span) {

			auto location = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);

			auto rotate_x = ofMap(ofNoise(noise_seed.x, radius + 0.001 - ofGetFrameNum() * 0.005), 0, 1, -360, 360);
			auto rotate_y = ofMap(ofNoise(noise_seed.y, radius + 0.001 - ofGetFrameNum() * 0.005), 0, 1, -360, 360);
			auto rotate_z = ofMap(ofNoise(noise_seed.z, radius + 0.001 - ofGetFrameNum() * 0.005), 0, 1, -360, 360);

			ofPushMatrix();
			ofTranslate(location);

			ofRotateZ(rotate_z);
			ofRotateY(rotate_y);
			ofRotateX(rotate_x);

			ofFill();
			ofSetColor(239);
			ofDrawBox(size);

			ofNoFill();
			ofSetColor(39);
			ofDrawBox(size);

			ofPopMatrix();
		}
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
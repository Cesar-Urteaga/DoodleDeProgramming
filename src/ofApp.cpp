#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
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

	int radius = 300;
	bool flag = true;

	float noise_seed_x = ofRandom(1000);
	float noise_seed_y = ofRandom(1000);
	float noise_seed_z = ofRandom(1000);
	for (int deg = 0; deg < 360; deg += 8) {

		auto location_1 = glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0);
		auto location_2 = glm::vec3(radius * 0.3 * cos(deg * DEG_TO_RAD), radius * 0.3 * sin(deg * DEG_TO_RAD), 0);

		auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_z, location_1.x * 0.0003, location_1.y * 0.0003, ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 0, 1));
		auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, location_1.x * 0.0003, location_1.y * 0.0003, ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
		auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, location_1.x * 0.0003, location_1.x * 0.0003, ofGetFrameNum() * 0.005), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));

		location_2 = glm::vec4(location_2, 0) * rotation_y * rotation_x;

		ofDrawLine(location_1, location_2);

		ofDrawSphere(location_1, 3);
		ofDrawSphere(location_2, 2);
	}

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
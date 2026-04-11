#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	ofEnableDepthTest();
	ofSetCircleResolution(72);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_SUBTRACT);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
	this->line.clear();

	ofColor color;
	auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));
	for (int i = 0; i < 4; i++) {

		auto rotation_z = glm::rotate(glm::mat4(), ofMap(i, 0, 4, 0, 360) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
		color.setHsb(ofMap(i, 0, 4, 0, 255), 230, 200);

		for (int x = -300; x <= 300; x += 2) {

			auto base_y = ofMap(ofNoise(noise_seed.x, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -400, 400);
			auto base_z = ofMap(ofNoise(noise_seed.y, x * 0.001 + (ofGetFrameNum() + i * 10000) * 0.002), 0, 1, -400, 400);

			auto y = base_y + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -80, 80);
			auto z = base_z + ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.005), 0, 1, -80, 80);
			auto location = glm::vec3(x, y, z);
			location = glm::length(location) > 280 ? glm::normalize(location) * 280 : location;
			location = glm::vec4(location, 0) * rotation_z;
			location.z = 0;

			this->line.addVertex(location);
			this->line.addColor(color);
		}
	}

	for (int i = 0; i < this->line.getNumVertices(); i++) {

		for (int k = i + 1; k < this->line.getNumVertices(); k++) {

			if (glm::distance(this->line.getVertex(i), this->line.getVertex(k)) < 20) {

				this->line.addIndex(i);	this->line.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofFill();
	for (int i = 0; i < this->line.getNumVertices(); i++) {

		ofSetColor(this->line.getColor(i));
		ofDrawCircle(this->line.getVertex(i), 1.5);
	}

	ofSetColor(39);
	ofNoFill();
	ofDrawCircle(glm::vec2(), 283);

	this->line.drawWireframe();

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
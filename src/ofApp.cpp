#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);

	ofEnableDepthTest();
	ofSetLineWidth(3);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateZ(ofGetFrameNum() * 1.44);

	int width = 42;
	int height = 42;
	int len = 5;

	for (int x = -300; x <= 300; x += 50) {

		for (int y = -300; y <= 300; y += 50) {

			for (int z = 0; z <= 300; z += 15) {

				auto noise_param = ofNoise(x * 0.003, y * 0.003, z * 0.0005 + ofGetFrameNum() * 0.015);

				if (noise_param > 0.4 && noise_param < 0.6) { continue; }

				ofPushMatrix();
				ofTranslate(x, y, z);

				auto alpha = ofMap(z, 0, 300, 255, 255);

				ofFill();
				ofSetColor(ofColor(255, alpha));

				ofBeginShape();

				ofVertex(glm::vec2(width * -0.5, height * -0.5));
				ofVertex(glm::vec2(width * 0.5, height * -0.5));
				ofVertex(glm::vec2(width * 0.5, height * 0.5));
				ofVertex(glm::vec2(width * -0.5, height * 0.5));

				ofEndShape(true);

				ofNoFill();
				ofSetColor(ofColor(0, alpha));

				ofBeginShape();

				ofVertex(glm::vec2(width * -0.5, height * -0.5));
				ofVertex(glm::vec2(width * 0.5, height * -0.5));
				ofVertex(glm::vec2(width * 0.5, height * 0.5));
				ofVertex(glm::vec2(width * -0.5, height * 0.5));

				ofEndShape(true);

				ofPopMatrix();
			}
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
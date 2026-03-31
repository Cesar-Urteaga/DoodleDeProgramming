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
	ofRotateY(180);
	ofRotateY(ofGetFrameNum() * 1.44);

	int width = 200;
	int height = 200;
	int len = 30;
	ofColor color;
	for (int z = -280; z <= 280; z += 10) {

		color.setHsb(ofMap(z, -280, 280, 0, 255), 130, 255);

		ofPushMatrix();
		ofTranslate(0, 0, z);
		ofRotate(ofMap(ofNoise((z + 300) * 0.003 + ofGetFrameNum() * 0.01), 0, 1, -360, 360));

		ofFill();
		ofSetColor(39);

		ofBeginShape();

		ofVertex(glm::vec2(width * -0.5, height * -0.5));
		ofVertex(glm::vec2(width * 0.5, height * -0.5));
		ofVertex(glm::vec2(width * 0.5, height * 0.5));
		ofVertex(glm::vec2(width * -0.5, height * 0.5));

		ofNextContour(true);

		ofVertex(glm::vec2(width * -0.5 + len, height * -0.5 + len));
		ofVertex(glm::vec2(width * 0.5 - len, height * -0.5 + len));
		ofVertex(glm::vec2(width * 0.5 - len, height * 0.5 - len));
		ofVertex(glm::vec2(width * -0.5 + len, height * 0.5 - len));

		ofEndShape(true);

		ofNoFill();
		ofSetColor(color);

		ofBeginShape();

		ofVertex(glm::vec2(width * -0.5, height * -0.5));
		ofVertex(glm::vec2(width * 0.5, height * -0.5));
		ofVertex(glm::vec2(width * 0.5, height * 0.5));
		ofVertex(glm::vec2(width * -0.5, height * 0.5));

		ofNextContour(true);

		ofVertex(glm::vec2(width * -0.5 + len, height * -0.5 + len));
		ofVertex(glm::vec2(width * 0.5 - len, height * -0.5 + len));
		ofVertex(glm::vec2(width * 0.5 - len, height * 0.5 - len));
		ofVertex(glm::vec2(width * -0.5 + len, height * 0.5 - len));

		ofEndShape(true);

		ofPopMatrix();
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
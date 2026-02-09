#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int m = 0; m < 7; m++) {

		for (int k = 0; k < 9; k++) {

			ofRotate(10);

			vector<glm::vec2> vertices;
			for (int i = 0; i < 65; i++) {

				auto radius = ofMap(sin((ofGetFrameNum() + i) * 0.314 * 0.75), -1, 1, 25 + m * 75, 60 + m * 75);
				auto deg = (ofGetFrameNum() + i) * 4;
				auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));

				vertices.push_back(location);
			}

			ofSetColor(ofMap(k, 0, 9, 39, 239), 39, 39);

			ofNoFill();
			ofBeginShape();
			ofVertices(vertices);
			ofEndShape();
		}
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
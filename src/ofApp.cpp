#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	int radius = 100;

	ofColor color;
	for (int i = 0; i < 5; i++) {

		vector<glm::vec2> vertices;
		for (float deg = 0; deg < 360; deg += 0.3) {

			auto location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec4(i * 0.2, location * 0.1, ofGetFrameNum() * 0.005));
			location *= noise_value > 0.5 ? ofMap(noise_value, 0.5, 1, 0.5, 4) : 0.5;

			vertices.push_back(location);
		}

		color.setHsb(ofMap(i, 0, 5, 0, 255), 255, 255);

		ofFill();
		ofSetColor(color, 64);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(color);
		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
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
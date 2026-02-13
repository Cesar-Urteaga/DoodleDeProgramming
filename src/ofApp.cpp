#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);
	ofNoFill();
	ofSetCircleResolution(60);

	this->seed_value = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(this->seed_value);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto center = glm::vec2(ofGetWindowSize() * 0.5);
	auto radius = 340;
	auto flag = ofRandom(100) < 50 ? true : false;

	vector<glm::vec2> vertices;
	for (int draw_radius = radius; draw_radius > 5;) {

		vertices.push_back(center);

		flag = !flag;

		auto tmp_radius = draw_radius;
		draw_radius *= 0.8;

		auto deg = ofMap(ofNoise(center.x * 0.0005, center.y * 0.0005, ofGetFrameNum() * 0.005), 0, 1, -720, 720);
		auto center_radius = tmp_radius - draw_radius;
		center = center + glm::vec2(center_radius * cos(deg * DEG_TO_RAD), center_radius * sin(deg * DEG_TO_RAD));
	}

	ofBeginShape();
	ofVertices(vertices);
	ofEndShape();

	for (auto& vertex : vertices) {

		ofDrawCircle(vertex, 5);
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 1;
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
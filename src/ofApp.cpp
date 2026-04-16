#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(300, 3);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.36);

	auto radius = 300;

	for (int i = 0; i < this->triangle_list.size(); i++) {

		glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.005, avg.z * 0.005, avg.y * 0.005 + ofGetFrameNum() * 0.025);
		noise_value = noise_value > 0.6 ? 1 : ofMap(noise_value, 0.6, 0, 1, 0);
		auto len = ofMap(abs(noise_value - 0.5), 0, 0.5, 1, 0);

		ofFill();
		ofSetColor(39);

		ofBeginShape();
		ofVertex(this->triangle_list[i].getVertex(0));
		ofVertex(this->triangle_list[i].getVertex(1));
		ofVertex(this->triangle_list[i].getVertex(2));

		ofNextContour(true);

		ofVertex((this->triangle_list[i].getVertex(0) - avg) * len + avg);
		ofVertex((this->triangle_list[i].getVertex(1) - avg) * len + avg);
		ofVertex((this->triangle_list[i].getVertex(2) - avg) * len + avg);

		ofEndShape(true);

		ofNoFill();
		ofSetColor(239);

		ofBeginShape();
		ofVertex(this->triangle_list[i].getVertex(0));
		ofVertex(this->triangle_list[i].getVertex(1));
		ofVertex(this->triangle_list[i].getVertex(2));

		ofNextContour(true);

		ofVertex((this->triangle_list[i].getVertex(0) - avg) * len + avg);
		ofVertex((this->triangle_list[i].getVertex(1) - avg) * len + avg);
		ofVertex((this->triangle_list[i].getVertex(2) - avg) * len + avg);

		ofEndShape(true);
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
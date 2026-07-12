#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 4);
	this->sphere_mesh = ico_sphere.getMesh();

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.005;

	this->draw_sphere_mesh = this->sphere_mesh;

	for (auto& vertex : this->draw_sphere_mesh.getVertices()) {

		auto noise_value = ofNoise(glm::vec4(vertex * 0.025, noise_param));
		auto noise_param = (noise_value < 0.35 ? 1 : ofMap(noise_value, 0.35, 1, 1, 6));
		noise_param = std::pow(1.5, noise_param);
		auto noise_radius = 150 * noise_param;

		vertex = glm::normalize(vertex) * noise_radius;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.5);

	ofSetColor(0, 0, 128);
	this->draw_sphere_mesh.draw();

	ofSetColor(128, 128, 255);
	this->draw_sphere_mesh.drawWireframe();

	this->cam.end();

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
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
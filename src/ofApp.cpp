#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(280, 4);
	this->mesh = ico_sphere.getMesh();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		this->param_list.push_back(0);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->draw_mesh = this->mesh;
	this->line_mesh = this->mesh;

	for (int i = 0; i < this->draw_mesh.getNumVertices(); i++) {

		auto vertex = this->draw_mesh.getVertex(i);
		auto noise_value = ofNoise(glm::vec4(vertex * 0.02, ofGetFrameNum() * 0.0005));

		if (noise_value <= 0.43 || noise_value >= 0.57) {

			vertex = glm::normalize(vertex) * 0;
		}

		this->draw_mesh.setVertex(i, vertex);
		this->line_mesh.setVertex(i, vertex);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	ofSetColor(39);
	this->draw_mesh.draw();

	ofSetColor(239);
	this->line_mesh.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 5;
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
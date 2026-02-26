#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(0.5);
	ofEnableDepthTest();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	vector<float> min_distance_list;
	this->mesh.clear();

	for (int i = 0; i < 1200; i++) {

		auto vertex = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -160, 160),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -160, 160),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -160, 160));
		this->mesh.addVertex(vertex);
		min_distance_list.push_back(40);
	}

	for (auto& vertex : this->mesh.getVertices()) {

		auto len = glm::length(vertex);
		if (len < 150) {

			vertex = glm::normalize(vertex) * 150;
		}
	}


	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = 0; k < this->mesh.getNumVertices(); k++) {

			if (i == k) { continue; }

			auto distance = glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k));
			if (distance < 30) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);

				if (distance < min_distance_list[i]) {

					min_distance_list[i] = distance;
				}
			}
		}

		this->mesh.addColor(ofColor(255, ofMap(min_distance_list[i], 0, 30, 255, 0)));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 0.72);

	this->mesh.draw();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 1.5);
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
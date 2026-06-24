#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(150, 4);
	this->noise_value = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.03, avg.y * 0.03, avg.z * 0.03, this->noise_value);

		float noise_radius = 150;
		noise_radius = ofMap(noise_value, 0, 1, 50, 450);

		int index = this->mesh.getNumVertices();

		this->mesh.addVertex(glm::normalize(avg) * (noise_radius + 100));
		this->mesh.addVertex(glm::normalize(triangle.getVertex(0)) * noise_radius);
		this->mesh.addVertex(glm::normalize(triangle.getVertex(1)) * noise_radius);
		this->mesh.addVertex(glm::normalize(triangle.getVertex(2)) * noise_radius);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 0);
		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 3);

		this->mesh.addIndex(index + 1);
		this->mesh.addIndex(index + 2);
		this->mesh.addIndex(index + 3);
	}

	this->noise_value += 0.03;
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.43);
	ofRotateY(ofGetFrameNum() * 0.65);

	ofSetColor(39);
	this->mesh.drawFaces();

	ofSetColor(239);
	this->mesh.drawWireframe();

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
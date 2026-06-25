#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofEnableDepthTest();

	this->ico_sphere = ofIcoSpherePrimitive(150, 2);
	this->noise_value = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	auto triangle_list = this->ico_sphere.getMesh().getUniqueFaces();

	for (auto& triangle : triangle_list) {

		glm::vec3 avg = (triangle.getVertex(0) + triangle.getVertex(1) + triangle.getVertex(2)) / 3;
		auto noise_value = ofNoise(avg.x * 0.01, avg.y * 0.01, avg.z * 0.01, this->noise_value);

		float noise_radius = 150;
		noise_radius = ofMap(noise_value, 0, 1, 50, 450);

		int index = this->mesh.getNumVertices();

		this->mesh.addVertex(glm::normalize(avg) * noise_radius);
		this->mesh.addVertex(triangle.getVertex(0));
		this->mesh.addVertex(triangle.getVertex(1));
		this->mesh.addVertex(triangle.getVertex(2));

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

	ofSetColor(39, 39, 255, 128);
	this->mesh.drawFaces();

	ofSetColor(255);
	this->mesh.drawWireframe();

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
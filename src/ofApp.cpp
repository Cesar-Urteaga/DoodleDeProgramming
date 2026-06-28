#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame_mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 25) {

		this->noise_param += ofMap(ofGetFrameNum() % 50, 0, 25, 0.15, 0.01);
	}

	this->face_mesh.clear();
	this->frame_mesh.clear();

	auto span = 8;
	auto max_height = 450;
	auto radius = 200;
	for (auto x = -300; x <= 300; x += span) {

		for (auto y = -300; y <= 300; y += span) {

			auto distance = glm::length(glm::vec2(x, y));
			if (distance > radius - 50 && distance < radius + 50) {

				auto power = ofMap(abs(distance - radius), 0, 30, 1, 0.1);
				auto len = ofMap(ofNoise(x * 0.0085, y * 0.0085, noise_param), 0, 1, -max_height * power, max_height * power);
				this->setBoxToMesh(this->face_mesh, this->frame_mesh, glm::vec3(x, y, len * 0.5), span, span, len);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	
	ofRotateX(ofGetFrameNum() * 1.44);

	this->face_mesh.drawFaces();
	this->frame_mesh.drawWireframe();

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
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float size) {

	this->setBoxToMesh(face_target, frame_target, location, size, size, size);
}

//--------------------------------------------------------------
void ofApp::setBoxToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float height, float width, float depth) {

	auto face_color = ofColor(0);
	auto frame_color = ofColor(255);

	int index = face_target.getVertices().size();

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * 0.5 * 0.99, depth * 0.5 * 0.99));

	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * -0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * 0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));
	face_target.addVertex(location + glm::vec3(width * -0.5 * 0.99, height * -0.5 * 0.99, depth * 0.5 * 0.99));

	for (int i = 0; i < 8; i++) {

		face_target.addColor(face_color);
	}

	face_target.addIndex(index + 0); face_target.addIndex(index + 1); face_target.addIndex(index + 2);
	face_target.addIndex(index + 0); face_target.addIndex(index + 2); face_target.addIndex(index + 3);

	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 4); face_target.addIndex(index + 6); face_target.addIndex(index + 7);

	face_target.addIndex(index + 0); face_target.addIndex(index + 4); face_target.addIndex(index + 1);
	face_target.addIndex(index + 4); face_target.addIndex(index + 5); face_target.addIndex(index + 1);

	face_target.addIndex(index + 1); face_target.addIndex(index + 5); face_target.addIndex(index + 6);
	face_target.addIndex(index + 6); face_target.addIndex(index + 2); face_target.addIndex(index + 1);

	face_target.addIndex(index + 2); face_target.addIndex(index + 6); face_target.addIndex(index + 7);
	face_target.addIndex(index + 7); face_target.addIndex(index + 3); face_target.addIndex(index + 2);

	face_target.addIndex(index + 3); face_target.addIndex(index + 7); face_target.addIndex(index + 4);
	face_target.addIndex(index + 4); face_target.addIndex(index + 0); face_target.addIndex(index + 3);

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * 0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * 0.5, depth * 0.5));

	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * -0.5));
	frame_target.addVertex(location + glm::vec3(width * 0.5, height * -0.5, depth * 0.5));
	frame_target.addVertex(location + glm::vec3(width * -0.5, height * -0.5, depth * 0.5));

	for (int i = 0; i < 8; i++) {

		frame_target.addColor(frame_color);
	}

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 1);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 0);

	frame_target.addIndex(index + 4); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 5); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 7);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 4);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 4);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 2); frame_target.addIndex(index + 6);
	frame_target.addIndex(index + 3); frame_target.addIndex(index + 7);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
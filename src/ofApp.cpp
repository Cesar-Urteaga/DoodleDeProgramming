#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	float span = 50;
	for (int x = -1200; x <= 1200; x += span) {

		for (int y = -2000; y <= 2000; y += span) {

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(x, y, 0));
			vertices.push_back(glm::vec3(x + span, y, 0));
			vertices.push_back(glm::vec3(x + span, y + span, 0));
			vertices.push_back(glm::vec3(x, y + span, 0));

			this->face.addVertices(vertices);

			this->face.addIndex(this->face.getNumVertices() - 1);
			this->face.addIndex(this->face.getNumVertices() - 4);
			this->face.addIndex(this->face.getNumVertices() - 3);

			this->face.addIndex(this->face.getNumVertices() - 1);
			this->face.addIndex(this->face.getNumVertices() - 2);
			this->face.addIndex(this->face.getNumVertices() - 3);

			this->frame.addVertices(vertices);

			this->frame.addIndex(this->frame.getNumVertices() - 1);
			this->frame.addIndex(this->frame.getNumVertices() - 2);

			this->frame.addIndex(this->frame.getNumVertices() - 1);
			this->frame.addIndex(this->frame.getNumVertices() - 4);

			this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 4);

			this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 2);
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clearColors();
	this->frame.clearColors();

	auto index = 0;
	ofColor color;
	for (auto& vertex : this->face.getVertices()) {

		auto len = ofMap(vertex.y, -2000, 2000, 450, 10);

		auto noise_value = ofNoise(glm::distance(glm::vec3(0, 2700, 0), vertex) * 0.001 - ofGetFrameNum() * 0.05, vertex.x * 0.00025, vertex.y * 0.00025);
		vertex.z = ofMap(noise_value, 0, 1, -len, len);

		this->frame.setVertex(index++, vertex);

		color.setHsb(230, ofMap(vertex.z, -len, len, 200, 255), ofMap(vertex.z, -len, len, 255, 0));
		this->face.addColor(color);
		this->frame.addColor(ofColor(39));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(270);

	this->face.draw();
	this->frame.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 1000;
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
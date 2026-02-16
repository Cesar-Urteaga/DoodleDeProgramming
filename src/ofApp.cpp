#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateZ(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));
	ofRotateY(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));
	ofRotateX(ofRandom(360) + ofGetFrameNum() * ofRandom(1, 3));

	ofMesh mesh;
	auto param = 130;
	glm::vec3 avg;
	float noise_value;

	vector<glm::vec3> vertices;
	vertices.push_back(glm::vec4(param, param, param, 0));
	vertices.push_back(glm::vec4(param, -param, -param, 0));
	vertices.push_back(glm::vec4(-param, param, -param, 0));
	vertices.push_back(glm::vec4(-param, -param, param, 0));

	avg = (vertices[0] + vertices[1] + vertices[2]) / 3;
	noise_value = ofNoise(glm::vec4(avg * 0.0085, ofGetFrameNum() * 0.05));
	noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

	mesh.addVertex(vertices[0] + avg * noise_value);
	mesh.addVertex(vertices[1] + avg * noise_value);
	mesh.addVertex(vertices[2] + avg * noise_value);

	ofDrawLine(glm::vec3(), avg + avg * noise_value);
	ofDrawBox(avg + avg * noise_value, 5);

	avg = (vertices[0] + vertices[1] + vertices[3]) / 3;
	noise_value = ofNoise(glm::vec4(avg * 0.0085, ofGetFrameNum() * 0.05));
	noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

	mesh.addVertex(vertices[0] + avg * noise_value);
	mesh.addVertex(vertices[1] + avg * noise_value);
	mesh.addVertex(vertices[3] + avg * noise_value);

	ofDrawLine(glm::vec3(), avg + avg * noise_value);
	ofDrawBox(avg + avg * noise_value, 5);

	avg = (vertices[0] + vertices[2] + vertices[3]) / 3;
	noise_value = ofNoise(glm::vec4(avg * 0.0085, ofGetFrameNum() * 0.05));
	noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 10);

	mesh.addVertex(vertices[0] + avg * noise_value);
	mesh.addVertex(vertices[2] + avg * noise_value);
	mesh.addVertex(vertices[3] + avg * noise_value);

	ofDrawLine(glm::vec3(), avg + avg * noise_value);
	ofDrawBox(avg + avg * noise_value, 5);

	avg = (vertices[1] + vertices[2] + vertices[3]) / 3;
	noise_value = ofNoise(glm::vec4(avg * 0.0085, ofGetFrameNum() * 0.05));
	noise_value = noise_value < 0.5 ? 0 : ofMap(noise_value, 0.5, 1, 0, 5);

	mesh.addVertex(vertices[1] + avg * noise_value);
	mesh.addVertex(vertices[2] + avg * noise_value);
	mesh.addVertex(vertices[3] + avg * noise_value);

	ofDrawLine(glm::vec3(), avg + avg * noise_value);
	ofDrawBox(avg + avg * noise_value, 5);

	mesh.drawWireframe();

	for (auto& vertex : mesh.getVertices()) {

		ofDrawSphere(vertex, 10);
	}
	ofDrawSphere(glm::vec3(), 10);

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
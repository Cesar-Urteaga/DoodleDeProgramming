#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum() * 0.72);

	int len = 300;
	int size = 5;
	float noise_span = 0.01;

	for (int s_1 = len * -0.5; s_1 <= len * 0.5; s_1 += size) {

		for (int s_2 = len * -0.5; s_2 <= len * 0.5; s_2 += size) {

			vector<glm::vec3> vertices;
			auto p = (len + size) * 0.5;

			auto noise_value = ofNoise(p * noise_span, s_1 * noise_span, s_2 * noise_span + ofGetFrameNum() * 0.1);
			auto tmp_size = (noise_value > 0.45 && noise_value < 0.55) ? size : 0;

			vertices.clear();
			vertices.push_back(glm::vec3(p, s_1 - tmp_size * 0.5, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(p, s_1 + tmp_size * 0.5, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(p, s_1 + tmp_size * 0.5, s_2 + tmp_size * 0.5));
			vertices.push_back(glm::vec3(p, s_1 - tmp_size * 0.5, s_2 + tmp_size * 0.5));
			this->draw_panel(vertices);

			noise_value = ofNoise(-p * noise_span, s_1 * noise_span, s_2 * noise_span + ofGetFrameNum() * 0.1);
			tmp_size = (noise_value > 0.45 && noise_value < 0.55) ? size : 0;

			vertices.clear();
			vertices.push_back(glm::vec3(-p, s_1 - tmp_size * 0.5, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(-p, s_1 + tmp_size * 0.5, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(-p, s_1 + tmp_size * 0.5, s_2 + tmp_size * 0.5));
			vertices.push_back(glm::vec3(-p, s_1 - tmp_size * 0.5, s_2 + tmp_size * 0.5));
			this->draw_panel(vertices);

			noise_value = ofNoise(s_1 * noise_span, p * noise_span, s_2 * noise_span + ofGetFrameNum() * 0.1);
			tmp_size = (noise_value > 0.45 && noise_value < 0.55) ? size : 0;

			vertices.clear();
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, p, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, p, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, p, s_2 + tmp_size * 0.5));
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, p, s_2 + tmp_size * 0.5));
			this->draw_panel(vertices);

			noise_value = ofNoise(s_1 * noise_span, p * noise_span, s_2 * noise_span + ofGetFrameNum() * 0.1);
			tmp_size = (noise_value > 0.45 && noise_value < 0.55) ? size : 0;

			vertices.clear();
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, -p, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, -p, s_2 - tmp_size * 0.5));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, -p, s_2 + tmp_size * 0.5));
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, -p, s_2 + tmp_size * 0.5));
			this->draw_panel(vertices);

			noise_value = ofNoise(s_1 * noise_span, s_2 * noise_span, p * noise_span + ofGetFrameNum() * 0.1);
			tmp_size = (noise_value > 0.45 && noise_value < 0.55) ? size : 0;

			vertices.clear();
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, s_2 - tmp_size * 0.5, p));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, s_2 - tmp_size * 0.5, p));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, s_2 + tmp_size * 0.5, p));
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, s_2 + tmp_size * 0.5, p));
			this->draw_panel(vertices);

			noise_value = ofNoise(s_1 * noise_span, s_2 * noise_span, p * noise_span + ofGetFrameNum() * 0.1);
			tmp_size = (noise_value > 0.45 && noise_value < 0.55) ? size : 0;

			vertices.clear();
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, s_2 - tmp_size * 0.5, -p));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, s_2 - tmp_size * 0.5, -p));
			vertices.push_back(glm::vec3(s_1 + tmp_size * 0.5, s_2 + tmp_size * 0.5, -p));
			vertices.push_back(glm::vec3(s_1 - tmp_size * 0.5, s_2 + tmp_size * 0.5, -p));
			this->draw_panel(vertices);
		}
	}

	ofNoFill();
	ofSetColor(39);
	ofDrawBox(len + size);

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
void ofApp::draw_panel(vector<glm::vec3> vertices) {

	ofMesh face, line;
	face.addVertices(vertices);

	face.addIndex(0); face.addIndex(1); face.addIndex(2);
	face.addIndex(0); face.addIndex(2); face.addIndex(3);

	ofSetColor(39);
	face.draw();

	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
	line.addVertices(vertices);

	line.addIndex(0); line.addIndex(1);
	line.addIndex(1); line.addIndex(2);
	line.addIndex(2); line.addIndex(3);
	line.addIndex(3); line.addIndex(0);

	ofSetColor(39, 239, 239);
	line.drawWireframe();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
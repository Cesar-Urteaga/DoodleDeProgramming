#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofNoFill();

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	vector<float> min_distance_list;
	this->mesh.clear();

	for (int i = 0; i < 1600; i++) {

		auto vertex = glm::vec3(
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -300, 300),
			ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.001), 0, 1, -300, 300));
		this->mesh.addVertex(vertex);
		min_distance_list.push_back(40);
	}

	for (auto& vertex : this->mesh.getVertices()) {

		vertex.x = vertex.x < -150 ? -150 : vertex.x > 150 ? 150 : vertex.x;
		vertex.y = vertex.y < -150 ? -150 : vertex.y > 150 ? 150 : vertex.y;
		vertex.z = vertex.z < -150 ? -150 : vertex.z > 150 ? 150 : vertex.z;

		auto len = glm::length(vertex);
		if (len < 210) {

			vertex = glm::normalize(vertex) * 210;
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

		this->mesh.addColor(ofColor(39, ofMap(min_distance_list[i], 0, 30, 255, 0)));
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofRotateY(ofGetFrameNum() * 1.44);

	this->mesh.draw();

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		ofSetColor(this->mesh.getColor(i));
		ofDrawSphere(this->mesh.getVertex(i), 1.5);
	}

	ofSetColor(0);
	ofDrawBox(300);

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
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}


//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
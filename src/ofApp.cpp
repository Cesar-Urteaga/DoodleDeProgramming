#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	for (int radius = 150; radius <= 300; radius += 150) {

		auto noise_param = ofRandom(1000);
		for (int theta = 0; theta < 90; theta += 2) {

			int phi_start = ofMap(ofNoise(noise_param, theta * 0.01 + ofGetFrameNum() * 0.025), 0, 1, -360, 360);
			int phi_len = 120;
			auto index = this->face.getNumVertices();
			for (int phi = phi_start; phi <= phi_start + phi_len; phi += 3) {
				
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(
					radius * cos(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * sin(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 1) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					radius * cos((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * sin((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 1) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					radius * cos((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * sin((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 1) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					radius * cos(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * sin(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 1) * DEG_TO_RAD)
				));

				vertices.push_back(glm::vec3(
					(radius - 20) * cos(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					(radius - 20) * sin(phi * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 1) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					(radius - 20) * cos((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					(radius - 20) * sin((phi + 3) * DEG_TO_RAD) * sin((theta + 1) * DEG_TO_RAD),
					radius * cos((theta + 1) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					(radius - 20) * cos((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					(radius - 20) * sin((phi + 3) * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 1) * DEG_TO_RAD)
				));
				vertices.push_back(glm::vec3(
					(radius - 20) * cos(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					(radius - 20) * sin(phi * DEG_TO_RAD) * sin((theta - 1) * DEG_TO_RAD),
					radius * cos((theta - 1) * DEG_TO_RAD)
				));

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->face.addIndex(index + 4); this->face.addIndex(index + 5); this->face.addIndex(index + 6);
				this->face.addIndex(index + 4); this->face.addIndex(index + 6); this->face.addIndex(index + 7);

				this->face.addIndex(index + 0); this->face.addIndex(index + 4); this->face.addIndex(index + 5);
				this->face.addIndex(index + 0); this->face.addIndex(index + 5); this->face.addIndex(index + 1);

				this->face.addIndex(index + 2); this->face.addIndex(index + 6); this->face.addIndex(index + 7);
				this->face.addIndex(index + 2); this->face.addIndex(index + 7); this->face.addIndex(index + 3);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
				this->frame.addIndex(index + 2); this->frame.addIndex(index + 3);

				this->frame.addIndex(index + 4); this->frame.addIndex(index + 5);
				this->frame.addIndex(index + 6); this->frame.addIndex(index + 7);

				if (phi == phi_start) {

					this->frame.addIndex(index + 0); this->frame.addIndex(index + 3);
					this->frame.addIndex(index + 4); this->frame.addIndex(index + 7);

					this->frame.addIndex(index + 0); this->frame.addIndex(index + 4);
					this->frame.addIndex(index + 3); this->frame.addIndex(index + 7);
				}

				if (phi == phi_start + phi_len) {

					this->frame.addIndex(index + 1); this->frame.addIndex(index + 2);
					this->frame.addIndex(index + 5); this->frame.addIndex(index + 6);

					this->frame.addIndex(index + 1); this->frame.addIndex(index + 5);
					this->frame.addIndex(index + 2); this->frame.addIndex(index + 6);
				}

				index += vertices.size();
			}
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 650;
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
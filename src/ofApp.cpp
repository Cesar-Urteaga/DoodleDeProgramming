#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	float span = 0.5;
	for (float noise_param = 0; noise_param < 1.1; noise_param += 0.1) {

		for (float x = 20; x <= 700; x += span) {

			for (float y = 20; y <= 700; y += span) {

				float noise_value = ofNoise(int(x / 20) * 20 * 0.0025, int(y / 20) * 20 * 0.0025, ofGetFrameNum() * 0.0005);
				if (noise_value >= noise_param - 0.025 && noise_value <= noise_param + 0.025) {

					this->mesh.addVertex(glm::vec3(x, y, 0));
					this->mesh.addVertex(glm::vec3(x + span, y, 0));
					this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
					this->mesh.addVertex(glm::vec3(x, y + span, 0));

					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
					this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

					for (int i = 0; i < 4; i++) {

						this->mesh.addColor(ofColor(39));
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 1;
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
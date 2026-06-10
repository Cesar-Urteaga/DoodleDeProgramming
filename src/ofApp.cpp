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
	for (float x = 18; x < 702; x += span) {

		for (float y = 18; y < 702; y += span) {

			float noise_value = ofNoise(x * 0.02, y * 0.02,ofGetFrameNum() * 0.01);
			if ((noise_value >= 0.35 && noise_value <= 0.45) || (noise_value >= 0.55 && noise_value <= 0.65)) {

				this->mesh.addVertex(glm::vec3(x, y, 0));
				this->mesh.addVertex(glm::vec3(x + span, y, 0));
				this->mesh.addVertex(glm::vec3(x + span, y + span, 0));
				this->mesh.addVertex(glm::vec3(x, y + span, 0));

				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 4); this->mesh.addIndex(this->mesh.getNumVertices() - 3);
				this->mesh.addIndex(this->mesh.getNumVertices() - 1); this->mesh.addIndex(this->mesh.getNumVertices() - 2); this->mesh.addIndex(this->mesh.getNumVertices() - 3);

				for (int i = 0; i < 4; i++) {

					if (noise_value > 0.5) {

						this->mesh.addColor(ofColor(239, 39, 39));
					}
					else {

						this->mesh.addColor(ofColor(39, 39, 239));
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
	int start = 5;
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
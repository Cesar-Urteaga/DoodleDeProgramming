#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1.5);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	for (int x = 90; x < ofGetWindowWidth(); x += 180) {

		for (int y = 90; y < ofGetWindowHeight(); y += 180) {

			ofPushMatrix();
			ofTranslate(x, y);

			for (int radius = 5; radius < 80; radius += 3) {

				ofMesh line;
				line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

				int start_deg = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, 0, 360);
				int deg_len = ofMap(ofNoise(ofRandom(1000), ofGetFrameNum() * 0.01), 0, 1, 0, 240);

				for (int deg = start_deg; deg < start_deg + deg_len; deg += 2) {

					line.addVertex(glm::vec3() + glm::vec3(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD), 0));
					line.addColor(0);

					if (deg != start_deg) {

						line.addIndex(line.getNumVertices() - 1);
						line.addIndex(line.getNumVertices() - 2);
					}
				}

				line.draw();
			}

			ofPopMatrix();
		}
	}

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
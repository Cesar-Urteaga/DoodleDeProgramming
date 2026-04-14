#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);

	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	int radius = 25;
	int len = 10;
	int gap_x = radius * cos(0 * DEG_TO_RAD);
	int gap_y = radius + (radius - cos(210 * DEG_TO_RAD)) * 0.6;

	for (int x = -gap_x * 20; x <= gap_x * 20; x += gap_x) {

		for (int y = -gap_y * 20; y <= gap_y * 20; y += gap_y) {

			for (int z = -100; z <= 100; z += 200) {

				auto noise_param = ofNoise(x * 0.0025, y * 0.0025 - ofGetFrameNum() * 0.025, z * 0.005);

				if (noise_param > 0.4 && noise_param < 0.6) { continue; }

				auto alpha = 255;
				int flag = abs(x) % (gap_x * 2) == 0;
				int deg_start = flag ? 90 : 270;
				int tmp_y = flag ? y : y + (radius - cos(210 * DEG_TO_RAD)) * 0.5;

				ofFill();
				ofSetColor(ofColor(39, alpha));

				ofBeginShape();

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), tmp_y + radius * sin(deg * DEG_TO_RAD), z));
				}

				ofNextContour(true);

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + (radius - len) * cos(deg * DEG_TO_RAD), tmp_y + (radius - len) * sin(deg * DEG_TO_RAD), z));
				}

				ofEndShape(true);


				ofNoFill();
				ofSetColor(ofColor(239, 39, 239, alpha));

				ofBeginShape();

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {
										ofVertex(glm::vec3(x + radius * cos(deg * DEG_TO_RAD), tmp_y + radius * sin(deg * DEG_TO_RAD), z));
				}

				ofNextContour(true);

				for (int deg = deg_start; deg < deg_start + 360; deg += 120) {

					ofVertex(glm::vec3(x + (radius - len) * cos(deg * DEG_TO_RAD), tmp_y + (radius - len) * sin(deg * DEG_TO_RAD), z));
				}

				ofEndShape(true);
			}
		}
	}

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
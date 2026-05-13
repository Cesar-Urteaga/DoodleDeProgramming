#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);

	this->noise_seed = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 25 < 15) {

		this->noise_seed += ofMap(ofGetFrameNum() % 25, 0, 15, 0.3, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int x = -230; x <= 230; x += 230) {

		for (int y = -230; y <= 230; y += 230) {

			ofPushMatrix();
			ofTranslate(x, y);

			int base_radius = 30;

			{
				vector<glm::vec2> vertices;
				for (int deg = 0; deg < 360; deg += 5) {

					vertices.push_back(glm::vec2(base_radius * cos(deg * DEG_TO_RAD), base_radius * sin(deg * DEG_TO_RAD)));
				}

				ofFill();
				ofSetColor(239);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(39);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);
			}

			for (int deg = 0; deg < 360; deg += 10) {

				auto base_location = glm::vec2(base_radius * cos(deg * DEG_TO_RAD), base_radius * sin(deg * DEG_TO_RAD));

				auto out_radius = ofMap(ofNoise((x + base_location.x) * 0.025, (y + base_location.y) * 0.025, this->noise_seed), 0, 1, base_radius, base_radius * 3);
				auto out_location = glm::vec2(out_radius * cos(deg * DEG_TO_RAD), out_radius * sin(deg * DEG_TO_RAD));

				ofDrawLine(base_location, out_location);

				auto small_radius = (out_radius * 2 * PI) / 360 * 10 * 0.5;

				ofPushMatrix();
				ofTranslate(out_location);

				vector<glm::vec2> vertices;
				for (int d = 0; d < 360; d += 5) {

					vertices.push_back(glm::vec2(small_radius * cos(d * DEG_TO_RAD), small_radius * sin(d * DEG_TO_RAD)));
				}

				ofFill();
				ofSetColor(255);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofNoFill();
				ofSetColor(0);
				ofBeginShape();
				ofVertices(vertices);
				ofEndShape(true);

				ofPopMatrix();
			}

			ofPopMatrix();
		}
	}

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 2;
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
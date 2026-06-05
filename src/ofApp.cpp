#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	int radius = 100;
	float handle_len = radius;
	int number_of_location = 4;
	int deg_span = 360 / number_of_location;

	ofColor color;
	int hue = 0;
	for (int x = 180; x <= ofGetWidth() - 180; x += 360) {

		for (int y = 180; y <= ofGetHeight() - 180; y += 360) {

			ofPushMatrix();
			ofTranslate(x, y);

			auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

			for (int i = 0; i < 8; i++) {

				color.setHsb((hue + ofGetFrameNum() + i * 10) % 255, 255, 200);

				vector<glm::vec2> location_list;
				vector<float> deg_list;
				for (int deg = 0; deg < 360; deg += deg_span) {

					location_list.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
					deg_list.push_back(deg + 90);
				}

				for (int k = 0; k < location_list.size(); k++) {

					deg_list[k] += ofMap(ofNoise(noise_seed.x + location_list[k].x, noise_seed.y + location_list[k].y, i * 0.08 + ofGetFrameNum() * 0.01), 0, 1, -90, 90);
				}

				ofSetColor(color, ofMap(i, 0, 8, 0, 200));

				ofBeginShape();
				for (int i = 0; i < location_list.size(); i++) {

					int n = (i + 1) % location_list.size();

					ofVertex(location_list[i]);
					ofBezierVertex(
						location_list[i] + glm::vec2(handle_len * cos(deg_list[i] * DEG_TO_RAD), handle_len * sin(deg_list[i] * DEG_TO_RAD)),
						location_list[n] + glm::vec2(handle_len * cos((deg_list[n] + 180) * DEG_TO_RAD), handle_len * sin((deg_list[n] + 180) * DEG_TO_RAD)),
						location_list[n]);
				}
				ofEndShape();
			}

			hue += 64;

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
#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
	ofNoFill();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color;
	for (int i = 0; i < 20; i++) {

		auto deg = ofRandom(360);
		auto start_radius = ofRandom(2) < 1 ? 180 : 320;
		auto location = glm::vec2(start_radius * cos(deg * DEG_TO_RAD), start_radius * sin(deg * DEG_TO_RAD));

		color.setHsb(start_radius == 180 ? ofRandom(60, 80) : ofRandom(190, 210), 200, 255);

		vector<glm::vec2> log;
		log.push_back(location);
		this->log_list.push_back(log);
		this->color_list.push_back(color);
		this->life_list.push_back(ofRandom(100, 150));
	}

	int radius = 4;
	for (int i = this->log_list.size() - 1; i >= 0; i--) {

		this->life_list[i] -= 1;
		if (this->life_list[i] < 0) {

			this->log_list.erase(this->log_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
			this->life_list.erase(this->life_list.begin() + i);

			continue;
		}

		int count = 0;
		while (true) {

			auto deg = ofMap(ofNoise(glm::vec3(this->log_list[i].back() * 0.01, count * 0.01 + ofGetFrameNum() * 0.01)), 0, 1, -360, 360);
			auto tmp = this->log_list[i].back() + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			if (glm::length(tmp) > 180 && glm::length(tmp) < 320) {

				this->log_list[i].push_back(this->log_list[i].back() + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
				break;
			}
			else {

				count++;
			}
		}

		while (this->log_list[i].size() > 100) {

			this->log_list[i].erase(this->log_list[i].begin());
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofPushMatrix();

		int t = this->color_list[i].getHue();
		t >= 190 && t <= 210 ? ofRotateZ(ofGetFrameNum() * 0.36) : ofRotateZ(ofGetFrameNum() * -0.36);

		if (this->life_list[i] > 80) {

			ofSetColor(this->color_list[i]);
			ofSetLineWidth(1);
		}
		else {

			ofSetColor(ofColor(this->color_list[i], ofMap(this->life_list[i], 0, 80, 0, 255)));
			ofSetLineWidth(ofMap(this->life_list[i], 0, 80, 0, 1));
		}

		ofBeginShape();
		ofVertices(this->log_list[i]);
		ofEndShape();

		ofPopMatrix();
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
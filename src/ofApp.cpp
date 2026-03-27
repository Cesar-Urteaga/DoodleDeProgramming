#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofFill();

	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofColor color(239);
	for (int i = 0; i < 12; i++) {

		auto deg = ofGetFrameNum() * 1.44 + i * 30;
		auto next_deg = deg + 10;
		auto noise_location = glm::vec2(280 * cos(deg * DEG_TO_RAD), 280 * sin(deg * DEG_TO_RAD));
		auto next_noise_location = glm::vec2(100 * cos(next_deg * DEG_TO_RAD), 100 * sin(next_deg * DEG_TO_RAD));

		for (int k = 0; k < 1; k++) {

			vector<glm::vec2> log;
			log.push_back(noise_location);
			this->log_list.push_back(log);

			auto deg = glm::atan(next_noise_location.y - noise_location.y, next_noise_location.x - noise_location.x) * RAD_TO_DEG + 180 + ofRandom(-30, 30);
			glm::vec2 velocity = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			this->velocity_list.push_back(velocity);

			this->noise_seed_list.push_back(ofRandom(1000));

			this->color_list.push_back(color);
		}
	}

	for (int i = 0; i < this->log_list.size(); i++) {

		auto future = this->velocity_list[i] * 200;
		auto random_deg = ofMap(ofNoise(glm::vec2(this->noise_seed_list[i], ofGetFrameNum() * 0.01)), 0, 1, 0, 360);
		future += glm::vec2(10 * cos(random_deg * DEG_TO_RAD), 10 * sin(random_deg * DEG_TO_RAD));

		auto next = this->log_list[i].back() + glm::normalize(future) * 2;
		next = glm::length(next) < 1000 ? next : glm::normalize(next) * 1000;
		this->log_list[i].push_back(next);

		if (this->log_list[i].size() > 30) {

			this->log_list.erase(this->log_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
			this->noise_seed_list.erase(this->noise_seed_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	for (int i = 0; i < this->log_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->log_list[i].back());

		auto rad = atan2(this->velocity_list[i].y, this->velocity_list[i].x);
		ofRotate(rad * RAD_TO_DEG + ofGetFrameNum() * 3);

		ofSetColor(this->color_list[i]);
		auto size = this->log_list[i].size() < 3 ? 25 : ofMap(this->log_list[i].size(), 3, 30, 25, 1);
		ofDrawCircle(glm::vec3(), size);

		ofPopMatrix();
	}

	for (int i = 0; i < this->log_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->log_list[i].back());

		auto rad = atan2(this->velocity_list[i].y, this->velocity_list[i].x);
		ofRotate(rad * RAD_TO_DEG + ofGetFrameNum() * 3);

		ofSetColor(39);
		auto size = this->log_list[i].size() < 3 ? 20 : ofMap(this->log_list[i].size(), 3, 30, 20, 0);
		ofDrawCircle(glm::vec3(), size);

		ofPopMatrix();
	}

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
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(1.5);

	this->radius = 30;
	vector<glm::vec2> start_location_list;
	auto x_span = this->radius * sqrt(3);
	auto flg = true;
	for (float y = 0; y < ofGetHeight() + this->radius; y += this->radius * 1.5) {

		for (float x = 0; x < ofGetWidth() + this->radius; x += x_span) {

			glm::vec2 location;
			if (flg) {

				location = glm::vec2(x, y);
			}
			else {

				location = glm::vec2(x + (this->radius * sqrt(3) / 2), y);
			}

			start_location_list.push_back(location);
		}
		flg = !flg;
	}

	ofColor color;
	for (int i = 0; i < 16; i++) {

		color.setHsb(ofMap(i, 0, 16, 0, 255), 255, 200);
		int r = ofRandom(start_location_list.size());

		auto log_list = vector<glm::vec2>();
		log_list.push_back(start_location_list[r]);
		this->hexagon_list.push_back(log_list);

		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 2 == 0) {

		auto span = this->radius * sqrt(3);
		for (auto& log_list : this->hexagon_list) {

			int r = ofRandom(6);
			int deg_start = r * 60;
			for (int deg = deg_start; deg < deg_start + 360; deg += 60) {

				auto tmp_location = log_list.back() + glm::vec2(span * cos(deg * DEG_TO_RAD), span * sin(deg * DEG_TO_RAD));
				if (tmp_location.x < 0 || tmp_location.x > ofGetWidth() + this->radius || tmp_location.y < 0 || tmp_location.y > ofGetHeight() + this->radius) {

					continue;
				}

				log_list.push_back(tmp_location);
				break;
			}

			while (log_list.size() > 10) {

				log_list.erase(log_list.begin());
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	int color_index = 0;
	for (auto& log_list : this->hexagon_list) {

		for (int i = 0; i < log_list.size(); i++) {

			vector<glm::vec2> vertices_1;
			for (auto deg = 90; deg < 450; deg += 60) {

				vertices_1.push_back(log_list[i] + glm::vec2(this->radius * ((i + 1) * 0.1) * cos(deg * DEG_TO_RAD), this->radius * ((i + 1) * 0.1) * sin(deg * DEG_TO_RAD)));
			}

			ofFill();
			ofSetColor(ofColor(this->color_list[color_index], ofMap(i, 0, log_list.size(), 255, 0)));

			ofBeginShape();
			ofVertices(vertices_1);
			ofEndShape(true);

			ofNoFill();
			ofSetColor(ofColor(this->color_list[color_index]));

			ofBeginShape();
			ofVertices(vertices_1);
			ofEndShape(true);
		}

		color_index++;
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
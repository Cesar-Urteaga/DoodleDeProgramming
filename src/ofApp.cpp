#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->mesh.clear();

	int width = 20;
	int deg_span = 90;
	for (int x = 180; x < ofGetWidth(); x += 360) {

		for (int y = 180; y < ofGetHeight(); y += 360) {

			for (int deg = 0; deg < 360; deg += deg_span) {

				auto noise_param = ofRandom(1000);

				int radius = ofMap(ofNoise(noise_param, cos(deg * DEG_TO_RAD) * 15, sin(deg * DEG_TO_RAD) * 15, this->noise_param), 0, 1, 30, 160);

				this->setRingToMesh(this->mesh, glm::vec3(x, y, 0), radius, width, deg, deg + deg_span);
			}
		}
	}

	if (ofGetFrameNum() % 50 < 40) {

		this->noise_param += ofMap(ofGetFrameNum() % 50, 0, 40, 0.15, 0);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->mesh.draw();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 50;
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
void ofApp::setRingToMesh(ofMesh& mesh, glm::vec3 location, float radius, float width, int deg_start, int deg_end) {

	if (deg_start == deg_end) { return; }

	int deg_span = 5;
	for (int deg = deg_start; deg < deg_end; deg += deg_span) {

		auto index = mesh.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(location + glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), 0));
		vertices.push_back(location + glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), 0));

		mesh.addVertices(vertices);

		mesh.addIndex(index + 0); mesh.addIndex(index + 1); mesh.addIndex(index + 2);
		mesh.addIndex(index + 0); mesh.addIndex(index + 2); mesh.addIndex(index + 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
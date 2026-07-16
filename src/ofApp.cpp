#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	int deg_span = 15;
	int radius_span = 10;
	int radius_max = 1200;

	for (int deg = 0; deg < 360; deg += deg_span) {

		int index = this->line.getNumVertices();

		for (int radius = 100; radius < radius_max; radius += radius_span) {

			auto noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
			auto noise_value = ofNoise(glm::vec3(noise_location * 0.5, radius * 0.001 - ofGetFrameNum() * 0.02));
			auto z = ofMap(noise_value, 0, 1, -150, 150);

			vector<glm::vec3> vertices;
			vertices.push_back(glm::vec3(radius * cos((deg - deg_span * 0.5 + 0.5) * DEG_TO_RAD), radius * sin((deg - deg_span * 0.5 + 0.5) * DEG_TO_RAD), z));
			vertices.push_back(glm::vec3(radius * cos((deg + deg_span * 0.5 - 0.5) * DEG_TO_RAD), radius * sin((deg + deg_span * 0.5 - 0.5) * DEG_TO_RAD), z));
			this->face.addVertices(vertices);
			this->line.addVertices(vertices);

			if (radius > 100) {

				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 4);
				this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 4); this->face.addIndex(this->face.getNumVertices() - 3);

				this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 3);
				this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 4);
			}
		}

		this->line.addIndex(index); this->line.addIndex(index + 1);
		//this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
	}

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 0.72);

	ofSetColor(39);
	ofFill();
	this->face.draw();

	ofSetColor(239);
	ofNoFill();
	this->line.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 1000;
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
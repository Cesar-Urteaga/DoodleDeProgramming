#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->frame.clear();

	int radius = 150;
	int phi_deg_step = 5;

	auto param = sin(ofGetFrameNum() * 0.05);

	for (float theta_deg = 1; theta_deg < 180; theta_deg += 5) {

		auto noise_z = radius * cos(theta_deg * DEG_TO_RAD);
		auto noise_value = ofNoise(0, 0, noise_z * 0.5 + ofGetFrameNum() * 0.03);

		auto param_x = ofMap(noise_value, 0, 1, radius * -1.5, radius * 1.5);
		param_x *= param;

		auto start_index = this->face.getNumVertices();
		for (int phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step + 1) {

			auto index = this->face.getNumVertices();

			vector<glm::vec3> vertices;

			vertices.push_back(glm::vec4(param_x + radius * sin((theta_deg - 2) * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD), radius * sin((theta_deg - 2) * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD), radius * cos((theta_deg - 2) * DEG_TO_RAD), 0));
			vertices.push_back(glm::vec4(param_x + radius * sin((theta_deg + 2) * DEG_TO_RAD) * cos(phi_deg * DEG_TO_RAD), radius * sin((theta_deg + 2) * DEG_TO_RAD) * sin(phi_deg * DEG_TO_RAD), radius * cos((theta_deg + 2) * DEG_TO_RAD), 0));

			this->face.addVertices(vertices);
			this->frame.addVertices(vertices);

			if (phi_deg > 0) {

				this->face.addIndex(index + 0); this->face.addIndex(index - 2); this->face.addIndex(index - 1);
				this->face.addIndex(index + 0); this->face.addIndex(index - 1); this->face.addIndex(index + 1);

				this->face.addIndex(index + 0); this->face.addIndex(index - 2); this->face.addIndex(start_index + 0);
				this->face.addIndex(index + 1); this->face.addIndex(index - 1); this->face.addIndex(start_index + 1);

				this->frame.addIndex(index + 0); this->frame.addIndex(index - 2);
				this->frame.addIndex(index + 1); this->frame.addIndex(index - 1);
			}
		}

		auto index = this->face.getNumVertices() - 2;
		this->face.addIndex(start_index + 0); this->face.addIndex(index + 0); this->face.addIndex(index + 1);
		this->face.addIndex(start_index + 1); this->face.addIndex(index + 1); this->face.addIndex(start_index + 1);

		this->frame.addIndex(start_index + 0); this->frame.addIndex(index + 0);
		this->frame.addIndex(start_index + 1); this->frame.addIndex(index + 1);
	}
}


//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);

	ofSetColor(0);
	this->face.draw();

	ofSetColor(255);
	this->frame.drawWireframe();

	this->cam.end();

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
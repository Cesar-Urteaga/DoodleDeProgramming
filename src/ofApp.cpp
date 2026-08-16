#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);

	this->face.clear();
	this->line.clear();

	auto radius = 250;
	auto start_deg = ofGetFrameNum() * 5;
	auto phi_len = 20;
	auto theta_deg_step = 0.1;

	for (float theta_deg = 0; theta_deg < 180; theta_deg += theta_deg_step) {

		auto phi_deg = start_deg + theta_deg * 3;
		auto next_theta_deg = theta_deg + theta_deg_step;
		auto next_phi_deg = start_deg + next_theta_deg * 3;

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3(
			radius * sin(theta_deg * DEG_TO_RAD) * cos((phi_deg - phi_len * 0.5) * DEG_TO_RAD),
			radius * sin(theta_deg * DEG_TO_RAD) * sin((phi_deg - phi_len * 0.5) * DEG_TO_RAD),
			radius * cos(theta_deg * DEG_TO_RAD)));
		vertices.push_back(glm::vec3(
			radius * sin(theta_deg * DEG_TO_RAD) * cos((phi_deg + phi_len * 0.5) * DEG_TO_RAD),
			radius * sin(theta_deg * DEG_TO_RAD) * sin((phi_deg + phi_len * 0.5) * DEG_TO_RAD),
			radius * cos(theta_deg * DEG_TO_RAD)));
		vertices.push_back(glm::vec3(
			radius * sin(next_theta_deg * DEG_TO_RAD) * cos((next_phi_deg + phi_len * 0.5) * DEG_TO_RAD),
			radius * sin(next_theta_deg * DEG_TO_RAD) * sin((next_phi_deg + phi_len * 0.5) * DEG_TO_RAD),
			radius * cos(next_theta_deg * DEG_TO_RAD)));
		vertices.push_back(glm::vec3(
			radius * sin(next_theta_deg * DEG_TO_RAD) * cos((next_phi_deg - phi_len * 0.5) * DEG_TO_RAD),
			radius * sin(next_theta_deg * DEG_TO_RAD) * sin((next_phi_deg - phi_len * 0.5) * DEG_TO_RAD),
			radius * cos(next_theta_deg * DEG_TO_RAD)));

		this->face.addVertices(vertices);
		this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 2); this->face.addIndex(this->face.getNumVertices() - 3);
		this->face.addIndex(this->face.getNumVertices() - 1); this->face.addIndex(this->face.getNumVertices() - 3); this->face.addIndex(this->face.getNumVertices() - 4);

		this->line.addVertices(vertices);
		this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 4);
		this->line.addIndex(this->line.getNumVertices() - 2); this->line.addIndex(this->line.getNumVertices() - 3);
	}

	ofColor color;
	for (int i = 0; i < 6; i++) {

		ofRotateZ(30);
		color.setHsb(ofMap(i, 0, 6, 0, 255), 180, 255);

		ofSetColor(color);
		this->face.draw();
		ofSetColor(255);
		this->line.drawWireframe();
	}

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 15;
	if (ofGetFrameNum() > start) {

		std::ostringstream  os;
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
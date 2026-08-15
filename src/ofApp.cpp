#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
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

	auto start_deg = ofGetFrameNum() * 15;
	auto phi_len = 25;
	auto theta_deg_step = 0.5;

	for (float theta_deg = 0; theta_deg < 360; theta_deg += theta_deg_step) {

		auto radius = theta_deg < 180 ? 250 : 150;

		auto phi_deg = start_deg + theta_deg * 15;
		auto next_theta_deg = theta_deg + theta_deg_step;
		auto next_phi_deg = start_deg + next_theta_deg * 15;

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

		for (int i = 0; i < vertices.size(); i++) {

			this->face.addColor(ofColor(239));
			this->line.addColor(ofColor(39));
		}
	}

	this->face.draw();
	this->line.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 500;
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
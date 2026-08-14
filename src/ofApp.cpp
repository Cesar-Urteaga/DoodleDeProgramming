#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	if (ofGetFrameNum() % 50 < 15) {

		this->noise_step += ofMap(ofGetFrameNum() % 50, 0, 15, 0.1, 0.00001);
	}

	this->face.clear();
	this->frame.clear();

	float phi_deg_step = 3;
	float theta_deg_step = 2;

	ofColor color;

	for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

		for (float deg_start = 5; deg_start < 185; deg_start += 10) {

			color.setHsb(ofMap(deg_start, 0, 180, 255, 0), 255, 255);
			int radius = 300 - deg_start;

			for (float theta_deg = deg_start; theta_deg < deg_start + theta_deg_step; theta_deg += theta_deg_step) {

				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg - theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg + phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));
				vertices.push_back(glm::vec3(
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * cos((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * sin((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD) * sin((phi_deg - phi_deg_step * 0.5) * DEG_TO_RAD),
					radius * cos((theta_deg + theta_deg_step * 0.5) * DEG_TO_RAD)));

				for (auto& vertex : vertices) {

					auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(theta_deg * 0.01 + this->noise_step), 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(1, 0, 0));
					auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(theta_deg * 0.01 + this->noise_step), 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));
					auto rotation_z = glm::rotate(glm::mat4(), ofMap(ofNoise(theta_deg * 0.01 + this->noise_step), 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));

					vertex = glm::vec4(vertex, 0) * rotation_z * rotation_y * rotation_x;
				}

				this->face.addVertices(vertices);
				this->frame.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				this->frame.addIndex(index + 0); this->frame.addIndex(index + 1);
				this->frame.addIndex(index + 3); this->frame.addIndex(index + 2);

				for (int i = index; i < this->face.getNumVertices(); i++) {

					this->face.addColor(ofColor(color, 64));
					this->frame.addColor(color);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	this->face.draw();
	this->frame.draw();

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
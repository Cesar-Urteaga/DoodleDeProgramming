#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofEnableDepthTest();
	ofSetLineWidth(1.5);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float phi_deg_step = 3;
	float theta_deg_step = 3;

	for (float radius = 200; radius <= 250; radius += 25) {

		for (float phi_deg = 0; phi_deg < 360; phi_deg += phi_deg_step) {

			for (float theta_deg = 80; theta_deg <= 100; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					radius * cos(phi_deg * DEG_TO_RAD) * 0.02,
					radius * sin(phi_deg * DEG_TO_RAD) * 0.02,
					radius * cos(theta_deg * DEG_TO_RAD) * 0.02,
					ofGetFrameNum() * 0.025);

				if (noise_value < 0.48) { continue; }

				auto noise_value_1 = ofNoise(
					radius * cos(phi_deg * DEG_TO_RAD) * 0.02,
					radius * sin(phi_deg * DEG_TO_RAD) * 0.02,
					radius * cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * 0.02,
					ofGetFrameNum() * 0.025);
				auto noise_value_2 = ofNoise(
					radius * cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * 0.02,
					radius * sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * 0.02,
					radius * cos(theta_deg * DEG_TO_RAD) * 0.02,
					ofGetFrameNum() * 0.025);
				auto noise_value_3 = ofNoise(
					radius * cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * 0.02,
					radius * sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * 0.02,
					radius * cos(theta_deg * DEG_TO_RAD) * 0.02,
					ofGetFrameNum() * 0.025);
				auto noise_value_4 = ofNoise(
					radius * cos(phi_deg * DEG_TO_RAD) * 0.02,
					radius * sin(phi_deg * DEG_TO_RAD) * 0.02,
					radius * cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * 0.02,
					ofGetFrameNum() * 0.025);

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

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 3);
				this->face.addIndex(index + 0); this->face.addIndex(index + 3); this->face.addIndex(index + 2);

				if (noise_value_1 < 0.48 || theta_deg == 80) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_2 < 0.48) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_3 < 0.48) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				if (noise_value_4 < 0.48 || theta_deg == 100) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
				}

				for (int i = 0; i < vertices.size(); i++) {

					this->face.addColor(ofColor(39));
					this->line.addColor(ofColor(239));
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(270);
	ofRotateZ(ofGetFrameNum() * 0.72);

	this->face.draw();
	this->line.draw();

	this->cam.end();

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
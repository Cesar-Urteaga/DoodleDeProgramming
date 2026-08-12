#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();
	ofSetLineWidth(1);

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.01;

	this->line.clear();

	float phi_deg_step = 0.1;
	float theta_deg_step = 0.1;
	float theta_start = 70;
	float theta_end = 110;
	float threshold_1 = 0.45;
	float threshold_2 = 0.55;
	float noise_span = 0.025;

	ofColor face_color(0), line_color(255);
	for (float radius = 250; radius <= 300; radius += 5) {

		line_color.setHsb(ofMap(ofGetFrameNum() % 250, 0, 250, 0, 255), 255, ofMap(radius, 250, 300, 0, 255));
		
		for (float phi_deg = 30; phi_deg < 150; phi_deg += phi_deg_step) {

			for (float theta_deg = theta_start; theta_deg <= theta_end; theta_deg += theta_deg_step) {

				auto noise_value = ofNoise(
					radius * cos(phi_deg * DEG_TO_RAD) * noise_span,
					radius * sin(phi_deg * DEG_TO_RAD) * noise_span,
					radius * cos(theta_deg * DEG_TO_RAD) * noise_span,
					this->noise_param);

				if (threshold_1 > noise_value || noise_value > threshold_2) { continue; }

				auto noise_value_1 = ofNoise(
					radius * cos(phi_deg * DEG_TO_RAD) * noise_span,
					radius * sin(phi_deg * DEG_TO_RAD) * noise_span,
					radius * cos((theta_deg - theta_deg_step) * DEG_TO_RAD) * noise_span,
					this->noise_param);
				auto noise_value_2 = ofNoise(
					radius * cos((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_span,
					radius * sin((phi_deg + phi_deg_step) * DEG_TO_RAD) * noise_span,
					radius * cos(theta_deg * DEG_TO_RAD) * noise_span,
					this->noise_param);
				auto noise_value_3 = ofNoise(
					radius * cos((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_span,
					radius * sin((phi_deg - phi_deg_step) * DEG_TO_RAD) * noise_span,
					radius * cos(theta_deg * DEG_TO_RAD) * noise_span,
					this->noise_param);
				auto noise_value_4 = ofNoise(
					radius * cos(phi_deg * DEG_TO_RAD) * noise_span,
					radius * sin(phi_deg * DEG_TO_RAD) * noise_span,
					radius * cos((theta_deg + theta_deg_step) * DEG_TO_RAD) * noise_span,
					this->noise_param);

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


				if (threshold_1 > noise_value_1 || noise_value_1 > threshold_2 || theta_deg == theta_start) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (threshold_1 > noise_value_2 || noise_value_2 > threshold_2) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (threshold_1 > noise_value_3 || noise_value_3 > threshold_2) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (threshold_1 > noise_value_4 || noise_value_4 > threshold_2 || theta_deg == theta_end) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);

	this->line.draw();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 2;
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
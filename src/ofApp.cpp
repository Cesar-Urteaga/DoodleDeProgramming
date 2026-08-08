#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(239);
	ofNoFill();
	ofEnableDepthTest();

	this->line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->face.clear();
	this->line.clear();

	float span = 1;
	float threshold_1 = 0.43;
	float threshold_2 = 0.57;
	float noise_param = 0.005;

	ofColor face_color(39);
	ofColor line_color(239);

	for (float x = 0; x <= 400; x += span) {

		for (float y = 0; y <= 400; y += span) {

			for (float z = -200; z <= 0; z += span * 15) {

				line_color = ofColor(ofMap(z, -200, 0, 39, 239));

				auto noise_value = ofNoise(x * noise_param, y * noise_param, z * noise_param * 0.5 + ofGetFrameNum() * 0.01);
				
				if (noise_value < threshold_1 || noise_value > threshold_2) { continue; }

				auto noise_value_1 = ofNoise((x - span) * noise_param, y * noise_param, z * noise_param * 0.5 + ofGetFrameNum() * 0.01);
				auto noise_value_2 = ofNoise(x * noise_param, (y + span) * noise_param, z * noise_param * 0.5 + ofGetFrameNum() * 0.01);
				auto noise_value_3 = ofNoise((x + span) * noise_param, y * noise_param, z * noise_param * 0.5 + ofGetFrameNum() * 0.01);
				auto noise_value_4 = ofNoise(x * noise_param, (y - span) * noise_param, z * noise_param * 0.5 + ofGetFrameNum() * 0.01);


				auto index = this->face.getNumVertices();
				vector<glm::vec3> vertices;

				vertices.push_back(glm::vec3(x - span * 0.5, y - span * 0.5, z));
				vertices.push_back(glm::vec3(x - span * 0.5, y + span * 0.5, z));
				vertices.push_back(glm::vec3(x + span * 0.5, y + span * 0.5, z));
				vertices.push_back(glm::vec3(x + span * 0.5, y - span * 0.5, z));

				this->face.addVertices(vertices);

				this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
				this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);

				this->face.addColor(face_color);
				this->face.addColor(face_color);
				this->face.addColor(face_color);
				this->face.addColor(face_color);

				if (noise_value_1 < threshold_1 || noise_value_1 > threshold_2 || x == 0) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[1]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_value_2 < threshold_1 || noise_value_2 > threshold_2 || y == 400) {

					this->line.addVertex(vertices[1]); this->line.addVertex(vertices[2]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_value_3 < threshold_1 || noise_value_3 > threshold_2 || x == 400) {

					this->line.addVertex(vertices[2]); this->line.addVertex(vertices[3]);
					this->line.addIndex(this->line.getNumVertices() - 1); this->line.addIndex(this->line.getNumVertices() - 2);
					this->line.addColor(line_color); this->line.addColor(line_color);
				}

				if (noise_value_4 < threshold_1 || noise_value_4 > threshold_2 || y == 0) {

					this->line.addVertex(vertices[0]); this->line.addVertex(vertices[3]);
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

	ofTranslate(-200, -200);

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
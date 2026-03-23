#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	for (int z = -128; z <= 128; z += 16) {

		for (int radius = 180; radius <= 360; radius += 30) {

			int deg_start = 0;
			int deg_end = 0;
			int tmp_deg = 0;
			for (int deg = 0; deg < 360 + tmp_deg; deg += 1) {

				auto noise_value = ofNoise(glm::vec4(radius * cos(deg * DEG_TO_RAD) * 0.001, radius * sin(deg * DEG_TO_RAD) * 0.001, z * 0.01, ofGetFrameNum() * 0.01));

				if (noise_value < 0.5) {

					deg_end = deg;

					if (deg == 0) {

						while (true) {

							tmp_deg -= 1;
							auto tmp_noise_value = ofNoise(glm::vec4(radius * cos(tmp_deg * DEG_TO_RAD) * 0.001, radius * sin(tmp_deg * DEG_TO_RAD) * 0.001, z * 0.01, ofGetFrameNum() * 0.01));
							if (tmp_noise_value > 0.5 || tmp_deg < -360) { break; }		
							deg_start = tmp_deg;
						}
					}
				}
				else {

					if (deg_start < deg_end) {

						this->setRingToMesh(this->face, this->frame, glm::vec3(0, 0, z + 8), radius, 30, 14, deg_start, deg_end);
					}

					deg_start = deg;
					deg_end = deg;
				}
			}

			if (deg_start != deg_end) {

				this->setRingToMesh(this->face, this->frame, glm::vec3(0, 0, z + 8), radius, 30, 14, deg_start, deg_end);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 1.44);

	ofSetColor(39);
	this->face.draw();

	ofSetColor(239);
	this->frame.drawWireframe();

	this->cam.end();

	/*
	// ffmpeg -i img_%04d.jpg aaa.mp4
	int start = 250;
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
void ofApp::setRingToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius, float width, float height, int deg_start, int deg_end) {

	if (deg_start == deg_end) { return; }

	int index = face_target.getNumVertices();

	for (int deg = deg_start; deg <= deg_end; deg += 1) {

		auto face_index = face_target.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + 1) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + 1) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		for (auto& vertex : vertices) {

			vertex += location;
		}

		face_target.addVertices(vertices);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 1); face_target.addIndex(face_index + 2);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 2); face_target.addIndex(face_index + 3);

		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 7);

		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 4); face_target.addIndex(face_index + 5);
		face_target.addIndex(face_index + 0); face_target.addIndex(face_index + 5); face_target.addIndex(face_index + 1);

		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 7); face_target.addIndex(face_index + 6);
		face_target.addIndex(face_index + 3); face_target.addIndex(face_index + 6); face_target.addIndex(face_index + 2);

		auto frame_index = frame_target.getNumVertices();

		frame_target.addVertices(vertices);

		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 1);
		frame_target.addIndex(frame_index + 2); frame_target.addIndex(frame_index + 3);
		frame_target.addIndex(frame_index + 4); frame_target.addIndex(frame_index + 5);
		frame_target.addIndex(frame_index + 6); frame_target.addIndex(frame_index + 7);
	}

	face_target.addIndex(index + 0); face_target.addIndex(index + 3); face_target.addIndex(index + 7);
	face_target.addIndex(index + 0); face_target.addIndex(index + 7); face_target.addIndex(index + 4);

	frame_target.addIndex(index + 0); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 0); frame_target.addIndex(index + 4);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 3);
	frame_target.addIndex(index + 7); frame_target.addIndex(index + 4);

	index = frame_target.getNumVertices() - 8;

	face_target.addIndex(index + 1); face_target.addIndex(index + 2); face_target.addIndex(index + 6);
	face_target.addIndex(index + 1); face_target.addIndex(index + 6); face_target.addIndex(index + 5);

	frame_target.addIndex(index + 1); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 1); frame_target.addIndex(index + 5);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 2);
	frame_target.addIndex(index + 6); frame_target.addIndex(index + 5);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
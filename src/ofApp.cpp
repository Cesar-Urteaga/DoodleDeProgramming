#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(90);
	ofRotateZ(ofGetFrameNum() * 2.88);

	ofMesh face, line;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	int radius = 300;
	int deg_len = 30;
	int z_span = 1;

	for (int radius = 300; radius <= 360; radius += 20) {

		for (int base_deg = 0; base_deg < 360; base_deg += 180) {

			for (int z = -1200; z < 1200; z += z_span) {

				auto deg_1 = base_deg + ofMap(ofNoise(z * 0.0005 - radius * 0.001 + ofGetFrameNum() * 0.01), 0, 1, -720, 720);
				auto deg_2 = deg_1 + deg_len;
				auto deg_3 = base_deg + ofMap(ofNoise((z + z_span) * 0.0005 - radius * 0.001 + ofGetFrameNum() * 0.01), 0, 1, -720, 720);
				auto deg_4 = deg_3 + deg_len;

				vector<glm::vec3> vertices;
				vertices.push_back(glm::vec3(radius * cos(deg_1 * DEG_TO_RAD), radius * sin(deg_1 * DEG_TO_RAD), z));
				vertices.push_back(glm::vec3(radius * cos(deg_2 * DEG_TO_RAD), radius * sin(deg_2 * DEG_TO_RAD), z));
				vertices.push_back(glm::vec3(radius * cos(deg_4 * DEG_TO_RAD), radius * sin(deg_4 * DEG_TO_RAD), z + z_span));
				vertices.push_back(glm::vec3(radius * cos(deg_3 * DEG_TO_RAD), radius * sin(deg_3 * DEG_TO_RAD), z + z_span));

				face.addVertices(vertices);
				line.addVertices(vertices);

				face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);

				if (z == -1200) {

					line.addIndex(line.getNumVertices() - 3); line.addIndex(line.getNumVertices() - 4);
				}

				if (z == 1200 - z_span) {

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);
				}
			}
		}
	}

	ofSetColor(0);
	face.draw();

	ofSetColor(239);
	line.drawWireframe();

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
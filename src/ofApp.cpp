#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(280, 4);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->frame.clear();

	for (float radius = 200; radius <= 300; radius += 5) {

		for (int i = 0; i < this->triangle_list.size(); i++) {

			glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
			auto noise_value = ofNoise(avg.y * 0.005, avg.x * 0.005, avg.z * 0.005, radius * 0.005 +  ofGetFrameNum() * 0.01);

			if (noise_value > 0.4 && noise_value < 0.5) {
				
				noise_value = 1;
			}
			else {

				continue;
			}

			vector<glm::vec3> vertices;

			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius + 1) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius + 1) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius + 1) - avg);

			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius - 1) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius - 1) - avg);
			vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius - 1) - avg);

			for (auto& vertex : vertices) {

				vertex *= noise_value;
				vertex += avg;
			}

			this->mesh.addVertices(vertices);
			this->frame.addVertices(vertices);

			for (int k = 0; k < 6; k++) {

				this->mesh.addColor(ofColor(0));
				this->frame.addColor(ofColor(255));
			}

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 4, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 6);

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 5);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 5, this->mesh.getNumVertices() - 4);

			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 1, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 4);

			this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 3, this->mesh.getNumVertices() - 6);
			this->mesh.addTriangle(this->mesh.getNumVertices() - 2, this->mesh.getNumVertices() - 6, this->mesh.getNumVertices() - 5);

			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 2);
			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 3);
			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 3);

			this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 5);
			this->frame.addIndex(this->frame.getNumVertices() - 5); this->frame.addIndex(this->frame.getNumVertices() - 6);
			this->frame.addIndex(this->frame.getNumVertices() - 4); this->frame.addIndex(this->frame.getNumVertices() - 6);

			this->frame.addIndex(this->frame.getNumVertices() - 1); this->frame.addIndex(this->frame.getNumVertices() - 4);
			this->frame.addIndex(this->frame.getNumVertices() - 2); this->frame.addIndex(this->frame.getNumVertices() - 5);
			this->frame.addIndex(this->frame.getNumVertices() - 3); this->frame.addIndex(this->frame.getNumVertices() - 6);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.72);

	ofSetColor(239);
	this->mesh.drawFaces();

	ofSetColor(39);
	this->frame.drawWireframe();

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
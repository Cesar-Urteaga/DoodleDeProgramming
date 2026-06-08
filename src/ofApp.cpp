#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetLineWidth(1);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(100, 4);
	this->triangle_list.insert(this->triangle_list.end(), ico_sphere.getMesh().getUniqueFaces().begin(), ico_sphere.getMesh().getUniqueFaces().end());

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->frame.clear();

	for (int radius = 300; radius <= 400; radius += 10) {

		for (int i = 0; i < this->triangle_list.size(); i++) {

			glm::vec3 avg = (this->triangle_list[i].getVertex(0) + this->triangle_list[i].getVertex(1) + this->triangle_list[i].getVertex(2)) / 3;
			auto noise_value = ofNoise(glm::vec4(avg * 0.01, (radius / 20 + ofGetFrameNum()) * 0.003));

			if (noise_value > 0.45 && noise_value < 0.55) {

				vector<glm::vec3> vertices;
				vertices.push_back(glm::normalize(((this->triangle_list[i].getVertex(0) - avg) * 0.999) + avg) * (radius + 5));
				vertices.push_back(glm::normalize(((this->triangle_list[i].getVertex(1) - avg) * 0.999) + avg) * (radius + 5));
				vertices.push_back(glm::normalize(((this->triangle_list[i].getVertex(2) - avg) * 0.999) + avg) * (radius + 5));

				vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(0)) * (radius - 5));
				vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(1)) * (radius - 5));
				vertices.push_back(glm::normalize(this->triangle_list[i].getVertex(2)) * (radius - 5));

				this->mesh.addVertices(vertices);
				this->frame.addVertices(vertices);

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
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(ofGetFrameNum() * 0.72);
	ofRotateY(ofGetFrameNum() * 1.44);

	ofSetColor(0);
	this->mesh.drawFaces();

	ofSetColor(255);
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
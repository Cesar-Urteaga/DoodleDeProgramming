#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(25);
	ofSetWindowTitle("openframeworks");

	ofBackground(39);
	ofEnableDepthTest();

	this->frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}
//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();
	this->frame.clear();

	int x = -400;
	int y = 0;
	float noise_seed = ofRandom(1000);

	glm::highp_mat4 rotation;
	for (auto radius = 200; radius <= 300; radius += 10) {

		glm::highp_mat4 rotation;
		auto noise_value = ofNoise(noise_seed, y, ofGetFrameNum() * 0.006 - radius * 0.001);

		if (noise_value < 0.2) { noise_value = 0; }
		else if (noise_value < 0.4) { noise_value = ofMap(noise_value, 0.2, 0.4, 0, 0.5); }
		else if (noise_value < 0.6) { noise_value = 0.5; }
		else if (noise_value < 0.8) { noise_value = ofMap(noise_value, 0.6, 0.8, 0.5, 1.0); }
		else { noise_value = 1; }

		rotation = glm::rotate(glm::mat4(), ofMap(noise_value, 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

		this->setRingToMesh(this->face, this->frame, glm::vec3(x, y, 0), radius, 15, 1, rotation);
	}

	noise_seed = ofRandom(1000);
	for (auto radius = 50; radius <= 150; radius += 10) {

		glm::highp_mat4 rotation;
		auto noise_value = ofNoise(noise_seed, y, ofGetFrameNum() * 0.006 - radius * 0.001);

		if (noise_value < 0.2) { noise_value = 0; }
		else if (noise_value < 0.4) { noise_value = ofMap(noise_value, 0.2, 0.4, 0, 0.5); }
		else if (noise_value < 0.6) { noise_value = 0.5; }
		else if (noise_value < 0.8) { noise_value = ofMap(noise_value, 0.6, 0.8, 0.5, 1.0); }
		else { noise_value = 1; }

		rotation = glm::rotate(glm::mat4(), ofMap(noise_value, 0, 1, -360, 360) * (float)DEG_TO_RAD, glm::vec3(0, 1, 0));

		this->setRingToMesh(this->face, this->frame, glm::vec3(x, y, 0), radius, 15, 1, rotation);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	ofSetColor(0);
	this->face.draw();

	ofSetColor(239);
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
void ofApp::setRingToMesh(ofMesh& face_target, ofMesh& frame_target, glm::vec3 location, float radius, float width, float height, glm::highp_mat4 rotation) {

	int deg_span = 1;
	for (int deg = 0; deg < 360; deg += deg_span) {

		auto face_index = face_target.getNumVertices();

		vector<glm::vec3> vertices;
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius + width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius + width * 0.5) * cos(deg * DEG_TO_RAD), (radius + width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * -0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos((deg + deg_span) * DEG_TO_RAD), (radius - width * 0.5) * sin((deg + deg_span) * DEG_TO_RAD), height * 0.5));
		vertices.push_back(glm::vec3((radius - width * 0.5) * cos(deg * DEG_TO_RAD), (radius - width * 0.5) * sin(deg * DEG_TO_RAD), height * 0.5));

		for (auto& vertex : vertices) {

			vertex = glm::vec4(vertex + location, 0) * rotation;
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

		frame_target.addIndex(frame_index + 0); frame_target.addIndex(frame_index + 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
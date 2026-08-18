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

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float v_span = 0.1;
	int u_span = 20;
	float radius = 200;

	ofMesh face, line;
	ofColor face_color(0), line_color;
	line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

	for (float r = 70; r <= 80; r += 5) {

		for (float v = 0; v <= 360; v += v_span) {

			bool flag = true;
			int u_start = ofMap(ofNoise(radius * cos(v * DEG_TO_RAD) * 0.0005, radius * sin(v * DEG_TO_RAD) * 0.0005, ofGetFrameNum() * 0.002), 0, 1, -720, 720);
			int next_u = ofMap(ofNoise(radius * cos((v + v_span) * DEG_TO_RAD) * 0.0005, radius * sin((v + v_span) * DEG_TO_RAD) * 0.0005, ofGetFrameNum() * 0.002), 0, 1, -720, 720);
			for (int u = u_start; u < u_start + 360; u += u_span) {

				if (flag) {

					face.addVertex(this->make_point(radius, r, u, v));
					face.addVertex(this->make_point(radius, r, u + u_span, v));
					face.addVertex(this->make_point(radius, r, next_u + u_span, v + v_span));
					face.addVertex(this->make_point(radius, r, next_u, v + v_span));

					line.addVertex(this->make_point(radius, r, u, v));
					line.addVertex(this->make_point(radius, r, u + u_span, v));
					line.addVertex(this->make_point(radius, r, next_u + u_span, v + v_span));
					line.addVertex(this->make_point(radius, r, next_u, v + v_span));

					line_color.setHsb(ofMap(u, u_start, u_start + 360, 0, 255), 180, 255);

					face.addColor(face_color);
					face.addColor(face_color);
					face.addColor(face_color);
					face.addColor(face_color);

					line.addColor(line_color);
					line.addColor(line_color);
					line.addColor(line_color);
					line.addColor(line_color);

					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 3);
					face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

					line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 4);
					line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 3);
				}

				next_u += u_span;
				flag = !flag;
			}
		}
	}

	face.drawFaces();
	line.drawWireframe();

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
glm::vec3 ofApp::make_point(float R, float r, float u, float v) {

	// 数学デッサン教室 描いて楽しむ数学たち　P.31

	u *= DEG_TO_RAD;
	v *= DEG_TO_RAD;

	auto x = (R + r * cos(u)) * cos(v);
	auto y = (R + r * cos(u)) * sin(v);
	auto z = r * sin(u);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
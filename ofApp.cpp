#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);

	ofNoFill();
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	float radius = 250;
	float small_radius = 50;
	int deg_span = 3;
	int small_deg_span = 10;
	ofColor color;
	
	for (int small_deg = 0; small_deg < 360; small_deg += small_deg_span) {

		color.setHsb(ofMap(small_deg, 0, 360, 0, 255), 255, 200);
		ofSetColor(color);

		int tmp_small_deg = small_deg;
		int deg_max = ofNoise(small_deg * 0.005, ofGetFrameNum() * 0.005) * 360;
		vector<glm::vec3> vertices;
		vector<glm::vec3> sub_vertices;

		for (int deg = 0; deg < deg_max; deg += deg_span) {

			vertices.push_back(this->make_point(radius, small_radius, deg, tmp_small_deg));
			sub_vertices.push_back(this->make_point(radius, small_radius, deg, tmp_small_deg + small_deg_span));
			tmp_small_deg = tmp_small_deg + small_deg_span;
		}

		for (int i = sub_vertices.size() - 1; i > -1; i--) {

			vertices.push_back(sub_vertices[i]);
		}

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec3 ofApp::make_point(float radius, float small_radius, float deg, float small_deg) {

	float x_1 = radius * cos(deg * DEG_TO_RAD);
	float y_1 = radius * sin(deg * DEG_TO_RAD);

	float x_2 = small_radius * cos(small_deg * DEG_TO_RAD) * cos(deg * DEG_TO_RAD);
	float y_2 = small_radius * cos(small_deg * DEG_TO_RAD) * sin(deg * DEG_TO_RAD);

	float x = x_1 + x_2;
	float y = y_1 + y_2;
	float z = small_radius * sin(small_deg * DEG_TO_RAD);

	return glm::vec3(x, y, z);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
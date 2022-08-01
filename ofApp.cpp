#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(0);
	ofSetColor(200);
	ofNoFill();
	ofSetCircleResolution(60);
	ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	auto span = 10;
	for (auto radius = 150; radius <= 450; radius += 50) {

		auto small_radius = (radius * 2 * 3.14) / 360 * span;
		for (auto deg = 0; deg < 360; deg += span * 1.5) {

			auto base_location = glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
			ofNoFill();
			ofDrawCircle(base_location, 10);
			ofFill();
			ofDrawCircle(base_location, 5);

			ofSeedRandom(39);
			for (auto i = 0; i < 3; i++) {

				auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

				auto noise_radius = ofMap(ofNoise(noise_seed.x, base_location.x * 0.05, ofGetFrameNum() * 0.005), 0, 1, 0, small_radius);
				auto noise_deg = ofMap(ofNoise(noise_seed.y, base_location.y * 0.05, ofGetFrameNum() * 0.005), 0, 1, -360, 360);

				auto noise_location = glm::vec2(noise_radius * cos(noise_deg * DEG_TO_RAD), noise_radius * sin(noise_deg * DEG_TO_RAD));

				ofNoFill();
				ofDrawCircle(base_location + noise_location, 5);
				ofFill();
				ofDrawCircle(base_location + noise_location, 2);
				ofDrawLine(base_location, base_location + noise_location);
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}
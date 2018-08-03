#include "ofApp.h"

constexpr size_t ofApp::kRaw;
constexpr size_t ofApp::kCol;
constexpr float ofApp::kMinLineWidth;
constexpr float ofApp::kMaxLineWidth;
constexpr float ofApp::kNarrowingRatio;

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(60);
    ofSetVerticalSync(true);
    ofBackground(0);

    pfft_.setup();
    pfft_.setNumFFTBins(kRaw * kCol);
    pfft_.setNormalize(true);

    win_cache_.setSize(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update() {
    pfft_.update();
}

//--------------------------------------------------------------
void ofApp::draw() {
    std::vector<float> spectrum = pfft_.getSpectrum();

    float box_w = win_cache_.getWidth() / kCol;
    float box_h = win_cache_.getHeight() / kRaw;

    for (size_t i = 0; i < kRaw; ++i) {
        float top = box_h * i;

        for (size_t j = 0; j < kCol; ++j) {
            float left = box_w * j;
            float line_width = ofMap(spectrum.at((kCol * i) + j), 0.0, 1.0, kMinLineWidth, kMaxLineWidth);
            divideRect(left, top, box_w, box_h, line_width);
        }
    }
}

void ofApp::divideRect(float x, float y, float w, float h, int n) {
    float randw = ofRandom(w);
    float randh = ofRandom(h);
    ofSetLineWidth(n);
    ofSetColor(255);
    ofNoFill();

    if (w > h) {
        ofDrawLine(x + randw, y, x + randw, y + h);    // vertical
        if (n > 1) {
            divideRect(x,         y, randw,     h, n - kNarrowingRatio);    // left box
            divideRect(x + randw, y, w - randw, h, n - kNarrowingRatio);    // right box
        }
    } else {
        ofDrawLine(x, y + randh, x + w, y + randh);    // holizontal
        if (n > 1) {
            divideRect(x, y,         w, randh,     n - kNarrowingRatio);    // top box
            divideRect(x, y + randh, w, h - randh, n - kNarrowingRatio);    // bottom box
        }
    }
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key) {

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {
    win_cache_.setSize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

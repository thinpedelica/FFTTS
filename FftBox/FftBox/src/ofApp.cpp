#include "ofApp.h"

constexpr float    ofApp::kCamSpeed;
constexpr size_t   ofApp::kBoxNum;
constexpr float    ofApp::kBoxSizeBase;
constexpr uint32_t ofApp::KEventFrameCount;

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);

    win_cache_.setSize(ofGetWidth(), ofGetHeight());

    pfft_.setup();
    pfft_.setNormalize(true);
    pfft_.setNumFFTBins(kBoxNum);
    pfft_.update();

    roll_cam_.setup();
    roll_cam_.setCamSpeed(kCamSpeed);
}

//--------------------------------------------------------------
void ofApp::update(){
    pfft_.update();
    roll_cam_.update();

    if ((ofGetFrameNum() % KEventFrameCount) == 0) {
        updateBoxSize();
        updateCamPos();
    }
}

void ofApp::updateBoxSize() {
    boxes_.resize(kBoxNum);
    for (auto& box : boxes_) {
        float size = kBoxSizeBase * pfft_.getMidVal() * ofRandom(1.0, 10.0);
        box.setPosition(ofRandom(-win_cache_.getWidth() * 0.8, win_cache_.getWidth() * 0.8),
                        ofRandom(-win_cache_.getWidth() * 0.8, win_cache_.getWidth() * 0.8),
                        ofRandom(-win_cache_.getWidth() * 0.8, win_cache_.getWidth() * 0.8));
        box.setWidth(size);
        box.setHeight(size);
        box.setDepth(size);
    }
}

void ofApp::updateCamPos() {
    roll_cam_.setRandomScale(0.1, 2.0);
    roll_cam_.setRandomPos(270);
}

//--------------------------------------------------------------
void ofApp::draw(){
    roll_cam_.begin();

    ofSetColor(255, ofMap(pfft_.getMidVal(), 0.0, 1.0, 64, 255));
    ofSetLineWidth(ofMap(pfft_.getLowVal(), 0.0, 1.0, 1.0, 10.0));
    for (auto& box : boxes_) {
        box.drawWireframe();
    }

    roll_cam_.end();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    win_cache_.setSize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

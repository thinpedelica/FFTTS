#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);
    win_cache_.setSize(ofGetWidth(), ofGetHeight());

    pfft_.setup();
    pfft_.setNormalize(true);

    roll_cam_.setup();
    roll_cam_.setCamSpeed(0.1);

    threshold_ = kThreshold;
    lissajous_points_.resize(kLissajousPointNum);
}

//--------------------------------------------------------------
void ofApp::update(){
    roll_cam_.update();
    pfft_.update();

    if (pfft_.getLowVal() > threshold_) {
        roll_cam_.setRandomScale(kScaleMin, kScaleMax);
        roll_cam_.setRandomPos(270);
        updateLissajousParamsOverThreshold();
    } else {
        roll_cam_.setPos(roll_cam_.posT.x + 1, roll_cam_.posT.y + 1, roll_cam_.posT.z + 1);
        updateLissajousParamsUnderThreshold();
    }

    updateLissajousPoints();
}

void ofApp::updateLissajousParamsUnderThreshold() {
    freq_x_ = ofMap(ofGetFrameNum() % kFrameCycle, 1.0, kFrameCycle, 1.0, kFreqMaxX);
    freq_y_ = ofMap(ofGetFrameNum() % kFrameCycle, 1.0, kFrameCycle, 1.0, kFreqMaxY);
    freq_z_ = ofMap(ofGetFrameNum() % kFrameCycle, 1.0, kFrameCycle, 1.0, kFreqMaxZ);
    color_ = ofColor(255, 255, 255, 32);
}

void ofApp::updateLissajousParamsOverThreshold() {
    freq_x_ = ofMap(pfft_.getLowVal(), 0.0, 1.0, 1.0, kFreqMaxX);
    freq_y_ = ofMap(pfft_.getMidVal(), 0.0, 1.0, 1.0, kFreqMaxY);
    freq_z_ = ofMap(pfft_.getHighVal(), 0.0, 1.0, 1.0, kFreqMaxZ);
    color_ = ofColor(ofColor::fromHsb(ofRandom(0, 255), 255, 255), 32);
}

void ofApp::updateLissajousPoints() {
    float radius = win_cache_.getWidth() * kSizeRatio;

    float angle = 0;
    float angle_unit = TWO_PI / lissajous_points_.size();
    for (auto& lissajous_point : lissajous_points_) {
        float x = sin(angle * freq_x_) * sin(angle * 2) * radius;
        float y = sin(angle * freq_y_) * cos(angle * 2) * radius;
        float z = sin(angle * freq_z_) * radius;
        lissajous_point = ofVec3f(x, y, z);
        angle += angle_unit;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    roll_cam_.begin();
    ofBeginShape();
    ofSetColor(color_);
    ofFill();
    for (size_t i = 0; i < lissajous_points_.size() - 2; ++i) {
        if (i % 3 == 0) {
            ofVertex(0, 0, 0);
            ofVertex(lissajous_points_.at(i).x,     lissajous_points_.at(i).y,     lissajous_points_.at(i).z);
            ofVertex(lissajous_points_.at(i + 2).x, lissajous_points_.at(i + 2).y, lissajous_points_.at(i + 2).z);
        }
    }
    ofEndShape();
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

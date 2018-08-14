#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);

    win_cache_.setSize(ofGetWidth(), ofGetHeight());

    pfft_.setup();
    pfft_.setNormalize(true);

    setTrianglePos(win_cache_.getWidth() * 0.5,
                   win_cache_.getHeight() * 0.5,
                   win_cache_.getHeight() * 0.5,
                   true,
                   pos1_, pos2_, pos3_);
    fpos1_ = pos1_;
    fpos2_ = pos2_;
    fpos3_ = pos3_;
}

//--------------------------------------------------------------
void ofApp::update(){
    pfft_.update();
    updateByRadnomPos(fpos1_, fpos2_, fpos3_);
    translatePos(fpos1_, fpos2_, fpos3_,
                 pos1_,  pos2_,  pos3_);
}

void ofApp::setTrianglePos(const float x_base, const float y_base, const float length, const bool is_up,
                           ofVec2f& pos1, ofVec2f& pos2, ofVec2f& pos3) {
    float y3 = length * 0.5 * tan(ofDegToRad(60));
    if (is_up) {
        y3 = -y3;
    }

    pos1 = ofVec2f(x_base,   y_base);
    pos2 = ofVec2f(pos1_.x + length,   pos1.y);
    pos3 = ofVec2f(pos1_.x + (pos2.x - pos1.x) * 0.5,   pos1.y + y3);
}

void ofApp::updateByRadnomPos(ofVec2f& pos1, ofVec2f& pos2, ofVec2f& pos3) {
    if (pfft_.getLowVal() > kUpdateThreshold) {
        setTrianglePos(ofRandom(win_cache_.getWidth()  * 0.5, win_cache_.getWidth()   * 0.75),
                       ofRandom(win_cache_.getHeight() * 0.25, win_cache_.getHeight() * 0.75),
                       ofRandom(win_cache_.getHeight() * 0.25, win_cache_.getHeight() * 0.40),
                       true,
                       pos1, pos2, pos3);
    } else if (pfft_.getMidVal() > kUpdateThreshold) {
        setTrianglePos(ofRandom(win_cache_.getWidth()  * 0.1, win_cache_.getWidth()   * 0.5),
                       ofRandom(win_cache_.getHeight() * 0.1, win_cache_.getHeight()  * 0.75),
                       ofRandom(win_cache_.getHeight() * 0.25, win_cache_.getHeight() * 0.40),
                       false,
                       pos1, pos2, pos3);
    }
}

void ofApp::translatePos(const ofVec2f& fpos1, const ofVec2f& fpos2, const ofVec2f& fpos3,
                         ofVec2f& pos1, ofVec2f& pos2, ofVec2f& pos3) {
    pos1 += (fpos1 - pos1) * 0.01;
    pos2 += (fpos2 - pos2) * 0.01;
    pos3 += (fpos3 - pos3) * 0.01;
}
//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255);
    drawTriangles(pos1_, pos2_, pos3_);
    drawLines(pos1_, pos2_, pos3_);
}

void ofApp::drawTriangles(const ofVec2f& pos1, const ofVec2f& pos2, const ofVec2f& pos3) {
    ofSetLineWidth(ofMap(pfft_.getLowVal(), 0.0f, 1.0f, 1.0f, 5.0f));
    ofNoFill();
    ofDrawTriangle(pos1, pos2, pos3);

    if (pfft_.getMidVal() > kDrawThreshold) {
        ofSetLineWidth(1);
        float num = ofMap(pfft_.getMidVal(), 0.0f, 1.0f, 1.0f, 100.0f);
        for (size_t i = 0; i < static_cast<size_t>(num); ++i) {
            ofVec2f pos11 = ofVec2f(ofRandom(pos1.x - 20.0f, pos1.x + 20.0f),
                                    ofRandom(pos1.y - 20.0f, pos1.y + 20.0f));
            ofVec2f pos22 = ofVec2f(ofRandom(pos2.x - 20.0f, pos2.x + 20.0f),
                                    ofRandom(pos2.y - 20.0f, pos2.y + 20.0f));
            ofVec2f pos33 = ofVec2f(ofRandom(pos3.x - 20.0f, pos3.x + 20.0f),
                                    ofRandom(pos3.y - 20.0f, pos3.y + 20.0f));
            ofDrawTriangle(pos11, pos22, pos33);
        }
    }
}

void ofApp::drawLines(const ofVec2f& pos1, const ofVec2f& pos2, const ofVec2f& pos3) {
    ofSetLineWidth(ofMap(pfft_.getMidVal(), 0.0f, 1.0f, 0.5f, 4.0f));
    float w = pos2.x - pos3.x;
    if (w < kMinWidth) {
        w = kMinWidth;
    }
    float w_unit  = w * 0.1;
    float w_space = w * 0.3;

    float k1 = (pos2.y - pos3.y) / (pos2.x - pos3.x);
    float k2 = (pos1.y - pos3.y) / (pos1.x - pos3.x);

    // bottom of triangle(left, right)
    for (float x1 = pos1.x + w_space; x1 < pos2.x; x1 += w_unit) {
        float y1 = pos1.y;
        float y2 = win_cache_.getHeight();
        float x2 = x1 - (y2 - y1) / k1;
        ofDrawLine(x1, y1, x2, y2);

        float x3 = x1 + (y2 - y1) / k1;
        ofDrawLine(x1, y1, x3, y2);
    }

    // top of triangle(left, right)
    for (float x1 = pos1.x; x1 < pos2.x - w_space; x1 += w_unit) {
        float y1 = pos1.y;
        float y2 = 0;
        float x2 = x1 - (y2 - y1) / k1;
        ofDrawLine(x1, y1, x2, y2);

        float x3 = x1 + (y2 - y1) / k1;
        ofDrawLine(x1, y1, x3, y2);
    }

    {
        // left
        float end_pos = pos1.x - w_space;
        float start_pos = end_pos - (end_pos * pfft_.getMidVal());
        for (float x1 = start_pos; x1 < end_pos; x1 += w_unit) {
            float y1 = pos1.y;
            float y2 = 0;
            float x2 = x1 - (y2 - y1) / k1;
            float y3 = win_cache_.getHeight();
            float x3 = x1 - (y3 - y1) / k1;
            ofDrawLine(x2, y2, x3, y3);
        }
    }

    {
        // right
        float start_pos = pos2.x + w_space;
        float end_pos = start_pos + (win_cache_.getWidth() - start_pos) * pfft_.getMidVal();
        for (float x1 = start_pos; x1 < end_pos; x1 += w_unit) {
            float y1 = pos1.y;
            float y2 = 0;
            float x2 = x1 + (y2 - y1) / k1;
            float y3 = win_cache_.getHeight();
            float x3 = x1 + (y3 - y1) / k1;
            ofDrawLine(x2, y2, x3, y3);
        }
    }
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

#include "ofApp.h"

constexpr size_t ofApp::kGridCol;
constexpr size_t ofApp::kGridRow;
constexpr size_t ofApp::kGridNum;
constexpr float  ofApp::kGridColHalf;
constexpr float  ofApp::kGridRowHalf;
constexpr float  ofApp::kGridHeight;
constexpr float  ofApp::kPointSizeMin;
constexpr float  ofApp::kPointSizeMax;
constexpr float  ofApp::kFOVBase;
constexpr float  ofApp::kCamPosBaseX;
constexpr float  ofApp::kCamPosBaseY;
constexpr float  ofApp::kCamPosBaseZ;
constexpr float  ofApp::kTransCamSpeed;

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackground(0);
    win_cache_.setSize(ofGetWidth(), ofGetHeight());

    pfft_.setup();
    pfft_.setNumFFTBins(kGridCol);
    pfft_.setNormalize(true);

    fft_history_.resize(kGridRow);
    for (auto& fft_item : fft_history_) {
        fft_item.assign(kGridCol, 0.0);
    }

    for (int i = 0; i < kGridCol; ++i) {
        for (int j = 0; j < kGridRow; ++j) {
            float x = static_cast<float>(i) - kGridColHalf;
            float y = static_cast<float>(j) - kGridRowHalf;
            vertex_[kGridRow * i + j].set(x, y);
            color_[kGridRow * i + j].set(0.5, 0.8, 1.0, 0.2);
        }
    }

    for (int i = 0; i < kGridCol; ++i) {
        vbo_[i].setVertexData(vertex_, kGridRow, GL_DYNAMIC_DRAW);
        vbo_[i].setColorData(color_,   kGridRow, GL_DYNAMIC_DRAW);
    }

    point_size_ = 0.0f;
    is_line_ = false;

    roll_cam_.setup();
    roll_cam_.setCamSpeed(kTransCamSpeed);
    initializeCamPosList();
    resetCamPos();
}

//--------------------------------------------------------------
void ofApp::update() {
    pfft_.update();
    fft_history_.push_back(pfft_.getSpectrum());
    fft_history_.erase(fft_history_.begin(), fft_history_.begin() + 1);

    for (int i = 0; i < kGridCol; ++i) {
        for (int j = 0; j < kGridRow; ++j) {
            float fft_val = fft_history_.at(j).at(i);
            float x = static_cast<float>(i) - kGridColHalf;
            float y = static_cast<float>(j) - kGridRowHalf;
            float z = fft_val * kGridHeight;

            vertex_[kGridCol * i + j] = ofVec3f(x, y, z);
            color_[kGridCol * i + j].set(0.5 + 0.5 * fft_val,
                                         0.8,
                                         1.0,
                                         0.2 + 0.8 * fft_val);
        }
    }

    for (int i = 0; i < kGridCol; ++i) {
        vbo_[i].updateVertexData(&vertex_[kGridRow * i], kGridRow);
        vbo_[i].updateColorData(&color_[kGridRow * i], kGridRow);
    }

    point_size_ = ofMap(pfft_.getLowVal(), 0.0f, 1.0f, kPointSizeMin, kPointSizeMax);

    roll_cam_.update();
    updateFov();
}

//--------------------------------------------------------------
void ofApp::draw() {
    ofPushMatrix();
    ofTranslate(win_cache_.getWidth() / 2, win_cache_.getHeight() / 2);

    cam_.begin();
    cam_.setFov(fov_);
    cam_.lookAt(target_);
    cam_.setPosition(cam_pos_);
    roll_cam_.begin();

    glPointSize(point_size_);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    for (int i = 0; i < kGridRow; ++i) {
        if (is_line_) {
            vbo_[i].draw(GL_LINE_STRIP, 0, kGridCol);
        } else {
            vbo_[i].draw(GL_POINTS, 0, kGridCol);
        }
    }

    roll_cam_.end();
    cam_.end();
    ofPopMatrix();
}

//--------------------------------------------------------------
void ofApp::resetCamPos(const size_t index) {
    target_  = ofVec3f(win_cache_.getWidth() / 2, 
                       win_cache_.getHeight() / 2);
    cam_pos_ = ofVec3f(kCamPosBaseX + win_cache_.getWidth() / 2, 
                       kCamPosBaseY + win_cache_.getHeight() / 2,
                       kCamPosBaseZ);

    cam_pos_index_ = index;
    fov_ = cam_pos_list_.at(cam_pos_index_).fov;
    translateCamPos();
}

void ofApp::initializeCamPosList() {
    cam_pos_list_.push_back(CamPose( 60.0, ofVec3f(  0.0, 0.0,   0.0)));
    cam_pos_list_.push_back(CamPose( 30.0, ofVec3f(-10.0, 0.0,   0.0)));
    cam_pos_list_.push_back(CamPose(150.0, ofVec3f(  0.0, 0.0,   0.0)));
    cam_pos_list_.push_back(CamPose(120.0, ofVec3f(  0.0, 0.0, 150.0)));
    cam_pos_list_.push_back(CamPose(160.0, ofVec3f(  0.0, 0.0, 150.0)));
    cam_pos_list_.push_back(CamPose(120.0, ofVec3f(-15.0, 0.0,   0.0)));
    cam_pos_list_.push_back(CamPose( 90.0, ofVec3f(  0.0, 0.0,   0.0)));
}

void ofApp::translateCamPos() {
    roll_cam_.setPos(cam_pos_list_.at(cam_pos_index_).rotate.x,
                     cam_pos_list_.at(cam_pos_index_).rotate.y,
                     cam_pos_list_.at(cam_pos_index_).rotate.z);
}

void ofApp::updateFov() {
    fov_ -= (fov_ - cam_pos_list_.at(cam_pos_index_).fov) * kTransCamSpeed;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
    if (key == 'g') {
        is_line_ = !is_line_;
    }

    if (key == 'x') {
        ++cam_pos_index_;
        if (cam_pos_index_ >= cam_pos_list_.size()) {
            cam_pos_index_ = 0;
        }
        translateCamPos();
    }
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
    resetCamPos(cam_pos_index_);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

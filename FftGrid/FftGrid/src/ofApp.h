#pragma once

#include "ofMain.h"
#include "ofxProcessFft.h"
#include "ofxRollingCam.h"

class ofApp : public ofBaseApp {

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

private:
    static constexpr size_t kGridRow = 256;
    static constexpr size_t kGridCol = 256;
    static constexpr size_t kGridNum = kGridRow * kGridCol;
    static constexpr float  kGridRowHalf = kGridRow / 2;
    static constexpr float  kGridColHalf = kGridCol / 2;
    static constexpr float  kGridHeight  = kGridRow / 4;

    static constexpr float  kPointSizeMin = 1.0f;
    static constexpr float  kPointSizeMax = 4.0f;

    static constexpr float kFOVBase = 60.f;
    static constexpr float kCamPosBaseX = 0.f;
    static constexpr float kCamPosBaseY = -kGridRowHalf;
    static constexpr float kCamPosBaseZ = kGridHeight / 2;

    static constexpr float kTransCamSpeed = 0.1f;

    void resetCamPos(const size_t index = 0);
    void initializeCamPosList();
    void translateCamPos();
    void updateFov();

    ProcessFFT pfft_;
    vector<vector<float> > fft_history_;

    ofVbo vbo_[kGridRow];
    ofVec3f vertex_[kGridNum];
    ofFloatColor color_[kGridNum];
    float point_size_;
    bool is_line_;

    ofRectangle win_cache_;

    ofEasyCam cam_;
    float fov_;
    ofVec3f target_;
    ofVec3f cam_pos_;

    ofxRollingCam roll_cam_;
    struct CamPose {
        float fov;
        ofVec3f rotate;

        CamPose() : fov(60.0), rotate(0.0, 0.0, 0.0) {}
        CamPose(float f, ofVec3f r) : fov(f), rotate(r) {}
    };

    std::vector<CamPose> cam_pos_list_;
    size_t cam_pos_index_;
};

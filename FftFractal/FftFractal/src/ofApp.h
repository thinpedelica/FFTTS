#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"

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
    static constexpr size_t kRaw = 4;
    static constexpr size_t kCol = 8;
    static constexpr float kMinLineWidth   =  2.0f;
    static constexpr float kMaxLineWidth   = 10.0f;
    static constexpr float kNarrowingRatio =  0.1f;

    void divideRect(float x, float y, float w, float h, int n);

    ProcessFFT pfft_;
};

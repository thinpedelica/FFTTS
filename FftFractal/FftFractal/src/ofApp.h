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
    static const size_t kRaw;
    static const size_t kCol;
    static const float kMinLineWidth;
    static const float kMaxLineWidth;
    static const float kNarrowingRatio;

    void divideRect(float x, float y, float w, float h, int n);

    ProcessFFT pfft_;
};

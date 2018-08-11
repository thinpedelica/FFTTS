#pragma once

#include "ofMain.h"
#include "ofxRollingCam.h"
#include "ofxProcessFFT.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
private:
    static constexpr float kThreshold = 0.5f;
    static constexpr int   kLissajousPointNum = 480;
    static constexpr float kSizeRatio = 0.25f;
    static constexpr float kScaleMin  = 0.2f;
    static constexpr float kScaleMax  = 2.0f;
    static constexpr int   kFrameCycle = 1260;
    static constexpr float kFreqMaxX   = 1.0f;
    static constexpr float kFreqMaxY   = 2.0f;
    static constexpr float kFreqMaxZ   = 4.0f;

    void updateLissajousParamsUnderThreshold();
    void updateLissajousParamsOverThreshold();
    void updateLissajousPoints();

    ofRectangle win_cache_;
    ProcessFFT pfft_;
    ofxRollingCam roll_cam_;

    float threshold_;

    std::vector<ofVec3f> lissajous_points_;
    float freq_x_;
    float freq_y_;
    float freq_z_;
    ofColor color_;
};

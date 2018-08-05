#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"
#include "ofxRollingCam.h"

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
    static constexpr float    kCamSpeed = 0.1f;
    static constexpr size_t   kBoxNum = 100;
    static constexpr float    kBoxSizeBase = 500.0;
    static constexpr uint32_t KEventFrameCount = 100;

    void updateBoxSize();
    void updateCamPos();

    ofRectangle win_cache_;
    ProcessFFT pfft_;
    ofxRollingCam roll_cam_;

    std::vector<ofBoxPrimitive> boxes_;
};

#pragma once

#include "ofMain.h"
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
    static constexpr float kUpdateThreshold = 0.5f;
    static constexpr float kDrawThreshold = 0.2f;
    static constexpr float kMinWidth = 10.0f;

    void setTrianglePos(const float x_base, const float y_base, const float length, const bool is_up,
                        ofVec2f& pos1, ofVec2f& pos2, ofVec2f& pos3);
    void updateByRadnomPos(ofVec2f& pos1, ofVec2f& pos2, ofVec2f& pos3);
    void translatePos(const ofVec2f& fpos1, const ofVec2f& fpos2, const ofVec2f& fpos3,
                      ofVec2f& pos1, ofVec2f& pos2, ofVec2f& pos3);

    void drawTriangles(const ofVec2f& pos1, const ofVec2f& pos2, const ofVec2f& pos3);
    void drawLines(const ofVec2f& pos1, const ofVec2f& pos2, const ofVec2f& pos3);

    ofRectangle win_cache_;
    ProcessFFT pfft_;

    ofVec2f pos1_, pos2_, pos3_;
    ofVec2f fpos1_, fpos2_, fpos3_;
};

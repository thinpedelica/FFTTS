#pragma once

#include "ofMain.h"
#include "Particle.h"
#include "ofxProcessFft.h"

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
    static constexpr int kBasePointNum =  500;
    static constexpr int kParticleNum  = 7000;

    void createBasePoint(const int num);
    void createDotPoint(const int num);
    void createParticle(const int num);

    void drawLineBetweenDots(const float level_val);
    void drawCircleOnDots(const float level_val);

    ofRectangle win_cache_;
    ProcessFFT pfft_;

    vector<ofVec2f> base_points_;
    vector<ofVec2f> dot_points_;
    std::unique_ptr<Particles> particles_ptr_;

    float friction_;
    float speed_;
};

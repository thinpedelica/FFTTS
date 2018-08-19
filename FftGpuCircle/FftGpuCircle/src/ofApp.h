#pragma once

#include "ofMain.h"
#include "ofxProcessFFT.h"
#include "pingPongBuffer.h"
#include "ofxGui.h"

#define _PROGRAMMABLE_RENDERER

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
    static constexpr size_t kParticleNum = 1000000;
    static constexpr float  kRadius = 400.f;
    static constexpr float  kMovingVelocity = 10.f;
    static constexpr float  kDecelerationRatio = 0.98f;

    void setupPingPongBuffer(const size_t texture_resolution);
    void setupParticleMesh(const size_t texture_resolution);
    void setupBoardMesh(const size_t texture_resolution);

    void updateParticlePos(const ofVec2f& target_pos, const float velocity, const bool is_move);

    void drawParticle(const ofColor& color);

    ofRectangle win_cache_;
    ProcessFFT pfft_;
    ofEasyCam cam_;

    PingPongBuffer ping_pong_buffer_;
    ofShader update_shader_;
    ofShader draw_shader_;

    ofVboMesh particle_mesh_;
    ofVboMesh board_mesh_;

    float   particle_velocity_;
    ofColor particle_color_;

    ofxPanel gui_;
    ofxFloatSlider target_pos_;


};

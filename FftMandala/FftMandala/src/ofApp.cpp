#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    ofSetCircleResolution(64);
    ofEnableSmoothing();
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    ofSetFrameRate(10);

    mandala_drawer_.setup();
    nano_kon_.setup();
}

//--------------------------------------------------------------
void ofApp::update(){
    nano_kon_.update();
    float base_color      = nano_kon_.knobs.at(0) * 2.0;
    float brightness_min  = nano_kon_.knobs.at(1) * 2.0;
    float brightness_max  = nano_kon_.knobs.at(2) * 2.0;
    float stroke_weight   = nano_kon_.knobs.at(3) * 0.01;
    float circle_div_base = nano_kon_.knobs.at(4) / 4.0;
    mandala_drawer_.update(base_color,
                           brightness_min,
                           brightness_max,
                           stroke_weight,
                           circle_div_base);
}

//--------------------------------------------------------------
void ofApp::draw(){
    mandala_drawer_.draw();
}

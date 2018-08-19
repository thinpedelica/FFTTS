#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofSetBackgroundColor(0);

    win_cache_.setSize(ofGetWidth(), ofGetHeight());

    pfft_.setup();
    pfft_.setNormalize(true);

    update_shader_.load("shader/update");
    draw_shader_.load("shader/draw");

    size_t texture_resolution = ceil(sqrt(kParticleNum));
    setupPingPongBuffer(texture_resolution);
    setupParticleMesh(texture_resolution);
    setupBoardMesh(texture_resolution);

    gui_.setup();
    gui_.add(target_pos_.setup("pos", 20, 0, 30));
}

void ofApp::setupPingPongBuffer(const size_t texture_resolution) {
    ping_pong_buffer_.allocate(texture_resolution, texture_resolution, GL_RGBA32F_ARB);

    float* initial_values = new float[texture_resolution * texture_resolution * 4];
    for (size_t i = 0; i < texture_resolution; ++i) {
        for (size_t j = 0; j < texture_resolution; ++j) {
            size_t index = texture_resolution * i + j;
            float  radius = kRadius * static_cast<float>(i) / static_cast<float>(texture_resolution) - kRadius;
            float  angle = 360.f * static_cast<float>(j) / static_cast<float>(texture_resolution);

            initial_values[index * 4 + 0] = radius * sin(angle);
            initial_values[index * 4 + 1] = radius * cos(angle);
            initial_values[index * 4 + 2] = 0.f; // x vec
            initial_values[index * 4 + 3] = 0.f; // y vec
        }
    }
    ping_pong_buffer_.src->getTextureReference(0).loadData(initial_values, texture_resolution, texture_resolution, GL_RGBA);

    delete[] initial_values;
}

void ofApp::setupParticleMesh(const size_t texture_resolution) {
    particle_mesh_.setMode(OF_PRIMITIVE_POINTS);
    for (size_t i = 0; i < texture_resolution; ++i) {
        for (size_t j = 0; j < texture_resolution; ++j) {
            particle_mesh_.addVertex(ofVec3f(0, 0, 0));
            particle_mesh_.addTexCoord(ofVec2f(i, j));
        }
    }
}

void ofApp::setupBoardMesh(const size_t texture_resolution) {
    board_mesh_.setMode(OF_PRIMITIVE_TRIANGLES);
    board_mesh_.addVertex(ofVec3f(-1.f, -1.f, 0.f));
    board_mesh_.addVertex(ofVec3f( 1.f, -1.f, 0.f));
    board_mesh_.addVertex(ofVec3f( 1.f,  1.f, 0.f));
    board_mesh_.addVertex(ofVec3f(-1.f,  1.f, 0.f));
    board_mesh_.addTexCoord(ofVec2f(0.f,                0.f));
    board_mesh_.addTexCoord(ofVec2f(texture_resolution, 0.f));
    board_mesh_.addTexCoord(ofVec2f(texture_resolution, texture_resolution));
    board_mesh_.addTexCoord(ofVec2f(0.f,                texture_resolution));
    board_mesh_.addIndex(0);
    board_mesh_.addIndex(1);
    board_mesh_.addIndex(2);
    board_mesh_.addIndex(0);
    board_mesh_.addIndex(2);
    board_mesh_.addIndex(3);
}

//--------------------------------------------------------------
void ofApp::update(){
    pfft_.update();

    // to generate circular motion
//    ofVec2f target_pos{ ofRandom(-2.0, 2.0), ofRandom(-2.0, 2.0) };
    ofVec2f target_pos{ ofRandom(-target_pos_, target_pos_), ofRandom(-target_pos_, target_pos_) };

    bool is_move_particle = false;
    if (pfft_.getLowVal() > 0.2f) {
        is_move_particle = true;
    } else if (pfft_.getMidVal() > 0.2f) {
        is_move_particle = true;
    }

    if (is_move_particle) {
        particle_velocity_ = kMovingVelocity;
    } else {
        particle_velocity_ *= kDecelerationRatio;
    }

    particle_color_.setHsb(ofMap(pfft_.getMidVal(), 0.0, 1.0, 128, 255), 255, 255, 128);
    updateParticlePos(target_pos, particle_velocity_, is_move_particle);
}

void ofApp::updateParticlePos(const ofVec2f& target_pos, const float velocity, const bool is_move) {
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_BLEND);

    ping_pong_buffer_.dst->begin();
    ping_pong_buffer_.dst->activateAllDrawBuffers();
    ofClear(0);

    update_shader_.begin();
    update_shader_.setUniformTexture("u_pos_tex", ping_pong_buffer_.src->getTextureReference(0), 0);
    update_shader_.setUniform2fv("u_target_pos",  target_pos.getPtr());
    update_shader_.setUniform1f("u_velocity",     velocity);
    update_shader_.setUniform1i("u_is_move",      is_move);
    board_mesh_.draw();
    update_shader_.end();

    ping_pong_buffer_.dst->end();
    ping_pong_buffer_.swap();

    glPopAttrib();
}

//--------------------------------------------------------------
void ofApp::draw(){
    cam_.begin();
    drawParticle(particle_color_);
    cam_.end();

    // gui_.draw();
}

void ofApp::drawParticle(const ofColor& color) {
    ofSetColor(color);

    ofPushStyle();
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    ofEnablePointSprites();

    draw_shader_.begin();
    draw_shader_.setUniformTexture("u_pos_tex", ping_pong_buffer_.src->getTextureReference(0), 0);
    particle_mesh_.draw();
    draw_shader_.end();

    ofDisablePointSprites();
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    win_cache_.setSize(w, h);
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

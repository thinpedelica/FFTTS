#pragma once

#include "ofMain.h"
#include "mandala.h"
#include "nanoKon2.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

private:
	MandalaDrawer mandala_drawer_;
	NanoKon2 nano_kon_;
};

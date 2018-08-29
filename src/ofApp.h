#pragma once

#include "ofMain.h"
#include "ofxGui.h"

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
    
    void dragonFlyDecision();
    
    ofxFloatSlider directionVar, speedMin, speedMax, distanceMin, distanceMax, waitTime, currentAltitude;
    ofxPanel guiFlight ;
    float flyWidth, flyLength, currentWaitTime, currentSpeed, currentHeading;
    bool b_drawGui;
    ofVec2f currentLoc, currentVec;
    
    int worldX, worldY, worldZ;    
    ofEasyCam cam;
    ofBoxPrimitive worldBox, flyBody;
    ofPlanePrimitive worldFloor;
    ofLight worldLight;
};

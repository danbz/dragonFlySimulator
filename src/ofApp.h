#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class dragonFly {
    
public:
    float flyWidth, flyLength, currentWaitTime, currentSpeed, currentHeading, directionVar, speedMin, speedMax, distanceMin, distanceMax, waitTime, currentAltitude;
    ofVec2f currentLoc, currentVec;
    ofSpherePrimitive flyHead;
    ofBoxPrimitive flyBody;
    int worldX, worldY, worldZ;
    
    void decision();
    void update();
    void draw();
    void reset();
};

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
    
    
    //ofxFloatSlider directionVar, speedMin, speedMax, distanceMin, distanceMax, waitTime, currentAltitude;
    ofxPanel guiFlight ;
   
    bool b_drawGui;
    int worldX, worldY, worldZ;

    ofEasyCam cam;
    ofBoxPrimitive worldBox;
    ofPlanePrimitive worldFloor;
    ofLight worldLight;
    dragonFly fly1;
};

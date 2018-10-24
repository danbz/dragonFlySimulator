#pragma once

#include "ofMain.h"
#include "ofxGui.h"


class dragonFly {
    
public:
    float width, length, currentWaitTime, currentSpeed, currentHeading, directionVar, speedMin, speedMax, distanceMin, distanceMax, waitTime, currentAltitude;
    ofVec2f currentLoc, currentVec;
    ofSpherePrimitive head;
    ofConePrimitive body;
    ofColor headColor, bodyColor;
    int worldX, worldY, worldZ;
    string name;
    
    dragonFly(); // dragonFly constructor
    ~dragonFly(); //dragonFly destructor
    
    void decision();
    void update();
    void draw();
    void reset();
    void setName(string newName);
    
    ofTrueTypeFont      flyFont;
    
    
    
    
};

// ---------------------------------------------
class LyricWord {
public:
    string  word;
    int     occurrences;
    
};
// ---------------------------------------------


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
    //dragonFly fly1, fly2;
    
    vector<dragonFly> flies;
    ofTrueTypeFont      font;

    string              flyNames;
    
    // adding elements to load and sort text files
    string              sortTypeInfo;
    vector <LyricWord>  words;
    
    static bool sortOnABC(const LyricWord &a, const LyricWord &b);
    static bool sortOnOccurrences(const LyricWord &a, const LyricWord &b);
    static bool sortOnLength(const LyricWord &a, const LyricWord &b);
    static bool removeWordIf(LyricWord &wrd);
    
    
    void setupWords(string content);
    void processOpenFileSelection(ofFileDialogResult openFileResult);
    string originalFileExtension;
    
};

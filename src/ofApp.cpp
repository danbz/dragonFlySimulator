#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    // define dragonfly size and world size
    flyWidth = 3.0;
    flyLength = 20.0;
    worldWidth =   ofGetScreenWidth();
    worldHeight= ofGetScreenHeight();
    
    // set up gui and sliders
    guiFlight.setup();
    guiFlight.add(directionVar.setup("directionVariance", 180, 1, 360));
    guiFlight.add(speedMin.setup("speedMin", 1.0, 0.1, 2));
    guiFlight.add(speedMax.setup("speedMax", 2.0, 2, 10));
    guiFlight.add(waitTime.setup("waitTime", 2000.0, 100, 10000));
    
    // choose initial conditions
    currentHeading = ofRandom(360.0);
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    currentLoc = ofVec2f(worldWidth/2,worldHeight/2);
    currentVec = ofVec2f(0,0);
    ofSetBackgroundColor(0);
    
    b_drawGui = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec2f v1(0, 1);
    
    if (ofGetSystemTimeMillis() > currentWaitTime) {
        dragonFlyDecision();
    }
    
    if (currentLoc.x < 0 && currentVec.x <0) {
        currentVec.x +=  2* abs(currentVec.x);
        currentHeading = v1.angle(currentVec);
    } else if (currentLoc.x > worldWidth && currentVec.x > 0){
        currentVec.x -=  2* abs(currentVec.x);
        currentHeading = v1.angle(currentVec);
    } else if (currentLoc.y <0 && currentVec.y <0) {
        currentVec.y += 2* abs(currentVec.y);
        currentHeading = v1.angle(currentVec);
    } else if (currentLoc.y >worldHeight && currentVec.y >0){
        currentVec.y -= 2* abs(currentVec.y);
        currentHeading = v1.angle(currentVec);
    }
    
    currentLoc += currentVec*currentSpeed;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofPushMatrix();
    ofTranslate(currentLoc);
    ofRotateZDeg(currentHeading);
    ofSetColor(128,128,0);
    ofDrawRectangle(0,0, flyWidth, flyLength); // draw dragonfly body
    ofSetColor(173,255,47);
    ofDrawCircle(flyWidth/2, flyLength, flyWidth); // draw dragonfly head
    ofPopMatrix();
    
    if (b_drawGui){
        stringstream flyStatus;
        flyStatus << "heading: " << currentHeading << " vec: " << currentVec << " loc: " << currentLoc << endl;
        ofDrawBitmapString(flyStatus.str(), 20,  20);
        guiFlight.draw();
    }
}

//--------------------------------------------------------------
void ofApp::dragonFlyDecision(){
    // choose new direction, speed and waittime
    currentHeading = currentHeading +  ofRandom(directionVar) - (directionVar/2);
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    
    //generate vector from heading
    ofVec2f v1(0, 1);
    currentVec = v1.getRotated(currentHeading); //
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
    switch (key) {
        case 'g':
        case 'G':
            b_drawGui =!b_drawGui;
            break;
            
        case 'f':
        case 'F':
            ofToggleFullscreen();
            worldWidth =  ofGetScreenWidth();
            worldHeight =  ofGetScreenHeight();
            break;
            
        case ' ': // reset location
            currentLoc = ofVec2f(worldWidth/2,worldHeight/2);
            break;
    }
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
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 
    
}

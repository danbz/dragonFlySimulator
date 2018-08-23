#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    flyWidth = 5.0;
    flyLength = 30.0;
    worldWidth =   ofGetScreenWidth();
    worldHeight= ofGetScreenHeight();
    worldWidth =   800;
    worldHeight= 800;
  
    
    guiFlight.setup();
    guiFlight.add(directionVar.setup("directionVariance", 180, 1, 360));
//    guiFlight.add(distanceMin.setup("distanceMin", 5.0, 1, 100));
//    guiFlight.add(distanceMax.setup("distanceMax", 800.0, 10, 1200));
    guiFlight.add(speedMin.setup("speedMin", 0.1, 1.0, 2));
    guiFlight.add(speedMax.setup("speedMax", 2.0, 3, 10));
    guiFlight.add(waitTime.setup("waitTime", 2000.0, 100, 10000));
    
    // choose initial conditions
    currentHeading = ofRandom(360.0);
    currentDistance = ofRandom(distanceMin, distanceMax);;
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    currentLoc = ofVec2f(worldWidth/2,worldHeight/2);
    currentVec = ofVec2f(0,0);
    ofSetBackgroundColor(0);
    
    b_drawGui = true;
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (ofGetSystemTimeMillis() > currentWaitTime) {
        dragonFlyDecision();
    }
    
    if (currentLoc.x < 0 && currentVec.x <0) {
        currentVec.x +=  currentVec.x += currentVec.x;
    } else if (currentLoc.x > worldWidth && currentVec.x > 0){
        currentVec.x -=  currentVec.x -= currentVec.x;
    } else if (currentLoc.y <0 && currentVec.y <0) {
        currentVec.y += currentVec.y += currentVec.y;
    } else if (currentLoc.y >worldHeight && currentVec.y >0){
        currentVec.y -= currentVec.y -= currentVec.y;
    }
    
    currentLoc += currentVec*currentSpeed;
}

//--------------------------------------------------------------
void ofApp::draw(){
     //yellowish draw colour
   
    ofPushMatrix();
    ofTranslate(currentLoc);
    ofRotateZDeg(currentHeading);
    ofSetColor(128,128,0);
      ofDrawRectangle(0,0, flyWidth, flyLength); // draw dragonfly body
    ofSetColor(173,255,47);
    ofDrawCircle(flyWidth/2, flyLength, flyWidth); // draw dragonfly head
  
    ofPopMatrix();
    stringstream flyStatus;
    
     flyStatus << "heading: " << currentHeading << " vec: " << currentVec << " loc: " << currentLoc << endl;
     ofDrawBitmapString(flyStatus.str(), 20,  20);
   if (b_drawGui) guiFlight.draw();
}

//--------------------------------------------------------------
void ofApp::dragonFlyDecision(){
    // choose new direction, speed, distance and waittime
    currentHeading = currentHeading +  ofRandom(directionVar) - (directionVar/2);
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    
    //generate vector from heading
    ofVec2f v1(0, 1);
    currentVec = v1.getRotated(currentHeading); //
    cout << "heading: " << currentHeading << " vec: " << currentVec << " loc: " << currentLoc << " speed: " << currentSpeed << " wait: " << currentWaitTime << endl;
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
            
        case ' ': //reset location
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

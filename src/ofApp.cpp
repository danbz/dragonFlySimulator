#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // dragon fly flight characteristics simulation
    // august 2018 dan buzzo dan@buzzo.com www.buzzo.com
    // flight charactre simulation in x,z plane with 3d viewport rendering
    // github.com/danbz
    
    // define dragonfly size and world size
    flyWidth = 10.0;
    flyLength = 50.0;
    //worldWidth =   ofGetScreenWidth(); //useful only for 2d rendering
    //worldHeight = ofGetScreenHeight();
    
    worldX =   2000; // set 3d world render size
    worldZ = 2000;
    worldY = 500;
    
    worldBox.set(worldX, worldY, worldZ); //setup wiredframe world edges
    worldBox.setResolution(1);
    
    flyBody.set(flyWidth, flyWidth, flyLength); // 3d shape for flybody
    flyBody.setResolution(1);
    flyBody.rotateDeg(90, 0, 0, 1);
    // set up gui and sliders
    guiFlight.setup();
    guiFlight.add(directionVar.setup("directionVariance", 180, 1, 360));
    guiFlight.add(speedMin.setup("speedMin", 1.0, 0.1, 2));
    guiFlight.add(speedMax.setup("speedMax", 4.0, 2, 20));
    guiFlight.add(waitTime.setup("waitTime", 2000.0, 100, 10000));
    guiFlight.add(currentAltitude.setup("altitude", 10.0, 0, 500));
    
    // choose initial conditions
    currentHeading = ofRandom(360.0);
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    currentLoc = ofVec2f(worldX/2,worldZ/2);
    currentVec = ofVec2f(0,0);
    ofSetBackgroundColor(0);
    
    b_drawGui = true;
    cam.setPosition(500, 100, -100);
    
}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec2f v1(0, 1); // constant for heading angle and vector calulations
    
    if (ofGetSystemTimeMillis() > currentWaitTime) {
        dragonFlyDecision();
    }
    
    if (currentLoc.x < 0 && currentVec.x <0) {
        currentVec.x +=  2* abs(currentVec.x);
        currentHeading = v1.angle(currentVec);
    } else if (currentLoc.x > worldX && currentVec.x > 0){
        currentVec.x -=  2* abs(currentVec.x);
        currentHeading = v1.angle(currentVec);
    } else if (currentLoc.y <0 && currentVec.y <0) {
        currentVec.y += 2* abs(currentVec.y);
        currentHeading = v1.angle(currentVec);
    } else if (currentLoc.y >worldZ && currentVec.y >0){
        currentVec.y -= 2* abs(currentVec.y);
        currentHeading = v1.angle(currentVec);
    }
    flyBody.resetTransform();
    flyBody.rotateDeg(-currentHeading, 0, 1 , 0);
    currentLoc += currentVec*currentSpeed;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    ofEnableDepthTest();
    cam.begin();
    // ofDrawAxis(100);
    // draw boundaries of visible/navigable flight area world.
   
    //ofPushMatrix();
    
    //worldBox.setPosition(worldWidth/2.0, , );
    ofSetColor(55,55,55);
    worldBox.drawWireframe();
    
    flyBody.setPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2.0);
    ofSetColor(173,255,47);
    flyBody.drawWireframe();
    
//    ofTranslate(currentLoc);
//    ofRotateZDeg(currentHeading);
//    ofSetColor(128,128,0);
//    ofDrawRectangle(0,0, flyWidth, flyLength); // draw dragonfly body
//    ofSetColor(173,255,47);
//    ofDrawCircle(flyWidth/2, flyLength, flyWidth); // draw dragonfly head
//    //ofPopMatrix();
    ofDisableDepthTest();
    
    cam.end();
    
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
    flyBody.resetTransform();
    flyBody.rotateDeg(-currentHeading, 0, 1 , 0);

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
//            worldX =  ofGetScreenWidth();
//            worldY =  ofGetScreenHeight();
            break;
            
        case ' ': // reset location
            currentLoc = ofVec2f(worldX/2,worldZ/2);
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

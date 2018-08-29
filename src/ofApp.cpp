#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // dragon fly flight characteristics simulation
    // august 2018 dan buzzo dan@buzzo.com www.buzzo.com
    // flight charactre simulation in x,z plane with 3d viewport rendering
    // github.com/danbz
    
    // define dragonfly size and world size
    flyWidth = 10.0;
    flyLength = 70.0;
    //worldWidth =   ofGetScreenWidth(); //useful only for 2d rendering
    //worldHeight = ofGetScreenHeight();
    
    worldX =   2000; // set 3d world render size
    worldZ = 2000;
    worldY = 500;
    
    worldBox.set(worldX, worldY, worldZ); //setup wiredframe world edges
    worldBox.setResolution(1);
    
    worldFloor.set(worldX, worldZ); //setup wiredframe world edges
    worldFloor.setResolution(10,10);
    worldFloor.rotateDeg(90, 1, 0, 0);
    worldFloor.setPosition(0, -worldY/2.0, 0);
    
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
    
    ofSetSmoothLighting(true);
    worldLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    worldLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    worldLight.setPosition(50,50,50);
    worldLight.setPointLight();
     worldLight.setAreaLight(1000, 1000);
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
    cam.begin();
    ofEnableDepthTest();
    ofEnableLighting();
    worldLight.enable();
   
    // draw boundaries of visible/navigable flight area world
    
    ofSetColor(200,200,200);
    worldBox.drawWireframe();
    ofSetColor(65,65,65);
    worldFloor.draw();
    flyBody.setPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2);
    ofSetColor(173,255,47);
    flyBody.draw();

//    ofSetColor(128,128,0);
//    ofSetColor(173,255,47);
//worldLight.draw();
    ofDisableLighting();
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

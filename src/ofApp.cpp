#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // dragon fly flight characteristics simulation
    // august 2018 dan buzzo dan@buzzo.com www.buzzo.com
    // flight charactre simulation in x,z plane with 3d viewport rendering
    // github.com/danbz
    
    int numOfFlies = 1000;
    worldX = 4000;
    worldY = 1000;
    worldZ = 4000;
    worldBox.set(worldX, worldY, worldZ); //setup wiredframe world edges
    worldBox.setResolution(1);
    worldFloor.set(worldX, worldZ); //setup wiredframe world edges
    worldFloor.setResolution(10,10);
    worldFloor.rotateDeg(90, 1, 0, 0);
    worldFloor.setPosition(0, -worldY/2.0, 0);
    
    
    // set up gui and sliders
    //    guiFlight.setup();
    //    guiFlight.add(directionVar.setup("directionVariance", 180, 1, 360));
    //    guiFlight.add(speedMin.setup("speedMin", 1.0, 0.1, 2));
    //    guiFlight.add(speedMax.setup("speedMax", 4.0, 2, 20));
    //    guiFlight.add(waitTime.setup("waitTime", 2000.0, 100, 10000));
    //    guiFlight.add(currentAltitude.setup("altitude", 10.0, 0, 500));
    
    
    ofSetBackgroundColor(0);
    b_drawGui = true;
    cam.setPosition(500, 100, -100);
    
    ofSetSmoothLighting(true);
    worldLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    worldLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    worldLight.setPosition(50,50,50);
    worldLight.setPointLight();
    worldLight.setAreaLight(1000, 1000);
    
    for (int i = 0 ; i < numOfFlies ; i++ ){
        dragonFly newfly;
        flies.push_back(newfly);
    }
}

//--------------------------------------------------------------
void ofApp::update(){
    for (int i = 0 ; i < flies.size() ; i++){
        flies[i].update();
    }
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
    
    for (int i = 0 ; i < flies.size() ; i++){
        flies[i].draw();
    }
    
    // worldLight.draw();
    ofDisableLighting();
    ofDisableDepthTest();
    
    cam.end();
    
    if (b_drawGui){
        stringstream flyStatus;
        //flyStatus << "heading: " << currentHeading << " vec: " << currentVec << " loc: " << currentLoc << endl;
        ofDrawBitmapString(flyStatus.str(), 20,  20);
        // guiFlight.draw();
    }
    
}
//--------------------------------------------------------------
dragonFly::dragonFly(){
    // dragonFly constructor
    
    worldX = 4000; // set individual fly 3d world  size
    worldY = 1000;
    worldZ = 4000;
    
    //fly characteristics
    width = ofRandom(8) + 3.0;
    length = ofRandom(50)+ 20.0;
    head.setParent(body);
    body.set(width, width, length); // 3d shape for flybody
    body.setResolution(1);
    body.rotateDeg(90, 0, 0, 1);
    head.set(1.2*width, 6);
    head.setPosition(0,0, length/2 );
    
    headColor = ofColor((ofRandom(100)+50),(ofRandom(50)+100),0);
    bodyColor = ofColor((ofRandom(75)+100),(ofRandom(155)+100),47);
    // choose initial flight conditions
    directionVar =  180;
    speedMin = 0.1;
    speedMax = 10.0;
    waitTime = 500.0;
    currentAltitude = ofRandom(0.0+worldY);
    currentHeading = ofRandom(360.0);
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    currentLoc = ofVec2f(worldX/2,worldZ/2);
    currentVec = ofVec2f(0,0);
    cout << "constructing dragonfly" << endl;

}

//--------------------------------------------------------------

dragonFly::~dragonFly(){
    cout << "destructing dragonfly" << endl;
}

//--------------------------------------------------------------

void dragonFly::update(){
    ofVec2f v1(0, 1); // constant for heading angle and vector calulations
    if (ofGetSystemTimeMillis() > currentWaitTime) {
        decision();
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
    currentLoc += currentVec*currentSpeed;
    head.setParent(body);
    body.resetTransform();
    body.rotateDeg(-currentHeading, 0, 1 , 0);
    // body.setPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2);
    body.setGlobalPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2);
   // head.setPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2);
}

//--------------------------------------------------------------
void dragonFly::decision(){
    // choose new direction, speed and waittime
    currentHeading = currentHeading +  ofRandom(directionVar) - (directionVar/2);
    currentSpeed = ofRandom(speedMin, speedMax);
    currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
    
    //generate vector from heading
    ofVec2f v1(0, 1);
    currentVec = v1.getRotated(currentHeading); //
    body.resetTransform();
    body.rotateDeg(-currentHeading, 0, 1 , 0);
    
}

//--------------------------------------------------------------

void dragonFly::draw(){
    ofSetColor(bodyColor);
    body.draw();
    ofSetColor(headColor);
    head.draw();
}

void dragonFly::reset(){
    currentLoc = ofVec2f(worldX/2,worldZ/2);
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
            for (int i = 0 ; i < flies.size() ; i++){
                flies[i].reset();
            }
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

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // dragon fly flight characteristics simulation
    // august 2018 dan buzzo dan@buzzo.com www.buzzo.com
    // flight charactre simulation in x,z plane with 3d viewport rendering
    // github.com/danbz
    //experimental branch to swap 3d for text representations
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
    
    font.load("monospace", 18);
    flyNames ="dragonFly";
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
    length = ofRandom(50)+ 40.0;
   // head.setParent(body);
    body.set(width, length);
    // body.setResolution(1, 1, 1);
    // body.setResolution(1);
    // body.rotateDeg(90, 0, 0, 1);
//    head.set(1.2*width, 6);
//    head.setPosition(0,length/2, 0 );
    
//    headColor = ofColor((ofRandom(100)+50),(ofRandom(50)+100),0);
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
    name = "dragonFly";
    cout << "constructing dragonfly" << endl;
    flyFont.load("sans-serif", ofRandom(15)+10);
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
//    head.setParent(body);
//    body.resetTransform();
//    body.rotateDeg(90, 0, 0, 1);
//
//    body.rotateDeg(-currentHeading+90, 0, 1 , 0);
//    body.setGlobalPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2);
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
//    body.resetTransform();
//    body.rotateDeg(-currentHeading, 0, 1 , 0);
    
}

//--------------------------------------------------------------

void dragonFly::draw(){
    ofSetColor(bodyColor);
   // body.draw();
    
    //ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2 );
    ofRotateDeg(-currentHeading+90, 0, 1 , 0);
  
    float scl = 1;
    glScalef(scl, scl, scl);
    flyFont.drawString("dragonFly", 0, 0);
    ofPopMatrix();
}

//--------------------------------------------------------------

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

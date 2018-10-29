#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // dragon fly flight characteristics simulation
    // august 2018 dan buzzo dan@buzzo.com www.buzzo.com
    // flight charactre simulation in x,z plane with 3d viewport rendering
    // github.com/danbz   http://www.buzzo.com
    //experimental branch to swap 3d for text representations October 2018
    
    int numOfFlies = 2000;
    worldX = 4000;
    worldY = 1000;
    worldZ = 4000;
    worldBox.set(worldX, worldY, worldZ); //setup wiredframe world edges
    worldBox.setResolution(1);
    worldFloor.set(worldX, worldZ); //setup wiredframe world edges
    worldFloor.setResolution(10,10);
    worldFloor.rotateDeg(90, 1, 0, 0);
    worldFloor.setPosition(0, (-worldY/2.0) -1, 0);
    
    ofSetBackgroundColor(0);
    b_drawGui = true;
    cam.setPosition(500, 100, -100);
    
    ofSetSmoothLighting(true);
    worldLight.setDiffuseColor( ofFloatColor(.85, .85, .55) );
    worldLight.setSpecularColor( ofFloatColor(1.f, 1.f, 1.f));
    worldLight.setPosition(50,50,50);
    worldLight.setPointLight();
    worldLight.setAreaLight(1000, 1000);
    
    font.load("monospace", 18);
    flyNames ="dragonFly";
    
    // load fresh prince lyrics
    sortTypeInfo = "no sort";
    
    ofBuffer buffer = ofBufferFromFile("freshprince.txt");
    string   content = buffer.getText();
    setupWords(content);
    // cout << content << endl;
    // create dragonfly swarm
    cout << "words in wordlist " << words.size() << endl;
    
    // create and name the flies
    int amountWords = words.size();
    string newName;
    
    for (int i = 0 ; i < numOfFlies ; i++ ){
        dragonFly newfly;
        newName = words[ i % amountWords ].word; // set name to lyric
        newfly.setName(newName);
        flies.push_back(newfly);
    }
    
//    buzz.load("buzz.aif");
//    buzz.setLoop(true);
//    buzz.setVolume(0.5f);
//    buzz.setPan(0.5f);
//    buzz.play();
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


ofVec3f ofApp::getCamPos(){
   return cam.getGlobalPosition();
};

//--------------------------------------------------------------

dragonFly::dragonFly(){  // dragonFly constructor
    worldX = 4000; // set individual fly 3d world  size
    worldY = 1000;
    worldZ = 4000;
    lifeTime = 10000 + ofRandom(20000); // life of dragonFly in milliseconds
    //fly characteristics
    width = ofRandom(8) + 3.0;
    length = ofRandom(50)+ 40.0;
    // head.setParent(body);
    body.set(width, length);
    // body.setResolution(1, 1, 1);
    // body.setResolution(1);
    // body.rotateDeg(90, 0, 0, 1);
    // headColor = ofColor((ofRandom(100)+50),(ofRandom(50)+100),0);
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
    name = "dragonFly"; // default dragonfly name
    spawnTime = ofGetSystemTimeMillis(); // add in timestamp of when this fly was spa2wned
    alive = true;
    
    // set type parameters
    flyFont.load( "sans-serif", ofRandom(15)+10, true, false, false, 0.3f, 192 );
    
    // set initial sound parameters
//    if ( sound.load("buzz.aif") ){
//        cout << "sound is loaded " << sound.isLoaded() << endl;
//        sound.setLoop(true);
//        sound.setPan(0.5f);
//        sound.setVolume(0.5f);
//        sound.play();
//    } else {
//        cout << "sound not loaded" << endl;
//    };
//
    
}

//--------------------------------------------------------------

dragonFly::~dragonFly(){
   // sound.unload();
}

//--------------------------------------------------------------

void dragonFly::update(){
    if (alive){
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
    }
    //    head.setParent(body);
    //    body.resetTransform();
    //    body.rotateDeg(90, 0, 0, 1);
    //
    //    body.rotateDeg(-currentHeading+90, 0, 1 , 0);
    //    body.setGlobalPosition(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2);
    // calculate position left or right of camera -observer
    // ofVec3f camDirection = ofApp::cam.getLookAtDir();
    // ofVec3f camPosition = ofApp::cam.getGlobalPosition();
    //ofVec3f camPosition =  ofApp::getCamPos();
    //    ofVec3f camPosition = ofVec3f(0,0,0);
    //    ofVec3f totalDistance = camPosition - (currentLoc.x, currentLoc.y, currentAltitude);
    //    float distance = totalDistance.x + totalDistance.y + totalDistance.z;
    //    //sound.setPan(<#float pan#>);
    //
    //    float vol =  ofMap(distance, 0, 1000, 1, 0);
    //    cout << "vol " << vol << endl;
    //   // sound.setVolume( vol );
    
    
}

//--------------------------------------------------------------
void dragonFly::decision(){
    
    if ( ofGetSystemTimeMillis()< spawnTime + lifeTime ){
        // choose new direction, speed and waittime
        currentHeading = currentHeading +  ofRandom(directionVar) - (directionVar/2);
        currentSpeed = ofRandom(speedMin, speedMax);
        currentWaitTime = ofGetSystemTimeMillis() + ofRandom(waitTime);
        
        //generate vector from heading
        ofVec2f v1(0, 1);
        currentVec = v1.getRotated(currentHeading); //
        //    body.resetTransform();
        //    body.rotateDeg(-currentHeading, 0, 1 , 0);
    } else {
        alive = false; // fly is past it's lifelength
        currentAltitude = 0;
        bodyColor = (ofRandom(200)+50);
        
    }
    
}

//--------------------------------------------------------------

void dragonFly::draw(){
    
    ofSetColor(bodyColor);
   
    // body.draw();
    
    //ofSetColor(255,255,255);
    ofPushMatrix();
    ofTranslate(currentLoc.x - worldX/2.0, currentAltitude - worldY/2.0 , currentLoc.y - worldZ/2 );
    ofRotateDeg(-currentHeading+90, 0, 1 , 0);
    if (!alive){
        ofRotateXDeg(-90);
    }
    float scl = 1;
    glScalef(scl, scl, scl);
    flyFont.drawString(name, 0, 0);
    ofPopMatrix();
//    if (!sound.isPlaying()){
//        sound.play();
//    }
//    cout << "sound is playing " << sound.isPlaying() << endl;
}

//--------------------------------------------------------------

void dragonFly::reset(){
    currentLoc = ofVec2f(worldX/2,worldZ/2);
    alive = true;
    spawnTime = ofGetSystemTimeMillis();
    currentAltitude = ofRandom(0.0+worldY);
}


void dragonFly::setName(string newName){
    name = newName;
}

//--------------------------------------------------------------

string dragonFly::getName(){
     return name;
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

            break;
            
        case ' ': // reset location
            for (int i = 0 ; i < flies.size() ; i++){
                flies[i].reset();
            }
            break;
        case 'l':
            
            //Open the Open File Dialog to load text file
            ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a txt file");
            
            //Check if the user opened a file
            if (openFileResult.bSuccess){
                
                ofLogVerbose("User selected a file");
                
                //We have a file, check it and process it
                processOpenFileSelection(openFileResult);
                
            }else {
                ofLogVerbose("User hit cancel");
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

//--------------------------------------------------------------

void ofApp::setupWords(string content){
    
    // take our text and process into a vector of words
    words.clear();
    
    // take the content and split it up by spaces
    // we need to also turn new lines into spaces so we can seperate words on new lines as well
    ofStringReplace(content, "\r", " ");
    ofStringReplace(content, "\n", " ");
    
    vector <string> splitString = ofSplitString(content, " ", true, true);
    
    // copy over the words to our object
    for (unsigned int i=0; i<splitString.size(); i++) {
        LyricWord wrd;
        wrd.occurrences = 1;
        wrd.word = ofToLower( splitString[i] );
        words.push_back(wrd);
    }
    
    // clean up the words removing any
    // characters that we do not want
    for (unsigned int i=0; i<words.size(); i++) {
        // run throught this ignore list and replace
        // that char with nothing
        char ignoreList[12] = {',', '.', '(', ')', '?', '!', '-', ':', '"', '\'', '\n', '\t'};
        for(int j=0; j<12; j++) {
            
            // make string from char
            string removeStr;
            removeStr += ignoreList[j];
            
            // remove and of the chars found
            ofStringReplace(words[i].word, removeStr, "");
        }
    }
    
    // count the amount of times that we see a word
    for (unsigned int i=0; i<words.size(); i++) {
        int c = 1;
        for (unsigned int j=0; j<words.size(); j++) {
            if(words[i].word == words[j].word) c ++;
        }
        words[i].occurrences = c;
    }
    
    // remove duplicates of the words
    vector<LyricWord>tempWord;
    for (unsigned int i=0; i<words.size(); i++) {
        bool bAdd = true;
        for(unsigned int j=0; j<tempWord.size(); j++) {
            if(words[i].word == tempWord[j].word) bAdd = false;
        }
        
        if(bAdd) {
            tempWord.push_back(words[i]);
        }
    }
    
    words = tempWord;
    
    // remove word we do not want
    ofRemove(words, ofApp::removeWordIf);
}

// remove extraneous words function
//--------------------------------------------------------------
bool ofApp::removeWordIf(LyricWord &wrd) {
    
    bool bRemove = false;
    static string ignoreWords[11] = {"the", "to", "of", "a", "and", "i", "it", "if", "is", "in", "be"};
    
    // if this word empty
    if(wrd.word.empty()) bRemove = true;
    
    // are we a word that we do now want
    for (int j=0; j<11; j++) {
        if(wrd.word == ignoreWords[j]) {
            bRemove = true;
            break;
        }
    }
    
    return bRemove;
}

// sort on abc's
//--------------------------------------------------------------
bool ofApp::sortOnABC(const LyricWord &a, const LyricWord &b) {
    return a.word < b.word;
}

// sort on word length
//--------------------------------------------------------------
bool ofApp::sortOnLength(const LyricWord &a, const LyricWord &b) {
    return (int)a.word.size() > (int)b.word.size();
}

// sort on occurrences
//--------------------------------------------------------------
bool ofApp::sortOnOccurrences(const LyricWord &a, const LyricWord &b) {
    return a.occurrences > b.occurrences;
}

//--------------------------------------------------------------

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult){
    
    ofLogVerbose("getName(): "  + openFileResult.getName());
    ofLogVerbose("getPath(): "  + openFileResult.getPath());
    
    ofFile file (openFileResult.getPath());
    
    if (file.exists()){
        
        ofLogVerbose("The file exists - now checking the type via file extension");
        string fileExtension = ofToUpper(file.getExtension());
        
        //We only want text
        if (fileExtension == "TXT") {
            
            // load the txt document into an ofBuffer
            ofBuffer buffer = ofBufferFromFile(file);
            string   content = buffer.getText();
            setupWords(content);
            
            // rename all the flies
            int amountWords = words.size();
            string newName;
            for (int i = 0 ; i < flies.size() ; i++ ){
                newName = words[ i % amountWords ].word; // set name to lyric
                flies[i].setName(newName);
            }
            
        }
    }
    
}

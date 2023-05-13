#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    ofBackground(0);
    
    //Initialize the drawing variables
    for (int i = 0; i < ofGetWidth(); ++i) {
        waveform[i] = 0;
    }
    waveIndex = 0;
    
    // Maximilian audio stuff
    int sampleRate = 44100; /* Sampling Rate */
    int bufferSize= 512; /* Buffer Size. you have to fill this buffer with sound using the for loop in the audioOut method */
    ofxMaxiSettings::setup(sampleRate, 2, bufferSize);
    
    // Setup ofSound
    ofSoundStreamSettings settings;
    settings.setOutListener(this);
    settings.sampleRate = sampleRate;
    settings.numOutputChannels = 2;
    settings.numInputChannels = 0;
    settings.bufferSize = bufferSize;
    soundStream.setup(settings);
    
    
    ofSetFrameRate(60); // Set the frame rate to 60 frames per second

    
    for(int i=0; i<NUM_STARS; i++){
        stars[i].x = ofRandom(-ofGetWidth(), ofGetWidth()); // Randomly set the initial abscissa of the star
        stars[i].y = ofRandom(-ofGetHeight(), ofGetHeight()); // Randomly set the initial ordinate of the star
        stars[i].z = ofRandom(ofGetWidth()); // Set the initial distance of the star randomly
        stars[i].speed = ofRandom(1, 10); // Set the rotation speed of the star randomly
    }
    radius = 200;
    angle = 0;
    angle2 = 0;
    angle3 = 0;
    angle4 = 0;
    angle5 = 0;
    angle6 = 0;

}

//--------------------------------------------------------------
void ofApp::update(){
    
    // Update the position and Angle of stars
    for(int i=0; i<NUM_STARS; i++){
        stars[i].z -= stars[i].speed; // Update the distance of a star based on its rotation speed
        if(stars[i].z < 1){ // If the star is already too far away from the screen, reset the original position and distance of the star
            stars[i].x = ofRandom(-ofGetWidth(), ofGetWidth());
            stars[i].y = ofRandom(-ofGetHeight(), ofGetHeight());
            stars[i].z = ofRandom(ofGetWidth());
        }
    }
    angle += 0.5; // Rotate 1 degree per frame
    angle2 += 3;
    angle3 += 2;
    angle4 += 0.05;
    angle5 += 0.01;
    angle6 -= 1;


}

//--------------------------------------------------------------
void ofApp::draw(){
    
    
    
     int a = ofRandom(0, 255);
     int b = ofRandom(0, 255);
     int c = ofRandom(0, 255);
     ofSetColor(a,b,c); // star's color
     ofPushMatrix(); // save current coordinate system state
     ofTranslate(ofGetWidth()/2, ofGetHeight()/2); // Move the origin of the frame to the center of the screen

     // Draw all the stars
     for(int i=0; i<NUM_STARS; i++){
         float sx = stars[i].x / stars[i].z * ofGetWidth(); // Calculate the star's horizontal coordinate on the screen based on the star's distance

         float sy = stars[i].y / stars[i].z * ofGetHeight(); // Calculate the vertical coordinate of the star on the screen based on its distance
         float r = ofMap(stars[i].z, 0, ofGetWidth(), 4, 0); // Calculate the size of a star based on its distance, and the closer star is bigger
         ofDrawCircle(sx, sy, r); // draw stars
     }

     ofPopMatrix(); // Restore a previously saved coordinate system state
    /////////////// waveform
    ofTranslate(0, ofGetHeight()/2);
    ofSetColor(ofRandom(0,255));
    ofFill();
    ofSetLineWidth(3);
    ofDrawLine(0, 0,1, waveform[1] * ofGetHeight()/2.); //first line
    for(int i = 1; i < (ofGetWidth() - 1); ++i) {
        ofDrawLine(i, waveform[i] * ofGetHeight()/2., i + 1, waveform[i+1] * ofGetHeight()/2.);
    }
    
    //ofPushMatrix(); // Save the current transformation matrix
    ofTranslate(ofGetWidth() / 2, ofGetHeight() / 2); // Move the coordinate system to the center of the screen
    ofRotate(angle); // rotation angle
    ofSetColor(255, 92+mouseX/9, 51);
    ofDrawCircle(0, 0, radius+(mouseX/90)*(mouseY/90)); // Draw a circle in the center of the screen
    
    ofRotate(angle2);
    ofSetColor(173-mouseX/6, 120, 31, 90);
    ofDrawCircle(-300, 0, 20+(mouseY/20+mouseY/40));
    ofRotate(angle6);
    ofRotate(angle6);
    ofRotate(angle6);
    
    ofRotate(angle3);
    ofSetColor(59+mouseY/6, 131-mouseX/4, 189, 90);
    ofDrawCircle(-350, 0, 40+(mouseY/20+mouseY/40));
    ofRotate(angle6);

    ofRotate(angle4);
    ofSetColor(0+mouseY/6, 255-mouseX/4, 0, 90);
    ofDrawCircle(-500, 0, 50+(mouseY/20+mouseY/40));
    ofRotate(angle6);
    
    ofRotate(angle5);
    ofSetColor(60+mouseY/6, 200-mouseX/4, 255, 90);
    ofDrawCircle(-700, 0, 60+(mouseY/20+mouseY/40));
    ofPopMatrix(); //Recovery transformation matrix
    

    
    
    

}

//--------------------------------------------------------------
void ofApp::audioIn(ofSoundBuffer& input){
    std::size_t nChannels = input.getNumChannels();
    for (size_t i = 0; i < input.getNumFrames(); i++)
    {
        // handle input here
    }
}
//--------------------------------------------------------------
void ofApp::audioOut(ofSoundBuffer& output){
    std::size_t outChannels = output.getNumChannels();
    for (int i = 0; i < output.getNumFrames(); ++i){
        double osc1 = oscillator1.triangle(mouseX)*(mouseY/float(ofGetHeight()));
        double osc2 = oscillator2.square(mouseX)*(1-mouseY/float(ofGetHeight()));
        double osc3 = oscillator3.sinewave(mouseX)*(0-mouseY/float(ofGetHeight()));
        output[i * outChannels] = (osc1+osc2+osc3) * 0.5;
        output[i * outChannels + 1] = output[i * outChannels];
        
        //Hold the values so the draw method can draw them
        waveform[waveIndex] =  output[i * outChannels];
        if (waveIndex < (ofGetWidth() - 1)) {
            ++waveIndex;
        } else {
            waveIndex = 0;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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

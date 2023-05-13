//
//  testApp.cpp
//  Boids
//
//  Created by Na Hong on 2023/3/8.
//

#include "testApp.hpp"

testApp::~testApp()
{
    for (int i = 0; i < boids.size(); i++)
    {
        delete boids[i];
    }
}

//--------------------------------------------------------------
void testApp::setup(){
    
    
    int screenW = ofGetScreenWidth();
    int screenH = ofGetScreenHeight();

    ofBackground(255,255,255);
    
    // create tree
    //ofSetFrameRate(60);
    //ofEnableSmoothing();
    //ofSetLineWidth(4);
    //ofSetColor(50, 50, 50);
        

    
    // set up the boids (using tree's leaf positions)
    ofVec3f pos;
    ofVec3f vel(0.5,0.5);
    ofVec3f rot(0,(200,200));
    for (int i = 0; i < 20; i++)
        boids.push_back(new Boid(pos, vel, rot));

}


//--------------------------------------------------------------
void testApp::update(){
    
    ofVec3f min(0, 0);
    ofVec3f max(ofGetWidth(), ofGetHeight());
    for (int i = 0; i < boids.size(); i++)
    {
        boids[i]->update(boids, min, max);
    }
}

//--------------------------------------------------------------
void testApp::drawBranch(float length, float angle, int level, ofMatrix4x4 transform){

    //ofMatrix4x4 pos = ofGetCurrentMatrix(OF_MATRIX_MODELVIEW);

    // tree branch
    if(level > 0){
        ofPushMatrix();
        ofRotate(angle);
        ofDrawLine(0, 0, 0, -length);
        ofTranslate(0, -length);
        
        ofSetColor(126,72,5);
        drawBranch(length*0.8, angle, level-1, transform);
        ofSetColor(126,72,5);
        drawBranch(length*0.8, -angle, level-1, transform);
        
        ofPopMatrix();
        
    }
    else
    {
        //draw all boids
       for (int i = 0; i < boids.size(); i++)
       {
        boids[i]->draw();
       }

    }

}


//--------------------------------------------------------------
void testApp::draw(){

    // draw tree
    ofSetColor(126,72,5);
    ofSetLineWidth(3); //     line's width of the tree
    ofPushMatrix();
    ofTranslate(ofGetWidth()/3, ofGetHeight());
    
    ofMatrix4x4 m;
    m.makeIdentityMatrix();
    drawBranch(120, 20, 8, m);
    ofPopMatrix();
    

    
    


}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
 
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

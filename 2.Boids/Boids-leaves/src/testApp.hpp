//
//  testApp.hpp
//  Boids
//
//  Created by Na Hong on 2023/3/8.
//

#ifndef testApp_hpp
#define testApp_hpp

#include <stdio.h>
#include "ofMain.h"
#include <vector>
#include "boid.hpp"

class testApp : public ofBaseApp{
    
public:
    ~testApp();
    
    void setup();
    void update();
    void drawBranch(float length, float angle, int level, ofMatrix4x4 transform);
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);

    std::vector<Boid *> boids;
    std::vector<ofMatrix4x4> transforms;
    
};

#endif /* testApp_hpp */

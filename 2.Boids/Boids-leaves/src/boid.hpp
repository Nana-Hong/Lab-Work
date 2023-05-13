//
//  boid.hpp
//  Boids
//
//  Created by Na Hong on 2023/3/8.
//

#ifndef boid_hpp
#define boid_hpp

#include <stdio.h>

#include <vector>
#include "ofMain.h"


class Boid
{
// all the methods and variables after the
// private keyword can only be used inside
// the class
private:
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f rotate;
    
    float separationWeight;
    float cohesionWeight;
    float alignmentWeight;
    
    float separationThreshold;
    float neighbourhoodSize;
    
    ofVec3f separation(std::vector<Boid *> &otherBoids);
    ofVec3f cohesion(std::vector<Boid *> &otherBoids);
    ofVec3f alignment(std::vector<Boid *> &otherBoids);
    
// all the methods and variables after the
// public keyword can only be used by anyone
public:
    Boid();
    Boid(ofVec3f &pos, ofVec3f &vel, ofVec3f &rot);
    
    ~Boid();
    
    ofVec3f getPosition();
    ofVec3f getVelocity();
    ofVec3f getRotate();
    
    
    float getSeparationWeight();
    float getCohesionWeight();
    float getAlignmentWeight();
    
    float getSeparationThreshold();
    float getNeighbourhoodSize();
    
    void setSeparationWeight(float f);
    void setCohesionWeight(float f);
    void setAlignmentWeight(float f);
    
    void setSeparationThreshold(float f);
    void setNeighbourhoodSize(float f);
    
    void update(std::vector<Boid *> &otherBoids, ofVec3f &min, ofVec3f &max);
    
    void walls(ofVec3f &min, ofVec3f &max);
    void draw();
    void centerposition();
    float angle;
    float axis;


    
};



#endif /* boid_hpp */

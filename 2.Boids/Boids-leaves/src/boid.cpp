//
//  boid.cpp
//  Boids
//
//  Created by Na Hong on 2023/3/8.
//

#include "boid.hpp"
#include "ofMain.h"

Boid::Boid()
{
   separationWeight = 1.0f;
   cohesionWeight = 0.2f;
   alignmentWeight = 0.1f;
   
   separationThreshold = 15;
   neighbourhoodSize = 100;
   
   position = ofVec3f(ofRandom(0, 200), ofRandom(0, 200));
   velocity = ofVec3f(ofRandom(-2, 2), ofRandom(-2, 2));
   rotate = ofVec3f(ofRandom(angle), ofRandom(axis));

}

//--------------------------------------------------------------
Boid::Boid(ofVec3f &pos, ofVec3f &vel, ofVec3f &rot)
{
   separationWeight = 1.0f;
   cohesionWeight = 0.2f;
   alignmentWeight = 0.1f;
   
   separationThreshold = 15;
   neighbourhoodSize = 100;
   
   position = pos;
   velocity = vel;
   rotate = rot;
}

//--------------------------------------------------------------
Boid::~Boid()
{
   
}

//--------------------------------------------------------------
float Boid::getSeparationWeight()
{
   return separationWeight;
}

//--------------------------------------------------------------
float Boid::getCohesionWeight()
{
   return cohesionWeight;
}

//--------------------------------------------------------------
float Boid::getAlignmentWeight()
{
   return alignmentWeight;
}

//--------------------------------------------------------------
float Boid::getSeparationThreshold()
{
   return separationThreshold;
}

//--------------------------------------------------------------
float Boid::getNeighbourhoodSize()
{
   return neighbourhoodSize;
}

//--------------------------------------------------------------
void Boid::setSeparationWeight(float f)
{
   separationWeight = f;
}

//--------------------------------------------------------------
void Boid::setCohesionWeight(float f)
{
   cohesionWeight = f;
}
//--------------------------------------------------------------
void Boid::setAlignmentWeight(float f)
{
   alignmentWeight = f;
}
//--------------------------------------------------------------
void Boid::setSeparationThreshold(float f)
{
   separationThreshold = f;
}
//--------------------------------------------------------------
void Boid::setNeighbourhoodSize(float f)
{
   neighbourhoodSize = f;
}

//--------------------------------------------------------------
ofVec3f Boid::getPosition()
{
   return position;
}

//--------------------------------------------------------------
ofVec3f Boid::getVelocity()
{
   return velocity;
}

//--------------------------------------------------------------
ofVec3f Boid::getRotate()
{
   return rotate;
}

//--------------------------------------------------------------
ofVec3f Boid::separation(std::vector<Boid *> &otherBoids)
{
    // finds the first collision and avoids that
    // should probably find the nearest one
    // can you figure out how to do that?
    for (int i = 0; i < otherBoids.size(); i++)
    {
        if(position.distance(otherBoids[i]->getPosition()) < separationThreshold)
        {
            ofVec3f v = position -  otherBoids[i]->getPosition();
            v.normalize();
            return v;
        }
    }
    return ofVec3f(0, 3, 0);
}

//--------------------------------------------------------------
ofVec3f Boid::cohesion(std::vector<Boid *> &otherBoids)
{
   ofVec3f average(0,2,0);
   int count = 0;
   for (int i = 0; i < otherBoids.size(); i++)
   {
       if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
       {
           average += otherBoids[i]->getPosition();
           count += 1;
       }
   }
   average /= count;
   ofVec3f v =  average - position;
   v.normalize();
   return v;
}

//--------------------------------------------------------------
ofVec3f Boid::alignment(std::vector<Boid *> &otherBoids)
{
   ofVec3f average(0,2,1);
   int count = 0;
   for (int i = 0; i < otherBoids.size(); i++)
   {
       if (position.distance(otherBoids[i]->getPosition()) < neighbourhoodSize)
       {
           average += otherBoids[i]->getVelocity();
           count += 1;
       }
   }
   average /= count;
   ofVec3f v =  average - velocity;
   v.normalize();
   return v;
}


//--------------------------------------------------------------
void Boid::update(std::vector<Boid *> &otherBoids, ofVec3f &min, ofVec3f &max)
{
   velocity += separationWeight*separation(otherBoids);
   velocity += cohesionWeight*cohesion(otherBoids);
   velocity += alignmentWeight*alignment(otherBoids);
   
   walls(min, max);
   position += velocity;
    

}

//--------------------------------------------------------------
void Boid::walls(ofVec3f &min, ofVec3f &max)
{
   if (position.x < min.x){
       position.x = min.x;
       velocity.x *= -1;
   } else if (position.x > max.x){
       position.x = max.x;
       velocity.x *= -1;
   }
   
   if (position.y < min.y){
       position.y = min.y;
       velocity.y *= -1;
   } else if (position.y > max.y){
       position.y = max.y;
       velocity.y *= -1;
   }
   
   
}

//--------------------------------------------------------------

void Boid::draw()
{
    
    // draw leaves
      ofSetColor(6,148,69,90);
      ofSetLineWidth(3);
      ofVec2f center(position.x, position.y);
      float width = 15;       // width of leaf
      float height = 30;      // height of leaf
    
    

     ofBeginShape();
     ofVertex(center.x, center.y);
     ofBezierVertex(center.x - width / 4, center.y + height / 4, center.x - width / 2, center.y - height / 4, center.x, center.y - height / 2); // 添加左下角曲线
     ofBezierVertex(center.x + width / 2, center.y - height / 4, center.x + width / 4, center.y + height / 4, center.x, center.y);
     ofEndShape(true);
    
    
                    

}

void Boid::centerposition()
{
    ofVec2f center(position.x, position.y);
    
}



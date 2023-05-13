#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"


const int NUM_STARS = 1000; 

class ofApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        // For drawing
        float waveform[4096]; //make this bigger, just in case
        int waveIndex;
    
        ofSoundStream soundStream;
    
        /* ofxMaxi*/
        void audioIn(ofSoundBuffer& input) override; // not used in this example
        void audioOut(ofSoundBuffer& output) override;
        maxiOsc oscillator1, oscillator2, oscillator3;
    
private:
    struct Star {
        float x;
        float y;
        float z; // Distance of stars
        float speed; // The rotation speed of the stars
    } stars[NUM_STARS];
    float radius;
    float angle;
    float angle2;
    float angle3;
    float angle4;
    float angle5;
    float angle6;
		
};

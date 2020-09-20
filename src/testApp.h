#pragma once

#include "ofMain.h"
#include "cassette.h"
#include "dancer.h"


class testApp : public ofBaseApp{

	public:

		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void bossWantsMusic();
        void Controls();
    
    //Cassette stuff
        cassette** myCassette;
        int nCassettes;        //variable for the number of cassettes
        dancer** myDancer; //Here are our dancer objects array
        int nDancer;        //variable for the number of dancers
        bool allTrue1, allTrue2;
		float 				* fftSmoothed;
		// we will draw a rectangle, bouncing off the wall:

		int nBandsToGet;
		float prevx, prevy;
    
    //Images Marty
    ofImage bar, boss, speak, floor;
    ofImage light1, light2;
    ofImage dancer1, dancer2, dancer3;
    ofImage mixerKnob;

   
    //Timer
    float startTime; // store when we start time timer
    float endTime; // when do want to stop the timer
    bool  bTimerReached; // used as a trigger when we hit the timer
	int days;
    ofTrueTypeFont	verdana30;
    
    //Boss
    float bossTime; //How long until the boss gets out
    float bossStartTime; //How much time it has been before he jumps out
    float tempBossTimer;
    int bossOriginX;
    int bossOriginY;
    bool bossLeave; //When to get the boos to leave
    string heWantsthis; //His choice in music
    float fScore;//This is to tell how long the person can play for
    int bossDeduction; //When to decduct if the mousic is not right

    
    //Mixer mashup
    int mixerX;
    float mixerLeftRightVol;
    ofSoundPlayer leftMix, rightMix;
    string leftMixName;
    string rightMixName;
    
    //Dj survive stuff
    float sustainability; // How long the Dj will last
    float bossHappy; //How happy the boss is with the music
    float dancerPop; //How many dancers are their
    float dayPer; //How much the DJ has to survive the day
    string musicTypes[6];
    
    //Game stuff
    string gameState;
    int survival; //This shows the player how much they are winning by
};


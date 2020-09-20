//
//  Cassette.h
//  barGame
//
//  Created by Marty on 24/03/14.
//
//

#ifndef barGame_Dancer_h
#define barGame_Dancer_h

#include "ofMain.h"

class dancer {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update(string leftMixName, string rightMixName, float mixerLeftRightVol);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    
    // variables
    float x;      // position
    float y;
    float speedY; // speed and direction
    float speedX;
    float dancerHappy;
    float danceTimer;
    float dancerLeftRightMix;
    string dancerMusic;
    string danceLeftMix, danceRightMix;
    int appear;//Lets get that body appearing!
    bool letsFunk; //This decides if the cassette has been takken out
    int wantAppeal;// This decides if the dancer wants to stay or not
    int maxHappy; //To max the happiness
    ofImage imageDancer;
   
    //Dancer Timer
    float startDancerTime; // store when we start time timer
    
    dancer(float x, float y, ofImage imageDancer, float dancerHappy, string dancerMusic); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!

#endif
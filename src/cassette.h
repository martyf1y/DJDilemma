//
//  Cassette.h
//  barGame
//
//  Created by Marty on 24/03/14.
//
//

#ifndef barGame_Cassette_h
#define barGame_Cassette_h

#include "ofMain.h"

class cassette {
    
public: // place public functions or variables declarations here
    
    // methods, equivalent to specific functions of your class objects
    void update(int cassMouseX, int cassMouseY);  // update method, used to refresh your objects properties
    void draw();    // draw method, this where you'll do the object's drawing
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void fullSizeCassette(int thisCassettePositionX, int thisCassettePositionY, int addLeft, int addRight, int addUp, int addDown);
    
    // variables
    float cassPlayerX;      // position
    float cassPlayerY;
    // we will draw a cassette, bouncing off the wall:
    float 				px, py, vx, vy; //This is the current position of the cassettes and also their velocity
    float prevx, prevy; //The whole dragging thing with cassettes
    float cassMixerX, cassMixerY; //This is the Mixer coordinates
    float cassMixer2X, cassMixer2Y;
    bool cassHeld; //This is to check that the object is being held
    bool cassMousePress; //checks when mouse pressed

    float boxSizeLeft; //These will be the boundary of the objects
    float boxSizeRight;
    float boxSizeUp;
    float boxSizeDown;
    
    int cassetteState;

    ofImage imageCassette;
    ofImage imageCassetteCrop;
    ofSoundPlayer cassBump;
    ofSoundPlayer cassBeat;
    
    cassette(float x, float y, ofImage imageCassette, ofSoundPlayer cassBump, ofSoundPlayer cassBeat); // constructor - used to initialize an object, if no properties are passed
    //               the program sets them to the default value
    
    //Mixer amshup
    bool isMixer1Full, isMixer2Full;
    bool allClearMixer1, allClearMixer2;
    
private: // place private functions or variables declarations here
    
}; // dont't forget the semicolon!!

#endif
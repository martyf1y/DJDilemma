//
//  cassette.cpp
//  barGame
//
//  Created by Marty on 25/03/14.
//
//

#include "dancer.h"


dancer::dancer(float _x, float _y, ofImage _imageDancer, float _dancerHappy, string _dancerMusic)
{
    x = _x;
    y = _y;
    
    speedX = ofRandom(-1, 1);
    speedY = ofRandom(-1, 1);
    
    imageDancer = _imageDancer;
    dancerHappy = _dancerHappy;
    maxHappy = _dancerHappy;
    dancerMusic = _dancerMusic;
    letsFunk = false;
    appear = 0;
    startDancerTime = ofGetElapsedTimeMillis();  // get the start time
    wantAppeal = 0;
}

void dancer::update(string _leftMixName, string _rightMixName, float _mixerLeftRightVol){
   //  cout << "XXXXXXX" << endl;
    danceLeftMix =_leftMixName;
    danceRightMix = _rightMixName;
    dancerLeftRightMix = _mixerLeftRightVol;
    
    float danceTimer = ofGetElapsedTimeMillis() - startDancerTime;
    if(danceTimer >= 1000) { //Only checks every second
        startDancerTime = ofGetElapsedTimeMillis();  // get the start time
        
        if(dancerMusic ==  danceLeftMix || dancerMusic == danceRightMix )//Checks to see if music is the right type
        {
            if(wantAppeal < 5)//Gives the dancer time to want to hear it
            {
            wantAppeal ++;
            }
        }
        else
        {
            if(wantAppeal > 0)
            {
            wantAppeal --;
            }
        }
        
        if(wantAppeal >= 5)
        {
            letsFunk = true;
            float dancerDeductDiff;
            if(dancerMusic == danceLeftMix) //These are to ratio it depedning on how loud the music is
            {
                dancerDeductDiff = ofMap(dancerLeftRightMix, -10, 10, -0.2, 0.5);
            }
            else if(dancerMusic == danceRightMix)
            {
                dancerDeductDiff = ofMap(dancerLeftRightMix, -10, 10, 0.5, -0.2);
            }
            else
            {
                dancerDeductDiff = 1.0;
            }
            
            if(dancerHappy > 0 && dancerDeductDiff > 0 || dancerHappy < maxHappy && dancerDeductDiff < 0)//This decides if the music is right for boss
            {
                dancerHappy = dancerHappy - (1 * dancerDeductDiff);
            }
        }
        else if(wantAppeal <= 0)
        {
            letsFunk = false;
        }
    }
    
    if(letsFunk && appear <= 255)
    {
        //cout << "YES" << endl;
        appear ++;
        
    }
    else if(!letsFunk && appear >= 0)
    {
        appear --;
    }
    
    if(!letsFunk)
    {
        
    }
    
    // x+=speedX;
    // y+=speedY;
}

void dancer::draw(){
    // values for R, G, B
    //ofSetColor(120,120,120);
    //  ofCircle(x, y, dim);
 
    ofSetColor(51*wantAppeal, 51*wantAppeal, 51*wantAppeal, appear);
    imageDancer.draw(x-imageDancer.width/2, y-imageDancer.height/2);
}
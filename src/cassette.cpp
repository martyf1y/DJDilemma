//
//  cassette.cpp
//  barGame
//
//  Created by Marty on 25/03/14.
//
//

#include "cassette.h"


cassette::cassette(float _x, float _y, ofImage _imageCassette, ofSoundPlayer _cassBump, ofSoundPlayer _cassBeat)
{
    
    cassMixerX = 390;//This is the Mixer coordinates
    cassMixerY = 465;
    cassMixer2X = 645;
    cassMixer2Y = 465;
    
    cassPlayerX = _x;
    cassPlayerY = _y;

    isMixer1Full = false;
    isMixer2Full = false;
    
    px = cassPlayerX;
    py = cassPlayerY;
    vx = 0;
	vy = 0;
    
    imageCassette = _imageCassette;
    cassetteState = 0;
    cassMousePress = false;
    cassBeat = _cassBeat;
    cassBump = _cassBump;
}

void cassette::update(int cassMouseX, int cassMouseY){
   
    
        switch(cassetteState){
        case 0: //When in cassette player
                // Make sure it is only the button that can be pressed
                //Change to the right cassette boundaries
                fullSizeCassette(cassPlayerX, cassPlayerY, 25, (imageCassette.width - 35),
                                 (-imageCassette.height + 15), -7);
                
                
                if(cassMouseX > boxSizeLeft && cassMouseX < boxSizeRight
                   && cassMouseY > boxSizeUp && cassMouseY < boxSizeDown && cassMousePress && cassHeld)
                {
                    cassetteState = 2;
                    cassMousePress = false;
                }
                break;
        case 1: //When in the mixer
           // doSomething();
                //Change to the right cassette boundaries
                 fullSizeCassette(px, py, (-imageCassette.width/2), (imageCassette.width/2),
                                  (-imageCassetteCrop.height/2),  (imageCassetteCrop.height/2));
                
                
                //Play song
                //Make sure it changes depending on mixer placement
                
                
                if(cassMouseX > boxSizeLeft && cassMouseX < boxSizeRight
                   && cassMouseY > boxSizeUp && cassMouseY < boxSizeDown && cassMousePress)
                {
                    //this checks which one the cassette is in
                    if(px == cassMixerX)
                    {
                        isMixer1Full = false;
                        allClearMixer1 = true;
                    }
                    else if(px == cassMixer2X)
                    {
                        isMixer2Full = false;
                        allClearMixer2 = true;
                        
                    }
                    
                    px = px - 6; //This is to stop the cassette from freexing in the spot
                    py = py - 6;
                    
                    cassetteState = 3;
                }
            break;
        case 2://When taken out of tape player
                
                //Change to the right cassette boundaries
                fullSizeCassette(px, py, (-imageCassette.width/2), (imageCassette.width/2),
                                 (-imageCassette.height/2),  (imageCassette.height/2));
                
                if(cassMouseX > boxSizeLeft && cassMouseX < boxSizeRight
                   && cassMouseY > boxSizeUp && cassMouseY < boxSizeDown && cassMousePress)
                {
                    cassetteState = 3;
                    px = px + 6; //This is to stop the cassette from freexing in the spot
                    py = py + 6;
                }
                break;
                
        case 3://When moving around
               
                //Change to the right cassette boundaries
                fullSizeCassette(px, py, (-imageCassette.width/2), (imageCassette.width/2),
                                 (-imageCassette.height/2),  (imageCassette.height/2));
                    
                //Here is all the object stuff
                //
                //
                //
                // (1) we increase px and py by adding vx and vy
                px += vx;
                py += vy;
                //px = cassMouseX;
               // py = cassMouseY;
              
                // (2) check for collision, and trigger sounds:
                // horizontal collisions:
                if (px < 0 + imageCassette.width/2){
                    px = 0 + imageCassette.width/2;
                    vx *= -0.3;
                    cassBump.play();
                } else if (px > ofGetWidth()- imageCassette.width/2){
                    px = ofGetWidth() - imageCassette.width/2;
                    vx *= -0.3;
                    cassBump.play();
                }
                // vertical collisions:
                if (py < 0 + imageCassette.height/2){
                    py = 0 + imageCassette.height/2;
                    vy *= -0.3;
                    cassBump.play();
                } else if (py > ofGetHeight()- imageCassette.height/2){
                    py = ofGetHeight() - imageCassette.height/2;//should take out the wring cassette MATTTTTTTTTTTTT
                    vy *= -0.3;
                    cassBump.play();
                }
                // (3) slow down velocity:
                vx 	*= 0.965f;
                vy 	*= 0.996f;
                
                
                if(!cassHeld) //This makes the cassette fall
                {
                    vy 	+= 0.996f;
                }
          
              
                //This will put the case back in its place
                if(px <= cassPlayerX + 5 && px >= cassPlayerX - 5
                   && py <= cassPlayerY + 5 && py >= cassPlayerY - 5
                   && cassHeld)
                {
                    px = cassPlayerX;
                    py = cassPlayerY;
                    cassetteState = 4;
                    
                }
                
                //It is in the mixer
                else if(px <= cassMixerX + 5 && px >= cassMixerX - 5
                   && py <= cassMixerY + 5 && py >= cassMixerY - 5
                   && cassHeld && !isMixer1Full)
                {
                    px = cassMixerX;
                    py = cassMixerY;
                    isMixer1Full = true;
                    cassetteState = 1;
                    
                }
                //It is in the mixer 2
                else if(px <= cassMixer2X + 5 && px >= cassMixer2X - 5
                   && py <= cassMixer2Y + 5 && py >= cassMixer2Y - 5
                   && cassHeld && !isMixer2Full)
                {
                    px = cassMixer2X;
                    py = cassMixer2Y;
                    isMixer2Full = true;
                    cassetteState = 1;
                }
                break;
                
        case 4: //When put back into tape player
         //   doSomethingElse();
            // fall through
                //Change to the right cassette boundaries
                fullSizeCassette(cassPlayerX, cassPlayerY, (-imageCassette.width/2), (imageCassette.width/2),
                                 (-imageCassette.height/2),  (imageCassette.height/2));
               
                if(cassMouseX > boxSizeLeft && cassMouseX < boxSizeRight
                   && cassMouseY > boxSizeUp && cassMouseY < boxSizeDown && cassMousePress)
                {
                    cassetteState = 0;
                }

                break;
            }
}

void cassette::fullSizeCassette(int thisCassettePositionX, int thisCassettePositionY,
                                int addLeft, int addRight, int addUp, int addDown){
   
    boxSizeLeft = thisCassettePositionX + addLeft;
    boxSizeRight = thisCassettePositionX + addRight;
    boxSizeUp = thisCassettePositionY + addUp;
    boxSizeDown = thisCassettePositionY + addDown;
    
}

void cassette::draw(){
    // values for R, G, B
  //  ofSetColor(120,120,120);
  //  ofCircle(x, y, dim);
    if(cassetteState >= 2)
    {   //Out and about
        imageCassette.draw(px-imageCassette.width/2, py-imageCassette.height/2);
 
    }
    else if(cassetteState == 1)
    {
        //When in the mixer
        //  imageCassette.draw(x-imageCassette.width/2, y-imageCassette.height/2);
        imageCassetteCrop.cropFrom(imageCassette, 0, 0, 71, 20);
        imageCassetteCrop.draw(px-imageCassette.width/2, py-imageCassette.height/2);
    }
    else if(cassetteState == 0)
    {
        //  imageCassette.draw(x-imageCassette.width/2, y-imageCassette.height/2);
        imageCassetteCrop.cropFrom(imageCassette, 4, 15, 60, 9);
        imageCassetteCrop.draw(px-imageCassette.width/2, py-imageCassette.height/2);

    }
}



void cassette::mouseDragged(int cassMouseX, int cassMouseY, int button){
	
   if(cassHeld)
   {
    // add into vx and vy a small amount of the change in mouse:
	vx += (cassMouseX - prevx) / 40.0f;
	vy += (cassMouseY - prevy) / 40.0f;
    
	// store the previous mouse position:
	prevx = cassMouseX;
	prevy = cassMouseY;
   }
    
}

void cassette::mousePressed(int cassMouseX, int cassMouseY, int button){
    
    
    cassMousePress = true; //This is just for the first 2 cases of cassette

    if(cassMouseX > boxSizeLeft && cassMouseX < boxSizeRight
       && cassMouseY > boxSizeUp && cassMouseY < boxSizeDown && !cassHeld)
    {
        // store the previous mouse position:
        // prevx = cassMouseX; MAYBE PUT THIS BACK IF ERRORS
        // prevy = cassMouseY;
        cassHeld = true; //This checks for if the cassette is already being held

    }

}

void cassette::mouseReleased(int cassMouseX, int cassMouseY, int button){
    
        cassHeld = false; //This checks for if the cassette is already being held
        cassMousePress = false;

}

#include "testApp.h"
#include "cassette.h"


//--------------------------------------------------------------
void testApp::setup(){
	
    ofSetDataPathRoot("../Resources/data/");
	// the fft needs to be smoothed out, so we create an array of floats
	// for that purpose:
	fftSmoothed = new float[8192];
	for (int i = 0; i < 8192; i++){
		fftSmoothed[i] = 0;
	}
	
	nBandsToGet = 128;
    
    //Image
    bar.loadImage("image/background.png");
    boss.loadImage("image/boss.png");
    speak.loadImage("image/speak.png");
    floor.loadImage("image/floor.png");
    light1.loadImage("image/light1.png");
    light2.loadImage("image/light2.png");
    mixerKnob.loadImage("image/knob.png");
    
    ///music
    musicTypes[0] = ("Techno");
    musicTypes[1] = ("Pop");
    musicTypes[2] = ("Classical");
    musicTypes[3] = ("Rock");
    musicTypes[4] = ("Funk");
    musicTypes[5] = ("Rap");
    
    //Dancer
    nDancer = 3; // the number of dancer objects we want to create
    
    myDancer = new dancer*[nDancer]; // an array of pointers for the objects
    vector <int> worthness; //Dancers worthness
    worthness.push_back(5);
    worthness.push_back(10);
    worthness.push_back(15);
    ofRandomize(worthness);
    
    
    vector <int> musicLiking; //Becuase I'm Lazy :p
    musicLiking.push_back(0);
    musicLiking.push_back(1);
    musicLiking.push_back(2);
    musicLiking.push_back(3);
    musicLiking.push_back(4);
    musicLiking.push_back(5);
    ofRandomize(musicLiking);
    
    for (int i = 0; i < nDancer; i++){
        float x = 676 - (180 * i);  // using the value of the counter variable(i) to differentiate them
        float y;
        if(i != 1)
        {
            y = 198;
        }
        else{
            y = 238;
        }
        ofImage imageDancer;
        imageDancer.loadImage("image/dancer" + ofToString(i) + ".png");
        float dancerHappy = worthness[i];
       
        myDancer[i] = new dancer(x, y, imageDancer, dancerHappy, musicTypes[musicLiking[i]]);  // create each object from the array
    }
    
    
    //Cassette
    nCassettes = 6; // the number of ball objects we want to create
    
    myCassette = new cassette*[nCassettes]; // an array of pointers for the objects
    
    for (int i = 0; i < nCassettes; i++){
        //This is the location of the cassettes
        float x;  // using the value of the counter variable(i) to differentiate them
        float y;
        if(i <= 2)
        {
            y = 554;
            x   = 403+(117*i);
        }

        else
        {
            y = 600;
            x   = 403+(117*(i - 3));
        }
        ofImage imageCassette;
        imageCassette.loadImage("image/" + musicTypes[i] + ".png");
        ofSoundPlayer cassBump;
        cassBump.loadSound("sounds/drop.mp3");
        ofSoundPlayer cassBeat;
        cassBeat.loadSound("sounds/" + musicTypes[i] + ".mp3");
        myCassette[i] = new cassette(x,y,imageCassette,cassBump, cassBeat);  // create each object from the array
        
    }
    
    //Timer
    bTimerReached = false;
    startTime = ofGetElapsedTimeMillis();  // get the start time
    endTime = (int)ofRandom(30000, 50000); // in milliseconds
    days = 0;
    verdana30.loadFont("verdana.ttf", 30, true, true);
	verdana30.setLineHeight(34.0f);
	verdana30.setLetterSpacing(1.035);
    
    //boss
    bossTime = ofRandom(7000, 12000);
    bossStartTime = 0;
    bossOriginX = -boss.width;
    bossOriginY = ofGetHeight()/8;
    bossLeave = false;
    bossDeduction = 0;
    
    fScore = 0;
    
    //Mixer mashup
    mixerX = 472;
    
    //Survive DJ
    bossHappy = 35.0;
    dancerPop = 35.0;//Starts as 0, goes up with more people
    dayPer = 1; //Needs to be timesed by .9 everyday
    
    //Game state
    gameState = "Start";
    
}


//--------------------------------------------------------------
void testApp::update(){
	
	ofBackground(80,80,20);
    
	// update the sound playing system:
	ofSoundUpdate();
	
    // (4) we use velocity for volume of the samples:
	
	// (5) grab the fft, and put in into a "smoothed" array,
	//		by taking maximums, as peaks and then smoothing downward
	float * val = ofSoundGetSpectrum(nBandsToGet);		// request 128 values for fft
    for (int i = 0;i < nBandsToGet; i++){
		
		// let the smoothed calue sink to zero:
		fftSmoothed[i] *= 0.96f;
		
		// take the max, either the smoothed or the incoming:
		if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
	}

    
    //GameStates
    if(gameState == "Play")
    {
        Controls(); //This controls the casettes and mixer and dancers
        sustainability = (bossHappy + dancerPop + myDancer[0]->dancerHappy + myDancer[1]->dancerHappy + myDancer[2]->dancerHappy) * dayPer; //This is the Dj's current state
        survival = sustainability*4;
        if(sustainability < 35)
        {
            gameState = "GameOver";
        }
    }
   
    //mixer mate and everything else
    
   
   

}

//--------------------------------------------------------------
void testApp::draw(){
    
    if(gameState == "Start")
    {
        ofEnableAlphaBlending();
        //DAYS
        verdana30.drawString(" Dj Dilemma!!", 100, 90);
        
        ofSetColor(255,255,255);
        verdana30.drawString("", 50, 150);
        ofDisableAlphaBlending();
        
    }
    else if(gameState == "Play" || gameState == "GameOver")
    {
	ofEnableAlphaBlending();
    //My CODE starts here
    ofSetColor(255,survival,survival);
    bar.draw(0, 0);
    
    ofSetColor(255,255,255,100);
    ofRect(293,0,5*90,283);
    
	ofDisableAlphaBlending();
	
	// draw the fft resutls:
	ofSetColor(34,198,100,200);
	
	float width = (float)(5*190) / nBandsToGet;
	for (int i = 0;i < nBandsToGet; i++){
		// (we use negative height here, because we want to flip them
		// because the top corner is 0,0)
        if(293+i*width <= 5*89+293)
        {
            ofRect(293+i*width,283,width,-(fftSmoothed[i] * 100));
        }
	}
	ofSetColor(25,55,205,255);
    
    
	// finally draw the playing circle:
    
    
	ofEnableAlphaBlending();
    
    ///floor
    floor.draw(241, 281);
    
    //Dancers
    for (int i = 0; i < nDancer; i++){
        myDancer[i]->draw();
    }
    ofSetColor(255,255,255);
    if(((ofGetElapsedTimeMillis()/300) % 2) == 0)
    {
        ///light1
        light1.draw(187, -2);
    }
    else{
        ///light2
        light2.draw(395, -5);
    }
    ofDisableAlphaBlending();
    
    
    mixerKnob.draw(mixerX - mixerKnob.width/2,462 - mixerKnob.height/2);
    
    ofEnableAlphaBlending();
    if(tempBossTimer >= bossTime || gameState == "GameOver")
    {
        //boss This guy will be annoying
        bossWantsMusic();
    }
    
    ofSetColor(255,255,255);
    //There are two for loops to separate draw order of the ones who are out of the cassette player and the ones who are in.
    for (int i = 0; i < nCassettes; i++){
        if(myCassette[i]->cassetteState!=3)
        {
            myCassette[i]->draw();
        }
    }
    for (int i = 0; i < nCassettes; i++){
        if(myCassette[i]->cassetteState==3)
        {
            myCassette[i]->draw();
        }
    }
    
    ofSetColor(255,255,255,20);
    ofCircle(mouseX, mouseY,50);
    
	ofDisableAlphaBlending();
    
    ofEnableAlphaBlending();
    //Timer
    // update the timer this frame
    float barWidth = 150;
    float timer = ofGetElapsedTimeMillis() - startTime;
    
    if(timer >= endTime) {
        startTime = ofGetElapsedTimeMillis();  // get the start time
        endTime = (int)ofRandom(30000, 50000); // in milliseconds
        days ++;
        dayPer = dayPer * 0.92;// Degrades the survival each day
    }
    
    //Timer for dancer
    
    
    // the background to the progress bar
    ofSetColor(100);
    ofRect(830, 100, barWidth, 30);
    
    // get the percantage of the timer
    float pct = ofMap(timer, 0.0, endTime, 0.0, 1.0, true);
    ofSetHexColor(0xf02589);
    ofRect(830, 100, barWidth*pct, 30);
    
    
    //DAYS
    verdana30.drawString(ofToString(days) + " Day", 830, 90);
    // some information about the timer
    string  info  = "FPS:        "+ofToString(ofGetFrameRate(),0)+"\n";
   // info += "Start Time: "+ofToString(startTime, 1)+"\n";
   // info += "End Time:   "+ofToString(endTime/1000.0, 1)+" seconds\n";
   // info += "Timer:      "+ofToString(timer/1000.0, 1)+" seconds\n";
    //info += "Percentage: "+ofToString(pct*100, 1)+"%\n";
   // info += "Score:      "+ofToString(fScore)+" \n \n";
    info += "Survival Happy: " +ofToString(sustainability)+ " \n";
   // info += "Boss Happy: " +ofToString(bossHappy) + " \n";
   // info += "Population: " +ofToString(dancerPop)+ " \n";
   // info += "Dancer1 Happy: "+ofToString(myDancer[0]->dancerHappy)+ " "+  ofToString(myDancer[0]->wantAppeal) +  " "+  ofToString(myDancer[0]->dancerMusic) + " \n";
  //  info += "Dancer2 Happy: "+ofToString(myDancer[1]->dancerHappy)+ " "+  ofToString(myDancer[1]->wantAppeal)+ " "+  ofToString(myDancer[1]->dancerMusic) + " \n";
  //  info += "Dancer3 Happy: "+ofToString(myDancer[2]->dancerHappy)+ " "+  ofToString(myDancer[2]->wantAppeal)+ " "+  ofToString(myDancer[2]->dancerMusic) + " \n";

    
    ofSetColor(255,255,255);
    ofDrawBitmapString(info, 830, 150);
    ofDisableAlphaBlending();
    //End Timer
    
	ofSetHexColor(0xffffff);
	ofCircle(mouseX, mouseY,2);
    }
}


//This will change the mixing of the music
void testApp::Controls()
{
    //Boss update
    tempBossTimer = ofGetElapsedTimeMillis() - bossStartTime;
    
    //Cassettes biatch
    for (int i = 0; i < nCassettes; i++){
        myCassette[i]->update(mouseX, mouseY);
        
        //Checking to see if the mixer is taken
        if(myCassette[i]->isMixer1Full == true && !allTrue1)//Put in all true to stop constant looping
        {
            
            leftMix = myCassette[i]->cassBeat;
            leftMix.setLoop(true);
            leftMix.play();
            leftMixName = musicTypes[i];
            for (int change = 0; change < nCassettes; change++)
            {
                myCassette[change]->isMixer1Full = true;
                allTrue1 = true;
            }
        }
        if(myCassette[i]->isMixer2Full == true &&  !allTrue2)
        {
            
            rightMix = myCassette[i]->cassBeat;
            rightMix.setLoop(true);
            rightMix.play();
            rightMixName = musicTypes[i];
            for (int change = 0; change < nCassettes; change++)
            {
                myCassette[change]->isMixer2Full = true;
                allTrue2 = true;
            }
        }
        //Now reset them all back
        if(myCassette[i]->allClearMixer1 == true)
        {
            for (int change = 0; change < nCassettes; change++)
            {
                myCassette[change]->isMixer1Full = false;
                myCassette[change]->allClearMixer1 = false;
                allTrue1 = false;
                leftMix.stop();
                leftMixName = " ";
            }
        }
        if(myCassette[i]->allClearMixer2 == true)
        {
            for (int change = 0; change < nCassettes; change++)
            {
                myCassette[change]->isMixer2Full = false;
                myCassette[change]->allClearMixer2 = false;
                allTrue2 = false;
                rightMix.stop();
                rightMixName = " ";
            }
        }
        
    }
    
    int popCounter = 0;
    for (int i = 0; i < nDancer; i++){
        myDancer[i]->update(leftMixName, rightMixName, mixerLeftRightVol);
        if(myDancer[i]->letsFunk == true) //Tells us when to appear the dancers
        {
            
            
        }
        else
        {
            //  myDancer[i]->letsFunk = false;
            popCounter ++;
        }
    }
    dancerPop = 35.0 - (11.5 * popCounter);
    
    //MIXER THINGS
    mixerLeftRightVol = ofMap(mixerX, 472, 557, -10, 10);
    
    
    leftMix.setVolume(ofMap(mixerLeftRightVol, -10, 10, 1.0, 0.0));
    rightMix.setVolume(ofMap(mixerLeftRightVol, -10, 10, 0, 1.0));
    
}

//Call this everytime the boss wants a song played
void testApp::bossWantsMusic()
{
    boss.draw(bossOriginX, bossOriginY);
    if(bossOriginX <= -boss.width/4 && !bossLeave) //The boss will pop out in front of us
    {
        bossOriginX += 4;
        bossOriginY -= 2;
        heWantsthis = musicTypes[(int)ofRandom(0,6)];
        bossDeduction = tempBossTimer + 1000;
    }
    else if(!bossLeave)
    {
        float bossDeductDiff;
        //Put in an array of different music
        int countCassBacks = 0; //This is to check how many cassettes are back in place
        for(int i = 0; i < nCassettes; i ++)
        {
            if(myCassette[i]->cassetteState != 0 && myCassette[i]->cassetteState != 1 && myCassette[i]->cassHeld == false)
            {
                countCassBacks ++;
            }

        }
        if(gameState != "GameOver")//TAKE THIS OUT WHEN YOU WANT TO CONTINUE REAL GAME MAKING
        {
            
        
        if(countCassBacks != 0)
        {
            speak.draw(134, 14);
            ofSetColor(0,0,0);
            verdana30.drawString("Put the ", 184, 86);
            verdana30.drawString("cassettes back!", 180, 142);
        }
        else if(heWantsthis != leftMixName && heWantsthis != rightMixName )
        {
            speak.draw(134, 14);
            ofSetColor(0,0,0);
            verdana30.drawString("Put on some", 184, 86);
            verdana30.drawString(heWantsthis + " music!", 188, 142);
        }
        
        if(heWantsthis == leftMixName) //These are to ratio it depedning on how loud the music is
        {
            bossDeductDiff = ofMap(mixerLeftRightVol, -10, 10, 0, 0.8);
        }
        else if(heWantsthis == rightMixName)
        {
            bossDeductDiff = ofMap(mixerLeftRightVol, -10, 10, 0.8, 0);
        }
        else
        {
            bossDeductDiff = 0.8;
        }
        cout << "bossDeduction " << bossDeduction << endl
        << " tempBossTimer " << tempBossTimer << endl
        << " bossHappy " << bossHappy << endl;

        if(bossDeduction < tempBossTimer && bossHappy > 0 && countCassBacks != 0)
        {
            bossHappy = bossHappy - 0.3;
            bossDeduction = tempBossTimer + 1000;
        }
        else if(bossDeduction < tempBossTimer && bossHappy > 0)//This decides if the music is right for boss
        {
            
            bossHappy = bossHappy - (1 * bossDeductDiff);
            bossDeduction = tempBossTimer + 1000;
        }
        
        if(tempBossTimer >= (bossTime*2))//Times it by two just to make another timer
        {
            bossLeave = true;
        }
        }
        else {
            speak.draw(134, 14);
            ofSetColor(0,0,0);
            verdana30.drawString("YOU'RE ", 254, 86);
            verdana30.drawString("FIRED!", 258, 142);
        }
    }
    
    
    //Now let's go back
    if(bossOriginX >= -boss.width && bossLeave) //The boss will pop out in front of us
    {
        bossOriginX -= 4;
        bossOriginY += 2;
    }
    else if (bossLeave)
    {
        bossTime = ofRandom(20000, 30000);
        bossStartTime = ofGetElapsedTimeMillis();
        bossLeave = false;
    }
}

//--------------------------------------------------------------
void testApp::keyPressed  (int key){
    if (key == 'z'){
        fScore ++;
         // do something
    } else if (key == 'x'){
        fScore --;
         // do something else
    }
    if (key == ' ' && gameState == "Start"){
        gameState = "Play";
    } // do something
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	// add into vx and vy a small amount of the change in mouse:
	// store the previous mouse position:
	prevx = x;
	prevy = y;
    
    for (int i = 0; i < nCassettes; i++){
        for(int holdTest = 0; holdTest< i; holdTest ++)
        {if (myCassette[holdTest]->cassHeld == true)
        {
            myCassette[i]->cassHeld = false;
        }
        }
        myCassette[i]->mouseDragged(prevx, prevy, button);
    }
    
    if(mouseX >= mixerX - mixerKnob.width/2 && mouseX <= mixerX + mixerKnob.width/2
       && mouseY >= 462 - mixerKnob.height/2 && mouseY <= 462 + mixerKnob.height/2)
    {
        if(mixerX >= 557 && mouseX <= mixerX)
        {
            mixerX = mouseX;
        }
        else if(mixerX <= 472 && mouseX >= mixerX)
        {
            mixerX = mouseX;
        }
        else if(mixerX > 472 && mixerX < 557)
        {
            mixerX = mouseX;
        }
    }
    
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	prevx = x;
	prevy = y;
    
    //Cassettes biatch. This checks all the cassette interaction
    for (int i = 0; i < nCassettes; i++){
        myCassette[i]->mousePressed(prevx, prevy, button);
        
    }
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    
    for (int i = 0; i < nCassettes; i++){
        myCassette[i]->mouseReleased(x, y, button);
        
    }
    
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){
    
}



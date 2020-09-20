#include "ofMain.h"
#include "testApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1020,780, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new testApp());

}


////Music from Incompetech
/*
Genre: Funk
Time: 0:38 130 BPM (Allegro - Pretty Fast)
Instruments: Guitar, Horns, Bass, Percussion
 
 Genre: Rock Collection: Rock Harder
 Time: 3:26 91 BPM (Moderato - A Bit Fast)
 Instruments: Bass, Kit, Organ, Guitar
 
 Genre: Pop Collection: Hard Electronic
 Time: 3:37 170 BPM (Presto - Fast)
 Instruments: Synths
 
 Genre: Classical Collection: Famous Classics
 Time: 2:33 160 BPM (Presto - Fast)
 Instruments: Orchestra
 
 Genre: Electronica Collection: Video Classica
 Time: 2:14 142 BPM (Allegro - Pretty Fast)
 Instruments: Synths
 
 
 Title:	THE PASSION HIFI - STRENGTH IN NUMBERS (FREE)
 Artist:	FREE HIP HOP BEATS FOR YOU    +136 songs
 Genre:	Instrumentals : Hip Hop

 
 To do list
 
 > Fix the percentage ratio problem
 > Make players animate
 > Give boss sound
 
*/
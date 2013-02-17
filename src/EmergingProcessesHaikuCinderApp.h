//
//  EmergingProcessesHaikuCinderApp.h
//  EmergingProcessesHaikuCinder
//
//  Created by Ryan Bartley on 2/14/13.
//
//


#pragma once

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Surface.h"
#include "cinder/gl/Texture.h"
#include "cinder/qtime/QuickTime.h"
#include "cinder/Rand.h"
#include "cinder/audio/SourceFile.h"
#include "cinder/audio/Output.h"
#include <iostream>

using namespace ci;
using namespace ci::app;
using namespace std;

//This is the magic. With this and some other tricks in c++
//you'll have total control over creating poetry in code.
//It's hard to think about code in this way and I did it
//after the fact (i.e. after writing a working version of
//the program.) This is really exciting.
typedef Rectf The;

class EmergingProcessesHaikuCinderApp : public AppBasic {
public:
	
    void prepareSettings( Settings* );
    void setup();
	void update();
	void draw();
    void keyDown( KeyEvent );
    Rectf composeItWithPattern( bool );
    void presentThe( The );
    
    
    gl::Texture                         set;
	qtime::MovieGl                      mMovie1;
    qtime::MovieGl                      mMovie2;
    qtime::MovieGl                      mMovie3;
    audio::TrackRef                     mTrack1;
    int                                 movie1Frames;
    int                                 movie2Frames;
    int                                 movie3Frames;
    int                                 totalSurpassedFrames;
    int                                 randomNumber;
    bool                                now;
    bool                                diff;
    bool                                exit;
    
    
};
#include "EmergingProcessesHaikuCinderApp.h"

using namespace std;

void EmergingProcessesHaikuCinderApp::prepareSettings(Settings* settings)
{
    //using the context settings to get 
    settings->setFullScreen(true);
    
}

void EmergingProcessesHaikuCinderApp::keyDown( KeyEvent event )
{
    //giving myself a way to jump out of the fullscreen for debug
    if(event.getChar() == 'f') {
        setFullScreen( !isFullScreen() );
    }
}

void EmergingProcessesHaikuCinderApp::setup()
{
    try {
		// load up the movies, settting them to loop, turning down the volume, and beginning to play
        mMovie1 = qtime::MovieGl( loadAsset("/analog.mov") );
		mMovie1.setLoop(true, false);
		mMovie1.play();
        mMovie1.setVolume(0);
        mMovie2 = qtime::MovieGl( loadAsset("/analogdigital.mov") );
		mMovie2.setLoop(true, false);
		mMovie2.play();
        mMovie2.setVolume(0);
        mMovie3 = qtime::MovieGl( loadAsset("/digital.mov") );
		mMovie3.setLoop(true, false);
		mMovie3.play();
        mMovie3.setVolume(0);
        
        //initializing the music that I made
        mTrack1 = audio::Output::addTrack( audio::load( loadAsset("/HaikuMusic.aif") ) );
        mTrack1->setVolume(3.0f);
        
        //getting the total number of frames so i don't access anything outside the array
        movie1Frames = mMovie1.getNumFrames();
        movie2Frames = mMovie2.getNumFrames();
        movie3Frames = mMovie3.getNumFrames();
        totalSurpassedFrames = 0;
        
        //setting up the switch statement
        randomNumber = rand()%3;
        now = true;
        diff = true;
	}
	catch( ... ) {
		//just throwing some errors to see what's happening
        if (!mMovie1){
            console() << "Unable to load the movie2." << std::endl;
            mMovie1.reset();
        } else if (!mMovie2){
            console() << "Unable to load the movie3." << std::endl;
            mMovie2.reset();
        } else if (!mMovie3){
            console() << "Unable to load the movie4." << std::endl;
            mMovie3.reset();
        }
	}
    
    //clearing the buffer on the texture
	set.reset();
    //only clearing the screen once.
    gl::clear( Color( 0, 0, 0 ) );
}



void EmergingProcessesHaikuCinderApp::update()
{
        
    if ( ((rand() % 100) > 50) && totalSurpassedFrames > 100 && mTrack1->isPlaying())
    {
        //cout << "I'm in the if part of the statement" << endl;
        randomNumber = (rand()%3) + 1;
        int randomFrame1 = randInt(movie1Frames);
        int randomFrame2 = randInt(movie2Frames);
        int randomFrame3 = randInt(movie3Frames);
        switch (randomNumber) {
            case 1:
                if( mMovie1 ) {
                    set = mMovie1.getTexture();
                    mMovie2.seekToFrame(randomFrame2);
                    mMovie3.seekToFrame(randomFrame3);
                    totalSurpassedFrames = 0;
                }
                break;
            case 2:
                if( mMovie2 ) {
                    set = mMovie2.getTexture();
                    mMovie1.seekToFrame(randomFrame1);
                    mMovie3.seekToFrame(randomFrame3);
                    totalSurpassedFrames = 0;
                }
                break;
            case 3:
                if( mMovie3 ) {
                    set = mMovie3.getTexture();
                    mMovie1.seekToFrame(randomFrame1);
                    mMovie2.seekToFrame(randomFrame2);
                    totalSurpassedFrames = 0;
                }
                break;
            default:
                break;
        }
    } else if (mTrack1->isPlaying()){
        //cout << "I'm in the else part of the statement" << endl;
        switch (randomNumber) {
            case 1:
                if( mMovie1 ) {
                    set = mMovie1.getTexture();
                }
                break;
            case 2:
                if( mMovie2 ) {
                    set = mMovie2.getTexture();
                }
                break;
            case 3:
                if( mMovie3 ) {
                    set = mMovie3.getTexture();
                }
                break;
            default:
                break;

        }
        totalSurpassedFrames++;
    }
    
}

//This is made specifically for the Haiku. I did not need to put this outside the draw
//step other than to write a sentence with the function name and pass it the boolean
//which is "now". Of course it's always true but just in case I made it put out the
//same content no matter what happened to the now variable. I could've made it a const
//but I think when I grow this idea I may make it do other things. Also, this function
//made an elegant place to check if the music was still playing and if not quit(). Kind
//of like this function that was created for the poem cleans itself up. I like that because
//of the name of the function.
Rectf EmergingProcessesHaikuCinderApp::composeItWithPattern( bool draw )
{
    if (mTrack1->isPlaying()) {
        if (draw)
            return Rectf( set.getBounds() ).getCenteredFit( getWindowBounds(), true );
        else
            return Rectf( set.getBounds() ).getCenteredFit( getWindowBounds(), true );
    } else {
        quit();
    }
}

//This is as above made specifically for the Haiku. The name like above is a literal
//of what it is actually doing, which is to draw the chaos.
void EmergingProcessesHaikuCinderApp::presentThe( The chaos )
{
    if(set) {
        gl::draw( set, chaos  );
        
    }
}



CINDER_APP_BASIC( EmergingProcessesHaikuCinderApp, RendererGl )

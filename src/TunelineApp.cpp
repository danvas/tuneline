#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"

#include <string>
#include <time.h>

// iPad dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1024

#define DOUBLE_CLICK_INTERVAL 0.30 //seconds

//For testing
#define BDAY_INPUT "1981-02-23"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace boost::gregorian;

class TunelineApp : public AppBasic {
  public:
    void prepareSettings(Settings*);
	void setup();
	void mouseDown(MouseEvent);
    void doubleClickLeft();
    void keyDown(KeyEvent);
    void mouseMove(MouseEvent);
    void mouseDrag(MouseEvent);
	void update();
	void draw();

    void testFunc(string);
    void levelUp();
    void levelDown();
    
    
    // Member variables
    DtnodeLine mDtnodeLine;
    
    Color mColor;
    Vec2i mMouseLoc;
    int mCurrentLevel;
    

    enum {LIFE, DECADE, YEAR, MONTH, DAY};
    unsigned int mLevelOnLaunch;
    Vec2f mParentPivot;
    unsigned int mDoubleClickFlag;
    double mLastClockReading;
};

void TunelineApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT ); 
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
    mParentPivot = Vec2f(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
    //mParentPivot = Vec2f(0.0f, 0.0f);

	mColor = Color(0.8f, 0.2f, 0.3f);
    mLevelOnLaunch = DAY;
    mCurrentLevel = mLevelOnLaunch;
    mDoubleClickFlag = 1;
    mLastClockReading = getElapsedSeconds();
    mDtnodeLine = DtnodeLine(BDAY_INPUT, mLevelOnLaunch, mParentPivot);
}

void TunelineApp::mouseDown( MouseEvent event )
{

    doubleClickLeft();
    Dtnode node = mDtnodeLine.getNodeAtPosition( event.getPos() );
    cout << "\nclicked at " << node.getPosition() <<endl;
    
}


void TunelineApp::keyDown( KeyEvent event )
{
    if ( event.getCode() == KeyEvent::KEY_DOWN )
    {
        levelDown();
    }
    
    if ( event.getCode() == KeyEvent::KEY_UP )
    {
        levelUp();
    }
}
/*
 * Double click function by chrisjeffdotcom on Cinder forum
 */
void TunelineApp::doubleClickLeft()
{
    double thisClockReading = getElapsedSeconds();
    double interval = thisClockReading - mLastClockReading;
    
    if( ( interval <= DOUBLE_CLICK_INTERVAL) && (mDoubleClickFlag!= 1) )
    {
        
        cout << "\ndouble clicked! ";
        cout << "interval = " << interval;
        testFunc("yep");
        mDoubleClickFlag = 1;
    }
    else
    {
        mDoubleClickFlag = 0;
    };
    mLastClockReading = thisClockReading;
}

void TunelineApp::mouseMove( MouseEvent event )
{
    mMouseLoc = event.getPos();
}

void TunelineApp::mouseDrag( MouseEvent event )
{
    mParentPivot = event.getPos();
    mouseMove( event );
    console() << "You dragged the mouse @ " << mParentPivot << endl;
}


void TunelineApp::update()
{
    
    mDtnodeLine.update(mColor, mParentPivot);
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.96f, 0.96f, 0.9f ) );
    mDtnodeLine.draw();
    

}


void TunelineApp::testFunc(string str)
{
    printf("\nPrinted %s from testFunc()", str.c_str());
}


void TunelineApp::levelUp()
{
    
    if ( mCurrentLevel != DAY )
    {
        mCurrentLevel += 1;
    }
    cout << "up key. View " << mCurrentLevel << endl;
}

void TunelineApp::levelDown()
{
    if ( mCurrentLevel != LIFE )
    {
        mCurrentLevel -= 1;
    }
    cout << "down key. View " << mCurrentLevel << endl;
}



CINDER_APP_BASIC( TunelineApp, RendererGl )

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"
#include "DateUtil.h"
#include "cinder/Rand.h"

#include <string>
#include <vector>
#include <time.h>

// iPad dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1004
#define MAX_TIMELINES 5
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
    void doubleClickLeft(MouseEvent&);
    void keyDown(KeyEvent);
    void mouseMove(MouseEvent);
    void mouseDrag(MouseEvent);
	void update();
	void draw();
    void levelUp();
    void levelDown();
    
    void testDateUtil(string);
    
    
    // Member variables
    DtnodeLine mDtnodeLine;
    DtnodeLine mLines[MAX_TIMELINES];
    
    Vec2i mMouseLoc;
    int mCurrentLevel;
    bool mMouseOnNode;
    

    enum {LIFE, DECADE, YEAR, MONTH, DAY};
    Vec2f mPivot;
    unsigned int mDoubleClickFlag;
    double mLastClockReading;
};

void TunelineApp::prepareSettings( Settings *settings )
{
//    settings->setWindowSize( 1, 1 );
	settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
//    testDateUtil(BDAY_INPUT);
//    mPivot = Vec2f(WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f);
    int levelOnLaunch = LIFE;
    mPivot = Vec2f(WINDOW_WIDTH/2.0f, 0.0f);
    mCurrentLevel = levelOnLaunch;
    mMouseOnNode = false;
    mDoubleClickFlag = 1;
    mLastClockReading = getElapsedSeconds();
    mDtnodeLine = DtnodeLine(BDAY_INPUT, levelOnLaunch, mPivot);
    mLines[levelOnLaunch] = mDtnodeLine;
}

void TunelineApp::mouseDown( MouseEvent event )
{
    doubleClickLeft(event);
}

/*
 * Double click function by chrisjeffdotcom on Cinder forum
 */
void TunelineApp::doubleClickLeft( MouseEvent &event)
{
    double thisClockReading = getElapsedSeconds();
    double interval = thisClockReading - mLastClockReading;
    
    if( ( interval <= DOUBLE_CLICK_INTERVAL) && (mDoubleClickFlag!= 1) )
    {
        
        cout << "\n***double clicked! ";
//        cout << "interval = " << interval << endl;
        Dtnode node = mLines[mCurrentLevel].getNodeAtPosition( event.getPos(), &mMouseOnNode );
        mPivot = node.position;
        levelUp();
//        cout << "\nmMouseOnNode = " << mMouseOnNode << endl;
        if(mMouseOnNode) cout << "\nclicked on node " << node.index <<endl;
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
    mouseMove(event);
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

void TunelineApp::update()
{
    mLines[mCurrentLevel].update();
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.96f, 0.96f, 0.9f ) );
    mLines[mCurrentLevel].draw();
//    gl::pushModelView();
//    gl::translate( Vec3f(getWindowWidth()/2,getWindowHeight()/2,0) );
//    gl::rotate( Vec3f(35,20,0) );
//    gl::drawCube( Vec3f::zero(), Vec3f(100,100,100) );
//    gl::popModelView();
//    gl::clear( Color( 0, 0, 0 ) );
    
}


void TunelineApp::levelUp()
{
    
    if ( mCurrentLevel != DAY )
    {
        mCurrentLevel++;
        mLines[mCurrentLevel] = DtnodeLine(BDAY_INPUT, mCurrentLevel, mPivot);
        mDtnodeLine = mLines[mCurrentLevel];
    }
    cout << "up key. View " << mCurrentLevel << endl;
}

void TunelineApp::levelDown()
{
    if ( mCurrentLevel != LIFE )
    {
        mDtnodeLine = mLines[--mCurrentLevel];
    }
    cout << "down key. View " << mCurrentLevel << endl;
}





void TunelineApp::testDateUtil(string dateStr){
    date today = day_clock::local_day();
    date birthdate = from_simple_string(dateStr);
    cout << "******************** DateUtil test output **************************" << endl;
    cout << "today: " << today << endl;
    cout << "birthdate: " << birthdate << endl;
    
    cout << birthdate.year() << " – " << today.year() <<" years: " << DateUtil::getYearspan(birthdate, today) << endl;
    cout << "2013 months: " << DateUtil::getMonthspan( greg_year(2013) ) << endl;
    cout << "Dec 2013 days: " << DateUtil::getDayspan( greg_year(2013), greg_month(12) ) << endl;
    
    cout << "*************************************************************" << endl;


}



CINDER_APP_BASIC( TunelineApp, RendererGl )

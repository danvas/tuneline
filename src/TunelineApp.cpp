#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"

#include <string>

// iPad dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1024

#define DOUBLE_CLICK_INTERVAL 0.30 //seconds
// age
#define AGE 32

using namespace ci;
using namespace ci::app;
using namespace std;

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
    
    void setTimeUnits(int, int, int);

    void testFunc(string);
    DtnodeLine mYearLine;
    
    Color mColor;
    Vec2i mMouseLoc;
    int mCurrentView;
    int decades;
    int years;
    int months;
    int days;
    enum mView {LIFE, DECADE, YEAR, MONTH, DAY};
    
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
    setTimeUnits(1981, -1, -1);
    mYearLine = DtnodeLine(days);
    
	mColor = Color(0.8f, 0.2f, 0.3f);
    mCurrentView = DECADE;
    mDoubleClickFlag = 1;
    mLastClockReading = getElapsedSeconds();
}

void TunelineApp::mouseDown( MouseEvent event )
{

    doubleClickLeft();
    Dtnode node = mYearLine.getNodeAtPosition( event.getPos() );
    cout << "clicked at " << node.getPosition() <<endl;
    
}


void TunelineApp::keyDown( KeyEvent event )
{
    if ( event.getCode() == KeyEvent::KEY_DOWN )
    {
        if ( mCurrentView != LIFE )
        {
            mCurrentView -= 1;
        }
        cout << "down key. View " << mCurrentView << endl;
        
    }
    
    if ( event.getCode() == KeyEvent::KEY_UP )
    {
        if ( mCurrentView != DAY )
        {
            mCurrentView += 1;
        }
        cout << "up key. View " << mCurrentView << endl;
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

void TunelineApp::mouseMove( MouseEvent event ) {
    mMouseLoc = event.getPos();
}

void TunelineApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void TunelineApp::update()
{
    
    mYearLine.update(mColor);
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.96f, 0.96f, 0.9f ) );
    mYearLine.draw();
    

}

void TunelineApp::setTimeUnits(int year, int month, int day)
{
    int thisYear = 2013;
    years = thisYear - year;
    decades = years/10;
    months = 12;
    days = 30;
}

void TunelineApp::testFunc(string str)
{
    cout << " Returned " << str << " from testFunc()" << endl;
}


CINDER_APP_BASIC( TunelineApp, RendererGl )

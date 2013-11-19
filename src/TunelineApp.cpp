#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"
#include "DateUtil.h"

#include <string>
#include <time.h>

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
    void levelUp();
    void levelDown();
    int getLevelResolution(int);
    
    
    DtnodeLine mDtnodeLine;
    DateUtil mDate;
    
    Color mColor;
    Vec2i mMouseLoc;
    int mCurrentView;
    int decades;
    int years;
    int months;
    int days;
    enum mLevel {LIFE, DECADE, YEAR, MONTH, DAY};
    unsigned int mLevelOnLaunch;
    
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
    //printf("years since 1981-Feb-23: %d", mDate.yearsSince("1981-02-23"));
    setTimeUnits(1981, 2, 23);
    
    
	mColor = Color(0.8f, 0.2f, 0.3f);
    mLevelOnLaunch = YEAR;
    mCurrentView = mLevelOnLaunch;
    mDoubleClickFlag = 1;
    mLastClockReading = getElapsedSeconds();
    int resolution = getLevelResolution(mLevelOnLaunch);
    mDtnodeLine = DtnodeLine(mLevelOnLaunch, resolution);
}

void TunelineApp::mouseDown( MouseEvent event )
{

    doubleClickLeft();
    Dtnode node = mDtnodeLine.getNodeAtPosition( event.getPos() );
    cout << "clicked at " << node.getPosition() <<endl;
    
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

void TunelineApp::mouseMove( MouseEvent event ) {
    mMouseLoc = event.getPos();
}

void TunelineApp::mouseDrag( MouseEvent event ) {
    mouseMove( event );
}


void TunelineApp::update()
{
    
    mDtnodeLine.update(mColor);
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.96f, 0.96f, 0.9f ) );
    mDtnodeLine.draw();
    

}

void TunelineApp::setTimeUnits(int year, int month, int day)
{
    time_t timer;
    struct tm y2k;
    double seconds;
    
    y2k.tm_hour = 0;   y2k.tm_min = 0; y2k.tm_sec = 0;
    y2k.tm_year = year - 1900; y2k.tm_mon = month; y2k.tm_mday = day;
    
    time(&timer);  /* get current time; same as: timer = time(NULL)  */
    
    seconds = difftime(timer,mktime(&y2k));
    
    
    printf ("\n%.f seconds since  %d, %d in the current timezone", seconds, y2k.tm_mday, year);
    
    int thisYear = 2013;
    years = thisYear - year;
    decades = years/10;
    months = 12;
    days = 30;
    printf("\nTime units set:\ndecades = %d\nyears = %d\nmonths = %d\ndays = %d", decades, years, months, days);
    printf("\nTimestamp units:\nyears = %d\nmonths = %d\ndays = %d", y2k.tm_year, y2k.tm_mon, y2k.tm_mday);
    
    
    //Current time
    time_t rawtime;
    struct tm * timeinfo;
    
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    printf ( "\nThe current date/time is: %s", asctime(timeinfo) );
    
    
    
}

void TunelineApp::testFunc(string str)
{
    printf("\nPrinted %s from testFunc()", str.c_str());
}


void TunelineApp::levelUp()
{
    
    if ( mCurrentView != DAY )
    {
        mCurrentView += 1;
    }
    cout << "up key. View " << mCurrentView << endl;
}

void TunelineApp::levelDown()
{
    if ( mCurrentView != LIFE )
    {
        mCurrentView -= 1;
    }
    cout << "down key. View " << mCurrentView << endl;
}

int TunelineApp::getLevelResolution(int level)
{
    int res = 1;
    switch (level) {
        case 0:
            break;
        case 1:
            res = decades;
            break;
        case 2:
            res = years;
            break;
        case 3:
            res = months;
            break;
        case 4:
            res = days;
            break;   
        default:
            res = -1;
            break;
    }
    return res;
}


CINDER_APP_BASIC( TunelineApp, RendererGl )

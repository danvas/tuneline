#include "cinder/qtime/MovieWriter.h"
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "cinder/Camera.h"
#include "cinder/params/Params.h"
#include "DtnodeLine.h"
#include "DateUtil.h"

#include "Resources.h"

#include <string>
#include <vector>
#include <time.h>


// iPad dimensions
#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define MAX_TIMELINES 5
#define DOUBLE_CLICK_INTERVAL 0.30 //seconds

//For testing
#define BDAY_INPUT "1981-02-23"

//MovieWriter options
#define MOVIE_REC 1 //true
#define MOVIE_WIDTH 1280
#define MOVIE_HEIGHT 720


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
    
    
    ///////////////////////////// Member variables /////////////////////////////////
    // CAMERA
	CameraOrtho         mCamera;
	Quatf				mSceneRotation;
	float				mCameraDistance;
	Vec3f				mEye, mCenter, mUp;
    
    // TIMELINE
    DtnodeLine mDtnodeLine;
    DtnodeLine mLines[MAX_TIMELINES];
    
    // MOUSE EVENTS
    Vec2i mMouseLoc;
    int mCurrentLevel;
    bool mMouseOnNode;
    
    // PARAMS
	params::InterfaceGlRef	mParams;
    
    
    enum {LIFE, DECADE, YEAR, MONTH, DAY};
    Vec2f mPivot;
    unsigned int mDoubleClickFlag;
    double mLastClockReading;
    
    // MovieWriter
    qtime::MovieWriterRef	mMovieWriter;
};

void TunelineApp::prepareSettings( Settings *settings )
{
	MOVIE_REC? settings->setWindowSize( MOVIE_WIDTH, MOVIE_HEIGHT ) : settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT );
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
    // CAMERA
    mCameraDistance = 500.0f;
	mEye			= Vec3f( 0.0f, 0.0f, mCameraDistance );
    mCenter     = Vec3f::zero();
    mUp         = Vec3f::yAxis();
    mCamera.setOrtho( 0, getWindowWidth(), getWindowHeight(), 0, -1000, 1000 );
    
    // SETUP PARAMS
//	mParams = params::InterfaceGl::create( "Tuneline", Vec2i( 200, 160 ) );
//	mParams->addParam( "Scene Rotation", &mSceneRotation, "opened=1" );
//	mParams->addSeparator();
//	mParams->addParam( "Cam Distance", &mCameraDistance, "min=50.0 max=1000.0 step=50.0 keyIncr=s keyDecr=w" );

//    testDateUtil(BDAY_INPUT);
    int levelOnLaunch = LIFE;
    mPivot = Vec2f(0.0f, getWindowHeight()/2.0f);
    mCurrentLevel = levelOnLaunch;
    mMouseOnNode = false;
    mDoubleClickFlag = 1;
    mLastClockReading = getElapsedSeconds();
    mDtnodeLine = DtnodeLine(BDAY_INPUT, levelOnLaunch, mPivot);
    mLines[levelOnLaunch] = mDtnodeLine;
    
    // MOVIEWRITER SETUP
    fs::path path = getSaveFilePath();
	if( path.empty() )
		return; // user cancelled save
    qtime::MovieWriter::Format format;
	mMovieWriter = qtime::MovieWriter::create( path, getWindowWidth(), getWindowHeight(), format );
	
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
        Dtnode node = mLines[mCurrentLevel].getNodeAtPosition( event.getPos(), &mMouseOnNode );
        if(mMouseOnNode){
            mPivot = node.position;
            cout << "\n*** double clicked on node " << node.index <<" at "<< node.position <<endl;
            levelUp();
        }
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
    // UPDATE CAMERA
	mEye = Vec3f( 0.0f, 0.0f, mCameraDistance );
	mCamera.lookAt( mEye, mCenter, mUp );
	gl::rotate( mSceneRotation );
//    cout << "mSceneRotation = " << mSceneRotation << endl;
    gl::setMatrices( mCamera );
    mLines[mCurrentLevel].update();
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0.96f, 0.96f, 0.9f ) );
    mLines[mCurrentLevel].draw();
    
    // DRAW PARAMS WINDOW
//	mParams->draw();
    
    // add this frame to our movie
	if( mMovieWriter )
		mMovieWriter->addFrame( copyWindowSurface() );
}


void TunelineApp::levelUp()
{
    
    if ( mCurrentLevel != DAY )
    {
        mCurrentLevel++;
        mDtnodeLine = DtnodeLine(BDAY_INPUT, mCurrentLevel, mPivot);
        mLines[mCurrentLevel] = mDtnodeLine;
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

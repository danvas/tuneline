#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"

#define YEARS 32

using namespace ci;
using namespace ci::app;
using namespace std;

class TunelineApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );

	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();

    DtnodeLine mDtnodeLine;
    Color mColor;
};

void TunelineApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 1024 );
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
    mDtnodeLine = DtnodeLine(YEARS);
	mColor = Color(0.5f, 0.3f, 0.8f);
    
}

void TunelineApp::mouseDown( MouseEvent event )
{
}

void TunelineApp::update()
{
    mDtnodeLine.update(mColor);
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    mDtnodeLine.draw();
    
    
}

CINDER_APP_BASIC( TunelineApp, RendererGl )

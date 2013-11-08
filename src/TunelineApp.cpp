#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"

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
};

void TunelineApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 800, 1024 );
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
}

void TunelineApp::mouseDown( MouseEvent event )
{
}

void TunelineApp::update()
{
}

void TunelineApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0 ) );
    gl::drawStrokedCube(getWindowCenter(), const Vec3f &size)
}

CINDER_APP_BASIC( TunelineApp, RendererGl )

#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"

// iPad dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1024
// age
#define YEARS 32

using namespace ci;
using namespace ci::app;
using namespace std;

class TunelineApp : public AppBasic {
  public:
    void prepareSettings( Settings *settings );
	void setup();
	void mouseDown( MouseEvent event );
    void mouseMove( MouseEvent event );
    void mouseDrag( MouseEvent event );
	void update();
	void draw();

    DtnodeLine mDtnodeLine;
    Color mColor;
    Vec2i mMouseLoc;
    

};

void TunelineApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT ); 
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
    mDtnodeLine = DtnodeLine(YEARS);
	mColor = Color(0.8f, 0.2f, 0.3f);

    
}

void TunelineApp::mouseDown( MouseEvent event )
{
    Dtnode node = mDtnodeLine.getNodeAtPosition( event.getPos() );
    cout << "clicked at " << node.getPosition() <<endl;
    
    

    
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

CINDER_APP_BASIC( TunelineApp, RendererGl )

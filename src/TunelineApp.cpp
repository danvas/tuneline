#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/Vector.h"
#include "DtnodeLine.h"

// iPad dimensions
#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 1024
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
    void keyDown(KeyEvent);
    void mouseMove(MouseEvent);
    void mouseDrag(MouseEvent);
	void update();
	void draw();

    DtnodeLine mDtnodeLine;
    Color mColor;
    Vec2i mMouseLoc;
    int mCurrentView;
    enum mView {DECADE, YEAR, MONTH, DAY};
    
    

};

void TunelineApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( WINDOW_WIDTH, WINDOW_HEIGHT ); 
	settings->setFrameRate( 60.0f );
}

void TunelineApp::setup()
{
    mDtnodeLine = DtnodeLine(AGE);
	mColor = Color(0.8f, 0.2f, 0.3f);
    mCurrentView = YEAR;
}

void TunelineApp::mouseDown( MouseEvent event )
{
    Dtnode node = mDtnodeLine.getNodeAtPosition( event.getPos() );
    cout << "clicked at " << node.getPosition() <<endl;
    
}


void TunelineApp::keyDown( KeyEvent event )
{
    if ( event.getCode() == KeyEvent::KEY_DOWN )
    {
        if ( mCurrentView != DECADE )
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

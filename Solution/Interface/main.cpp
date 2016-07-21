#include "Framework.h"
#include "Viewer.h"
#include "App.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	AppPtr app = AppPtr( new App );
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( App::getTag( ), app );
}

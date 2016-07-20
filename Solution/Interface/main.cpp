#include "Framework.h"
#include "Viewer.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	fw->addTask( Viewer::getTag( ), viewer );
}

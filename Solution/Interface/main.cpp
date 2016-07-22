#include "Framework.h"
#include "Viewer.h"
#include "Drawer.h"
#include "App.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	AppPtr app = AppPtr( new App );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( App::getTag( ), app );
	fw->addTask( Drawer::getTag( ), drawer );
}

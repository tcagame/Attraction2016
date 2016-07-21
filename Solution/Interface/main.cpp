#include "Framework.h"
#include "Drawer.h"
#include "Viewer.h"

void main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Drawer::getTag( ), drawer );
}

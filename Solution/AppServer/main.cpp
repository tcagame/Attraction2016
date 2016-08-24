#include "AppServer.h"
#include "Viewer.h"
#include "Drawer.h"
#include "Framework.h"


bool main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	AppServerPtr app_server = AppServerPtr( new AppServer );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );

	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( AppServer::getTag( ), app_server );
	

	return true;
}
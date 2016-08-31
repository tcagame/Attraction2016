#include "AppServer.h"
#include "Viewer.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Framework.h"


bool main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	AppServerPtr app_server = AppServerPtr( new AppServer );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );

	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( AppServer::getTag( ), app_server );
	fw->addTask( Keyboard::getTag( ), keyboard );
	return true;
}
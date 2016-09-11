#include "AppServer.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Framework.h"

bool main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	AppServerPtr app_server = AppServerPtr( new AppServer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );

	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( AppServer::getTag( ), app_server );
	fw->addTask( Keyboard::getTag( ), keyboard );

	fw->setWindowSize( 800, 600 );

	return true;
}
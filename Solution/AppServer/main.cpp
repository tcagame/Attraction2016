#include "AppServer.h"
#include "Drawer.h"
#include "Keyboard.h"
#include "Framework.h"
#include "Server.h"

bool main( ) {
	FrameworkPtr fw = Framework::getInstance ( );
	AppServerPtr app_server = AppServerPtr( new AppServer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	KeyboardPtr keyboard = KeyboardPtr( new Keyboard );
	ServerPtr server = ServerPtr( new Server );

	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( AppServer::getTag( ), app_server );
	fw->addTask( Keyboard::getTag( ), keyboard );
	fw->addTask( Server::getTag( ), server );

	fw->setWindowSize( 800, 600 );

	return true;
}
#include "PlayerFactory.h"
#include "Framework.h"
#include "Drawer.h"
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Client.h"
#include "PlayerCamera.h"
#include "Viewer.h"
#include "App.h"


PlayerFactory::PlayerFactory( const unsigned char player_id ) {
	FrameworkPtr fw = Framework::getInstance ( );
	DevicePtr device = DevicePtr( new Device );
	KeyboardPtr keyboad = KeyboardPtr( new Keyboard );
	MousePtr mouse = MousePtr( new Mouse );
	ClientPtr client = ClientPtr( new Client );
	AppPtr app = AppPtr( new App( player_id )  );
	ViewerPtr viewer = ViewerPtr( new Viewer );
	DrawerPtr drawer = DrawerPtr( new Drawer( "../Resource" ) );
	PlayerCameraPtr camera = PlayerCameraPtr( new PlayerCamera( ) );

	fw->addTask( Device::getTag( ), device );
	fw->addTask( Keyboard::getTag( ), keyboad );
	fw->addTask( Mouse::getTag( ), mouse );
	fw->addTask( Client::getTag( ), client );
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( App::getTag( ), app );
	fw->addTask( PlayerCamera::getTag( ), camera );
}


PlayerFactory::~PlayerFactory( ) {
}

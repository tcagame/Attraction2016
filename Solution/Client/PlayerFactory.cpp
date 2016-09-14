#include "PlayerFactory.h"
#include "Framework.h"
#include "Drawer.h"
#include "Device.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "Client.h"
#include "PlayerCamera.h"
#include "LiveCamera.h"
#include "Sound.h"
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
	CameraPtr camera;
	if ( player_id == PLAYER_NONE ) {
		camera = LiveCameraPtr( new LiveCamera );
	} else {
		camera = PlayerCameraPtr( new PlayerCamera );
	}
	SoundPtr sound = SoundPtr( new Sound( ) );

	fw->addTask( Device::getTag( ), device );
	fw->addTask( Keyboard::getTag( ), keyboad );
	fw->addTask( Mouse::getTag( ), mouse );
	fw->addTask( Client::getTag( ), client );
	fw->addTask( Viewer::getTag( ), viewer );
	fw->addTask( Drawer::getTag( ), drawer );
	fw->addTask( App::getTag( ), app );
	fw->addTask( Camera::getTag( ), camera );
	fw->addTask( Sound::getTag( ), sound );
}


PlayerFactory::~PlayerFactory( ) {
}

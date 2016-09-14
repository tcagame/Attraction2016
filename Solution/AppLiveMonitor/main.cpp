#include "PlayerFactory.h"
#include "LiveCamera.h"
#include "Live.h"
#include "Framework.h"

void main( ) {
	CameraPtr camera = LiveCameraPtr( new LiveCamera );
	PlayerFactory factory( PLAYER_NONE, camera );

	LivePtr live = LivePtr( new Live );
	FrameworkPtr fw = Framework::getInstance( );
	fw->addTask( Live::getTag( ), live );
}

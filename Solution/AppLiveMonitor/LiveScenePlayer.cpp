#include "LiveScenePlayer.h"
#include "Network.h"
#include "App.h"
#include "Player.h"
#include "Camera.h"

const int SCENE_TIME = 300; 

LiveScenePlayer::LiveScenePlayer() {
	_time = 0;
		_player_id = rand( ) % 4;
}


LiveScenePlayer::~LiveScenePlayer()
{
}

bool LiveScenePlayer::update( ) {
	PlayerPtr player;
	AppPtr app = App::getTask( );
	for ( int i = 0; i< 4; i++ ) {
		player = app->getPlayer( _player_id );
		if ( player->isExpired( ) ) {
			break;
		}
		_player_id = ( _player_id + 1 ) % 4;
	}

	if ( !player->isExpired( ) ) {
		return false;
	}

	_time++;
	if ( _time > SCENE_TIME ) {
		return true;
	}
	CameraPtr camera = Camera::getTask( );
	camera->setTarget( player->getPos( ) );
	return false;
}
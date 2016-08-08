#include "PlayerKnight.h"
#include "Camera.h"

const int MAX_HP = 200;
const int MAX_POWER = 1;

PlayerKnight::PlayerKnight( CameraConstPtr camera ) :
Player( new PlayerKnightBehavior( camera ) ) {
}

PlayerKnight::~PlayerKnight( ) {
}

void PlayerKnight::init( ) {
	setPos( Vector( 0, 0, 0 ) );
	setDir( Vector( 0, 1, 0 ) );
	STATUS status;
	status.hp = MAX_HP;
	status.power = MAX_POWER;
	status.speed = 0.1;
	setStatus( status );
	setExpired( false );
}
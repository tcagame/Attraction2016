#include "Viewer.h"
#include "Framework.h"
#include "Drawer.h"
#include "mathmatics.h"

enum MOTION {
	MOTION_WAIT
};

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	FrameworkPtr fw = Framework::getInstance( );
	fw->setCamera( Vector( 0, 0, 100 ), Vector( 0, 0, 0 ) );
	fw->setCameraUp( Vector( 0, 1, 0 ) );
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( MOTION_WAIT, "knight/player_knight_wait.mv1" );
}

void Viewer::finalize( ) {
}

void Viewer::update( ) {
	drawPlayer( );
}

void Viewer::drawPlayer( ) {
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Sprite sprite;
	sprite.res = MOTION_WAIT;
	sprite.transform = Drawer::Transform( 0, 0, 0, 1, 0 );
	sprite.time = 0;
	drawer->set( sprite );
}
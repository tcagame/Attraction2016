#include "Effect.h"
#include "Drawer.h"
#include "Camera.h"


Effect::Effect( ) {

}


Effect::~Effect( ) {

}


int Effect::setEffect( EFFECT effect ) {
	DrawerPtr drawer = Drawer::getTask( );
	return drawer->setEffect( effect );
}

void Effect::drawEffect( int playing_handle, Vector scale,Vector pos, Vector dir ) {
	CameraPtr camera = Camera::getTask( );
	if ( !camera ) {
		return;
	}
	bool in_screen = camera->isInScreen( pos );
	if ( !in_screen ) {
		return;
	}
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setPlayingEffectStatus( playing_handle, scale, pos, dir );
}

void Effect::deletEffect( int effect_handle ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->deleteEffect( effect_handle );
}
#include "Effect.h"
#include "Drawer.h"


Effect::Effect( ) {

}


Effect::~Effect( ) {

}


int Effect::setEffect( EFFECT effect ) {
	DrawerPtr drawer = Drawer::getTask( );
	return drawer->setEffect( effect );
}

void Effect::drawEffect( int playing_handle, Vector scale,Vector pos, Vector dir ) {
	DrawerPtr drawer = Drawer::getTask( );
	drawer->setPlayingEffectStatus( playing_handle, scale, pos, dir );
}

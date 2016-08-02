#include "App.h"
#include "Ground.h"
#include "GroundModel.h"
#include "Player.h"
#include "Keyboard.h"
#include "Framework.h"

AppPtr App::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< App >( fw->getTask( App::getTag( ) ) );
}

App::App( ) {

}


App::~App( ) {
}

void App::update( ) {
	_player->update( );
	KeyboardPtr keyboad = Keyboard::getTask( );
	if ( keyboad->isPushKey( "A" ) ) {
		_player->setPos( Vector( 0, 0, 0 ) );
	}
}

void App::initialize( ) {
	_ground = GroundPtr( new Ground( "map.csv" ) );
	_player = PlayerPtr( new Player( ) );
	_ground_model = GroundModelPtr( new GroundModel( ) );
	_ground_model->loadModelData( );
}

void App::finalize( ) {

}

GroundPtr App::getGround( ) const {
	return _ground;
}

PlayerPtr App::getPlayer( ) const {
	return _player;
}
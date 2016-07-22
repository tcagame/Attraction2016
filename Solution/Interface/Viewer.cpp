#include "Viewer.h"
#include "App.h"
#include "Model.h"
#include "Ground.h"
#include "Drawer.h"
#include "Framework.h"
#include "mathmatics.h"


const char* TEXTURE_NAME = "dummy_tex.jpg";
const char* PILLAR_NAME = "dummy_tex.jpg";
const char* PLAIN_NAME = "dummy_tex.jpg";

enum GROUND_TYPE {
	GROUND_TYPE_PILLAR,
	GROUND_TYPE_PLAIN,
	GROUND_TYPE_MAX
};

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
	_model = ModelPtr( new Model( ) );
	_tex_handle = _model->getTextureHandle( TEXTURE_NAME );
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

void Viewer::drawPillarGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGroundPtr( );
	_model->load( PILLAR_NAME );
	
	int width = ground->getWidth( );
	int height = ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int data = ground->getGroundData( idx );
			if ( data == GROUND_TYPE_PILLAR ) {
				_model->draw( _tex_handle );
			}
		}
	}
}

void Viewer::drawPlainGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGroundPtr( );
	_model->load( PILLAR_NAME );
	
	int width = ground->getWidth( );
	int height = ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int data = ground->getGroundData( idx );
			if ( data == GROUND_TYPE_PLAIN ) {
				_model->draw( _tex_handle );
			}
		}
	}
}
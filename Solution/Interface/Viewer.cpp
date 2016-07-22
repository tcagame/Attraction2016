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
	MOTION_WAIT,
	MOTION_WALK,
	MOTION_ATTACK,
	MOTION_DAMAGE,
	MOTION_DEAD,
	MOTION_USE,
	MOTION_MAX
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
	fw->setCameraUp( Vector( 0, 1, 0 ) );
	fw->setCamera( Vector( 0, 40, 40 ), Vector( 0, 0, 0 ) );
	_model = ModelPtr( new Model( ) );
	_tex_handle = _model->getTextureHandle( TEXTURE_NAME );
	
	//モーションのロード
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( MOTION_WAIT, "knight/player_knight_wait.mv1" );
	drawer->load( MOTION_WALK, "knight/player_knight_walk.mv1" );
	drawer->load( MOTION_ATTACK, "knight/player_knight_attack.mv1" );
	drawer->load( MOTION_DAMAGE, "knight/player_knight_damege.mv1" );
	drawer->load( MOTION_DEAD, "knight/player_knight_dead.mv1" );
	drawer->load( MOTION_USE, "knight/player_knight_use.mv1" );

	_time = 0.0;
}

void Viewer::finalize( ) {
}

void Viewer::update( ) {
	drawPlayer( );
}

void Viewer::drawPlayer( ) {
	static int res = 0;
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Sprite sprite;
	sprite.res = res;
	sprite.transform = Drawer::Transform( 0, 0, 0, 0, -1 );
	sprite.time = _time;
	drawer->set( sprite );
	if ( drawer->getEndAnimTime( sprite.res ) < _time ) {
		res++;
		if ( res == MOTION_MAX ) {
			res = 0;
		}
		_time = 0;
	}
	_time += 1;
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
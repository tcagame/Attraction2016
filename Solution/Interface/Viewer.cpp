#include "Viewer.h"
#include "App.h"
#include "Model.h"
#include "Ground.h"
#include "Drawer.h"
#include "Framework.h"
#include "Device.h"
#include "mathmatics.h"


const char* TEXTURE_NAME = "../Resource/data/dummy_tex.jpg";
const char* PILLAR_NAME = "../Resource/data/Pillar.mdl";
const char* PLAIN_NAME = "../Resource/data/Plain.mdl";
const double CHIP_SIZE = 1;
const Vector UP_VEC = Vector( 0, 1, 0 );
const Vector START_CAMERA_POS = Vector( 0, 50, 50 );
const Vector START_TARGET_POS = Vector( 0, 0, 0 );


enum GROUND_TYPE {
	GROUND_TYPE_PILLAR,
	GROUND_TYPE_PLAIN,
	GROUND_TYPE_MAX
};

enum MOTION {
	MOTION_PLAYER_WAIT,
	MOTION_PLAYER_WALK,
	MOTION_PLAYER_ATTACK,
	MOTION_PLAYER_DAMAGE,
	MOTION_PLAYER_DEAD,
	MOTION_PLAYER_USE,
	MOTION_MINOTAUR_WAIT,
	MOTION_MINOTAUR_WALK,
	MOTION_MINOTAUR_CLEAVE,
	MOTION_MINOTAUR_DAMAGE,
	MOTION_MINOTAUR_DEAD,
	MOTION_MINOTAUR_SMASH,
	MOTION_MINOTAUR_DASH,
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
	fw->setCameraUp( UP_VEC );
	fw->setCamera( START_CAMERA_POS, START_TARGET_POS );
	_model = ModelPtr( new Model( ) );
	_tex_handle = _model->getTextureHandle( TEXTURE_NAME );
	
	//モーションのロード
	DrawerPtr drawer = Drawer::getTask( );
	drawer->load( MOTION_PLAYER_WAIT, "knight/player_knight_wait.mv1" );
	drawer->load( MOTION_PLAYER_WALK, "knight/player_knight_walk.mv1" );
	drawer->load( MOTION_PLAYER_ATTACK, "knight/player_knight_attack.mv1" );
	drawer->load( MOTION_PLAYER_DAMAGE, "knight/player_knight_damege.mv1" );
	drawer->load( MOTION_PLAYER_DEAD, "knight/player_knight_dead.mv1" );
	drawer->load( MOTION_PLAYER_USE, "knight/player_knight_use.mv1" );
	drawer->load( MOTION_MINOTAUR_WAIT, "minotaur/enemy_minotaur_wait.mv1" );
	drawer->load( MOTION_MINOTAUR_WALK, "minotaur/enemy_minotaur_walk.mv1" );
	drawer->load( MOTION_MINOTAUR_CLEAVE, "minotaur/enemy_minotaur_cleave.mv1" );
	drawer->load( MOTION_MINOTAUR_DAMAGE, "minotaur/enemy_minotaur_damege.mv1" );
	drawer->load( MOTION_MINOTAUR_DEAD, "minotaur/enemy_minotaur_dead.mv1" );
	drawer->load( MOTION_MINOTAUR_SMASH, "minotaur/enemy_minotaur_smash.mv1" );
	drawer->load( MOTION_MINOTAUR_DASH, "minotaur/enemy_minotaur_dash.mv1" );
}

Vector Viewer::getDeviceConvertDir( ) {
	const Vector BASE_DIR = Vector( 0, 0, 1 );
	Vector camera_dir = START_TARGET_POS - START_CAMERA_POS;
	camera_dir.y = 0;
	double angle = camera_dir.angle( BASE_DIR );
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), angle );
	DevicePtr device = Device::getTask( );
	Vector device_dir;
	device_dir.x = device->getDirX( );
	device_dir.z = device->getDirY( );
	return mat.multiply( device_dir );
}

void Viewer::update( ) {
	drawPlayer( );
	//drawEnemy( );
	drawGroundModel( );
}

void Viewer::drawPlayer( ) {
	Vector move_vec = getDeviceConvertDir( );
	static int res = MOTION_PLAYER_WAIT;
	if ( move_vec.getLength( )  > 0 ) {
		res = MOTION_PLAYER_WALK;
	} else {
		 res = MOTION_PLAYER_WAIT;
	}
	static int p_time = 0;
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Sprite sprite;
	sprite.res = res;
	sprite.transform = Drawer::Transform( move_vec.x / 100, move_vec.y / 100, move_vec.z / 100, move_vec.x, move_vec.z );
	sprite.time = p_time % ( int )( drawer->getEndAnimTime( sprite.res ) );
	drawer->set( sprite );
	p_time += 1;
}

void Viewer::drawEnemy( ) {
	static int res = MOTION_MINOTAUR_WAIT;
	static int e_time = 0;
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Sprite sprite;
	sprite.res = res;
	sprite.transform = Drawer::Transform( 0, 0, 0, 0, -1 );
	sprite.time = e_time;
	drawer->set( sprite );
	if ( drawer->getEndAnimTime( sprite.res ) < e_time ) {
		res++;
		if ( res == MOTION_MAX ) {
			res = MOTION_MINOTAUR_WAIT;
		}
		e_time = 0;
	}
	e_time += 1;
}

void Viewer::drawGroundModel( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGroundPtr( );
	_model->load( PILLAR_NAME );
	
	int width = ground->getWidth( );
	int height = ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			int idx = ground->getIdx( i, j );
			int data = ground->getGroundData( idx );
			switch( data ) {
			case GROUND_TYPE_PILLAR:
				_model->load( PILLAR_NAME );
				break;
			case GROUND_TYPE_PLAIN:
				_model->load( PLAIN_NAME );
				break;
			default:
				break;
			}
			if ( _model ) {
				_model->translate( Vector( i * CHIP_SIZE, 0, j * CHIP_SIZE ) );
				_model->draw( _tex_handle );
			}
		}
	}
}

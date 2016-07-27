#include "Viewer.h"
#include "App.h"
#include "Model.h"
#include "Ground.h"
#include "Player.h"
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

Vector Viewer::getConvertDeviceVec( ) {
	//カメラの向きを求めている
	Vector camera_dir = getCameraDir( );
	//カメラの向きとまっすぐ進む向きとの差角を求める
	double angle = camera_dir.angle( Vector( 0, 0, 1 ) );
	int temp = ( angle * 180 ) / PI;//度数で確認する用
	//差角分回転する回転行列をつくる
	Matrix mat = Matrix::makeTransformRotation( Vector( 0, 1, 0 ), angle );

	//デバイスの入力方向をXZに
	Vector device_dir = covertInputDirXZ( );
	//差角分回転させる
	device_dir = mat.multiply( device_dir );
	return device_dir;
}

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( getTag( ) ) );
}

Viewer::Viewer( ) {
}

Viewer::~Viewer( ) {
}

void Viewer::initialize( ) {
	//カメラの設定
	FrameworkPtr fw = Framework::getInstance( );
	fw->setCameraUp( UP_VEC );
	_camera_pos = START_CAMERA_POS;
	_target_pos = START_TARGET_POS;

	//モーションのロード
	DrawerPtr drawer = Drawer::getTask( );
	drawer->loadMV1Model( MOTION_PLAYER_WAIT, "knight/player_knight_wait.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_WALK, "knight/player_knight_walk.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_ATTACK, "knight/player_knight_attack.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_DAMAGE, "knight/player_knight_damege.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_DEAD, "knight/player_knight_dead.mv1" );
	drawer->loadMV1Model( MOTION_PLAYER_USE, "knight/player_knight_use.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_WAIT, "minotaur/enemy_minotaur_wait.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_WALK, "minotaur/enemy_minotaur_walk.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_CLEAVE, "minotaur/enemy_minotaur_cleave.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_DAMAGE, "minotaur/enemy_minotaur_damege.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_DEAD, "minotaur/enemy_minotaur_dead.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_SMASH, "minotaur/enemy_minotaur_smash.mv1" );
	drawer->loadMV1Model( MOTION_MINOTAUR_DASH, "minotaur/enemy_minotaur_dash.mv1" );

	_model = ModelPtr( new Model( ) );
	_tex_handle = _model->getTextureHandle( TEXTURE_NAME );
}

void Viewer::update( ) {
	FrameworkPtr fw = Framework::getInstance( );
	drawPlayer( );
	//drawEnemy( );
	drawGroundModel( );
	fw->setCamera( _camera_pos, _target_pos );
}

void Viewer::drawPlayer( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );

	int motion = MOTION_PLAYER_WAIT;
	switch( player->getStatus( ) ) {
	case Player::STATUS_WAIT:
		motion = MOTION_PLAYER_WAIT;
		break;
	case Player::STATUS_WALK:
		motion = MOTION_PLAYER_WALK;
		break;
	default:
		break;
	}
	
	int time = player->getAnimTime( );
	Vector pos = player->getPos( );
	Vector dir = player->getDir( );
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( pos.x, pos.y, pos.z, dir.x, dir.z, motion, time );
	drawer->setModel( model );
}

void Viewer::drawEnemy( ) {
	static int motion = MOTION_MINOTAUR_WAIT;
	static int time = 0;
	DrawerPtr drawer = Drawer::getTask( );
	Drawer::Model model = Drawer::Model( 0, 0, 0, 1, 0, motion, time );
	drawer->setModel( model );
	if ( drawer->getEndAnimTime( model.motion ) < time ) {
		motion++;
		if ( motion == MOTION_MAX ) {
			motion = MOTION_MINOTAUR_WAIT;
		}
		time = 0;
	}
	time += 1;
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

Vector Viewer::getCameraDir( ) {
	Vector result = _target_pos - _camera_pos;
	result.y = 0;//Yの値を０にしてXZ平面のベクトルにする。
	return result.normalize( );
}

Vector Viewer::covertInputDirXZ( ) {
	//ゲームパッドからの入力をXZ平面に
	DevicePtr device = Device::getTask( );
	Vector result;
	result.x = -device->getDirX( );
	result.z = device->getDirY( );
	return result;
}
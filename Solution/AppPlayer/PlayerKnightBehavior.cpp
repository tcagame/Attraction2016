#include "PlayerKnightBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "Camera.h"
#include "App.h"
#include "BulletSword.h"
#include "Weapon.h"
#include "GroundModel.h"

PlayerKnightBehavior::PlayerKnightBehavior( CameraConstPtr camera ) : 
PlayerBehavior( camera ) {
}

PlayerKnightBehavior::~PlayerKnightBehavior( ) {
}

//アニメーションを変更したらその時点でリターン
void PlayerKnightBehavior::animationUpdate( ) {
	if ( _animation->isEndAnimation( ) ) {
		_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WAIT ) );
		return;
	}
	int motion = _animation->getMotion( );

	if ( !canChangeMotion( ) ) {
		return;
	}

	bool on_move = false;
	if ( _camera->getConvertDeviceVec( ).getLength2( ) > 0 ) {
		on_move = true;
	}
	if ( on_move && motion != Animation::MOTION_MINOTAUR_WALK ) {
		_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_WALK ) );
		return;
	}
}

void PlayerKnightBehavior::attack( ) {
	bool is_attack = _animation->getMotion( ) == Animation::MOTION_PLAYER_ATTACK;
	bool on_attack = is_attack && !_animation->isEndAnimation( );
	if ( on_attack || !canChangeMotion( ) ) {
		return;
	}
	AppPtr app = App::getTask( );
	WeaponPtr weapon = app->getWeapon( );
	BulletPtr bullet = BulletSwordPtr( new BulletSword( _parent->getPos( ) + Vector( 0, 0, 0.5 ), _parent->getDir( ).x, _parent->getDir( ).y ) );
	weapon->add( bullet );
	_animation = AnimationPtr( new Animation( Animation::MOTION_PLAYER_ATTACK ) );
}

bool PlayerKnightBehavior::canChangeMotion( ) {
	int motion = _animation->getMotion( );
	bool result = motion == Animation::MOTION_PLAYER_WALK; 
	result = result || motion == Animation::MOTION_PLAYER_WAIT;
	return result;
}
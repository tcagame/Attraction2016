#pragma once
#include "smart_ptr.h"

PTR( Animation );

class Animation {
public:
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
	MOTION_GHOST_WAIT,
	MOTION_GHOST_WALK,
	MOTION_DEEDBOX,
	MOTION_MAX
};
public:
	Animation( MOTION motion = MOTION_MAX, double anim_speed = 1.0 );
	virtual ~Animation( );
public:
	void update( );
	bool isEndAnimation( ) const;
	int getMotion( ) const;
	double getAnimTime( ) const;
	void setAnimationTime( double anim_time );
private:
	double _anim_time;
	double _max_anim_time;
	double _anim_speed;
	MOTION _motion;
};


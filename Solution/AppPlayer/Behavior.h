#pragma once
#include "smart_ptr.h"

PTR( Animation );
PTR( Behavior );
PTR( Character );

class Behavior {
public:
	enum COMMON_STATE {
		COMMON_STATE_WAIT,
		COMMON_STATE_WALK,
		COMMON_STATE_ATTACK,
		COMMON_STATE_DEAD,
	};
public:
	Behavior( );
	virtual ~Behavior( );
public:
	virtual void update( ) = 0;
	AnimationPtr getAnimation( ) const;
	void setParent( CharacterPtr parent );
protected:
	virtual void animationUpdate( ) = 0;
protected:
	CharacterPtr _parent;
	AnimationPtr _animation;
	COMMON_STATE _common_state;
	COMMON_STATE _befor_state;
};


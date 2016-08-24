#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( DeedBox );
PTR( Animation );

class DeedBox {
public:
	enum  PHASE {
		PHASE_CLOSE,
		PHASE_UNLOCK,
		PHASE_OPEN,
	};
public:
	DeedBox( Vector pos );
	virtual ~DeedBox( );
public:
	void update( );
	Vector getPos( ) const;
	Vector getDir( ) const;
	AnimationPtr getAnimation( );
	void pickup( );
private:
	Vector _pos;
	Vector _dir;
	AnimationPtr _animation;
	PHASE _phase;
};


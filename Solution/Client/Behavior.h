#pragma once
#include "smart_ptr.h"

PTR( Animation );
PTR( Behavior );
PTR( Character );

class Behavior {
public:
	Behavior( );
	virtual ~Behavior( );
public:
	void mainLoop( );
	AnimationPtr getAnimation( ) const;
	void setParent( CharacterPtr parent );
	void reset( );
protected:
	virtual void update( ) = 0;
	virtual void animationUpdate( ) = 0;
protected:
	CharacterPtr _parent;
	AnimationPtr _animation;
};


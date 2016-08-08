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
	void update( );
	void setParent( CharacterPtr parent );
	AnimationPtr getAnimation( ) const;
protected:
	virtual void moveUpdate( ) = 0;
private:
	void animationUpdate( );
protected:
	AnimationPtr _animation;
	CharacterPtr _parent;
};


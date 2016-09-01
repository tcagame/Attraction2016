#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"

PTR( LiveCamera );

class LiveCamera {
public:
	LiveCamera( );
	virtual ~LiveCamera( );
public:
	Vector getPos( ) const;
	Vector getTarget( ) const;
	void setTarget( Vector target );
	void update( );
private:
	Vector _pos;
	Vector _target;
};
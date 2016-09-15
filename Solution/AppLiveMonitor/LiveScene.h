#pragma once
#include "smart_ptr.h"

PTR( LiveScene );

class LiveScene {
public:
	LiveScene( );
	virtual ~LiveScene( );
public:
	virtual bool update( ) = 0;
};


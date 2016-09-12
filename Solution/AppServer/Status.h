#pragma once

#include "smart_ptr.h"

PTR( Status );
PTR( TableDrawer );

class Status {
public:
	Status();
	virtual ~Status();
public:
	void update( );
	void draw( );
private:
	TableDrawerPtr _td;
};


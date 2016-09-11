#pragma once

#include "smart_ptr.h"

PTR( Connect );
PTR( TableDrawer );

class Connect {
public:
	Connect( );
	virtual ~Connect( );
public:
	void draw( );
private:
	TableDrawerPtr _td;
};


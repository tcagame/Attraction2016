#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Crystal )

class Crystal {
public:
	Crystal( );
	virtual ~Crystal( );
public:
	void create( Vector pos );
	Vector getPos( );
	bool isExpired( );
	void pickup( );
private:
	Vector _pos;
	bool _expired;
};


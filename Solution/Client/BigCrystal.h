#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( BigCrystal );

class BigCrystal {
public:
	BigCrystal( );
	virtual ~BigCrystal( );
public:
	Vector getPos( );
	void create( Vector pos );
	bool isExpired( );
private:
	Vector _pos;
	bool _expired;
};


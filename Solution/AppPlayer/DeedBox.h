#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( DeedBox );

class DeedBox {
public:
	DeedBox( Vector pos );
	virtual ~DeedBox( );
public:
	Vector getPos( ) const;
	Vector getDir( ) const;
private:
	Vector _pos;
	Vector _dir;

};


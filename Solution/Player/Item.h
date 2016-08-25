#pragma once
#include "smart_ptr.h"
#include "mathmatics.h"

PTR( Item );
class Item {
public:
	Item( );
	virtual ~Item( );
public:
	Vector getPos( );
private:
	Vector _pos;
};


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
	void pickup( );
	bool isExpired( );
private:
	Vector _pos;
	bool _expired;
};


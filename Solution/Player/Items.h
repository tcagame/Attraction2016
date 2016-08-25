#pragma once
#include "smart_ptr.h"
#include <array>

PTR( Items );
PTR( Item );
class Items {
public:
	static const int MAX_ITEM_NUM = 100;
public:
	Items( );
	virtual ~Items( );
public:
	ItemPtr getItem( int idx );
	void add( );
	void update( );
private:
	std::array< ItemPtr, MAX_ITEM_NUM > _items;
};


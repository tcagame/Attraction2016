#pragma once
#include "smart_ptr.h"
#include <array>

PTR( Field );
PTR( Object );

class Field {
public:
	Field( );
	virtual ~Field( );
public:
	void initialize( );
	bool setTarget( int x, int y, ObjectPtr object );
	void delTarget( int x, int y, ObjectPtr object );
	ObjectPtr getTarget( int x, int y );
private:
	int getIndexTargetBoard( int x, int y );
private:
	static const int MAX_MAP_CHIP_NUM = 50000;
private:
	std::array< ObjectWeakPtr, MAX_MAP_CHIP_NUM > _target_board;
};


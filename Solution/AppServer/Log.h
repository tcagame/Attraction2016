#pragma once
#include "smart_ptr.h"
#include <string>

PTR( Log );
PTR( TableDrawer );

class Log {
public: 
	Log( );
	virtual ~Log( );
public:
	void add( std::string str );
	void draw( );
private:
	TableDrawerPtr _td;
};


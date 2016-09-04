#pragma once

#include "smart_ptr.h"
#include <string>

PTR( Command );
PTR( TableDrawer );

class Command {
public:
	Command( );
	virtual ~Command( );
public:
	void update( );
	void draw( );
	std::string get( );
private:
	std::string _display;
	std::string _output;
	TableDrawerPtr _td;
};

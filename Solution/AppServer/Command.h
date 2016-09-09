#pragma once

#include "smart_ptr.h"
#include <string>
#include <vector>

PTR( Command );
PTR( TableDrawer );

class Command {
public:
	Command( );
	virtual ~Command( );
public:
	struct DATA {
		std::string input;
		std::vector< std::string > word;
	};
public:
	DATA update( );
	void draw( );
private:
	std::string _input;
	TableDrawerPtr _td;
};

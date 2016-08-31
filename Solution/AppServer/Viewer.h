#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( Viewer );
PTR( TableDrawer );


class Viewer : public Task {
public:
	static std::string getTag( ) { return "VIEWER"; }
	static ViewerPtr getTask( );
public:
	void update( );
	void initialize( );
public:
	Viewer( );
	virtual ~Viewer( );
private:

};
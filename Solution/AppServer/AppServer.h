#pragma once
#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( AppServer );

class AppServer : public Task {
public:
	static std::string getTag( ) { return "APPSERVER"; }
	static AppServerPtr getTask( );
public:
	AppServer( );
	virtual ~AppServer( );
public:
	void update( );
};


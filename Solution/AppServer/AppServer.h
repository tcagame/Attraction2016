#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( AppServer );
PTR( TableDrawer );
PTR( Log );
PTR( Command );

class AppServer : public Task {
public:
	static std::string getTag( ) { return "APPSERVER"; }
	static AppServerPtr getTask( );
public:
	AppServer( );
	virtual ~AppServer( );
public:
	void initialize( );
	void update( );
private:
	void updateCommand( );
private:
	TableDrawerPtr _td_status;
	CommandPtr _command;
	LogPtr _log;
};


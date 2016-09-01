#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include <string>

PTR( AppServer );
PTR( TableDrawer );
PTR( Log );

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
	std::string _command;
	TableDrawerPtr _td_status;
	TableDrawerPtr _td_command;
	LogPtr _log;
};


#pragma once

#include "Task.h"
#include "smart_ptr.h"
#include <string>
#include <vector>

PTR( AppServer );
PTR( TableDrawer );
PTR( Log );
PTR( Command );
PTR( Connect );
PTR( Server );

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
	void draw( );
	void process( );
	void processCommand( );
private:
	TableDrawerPtr _td_status;
	CommandPtr _command;
	LogPtr _log;
	ConnectPtr _connect;
	ServerPtr _server;
};


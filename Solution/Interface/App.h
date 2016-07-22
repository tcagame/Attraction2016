#pragma once
#include "Task.h"
#include <string>

PTR( App );
PTR( Ground );

class App : public Task {
public:
	static std::string getTag( ) { return "APP"; }
	static AppPtr getTask( );
public:
	App( );
	virtual ~App( );
public:
	void update( );
	void initialize( );
	void finalize( );
	GroundPtr getGroundPtr( ) const;
private:
	GroundPtr _ground;
};


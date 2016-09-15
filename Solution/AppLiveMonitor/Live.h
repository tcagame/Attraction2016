#pragma once

#include "Task.h"
#include <string>

PTR( Live );
PTR( LiveScene );

class Live : public Task {
public:
	static std::string getTag( ) { return "LIVE"; }
	static LivePtr getTask( );
public:
	Live();
	virtual ~Live();
public:
	void update( );
	void initialize( );
	void finalize( );
private:
	LiveScenePtr _scene;
};


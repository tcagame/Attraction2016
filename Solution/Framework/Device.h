#pragma once
#include "Task.h"
#include "mathmatics.h"
#include <string>

PTR( Device );

class Device : public Task {
public:
	static std::string getTag( ) { return "DEVICE"; }
	static DevicePtr getTask( );
public:
	Device( );
	virtual ~Device( );
public:
	void update( );
	char getDirX( ) const;
	char getDirY( ) const;
	unsigned char getButton( ) const;
private:
	struct DATA {
		char x;
		char y;
	};
private:
	DATA _data;
};
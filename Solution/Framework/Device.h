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
	void changeInputVec( Vector base_dir );
	unsigned char getButton( ) const;
private:
	struct DATA {
		char x;
		char y;
	};
private:
	DATA _data;
	Matrix _mat;
};
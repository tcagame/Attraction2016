#pragma once

#include "smart_ptr.h"
#include "mathmatics.h"
#include "Task.h"
#include <string>

PTR( Camera );

class Camera : public Task {
public:
	static std::string getTag( ) { return "CAMERA"; }
	static CameraPtr getTask( );
public:
	Camera( );
	virtual ~Camera( );
public:
	Vector getPos( ) const;
	Vector getTarget( ) const;
	void setTarget( Vector target );
	virtual void update( ) = 0;
	virtual void initialize( ) { };
protected:
	Vector _pos;
	Vector _target;
};


#pragma once
#include "Task.h"
#include "mathmatics.h"
#include <string>

PTR( Device );

class Device : public Task {
public:
	enum BUTTON_LIST {
		BUTTON_LIST_DOWN,//PAD_INPUT_DOWN
		BUTTON_LIST_LEFT,//PAD_INPUT_LEFT
		BUTTON_LIST_RIGHT,//PAD_INPUT_RIGHT
		BUTTON_LIST_UP,//PAD_INPUT_UP
		BUTTON_LIST_1,//PAD_INPUT_1　	
		BUTTON_LIST_2,//PAD_INPUT_2　	
		BUTTON_LIST_3,//PAD_INPUT_3　	
		BUTTON_LIST_4,//PAD_INPUT_4　	
		BUTTON_LIST_5,//PAD_INPUT_5　	
		BUTTON_LIST_6,//PAD_INPUT_6　	
		BUTTON_LIST_7,//PAD_INPUT_7　	
		BUTTON_LIST_8,//PAD_INPUT_8　	
		BUTTON_LIST_9,//PAD_INPUT_9　	
		BUTTON_LIST_10,//PAD_INPUT_10
		BUTTON_LIST_MAX,
	};

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
	bool isHoldButton( BUTTON_LIST button ) const;
private:
	struct DATA {
		char x;
		char y;
		char button;
	};
private:
	DATA _data;
};
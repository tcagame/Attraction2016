#pragma once
#include "Task.h"
#include <string>
#include <array>

PTR( Drawer );

class Drawer : public Task {
public:
	static DrawerPtr getTask( );
	static std::string getTag( ) { return "DRAWER"; }
public:
	Drawer( const char* directory );
	virtual ~Drawer( );
public:
	struct Transform {
		double x;
		double y;
		double z;
		double dir_x;
		double dir_z;
		Transform( );
		Transform( double x_, double y_, double z_, double dir_x_, double dir_z_ );
	};
	struct Sprite {
		Transform transform;
		int res;
		double time;
		Sprite( );
		Sprite( Transform transform_, int res_, double time_ );
	};
	struct ID {
		int body;
		int body_anim;
	};
public:
	void initialize( );
	void update( );
	void load( int res, const char* filename );
	void set( const Sprite& sprite );
private:
	void drawSprite( );
private:
	static const int ID_NUM = 1000;
	static const int SPRITE_NUM = 10000;
	std::array< ID, ID_NUM > _id;
	std::array< Sprite, SPRITE_NUM > _sprite; 
	const char* _directory;
	int _sprite_idx;
};


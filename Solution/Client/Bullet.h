#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Bullet );
PTR( Enemy );

class Bullet {
public:
	enum TYPE {
		TYPE_SLASH,
		TYPE_SWORD,
		TYPE_STAB,
		TYPE_EXCALIBUR,
		TYPE_JAB,
		TYPE_IMPACT,
		TYPE_UPPER,
		TYPE_RUSH,
		TYPE_BEAM,
		TYPE_BUBBLE,
		TYPE_LAY,
		TYPE_STREAM,
		TYPE_FIRE,
		TYPE_RAPID_FIRE,
		TYPE_SHOT,
		TYPE_BULLET_RAIN,
		TYPE_FIRE_BALL,
		TYPE_MAX,
	};
public:
	Bullet( TYPE type );
	virtual ~Bullet( );
public:
	virtual bool update( ) = 0;
public:
	TYPE getType( ) const;
	Vector getPos( ) const;
	Vector getDir( ) const;
	Vector getHitPos( ) const;
protected:
	void attackEnemy( const Vector& pos, int power );
protected:
	Vector _pos;
	Vector _dir;
	Vector _hit_pos;
	int _effect_handle;
private:
	const TYPE _type;
};
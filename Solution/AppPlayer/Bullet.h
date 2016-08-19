#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Bullet );

class Bullet {
public:
	enum TYPE {
		SWORD,
		MISSILE,
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
protected:
	//void attackEnemy( const Vector& pos, int power );
protected:
	Vector _pos;
private:
	const TYPE _type;
};
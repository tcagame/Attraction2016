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
protected:
	void attackEnemy( const Vector& pos, int power );
private:
	const TYPE _type;
};
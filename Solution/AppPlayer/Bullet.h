#pragma once
#include "mathmatics.h"
#include "smart_ptr.h"

PTR( Bullet );

class Bullet {
public:
	enum TYPE {
		SWORD,
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
	bool attackEnemy( const Vector& pos, double power );
private:
	const TYPE _type;
};
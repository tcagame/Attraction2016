#pragma once
#include "smart_ptr.h"

PTR( Bullet );

class Bullet {
public:
	enum TYPE {
		SWORD,
	};
public:
	Bullet( TYPE type );
	virtual ~Bullet();
public:
	virtual bool update( ) = 0;
public:
	TYPE getType( ) const;
private:
	const TYPE _type;
};


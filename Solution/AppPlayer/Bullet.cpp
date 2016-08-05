#include "Bullet.h"
#include "mathmatics.h"
#include "Framework.h"

Bullet::Bullet( TYPE type )
: _type( type ) {
}


Bullet::~Bullet( ) {
}

Bullet::TYPE Bullet::getType( ) const {
	return _type;
}
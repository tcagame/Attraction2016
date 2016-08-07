#include "Weapon.h"
#include "Bullet.h"
#include "BulletSword.h"
#include "Framework.h"


Weapon::Weapon( ) {
}


Weapon::~Weapon( ) {
}

void Weapon::update( ) {
	std::list< BulletPtr >::iterator it = _bullet.begin( );
	while ( it != _bullet.end( ) ) {
		BulletPtr bullet = *it;
		if ( bullet->update( ) ) {
			it++;
		} else {
			it = _bullet.erase( it );
		}
	}
}

void Weapon::add( BulletPtr bullet ) {
	_bullet.push_back( bullet );
}

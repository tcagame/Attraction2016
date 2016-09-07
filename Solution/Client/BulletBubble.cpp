#include "BulletBubble.h"

BulletBubble::BulletBubble( const Vector& pos, const Vector& dir ) :
Bullet( Bullet::TYPE_BUBBLE ) {
	_pos = pos;
	_dir = dir;
}

BulletBubble::~BulletBubble( ) {
}

bool BulletBubble::update( ) {
	return false;
}
#include "Crystal.h"


Crystal::Crystal( ) {
}


Crystal::~Crystal( ) {
}

void Crystal::creat( Vector pos ) {
	_pos = pos;
	_expired = true;
}

Vector Crystal::getPos( ) {
	return _pos;
}

bool Crystal::isExpired( ) {
	return _expired;
}

void Crystal::pickup( ) {
	_expired = false;
}
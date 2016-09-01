#include "BigCrystal.h"


BigCrystal::BigCrystal( ) {
	_pos = Vector( 0, 0, 0 );
	_expired = false;
}


BigCrystal::~BigCrystal( ) {

}

Vector BigCrystal::getPos( ) {
	return _pos;
}

void BigCrystal::create( Vector pos ) { 
	_pos = pos;
	_expired = true;
}

bool BigCrystal::isExpired( ){
	return _expired;
}
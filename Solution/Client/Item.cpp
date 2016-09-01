#include "Item.h"


Item::Item( ) {
	_pos = Vector( 0, 0, 0 );
	_expired = true;
}


Item::~Item( ) {

}

Vector Item::getPos( ) {
	return _pos;
}

void Item::pickup( ) {
	_expired = false;
}

bool Item::isExpired( ) {
	return _expired;
}
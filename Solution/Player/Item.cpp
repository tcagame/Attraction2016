#include "Item.h"


Item::Item( ) {
	_pos = Vector( 0, 0, 0 );
}


Item::~Item( ) {

}

Vector Item::getPos( ) {
	return _pos;
}
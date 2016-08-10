#include "DeedBox.h"


DeedBox::DeedBox( Vector pos ) {
	_pos = pos;
}


DeedBox::~DeedBox( ) {

}

Vector DeedBox::getPos( ) const {
	return _pos;
}

Vector DeedBox::getDir( ) const {
	return _dir;
}
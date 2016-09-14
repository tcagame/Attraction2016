#include "Live.h"
#include "Framework.h"

LivePtr Live::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Live >( fw->getTask( Live::getTag( ) ) );
}

Live::Live( ) {
}


Live::~Live( ) {
}

void Live::initialize( ) {

}

void Live::finalize( ) {

}

void Live::update( ) {

}
#include "Live.h"
#include "Framework.h"
#include "Viewer.h"

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
	ViewerPtr viewer = Viewer::getTask( );
	viewer->drawTitle( );
}
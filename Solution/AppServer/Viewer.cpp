#include "Viewer.h"
#include "AppServer.h"

#include "Drawer.h"
#include "Framework.h"


ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( Viewer::getTag( ) ) );
}


void Viewer::initialize( ) {
	
}

Viewer::Viewer( ) {
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {

}

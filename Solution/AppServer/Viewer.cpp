#include "Viewer.h"
#include "TableDrawer.h"
#include "Drawer.h"
#include "Framework.h"

ViewerPtr Viewer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Viewer >( fw->getTask( Viewer::getTag( ) ) );
}


void Viewer::initialize( ) {
	_td_status = TableDrawerPtr( new TableDrawer );
	_td_status->setPos( Vector( 10, 10, 0 ) );
	_td_status->setTitle( "status" );
	_td_status->addCal( 50 );
	_td_status->addRow( 200 );
	_td_status->addCal( 100 );
	_td_status->addRow( 200 );
	_td_status->addCal( 300 );
	_td_status->addRow( 50 );
	_td_status->setCell( TableDrawer::Cell( 2, 3, "‰Á£" ) );

}

Viewer::Viewer( ) {
}


Viewer::~Viewer( ) {
}

void Viewer::update( ) {
	_td_status->draw( );
}
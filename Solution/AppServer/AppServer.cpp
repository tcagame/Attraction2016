#include "AppServer.h"
#include "Framework.h"


AppServerPtr AppServer::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< AppServer >( fw->getTask( AppServer::getTag( ) ) );
}

AppServer::AppServer( ) {

}


AppServer::~AppServer( ) {

}

void AppServer::update( ) {

}
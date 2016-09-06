#include "Crystal.h"
#include "App.h"
#include "Cohort.h"


Crystal::Crystal( ) {
	_expired = false;
}


Crystal::~Crystal( ) {
}

void Crystal::create( Vector pos ) {
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
	AppPtr App = App::getTask( );
	CohortPtr cohort = App->getCohort( );
	cohort->init( );
	_expired = false;
}
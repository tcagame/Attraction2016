#include "Crystal.h"
#include "App.h"
#include "Field.h"
#include "Cohort.h"


Crystal::Crystal( ) {
	_expired = false;
}


Crystal::~Crystal( ) {
}

void Crystal::reset( ) {
	_expired = false;
	AppPtr App = App::getTask( );
	FieldPtr field = App->getField( );
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

void Crystal::create( Vector pos ) {
	_pos = pos;
	_expired = true;
	_float_speed = 0.008;

	AppPtr App = App::getTask( );
	FieldPtr field = App->getField( );
	field->setTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
}

Vector Crystal::getPos( ) {
	return _pos;
}

void Crystal::update( ) {
	_pos.z += _float_speed;
	if ( _pos.z >= 0.3 || _pos.z <= 0.0 ) {
		_float_speed *= -1; 
	}
}

bool Crystal::isExpired( ) {
	return _expired;
}

void Crystal::pickup( ) {
	AppPtr App = App::getTask( );
	CohortPtr cohort = App->getCohort( );
	cohort->init( );
	FieldPtr field = App->getField( );
	field->delTarget( ( int )_pos.x, ( int )_pos.y, getThis( ) );
	_expired = false;
}
#include "Field.h"
#include "Ground.h"
#include "App.h"

Field::Field( ) {
	initialize( );
}


Field::~Field( ) {

}

void Field::reset( ) {
	initialize( );
}

void Field::initialize(  ) {
	for ( int i = 0; i < MAX_MAP_CHIP_NUM; i++ ) {
		_target_board[ i ].reset( );
	}
}

void Field::delTarget( int x, int y, ObjectPtr object ) {
	int idx = getIndexTargetBoard( x, y );
	ObjectPtr target = _target_board[ idx ].lock( );
	if ( target == object ) {
		_target_board[ idx ].reset( );
	}
}


bool Field::setTarget(int x, int y, ObjectPtr object) {
	int idx = getIndexTargetBoard( x, y );
	ObjectPtr target = _target_board[ idx ].lock();
	if ( !target ) {
		_target_board[ idx ] = object;
		return true;
	}
	return false;
	//target = _target_board[ idx ].lock( );//ƒeƒXƒg
}

ObjectPtr Field::getTarget( int x, int y ) {
	int idx = getIndexTargetBoard( x, y );
	return _target_board[ idx ].lock( );
}

int Field::getIndexTargetBoard( int x, int y ) {
	int ret = 0;
	int map_x = x; 
	int map_y = y;
	if ( map_x < 0 ) {
		map_x = 0;
	}
	if ( map_y < 0 ) {
		map_y = 0;
	}
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	int map_width = ground->getWidth( ) * 7;
	int map_height = ground->getHeight( ) * 7;
	ret = map_x + map_y * map_width ;
	return ret;
}
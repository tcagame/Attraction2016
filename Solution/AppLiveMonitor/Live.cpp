#include "Live.h"
#include "Framework.h"
#include "Viewer.h"
#include "LiveScene.h"
#include "LiveScenePlayer.h"
#include "LiveSceneTitle.h"

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

	//ViewerPtr viewer = Viewer::getTask( );
	//viewer->drawTitle( );
	if ( _scene ) {
		bool finished = _scene->update();
		if ( !finished ) {
			return;
		}
	}

	//éüÇÃÉVÅ[ÉìÇ÷
	static int toggle = 0;
	//toggle = 1 - toggle;
	if ( toggle ) {
		_scene = LiveScenePtr( new LiveSceneTitle( ) );
	} else {
		_scene = LiveScenePtr( new LiveScenePlayer( ) );
	}
}
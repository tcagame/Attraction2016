#include "Live.h"
#include "Framework.h"
#include "Viewer.h"
#include "LiveScene.h"
#include "LiveScenePlayer.h"
#include "LiveSceneTitle.h"

const int FADE_OUT_COUNT = 10;
const int FADE_IN_COUNT = 5;

LivePtr Live::getTask( ) {
	FrameworkPtr fw = Framework::getInstance( );
	return std::dynamic_pointer_cast< Live >( fw->getTask( Live::getTag( ) ) );
}

Live::Live( ) {
}


Live::~Live( ) {
}

void Live::initialize( ) {
	_scene = LiveScenePtr( new LiveSceneTitle( ) );
	_fade_count = FADE_OUT_COUNT;
	_fade_out = true;
}

void Live::finalize( ) {

}

void Live::update( ) {
	ViewerPtr viewer = Viewer::getTask( );
	_fade_count++;
	if ( _fade_out ) {
		if ( _fade_count > FADE_OUT_COUNT ) {
			viewer->setFade( true, 1.0 ); 
		} else {
			viewer->setFade( true, ( double )_fade_count / FADE_OUT_COUNT );
		}
	} else {
		if ( _fade_count > FADE_IN_COUNT ) {
			viewer->setFade( false, 1.0 ); 
		} else {
			viewer->setFade( false, ( double )_fade_count / FADE_IN_COUNT ); 
		}
	}

	bool finished = _scene->update();
	if ( finished && !_fade_out ) {
		// フェードアウト
		_fade_out = true;
		_fade_count = 0;
	}

	// フェードアウトしていない
	if ( !_fade_out || _fade_count <= FADE_OUT_COUNT ) {
		return;
	}

	//次のシーンへ
	static int toggle = 0;
	toggle = 1 - toggle;
	if ( toggle ) {
		_scene = LiveScenePtr( new LiveSceneTitle( ) );
	} else {
		_scene = LiveScenePtr( new LiveScenePlayer( ) );
	}

	// フェードイン
	_fade_out = false;
	_fade_count = 0;
}

/*#include "ViewerPlayer.h"

ViewerPlayer::ViewerPlayer( ) {
	init( );
	createModel( );
}

ViewerPlayer::~ViewerPlayer( ) {
}

void ViewerPlayer::init( ) {
	for ( int i = 0; i < MOTION_MAX; i++ ) {
		_player.id[ i ].body = -1;
	}
}

void ViewerPlayer::drawPlayer( Vector pos, Vector dir, ViewerPlayer::MOTION motion ) {
	int id = _player.id[ motion ].body;
	int anim = _player.id[ motion ].body_anim;
	//double time = player->getTime( );
	double dir_x = dir.x;
	double dir_z = dir.z;
	if ( ( float )dir_x == 0 ) {
		dir_x = 0.001;
	}

	// 座標変換
	MATRIX matrix = MGetIdent( );
	matrix = MMult( matrix, MGetRotVec2( VGet( 0, 0, -1 ), VGet( ( float )dir_x, 0, ( float )dir_z ) ) );
	matrix = MMult( matrix, MGetScale( VGet( 0.008f, 0.008f, 0.008f ) ) );
	matrix = MMult( matrix, MGetTranslate( VGet( ( float )pos.x, ( float )pos.y, ( float )pos.z ) ) );
	MV1SetMatrix( id, matrix );

	// アニメーション時間設定
	MV1SetAttachAnimTime( id, anim, ( float )time );

	// ３Ｄモデルの描画
	MV1DrawModel( id ) ;
}

void ViewerPlayer::createModel( ) {
	create( MOTION_DAMAGE, "resource/knight/player_knight_damage.mv1" );
	create( MOTION_DEAD  , "resource/knight/player_knight_dead.mv1");
	create( MOTION_JUMP  , "resource/knight/player_knight_jump.mv1");
	create( MOTION_ATTACK, "resource/knight/player_knight_attack.mv1" );
	create( MOTION_USE   , "resource/knight/player_knight_use.mv1");
	create( MOTION_WAIT  , "resource/knight/player_knight_wait.mv1" );
	create( MOTION_WALK  , "resource/knight/player_knight_walk.mv1" );
}

void ViewerPlayer::create( ViewerPlayer::MOTION motion, const char * filename ) {
	int& id = _player.id[ motion ].body;
	id = MV1LoadModel( filename );
	if ( id < 0 ) {
		return;
	}
	int num = MV1GetMaterialNum( id ) ;
	for ( int i = 0; i < num; i++ ) {
		MV1SetMaterialEmiColor( id, i, GetColorF( 1.0f, 1.0f, 1.0f, 1.0f ) );
	}
	int& anim = _player.id[ motion ].body_anim;
	anim = MV1AttachAnim( id, 0, -1, FALSE );
}

*/
#pragma once
#include "Behavior.h"
#include "smart_ptr.h"


PTR( PlayerBehavior );
PTR( Camera );

//�R���g���[���[�œ�������
class PlayerBehavior : public Behavior {
public:
	PlayerBehavior( CameraConstPtr camera );
	virtual ~PlayerBehavior( );
public:
	void update( );
	void pickupDeedBox( );
	void pickupItem( );
	void pickupCrystal( );
protected:
	virtual void otherAction( ) = 0;//�U���Ȃǂ̊O�̍s��
protected:
	CameraConstPtr _camera;
};
#pragma once
#include "Behavior.h"
#include "smart_ptr.h"


PTR( PlayerBehavior );
PTR( Camera );

//�R���g���[���[�œ�������
class PlayerBehavior : public Behavior {
public:
	static const int LENGHT = 2;
public:
	PlayerBehavior( CameraConstPtr camera );
	virtual ~PlayerBehavior( );
public:
	void update( );
	void pickupDeedBox( );
protected:
	virtual void otherAction( ) = 0;//�U���Ȃǂ̊O�̍s��
protected:
	CameraConstPtr _camera;
};
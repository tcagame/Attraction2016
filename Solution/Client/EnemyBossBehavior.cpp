#include "EnemyBossBehavior.h"
#include "Character.h"
#include "Animation.h"
#include "Crystals.h"
#include "App.h"
#include "Player.h"

const double MOTION_SPEED = 1;
const double BOSS_DAMAGE_HP = 100;
const double MAX_BOSS_FLIGHT_ALTITUDE = 5;
const double ATTACK_TIME[ ] = {
	27.0,
	10.0,
	25.0,
	23.0
};

const Animation::MOTION BOSS_ATTACK_MOTION[ ] = {
	Animation::MOTION::MOTION_BOSS_ATTACK_CLEAVE,	
	Animation::MOTION::MOTION_BOSS_ATTACK_BITE,	
	Animation::MOTION::MOTION_BOSS_ATTACK_FIRE,	
};

const int BOSS_ATTACK_POWER[ ] = {
	40,
	30,
	20,
	10,
};

EnemyBossBehavior::EnemyBossBehavior() {
	_attack_range[ BOSS_ATTACK_PATTERN_CLEAVE ] = 1.0;
	_attack_range[ BOSS_ATTACK_PATTERN_BITE ] = 2.0;
	_attack_range[ BOSS_ATTACK_PATTERN_FIRE ] = 3.0;
	_attack_pattern = BOSS_ATTACK_PATTERN_MAX;
	_on_damage = false;
	_has_entry = false;
	_boss_state = BOSS_STATE_WAIT;
	_boss_damage_hp = BOSS_DAMAGE_HP;
}

EnemyBossBehavior::~EnemyBossBehavior() {
}

void EnemyBossBehavior::update( ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}
	if ( _boss_state == BOSS_STATE_FLY ) {
		Vector move_lenght = Vector( 0, 0, 0.05 );
		_parent->move( move_lenght );
	}
	if ( _boss_state == BOSS_STATE_DESCENT ) {
		Vector move_lenght = Vector( 0, 0, -0.05 );
		_parent->move( move_lenght );
	}
	if ( _boss_state == BOSS_STATE_DESCENT && _parent->getPos( ).z <= 0 ) {
		Vector pos = Vector( 0, 0.0001, 0 );
		_parent->move( pos );
	}
	switchStatus( );
	_before_state = _boss_state;
}


void EnemyBossBehavior::switchStatus( ) {
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	Vector target_pos = player->getPos( );
	Vector stance = target_pos - _parent->getPos( );
	Vector pos = _parent->getPos( );
	double range = stance.getLength();
	AppPtr app = App::getTask();
	CrystalsPtr crystals = app->getCrystals();
	switch ( _boss_state ) {
	case BOSS_STATE_WAIT:
		for ( int i = 0; i < BOSS_ATTACK_PATTERN_MAX; i++ ) {
			if ( range <= _attack_range[i] && _before_state != BOSS_STATE_ATTACK ) {
				_boss_state = BOSS_STATE_ATTACK;
				_attack_pattern = i;
				break;
			}
		}
		if ( _boss_damage_hp >= _parent->getStatus( ).hp ) {
			_boss_damage_hp -= BOSS_DAMAGE_HP;
			_boss_state = BOSS_STATE_DAMAGE;
		}
		if ( crystals->isGetBigCrystal( ) && !_has_entry ) {
			_boss_state = BOSS_STATE_ENTRY;
			Vector player_pos = player->getPos( );
			Vector pos = _parent->getPos( );
			_parent->move( ( player_pos - pos ).normalize( ) );
		}
		break;
	case BOSS_STATE_ENTRY:
		if (  _animation->isEndAnimation( ) ) {
			_boss_state = BOSS_STATE_WAIT;
			_has_entry = true;
		}
		break;
	case BOSS_STATE_ATTACK:
		if ( _animation->isEndAnimation( ) ) {
			_boss_state = BOSS_STATE_WAIT;
		}
		break;
	case BOSS_STATE_DAMAGE:
		if ( _animation->isEndAnimation( ) ) {
			_boss_state = BOSS_STATE_FLY;
		}
		break;
	case BOSS_STATE_FLY:
		if ( pos.z >= MAX_BOSS_FLIGHT_ALTITUDE ) {
			_boss_state = BOSS_STATE_BOMBING;
		}
		break;
	case BOSS_STATE_BOMBING:
		if ( _animation->isEndAnimation( ) ) {
			_boss_state = BOSS_STATE_DESCENT;
		}
		break;
	case BOSS_STATE_DESCENT:
		if ( pos.z <= 0 ) {
			_boss_state = BOSS_STATE_WAIT;
		}
		break;
	default:
		break;
	}
	if ( _parent->getStatus( ).hp <= 0 ) {
		_boss_state = BOSS_STATE_DEAD;
		app->setState( App::STATE_CLEAR );
	}
	
}

void EnemyBossBehavior::animationUpdate( ) {
	
	if ( _animation->getMotion( ) == Animation::MOTION_BOSS_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
		}
		return;
	}
	if ( _boss_state == BOSS_STATE_FLY ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_FLY ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_FLY, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_DESCENT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_DESCENT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_DESCENT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_BOMBING ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_ATTACK_BOMBING ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_ATTACK_BOMBING, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_ENTRY ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_ENTRY ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_ENTRY, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_WAIT ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_WAIT ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_WAIT, MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_ATTACK && _has_entry ) {
		if( _animation->getMotion( ) != BOSS_ATTACK_MOTION[ _attack_pattern ] ) {
			_animation = AnimationPtr( new Animation( BOSS_ATTACK_MOTION[ _attack_pattern ], MOTION_SPEED ) );
		} else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
			if ( _animation->getAnimTime( ) == ATTACK_TIME[ _attack_pattern ] ) {
				onAttack( _attack_pattern );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_DAMAGE ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_DAMAGE ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_DAMAGE, MOTION_SPEED ) );
		}
		else {
			if ( _animation->isEndAnimation( ) ) {
				_animation->setAnimationTime( 0 );
			}
		}
	}
	if ( _boss_state == BOSS_STATE_DEAD ) {
		if ( _animation->getMotion( ) != Animation::MOTION_BOSS_DEAD ) {
			_animation = AnimationPtr( new Animation( Animation::MOTION_BOSS_DEAD, MOTION_SPEED ) );
		}
	}
}

void EnemyBossBehavior::onAttack( int attack_pattern ) {
	AppPtr app = App::getTask( );
	PlayerPtr player = app->getPlayer( );
	int power = _parent->getStatus( ).power;
	power += BOSS_ATTACK_POWER[ attack_pattern ];
	player->damage( power );
}
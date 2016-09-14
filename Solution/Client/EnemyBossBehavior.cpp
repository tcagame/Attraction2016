#include "EnemyBossBehavior.h"
#include "Character.h"
#include "Effect.h"
#include "Animation.h"
#include "Crystals.h"
#include "Sound.h"
#include "App.h"
#include "Player.h"
#include "Sound.h"

const double MOTION_SPEED = 1;
const double BOSS_DAMAGE_HP = 700;
const double MAX_BOSS_FLIGHT_ALTITUDE = 5;
const double EFFECT_SCALE = 0.5;
const double BOSS_MAX_FLY_TIME = 120;
const int BOSS_CRICLE_TIME = 60;
const int BOSS_METOR_TIME = 90;
const int BOSS_EXPLOSION_TIME = 120;

const double ATTACK_TIME[ ] = {
	27.0,
	10.0,
	140.0,
	70.0
};

const Effect::EFFECT BOSS_EFFCT[ ] = {
	Effect::EFFECT_BOSS_ATTACK_FIRE, 
	Effect::EFFECT_BOSS_ATTACK_BOMBING,
	Effect::EFFECT_BOSS_HIT_CIRCLE, 
	Effect::EFFECT_BOSS_HIT_EXPLOSION,
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
	1000,
};

EnemyBossBehavior::EnemyBossBehavior() {
	_attack_range[ BOSS_ATTACK_PATTERN_CLEAVE ] = 3.0;
	_attack_range[ BOSS_ATTACK_PATTERN_BITE ] = 5.0;
	_attack_range[ BOSS_ATTACK_PATTERN_FIRE ] = 7.0;
	_attack_pattern = BOSS_ATTACK_PATTERN_MAX;
	_has_entry = false;
	_boss_fly_time = 0;
	_boss_state = BOSS_STATE_WAIT;
	_boss_damage_hp = BOSS_DAMAGE_HP;
}

EnemyBossBehavior::~EnemyBossBehavior() {
}

void EnemyBossBehavior::update( ) {
	AppPtr app = App::getTask( );
	SoundPtr sound = Sound::getTask( );
	PlayerPtr player = app->getPlayerMine( );
	if ( player->isExpired( ) ) {
		_target = player;
	} else {
		_target.reset( );
	}

	if ( _boss_fly_time >= BOSS_CRICLE_TIME && _boss_fly_time < BOSS_METOR_TIME ) {
		Effect effect;
		int boss_hit_cricle_handle = effect.setEffect( Effect::EFFECT_BOSS_HIT_CIRCLE );
		effect.drawEffect( boss_hit_cricle_handle, Vector( EFFECT_SCALE * 3, EFFECT_SCALE * 3, EFFECT_SCALE ), player->getPos( ), _parent->getDir( ) );
	}
	if ( _boss_fly_time >= BOSS_METOR_TIME && _boss_fly_time < BOSS_EXPLOSION_TIME ) {
		Effect effect;
		Vector player_pos = player->getPos( );
		sound->playSE( Sound::SE_BOSS_BOMBING );
		int boss_attack_bombing_handle = effect.setEffect( Effect::EFFECT_BOSS_ATTACK_BOMBING );
		
		effect.drawEffect( boss_attack_bombing_handle, Vector( EFFECT_SCALE * 3, EFFECT_SCALE * 3, EFFECT_SCALE * 3 ), player_pos, _parent->getDir( ) );
	}
	if ( _boss_fly_time == BOSS_EXPLOSION_TIME ) {
		sound->playSE( Sound::SE_BOSS_BOMBING );
		Effect effect;
		//int boss_attack_explosion_handle = effect.setEffect( Effect::EFFECT_BOSS_ATTACK_BOMBING );
		//effect.drawEffect( boss_attack_explosion_handle, Vector( EFFECT_SCALE * 3, EFFECT_SCALE * 3, EFFECT_SCALE * 3 ), player->getPos( ), _parent->getDir( ) );
		onAttack( 4 );
	}
	switchStatus( );
	_before_state = _boss_state;
}


void EnemyBossBehavior::switchStatus( ) {
	SoundPtr sound = Sound::getTask( );
	AppPtr app = App::getTask();
	CrystalsPtr crystals = app->getCrystals();
	if ( !crystals ) {
		return;
	}
	if ( _target.expired( ) ) {
		return;
	}
	PlayerPtr player = _target.lock( );
	_target_pos = player->getPos( );
	Vector stance = _target_pos - _parent->getPos( );
	Vector pos = _parent->getPos( );
	double range = stance.getLength();
	int hp = _parent->getStatus( ).hp;
	switch ( _boss_state ) {
	case BOSS_STATE_WAIT:
		for ( int i = 0; i < BOSS_ATTACK_PATTERN_MAX; i++ ) {
			if ( range <= _attack_range[ i ] && _before_state != BOSS_STATE_ATTACK ) {
				_boss_state = BOSS_STATE_ATTACK;
				_attack_pattern = i;
				sound->playSE( Sound::SE_BOSS_ATTACK_1 );
				break;
			}
		}
		
		if ( _boss_damage_hp >= hp ) {
			_boss_damage_hp -= BOSS_DAMAGE_HP;
			_boss_state = BOSS_STATE_DAMAGE;
			sound->playSE( Sound::SE_BOSS_DAMAGE );

		}
		if ( crystals->isGetBigCrystal( ) && !_has_entry ) {
			_boss_state = BOSS_STATE_ENTRY;
		
			Vector pos = _parent->getPos( );
			_parent->move( ( Vector( 0, -1, 0 ) ) );
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
			sound->playSE( Sound::SE_BOSS_WING );

		}
		break;
	case BOSS_STATE_FLY:
		if ( _animation->isEndAnimation( ) ) {
			if ( _boss_fly_time < BOSS_MAX_FLY_TIME ) {
				_boss_state = BOSS_STATE_FLY;
				_boss_fly_time++;
				_animation->setAnimationTime( _animation->getEndAnimTime( ) );
			} else {
				_boss_state = BOSS_STATE_DESCENT;
				sound->playSE( Sound::SE_BOSS_WING );
			}
		} 
		break;
	case BOSS_STATE_DESCENT:
		if ( _animation->isEndAnimation( ) ) {
			_boss_state = BOSS_STATE_WAIT;
			sound->playSE( Sound::SE_BOSS_WING );

		}
		break;
	default:
		break;
	}
	if ( _parent->getStatus( ).hp <= 0 ) {
		_boss_state = BOSS_STATE_DEAD;
	}
	
}

void EnemyBossBehavior::animationUpdate( ) {
	
	if ( _animation->getMotion( ) == Animation::MOTION_BOSS_DEAD ) {
		if ( _animation->isEndAnimation( ) ) {
			_parent->dead( );
			AppPtr app = App::getTask( );
			app->setState( App::STATE_CLEAR );
			SoundPtr sound = Sound::getTask( );
			sound->playSE( Sound::SE_GAME_CLEAR );
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
	SoundPtr sound = Sound::getTask( );
	PlayerPtr player = app->getPlayerMine( );
	int power = _parent->getStatus( ).power;
	power += BOSS_ATTACK_POWER[ attack_pattern ];
	player->damage( power );
	Vector pos = _parent->getPos( );
	Effect effect;
	if ( _attack_pattern == BOSS_ATTACK_PATTERN_FIRE ) {
		sound->playSE( Sound::SE_BOSS_ATTACK_3 );
		int effect_handle = effect.setEffect( Effect::EFFECT_BOSS_ATTACK_FIRE );
		Vector effect_dir = ( pos - _target_pos ).normalize( );
		effect.drawEffect( effect_handle, Vector( EFFECT_SCALE, EFFECT_SCALE, EFFECT_SCALE ), pos + ( ( _target_pos - pos ).normalize( ) * 2 ), effect_dir );
	}
	
}
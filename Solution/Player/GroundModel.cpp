#include "GroundModel.h"
#include "App.h"
#include "Ground.h"
#include "Model.h"
#include "MapType.h"
#include "Cohort.h"

GroundModel::ModelData::ModelData( ) :
polygon_num( 0 ) {

}

GroundModel::GroundModel() {
	_map_floor01_filepath = "../Resource/map_model/floor01.mdl";
	_map_path01_filepath = "../Resource/map_model/path01.mdl";
	_map_path02_filepath = "../Resource/map_model/path02.mdl";
	_map_path03_filepath = "../Resource/map_model/path03.mdl";
}


GroundModel::~GroundModel()
{
}

void GroundModel::loadModelData( ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );
	CohortPtr Cohort = app->getCohort( );
	int width = ground->getWidth( );
	int height = ground->getHeight( );

	for ( int i = 0; i < width; i++ ) {
		for ( int j = 0; j < height; j++ ) {
			ModelPtr model = ModelPtr( new Model( ) ); 
			int idx = ground->getIdx( i, j );
			int type = ground->getGroundData( idx );
			std::string enemy_filepath;
			
			switch( type ) {
			case GROUND_TYPE_FLOOR_01:
				//ここでエネミーデータ読み込みをする
				enemy_filepath = "../Resource/enemy/floor01.ene";
				Cohort->loadBlockEnemyData( enemy_filepath );
				model->load( _map_floor01_filepath );
				loadModelPos( idx, i, j, model );
				break;
			case GROUND_TYPE_PATH_01:
				enemy_filepath = "../Resource/enemy/path01.ene";
				Cohort->loadBlockEnemyData( enemy_filepath );
				model->load( _map_path01_filepath );
				loadModelPos( idx, i, j, model );
				break;
			case GROUND_TYPE_PATH_02:
				enemy_filepath = "../Resource/enemy/path02.ene";
				Cohort->loadBlockEnemyData( enemy_filepath );
				model->load( _map_path02_filepath );
				loadModelPos( idx, i, j, model );
				break;
			case GROUND_TYPE_PATH_03:
				enemy_filepath = "../Resource/enemy/path03.ene";
				Cohort->loadBlockEnemyData( enemy_filepath );
				model->load( _map_path03_filepath );
				loadModelPos( idx, i, j, model );
				break;
			default:
				break;
			}
		}
	}
}

void GroundModel::loadModelPos( int idx, int x, int y, ModelPtr model ) {
	int polygon_num = model->getPolygonNum( );
	_model_data[ idx ].polygon_num = polygon_num;
	model->translate( Vector( x * Ground::CHIP_WIDTH, y * Ground::CHIP_HEIGHT ) );
	int num = 0;
	for ( int i = 0; i < polygon_num * 3; i++ ) {
		Vector pos = model->getPoint( i );
		_model_data[ idx ].pos[ num ] = pos;
		num++;
	}
}

bool GroundModel::isCollisionGround( Vector pos ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	
	double size = ( ( Ground::CHIP_WIDTH + 5) / 2.0f );
	int x = (int)( abs( pos.x ) / size );
	int y = (int)( abs( pos.y ) / size );
	if ( x < 0 ) {
		x = 0;
	}
	if ( y < 0 ) {
		y = 0;
	}
	double chip_pos_x = pos.x - ( size * x );
	double chip_pos_y = pos.y - ( size * y );


	int model_idx = ground->getIdx( x, y );
	
	Vector pos_a = Vector( pos.x, pos.y, 100 );
	Vector pos_b = Vector( pos.x, pos.y, -100 );
	bool ret = false;
	for ( int i = 0; i < 2; i++ ) {
		
		int add_y = 0;
		if ( chip_pos_y > 0 ) {
			add_y = 1;
		} else if ( chip_pos_y < 0 ) {
			add_y = -1;
		}
		if ( chip_pos_x > 2.5 ) {
			x += 1;
		}
		if ( chip_pos_x < 2.5 && chip_pos_x > -2.5 ) {
			add_y *= i;
		}
		if ( chip_pos_x < -2.5 ) {
			x -= 1;
		}
		y += add_y;
		if ( x < 0 ) {
			x = 0;
		}
		if ( y < 0 ) {
			y = 0;
		}
		ret = isCollisionModel( model_idx, pos_a, pos_b );
		model_idx = ground->getIdx( x, y );
		if ( ret ) {
			return ret;
		}
	}
	return ret;
}


bool GroundModel::isCollisionModel( int model_idx, Vector pos_a, Vector pos_b ) {
	int polygon_idx = 0;
	for ( int i = 0; i < _model_data[ model_idx ].polygon_num; i++ ) {
		polygon_idx = i * 3;
		Vector plane_point_a = _model_data[ model_idx ].pos[ polygon_idx ];
		Vector plane_point_b = _model_data[ model_idx ].pos[ polygon_idx + 1 ];
		Vector plane_point_c = _model_data[ model_idx ].pos[ polygon_idx + 2 ];

		Vector normal_plane = ( plane_point_b - plane_point_a ).cross( plane_point_c - plane_point_b );
		normal_plane = normal_plane.normalize( );

		Vector plane_to_pos_a = plane_point_a - pos_a;
		Vector plane_to_pos_b = plane_point_a - pos_b;
		
		double dot_a = normal_plane.dot( plane_to_pos_a );
		double dot_b = normal_plane.dot( plane_to_pos_b );
		
		
		if( dot_a == 0 && dot_b == 0 ) {
			continue;
		} 
		if ( ( dot_a <= 0 || dot_b >= 0 ) &&
			 ( dot_a >= 0 || dot_b <= 0 ) ) {
			continue;

		} 

		Vector pos_a_to_b = pos_b - pos_a;
		double ratio =  abs( dot_a ) / ( abs( dot_a ) + abs( dot_b ) );
		Vector cross_pos = pos_a + ( pos_a_to_b * ratio );
		

		Vector ab_cross_bcroos_pos = ( plane_point_b - plane_point_a ).cross( cross_pos - plane_point_b );
		Vector ca_cross_acroos_pos = ( plane_point_a - plane_point_c ).cross( cross_pos - plane_point_a );
		Vector bc_cross_ccroos_pos = ( plane_point_c - plane_point_b ).cross( cross_pos - plane_point_c );
	
		if ( ab_cross_bcroos_pos != normal_plane ||
			 ca_cross_acroos_pos != normal_plane || 
			 bc_cross_ccroos_pos != normal_plane ) {
			continue;
		}
		return true;
	}
	return false;
}

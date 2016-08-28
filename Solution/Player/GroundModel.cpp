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
	_model_max_idx  = 0;
}

GroundModel::~GroundModel()
{
}

void GroundModel::loadModelData( int x, int y, std::string filename ) {
	ModelPtr model = ModelPtr( new Model( ) );
	model->load( filename );
	loadModelPos( x, y, model );
}

void GroundModel::loadModelPos( int x, int y, ModelPtr model ) {
	int polygon_num = model->getPolygonNum( );
	_model_data[ _model_max_idx ].polygon_num = polygon_num;
	model->translate( Vector( x * Ground::CHIP_WIDTH, y * Ground::CHIP_HEIGHT ) );
	int num = 0;
	double max_x = 0;
	double max_y = 0;
	double min_x = 10000;
	double min_y = 10000;
	for ( int i = 0; i < polygon_num * 3; i++ ) {
		Vector pos = model->getPoint( i );
		_model_data[ _model_max_idx ].pos[ num ] = pos;
		if ( pos.x > max_x ) {
			max_x = pos.x;
		}
		if ( pos.y > max_y ) {
			max_y = pos.y;
		}
		if ( pos.x < min_x ) {
			min_x = pos.x;
		}
		if ( pos.y < min_y ) {
			min_y = pos.y;
		}
		num++;
	}
	_model_data[ _model_max_idx ].max_x = max_x;
	_model_data[ _model_max_idx ].max_y = max_y;
	_model_data[ _model_max_idx ].min_x = min_x;
	_model_data[ _model_max_idx ].min_y = min_y;

	_model_max_idx ++;
}

bool GroundModel::isCollisionGround( Vector pos ) {
	AppPtr app = App::getTask( );
	GroundPtr ground = app->getGround( );

	bool ret = false;
	for ( int i = 0; i < _model_max_idx; i++ ) {
		if ( _model_data[ i ].max_x < pos.x ) {
			continue;
		}  
		if ( _model_data[ i ].max_y < pos.y ) {
			continue;
		}  
		if ( _model_data[ i ].min_x > pos.x ) {
			continue;
		}  
		if ( _model_data[ i ].min_y > pos.y ) {
			continue;
		}  
		Vector pos_a = pos;
		Vector pos_b = pos;
		pos_a.z = 100;
		pos_b.z = -100;
		ret = isCollisionModel( i, pos_a, pos_b );
		if ( ret ) {
			return true;
		}
	}
	return false;
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

#pragma once
#include "NumberSystem.h"

enum class StateCode {
	
	
	NO_DATA = 0,
		
	// Warning area	
	WARNING = 1,
	
	// ETC

	CONNECTION_LOST = 2 ,
	CONNECTION_HALT = 3 ,

	// Error area
	CONNECTION_ERR = 4 ,

	// Fatal area

	FATAL = -1,
	FATAL_WITH_ERROR = -2

};


typedef struct Pose {

};

typedef struct PoseWithCovariance {
	Covariance covariance;
};

typedef struct TwistWithCovariance {

	Covariance covariance;
};

typedef struct Odometry {
	char* child_frmae_id;

	PoseWithCovariance pose;
	TwistWithCovariance twist;

};

typedef struct Movement {

	Point3d velocity;
	Point3d acceleration;
};

typedef struct CarState {
    int speed;
    int direction;
} CarState;

typedef struct State {
    CarState state;
};

typedef struct Car {
    int id;
    char name[64];
    State state;
};


// 제어국의 현재 상황
typedef struct ControlTowerState 
{
	size_t car_count;
	Car cars[]; // 현재 제어하고 있는 차량의 목록


};


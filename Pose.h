#pragma once


typedef struct Position {
	double x;
	double y;
	double z;
	double w;
};

typedef struct Orientation {

	double x;
	double y;
	double z;
	double w;
};
typedef struct Pose {
	Position position;
	


};

typedef struct PoseWithCovariance {

};

typedef struct TwistWithCovariance {

};

typedef struct Odometry {
	char* child_frmae_id;

	PoseWithCovariance pose;
	TwistWithCovariance twist;

};
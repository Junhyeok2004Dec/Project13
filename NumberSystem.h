#pragma once

typedef struct Point3d {
	double x;
	double y;
	double z;
};
// x,y,z,r,p,y 6-dof
typedef struct Covariance {
	double covariance[36];
};

// w + xi + yj + zk (H)
typedef struct Quaternion {
	double x;
	double y;
	double z;
	double w;

};



// a+bi (C)
typedef struct Complex {
	double a;
	double b;
};
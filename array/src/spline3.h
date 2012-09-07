#include "ap.h"

void spline3buildtable(int n,
     int diffn,
     ap::real_1d_array x,
     ap::real_1d_array y,
     double boundl,
     double boundr,
     ap::real_2d_array& ctbl);
double spline3interpolate(int n, const ap::real_2d_array& c, double x);

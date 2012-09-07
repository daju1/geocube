

#include "vdouble.h"


#define WF_HAAR							0
#define WF_DAUBECHIES					1
#define WF_SYMLETS						2
#define WF_COIFLETS						3
#define WF_BIORTOGONAL					4
#define WF_MY_BIORTOGONAL				5
#define WF_BIORTOGONAL_NONSTANDART		6
#define WF_DISCRETE_MEYER				7


void WaveletFilters(int wf, // флаг типа вейвлетов
	int order, // порядоак вейвлета
	int orderBiorthogonalDecomposition,
	int& nd1, int& nd2, vdouble& d_h,
	int& ngd1, int& ngd2, vdouble& d_g,
	int& nr1, int& nr2, vdouble& r_h, 
	int& ngr1, int& ngr2,vdouble& r_g,
	int& n00, double& m00);

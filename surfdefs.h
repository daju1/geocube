// surfdefs.h

#define OG_DOUBLE_PRECISION 1

#define FIRST_FONT_LIST_BITMAPS  0
#define FIRST_FONT_LIST_OUTLINES 300

#define FIRST_HARD_LIST 600
#define N_HARD_LISTS 4

// for Broken planes
#if 0
#define PLANE_MEMBERS_VECTOR		vector
#define PLANE_MEMBERS_VECTOR_SIZE	size
#else
#define PLANE_MEMBERS_VECTOR		Vector
#define PLANE_MEMBERS_VECTOR_SIZE	Size
#endif

//for primitive3d


#define DISVISIBLE_AS_ALPHA 0
#define DISVISIBLE_ALPHA 25

#if 0
#define PRIMITIVE_POINTS_TYPE(type)			type *
#define PRIMITIVE_POINTS_PTR(type)			type *
#define PRIMITIVE_POINTS_ALLOC(v, n, type)	v = new type[n]
#define PRIMITIVE_POINTS_FREE(v)			if(v) delete[](v)
#define PRIMITIVE_POINTS_PTR_BEGIN			
#else
#if 0
#include <deque>
#define PRIMITIVE_POINTS_TYPE(type)			deque<type>
#define PRIMITIVE_POINTS_PTR(type)			deque<type>::iterator
#define PRIMITIVE_POINTS_ALLOC(v, n, type)	v.resize(n)
#define PRIMITIVE_POINTS_FREE(v)			v.clear()
#define PRIMITIVE_POINTS_PTR_BEGIN			.begin()
#else
#define PRIMITIVE_POINTS_TYPE(type)			vector<type>
#define PRIMITIVE_POINTS_PTR(type)			vector<type>::iterator
#define PRIMITIVE_POINTS_ALLOC(v, n, type)	v.resize(n)
#define PRIMITIVE_POINTS_FREE(v)			v.clear()
#define PRIMITIVE_POINTS_PTR_BEGIN			.begin()
#endif
#endif


#if 0
#define VXYZ_VECTOR			vector
#define VXYZ_VECTOR_SIZE	size
#else
#define VXYZ_VECTOR			Vector
#define VXYZ_VECTOR_SIZE	Size
#endif

#define BROKEN_PLANE_VECTOR_TYPE 1

#if		BROKEN_PLANE_VECTOR_TYPE
#define BROKEN_PLANE_VECTOR					vect
#define BROKEN_PLANE_PUSH_BACK(item)		AddMsg(&item)
#else
#define BROKEN_PLANE_VECTOR					vector
#define BROKEN_PLANE_PUSH_BACK(item)		push_back(item)
#endif


#define USE_UNVISIBLE_CUTTING 1

#define USE_BLANK_POLYGON_MATRIX_ON_CUTTING 1


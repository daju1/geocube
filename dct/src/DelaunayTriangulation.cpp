// DelaunayTriangulation.cpp: implementation of the DelaunayTriangulation class.
//
//////////////////////////////////////////////////////////////////////
#define CONSOL 0

//#if !CONSOL
#include "../StdAfx.h"
//#endif

#include "../../array/src/vdouble.h"
#include "DelaunayTriangulation.h"
#include "dc.h"
#include  <stdio.h>
#include  <stdlib.h>
#include <vector>
using namespace std;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DelaunayTriangulation::DelaunayTriangulation()
{

}

DelaunayTriangulation::~DelaunayTriangulation()
{

}

int DelaunayTriangulation::main(int argc, char *argv[])
{
  cardinal n;
  edge *l_cw, *r_ccw;
  index i;
  point **p_sorted, **p_temp;

  if (scanf("%d", &n) != 1)
    panic("Problem reading number of points on first line\n");

  if (n <= 0)
    panic("Number of points has to be greater than 0\n");

  alloc_memory(n);

  read_points(n);

  /* Initialise entry edge pointers. */
  for (i = 0; i < n; i++)
    p_array[i].entry_pt = NULL;

  /* Sort. */
  p_sorted = (point **)malloc((unsigned)n*sizeof(point *));
  if (p_sorted == NULL)
    panic("triangulate: not enough memory\n");
  p_temp = (point **)malloc((unsigned)n*sizeof(point *));
  if (p_temp == NULL)
    panic("triangulate: not enough memory\n");
  for (i = 0; i < n; i++)
    p_sorted[i] = p_array + i;

  merge_sort(p_sorted, p_temp, 0, n-1);
  
  free((char *)p_temp);


  /* Triangulate. */
  divide(p_sorted, 0, n-1, &l_cw, &r_ccw);

  free((char *)p_sorted);

  if (argc == 2)
    print_results(n, argv[1][1]);
  else
    print_results(n, 'e');

  free_memory();

  exit(EXIT_SUCCESS);
  return 0;	/* To keep lint quiet. */
}

void DelaunayTriangulation::alloc_memory(cardinal n)
{
  edge *e;
  index i;

  /* Point storage. */
  p_array = (point *)calloc(n, sizeof(point));
  if (p_array == NULL)
    panic("Not enough memory\n");

  /* Edges. */
  n_free_e = 3 * n;   /* Eulers relation */
  e_array = e = (edge *)calloc(n_free_e, sizeof(edge));
  if (e_array == NULL)
    panic("Not enough memory\n");
  free_list_e = (edge **)calloc(n_free_e, sizeof(edge *));
  if (free_list_e == NULL)
    panic("Not enough memory\n");
  for (i = 0; i < n_free_e; i++, e++)
    free_list_e[i] = e;
}

void DelaunayTriangulation::free_memory()
{
  free(p_array);  
  free(e_array);  
  free(free_list_e);  
}

edge * DelaunayTriangulation::get_edge()
{
  if (n_free_e == 0)
    panic("Out of memory for edges\n");

   return (free_list_e[--n_free_e]);
}

void DelaunayTriangulation::free_edge(edge *e)
{
   free_list_e[n_free_e++] = e;
}

void DelaunayTriangulation::delete_edge(edge *e)
{
/* 
 *  Remove an edge.
 */
  point *u, *v;

  /* Cache origin and destination. */
  u = Org(e);
  v = Dest(e);

  /* Adjust entry points. */
  if (u->entry_pt == e)
    u->entry_pt = e->onext;
  if (v->entry_pt == e)
    v->entry_pt = e->dnext;

   /* Four edge links to change */
  if (Org(e->onext) == u)
    e->onext->oprev = e->oprev;
  else
    e->onext->dprev = e->oprev;

  if (Org(e->oprev) == u)
    e->oprev->onext = e->onext;
  else
    e->oprev->dnext = e->onext;

  if (Org(e->dnext) == v)
    e->dnext->oprev = e->dprev;
  else
    e->dnext->dprev = e->dprev;

  if (Org(e->dprev) == v)
    e->dprev->onext = e->dnext;
  else
    e->dprev->dnext = e->dnext;

  free_edge(e);

}
void DelaunayTriangulation::divide(point *p_sorted[], index l, index r, edge **l_ccw, edge **r_cw)
{
  cardinal n;
  index split;
  edge *l_ccw_l, *r_cw_l, *l_ccw_r, *r_cw_r, *l_tangent;
  edge *a, *b, *c;
  real c_p;
  
  n = r - l + 1;
  if (n == 2) {
    /* Bottom of the recursion. Make an edge */
    *l_ccw = *r_cw = make_edge(p_sorted[l], p_sorted[r]);
  } else if (n == 3) {
    /* Bottom of the recursion. Make a triangle or two edges */
    a = make_edge(p_sorted[l], p_sorted[l+1]);
    b = make_edge(p_sorted[l+1], p_sorted[r]);
    splice(a, b, p_sorted[l+1]);
    c_p = Cross_product_3p(p_sorted[l], p_sorted[l+1], p_sorted[r]);
    
    if (c_p > 0.0)
    {
      /* Make a triangle */
      c = join(a, p_sorted[l], b, p_sorted[r], Right);
      *l_ccw = a;
      *r_cw = b;
    } else if (c_p < 0.0) {
      /* Make a triangle */
      c = join(a, p_sorted[l], b, p_sorted[r], Left);
      *l_ccw = c;
      *r_cw = c;
    } else {
      /* Points are collinear,  no triangle */ 
      *l_ccw = a;
      *r_cw = b;
    }
  } else if (n  > 3) {
    /* Continue to divide */

    /* Calculate the split point */
    split = (l + r) / 2;
  
    /* Divide */
    divide(p_sorted, l, split, &l_ccw_l, &r_cw_l);
    divide(p_sorted, split+1, r, &l_ccw_r, &r_cw_r);

    /* Merge */
    merge(r_cw_l, p_sorted[split], l_ccw_r, p_sorted[split+1], &l_tangent);

    /* The lower tangent added by merge may have invalidated 
       l_ccw_l or r_cw_r. Update them if necessary. */
    if (Org(l_tangent) == p_sorted[l])
      l_ccw_l = l_tangent;
    if (Dest(l_tangent) == p_sorted[r])
      r_cw_r = l_tangent;

    /* Update edge refs to be passed back */ 
    *l_ccw = l_ccw_l;
    *r_cw = r_cw_r;
  }
}

/*
 *  Determines the lower tangent of two triangulations. 
 */
/*static*/ void DelaunayTriangulation::lower_tangent(edge *r_cw_l, point *s, edge *l_ccw_r, point *u,
			  edge **l_lower, point **org_l_lower,
			  edge **r_lower, point **org_r_lower)
{
  edge *l, *r;
  point *o_l, *o_r, *d_l, *d_r;
  boolean finished;

  l = r_cw_l;
  r = l_ccw_r;
  o_l = s;
  d_l = Other_point(l, s);
  o_r = u;
  d_r = Other_point(r, u);
  finished = FALSE;

  while (!finished)
    if (Cross_product_3p(o_l, d_l, o_r) > 0.0) {
      l = Prev(l, d_l);
      o_l = d_l;
      d_l = Other_point(l, o_l);
    } else if (Cross_product_3p(o_r, d_r, o_l) < 0.0) {
      r = Next(r, d_r);
      o_r = d_r;
      d_r = Other_point(r, o_r);
    } else
      finished = TRUE;

  *l_lower = l;
  *r_lower = r;
  *org_l_lower = o_l;
  *org_r_lower = o_r;
}

/* 
 *  The merge function is where most of the work actually gets done.  It is
 *  written as one (longish) function for speed.
 */ 
/*static*/ void DelaunayTriangulation::merge(edge *r_cw_l, point *s, edge *l_ccw_r, point *u, edge **l_tangent)
{
  edge *base, *l_cand, *r_cand;
  point *org_base, *dest_base;
  real u_l_c_o_b, v_l_c_o_b, u_l_c_d_b, v_l_c_d_b;
  real u_r_c_o_b, v_r_c_o_b, u_r_c_d_b, v_r_c_d_b;
  real c_p_l_cand, c_p_r_cand;
  real d_p_l_cand, d_p_r_cand;
  boolean above_l_cand, above_r_cand, above_next, above_prev;
  point *dest_l_cand, *dest_r_cand;
  real cot_l_cand, cot_r_cand;
  edge *l_lower, *r_lower;
  point *org_r_lower, *org_l_lower;

  /* Create first cross edge by joining lower common tangent */
  lower_tangent(r_cw_l, s, l_ccw_r, u, &l_lower, &org_l_lower, &r_lower, &org_r_lower);
  base = join(l_lower, org_l_lower, r_lower, org_r_lower, Right);
  org_base = org_l_lower;
  dest_base = org_r_lower;
  
  /* Need to return lower tangent. */
  *l_tangent = base;

  /* Main merge loop */
  do 
  {
    /* Initialise l_cand and r_cand */
    l_cand = Next(base, org_base);
    r_cand = Prev(base, dest_base);
    dest_l_cand = Other_point(l_cand, org_base);
    dest_r_cand = Other_point(r_cand, dest_base);

    /* Vectors for above and "in_circle" tests. */
    Vector(dest_l_cand, org_base, u_l_c_o_b, v_l_c_o_b);
    Vector(dest_l_cand, dest_base, u_l_c_d_b, v_l_c_d_b);
    Vector(dest_r_cand, org_base, u_r_c_o_b, v_r_c_o_b);
    Vector(dest_r_cand, dest_base, u_r_c_d_b, v_r_c_d_b);

    /* Above tests. */
    c_p_l_cand = Cross_product_2v(u_l_c_o_b, v_l_c_o_b, u_l_c_d_b, v_l_c_d_b);
    c_p_r_cand = Cross_product_2v(u_r_c_o_b, v_r_c_o_b, u_r_c_d_b, v_r_c_d_b);
    above_l_cand = c_p_l_cand > 0.0;
    above_r_cand = c_p_r_cand > 0.0;
    if (!above_l_cand && !above_r_cand)
      break;        /* Finished. */

    /* Advance l_cand ccw,  deleting the old l_cand edge,  until the 
       "in_circle" test fails. */
    if (above_l_cand)
    {
      real u_n_o_b, v_n_o_b, u_n_d_b, v_n_d_b;
      real c_p_next, d_p_next, cot_next;
      edge *next;
      point *dest_next;

      d_p_l_cand = Dot_product_2v(u_l_c_o_b, v_l_c_o_b, u_l_c_d_b, v_l_c_d_b);
      cot_l_cand = d_p_l_cand / c_p_l_cand;

      do 
      {
        next = Next(l_cand, org_base);
        dest_next = Other_point(next, org_base);
        Vector(dest_next, org_base, u_n_o_b, v_n_o_b);
        Vector(dest_next, dest_base, u_n_d_b, v_n_d_b);
        c_p_next = Cross_product_2v(u_n_o_b, v_n_o_b, u_n_d_b, v_n_d_b);
        above_next = c_p_next > 0.0;

        if (!above_next) 
          break;    /* Finished. */

        d_p_next = Dot_product_2v(u_n_o_b, v_n_o_b, u_n_d_b, v_n_d_b);
        cot_next = d_p_next / c_p_next;

        if (cot_next > cot_l_cand)
          break;    /* Finished. */

        delete_edge(l_cand);
        l_cand = next;
        cot_l_cand = cot_next;
  
      } while (TRUE);
    }

    /* Now do the symmetrical for r_cand */
    if (above_r_cand)
    {
      real u_p_o_b, v_p_o_b, u_p_d_b, v_p_d_b;
      real c_p_prev, d_p_prev, cot_prev;
      edge *prev;
      point *dest_prev;

      d_p_r_cand = Dot_product_2v(u_r_c_o_b, v_r_c_o_b, u_r_c_d_b, v_r_c_d_b);
      cot_r_cand = d_p_r_cand / c_p_r_cand;

      do
      {
        prev = Prev(r_cand, dest_base);
        dest_prev = Other_point(prev, dest_base);
        Vector(dest_prev, org_base, u_p_o_b, v_p_o_b);
        Vector(dest_prev, dest_base, u_p_d_b, v_p_d_b);
        c_p_prev = Cross_product_2v(u_p_o_b, v_p_o_b, u_p_d_b, v_p_d_b);
        above_prev = c_p_prev > 0.0;

        if (!above_prev) 
          break;    /* Finished. */

        d_p_prev = Dot_product_2v(u_p_o_b, v_p_o_b, u_p_d_b, v_p_d_b);
        cot_prev = d_p_prev / c_p_prev;

        if (cot_prev > cot_r_cand)
          break;    /* Finished. */

        delete_edge(r_cand);
        r_cand = prev;
        cot_r_cand = cot_prev;

      } while (TRUE);
    }

    /*
     *  Now add a cross edge from base to either l_cand or r_cand. 
     *  If both are valid choose on the basis of the in_circle test . 
     *  Advance base and  whichever candidate was chosen.
     */
    dest_l_cand = Other_point(l_cand, org_base);
    dest_r_cand = Other_point(r_cand, dest_base);
    if (!above_l_cand || (above_l_cand && above_r_cand && cot_r_cand < cot_l_cand))
    {
      /* Connect to the Right */
      base = join(base, org_base, r_cand, dest_r_cand, Right);
      dest_base = dest_r_cand;
    } else {
      /* Connect to the Left */
      base = join(l_cand, dest_l_cand, base, dest_base, Right);
      org_base = dest_l_cand;
    }

  } while (TRUE);
}
/* 
 *  Creates a new edge and adds it to two rings of edges.
 */
edge *DelaunayTriangulation::join(edge *a, point *u, edge *b, point *v, side s)
{
  edge *e;

  /* u and v are the two vertices which are being joined.
     a and b are the two edges associated with u and v res.  */

  e = make_edge(u, v);
  
  if (s == Left) {
    if (Org(a) == u)
      splice(Oprev(a), e, u);
    else
      splice(Dprev(a), e, u);
    splice(b, e, v);
  } else {
    splice(a, e, u);
    if (Org(b) == v)
      splice(Oprev(b), e, v);
    else
      splice(Dprev(b), e, v);
  }

  return e;
}


/* 
 *  Add an edge to a ring of edges. 
 */
void DelaunayTriangulation::splice(edge *a, edge *b, point *v)
{
  edge *next;

  
  /* b must be the unnattached edge and a must be the previous 
     ccw edge to b. */

  if (Org(a) == v) { 
    next = Onext(a);
    Onext(a) = b;
  } else {
    next = Dnext(a);
    Dnext(a) = b;
  }

  if (Org(next) == v)
    Oprev(next) = b;
  else
    Dprev(next) = b;

  if (Org(b) == v) {
    Onext(b) = next;
    Oprev(b) = a;
  } else {
    Dnext(b) = next;
    Dprev(b) = a;
  }
}

/*
 *  Initialise a new edge.
 */
edge *DelaunayTriangulation::make_edge(point *u, point *v)
{
  edge *e;

  e = get_edge();

  e->onext = e->oprev = e->dnext = e->dprev = e;
  e->org = u;
  e->dest = v;
  if (u->entry_pt == NULL)
    u->entry_pt = e;
  if (v->entry_pt == NULL)
    v->entry_pt = e;
  

  return e;
}

void DelaunayTriangulation::panic(char *m)
{
#if !CONSOL
	MessageBox(0, m, "DelaunayTriangulation::panic", 0);
#else
  (void)fprintf(stderr, m);
  exit(EXIT_FAILURE);
#endif
}
void DelaunayTriangulation::read_points(cardinal np)
{
  index i;

  for (i = 0; i < np; i++)
    if (scanf("%f %f", &p_array[i].x, &p_array[i].y) != 2)
	panic("Error reading points\n");
}

/*
 * Driver function.
 */
void DelaunayTriangulation::print_results(cardinal n, char o)
{
  /* Output edges or triangles. */
  if (o == 't')
    print_triangles(n);
  else
    print_edges(n);
}

/* 
 *  Print the ring of edges about each vertex.
 */
/*static*/ 
void DelaunayTriangulation::print_edges(cardinal n)
{
printf("DelaunayTriangulation::print_edges(cardinal n = %d)", n);
  edge *e_start, *e;
  point *u, *v;
  index i;

  for (i = 0; i < n; i++) {
    u = &p_array[i];
printf("i = %d\tu = &p_array[i]\t u->x = %d\tu->y = %d\n", i, u->x, u->y);
    e_start = e = u->entry_pt;
    do
    {
      v = Other_point(e, u);
      if (u < v)
	if (printf("%d %d\n", u - p_array, v - p_array) == EOF)
	  panic("Error printing results\n");
      e = Next(e, u);
    } while (!Identical_refs(e, e_start));
  }
}




/* 
 *  Print the ring of triangles about each vertex.
 */
/*static*/ void DelaunayTriangulation::print_triangles(cardinal n)
{
  edge *e_start, *e, *next;
  point *u, *v, *w;
  index i;
  point *t;

  for (i = 0; i < n; i++) {
    u = &p_array[i];
    e_start = e = u->entry_pt;
    do
    {
      v = Other_point(e, u);
      if (u < v) {
	next = Next(e, u);
	w = Other_point(next, u);
	if (u < w)
	  if (Identical_refs(Next(next, w), Prev(e, v))) {  
	    /* Triangle. */
	    if (v > w) { t = v; v = w; w = t; }
	    if (printf("%d %d %d\n", u - p_array, v - p_array, w - p_array) == EOF)
	      panic("Error printing results\n");
	  }
      }

      /* Next edge around u. */
      e = Next(e, u);
    } while (!Identical_refs(e, e_start));
  }
}
void DelaunayTriangulation::merge_sort(point *p[], point *p_temp[], index l, index r)
{
  index i, j, k, m;

  if (r - l > 0)
  {
    m = (r + l) / 2;
    merge_sort(p, p_temp, l, m);
    merge_sort(p, p_temp, m+1, r);

    for (i = m+1; i > l; i--)
      p_temp[i-1] = p[i-1];
    for (j = m; j < r; j++)
      p_temp[r+m-j] = p[j+1];
    for (k = l; k <= r; k++)
      if (p_temp[i]->x < p_temp[j]->x) {
        p[k] = p_temp[i];
        i = i + 1;
      } else if (p_temp[i]->x == p_temp[j]->x && p_temp[i]->y < p_temp[j]->y) {
        p[k] = p_temp[i];
        i = i + 1;
      } else {
        p[k] = p_temp[j];
        j = j - 1;
      }
  }
}

#if !CONSOL
void DelaunayTriangulation::work(vector<double>& x, vector<double>& y, int sloj, void *p, void (*func)(int sloj, void *p, /*__w64*/long i1, /*__w64*/long i2, vector<int>* indexes), vector<int>* indexes)
{
	cardinal n;
	edge *l_cw, *r_ccw;
	index i;
	point **p_sorted, **p_temp;

	
	n = (cardinal)x.size();
	if (n != (cardinal)y.size())
	{
		MessageBox(0,"x.Length() != y.Length()","DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}
	
	if (n <= 1)
	{
		MessageBox(0, "Number of points has to be greater than 1\n", "DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}
	alloc_memory(n);
	
	//read_points(n);
	for (i = 0; i < n; i++)
	{
		p_array[i].x = x[i];
		p_array[i].y = y[i];
	}
	
	/* Initialise entry edge pointers. */
	for (i = 0; i < n; i++)
		p_array[i].entry_pt = NULL;
	
	/* Sort. */
	p_sorted = (point **)malloc((unsigned)n*sizeof(point *));
	if (p_sorted == NULL)
		panic("triangulate: not enough memory\n");
	p_temp = (point **)malloc((unsigned)n*sizeof(point *));
	if (p_temp == NULL)
		panic("triangulate: not enough memory\n");
	for (i = 0; i < n; i++)
		p_sorted[i] = p_array + i;
	
	merge_sort(p_sorted, p_temp, 0, n-1);
	
	free((char *)p_temp);
	
	/* Triangulate. */
	divide(p_sorted, 0, n-1, &l_cw, &r_ccw);
	
	free((char *)p_sorted);
	work_edges(n, sloj, p, func, indexes);
	free_memory();
}

void DelaunayTriangulation::work_edges(cardinal n, int sloj, void *p, void (*func)(int i, void *p, /*__w64*/long i1, /*__w64*/long i2, vector<int>* indexes), vector<int>* indexes)
{
printf("DelaunayTriangulation::work_edges(cardinal n = %d, int sloj = %d)\n", n, sloj);
	edge *e_start, *e; 
	point *u, *v;
	index i;
	
	for (i = 0; i < n; i++) {
		u = &p_array[i];
		//printf("i = %d\tu = &p_array[i]\t u->x = %d\tu->y = %d\n", i, u->x, u->y);
		e_start = e = u->entry_pt;
		do
		{
			v = Other_point(e, u);
			if (u < v)
			{

				/*if (printf("%d %d\n", u - p_array, v - p_array) == EOF)
					panic("Error printing results\n");*/

				(*func)(sloj, p, u - p_array, v - p_array, indexes);
			}
			e = Next(e, u);
		} 
		while (!Identical_refs(e, e_start));
	}
}
void DelaunayTriangulation::work(vector<double>& x, vector<double>& y, int sloj, void *p, void (*func)(int sloj, void *p, /*__w64*/long i1, /*__w64*/long i2, /*__w64*/long i3, vector<int>* indexes), vector<int>* indexes)
{
	cardinal n;
	edge *l_cw, *r_ccw;
	index i;
	point **p_sorted, **p_temp;

	
	n = (cardinal)x.size();
	if (n != (cardinal)y.size())
	{
		MessageBox(0,"x.Length() != y.Length()","DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}
	
	if (n <= 2)
	{
		MessageBox(0, "Number of points has to be greater than 2\n", "DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}
	alloc_memory(n);
	
	//read_points(n);
	for (i = 0; i < n; i++)
	{
		p_array[i].x = x[i];
		p_array[i].y = y[i];
	}
	
	/* Initialise entry edge pointers. */
	for (i = 0; i < n; i++)
		p_array[i].entry_pt = NULL;
	
	/* Sort. */
	p_sorted = (point **)malloc((unsigned)n*sizeof(point *));
	if (p_sorted == NULL)
		panic("triangulate: not enough memory\n");
	p_temp = (point **)malloc((unsigned)n*sizeof(point *));
	if (p_temp == NULL)
		panic("triangulate: not enough memory\n");
	for (i = 0; i < n; i++)
		p_sorted[i] = p_array + i;
	
	merge_sort(p_sorted, p_temp, 0, n-1);
	
	free((char *)p_temp);
	
	/* Triangulate. */
	divide(p_sorted, 0, n-1, &l_cw, &r_ccw);
	
	free((char *)p_sorted);
	work_triangles(n, sloj, p, func, indexes);
	free_memory();
}
/*static*/ 
void DelaunayTriangulation::work_triangles(cardinal n, int sloj, void *p, void (*func)(int i, void *p, /*__w64*/long i1, /*__w64*/long i2, /*__w64*/long i3, vector<int>* indexes), vector<int>* indexes)
{ 
	edge *e_start, *e, *next;
	point *u, *v, *w;
	index i;
	point *t;
	
	for (i = 0; i < n; i++) {
		u = &p_array[i];
		e_start = e = u->entry_pt;
		do
		{
			v = Other_point(e, u);
			if (u < v) {
				next = Next(e, u);
				w = Other_point(next, u);
				if (u < w)
					if (Identical_refs(Next(next, w), Prev(e, v))) {  
						/* Triangle. */
						if (v > w) { t = v; v = w; w = t; }
						/*if (printf("%d %d %d\n", u - p_array, v - p_array, w - p_array) == EOF)
							panic("Error printing results\n");*/

						(*func)(sloj, p, u - p_array, v - p_array, w - p_array, indexes);
					}
			}
			/* Next edge around u. */
			e = Next(e, u);
		} 
		while (!Identical_refs(e, e_start));
	}
}

void DelaunayTriangulation::main(vector<double>& x, vector<double>& y)
{
printf( "DelaunayTriangulation::main(vector<double>& x, vector<double>& y)\n");
	cardinal n;
	edge *l_cw, *r_ccw;
	index i;
	point **p_sorted, **p_temp;


	
	n = (cardinal)x.size();
	if (n != (cardinal)y.size())
	{
		MessageBox(0,"x.Length() != y.Length()","DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}
	
	if (n <= 0)
	{
		MessageBox(0, "Number of points has to be greater than 0\n", "DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}

  alloc_memory(n);

  //read_points(n);

  for (i = 0; i < n; i++)
  {
    p_array[i].x = x[i];
	p_array[i].y = y[i];
  }


  /* Initialise entry edge pointers. */
  for (i = 0; i < n; i++)
    p_array[i].entry_pt = NULL;

  /* Sort. */
  p_sorted = (point **)malloc((unsigned)n*sizeof(point *));
  if (p_sorted == NULL)
    panic("triangulate: not enough memory\n");
  p_temp = (point **)malloc((unsigned)n*sizeof(point *));
  if (p_temp == NULL)
    panic("triangulate: not enough memory\n");
  for (i = 0; i < n; i++)
    p_sorted[i] = p_array + i;

  merge_sort(p_sorted, p_temp, 0, n-1);
  
  free((char *)p_temp);


  /* Triangulate. */
  divide(p_sorted, 0, n-1, &l_cw, &r_ccw);

  free((char *)p_sorted);

//  if (argc == 2)
//    print_results(n, argv[1][1]);
//  else
    print_results(n, 't');
    print_results(n, 'e');

  free_memory();
}

void DelaunayTriangulation::main(vdouble& x, vdouble& y)
{
	cardinal n;
	edge *l_cw, *r_ccw;
	index i;
	point **p_sorted, **p_temp;
	
	n = x.Length();
	if (n != (cardinal)y.Length())
	{
		MessageBox(0,"x.Length() != y.Length()","DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}
	if (n <= 0)
	{
		MessageBox(0, "Number of points has to be greater than 0\n", "DelaunayTriangulation::main(vdouble& x, vdouble& y)", 0);
		return;
	}

  alloc_memory(n);

  //read_points(n);

  for (i = 0; i < n; i++)
  {
    p_array[i].x = x[i];
	p_array[i].y = y[i];
  }


  /* Initialise entry edge pointers. */
  for (i = 0; i < n; i++)
    p_array[i].entry_pt = NULL;

  /* Sort. */
  p_sorted = (point **)malloc((unsigned)n*sizeof(point *));
  if (p_sorted == NULL)
    panic("triangulate: not enough memory\n");
  p_temp = (point **)malloc((unsigned)n*sizeof(point *));
  if (p_temp == NULL)
    panic("triangulate: not enough memory\n");
  for (i = 0; i < n; i++)
    p_sorted[i] = p_array + i;

  merge_sort(p_sorted, p_temp, 0, n-1);
  
  free((char *)p_temp);


  /* Triangulate. */
  divide(p_sorted, 0, n-1, &l_cw, &r_ccw);

  free((char *)p_sorted);

//  if (argc == 2)
//    print_results(n, argv[1][1]);
//  else
    print_results(n, 'e');

  free_memory();
}
#endif/*CONSOL*/

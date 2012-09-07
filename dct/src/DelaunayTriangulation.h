// DelaunayTriangulation.h: interface for the DelaunayTriangulation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELAUNAYTRIANGULATION_H__8D514805_A957_43BB_A2AB_25E7AB52BDB1__INCLUDED_)
#define AFX_DELAUNAYTRIANGULATION_H__8D514805_A957_43BB_A2AB_25E7AB52BDB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include  "defs.h"
#include  "edge.h"
#include <vector>
using namespace std;

class vdouble;

class DelaunayTriangulation  
{
	point *p_array;
	edge *e_array;
	edge **free_list_e;
	cardinal n_free_e;
public:
	void work(vector<double>& x, vector<double>& y, int sloj, void *p, void (*func)(int sloj, void *p, /*__w64*/long i1, /*__w64*/long i2, /*__w64*/long i3, vector<int>* indexes), vector<int>* indexes);
	void work_triangles(cardinal n, int sloj, void *p, void (*func)(int sloj, void *p, /*__w64*/long i1, /*__w64*/long i2, /*__w64*/long i3, vector<int>* indexes), vector<int>* indexes);

	void work(vector<double>& x, vector<double>& y,  int sloj, void *p, void (*func)(int sloj, void *p, /*__w64*/long i1, /*__w64*/long i2, vector<int>* indexes), vector<int>* indexes);
	void work_edges(cardinal n,  int sloj, void *p, void (*func)(int sloj, void *p, /*__w64*/long i1, /*__w64*/long i2, vector<int>* indexes), vector<int>* indexes);

	void main(vector<double>& x, vector<double>& y);
	void main(vdouble& x, vdouble& y);
	void merge_sort(point *p[], point *p_temp[], index l, index r);
	/*static*/ void print_triangles(cardinal n);
	/*static*/ void print_edges(cardinal n);
	void print_results(cardinal n, char o);
	void read_points(cardinal np);
	void panic(char *m);
	edge *make_edge(point *u, point *v);
	void splice(edge *a, edge *b, point *v);
	edge *join(edge *a, point *u, edge *b, point *v, side s);
	/*static*/ void merge(edge *r_cw_l, point *s, edge *l_ccw_r, point *u, edge **l_tangent);
	/*static*/ void lower_tangent(edge *r_cw_l, point *s, edge *l_ccw_r, point *u,
		edge **l_lower, point **org_l_lower,
		edge **r_lower, point **org_r_lower);
	void divide(point *p_sorted[], index l, index r, edge **l_ccw, edge **r_cw);
	void delete_edge(edge *e);
	void free_edge(edge *e);
	edge * get_edge();
	void free_memory();
	void alloc_memory(cardinal n);
	int main(int argc, char *argv[]);
	DelaunayTriangulation();
	virtual ~DelaunayTriangulation();

};

#endif // !defined(AFX_DELAUNAYTRIANGULATION_H__8D514805_A957_43BB_A2AB_25E7AB52BDB1__INCLUDED_)

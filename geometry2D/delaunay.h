//delaunay.h

#include "./SearchTree.h"
#include "./BraidedSearchTree.h"
#include "./RandomizedSearchTree.h"
#include "./Point.h"

#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#include <cfloat>
#include <limits>

namespace geometry2D
{
//#define Dictionary SearchTree
#define Dictionary BraidedSearchTree
//#define Dictionary RandomizedSearchTree
void save_Edge(Edge* e, void * file);

void SavePointAsDat(Point & p, char * dat_file);

void SavePolygonExAsBln(PolygonEx* p, char * bln_file);
void SaveEdgeExAsBln(EdgeEx * ex, char * bln_file);

void SavePolygonesAsBln(List<Polygon*> * poly, char * bln_file);
void SavePolygonesExAsBln(List<PolygonEx*> * poly, char * bln_file);

void SaveEdgesAsBln(Dictionary<Edge*>& frontier, char * bln_file);
void SaveEdgesExAsBln(Dictionary<EdgeEx*>& frontier, char * bln_file);

template<class T> void SaveEdgesAsBln (List<T> * edges, char * bln_file);
template<class T> void SaveEdgesAsBln2(List<T> * edges, char * bln_file);

Dictionary<Edge*>	* GetContourOfPolygonesEx (List<PolygonEx*> * poly);
List<EdgeEx*>		* GetContourOfPolygonesEx2(List<PolygonEx*> * poly);
template<class T> double GetMaxLenOfEdges(List<T> * edges);
template<class T> double GetMinLenOfEdges(List<T> * edges);
template<class T> double GetMeanLenOfEdges(List<T> * edges);
template<class T> double GetMedianLenOfEdges(List<T> * edges);
template<class T> List<T> * MakeBissectrissToContour(List<T> * edges, double len_biss);
List<EdgeEx*> *  CorrectBissectriss2(List<EdgeEx*> * edges);
List<EdgeEx*> *  CorrectBissectriss3(List<EdgeEx*> * edges);
List<EdgeEx*> *  CorrectBissectriss4(List<EdgeEx*> * edges);

List<PolygonEx*> * GetContourOfExtraPolygones(List<EdgeEx*> * contour, List<EdgeEx*> * biss, vector<Point> * poly_contour_base_points, int base_points_type);

bool GetContourInsidePoint(geometry2D::List<geometry2D::PolygonEx*> * poly, Point & pt_intersect);

void FilteringEdgeEx(Dictionary<EdgeEx*> * out_edges, PolygonEx* p);
void FilteringPolygonesEx0(List<PolygonEx*> * poly, Dictionary<EdgeEx*> * out_edges);
void FilteringPolygonesEx1(List<PolygonEx*> * poly, Dictionary<EdgeEx*> * out_edges);
void FilteringPolygonesEx2(List<PolygonEx*> * poly, Dictionary<EdgeEx*> * out_edges);


geometry2D::List<geometry2D::Polygon*>   * delaunayTriangulate(Point s[], int n);
geometry2D::List<geometry2D::PolygonEx*> * delaunayTriangulateEx(Point s[], int n, Dictionary<EdgeEx*> * out_edges);
geometry2D::List<geometry2D::PolygonEx*> * delaunayTriangulateEx(std::vector<geometry2D::Point>& s, Dictionary<EdgeEx*> * out_edges);
geometry2D::List<geometry2D::PolygonEx*> * delaunayTriangulateEx(std::vector<geometry2D::Point>& s, double min_x, double min_y, double max_x, double max_y, Dictionary<EdgeEx*> * out_edges);

int edgeCmp (Edge *a, Edge *b);
int edgeCmpEx (EdgeEx *a, EdgeEx *b);
int edgeCmpExEpsilon (EdgeEx *a, EdgeEx *b);
int edgeCmpExIndex (EdgeEx *a, EdgeEx *b);



void updateFrontier (Dictionary<Edge*> &frontier, Point &a, Point &b);
void updateFrontier (Dictionary<EdgeEx*> &frontier, Point &a, Point &b, PolygonEx * tria, Dictionary<EdgeEx*> * out_edges);
Edge *hullEdge (Point s[], int n);
Edge *hullEdge (std::vector<geometry2D::Point>& s );

Polygon * triangle(Point &a, Point &b, Point &c);
PolygonEx * triangleEx(Point &a, Point &b, Point &c);
bool mate (Edge &e, Point s[], int n, Point  &p, double& r);
bool mate (Edge &e, std::vector<geometry2D::Point>& s, Point  &p, double& r);

///////////////////////////////////////////////////////////////////////////

template<class T> void SaveEdgesAsBln (List<T> * edges, char * bln_file)
{
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{					
		for (edges->first(); !edges->isHead(); edges->next() )
		{
			geometry2D::Edge* e = edges->val();

			if(e)
			{
				fprintf(bln, "%d,%d\n", 2, 0);
			
				fprintf(bln, "%f,%f\n", e->org.x,  e->org.y);
				fprintf(bln, "%f,%f\n", e->dest.x, e->dest.y);
			}
		}		
		fclose(bln);
	}
}

template<class T> void SaveEdgesAsBln2(List<T> * edges, char * bln_file)
{
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{	
		if (edges)
		{
			fprintf(bln, "%d,%d\n", edges->length()+1, 0);
		
			for (edges->first(); !edges->isHead(); edges->next() )
			{
				geometry2D::Edge* e = edges->val();

				if(e)
				{				
					fprintf(bln, "%f,%f\n", e->org.x,  e->org.y);
					////fprintf(bln, "%f,%f\n", e->dest.x, e->dest.y);
				}
			}
			edges->first();
			if(!edges->isHead())
			{
				geometry2D::Edge* e = edges->val();

				if(e)
				{				
					fprintf(bln, "%f,%f\n", e->org.x,  e->org.y);
					////fprintf(bln, "%f,%f\n", e->dest.x, e->dest.y);
				}
			}
		}
		fclose(bln);
	}
}

template<class T> double GetMaxLenOfEdges(List<T> * edges)
{
	double max_len = 0.0;

	if (!edges)
	{
		MessageBox(0,"Warning: !edges", "GetMaxLenOfEdges", MB_OK);
		return 1.0;
	}
				
	for (edges->first(); !edges->isHead(); edges->next() )
	{
		geometry2D::Edge* e = edges->val();

		if(e)
		{
			Point v = e->dest - e->org;
			double len = v.length();
			if (len > max_len) max_len = len;
		}
	}
	return max_len;
}
template<class T> double GetMinLenOfEdges(List<T> * edges)
{
	double min_len = DBL_MAX;

	if (!edges)
	{
		MessageBox(0,"Warning: !edges", "GetMaxLenOfEdges", MB_OK);
		return 1.0;
	}
				
	for (edges->first(); !edges->isHead(); edges->next() )
	{
		geometry2D::Edge* e = edges->val();

		if(e)
		{
			Point v = e->dest - e->org;
			double len = v.length();
			if (len < min_len) min_len = len;
		}
	}
	return min_len;
}
template<class T> double GetMeanLenOfEdges(List<T> * edges)
{
	double sum_len = 0.0;
	int num = 0;

	if (!edges)
	{
		MessageBox(0,"Warning: !edges", "GetMaxLenOfEdges", MB_OK);
		return 1.0;
	}
				
	for (edges->first(); !edges->isHead(); edges->next() )
	{
		geometry2D::Edge* e = edges->val();

		if(e)
		{
			Point v = e->dest - e->org;
			double len = v.length();
			sum_len += len;
			num++;
		}
	}
	if (num > 0)
		return (sum_len)/num;
	else
		return 1.0;
}
template<class T> double GetMedianLenOfEdges(List<T> * edges)
{
	vector<double> vlen;

	if (!edges)
	{
		MessageBox(0,"Warning: !edges", "GetMaxLenOfEdges", MB_OK);
		return 1.0;
	}
				
	for (edges->first(); !edges->isHead(); edges->next() )
	{
		geometry2D::Edge* e = edges->val();

		if(e)
		{
			Point v = e->dest - e->org;
			double len = v.length();
			vlen.push_back(len);
		}
	}

	std::sort(vlen.begin(), vlen.end());
	if(vlen.size() > 0)
		return vlen[vlen.size()/2];
	else
		return 1.0;
}
template<class T> bool test_orientation(T sa, bool cw)
{
	if (cw)
		return sa > 0.0;
	else
		return sa < 0.0;
}
template<class T> void AppendBissectriss(List<T*> * edges_biss, T* e_1, T* e_2, double len_b)
{
	bool cw = true;
	//построение внешней биссекрисы
	if (e_1->dest != e_2->org)
	{
		char err[2048];
		sprintf(err, 
			"e_1->dest != e_2->org\n" 
			"e_1 (org = [%f %f] dest = [%f %f])\n"
			"e_2 (org = [%f %f] dest = [%f %f])\n"
			,
			e_1->org.x, e_1->org.y, e_1->dest.x, e_1->dest.y, 
			e_2->org.x, e_2->org.y, e_2->dest.x, e_2->dest.y
			); 
		
		MessageBox(0, err, "AppendBissectriss", MB_OK);
		return;
	}

	//перводим ребра в вектора
	Point v1 = e_1->org - e_1->dest;
	Point v2 = e_2->dest - e_2->org;

	//ищем длину векторов-ребер

	double len1 = v1.length();
	double len2 = v2.length();

	//скалярное произведение векторов-рёбер

	double dp = dotProduct(v1, v2);

	//угол между рёбрами

	double cosine = dp / (len1*len2);
	double alpha = acos(cosine);

	// косинус угла между каждым из ребром и внешней биссектисой
	// знак минус характеризует факт того, что биссектрисса внешняя
	double cosine_2;
	double sa = v2.x*v1.y - v1.x*v2.y;

	if (test_orientation<double>(sa,cw))
	{
		cosine_2 = cos(alpha/2.0);
	}
	else
	{
		cosine_2 = - cos(alpha/2.0);
	}

	//скалярное произведение второго ребра и внешней биссектриссы

	double dp2 = len2*len_b*cosine_2;

	// начальная точка внешней биссектриссы

	Point b1 = e_1->dest;// == e_2->org

	// теперь, зная значение скалярного произведения 
	// и начальной точки запишем систему двух уравнений
	// с целью отыскания конечной точки внешней биссектриссы
	Point b2;
	// (b2.x - b1.x) * v2.x + (b2.y - b1.y) * v2.y = dp2
	// (b2.x - b1.x) = vb.x
	// (b2.y - b1.y) = vb.y

	// Вектор биссектриссы
	Point vb;
	// vb.x * v2.x + vb.y * v2.y = dp2
	// vb.x * vb.x + vb.y * vb.y = len_b*len_b

	// if (v2.x != 0)
	// vb.x = (dp2 - vb.y * v2.y) / v2.x
	// ((dp2 - vb.y * v2.y) / v2.x) * ((dp2 - vb.y * v2.y) / v2.x) + vb.y * vb.y = len_b*len_b
	// (dp2 - vb.y * v2.y) * (dp2 - vb.y * v2.y) + vb.y * vb.y * v2.x * v2.x = len_b*len_b * v2.x * v2.x
	
	// [(dp2*dp2) - (vb.y * 2*v2.y*dp2) + (vb.y*vb.y * v2.y*v2.y)] + vb.y*vb.y * v2.x*v2.x = len_b*len_b*v2.x*v2.x
	
	// vb.y*vb.y * (v2.y*v2.y + v2.x*v2.x) - vb.y * (2*v2.y*dp2) + [dp2*dp2 - len_b*len_b*v2.x*v2.x] = 0.0

	// D = (2.0*v2.y*dp2)*(2.0*v2.y*dp2) - 4.0 * (v2.y*v2.y + v2.x*v2.x) * (dp2*dp2 - len_b*len_b*v2.x*v2.x)

	// if (D > 0.0)
	// vb.y = ( 2.0*v2.y*dp2 +- sqrt(D) ) / ( 2.0 * (v2.y*v2.y + v2.x*v2.x) )

	// vb.x = (dp2 - vb.y * v2.y) / v2.x



	// if (v2.y != 0)
	// vb.y = (dp2 - vb.x * v2.x) / v2.y  
	// vb.x * vb.x + ((dp2 - vb.x * v2.x) / v2.y) * ((dp2 - vb.x * v2.x) / v2.y) = len_b*len_b
	// vb.x*vb.x * v2.y*v2.y + (dp2 - vb.x * v2.x) * (dp2 - vb.x * v2.x) = len_b*len_b * v2.y * v2.y
	
	// vb.x*vb.x * v2.y*v2.y + [(dp2*dp2) - (vb.x * 2*v2.x*dp2) + vb.x*vb.x * v2.x*v2.x)] = len_b*len_b*v2.y*v2.y
	
	// vb.x*vb.x * (v2.y*v2.y + v2.x*v2.x) - vb.x * (2*v2.x*dp2) + [dp2*dp2 - len_b*len_b*v2.y*v2.y] = 0.0

	// D = (2.0*v2.x*dp2)*(2.0*v2.x*dp2) - 4.0 * (v2.y*v2.y + v2.x*v2.x) * [dp2*dp2 - len_b*len_b*v2.y*v2.y]

	// if (D > 0.0)
	// vb.x = ( 2.0*v2.x*dp2 +- sqrt(D) ) / ( 2.0 * (v2.y*v2.y + v2.x*v2.x) )

	// vb.x * v2.x + vb.y * v2.y = dp2

	// vb.y = (dp2 - vb.x * v2.x) / v2.y  

	bool solved = false;


	if (fabs(v2.x) > fabs(v2.y))
	{
		if (v2.x != 0.0)
		{
			double D = (2.0*v2.y*dp2)*(2.0*v2.y*dp2) - 4.0 * (v2.y*v2.y + v2.x*v2.x) * (dp2*dp2 - len_b*len_b*v2.x*v2.x);
			if (D > 0.0)
			{
				vb.y = ( 2.0*v2.y*dp2 + sqrt(D) ) / ( 2.0 * (v2.y*v2.y + v2.x*v2.x) );
                vb.x = (dp2 - vb.y * v2.y) / v2.x;
				// Пара векторов (v2,vb) должна быть -тельно ориентированной
				double sa = v2.x*vb.y - vb.x*v2.y;
				if (test_orientation<double>(sa,cw))
				{
					solved = true;
				}
				else
				{
					vb.y = ( 2.0*v2.y*dp2 - sqrt(D) ) / ( 2.0 * (v2.y*v2.y + v2.x*v2.x) );
					vb.x = (dp2 - vb.y * v2.y) / v2.x;
					// Пара векторов (v2,vb) должна быть -тельно ориентированной
					sa = v2.x*vb.y - vb.x*v2.y;
					if (test_orientation<double>(sa,cw))
					{
						solved = true;
					}
					else
					{
					}
				}
			}
		}
	}
	else
	{
		if (v2.y != 0.0)
		{
			double D = (2.0*v2.x*dp2)*(2.0*v2.x*dp2) - 4.0 * (v2.y*v2.y + v2.x*v2.x) * (dp2*dp2 - len_b*len_b*v2.y*v2.y);
			if (D > 0.0)
			{
				vb.x = ( 2.0*v2.x*dp2 + sqrt(D) ) / ( 2.0 * (v2.y*v2.y + v2.x*v2.x) );
				vb.y = (dp2 - vb.x * v2.x) / v2.y;
				// Пара векторов (v2,vb) должна быть -тельно ориентированной
				double sa = v2.x*vb.y - vb.x*v2.y;
				if (test_orientation<double>(sa,cw))
				{
					solved = true;
				}
				else
				{
					vb.x = ( 2.0*v2.x*dp2 - sqrt(D) ) / ( 2.0 * (v2.y*v2.y + v2.x*v2.x) );
					vb.y = (dp2 - vb.x * v2.x) / v2.y;
					// Пара векторов (v2,vb) должна быть -тельно ориентированной
					sa = v2.x*vb.y - vb.x*v2.y;
					if (test_orientation<double>(sa,cw))
					{
						solved = true;
					}
					else
					{
					}
				}
			}
		}
	}

	if (solved)
	{
		b2.x = vb.x + b1.x;
		b2.y = vb.y + b1.y;
		if(edges_biss)
		{
			T* e = new T(b1,b2);
			edges_biss->append(e);
		}
	}
}


template<class T> List<T> * MakeBissectrissToContour(List<T> * edges, double len_biss)
{
	List<T> * edges_biss = new List<T>;

	edges->first();
	if (!edges->isHead())
	{			
		T e_first = edges->val();

		T e_1 = e_first;
		T e_2 = NULL;

		for (edges->next(); !edges->isHead(); edges->next() )
		{
			e_2 = edges->val();

			if(e_1 && e_2)
			{
				AppendBissectriss(edges_biss, e_1, e_2, len_biss);
			}

			e_1 = e_2;
		}
		e_2 = e_first;
		if(e_1 && e_2)
		{
			AppendBissectriss(edges_biss, e_1, e_2, len_biss);
		}
	}
	return edges_biss;
}



}

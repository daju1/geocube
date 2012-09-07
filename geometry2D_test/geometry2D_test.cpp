// geometry2D_test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../geometry2D/Point.h"
#include "../geometry2D/Vertex.h"
#include "../geometry2D/Edge.h"
#include "../geometry2D/Polygon.h"
#include "../geometry2D/PolygonEx.h"
#include "../geometry2D/List.h"
#include "../geometry2D/SearchTree.h"
#include "../geometry2D/BraidedSearchTree.h"
#include "../geometry2D/RandomizedSearchTree.h"
#include "../geometry2D/delaunay.h"


#include "./../tools/src/filedlg.h"
#include "./../tools/src/readfile.h"

using namespace geometry2D;
#include <stdlib.h>
#include <math.h>
#include <vector>
using namespace std;

extern char szPath[];
extern char directory[];

HINSTANCE hInst;								// current instance


int intcmp(int a, int b)
{
	if (a < b) return -1;
	if (a > b) return 1;
	return 0;
}
int strings_in_tree = 0;
void printstring(const char *s, void *)
{
  cout << s << "\n";
  strings_in_tree++;
}
void printint(int i, void *)
{
  cout << i << "\n";
}
int _tmain(int argc, _TCHAR* argv[])
{
#if 0
/*	List<const char*> s;
	s.append("bat");
	s.append("ant");
	s.append("cat");
	cout << leastItem<const char*>(s, strcmp);
	cout << endl;
	cout << endl;

	List<int> l;
	l.append(1);
	l.append(2);
	l.append(-3);
	cout << leastItem<int>(l, intcmp);
	cout << endl;
	cout << endl;*/


	RandomizedSearchTree<const char * > a(strcmp);
	a.insert("df");
	a.insert("df");
	a.insert("sbvfdsb");
	a.insert("sdfbdgb");
	a.insert("dfnggf");
	a.insert("ahg");
	a.insert("ждлкиваз");
	a.insert("ждлк  иваз");
	a.insert("ждлфывмывваз");
	a.insert("ждавмаывмваз");
	a.insert("ждлывмиыавваз");
	a.insert("ждлк иваз");
	a.insert("ждлквмывм ваз");

	strings_in_tree = 0; a.inorder(printstring, NULL);

	cout << "strings_in_tree = " << strings_in_tree << endl;
	cout << endl;

	printf("Now removeMin():\n");
	a.removeMin();
	printf("Now inorder after removeMin():\n");
	cout << endl;
	cout << endl;


	strings_in_tree = 0;a.inorder(printstring, NULL);
	cout << "strings_in_tree = " << strings_in_tree << endl;
	cout << endl;


	int nn = strings_in_tree;

	for (int i = 1; i < nn; i++)
	{
	printf("Now removeMin() again:\n");

	cout << endl;
	cout << endl;
		cout << endl;
		a.removeMin();
		cout << endl;

		printf("Now inorder after  removeMin():\n");
		cout << endl;
		a.inorder(printstring, NULL);
		cout << endl;
	}



	SearchTree<int> t(intcmp);

	t.insert(7);
	t.insert(8);
	t.insert(3);
	t.insert(2);
	t.insert(5);

	t.inorder(printint, NULL);
	cout << endl;
	cout << endl;

	t.insert(4);
	t.inorder(printint, NULL);
	cout << endl;
	cout << endl;
	t.insert(4);
	t.inorder(printint, NULL);
	cout << endl;
	cout << endl;
	int N = 100;

#if 1
	//пррверка максимальной глубины рекурсии - не вылетит ли стек - не произойдёт ли переполнение стека?
	BraidedSearchTree<int> T(intcmp);
	for (int i = 0; i < N; i++)
	{
		T.insert(i);
//		T.insert(rand());
			
		cout << i << "\t";

	}
	cout << endl;

	T.inorder(printint, NULL);
#else

	SearchTree<int> T(intcmp);
	int *v = new int[N];
	for (int i = 0; i < N; i++)
	{
		v[i] = rand();			
		cout << v[i] << "\t";
	}
	cout << endl;

	T.inorder(printint);
	heapSort<int> (v, N, intcmp);

	for (int i = 0; i < N; i++)
	{
		cout << v[i] << "\t";
	}
	cout << endl;
#endif

#endif
#if 1
	if (OpenFileDlg(NULL, "Surfer 7 (*.dat)\0*.dat\0All files \0*.*\0") == S_OK)
	{	
		vector<vector<double> > * vectors = new vector<vector<double> >;
		char dat_filename[255];


		if (ReadDatFile(NULL, szPath, dat_filename, vectors, NULL) == 0)
		{
			vector<double> VX, VY, VZ;// векторы для построения гридов
			double min_x = DBL_MAX, min_y = DBL_MAX;
			double max_x = DBL_MIN, max_y = DBL_MIN;

			int n = int(vectors->size());
			geometry2D::Point * s = new geometry2D::Point[n];

			std::vector<geometry2D::Point> vs;
				
			geometry2D::Point p;

			for (size_t i = 0; i < vectors->size(); i++)
			{
				if ((*vectors)[i].size() < 3)
				{
					char error_str[1024];
					sprintf(error_str, 
						"There must be at least 3 elements in each row\n"
						"But at %u row there are %u elements", i, (*vectors)[i].size());
					MessageBox(NULL, error_str, "Grid->Data", MB_OK | MB_ICONEXCLAMATION);
					return -1;
				}
				double X = (*vectors)[i][0];
				double Y = (*vectors)[i][1];
				double Z = (*vectors)[i][2];

				s[i].x = X;
				s[i].y = Y;
				s[i].index = i;

				p.x = X;
				p.y = Y;
				p.index = i;

				vs.push_back(p);
				
				VX.push_back(X);
				VY.push_back(Y);
				VZ.push_back(Z);
				
				if (min_x > X) min_x = X;
				if (min_y > Y) min_y = Y;
				if (max_x < X) max_x = X;
				if (max_y < Y) max_y = Y;
			}

			printf("pre delaunayTriangulate\n");
			
			//geometry2D::List<geometry2D::Polygon*> * poly = delaunayTriangulate(s, n);
			
			//geometry2D::List<geometry2D::PolygonEx*> * polyEx = delaunayTriangulateEx(s, n);

			Dictionary<EdgeEx*> * out_edges		= new Dictionary<EdgeEx*>(edgeCmpEx);
			Dictionary<EdgeEx*> * out_edges_	= new Dictionary<EdgeEx*>(edgeCmpEx);
			
			geometry2D::List<geometry2D::PolygonEx*> * polyEx	= delaunayTriangulateEx(vs, out_edges);
			geometry2D::List<geometry2D::PolygonEx*> * polyEx_	= delaunayTriangulateEx(vs, min_x, min_y, max_x, max_y, out_edges_);


			char bln_file[1024];
			TCHAR filter[] =   
				TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
				TEXT("All Files (*.*)\0*.*\0");
			
			sprintf(bln_file, "%s", dat_filename);
			DWORD nFilterIndex = 0;
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SavePolygonesExAsBln(polyEx, bln_file);
			}
#if 1
			
			FilteringPolygonesEx1(polyEx, out_edges);

			sprintf(bln_file, "%s_filtered", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SavePolygonesExAsBln(polyEx, bln_file);
			}

			sprintf(bln_file, "%s_filtered_out_edges", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesExAsBln(*out_edges, bln_file);
			}	



			FilteringPolygonesEx2(polyEx, out_edges);

			sprintf(bln_file, "%s_filtered2", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SavePolygonesExAsBln(polyEx, bln_file);
			}

			sprintf(bln_file, "%s_filtered2_out_edges", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesExAsBln(*out_edges, bln_file);
			}

			List<EdgeEx*> * contour = GetContourOfPolygonesEx2(polyEx);
			
			sprintf(bln_file, "%s_filtered2_edges", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesAsBln(contour, bln_file);
				//SaveEdgesAsBln2(contour, bln_file);
			}	

			sprintf(bln_file, "%s_filtered3", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SavePolygonesExAsBln(polyEx_, bln_file);
			}		

			List<EdgeEx*> * contour_ = GetContourOfPolygonesEx2(polyEx_);
			
			sprintf(bln_file, "%s_filtered3_contour", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesAsBln(contour_, bln_file);
				//SaveEdgesAsBln2(contour_, bln_file);
			}	

			sprintf(bln_file, "%s_filtered2_contour_biss", dat_filename);
			double len_biss = GetMaxLenOfEdges(contour);
			List<EdgeEx*> * biss = MakeBissectrissToContour(contour, len_biss);
			CorrectBissectriss3(biss);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesAsBln(biss, bln_file);
			}

			sprintf(bln_file, "%s_filtered3_contour_biss", dat_filename);
			len_biss = GetMaxLenOfEdges(contour_);
			List<EdgeEx*> * biss_ = MakeBissectrissToContour(contour_, len_biss);
			CorrectBissectriss4(biss_);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesAsBln(biss_, bln_file);
			}	

			sprintf(bln_file, "%s_filtered3_out_edges", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesExAsBln(*out_edges_, bln_file);
			}
			/*
			List<PolygonEx*> * poly_contour = 
				GetContourOfExtraPolygones(polyEx, out_edges, contour, biss);

			sprintf(bln_file, "%s_poly_contour2", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SavePolygonesExAsBln(poly_contour, bln_file);
			}

			List<PolygonEx*> * poly_contour_ = 
				GetContourOfExtraPolygones(polyEx_, out_edges_, contour_, biss_);

			sprintf(bln_file, "%s_poly_contour3", dat_filename);
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SavePolygonesExAsBln(poly_contour_, bln_file);
			}
			*/
#endif
		}
		delete vectors;
	}


#endif
	return 0;
}


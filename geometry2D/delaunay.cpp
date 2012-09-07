#include "StdAfx.h"
#include ".\list.h"
#include ".\vertex.h"
#include ".\Edge.h"
#include ".\Polygon.h"
#include ".\PolygonEx.h"

#include ".\delaunay.h"
#include <float.h>



namespace geometry2D
{
	/*
��������������� �������� ���������� ������������ ������  

�� ����� �����,
"�������������� ��������� � ������������ ������� �� �++"
 
  ����������� ������������ ������  

������������ ��� ��������� ������ ����� S 
�������� ������� ������������ �������� �������� CH(S), 
������������ ��� ����� ������ S. ������� ������ ����� 
��� ������������ �� ����� ������������ � ��� ����� 
������ ����������� � ����� ������, ������������� 
������ S. ��������� ������� ������ ����� �������� 
������������, �� ����� ������� �� �������. �� ���. 1 
�������� ��� ��������� �������� ������������ ��� 
������ � ���� �� ������ ����� (�������� ������������� 
����������, ����������� �� ���� ��������).


���. 1: ��� ��������� �������� ������������ 
�� ������ ������ �����
��� ������� ������ ����� S �� ����� ������, 
��� ��� ����� �� ������ S ����� ���� ������������ 
�� ��������� ����� � �� �����, ������� ����� �� 
������� �������� �������� CH(S), � ���������� ����� � 
������� ������ �������� �������� CH(S). ����� ����� 
���������������� � �����, ���������� � ���������� 
������������ S, ��� ����� �������� � ���������� �����. 
� ������ �������� ��������� �����, ������������� ����� 
������� �������� �������� CH(S), � � ���������� ������ � 
��� ��������� �����, ���������� ���� ������������� ������ 
�������� ��������. �������, ��� ������ ����� �������� 
��������� ��� �������� ��������� �����, ����� ��� 
���������� ����� ����� ��������� ��� ����� ������ ����. 
� ���������, ���� ���������� ����� ��������� ��� ��������� 
�����, �� ��� �������� ������ �������� �������� CH(S). 
������� �����, ��� ������ ����� ������������ �������� 
�������� ���� ��������: ������ ���������� ����� ��������� 
����� ����� ��������������, � ������ ����� �������� � 
����� ������������� � ����������� ����������.

����� ����� �����, �� ����������� ��������� ����������� 
�������, ��������� ����� ������ ������� ������������. 
�� ��� ���� ���������� ������������� ��������: ����� 
������ ������������ ��� ������� ������ ���������� 
���������� ����� �������������, ��� ������� �� �������:

������� � ������������ ������ �����. �����������, 
��� ����� ����� S �������� n>3 ����� � �� ��� �� 
��� �����������. ����� ����, i ����� �� ��� �������� 
����������� (�. �. �������� ������ �������� �������� CH(S). 
����� ��� ����� ������� ������������ ������ S ����� �������� 
����� n + i - 2 �������������.

��� �������������� ������� ���������� ������� 
������������ n-i ��������� �����. ��������� ��� 
��� �������� ��������� ��������� ��������, �� ��� 
����� ������������ ����� �������� (n - i) - 2 
�������������. (� ���� �������� �������������� 
�, ����� ����, ����� ��������, ��� ����� ������������ 
������������� m-���������� �������� - ��������� ��� 
����������� � �������� m - 2 ������������). ������ 
��������, ��� ����� ����������� � ������������� ��� 
���������� ���������� i ���������� �����, ������ 
��� �� �����. �� ����������, ��� ���������� ������ 
����� ����� �������� � ���������� ����� ������������� 
�� ���. ��� ���������� ���������� ����� ����� ���������� 
��� ��������, ���������� �� ���. 2. ��-������, ����� 
����� ��������� ������ ���������� ������������ � ����� 
����� ����������� ���������� ����� ������ ��������������. 
��-������, ���� ����� ��������� � ����� �� ����� ������������, 
�� ������ �� ���� �������������, ����������� � ����� �����, 
���������� ����� ������ ��������������. �� ����� �������, 
��� ����� ���������� ���� � �����, ����� ����� ������������� 
�������� (n - i - 2) + (2i), ��� ������ n + i - 2.


���. 2: ��� ��������, ����������� ��� ������������ �����
���������� ����� ���������� �����
� ���� ������� �� ���������� �������� ������������ 
������������ ���� ������������, ��������� ��� ������������ ������. 
��� ������������ ������ �������������� � ��� ������, ��� 
����������� ������������ ��������� � ���������������. ��� 
��������, ������������, ������������ �� ���. 1�, ����� 
������� � ���� ������������ ������, � �� ���. 1� 
������������ �������� ��������� ������ ��������� 
������������� � �� ������ ������� � ���� ������. 
�� ���. 3 ������� ������ ������������ ������ ��� 
������ �������� ����� �����.


���. 3: ������������ ������ ��� 250 �����, ��������� 
��������� ������� � �������� ��������������. ����� 
���������� 484 ������������
��� ������������ ������������ ������ ��� ����������� 
��������� ����� �����������. ����� ����� ��������� 
��������, ���� ���������� ��������� ����������, �� 
������� ����� ��� ����� ������. ����� ���������� ����� 
��������� ��� ������� ������ �����. ��������� ���������� 
��� ������������ �������� ����� ��� ��� �� (�� ������������) 
�������. �������, ��� ���������� ����� ��������� �� ����� 
� ��������� � ��������� ������ ����� S, ���� ������ ���������� 
��� �� ����� ����� �� ������ S. ��, ������, ����� �� ������ 
S ����� ������������� �� ����� ��������� �� ����� ����������.

������������ ������ ����� S ����� ������������� ������, 
���� ��������� ���������� ��� ������� ������������ ����� 
�������� �� �����. �� ����� ������������ ���. 1� �������� 
��� ����������, ������� ���� �� �������� ������ ���� ������ 
����� (����� �������� ���������� � ��� ������ �������������, 
����� ���������, ��� ��� ����� �������� �� ����� ������). 
��� ������� �� ����������� �� ����� ���. 16 � ������ 
���������� ���������� ������ ���� ����� ������� ������������, 
�������������, ��� ������������ �� ��������� � ���� ������.

����� ������� ��� ������������� ������������ ����� � ������ S, 
����� ��������� �������� ������������. ��-������, ����� ������ 
������������ ������������, �� ������ ��������, ��� ����� S 
�������� �� ������� ���� ��� ����� � ��� �� �����������. 
��-������, ��� ������������ ������������ ������ ����������, 
����� ������� ������ ����� �� ������ S �� ������ �� ����� 
��������� ����������. ����� ������, ��� ��� ������ ������������� 
������������ ������ �� ����� ����������, ��� 4 ����� �� ����� 
��������� ���������� ��������� ����������� ��� ��������� 
������������ ������.

��� �������� �������� ����� ����������� ����������� ������� 
������������ �� ������ ������������ �� ���� ���. ������� 
������� ������������ ������� �� ������������� ����� ��������, 
�� ��������� ������ ��������� ������� ������������ ���������� 
������������� ������. �� ������ �������� �������� ���� ����� 
�����������, ������� ������������ � ������� ������� ������������.

����������� ������� ������� �� ��������� ����� ������������� 
����� ������������ ������ ������������ ������� ������������. 
������ ����� ����� ���� ������, ����� ��� �������:

������ �����: ����� ������������ ������ �������� ������, ���� 
��� ��� �� ���� ���������� ����������; 
����� �����: ����� �����, ���� ��� ����������, �� �������� ������ 
���� ����������� � ���� �������; 
������� �����: ����� ��������� �������, ���� ��� ���������� � 
�������� ��� ����������� � ���� �������. 
������� ����� �������� ������������ �����, ������������� �������� 
i ����� � � ���� ��������� �������������� ���������, � ��� 
��������� ����� ������. �� ���� ������ ��������� ����� �� 
������ ���������� ������, ����� ��������. ������� �� ������ 
����� ������� �� ������ ����� �����.

�� ������ �������� ���������� ����� ���� �� ����� � ������� 
� ��� ������������ ���������, ������������� � ������ ����������� 
�������, �� ����� ����������� ����� �. ���� ��� ������� �������� 
������������� f, ������������ ��������� ������� ����� � � ��������� 
������� �������� v, �� ����� � ���������� �������, ��������� ������
�������� ��� ����������� � ���� �������. ������ �� ���� ������ ����� 
������������ t ����������� � ��������� ���������: �� ������� � ����� 
��� �� ������ � �������. ����� ������� v ����� ���������� ����������� 
� ������ �. ��������� ������, ���� ����������� ������� ����������� 
����������� ����������, �� ����� � ������ �������. � ���� ������ ����� 
� �� ����� ����������� �������.

�� ���. 4 �������� ������ ���������, ��� �������� ���������� ������ 
���� � ����� �������. ������� �� ������ ����� �������� ������� ������.

�������� ���������� � ��������� delaunayTriangulate. ��������� 
�������� ������ s �� n ����� � ��� ���������� ������ �������������,
�������������� ������������ ������. ���������� ���������� ����� 
���������� ������ � ������ �� ������� ��������� �������������� ������. 
� �������� ������ Dictionary ����� ������������ ����� �������,
�������������� ��������� ��������. ��������, ����� ��������������
#define Dictionary RandomizedSearchTree.
*/
void SavePolygonesAsBln(List<Polygon*> * poly, char * bln_file)
{
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{					
		for (poly->first(); !poly->isHead(); poly->next() )
		{
			geometry2D::Polygon* p = poly->val();

			if(p->size())
				fprintf(bln, "%d,%d\n", p->size(), 0);

			for (int i = 0; i < p->size(); i++)
			{
				p->advance(CLOCKWISE);
				fprintf(bln, "%f,%f\n", p->point().x, p->point().y);
			}
		}		
		fclose(bln);
	}
}


void SavePolygonesExAsBln(List<PolygonEx*> * poly, char * bln_file)
{
#if 1
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{					
		for (poly->first(); !poly->isHead(); poly->next() )
		{
			geometry2D::PolygonEx* p = poly->val();

			if(p->size())
			{
				fprintf(bln, "%d,%d\t%f\t%u\n", p->size()+1, 0, p->_r, p->index);

				Point first;

				for (int i = 0; i < p->size(); i++)
				{

					p->advance(CLOCKWISE);
					if (i == 0)
						first = p->point();
					fprintf(bln, "%f,%f\t%d\n", p->point().x, p->point().y, p->point().index);
				}
					
				fprintf(bln, "%f,%f\t%d\n", first.x, first.y, first.index);
			}
		}		
		fclose(bln);
	}
#else
	char * p = strrchr(bln_file, '.');
	if (p)
		*p = '\0';

	char tmp[1024];
	sprintf(tmp, "%s_0.bln", bln_file);
	FILE * bln0 = fopen(tmp, "wt");
	sprintf(tmp, "%s_1.bln", bln_file);
	FILE * bln1 = fopen(tmp, "wt");
	sprintf(tmp, "%s_2.bln", bln_file);
	FILE * bln2 = fopen(tmp, "wt");
	sprintf(tmp, "%s_3.bln", bln_file);
	FILE * bln3 = fopen(tmp, "wt");


	if(bln0 && bln1 && bln2 && bln3)
	{					
		for (poly->first(); !poly->isHead(); poly->next() )
		{
			geometry2D::PolygonEx* p = poly->val();

			if(p->size())
			{
				int nn = 0;
				for (int i = 0; i < p->size(); i++)
				{
					p->advance(CLOCKWISE);
					if(p->GetNeighborPolygon())
						nn++;
				}
					
				FILE *bln = NULL;

				switch(nn)
				{
				case 0:
					bln = bln0;
					break;
				case 1:
					bln = bln1;
					break;
				case 2:
					bln = bln2;
					break;
				case 3:
					bln = bln3;
					break;
				}

				if (bln)
				{				
					fprintf(bln, "%d,%d\t%f\t%u\n", p->size()+1, 0, p->_r, p->index);

					Point first;
					for (int i = 0; i < p->size(); i++)
					{

						p->advance(CLOCKWISE);
						if (i == 0)
							first = p->point();
						fprintf(bln, "%f,%f\t%d\n", p->point().x, p->point().y, p->point().index);
					}
						
					fprintf(bln, "%f,%f\t%d\n", first.x, first.y, first.index);
				}
			}
		}		
		fclose(bln0);
		fclose(bln1);
		fclose(bln2);
		fclose(bln3);
	}
#endif
}

void SavePointAsDat(Point & p, char * dat_file)
{
	FILE * dat = fopen(dat_file, "wt");
	if(dat)
	{
		fprintf(dat, "%f,%f\n", p.x, p.y);
		fclose(dat);
	}
}

void SavePolygonExAsBln(PolygonEx* p, char * bln_file)
{
printf("SavePolygonExAsBln\n");
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{
printf("if(bln) p->size() = %d\n", p->size());
		if(p->size())
		{
			fprintf(bln, "%d,%d, %f\n", p->size()+1, 0, p->_r);
printf("%d,%d, %f\n", p->size()+1, 0, p->_r);

			Point first;

			for (int i = 0; i < p->size(); i++)
			{

				p->advance(CLOCKWISE);
				if (i == 0)
					first = p->point();
				fprintf(bln, "%f,%f\n", p->point().x, p->point().y);
printf("%f,%f\n", p->point().x, p->point().y);
			}
				
			fprintf(bln, "%f,%f\n", first.x, first.y);
printf("%f,%f\n", first.x, first.y);
		}

		fclose(bln);
	}
}
void save_EdgeEx(EdgeEx* e, void * file)
{
	FILE * bln = (FILE *)file;
				
	fprintf(bln, "%d,%d\n", 2, 0);				
	fprintf(bln, "%f,%f\n", e->org.x,  e->org.y);
	fprintf(bln, "%f,%f\n", e->dest.x, e->dest.y);
	// ����� �� ���������� ��������� ���������� ��������� �� ��������
	if (true)
	{
		if(e->LeftPolygon())
		{
			Edge f(e->org, e->dest);
			f.flip();f.rot();//������ ������� ������� �� 90 ��������

			fprintf(bln, "%d,%d\n", 2, 0);				
			fprintf(bln, "%f,%f\n", f.point(0.5).x,  f.point(0.5).y );
			fprintf(bln, "%f,%f\n", f.point(0.52).x, f.point(0.52).y);
		}
		if(e->RightPolygon())
		{
			Edge f(e->org, e->dest);
			f.rot();//�� ������� ������� �� 90 ��������

			fprintf(bln, "%d,%d\n", 2, 0);				
			fprintf(bln, "%f,%f\n", f.point(0.5).x,  f.point(0.5).y );
			fprintf(bln, "%f,%f\n", f.point(0.52).x, f.point(0.52).y);
		}	
	}
}

void SaveEdgesExAsBln(Dictionary<EdgeEx*>& frontier, char * bln_file)
{
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{		
		frontier.inorder(save_EdgeEx, (void *)bln);		
		fclose(bln);
	}
}

void SaveEdgeExAsBln(EdgeEx * ex, char * bln_file)
{
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{		
		save_EdgeEx(ex,(void *)bln);		
		fclose(bln);
	}
}

void save_Edge(Edge* e, void * file)
{
	FILE * bln = (FILE *)file;
				
	fprintf(bln, "%d,%d\n", 2, 0);				
	fprintf(bln, "%f,%f\n", e->org.x,  e->org.y);
	fprintf(bln, "%f,%f\n", e->dest.x, e->dest.y);
}

template<class T> void SaveEdgesAsBln(Dictionary<Edge*>& frontier, char * bln_file)
{
	FILE * bln = fopen(bln_file, "wt");
	if(bln)
	{		
		frontier.inorder(save_Edge, (void *)bln);		
		fclose(bln);
	}
}

int Edges;

void visit_EdgeEx(EdgeEx* e, void * )
{
	Edges++;
  //cout << "e->org.x = " << e->org.x << "\n";
  //cout << "e->org.y = " << e->org.y << "\n";

  //cout << "e->dest.x = " << e->dest.x << "\n";
  //cout << "e->dest.y = " << e->dest.y << "\n\n";
}

void visit_Edge(Edge* e, void * )
{
	Edges++;
  //cout << "e->org.x = " << e->org.x << "\n";
  //cout << "e->org.y = " << e->org.y << "\n";

  //cout << "e->dest.x = " << e->dest.x << "\n";
  //cout << "e->dest.y = " << e->dest.y << "\n\n";
}

List<Polygon*> * delaunayTriangulate(Point s[], int n)
{
  int iter = 0;
  Point p;
  List<Polygon*> *triangles = new List<Polygon*>; 
  Dictionary<Edge*> frontier(edgeCmp);
  Edge *e = hullEdge(s, n);
  frontier.insert(e);

  while (!frontier.isEmpty()) {
	  e = frontier.removeMin();	
	  double r;
	  if (mate(*e, s, n, p, r)) {
		  updateFrontier(frontier, p, e->org);
		  updateFrontier(frontier, e->dest, p);
          triangles->insert(triangle(e->org, e->dest, p));
	  }
	  delete e;	

	  if (++iter > n*n)
	  {
		  //MessageBox(0,"Warning!!!\nbreak if (iter > n*n)", "delaunayTriangulate", MB_OK);
		  printf("delaunayTriangulate\tWarning!!!\tbreak if (iter > n*n)\n");
		  break;
	  }

  }
  return triangles;
}
List<Polygon*> * delaunayTriangulate(std::vector<geometry2D::Point>& s)
{
	int n = s.size();
  int iter = 0;
  Point p;
  List<Polygon*> *triangles = new List<Polygon*>; 
  Dictionary<Edge*> frontier(edgeCmp);
  Edge *e = hullEdge(s);
  frontier.insert(e);

  while (!frontier.isEmpty()) {
	  e = frontier.removeMin();	
	  double r;
	  if (mate(*e, s, p, r)) {
		  updateFrontier(frontier, p, e->org);
		  updateFrontier(frontier, e->dest, p);
          triangles->insert(triangle(e->org, e->dest, p));
	  }
	  delete e;	

	  if (++iter > n*n)
	  {
		  //MessageBox(0,"Warning!!!\nbreak if (iter > n*n)", "delaunayTriangulate", MB_OK);
		  printf("delaunayTriangulate\tWarning!!!\tbreak if (iter > n*n)\n");
		  break;
	  }

  }
  return triangles;
}
List<PolygonEx*> * delaunayTriangulateEx(Point s[], int n, Dictionary<EdgeEx*> * out_edges)
{
  int iter = 0;
  Point p;
  List<PolygonEx*> *triangles = new List<PolygonEx*>; 
  Dictionary<EdgeEx*> frontier(edgeCmpEx);
  Edge *e = hullEdge(s, n);
  EdgeEx *ex = new EdgeEx(e->org, e->dest);
  delete e;
  frontier.insert(ex);

  while (!frontier.isEmpty()) {

	  //Edges = 0;frontier.inorder(visit_EdgeEx, NULL);
	  //printf("post1 frontier.inorder(visit_EdgeEx); Edges = %d\n", Edges);

	  ex = frontier.removeMin();
	
	  //Edges = 0;frontier.inorder(visit_EdgeEx, NULL);
	  //printf("post2 frontier.inorder(visit_EdgeEx); Edges = %d\n", Edges);
	  double r;
	  if (mate(*ex, s, n, p, r)) {
		  PolygonEx * tria = triangleEx(ex->org, ex->dest, p);
		  tria->_r = r;

		  updateFrontier(frontier, p, ex->org, tria, out_edges);
		  updateFrontier(frontier, ex->dest, p, tria, out_edges);

		  tria->SetNeighborPolygon(ex, ex->LeftPolygon());
		  if (ex->LeftPolygon())
			  ex->LeftPolygon()->SetNeighborPolygon(ex, tria);
		  
		  ex->RightPolygon(tria);

          triangles->insert(tria);
	  }
	  if (out_edges)
	  {
		  out_edges->insert(ex);
	  }
	  else
		  delete ex;	  

	  //Edges = 0;frontier.inorder(visit_EdgeEx, NULL);
	  //printf("post3 frontier.inorder(visit_EdgeEx); Edges = %d\n", Edges);
/*
	  CreateDirectory("temp", NULL);

	  char bln_file[1024];
	  sprintf( bln_file, "temp/frontier%04d.bln", iter);
	  SaveEdgesExAsBln(frontier, bln_file);

	  printf("%s\n", bln_file);

	  sprintf( bln_file, "temp/triangles%04d.bln", iter);
	  SavePolygonesExAsBln(triangles, bln_file);
*/
	  if (++iter > n*n)
	  {
		  //MessageBox(0,"Warning!!!\nbreak if (iter > n*n)", "delaunayTriangulate", MB_OK);
		  printf("delaunayTriangulate\tWarning!!!\tbreak if (iter > n*n)\n");
		  break;
	  }

  }
  return triangles;
}

List<PolygonEx*> * delaunayTriangulateEx(std::vector<geometry2D::Point>& s, Dictionary<EdgeEx*> * out_edges)
{
	int n = s.size();
  int iter = 0;
  Point p;
  List<PolygonEx*> *triangles = new List<PolygonEx*>; 
  Dictionary<EdgeEx*> frontier(edgeCmpEx);
  Edge *e = hullEdge(s);
  EdgeEx *ex = new EdgeEx(e->org, e->dest);
  delete e;
  frontier.insert(ex);

  while (!frontier.isEmpty()) {

	  //Edges = 0;frontier.inorder(visit_EdgeEx, NULL);
	  //printf("post1 frontier.inorder(visit_EdgeEx); Edges = %d\n", Edges);

	  ex = frontier.removeMin();
	
	  //Edges = 0;frontier.inorder(visit_EdgeEx, NULL);
	  //printf("post2 frontier.inorder(visit_EdgeEx); Edges = %d\n", Edges);
	  double r;
	  if (mate(*ex, s, p, r)) {
		  PolygonEx * tria = triangleEx(ex->org, ex->dest, p);
		  tria->_r = r;

		  updateFrontier(frontier, p, ex->org, tria, out_edges);
		  updateFrontier(frontier, ex->dest, p, tria, out_edges);

		  tria->SetNeighborPolygon(ex, ex->LeftPolygon());
		  if (ex->LeftPolygon())
			  ex->LeftPolygon()->SetNeighborPolygon(ex, tria);
		  
		  ex->RightPolygon(tria);

		  triangles->insert(tria);
	  }
	  if (out_edges)
	  {
		  out_edges->insert(ex);
	  }
	  else
		  delete ex;	  

	  //Edges = 0;frontier.inorder(visit_EdgeEx, NULL);
	  //printf("post3 frontier.inorder(visit_EdgeEx); Edges = %d\n", Edges);
/*
	  CreateDirectory("temp", NULL);

	  char bln_file[1024];
	  sprintf( bln_file, "temp/frontier%04d.bln", iter);
	  SaveEdgesExAsBln(frontier, bln_file);

	  printf("%s\n", bln_file);

	  sprintf( bln_file, "temp/triangles%04d.bln", iter);
	  SavePolygonesExAsBln(triangles, bln_file);
*/
	  if (++iter > n*n)
	  {
		  //MessageBox(0,"Warning!!!\nbreak if (iter > n*n)", "delaunayTriangulate", MB_OK);
		  printf("delaunayTriangulate\tWarning!!!\tbreak if (iter > n*n)\n");
		  break;
	  }

  }
  return triangles;
}
void FilteringEdgeEx(Dictionary<EdgeEx*> * out_edges, PolygonEx* p)
{
	if (out_edges)
	{
		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			EdgeEx * e = new EdgeEx(p->edge().org, p->edge().dest);
			EdgeEx * ex = out_edges->find(e);
			if (ex)
			{
				if (ex->LeftPolygon() == p)
				{
					ex->LeftPolygon(NULL);
				}
				if (ex->RightPolygon() == p)
				{
					ex->RightPolygon(NULL);
				}
				if (ex->LeftPolygon() == NULL && ex->RightPolygon() == NULL)
				{
					out_edges->remove(e);
					delete ex;
				}
			}
			else
			{
				e->flip();
				EdgeEx * ex_ = out_edges->find(e);
				if (ex_)
				{
					if (ex_->LeftPolygon() == p)
					{
						ex_->LeftPolygon(NULL);
					}
					if (ex_->RightPolygon() == p)
					{
						ex_->RightPolygon(NULL);
					}
					if (ex_->LeftPolygon() == NULL && ex_->RightPolygon() == NULL)
					{
						out_edges->remove(e);
						delete ex_;
					}
				}
				else
				{
					// ����� �� ���� ������� ������� ���������� 
					// ��-�� ��������������� ������� ���������
					printf("Warning: edge (e->org [%f %f %d], e->dest [%f %f %d]) not found\n"
						"Now try not fast algorithm\n", 
						e->org.x, 
						e->org.y, 
						e->org.index, 
						e->dest.x,
						e->dest.y,
						e->dest.index
						);

					bool equial = false;
					EdgeEx * exx = NULL;
					for(out_edges->first(); !out_edges->isHead(); out_edges->next())
					{
						exx = out_edges->val();
						if (exx)
						{
							if (exx->org.index == e->org.index
								&& 
								exx->dest.index == e->dest.index)
							{
								equial = true;
								break;
							}
							else
							{
								if (exx->org.index == e->dest.index
									&& 
									exx->dest.index == e->org.index)
								{
									equial = true;
									break;
								}
							}
						}
					}
					if (equial && exx)
					{						
						if (exx->LeftPolygon() == p)
						{
							exx->LeftPolygon(NULL);
						}
						if (exx->RightPolygon() == p)
						{
							exx->RightPolygon(NULL);
						}
						if (exx->LeftPolygon() == NULL && exx->RightPolygon() == NULL)
						{
							/*if (out_edges->remove())
								delete exx;
							else
							{
								printf("Warning: Can not remove edge (exx->org [%f %f %d], exx->dest [%f %f %d])!!!\n", 
									exx->org.x, 
									exx->org.y, 
									exx->org.index, 
									exx->dest.x,
									exx->dest.y,
									exx->dest.index
									);
							}*/
						}
					}
					else
					{
						printf("Error: edge (e->org [%f %f %d], e->dest [%f %f %d]) not found again!!!\n", 
							e->org.x, 
							e->org.y, 
							e->org.index, 
							e->dest.x,
							e->dest.y,
							e->dest.index
							);
					}
				}
			}
			delete e;
		}
	}
}
void FilteringPolygonesEx0(List<PolygonEx*> * poly, Dictionary<EdgeEx*> * out_edges)
{
	// ����� �� ������� ��� ������������, ������� ����� ������� � �������� -1
	// �� ��������� ���������
	for (poly->first(); !poly->isHead(); poly->next() )
	{
		geometry2D::PolygonEx* p = poly->val();

		bool to_delete = false;

		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			if (p->point().index == -1)
				to_delete = true;
		}
		if (to_delete)
		{
			FilteringEdgeEx(out_edges, p);
			delete poly->remove();
		}
	}	

}



List<PolygonEx*> * delaunayTriangulateEx(std::vector<geometry2D::Point>& s, double min_x, double min_y, double max_x, double max_y, Dictionary<EdgeEx*> * out_edges)
{
	int len = s.size();

	//������� ��������
	double S = fabs((max_x-min_x)*(max_y-min_y));

	//������� ��������� �����
	double plotnost_t = double(len) / S;

	//����������� ���������� ����� ������ ������ � ��������� � ��� ��������
	double delta_ma = 0.5 / sqrt(plotnost_t);

	//������������ ������ ������� �������

	Point p;
	p.index = -1;
	double x,y;

	y = min_y - delta_ma;
	for (x = min_x - delta_ma; x < max_x + 0.5*delta_ma; x += delta_ma)
	{
		p.x = x;
		p.y = y;
		s.push_back(p);
	}

	x = max_x + delta_ma;
	for (y = min_y - delta_ma; y < max_y + 0.5*delta_ma; y += delta_ma)
	{
		p.x = x;
		p.y = y;
		s.push_back(p);
	}

	y = max_y + delta_ma;
	for (x = max_x + delta_ma; x > min_x - 0.5*delta_ma; x -= delta_ma)
	{
		p.x = x;
		p.y = y;
		s.push_back(p);
	}

	x = min_x - delta_ma;
	for (y = max_y + delta_ma; y > min_y - 0.5*delta_ma; y -= delta_ma)
	{
		p.x = x;
		p.y = y;
		s.push_back(p);
	}

	List<PolygonEx*> *triangles = delaunayTriangulateEx(s, out_edges);

	FilteringPolygonesEx0(triangles, out_edges);

	return triangles;
}
Dictionary<Edge*> * GetContourOfPolygonesEx(List<PolygonEx*> * poly)
{
	Dictionary<Edge*> * edges = new Dictionary<Edge*>(edgeCmp);
	for (poly->first(); !poly->isHead(); poly->next() )
	{
		geometry2D::PolygonEx* p = poly->val();

		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			//******************************
			PolygonEx* pn = p->GetNeighborPolygon();
			if (!pn)
			{
				//******************************
				Edge *e = new Edge(p->edge());
				edges->insert(e);
			}
		}
	}	
	return edges;
}

bool GetContourInsidePoint(geometry2D::List<geometry2D::PolygonEx*> * poly, Point & pt_intersect)
{
	// ���� ������ ���������� ������� �������
	bool krajnij_found = false;
	geometry2D::PolygonEx* krajnij_first = NULL;
	for (poly->first(); !poly->isHead(); poly->next() )
	{
		geometry2D::PolygonEx* p = poly->val();
		geometry2D::Vertex* _v = p->v();//���������� ��������� �������

		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			//******************************
			PolygonEx* pn = p->GetNeighborPolygon();
			if (!pn)
			{
				krajnij_found = true;
				//******************************
				krajnij_first  = p;
			}
		}
		if (krajnij_found)
			break;
	}	

	if(!krajnij_found)
		return false;

	geometry2D::PolygonEx* p = krajnij_first;

	// ������� ����� ����������� ���������� ������������
	
	bool pt_intersect_calculed = false;

	List<Edge*> * edges_biss = new List<Edge*>;

	int i = 0;
	if (i < p->size())
	{		
		Edge* e_1 = &p->edge();	p->advance(CLOCKWISE); i++;
		if (i < p->size())
		{
			Edge* e_2 = &p->edge();	p->advance(CLOCKWISE); i++;
			AppendBissectriss(edges_biss, e_1, e_2, 1.0);
			if (i < p->size())
			{
				Edge* e_3 = &p->edge();	p->advance(CLOCKWISE); i++;
				AppendBissectriss(edges_biss, e_2, e_3, 1.0);
			}
		}
	}

	edges_biss->first();

	if( !edges_biss->isHead() )
	{
		Edge* b_1 = edges_biss->val();
		edges_biss->next();
		if ( !edges_biss->isHead() )
		{
			Edge* b_2 = edges_biss->val();
			double f;
			b_1->intersect(*b_2, f);
			pt_intersect = b_1->point(f);
			pt_intersect_calculed = true;
		}
	}
    
	delete edges_biss;

	if (pt_intersect_calculed)            
		return true;
	else
	{
		return false;
	}
}

geometry2D::List<EdgeEx*> * GetContourOfPolygonesEx2(geometry2D::List<geometry2D::PolygonEx*> * poly)
{
	// ���� ������ ���������� ������� �������
	bool krajnij_found = false;
	geometry2D::PolygonEx* krajnij_first = NULL;
	for (poly->first(); !poly->isHead(); poly->next() )
	{
		geometry2D::PolygonEx* p = poly->val();
		geometry2D::Vertex* _v = p->v();//���������� ��������� �������

		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			//******************************
			PolygonEx* pn = p->GetNeighborPolygon();
			if (!pn)
			{
				krajnij_found = true;
				//******************************
				krajnij_first  = p;
			}
		}
		if (krajnij_found)
			break;
	}	

	if(!krajnij_found)
		return NULL;

	List<EdgeEx*> * edges = new List<EdgeEx*>;

	geometry2D::PolygonEx* p = krajnij_first;//�������������� ������� �������

	while(true)
	{ 
		geometry2D::Vertex* _v = p->v();//���������� ��������� �������

		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			//******************************
			PolygonEx* pn = p->GetNeighborPolygon();
			if (!pn)
			{	
				break;
				//������� �� ����� for ���� �� �������� �������� �����
			}
			//******************************
		}
		//������ ����� ���� �� ����� ������ ��������� ����� - �������������� ��������
		for (int i = 0; i < p->size(); i++)
		{
			p->advance(COUNTER_CLOCKWISE);
			//******************************
			PolygonEx* pn = p->GetNeighborPolygon();
			if (pn)
			{	
				break;
			}
			//******************************
		}
		if(!p->GetNeighborPolygon())
		{
			//��� ���������� �������� - �� ����� ���� � ��������� ��� �������
			//!!!!!!!!!!!!!!!!!!!!!!!
			for (int i = 0; i < p->size(); i++)
			{
				p->advance(CLOCKWISE);
				//******************************
				EdgeEx *e = new EdgeEx(p->edge());
				e->RightPolygon(p);
				edges->append(e);
			}
			MessageBox(0,"��� ���������� �������� - �� ����� ���� � ��������� ��� �������", "Warning GetContourOfPolygonesEx2", MB_OK);
			return edges;
		}
		// �� ���� ��� ����� 
		p->advance(CLOCKWISE);
		// � �� �� ������ ������� ����� 
		// (� �������� ������������ ����� ���� ��� ���� ��� � ��� ������� �����)
		if(p->GetNeighborPolygon())
		{
			//��� ������
			//!!!!!!!!!!!!!!!!!!!!!!!
			MessageBox(0,"Error", "GetContourOfPolygonesEx2", MB_OK);
			return edges;
		}
		// ���� ��� ����� ���������� � ������
		EdgeEx *e = new EdgeEx(p->edge());
		e->RightPolygon(p);
		edges->append(e);
		// �� ���� ��� ����� - �� ������� �������
		p->advance(CLOCKWISE);
		// ���� ������ ����� ���� �������, 
		// ����� ��� ���� ���������� � ������ 
		// � ����� ������ ��� �����
		if(!p->GetNeighborPolygon())
		{
			EdgeEx *e = new EdgeEx(p->edge());
			e->RightPolygon(p);
			edges->append(e);
			// �� ���� ��� ����� - �� ������� �������
			p->advance(CLOCKWISE);
		}
		// ������ �� ������ ������� �� ������
		PolygonEx* pn = p->GetNeighborPolygon();


		if(!pn)
		{
			//��� ������
			//!!!!!!!!!!!!!!!!!!!!!!!
			MessageBox(0,"Error 2", "GetContourOfPolygonesEx2", MB_OK);
			return edges;
		}


		//���� ������ ��������� �������� ������������ 
		while(true)
		{  
			geometry2D::Vertex* _vn = pn->v();//���������� ��������� �������
			bool vertex_found = false;
			//� ������ ���� �������, ������� �� ����������� ������������� ������� ������� ����������� ��������
			for (int i = 0; i < pn->size(); i++)
			{
				pn->advance(CLOCKWISE);
				if (pn->point() == p->point())
				{
					vertex_found = true;
					break;
				}
			}
			if (!vertex_found)
			{
				//��� ������
				//!!!!!!!!!!!!!!!!!!!!!!!
				MessageBox(0,"Error 3", "GetContourOfPolygonesEx2", MB_OK);
				return edges;
			}
			//����� �������
			bool border_found = false;
			for (int i = 0; i < pn->size(); i++)
			{
				pn->advance(CLOCKWISE);
				if (!pn->GetNeighborPolygon())
				{
					vertex_found = true;
				}
			}
			if (!pn->GetNeighborPolygon())
			{
				//�������� ������� ����������� ������
				p = pn;
				break;
			}
			else
			{
				// ���������� ����� ��������� �������� ������������
				pn = pn->GetNeighborPolygon();
			}
		}

		if (p == krajnij_first)
		{
			//���!!!!!
			//����� ���������
			break;
		}
	}

	return edges;
}

List<PolygonEx*> * GetContourOfExtraPolygones(List<EdgeEx*> * contour, 
											  List<EdgeEx*> * biss, 
											  vector<Point> * poly_contour_base_points, 
											  int base_points_type)
{
	List<PolygonEx*> * poly_contour = new List<PolygonEx*>;
		
	biss->last();
	EdgeEx * b1 = biss->val();

	for (contour->first(), biss->first(); 
		!contour->isHead() && !biss->isHead(); 
		contour->next(), biss->next() )
	{
		EdgeEx * ex = contour->val();
		EdgeEx * b2 = biss->val();
		PolygonEx * p = new PolygonEx;
		if (b1 && ex && b2)
		{
			// ������� ����������������� �������
			p->insert(b1->dest);
			p->insert(ex->org);
			p->insert(ex->dest);
			p->insert(b2->dest);

            // ����� ������� ����������� ��������� �� ��������� ����������������� �������
			ex->LeftPolygon(p);
			// ���������������� �������� ����� ��� ��������� �� ��������� ����������������� �������
			if (ex->RightPolygon())
				ex->RightPolygon()->SetNeighborPolygon(ex, p);

			p->SetNeighborPolygon(ex, ex->RightPolygon());
			if (poly_contour_base_points)
			{
				switch(base_points_type)
				{
				case 0:
					{
						poly_contour_base_points->push_back(ex->org);
					}
					break;
				case 1:
					{
						Point pt_intersect; bool pt_intersect_calculed = false;

						List<EdgeEx*> * edges_biss = new List<EdgeEx*>;
						EdgeEx b1_flip  = *b1; b1_flip.flip();
						AppendBissectriss(edges_biss, &b1_flip, ex, 1.0);
						AppendBissectriss(edges_biss, ex, b2, 1.0);


						edges_biss->first();

						if( !edges_biss->isHead() )
						{
							Edge* b_1 = edges_biss->val();
							edges_biss->next();
							if ( !edges_biss->isHead() )
							{
								Edge* b_2 = edges_biss->val();
								double f;
								b_1->intersect(*b_2, f);
								pt_intersect = b_1->point(f);
								pt_intersect_calculed = true;
							}
						}
				        
						delete edges_biss;

						if (pt_intersect_calculed)            
							poly_contour_base_points->push_back(pt_intersect);
						else
						{
							char err[2048];
							sprintf(err, 
								"!pt_intersect_calculed\n" 
								"b1 (org = [%f %f] dest = [%f %f])\n"
								"b1f(org = [%f %f] dest = [%f %f])\n"
								"ex (org = [%f %f] dest = [%f %f])\n"
								"b2 (org = [%f %f] dest = [%f %f])\n"
								,
								b1->org.x, b1->org.y, b1->dest.x, b1->dest.y, 
								b1_flip.org.x, b1_flip.org.y, b1_flip.dest.x, b1_flip.dest.y, 
								ex->org.x, ex->org.y, ex->dest.x, ex->dest.y,
								b2->org.x, b2->org.y, b2->dest.x, b2->dest.y 
								); 
							
							MessageBox(0, err, "GetContourOfExtraPolygones", MB_OK);
							
							poly_contour_base_points->push_back(ex->org);
						}
					}
					break;
				}
			}

			// ������������ ����������� ��������� �� ������ ��� ������������ �������
			b1->RightPolygon(p);
			b2->LeftPolygon(p);
		}

		poly_contour->append(p);
		b1 = b2;
	}

	return poly_contour;
}

void CorrectBissectriss(Edge* e_1, Edge* e_2)
{
	if (e_1 && e_2)
	{
		double t1;
		e_1->intersect(*e_2, t1);
		double t2;
		e_2->intersect(*e_1, t2);
		if (t1 > 0.0 && t2 > 0.0) 
		{
			if (t1 < 1.0)
			{
				Point end1 = e_1->point(t1);
				e_1->dest = end1;
			}
			if (t2 < 1.0)
			{
				Point end2 = e_2->point(t2);
				e_2->dest = end2;
			}
		}
	}
}
void CorrectBissectriss(Edge* e_1, Edge* e_2, Edge* e_3)
{
	CorrectBissectriss(e_1, e_2);
	CorrectBissectriss(e_2, e_3);
	CorrectBissectriss(e_1, e_3);
}

void CorrectBissectriss(Edge* e_1, Edge* e_2, Edge* e_3, Edge* e_4)
{
	CorrectBissectriss(e_1, e_2);
	CorrectBissectriss(e_2, e_3);
	CorrectBissectriss(e_3, e_4);

	CorrectBissectriss(e_1, e_3);
	CorrectBissectriss(e_2, e_4);

	CorrectBissectriss(e_1, e_4);
}


List<EdgeEx*> *  CorrectBissectriss2(List<EdgeEx*> * edges)
{

	edges->first();
	if (edges->isHead()) return edges;			
	geometry2D::Edge* e_first = edges->val();





	geometry2D::Edge* e_1 = e_first;
	geometry2D::Edge* e_2 = NULL;

	for (edges->next(); !edges->isHead(); edges->next() )
	{
		e_2 = edges->val();

		if(e_1 && e_2)
		{
			CorrectBissectriss(e_1, e_2);
		}

		e_1 = e_2;
	}

	e_1 = e_2;
	e_2 = e_first;
	if(e_1 && e_2)
	{
		CorrectBissectriss(e_1, e_2);
	}

	return edges;
}
List<EdgeEx*> *  CorrectBissectriss3(List<EdgeEx*> * edges)
{

	edges->first();
	if (edges->isHead()) return edges;			
	geometry2D::Edge* e_first = edges->val();

	edges->next();
	if (edges->isHead()) return edges;			
	geometry2D::Edge* e_second = edges->val();

	geometry2D::Edge* e_1 = e_first;
	geometry2D::Edge* e_2 = e_second;
	geometry2D::Edge* e_3 = NULL;

	for (edges->next(); !edges->isHead(); edges->next() )
	{
		e_3 = edges->val();

		if(e_1 && e_2 && e_3)
		{
			CorrectBissectriss(e_1, e_2, e_3);
		}

		e_1 = e_2;
		e_2 = e_3;
	}

	e_1 = e_2;
	e_2 = e_3;
	e_3 = e_first;
	if(e_1 && e_2 && e_3)
	{
		CorrectBissectriss(e_1, e_2, e_3);
	}
	
	e_1 = e_2;
	e_2 = e_3;
	e_3 = e_second;
	if(e_1 && e_2 && e_3)
	{
		CorrectBissectriss(e_1, e_2, e_3);
	}
	return edges;
}

List<EdgeEx*> *  CorrectBissectriss4(List<EdgeEx*> * edges)
{

	edges->first();
	if (edges->isHead()) return edges;			
	geometry2D::Edge* e_first = edges->val();

	edges->next();
	if (edges->isHead()) return edges;			
	geometry2D::Edge* e_second = edges->val();

	edges->next();
	if (edges->isHead()) return edges;			
	geometry2D::Edge* e_third = edges->val();

	geometry2D::Edge* e_1 = e_first;
	geometry2D::Edge* e_2 = e_second;
	geometry2D::Edge* e_3 = e_third;
	geometry2D::Edge* e_4 = NULL;

	for (edges->next(); !edges->isHead(); edges->next() )
	{
		e_4 = edges->val();

		if(e_1 && e_2 && e_3 && e_4)
		{
			CorrectBissectriss(e_1, e_2, e_3, e_4);
		}

		e_1 = e_2;
		e_2 = e_3;
		e_3 = e_4;
	}

	e_1 = e_2;
	e_2 = e_3;
	e_3 = e_4;
	e_4 = e_first;
	if(e_1 && e_2 && e_3 && e_4)
	{
		CorrectBissectriss(e_1, e_2, e_3, e_4);
	}
	
	e_1 = e_2;
	e_2 = e_3;
	e_3 = e_4;
	e_4 = e_second;
	if(e_1 && e_2 && e_3 && e_4)
	{
		CorrectBissectriss(e_1, e_2, e_3, e_4);
	}

	e_1 = e_2;
	e_2 = e_3;
	e_3 = e_4;
	e_4 = e_third;
	if(e_1 && e_2 && e_3 && e_4)
	{
		CorrectBissectriss(e_1, e_2, e_3, e_4);
	}
	return edges;
}


void FilteringPolygonesEx1(List<PolygonEx*> * poly, Dictionary<EdgeEx*> * out_edges)
{
	// ������� �� ������� ������������, 
	// ������� ����� ������ ��������� ���������� 
	// �������, ��� ������������ �����
	while (true)
	{		
		int deleted = 0;
		for (poly->first(); !poly->isHead(); poly->next() )
		{
			geometry2D::PolygonEx* p = poly->val();

			double perimetr = 0.0;
			double max_len = 0.0;
			int neighbors_number = 0;

			for (int i = 0; i < p->size(); i++)
			{
				p->advance(CLOCKWISE);
				//******************************
				PolygonEx* pn = p->GetNeighborPolygon();
				//printf("pn = 0x%08x\n", pn);
				if (pn)
					neighbors_number++;
				//******************************
				Edge e = p->edge();
				Point v = e.org - e.dest;
				double len = v.length();

				perimetr += len;
				if (len > max_len) max_len = len;
				//******************************
			}/*
			printf("perimetr = %f\n", perimetr);
			printf("max_len = %f\n", max_len);
			printf("_radius = %f\n", p->_r);
			printf("neighbors_number = %d\n", neighbors_number);
*/
			if (neighbors_number == 2 && p->_r > max_len)
			{
				FilteringEdgeEx(out_edges, p);
				delete poly->remove();
				deleted++;
			}
		}	
		if (!deleted)
			break;
	}
}

struct edge_tria
{
	double len;
	bool have_neighbor;
	bool operator>(edge_tria& et)
	{
		return len > et.len;
	}
	bool operator<(edge_tria& et)
	{
		return len < et.len;
	}
};

void FilteringPolygonesEx2(List<PolygonEx*> * poly, Dictionary<EdgeEx*> * out_edges)
{
	while (true)
	{		
		int deleted = 0;
		for (poly->first(); !poly->isHead(); poly->next() )
		{
			geometry2D::PolygonEx* p = poly->val();
			if ( p->size() > 1 )
			{
				int neighbors_number = 0;

				vector<edge_tria> v_et;
				v_et.clear();

				for (int i = 0; i < p->size(); i++)
				{
					p->advance(CLOCKWISE);
					//******************************
					PolygonEx* pn = p->GetNeighborPolygon();
					//printf("pn = 0x%08x\n", pn);
					if (pn)
						neighbors_number++;
					//******************************
					Edge e = p->edge();
					Point v = e.org - e.dest;
					double len = v.length();
					edge_tria et;
					et.len = len;
					et.have_neighbor = pn != NULL;
					v_et.push_back(et);
					//******************************
				}

				std::sort(v_et.begin(), v_et.end());
				double mean_len = v_et[v_et.size()-2].len;
				double max_len = v_et[v_et.size()-1].len;

/*
				printf("perimetr = %f\n", perimetr);
				printf("max_len = %f\n", max_len);
				printf("mean_len = %f\n", mean_len);
				printf("_radius = %f\n", p->_r);
				printf("neighbors_number = %d\n", neighbors_number);
*/

                // ���� ������ ������ ������ ����������� ����� - �� ������� ����� �����������
				if (neighbors_number == 2 && !v_et[0].have_neighbor)
					continue;

                // ���� ������ ������ ������ ������� ����� - �� ������� ����� �����������
				if (neighbors_number == 2 && !v_et[1].have_neighbor)
					continue;

				if (neighbors_number == 2 && p->_r > mean_len)
				{
					FilteringEdgeEx(out_edges, p);
					delete poly->remove();
					deleted++;
				}
			}
			else
			{
				FilteringEdgeEx(out_edges, p);
				delete poly->remove();
			}

		}
		if (!deleted)
			break;
	}
}



/*
���. 4: ����������� ������������ ������. �����, �������� � ������ �������, �������� ������� ������
������������, ���������� ������������, ������������ � ������ triangles. ������� ������������ �������� frontier ����� �����. ������ ����� ����������, ��� ��� ����������� ������� ��� ���� (���������� �����������) ����� ������ �� �����. ������� ��������� edgeCmp ������������ ��� ��������� �������. � ��� ������������ ��������� ����� ���� �����, ���� ��� ����������� �������, �� ����� ������������ �� �������� �����:
*/
int edgeCmp (Edge *a, Edge *b)
{
  if (a->org < b->org) return 1;
  if (a->org > b->org) return 1;
  if (a->dest < b->dest) return -1;
  if (a->dest > b->dest) return 1;
  return 0;
}
int edgeCmpEx (EdgeEx *a, EdgeEx *b)
{
  if (a->org < b->org) return 1;
  if (a->org > b->org) return 1;
  if (a->dest < b->dest) return -1;
  if (a->dest > b->dest) return 1;
  return 0;
}

int edgeCmpExIndex (EdgeEx *a, EdgeEx *b)
{
	if (a->org.index < b->org.index) return 1;
	if (a->org.index > b->org.index) return 1;
	if (a->dest.index < b->dest.index) return -1;
	if (a->dest.index > b->dest.index) return 1;
	return 0;
}
int edgeCmpExEpsilon (EdgeEx *a, EdgeEx *b)
{
	double epsilon = 0.1;
	//if (a->org < b->org) return 1;
	if (a->org.LessThan(b->org, epsilon)) return 1;
	//if (a->org > b->org) return 1;    
	if (a->org.MoreThan(b->org, epsilon)) return 1;
	//if (a->dest < b->dest) return -1;
	if (a->dest.LessThan(b->dest, epsilon)) return -1;
	//if (a->dest > b->dest) return 1;
	if (a->dest.MoreThan(b->dest, epsilon)) return 1;
	return 0;
}
/*
int Point::operator< (Point &p)
{
  return ((x < p.x) || ((x == p.x) && (y<p.y)));
}

int Point::operator> (Point &p)
{
  return ((x>p.x) || ((x == p.x) && (y > p.y)));
}
*/
/*
��� �� ���������� ������� �� ������ ���� � ������� � ��� ������� updateFrontier �������� ������� ����� ������� ��� ��������� ���� ���������? ��� ������������� � ������� ������ ������������ t ���������� ��������� ���� ����� ������������. ����� ������������ t, ����������� � �������, �� ������ ���������� �������. ������� updateFrontier ����� ������������ ��� �����, ��������� ��� ��� ������ ���� ������� �� ������� ��� ��������� � ������� removeMin. ������ �� ���� ���������� ����� ������������ t �������� ���� ��������� �� ������� �� �����, ���� ��� ��� ����� �� ���� �������� � �������, ��� �� ������ � �������, ���� ����� ��� ��������� � �������. �� ���. 5 �������� ��� ������. � ������������ � �������� �� ������������ ����� ����� af �, ����� �����������, ��� ����� b �������� ����������� ���, ��������� ����������� afb � ������� ������������. ����� ���� ����� fb � ������� �, ��������� ��� ��� ��� ��� � ��� ���������� �������, ��� ��������� ���������� �� ������� � ������. ��� �������������� ������� �� �������� ����� fb ���, ����� ����������� � ���� ����������� ������� ������ ������ �� ���� � ������� ��� ����� � �������. ����� ������ � ������� ����� ba � ��������� ��� ���� � ���, �� ��� ��� ����� (��������� ����������� � ���� ������� � ����������� abc). ��� ��� ����������� ��� ���� �������, ����������� afb, ������ ��� ���� ����������, ��� ����� ��������� �� �������.

������� updateFrontier ����������� ������� frontier, � ������� ���������� ��������� ����� �� ����� � � ����� b:


���. 5: ����������� ������������ afb � ������ ����� �t
*/
void updateFrontier (Dictionary<Edge*> &frontier, Point &a, Point &b)
{
	if (a != b)
	{
		Edge *e = new Edge (a, b);
		if (frontier.find (e))
		{
			frontier.remove(e);
			delete e;
		}
		else 
		{
			e->flip();
			frontier.insert(e);
		}
	}
}
void updateFrontier (Dictionary<EdgeEx*> &frontier, Point &a, Point &b, PolygonEx * tria, Dictionary<EdgeEx*> * out_edges)
{
	if (a != b)
	{
		EdgeEx *e = new EdgeEx (a, b);
		EdgeEx * ex = frontier.find (e);
		if (ex)
		{
			frontier.remove(e);
			// ���� �� ������� ����� �� �������,
			// �� ���������������� ����� ����� ������������� ������������
			// ��� ��������� �� ������ ������ ���������� �����
			tria->SetNeighborPolygon(ex, ex->LeftPolygon());
			// � ��������
			if (ex->LeftPolygon())
				ex->LeftPolygon()->SetNeighborPolygon(ex, tria);

			ex->RightPolygon(tria);
			if (out_edges)
			{
				out_edges->insert(ex);
			}
			else
			{
				delete ex;
			}
			delete e;
		}
		else 
		{
			e->flip();
			//���� �� ��������� ����� � ������� 
			//�� � ������ ������ ����������� ��������� 
			//�� ����� ������������ �������-�����������
			e->LeftPolygon(tria);
			frontier.insert(e);
		}
	}
}
/*
������� hullEdge ������������ ����� �������� ����� � ����� ������� s. � ���� ������� ���������� ����������� ���� ������������� � ������ �������� ������ ������������� �������:
*/
template <class T>
void swap(T & p1, T & p2)
{
	T p = p1;
	p1 = p2;
	p2 = p;
}
Edge *hullEdge (std::vector<geometry2D::Point>& s )
{
	int i, n = s.size();
  int m = 0;
  for (i = 1; i < n; i++)
    if (s[i] < s[m])
      m = i;
  swap<Point>(s[0], s[m]);
  for (m = 1, i = 2; i < n; i++) 
  {
	  int c = s[i].classify (s[0], s[m]);
	  if ( (c  ==  LEFT) || (c  == BETWEEN) )
		  m = i;
  }
  return new Edge(s[0], s[m] );
}

Edge *hullEdge (Point s[], int n)
{
  int i, m = 0;
  for (i = 1; i < n; i++)
    if (s[i] < s[m])
      m = i;
  swap<Point>(s[0], s[m]);
  for (m = 1, i = 2; i < n; i++) 
  {
	  int c = s[i].classify (s[0], s[m]);
	  if ( (c  ==  LEFT) || (c  == BETWEEN) )
		  m = i;
  }
  return new Edge(s[0], s[m] );
}
/*
������� triangle ������ ��������� � ���������� ������� ��� ���� �����, ������������ �� � �������� ����������:
*/
PolygonEx * triangleEx(Point &a, Point &b, Point &c)
{
  PolygonEx *t = new PolygonEx;
  t->insert (a);
  t->insert (b);
  t->insert (c);
  return t;
}

Polygon * triangle(Point &a, Point &b, Point &c)
{
  Polygon *t = new Polygon;
  t->insert (a);
  t->insert (b);
  t->insert (c);
  return t;
}

 /*

  ����� ����������� ����� ��� ����� 

 

 

������� �������� �� ������, �������� �������� mate, ������� ����������, ���������� �� ��� ������� ������ ����� ����������� ����� �, ���� ��� ����, ������� ��. ���������� �����������: ����� ����� ab ���������� ����������� ��������� �����������, ���������� ����� ��� �������� ����� � � b. ��������� ��� ��������� ����������� ����� � (�, b) (���. 6).


���. 6: ������ ���������� �� ��������� �(�,b), ������������� ������ �b � �� ��������������� ��������
������ ����������� ��������� � (�, b) ����� �� ������ �����, ���������������� ������� ab � ���������� ����� ��� �����, � ��� ��� ����� ���������� ����������� ����������� � ������� �� ���� ��������������. ��� ������������ ����������� ��������� ������������� ������������� � �������� ������ ���������� ��������������� �������� ��������� �� ������. ��������, ��������� � ������� � ���������� �������������� ������, ��������� ���������� ������������ ��������������: ����� ab �������������� ������ ����� ������� ����� �� 90 �������� �� ���������� � ��������������� � ����� ����� ������������ ��������������� �������� ����� ����� ����� �����. �� ���. 6 ������������ ������ �r ��� ����������� ����������, ��������������� ���������������� �������� r.

��� �� ����� ����������� ����� ��� ���������� ������ ����� ab ����� ��������� ����� ������ S? �����������, ��� ���������� �r �������� ��������� ����������� ��� ��������� ������� ����� ab (�� ���. 7 ����� ��������� �������� ����� ����������� abc). ���� ��������� ������� ��� ����� ab �������� ��������������, �� r = -�� � �r ������������ ����� �������������, ������� ����� �� ab. ��� ����� ����� ����� ���������� �������� t > r, ����� ��������� ����� �� ������ S (�������� �� ����� � � b), ������������ �������c�� �t. ���� �� ���������� ������ �������� t, �� ����� ab �� ����� ����������� �����. ����� ������� ��� ������������� ��������� ����������� ������, ������������ � ������� ab. ���� ����� ������ ��������� ��������� ����� �� ������ S, �� ��� ����� �������� ����������� ������� ab (����� d �� ���. 7). � ��������� ������, ���� �� ���������� �� ����� ����� ����� �� S, �� ������ ������������ �� ���������� ���� ����������� ������������� ������ �� ������� ab � ����� ������� ab �� ����� ����������� �����.


���. 7: ����������� ����������� ����� (d) ��� ����� ab
������ �� �������� ����� ��������? ����� �r ���������� ��������� ���������� ��������� ������� ������� ab � Ct � ��������� ���������� ����������� ������� ������� ab. ����� t > r � t = oo, ���� ������� ab �� ����� ����������� �����. ����� �� ���������� Ct ��������� �� �����, ��� ��� �����? ����� �� ������� ab ���������� Ct ������ ���� ��������� �� �����, ��������� �r �������� �� �����, � ����� Ct, ������� ����� �� ����� ab, �������� ������ �r. ������ �� ����� ab Ct ����� ������ ���� �������� �� �����, ��������� ���� �� ��������� ����� q ������ �� ������ ���� ����������, �� ��� �� ������������ ���������� Cs �� C(a,b), ��� r < s < t, ��� ������������� �� ������ ������ t. � ����� �������� � ������� ������������� ������ ������ �� ����� q �� ����, ��� �� ������ ����������� ����� ����� ab.

��� ������ ����������� ����� ��� ����� ab �� ����� ������������� ������ �� ����� � �� S, ������� ����� ������ �� �b. ����� ����������, ��������� ������ ����� ���� ����� �, b, � �, ����� �� ����������� ���������������, ����������� ����� �������� �������� ab � b�. (����� ������������ ��� ����, ��� �������������� � ��������� ����� ������������� ������������ � ������ ��������� ���������� ������������.) ������ ���������� ��������� ������ ���������� �� ����� ��������� ��� ��������������� �������� ����� �������������� � �������� ����� �b. ����� ������� �� ����� ����������� ����� ����������� ���������������� ��������.

��� �������� ����������� � ������� mate, ������� ���������� �������� TRUE, ���� ����� � ����� ����������� �����, � FALSE, ���� ����� ����� ���. ���� ����������� ����� ����������, �� ��� ������������ ����� ��������� �������� �: 
*/
bool mate (Edge &e, Point s[], int n, Point  &p, double& r)
{
	
	if (e.org == e.dest)
		return FALSE;
		

  Point *bestp = NULL;
  double  t, bestt = DBL_MAX;
  r = DBL_MAX;
  Edge  f = e;
  f.rot();      // f - ������������� � �������� ������� �
  for (int i = 0; i < n; i++)
    if (s[i].classify(e) == RIGHT) {
		//printf("s[%d](x=%0.1e,y=%0.1e).classify(e(e.org(x=%0.1e,y=%0.1e).dest(x=%0.1e,y=%0.1e))\n",
		//	i, s[i].x, s[i].y, e.org.x, e.org.y, e.dest.x, e.dest.y);
      Edge g(e.dest, s[i]);
      g.rot();
      if (f.intersect (g, t) == SKEW)
	  {
		  if (t < bestt) {
			  bestp = &s[i];
			  bestt = t;

		  }	  
      }
    }
  if (bestp) {
    p = *bestp;	
    Point _p, v;
	_p = f.point(bestt);// ����� ��������� ����������
	v = p - _p; //������ ������
	r = v.length(); // ������ ��������� ����������
    return TRUE;
  }
return FALSE;
}
bool mate (Edge &e, std::vector<geometry2D::Point>& s, Point  &p, double& r)
{

	int n = s.size();
	
	if (e.org == e.dest)
		return FALSE;
		

  Point *bestp = NULL;
  double  t, bestt = DBL_MAX;
  r = DBL_MAX;
  Edge  f = e;
  f.rot();      // f - ������������� � �������� ������� �
  for (int i = 0; i < n; i++)
    if (s[i].classify(e) == RIGHT) {
		//printf("s[%d](x=%0.1e,y=%0.1e).classify(e(e.org(x=%0.1e,y=%0.1e).dest(x=%0.1e,y=%0.1e))\n",
		//	i, s[i].x, s[i].y, e.org.x, e.org.y, e.dest.x, e.dest.y);
      Edge g(e.dest, s[i]);
      g.rot();
      if (f.intersect (g, t) == SKEW)
	  {
		  if (t < bestt) {
			  bestp = &s[i];
			  bestt = t;

		  }	  
      }
    }
  if (bestp) {
    p = *bestp;	
    Point _p, v;
	_p = f.point(bestt);// ����� ��������� ����������
	v = p - _p; //������ ������
	r = v.length(); // ������ ��������� ����������
    return TRUE;
  }
return FALSE;
}
/*
� ������� mate ���������� bestp ��������� �� ����� ������ �����, ��������� � ������� �������, � � ���������� bestt �������� ��������������� �������� ��� ����������, ������� �������� ����� ��� �����. ��������, ��� ��� ���� ������������� ������ �� �����, ��� ����� ������ �� ����� �.

���� �������� ��� ���������� ������������ ������ �� ������ �� n ����� ����������� �� ����� �(n2), ��������� ��� ������ �������� �� ������� ����������� ���� �����. ��������� ������ ����� ����������� �� ������� ����� ������� � ������ ����� ��������� � ������� ������� � ����� ����������� �� ���, ������� �� ����������� � ����� �������� ����� ����� ����� � ������������ ������. �������� ������� � ������������ ����� ����� ����� ������������ �������� �� �����, ��� �(n) �����, ������� �������� ��������� �(n) ��������. ��������� �� ������ �������� �������� ����� �(n), �� ��������� �������� ����������� �� ����� �(n2). 
*/
} // namespace

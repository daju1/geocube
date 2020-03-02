#include "StdAfx.h"
#include "./List.h"
#include "./Vertex.h"
#include "./Edge.h"
#include "./Polygon.h"
#include "./PolygonEx.h"

#include "./delaunay.h"
#include <float.h>



namespace geometry2D
{
	/*
Инкрементальный алгоритм построения триангуляции Делоне  

По книге Ласло,
"Вычислительная геометрия и компьютерная графика на С++"
 
  Определение триангуляции Делоне  

Триангуляция для конечного набора точек S 
является задачей триангуляции выпуклой оболочки CH(S), 
охватывающей все точки набора S. Отрезки прямых линий 
при триангуляции не могут пересекаться — они могут 
только встречаться в общих точках, принадлежащих 
набору S. Поскольку отрезки прямых линий замыкают 
треугольники, мы будем считать их ребрами. На рис. 1 
показаны два различных варианта триангуляции для 
одного и того же набора точек (временно проигнорируем 
окружности, проведенные на этих рисунках).


Рис. 1: Два различных варианта триангуляции 
мя одного набора точек
Для данного набора точек S мы можем видеть, 
что все точки из набора S могут быть подразделены 
на граничные точки — те точки, которые лежат на 
границе выпуклой оболочки CH(S), и внутренние точки — 
лежащие внутри выпуклой оболочки CH(S). Также можно 
классифицировать и ребра, полученные в результате 
триангуляции S, как ребра оболочки и внутренние ребра. 
К ребрам оболочки относятся ребра, расположенные вдоль 
границы выпуклой оболочки CH(S), а к внутренним ребрам — 
все остальные ребра, образующие сеть треугольников внутри 
выпуклой оболочки. Отметим, что каждое ребро оболочки 
соединяет две соседние граничные точки, тогда как 
внутренние ребра могут соединять две точки любого типа. 
В частности, если внутреннее ребро соединяет две граничные 
точки, то оно является хордой выпуклой оболочки CH(S). 
Заметим также, что каждое ребро триангуляции является 
границей двух областей: каждое внутреннее ребро находится 
между двумя треугольниками, а каждое ребро оболочки — 
между треугольником и бесконечной плоскостью.

Любой набор точек, за исключением некоторых тривиальных 
случаев, допускает более одного способа триангуляции. 
Но при этом существует замечательное свойство: любой 
способ триангуляции для данного набора определяет 
одинаковое число треугольников, что следует из теоремы:

Теорема о триангуляции набора точек. Предположим, 
что набор точек S содержит n>3 точек и не все из 
них коллинеарны. Кроме того, i точек из них являются 
внутренними (т. е. лежащими внутри выпуклой оболочки CH(S). 
Тогда при любом способе триангуляции набора S будет получено 
точно n + i - 2 треугольников.

Для доказательства теоремы рассмотрим сначала 
триангуляцию n-i граничных точек. Поскольку все 
они являются вершинами выпуклого полигона, то при 
такой триангуляции будет получено (n - i) - 2 
треугольников. (В этом нетрудно удостовериться 
и, более того, можно показать, что любая триангуляция 
произвольного m-стороннего полигона - выпуклого или 
невыпуклого — содержит m - 2 треугольника). Теперь 
проверим, что будет происходить с триангуляцией при 
добавлении оставшихся i внутренних точек, каждый 
раз по одной. Мы утверждаем, что добавление каждой 
такой точки приводит к увеличению числа треугольников 
на два. При добавлении внутренней точки могут возникнуть 
две ситуации, показанные на рис. 2. Во-первых, точка 
может оказаться внутри некоторого треугольника и тогда 
такой треугольник заменяется тремя новыми треугольниками. 
Во-вторых, если точка совпадает с одним из ребер триангуляции, 
то каждый из двух треугольников, примыкающих к этому ребру, 
заменяется двумя новыми треугольниками. Из этого следует, 
что после добавления всех г точек, общее число треугольников 
составит (n - i - 2) + (2i), или просто n + i - 2.


Рис. 2: Две ситуации, возникающие при триангуляции после
добавления новой внутренней точки
В этом разделе мы представим алгоритм формирования 
специального вида триангуляции, известный как триангуляция Делоне. 
Эта триангуляция хорошо сбалансирована в том смысле, что 
формируемые треугольники стремятся к равноугольности. Так 
например, триангуляцию, изображенную на рис. 1а, можно 
отнести к типу триангуляции Делоне, а на рис. 1б 
триангуляция содержит несколько сильно вытянутых 
треугольников и ее нельзя отнести к типу Делоне. 
На рис. 3 показан пример триангуляции Делоне для 
набора большого числа точек.


Рис. 3: Триангуляция Делоне для 250 точек, выбранных 
случайным образом в пределах прямоугольника. Всего 
образовано 484 треугольника
Для формирования триангуляции Делоне нам потребуется 
несколько новых определений. Набор точек считается 
круговым, если существует некоторая окружность, на 
которой лежат все точки набора. Такая окружность будет 
описанной для данного набора точек. Описанная окружность 
для треугольника проходит через все три ее (не коллинеарные) 
вершины. Говорят, что окружность будет свободной от точек 
в отношении к заданному набору гочек S, если внутри окружности 
нет ни одной точки из набора S. Но, однако, точки из набора 
S могут располагаться на самой свободной от точек окружности.

Триангуляция набора точек S будет триангуляцией Делоне, 
если описанная окружность для каждого треугольника будет 
свободна от точек. На схеме триангуляции рис. 1а показаны 
две окружности, которые явно не содержат внутри себя других 
точек (можно провести окружности и для других треугольников, 
чтобы убедиться, что они также свободны от точек набора). 
Это правило не соблюдается на схеме рис. 16 — внутрь 
проведеной окружности попала одна точка другого треугольника, 
следовательно, эта гриангуляция не относится к типу Делоне.

Можно сделать два предположения относительно точек в наборе S, 
чтобы упростить алгоритм триангуляции. Во-первых, чтобы вообще 
существовала триангуляция, мы должны полагать, что набор S 
содержит по крайней мере три точки и они не коллинеарны. 
Во-вторых, для уникальности триангуляции Делоне необходимо, 
чтобы никакие четыре точки из набора S не лежали на одной 
описанной окружности. Легко видеть, что без такого предположения 
гриангуляция Делоне не будет уникальной, ибо 4 точки на одной 
описанной окружности позволяют реализовать две различные 
триангуляции Делоне.

Наш алгоритм работает путем постоянного наращивания текущей 
триангуляции по одному треугольнику за один шаг. Вначале 
текущая триангуляция состоит из единственного ребра оболочки, 
по окончании работы алгоритма текущая триангуляция становится 
триангуляцией Делоне. На каждой итерации алгоритм ищет новый 
треугольник, который подключается к границе текущей триангуляции.

Определение границы зависит от следующей схемы классификации 
ребер триангуляции Делоне относительно текущей триангуляции. 
Каждое ребро может быть спящим, живым или мертвым:

спящие ребра: ребро триангуляции Делоне является спящим, если 
она еще не было обнаружено алгоритмом; 
живые ребра: ребро живое, если оно обнаружено, но известна только 
одна примыкающая к нему область; 
мертвые ребра: ребро считается мертвым, если оно обнаружено и 
известны обе примыкающие к нему области. 
Вначале живым является единственное ребро, принадлежащее выпуклой 
i лочке — к нему примыкает неограниченная плоскость, а все 
остальные ребра спящие. По мере работы алгоритма ребра из 
спящих становятся живыми, затем мертвыми. Граница на каждом 
этапе состоит из набора живых ребер.

На каждой итерации выбирается любое одно из ребер е границы 
и оно подвергается обработке, заключающейся в поиске неизвестной 
области, ко торой принадлежит ребро е. Если эта область окажется 
треугольником f, определяемым концевыми точками ребра е и некоторой 
третьей вершинов v, то ребро е становится мертвым, поскольку теперь
известны обе примыкающие к нему области. Каждое из двух других ребер 
треугольника t переводятся в следующее состояние: из спящего в живое 
или из живого в мертвое. Здесь вершина v будет называться сопряженной 
с ребром е. противном случае, если неизвестная область оказывается 
бесконечной плоскостью, то ребро е просто умирает. В этом случае ребро 
е не имеет сопряженной вершины.

На рис. 4 показана работа алгоритма, где действие происходит сверху 
вниз и слава направо. Граница на каждом этапе выделена толстой линией.

Алгоритм реализован в программе delaunayTriangulate. Программе 
задается массив s из n точек и она возвращает список треугольников,
представляющих триангуляцию Делоне. Реализация использует класс 
кольцевого списка и классы из раздела структуры геометрических данных. 
В качестве класса Dictionary можно использовать любой словарь,
поддерживающий требуемые операции. Например, можно переопределить
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
	// здесь мы попытаемся символьно нарисовать указатели на полигоны
	if (true)
	{
		if(e->LeftPolygon())
		{
			Edge f(e->org, e->dest);
			f.flip();f.rot();//против часовой стрелки на 90 градусов

			fprintf(bln, "%d,%d\n", 2, 0);				
			fprintf(bln, "%f,%f\n", f.point(0.5).x,  f.point(0.5).y );
			fprintf(bln, "%f,%f\n", f.point(0.52).x, f.point(0.52).y);
		}
		if(e->RightPolygon())
		{
			Edge f(e->org, e->dest);
			f.rot();//по часовой стрелки на 90 градусов

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

          tria->SetNeighborPolygon(*ex, ex->LeftPolygon());
		  if (ex->LeftPolygon())
              ex->LeftPolygon()->SetNeighborPolygon(*ex, tria);
		  
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

          tria->SetNeighborPolygon(*ex, ex->LeftPolygon());
		  if (ex->LeftPolygon())
              ex->LeftPolygon()->SetNeighborPolygon(*ex, tria);
		  
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
					// ребро не было найдено быстрым алгоритмом 
					// из-за несовершенности функции сравнения
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
	// здесь мы удаляем все треугольники, которые имеют вершину с индексом -1
	// по алгоритму Григорича
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

	//Площадь плошадки
	double S = fabs((max_x-min_x)*(max_y-min_y));

	//средняя плотность точек
	double plotnost_t = double(len) / S;

	//матожидание расстояния между каждой точкой и ближайшей к ней соседней
	double delta_ma = 0.5 / sqrt(plotnost_t);

	//оконтуриваем против часовой стрелки

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
	// ищем первый попавшийся крайний полигон
	bool krajnij_found = false;
	geometry2D::PolygonEx* krajnij_first = NULL;
	for (poly->first(); !poly->isHead(); poly->next() )
	{
		geometry2D::PolygonEx* p = poly->val();
		geometry2D::Vertex* _v = p->v();//запоминаем начальную вершину

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

	// находим точку пересечения биссектрис треугольника
	
	bool pt_intersect_calculed = false;

	List<Edge*> * edges_biss = new List<Edge*>;

	int i = 0;
	if (i < p->size())
	{		
        Edge e_1 = p->edge();	p->advance(CLOCKWISE); i++;
		if (i < p->size())
		{
            Edge e_2 = p->edge();	p->advance(CLOCKWISE); i++;
            AppendBissectriss(edges_biss, &e_1, &e_2, 1.0);
			if (i < p->size())
			{
                Edge e_3 = p->edge();	p->advance(CLOCKWISE); i++;
                AppendBissectriss(edges_biss, &e_2, &e_3, 1.0);
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
	// ищем первый попавшийся крайний полигон
	bool krajnij_found = false;
	geometry2D::PolygonEx* krajnij_first = NULL;
	for (poly->first(); !poly->isHead(); poly->next() )
	{
		geometry2D::PolygonEx* p = poly->val();
		geometry2D::Vertex* _v = p->v();//запоминаем начальную вершину

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

	geometry2D::PolygonEx* p = krajnij_first;//инициализируем текущий полигон

	while(true)
	{ 
		geometry2D::Vertex* _v = p->v();//запоминаем начальную вершину

		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			//******************************
			PolygonEx* pn = p->GetNeighborPolygon();
			if (!pn)
			{	
				break;
				//выходим из цикла for если мы достигли внешнего ребра
			}
			//******************************
		}
		//крутим назад пока не найдём первое внутренне ребро - предшественник внешнего
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
			//тут экстренная ситуация - мы имеем дело с полигоном без соседей
			//!!!!!!!!!!!!!!!!!!!!!!!
			for (int i = 0; i < p->size(); i++)
			{
				p->advance(CLOCKWISE);
				//******************************
				EdgeEx *e = new EdgeEx(p->edge());
				e->RightPolygon(p);
				edges->append(e);
			}
			MessageBox(0,"тут экстренная ситуация - мы имеем дело с полигоном без соседей", "Warning GetContourOfPolygonesEx2", MB_OK);
			return edges;
		}
		// на один шаг вперёд 
		p->advance(CLOCKWISE);
		// и мы на первом внешнем ребре 
		// (у внешнего треугольника могут быть как одно так и два внешних ребра)
		if(p->GetNeighborPolygon())
		{
			//тут ошибка
			//!!!!!!!!!!!!!!!!!!!!!!!
			MessageBox(0,"Error", "GetContourOfPolygonesEx2", MB_OK);
			return edges;
		}
		// берём это ребро складываем в список
		EdgeEx *e = new EdgeEx(p->edge());
		e->RightPolygon(p);
		edges->append(e);
		// на один шаг вперёд - по часовой стрелке
		p->advance(CLOCKWISE);
		// если второе ребро тоже внешнее, 
		// тогда его тоже складываем в список 
		// и опять делаем шаг вперёд
		if(!p->GetNeighborPolygon())
		{
			EdgeEx *e = new EdgeEx(p->edge());
			e->RightPolygon(p);
			edges->append(e);
			// на один шаг вперёд - по часовой стрелке
			p->advance(CLOCKWISE);
		}
		// теперь мы должны попасть на соседа
		PolygonEx* pn = p->GetNeighborPolygon();


		if(!pn)
		{
			//тут ошибка
			//!!!!!!!!!!!!!!!!!!!!!!!
			MessageBox(0,"Error 2", "GetContourOfPolygonesEx2", MB_OK);
			return edges;
		}


		//цикл поиска соседнего внешнего треугольника 
		while(true)
		{  
			geometry2D::Vertex* _vn = pn->v();//запоминаем начальную вершину
			bool vertex_found = false;
			//у соседа ищем вершину, которая по координатам соотвертсвует текущей вершине предыдущего полигона
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
				//тут ошибка
				//!!!!!!!!!!!!!!!!!!!!!!!
				MessageBox(0,"Error 3", "GetContourOfPolygonesEx2", MB_OK);
				return edges;
			}
			//поиск границы
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
				//соседний внешний треугольник найден
				p = pn;
				break;
			}
			else
			{
				// продолжаем поиск соседнего снешнего треугольника
				pn = pn->GetNeighborPolygon();
			}
		}

		if (p == krajnij_first)
		{
			//УРА!!!!!
			//конец алгоритма
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
			// готовим экстраполяционный полигон
			p->insert(b1->dest);
			p->insert(ex->org);
			p->insert(ex->dest);
			p->insert(b2->dest);

            // ребру контура присваиваем указатель на созданный экстраполяционный полигон
			ex->LeftPolygon(p);
			// соответствующему полигону также даём указатель на созданный экстраполяционный полигон
			if (ex->RightPolygon())
                ex->RightPolygon()->SetNeighborPolygon(*ex, p);

            p->SetNeighborPolygon(*ex, ex->RightPolygon());
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

			// биссектрисам присваиваем указатели на только что образованный полигон
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
	// удаляем те внешние треугольники, 
	// которые имеют радиус описанной окружности 
	// больший, чем максимальное ребро
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

                // если наружу торчит только минимальная грань - не удаляем такой треугольник
				if (neighbors_number == 2 && !v_et[0].have_neighbor)
					continue;

                // если наружу торчит только средняя грань - не удаляем такой треугольник
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
Рис. 4: Наращивание триангуляции Делоне. Ребра, входящие в состав границы, выделены толстой линией
Треугольники, образующие триангуляцию, записываются в список triangles. Граница представлена словарем frontier живых ребер. Каждое ребро направлено, так что неизвестная область для него (подлежащая определению) лежит справа от ребра. Функция сравнения edgeCmp используется для просмотра словаря. В ней сравниваются начальные точки двух ребер, если они оказываются равными, то потом сравниваются их концевые точки:
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
Как же изменяется граница от одного шага к другому и как функция updateFrontier изменяет словарь ребер границы для отражения этих изменений? При подсоединении к границе нового треугольника t изменяются состояния трех ребер треугольника. Ребро треугольника t, примыкающее к границе, из живого становится мертвым. Функция updateFrontier может игнорировать это ребро, поскольку оно уже должно быть удалено из словаря при обращении к функции removeMin. Каждое из двух оставшихся ребер треугольника t изменяют свое состояние из спящего на живое, если они уже ранее не были записаны в словарь, или из живого в мертвое, если ребро уже находится в словаре. На рис. 5 показаны оба случая. В соответствии с рисунком мы обрабатываем живое ребро af и, после обнаружения, что точка b является сопряженной ему, добавляем треугольник afb к текущей триангуляции. Затем ищем ребро fb в словаре и, поскольку его там еще нет и оно обнаружено впервые, его состояние изменяется от спящего к живому. Для редактирования словаря мы повернем ребро fb так, чтобы примыкающая к нему неизвестная область лежала справа от него и запишем это ребро в словарь. Затем отыщем в словаре ребро ba — поскольку оно есть в нем, то оно уже живое (известная примыкающая к нему область — треугольник abc). Так как неизвестная для него область, треугольник afb, только что была обнаружена, это ребро удаляется из словаря.

Функция updateFrontier редактирует словарь frontier, в котором изменяется состояние ребра из точки а в точку b:


Рис. 5: Подключение треугольника afb к живому ребру аt
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
			// если мы удаляем ребро из словаря,
			// то соответствующему ребру вновь образованного треугольника
			// даём указатель на левого соседа удаляемого ребра
            tria->SetNeighborPolygon(*ex, ex->LeftPolygon());
			// и наоборот
			if (ex->LeftPolygon())
                ex->LeftPolygon()->SetNeighborPolygon(*ex, tria);

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
			//если мы вставляем ребро в словарь 
			//то её левому соседу присваиваем указатель 
			//на вновь образованный полигон-треугольник
			e->LeftPolygon(tria);
			frontier.insert(e);
		}
	}
}
/*
Функция hullEdge обнаруживает ребро оболочки среди п точек массива s. В этой функции фактически применяется этап инициализации и первой итерации метода заворачивания подарка:
*/
template <class T>
void _swap(T & p1, T & p2)
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
  _swap<Point>(s[0], s[m]);
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
  _swap<Point>(s[0], s[m]);
  for (m = 1, i = 2; i < n; i++) 
  {
	  int c = s[i].classify (s[0], s[m]);
	  if ( (c  ==  LEFT) || (c  == BETWEEN) )
		  m = i;
  }
  return new Edge(s[0], s[m] );
}
/*
Функция triangle просто формирует и возвращает полигон для трех точек, передаваемых ей в качестве параметров:
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

  Поиск сопряженной точки для ребра 

 

 

Обратим внимание на задачу, решаемую функцией mate, которая определяет, существует ли для данного живого ребра сопряженная точка и, если она есть, находит ее. Рассмотрим определение: любое ребро ab определяет бесконечное семейство окружностей, проходящих через его концевые точки а и b. Обозначим это семейство окружностей через С (а, b) (рис. 6).


Рис. 6: Четыре окружности из семейства С(а,b), определяемого ребром аb и их параметрические значения
Центры окружностей семейства С (а, b) лежат на прямой линии, перпендикулярной отрезку ab и проходящей через его центр, и для них можно установить однозначное соотношение с точками на этом перпендикуляре. Для спецификации окружностей семейства параметризуем перпендикуляр — припишем каждой окружности параметрическое значение положения ее центра. Средства, описанные в разделе о структурах геометрических данных, позволяют определить естественную параметризацию: ребро ab поворачивается вокруг своей средней точки на 90 градусов до совпадения с перпендикуляром и затем можно использовать параметрические значения точек вдоль этого ребра. На рис. 6 используется запись Сr для обозначения окружности, соответствующей параметрическому значению r.

Как же найти сопряженную точку для некоторого живого ребра ab среди множества точек набора S? Предположим, что окружность Сr является описанной окружностью для известной области ребра ab (на рис. 7 такой известной областью будет треугольник abc). Если известная область для ребра ab является неограниченной, то r = -оо и Сr представляет собой полуплоскость, лежащую слева от ab. Нам нужно найти такое наименьшее значение t > r, чтобы некоторая точка из набора S (отличная от точек а и b), принадлежала окружноcти Сt. Если не существует такого значения t, то ребро ab не имеет сопряженной точки. Более образно это соответствует надуванию двухмерного пузыря, привязанного к отрезку ab. Если такой пузырь достигает некоторой точки из набора S, то эта точка является сопряженной отрезку ab (точка d на рис. 7). В противном случае, если не встретится ни одной такой точки из S, то пузырь разрастается до заполнения всей бесконечной полуплоскости справа от отрезка ab и тогда отрезок ab не имеет сопряженной точки.


Рис. 7: Определение сопряженной точки (d) для ребра ab
Почему же работает такой алгоритм? Пусть Сr обозначает описанную окружность известной области отрезка ab и Ct — описанную окружность неизвестной области отрезка ab. Здесь t > r и t = oo, если отрезок ab не имеет сопряженной точки. Будет ли окружность Ct свободной от точек, что нам нужно? Слева от отрезка ab окружность Ct должна быть свободной от точек, поскольку Сr свободна от точек, а часть Ct, лежащая слева от ребра ab, юходится внутри Сr. Справа от ребра ab Ct также должна быть свободна от точек, поскольку если бы некоторая точка q попала бы внутрь этой окружности, то она бы принадлежала окружности Cs из C(a,b), где r < s < t, что противоречило бы нашему выбору t. В нашей аналогии с пузырем расширяющийся пузырь достиг бы точки q до того, как он достиг сопряженной гечки ребра ab.

При поиске сопряженной точки для ребра ab мы будем рассматривать только те точки р из S, которые лежат справа от аb. Центр окружности, описанной вокруг любых трех точек а, b, и с, лежит на пересечении перпендикуляров, проведенных через середины отрезков ab и bр. (Здесь используется тот факт, что перпендикуляры в серединах ребер треугольников пересекаются в центре описанной окружности треугольника.) Вместо вычисления положения центра окружности мы будем вычислять его параметрическое значение вдоль перпендикуляра к середине ребра аb. Таким образом мы можем осуществить поиск наименьшего параметрического значения.

Эта методика реализована в функции mate, которая возвращает значение TRUE, если ребро е имеет сопряженную точку, и FALSE, если такой точки нет. Если сопряженная точка существует, то она возвращается через ссылочный параметр р: 
*/
bool mate (Edge &e, Point s[], int n, Point  &p, double& r)
{
	
	if (e.org == e.dest)
		return FALSE;
		

  Point *bestp = NULL;
  double  t, bestt = DBL_MAX;
  r = DBL_MAX;
  Edge  f = e;
  f.rot();      // f - перпендикуляр в середине отрезка е
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
	_p = f.point(bestt);// центр описанной окружности
	v = p - _p; //радиус вектор
	r = v.length(); // радиус описанной окружности
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
  f.rot();      // f - перпендикуляр в середине отрезка е
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
	_p = f.point(bestt);// центр описанной окружности
	v = p - _p; //радиус вектор
	r = v.length(); // радиус описанной окружности
    return TRUE;
  }
return FALSE;
}
/*
В функции mate переменная bestp указывает на самую лучшую точку, найденную к данному моменту, а в переменной bestt хранится параметрическое значение для окружности, которое проходит через эту точку. Напомним, что при этом анализируются только те точки, что лежат справа от ребра е.

Этот алгоритм для вычисления триангуляции Делоне по набору из n точек выполняется за время О(n2), поскольку при каждой итерации из границы исключается одно ребро. Поскольку каждое ребро исключается из границы точно однажды — каждое ребро относится к границе однажды и затем исключается из нее, никогда не возвращаясь — число итераций равно числу ребер в триангуляции Делоне. Согласно теореме о триангуляции набор точек любая триангуляция содержит не более, чем О(n) ребер, поэтому алгоритм выполняет О(n) итераций. Поскольку на каждую итерацию тратится время О(n), то полностью алгоритм выполняется за время О(n2). 
*/
} // namespace

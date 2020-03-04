#include "StdAfx.h"
#if defined (_MSC_VER) && !defined (QT_PROJECT)
#include <windows.h>
#else
#include "mywindows.h"
#endif
#include "./Polygon.h"
#include "./PolygonEx.h"
#include "./VertexEx.h"
#include "./Edge.h"
namespace geometry2D
{
	/*
Конструкторы и деструкторы
Имеется несколько конструкторов для класса Polygon. Конструктор, не имеющий аргументов, инициирует пустой полигон
*/
PolygonEx::PolygonEx(void) : 
  _v(NULL) , _size(0)
{
}
/*
Копирующий конструктор берет некоторый полигон p и с его помощью инициализирует новый полигон. Он осуществляет полную копию, дублируя связный список, в котором хранится полигон р. Окно нового полигона помещается над вершиной, соответствующей текущей вершине полигона р:
*/
PolygonEx::PolygonEx (PolygonEx &p) {
	
  _size = p._size;
  if (_size == 0)
    _v = NULL;
  else {
    _v = new VertexEx (p.point());
    for (int i = 1; i < _size; i++) {
      p.advance(CLOCKWISE);
      _v = (VertexEx*)_v->insert (new VertexEx (p.point()));
    }
    p.advance (CLOCKWISE);
    _v = (VertexEx*)_v->cw();
  }
}
/*
Третий конструктор инициализирует полигон с кольцевым двухсвязным списком вершин:
*/
PolygonEx::PolygonEx (Vertex *v)
{
	_v = (VertexEx*)v;
	resize();
}
/*
Конструктор вызывает собственную компонентную функцию resize для изменения значения элемента _size. В принципе, функция resize должна вызываться всегда, когда к полигону добавляется или из него удаляется цепочка вершин неизвестной длины. Эта функция определяется следующим образом:
*/
void PolygonEx::resize (void)
{
  if (_v == NULL)
    _size = 0;
  else {
    Vertex *v = _v->cw();
    for (_size = 1; v != _v; ++_size, v = v->cw());
  }
}
/*
Деструктор ~Polygon освобождает вершины текущего полигона, прежде чем удалить сам объект Polygon:
*/
PolygonEx::~PolygonEx (void)
{
	// устанавливаем для всех соседей на себя нулевой указатель
	for (int i = 0; i < this->size(); i++, this->advance(CLOCKWISE))
	{
		PolygonEx * pn = this->_v->_neighbor_polygon;
		if (pn)
		{
            const Edge edg = this->edge();
            pn->SetNeighborPolygon(edg, NULL);
		}
	}

	// а затем лишь удаляем себя
	if (_v) {
		Vertex *w = _v->cw();
		while (_v != w) {
			delete w->remove();
			w = _v->cw();
		}
		delete _v;
	}
}
/*
Функции доступа
Следующие несколько компонентных функций позволяют получить некоторые сведения о текущем полигоне. Функция v возвращает текущую вершину данного полигона, а функция size — его размер:
*/
Vertex *PolygonEx::v(void) const
{
  return _v;
}

int PolygonEx::size(void) const
{
  return _size;
}
/*
Указатель, возвращаемый функцией v, может быть использован в виде дополнительного окна для полигона как дополнение к неявному окну полигона. В некоторых применениях требуется одновременное использование нескольких окон для одного и того же полигона — единственного окна, обеспечиваемого в классе неявно, не всегда оказывается достаточно.

Компонентная функция point возвращает точку на плоскости, которая соответствует текущей вершине. Компонентная функция edge возвращает текущее ребро. Текущее ребро начинается в текущей вершине и заканчивается в следующей после нее вершине:
*/
const Point & PolygonEx::point (void) const
{
  return _v->point();
}

Edge PolygonEx::edge(void) const
{
  return Edge (this->point(), _v->cw()->point());
}
/*
Класс Edge (ребро) будет определен в следующем разделе.

Компонентные функции cw и ccw возвращают последователя и предшественника для текущей вершины, оставляя без изменения положение окна. Функция neighbor (сосед) возвращает указатель на последователя или предшественника текущей вершины в зависимости от значения аргумента, с которым она вызывается (CLOCKWISE или COUNTER_CLOCKWISE — по часовой стрелке или против):
*/
Vertex *PolygonEx::cw(void)
{
  return _v->cw();
}

Vertex *PolygonEx::ccw(void)
{
  return _v->ccw();
}

Vertex *PolygonEx::neighbor(int rotation)
{
  return _v->neighbor(rotation);
}
/*
Функции редактирования
Компонентные функции advance и setV перемещают окно на различные вершины. Функция advance (продвинуть) перемещает окно на последователя или предшественника текущей вершины в зависимости от заданного аргумента:
*/
Vertex *PolygonEx::advance(int rotation)
{
  return _v = (VertexEx*)_v->neighbor(rotation);
}
/*
Компонентная функция setV перемещает окно на вершину v, указанную в качестве аргумента:
*/
Vertex *PolygonEx::setV(Vertex *v)
{
  return _v = (VertexEx*)v;
}
/*
В программе должно быть обеспечено, чтобы вершина - v принадлежала текущему полигону.

Компонентная функция insert вносит новую вершину после текущей и затем перемещает окно на новую вершину:
*/
Vertex *PolygonEx::insert(Point &p)
{
  if (_size++ == 0)
    _v = new VertexEx(p);
  else
    _v = (VertexEx*)_v->insert(new VertexEx(p));
  return _v;
}
/*
Компонентная функция remove удаляет текущую вершину. Окно перемещается на предшественника или остается неопределенным, если полигон становится пустым:
*/
void PolygonEx::remove(void)
{
  Vertex *v = _v;
  _v = (--_size == 0) ? NULL : (VertexEx*)_v->ccw();
  delete v->remove();
}
/*
Расщепление полигонов
Расщепление полигонов заключается в делении полигонов на два меньших полигона. Разрезание осуществляется по некоторой хорде. Чтобы разрезать полигон вдоль хорды ab, вначале внесем после вершины а ее дубликат, а дубликат вершины b внесем перед вершиной b (эти дубликаты назовем ар и bр). Затем произведем разделение в вершинах а и bр. Этот процесс проиллюстрирован на рис. 1.


Рис. 1: Разрезание полигона вдоль хорды ab. Текущие вершины (в окне каждого полигона) обведены кружком


Компонентная функция Polygon::split определена в терминах функции Vertex::split. Эта последняя функция разделяет полигон вдоль хорды, соединяющей текущую вершину (которая играет роль вершины а) с вершиной b. Она возвращает указатель на вершину bр, являющуюся дублем вершины b:

Vertex *Vertex::split(Vertex *b)
{	                    // занесение bр перед вершиной b
  Vertex *bр = b->ccw()->insert(new Vertex(b->point()));
  insert(new Vertex(point()));
                       // занесение ар после текущей вершины
  splice(bр);
  return bр;
}*/
/*
Компонентная функция Polygon::split разрезает текущий полигон вдоль хорды, соединяющей ее текущую вершину с вершиной b. Она возвращает указатель на новый полигон, окно которого размещено над вершиной bр, являющейся дубликатом вершины b. Положение окна над текущим полигоном не изменяется.
*/
PolygonEx *PolygonEx::split (Vertex *b)
{
  Vertex *bp = _v->split(b);
  resize();
  return new PolygonEx(bp);
}
/*
Компонентная функция Polygon::split должна использоваться с некоторой осторожностью. Если вершина b является последователем текущей вершины _v, то после выполнения операции полигон остается неизменным. Если разрезание производится вдоль диагонали, не являющейся хордой, то один или даже оба результирующих «полигона» могут оказаться взаимно пересекающимися. Если вершины b и _v принадлежат разным полигонам, то операция разделения приводит к соединению двух полигонов по двум совпадающим ребрам, которые соединяют эти две вершины.

Точки, входящие в состав выпуклого полигона
В этом и последующем подразделах будут представлены две простые программы для работы с полигонами. Программа point InConvexPolygon обсчитывает точку s и полигон р и возвращает значение TRUE только в том случае, если точка лежит внутри полигона р (в том числе и на его границе): 
*/

BOOL pointlnConvexPolygon (const Point &s, PolygonEx &p)
{
  if (p. size() == 1)
    return (s == p.point());
  if (p. size () == 2) {
    Edge e = p. edge ();
    int c = s .classify (e);
    return ( (c==BETWEEN) || (c==ORIGIN) || (c==DESTINATION) );
  }
  Vertex *org = p.v();
  for (int i = 0; i < p.size(); i++, p.advance(CLOCKWISE)) {
    Edge e = p. edge ();
    if (s.classify (e) == LEFT) {
      p.setV(org);
      return FALSE;
    }
  }
  return TRUE;
}
/*
В этой функции вначале анализируются специальные случаи на принадлежность полигона р вырожденным полигонам — 1-гону или 2-гону. В общем случае в процессе работы алгоритма обходится граница полигона, т. е. окно перемещается от вершины к соседней вершине и производится поочередный анализ взаимного положения точки s и каждого ребра. Поскольку предполагается, что полигон р выпуклый, то точка s лежит вне полигона только в том случае, если она окажется слева от какого-либо узла. Заметим, что перед выходом в программе восстанавливается первоначальное положение окна в полигоне р.

Определение наименьшей вершины в полигоне
В следующую функцию в качестве аргументов передаются полигон р и функция сравнения cmp и в ней производится поиск наименьшей вершины в полигоне р. Здесь под термином наименьшая вершина подразумевается вершина, которая меньше всех остальных при линейном упорядочении точек в смысле, задаваемом функцией cmp. Функция leastVertex перемещает окно полигона р на эту наименьшую вершину и возвращает указатель на эту вершину:
*/
Vertex *leastVertex( PolygonEx &p, int (*cmp)(Point*,Point*) )
{
  Vertex *bestV = p.v();
  p.advance(CLOCKWISE);
  for (int  i=1; i < p.size(); p.advance(CLOCKWISE), i++)
    if ((*cmp)(p.v(),bestV) < 0)
      bestV = p.v();
  p.setV(bestV);
  return bestV;
}
/*
Например, для обнаружения самой левой вершины следует обратиться к функции leastVertex со следующей функцией сравнения:

int leftToRightCmp (Point *a, Point *b)
{
  if (*a < *b) return -1;
  if (*a > *b) return 1;
  return 0;
}

Для нахождения самой правой вершины можно использовать такую функцию сравнения:

int rightToLeftCmp(Point *a, Point *b)
{
  return leftToRightCmp(b, a);
}
*/

  
void PolygonEx::SetNeighborPolygon(const Edge& e, PolygonEx* p)
{
	//printf("PolygonEx(this = %x)::SetNeighborPolygon(Edge * e = %x, PolygonEx* p = %x)\n", this, e, p);
    //if (e)
	{
		//находим соответствующее ребро
		//и присваиваем ему указателя на соседа
		for (int i = 0; i < this->size(); i++, this->advance(CLOCKWISE))
		{
			Edge ei = this->edge();

			if ( 
                (ei.org == e.org && ei.dest == e.dest)
				||
                (ei.org == e.dest && ei.dest == e.org)
				) 
			{
				this->_v->_neighbor_polygon = p;
				//printf("this->_v->_neighbor_polygon = p = %x)\n", p);
			}
		}
	}
}

PolygonEx* PolygonEx::GetNeighborPolygon()
{
	if (this->_v)
	{
		return
			this->_v->_neighbor_polygon;
	}
	return NULL;
}

} // namespace

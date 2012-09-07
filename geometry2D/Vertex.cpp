#include "StdAfx.h"
#include ".\vertex.h"

namespace geometry2D
{
	/*
Объект класса Vertex может быть сформирован на основе точки или по ее координатам х и у.
*/

Vertex::Vertex(double x, double y) : Point (x,y)
{
}

Vertex::Vertex (Point &p) :
  Point (p)
{
}
/*
Компонентные функции cw и ccw возвращают указатели на последователя и предшественника текущей вершины соответственно.
*/
Vertex *Vertex::cw(void)
{
  return (Vertex*)_next;
}

Vertex *Vertex::ccw(void)
{
  return (Vertex*)_prev;
}
/*
Компонентная функция neighbor сообщает, какой из соседей определен параметром rotation, возвращая одно из значений типа перечисления CLOCKWISE или COUNTER_CLOCKWISE
*/
Vertex *Vertex::neighbor (int rotation)
{
  return ((rotation == CLOCKWISE) ? cw() : ccw());
}
/*
Компонентная функция point возвращает точку на плоскости, в которой находится текущая вершина
*/
Point Vertex::point(void)
{
  return  *((Point*)this);
}
/*
Компонентные функции insert , remove и splice соответствуют своим аналогам, определенным в базовом классе Node.
*/
Vertex *Vertex::insert (Vertex *v)
{
  return (Vertex *) (Node::insert (v));
}

Vertex *Vertex::remove (void)
{
  return (Vertex *) (Node::remove ());
}
void Vertex::splice (Vertex *b)
{
  Node::splice (b);
}
/*
Заметим, что в функциях insert и remove перед выводом производится преобразование возвращаемых значений к типу указатель_на_Vertех. Явное преобразование необходимо здесь потому, что язык C++ не может автоматически преобразовать указатель из базового класса, чтобы указать на объект производного класса. Причина заключается в том, что компилятор языка C++ не может быть уверенным в том, что имеется объект производного класса, на который нужно указать, поскольку объект базового класса не обязательно должен быть частью объекта производного класса (но, с другой стороны, компилятор языка C++ автоматически преобразует указатель на производный класс для указания на объект базового класса, поскольку каждый объект производного класса включает внутри себя объект базового класса).

Последняя компонентная функция Vertex::split будет определена несколько ниже.
*/

Vertex * Vertex::split(Vertex* b)
{
	// занесение bр перед вершиной b
	Vertex *bp = b->ccw()->insert(new Vertex(b->point()));
	insert(new Vertex(point()));

	// занесение ар после текущей вершины
	splice(bp);
	return bp;
}
} // namespace

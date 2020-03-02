#include "StdAfx.h"
#include "Node.h"

namespace geometry2D
{
//Конструктор класса Node формирует новый узел, 
	//который имеет двойную ссылку на самого себя — 
	//новый узел представляет собой одноузловой связанный список.
/*
Node::Node (void):
_next ( this ) , _prev ( this )
{
}*/

Node::Node (void)
{
_next = this ;
_prev = this ;
}

//Внутри компонентной функции переменная this 
//автоматически указывает на принимающий объект, 
//объект, для которого инициируется компонентная функция. 
//В конструкторе переменная this указывает на объект, 
//который подлежит внесению. Соответственно при обсуждении 
//компонентных функций мы будем ссылаться на принимающий объект 
//как на текущий объект (объект с именем this). Деструктор ~Node 
//отвечает за удаление этого объекта. При описании класса он объявлен 
//виртуальным (virtual), так что удаляемый объект (объект класса, 
//полученного из класса Node) будет удален корректно:

Node::~Node (void)
{
}

/*Компонентные функции next и prev используются для 
перемещения из этого узла к последователю или предшественнику:
*/

Node *Node::next(void) 
{
  return _next;
}
Node *Node::prev(void) 
{
  return _prev;
}

/*Компонентная функция insert включает узел b сразу же 
после текущего (this) узла (рис. 1):
*/
 
//Рис. 1: Включение узла в связанный список
 

Node *Node::insert(Node *b)
{
  Node *c = _next;
  b->_next = c;
  b->_prev = this ;
  _next = b;
  c->_prev = b;
  return b;
}

/*Узел можно удалить из списка. Компонентная функция remove 
удаляет текущий узел из данного связанного списка (рис. 2). 
При этом возвращается указатель на текущий узел, так что 
впоследствии он может быть исключен:
*/
 
//Рис. 2: Удаление узла из связанного списка
 

Node *Node::remove(void)
{
  _prev->_next = _next;
  _next->_prev = _prev;
  _next = _prev = this;
  return  this;
}
/*
Компонентная функция splice используется для соединения двух узлов а и b. 
Операция соединения приводит к разным результатам, зависящим от 
принадлежности этих двух узлов к одному и тому же списку. 
Если принадлежат, то связанный список разделяется на два меньших списка. 
И наоборот, если узлы а и b принадлежат разным спискам, то оба списка 
объединяются в один более крупный список.

Для слияния двух узлов а и b мы устанавливаем ссылку из а на b->_next 
(на последователя узла b) и из b на a->_next (на последователя узла а). 
Также необходимо изменить и соответствующие ссылки на предшественника. 
Для этого для нового последователя узла а устанавливаем обратную ссылку 
на а, а для нового последователя узла b — обратную ссылку на b. 
Эта операция схематически отображена на рис. 3. Из рисунка очевидно, 
что операция соединения splice взаимно обратна: соединение узлов а и b 
на левой схеме приводит к образованию правой схемы, а повторное соединение 
узлов а и b (на правой схеме) приводит к левой схеме.

 
Рис. 3: Слияние двух узлов a и b
 

В следующей реализации компонентной функции splice текущий узел 
играет роль узла а и в качестве аргумента функции указывается 
только узел b. Переменная а введена в программу исключительно для 
отображения симметрии операции: для заданных указателей узлов а и b 
операции a->splice(b) и b->splice(a) дают одинаковый результат.
*/
void Node::splice (Node *b)
{
  Node *a = this;
  Node *an = a->_next;
  Node *bn = b->_next;
  a->_next = bn;
  b->_next = an;
  an->_prev = b;
  bn->_prev = a;
}
/*
Заметим, что в случаях, когда узел а предшествует узлу b в 
связанном списке, то операция слияния приводит к удалению узла b. 
Слияние одноузлового связанного списка b с узлом а некоторого другого 
связанного списка приводит к фактическому включению узла b после узла а. 
Это явление приводит к выводу, что операции включения узла в связанный 
список и удаления узла из связанного списка фактически являются частными 
случаями операции слияния. Но это только замечание — компонентные функции 
insert и remove предусмотрены для удобства.

И, наконец, заметим, что слияние узла с самим собой, например, 
при обращении a->splice (а), не приводит ни к каким изменениям. 
Это легко проверить по реализации функции splice
*/

} // namespace

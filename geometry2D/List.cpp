#include "StdAfx.h"

namespace geometry2D
{
	/*
����������� ListNode ����� ���� ��������� �������


template<class T> ListNode::ListNode (� val) :
   _val(val)
{
}
*/
template <class T> ListNode<T>::ListNode<T> (T val) : _val(val)
{
}
/*
����������� ListNode ������ ���������� ����������� ��� 
�������� ������ Node, ��������� ��������� ����������� 
�� ����� ����������.

�� �� ���������� ����� ����������� ������ ListNode. 
��� ������ ��������� ������ ListNode, ������������� 
������������ ���������� �������� ������ Node::~Node, 
����������� ��� �����������. �������, ��� �������, 
��������� ��������� ������ ListNode::_val �� �����������. 
���� �� ��������� ��������� ������� ������ � ��� ������, 
���� �� ���� ��������, ��� �� ������ ��� ����� (new), 
�� ��� ������� �������� ����� ��������.
*/

/*

������������ � �����������
����������� List ������� � �������������� ������ ������, 
�������������� ����� �������� �����, �� �������� 
�� ������ ����:
*/
template<class T> List<T>::List(void) : 
  _length(0)
{
  header = new ListNode<T> (NULL);
  win = header;
}
/*
���������� ������ ��������� ���� ���������� ������:
*/
template<class T> List<T>::~List (void)
{
  while (length() > 0) {
    first();
	remove ();
  }
  delete header;
}
/*
�������, ��� ���������� �� ��������� ���� �������� ������.

��������� �������
������������ ������� insert, prepend � append 
������������ ��� ��������� � ������ ����� ���������. 
�� ���� �� ���� ���� ������� �� �������� ������� ����. 
������� insert ������� ����� ������� ����� ���� � 
���������� ��������� �� ����� �������:
*/
template<class T> T List<T>::insert(T val)
{
  win->insert(new ListNode<T>(val) );
  ++_length;
  return val;
}
/*
������������ ������� prepend � append ��������� 
����� ������� � ������ ��� � ����� ������ 
�������������� � ���������� ��������� �� ����� �������:
*/
template<class T> T List<T>::prepend(T val)
{
  header->insert (new ListNode<T> (val));
  ++_length;
  return val;
}

template<class T> T List<T>::append (T val)
{
  header->prev()->insert (new ListNode<T> (val) );
  ++_length;
  return val;
}
/*
������ ������ ������������ ������� append ������������ 
��� ���������� ������ 1 � ����� �������� ������ � 
������ ������� ������ 1 ���������� ����� ���������� 
�������� �������� ������. � �������� ���������� 
������ 1 ���������� ������. ������������ ��������� 
�� ������� ������:
*/
template<class T> List<T>* List<T>::append (List<T> *l)
{
  ListNode<T> *a = (ListNode<T>*) header->prev() ;
  a->splice(l->header);
  _length += l-> _length;
  l->header->remove();
  l->_length = 0;
  l->win = header;
  return this;
}
/*
������������ ������� remove ������� �������, 
����������� � ����, ���������� ���� � ���������� 
������� � ���������� ��������� �� ������ ��� 
��������� �������. ���� ���� ��������� � �������� �������, 
�� ����� �������� �� ������������:
*/
template<class T> T List<T>::remove (void)
{
  if (win == header) return NULL;
  void *val = (void*)win->_val;
  win = (ListNode<T>*) win->prev();
  delete (ListNode<T>*) win->next()->remove();
  -- _length ;
  return (T)val;
}
/*
���� ���������� ������������ ������� val � ������ 
���������� �������� v, �� ���������� ������ ��������, 
������������ � ������� ����, �� ������� v. ���� ���� 
��������� � �������� �������, �� ������� �������� �� 
������������.
*/
template<class T> void List<T>::val (T v)
{
  if (win != header) 
    win->_val = v;
}
/*
������ � ��������� ������
���� ��������� � ������������ ������� val ���������� 
��� ����������, �� ������������ �������, ����������� 
� ����, ��� ���� NULL, ���� ���� ������������� � 
�������� �������:
*/
template<class T> T List<T>::val(void)
{
  return win->_val;
}
/*
������������ ������� next � prev ���������� ���� 
� ��������� ��� ���������� ������� ��������������. 
������ �� ��� ���������� ��������� �� �������, 
������������� � ����� ������� ����. �������, ��� 
����� List ������������ �������� "�������������". 
��������, ���� ���� ��������� � ��������� �������, 
�� ���������� �������� next ���������� ���� � 
�������� �������, ��� ���� ��������� � next 
���������� ���� � ������ �������.
*/
template<class T> T List<T>::next(void)
{
  win = (ListNode<T>*) win->next();
  return win->_val;
}

template<class T> T List<T>::prev(void)
{
  win = (ListNode<T>*) win->prev();
  return win->_val;
}
/*
������������ ������� first � last ��������� 
���� � ������ � ��������� ������� ��������������, 
��� �� ���������� ������� ��������, ���� ���� 
������. ������ �� ���� ������� ���������� ��������� 
�� �������, ���������� � ����� ��������� ����:
*/
template<class T> T List<T>::first (void)
{
  win = (ListNode<T>*) header->next();
  return win->_val;
}

template<class T> T List<T>::last (void)
{
  win = (ListNode<T>*) header->prev();
  return win->_val;
}
/*
������������ ������� length ���������� �������� ����� ������:
*/
template<class T> int List<T>::length (void)
{
  return _length;
}
/*
������������ ������� isFirst, isLast � isHead ���������� �������� TRUE (������) ������ � �������, ���� ���� ��������� � ������, ��������� ��� �������� �������� ��������������.
*/
template<class T> bool List<T>::isFirst(void)
{
  return ( (win == header->next() ) && (_length > 0) );
}

template<class T> bool List<T>::isLast (void)
{
  return ( (win == header->prev() ) && (_length > 0) );
}

template<class T> bool List<T>::isHead(void)
{
  return (win == header);
}






/*

������� �������
��� ������� ������� ������������ ������������� �������. � ������ ������� ������ ������� arrayToList ��������� n ��������� ������� � � ������ � ���������� ��������� �� ���� ������:

*/
template<class T> List<T> *arrayToList(T a[], int n)
{
  List<T> *s = new List<T>;
  for (int i = 0; i < n; i++)
    s->append(a[i]);
  return s;
}
/*
��������, ���� � ������������ ����� ������ �����, �� ��������� �������� ��������� ����������� ������ � � ������ ����� s :

char *a[20];
  .
  .
// ����� ������ ���� ��������� ������ �
  .
  .
List<char*> *s = arrayToList(a, 20);

������ ������� arrayToList �� ����� ������������ ������������ ��� ������� � ��������� ����������.

� �������� ������� ������� ���������� ������ ������� leastltem, ������� ���������� ���������� ������� � ������ s. ��� �������� ������������ � ������� ������� ���, � ���������� ������ ������� ������������ �������� -1, 0 ��� 1, ���� ������ �������� �������������� ������, ����� ��� ������ ������� ���������:
*/
template<class T> T leastItem(List<T> &s, int(*cmp) (T,T) )
{
  if (s.length() == 0)
    return NULL;
   T v = s.first();
   for (s.next(); !s.isHead(); s.next() )
     if (cmp(s.val(), v) < 0)
       v = s.val();
   return v;
}
/*
��� �����������, ����� �� ������� ����� ���������� ������ � ���������� �������, ������� ���������� � ������� leastltem � �������� ��������� strcmp. ��� ����������� ������������ ������� ����� C++, ������� ��� ��������� ���� ����� ������ �������� -1, 0 ��� 1 � ����������� �� ����, ����� �� ������ ������ ������, ����� ��� ������ ������ ������ � ���������� �������. ��������, � ���������� ������ ���������� ��������� ��������� ����� ���������� ������ ant:

List<char*> s;
s.append("bat");
s.append("ant");
s.append("cat");
cout << leastltem(s, strcmp);

* - ������� ���� ������� ������� � �� ���������������. ����� �������� - ������ algolist@manual.ru. 
*/
} // namespace
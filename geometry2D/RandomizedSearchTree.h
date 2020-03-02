#pragma once
#include "RandomizedNode.h"

namespace geometry2D
{

/*
Деревья случайного поиска представляются в виде объектов класса RandomizedSearchTree. Во многих отношениях шаблон класса напоминает класс BraidedSearchTree: элемент данных root указывает на головной узел, win представляет окно, а элемент cmp указывает на функцию сравнения деревьев.
*/
template<class T> class RandomizedSearchTree {
 private :
  RandomizedNode<T> *root;       // головной узел 
  RandomizedNode<T> *win;        // окно 
  int (*cmp) (T,T);	             // функция сравнения
  void _remove(RandomizedNode<T>*);
 public :
  //RandomizedSearchTree (int (*) (T,T) , int = -1);
  RandomizedSearchTree<T>(int (*c) (T, T), int seed = -1):cmp(c)
  {
    win = root = new RandomizedNode<T> (NULL, seed);
    root->_priority = -1.0;
  }
  ~RandomizedSearchTree (void);
  T next (void);
  T prev(void);
  void inorder (void (*) (T, void * ), void * );
  T val (void);
  bool isFirst (void);
  bool isLast (void);
  bool isHead(void);
  bool isEmpty (void);
  T find (T);
  T findMin (void);
  T locate (T);
  T insert (T);
  void remove (void);
  T remove (T);
  T removeMin (void);
};


} //namespace

#include "RandomizedSearchTree.cpp"

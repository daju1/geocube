#pragma once
#include "./Node.h"
#include "./TreeNode.h"

namespace geometry2D
{
	/*
Рис. 1: Связанное двоичное дерево поиска с головным узлом. 
Связи ленты представлены дугами
Для краткости связанное двоичное дерево 
поиска будем называть связанным деревом 
поиска, а охватывающий его связный список — лентой.

Связанное дерево поиска реализуем в виде 
класса BraidedSearchTree. Этот класс отличается 
от класса SearchTree из описания двоичных деревьев 
поиска по трем существенным признакам. Во-первых, 
объекты класса BraidedSearchTree обладают связным 
списком (лентой), который для каждого узла устанавливает 
ссылки на предшественника и последователя. Во-вторых, 
объекты класса BraidedSearchTree поддерживают окно, 
которое в любой момент времени располагается над 
каким-либо элементом в дереве. Окно служит той же 
цели, что и в классе List(используется класс Node 
из реализации кольцевого списка): существует целый 
ряд операций с окном или с элементом в окне. В-третьих, 
элемент root класса BraidedSearchTree указывает на 
головной узел — "псевдокорневой узел", правый потомок 
которого является фактическим корнем связанного дерева поиска. 
Если посмотреть на ленту, то узел, содержащий наименьший 
элемент в дереве, следует за головным узлом, а узел, 
содержащий самый большой элемент, предшествует головному 
узлу. Следовательно, головной узел соответствует головной 
позиции, которая располагается одновременно перед первой 
позицией и после последней (рис. 1).
 

  Класс BraidedNode 

 

 

Узлы связанного дерева поиска являются объектами 
класса BraidedNode. Поскольку эти узлы действуют 
одновременно как узлы дерева и как узлы списка, 
то шаблон класса BraidedNode составим на основе 
классов TreeNode и Node:
*/
template<class T>
class BraidedNode : public Node, public TreeNode<T> {
 public :
  BraidedNode<T>(T);
  BraidedNode<T> (BraidedNode<T>& n);
  BraidedNode<T> *rchild(void);
  BraidedNode<T> *lchild (void);
  BraidedNode<T> *next (void);
  BraidedNode<T> *prev(void);
  friend class BraidedSearchTree<T>;
};

 

} //namespace

#include "./BraidedNode.cpp"

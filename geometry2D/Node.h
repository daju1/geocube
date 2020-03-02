#pragma once

namespace geometry2D
{
//Узлы  

//Кольцевые списки удобны, например, в геометрии, 
	//где многоугольник хранится в виде кольцевого списка 
	//вершин в порядке обхода. Узел такого списка является 
	//объектом класса Node:

class Node {
protected:
  Node *_next;	// связь к последующему узлу
  Node *_prev;	// связь к предшествующему узлу
public:
  Node (void);
  virtual ~Node (void);
  Node *next(void);
  Node *prev(void);
  Node *insert(Node*);  // вставить узел после текущего
  Node *remove(void);  // удалить узел из списка, возвратить его указатель


  void splice(Node*);
};

 


} // namespace
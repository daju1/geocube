#pragma once

namespace geometry2D
{
//����  

//��������� ������ ������, ��������, � ���������, 
	//��� ������������� �������� � ���� ���������� ������ 
	//������ � ������� ������. ���� ������ ������ �������� 
	//�������� ������ Node:

class Node {
protected:
  Node *_next;	// ����� � ������������ ����
  Node *_prev;	// ����� � ��������������� ����
public:
  Node (void);
  virtual ~Node (void);
  Node *next(void);
  Node *prev(void);
  Node *insert(Node*);  // �������� ���� ����� ��������
  Node *remove(void);  // ������� ���� �� ������, ���������� ��� ���������


  void splice(Node*);
};

 


} // namespace
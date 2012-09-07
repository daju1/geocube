#include "StdAfx.h"

namespace geometry2D
{
/*
����������� ������ ��������� �������� ������ ���������� ������� � ������������ ���������� ���� ����� ��� ������ �������, ������ �� ������� ������������ ����� NULL:
*/
template<class T> TreeNode<T>::TreeNode<T>(T v) :
  val(v), _lchild(NULL), _rchild (NULL)
{
	/*printf("TreeNode<T>::TreeNode(void) this = 0x%08x\n", this);
	printf("TreeNode<T>::TreeNode(void) val  = 0x%08x\n", val);
	printf("TreeNode<T>::TreeNode(void) this->_lchild = 0x%08x\n", this->_lchild);
	printf("TreeNode<T>::TreeNode(void) this->_rchild = 0x%08x\n", this->_rchild);*/
}

template<class T> TreeNode<T>::TreeNode<T>(TreeNode<T>& n)
: val(n.val), _lchild(n._lchild ? new TreeNode<T>(*n._lchild) : NULL), _rchild (n._rchild ? new TreeNode<T>(*n._rchild) : NULL)
{

	/*
	printf("TreeNode<T>::TreeNode(TreeNode<T>& n) this = 0x%08x\n", this);
	printf("TreeNode<T>::TreeNode(TreeNode<T>& n) val  = 0x%08x\n", val);
	printf("TreeNode<T>::TreeNode(TreeNode<T>& n) this->_lchild = 0x%08x\n", this->_lchild);
	printf("TreeNode<T>::TreeNode(TreeNode<T>& n) this->_rchild = 0x%08x\n", this->_rchild);//*/
}
/*
template<class T> TreeNode<T>::TreeNode<T>(T v) 
{
  val = v;
  _lchild = NULL;
  _rchild = NULL;
}*/

/*
���������� ~TreeNode ���������� ������� ��� ������� �������� ���� (���� ��� ����������) ����� ������������ ������ �������� ����:
*/
template<class T> TreeNode<T>::~TreeNode(void)
{
	/*printf("TreeNode<T>::~TreeNode(void) this = 0x%08x\n", this);
	printf("TreeNode<T>::~TreeNode(void) this->_lchild = 0x%08x\n", this->_lchild);
	printf("TreeNode<T>::~TreeNode(void) this->_rchild = 0x%08x\n", this->_rchild);//*/
	if (_lchild) {delete _lchild; _lchild = NULL;}
	if (_rchild) {delete _rchild; _rchild = NULL;}
}


} // namespace
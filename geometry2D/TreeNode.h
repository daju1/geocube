#pragma once

#include <vector>
using namespace std;

void DoMyMethod(vector<double> & X,
				vector<double> & Y,
				vector<double> & signal,
				string name);

class sparse_row;
// �������� ���� � ���� ������ ��������� ��������� 
// ��� ������ ��������� ��������� 
// ( � ����������� �� �������� ����������  bool to_form_full_structure ) 
// �� ������������ ������������ ����������� �������. 
// ������ ����������� ����� � ���� ������� ����������� �����

bool Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag);

// ������ ���������� ���� ����������� � ����� �������� XADJ, ADJNCY
// ���� �� �������� ����� ��������������� � �������

bool Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values);

// �������� �������������� ����� � ����� vector<sparse_row>
// ���� �� �������� ����� ��������������� � �������

bool Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G);

// ���������� ������ ����� �������

int Get_Band_Len(vector<sparse_row> & m, vector<int> & beta);

// ���������� ������ ������ �������

int Get_Front_Width(vector<sparse_row> & m, vector<int> & omega);

// �������� ���� � ���� ������ ��������� ��������� 
// ��� ������ ��������� ��������� 
// ( � ����������� �� �������� ����������  bool to_form_full_structure ) 
// �� ������������ ������������ ����������� �������. 
// ������ ����������� ����� � ���� ������� ����������� �����

bool Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag);

// ������ ���������� ���� ����������� � ����� �������� XADJ, ADJNCY
// ���� �� �������� ����� ��������������� � �������

bool Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values);

// �������� �������������� ����� � ����� vector<sparse_row>
// ���� �� �������� ����� ��������������� � �������

bool Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G);

// ���������� ������ ����� �������

size_t Get_Band_Len(vector<sparse_row> & m, vector<size_t> & beta);

// ���������� ������ ������ �������

size_t Get_Front_Width(vector<sparse_row> & m, vector<size_t> & omega);

// �������������� ������������ ������������ ����������� ������� 
// � ����������������� ��������� ����������
// �� ���� ������� ����������������� ����� ������������ ������������ ����������� �������
// ������� ��������� �������� ������

bool Holesski(vector<sparse_row> & m);
bool Holesski3(vector<sparse_row> & m);
bool Holesski(char * fn_min_sq_mat, char * fn_Lt, char * dir);
bool Holesski3(const char * fn_min_sq_mat, const char * fn_Lt, char * dir, long j_start, double alpha);
bool Holesski3_in_operative_memory(char * fn_min_sq_mat, char * fn_Lt, char * dir, double alpha);
// 
// ������ ���� �������� ������ ����������� ������� ��������� 
// � ����������������� ���������� ����������
// 

bool tria_solve_of_down (vector<sparse_row> t,
	vector<double> b, vector<double>& x);
// 
// ������ ���� �������� ������ ����������� ������� ��������� 
// � ����������������� ���������� ����������
// 

bool tria_solve_of_up (vector<sparse_row> & t,
	vector<double>& b, vector<double>& x);


bool SLAU_excl(size_t prec_eqns,
			   vector<sparse_row > & a,
			   size_t cols, vector<double> & alpha,
			   vector<double> & b,
			   vector<double> & sol);

bool Tichonov(size_t cols, vector<sparse_row> & A,						  
						  vector<double> & b,
						  vector<double> & x, bool AlphaNonZero);
bool Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  vector<double> & valpha);

namespace geometry2D
{
	/*
��� ���������� �������� ��������, ���������� �� �������� �������������, ���� �������� ��������� ������ TreeNode.
*/
template<class T> class SearchTree;
template<class T> class BraidedSearchTree;
//template<class T> class sparse_row_element;
//class sparse_row : public template<class T> class BraidedSearchTree <T>;
//class sparse_row : public BraidedSearchTree <sparse_row_element<double> * >; 

template<class T> class TreeNode {
 protected:
  TreeNode  *_lchild;
  TreeNode  *_rchild;
  T val;
 public:
	 T Val(){return val;} // my test
  TreeNode(T);
  TreeNode(TreeNode& n);
  virtual ~TreeNode(void);
  friend class SearchTree<T>;        // ��������� ����������
  friend class BraidedSearchTree<T>; // ���������
  friend class sparse_row; // ���������

	friend void ::DoMyMethod(vector<double> & X,
				vector<double> & Y,
				vector<double> & signal,
				string name);


	// �������� ���� � ���� ������ ��������� ��������� 
	// ��� ������ ��������� ��������� 
	// ( � ����������� �� �������� ����������  bool to_form_full_structure ) 
	// �� ������������ ������������ ����������� �������. 
	// ������ ����������� ����� � ���� ������� ����������� �����

	friend bool ::Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag);

	// ������ ���������� ���� ����������� � ����� �������� XADJ, ADJNCY
	// ���� �� �������� ����� ��������������� � �������

	friend bool ::Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values);

	// �������� �������������� ����� � ����� vector<sparse_row>
	// ���� �� �������� ����� ��������������� � �������

	//friend bool ::Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G);

	// ���������� ������ ����� �������

	friend int ::Get_Band_Len(vector<sparse_row> & m, vector<int> & beta);

	// ���������� ������ ������ �������

	friend int ::Get_Front_Width(vector<sparse_row> & m, vector<int> & omega);




	// �������������� ������������ ������������ ����������� ������� 
	// � ����������������� ��������� ����������
	// �� ���� ������� ����������������� ����� ������������ ������������ ����������� �������
	// ������� ��������� �������� ������

	friend bool ::Holesski(vector<sparse_row> & m);
	friend bool ::Holesski3(vector<sparse_row> & m);
	friend bool ::Holesski(char * fn_min_sq_mat, char * fn_Lt, char * dir);
	friend bool ::Holesski3(const char * fn_min_sq_mat, const char * fn_Lt, char * dir, long j_start, double alpha);
	friend bool ::Holesski3_in_operative_memory(char * fn_min_sq_mat, char * fn_Lt, char * dir, double alpha);

	// 
	// ������ ���� �������� ������ ����������� ������� ��������� 
	// � ����������������� ���������� ����������
	// 

	friend bool ::tria_solve_of_down (vector<sparse_row> t,
		vector<double> b, vector<double>& x);
	// 
	// ������ ���� �������� ������ ����������� ������� ��������� 
	// � ����������������� ���������� ����������
	// 

	friend bool ::tria_solve_of_up (vector<sparse_row> & t,
		vector<double>& b, vector<double>& x);



	friend bool ::SLAU_excl(size_t prec_eqns,
			   vector<sparse_row > & a,
			   size_t cols, vector<double> & alpha,
			   vector<double> & b,
			   vector<double> & sol);

	friend bool ::Tichonov(size_t cols,
		vector<sparse_row> & A,
		vector<double> & b,
		vector<double> & x,
		bool AlphaNonZero);


	friend bool ::Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  vector<double> & valpha);


};
/*
�������� ������ _lchild � _rchild ���������� ����� �������� ���� � ����� � ������ ��������� ��������������, � ������� ������ val �������� ��� �������.
*/
} // namespace

#include ".\treenode.cpp"

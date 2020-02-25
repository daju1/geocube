#ifndef SPARSE_ROW_H
#define SPARSE_ROW_H

#include "../../geometry2D/BraidedSearchTree.h"
using namespace geometry2D;

int cmpCol (sparse_row_element<double> e1, sparse_row_element<double> e2);

#define SPARSE_ROW_EX 0
#include "../../surfdoc/src/Archive.h"

//#define SparseRowDictionary RandomizedSearchTree
#define SparseRowDictionary BraidedSearchTree

class sparse_row : public SparseRowDictionary <sparse_row_element<double>  >
{
public:
#if SPARSE_ROW_EX
        int _order;
        double _weight; // вес строки при решении уравнения методом наименьших квадратов
        size_t min_col;
        size_t max_col;
#endif


        void swap(sparse_row & r)
        {
                BraidedNode<sparse_row_element<double> > * tmp_root = this->root;    // головной узел
                BraidedNode<sparse_row_element<double> > * tmp_win  = this->win;     // текущее окно
                this->root = r.root;
                this->win  = r.win;

                r.root = tmp_root;
                r.win  = tmp_win;
        }

        sparse_row() : BraidedSearchTree<sparse_row_element<double> >(cmpCol){
#if SPARSE_ROW_EX
                min_col = 0;max_col = 0;_order = 0;_weight = 1.0;
#endif
        }


        //sparse_row (sparse_row & r) : BraidedSearchTree<sparse_row_element<double> >(r){}

        sparse_row (const sparse_row & tree) : BraidedSearchTree<sparse_row_element<double> >(tree.cmp)
        {
                this->BraidedSearchTree<sparse_row_element<double> >::Init(tree);
#if SPARSE_ROW_EX
                min_col = tree.min_col;
                max_col = tree.max_col;
                _order   = tree._order;
                _weight   = tree._weight;
#endif
        }

        sparse_row& operator= (const sparse_row & tree)
        {
                if (this == &tree)
                {
                        return *this;
                }

                this->BraidedSearchTree<sparse_row_element<double> >::Init(tree);
#if SPARSE_ROW_EX
                min_col = tree.min_col;
                max_col = tree.max_col;
                _order   = tree._order;
                _weight   = tree._weight;
#endif
                return *this;
        }
#if SPARSE_ROW_EX
        void FindMinCol()
        {
                this->min_col = this->findMin().col;
        }
        void FindMaxCol()
        {
                this->max_col = this->findMax().col;
        }
#endif
        /*bool operator< (sparse_row & r)
        {
                return this->min_col < r.min_col;
        }

        bool operator> (sparse_row & r)
        {
                return this->min_col > r.min_col;
        }*/

        void multip_equal (double x)
        {
                for(this->first();!this->isHead(); this->next())
                {
                        this->win->Val().val *= x;
                }
        }

        void multip_equal (vector<double>& x)
        {
                //size_t x_size = x.size();
                for(this->first();!this->isHead(); this->next())
                {
                        //size_t c = this->val().col;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                //this->val().val *= x[this->val().col];
                                this->win->Val().val *= x[this->val().col];
                        //}
                }
        }

        double ScalarProduct(vector<double>& x)
        {
                double product = 0.0;
                //size_t x_size = x.size();
                for(this->first();!this->isHead(); this->next())
                {
                        //size_t c = this->val().col;
                        //if (c < x_size)//убрал проверку, чтобы вырубались непродуманные алгоритмы
                        //{
                                product += this->val().val * x[this->val().col];
                        //}
                }
                return product;
        }
        double Sum()
        {
                double sum = 0.0;
                for(this->first();!this->isHead(); this->next())
                {
                        sum += this->val().val;
                }
                return sum;
        }
        double SumExcludeColomn(size_t col)
        {
                double sum = 0.0;
                for(this->first();!this->isHead(); this->next())
                {
                        if (col != this->val().col)
                        {
                                sum += this->val().val;
                        }
                }
                return sum;
        }
        friend Archive& operator <<(Archive& ar, sparse_row& ob);
        friend Archive& operator >>(Archive& ar, sparse_row& ob);

        typedef BraidedNode<sparse_row_element<double> > * sparse_row_node_ptr;

        void SaveDissorted(Archive& ar)
        {
                size_t tree_size = 0;
                for(this->first();!this->isHead(); this->next())
                {
                        tree_size++;
                }


                sparse_row_node_ptr * vn = new sparse_row_node_ptr[tree_size+1];
                memset(vn,0,(tree_size+1)*sizeof(sparse_row_node_ptr));

                vn[0] = this->root->rchild();

                size_t i, i_first = 0, i_pre_last, i_last = 0;

                while (vn[i_first])
                {
                        i_pre_last = i_last;
                        for (i = i_first; i <= i_pre_last; i++)
                        {
                                sparse_row_node_ptr lf = vn[i]->lchild();
                                sparse_row_node_ptr rt = vn[i]->rchild();
                                if (lf) vn [++i_last] = lf;
                                if (rt) vn [++i_last] = rt;
                        }
                        i_first = i_pre_last+1;
                }

                long cc;
                double value;

                for (i = 0; i < tree_size; i++)
                {
                        long cc = long(vn[i]->Val().col);
                        double value = vn[i]->Val().val;
                        ar << cc;
                        ar << value;
                }

                cc = -1;
                value = 0.0;
                ar << cc;
                ar << value;

                delete [] vn;
        }

        void save_node (sparse_row_node_ptr n, Archive& ar)
        {
                if (n)
                {
                        long cc = long(n->Val().col);
                        double value = n->Val().val;
                        ar << cc;
                        ar << value;

                        save_node (n->lchild(), ar);
                        save_node (n->rchild(), ar);
                }
        }

        void SaveDissorted_recursive(Archive& ar)
        {
                sparse_row_node_ptr n = this->root->rchild();

                save_node(n, ar);

                long cc = -1;
                double value = 0.0;
                ar << cc;
                ar << value;
        }

        void InverseSortedSave(Archive& ar)
        {
                long cc;
                double value;
                for(this->last();!this->isHead(); this->prev())
                {
                        long cc = long(this->val().col);
                        double value = this->val().val;
                        ar << cc;
                        ar << value;
                }

                cc = -1;
                value = 0.0;
                ar << cc;
                ar << value;
        }
        /*
        BraidedNode<T> *n = root->rchild();
        if (_find (val, n))


        BOOL Find (size_t j)
{
  while (n) {
    int result = (*cmp) (val, n->val);
    if (result < 0)
      n = n->lchild();
    else if (result > 0)
          n = n->rchild();
        else {
      win=n;
      return TRUE;
    }
  }
  return FALSE;
}*/
};

// Return whether first element is greater than the second
bool sparse_row_greater (sparse_row& elem1, sparse_row& elem2 );


#endif // SPARSE_ROW_H


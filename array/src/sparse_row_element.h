#ifndef SPARSE_ROW_ELEMENT_H
#define SPARSE_ROW_ELEMENT_H

template <class T> class sparse_row_element
{
public:
        size_t col;
        T val;
        sparse_row_element(size_t c, T v) : col(c), val(v){}
        sparse_row_element(int ) : col(0), val(0.0){}
        //sparse_row_element(const sparse_row_element & r) : col(r.col), val(r.val){}
        virtual ~sparse_row_element(){}
};


#endif // SPARSE_ROW_ELEMENT_H


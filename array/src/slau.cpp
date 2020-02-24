#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

#define TRACE              printf

#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "StdAfx.h"
#include "slau.h"
#include "sorting.h"

class sparse_col_element
{
public:
	size_t row;
	//sparse_row_element<double> * ref;
	double val;
	//sparse_col_element(const sparse_col_element & cl) : row(cl.row), ref(cl.ref){}
	sparse_col_element & operator=(const sparse_col_element & cl)// : row(cl.row), ref(cl.ref){}
	{
		row = cl.row;  
		//ref = cl.ref;
		val = cl.val;
		return *this;
	}
	sparse_col_element(size_t r, double v) : row(r), val(v) {} 
	//sparse_col_element(size_t r, sparse_row_element<double> * rf) : row(r), ref(rf) {} 
	virtual ~sparse_col_element(){}
};
Archive& operator <<(Archive& ar, sparse_row_map& ob)
{
	long cc;
	double value;
	map<size_t, double>::iterator it = ob.begin();
	for(;it != ob.end(); it++)
	{
		long cc = long((*it).first);
		double value = (*it).second;
		ar << cc;
		ar << value;
	}

	cc = -1;
	value = 0.0;
	ar << cc;
	ar << value;

	return ar;

}
Archive& operator >>(Archive& ar, sparse_row_map& ob)
{
	//printf("Archive& operator >>(Archive& ar, sparse_row& ob)\n");
	long cc;
	double value;
	ob.clear();
	do 
	{
	//printf("do\n");
		ar >> cc;
	//printf("do %ld\n", cc);
		ar >> value;
	//printf("do %ld %f\n", cc, value);
		if (cc >= 0)
		{
			ob.put(size_t(cc), value);
		}
		else
			break;
	}
	while(true);

	return ar;
}



Archive& operator <<(Archive& ar, sparse_row& ob)
{
	long cc;
	double value;
	for(ob.first();!ob.isHead(); ob.next())
	{
		long cc = long(ob.val().col);
		double value = ob.val().val;
		ar << cc;
		ar << value;
	}

	cc = -1;
	value = 0.0;
	ar << cc;
	ar << value;

	return ar;

}
Archive& operator >>(Archive& ar, sparse_row& ob)
{
	//printf("Archive& operator >>(Archive& ar, sparse_row& ob)\n");
	long cc;
	double value;
	ob.clear();
	do 
	{
	//printf("do\n");
		ar >> cc;
	//printf("do %ld\n", cc);
		ar >> value;
	//printf("do %ld %f\n", cc, value);
		if (cc >= 0)
		{
			ob.put(size_t(cc), value);
		}
		else
			break;
	}
	while(true);

	return ar;
}


Archive& operator <<(Archive& ar, sparse_row_simple& ob)
{
	long cc;
	double value;
	vector<sparse_row_element<double> >::iterator it;
	for(it = ob.begin(); it != ob.end(); it++)
	{
		long cc = long((*it).col);
		double value = (*it).val;
		ar << cc;
		ar << value;
	}
	//признак конца записи
	cc = -1;
	value = 0.0;
	ar << cc;
	ar << value;

	return ar;

}
Archive& operator >>(Archive& ar, sparse_row_simple& ob)
{
	//printf ("Archive& operator >>(Archive& ar, sparse_row_simple& ob)\n");

	long cc;
	double value;
	ob.clear();
	do 
	{
		ar >> cc;
		ar >> value;

		//printf ("cc = %ld value = %f\t", cc, value);

		if (cc >= 0)
		{
			ob.put(size_t(cc), value);
		}
		else
			break;
	}
	while(true);

	//printf("\n");

	return ar;
}


int cmpCol (sparse_row_element<double> e1,sparse_row_element<double> e2)
{
	if(e1.col < e2.col) return -1;
	if(e1.col > e2.col) return +1;
	return 0;
}
bool sparse_row_greater ( const sparse_row& elem1, const sparse_row& elem2 )
{
	elem1.first();
	elem2.first();

	/*if (elem1.isHead() && elem2.isHead())
		return true;

	if ( elem1.val().col > elem2.val().col )
		return false;
	else
	{
		if (elem1.val().col < elem2.val().col )
			return true;
	}
	elem1.next();
	elem2.next();*/

	do
	{
		if (elem1.isHead() && elem2.isHead())
			return true;

		if ( elem1.val().col > elem2.val().col )
			return false;
		else
		{
			if (elem1.val().col < elem2.val().col )
				return true;
			else
			{
				elem1.next();
				elem2.next();
			}
		}

	}
	while(!elem1.isHead() && !elem2.isHead());


		
	return true;

}
#if SPARSE_ROW_EX
bool sparse_row_greater1 (const sparse_row& elem1, const sparse_row& elem2 )
{
	return elem1.min_col > elem2.min_col;
}
bool sparse_row_greater2 ( const sparse_row& elem1, const sparse_row& elem2 )
{
	return elem1.min_col > elem2.min_col;
}
#endif
void print_slau(vector<vector<double> >& a,
     size_t N,
     vector<double>& b, char * s)
{
	printf("print_slau (%s):\n", s);
	for(size_t r = 0; r < N; r++)
	{
		for(size_t c = 0; c < N; c++)
		{
			printf("%f ", a[r][c]);
		}			
		printf("\t%f\n", b[r]);
	}
	printf("\n");
}

void print_slau(vector<vector<double> >& a,
     vector<double>& b, char * s)
{
	printf("print_slau (%s):\n", s);
	for(size_t r = 0; r < a.size(); r++)
	{
		for(size_t c = 0; c < a[r].size(); c++)
		{
			printf("%f ", a[r][c]);
		}			
		printf("\t%f\n", b[r]);
	}
	printf("\n");
}

void print_slau(vector<vector<sparse_row_element<double> > >& a,
     vector<double>& b, char * s)
{
	printf("print_slau (%s):\n", s);
	for(size_t r = 0; r < a.size(); r++)
	{
		for(size_t q = 0; q < a[r].size(); q++)
		{
			printf("%u[%f] ", a[r][q].col, a[r][q].val);
		}			
		printf("\t%f\n", b[r]);
	}
	printf("\n");
}
void visit_print(sparse_row_element<double> *e, void * )
{
	printf("%u[%f] ", e->col, e->val);
}
void visit_print(sparse_row_element<double> e, void * )
{
	printf("%u[%f] ", e.col, e.val);
}
#if SPARSE_ROW_EX
void SaveMatrixMinMaxCol(vector<sparse_row>& M, char * dat_file)
{
	FILE * dat = fopen(dat_file, "wt");
	if(dat)
	{
		for (size_t i = 0; i < M.size(); i++)
		{
			fprintf(dat, "%d,%u,%u\n", i, M[i].min_col, M[i].max_col);
		}
		fclose(dat);
	}
}
#endif
void print_slau(vector<sparse_row>& a,
     vector<double>& b, char * s)
{
	printf("print_slau (%s):\n", s);
	for(size_t r = 0; r < a.size(); r++)
	{
		a[r].inorder(visit_print, NULL);
		printf("\t%f\n", b[r]);
	}
	printf("\n");
}

bool lesgausssolve_find_max_norm(vector<vector<double> > a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon)
{
    bool result;
    int k;
    int u;
    int m;
    int j;
    int i;
    double t;

	print_slau(a, b, "start");

    x.resize(cols);
    u = 0; // номер текущей колонки
    result = true;
    do
    {
        k = u;// текущий диагональный элемент, начиная с верхнего левого
		// движение вниз по текущему столбцу

		// пока не найдём ненулевой элемент
		// ищем максимальный по модулю элемент
		double max_abs = 0.0;

		int r = u, r_max = -1;
        while(r < rows-1)
        {
			double curr = fabs(a[r][u]);

			j = u;
			double squsum = 0.0;
			while(j < cols)
			{
				squsum += a[r][j]*a[r][j];
				j++;
			}
			if (squsum > epsilon)
			{
				curr /= sqrt(squsum);

				if (curr > max_abs) 
				{
					max_abs = curr;
					r_max = r;
				}
			}
            r++;
        }

		// если максимальный по модулю элемент больше epsilon
		if (max_abs > epsilon)
		{
			k = r_max;

			// если это не диагональный элемент
			// то придётся переставить строки местами
            if( k!=u )
            {
                m = u;
                do
                {
                    t = a[u][m];
                    a[u][m] = a[k][m];
                    a[k][m] = t;
                    m = m+1;
                }
                while(m<cols);// 
				// иначе тут же надо переставить местами элементы вектора правых частей
				t = b[u];
				b[u] = b[k];
				b[k] = t;
            }
				
			print_slau(a, b , "after perestanovka strok");
			
#if 0
			i = u;
			double a_u_u = a[u][u];
			do 
			{

				// делим всю строку на текущий диагональный элемент
				j = cols-1; // надо и элемент вектора правых частей разделить на текущий диагональный элемент
				b[i] = b[i] / a_u_u;
				do
				{
					a[i][j] = a[i][j]/a_u_u;
					j = j-1;
				}
				while(j>=u);
				i++;
			}
			while(i < rows);
#else
			// делим всю строку на текущий диагональный элемент
			j = cols-1; // иначе надо и элемент вектора правых частей разделить на текущий диагональный элемент
			b[u] = b[u] / a[u][u];
            do
            {
                a[u][j] = a[u][j]/a[u][u];
                j = j-1;
            }
            while(j>=u);
#endif
				
			print_slau(a, b, "after delenie");


            if( u+1<rows )// если найдённая строка с ненулевым элементом в текущей колонке не самая нижняя
            {
                i = u+1;// номер следующей строки (то есть строки, начиная с которой надо обнулять элементы текущей колонки)
                do
                {
                    j = u;// номер колонки - мы перебираем все колонки
					double a_i_u = a[i][u];
                    do
                    {
                        a[i][j] = a[i][j] - a_i_u*a[u][j];
                        j = j+1;
                    }
                    while(j<cols);
					// а тут надо ещё отдельно обработать вектор правых частей
					b[i] = b[i] - a_i_u*b[u];

                    i = i+1;// пререходим на строку вниз
                }
                while(i<rows);
            }


			print_slau(a, b, "after otnjatie");
        }
        else
        {
			// матрица вырождена
			// система не имеет решения
            result = false;
        }
        u = u+1;
    }
    while(u != cols && result);

    if( result )// если матрица не вырождена
    {
        i = cols-1;
        do
        {
			x[i] = b[i];
            if( i!=0 )
            {
                k = i-1;
                do
                {
                    b[k] = b[k]-a[k][i]*x[i];
                    k = k-1;
                }
                while(k>=0);
            }
            i = i-1;
        }
        while(i>=0);
    }
    return result;
}




bool lesgausssolve_find_max(vector<vector<double> > a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon)
{
    bool result;
    int k;
    int u;
    int m;
    int j;
    int i;
    double t;

	//print_slau(a, b, "start");

    x.resize(cols);
    u = 0; // номер текущей колонки
    result = true;
    do
    {
        k = u;// текущий диагональный элемент, начиная с верхнего левого
		// движение вниз по текущему столбцу

		// пока не найдём ненулевой элемент
		// ищем максимальный по модулю элемент
		double max_abs = 0.0;

		int r = u, r_max = -1;
        while(r < rows-1)
        {
			double curr = fabs(a[r][u]);

			if (curr > max_abs) 
			{
				max_abs = curr;
				r_max = r;
			}

            r++;
        }

		// если максимальный по модулю элемент больше epsilon
		if (max_abs > epsilon)
		{
			k = r_max;

			// если это не диагональный элемент
			// то придётся переставить строки местами
            if( k!=u )
            {
                m = u;
                do
                {
                    t = a[u][m];
                    a[u][m] = a[k][m];
                    a[k][m] = t;
                    m = m+1;
                }
                while(m<cols);// 
				// иначе тут же надо переставить местами элементы вектора правых частей
				t = b[u];
				b[u] = b[k];
				b[k] = t;
            }
				
			//print_slau(a, b , "after perestanovka strok");
			
#if 0
			i = u;
			double a_u_u = a[u][u];
			do 
			{

				// делим всю строку на текущий диагональный элемент
				j = cols-1; // надо и элемент вектора правых частей разделить на текущий диагональный элемент
				b[i] = b[i] / a_u_u;
				do
				{
					a[i][j] = a[i][j]/a_u_u;
					j = j-1;
				}
				while(j>=u);
				i++;
			}
			while(i < rows);
#else
			// делим всю строку на текущий диагональный элемент
			j = cols-1; // иначе надо и элемент вектора правых частей разделить на текущий диагональный элемент
			b[u] = b[u] / a[u][u];
            do
            {
                a[u][j] = a[u][j]/a[u][u];
                j = j-1;
            }
            while(j>=u);
#endif
				
			//print_slau(a, b, "after delenie");


            if( u+1<rows )// если найдённая строка с ненулевым элементом в текущей колонке не самая нижняя
            {
                i = u+1;// номер следующей строки (то есть строки, начиная с которой надо обнулять элементы текущей колонки)
                do
                {
                    j = u;// номер колонки - мы перебираем все колонки
					double a_i_u = a[i][u];
                    do
                    {
                        a[i][j] = a[i][j] - a_i_u*a[u][j];
                        j = j+1;
                    }
                    while(j<cols);
					// а тут надо ещё отдельно обработать вектор правых частей
					b[i] = b[i] - a_i_u*b[u];

                    i = i+1;// пререходим на строку вниз
                }
                while(i<rows);
            }


			//print_slau(a, b, "after otnjatie");
        }
        else
        {
			// матрица вырождена
			// система не имеет решения
            result = false;
        }
        u = u+1;
    }
    while(u != cols && result);

    if( result )// если матрица не вырождена
    {
        i = cols-1;
        do
        {
			x[i] = b[i];
            if( i!=0 )
            {
                k = i-1;
                do
                {
                    b[k] = b[k]-a[k][i]*x[i];
                    k = k-1;
                }
                while(k>=0);
            }
            i = i-1;
        }
        while(i>=0);
    }
    return result;
}




bool lesgausssolve_find_max(vector<sparse_row> a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon)
{
    bool result;
    int k;
    int u;
    int i;
    double t;

	//print_slau(a, b, "start");

    x.resize(cols);
    u = 0; // номер текущей колонки
    result = true;
    do
    {

       k = u;// текущий диагональный элемент, начиная с верхнего левого
		// движение вниз по текущему столбцу

		// пока не найдём ненулевой элемент
		// ищем максимальный по модулю элемент
		double max_abs = 0.0;

		int r = u, r_max = -1;
        while(r < rows)
        {
			double curr = fabs(a[r][u]);

			if (curr > max_abs) 
			{
				max_abs = curr;
				r_max = r;
			}

            r++;
        }

 printf("u = %d cols = %d max_abs = %f r_max = %d\n", u, cols, max_abs, r_max);

		// если максимальный по модулю элемент больше epsilon
		if (max_abs > epsilon)
		{
			k = r_max;
//printf("u=%d\tk=%d:\n", u,k);

			// если это не диагональный элемент
			// то придётся переставить строки местами
            if( k!=u )
            {		
/*printf("swap %d %d:\n", u,k);
a[u].inorder(visit_print, NULL);printf("\t%f\n", b[u]);
a[k].inorder(visit_print, NULL);printf("\t%f\n", b[k]);
*/
				a[u].swap(a[k]);
				// тут же надо переставить местами элементы вектора правых частей
				t = b[u];
				b[u] = b[k];
				b[k] = t;
            }				
			
#if 0
			i = u;
			double a_u_u = a[u][u];
			do 
			{
				// делим всю строку на текущий диагональный элемент
				b[i] = b[i] / a_u_u;
				a[i].divide_equal(a_u_u);
				i++;
			}
			while(i < rows);
#else
			// делим всю строку на текущий диагональный элемент
			b[u] = b[u] / a[u][u];
			double a_u_u = a[u][u];
//printf("a_u_u = %f\n", a_u_u);
			a[u].divide_equal(a_u_u);
#endif
				


            if( u+1<rows )// если найдённая строка с ненулевым элементом в текущей колонке не самая нижняя
            {
                i = u+1;// номер следующей строки (то есть строки, начиная с которой надо обнулять элементы текущей колонки)
                do
                {

                    //j = u;// номер колонки - мы перебираем все колонки
					double a_i_u = a[i][u];

					if (a_i_u != 0.0)
					{
/*printf("a_i_u = %f\ti = %d\tu = %d\n", a_i_u, i, u);
printf("plus_equal %d %d:\n", i,u);
a[i].inorder(visit_print, NULL);printf("\t%f\n", b[i]);
a[u].inorder(visit_print, NULL);printf("\t%f\n", b[u]);*/
						a[i].plus_equal(- a_i_u, a[u]);
						// а тут надо ещё отдельно обработать вектор правых частей
						b[i] = b[i] - a_i_u*b[u];
					}

                    i = i+1;// пререходим на строку вниз
                }
                while(i<rows);
           }
        }
        else
        {
			// матрица вырождена
			// система не имеет решения
            result = false;
 
			printf("result = false\n", u, cols);
			for (int ii = u; ii < rows; ii ++)
			{
				a[ii].inorder(visit_print, NULL);printf("\t%f\n", b[ii]);
			}
		}
        u = u+1;

    }
    while(u != cols && result);


	if( result )// если матрица не вырождена
    {
        i = cols-1;
        do
        {
			x[i] = b[i];
            if( i!=0 )
            {
                k = i-1;
                do
                {
                    b[k] = b[k]-a[k][i]*x[i];
                    k = k-1;
                }
                while(k>=0);
            }
            i = i-1;
        }
        while(i>=0);
    }
	for (size_t r = 0; r < a.size(); r++)
	{
		a[r].clear();
	}
   return result;
}




// здесь число строк может быть больше числа столбцов на случай, 
// если имеются линейно-зависимые строки
bool lesgausssolve(vector<vector<double> > a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon)
{
    bool result;
    int k;
    int u;
    int m;
    int j;
    int i;
    double t;

	print_slau(a, b, "start");

    x.resize(cols);
    u = 0; // номер текущей колонки
    result = true;
    do
    {
        k = u;// текущий диагональный элемент, начиная с верхнего левого
		// движение вниз по текущему столбцу
		// пока не найдём ненулевой элемент
        while(k < rows-1 && fabs(a[k][u]) <= epsilon)
        {
            k = k+1;
        }
		// если ненулевой элемент на текущем столбце найден
        if( k!=rows-1 || fabs(a[rows-1][u]) > epsilon )
        {
			// если это не диагональный элемент
			// то придётся переставить строки местами
            if( k!=u )
            {
                m = u;
                do
                {
                    t = a[u][m];
                    a[u][m] = a[k][m];
                    a[k][m] = t;
                    m = m+1;
                }
                while(m<cols);// 
				// иначе тут же надо переставить местами элементы вектора правых частей
				t = b[u];
				b[u] = b[k];
				b[k] = t;
            }
				
			print_slau(a, b , "after perestanovka strok");

			// делим всю строку на текущий диагональный элемент
			j = cols-1; // иначе надо и элемент вектора правых частей разделить на текущий диагональный элемент
			b[u] = b[u] / a[u][u];
            do
            {
                a[u][j] = a[u][j]/a[u][u];
                j = j-1;
            }
            while(j>=u);

				
			print_slau(a, b, "after delenie");


            if( k+1<rows )// если найдённая строка с ненулевым элементом в текущей колонке не самая нижняя
            {
                i = k+1;// номер следующей строки (то есть строки, начиная с которой надо обнулять элементы текущей колонки)
                do
                {
                    j = u;// номер колонки - мы перебираем все колонки
					double a_i_u = a[i][u];
                    do
                    {
                        a[i][j] = a[i][j] - a_i_u*a[u][j];
                        j = j+1;
                    }
                    while(j<cols);
					// а тут надо ещё отдельно обработать вектор правых частей
					b[i] = b[i] - a_i_u*b[u];

                    i = i+1;// пререходим на строку вниз
                }
                while(i<rows);
            }


			print_slau(a, b, "after otnjatie");
        }
        else
        {
			// матрица вырождена
			// система не имеет решения
            result = false;
        }
        u = u+1;
    }
    while(u != cols && result);

    if( result )// если матрица не вырождена
    {
        i = cols-1;
        do
        {
			x[i] = b[i];
            if( i!=0 )
            {
                k = i-1;
                do
                {
                    b[k] = b[k]-a[k][i]*x[i];
                    k = k-1;
                }
                while(k>=0);
            }
            i = i-1;
        }
        while(i>=0);
    }
    return result;
}


bool lesgausssolve(vector<sparse_row> a,
     int rows,
     int cols,
     vector<double> b,
     vector<double>& x,
     double epsilon)
{
    bool result;
    int k;
    int u;
    int i;
    double t;

	//print_slau(a, b, "start");


    x.resize(cols);
    u = 0; // номер текущей колонки
    result = true;
    do
    {
		printf("u = %d cols = %d\n", u, cols);
		
		k = u;// текущий диагональный элемент, начиная с верхнего левого
		// движение вниз по текущему столбцу
		// пока не найдём ненулевой элемент
        while(k < rows-1 && fabs(a[k][u]) <= epsilon)
        {
            k = k+1;
        }
		// если ненулевой элемент на текущем столбце найден
        if( k!=rows-1 || fabs(a[rows-1][u]) > epsilon )
        {
			// если это не диагональный элемент
			// то придётся переставить строки местами
            if( k!=u )
            {
                a[u].swap(a[k]);
				// иначе тут же надо переставить местами элементы вектора правых частей
				t = b[u];
				b[u] = b[k];
				b[k] = t;
            }
				

			// делим всю строку на текущий диагональный элемент
			b[u] = b[u] / a[u][u];
			double a_u_u = a[u][u];
			a[u].divide_equal(a_u_u);



            if( k+1<rows )// если найдённая строка с ненулевым элементом в текущей колонке не самая нижняя
            {
                i = k+1;// номер следующей строки (то есть строки, начиная с которой надо обнулять элементы текущей колонки)
                do
                {
                    //j = u;// номер колонки - мы перебираем все колонки
					double a_i_u = a[i][u];

					if (a_i_u != 0.0)
					{
                        
						a[i].plus_equal(- a_i_u, a[u]);
						// а тут надо ещё отдельно обработать вектор правых частей
						b[i] = b[i] - a_i_u*b[u];
					}

                    i = i+1;// пререходим на строку вниз
                }
                while(i<rows);
            }
        }
        else
        {
			// матрица вырождена
			// система не имеет решения
            result = false;

			printf("result = false\n", u, cols);
			for (int ii = u; ii < rows; ii ++)
			{
				a[ii].inorder(visit_print, NULL);printf("\t%f\n", b[ii]);
			}
        }
        u++;

    }
    while(u != cols && result);

    if( result )// если матрица не вырождена
    {
        i = cols-1;
        do
        {
			x[i] = b[i];
            if( i!=0 )
            {
                k = i-1;
                do
                {
                    b[k] = b[k]-a[k][i]*x[i];
                    k = k-1;
                }
                while(k>=0);
            }
            i = i-1;
        }
        while(i>=0);
    }
    return result;
}


// обычный метод гаусса - число строк равно числу столбцов
bool lesgausssolve(vector<vector<double> > a,
     int n,
     vector<double> b,
     vector<double>& x,
     double epsilon)
{
    bool result;
    int k;
    int u;
    int m;
    int j;
    int i;
    double t;

	//print_slau(a, n, b, "start");

    x.resize(n);
    u = 0; // номер текущей колонки
    result = true;
    do
    {
        k = u;// текущий диагональный элемент, начиная с верхнего левого
		// движение вниз по текущему столбцу
		// пока не найдём ненулевой элемент
        while(k < n-1  && fabs(a[k][u]) <= epsilon)
        {
            k = k+1;
        }
		// если ненулевой элемент на текущем столбце найден
        if( k!=n-1 || fabs(a[n-1][u]) > epsilon )
        {
			// если это не диагональный элемент
			// то придётся переставить строки местами
            if( k!=u )
            {
                m = u;
                do
                {
                    t = a[u][m];
                    a[u][m] = a[k][m];
                    a[k][m] = t;
                    m = m+1;
                }
                while(m<n);// 
				// иначе тут же надо переставить местами элементы вектора правых частей
				t = b[u];
				b[u] = b[k];
				b[k] = t;
            }
				
			//print_slau(a, n, b , "after perestanovka strok");

			// делим всю строку на текущий диагональный элемент
			j = n-1; // иначе надо и элемент вектора правых частей разделить на текущий диагональный элемент
			b[u] = b[u] / a[u][u];
            do
            {
                a[u][j] = a[u][j]/a[u][u];
                j = j-1;
            }
            while(j>=u);

				
			//print_slau(a, n, b, "after delenie");


			m = n-1;// вектор правых частей не включаем, его надо будет обработать отдельно
            if( k+1<n )// если найдённая строка с ненулевым элементом в текущей колонке не самая нижняя
            {
                i = k+1;// номер следующей строки (то есть строки, начиная с которой надо обнулять элементы текущей колонки)
                do
                {
                    j = u;// номер колонки - мы перебираем все колонки
					double a_i_u = a[i][u];
                    do
                    {
                        a[i][j] = a[i][j] - a_i_u*a[u][j];
                        j = j+1;
                    }
                    while(j<=m);
					// а тут надо ещё отдельно обработать вектор правых частей
					b[i] = b[i] - a_i_u*b[u];

                    i = i+1;// пререходим на строку вниз
                }
                while(i<n);
            }


			//print_slau(a, n, b, "after otnjatie");
        }
        else
        {
			// матрица вырождена
			// система не имеет решения
            result = false;
        }
        u = u+1;
    }
    while(u != n && result);

    if( result )// если матрица не вырождена
    {
        i = n-1;
        do
        {
			x[i] = b[i];
            if( i!=0 )
            {
                k = i-1;
                do
                {
                    b[k] = b[k]-a[k][i]*x[i];
                    k = k-1;
                }
                while(k>=0);
            }
            i = i-1;
        }
        while(i>=0);
    }
    return result;
}



bool Tichonov(vector<vector<double> > & A,
						  size_t cols, double alpha, // регуляризационный коэффициент						  		
						  bool rand_not_zero_init,
						  int maxq,
						  vector<double> & b,
						  vector<double> & x)
{
		
	printf ("Tichonov %d\n", maxq);
	/*if (m_dims != 2)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b) (m_dims != 2)",
			"Error",0);
		ExitProcess(0);
		return vdouble();
	}
	if (m_size[0] < 1 || m_size[1] < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		ExitProcess(0);
		return vdouble();
	}
	if (m_size[0] != b.m_length)
	{
		char str[1024];
		sprintf(str, "Error using double::Tichonov(vdouble& b)\nSize of vector %i must be equial to size of matrix = %i %i", b.m_length,m_size[0],m_size[1]);
		MessageBox(0, str,"Error",0);
		ExitProcess(0);
		return vdouble();
	}*/
	int 
		i, r, c,
		rows = A.size(),
//		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
		 //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		alpha_old, // 
		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 0.4, // минимальное значение коэффициента скорости обучения
		maxetha = 1.3, // максимальное значение коэффициента скорости обучения
		little_up = 1.3, // параметры подстройки коэффициента скорости обучения
		little_down = 0.82, //
		much_down = 0.49, //
		etha0 = 1.2, // начальное значение коэффициента скорости обучения
		F, // функционал
		*pdx, *petha, *pvF, *pdF,*pdFdx,
		*pE, *pb, *px, *pb0, *pM, *p2;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второйпроизводной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0), // вектор коэффициентов скорости обучения
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала
	/*pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;*/
	// флаг настройки каждого элемента
	vector<bool> ToTurn; 
	ToTurn.resize(cols,true);

	bool AlphaNonZero = true,
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
//	if (rows >= cols)
//	{
/*
		vdouble M;
		M.resize(cols, cols); // Выделяем память под квадратную матрицу
		vdouble b0;
		b0.resize(cols); // Выделяем память под  соответствующий вектор
		pb0 = b0.pD;
		pM = M.pD;
		int len = cols * cols; // число строк равно числу столбцов
		// формируем квадратную матрицу из верхней части решаемой матрицы
		for (i = 0; i < len; i++)
			*(pM + i) = *(pD + i);
		// соответствующий отрезок вектора правых частей
		for (i = 0; i < cols; i++)
			*(pb0 + i) = *(pb + i);

		// Полученную систему линейных уравнений решаем методом Гаусса - получаем первое приближение решения
		double det;
		M.sls_det(b0,x,det);
		px = x.pD;
		//return x;
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			int rcols = r * cols;
			*(pE + r) = - *(pb + r); // элемент вектора правых частей со знакомминус
			for (c = 0; c < cols; c++)
				*(pE + r) += *(px + c) * *(pD + c + rcols); // суммируем поэлементно произведения искомого вектора на строку
		}
		// Приближение
		delta = sqrt(E.SquareSum());
		// Регуляризационный коэффициент
		alpha = 0.0;*/

//	}
//	else // если система недоопределена
//	{
		//x = ones(cols); // инициализируем вектор решения единицами
		//px = x.pD;
		x.resize(cols,1.0); // вектор решения
		for (c = 0; c < cols; c++)
		{
			if (rand_not_zero_init)
				x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
			else
				x[c] = 0.0;
		}
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r];
			for (c = 0; c < cols; c++)
				E[r] += x[c] * A[r][c];
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		alpha = delta;
//	}
	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;
//	p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = alpha;
		for (r = 0; r < rows; r++)
		{
			d2Fdx2[c] += A[r][c] * A[r][c];
		}
		d2Fdx2[c] *= 2.0;
	}

	ToTurn.resize(cols,true);
	int q = 0;
	do
	{
		q++;
		NotFailed = true; // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement = false; // флаг необходимости настройки хоть одного элемента вектора решения
		alpha_old = alpha;
		// Приближение
		// Регуляризационный коэффициент
		if (AlphaNonZero)
		{
			xS = SquareSum(E) / SquareSum(x);
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;
		// Поправка второй производной
		for (c = 0; c < cols; c++)
			d2Fdx2[c] += 2.0*(alpha - alpha_old);

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;
				// Вычисляем первую производную
				dFdx[c] = alpha * x[c];
				for (r = 0; r < rows; r++)
				{
					dFdx[c] += E[r] * A[r][c];
				}
				dFdx[c] *= 2.0 / d2Fdx2[c];
				//
				if (q > 1)
				{
					//
					if ( fabs(dFdx[c]) < mindFdx)
						ToTurn[c] = false;
					else
						ToTurn[c] = true;

				}
				//
				if (q > 1)
				{
					// вычисляем максимум и минимум модуля отношения первой ко второй производных функционала по элементам вектора решения
					bool first = true;
					double min, max, cur;
					int TurnedElements = 0;
					for (int i = 0; i < cols; i++)
					{
						if ( ToTurn[i])
						{
							TurnedElements++;
							if (first)
							{
								first = false;
								min = fabs(dFdx[i]);
								max = min;
							}
							else
							{
								cur = fabs(dFdx[i]);
								min = cur < min ? cur : min;
								max = cur > max ? cur : max;
							}
						}
					}
					if (TurnedElements > 2)
					{
						cur = fabs(dFdx[c]);
						if (cur == min)	// изменение функционала (<0) минимально по абсолютной величине - т.о. минимально по модулю
						{
							// немного уменьшаем коэффициент скорости подстройки
							etha[c] *= little_down;
							// не вышли ли за пределы нижней границы?
							etha[c] = etha[c] < minetha ? minetha : etha[c];
						}
						else if (cur == max) // изменение функционала (<0) минимально по абсолютной величине - т.о. минимально  по модулю
						{
							// немного увеличиваем коэффициент скорости подстройки
							etha[c] *= little_up;
							// не вышли ли за пределы верхней границы?
							etha[c] = etha[c] > maxetha ? maxetha : etha[c];
						}
					}
				}


				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1)
					dx[c] = etha[c] * dFdx[c];
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					dx[c] *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					dx[c] += etha[c] * dFdx[c];
				}
				//Подстраиваем элемент вектора x
				x[c] -= dx[c];
				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					//int rcols = r * cols;
					E[r] = - b[r];
					for (int C = 0; C < cols; C++)
						E[r] += x[C] * A[r][C];
				}
#if 1
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E) + alpha * SquareSum(x);
				if (q > 1)
				{
					// вектор изменения функционала за текущую итерацию
					dF[c] = F - vF[c];
					if ( dF[c] > 0) // функционал вырос - текущая подстройка неудаяная
					{
						// восстанавливаем предыдущее значение инерционного члена
						dx[c] -= etha[c] * dFdx[c];
						dx[c] /= inertio;
						// отменяем текущее изменение элемента вектора решения
						x[c] += etha[c] * dFdx[c];
						// заново вычисляем вектор невязки
						for (r = 0; r < rows; r++)
						{
							//int rcols = r * cols;
							E[r] = - b[r];
							for (int C = 0; C < cols; C++)
								E[r] += x[C] * A[r][C];
						}
						// восстанавливаем прежнее значение функционала
						F = vF[c];
						// изменение функционала = 0
						dF[c] = 0; 
						ToTurn[c] = true;
						NotFailed = false;
						if (etha[c] == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (etha[c] == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}
						// радикально уменьшаем коэффициент скорости подстройки
						etha[c] *= much_down;

						// не вышли ли за пределы нижней границы?
						etha[c] = etha[c] < minetha ? minetha : etha[c];
					}
				}
				// Запоминаем вычисленный функционал в вектор
				vF[c]  = F;
#endif
				
			}
		}
		// По достижении минимизации функционала или половины числа итераций обнуляем регуляризационный коэффициент
		if (AlphaNonZero && (!ToTurnAnyElement || q > maxq / 2 ))
		{
			AlphaNonZero = false;
			ToTurnAnyElement = true;
			ToTurn.resize(cols, true);
		}
		/*char str[255];
		sprintf(str,"dF %d %lf",q, dF.SquareSum());
		dF.Write("d://_.txt","at", str);
		//dF.Write("d://_.txt","at", "dF");*/

		if (q > 2 && SquareSum(dF) < 0.000001)
			ToTurnAnyElement = false;



		printf ("Tichonov %d %d\n", q, maxq);
	}
	while(ToTurnAnyElement && q < maxq );
//

//CString s;	s.Format("alpha = %g", alpha);	AfxMessageBox(s);

/*	if (epoch == max_epochs)
	{
		AlphaNonZero = false;
		part = 0.0;
	}
	else
		part *= part_down;
	//
	mindFdx *= mindFdx_down;
	}*/
//	return x;
	return true;

}

bool Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  bool AlphaNonZero)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using double::Tichonov()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		i, r, c;
//		rows = m_size[0],
//		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
int		maxq = 100, //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		alpha, // регуляризационный коэффициент
		alpha_old, // 
		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 0.4, // минимальное значение коэффициента скорости обучения
		maxetha = 1.3, // максимальное значение коэффициента скорости обучения
		little_up = 1.3, // параметры подстройки коэффициента скорости обучения
		little_down = 0.82, //
		much_down = 0.49, //
		etha0 = 1.2, // начальное значение коэффициента скорости обучения
		F // функционал
		//*pdx, *petha, *pvF, *pdF,*pdFdx,
		//*pE, *pb, *px, *pb0, *pM, *p2
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0), // вектор коэффициентов скорости обучения
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала

/*	pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;
*/
	// флаг настройки каждого элемента
	vector<bool> ToTurn(cols,true); 

	bool 
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
	if (rows >= cols)
	{
		//система переопределена
/*
		vdouble M;
		M.resize(cols, cols); // Выделяем память под квадратную матрицу
		vdouble b0;
		b0.resize(cols); // Выделяем память под  соответствующий вектор
		pb0 = b0.pD;
		pM = M.pD;
		int len = cols * cols; // число строк равно числу столбцов
		// формируем квадратную матрицу из верхней части решаемой матрицы
		for (i = 0; i < len; i++)
			*(pM + i) = *(pD + i);
		// соответствующий отрезок вектора правых частей
		for (i = 0; i < cols; i++)
			*(pb0 + i) = *(pb + i);

		// Полученную систему линейных уравнений решаем методом Гаусса - получаем первое приближение решения
		double det;
		M.sls_det(b0,x,det);
		px = x.pD;
		//return x;
		*/

		x.resize(cols,1.0); // вектор решения


		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			// for (i = 0; i < A[r].size(); i++)
			// {
			// 		c = A[r][i].col;
			//		E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			// }
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
				//E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
				E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
				nd = nd->next();
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		alpha = 0.0;

	}
	else // если система недоопределена
	{
		x.resize(cols,1.0); // вектор решения
		//x = ones(cols); // инициализируем вектор решения единицами
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			//for (i = 0; i < A[r].size(); i++)
			//{
			//	c = A[r][i].col;
			//	E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			//}
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
				//E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
				E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
				nd = nd->next();
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		alpha = delta;
	}
	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;

	//p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	/*
	for (c = 0; c < cols; c++)
	{
		for (r = 0; r < rows; r++)
		{
			d2Fdx2[c] += A[r][c] * A[r][c];
		}
	}
	*/
	for (r = 0; r < rows; r++)
	{
		//for (i = 0; i < A[r].size(); i++)
		//{
		//	c = A[r][i].col;
		//	d2Fdx2[c] += A[r][i].val * A[r][i].val;
		//}

		BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
		while (nd != A[r].root)
		{
		//	d2Fdx2[c] += A[r][i].val * A[r][i].val;
			d2Fdx2[nd->val.col] += nd->val.val * nd->val.val;
			nd = nd->next();
		}
	}
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
	}

	ToTurn.resize(cols,true);
	int q = 0;
	do
	{
		q++;
printf("Tichoniv q = %d\n", q);
		NotFailed = true; // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement = false; // флаг необходимости настройки хоть одного элемента вектора решения
		alpha_old = alpha;
		// Приближение
		// Регуляризационный коэффициент
		if (AlphaNonZero)
		{
			xS = SquareSum(E) / SquareSum(x);
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;
		// Поправка второй производной
		for (c = 0; c < cols; c++)
			d2Fdx2[c] += 2.0*(alpha - alpha_old);


#define FIRST_DERIVATIVE_OUT_OF_CICLE 1
#define E_OUT_OF_CICLE 1
#if FIRST_DERIVATIVE_OUT_OF_CICLE
		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = alpha * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			//for(i = 0; i < A[r].size(); i++)
			//{
			//	c = A[r][i].col;                        
			//	dFdx[c] += E[r] * A[r][i].val;
			//}
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
			//	dFdx[c] += E[r] * A[r][i].val;
				dFdx[nd->val.col] += E[r] * nd->val.val;
				nd = nd->next();
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0 / d2Fdx2[c];
		}
#endif
printf("first derivative\n");

#if E_OUT_OF_CICLE
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			//for (i = 0; i < A[r].size(); i++)
			//{
			//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			//}
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
			//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
				E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
				nd = nd->next();
			}
//printf ("E[%u] = %e\n", r, E[r]);

		}
#endif
printf("E\n");
		// вычисляем функционал после подстройки очередного элемента вектора решения
		//F = SquareSum(E) + alpha * SquareSum(x);
		double sE = SquareSum(E);
		double sx = SquareSum(x);
		F = sE + alpha * sx;
		printf ("F = %e, sE = %e, sx = %e\n", F, sE, sx);

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;

#if !FIRST_DERIVATIVE_OUT_OF_CICLE
				// Вычисляем первую производную
				dFdx[c] = alpha * x[c];
				for (r = 0; r < rows; r++)
				{
					//for(i = 0; i < A[r].size(); i++)
					//{
					//	if (A[r][i].col == c)
					//	{
					//		dFdx[c] += E[r] * A[r][i].val;
					//		break;
					//	}
					//}

					BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
					while (nd != A[r].root)
					{
						if (nd->val.col == c)
						{
							dFdx[c] += E[r] * nd->val.val;
							break;
						}
						nd = nd->next();
					}
				}
				dFdx[c] *= 2.0 / d2Fdx2[c];
#endif
				//
				if (q > 1)
				{
					//
					if ( fabs(dFdx[c]) < mindFdx)
						ToTurn[c] = false;
					else
						ToTurn[c] = true;

				}
				//
#if 0
				if (q > 1)
				{
					// вычисляем максимум и минимум модуля отношения первой ко второй производных функционала по элементам вектора решения
					bool first = true;
					double min, max, cur;
					int TurnedElements = 0;
					for (int i = 0; i < cols; i++)
					{
						if ( ToTurn[i])
						{
							TurnedElements++;
							if (first)
							{
								first = false;
								min = fabs(dFdx[i]);
								max = min;
							}
							else
							{
								cur = fabs(dFdx[i]);
								min = cur < min ? cur : min;
								max = cur > max ? cur : max;
							}
						}
					}
					if (TurnedElements > 2)
					{
						cur = fabs(dFdx[c]);
						if (cur == min)	// изменение функционала (<0) минимально по абсолютной величине - т.о. минимально по модулю
						{
							// немного уменьшаем коэффициент скорости подстройки
							etha[c] *= little_down;
							// не вышли ли за пределы нижней границы?
							etha[c] = etha[c] < minetha ? minetha : etha[c];
						}
						else if (cur == max) // изменение функционала (<0) минимально по абсолютной величине - т.о. минимально  по модулю
						{
							// немного увеличиваем коэффициент скорости подстройки
							etha[c] *= little_up;
							// не вышли ли за пределы верхней границы?
							etha[c] = etha[c] > maxetha ? maxetha : etha[c];
						}
					}
				}


#endif
				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1)
					dx[c] = etha[c] * dFdx[c];
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					dx[c] *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					dx[c] += etha[c] * dFdx[c];
				}
				//Подстраиваем элемент вектора x
				x[c] -= dx[c];
				// Вектор невязки
				/*for (r = 0; r < rows; r++)
				{
					int rcols = r * cols;
					*(pE + r) = - *(pb + r);
					for (int C = 0; C < cols; C++)
						*(pE + r) += *(px + C) * *(pD + C + rcols);
				}*/

#if !E_OUT_OF_CICLE

				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					//for (i = 0; i < A[r].size(); i++)
					//{
					//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
					//}
					BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
					while (nd != A[r].root)
					{
					//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
						E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
						nd = nd->next();
					}
				}
#endif
//printf("6\n");
#if 0
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E) + alpha * SquareSum(x);
				printf ("F = %e\n", F);
				if (q > 1)
				{
					// вектор изменения функционала за текущую итерацию
					dF[c] = F - vF[c];
					if ( dF[c] > 0) // функционал вырос - текущая подстройка неудаяная
					{
						// восстанавливаем предыдущее значение инерционного члена
						dx[c] -= etha[c] * dFdx[c];
						dx[c] /= inertio;
						// отменяем текущее изменение элемента вектора решения
						x[c] += etha[c] * dFdx[c];
						// заново вычисляем вектор невязки
						/*for (r = 0; r < rows; r++)
						{
							int rcols = r * cols;
							*(pE + r) = - *(pb + r);
							for (int C = 0; C < cols; C++)
								*(pE + r) += *(px + C) * *(pD + C + rcols);
						}*/
						for (r = 0; r < rows; r++)
						{
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							//for (i = 0; i < A[r].size(); i++)
							//{
							//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
							//}
							BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
							while (nd != A[r].root)
							{
							//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
								E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
								nd = nd->next();
							}
						}
						// восстанавливаем прежнее значение функционала
						F = vF[c];
						// изменение функционала = 0
						dF[c] = 0; 
						ToTurn[c] = true;
						NotFailed = false;
						if (etha[c] == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (etha[c] == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}
						// радикально уменьшаем коэффициент скорости подстройки
						etha[c] *= much_down;

						// не вышли ли за пределы нижней границы?
						etha[c] = etha[c] < minetha ? minetha : etha[c];
					}
				}
				// Запоминаем вычисленный функционал в вектор
				vF[c]  = F;
#endif
				
			}
		}
		// По достижении минимизации функционала или половины числа итераций обнуляем регуляризационный коэффициент
		if (AlphaNonZero && (!ToTurnAnyElement || q > maxq / 2 ))
		{
			AlphaNonZero = false;
			ToTurnAnyElement = true;
			ToTurn.resize(cols, true);
		}
		/*char str[255];
		sprintf(str,"dF %d %lf",q, dF.SquareSum());
		dF.Write("d://_.txt","at", str);
		//dF.Write("d://_.txt","at", "dF");*/

		if (q > 2 && SquareSum(dF) < 0.000001)
			ToTurnAnyElement = false;



	}
	while(ToTurnAnyElement && q < maxq );
//

//CString s;	s.Format("alpha = %g", alpha);	AfxMessageBox(s);

/*	if (epoch == max_epochs)
	{
		AlphaNonZero = false;
		part = 0.0;
	}
	else
		part *= part_down;
	//
	mindFdx *= mindFdx_down;
	}*/
	return true;
}

bool Tichonov(size_t cols,
			  vector<sparse_row> & A,	
			  vector<double> & b,
			  vector<double> & x,
			  vector<double> & valpha)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using double::Tichonov()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		i, r, c;
//		rows = m_size[0],
//		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
int		maxq = 100, //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		//alpha, // регуляризационный коэффициент
		//alpha_old, // 
		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 0.4, // минимальное значение коэффициента скорости обучения
		maxetha = 1.3, // максимальное значение коэффициента скорости обучения
		little_up = 1.3, // параметры подстройки коэффициента скорости обучения
		little_down = 0.82, //
		much_down = 0.49, //
		etha0 = 1.2, // начальное значение коэффициента скорости обучения
		F // функционал
		//*pdx, *petha, *pvF, *pdF,*pdFdx,
		//*pE, *pb, *px, *pb0, *pM, *p2
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0), // вектор коэффициентов скорости обучения
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала

/*	pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;
*/
	// флаг настройки каждого элемента
	vector<bool> ToTurn(cols,true); 

	bool 
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
	if (rows >= cols)
	{
		//система переопределена
/*
		vdouble M;
		M.resize(cols, cols); // Выделяем память под квадратную матрицу
		vdouble b0;
		b0.resize(cols); // Выделяем память под  соответствующий вектор
		pb0 = b0.pD;
		pM = M.pD;
		int len = cols * cols; // число строк равно числу столбцов
		// формируем квадратную матрицу из верхней части решаемой матрицы
		for (i = 0; i < len; i++)
			*(pM + i) = *(pD + i);
		// соответствующий отрезок вектора правых частей
		for (i = 0; i < cols; i++)
			*(pb0 + i) = *(pb + i);

		// Полученную систему линейных уравнений решаем методом Гаусса - получаем первое приближение решения
		double det;
		M.sls_det(b0,x,det);
		px = x.pD;
		//return x;
		*/

		x.resize(cols,1.0); // вектор решения


		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			// for (i = 0; i < A[r].size(); i++)
			// {
			// 		c = A[r][i].col;
			//		E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			// }
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
				//E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
				E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
				nd = nd->next();
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		//alpha = 0.0;

	}
	else // если система недоопределена
	{
		x.resize(cols,1.0); // вектор решения
		//x = ones(cols); // инициализируем вектор решения единицами
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			//for (i = 0; i < A[r].size(); i++)
			//{
			//	c = A[r][i].col;
			//	E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			//}
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
				//E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
				E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
				nd = nd->next();
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		//alpha = delta;
	}
	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;

	//p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	/*
	for (c = 0; c < cols; c++)
	{
		for (r = 0; r < rows; r++)
		{
			d2Fdx2[c] += A[r][c] * A[r][c];
		}
	}
	*/
	for (r = 0; r < rows; r++)
	{
		//for (i = 0; i < A[r].size(); i++)
		//{
		//	c = A[r][i].col;
		//	d2Fdx2[c] += A[r][i].val * A[r][i].val;
		//}

		BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
		while (nd != A[r].root)
		{
		//	d2Fdx2[c] += A[r][i].val * A[r][i].val;
			d2Fdx2[nd->val.col] += nd->val.val * nd->val.val;
			nd = nd->next();
		}
	}
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
		// Поправка второй производной
		d2Fdx2[c] += 2.0*(valpha[c]);
	}

	ToTurn.resize(cols,true);
	int q = 0;
	do
	{
		q++;
printf("Tichoniv q = %d\n", q);
		NotFailed = true; // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement = false; // флаг необходимости настройки хоть одного элемента вектора решения
		//alpha_old = alpha;
		// Приближение
		// Регуляризационный коэффициент
		/*if (AlphaNonZero)
		{
			xS = SquareSum(E) / SquareSum(x);
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;*/


#define FIRST_DERIVATIVE_OUT_OF_CICLE 1
#define E_OUT_OF_CICLE 1
#if FIRST_DERIVATIVE_OUT_OF_CICLE
		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = valpha[c] * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			//for(i = 0; i < A[r].size(); i++)
			//{
			//	c = A[r][i].col;                        
			//	dFdx[c] += E[r] * A[r][i].val;
			//}
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
			//	dFdx[c] += E[r] * A[r][i].val;
				dFdx[nd->val.col] += E[r] * nd->val.val;
				nd = nd->next();
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0 / d2Fdx2[c];
		}
#endif
printf("first derivative\n");

#if E_OUT_OF_CICLE
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			//for (i = 0; i < A[r].size(); i++)
			//{
			//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			//}
			BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
			while (nd != A[r].root)
			{
			//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
				E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
				nd = nd->next();
			}
//printf ("E[%u] = %e\n", r, E[r]);

		}
#endif
printf("E\n");
		// вычисляем функционал после подстройки очередного элемента вектора решения
		//F = SquareSum(E) + alpha * SquareSum(x);
		double sE = SquareSum(E);
		double alpha_sx = SquareSum(valpha, x);
		F = sE + alpha_sx;
		printf ("F = %e, sE = %e, sx = %e\n", F, sE, alpha_sx);

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;

#if !FIRST_DERIVATIVE_OUT_OF_CICLE
				// Вычисляем первую производную
				dFdx[c] = alpha * x[c];
				for (r = 0; r < rows; r++)
				{
					//for(i = 0; i < A[r].size(); i++)
					//{
					//	if (A[r][i].col == c)
					//	{
					//		dFdx[c] += E[r] * A[r][i].val;
					//		break;
					//	}
					//}

					BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
					while (nd != A[r].root)
					{
						if (nd->val.col == c)
						{
							dFdx[c] += E[r] * nd->val.val;
							break;
						}
						nd = nd->next();
					}
				}
				dFdx[c] *= 2.0 / d2Fdx2[c];
#endif
				//
				if (q > 1)
				{
					//
					if ( fabs(dFdx[c]) < mindFdx)
						ToTurn[c] = false;
					else
						ToTurn[c] = true;

				}
				//
#if 0
				if (q > 1)
				{
					// вычисляем максимум и минимум модуля отношения первой ко второй производных функционала по элементам вектора решения
					bool first = true;
					double min, max, cur;
					int TurnedElements = 0;
					for (int i = 0; i < cols; i++)
					{
						if ( ToTurn[i])
						{
							TurnedElements++;
							if (first)
							{
								first = false;
								min = fabs(dFdx[i]);
								max = min;
							}
							else
							{
								cur = fabs(dFdx[i]);
								min = cur < min ? cur : min;
								max = cur > max ? cur : max;
							}
						}
					}
					if (TurnedElements > 2)
					{
						cur = fabs(dFdx[c]);
						if (cur == min)	// изменение функционала (<0) минимально по абсолютной величине - т.о. минимально по модулю
						{
							// немного уменьшаем коэффициент скорости подстройки
							etha[c] *= little_down;
							// не вышли ли за пределы нижней границы?
							etha[c] = etha[c] < minetha ? minetha : etha[c];
						}
						else if (cur == max) // изменение функционала (<0) минимально по абсолютной величине - т.о. минимально  по модулю
						{
							// немного увеличиваем коэффициент скорости подстройки
							etha[c] *= little_up;
							// не вышли ли за пределы верхней границы?
							etha[c] = etha[c] > maxetha ? maxetha : etha[c];
						}
					}
				}


#endif
				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1)
					dx[c] = etha[c] * dFdx[c];
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					dx[c] *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					dx[c] += etha[c] * dFdx[c];
				}
				//Подстраиваем элемент вектора x
				x[c] -= dx[c];
				// Вектор невязки
				/*for (r = 0; r < rows; r++)
				{
					int rcols = r * cols;
					*(pE + r) = - *(pb + r);
					for (int C = 0; C < cols; C++)
						*(pE + r) += *(px + C) * *(pD + C + rcols);
				}*/

#if !E_OUT_OF_CICLE

				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					//for (i = 0; i < A[r].size(); i++)
					//{
					//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
					//}
					BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
					while (nd != A[r].root)
					{
					//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
						E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
						nd = nd->next();
					}
				}
#endif
//printf("6\n");
#if 0
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E) + alpha * SquareSum(x);
				printf ("F = %e\n", F);
				if (q > 1)
				{
					// вектор изменения функционала за текущую итерацию
					dF[c] = F - vF[c];
					if ( dF[c] > 0) // функционал вырос - текущая подстройка неудаяная
					{
						// восстанавливаем предыдущее значение инерционного члена
						dx[c] -= etha[c] * dFdx[c];
						dx[c] /= inertio;
						// отменяем текущее изменение элемента вектора решения
						x[c] += etha[c] * dFdx[c];
						// заново вычисляем вектор невязки
						/*for (r = 0; r < rows; r++)
						{
							int rcols = r * cols;
							*(pE + r) = - *(pb + r);
							for (int C = 0; C < cols; C++)
								*(pE + r) += *(px + C) * *(pD + C + rcols);
						}*/
						for (r = 0; r < rows; r++)
						{
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							//for (i = 0; i < A[r].size(); i++)
							//{
							//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
							//}
							BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
							while (nd != A[r].root)
							{
							//	E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
								E[r] += x[nd->val.col] * nd->val.val; // суммируем поэлементно произведения искомого вектора на строку
								nd = nd->next();
							}
						}
						// восстанавливаем прежнее значение функционала
						F = vF[c];
						// изменение функционала = 0
						dF[c] = 0; 
						ToTurn[c] = true;
						NotFailed = false;
						if (etha[c] == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (etha[c] == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}
						// радикально уменьшаем коэффициент скорости подстройки
						etha[c] *= much_down;

						// не вышли ли за пределы нижней границы?
						etha[c] = etha[c] < minetha ? minetha : etha[c];
					}
				}
				// Запоминаем вычисленный функционал в вектор
				vF[c]  = F;
#endif
				
			}
		}
		// По достижении минимизации функционала или половины числа итераций обнуляем регуляризационный коэффициент
		/*if (AlphaNonZero && (!ToTurnAnyElement || q > maxq / 2 ))
		{
			AlphaNonZero = false;
			ToTurnAnyElement = true;
			ToTurn.resize(cols, true);
		}*/
		/*char str[255];
		sprintf(str,"dF %d %lf",q, dF.SquareSum());
		dF.Write("d://_.txt","at", str);
		//dF.Write("d://_.txt","at", "dF");*/

		if (q > 2 && SquareSum(dF) < 0.000001)
			ToTurnAnyElement = false;



	}
	while(ToTurnAnyElement && q < maxq );
//

//CString s;	s.Format("alpha = %g", alpha);	AfxMessageBox(s);

/*	if (epoch == max_epochs)
	{
		AlphaNonZero = false;
		part = 0.0;
	}
	else
		part *= part_down;
	//
	mindFdx *= mindFdx_down;
	}*/
	return true;
}

bool Tichonov(vector<vector<sparse_row_element<double> > > & A,
						  size_t cols,
						  vector<double> & b,
						  vector<double> & x, bool AlphaNonZero)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using double::Tichonov()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		i, r, c;
//		rows = m_size[0],
//		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
int		maxq = 100, //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		alpha, // регуляризационный коэффициент
		alpha_old, // 
		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 0.4, // минимальное значение коэффициента скорости обучения
		maxetha = 1.3, // максимальное значение коэффициента скорости обучения
		little_up = 1.3, // параметры подстройки коэффициента скорости обучения
		little_down = 0.82, //
		much_down = 0.49, //
		etha0 = 1.2, // начальное значение коэффициента скорости обучения
		F // функционал
		//*pdx, *petha, *pvF, *pdF,*pdFdx,
		//*pE, *pb, *px, *pb0, *pM, *p2
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0), // вектор коэффициентов скорости обучения
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала

/*	pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;
*/
	// флаг настройки каждого элемента
	vector<bool> ToTurn(cols,true); 

	bool 
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
	if (rows >= cols)
	{
		//система переопределена
/*
		vdouble M;
		M.resize(cols, cols); // Выделяем память под квадратную матрицу
		vdouble b0;
		b0.resize(cols); // Выделяем память под  соответствующий вектор
		pb0 = b0.pD;
		pM = M.pD;
		int len = cols * cols; // число строк равно числу столбцов
		// формируем квадратную матрицу из верхней части решаемой матрицы
		for (i = 0; i < len; i++)
			*(pM + i) = *(pD + i);
		// соответствующий отрезок вектора правых частей
		for (i = 0; i < cols; i++)
			*(pb0 + i) = *(pb + i);

		// Полученную систему линейных уравнений решаем методом Гаусса - получаем первое приближение решения
		double det;
		M.sls_det(b0,x,det);
		px = x.pD;
		//return x;
		*/

		x.resize(cols,1.0); // вектор решения


		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			for (i = 0; i < A[r].size(); i++)
			{
				c = A[r][i].col;
				E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		alpha = 0.0;

	}
	else // если система недоопределена
	{
		x.resize(cols,1.0); // вектор решения
		//x = ones(cols); // инициализируем вектор решения единицами
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			for (i = 0; i < A[r].size(); i++)
			{
				c = A[r][i].col;
				E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
		alpha = delta;
	}
	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;

	//p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	/*
	for (c = 0; c < cols; c++)
	{
		for (r = 0; r < rows; r++)
		{
			d2Fdx2[c] += A[r][c] * A[r][c];
		}
	}
	*/
	for (r = 0; r < rows; r++)
	{
		for (i = 0; i < A[r].size(); i++)
		{
			c = A[r][i].col;
			d2Fdx2[c] += A[r][i].val * A[r][i].val;
		}
	}
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
	}

	ToTurn.resize(cols,true);
	int q = 0;
	do
	{
		q++;
printf("Tichoniv q = %d\n", q);
		NotFailed = true; // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement = false; // флаг необходимости настройки хоть одного элемента вектора решения
		alpha_old = alpha;
		// Приближение
		// Регуляризационный коэффициент
		if (AlphaNonZero)
		{
			xS = SquareSum(E) / SquareSum(x);
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;
		// Поправка второй производной
		for (c = 0; c < cols; c++)
			d2Fdx2[c] += 2.0*(alpha - alpha_old);


#define FIRST_DERIVATIVE_OUT_OF_CICLE 1
#define E_OUT_OF_CICLE 1
#if FIRST_DERIVATIVE_OUT_OF_CICLE
		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = alpha * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			for(i = 0; i < A[r].size(); i++)
			{
				c = A[r][i].col;                        
				dFdx[c] += E[r] * A[r][i].val;
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0 / d2Fdx2[c];
		}
#endif
printf("first derivative\n");

#if E_OUT_OF_CICLE
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			for (i = 0; i < A[r].size(); i++)
			{
				E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			}
//printf ("E[%u] = %e\n", r, E[r]);

		}
#endif
printf("E\n");
		// вычисляем функционал после подстройки очередного элемента вектора решения
		//F = SquareSum(E) + alpha * SquareSum(x);
		double sE = SquareSum(E);
		double sx = SquareSum(x);
		F = sE + alpha * sx;
		printf ("F = %e, sE = %e, sx = %e\n", F, sE, sx);

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;

#if !FIRST_DERIVATIVE_OUT_OF_CICLE
				// Вычисляем первую производную
				dFdx[c] = alpha * x[c];
				for (r = 0; r < rows; r++)
				{
					for(i = 0; i < A[r].size(); i++)
					{
						if (A[r][i].col == c)
						{
							dFdx[c] += E[r] * A[r][i].val;
							break;
						}
					}
				}
				dFdx[c] *= 2.0 / d2Fdx2[c];
#endif
				//
				if (q > 1)
				{
					//
					if ( fabs(dFdx[c]) < mindFdx)
						ToTurn[c] = false;
					else
						ToTurn[c] = true;

				}
				//
#if 0
				if (q > 1)
				{
					// вычисляем максимум и минимум модуля отношения первой ко второй производных функционала по элементам вектора решения
					bool first = true;
					double min, max, cur;
					int TurnedElements = 0;
					for (int i = 0; i < cols; i++)
					{
						if ( ToTurn[i])
						{
							TurnedElements++;
							if (first)
							{
								first = false;
								min = fabs(dFdx[i]);
								max = min;
							}
							else
							{
								cur = fabs(dFdx[i]);
								min = cur < min ? cur : min;
								max = cur > max ? cur : max;
							}
						}
					}
					if (TurnedElements > 2)
					{
						cur = fabs(dFdx[c]);
						if (cur == min)	// изменение функционала (<0) минимально по абсолютной величине - т.о. минимально по модулю
						{
							// немного уменьшаем коэффициент скорости подстройки
							etha[c] *= little_down;
							// не вышли ли за пределы нижней границы?
							etha[c] = etha[c] < minetha ? minetha : etha[c];
						}
						else if (cur == max) // изменение функционала (<0) минимально по абсолютной величине - т.о. минимально  по модулю
						{
							// немного увеличиваем коэффициент скорости подстройки
							etha[c] *= little_up;
							// не вышли ли за пределы верхней границы?
							etha[c] = etha[c] > maxetha ? maxetha : etha[c];
						}
					}
				}


#endif
				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1)
					dx[c] = etha[c] * dFdx[c];
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					dx[c] *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					dx[c] += etha[c] * dFdx[c];
				}
				//Подстраиваем элемент вектора x
				x[c] -= dx[c];
				// Вектор невязки
				/*for (r = 0; r < rows; r++)
				{
					int rcols = r * cols;
					*(pE + r) = - *(pb + r);
					for (int C = 0; C < cols; C++)
						*(pE + r) += *(px + C) * *(pD + C + rcols);
				}*/

#if !E_OUT_OF_CICLE

				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					for (i = 0; i < A[r].size(); i++)
					{
						E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
					}
				}
#endif
//printf("6\n");
#if 0
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E) + alpha * SquareSum(x);
				printf ("F = %e\n", F);
				if (q > 1)
				{
					// вектор изменения функционала за текущую итерацию
					dF[c] = F - vF[c];
					if ( dF[c] > 0) // функционал вырос - текущая подстройка неудаяная
					{
						// восстанавливаем предыдущее значение инерционного члена
						dx[c] -= etha[c] * dFdx[c];
						dx[c] /= inertio;
						// отменяем текущее изменение элемента вектора решения
						x[c] += etha[c] * dFdx[c];
						// заново вычисляем вектор невязки
						/*for (r = 0; r < rows; r++)
						{
							int rcols = r * cols;
							*(pE + r) = - *(pb + r);
							for (int C = 0; C < cols; C++)
								*(pE + r) += *(px + C) * *(pD + C + rcols);
						}*/
						for (r = 0; r < rows; r++)
						{
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							for (i = 0; i < A[r].size(); i++)
							{
								E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
							}
						}
						// восстанавливаем прежнее значение функционала
						F = vF[c];
						// изменение функционала = 0
						dF[c] = 0; 
						ToTurn[c] = true;
						NotFailed = false;
						if (etha[c] == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (etha[c] == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}
						// радикально уменьшаем коэффициент скорости подстройки
						etha[c] *= much_down;

						// не вышли ли за пределы нижней границы?
						etha[c] = etha[c] < minetha ? minetha : etha[c];
					}
				}
				// Запоминаем вычисленный функционал в вектор
				vF[c]  = F;
#endif
				
			}
		}
		// По достижении минимизации функционала или половины числа итераций обнуляем регуляризационный коэффициент
		if (AlphaNonZero && (!ToTurnAnyElement || q > maxq / 2 ))
		{
			AlphaNonZero = false;
			ToTurnAnyElement = true;
			ToTurn.resize(cols, true);
		}
		/*char str[255];
		sprintf(str,"dF %d %lf",q, dF.SquareSum());
		dF.Write("d://_.txt","at", str);
		//dF.Write("d://_.txt","at", "dF");*/

		if (q > 2 && SquareSum(dF) < 0.000001)
			ToTurnAnyElement = false;



	}
	while(ToTurnAnyElement && q < maxq );
//

//CString s;	s.Format("alpha = %g", alpha);	AfxMessageBox(s);

/*	if (epoch == max_epochs)
	{
		AlphaNonZero = false;
		part = 0.0;
	}
	else
		part *= part_down;
	//
	mindFdx *= mindFdx_down;
	}*/
	return true;
}

bool SLAU(vector<vector<sparse_row_element<double> > > & A,
						  size_t cols,
						  vector<double> & b,
						  vector<double> & x)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using double::Tichonov()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		i, r, c;
//		rows = m_size[0],
//		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
	int	maxq = 100, //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		//alpha, // регуляризационный коэффициент
		//alpha_old, // 
//		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 0.4, // минимальное значение коэффициента скорости обучения
		maxetha = 1.3, // максимальное значение коэффициента скорости обучения
		little_up = 1.3, // параметры подстройки коэффициента скорости обучения
		little_down = 0.82, //
		much_down = 0.49, //
		etha0 = 1.2, // начальное значение коэффициента скорости обучения
		F // функционал
		//*pdx, *petha, *pvF, *pdF,*pdFdx,
		//*pE, *pb, *px, *pb0, *pM, *p2
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0), // вектор коэффициентов скорости обучения
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала

/*	pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;
*/
	// флаг настройки каждого элемента
	vector<bool> ToTurn(cols,true); 

	bool 
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
	if (rows >= cols)
	{
		// система переопределена

		// формируем квадратную матрицу из верхней части решаемой матрицы
		vector<vector<sparse_row_element<double> > > M;
		// соответствующий отрезок вектора правых частей
		vector<double> B0;
		for (r = 0; r < cols; r++)
		{
			M.push_back(A[r]);
			B0.push_back(b[r]);
		}

		// Полученную систему линейных уравнений решаем методом Гаусса - получаем первое приближение решения
//		double det;
//		sls_det(M,B0,x,det);
		//return x;
/*
		vdouble M;
		M.resize(cols, cols); // Выделяем память под квадратную матрицу
		vdouble b0;
		b0.resize(cols); // Выделяем память под  соответствующий вектор
		pb0 = b0.pD;
		pM = M.pD;
		int len = cols * cols; // число строк равно числу столбцов
		// формируем квадратную матрицу из верхней части решаемой матрицы
		for (i = 0; i < len; i++)
			*(pM + i) = *(pD + i);
		// соответствующий отрезок вектора правых частей
		for (i = 0; i < cols; i++)
			*(pb0 + i) = *(pb + i);

		// Полученную систему линейных уравнений решаем методом Гаусса - получаем первое приближение решения
		double det;
		M.sls_det(b0,x,det);
		px = x.pD;
		//return x;
		*/



		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			for (i = 0; i < A[r].size(); i++)
			{
				c = A[r][i].col;
				E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
//		alpha = 0.0;

	}
	else // если система недоопределена
	{
		x.resize(cols,1.0); // вектор решения
		//x = ones(cols); // инициализируем вектор решения единицами
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			for (i = 0; i < A[r].size(); i++)
			{
				c = A[r][i].col;
				E[r] += x[c] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			}
		}
		// Приближение
		delta = sqrt(SquareSum(E));
		// Регуляризационный коэффициент
//		alpha = delta;
	}
	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;

	//p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	/*
	for (c = 0; c < cols; c++)
	{
		for (r = 0; r < rows; r++)
		{
			d2Fdx2[c] += A[r][c] * A[r][c];
		}
	}
	*/
	for (r = 0; r < rows; r++)
	{
		for (i = 0; i < A[r].size(); i++)
		{
			c = A[r][i].col;
			d2Fdx2[c] += A[r][i].val * A[r][i].val;
		}
	}
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
	}

	ToTurn.resize(cols,true);
	int q = 0;
	do
	{
		q++;
printf("Tichoniv q = %d\n", q);
		NotFailed = true; // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement = false; // флаг необходимости настройки хоть одного элемента вектора решения
//		alpha_old = alpha;
		// Приближение
		// Регуляризационный коэффициент
/*		if (AlphaNonZero)
		{
			xS = SquareSum(E) / SquareSum(x);
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;
		// Поправка второй производной
		for (c = 0; c < cols; c++)
			d2Fdx2[c] += 2.0*(alpha - alpha_old);*/


#define FIRST_DERIVATIVE_OUT_OF_CICLE 1
#define E_OUT_OF_CICLE 1
#if FIRST_DERIVATIVE_OUT_OF_CICLE
		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = 0.0;//alpha * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			for(i = 0; i < A[r].size(); i++)
			{
				c = A[r][i].col;                        
				dFdx[c] += E[r] * A[r][i].val;
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0 / d2Fdx2[c];
		}
#endif
printf("first derivative\n");
#if E_OUT_OF_CICLE
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			for (i = 0; i < A[r].size(); i++)
			{
				E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
			}
//printf ("E[%u] = %e\n", r, E[r]);

		}
#endif
printf("E\n");
		// вычисляем функционал после подстройки очередного элемента вектора решения
		//F = SquareSum(E) + alpha * SquareSum(x);
		double sE = SquareSum(E);
		double sx = SquareSum(x);
		F = sE;// + alpha * sx;
		printf ("F = %e, sE = %e, sx = %e\n", F, sE, sx);

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;

#if !FIRST_DERIVATIVE_OUT_OF_CICLE
				// Вычисляем первую производную
				dFdx[c] = alpha * x[c];
				for (r = 0; r < rows; r++)
				{
					for(i = 0; i < A[r].size(); i++)
					{
						if (A[r][i].col == c)
						{
							dFdx[c] += E[r] * A[r][i].val;
							break;
						}
					}
				}
				dFdx[c] *= 2.0 / d2Fdx2[c];
#endif
				//
				if (q > 1)
				{
					//
					if ( fabs(dFdx[c]) < mindFdx)
						ToTurn[c] = false;
					else
						ToTurn[c] = true;

				}
				//
#if 0
				if (q > 1)
				{
					// вычисляем максимум и минимум модуля отношения первой ко второй производных функционала по элементам вектора решения
					bool first = true;
					double min, max, cur;
					int TurnedElements = 0;
					for (int i = 0; i < cols; i++)
					{
						if ( ToTurn[i])
						{
							TurnedElements++;
							if (first)
							{
								first = false;
								min = fabs(dFdx[i]);
								max = min;
							}
							else
							{
								cur = fabs(dFdx[i]);
								min = cur < min ? cur : min;
								max = cur > max ? cur : max;
							}
						}
					}
					if (TurnedElements > 2)
					{
						cur = fabs(dFdx[c]);
						if (cur == min)	// изменение функционала (<0) минимально по абсолютной величине - т.о. минимально по модулю
						{
							// немного уменьшаем коэффициент скорости подстройки
							etha[c] *= little_down;
							// не вышли ли за пределы нижней границы?
							etha[c] = etha[c] < minetha ? minetha : etha[c];
						}
						else if (cur == max) // изменение функционала (<0) минимально по абсолютной величине - т.о. минимально  по модулю
						{
							// немного увеличиваем коэффициент скорости подстройки
							etha[c] *= little_up;
							// не вышли ли за пределы верхней границы?
							etha[c] = etha[c] > maxetha ? maxetha : etha[c];
						}
					}
				}


#endif
				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1)
					dx[c] = etha[c] * dFdx[c];
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					dx[c] *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					dx[c] += etha[c] * dFdx[c];
				}
				//Подстраиваем элемент вектора x
				x[c] -= dx[c];
				// Вектор невязки
				/*for (r = 0; r < rows; r++)
				{
					int rcols = r * cols;
					*(pE + r) = - *(pb + r);
					for (int C = 0; C < cols; C++)
						*(pE + r) += *(px + C) * *(pD + C + rcols);
				}*/
#if !E_OUT_OF_CICLE
				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					for (i = 0; i < A[r].size(); i++)
					{
						E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
					}
				}
#endif
//printf("6\n");
#if 0
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E) + alpha * SquareSum(x);
				printf ("F = %e\n", F);
				if (q > 1)
				{
					// вектор изменения функционала за текущую итерацию
					dF[c] = F - vF[c];
					if ( dF[c] > 0) // функционал вырос - текущая подстройка неудаяная
					{
						// восстанавливаем предыдущее значение инерционного члена
						dx[c] -= etha[c] * dFdx[c];
						dx[c] /= inertio;
						// отменяем текущее изменение элемента вектора решения
						x[c] += etha[c] * dFdx[c];
						// заново вычисляем вектор невязки
						/*for (r = 0; r < rows; r++)
						{
							int rcols = r * cols;
							*(pE + r) = - *(pb + r);
							for (int C = 0; C < cols; C++)
								*(pE + r) += *(px + C) * *(pD + C + rcols);
						}*/
						for (r = 0; r < rows; r++)
						{
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							for (i = 0; i < A[r].size(); i++)
							{
								E[r] += x[A[r][i].col] * A[r][i].val; // суммируем поэлементно произведения искомого вектора на строку
							}
						}
						// восстанавливаем прежнее значение функционала
						F = vF[c];
						// изменение функционала = 0
						dF[c] = 0; 
						ToTurn[c] = true;
						NotFailed = false;
						if (etha[c] == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (etha[c] == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}
						// радикально уменьшаем коэффициент скорости подстройки
						etha[c] *= much_down;

						// не вышли ли за пределы нижней границы?
						etha[c] = etha[c] < minetha ? minetha : etha[c];
					}
				}
				// Запоминаем вычисленный функционал в вектор
				vF[c]  = F;
#endif
				
			}
		}
		// По достижении минимизации функционала или половины числа итераций обнуляем регуляризационный коэффициент
/*		if (AlphaNonZero && (!ToTurnAnyElement || q > maxq / 2 ))
		{
			AlphaNonZero = false;
			ToTurnAnyElement = true;
			ToTurn.resize(cols, true);
		}*/
		/*char str[255];
		sprintf(str,"dF %d %lf",q, dF.SquareSum());
		dF.Write("d://_.txt","at", str);
		//dF.Write("d://_.txt","at", "dF");*/

		if (q > 2 && SquareSum(dF) < 0.000001)
			ToTurnAnyElement = false;



	}
	while(ToTurnAnyElement && q < maxq );
//

//CString s;	s.Format("alpha = %g", alpha);	AfxMessageBox(s);

/*	if (epoch == max_epochs)
	{
		AlphaNonZero = false;
		part = 0.0;
	}
	else
		part *= part_down;
	//
	mindFdx *= mindFdx_down;
	}*/
	return true;
}
size_t GetRealColsNumber(size_t r0, vector<sparse_row > & A,
						 size_t cols)
{
	vector<bool> have_elements(cols, false);
	size_t r, c, rows = A.size(), real_cols = 0;
	for (r = r0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			if (c < cols)
				have_elements[c] = true;
		}
	}
	printf("\n");

	for (c = 0; c < cols; c++)
	{
		if (c%100 == 0)printf("\n");

		if (have_elements[c])
		{
			printf("1");
			real_cols++;
		}
		else
			printf("0");

	}
	printf("\n");

	return real_cols;
}



size_t GetRealColsNumber(vector<sparse_row > & A,
						 size_t cols)
{
	vector<bool> have_elements(cols, false);
	size_t r, c, rows = A.size(), real_cols = 0;
	for (r = 0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			if (c < cols)
				have_elements[c] = true;
		}
	}
	printf("\n");

	for (c = 0; c < cols; c++)
	{
		if (c%100 == 0)printf("\n");

		if (have_elements[c])
		{
			printf("1");
			real_cols++;
		}
		else
			printf("0");

	}
	printf("\n");

	return real_cols;
}



// получить граф в виде полной структуры смежности 
// или нижней структуры смежности 
// ( в зависимости от значения переменной  bool to_form_full_structure ) 
// из симметричной положительно определённой матрицы. 
// Формат получаемого графа в виде вектора разреженных строк

bool Graf_from_matrix(vector<sparse_row> & A, bool to_form_full_structure, vector<sparse_row> & G, vector<double> & diag)
{
	size_t r, c, rows = A.size();
	G.resize(rows); for (r = 0; r < rows; r++) G[r].clear();
	diag.resize(rows);
	for (r = 0; r < rows; r++)
	{
//printf("Graf_from_matrix %u %u\n", r, rows);
		BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
		if (nd == A[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", r);
			//MessageBox(0, err, "Graf_from_matrix", MB_OK);
			printf("Graf_from_matrix Error:\t%s\n", err);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", r);
			//MessageBox(0, err, "Graf_from_matrix", MB_OK);
			printf("Graf_from_matrix Error:\t%s\n", err);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %e", r, d);
			printf("Graf_from_matrix Error:\t%s\n", err);
			//MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		diag[r] = d;

		BraidedNode<sparse_row_element<double> > * nc = nd->next();
		while (nc != A[r].root)
		{
			c = nc->val.col;
			if (c > r && c < rows)
			{
				G[r].put(c, nc->val.val);
				if (to_form_full_structure)
				{
					G[c].put(r, nc->val.val);
				}
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < rows %u && c %u > r %u)\n", c, rows, c, r);
				printf("Graf_from_matrix Error:\t%s\n", err);
				//MessageBox(0, err, "Graf_from_matrix", MB_OK);
				return false;
			}
			nc = nc->next();
		}

	}
	return true;
}

// теперь полученный граф преобразуем к форме хранения XADJ, ADJNCY
// этой же функцией можно преобразовывать и матрицу

bool Graf_to_vectors(vector<sparse_row> & G, vector<int>& xadj, vector<int> & adjncy, vector<double> & values)
{
	size_t r, c, rows = G.size();
	xadj.clear();
	adjncy.clear();
	values.clear();
	for (r = 0; r < rows; r++)
	{
//printf("Graf_to_vectors %u %u\n", r, rows);
		xadj.push_back(adjncy.size());
		BraidedNode<sparse_row_element<double> > * nc = G[r].root->next();
		while (nc != G[r].root)
		{
			c = nc->val.col;
			if (c < rows)
			{
				adjncy.push_back(c);
				values.push_back(nc->val.val);
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < rows %u)\n", c, rows);
				printf("Graf_to_vectors\t%s\n", err);
				//MessageBox(0, err, , MB_OK);
				return false;
			}
			nc = nc->next();
		}
	}
	xadj.push_back(adjncy.size());
	return true;
}

/*
bool matrix2vectors(vector<sparse_row> & A, bool to_form_full_structure, 
					vector<double> & diag, vector<int>& xadj, vector<int> & adjncy, vector<double> & values)
{
	size_t r, c, rows = A.size();
	diag.resize(rows);
	xadj.clear();
	adjncy.clear();
	values.clear();

	for (r = 0; r < rows; r++)
	{
//printf("Graf_from_matrix %u %u\n", r, rows);
		xadj.push_back(adjncy.size());
		BraidedNode<sparse_row_element<double> > * nd = A[r].root->next();
		if (nd == A[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", r);
			MessageBox(0, err, "Graf_from_matrix", MB_OK);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", r);
			MessageBox(0, err, "Graf_from_matrix", MB_OK);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %e", r, d);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		diag[r] = d;

		BraidedNode<sparse_row_element<double> > * nc = nd->next();
		while (nc != A[r].root)
		{
			c = nc->val.col;
			if (c > r && c < rows)
			{
				G[r].put(c, nc->val.val);
				if (to_form_full_structure)
				{
					G[c].put(r, nc->val.val);
				}
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < rows %u && c %u > r %u)\n", c, rows, c, r);
				MessageBox(0, err, "Graf_from_matrix", MB_OK);
				return false;
			}
			nc = nc->next();
		}

	}
	return true;
}
*/

// обратное преобразование графа в форму vector<sparse_row>
// этой же функцией можно преобразовывать и матрицу

bool Graf_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<sparse_row> & G)
{
	if (xadj.size() > 1)
	{
		size_t r, i, rows = xadj.size() - 1;
		G.resize(rows); for (r = 0; r < rows; r++) G[r].clear();
		for (r = 0; r < rows; r++)
		{
			for (i = xadj[r]; i < xadj[r+1]; i++)
			{
				G[r].put(adjncy[i], values[i]);
			}
		}
		return true;
	}
	return false;
}

bool Matrix_from_vectors(vector<int>& xadj, vector<int> & adjncy, vector<double> & values, vector<double> & diag, int * invp, vector<sparse_row> & m)
{
	if (xadj.size() > 1)
	{
		size_t r, i, c, rows = xadj.size() - 1;
		int r2, c2;
		m.resize(rows); for (r = 0; r < rows; r++) m[r].clear();
		for (r = 0; r < rows; r++)
		{
			// номер строки после перестановки
			r2 = invp[r];
			// вставляем диагональный элемент
			m[r2].put(r2, diag[r]);
			for (i = xadj[r]; i < xadj[r+1]; i++)
			{
				// исходный номер колонки
				c = adjncy[i];
				// номер колонки после перестановки
				c2 = invp[c];
				if (c2 > r2)
					m[r2].put(c2, values[i]);
			}
		}
		return true;
	}
	return false;
}

// определить ширину ленты матрицы

int Get_Band_Len(vector<sparse_row> & m, vector<int> & beta)
{
	size_t i, c, rows = m.size();
	vector<int> fi(rows);
	beta.resize(rows);
	for (i = 0; i < rows; i ++) fi[i] = i;
	for (i = 0; i < rows; i ++)
	{
		BraidedNode<sparse_row_element<double> > * nc = m[i].root->next();
		while (nc != m[i].root)
		{
			c = nc->val.col;
			if (c < rows)
			{
				if (fi[c] > i) fi[c] = i;
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < rows %u)\n", c, rows);
				MessageBox(0, err, "Get_Band_Len", MB_OK);
				return false;
			}
			nc = nc->next();
		}
	}
	int band_len = 0;
	for (i = 0; i < rows; i ++)
	{
		beta[i] = i - fi[i];
		if (band_len < beta[i]) band_len = beta[i];
	}
	return band_len;
}

// определить ширину фронта матрицы

int Get_Front_Width(vector<sparse_row> & m, vector<int> & omega)
{
	size_t i, c, rows = m.size();
	vector<int> fi(rows);
	omega.resize(rows, 0);
	for (i = 0; i < rows; i ++) fi[i] = i;
	for (i = 0; i < rows; i ++)
	{
		BraidedNode<sparse_row_element<double> > * nc = m[i].root->next();
		while (nc != m[i].root)
		{
			c = nc->val.col;
			if (c < rows)
			{
				if (fi[c] > i) fi[c] = i;
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < rows %u)\n", c, rows);
				MessageBox(0, err, "Get_Band_Len", MB_OK);
				return false;
			}
			nc = nc->next();
		}
	}
	int front_width = 0;
	for (c = 0; c < rows; c ++)
	{
		for (i = c+1; i < rows; i ++)
		{
			if (fi[i] <= c) omega[c] += 1;
		}
		if (front_width < omega[c]) front_width = omega[c];
	}
	return front_width;
}

// ROOTLS (ROOTed Level Structure)		корневая структура уровней
// генерирует структуру уровней с корнем в узле, задаваемом входным параметром ROOT
// учитываются лишь узлы, которым соответствуют ненулевые значения MASK
// Входные параметры:
//		ROOT - заданный корень структуры уровней
//		(XADJ, ADJNCY) - пара массивов, хранящая структуру смежности заданного графа
//		MASK - нужен для задания подграфа. Узлы, для которых MASK[i] == 0, игнорируются.
// Выходные параметры
//		NLVL - число уровней в структуре уровней
//		(XLS, LS) - массивы для структуры уровней

void ROOTLS(int& root, vector<int>& xadj, vector<int>& adjncy, vector<bool>& mask, int& nlvl, vector<int>& xls, int * ls)
{
	int i, j, node, j_stop, nbr;
	// присвоение начальных значений
	nlvl = 0;
	mask[root] = false;
	ls[0] = root; // ls.push_back(root);
	int lbegin, lvlend = 0;
	int ccsize = 1;
	// LBEGIN - указатель начала текущего уровня
	// LVLEND - указывает конец этого уровня
	do
	{
		lbegin = lvlend;
		lvlend = ccsize;
		xls[nlvl] = lbegin;
		nlvl++;
		// построить следующий уровень, находя всех маркированных соседей
		// узлов текущего уровня
		for (i = lbegin; i < lvlend; i++)
		{
			node = ls[i];
			j_stop = xadj[node+1];
			for ( j = xadj[node]; j < j_stop; j++)
			{
				nbr = adjncy[j];
				if(mask[nbr])
				{
					ls[ccsize] = nbr; // ls.push_back(nbr);
					ccsize++;
					mask[nbr] = false;
				}
			}
		}
		// вычислить ширину текущего уровня, если она 
		// не равнва нулю, пгостроить следующий уровень
	}
	while(ccsize > lvlend);
	xls[nlvl] = lvlend;
	// В MASK восстановить 1 для узлов структуры уровней
	for (i = 0; i < ccsize; i++)
	{
		node = ls[i];
		mask[node] = true;
	}
}

// FNROOT (FiNd ROOT) поиск псевдопериферийного узла
// FNROOT реализует модифицированный вариант схемы Гиббса, 
// Пула и Стокмейера отыскания псевдопериферийных узлов.
// Она определяет такой узел для подграфа, задаваемого MASK и ROOT
// Входные параметры
//		(XADJ, ADJNCY) - массивы для структуры смежности графа
//		MASK - задаёт подграф. Узлы, для которых MASK[i] == 0, игнорируются.
// Изменяемый параметр
//		ROOT - на входе (вместе с MASK) определяет компоненту,
//			для которой ищется псевлопериферийный узел.
//			На выходе - это найденный узел.
// Выходные параметры
//		NLVL - число уровней в структуре уровней с корнем в узле ROOT
//		(XLS, LS) - пара массивов для хранения найденной структуры уровней
// Используемые подпрограммы
//		ROOTLS
void FNROOT(int& root, vector<int>& xadj, vector<int>& adjncy, vector<bool>& mask, int& nlvl, vector<int>& xls, int * ls)
{
	int j, k, j_start, k_stop, mindeg, node, ndeg, nabor, nunlvl;
	// определить структуру уровней с корнем в ROOT
	ROOTLS(root, xadj, adjncy, mask, nlvl, xls, ls);
	int ccsize = xls[nlvl];
	if (nlvl == 1 || nlvl == ccsize) return;
	// выбрать в последнем уровне узел с минимальной степенью
	do
	{
		j_start = xls[nlvl-1];
		mindeg = ccsize;
		root = ls[j_start];
		for (j = j_start; j < ccsize; j++)
		{
			node = ls[j];
			ndeg = 0;
			k_stop = xadj[node+1];
			for (k = xadj[node]; k < k_stop; k++)
			{
				nabor = adjncy[k];
				if (mask[nabor]) ndeg++;
			}
			if (ndeg < mindeg)
			{
				root = node;
				mindeg = ndeg;
			}
		}
		// построить структуру уровней с корнем в этом узле
		ROOTLS(root, xadj, adjncy, mask, nunlvl, xls, ls);
		if (nunlvl <= nlvl) return;
		nlvl = nunlvl;
	}
	while(nlvl < ccsize);
}

// DEGREE степени в маркированной (masked) компоненте
// Подпрограмма вычисляет степени узлов в связной компоненте,
// задаваемой MASK и ROOT. Узлы, для которых MASK[i] == 0, игнорируются.
// Входные параметры
//		ROOT - узел, определяющий компоненту,
//		(XADJ, ADJNCY) - массивы для структуры смежности
//		MASK - задаёт подграф. 
// Выходные параметры
//		DEG - Массив, содержащий степени узлов в компоненте.
//		CCSIZE - число узлов компоненты, задаваемой MASK и ROOT
// Рабочий параметр
//		LS - вектор для хранения узлов компоненты, уровень за уровнем

void DEGREE(int& root, vector<int>& xadj, vector<int>& adjncy, vector<bool>& mask, vector<int>& deg, int& ccsize, int * ls)
{
	int i, ideg, j, j_start, j_stop, lbegin, lvlend, nbr, node;
	// присвоение начальных значений
	// массив xadj используется для указания, какие узлы обработаны на данный момент
	ls[0] = root;
	xadj[root] = -xadj[root]-1;
	lvlend = 0;
	ccsize = 1;
	// LBEGIN - указатель начала текущего уровня
	// LVLEND - указывает конец этого уровня

	//size_t xadj_size = xadj.size();
	//size_t adjncy_size = adjncy.size();
	do
	{
		lbegin = lvlend;
		lvlend = ccsize;
		// найти степени узлов текущего уровня и построить следующий уровень
		for (i = lbegin; i < lvlend; i++)
		{
			node = ls[i];
			j_start = -xadj[node]-1;
			j_stop = xadj[node+1] < 0 ? -xadj[node+1]-1 : xadj[node+1];
			ideg = 0;
			for (j = j_start; j < j_stop; j++)
			{
				nbr = adjncy[j];
				if (mask[nbr])
				{
					ideg++;
					if (xadj[nbr] >= 0)
					{
						xadj[nbr] = -xadj[nbr]-1;
						ls[ccsize] = nbr;
						ccsize++;
					}
				}
			}
			deg[node] = ideg;
		}
		// вычислить ширину текущего уровня, если она 
		// не равнва нулю, пгостроить следующий уровень
	}
	while(ccsize > lvlend);
	// восстановить правильные знаки в xadj. Возврат.
	for (i = 0; i < ccsize; i++)
	{
		node = ls[i];
		xadj[node] = -xadj[node]-1;
	}
	return;
}

// RCM (Reverse Cethill - McKee) - обратное упорядочение Катхилла - Макки
// RCM нумерует связную компоненту, заданную MASK и ROOT.
// используя алгоритм RCM.
// Процесс нумерации должен начинаться с узла ROOT
// Входные параметры
//		ROOT - узел, определяющий связную компоненту,
//			начальный для RCM - упорядочения
//		(XADJ, ADJNCY) - массивы для структуры смежности графа
// Изменяемый параметр
//		MASK - рассматриваются лишь узлы, которым 
//			соответствуют ненулевые входные значения 
//			в MASK. Для узлов, пронумерованных RCM,
//			в MASK задаётся 0.
// Выходные параметры
//		PERM - содержит RCM - упорядочение.
//		CCSIZE - число узлов компоненты, пронумерованной подпрограммой RCM
// Рабочий параметр
//		DEG - Массив для хранения степеней узлов подграфа,
//			заданного посредствои MASK и ROOT.
// Используемые подпрограммы
//		DEGREE
void RCM(int& root, vector<int>& xadj, vector<int>& adjncy, vector<bool>& mask, int * perm, int& ccsize, vector<int> & deg)
{
	int i, j, fnbr, k, L, j_stop, lbegin, lnbr, lperm, lvlend, nbr, node;
	// найти степени узлов в компоненте, заданной MASK и ROOT
	DEGREE(root, xadj, adjncy, mask, deg, ccsize, perm);

	mask[root] = false;
	if (ccsize <= 1) return;
	lvlend = 0;
	lnbr = 1;
	// LBEGIN - указатель начала текущего уровня
	// LVLEND - указывает конец этого уровня
	do
	{
		lbegin = lvlend;
		lvlend = lnbr;
		for (i = lbegin; i < lvlend; i++)
		{
			// для каждого узла в текущем уровне
			node = perm[i];
			j_stop = xadj[node+1];
			// найти ненумерованных соседей
			// FNBR и LNBR  указывают первого и последнего
			// из ненумерованных соседей текущего узла из PERM+
			fnbr = lnbr;
			for (j = xadj[node]; j < j_stop; j++)
			{
				nbr = adjncy[j];
				if (mask[nbr])
				{
					perm[lnbr] = nbr;
					lnbr++;
					mask[nbr] = false;
				}
			}
			if(fnbr < lnbr - 1)//(!(fnbr >= lnbr))
			{
				// упорядочить соседей данного узла по возрастанию
				// степеней. сортировка методом пузырька
				k = fnbr;
				do
				{
					L = k;
					k++;
					nbr = perm[k];
					while (L >= fnbr)
					{
						lperm = perm[L];
						if (deg[lperm] <= deg[nbr] ) break;
						perm[L+1] = lperm;
                        L--;
					}
					perm[L+1] = nbr;
				}
				while (k < lnbr - 1);
			}
		}
	}
	while(lnbr > lvlend);

	// получено упорядочение Катхилла - Макки
	// Ниже оно будет обращено
	k = ccsize/2;
	L = ccsize-1;
	for (i = 0; i < k; i++)
	{
		lperm = perm[L];
		perm[L] = perm[i];
		perm[i] = lperm;
		L--;
	}
}

// GENRCM (General RCM) - обратное упорядочение Катхилла - Макки произвольного графа
// GENRCM находит обратное упорядочение Катхилла - Макки произвольного графа. Для каждой
// связной компоненты графа упорядочение достигается вызовом RCM
// 
// Входные параметры
//		NEQNS - число уравнений
//		(XADJ, ADJNCY) - массивы для структуры смежности графа матрицы
// 
// Выходные параметры
//		PERM - вектор, содержащий RCM - упорядочение.
// 
// Рабочие параметры
//		MASK - вектор для маркировки переменных, 
//			пронумерованных в процессе упорядочения.
//			Начальные значения компонент равны 1.
//			Они заменяются на 0 при нумерации узлов
//		XLS - индексный вектор для структуры уровней,
//			хранящейся в неиспользуемых на данный момент 
//			позициях перестановки PERM
// Используемые подпрограммы
//		FNROOT, RCM

void GENRCM(int& neqns, vector<int>& xadj, vector<int>& adjncy, int * perm, vector<bool>& mask, vector<int> & xls)
{
	int ccsize, i, nlvl, num, root;
	for (i = 0; i < neqns; i++)
	{
		mask[i] = true;
	}
	num = 0;
	for (i = 0; i < neqns; i++)
	{
		if (mask[i])
		{
			root = i;
			// вначале найти псевдопериферийный узел ROOT.
			// структура уровней, найденная FNROOT, 
			// хранится, начиная с PERM[num]. Затем 
			// происходит обращение к RCM. ROOT - начальный 
			// узел при упорядочении компонент
			FNROOT(root, xadj, adjncy, mask, nlvl, xls, perm + num);
			RCM   (root, xadj, adjncy, mask, perm + num, ccsize, xls);
			num += ccsize;
			if (num >  neqns)  return;
		}
	}
}

// преобразование симметричной положительно определённой матрицы 
// в верхнетреугольный множитель Холесского
// на вход подаётся верхнетреугольная часть симметричной положительно определённой матрицы
// функция разрушает исходные данные

bool Holesski(vector<sparse_row > & m)
{
	size_t rows = m.size();
	for (size_t r = 0; r < rows; r++)
	{
printf("Holesski test %u %u\n", r, rows);
		BraidedNode<sparse_row_element<double> > * nd = m[r].root->next();
		if (nd == m[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", r);
			MessageBox(0, err, "Holesski  test", MB_OK);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", r);
			MessageBox(0, err, "Holesski  test", MB_OK);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %e", r, d);
			MessageBox(0, err, "Holesski  test", MB_OK);
			return false;
		}
	}


	for (size_t r = 0; r < rows; r++)
	{
printf("Holesski %u %u\n", r, rows);
		BraidedNode<sparse_row_element<double> > * nd = m[r].root->next();
		if (nd == m[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", r);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", r);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %e", r, d);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		double sqrt_d = sqrt(d);
		nd->val.val = sqrt_d;
		BraidedNode<sparse_row_element<double> > * n1 = nd->next();
		while (n1 != m[r].root)
		{
			BraidedNode<sparse_row_element<double> > * n2 = n1;
			size_t c1 = n1->val.col;
			double v1 = n1->val.val;
			while (n2 != m[r].root)
			{
				size_t c2 = n2->val.col;
				double v2 = n2->val.val;
				m[c1].plus(c2, - v1*v2/d);
				n2 = n2->next();
			}
			n1->val.val /= sqrt_d;
			n1 = n1->next();
		}

	}
	return true;
}

bool Holesski3(vector<sparse_row > & m)
{
	// вычисление разложения Холесского в форме скалярных произведений
	size_t rows = m.size();
#if 0
	for (size_t r = 0; r < rows; r++)
	{
printf("Holesski3 test %u %u\n", r, rows);
		BraidedNode<sparse_row_element<double> > * nd = m[r].root->next();
		if (nd == m[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", r);
			MessageBox(0, err, "Holesski  test", MB_OK);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", r);
			MessageBox(0, err, "Holesski  test", MB_OK);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %e", r, d);
			MessageBox(0, err, "Holesski  test", MB_OK);
			return false;
		}
	}
#endif

	for (size_t j = 0; j < rows; j++)
	{
printf("Holesski3 %u %u\n", j, rows);
		BraidedNode<sparse_row_element<double> > * nd = m[j].root->next();
		if (nd == m[j].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", j);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		if (nd->val.col != j)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", j);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		for(size_t k = 0; k < j; k++)
		{
			//  ищем в k-той строке узел равный j
			BraidedNode<sparse_row_element<double> > * n1 = m[k].root->rchild();
			if (m[k]._find(sparse_row_element<double>(j,1.0), n1))
			{
				size_t c1 = n1->val.col;
				double v1 = n1->val.val;
				BraidedNode<sparse_row_element<double> > * n2 = n1;
				while (n2 != m[k].root)
				{
					size_t c2 = n2->val.col;
					double v2 = n2->val.val;
					m[j].plus(c2, - v1*v2);
					n2 = n2->next();
				}
			}
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %e", j, d);
			MessageBox(0, err, "Holesski", MB_OK);
			return false;
		}
		double sqrt_d = sqrt(d);
		nd->val.val = sqrt_d;

		BraidedNode<sparse_row_element<double> > * n = nd->next();

		while (n != m[j].root)
		{
			n->val.val /= sqrt_d;
			n = n->next();
		}

	}
	return true;
}

// 
// Дальше этой функцией решаем треугольную систему уравнений 
// с верхнетреугольным множителем Холесского
// 

bool tria_solve_of_down (vector<sparse_row> t,
	vector<double> b, vector<double>& x)
{
	size_t rows = t.size(); x.resize(rows);
printf("tria_solve_of_down %u\n", rows);
	if (b.size() != rows)
	{
		char err[512];
		sprintf(err, "Error: b.size() %u != rows %u\n", b.size(), rows);
		MessageBox(0, err, "tria_solve_of_down", MB_OK);
		return false;
	}
	for (size_t r = 0; r < rows; r++)
	{
printf("tria_solve_of_down %u %u\n", r, rows);
		BraidedNode<sparse_row_element<double> > * nd = t[r].root->next();
		if (nd == t[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %u is missed", r);
			MessageBox(0, err, "tria_solve_of_down", MB_OK);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is missed", r);
			MessageBox(0, err, "tria_solve_of_down", MB_OK);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %u is not positive %f", r, d);
			MessageBox(0, err, "tria_solve_of_down", MB_OK);
			return false;
		}
		x[r] = b[r] / d;
		BraidedNode<sparse_row_element<double> > * ni = nd->next();
		while (ni != t[r].root)
		{
			size_t c = ni->val.col;
			if(c < b.size() && c > r)
			{
				b[c] -= x[r] * ni->val.val;
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < b.size() %u && c %u > r %u)\n", c, b.size(), c, r);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}
			ni = ni->next();
		}

	}
	return true;
}


// 
// Дальше этой функцией решаем треугольную систему уравнений 
// с верхнетреугольным множителем Холесского
// 

bool tria_solve_of_up (vector<sparse_row> & t,
	vector<double>& b, vector<double>& x)
{
	int rows = t.size(); x.resize(rows);
printf("tria_solve_of_up %d\n", rows);
	if (b.size() != rows)
	{
		char err[512];
		sprintf(err, "Error: b.size() %u != rows %d\n", b.size(), rows);
		MessageBox(0, err, "tria_solve_of_up", MB_OK);
		return false;
	}
	for (int r = rows-1; r >= 0; r--)
	{
printf("tria_solve_of_up %d %d\n", r, rows);
		BraidedNode<sparse_row_element<double> > * nd = t[r].root->next();
		if (nd == t[r].root)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As row %d is missed", r);
			MessageBox(0, err, "tria_solve_of_up", MB_OK);
			return false;
		}
		if (nd->val.col != r)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %d is missed", r);
			MessageBox(0, err, "tria_solve_of_up", MB_OK);
			return false;
		}
		double d = nd->val.val;
		if (d <= 0.0)
		{
			char err[512];
			sprintf(err, "The matrix is not positively defined\n"
				"As diagonal element at row %d is not positive %f", r, d);
			MessageBox(0, err, "tria_solve_of_up", MB_OK);
			return false;
		}
		x[r] = b[r];
		BraidedNode<sparse_row_element<double> > * ni = nd->next();
		while (ni != t[r].root)
		{
			size_t c = ni->val.col;
			if(c < x.size() && c > r)
			{
				x[r] -= ni->val.val * x[c];
			}
			else
			{
				char err[512];
				sprintf(err, "!(c %u < x.size() %u && c %u > r %d)\n", c, x.size(), c, r);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}
			ni = ni->next();
		}
		x[r] /= d;

	}
	return true;
}
#define BUFF_SIZE 1024
bool tria_solve_of_down_and_up(const char * fn_L, const char * fn_U, vector<double> b, vector<double> & sol)
{
	vector<double> y;

	/*long cols;
	vector<sparse_row> Lt;
	LoadMatrix(fn_Lt, Lt, cols);

	if (tria_solve_of_down(Lt, B, y))
	{
		if (tria_solve_of_up(Lt, y, sol))
		{
			return true;
		}
	}*/

		
	vector<long> file_pointers;

	long cols, rows;
	bool res = false;

		
	AFile fL;
	if( ! fL.Open( fn_L, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareMatrix\nUnable to open file" , fn_L, MB_OK);
		return false;
	}

	char buffL[BUFF_SIZE];
	Archive arL( &fL, Archive::load, BUFF_SIZE, buffL );
	
	try
	{
		arL >> rows;
		arL >> cols;

		if (b.size() != rows)
		{
			char err[512];
			sprintf(err, "Error: b.size() %u != rows %u\n", b.size(), rows);
			MessageBox(0, err, "tria_solve_of_down", MB_OK);
			return false;
		}

		y.resize(rows);

		//file_pointers.resize(rows+1);
		//file_pointers[0] = 2*sizeof(long);


		sparse_row_simple t_row_s;
		for (long r = 0; r < rows; r++)
		{
			t_row_s.clear();
			arL >> t_row_s;
		//	file_pointers[r+1] = file_pointers[r] + (t_row_s.size() + 1)*(sizeof(long) + sizeof(double));

//printf("tria_solve_of_down %u %u\n", r, rows);
			//BraidedNode<sparse_row_element<double> > * nd = t[r].root->next();
			vector<sparse_row_element<double> >::reverse_iterator nd = t_row_s.rbegin();
			if (nd == t_row_s.rend())
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As row %u is missed", r);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}
			/*if ((*nd).col != r)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is missed", r);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}*/
			double d = (*nd).val;
			/*if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is not positive %f", r, d);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}*/
			y[r] = b[r];
			//BraidedNode<sparse_row_element<double> > * ni = nd->next();
			vector<sparse_row_element<double> >::reverse_iterator ni = nd+1;
			while (ni != t_row_s.rend())
			{
				size_t c = (*ni).col;
				if(c < b.size())
				{
					y[r] -= y[c] * (*ni).val;
				}
				else
				{
					char err[512];
					sprintf(err, "!(c %u < b.size())\n", c, b.size());
					MessageBox(0, err, "tria_solve_of_down", MB_OK);
					return false;
				}
				ni++;
			}
			y[r]/=d;
		}
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	arL.Close();
	fL.Close();


	AFile fU;
	if( ! fU.Open( fn_U, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareMatrix\nUnable to open file" , fn_U, MB_OK);
		return false;
	}

	char buffU[BUFF_SIZE];
	Archive arU( &fU, Archive::load, BUFF_SIZE, buffU );
	
	try
	{
		arU >> rows;
		arU >> cols;

		if (b.size() != rows)
		{
			char err[512];
			sprintf(err, "Error: b.size() %u != rows %u\n", b.size(), rows);
			MessageBox(0, err, "tria_solve_of_down", MB_OK);
			return false;
		}


		file_pointers.resize(rows+1);
		file_pointers[0] = 2*sizeof(long);


		sparse_row_simple t_row_s;
		for (long r = 0; r < rows; r++)
		{
			t_row_s.clear();
			arU >> t_row_s;
			file_pointers[r+1] = file_pointers[r] + (t_row_s.size() + 1)*(sizeof(long) + sizeof(double));
		}

		sol.resize(rows);

		for (int r = rows-1; r >= 0; r--)
		{
//printf("tria_solve_of_up %d %d\n", r, rows);

			t_row_s.clear();

			fU.Seek(file_pointers[r], FILE_BEGIN);arU.ClearReadBuffer();
			arU >> t_row_s;

			//BraidedNode<sparse_row_element<double> > * nd = t[r].root->next();
			vector<sparse_row_element<double> >::iterator nd = t_row_s.begin();
			
			if (nd == t_row_s.end())
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As row %d is missed", r);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}
			if ((*nd).col != r)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %d is missed", r);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}
			double d = (*nd).val;
			/*if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %d is not positive %f", r, d);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}*/
			sol[r] = y[r];
			//BraidedNode<sparse_row_element<double> > * ni = nd->next();
			vector<sparse_row_element<double> >::iterator ni = nd+1;
			while (ni != t_row_s.end())
			{
				size_t c = (*ni).col;
				if(c < sol.size() && c > r)
				{
					sol[r] -= (*ni).val * sol[c];
				}
				else
				{
					char err[512];
					sprintf(err, "!(c %u < x.size() %u && c %u > r %d)\n", c, sol.size(), c, r);
					MessageBox(0, err, "tria_solve_of_up", MB_OK);
					return false;
				}
				ni++;
			}
			sol[r] /= d;
		}
		

		res = true;


	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	arU.Close();
	fU.Close();


	return res;


}
bool tria_solve_of_down_and_up(const char * fn_Lt, vector<double> b, vector<double> & sol)
{
	vector<double> y;

	/*long cols;
	vector<sparse_row> Lt;
	LoadMatrix(fn_Lt, Lt, cols);

	if (tria_solve_of_down(Lt, B, y))
	{
		if (tria_solve_of_up(Lt, y, sol))
		{
			return true;
		}
	}*/

		
	vector<long> file_pointers;

	long cols, rows;
	bool res = false;

	AFile f;
	if( ! f.Open( fn_Lt, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareMatrix\nUnable to open file" , fn_Lt, MB_OK);
		return false;
	}

	char buff[BUFF_SIZE];
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );
	
	try
	{
		ar >> rows;
		ar >> cols;

		if (b.size() != rows)
		{
			char err[512];
			sprintf(err, "Error: b.size() %u != rows %u\n", b.size(), rows);
			MessageBox(0, err, "tria_solve_of_down", MB_OK);
			return false;
		}

		y.resize(rows);

		file_pointers.resize(rows+1);
		file_pointers[0] = 2*sizeof(long);


		sparse_row_simple t_row_s;
		for (long r = 0; r < rows; r++)
		{
			t_row_s.clear();
			ar >> t_row_s;
			file_pointers[r+1] = file_pointers[r] + (t_row_s.size() + 1)*(sizeof(long) + sizeof(double));

//printf("tria_solve_of_down %u %u\n", r, rows);
			//BraidedNode<sparse_row_element<double> > * nd = t[r].root->next();
			vector<sparse_row_element<double> >::iterator nd = t_row_s.begin();
			if (nd == t_row_s.end())
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As row %u is missed", r);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}
			if ((*nd).col != r)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is missed", r);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}
			double d = (*nd).val;
			if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %u is not positive %f", r, d);
				MessageBox(0, err, "tria_solve_of_down", MB_OK);
				return false;
			}
			y[r] = b[r] / d;
			//BraidedNode<sparse_row_element<double> > * ni = nd->next();
			vector<sparse_row_element<double> >::iterator ni = nd+1;
			while (ni != t_row_s.end())
			{
				size_t c = (*ni).col;
				if(c < b.size() && c > r)
				{
					b[c] -= y[r] * (*ni).val;
				}
				else
				{
					char err[512];
					sprintf(err, "!(c %u < b.size() %u && c %u > r %u)\n", c, b.size(), c, r);
					MessageBox(0, err, "tria_solve_of_down", MB_OK);
					return false;
				}
				ni++;
			}

		}

		sol.resize(rows);

		for (int r = rows-1; r >= 0; r--)
		{
//printf("tria_solve_of_up %d %d\n", r, rows);

			t_row_s.clear();

			f.Seek(file_pointers[r], FILE_BEGIN);ar.ClearReadBuffer();
			ar >> t_row_s;

			//BraidedNode<sparse_row_element<double> > * nd = t[r].root->next();
			vector<sparse_row_element<double> >::iterator nd = t_row_s.begin();
			
			if (nd == t_row_s.end())
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As row %d is missed", r);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}
			if ((*nd).col != r)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %d is missed", r);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}
			double d = (*nd).val;
			if (d <= 0.0)
			{
				char err[512];
				sprintf(err, "The matrix is not positively defined\n"
					"As diagonal element at row %d is not positive %f", r, d);
				MessageBox(0, err, "tria_solve_of_up", MB_OK);
				return false;
			}
			sol[r] = y[r];
			//BraidedNode<sparse_row_element<double> > * ni = nd->next();
			vector<sparse_row_element<double> >::iterator ni = nd+1;
			while (ni != t_row_s.end())
			{
				size_t c = (*ni).col;
				if(c < sol.size() && c > r)
				{
					sol[r] -= (*ni).val * sol[c];
				}
				else
				{
					char err[512];
					sprintf(err, "!(c %u < x.size() %u && c %u > r %d)\n", c, sol.size(), c, r);
					MessageBox(0, err, "tria_solve_of_up", MB_OK);
					return false;
				}
				ni++;
			}
			sol[r] /= d;
		}
		

		res = true;


	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}
	
	ar.Close();
	f.Close();


	return res;


}
#include "..\..\surfdoc\src\Grid.h"
extern char directory[];
struct sparse_row_store
{
	FILE * stream;
	size_t rows;
	size_t r;
};
void SaveSparseRow(sparse_row_element<double> el, void * _p)
{
	sparse_row_store * p = (sparse_row_store *)_p;
	if(p)	fprintf(p->stream, "%u, %u, %f\n", el.col, p->rows-p->r-1, el.val);
}
double g_min_of_sparse_matrix;
double g_max_of_sparse_matrix;

void MakeFullRow(sparse_row_element<double> el, void * _vect)
{
	double * vect = (double *)_vect;
	vect[el.col] = el.val;

	if (g_min_of_sparse_matrix > el.val) g_min_of_sparse_matrix = el.val;
	if (g_max_of_sparse_matrix < el.val) g_max_of_sparse_matrix = el.val;
}

void SaveSparseMatrixAsDat(vector<sparse_row > & m, const char *name)
{

	size_t rows = m.size();
	//
	char file[2048];
	sprintf(file, "%s\\sparse_martix_%s.dat", directory,
		name
		);
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	FILE * dat = fopen(file, "wt");
	if (dat)
	{
		sparse_row_store p;
		p.rows = rows;
		p.stream = dat;
		for (long r = 0; r < rows; r++)
		{
			p.r = r;
			m[r].inorder(SaveSparseRow, &p);
		}
		fclose(dat);
	}
}

void SaveSparseMatrixAsGrid(vector<sparse_row > & m, size_t cols, const char *name)
{
	g_min_of_sparse_matrix = DBL_MAX;
	g_max_of_sparse_matrix = -DBL_MAX;

	size_t rows = m.size();

	Grid grid;
	grid.gridSection.z = AllocDoubleMat(rows,cols);
	for (long r = 0; r < rows; r++)
	{
		for (long c = 0; c < cols; c++)
		{
			grid.gridSection.z[rows-r-1][c] = BLANK_VALUE;
		}
		m[r].inorder(MakeFullRow, grid.gridSection.z[rows-r-1]);
	}



	grid.gridSection.nCol = cols;
	grid.gridSection.nRow = rows;
	grid.gridSection.xLL = 0.0;
	grid.gridSection.yLL = 0.0;
	grid.gridSection.xSize = 1.0;
	grid.gridSection.ySize = 1.0;
	grid.gridSection.zMax = g_max_of_sparse_matrix;
	grid.gridSection.zMin = g_min_of_sparse_matrix;

	grid.faultSection.nTraces = 0;
	grid.faultSection.nVertices = 0;
	grid.faultSection.traces = NULL;
	grid.faultSection.vertexes = NULL;


	//
	char file[2048];
	sprintf(file, "%s\\sparse_martix_%s.grd", directory,
		name
		);
	char * p;
	while (p=strchr (file,'\"'))
	{
		*p = '_';
	}
	SaveAsSurfer7Grid(file, &grid);
}

// решаем систему исходя из готовых множителей Холесского
/*bool solve_using_Holesski_tria_matrixes(vector<sparse_row_simple > L, vector<double> & B, vector<double> & x)
{
	vector<double> y;

	if (Holesski(L))
	{
	//SaveSparseMatrixAsGrid(L, L.size(), "L");
#if 0
		vector<sparse_row> Lt = Transponate(L, cols);
		double ssum3 = 0.0;
		for (i = 0; i < cols; i++)
		{
			// формируем строку квадратной системы уравнений
			for (c = i; c < cols; c++)
			{
				// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
				// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
				double A_i_c  = at[i].ScalarProduct_fast(at[c]);
				//double A_i_c2 = L[i].ScalarProduct_fast(Lt[c]);
				double A_i_c3 = Lt[i].ScalarProduct_fast(Lt[c]);

				double dd3 = A_i_c - A_i_c3;	
				//printf("%u %u %u %e %e %e\n", i, c, cols, A_i_c, A_i_c3, dd3);
				ssum3 += dd3*dd3;
			}			
		}
			
		printf("\n\tssum of Holesski = %e\n\n", ssum3);
#endif
		if (tria_solve_of_down(L, B, y))
		{
#if 0
			double ssum = 0.0;

			for (i = 0; i < cols; i++)
			{
				double d2 = Lt[i].ScalarProduct(y) - B[i];
				printf("\t%e\n", d2);
				ssum += d2*d2;
			}
			printf("\tssum of tria_solve_of_down = %e\n", ssum);
#endif
			if (tria_solve_of_up(L, y, x))
			{
#if 0
				double ssum = 0.0;

				for (i = 0; i < cols; i++)
				{
					double d2 = L[i].ScalarProduct(x) - y[i];
					printf("\t\t%e\n", d2);
					ssum += d2*d2;
				}

				printf("\t\tssum of tria_solve_of_up = %e\n", ssum);

				for (i = 0; i < cols; i++)
				{
			printf("%u %u ", i, cols);
					// формируем строку квадратной системы уравнений
					row.clear();
					size_t row_size = 0;
					for (c = 0; c < cols; c++)
					{
						// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
						// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);

						double A_i_c = at[i].ScalarProduct_fast(at[c]);


						// printf(" %f %f \n", A_i_c, B[i]);

						if (row.put(c, A_i_c))
							row_size++;
					}
					printf("%u\t",row_size);
					//A.push_back(row);
								
					//B[i]         = at[i].ScalarProduct(b);

					printf("%e\n", row.ScalarProduct(x) - B[i]);

				}
#endif
#if 0
	vector<double> x2 = x;
	for (int i = 0; i < neqns; i++)
	{
		x[i] = x2[iperm[i]];
	}
#endif
				return true;

			}
		}
	}

	return false;
}

*/


bool solve_using_Holesski_tria_matrixes(vector<sparse_row > Lt, vector<double> & B, vector<double> & x)
{
	vector<double> y;

	DWORD 
		time_eplased,
		time_start = GetCurrentTime(),
		time_current,
		time_pre_current = time_start;

	if (Holesski(Lt))
	//if (Holesski3(Lt))
	{
		time_current = GetCurrentTime();
		time_eplased = time_current - time_pre_current;
		time_pre_current = time_current;

		printf("solve_using_Holesski_tria_matrixes, time_eplased on Holesski %d %d millisec\n", time_eplased, time_current - time_start);

		if (tria_solve_of_down(Lt, B, y))
		{
			if (tria_solve_of_up(Lt, y, x))
			{
				return true;
			}
		}
	}

	return false;
}
#define BUFF_SIZE_ 1024
bool solve_using_Holesski_tria_matrixes_(vector<sparse_row > Lt, vector<double> & B, vector<double> & x)
{
	printf("solve_using_Holesski_tria_matrixes_\n");


	StoreMatrix("At.smf", Lt, Lt.size());	
	SparseStructureToMetafile("At.smf", "At.emf");

	vector<sparse_row> G;
	vector<double> diag;
	vector<int> xadj, adjncy;
	vector<double> values;

	if (!Graf_from_matrix(Lt, true, G, diag))
	{
		return false;
	}
	if (!Graf_to_vectors(G, xadj, adjncy, values))
	{
		return false;
	}

	int neqns = Lt.size();
	int * perm = new int[neqns];
	int * invp = new int[neqns];
	vector<bool> mask(neqns);
	vector<int> xls(neqns);
	GENRCM(neqns, xadj, adjncy, perm, mask, xls);

	for (int i = 0; i < neqns; i++)
	{
		invp[perm[i]] = i;
	}

	vector<sparse_row > Lt2;
	Matrix_from_vectors(xadj, adjncy, values, diag, invp, Lt2);

	vector<double> Bp(neqns);
	for (int i = 0; i < neqns; i++)
	{
		Bp[i] = B[perm[i]];
	}
		
	StoreMatrix("At2.smf", Lt2, Lt2.size());
	SparseStructureToMetafile("At2.smf", "At2.emf");
	
	vector<double> y;

	if (Holesski(Lt2))
	{
		StoreMatrix("Lt2.smf", Lt2, Lt2.size());
		SparseStructureToMetafile("Lt2.smf", "Lt2.emf");
		
		if (tria_solve_of_down(Lt2, Bp, y))
		{
			vector<double> xp;
			if (tria_solve_of_up(Lt2, y, xp))
			{
				for (int i = 0; i < neqns; i++)
				{
					x[i] = xp[invp[i]];
				}
				return true;
			}
		}
	}



	//vector<sparse_row > L = A;
#if 0
	if (Holesski(L))
	{
	//SaveSparseMatrixAsGrid(L, L.size(), "L");
#if 0
		vector<sparse_row> Lt = Transponate(L, cols);
		double ssum3 = 0.0;
		for (i = 0; i < cols; i++)
		{
			// формируем строку квадратной системы уравнений
			for (c = i; c < cols; c++)
			{
				// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
				// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
				double A_i_c  = at[i].ScalarProduct_fast(at[c]);
				//double A_i_c2 = L[i].ScalarProduct_fast(Lt[c]);
				double A_i_c3 = Lt[i].ScalarProduct_fast(Lt[c]);

				double dd3 = A_i_c - A_i_c3;	
				//printf("%u %u %u %e %e %e\n", i, c, cols, A_i_c, A_i_c3, dd3);
				ssum3 += dd3*dd3;
			}			
		}
			
		printf("\n\tssum of Holesski = %e\n\n", ssum3);
#endif
		if (tria_solve_of_down(L, B, y))
		{
#if 0
			double ssum = 0.0;

			for (i = 0; i < cols; i++)
			{
				double d2 = Lt[i].ScalarProduct(y) - B[i];
				printf("\t%e\n", d2);
				ssum += d2*d2;
			}
			printf("\tssum of tria_solve_of_down = %e\n", ssum);
#endif
			if (tria_solve_of_up(L, y, x))
			{
#if 0
				double ssum = 0.0;

				for (i = 0; i < cols; i++)
				{
					double d2 = L[i].ScalarProduct(x) - y[i];
					printf("\t\t%e\n", d2);
					ssum += d2*d2;
				}

				printf("\t\tssum of tria_solve_of_up = %e\n", ssum);

				for (i = 0; i < cols; i++)
				{
			printf("%u %u ", i, cols);
					// формируем строку квадратной системы уравнений
					row.clear();
					size_t row_size = 0;
					for (c = 0; c < cols; c++)
					{
						// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
						// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);

						double A_i_c = at[i].ScalarProduct_fast(at[c]);


						// printf(" %f %f \n", A_i_c, B[i]);

						if (row.put(c, A_i_c))
							row_size++;
					}
					printf("%u\t",row_size);
					//A.push_back(row);
								
					//B[i]         = at[i].ScalarProduct(b);

					printf("%e\n", row.ScalarProduct(x) - B[i]);

				}
#endif
#if 0
	vector<double> x2 = x;
	for (int i = 0; i < neqns; i++)
	{
		x[i] = x2[iperm[i]];
	}
#endif
				return true;

			}
		}
	}

#endif
	return false;
}

void Transponate(vector<sparse_row > & a, size_t cols, vector<sparse_row> & at)
{
	size_t rows = a.size();
    //представление матрицы в транспонированном виде
	at.clear();
	at.resize(cols);
	size_t r, c;
	for (r = 0; r < rows; r++)
	{
		for (a[r].first(); !a[r].isHead(); a[r].next())
		{
			c = a[r].val().col;
			at[c].put(r, a[r].val().val);
		}
	}
}
void Transponate(vector<sparse_row_simple > & a, size_t cols, vector<sparse_row_simple> & at)
{
	size_t rows = a.size();
    //представление матрицы в транспонированном виде
	at.clear();
	at.resize(cols);
	size_t r, c;
	for (r = 0; r < rows; r++)
	{
		for (std::vector<sparse_row_element<double> >::iterator it = a[r].begin(); it != a[r].end(); it++)
		{
			c = (*it).col;
			at[c].put(r, (*it).val);
		}
	}
}
void Transponate(vector<sparse_row_map > & a, size_t cols, vector<sparse_row_map> & at)
{
	size_t rows = a.size();
    //представление матрицы в транспонированном виде
	at.clear();
	at.resize(cols);
	size_t r, c;
	for (r = 0; r < rows; r++)
	{
		for (std::map<size_t, double>::iterator it = a[r].begin(); it != a[r].end(); it++)
		{
			c = (*it).first;
			at[c].put(r, (*it).second);
		}
	}
}
#if SPARSE_ROW_EX
void Transponate_ex(double alpha, vector<sparse_row > & a, size_t cols, vector<double> & b, vector<sparse_row> & at)
{
	size_t rows = a.size();
    //представление матрицы в транспонированном виде
	at.clear();
	at.resize(cols);
	size_t r, c;
	for (r = 0; r < rows; r++)
	{
		if(a[r]._order > 0)
		{
			for (a[r].first(); !a[r].isHead(); a[r].next())
			{
				c = a[r].val().col;
				at[c].put(r, a[r].val().val * alpha);
			}
			b[r] *= alpha;
		}
		else
		{
			for (a[r].first(); !a[r].isHead(); a[r].next())
			{
				c = a[r].val().col;
				at[c].put(r, a[r].val().val);
			}
		}
	}
}
void Transponate_use_weight(vector<sparse_row > & a, size_t cols, vector<double> & b, vector<sparse_row> & at)
{
	size_t rows = a.size();
    //представление матрицы в транспонированном виде
	at.clear();
	at.resize(cols);
	size_t r, c;
	for (r = 0; r < rows; r++)
	{
		for (a[r].first(); !a[r].isHead(); a[r].next())
		{
			c = a[r].val().col;
			at[c].put(r, a[r].val().val * a[r]._weight);
		}
		b[r] *= a[r]._weight;
	}
}
bool SLAU10(vector<sparse_row > & a,
		  size_t cols, vector<double> & alpha,
		  vector<double> & b,
		  vector<double> & sol)
{
	printf("Slau10\n");

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate_use_weight(a, cols, b, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
		B[i]         = at[i].ScalarProduct(b);
		// формируем строку квадратной системы уравнений
		row.clear();
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				A_i_c += 1.0*alpha[i];
				B[i]  += sol[i]*alpha[i];
			}
			row.put(c, A_i_c);
		}			
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, sol);
}

#endif



bool SLAU_excl(size_t prec_eqns,
			   vector<sparse_row > & a,
			   size_t cols, vector<double> & valpha,
			   vector<double> & b,
			   vector<double> & sol)
{
	printf("SLAU_excl\n");

	size_t rows = a.size();
		
	printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, a.size(), GetRealColsNumber(a,cols));


	// делаем копию матрицы и колонки правых частей
    vector<sparse_row> a_copy = a;
	vector<double> b_copy = b;

	printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, a_copy.size(), GetRealColsNumber(a_copy,cols));

	// номера неисключённых (существующих) строк и колонок
	vector<bool> exist_row(rows, true); 
	vector<bool> exist_sol(cols, true); 

	// перебираем все точные уравнения
	// из каздого точного уравнения последнюю значимую переменную решения выражаем через остальные
	// и исключаем из всех остальных строк уравнений


	for (size_t ir = 0; ir < prec_eqns; ir++)
	{
		size_t excl_col_ir = a_copy[ir].last().col;
		double excl_val_ir = a_copy[ir].last().val;
		
		exist_row[ir] = false;

		if (excl_col_ir < cols)
			exist_sol[excl_col_ir] = false;
		else
		{
			//MessageBox(0, "excl_col_ir >= cols !!!", "SLAU_excl error", 0);
			printf("SLAU_excl error excl_col_ir >= cols !!!\n");
			return false;
		}

		for (size_t r = 0; r < rows; r++)
		{
			if(exist_row[r])
			{
				BraidedNode<sparse_row_element<double> > * n = a_copy[r].root->rchild();
				if(a_copy[r]._find(sparse_row_element<double>(excl_col_ir, 0.0), n))
				{
					double excl_val_r = n->val.val;
					double m = excl_val_r / excl_val_ir;

					a_copy[r].remove(sparse_row_element<double>(excl_col_ir, 0.0));					
					b_copy[r] -= b_copy[ir] * m;
					
					a_copy[ir].last();
					a_copy[ir].prev();
					for( ;!a_copy[ir].isHead(); a_copy[ir].prev())
					{
						size_t c = a_copy[ir].val().col;
						double v = a_copy[ir].val().val;

						a_copy[r].plus(c, - v * m);
					}
				}
			}
		}
	//printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, a_copy.size(), GetRealColsNumber(ir+1, a_copy, cols));
	}

	// решаем вторую систему из неточных строк 
	// и неисключёных неизвестных
	size_t rows2 = rows - prec_eqns;
	size_t cols2 = cols - prec_eqns;


	    
	//представление матрицы в транспонированном виде
	vector<sparse_row> at_copy;
	at_copy.resize(cols);
	size_t r, c, cc;
	for (r = 0; r < rows; r++)
	{
		if(exist_row[r])
		{
			for (a_copy[r].first(); !a_copy[r].isHead(); a_copy[r].next())
			{
				c = a_copy[r].val().col;
				at_copy[c].put(r, a_copy[r].val().val);
			}
		}
	}

	printf("a_copy cols = %d, rows = %u, real_cols_number = %u\n", rows, at_copy.size(), GetRealColsNumber( at_copy, rows));

//MessageBox(0, "SLAU_excl", "SLAU_excl", 0);

	vector<sparse_row > A(cols2);
	vector<double> B(cols2);

	//sparse_row row;
	for (size_t i = 0, ii = 0; i < cols; i++)
	{
		if(exist_sol[i])
		{
			B[ii]         = at_copy[i].ScalarProduct(b_copy);
			// формируем строку квадратной системы уравнений
			//row.clear();
			for (c = i, cc = ii; c < cols; c++)
			{
				if(exist_sol[c])
				{
					// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
					// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
					double A_i_c = at_copy[i].ScalarProduct_fast(at_copy[c]);
					if (c == i)
					{
						A_i_c += 1.0*valpha[i];
						B[ii]  += sol[i]*valpha[i];
					}
					A[ii].put(cc, A_i_c);
					cc++;
				}
			}			
			//A.push_back(row);
			ii++;
		}
	}
	vector<double> sol2(cols2, 0.0);
	
	printf("A cols = %d, rows = %u, real_cols_number = %u\n", cols2, A.size(), GetRealColsNumber(A,cols2));

	//return solve_using_Holesski_tria_matrixes(A, B, sol);
	if (!solve_using_Holesski_tria_matrixes_(A, B, sol2))
	{
		return false;
	}
	vector <size_t> vic1(cols, 0);
	for (size_t c = 0, ic1 = 0, ic2 = 0; c < cols; c++)
	{
		if(exist_sol[c])
		{
			sol[c] = sol2[ic2];
			ic2++;
		}
		else
		{
			vic1[c] = ic1;
			ic1++;
		}
	}
	// из точных уравненй исключаем sol2 
	// перенося их в правую часть и получаем новую систему, 
	// для решения методом Гаусса
	size_t rows1 = prec_eqns;
	vector<sparse_row> a1(rows1);
	vector<double> b1(rows1);

	for (size_t r = 0, ir = 0; r < rows; r++)
	{
		if(!exist_row[r])
		{
			//a1[ir] = a[r];
			b1[ir] = b[r];
			for (a[r].first(); !a[r].isHead(); a[r].next())
			{
				c = a[r].val().col;
				double v = a[r].val().val;
				if(exist_sol[c])
				{
					b1[ir] -= sol[c] * v;
				}
				else
				{
					a1[ir].put(vic1[c], v);
				}
			}
			ir++;
		}
	}

	vector<double> sol1;

	lesgausssolve_find_max(a1, a1.size(), a1.size(), b1, sol1, 0.0);

	for (size_t c = 0; c < cols; c++)
	{
		if(!exist_sol[c])
		{
			sol[c] = sol1[vic1[c]];
		}
	}


return true;

}


bool SLAU9(vector<sparse_row > & a,
		  size_t cols, vector<double> & alpha,
		  vector<double> & b,
		  vector<double> & sol)
{
	printf("Slau9\n");

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
		B[i]         = at[i].ScalarProduct(b);
		// формируем строку квадратной системы уравнений
		row.clear();
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				A_i_c += 1.0*alpha[i];
				B[i]  += sol[i]*alpha[i];
			}
			row.put(c, A_i_c);
		}			
		A.push_back(row);
	}

	//return solve_using_Holesski_tria_matrixes(A, B, sol);
	return solve_using_Holesski_tria_matrixes_(A, B, sol);
}
bool SLAU_Tichonov(vector<sparse_row > & a,
		  size_t cols, double alpha,
		  vector<double> & b,
		  vector<double> & sol)
{
	printf("SLAU_Tichonov\n");

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
		B[i]         = at[i].ScalarProduct(b);
		// формируем строку квадратной системы уравнений
		row.clear();
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				A_i_c += alpha;
			}
			row.put(c, A_i_c);
		}			
		A.push_back(row);
	}

	bool result = solve_using_Holesski_tria_matrixes(A, B, sol);
	// Вектор невязки
	vector<double> E(rows); // вектор невязки
	for (size_t r = 0; r < rows; r++)
	{
		E[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E[r] += a[r].ScalarProduct(sol);
	}
	double sE = SquareSum(E);
	printf("\t\tSLAU_Tichonov sE = %e\n", sE);

	return result;
}
bool SLAU8(vector<sparse_row > & a,
		  size_t cols, double alpha,
		  vector<double> & b,
		  vector<double> & sol)
{
	printf("Slau8\n");

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
		B[i]         = at[i].ScalarProduct(b);
		// формируем строку квадратной системы уравнений
		row.clear();
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				A_i_c += 1.0*alpha;
				B[i]  += sol[i]*alpha;
			}
			row.put(c, A_i_c);
		}			
		A.push_back(row);
	}

	bool result = solve_using_Holesski_tria_matrixes(A, B, sol);
					
	// Вектор невязки
	vector<double> E(rows); // вектор невязки
	for (size_t r = 0; r < rows; r++)
	{
		E[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E[r] += a[r].ScalarProduct(sol);
	}
	double sE = SquareSum(E);
	printf(" SLAU8 sE = %e\n", sE);

	return result;
}
#if SPARSE_ROW_EX

bool SLAU7(vector<sparse_row > & a,
		  size_t cols, size_t nk, vector<double> & base_points_z,
		  vector<double> & b,
		  vector<double> & x)
{
	printf("Slau4\n");

	double alpha  = 0.5;

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, r, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate_ex(0.1, a, cols, b, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// формируем строку квадратной системы уравнений
		row.clear();
		size_t row_size = 0;
		B[i]         = at[i].ScalarProduct(b);
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
				//if (a[i]._order > 0)
				if (i%nk == 0)
				{
					A_i_c += 1.0*alpha;
					B[i]  += base_points_z[i/nk]*alpha;
				printf ("%f ", A_i_c);
				}
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
printf("%u\n",row_size);
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, x);
}

#endif
bool SLAU6(vector<sparse_row > & a,
		  size_t cols, size_t nk, vector<double> & base_points_z,
		  vector<double> & b,
		  vector<double> & x)
{
	printf("Slau4\n");

	double alpha  = 0.5;

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, r, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// формируем строку квадратной системы уравнений
		row.clear();
		size_t row_size = 0;
		B[i]         = at[i].ScalarProduct(b);
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
				//if (a[i]._order > 0)
				if (i%nk == 0)
				{
					A_i_c += 1.0*alpha;
					B[i]  += base_points_z[i/nk]*alpha;
				printf ("%f ", A_i_c);
				}
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
printf("%u\n",row_size);
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, x);
}
#if SPARSE_ROW_EX

bool SLAU5(vector<sparse_row > & a,
		  size_t cols,
		  vector<double> b,
		  vector<double> & x)
{
	printf("Slau4\n");

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, r, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate_ex(0.0001, a, cols, b, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// формируем строку квадратной системы уравнений
		row.clear();
		size_t row_size = 0;
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
		B[i]         = at[i].ScalarProduct(b);
printf("%u\n",row_size);
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, x);
}
#endif
bool SLAU4(vector<sparse_row > & a,
		  size_t cols, size_t nk, size_t lc,
		  vector<double> & b,
		  vector<double> & x)
{
	printf("Slau4\n");

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, r, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// формируем строку квадратной системы уравнений
		row.clear();
		size_t row_size = 0;
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
				//if (a[i]._order > 0)
				if (i%nk > lc)
				{
					A_i_c += 1.0;
				printf ("%f ", A_i_c);
				}
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
		B[i]         = at[i].ScalarProduct(b);
printf("%u\n",row_size);
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, x);
}
bool SLAU3(vector<sparse_row_simple > & a,
		  size_t cols,
		  vector<double> & b,
		  vector<double> & x)
{
	printf("Slau3 cols = %u\n",  cols);

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, r, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row_simple> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// формируем строку квадратной системы уравнений
		row.clear();
		size_t row_size = 0;
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
		B[i]         = at[i].ScalarProduct(b);
printf("%u\n",row_size);
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, x);
}
bool SLAU3(vector<sparse_row > & a,
		  size_t cols,
		  vector<double> & b,
		  vector<double> & x)
{
	printf("Slau3 cols = %u\n",  cols);

	// решение уравнения методом наименьших квадратов
	// из прямоугольной разреженной матрицы 
	// формируем квадратную систему уравнений
	
	size_t rows = a.size();
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t i, r, c;
    //представление матрицы в транспонированном виде
	vector<sparse_row> at;
	Transponate(a, cols, at);

	vector<sparse_row > A;
	vector<double> B(cols);

	sparse_row row;
	for (i = 0; i < cols; i++)
	{
printf("%u %u ", i, cols);
		// формируем строку квадратной системы уравнений
		row.clear();
		size_t row_size = 0;
		for (c = i; c < cols; c++)
		{
			// A[i][c] = sum(a[r][i]*a[r][c], r=1..rows);
			// B[i]    = sum(a[r][i]*b[r]   , r=1..rows);
			double A_i_c = at[i].ScalarProduct_fast(at[c]);
			if (c == i)
			{
				printf ("%u %f ", c, A_i_c);
			}

			// printf(" %f %f \n", A_i_c, B[i]);

			if (row.put(c, A_i_c))
				row_size++;
		}			
		B[i]         = at[i].ScalarProduct(b);
printf("%u\n",row_size);
		A.push_back(row);
	}

	return solve_using_Holesski_tria_matrixes(A, B, x);
}
bool SLAU(vector<sparse_row > & A,
		  size_t cols,
		  vector<double> & b,
		  vector<double> & x,
		  // накладываем дополнительные условия на решение системы уравнений
		  void (*pSlauAdditionalConditions)(
		  vector<double> & x,
		  double & add_F,
		  vector<double> & add_dFdx,
		  vector<double> & add_d2Fdx2,
		  void * _param),

		  void * _param)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		 r, c;
	int	maxq = 100; //
	double  // Приближение - норма векторав невязки
		//part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		//part_down = 0.1, //
		//mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		//mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 1.0e-8, // минимальное значение коэффициента скорости обучения
		maxetha = 10000, // максимальное значение коэффициента скорости обучения
		little_up = 1.05, // параметры подстройки коэффициента скорости обучения
		little_down = 0.8, //
		much_down = 0.49, //
		etha = 1.2, // начальное значение коэффициента скорости обучения
		F
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols); // вектор величины подстройки весов на текущей итерации
		//dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		//vF(cols); // вектор функционала

	bool not_inertio = false;
	bool to_init = true;
	if(to_init)
	{
		if (rows >= cols)
		{
			// система переопределена
			double epsilon = 0.0;
			if (!lesgausssolve_find_max(A, A.size(), cols, b, x, epsilon))
			{
				printf("system was not solved\n");
				x.resize(cols); // вектор решения
				for (c = 0; c < cols; c++)
				{
					x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
					x[c] = 0.0;
				}
			}

		}
		else // если система недоопределена
		{
			x.resize(cols,1.0); // вектор решения
			for (c = 0; c < cols; c++)
			{
				x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
				x[c] = 0.0;
			}
		}
	}
	// Вектор невязки
	for (r = 0; r < rows; r++)
	{
		E[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E[r] += A[r].ScalarProduct(x);
	}

	//Цикл подстройки

	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	for (r = 0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			double avv = A[r].val().val;
			d2Fdx2[c] += avv * avv;
		}
	}
	size_t empty_cols = 0;
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
		if (d2Fdx2[c] == 0.0)
		{
			empty_cols++;
			printf("We have the zero colomn number = %u\n", c);
		}
	}
	if (empty_cols > 0)
	{
		char err[1024];
		sprintf(err, "The system was not solved as we have %u empty colomns\n", empty_cols);
		printf(err);
		MessageBox(0, err, "SLAU", MB_OK);
		return false;
	}

	double norm_dFdx = 1.0;
	
	double add_F;
	vector<double> add_dFdx(cols);
	vector<double> add_d2Fdx2(cols);
	pSlauAdditionalConditions(x,add_F,add_dFdx,add_d2Fdx2,_param);

	double sE = SquareSum(E);
	double sx = SquareSum(x);
	F = sE + add_F;// + alpha * sx;
	printf ("F = %e, sE = %e, add_F = %e\n", F, sE, add_F);
		
	double F_old = F;
	double add_F_old = add_F;

	int q = 0;
	do
	{
		q++;

		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = 0.0;//alpha[c] * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			for (A[r].first(); !A[r].isHead(); A[r].next())
			{
				c = A[r].val().col;                        
				dFdx[c] += E[r] * A[r].val().val;
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0;
			dFdx[c] += add_dFdx[c];
			dFdx[c] /= (d2Fdx2[c] + add_d2Fdx2[c]);
		}   

		norm_dFdx = sqrt(SquareSum(dFdx));

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			// Алгоритм подстройки с использованием инерционного члена
			if (q == 1 || not_inertio)
				dx[c] = etha * dFdx[c] / norm_dFdx;
			else // используем инерционный член
			{
				// предыдущий прирост умножаем на инерционный коэффициент
				dx[c] *= inertio; 
				// результат суммируем с текущим приростом элемента вектора решения
				dx[c] += etha * dFdx[c] / norm_dFdx;
			}
			//Подстраиваем элемент вектора x
			x[c] -= dx[c];			
		}
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			E[r] += A[r].ScalarProduct(x);
		}
		sE = SquareSum(E);
		pSlauAdditionalConditions(x,add_F,add_dFdx,add_d2Fdx2,_param);
		F = sE + add_F;

		double dF = F - F_old;
		double d_add_F = add_F - add_F_old;

		printf("d_add_F = %e\n", d_add_F);


		sx = SquareSum(x);//sx = ScalarProduct(alpha, sx);
		//F = sE;// + alpha * sx;

		if (dF > 0)
		{
#if 1					
			for (c = 0; c < cols; c++)
			{
				x[c] += dx[c];
				if(!not_inertio)
				{
					dx[c] -= etha * dFdx[c] / norm_dFdx;                    
					dx[c] /= inertio; 
				}
			}
			etha *= little_down;
			printf ("etha = %e\t", etha);
			// не вышли ли за пределы нижней границы?
			if(etha < minetha)
			{
				etha = minetha;
			}
				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					E[r] += A[r].ScalarProduct(x);
				}
				sE = SquareSum(E);
				pSlauAdditionalConditions(x,add_F,add_dFdx,add_d2Fdx2,_param);
				F = sE + add_F;
				dF = F - F_old;
				d_add_F = add_F - add_F_old;
#else
			bool is_minetha = false;
			while (dF > 0 && !is_minetha)
			{
				// подстройка неудачная возврат назад
				for (c = 0; c < cols; c++)
				{
					x[c] += dx[c];
					if(!not_inertio)
					{
						dx[c] -= etha * dFdx[c] / norm_dFdx;                    
						dx[c] /= inertio; 
					}
				}
				etha *= little_down;
				printf ("etha = %e\t", etha);
				if(etha < minetha)
				{
					etha = minetha;
					is_minetha = true;
				}
				else
				{
					for (c = 0; c < cols; c++)
					{
						// Алгоритм подстройки с использованием инерционного члена
						if (q == 1 || not_inertio)
							dx[c] = etha * dFdx[c] / norm_dFdx;
						else // используем инерционный член
						{
							// предыдущий прирост умножаем на инерционный коэффициент
							dx[c] *= inertio; 
							// результат суммируем с текущим приростом элемента вектора решения
							dx[c] += etha * dFdx[c] / norm_dFdx;
						}
						//Подстраиваем элемент вектора x
						x[c] -= dx[c];			
					}
				}

				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					E[r] += A[r].ScalarProduct(x);
				}
				sE = SquareSum(E);
				pSlauAdditionalConditions(x,add_F,add_dFdx,add_d2Fdx2,_param);
				F = sE + add_F;
				dF = F - F_old;
				d_add_F = add_F - add_F_old;

				printf("d_add_F = %e\n", d_add_F);
			}
#endif
		}
		else
		{
			etha *= little_up;					
			etha = etha > maxetha ? maxetha : etha;

		}
			
		F_old = F;
		add_F_old = add_F;

		printf ("%d %e %e %e %e %e ", q, sE, add_F, F, dF, d_add_F);
		printf ("%e\n", etha);

//		if (q > 10 && fabs(dF) < 0.000000001)
///			break;
	}
	while(q < maxq);

	return true;
}

bool SLAU(vector<sparse_row > & A,
		  size_t cols,
		  vector<double> & b,
		  bool to_init,
		  bool rand_not_zero_init,
		  int	maxq, 
		  vector<double> & x,
		  bool echo)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using SLAU()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		 r, c;
	//
//		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double  // Приближение - норма векторав невязки
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 1.0e-12, // минимальное значение коэффициента скорости обучения
		maxetha = 10000, // максимальное значение коэффициента скорости обучения
		little_up = 1.05, // параметры подстройки коэффициента скорости обучения
		little_down = 0.8, //
		much_down = 0.49, //
		etha = 1.2, // начальное значение коэффициента скорости обучения
		F
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала

	bool not_inertio = false;
	if(to_init)
	{
		if (rows >= cols)
		{
			// система переопределена
			double epsilon = 0.0;
			if (!lesgausssolve_find_max(A, A.size(), cols, b, x, epsilon))
			{
				printf("system was not solved\n");
				x.resize(cols); // вектор решения
				for (c = 0; c < cols; c++)
				{
					if (rand_not_zero_init)
						x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
					else
						x[c] = 0.0;
				}
			}

		}
		else // если система недоопределена
		{
			x.resize(cols,1.0); // вектор решения
			for (c = 0; c < cols; c++)
			{
				if (rand_not_zero_init)
					x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
				else
					x[c] = 0.0;
			}
		}
	}
	// Вектор невязки
	for (r = 0; r < rows; r++)
	{
		E[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E[r] += A[r].ScalarProduct(x);
	}

	//Цикл подстройки

	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	for (r = 0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			double avv = A[r].val().val;
			d2Fdx2[c] += avv * avv;
		}
	}
	size_t empty_cols = 0;
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
		if (d2Fdx2[c] == 0.0)
		{
			empty_cols++;
			printf("We have the zero colomn number = %u\n", c);
		}
	}
	if (empty_cols > 0)
	{
		char err[1024];
		sprintf(err, "The system was not solved as we have %u empty colomns\n", empty_cols);
		printf(err);
		MessageBox(0, err, "SLAU", MB_OK);
		return false;
	}

	double norm_dFdx = 1.0;

	double sE = SquareSum(E);
	double sx = SquareSum(x);
	F = sE;// + alpha * sx;
	if (echo) printf ("F = %e, sE = %e, sx = %e\n", F, sE, sx);
		
	double sE_old = sE;

	int q = 0;
	do
	{
		q++;
		


		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = 0.0;//alpha[c] * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			for (A[r].first(); !A[r].isHead(); A[r].next())
			{
				c = A[r].val().col;                        
				dFdx[c] += E[r] * A[r].val().val;
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0 / d2Fdx2[c];
		}

		norm_dFdx = sqrt(SquareSum(dFdx));



		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{

			// Алгоритм подстройки с использованием инерционного члена
			if (q == 1 || not_inertio)
				dx[c] = etha * dFdx[c] / norm_dFdx;
			else // используем инерционный член
			{
				// предыдущий прирост умножаем на инерционный коэффициент
				dx[c] *= inertio; 
				// результат суммируем с текущим приростом элемента вектора решения
				dx[c] += etha * dFdx[c] / norm_dFdx;
			}
			//Подстраиваем элемент вектора x
			x[c] -= dx[c];			
		}
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			E[r] += A[r].ScalarProduct(x);
		}
		sE = SquareSum(E);

		double dE = sE - sE_old;

		sx = SquareSum(x);//sx = ScalarProduct(alpha, sx);
		//F = sE;// + alpha * sx;

		if (dE > 0)
		{
#if 0					
			etha *= little_down;
			// не вышли ли за пределы нижней границы?
			if(etha < minetha)
			{
				etha = minetha;
			}
#else
			bool is_minetha = false;
			while (dE > 0 && !is_minetha)
			{
				// подстройка неудачная возврат назад
				for (c = 0; c < cols; c++)
				{
					x[c] += dx[c];
					if(!not_inertio)
					{
						dx[c] -= etha * dFdx[c] / norm_dFdx;                    
						dx[c] /= inertio; 
					}
				}
				etha *= little_down;				
				if(etha < minetha)
				{
					etha = minetha;
					is_minetha = true;
				}
				else
				{
					for (c = 0; c < cols; c++)
					{
						// Алгоритм подстройки с использованием инерционного члена
						if (q == 1 || not_inertio)
							dx[c] = etha * dFdx[c] / norm_dFdx;
						else // используем инерционный член
						{
							// предыдущий прирост умножаем на инерционный коэффициент
							dx[c] *= inertio; 
							// результат суммируем с текущим приростом элемента вектора решения
							dx[c] += etha * dFdx[c] / norm_dFdx;
						}
						//Подстраиваем элемент вектора x
						x[c] -= dx[c];			
					}
				}

				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					E[r] += A[r].ScalarProduct(x);
				}
				sE = SquareSum(E);
				dE = sE - sE_old;
			}
#endif
		}
		else
		{
			etha *= little_up;					
			etha = etha > maxetha ? maxetha : etha;

			sE_old = sE;

		}
		if (echo) printf ("%d %e %e %e %e ", q, sE, sx, norm_dFdx, dE);
		if (echo) printf ("%e\n", etha);

		if (q > 2 && fabs(dE) < 0.000000001)
			break;
	}
	while(q < maxq);

	return true;
}

bool SLAU_block(vector<sparse_row > & A,
		  size_t cols, size_t  block_size,
		  vector<double> & b,
		  vector<double> & x)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using double::Tichonov()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		 r, c;
	int	maxq = 100, //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double  // Приближение - норма векторав невязки
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 1.0e-3, // минимальное значение коэффициента скорости обучения
		maxetha = 10, // максимальное значение коэффициента скорости обучения
		little_up = 1.05, // параметры подстройки коэффициента скорости обучения
		little_down = 0.8, //
		much_down = 0.49, //
//		etha = 1.2, // начальное значение коэффициента скорости обучения
		F
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала


	bool to_init = false;
	if(to_init)
	{
		if (rows >= cols)
		{
			// система переопределена
			double epsilon = 0.00000000000;
			if (!lesgausssolve_find_max(A, A.size(), cols, b, x, epsilon))
			{
				printf("system was not solved\n");
				//return false;
				x.resize(cols); // вектор решения
				for (c = 0; c < cols; c++)
				{
					x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
					x[c] = 0.0;
				}
			}
			/*else
				return true;*/
		}
		else // если система недоопределена
		{
			x.resize(cols,1.0); // вектор решения
			for (c = 0; c < cols; c++)
			{
				x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
				x[c] = 0.0;
			}
		}
	}
	// Вектор невязки
	for (r = 0; r < rows; r++)
	{
		E[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E[r] += A[r].ScalarProduct(x);
	}

	//Цикл подстройки

	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	for (r = 0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			double avv = A[r].val().val;
			d2Fdx2[c] += avv * avv;
		}
	}
	size_t empty_cols = 0;
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
		if (d2Fdx2[c] == 0.0)
		{
			empty_cols++;
			printf("We have the zero colomn number = %u\n", c);
		}
	}
	if (empty_cols > 0)
	{
		char err[1024];
		sprintf(err, "The system was not solved as we have %u empty colomns\n", empty_cols);
		printf(err);
		MessageBox(0, err, "SLAU", MB_OK);
		return false;
	}

	double norm_dFdx = 1.0;

	double sE = SquareSum(E);
	double sx = SquareSum(x);
	F = sE;// + alpha * sx;
	printf ("F = %e, sE = %e, sx = %e\n", F, sE, sx);

	size_t n_blocks = cols / block_size;
		
	vector<double> etha(n_blocks, 1.2); // начальное значение коэффициента скорости обучения

		
	double sE_old = sE;

bool not_inertio = true;

	int q = 0;
	do
	{
		q++;

		for (size_t i_block = 0; i_block < n_blocks; i_block++)
		{
		


		// попробуем изменить первоначальный алгоритм
		// вынести вычисление первой производной 
		// перед общим циклом подстройки
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx[c] = 0.0;//alpha[c] * x[c];
		}
		for (r = 0; r < rows; r++)
		{
			for (A[r].first(); !A[r].isHead(); A[r].next())
			{
				c = A[r].val().col;                        
				dFdx[c] += E[r] * A[r].val().val;
			}
		}
		for (c = 0; c < cols; c++)
		{
			dFdx[c] *= 2.0 / d2Fdx2[c];
		}

//		norm_dFdx = sqrt(SquareSum(dFdx));

		norm_dFdx = 0.0;				
		for (c = i_block*block_size; c < (i_block+1)*block_size; c++)
		{
			norm_dFdx += dFdx[c]*dFdx[c];
		}
		norm_dFdx = sqrt(norm_dFdx);




		// Перебираем все элементы x
		for (c = i_block*block_size; c < (i_block+1)*block_size; c++)
		{
			// Алгоритм подстройки с использованием инерционного члена
			if (q == 1 || not_inertio)
				dx[c] = etha[i_block] * dFdx[c] / norm_dFdx;
			else // используем инерционный член
			{
				// предыдущий прирост умножаем на инерционный коэффициент
				dx[c] *= inertio; 
				// результат суммируем с текущим приростом элемента вектора решения
				dx[c] += etha[i_block] * dFdx[c] / norm_dFdx;
			}
			//Подстраиваем элемент вектора x
			//printf("dx[%d] = %e = etha[c] %e * dFdx[c] %e\n", c, dx[c], etha[c], dFdx[c]);
			x[c] -= dx[c];			
		}
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			E[r] = - b[r]; // элемент вектора правых частей со знакомминус
			E[r] += A[r].ScalarProduct(x);
		}
		sE = SquareSum(E);

		double dE = sE - sE_old;

		sx = SquareSum(x);//sx = ScalarProduct(alpha, sx);
		//F = sE;// + alpha * sx;

		if (dE > 0)
		{
			bool is_minetha = false;
			while (dE > 0 && !is_minetha)
			{
				// подстройка неудачная возврат назад
				for (c = i_block*block_size; c < (i_block+1)*block_size; c++)
				{
					x[c] += dx[c];

					if(!not_inertio) 
					{
						dx[c] -= etha[i_block] * dFdx[c] / norm_dFdx;
						dx[c] /= inertio; 
					}
				}
				etha[i_block] *= little_down;	

				if(etha[i_block] < minetha)
				{
					etha[i_block] = minetha;
					is_minetha = true;
				}
				else
				{

					for (c = i_block*block_size; c < (i_block+1)*block_size; c++)
					{
						// Алгоритм подстройки с использованием инерционного члена
						if (q == 1 || not_inertio)
							dx[c] = etha[i_block] * dFdx[c] / norm_dFdx;
						else // используем инерционный член
						{
							// предыдущий прирост умножаем на инерционный коэффициент
							dx[c] *= inertio; 
							// результат суммируем с текущим приростом элемента вектора решения
							dx[c] += etha[i_block] * dFdx[c] / norm_dFdx;
						}
						//Подстраиваем элемент вектора x
						//printf("dx[%d] = %e = etha[c] %e * dFdx[c] %e\n", c, dx[c], etha[c], dFdx[c]);
						x[c] -= dx[c];			
					}
				}

				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					E[r] += A[r].ScalarProduct(x);
				}
				sE = SquareSum(E);
				dE = sE - sE_old;
			}
		}
		else
		{
			etha[i_block] *= little_up;					
			etha[i_block] = etha[i_block] > maxetha ? maxetha : etha[i_block];

			///*if (q > 2 && fabs(dE)/*SquareSum(dF)*/ < 0.000001)
			//	break;*/
		sE_old = sE;
		}
		printf ("%d %u %e %e %e %e ", q, i_block, sE, sx, norm_dFdx, dE);

		printf ("%e\n", etha[i_block]);
		}
	}
	while(q < maxq);

	return true;
}

bool SLAU2(vector<sparse_row > & A,
						  size_t cols,
						  vector<double> & b,
						  bool to_init,
						  bool rand_not_zero_init,
						  vector<double> & x)
{
	size_t rows = A.size();

	if (rows < 1 || cols < 1)
	{
		MessageBox(0, "Error using double::Tichonov(vdouble& b)\n Size < 1",
			"Error",0);
		return NULL;
	}
	if (rows != b.size())
	{
		char str[1024];
		sprintf(str, 
			"Error using double::Tichonov()\n"
			"Size of vector %i must be equial to size of matrix = %i %i", 
			b.size(), rows, cols);
		MessageBox(0, str,"Error",0);
		return NULL;
	}
	size_t 
		i, r, c;
//		rows = m_size[0],
//		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
	int	maxq = 100, //
		MaxNotTurned = 2;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		//alpha, // регуляризационный коэффициент
		//alpha_old, // 
//		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		part_down = 0.1, //
		meanFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		//mindFdx_down = 0.1, //
		inertio = 0.4, // инерционный коэффициент
		minetha = 0.0004, // минимальное значение коэффициента скорости обучения
		maxetha = 2.5, // максимальное значение коэффициента скорости обучения
		little_up = 1.1, // параметры подстройки коэффициента скорости обучения
		little_down = 0.82, //
		much_down = 0.49, //
		etha0 = 1.2, // начальное значение коэффициента скорости обучения
		F // функционал
		//*pdx, *petha, *pvF, *pdF,*pdFdx,
		//*pE, *pb, *px, *pb0, *pM, *p2
		;
	vector<double> 
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второй производной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0); // вектор коэффициентов скорости обучения
	//	dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
	//	vF(cols); // вектор функционала

/*	pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;
*/

	// флаг настройки каждого элемента
	vector<bool> ToTurn(cols,true); 

	bool 
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
	bool not_inertio = true;
	
	if(to_init)
	{
		if (rows >= cols)
		{
			// система переопределена
			double epsilon = 0.0;
			if (!lesgausssolve_find_max(A, A.size(), cols, b, x, epsilon))
			{
				printf("system was not solved\n");
				x.resize(cols); // вектор решения
				for (c = 0; c < cols; c++)
				{
					if (rand_not_zero_init)
						x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
					else
						x[c] = 0.0;
				}
			}

		}
		else // если система недоопределена
		{
			x.resize(cols,1.0); // вектор решения
			for (c = 0; c < cols; c++)
			{
				if (rand_not_zero_init)
					x[c] = double(rand() - (RAND_MAX/2)) / double(RAND_MAX);
				else
					x[c] = 0.0;
			}
		}
	}

	// Вектор невязки
	for (r = 0; r < rows; r++)
	{
		E[r] = - b[r]; // элемент вектора правых частей со знаком минус
		E[r] += A[r].ScalarProduct(x);
	}
	vector<double> E_old(E);
	vector<double> x_old(x);

    //представление матрицы в транспонированном виде
	vector<vector<sparse_col_element> > At;

	At.resize(cols);
	for (r = 0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			At[c].push_back(sparse_col_element(r, A[r].val().val) );
		}
	}


	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;

	//p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] = 0.0;// alpha;
	}
	for (r = 0; r < rows; r++)
	{
		for (A[r].first(); !A[r].isHead(); A[r].next())
		{
			c = A[r].val().col;
			double avv = A[r].val().val;
			d2Fdx2[c] += avv * avv;
		}
	}
	size_t empty_cols = 0;
	for (c = 0; c < cols; c++)
	{
		d2Fdx2[c] *= 2.0;
		if (d2Fdx2[c] == 0.0)
		{
			empty_cols++;
			printf("We have the zero colomn number = %u\n", c);
		}
	}
	if (empty_cols > 0)
	{
		char err[1024];
		sprintf(err, "The system was not solved as we have %u empty colomns\n", empty_cols);
		printf(err);
		MessageBox(0, err, "SLAU", MB_OK);
		return false;
	}

	// вычисляем функционал после подстройки очередного элемента вектора решения
	//F = SquareSum(E) + alpha * SquareSum(x);
	double sE = SquareSum(E);
	double sx = SquareSum(x);
	F = sE;// + alpha * sx;
	printf ("F = %e, sE = %e, sx = %e\n", F, sE, sx);
				
	double F_old = F;

	ToTurn.resize(cols,true);
	int q = 0;
	do
	{
		q++;
printf("Tichoniv q = %d\n", q);
		NotFailed = true; // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement = false; // флаг необходимости настройки хоть одного элемента вектора решения
//		alpha_old = alpha;
		// Приближение
		// Регуляризационный коэффициент
/*		if (AlphaNonZero)
		{
			xS = SquareSum(E) / SquareSum(x);
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;
		// Поправка второй производной
		for (c = 0; c < cols; c++)
			d2Fdx2[c] += 2.0*(alpha - alpha_old);*/

/*
						// заново вычисляем вектор невязки
						for (r = 0; r < rows; r++)
						{
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							E[r] += A[r].ScalarProduct(x);
						}
						// восстанавливаем прежнее значение функционала
						F = SquareSum(E);// + alpha * SquareSum(x);
*/

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
printf ("%d %u %u\t", q, c, cols);
#if 0
//{ТУТ ОЧЕНЬ ДОЛГО!!!
			// Вычисляем первую производную
			dFdx[c] = 0.0;//alpha * x[c];
			for (r = 0; r < rows; r++)
			{
				dFdx[c] += E[r] * A[r][c];					
			}
			dFdx[c] *= 2.0 / d2Fdx2[c];
//}ТУТ ОЧЕНЬ ДОЛГО!!!
#else
			// Вычисляем первую производную
			dFdx[c] = 0.0;//alpha * x[c];
			size_t col_len = At[c].size();
			for (size_t ir = 0; ir < col_len; ir++)
			{
				dFdx[c] += E[At[c][ir].row] * At[c][ir].val;					
			}
			dFdx[c] *= 2.0 / d2Fdx2[c];
#endif 

			if (q > 1)
			{
				//
				//printf ("%f < %f\t", fabs(dFdx[c]), meanFdx);
				if ( fabs(dFdx[c]) < meanFdx)
					ToTurn[c] = false;
				else
					ToTurn[c] = true;
			}

			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;

				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1 || not_inertio)
					dx[c] = etha[c] * dFdx[c];
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					dx[c] *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					dx[c] += etha[c] * dFdx[c];
				}
				//Подстраиваем элемент вектора x
				x[c] -= dx[c];
#if 0
//{ТУТ ОЧЕНЬ ДОЛГО!!!
				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					E[r] += A[r].ScalarProduct(x);
				}
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E);// + alpha * SquareSum(x);
//}ТУТ ОЧЕНЬ ДОЛГО!!!
#else

				// Вектор невязки
				for (size_t ir = 0; ir < col_len; ir++)
				{
					r = At[c][ir].row;
					//E[r] -= x_old[c] * At[c][ir].val;
					//E[r] += x[c] * At[c][ir].val;
#if 0
					E[r] += (x[c] - x_old[c]) * At[c][ir].val;
					x_old[c] = x[c];
					//E[r] = - b[r]; // элемент вектора правых частей со знакомминус
					//E[r] += A[r].ScalarProduct(x);
					double E_r = A[r].ScalarProduct(x) - b[r];
					if (E[r] != E_r)
					{
						printf ("\n %u %f ", r,  E[r]);
						printf ("%f ", E_r);
					}
#else
					E[r] = A[r].ScalarProduct(x) - b[r];
#endif

					//F += E[r] * E[r] - E_old[r] * E_old[r];
					//E_old[r] = E[r];
				}
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = SquareSum(E);// + alpha * SquareSum(x);
				//printf ("%f ", F);
#endif

				if ( F > F_old) // функционал вырос - текущая подстройка неудаяная
				{
#if 0
					bool is_minetha = false;
					while (F > F_old && !is_minetha)
					{
						// отменяем текущее изменение элемента вектора решения
						x[c] += dx[c];
						if(!not_inertio)
						{
							// восстанавливаем предыдущее значение инерционного члена
							dx[c] -= etha[c] * dFdx[c];
							dx[c] /= inertio;
						}
						ToTurn[c] = true;
						NotFailed = false;
						/*if (etha[c] == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (etha[c] == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}*/
						// радикально уменьшаем коэффициент скорости подстройки
						etha[c] *= little_down;

						// не вышли ли за пределы нижней границы?
						if(etha[c] < minetha)
						{
							etha[c] = minetha;
							is_minetha = true;
						}
						else
						{
							if (q == 1 || not_inertio)
								dx[c] = etha[c] * dFdx[c];
							else // используем инерционный член
							{
								// предыдущий прирост умножаем на инерционный коэффициент
								dx[c] *= inertio; 
								// результат суммируем с текущим приростом элемента вектора решения
								dx[c] += etha[c] * dFdx[c];
							}
							//Подстраиваем элемент вектора x
							x[c] -= dx[c];
						}
#if 0
//{ТУТ ОЧЕНЬ ДОЛГО!!!
						// заново вычисляем вектор невязки
						for (r = 0; r < rows; r++)
						{
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							E[r] += A[r].ScalarProduct(x);
						}
						// восстанавливаем прежнее значение функционала
						F = SquareSum(E);// + alpha * SquareSum(x);
//}ТУТ ОЧЕНЬ ДОЛГО!!!
#else
						// Вектор невязки
						for (size_t ir = 0; ir < col_len; ir++)
						{
							r = At[c][ir].row;
							//E[r] -= x_old[c] * At[c][ir].val;
							//E[r] += x[c] * At[c][ir].val;
#if 0
							E[r] += (x[c] - x_old[c]) * At[c][ir].val;
#else
							E[r] = - b[r]; // элемент вектора правых частей со знакомминус
							E[r] += A[r].ScalarProduct(x);
#endif
							//F += E[r] * E[r] - E_old[r] * E_old[r];
							//E_old[r] = E[r];
							x_old[c] = x[c];
						}
						F = SquareSum(E);// + alpha * SquareSum(x);
#endif
					}
#else											
					etha[c] *= little_down;
					// не вышли ли за пределы нижней границы?
					if(etha[c] < minetha)
					{
						etha[c] = minetha;
					}

#endif
					printf ("%f %f\n", F, etha[c]);
				}
				else
				{
					F_old = F;
					etha[c] *= little_up;
					etha[c] = etha[c] > maxetha ? maxetha : etha[c];
					printf ("%f %f\n", F, etha[c]);
				}	

				
			}
			else 
			{
				printf("\n");
			}
		}
		// По достижении минимизации функционала или половины числа итераций обнуляем регуляризационный коэффициент
		printf ("%d %u %u\t", q, c, cols);
		printf ("%f\n", F);

//		if (q > 2 && SquareSum(dF) < 0.000001)
//			ToTurnAnyElement = false;

		meanFdx = 0.0; 
		for (c = 0; c < cols; c++)
			meanFdx += fabs(dFdx[c]);

		meanFdx /= cols;

	}
	while(ToTurnAnyElement && q < maxq );
//

//CString s;	s.Format("alpha = %g", alpha);	AfxMessageBox(s);

/*	if (epoch == max_epochs)
	{
		AlphaNonZero = false;
		part = 0.0;
	}
	else
		part *= part_down;
	//
	mindFdx *= mindFdx_down;
	}*/
	return true;
}
#if 0
void SparseStructureToMetafile(char * fn_spm, char * fn_emf = NULL)
{
	char buff[BUFF_SIZE];
	long cols, rows;

	AFile f;
	if( !f.Open( fn_spm, GENERIC_READ, OPEN_EXISTING) ) 
	{
		MessageBox(0, "FormMinSquareB\nUnable to open file" , fn_spm, MB_OK);
	}
	
	Archive ar( &f, Archive::load, BUFF_SIZE, buff );

	try
	{
		ar >> rows;
		ar >> cols;
	}
	catch(char * str)
	{
		MessageBox(0,str,"",0);
	}
	catch (CException* pe)
	{
		// catch errors from WinINet 
		TCHAR szErr[4098]; 
		pe->GetErrorMessage(szErr, 4098); 
		AfxMessageBox(szErr);
		pe->Delete();
	}
	catch(...)
	{
		MessageBox(0,"unknown error of archive read","",0);
	}

	PRINTDLG pd;
	
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = NULL;
	pd.hDevMode    = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames   = NULL;     // Don't forget to free or store hDevNames
	
	if (PrintDlg(&pd)!=TRUE) 
	{
		// GDI calls to render output.
		// что нибудб печатаем... 
		// BeginPrinting(hwnd, &pd);
		return;
	}	

	HDC hDC;
	DOCINFO di;
	
	if(!pd.hDevNames)
	{
		MessageBox(0,"!psd->hDevNames","BeginPrinting", 0);
		return ;
	}

	if(!pd.hDevMode)
	{
		MessageBox(0,"!psd->hDevMode","BeginPrinting", 0);
		return ;
	}

	// Получаем указатели на две структуры с установками.
	DEVNAMES FAR *lpDevNames =
		(DEVNAMES FAR *)::GlobalLock(pd.hDevNames);
	
	DEVMODE FAR *lpDevMode =
		(DEVMODE FAR *)::GlobalLock(pd.hDevMode);

	
	LPSTR szPrinterName = (LPTSTR)lpDevNames +
		lpDevNames->wDeviceOffset;
	
	LPSTR szDriverName = (LPTSTR)lpDevNames +
		lpDevNames->wDriverOffset;

	LPSTR szOutputPortName = (LPTSTR)lpDevNames +
		lpDevNames->wOutputOffset;

	// Создать контекст устройства для принтера, 
	// на котором должна быть выполнена печать.
	//........................................

	hDC = CreateDC( 
		szDriverName,//"WINSPOOL", 
		szPrinterName,
		szOutputPortName, 
		lpDevMode			//pDevModeUser 
		);

	int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
	double  iMMPerPelX, iMMPerPelY;

	// Вычислить размер клиентской области в единицах 
	// длины 0,01 мм.
	//................................................
	iWidthMM    = GetDeviceCaps(hDC, HORZSIZE);
	iHeightMM   = GetDeviceCaps(hDC, VERTSIZE);
	iWidthPels  = GetDeviceCaps(hDC, HORZRES);
	iHeightPels = GetDeviceCaps(hDC, VERTRES);

	printf("iWidthMM %d, iHeightMM %d, iWidthPels %d, iHeightPels %d\n", iWidthMM, iHeightMM, iWidthPels, iHeightPels);

	iMMPerPelX = double(iWidthMM * 100)/iWidthPels;
	iMMPerPelY = double(iHeightMM * 100)/iHeightPels;

	printf("iMMPerPelX %f, iMMPerPelY %f\n", iMMPerPelX, iMMPerPelY);

	int m = 10, m_2 = m/2;

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = (cols+1)*m * iMMPerPelX;
	rect.bottom = (rows+1)*m * iMMPerPelY;

	printf("lf %d rt %d tp %d bt %d", rect.left,rect.right,rect.top,rect.bottom);

	// Создать расширенный метафайл.
	//.............................
	HENHMETAFILE hMetaFile = NULL;
	HDC  hMetaDC;
	hMetaDC = CreateEnhMetaFile( hDC, fn_emf, &rect,  "Sparse Matrix Structure" );
	if  (!hMetaDC)
	{
		TCHAR filter[] =
							TEXT("Metafiles (*.emf)\0*.emf\0")
							TEXT("All Files (*.*)\0*.*\0");
		char fn_emf_[4098];
		DWORD nFilterIndex = 0;
		if (S_OK == SaveFileDlg(NULL, fn_emf_, filter,nFilterIndex))
		{
			hMetaDC = CreateEnhMetaFile( hDC, fn_emf_, &rect,  "Sparse Matrix Structure" );
		}
		//else
		//	hMetaDC = CreateEnhMetaFile( hDC, NULL, &rect,  "Sparse Matrix Structure" );
	}



	if ( hMetaDC )
	{
		HFONT font = CreateFont(1,0,0,0,100,0,0,0,DEFAULT_CHARSET,
				OUT_RASTER_PRECIS, CLIP_DEFAULT_PRECIS,
				DEFAULT_QUALITY,FF_DONTCARE,"Times New Roman");

		SelectObject (hMetaDC, font);
		
		char s[31];
		try
		{
			for (long r = 0; r < rows; r++)
			{
				printf("r  = %ld %ld\n", r, rows);							
				long cc;
				double value;

				do 
				{
					ar >> cc;
					ar >> value;

					if (cc >= 0)
					{
						//x.push_back(cc);
						//y.push_back(r);
#if 0
						sprintf(s,"%d*%d", int(r), int(cc));
						TextOut(hMetaDC, m_2+cc*m - ((int)strlen(s))/2, m_2+r*m + 1, s, (int)strlen(s));
#endif
						SetPixel(hMetaDC, m_2+cc*m,  m_2+r*m, RGB(255,0,0));
					}
					else
						break;
				}
				while(true);
			}
		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}

		hMetaFile = CloseEnhMetaFile( hMetaDC );
	}
	else
		ErrorExit("CreateEnhMetaFile",false);
	
	ar.Close();
	f.Close();
	
	if (fn_emf == NULL)
		SavePlot( NULL, hMetaFile, "000" );

	if(hMetaFile)
		DeleteEnhMetaFile(hMetaFile);
}
#endif

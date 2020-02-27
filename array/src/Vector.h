#include "stdafx.h"

#if !defined(_VECTOR333_)
#define _VECTOR333_


#include <stdio.h>
#include <stdlib.h>
//#include <windows.h>
#include <assert.h>
#ifdef _MSC_VER
class Archive;
#else
#include "../../surfdoc/src/Archive.h"
#endif

template <class T> class Vector;

Vector<bool> inline operator>(Vector<int>& ob1, Vector<int>& ob2);
Vector<bool> inline operator>(const int& a, Vector<int>& ob);
Vector<bool> inline operator>(Vector<int>& ob, const int& a);


/*
#ifdef COMMON_RAPORT
extern void WriteRaportoB(LPCTSTR s);
#else
extern void WriteRaportoA(LPCTSTR file, LPCTSTR s);
#endif
*/
//#define WriteRaporto NULL
/*template <class T> class Allocator
{
};
template <class T> class Allocator2
{
};
*/
template <class T> class Vector
{
	friend class CGraph;
	friend class vdouble;
//====== Данные класса 
private:
	int size;		// Размер массива
//	bool m_Constructed;
//====== Методы класса
public:
	T *data;		// Указатель начала массива компонент
	Vector()
	{
		data = NULL;
		size=0;
	}
	void Alloc(int sz)
	{
		size = sz;
		if ((data = new T [size]) == NULL && size != 0)
		{
			size = 0;
			TCHAR str[200];
			stprintf_s(str, 200, _T("Vector<T>::Alloc(%d) - Not enough memory"), size);
			MessageBox(0, str, _T("Vector"), 0);
			return;
		}
	}
	void Free()
	{
		if(data) delete[] data;
		data = NULL;
		size=0;
	}
	Vector(int n)
	{
		Alloc(n);
	}
	Vector(const Vector<T>& v)
	{
		Alloc(v.size);
		T *vdata;
		vdata = v.data;

#if 0
		for(int i=0; i< size; i++)
		{
			this->operator[](i) = v[i];
		}
#else
		for(int i=0; i< size; i++)
		{
			*(data+i) = *(vdata+i);
		}
#endif
		return;
	}

	~Vector() 
	{
		Free(); 
	}
    int Size() const { return size; }  // Возвращает длину вектора
    T Max() const // Возвращает мaксимальный элемент вектора
	{
		T _Max;
		_Max=*(data);
		for(int i=1;i<size;i++)
			_Max = _Max > *(data+i) ? _Max : *(data+i);
		return _Max;
	}
    T Min() const // Возвращает минимальный элемент вектора
	{
		T _Min;
		_Min=*(data);
		for(int i=1;i<size;i++)
			_Min = _Min < *(data+i) ? _Min : *(data+i);
		return _Min;
	}
	T& operator [](size_t i) const 
	{ 
		if (i < 0 || i >= size_t(size))
		{
			TCHAR strerr[1024];;
			stprintf_s(strerr, 1024, _T("Index = %i Error using Vector<size = %i>::Operator[]"), i, size);
			printf("%s\n", strerr);
			MessageBox(0, strerr, _T(""), 0);
			assert(false);
		}
		return data[i]; 
	}

	void resize(int _size)
	{
		if (size != _size)
		{
			Free();
			Alloc(_size);
		}
	}
	void resize(int _size, const T a)
	{
		if (size != _size)
		{
			Free();
			Alloc(_size);
		}
		for(int i=0; i<size; i++)
			*(data+i) = a;
	}
	void clear()
	{
		Free();
	}
	bool empty()
	{
		return size == 0 ? true : false;
	}
	void push_back(const T& a) // Добавляет элемент в конец вектора
	{
		int size_1 = size;
		size++; 
		T *data2;
		if ((data2 = new T [size]) == NULL && size != 0)
		{
			size--;
			char s[200];
			sprintf_s(s, 200, "Vector <T>::push_back(const T &a) - Not enough memory\nsize = %d, sizeof(T) = %d",
				size, sizeof(T));
			MessageBox(0,s,"Vector",0);
			return;
		}
		for(int i=0; i<size_1; i++)
			*(data2+i) = *(data+i);
		*(data2+size_1) = a;
		if (data) delete[] data;
		data=data2;
	}
	void push_back_Vector(T& a) // Добавляет элемент в конец вектора
	{
		Vector<T> v(size + 1);
		Vector<T> *pv;
		pv = this;
		for (int i = 1; i < size; i++)
			v[i] = this->operator[](i);
		v[size] = a;
		this = &v;
		pv->~Vector<T>();
	}
	void push_back(T& a) // Добавляет элемент в конец вектора
	{
		int size_1 = size;
		size++; 
		T *data2;
		if ((data2 = new T [size]) == NULL && size != 0)
		{
			size--;
			TCHAR s[200];
			stprintf_s(s, 200, _T("Vector <T>::push_back(const T &a) - Not enough memory\nsize = %d, sizeof(T) = %d"),
				size, sizeof(T));
			MessageBox(0,s,_T("Vector"),0);
			return;
		}
		for(int i=0; i<size_1; i++)
		{
			*(data2+i) = *(data+i);
		}
		*(data2+size_1) = a;
		if (data) delete[] data;
		data=data2;
	}
	void DeleteAll() // Удаляет все элементы вектора
	{
		Free();
	}
	void DeleteElement_(const int& index) // Удаляет index-ный элемент вектора
	{
		if (index > size-1 || index < 0)
		{
			MessageBox(0,"Error using Vector::DeleteElement(int index) : index out of Vector's indexes \n",
				"Vector",0);
			return;
		}
		size--;
		T *data2;
		if ((data = new T [size]) == NULL && size != 0)
		{
			MessageBox(0,"Vector<T>::DeleteElement(int index) - Not enough memory",
				"Vector",0);
			return;
		}
		for(int i=0; i<index; i++)
			*(data2+i) = *(data+i);
                for(int i=index; i<size; i++)
			*(data2+i) = *(data+i+1);
		if (data) delete[] data;
		data=data2;
	}
	void DeleteElement(const int& index) // Удаляет index-ный элемент вектора
	{
		if (index > size-1 || index < 0)
		{
			MessageBox(0,"Error using Vector::DeleteElement(int index) : index out of Vector's indexes \n",
				"Vector",0);
			return;
		}
		size--;
		for(int i=index; i<size; i++)
			*(data+i) = *(data+i+1);
	}
	void DeleteElements(Vector<bool>& vbl) // Удаляет элементы вектора
	{
		if (size != vbl.Size())
		{
//			AfxMessageBox("Error using Vector::DeleteElements(Vector<bool>& vbl) : size of input bool vector must be equial to size of current Vector\n");
			return;
		}
		int old_size = size;
		int j=-1;// new indexes
		int minus = Find(vbl).Size();
		size -= minus;
		T *data2;
		if ((data2 = new T [size]) == NULL && size != 0)
		{
			size += minus;
			MessageBox(0,
				"Vector::DeleteElements(Vector<bool>& vbl) - Not enough memory",
				"Vector", 0);
			return;
		}

		for(int i=0; i<old_size; i++) //  old indexes
		{
			if (! vbl[i])
			{
				j++;
				*(data2+j) = *(data+i);
			}
		}
		if (data) delete[] data;
		data=data2;
	}
	T& End() // Возвращает последний элемент вектора
	{
		if (size == 0)
		{
/*			AfxMessageBox("Error using Vector::End() : size of vector = 0 \n");
			AfxThrowUserException();*/
		}
		return data[size - 1];
	}
	T Product()
	{
		if (size < 1)
		{
//			AfxMessageBox("T Product()(size < 1)");
			return (T)0;
		}
		T prod;
		prod = data[0];
		for(int i=1; i<size; i++)
			prod *= data[i];
		return prod;
	}
	T Product(int i1, int i2)
	{
		if (size < 1)
		{
//			AfxMessageBox("T Product()(size < 1)");
			return (T)0;
		}
		if (i1 < 0)
		{
//			AfxMessageBox("T Product()(i1 < 0)");
			return (T)0;
		}
		if (i2 < 0)
		{
//			AfxMessageBox("T Product()(i2 < 0)");
			return (T)0;
		}
		if (i1 >= size)
		{
//			AfxMessageBox("T Product()(i1 >= size)");
			return (T)0;
		}
		if (i2 >= size)
		{
//			AfxMessageBox("T Product()(i2 >= size)");
			return (T)0;
		}
		T prod;
		prod = data[i1];
		for(int i=i1+1; i<i2; i++)
			prod *= data[i];
		return prod;
	}
/*	void disp()
	{
		AfxMessageBox("Function disp is unworked");
		for(int i=0;i<size;i++)
		{
			cout << "   ";
			cout << *(data+i);
		}
		cout << endl << endl;
		
	}*/
	Vector<T>& operator=(const Vector<T>& v)
	{
		if (this == &v)
		{
			return *this;
		}
		this->resize(v.size);
		for(int i=0; i< size; i++)
		{
			this->operator[](i) = v[i];
		}
		return *this;
	}

    friend Vector<int> inline Find(const Vector<bool>& vbl);
    friend Vector<bool> inline operator!(const Vector<bool>& vb);

    friend Vector<bool> inline operator||(const Vector<bool>& vb, const bool& bl);
    friend Vector<bool> inline operator||(const bool& bl, const Vector<bool>& vb);
    friend Vector<bool> inline operator||(const Vector<bool>& vb1, const Vector<bool>& vb2);

    friend Vector<bool> inline operator&&(const Vector<bool>& vb, const bool& bl);
    friend Vector<bool> inline operator&&(const bool& bl, const Vector<bool>& vb);
    friend Vector<bool> inline operator&&(const Vector<bool>& vb1, const Vector<bool>& vb2);
	//=================== Логические операторы =============================
	//////////////////////////////////////////////////////////////
    friend Vector<bool> inline operator>(const Vector<int>& ob1, const Vector<int>& ob2);
    friend Vector<bool> inline operator>(const int& a, const Vector<int>& ob);
    friend Vector<bool> inline operator>(const Vector<int>& ob, const int& a);

//	friend void inline operator<<(Vector<T>& v, const T& a);
//	friend void inline operator>>(const T& a, Vector<T>& v);

};
//====== Внешняя реализация тела конструктора
Vector<int> inline Find(const Vector<bool>& vbl)
{
	int sz = vbl.size;
	int i, len = 0;
	for (i = 0; i < sz; i++)
	{
		if (vbl[i])
			len++;
	}
	Vector<int> indexes(len);
	int j = 0;
	for (i = 0; i < sz; i++)
	{
		if (vbl[i])
		{
			indexes[j] = i;
			j++;
		}
	}
	return indexes;
}

//////////////////////////////////////////////////////////////
Vector<bool> inline operator!(const Vector<bool>& vb)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = reinterpret_cast<bool *>(vb.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr+i) = !(*(pv+i));
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
Vector<bool> inline operator||(const Vector<bool>& vb, const bool& bl)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = reinterpret_cast<bool *>(vb.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv + i) || bl ;
	}
	return vbl;
}

Vector<bool> inline operator||(const bool& bl, const Vector<bool>& vb)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = reinterpret_cast<bool *>(vb.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = bl || *(pv + i);
	}
	return vbl;
}

Vector<bool> inline operator||(const Vector<bool>& vb1, const Vector<bool>& vb2)
{
	int sz = vb1.size;
	if (sz != vb2.size)
	{
//		fprintf(stderr,"Error using Vector<bool> inline operator||(Vector<bool>& vb1, Vector<bool>& vb2):\n");
//		fprintf(stderr,"Lengthes of compared bool vectors = %i, %i must be equial",
//			vb1.size, vb2.size);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(sz);
	bool *pv1, *pv2, *pr;
	pv1 = reinterpret_cast<bool *>(vb1.data);
	pv2 = reinterpret_cast<bool *>(vb2.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv1 + i) || *(pv2 + i);
	}
	return vbl;
}

//////////////////////////////////////////////////////////////
Vector<bool> inline operator&&(const Vector<bool>& vb, const bool& bl)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = reinterpret_cast<bool *>(vb.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv + i) && bl ;
	}
	return vbl;
}

Vector<bool> inline operator&&(const bool& bl, const Vector<bool>& vb)
{
	int sz = vb.size;
	Vector<bool> vbl(sz);
	bool *pv, *pr;
	pv = reinterpret_cast<bool *>(vb.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = bl && *(pv + i);
	}
	return vbl;
}

Vector<bool> inline operator&&(const Vector<bool>& vb1, const Vector<bool>& vb2)
{
	int sz = vb1.size;
	if (sz != vb2.size)
	{
//		fprintf(stderr,"Error using Vector<bool> inline operator&&(Vector<bool>& vb1, Vector<bool>& vb2):\n");
//		fprintf(stderr,"Lengthes of compared bool vectors = %i, %i must be equial",
//			vb1.size, vb2.size);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(sz);
	bool *pv1, *pv2, *pr;
	pv1 = reinterpret_cast<bool *>(vb1.data);
	pv2 = reinterpret_cast<bool *>(vb2.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0; i< sz; i++)
	{
		*(pr + i) = *(pv1 + i) && *(pv2 + i);
	}
	return vbl;
}
//=================== Логические операторы =============================
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>(const Vector<int>& ob1, const Vector<int>& ob2)
{
	int len = ob1.size;
	if (len != ob2.size)
	{
//		fprintf(stderr,"Error using Vector<T> operator>(Vector<T> ob1, Vector<T>& ob2):\n");
//		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
//			ob1.size, ob2.size);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	int *pv1, *pv2; 
	bool *pr;
	pv1 = reinterpret_cast<int *>(ob1.data);
	pv2 = reinterpret_cast<int *>(ob2.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) > (*(pv2+i));
	}
	return vbl;
}

Vector<bool> inline operator>(const int& a, const Vector<int>& ob)
{
	int len = ob.size;
	Vector<bool> vbl(len);
	int *pv; 
	bool *pr;
	pv = reinterpret_cast<int *>(ob.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a > (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>(const Vector<int>& ob, const int& a)
{
	int len = ob.size;
	Vector<bool> vbl(len);
	int *pv; 
	bool *pr;
	pv = reinterpret_cast<int *>(ob.data);
	pr = reinterpret_cast<bool *>(vbl.data);
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) > a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
template <class T> void inline operator<<(const Vector<T>& v, const T& a)
{
	int len_1 = v.size - 1;
	if ( len_1 < 0)
		return;
	T *pv, *pr; 
	pv = v.data + 1;
	pr = v.data;
	for (int i = 0; i < len_1; i++)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr + len_1) = a;
}
template <class T> void inline operator>>(const T &a, const Vector<T>& v)
{
	int len_1 = v.size - 1;
	if ( len_1 < 0)
		return;
	T *pv, *pr; 
	pv = v.data - 1;
	pr = v.data;
	for (int i = len_1; i > 0; i--)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr) = a;
}

template <class T> Archive& operator <<(Archive& ar, Vector<T>& v)
{
	// метка старта вектора заносим в архив
	/*DWORD start_of_vector	= 0xabcd1234;

	ar << start_of_vector;*/
	// заносим в архив число элементов вектора
	ar << v.Size();
	for (int i = 0; i < v.Size(); i++)
		ar << v[i];



	// метка конца вектора
	/*DWORD end_of_vector		= 0x4321dcba;
	ar << end_of_vector;*/
	return ar;
}
template <class T> Archive& operator >>(Archive& ar, Vector<T>& v)
{
	// метка старта вектора
	/*DWORD start_of_vector;
	ar >> start_of_vector;
	if (start_of_vector	!= 0xabcd1234)
	{
		printf("Error of reading of start of vect from archive:\nstart_of_vector(%x) != 0xabcd1234", start_of_vector);
	}*/
	// число элементов вектора
	int len;
#ifdef _MSC_VER
	ar >> len;
#else
    ar.Read((unsigned char *)&len, sizeof(int));
#endif
	v.resize(len);
	for (int i = 0; i < len; i++)
		ar >> v[i];


	// метка конца вектора
	/*DWORD end_of_vector		= 0x4321dcba;
	ar >> end_of_vector;
	if (end_of_vector != 0x4321dcba)
	{
		printf("Error of reading of end of vect from archive:\nend_of_vector(%x) != 0x4321dcba", start_of_vector);
	}*/
	return ar;

}

#endif

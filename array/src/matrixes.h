// matrixes.h

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#else
#include "mywindows.h"
#endif

void ZeroDoubleMat(double **v, int nrows, int cols);
template <class T> T **Alloc2DMat (size_t size1, size_t size2);
template <class T> T **Alloc2DMat (size_t size1, size_t size2, T val);
template <class T> void Free2DMat(T ** v);

template <class T> T **Alloc2DMat (size_t size1, size_t size2) 
{
    T **v;
    size_t k;
	v = (T **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		size1 * sizeof( T * ) );
    v[0] = (T *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		size1 * size2 * sizeof (T));
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v);	
}
template <class T> T **Alloc2DMat (size_t size1, size_t size2, T val) 
{
    T **v;
    size_t k;
	v = (T **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		size1 * sizeof( T * ) );
    v[0] = (T *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		size1 * size2 * sizeof (T));
    for (k = 1; k < size1; k ++)
	{
		v[k] = v[k - 1] + size2;
		memcpy(v[k], &val, size2);
	}
    return (v);	
}

template <class T> void Free2DMat(T ** v)
{
	if (v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}
template <class T> T ****Alloc4DMat (size_t ncubes, size_t npages, size_t nrows, size_t ncols) 
{
    T ****v;
    size_t cube, page, row;
	// выделяем память под указатели на cubы
	v = (T ****)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		ncubes *  sizeof( T *** ) );

	if (v == NULL)
	{
                TCHAR errstr[255];
                sprintf_s(errstr, 255, _T("Not enough memory for %d * sizeof( T *** ) = %d bytes"), ncubes, ncubes * sizeof( T *** ) );
                MessageBox(0,errstr, _T("Alloc4DMat"),0);
	}	
	// выделяем память под указатели на страницы
	v[0] = (T ***)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		ncubes * npages * sizeof( T ** ) );
	if (v[0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * %d * sizeof( T ** ) = %d bytes", ncubes, npages, ncubes * npages * sizeof( T ** ) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}
	// выделяем память под указатели на строки
    v[0][0] = (T **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		ncubes * npages * nrows * sizeof (T*));
 	if (v[0][0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * %d * %d * sizeof( T* ) = %d bytes", ncubes, npages, nrows, ncubes * npages * nrows * sizeof (T*) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}
	// выделяем память под указатели на элементы строк
    v[0][0][0] = (T *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		ncubes * npages * nrows * ncols * sizeof (T));
 	if (v[0][0][0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * %d * %d  * %d * sizeof( T ) = %d bytes", ncubes, npages, nrows, ncols, ncubes * npages * nrows * ncols * sizeof (T) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}
	for (cube = 0; cube < ncubes; cube ++)
	{
		if (cube > 0)
		{
			v[cube] = v[cube - 1] + npages;
			v[cube][0] = v[cube - 1][0] + npages*nrows;
			v[cube][0][0] = v[cube - 1][0][0] + npages*nrows*ncols;
		}
		for (page = 0; page < npages; page ++)
		{
			// указателям на страницы присваиваем значения 
			// указателей на первую строку на каждой странице
			if (page > 0)
			{
				v[cube][page] = v[cube][page - 1] + nrows;
				v[cube][page][0] = v[cube][page - 1][0] + nrows*ncols;
			}
			for (row = 1; row < nrows; row++)
			{
				// указателям на строки присваиваем 
				// значения указателей на первый элемент в каждой строке
				v[cube][page][row] = v[cube][page][row-1] + ncols;
			}
		}
	}
	return (v);	
}


template <class T> T ****Alloc4DMat (size_t ncubes, size_t npages, size_t nrows, size_t ncols, T val) 
{
    T ****v;
    size_t cube, page, row;
	// выделяем память под указатели на cubы
	v = (T ****)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		ncubes *  sizeof( T *** ) );

	if (v == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * sizeof( T *** ) = %d bytes", ncubes, ncubes * sizeof( T *** ) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}	
	// выделяем память под указатели на страницы
	v[0] = (T ***)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		ncubes * npages * sizeof( T ** ) );
	if (v[0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * %d * sizeof( T ** ) = %d bytes", ncubes, npages, ncubes * npages * sizeof( T ** ) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}
	// выделяем память под указатели на строки
    v[0][0] = (T **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		ncubes * npages * nrows * sizeof (T*));
 	if (v[0][0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * %d * %d * sizeof( T* ) = %d bytes", ncubes, npages, nrows, ncubes * npages * nrows * sizeof (T*) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}
	// выделяем память под указатели на элементы строк
    v[0][0][0] = (T *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		ncubes * npages * nrows * ncols * sizeof (T));
 	if (v[0][0][0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %d * %d * %d  * %d * sizeof( T ) = %d bytes", ncubes, npages, nrows, ncols, ncubes * npages * nrows * ncols * sizeof (T) );
		MessageBox(0,errstr,"Alloc4DMat",0);
	}
	for (cube = 0; cube < ncubes; cube ++)
	{
		if (cube > 0)
		{
			v[cube] = v[cube - 1] + npages;
			v[cube][0] = v[cube - 1][0] + npages*nrows;
			v[cube][0][0] = v[cube - 1][0][0] + npages*nrows*ncols;
		}
		for (page = 0; page < npages; page ++)
		{
			// указателям на страницы присваиваем значения 
			// указателей на первую строку на каждой странице
			if (page > 0)
			{
				v[cube][page] = v[cube][page - 1] + nrows;
				v[cube][page][0] = v[cube][page - 1][0] + nrows*ncols;
			}
			for (row = 1; row < nrows; row++)
			{
				// указателям на строки присваиваем 
				// значения указателей на первый элемент в каждой строке
				v[cube][page][row] = v[cube][page][row-1] + ncols;
			}
		}
	}
	memcpy(v[0][0][0], &val, ncubes * npages * nrows * ncols);
	return (v);	
}

template <class T> T ***Alloc3DMat (size_t npages, size_t nrows, size_t ncols) 
{
    T ***v;
    size_t page, row;
	// выделяем память под указатели на страницы
	v = (T ***)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		npages * sizeof( T ** ) );

	if (v == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %u * sizeof( T ** ) = %d bytes", npages, npages * sizeof( T ** ) );
		MessageBox(0,errstr,"AllocTMat",0);
	}
	// выделяем память под указатели на строки
    v[0] = (T **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		npages * nrows * sizeof (T*));

 	if (v[0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %u * %u * sizeof( T* ) = %u bytes", npages, nrows, npages * nrows * sizeof (T*) );
		MessageBox(0,errstr,"AllocTMat",0);
	}
	// выделяем память под указатели на элементы строк
    v[0][0] = (T *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		npages * nrows * ncols * sizeof (T));

 	if (v[0][0] == NULL)
	{
		char errstr[255];
                sprintf_s(errstr, 255, "Not enough memory for %u * %u * %u * sizeof( T ) = %u bytes", npages, nrows, ncols, npages * nrows * ncols * sizeof (T) );
		MessageBox(0,errstr,"AllocTMat",0);
	}

	for (page = 0; page < npages; page ++)
	{
		// указателям на страницы присваиваем значения 
		// указателей на первую строку на каждой странице
		if (page > 0)
		{
			v[page] = v[page - 1] + nrows;
			v[page][0] = v[page - 1][0] + nrows*ncols;
		}
		for (row = 1; row < nrows; row++)
		{
			// указателям на строки присваиваем 
			// значения указателей на первый элемент в каждой строке
			v[page][row] = v[page][row-1] + ncols;
		}
	}
	return (v);	
}
template <class T> void Free3DMat(T *** v)
{
	if (v && v[0] && v[0][0]) HeapFree( GetProcessHeap(), 0, v[0][0] );
	if (v && v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}
template <class T> void Free4DMat(T **** v)
{
	if (v && v[0] && v[0][0] && v[0][0][0]) HeapFree( GetProcessHeap(), 0, v[0][0][0] );
	if (v && v[0] && v[0][0]) HeapFree( GetProcessHeap(), 0, v[0][0] );
	if (v && v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}
template <class T> void Zero3DMat(T ***v, size_t npages, size_t nrows, size_t ncols)
{
	memset(v[0][0],0,npages * nrows * ncols * sizeof (double));
}

template <class T> void Fill3DMatByValue(double value, T ***v, size_t npages, size_t nrows, size_t ncols)
{
	memset(v[0][0], value, npages * nrows * ncols * sizeof (double));
}











BYTE **AllocByteMat (int size1, int size2);
void FreeByteMat(BYTE ** v);
double **AllocDoubleMat (int nrows, int cols);

double ***AllocDouble3DMat (int npages, int nrows, int ncols) ;
void FreeDouble3DMat(double *** v);
int ***AllocInteger3DMat (int npages, int nrows, int ncols);
void FreeInteger3DMat(int *** v);

void FreeDoubleMat(double ** v);

float **AllocFloatMat (int size1, int size2) ;
void FreeFloatMat(float ** v);


int **AllocIntegerMat (int size1, int size2) ;
void FreeIntegerMat(int ** v);

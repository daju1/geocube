#include "stdafx.h"
#include "matrixes.h"




BYTE **AllocByteMat (int size1, int size2) 
{
    BYTE **v;
    int k;
	v = (BYTE **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		size1 * sizeof( BYTE * ) );
    v[0] = (BYTE *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		size1 * size2 * sizeof (BYTE));
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v);	
}
void FreeByteMat(BYTE ** v)
{
	if (v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}
void ZeroDoubleMat(double **v, int nrows, int cols)
{
	memset(v[0],0,nrows * cols * sizeof (double));
}
double **AllocDoubleMat (int nrows, int cols) 
{
    double **v;
    int k;
	// выделяем память под указатели на строки
	v = (double **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		nrows * sizeof( double * ) );

	if (v == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * sizeof( double * ) = %d bytes", nrows, nrows * sizeof( double * ) );
		MessageBox(0,errstr,"AllocDoubleMat",0);
	}
	// выделяем память под указатели на элементы строк
    v[0] = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		nrows * cols * sizeof (double));

 	if (v[0] == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * %d * sizeof( double ) = %d bytes", nrows, cols, nrows * cols * sizeof (double) );
		MessageBox(0,errstr,"AllocDoubleMat",0);
	}
	// указателям на строки присваиваем 
	// значения указателей на первый элемент в каждой строке
	for (k = 1; k < nrows; k ++) v[k] = v[k - 1] + cols;
    return (v);	
}

double ***AllocDouble3DMat (int npages, int nrows, int ncols) 
{
    double ***v;
    int page, row;
	// выделяем память под указатели на страницы
	v = (double ***)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		npages * sizeof( double ** ) );

	if (v == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * sizeof( double ** ) = %d bytes", npages, npages * sizeof( double ** ) );
		MessageBox(0,errstr,"AllocDoubleMat",0);
	}
	// выделяем память под указатели на строки
    v[0] = (double **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		npages * nrows * sizeof (double*));

 	if (v[0] == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * %d * sizeof( double* ) = %d bytes", npages, nrows, npages * nrows * sizeof (double) );
		MessageBox(0,errstr,"AllocDoubleMat",0);
	}
	// выделяем память под указатели на элементы строк
    v[0][0] = (double *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		npages * nrows * ncols * sizeof (double));

 	if (v[0][0] == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * %d * %d * sizeof( double ) = %d bytes", npages, nrows, ncols, npages * nrows * ncols * sizeof (double) );
		MessageBox(0,errstr,"AllocDoubleMat",0);
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
void FreeDouble3DMat(double *** v)
{
	if (v[0][0]) HeapFree( GetProcessHeap(), 0, v[0][0] );
	if (v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}
int ***AllocInteger3DMat (int npages, int nrows, int ncols) 
{
    int ***v;
    int page, row;
	// выделяем память под указатели на страницы
	v = (int ***)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		npages * sizeof( int ** ) );

	if (v == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * sizeof( int ** ) = %d bytes", npages, npages * sizeof( int ** ) );
		MessageBox(0,errstr,"AllocDoubleMat",0);
	}
	// выделяем память под указатели на строки
    v[0] = (int **) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		npages * nrows * sizeof (int*));

 	if (v[0] == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * %d * sizeof( int* ) = %d bytes", npages, nrows, npages * nrows * sizeof (int) );
		MessageBox(0,errstr,"AllocintMat",0);
	}
	// выделяем память под указатели на элементы строк
    v[0][0] = (int *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		npages * nrows * ncols * sizeof (int));

 	if (v[0][0] == NULL)
	{
		char errstr[255];
		sprintf(errstr, "Not enough memory for %d * %d * %d * sizeof( int ) = %d bytes", npages, nrows, ncols, npages * nrows * ncols * sizeof (int) );
		MessageBox(0,errstr,"AllocintMat",0);
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
void FreeInteger3DMat(int *** v)
{
	if (v && v[0] && v[0][0]) HeapFree( GetProcessHeap(), 0, v[0][0] );
	if (v && v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}

void FreeDoubleMat(double ** v)
{
	if (v && v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}

float **AllocFloatMat (int size1, int size2) 
{
    float **v;
    int k;
	v = (float **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		size1 * sizeof( float * ) );
    v[0] = (float *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		size1 * size2 * sizeof (float));
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v);	
}
void FreeFloatMat(float ** v)
{
	if (v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}


int **AllocIntegerMat (int size1, int size2) 
{
    int **v;
    int k;
	v = (int **)HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY,
		size1 * sizeof( int * ) );
    v[0] = (int *) HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, 
		size1 * size2 * sizeof (int));
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v);	
}
void FreeIntegerMat(int ** v)
{
	if (v[0]) HeapFree( GetProcessHeap(), 0, v[0] );
	if (v) HeapFree( GetProcessHeap(), 0, v );
}
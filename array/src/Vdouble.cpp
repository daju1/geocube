#pragma once 

#include "StdAfx.h"
#include "Vdouble.h"
#include "factorial.h"
#include "lagerfun.h"
#include "sequence.h"
#include "wav.h"

#if defined (_MSC_VER) && !defined (QT_PROJECT)
#else
#include "mywindows.h"
#endif

int vdouble::m_nMaxDims = VDOUBLE_MAX_DIMS;
unsigned int vdouble::m_nConstructions = 0;
unsigned int vdouble::m_nDestructions = 0;

#define TEST_VDOUBLE_MSG_MEMORY 0
size_t vdouble::m_szMemory = 0;
#define S_LEN 256
//
vdouble::vdouble()
{
	m_nConstructions++;
	m_length=0;
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(vdouble& src) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
	m_dims = 1;
//	m_size.resize(1);
	m_size[0] = m_length;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble()",0);
#endif
}
//
vdouble::vdouble(const vdouble& src)
{
	m_nConstructions++;
	m_length=src.m_length;
	m_isgorizontal=src.m_isgorizontal;
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(vdouble& src) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	int len = src.m_length;
	double *pv; pv = src.pD;
	for (int i = 0; i < len; i++)
		*(pD+i) = *(pv+i);

	m_dims = src.m_dims;
	for (int d = 0; d < m_dims; d++)
		m_size[d] = src.m_size[d];
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(vdouble& src)",0);
#endif
}
vdouble::vdouble(int _length)
{
	m_nConstructions++;
	m_length=_length;
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(int) - Not enough memory"),
			_T("vdouble"), 0);
		m_length = 0;

		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;

	m_dims = 1;
//	m_size.resize(1);
	m_size[0] = m_length;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(int _length)",0);
#endif
}


vdouble::vdouble(double& array, int _length)
{
	m_nConstructions++;
	m_length = _length;
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(double& array, int _length) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
	for(int i = 0; i < m_length; i++)
		*(pD + i) = *(&array + i);
	m_dims = 1;
//	m_size.resize(1);
	m_size[0] = m_length;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(double& array, int _length)",0);
#endif
}


vdouble::vdouble(double array[], int _length)
{
	m_nConstructions++;
	m_length = _length;
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(double array[], int _length) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
	for(int i = 0; i < m_length; i++)
		*(pD + i) = *(array + i);
	m_dims = 1;
//	m_size.resize(1);
	m_size[0] = m_length;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(double array[], int _length)",0);
#endif
}
vdouble::vdouble(int _length, const double& ra)
{
	m_nConstructions++;
	m_length=_length;
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(int _length, const double& ra) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
	for(int i=0;i<m_length;i++)
		*(pD+i)=ra;
	m_dims = 1;
//	m_size.resize(1);
	m_size[0] = m_length;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(int _length, const double& ra)",0);
#endif
}
vdouble inline zeros(int _length)// Создаёт вектор заданной длины из нулей
{
	vdouble z = vdouble (_length);
	double *p; p = z.pD;
	for( int i = 0; i < _length; i++)
		*(p + i) = 0.0;
	return z;
}
vdouble inline ones(int _length) // Создаёт вектор заданной длины из единиц
{
	vdouble z = vdouble (_length);
	double *p; p = z.pD;
	for( int i = 0; i < _length; i++)
		*(p + i) = 1.0;
	return z;
}
vdouble::vdouble(int rows, int cols) // Конструктор двумерной матрицы
{
	m_dims = 2;
//	m_size.resize(m_dims);
	m_length = rows * cols;

	m_size[0] = rows;
	m_size[1] = cols;

	m_nConstructions++;

	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(int rows, int cols) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(int rows, int cols)",0);
#endif
}

vdouble::vdouble(int rows, int cols, int tabs) // Конструктор трёхмерной матрицы
{
	m_dims = 3;
//	m_size.resize(m_dims);
	m_length = rows * cols * tabs;

	m_size[0] = rows;
	m_size[1] = cols;
	m_size[2] = tabs;

	m_nConstructions++;

	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(int rows, int cols, int tabs) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(int rows, int cols, int tabs)",0);
#endif
}

vdouble::vdouble(Vector<int>& vsize) // Конструктор многомерной матрицы
{
	m_dims = 
		vsize.Size() <= m_nMaxDims ?
		vsize.Size() : m_nMaxDims ;

	m_length = 1;

	for (int d = 0; d < m_dims; d++)
	{
		m_size[d] = vsize[d];
		m_length *= m_size[d];
	}

	m_nConstructions++;

	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		MessageBox(0, _T("vdouble::vdouble(Vector<int>& vsize) - Not enough memory"),
			_T("vdouble"), 0);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble(Vector<int>& vsize)",0);
#endif

}
void
vdouble::resize(const int _length)
{
//WriteRaporto("vdouble::resize 1_\n");
	if (m_length != _length)
	{
//WriteRaporto("vdouble::resize 2\n");
		if (m_length > 0)
		{
//WriteRaporto("vdouble::resize 3\n");
			if (pD)
			{
//WriteRaporto("vdouble::resize 4\n");
				HeapFree(GetProcessHeap(), 0,pD);
//WriteRaporto("vdouble::resize 5\n");
				pD = NULL;
			}
			m_szMemory -=m_length*SD;
//WriteRaporto("vdouble::resize 6\n");
		}
//WriteRaporto("vdouble::resize 6 1\n");
		m_length=_length;
//WriteRaporto("vdouble::resize 6 2\n");
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
//WriteRaporto("vdouble::resize 6 ret\n");
			m_length = 0;
			TCHAR err[S_LEN];
			stprintf_s(err, S_LEN, _T("vdouble::resize(int _length) - Not enough memory\n_length = %i"),
				_length);
			MessageBox(0,err,_T(""),0);
			m_length = 0;
			return;
		}
		m_szMemory +=m_length*SD;
//WriteRaporto("vdouble::resize 7_\n");
	}
//WriteRaporto("vdouble::resize 8\n");
	m_isgorizontal=true;
//WriteRaporto("vdouble::resize 9\n");
	m_dims = 1;
//WriteRaporto("vdouble::resize 8\n");
//	m_size.resize(1);
//WriteRaporto("vdouble::resize 9\n");
	m_size[0] = m_length;
//WriteRaporto("vdouble::resize end\n");
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::resize(int _length)",0);
#endif
}
void
vdouble::resize(const int _length, const double& ra)
{
//printf("vdouble::resize(int %d, double %f) 1\n",  _length, ra);
	if (m_length != _length)
	{
		if (m_length > 0)
		{
			if (pD)
			{
				HeapFree(GetProcessHeap(), 0,pD);
				pD = NULL;
			}
			m_szMemory -=m_length*SD;
		}
		m_length=_length;
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
			m_length = 0;
			TCHAR err[200];
			stprintf_s(err, 200, _T("vdouble::resize(int %d, const double %f) - Not enough memory\nm_length = %i"),
				_length, ra, m_length);
			MessageBox(0,err,_T("vdouble"),0);
			return;
		}
		m_szMemory +=m_length*SD;
	}
	m_isgorizontal=true;
	for(int i=0;i<m_length;i++)
	{
		*(pD+i)=ra;
//		this->operator [](i)=ra;
	}
	m_dims = 1;
//		m_size.resize(1);
	m_size[0] = m_length;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::resize(int _length, const double& ra)",0);
#endif
}

void
vdouble::resize(const int rows, const int cols) // двумерной матрицы
{
	if (m_length != rows * cols)
	{
		if (m_length > 0)
		{
			if (pD)
			{
				HeapFree(GetProcessHeap(), 0,pD);
				pD = NULL;
			}
			m_szMemory -=m_length*SD;
		}
		m_length = rows * cols;
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
			m_length = 0;
			TCHAR str[512];
			stprintf_s(str, 512, _T("vdouble::resize(%d, %d) - Not enough memory"), rows, cols);
            MessageBox(0,str,_T("(vdouble::resize"), MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		m_szMemory +=m_length*SD;
	}
	m_dims = 2;
//	m_size.resize(m_dims);

	m_size[0] = rows;
	m_size[1] = cols;

	m_isgorizontal=true;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::resize(int rows, int cols)",0);
#endif
}

void
vdouble::resize(const int rows, const int cols, const double& ra) // двумерной матрицы
{
	if (m_length != rows * cols)
	{
		if (m_length > 0)
		{
			HeapFree(GetProcessHeap(), 0,pD);
			m_szMemory -=m_length*SD;
		}
		m_length = rows * cols;
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
			m_length = 0;

			TCHAR str[512];
			stprintf_s(str, 512, _T("vdouble::resize(%d, %d, %f) - Not enough memory"), rows, cols, ra);
			MessageBox(0,str, _T("vdouble::resize"),MB_OK | MB_ICONEXCLAMATION);

			return;
		}
		m_szMemory +=m_length*SD;
	}
	m_dims = 2;
//	m_size.resize(m_dims);

	m_size[0] = rows;
	m_size[1] = cols;

	m_isgorizontal=true;
	for(int i=0;i<m_length;i++)
		*(pD+i)=ra;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::resize(int rows, int cols, const double& ra)",0);
#endif

}

void
vdouble::resize(const int rows, const int cols, const int tabs) // Конструктор трёхмерной матрицы
{
	if (m_length != rows * cols * tabs)
	{
		if (m_length > 0)
		{
			HeapFree(GetProcessHeap(), 0,pD);
			m_szMemory -=m_length*SD;
		}
		m_length = rows * cols * tabs;
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
			m_length = 0;
			TCHAR str[512];
			stprintf_s(str, 512, _T("vdouble::resize(%d, %d, %d) - Not enough memory"), rows, cols, tabs);
			MessageBox(0,str,_T("vdouble::resize"),MB_OK | MB_ICONEXCLAMATION);
			return;
		}
		m_szMemory +=m_length*SD;
	}
	m_dims = 3;
//	m_size.resize(m_dims);

	m_size[0] = rows;
	m_size[1] = cols;
	m_size[2] = tabs;

	m_isgorizontal=true;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::resize(int rows, int cols, int tabs)",0);
#endif
}
void
vdouble::resize(const Vector<int>& vsize) // Конструктор многомерной матрицы
{
	if (m_length > 0)
		if (pD)
			HeapFree(GetProcessHeap(), 0,pD);

	m_dims = 
		vsize.Size() <= m_nMaxDims ?
		vsize.Size() : m_nMaxDims ;

	m_length = 1;

	for (int d = 0; d < m_dims; d++)
	{
		m_size[d] = vsize[d];
		m_length *= m_size[d];
	}

	m_nConstructions++;

	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		m_length = 0;
		TCHAR str[512];
		stprintf_s(str, 512, _T("vdouble::resize(Vector<int>& vsize) - Not enough memory"));
		MessageBox(0,str,_T("vdouble::resize"),MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	m_szMemory +=m_length*SD;
	m_isgorizontal=true;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::resize(Vector<int>& vsize)",0);
#endif

}

void vdouble::OnDestroy() // Деструктор выполняет освобождение памяти
{
#if TEST_VDOUBLE_MSG_MEMORY
	MessageBox(0,"", "~vdouble()",0);
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "~vdouble()",0);
#endif
	m_nDestructions++;
	if (m_length > 0)
		if (pD)
		HeapFree(GetProcessHeap(), 0,pD);
	m_szMemory -=m_length*SD;
	m_length = 0;
}
vdouble::~vdouble() // Деструктор выполняет освобождение памяти
{
	OnDestroy();
}
//
int vdouble::_printf(const char *name, bool asIntegers)//
{

	printf("name = %s\n", name );
	printf("m_length = %d\n", m_length );
	// Записываем данные
	if (this->m_dims == 2)
	{
		int r,c,i,
		rows = m_size[0],
		cols = m_size[1];

		printf("m_size[0] = %d\n", m_size[0] );
		printf("m_size[1] = %d\n", m_size[1] );
		for (r = 0; r < rows; r++)
		{
			for (c = 0; c < cols; c++)
			{
				i = c + r * cols;
				if(asIntegers)
				{
					if (*(pD + i) >=0.0)
						printf(" %d", (int)*(pD + i) );
					else 
						printf("-%d", (int)fabs(*(pD + i)) );
				}
				else
				{
					if (*(pD + i) >=0.0)
						printf("   %7.4f", *(pD + i) );
					else 
						printf("  -%7.4f", fabs(*(pD + i)) );
				}
			}
			printf("\n");
		}
	}
	else
	{
		for(int i=0;i<m_length;i++)
		{
			if (i%5 == 0) printf("\n");
			if(asIntegers)
			{
				if (*(pD + i) >=0.0)
					printf("   %d", (int)*(pD + i) );
				else 
					printf("  -%d", (int)fabs(*(pD + i)) );
			}
			else
			{
				if (*(pD + i) >=0.0)
					printf("   %lf", *(pD + i) );
				else 
					printf("  -%lf", fabs(*(pD + i)) );
			}
		}
	}
	printf("\n\n");
	// закрываем файл
	return 0;
}
int vdouble::Write(const char * filename, const char *mode, const char *name , bool asIntegers)//
{
	FILE *stream;
	// открываем бинарный файл для записи
	if ((stream = fopen(filename, mode)) == NULL)
	{
//		AfxMessageBox("Cannot open file for write.\n");
		return -1;
	}
	fprintf(stream, "name = %s\n", name );
	fprintf(stream, "m_length = %d\n", m_length );
	// Записываем данные
	if (this->m_dims == 2)
	{
		int r,c,i,
		rows = m_size[0],
		cols = m_size[1];

		fprintf(stream, "m_size[0] = %d\n", m_size[0] );
		fprintf(stream, "m_size[1] = %d\n", m_size[1] );
		for (r = 0; r < rows; r++)
		{
			for (c = 0; c < cols; c++)
			{
				i = c + r * cols;
				if(asIntegers)
				{
					if (*(pD + i) >=0.0)
						fprintf(stream, " %d", (int)*(pD + i) );
					else 
						fprintf(stream, "-%d", (int)fabs(*(pD + i)) );
				}
				else
				{
					if (*(pD + i) >=0.0)
						fprintf(stream, "   %7.4f", *(pD + i) );
					else 
						fprintf(stream, "  -%7.4f", fabs(*(pD + i)) );
				}
			}
			fprintf(stream, "\n");
		}
	}
	else
	{
		for(int i=0;i<m_length;i++)
		{
			if (i%5 == 0) fprintf(stream, "\n");
			if(asIntegers)
			{
				if (*(pD + i) >=0.0)
					fprintf(stream, "   %d", (int)*(pD + i) );
				else 
					fprintf(stream, "  -%d", (int)fabs(*(pD + i)) );
			}
			else
			{
				if (*(pD + i) >=0.0)
					fprintf(stream, "   %lf", *(pD + i) );
				else 
					fprintf(stream, "  -%lf", fabs(*(pD + i)) );
			}
		}
	}
	fprintf(stream, "\n\n");
	// закрываем файл
	fclose(stream);
	return 0;
}
int vdouble::Save(const char * filename)//
{
	int result;
	FILE *stream;
	// открываем бинарный файл для записи
	if ((stream = fopen(filename,"wb")) == NULL)
	{
//		AfxMessageBox("Cannot open file for write.\n");
		return -1;
	}
	size_t wrote;

	// Записываем длину вектора
	wrote = fwrite(&m_length, sizeof(int), 1, stream);
	// Записываем размерность 
	wrote = fwrite(&m_dims, sizeof(int), 1, stream);
	// Записываем размеры по каждой размерности
	wrote = fwrite(m_size, sizeof(int), m_dims, stream);
	// Записываем данные
	wrote = fwrite(pD, sizeof(double), m_length, stream);
	// закрываем файл
	fclose(stream);
	if ((int)wrote == m_length)
		result = 0;
	else
	{
	//	AfxMessageBox("Not all data are wrote\n");
		result = -1;
	}
	return result;
}
int vdouble::Load(const char * filename)//
{
	int result;
	FILE *stream;
	// открываем бинарный файл для чтения
	if ((stream = fopen(filename,"rb")) == NULL)
	{
		MessageBox(0,_T("Cannot open file for write.\n"),_T("vdouble::Load(const char * filename)"),0);
		return -1;
	}
	// считываем длину вектора
	size_t read;
	read = fread(&m_length, sizeof(int), 1, stream);
	// считываем размерность
	read = fread(&m_dims, sizeof(int), 1, stream);
	// размеры по каждой размерности
//	m_size.resize(m_dims);
	read = fread(m_size, sizeof(int), m_dims, stream);
	// выделяем в виртуальной памяти место для вектора
	if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
//		AfxMessageBox("vdouble::vdouble(int, const double) - Not enough memory");
		// закрываем файл
		fclose(stream);
//		AfxThrowMemoryException();
		return -1;
	}
	// считываем данные из файла в виртуальную память
	read = fread(pD, sizeof(double), m_length, stream);
	// закрываем файл
	fclose(stream);
	if ((int)read == m_length)
		result = 0;
	else
	{
//		AfxMessageBox("Not all data are read\n");
		result = -1;
	}
	return result;
}
void vdouble::dispSquareMatrix()
{
	int n = (int)sqrt((double)m_length);
	if(m_length==n*n)
	{
		for(int r = 0; r<n; r++)
		{
			int rn = r * n;
			for(int c=0;c<n;c++)
			{
				fprintf(stderr, "   %g", *(pD + rn + c) );
			}
			fprintf(stderr, "\n");
		}
		fprintf(stderr, "\n");
	}
}
char* vdouble::dispMatrix_str()
{
	if (m_dims != 2)
	{
		MessageBox(0,_T("Error using dispMatrix_str()\n(m_dims != 2)\n"),_T("vdouble"),0);
		return NULL;
	}
	int rows = m_size[0],
		cols = m_size[1];

	int charlen = rows*cols*32;
	char *str = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,charlen*sizeof(char));
	char s[255];

	if (!str)
		return NULL;

	sprintf(s, "\n\n");
	strcpy(str, s);
	for(int r = 0; r<rows; r++)
	{
		int rn = r * cols;
		for(int c=0;c<cols;c++)
		{
			sprintf(s, "   %g", *(pD + rn + c) );
			strcat(str, s);
		}
		sprintf(s, "\n");
		strcat(str, s);
	}
	sprintf(s, "\n");
	strcat(str, s);
	return str;
}

char* vdouble::disp_str()
{
	int charlen = m_length*32;
	char *str = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,charlen*sizeof(char));
	char s[255];
	if (!str)
		return NULL;
	sprintf(s, " Length of Vector = %i\n", m_length);
	strcpy(str, s);
	for(int i=0;i<m_length;i++)
	{
		if (i%10 == 0)
		{
			sprintf(s, "\n");
			strcat(str, s);
		}
		if (*(pD + i) >=0.0)
		{

			sprintf(s, "   %g", *(pD + i) );
			strcat(str, s);
		}
		else 
		{
			sprintf(s, "  -%g", fabs(*(pD + i)) );
			strcat(str, s);
		}
	}
	sprintf(s, "\n");
	return str;
}
void vdouble::disp()
{
	if(m_isgorizontal==true)
	{
		for(int i=0;i<m_length;i++)
		{
			if (i%6 == 0) fprintf(stderr, "\n");
			if (*(pD + i) >=0.0)
				fprintf(stderr, "   %e", *(pD + i) );
			else 
				fprintf(stderr, "  -%e", fabs(*(pD + i)) );
		}
		fprintf(stderr, "\n\n");
	}
	else
	{
		for(int i=0;i<m_length;i++)
		{
			fprintf(stderr, "   %e\n", *(pD + i) );
		}
		fprintf(stderr, "\n");
	}
}
void vdouble::dispWithIndex()
{
	fprintf(stderr, "\n");
	for(int i=0;i<m_length;i++)
	{
		if (i%4 == 0) fprintf(stderr, "\n   ");
		fprintf(stderr, "%i: %e\t", i, *(pD + i) );
	}
	fprintf(stderr, "\n\n");
}
bool vdouble::is_zeros()
{
	bool flag = true;
	for (int i = 0; i < m_length; i++)
		flag = flag && *(pD + i) == 0.0;
	return flag;
}
bool vdouble::is_zeros(const double& epsilon)
{
	bool flag = true;
	for (int i = 0; i < m_length; i++)
		flag = flag && fabs(*(pD + i)) < epsilon;
	return flag;
}

const double& vdouble::operator[](int index) const
{
	if (index <0 || index >= m_length)
	{
		TCHAR s[S_LEN];
		stprintf_s(s, S_LEN, _T("Error using vdouble::operator[](int index): \n index = %i go away from massive of length = %i \n"),index, m_length);
		MessageBox(0,s,_T(""),0);
		static double iErr=NULL;
		return iErr;
	}
	return pD[index];
}
double& vdouble::operator[](int index)
{
	if (index <0 || index >= m_length)
	{
		TCHAR s[S_LEN];
		stprintf_s(s, S_LEN, _T("Error using vdouble::operator[](int index): \n index = %i go away from massive of length = %i \n"),index, m_length);
		MessageBox(0,s,_T(""),0);
		static double iErr=NULL;
		return iErr;
	}
	return pD[index];
}
vdouble vdouble::operator()(const Vector<int>& vrows, const Vector<int>& vcols) const
{
	if (m_dims != 2)
	{
/*		AfxMessageBox("Error using vdouble::operator()(Vector<int>& vrows, Vector<int>& vcols)\n (m_dims != 2)");
		AfxThrowUserException();*/
		return vdouble();
	}
	if (vrows.Min() < 0 || vrows.Max() >= m_size[0])
	{
/*		AfxMessageBox("Index error using vdouble::operator()(Vector<int>& vrows, Vector<int>& vcols)\n");
		AfxThrowUserException();*/
		return vdouble();
	}
	int rows = vrows.Size(),
		cols = vcols.Size(),
		 j, r, c;
	vdouble v = vdouble(rows, cols);
	double *vpD;
	vpD = v.pD;
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < cols; c++)
		{
			j = vcols[c] + vrows[r] * m_size[1];
			*vpD = *(pD + j);
			vpD++;
		}
	}
	/*
	for (c = 0; c < cols; c++)
	{
		for (r = 0; r < rows; r++)
		{
			j = vrows[r] + vcols[c] * m_size[0];
			*vpD = *(pD + j);
			vpD++;
		}
	}*/

	return v;
}
vdouble vdouble::operator[](const Vector<int>& ind) const
{
	int len, i;
	len = ind.size;
	vdouble v(0);
	if (len == 0)
	{
		return v;
	}
	double *p;
	bool valid = true;
	for ( i = 0; i < len; i++)
		valid = valid && ind[i] >=0 && ind[i] < m_length;
	if (valid)
	{
		 v = vdouble(len);
		 p = v.pD;
		 for ( i = 0; i < len; i++)
			 *(p + i) = *(pD + ind[i]);
	}
	else
	{
		MessageBox(0, _T("Error using vdouble::operator[](Vector<int>& ind): index go away from massive\n"),
			_T("vdouble"), 0);
		return vdouble (0);
	}
	return v;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//
const double& vdouble::operator()(const int index) const
{
	if (index < 0 || index >= m_length)
	{
		char s[1024];
		stprintf_s(s, 1024, _T("Error using vdouble::operator[](int index): \n index = %i go away from massive \n"), index);
		MessageBox(0, s, _T(""), 0);
		static double iErr=NULL;
		return iErr;
	}
	return pD[index];
}
double& vdouble::operator()(const int index)
{
	if (index < 0 || index >= m_length)
	{
		char s[1024];
		stprintf_s(s, 1024, _T("Error using vdouble::operator[](int index): \n index = %i go away from massive \n"), index);
		MessageBox(0, s, _T(""), 0);
		static double iErr=NULL;
		return iErr;
	}
	return pD[index];
}
double& vdouble::operator()(const int row, const int col) const
{
	if (m_dims != 2)
	{
		static double iErr=NULL;
		MessageBox(0,
			_T("Error using vdouble::operator()(int row, int col):\n (m_dims != 2) \n"),
			_T("Error"),0);
/*		AfxThrowUserException();*/
		return iErr;
	}
	if (row <0 || row >= m_size[0])
	{
		static double iErr=NULL;
		TCHAR errstr[255];
		stprintf_s(errstr, 255, _T("Error using vdouble::operator()(int row, int col): row (%d) go away from massive[0 %d] \n"), row, m_size[0]);
		MessageBox(0,errstr,_T("Error"),0);
/*		AfxThrowUserException();*/
		return iErr;
	}
	if (col <0 || col >= m_size[1])
	{
		static double iErr=NULL;
		TCHAR errstr[255];
		stprintf_s(errstr, 255, _T("Error using vdouble::operator()(int row, int col): col (%d) go away from massive[0 %d] \n"), col, m_size[1]);
		MessageBox(0,errstr,_T("Error"),0);
/*		AfxThrowUserException();*/
		return iErr;
	}
	int i = col + row * m_size[1];
//	int i = row + col * m_size[0];

	return *(pD + i);
}
double& vdouble::operator()(const int row, const int col, const int tab) const
{
	if (m_dims != 3)
	{
		static double iErr=NULL;
/*		AfxMessageBox( "Error using vdouble::operator()(int row, int col, int tab):\n (m_dims != 3) \n");
		AfxThrowUserException();*/
		return iErr;
	}
	if (row <0 || row >= m_size[0])
	{
		static double iErr=NULL;
/*		AfxMessageBox( "Error using vdouble::operator()(int row, int col, int tab): row go away from massive \n");
		AfxThrowUserException();*/
		return iErr;
	}
	if (col <0 || col >= m_size[1])
	{
		static double iErr=NULL;
/*		AfxMessageBox( "Error using vdouble::operator()(int row, int col, int tab): col go away from massive \n");
		AfxThrowUserException();*/
		return iErr;
	}
	if (tab <0 || tab >= m_size[2])
	{
		static double iErr=NULL;
/*		AfxMessageBox( "Error using vdouble::operator()(int row, int col, int tab): tab go away from massive \n");
		AfxThrowUserException();*/
		return iErr;
	}
	int i = col + row * m_size[1] + m_size[0]*m_size[1]*tab;
//	int i = row + col * m_size[0] + m_size[0]*m_size[1]*tab;

	return *(pD + i);
}
#if 1
double& vdouble::operator()(const Vector<int>& indexes) const
{
	int d;
	if (m_dims != indexes.size)
	{
		static double iErr=NULL;
		MessageBox(0, _T("Error using vdouble::operator()(Vector<int>& indexes):\n (m_dims != indexes.size) \n"), _T(""), 0);
		return iErr;
	}
	for (d = 0; d < m_dims;  d++)
	{
		if (indexes[d] <0 || indexes[d] >= m_size[d])
		{
			static double iErr=NULL;
			MessageBox(0, _T("Error using vdouble::operator()(Vector<int>& indexes): index go away from massive \n"),_T(""), 0);
			return iErr;
		}
	}
	int i = indexes[1] + m_size[1] * indexes[0];
	for (d = 2; d < m_dims;  d++)
	{
		int product = 1;
		for (int id = 0; id < d-1; id++)
			product *= m_size[id];
		i += indexes[d] * product;
	}
	/* // A la fortran
	int i = indexes[0];
	for (d = 1; d < m_dims;  d++)
		i += indexes[d] * m_size.Product(0, d-1);
*/
	return *(pD + i);
}
#endif
//1
vdouble& vdouble::operator=(const vdouble& rhs)
{
//WriteRaporto("vdouble::operator= 1\n");
	if (this == &rhs)
	{
//WriteRaporto("vdouble::operator= return *this\n");
		return *this;
	}
	if  (m_length != rhs.m_length)
	{
//WriteRaporto("vdouble::operator= 2\n");
		if (m_length >= 1) 	HeapFree(GetProcessHeap(), 0,pD);
//WriteRaporto("vdouble::operator= 3\n");
		m_length=rhs.m_length;
//WriteRaporto("vdouble::operator= 4\n");
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
			TCHAR s[S_LEN];
			stprintf_s(s, S_LEN, _T("vdouble::operator=(vdouble& rhs) - Not enough memory\n m_length = %i"), m_length);
			MessageBox(0,s, _T("vdouble"), 0);
			return *this;
		}
//WriteRaporto("vdouble::operator= 5\n");
		m_szMemory +=m_length*SD;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::operator=(vdouble& rhs)",0);
#endif
	}
//WriteRaporto("vdouble::operator= 6\n");
	m_isgorizontal=rhs.m_isgorizontal;
	double *pv; pv = rhs.pD;
	for(int i=0;i<m_length;i++)
	{
		*(pD + i) = *(pv + i);
	}
	m_dims = rhs.m_dims;
	for (int d = 0; d < m_dims; d++)
		m_size[d] = rhs.m_size[d];
//WriteRaporto("vdouble::operator= end a\n");
	return *this;

}
//3
vdouble& vdouble::operator=(const double& ra)
{
	if  (m_length != 1)
	{
		m_szMemory -=m_length*SD;
		if (m_length >=1) HeapFree(GetProcessHeap(), 0,pD);
		m_length=1;
		if ((pD = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
/*			AfxMessageBox("vdouble::operator=(const double& ra) - Not enough memory");
			AfxThrowMemoryException();*/
			return *this;
		}
		m_szMemory +=m_length*SD;
#if TEST_VDOUBLE_MSG_MEMORY
	char str[255];
	sprintf(str, "m_length = %d", m_length);
	MessageBox(0,str, "vdouble::operator=(const double& ra)",0);
#endif
	}
	m_isgorizontal=true;
	pD[0]=ra;
	m_dims = 1;
//	m_size.resize(1);
	m_size[0] = m_length;
	return *this;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble& vdouble::SummingFrom(int i0, vdouble& rhs)
{
	int len = rhs.m_length;
	if  (rhs.m_length + i0 != m_length) 
	{
/*		AfxMessageBox( "Error using vdouble::SummingFrom():\n "
			 "length of the vectors must be eqial to begin index\n");
		AfxThrowUserException();*/
		return *this;
	}
	double *pv, *pr;
	pv=rhs.pD;
	pr = pD + i0;
	for(int i=0; i<len; i++)
	{
		*(pr+i) += *(pv+i); 
	}
	return *this;

}
vdouble& vdouble::operator+=(const vdouble& rhs)
{
	if  ((rhs.m_length != m_length) && (rhs.m_length != 1))
	{
/*		AfxMessageBox(  "Error using vdouble::operator +=: \n"
			  "the lengthes of the vectors must be the same\n");
		AfxThrowUserException();*/
		return *this;
	}
	if  ((rhs.m_length == m_length) && (m_length != 1))
	{
		double *p1, *p2;
		p2=pD;p1=rhs.pD;

		for(int i=0;i<m_length;i++)
		{
			*p2 += (*p1); 
			p2++; p1++;
		}
	}
	if  (rhs.m_length==1)
	{
		double *p2; p2=pD;
		double ra = *(rhs.pD);
		for(int i=0;i<m_length;i++)
		{
			*p2 += ra; 
			p2++;
		}
	}
	return *this;

}
//3
vdouble& vdouble::operator+=(const double& ra)
{
	double *p2; p2=pD;
	for(int i=0;i<m_length;i++)
	{
		*p2 += ra; 
		p2++;
	}
	return *this;
}
//////////////////////////////////////////////////////////////
//1
vdouble& vdouble::operator*=(const vdouble& rhs)
{
	if  ((rhs.m_length != m_length) && (rhs.m_length != 1))
	{
/*		AfxMessageBox( "Error using vdouble::operator *=: \n"
			 "the lengthes of the vectors must be the same");
		AfxThrowUserException();/*/
		return *this;
	}
	if  ((rhs.m_length == m_length) && (m_length != 1))
	{
		double *p1, *p2;
		p2=pD;p1=rhs.pD;

		for(int i=0;i<m_length;i++)
		{
			*p2 *= *p1; 
			p2++; p1++;
		}
	}
	if  (rhs.m_length==1)
	{
		double *p2; p2=pD;
		double ra = *(rhs.pD);
		for(int i=0;i<m_length;i++)
		{
			*p2 *= ra; 
			p2++;
		}
	}
	return *this;
}
//3
vdouble& vdouble::operator*=(const double& ra)
{
	double *p2; p2=pD;
	for(int i=0;i<m_length;i++)
	{
		*p2 *= ra; 
		p2++;
	}
	return *this;
}
//////////////////////////////////////////////////////////////
//1
vdouble& vdouble::operator/=(const vdouble& rhs)
{
	if  ((rhs.m_length != m_length) && (rhs.m_length != 1))
	{
/*		AfxMessageBox( "Error using vdouble::operator /=: "
			 "the lengthes of the vectors must be the same\n");
		AfxThrowUserException();*/
		return *this;
	}
	if  ((rhs.m_length == m_length) && (m_length != 1))
	{
		double *p1, *p2;
		p2=pD;p1=rhs.pD;

		for(int i=0;i<m_length;i++)
		{
			*p2 /= (*p1); 
			p2++; p1++;
		}
	}
	if  (rhs.m_length==1)
	{
		double *p2; p2=pD;
		double ra = *(rhs.pD);
		for(int i=0;i<m_length;i++)
		{
			*p2 /= ra; 
			p2++;
		}
	}
	return *this;
}
//3
vdouble& vdouble::operator/=(const double& ra)
{
	double *p2; p2=pD;
	for(int i=0;i<m_length;i++)
	{
		*p2 /= ra; 
		p2++;
	}
	return *this;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble& vdouble::operator-=(const vdouble& rhs)
{
	if  ((rhs.m_length != m_length) && (rhs.m_length != 1))
	{
/*		AfxMessageBox( "Error using vdouble::operator -=:\n"
			 "the lengthes of the vectors must be the same\n");
		AfxThrowUserException();*/
		return *this;
	}
	if  ((rhs.m_length == m_length) && (m_length != 1))
	{
		double *p1, *p2;
		p2=pD;p1=rhs.pD;

		for(int i=0;i<m_length;i++)
		{
			*p2 -= (*p1); 
			p2++; p1++;
		}
	}
	if  (rhs.m_length==1)
	{
		double *p2; p2=pD;
		double ra = *(rhs.pD);
		for(int i=0;i<m_length;i++)
		{
			*p2 -= - ra; 
			p2++;
		}
	}
//	vdouble::FreeIntermediate();
	return *this;

}
vdouble& vdouble::operator-=(const double& ra)
{
	double *p2; p2=pD;
	for(int i=0;i<m_length;i++)
	{
		*p2 -= ra; 
		p2++;
	}
	return *this;
}
//////////////////////////////////////////////////////////////
void vdouble::Resetting() // Обнуляет все элементы вектора
{
	for(int i=0;i<m_length;i++)
		*(pD+i) = 0.0;
}
double& vdouble::End() const // Возвращает последний элемент вектора
{
	return pD[m_length - 1];
}
double& vdouble::End(int n) const// Возвращает последний элемент вектора
{
	if (n > 0 || n <= - m_length)
	{
		//AfxThrowUserException();
		return pD[0];
	}
	return pD[m_length - 1 + n];
}
vdouble vdouble::Select(Vector<int>& indexes) // Возвращает новый вектор, выбирая элементы из данного вектора
{
	vdouble slt;
	for (int i = 0; i < indexes.size; i++)
	{
		if (indexes[i] >= 0 && indexes[i] < m_length)
			slt.push_back(*(pD + indexes[i]));
	}
	return slt;
}
vdouble vdouble::Select(Vector<bool>& vbl) // Возвращает новый вектор, выбирая элементы из данного вектора
{
	if (vbl.size != m_length)
	{
/*		CString strerr;
		strerr.Format( "Error using vdouble::Select(Vector<bool>& vbl) :\n" 
			 "Length of current vector = %i, and size of bool Vector = %i must be equial",
			m_length, vbl.size);
		AfxMessageBox(strerr);
		AfxThrowUserException();*/
		return vdouble();
	}
	vdouble slt;
	for (int i = 0; i < m_length; i++)
	{
		if (vbl[i])
			slt.push_back(*(pD + i));
	}
	return slt;
}
void vdouble::LocalMaximums(vdouble& LocMax, Vector<int>& indexes) const // Формирует вектор локальных максимумов и целочисленный вектор их индексов
{
	int i;
	if (m_length < 3)
	{
/*		CString strerr;
		strerr.Format( "Error using LocalMaximums(vdouble& LocMax, Vector<int> indexes) :\n"
			 "the length of vector = %i is too small \n"
			"must be more than 3", m_length);
		AfxMessageBox(strerr);
		AfxThrowUserException();*/
	}
	if (LocMax.m_length !=0)
		LocMax.DeleteAll();
	if (indexes.size != 0)
		indexes.DeleteAll();
#if 0
	for(int i=1;i<m_length-1;i++)
	{
		if ( *(pD+i - 1) < *(pD+i) && *(pD+i) > *(pD+i +1) )
		{
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
#else
	int k = 0;
	for(i=1;i<m_length-1;i++)
	{
		if ( *(pD+i - 1) < *(pD+i) && *(pD+i) > *(pD+i +1) )
		{
			k++;
		}
	}
	LocMax.resize(k);
	indexes.resize(k);
	k = 0;
	for( i=1;i<m_length-1;i++)
	{
		if ( *(pD+i - 1) < *(pD+i) && *(pD+i) > *(pD+i +1) )
		{
			LocMax[k] = *(pD+i);
			indexes[k] = i;
			k++;
		}
	}
#endif
}
void vdouble::LocalMaximums(int n, vdouble& LocMax, Vector<int>& indexes) const// Формирует вектор локальных максимумов и целочисленный вектор их индексов
{
	int i;
	int wind_length = 2*n+1;
	if (m_length < wind_length)
	{
/*		CString strerr;
		strerr.Format( "Error using LocalMaximums(int n, vdouble& LocMax, Vector<int> indexes) :\n"
			"the length of vector = %i is too small \n"
			"must be more than %i", m_length, wind_length);
		AfxMessageBox(strerr);
		AfxThrowUserException();*/
		return;

	}
	if (LocMax.m_length !=0)
		LocMax.DeleteAll();
	if (indexes.size != 0)
		indexes.DeleteAll();
	bool FlagMax;
#if 0
	for(int i=n;i<m_length-n;i++)
	{
		FlagMax = true;
		for (int j = 1; j <= n; j++)
			FlagMax = FlagMax && 
			(*(pD+i - j) < *(pD+i) && *(pD+i) > *(pD+i + j) );
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
#else
	int k = 0;
	for(i=n;i<m_length-n;i++)
	{
		FlagMax = true;
		for (int j = 1; j <= n; j++)
			FlagMax = FlagMax && 
			(*(pD+i - j) < *(pD+i) && *(pD+i) > *(pD+i + j) );
		if (FlagMax)
		{				
			k++;
		}
	}
	LocMax.resize(k);
	indexes.resize(k);
	k = 0;
	for( i=n;i<m_length-n;i++)
	{
		FlagMax = true;
		for (int j = 1; j <= n; j++)
			FlagMax = FlagMax && 
			(*(pD+i - j) < *(pD+i) && *(pD+i) > *(pD+i + j) );
		if (FlagMax)
		{				
			LocMax[k] = *(pD+i);
			indexes[k] = i;
			k++;
		}
	}

#endif
}
void vdouble::LocalMaximumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes) const// Формирует вектор локальных максимумов и целочисленный вектор их индексов
{
	int i;
	int wind_length = 2*n+1;
	if (m_length < wind_length)
	{
/*		fprintf(stderr, "Error using LocalMaximumsWithBorders(int n, vdouble& LocMax, Vector<int> indexes) :\n");
		fprintf(stderr, "the length of vector = %i is too small \n" , m_length);
		fprintf(stderr, "must be more than %i", wind_length);
		AfxThrowUserException();*/
		return;
	}
	if (LocMax.m_length !=0)
		LocMax.DeleteAll();
	if (indexes.size != 0)
		indexes.DeleteAll();
	bool FlagMax;
	for(i = 1; i < n; i++)
	{
		int j1;
		FlagMax = true;
		for (int j = 1; j <= n; j++)
		{
			j1 = j > i ? i : j;
			FlagMax = FlagMax && 
			(*(pD+i-j1) < *(pD+i) && *(pD+i) > *(pD+i + j) );
		}
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
	for(i=n;i<m_length-n;i++)
	{
		FlagMax = true;
		for (int j = 1; j <= n; j++)
			FlagMax = FlagMax && 
			(*(pD+i - j) < *(pD+i) && *(pD+i) > *(pD+i + j) );
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
	for(i = m_length-n; i < m_length - 1; i++)
	{
		int j2;
		FlagMax = true;
		for (int j = 1; j <= n; j++)
		{
			j2 = j > m_length-1-i ? m_length-1-i : j;
			FlagMax = FlagMax && 
				(*(pD+i - j) < *(pD+i) && *(pD+i) > *(pD+i+j2) );
		}
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
}
void vdouble::LocalMinimums(vdouble& LocMin, Vector<int>& indexes) const// Формирует вектор локальных минимумов и целочисленный вектор их индексов
{
	int i;
	if (m_length < 3)
	{
/*		fprintf(stderr, "Error using LocalMinimums(vdouble& LocMax, Vector<int> indexes) :\n");
		fprintf(stderr, "the length of vector = %i is too small \n" , m_length);
		fprintf(stderr, "must be more than 3" );
		AfxThrowUserException();*/
		return;
	}
	if (LocMin.m_length !=0)
		LocMin.DeleteAll();
	if (indexes.size != 0)
		indexes.DeleteAll();
#if 0
	for(i=1;i<m_length-1;i++)
	{
		if ( *(pD+i - 1) > *(pD+i) && *(pD+i) < *(pD+i +1) )
		{
			LocMin.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
#else
	int j = 0, len;
	for(i=1;i<m_length-1;i++)
	{
		if ( *(pD+i - 1) > *(pD+i) && *(pD+i) < *(pD+i +1) )
		{
			j++;
		}
	}
	len = j;
	LocMin.resize(len);
	indexes.resize(len);
	j = 0;
	for(i=1;i<m_length-1;i++)
	{
		if ( *(pD+i - 1) > *(pD+i) && *(pD+i) < *(pD+i +1) )
		{
			LocMin[j] = *(pD+i);
			indexes[j] = i;
			j++;
		}
	}
#endif
}
void vdouble::LocalMinimums(int n, vdouble& LocMin, Vector<int>& indexes) const// Формирует вектор локальных минимумов и целочисленный вектор их индексов
{
	int i;
	int wind_length = 2*n+1;
	if (m_length < wind_length)
	{
/*		fprintf(stderr, "Error using LocalMinimums(int n, vdouble& LocMax, Vector<int> indexes) :\n");
		fprintf(stderr, "the length of vector = %i is too small \n" , m_length);
		fprintf(stderr, "must be more than %i", wind_length);
		AfxThrowUserException();*/
		return;
	}
	if (LocMin.m_length !=0)
		LocMin.DeleteAll();
	if (indexes.size != 0)
		indexes.DeleteAll();
	bool FlagMin;
#if 0
	for(int i=n;i<m_length-n;i++)
	{
		FlagMin = true;
		for (int j = 1; j <= n; j++)
			FlagMin = FlagMin && (*(pD+i - j) > *(pD+i) && *(pD+i) < *(pD+i + j) );
		if (FlagMin)
		{				
			LocMin.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
#else
	int k = 0, len;
	for(i=n;i<m_length-n;i++)
	{
		FlagMin = true;
		for (int j = 1; j <= n; j++)
			FlagMin = FlagMin && (*(pD+i - j) > *(pD+i) && *(pD+i) < *(pD+i + j) );
		if (FlagMin)
		{				
			k++;
		}
	}
	len = k;
	LocMin.resize(len);
	indexes.resize(len);
	k = 0;
	for( i=n;i<m_length-n;i++)
	{
		FlagMin = true;
		for (int j = 1; j <= n; j++)
			FlagMin = FlagMin && (*(pD+i - j) > *(pD+i) && *(pD+i) < *(pD+i + j) );
		if (FlagMin)
		{				
			LocMin[k] = *(pD+i);
			indexes[k] = i;
			k++;
		}
	}
#endif
}
void vdouble::LocalMinimumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes) const// Формирует вектор локальных максимумов и целочисленный вектор их индексов
{
	int i;
	int wind_length = 2*n+1;
	if (m_length < wind_length)
	{
/*		fprintf(stderr, "Error using LocalMinimumsWithBorders(int n, vdouble& LocMax, Vector<int> indexes) :\n");
		fprintf(stderr, "the length of vector = %i is too small \n" , m_length);
		fprintf(stderr, "must be more than %i", wind_length);
		AfxThrowUserException();*/
		return;
	}
	if (LocMax.m_length !=0)
		LocMax.DeleteAll();
	if (indexes.size != 0)
		indexes.DeleteAll();
	bool FlagMax;
	for(i = 1; i < n; i++)
	{
		int j1;
		FlagMax = true;
		for (int j = 1; j <= n; j++)
		{
			j1 = j > i ? i : j;
			FlagMax = FlagMax && 
				(*(pD+i - j1) > *(pD+i) && *(pD+i) < *(pD+i + j) );
		}
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
	for(i=n;i<m_length-n;i++)
	{
		FlagMax = true;
		for (int j = 1; j <= n; j++)
			FlagMax = FlagMax && 
			(*(pD+i - j) > *(pD+i) && *(pD+i) < *(pD+i + j) );
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
	for(i = m_length-n; i < m_length - 1; i++)
	{
		int j2;
		FlagMax = true;
		for (int j = 1; j <= n; j++)
		{
			j2 = j > m_length-1-i ? m_length-1-i : j;
			FlagMax = FlagMax && 
				(*(pD+i - j) > *(pD+i) && *(pD+i) < *(pD+i + j2) );
		}
		if (FlagMax)
		{				
			LocMax.push_back(*(pD+i));
			indexes.push_back(i);
		}
	}
}
bool vdouble::IsEndLocalMin(int n) const
{
	if (m_length - n - 1 < 0)
		return false;
	bool Answer = false;
	for(int i = m_length - n - 1; i < m_length - n; i++)
	{
		int j1, j2;
		bool FlagMax = true;
		for (int j = 1; j <= n; j++)
		{
			j1 = j > i ? i : j;
			j2 = j > m_length-1-i ? m_length-1-i : j;
			FlagMax = FlagMax && 
				(*(pD+i - j1) > *(pD+i) && *(pD+i) < *(pD+i + j2) );
		}
		if (FlagMax)
		{				
			Answer = true;
		}
	}
	return Answer;
}
bool vdouble::IsEndLocalMax(int n) const
{
	if (m_length - n - 1 < 0)
		return false;
	bool Answer = false;
	for(int i = m_length - n - 1; i < m_length - n; i++)
	{
		int j1, j2;
		bool FlagMax = true;
		for (int j = 1; j <= n; j++)
		{
			j1 = j > i ? i : j;
			j2 = j > m_length-1-i ? m_length-1-i : j;
			FlagMax = FlagMax && 
				(*(pD+i - j1) < *(pD+i) && *(pD+i) > *(pD+i + j2) );
		}
		if (FlagMax)
		{				
			Answer = true;
		}
	}
	return Answer;
}
/*
bool vdouble::IsEndLocalMin(int n)
{
	if (n < 3)
		return false;
	if (n + 2 > m_length)
		return false;
	Vector<int> indexes;
	indexes = sequence(m_length - n - 2, m_length - 1);
	double dt = 1.0,
		epsilon = 1e-9;
	vdouble pinvT,
		tau,
		wma, d1, d2, v = this->operator[](indexes),
		t = dsequence(0.0,1.0, (double)(n+2));
	bool answer = false;
	v.Derivatives(t, dt, pinvT, tau, wma,d1,d2,n,2,true);
	if ( (d1.End(-2) < - epsilon || d1.End(-1) < -epsilon)
		&& d1.End() >= -epsilon
		&& d2.End() > 0.0)
		answer = true;
	return answer;
}
bool vdouble::IsEndLocalMax(int n)
{
	if (n < 3)
		return false;
	if (n + 2 > m_length)
		return false;
	Vector<int> indexes;
	indexes = sequence(m_length - n - 2, m_length - 1);
	double dt = 1.0,
		epsilon = 1e-9;
	vdouble pinvT,
		tau,
		wma, d1, d2, v = this->operator[](indexes),
		t = dsequence(0.0,1.0, (double)(n+2));
	bool answer = false;
	v.Derivatives(t, dt, pinvT, tau, wma,d1,d2,n,2,true);
	if ( (d1.End(-2) > epsilon || d1.End(-1) > epsilon)
		&& d1.End() <=epsilon
		&& d2.End() < 0.0)
		answer = true;
	return answer;
}

bool vdouble::IsEndGrowUp(int n)
{
	if (n < 3)
		return false;
	if (2*n + 2 > m_length)
		return false;
	Vector<int> indexes;
	indexes = sequence(m_length - 2*n - 2, m_length - 1);
	double dt = 1.0,
		epsilon = 1e-9;
	vdouble pinvT,
		tau,
		wma, d1, d2, v = this->operator[](indexes),
		t = dsequence(0.0,1.0, (double)(2*n+2));
	bool answer = false;
	v.Derivatives(t, dt, pinvT, tau, wma,d1,d2,n,2,true);
	if (d1.IsEndLocalMax(n))
		answer = true;
	return answer;
}
bool vdouble::IsEndDecreaseDown(int n)
{
	if (n < 3)
		return false;
	if (2*n + 2 > m_length)
		return false;
	Vector<int> indexes;
	indexes = sequence(m_length - 2*n - 2, m_length - 1);
	double dt = 1.0,
		epsilon = 1e-9;
	vdouble pinvT,
		tau,
		wma, d1, d2, v = this->operator[](indexes),
		t = dsequence(0.0,1.0, (double)(2*n+2));
	bool answer = false;
	v.Derivatives(t, dt, pinvT, tau, wma,d1,d2,n,2,true);
	if (d1.IsEndLocalMin(n))
		answer = true;
	return answer;
}
*/
double vdouble::Max(int iFirst, int iLast) const  // Возвращает мaксимальный элемент вектора
{
	if(m_length == 0)
		return 0.0;
	if (iFirst < 0 || iFirst >= m_length)
		iFirst = 0;
	if (iLast < 0 || iLast >= m_length)
		iLast = 0;
	if (iLast + iFirst >= m_length)
	{
		iFirst = 0;
		iLast = 0;
	}
	double _Max;
	_Max=*(pD + iFirst);
	for(int i=1 + iFirst;i<m_length - iLast;i++)
		_Max = _Max > *(pD+i) ? _Max : *(pD+i);
	return _Max;
}
double vdouble::Max() const  // Возвращает мaксимальный элемент вектора
{
	double _Max = 0.0;
	if(m_length == 0)
		return _Max;
	_Max=*(pD);
	for(int i=1;i<m_length;i++)
		_Max = _Max > *(pD+i) ? _Max : *(pD+i);
	return _Max;
}
double vdouble::Min(int iFirst, int iLast) const // Возвращает минимальный элемент вектора
{
	double _Min = 0.0;
	if(m_length == 0)
		return _Min;
	if (iFirst < 0 || iFirst >= m_length)
		iFirst = 0;
	if (iLast < 0 || iLast >= m_length)
		iLast = 0;
	if (iLast + iFirst >= m_length)
	{
		iFirst = 0;
		iLast = 0;
	}
	_Min=*(pD + iFirst);
	for(int i= 1 + iFirst;i<m_length - iLast;i++)
		_Min = _Min < *(pD+i) ? _Min : *(pD+i);
	return _Min;
}
double vdouble::MinFromTo(int i1, int i2) const // Возвращает минимальный элемент вектора
{
	double _Min = 0.0;
	if(m_length == 0)
		return _Min;
	if (i1 < 0 || i1 >= m_length)
		i1 = 0;
	if (i2 < 0 || i2 >= m_length)
		i2 = m_length - 1;
	if (i1>=i2)
	{
		i1 = 0;
		i2 = m_length - 1;
	}
	_Min=*(pD + i1);
	for(int i = 1 + i1;i <= i2;i++)
		_Min = _Min < *(pD+i) ? _Min : *(pD+i);
	return _Min;
}
double vdouble::MaxFromTo(int i1, int i2) const // Возвращает минимальный элемент вектора
{
	double _Max = 0.0;
	if(m_length == 0)
		return _Max;
	if (i1 < 0 || i1 >= m_length)
		i1 = 0;
	if (i2 < 0 || i2 >= m_length)
		i2 = m_length - 1;
	if (i1>=i2)
	{
		i1 = 0;
		i2 = m_length - 1;
	}
	_Max=*(pD + i1);
	for(int i = 1 + i1;i <= i2;i++)
		_Max = _Max > *(pD+i) ? _Max : *(pD+i);
	return _Max;
}
double vdouble::Min() const // Возвращает минимальный элемент вектора
{
	double _Min = 0.0;
	if(m_length == 0)
		return _Min;
	_Min=*(pD);
	for(int i=1;i<m_length;i++)
		_Min = _Min < *(pD+i) ? _Min : *(pD+i);
	return _Min;
}
double vdouble::MinPositive() const // Возвращает минимальный положительный элемент вектора
{
	double _Min;
	bool started = false;
	for(int i=0;i<m_length;i++)
	{
		if (started)
		{
			_Min = *(pD+i) > 0 && _Min > *(pD+i) ? *(pD+i) : _Min;
		}
		else
		{
			if (*(pD+i) > 0)
			{
				_Min = *(pD+i);
				started = true;
			}
		}
	}
	if (started)
		return _Min;
	else
		return 0.0;
}
double vdouble::MaxAbs() const // Возвращает мaксимальный по абсолютному значению элемент вектора
{
	if(m_length == 0)
		return 0.0;
	double _MaxAbs;
	_MaxAbs=fabs(*(pD));
	for(int i=1;i<m_length;i++)
		_MaxAbs = _MaxAbs > fabs(*(pD+i)) ? _MaxAbs : fabs(*(pD+i));
	return _MaxAbs;
}
double vdouble::MinAbs() const // Возвращает минимальный по абсолютному значению элемент вектора
{
	if(m_length == 0)
		return 0.0;
	double _MinAbs;
	_MinAbs=fabs(*(pD));
	for(int i=1;i<m_length;i++)
		_MinAbs = _MinAbs < fabs(*(pD+i)) ? _MinAbs : fabs(*(pD+i));
	return _MinAbs;
}
double vdouble::Mean() const // Возврашает среднее арифметическое элементов вектора
{
	if (!m_length)
		return 0.0;
	double _Sum;
	_Sum=*(pD);
	for(int i=1;i<m_length;i++)
		_Sum += *(pD+i);
	return _Sum/m_length;
}
double vdouble::Mean(int realElementsNumber) const // Возврашает среднее арифметическое realElementsNumber элементов вектора
{
	if (m_length == 0 || realElementsNumber == 0)
		return 0.0;

	if (realElementsNumber > m_length)
		realElementsNumber = m_length;

	double _Sum;
	_Sum=*(pD);
	for(int i = 1; i < realElementsNumber; i++)
		_Sum += *(pD+i);
	return _Sum/realElementsNumber;
}
void sortrows21(vdouble& x, vdouble& y, vdouble& z)
{
	int len = x.Length();
	if (len != y.Length() || len != z.Length() )
	{
		MessageBox(0,_T("len != y.Length() || len != z.Length()"),_T("sortrows21"),0);
		return;
	}
	double *pSortX;
	if ((pSortX = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*sizeof(double))) == NULL && len != 0)
	{
		MessageBox(0, _T("sortrows21 - Not enough memory"),
			_T(""), 0);
		return;
	}
	double *pSortY;
	if ((pSortY = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*sizeof(double))) == NULL && len != 0)
	{
		MessageBox(0, _T("sortrows21 - Not enough memory"),
			_T(""), 0);
		return;
	}
	double *pSortZ;
	if ((pSortZ = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*sizeof(double))) == NULL && len != 0)
	{
		MessageBox(0, _T("sortrows21 - Not enough memory"),
			_T(""), 0);
		return;
	}
	int i;
	for ( i = 0 ; i < len ; i++ )
	{
		pSortX[i] = x[i];
		pSortY[i] = y[i];
		pSortZ[i] = z[i];
	}
	bool sortedY = false;
	while(!sortedY)
	{
		int j;
		sortedY = true;
		for ( i = 0, j = 1 ; j < len ; j++ )
		{
			if (pSortY[j] < pSortY[j-1])
			{
				if (pSortY[j] <= pSortY[i])
				{
					double tempY = pSortY[j];
					double tempX = pSortX[j];
					double tempZ = pSortZ[j];
					int ii;
					for (ii = j; ii > i; ii--)
					{
						pSortY[ii] = pSortY[ii-1];
						pSortX[ii] = pSortX[ii-1];
						pSortZ[ii] = pSortZ[ii-1];
					}
					pSortY[i] = tempY;
					pSortX[i] = tempX;
					pSortZ[i] = tempZ;
					sortedY = false;
				}
				else
				{
					int jj = j;
					double tempY = pSortY[j];
					double tempX = pSortX[j];
					double tempZ = pSortZ[j];
					do
					{
						pSortY[jj] = pSortY[jj-1];
						pSortX[jj] = pSortX[jj-1];
						pSortZ[jj] = pSortZ[jj-1];
						jj--;
					}
					while (tempY < pSortY[jj-1]);
					pSortY[jj] = tempY;
					pSortX[jj] = tempX;
					pSortZ[jj] = tempZ;
					sortedY = false;
				}
			}
		}
	}
	// теперь сортируем по x
	bool sortedX = false;
	while(!sortedX)
	{
		int j;
		sortedX = true;
		for ( i = 0, j = 1 ; j < len ; j++ )
		{
			if (pSortX[j] < pSortX[j-1])
			{
				if (pSortX[j] <= pSortX[i])
				{
					double tempY = pSortY[j];
					double tempX = pSortX[j];
					double tempZ = pSortZ[j];
					int ii;
					for (ii = j; ii > i; ii--)
					{
						pSortY[ii] = pSortY[ii-1];
						pSortX[ii] = pSortX[ii-1];
						pSortZ[ii] = pSortZ[ii-1];
					}
					pSortY[i] = tempY;
					pSortX[i] = tempX;
					pSortZ[i] = tempZ;
					sortedX = false;
				}
				else
				{
					int jj = j;
					double tempY = pSortY[j];
					double tempX = pSortX[j];
					double tempZ = pSortZ[j];
					do
					{
						pSortY[jj] = pSortY[jj-1];
						pSortX[jj] = pSortX[jj-1];
						pSortZ[jj] = pSortZ[jj-1];
						jj--;
					}
					while (tempX < pSortX[jj-1]);
					pSortY[jj] = tempY;
					pSortX[jj] = tempX;
					pSortZ[jj] = tempZ;
					sortedX = false;
				}
			}
		}
	}
	for ( i = 0 ; i < len ; i++ )
	{
		x[i] = pSortX[i];
		y[i] = pSortY[i];
		z[i] = pSortZ[i];
	}
	if (pSortX)
		HeapFree(GetProcessHeap(), 0,pSortX);
	if (pSortY)
		HeapFree(GetProcessHeap(), 0,pSortY);
	if (pSortZ)
		HeapFree(GetProcessHeap(), 0,pSortZ);

}
double Median_sort(double *p, int n) // Возврашает среднее арифметическое элементов вектора
{
	if (n<1)
		return 0.0;
	double *pSort;
	if ((pSort = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*SD)) == NULL && n != 0)
	{
		MessageBox(0, _T("vdouble::Median() - Not enough memory"),
			_T("vdouble"), 0);
		return 0.0;
	}

	int i;
	for ( i = 0 ; i < n ; i++ )
	{
		pSort[i] = p[i];
	}

	bool sorted = false;
	while(!sorted)
	{
		int j;
		sorted = true;
		for ( i = 0, j = 1 ; j < n ; j++ )
		{
			if (pSort[j] < pSort[j-1])
			{
				if (pSort[j] <= pSort[i])
				{
					double temp = pSort[j];
					int ii;
					for (ii = j; ii > i; ii--)
						pSort[ii] = pSort[ii-1];
					pSort[i] = temp;
					sorted = false;
				}
				else
				{
					int jj = j;
					double temp = pSort[j];
					do
					{
						pSort[jj] = pSort[jj-1];
						jj--;
					}
					while (temp < pSort[jj-1]);
					pSort[jj] = temp;
					sorted = false;
				}
			}
		}
	}

	double median ;
	median = pSort[n/2];
	if (pSort)
		HeapFree(GetProcessHeap(), 0,pSort);

	return median;
}

double Quantil(double qu, double *p, int len) 
{
	// find min and max of diapazon
	int i;
	double min, max;
	for ( i = 0; i < len; i++ )
	{
		if(i == 0)
		{
			min = *p;
			max = *p;
		}
		else
		{
			if (*(p+i) < min)
				min = *(p+i);
			if (*(p+i) > max)
				max = *(p+i);
		}
	}
//	char str[225];
//	sprintf(str,"min = %lf max = %lf", min, max);
//	MessageBox(0,str,"double Median(double *p, int len)",0);
	// allocate memory for histogramm
	int N = 1000;
	double *pn;
	if ((pn = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,N*SD)) == NULL && len != 0)
	{
		MessageBox(0, _T("vdouble::Median() - Not enough memory"),
			_T("vdouble"), 0);
		return 0.0;
	}
	// zero of histogramm registers
	for ( i = 0 ; i < N ; i++ )
	{
		pn[i] = 0.0;
	}
	int j;
	double nsum = 0., nsum1 = 0., nsum2 = 0.;
	for ( i = 0; i < len; i++)
	{
		// fulling of histogramm
		j = int( (*(p+i) - min) / (max-min) * double(N-1) );
		if (j >= 0 && j < N)
			pn[j] = pn[j] + 1.0;
	}
	for ( i = 0 ; i < N ; i++ )
	{
		// summing of histogramm
		nsum += *(pn+i);
	}
	// taking left halfsumm of histogramm
	int i1 = -1;
	while(nsum > 0 && nsum1 + pn[i1+1] < nsum*qu)
	{
		i1++; nsum1 += pn[i1]; 
	}
	// taking right halfsumm of histogramm
	int i2 = N;
	while(nsum > 0 && nsum2 + pn[i2-1] < nsum*(1.0 - qu))
	{
		i2--; nsum2 += pn[i2]; 
	}

//	sprintf(str,"nsum = %lf nsum1 = %lf nsum2 = %lf", nsum, nsum1, nsum2);
//	MessageBox(0,str,"double Median(double *p, int len)",0);
	
	// the part for left and for right sum
	double d1 = double (nsum1) / double (nsum);
	double d2 = double (nsum2) / double (nsum);
	// приближения слева и справа искомого квантиля
	double x1 = min + double(i1) * (max - min) / double(N-1);
	double x2 = min + double(i2) * (max - min) / double(N-1);

	if (pn)
		HeapFree(GetProcessHeap(), 0, pn);

	// доля гистограммы, не учтённая в правой и в левой сумме (1.0-d2-d1)
	// разница между приближениями искомого квантиля (x2-x1)
	// (qu-d1) - доля гистограммы, которую надо прибавить к левой сумме, 
	// чтобы получилось деление гистограммы в соответствие с квантилем

	return x1 + (x2-x1)*(qu-d1)/(1.0-d2-d1);
}

double Median(double *p, int len) // Возврашает среднее арифметическое элементов вектора
{
	// find min and max of diapazon
	int i;
	double min, max;
	for ( i = 0; i < len; i++ )
	{
		if(i == 0)
		{
			min = *p;
			max = *p;
		}
		else
		{
			if (*(p+i) < min)
				min = *(p+i);
			if (*(p+i) > max)
				max = *(p+i);
		}
	}
//	char str[225];
//	sprintf(str,"min = %lf max = %lf", min, max);
//	MessageBox(0,str,"double Median(double *p, int len)",0);
	// allocate memory for histogramm
	int N = 1000;
	double *pn;
	if ((pn = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,N*SD)) == NULL && len != 0)
	{
		MessageBox(0, _T("vdouble::Median() - Not enough memory"),
			_T("vdouble"), 0);
		return 0.0;
	}
	// zero of histogramm registers
	for ( i = 0 ; i < N ; i++ )
	{
		pn[i] = 0.0;
	}
	int j;
	double nsum = 0, nsum1 = 0, nsum2 = 0;
	for ( i = 0; i < len; i++)
	{
		// fulling of histogramm
		j = int( (*(p+i) - min) / (max-min) * double(N-1) );
		if (j >= 0 && j < N)
			pn[j] = pn[j] + 1.0;
	}
	for ( i = 0 ; i < N ; i++ )
	{
		// summing of histogramm
		nsum += *(pn+i);
	}
	// taking left halfsumm of histogramm
	int i1 = -1;
	while(nsum > 0 && nsum1 + pn[i1+1] < nsum/2)
	{
		i1++; nsum1 += pn[i1]; 
	}
	// taking right halfsumm of histogramm
	int i2 = N;
	while(nsum > 0 && nsum2 + pn[i2-1] < nsum/2)
	{
		i2--; nsum2 += pn[i2]; 
	}

//	sprintf(str,"nsum = %lf nsum1 = %lf nsum2 = %lf", nsum, nsum1, nsum2);
//	MessageBox(0,str,"double Median(double *p, int len)",0);
	
	double d1 = double (nsum1) / double (nsum);
	double d2 = double (nsum2) / double (nsum);
	double x1 = min + double(i1) * (max - min) / double(N-1);
	double x2 = min + double(i2) * (max - min) / double(N-1);


	double median = x1 + (x2-x1)*(0.5-d1)/(1.0-d2-d1);

	if (pn)
		HeapFree(GetProcessHeap(), 0, pn);

	return median;
}

double vdouble::Median() const // Возврашает среднее арифметическое элементов вектора
{
	if (!m_length)
		return 0.0;

	double min = Min(), max = Max();
//	char str[225];
//	sprintf(str,"min = %lf max = %lf", min, max);
	//MessageBox(0,str,"double vdouble::Median2()",0);

	vdouble n;
	// x = dsequence(min,df,max);
	// n = hist(*this,n,x);

	
	int N = 1000;

	if (n.Length() != N)
		n.resize(N, 0.0);

	int j;

	for (int i = 0; i < m_length; i++)
	{
		j = int( (*(pD+i) - min) / (max-min) * double(N-1) );
		if (j >= 0 && j < N)
			n(j) = n(j) + 1.0;
	}

	double nsum = n.Sum(), nsum1 = 0, nsum2 = 0;

	int i1 = -1;
	while(nsum > 0 && nsum1 + n[i1+1] < nsum/2)
	{
		i1++; nsum1 += n[i1]; 
	}

	int i2 = n.Length();
	while(nsum > 0 && nsum2 + n[i2-1] < nsum/2)
	{
		i2--; nsum2 += n[i2]; 
	}
//	sprintf(str,"nsum = %lf nsum1 = %lf nsum2 = %lf", nsum, nsum1, nsum2);
//	MessageBox(0,str,"double vdouble::Median2()",0);

	double d1 = double (nsum1) / double (nsum);
	double d2 = double (nsum2) / double (nsum);
	double x1 = min + double(i1) * (max - min) / double(N-1);
	double x2 = min + double(i2) * (max - min) / double(N-1);


	double median = x1 + (x2-x1)*(0.5-d1)/(1.0-d2-d1);

	return median;
}


double vdouble::Median_sort() const// Возврашает среднее арифметическое элементов вектора
{
	if (!m_length)
		return 0.0;
	double *pSort;
  // using namespace std;
 //  vector <double> v1;
	if ((pSort = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
		MessageBox(0, _T("vdouble::Median() - Not enough memory"),
			_T("vdouble"), 0);
		return 0.0;
	}

	int i;
	for ( i = 0 ; i < m_length ; i++ )
	{
		pSort[i] = pD[i];
	}

	bool sorted = false;
	while(!sorted)
	{
		int j;
		sorted = true;
		for ( i = 0, j = 1 ; j < m_length ; j++ )
		{
			if (pSort[j] < pSort[j-1])
			{
				if (pSort[j] <= pSort[i])
				{
					double temp = pSort[j];
					int ii;
					for (ii = j; ii > i; ii--)
						pSort[ii] = pSort[ii-1];
					pSort[i] = temp;
					sorted = false;
				}
				else
				{
					int jj = j;
					double temp = pSort[j];
					do
					{
						pSort[jj] = pSort[jj-1];
						jj--;
					}
					while (temp < pSort[jj-1]);
					pSort[jj] = temp;
					sorted = false;
				}
			}
		}
	}

	double median ;
	median = pSort[m_length/2];
	if (pSort)
		HeapFree(GetProcessHeap(), 0,pSort);

	return median;
}
double vdouble::Root_mean_square_Dismissal() const // Возврашает среднеквадратичное отклонение
{
	if(m_length == 0)
		return 0.0;
	double _mean = Mean();
	double _SquareSum;
	_SquareSum = pow(*(pD) - _mean, 2.0);
	for(int i=1;i<m_length;i++)
		_SquareSum += pow(*(pD+i) - _mean, 2.0);
	return sqrt( _SquareSum / (m_length - 1) );
}
double vdouble::Sum() const // Возврашает сумму элементов вектора
{
	if(m_length == 0)
		return 0.0;
	double _Sum;
	_Sum = *pD;
	for(int i=1;i<m_length;i++)
		_Sum += *(pD+i);
	return _Sum;
}
double vdouble::SquareSum() const // Возврашает сумму квадратов элементов вектора
{
	if(m_length == 0)
		return 0.0;
	double _SquareSum=0.0;
	double *pv; pv = pD;
	_SquareSum=(*(pv)) * (*(pv));
	for(int i=1;i<m_length;i++)
	{
		pv++;
		_SquareSum += *pv * *pv;
	}
	return _SquareSum;
}
double vdouble::SquareSumFrom(int i0) const // Возврашает сумму квадратов элементов вектора
{
	if(m_length == 0)
		return 0.0;
	if (i0 < 0 || i0 >= m_length)
	{
/*		fprintf(stderr,"Error using SquareSumFrom(int i0) : \n");
		fprintf(stderr,"reseived invalid index = %i, it must be in interval [0 %i]\n",i0,m_length-1);
		AfxThrowUserException();*/
		return 0;
	}
	double _SquareSum=0.0;
	double *pv;
	pv = pD+i0;
	for(int i=i0;i<m_length;i++)
	{
		_SquareSum += (*(pv)) * (*(pv));
		pv++;
	}
	return _SquareSum;
}
void vdouble::push_back(double a) // Добавляет элемент в конец вектора
{
	m_length++;
	double *pD2;
	if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
/*		fprintf(stderr,"vdouble::push_back(double a) - Not enough memory");
		AfxThrowMemoryException();*/
		return;
	}
	m_szMemory +=SD;
	for(int i=0; i<(m_length-1); i++)
		*(pD2+i) = *(pD+i);
	*(pD2+m_length-1) = a;
	if (m_length >= 2) HeapFree(GetProcessHeap(), 0,pD);
	pD=pD2;
}
void vdouble::push_front(double a) // Добавляет элемент в начало вектора
{
	m_length++;
	double *pD2;
	if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
/*		fprintf(stderr,"vdouble::push_back(double a) - Not enough memory");
		AfxThrowMemoryException();*/
		return;
	}
	m_szMemory +=SD;
	for(int i = 1; i < m_length; i++)
		*(pD2 + i) = *(pD + i - 1);
	*pD2 = a;
	if (m_length >= 2) HeapFree(GetProcessHeap(), 0,pD);
	pD=pD2;
}


void vdouble::DeleteEnd() // Удаляет 1 последний элемент вектора
{
	m_length--;
	double *pD2;
	if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
/*		fprintf(stderr,"vdouble::DeleteEnd() - Not enough memory");
		AfxThrowMemoryException();*/
		return;
	}
	m_szMemory -=SD;
	for(int i=0; i<(m_length); i++)
		*(pD2+i) = *(pD+i);
	if (m_length >= 0) HeapFree(GetProcessHeap(), 0,pD);
	pD=pD2;
}
void vdouble::DeleteEnd(int n) // Удаляет n последних элементов вектора
{
	if (n > m_length)
	{
/*		fprintf(stderr, "Error using vdouble::DeleteEnd(int n) : n must be less than length of vector\n");
		AfxThrowUserException();*/
		return;
	}
	m_length -= n;
	double *pD2;
	if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
/*		fprintf(stderr,"vdouble::DeleteEnd(int) - Not enough memory");
		AfxThrowMemoryException();*/
		return;
	}
	m_szMemory -=n*SD;
	for(int i=0; i<m_length; i++)
		*(pD2+i) = *(pD+i);
    HeapFree(GetProcessHeap(), 0,pD);
	pD=pD2;
}
void vdouble::DeleteElement(int index) // Удаляет index-ный элемент вектора
{
	int i;
	if (index > m_length-1 || index < 0)
	{
/*		fprintf(stderr, "Error using vdouble::DeleteElement(int index) : index out of vector's indexes \n");
		AfxThrowUserException();*/
		return;
	}
	m_length--;
	double *pD2;
	if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
/*		fprintf(stderr,"vdouble::DeleteElement(int& index) - Not enough memory");
		AfxThrowMemoryException();*/
		return;
	}
	m_szMemory -=SD;
	for(i=0; i<index; i++)
		*(pD2+i) = *(pD+i);
	for(i=index; i<m_length; i++)
		*(pD2+i) = *(pD+i+1);
	HeapFree(GetProcessHeap(), 0,pD);
	pD=pD2;
}
void vdouble::DeleteElements(Vector<bool>& vbl) // Удаляет элементы вектора
{
	if (m_length != vbl.size)
	{
/*		fprintf(stderr, "Error using vdouble::DeleteElements(Vector<bool>& vbl) : size of input bool vector must be equial to length of current vector\n");
		AfxThrowUserException();*/
		return;
	}
	int old_length = m_length;
	int j=-1;// new indexes
	m_length -= Find(vbl).size;
	double *pD2;
	if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
	{
/*		fprintf(stderr,"vdouble::DeleteElements(Vector<bool>& vbl) - Not enough memory");
		AfxThrowMemoryException();*/
		return;
	}
	m_szMemory -=Find(vbl).size*SD;
	for(int i=0; i<old_length; i++) //  old indexes
	{
		if (! vbl[i])
		{
			j++;
			*(pD2+j) = *(pD+i);
		}
	}
	HeapFree(GetProcessHeap(), 0,pD);
	pD=pD2;
}
void vdouble::DeleteAll() // Удаляет все элементы вектора
{
	if (m_length >= 1)
	{
		m_szMemory -=m_length*SD;
		m_length = 0;
		double *pD2;
		if ((pD2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length*SD)) == NULL && m_length != 0)
		{
/*			fprintf(stderr,"vdouble::DeleteAll() - Not enough memory");
			AfxThrowMemoryException();*/
			return;
		}
		if (pD)
			HeapFree(GetProcessHeap(), 0,pD);
		pD=pD2;
	}
}
vdouble vdouble::CumMeanSquareSum() // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента
{
	int len = m_length;
	vdouble cms = vdouble(len);
	double *pv, *pr, sum = 0.0, num = 0.0;
	pr = cms.pD;
	pv = pD;
	for (int i = 0; i < len; i++)
	{
		sum += *pv * *pv; pv++;
		num += 1.0;
		*(pr+i) = sqrt(sum / num);
	}
	return cms;
}
vdouble vdouble::CumMeanSquareSumFrom(int i0) // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента, начиная с i0
{
	int len = m_length - i0;
	vdouble cms = vdouble(len);
	double *pv, *pr, sum = 0.0, num = 0.0;
	pr = cms.pD;
	pv = pD + i0;
	for (int i = 0; i < len; i++)
	{
		sum += *pv * *pv; pv++;
		num += 1.0;
		*(pr+i) = sqrt(sum / num);
	}
	return cms;
}
vdouble vdouble::CumSum() // Возврашает вектор кумулятивных сумм
{
	int len = m_length;
	vdouble cms = vdouble(len);
	double *pv, *pr, sum = 0.0;
	pr = cms.pD;
	pv = pD;
	for (int i = 0; i < len; i++)
	{
		sum += *(pv+i);
		*(pr+i) = sum;
	}
	return cms;
}

vdouble vdouble::CumMeanSum() // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента
{
	int len = m_length;
	vdouble cms = vdouble(len);
	double *pv, *pr, sum = 0.0, num = 0.0;
	pr = cms.pD;
	pv = pD;
	for (int i = 0; i < len; i++)
	{
		sum += *(pv+i);
		num += 1.0;
		*(pr+i) = sum / num;
	}
	return cms;
}
vdouble vdouble::CumMeanSumFrom(int i0) // Возврашает вектор кумулятивных сумм, усреднённых по номеру элемента, начиная с i0
{
	int len = m_length - i0;
	vdouble cms = vdouble(len);
	double *pv, *pr, sum = 0.0, num = 0.0;
	pr = cms.pD;
	pv = pD + i0;
	for (int i = 0; i < len; i++)
	{
		sum += *(pv+i);
		num += 1.0;
		*(pr+i) = sum / num;
	}
	return cms;
}
vdouble vdouble::DiffVector() const // Вектор конечных разностей (возвращает вектор на 1 короче)
{
	if (m_length < 2)
	{
/*		fprintf(stderr,"Error using vdouble::Diff():\n length must be more then 1\n");
		AfxThrowUserException();*/
		return *this;
	}
	int len_1 = m_length - 1;
	vdouble Diff = vdouble(len_1);
	double *pv, *pr;
	pr = Diff.pD;
	pv = pD;
	for (int i = 0; i < len_1; i++)
	{
		*(pr+i) = *(pv+1) - *(pv);
		pv++;
	}
	return Diff;
}
vdouble vdouble::SumVector() const //Вектор конечных сумм (сумм в соседних точках) - возвр. вект. на 1 короче
{
	if (m_length < 2)
	{
/*		fprintf(stderr,"Error using vdouble::MeanInIntervals():\n length must be more then 1\n");
		AfxThrowUserException();*/
		return *this;
	}
	int len_1 = m_length - 1;
	vdouble Mean = vdouble(len_1);
	double *pv, *pr;
	pr = Mean.pD;
	pv = pD;
	for (int i = 0; i < len_1; i++)
	{
		*(pr+i) = *(pv+1) + *(pv);
		pv++;
	}
	return Mean;
}
double vdouble::Trapz(const vdouble& t)
{
	if (m_length != t.m_length)
	{
/*		fprintf(stderr,  "Error using vdouble::Trapz :\n the lengthes of the vectors must be the same\n");
		AfxThrowUserException();*/
		return 0;
	}
	return SumVector().ScalarProduct(t.DiffVector()) / 2;
}
//////////////////////////////////////////////////////////////
double vdouble::ScalarProduct(const vdouble& rhs)
{
	if  (rhs.m_length != m_length)
	{
		TCHAR errstr[1024];
		stprintf_s (errstr, 1024, _T("%s\n%s\n%d != %d\n"),
			_T("Error using vdouble::ScalarProduct():\n"),
			_T("the lengthes of the vectors must be the same"),
			rhs.m_length, m_length);
		MessageBox(0,errstr, _T("Error"), 0);
        //ExitProcess(0);
		return 0;
	}
	double *p1, *p2;
	p2=pD;p1=rhs.pD;
	double _ScalarProduct = (*p2) * (*p1);
	for(int i=1;i<m_length;i++)
	{
		p2++; p1++;
		_ScalarProduct += (*p2) * (*p1);
	}
	return _ScalarProduct;
}

double vdouble::ScalarProductFrom(int i0, const vdouble& rhs)
{
	int len = rhs.m_length;
	if  (rhs.m_length + i0 != m_length)
	{
/*		fprintf(stderr,  "Error using vdouble::ScalarProduct(): \n");
		fprintf(stderr,  "the lengthes of the vectors must be the same\n");
		AfxThrowUserException();*/
		return 0;
	}
	double *p1, *p2;
	p2=pD + i0;
	p1=rhs.pD;
	double _ScalarProduct = (*p2) * (*p1);
	for(int i=1;i<len;i++)
	{
		p2++; p1++;
		_ScalarProduct += (*p2) * (*p1);
	}
	return _ScalarProduct;
}
void vdouble::FourierTransform(const vdouble& t,
					  vdouble& omega, vdouble& A, 
					  vdouble& fi )
{
	if (m_length != t.m_length)
	{
/*		fprintf(stderr,  "Error using FourierTransform : the lengthes of the vectors must be the same\n");
		AfxThrowUserException();*/
		return;
	}
	double T = t.End() - t[0]; 
	if (T <=0)
	{
/*		fprintf(stderr,  "Error using vdouble::FourierTransform : Vector of time must be increase\n");
		AfxThrowUserException();*/
		return;
	}
	
	double w = 2 * PI / T;
	vdouble a, b;
	omega = vdouble(m_length);
	a = vdouble(m_length);
	b = vdouble(m_length);
	A = vdouble(m_length);
	fi = vdouble(m_length);

	for (int k = 0; k < m_length; k++)
	{
		omega[k] = (k+1) * w;
		a[k] = ( (*this) * cos(omega[k] * t) ).Trapz(t);
		b[k] = ( (*this) * sin(omega[k] * t) ).Trapz(t);
	}
	A = sqrt(a*a + b*b);
	fi = -atan2(b, a);
	return;
}

/*
//============Функции Лаггер - спектральных преобразований ============
vdouble LagerPolynom(const int& n, const double& alpha, const double& beta, vdouble& t)
{
	switch(n)
	{
	// 2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 0 : return sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-2*alpha*t)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 1 : return (1.0-2.0*alpha*t)*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-4*alpha*t+2*alpha^2*t^2)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 2 : return (1.0-4.0*alpha*t+2.0*pow(alpha*t,2.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-6*alpha*t+6*alpha^2*t^2-4/3*alpha^3*t^3)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 3 : return (1.0-6.0*alpha*t+6.0*pow(alpha*t,2.0)-4.0/3.0*pow(alpha*t,3.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-8*alpha*t+12*alpha^2*t^2-16/3*alpha^3*t^3+2/3*alpha^4*t^4)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 4 : return (1.0-8.0*alpha*t+12.0*pow(alpha*t,2.0)-16.0/3.0*pow(alpha*t,3.0)+2.0/3.0*pow(alpha*t,4.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-10*alpha*t+20*alpha^2*t^2-40/3*alpha^3*t^3+10/3*alpha^4*t^4-4/15*alpha^5*t^5)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 5 : return (1.0-10.0*alpha*t+20.0*pow(alpha*t,2.0)-40.0/3.0*pow(alpha*t,3.0)+10.0/3.0*pow(alpha*t,4.0)-4.0/15.0*pow(alpha*t,5.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-12*alpha*t+30*alpha^2*t^2-80/3*alpha^3*t^3+10*alpha^4*t^4-8/5*alpha^5*t^5+4/45*alpha^6*t^6)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 6 : return (1.0-12.0*alpha*t+30.0*pow(alpha*t,2.0)-80.0/3.0*pow(alpha*t,3.0)+10.0*pow(alpha*t,4.0)-8.0/5.0*pow(alpha*t,5.0)+4.0/45.0*pow(alpha*t,6.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-14*alpha*t+42*alpha^2*t^2-140/3*alpha^3*t^3+70/3*alpha^4*t^4-28/5*alpha^5*t^5+28/45*alpha^6*t^6-8/315*alpha^7*t^7)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 7 : return (1.0-14.0*alpha*t+42.0*pow(alpha*t,2.0)-140.0/3.0*pow(alpha*t,3.0)+70.0/3.0*pow(alpha*t,4.0)-28.0/5.0*pow(alpha*t,5.0)+28.0/45.0*pow(alpha*t,6.0)-8.0/315.0*pow(alpha*t,7.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-16*alpha*t+56*alpha^2*t^2-224/3*alpha^3*t^3+140/3*alpha^4*t^4-224/15*alpha^5*t^5+112/45*alpha^6*t^6-64/315*alpha^7*t^7+2/315*alpha^8*t^8)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 8 : return (1.0-16.0*alpha*t+56.0*pow(alpha*t,2.0)-224.0/3.0*pow(alpha*t,3.0)+140.0/3.0*pow(alpha*t,4.0)-224.0/15.0*pow(alpha*t,5.0)+112.0/45.0*pow(alpha*t,6.0)-64.0/315.0*pow(alpha*t,7.0)+2.0/315.0*pow(alpha*t,8.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-18*alpha*t+72*alpha^2*t^2-112*alpha^3*t^3+84*alpha^4*t^4-168/5*alpha^5*t^5+112/15*alpha^6*t^6-32/35*alpha^7*t^7+2/35*alpha^8*t^8-4/2835*alpha^9*t^9)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 9 : return (1.0-18.0*alpha*t+72.0*pow(alpha*t,2.0)-112.0*pow(alpha*t,3.0)+84.0*pow(alpha*t,4.0)-168.0/5.0*pow(alpha*t,5.0)+112.0/15.0*pow(alpha*t,6.0)-32.0/35.0*pow(alpha*t,7.0)+2.0/35.0*pow(alpha*t,8.0)-4.0/2835.0*pow(alpha*t,9.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-20*alpha*t+90*alpha^2*t^2-160*alpha^3*t^3+140*alpha^4*t^4-336/5*alpha^5*t^5+56/3*alpha^6*t^6-64/21*alpha^7*t^7+2/7*alpha^8*t^8-8/567*alpha^9*t^9+4/14175*alpha^10*t^10)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 10 : return (1.0-20.0*alpha*t+90.0*pow(alpha*t,2.0)-160.0*pow(alpha*t,3.0)+140.0*pow(alpha*t,4.0)-336.0/5.0*pow(alpha*t,5.0)+56.0/3.0*pow(alpha*t,6.0)-64.0/21.0*pow(alpha*t,7.0)+2.0/7.0*pow(alpha*t,8.0)-8.0/567.0*pow(alpha*t,9.0)+4.0/14175.0*pow(alpha*t,10.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-22*alpha*t+110*alpha^2*t^2-220*alpha^3*t^3+220*alpha^4*t^4-616/5*alpha^5*t^5+616/15*alpha^6*t^6-176/21*alpha^7*t^7+22/21*alpha^8*t^8-44/567*alpha^9*t^9+44/14175*alpha^10*t^10-8/155925*alpha^11*t^11)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 11 : return (1.0-22.0*alpha*t+110.0*pow(alpha*t,2.0)-220.0*pow(alpha*t,3.0)+220.0*pow(alpha*t,4.0)-616.0/5.0*pow(alpha*t,5.0)+616.0/15.0*pow(alpha*t,6.0)-176.0/21.0*pow(alpha*t,7.0)+22.0/21.0*pow(alpha*t,8.0)-44.0/567.0*pow(alpha*t,9.0)+44.0/14175.0*pow(alpha*t,10.0)-8.0/155925.0*pow(alpha*t,11.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-24*alpha*t+132*alpha^2*t^2-880/3*alpha^3*t^3+330*alpha^4*t^4-1056/5*alpha^5*t^5+1232/15*alpha^6*t^6-704/35*alpha^7*t^7+22/7*alpha^8*t^8-176/567*alpha^9*t^9+88/4725*alpha^10*t^10-32/51975*alpha^11*t^11+4/467775*alpha^12*t^12)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 12 : return (1.0-24.0*alpha*t+132.0*pow(alpha*t,2.0)-880.0/3.0*pow(alpha*t,3.0)+330.0*pow(alpha*t,4.0)-1056.0/5.0*pow(alpha*t,5.0)+1232.0/15.0*pow(alpha*t,6.0)-704.0/35.0*pow(alpha*t,7.0)+22.0/7.0*pow(alpha*t,8.0)-176.0/567.0*pow(alpha*t,9.0)+88.0/4725.0*pow(alpha*t,10.0)-32.0/51975.0*pow(alpha*t,11.0)+4.0/467775.0*pow(alpha*t,12.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-26*alpha*t+156*alpha^2*t^2-1144/3*alpha^3*t^3+1430/3*alpha^4*t^4-1716/5*alpha^5*t^5+2288/15*alpha^6*t^6-4576/105*alpha^7*t^7+286/35*alpha^8*t^8-572/567*alpha^9*t^9+1144/14175*alpha^10*t^10-208/51975*alpha^11*t^11+52/467775*alpha^12*t^12-8/6081075*alpha^13*t^13)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 13 : return (1.0-26.0*alpha*t+156.0*pow(alpha*t,2.0)-1144.0/3.0*pow(alpha*t,3.0)+1430.0/3.0*pow(alpha*t,4.0)-1716.0/5.0*pow(alpha*t,5.0)+2288.0/15.0*pow(alpha*t,6.0)-4576.0/105.0*pow(alpha*t,7.0)+286.0/35.0*pow(alpha*t,8.0)-572.0/567.0*pow(alpha*t,9.0)+1144.0/14175.0*pow(alpha*t,10.0)-208.0/51975.0*pow(alpha*t,11.0)+52.0/467775.0*pow(alpha*t,12.0)-8.0/6081075.0*pow(alpha*t,13.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-28*alpha*t+182*alpha^2*t^2-1456/3*alpha^3*t^3+2002/3*alpha^4*t^4-8008/15*alpha^5*t^5+4004/15*alpha^6*t^6-9152/105*alpha^7*t^7+286/15*alpha^8*t^8-1144/405*alpha^9*t^9+572/2025*alpha^10*t^10-416/22275*alpha^11*t^11+52/66825*alpha^12*t^12-16/868725*alpha^13*t^13+8/42567525*alpha^14*t^14)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 14 : return (1.0-28.0*alpha*t+182.0*pow(alpha*t,2.0)-1456.0/3.0*pow(alpha*t,3.0)+2002.0/3.0*pow(alpha*t,4.0)-8008.0/15.0*pow(alpha*t,5.0)+4004.0/15.0*pow(alpha*t,6.0)-9152.0/105.0*pow(alpha*t,7.0)+286.0/15.0*pow(alpha*t,8.0)-1144.0/405.0*pow(alpha*t,9.0)+572.0/2025.0*pow(alpha*t,10.0)-416.0/22275.0*pow(alpha*t,11.0)+52.0/66825.0*pow(alpha*t,12.0)-16.0/868725.0*pow(alpha*t,13.0)+8.0/42567525.0*pow(alpha*t,14.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-30*alpha*t+210*alpha^2*t^2-1820/3*alpha^3*t^3+910*alpha^4*t^4-4004/5*alpha^5*t^5+4004/9*alpha^6*t^6-1144/7*alpha^7*t^7+286/7*alpha^8*t^8-572/81*alpha^9*t^9+572/675*alpha^10*t^10-104/1485*alpha^11*t^11+52/13365*alpha^12*t^12-8/57915*alpha^13*t^13+8/2837835*alpha^14*t^14-16/638512875*alpha^15*t^15)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 15 : return (1.0-30.0*alpha*t+210.0*pow(alpha*t,2.0)-1820.0/3.0*pow(alpha*t,3.0)+910.0*pow(alpha*t,4.0)-4004.0/5.0*pow(alpha*t,5.0)+4004.0/9.0*pow(alpha*t,6.0)-1144.0/7.0*pow(alpha*t,7.0)+286.0/7.0*pow(alpha*t,8.0)-572.0/81.0*pow(alpha*t,9.0)+572.0/675.0*pow(alpha*t,10.0)-104.0/1485.0*pow(alpha*t,11.0)+52.0/13365.0*pow(alpha*t,12.0)-8.0/57915.0*pow(alpha*t,13.0)+8.0/2837835.0*pow(alpha*t,14.0)-16.0/638512875.0*pow(alpha*t,15.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-32*alpha*t+240*alpha^2*t^2-2240/3*alpha^3*t^3+3640/3*alpha^4*t^4-5824/5*alpha^5*t^5+32032/45*alpha^6*t^6-18304/63*alpha^7*t^7+572/7*alpha^8*t^8-9152/567*alpha^9*t^9+4576/2025*alpha^10*t^10-1664/7425*alpha^11*t^11+208/13365*alpha^12*t^12-128/173745*alpha^13*t^13+64/2837835*alpha^14*t^14-256/638512875*alpha^15*t^15+2/638512875*alpha^16*t^16)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 16 : return (1.0-32.0*alpha*t+240.0*pow(alpha*t,2.0)-2240.0/3.0*pow(alpha*t,3.0)+3640.0/3.0*pow(alpha*t,4.0)-5824.0/5.0*pow(alpha*t,5.0)+32032.0/45.0*pow(alpha*t,6.0)-18304.0/63.0*pow(alpha*t,7.0)+572.0/7.0*pow(alpha*t,8.0)-9152.0/567.0*pow(alpha*t,9.0)+4576.0/2025.0*pow(alpha*t,10.0)-1664.0/7425.0*pow(alpha*t,11.0)+208.0/13365.0*pow(alpha*t,12.0)-128.0/173745.0*pow(alpha*t,13.0)+64.0/2837835.0*pow(alpha*t,14.0)-256.0/638512875.0*pow(alpha*t,15.0)+2.0/638512875.0*pow(alpha*t,16.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-34*alpha*t+272*alpha^2*t^2-2720/3*alpha^3*t^3+4760/3*alpha^4*t^4-24752/15*alpha^5*t^5+49504/45*alpha^6*t^6-155584/315*alpha^7*t^7+9724/63*alpha^8*t^8-19448/567*alpha^9*t^9+77792/14175*alpha^10*t^10-14144/22275*alpha^11*t^11+3536/66825*alpha^12*t^12-544/173745*alpha^13*t^13+1088/8513505*alpha^14*t^14-2176/638512875*alpha^15*t^15+34/638512875*alpha^16*t^16-4/10854718875*alpha^17*t^17)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 17 : return (1.0-34.0*alpha*t+272.0*pow(alpha*t,2.0)-2720.0/3.0*pow(alpha*t,3.0)+4760.0/3.0*pow(alpha*t,4.0)-24752.0/15.0*pow(alpha*t,5.0)+49504.0/45.0*pow(alpha*t,6.0)-155584.0/315.0*pow(alpha*t,7.0)+9724.0/63.0*pow(alpha*t,8.0)-19448.0/567.0*pow(alpha*t,9.0)+77792.0/14175.0*pow(alpha*t,10.0)-14144.0/22275.0*pow(alpha*t,11.0)+3536.0/66825.0*pow(alpha*t,12.0)-544.0/173745.0*pow(alpha*t,13.0)+1088.0/8513505.0*pow(alpha*t,14.0)-2176.0/638512875.0*pow(alpha*t,15.0)+34.0/638512875.0*pow(alpha*t,16.0)-4.0/10854718875.0*pow(alpha*t,17.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-36*alpha*t+306*alpha^2*t^2-1088*alpha^3*t^3+2040*alpha^4*t^4-11424/5*alpha^5*t^5+24752/15*alpha^6*t^6-28288/35*alpha^7*t^7+9724/35*alpha^8*t^8-38896/567*alpha^9*t^9+19448/1575*alpha^10*t^10-28288/17325*alpha^11*t^11+3536/22275*alpha^12*t^12-1088/96525*alpha^13*t^13+544/945945*alpha^14*t^14-4352/212837625*alpha^15*t^15+34/70945875*alpha^16*t^16-8/1206079875*alpha^17*t^17+4/97692469875*alpha^18*t^18)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 18 : return (1.0-36.0*alpha*t+306.0*pow(alpha*t,2.0)-1088.0*pow(alpha*t,3.0)+2040.0*pow(alpha*t,4.0)-11424.0/5.0*pow(alpha*t,5.0)+24752.0/15.0*pow(alpha*t,6.0)-28288.0/35.0*pow(alpha*t,7.0)+9724.0/35.0*pow(alpha*t,8.0)-38896.0/567.0*pow(alpha*t,9.0)+19448.0/1575.0*pow(alpha*t,10.0)-28288.0/17325.0*pow(alpha*t,11.0)+3536.0/22275.0*pow(alpha*t,12.0)-1088.0/96525.0*pow(alpha*t,13.0)+544.0/945945.0*pow(alpha*t,14.0)-4352.0/212837625.0*pow(alpha*t,15.0)+34.0/70945875.0*pow(alpha*t,16.0)-8.0/1206079875.0*pow(alpha*t,17.0)+4.0/97692469875.0*pow(alpha*t,18.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-38*alpha*t+342*alpha^2*t^2-1292*alpha^3*t^3+2584*alpha^4*t^4-15504/5*alpha^5*t^5+36176/15*alpha^6*t^6-134368/105*alpha^7*t^7+16796/35*alpha^8*t^8-369512/2835*alpha^9*t^9+369512/14175*alpha^10*t^10-67184/17325*alpha^11*t^11+67184/155925*alpha^12*t^12-10336/289575*alpha^13*t^13+10336/4729725*alpha^14*t^14-20672/212837625*alpha^15*t^15+646/212837625*alpha^16*t^16-76/1206079875*alpha^17*t^17+76/97692469875*alpha^18*t^18-8/1856156927625*alpha^19*t^19)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 19 : return (1.0-38.0*alpha*t+342.0*pow(alpha*t,2.0)-1292.0*pow(alpha*t,3.0)+2584.0*pow(alpha*t,4.0)-15504.0/5.0*pow(alpha*t,5.0)+36176.0/15.0*pow(alpha*t,6.0)-134368.0/105.0*pow(alpha*t,7.0)+16796.0/35.0*pow(alpha*t,8.0)-369512.0/2835.0*pow(alpha*t,9.0)+369512.0/14175.0*pow(alpha*t,10.0)-67184.0/17325.0*pow(alpha*t,11.0)+67184.0/155925.0*pow(alpha*t,12.0)-10336.0/289575.0*pow(alpha*t,13.0)+10336.0/4729725.0*pow(alpha*t,14.0)-20672.0/212837625.0*pow(alpha*t,15.0)+646.0/212837625.0*pow(alpha*t,16.0)-76.0/1206079875.0*pow(alpha*t,17.0)+76.0/97692469875.0*pow(alpha*t,18.0)-8.0/1856156927625.0*pow(alpha*t,19.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	// (1-40*alpha*t+380*alpha^2*t^2-1520*alpha^3*t^3+3230*alpha^4*t^4-20672/5*alpha^5*t^5+10336/3*alpha^6*t^6-41344/21*alpha^7*t^7+16796/21*alpha^8*t^8-134368/567*alpha^9*t^9+739024/14175*alpha^10*t^10-268736/31185*alpha^11*t^11+33592/31185*alpha^12*t^12-41344/405405*alpha^13*t^13+20672/2837835*alpha^14*t^14-82688/212837625*alpha^15*t^15+646/42567525*alpha^16*t^16-304/723647925*alpha^17*t^17+152/19538493975*alpha^18*t^18-32/371231385525*alpha^19*t^19+4/9280784638125*alpha^20*t^20)*2^(1/2)*alpha^(1/2)*exp(-(alpha+beta)*t)
	case 20 : return (1.0-40.0*alpha*t+380.0*pow(alpha*t,2.0)-1520.0*pow(alpha*t,3.0)+3230.0*pow(alpha*t,4.0)-20672.0/5.0*pow(alpha*t,5.0)+10336.0/3.0*pow(alpha*t,6.0)-41344.0/21.0*pow(alpha*t,7.0)+16796.0/21.0*pow(alpha*t,8.0)-134368.0/567.0*pow(alpha*t,9.0)+739024.0/14175.0*pow(alpha*t,10.0)-268736.0/31185.0*pow(alpha*t,11.0)+33592.0/31185.0*pow(alpha*t,12.0)-41344.0/405405.0*pow(alpha*t,13.0)+20672.0/2837835.0*pow(alpha*t,14.0)-82688.0/212837625.0*pow(alpha*t,15.0)+646.0/42567525.0*pow(alpha*t,16.0)-304.0/723647925.0*pow(alpha*t,17.0)+152.0/19538493975.0*pow(alpha*t,18.0)-32.0/371231385525.0*pow(alpha*t,19.0)+4.0/9280784638125.0*pow(alpha*t,20.0))*sqrt(2.0*alpha)*exp(-(alpha+beta)*t); break;

	}
	fprintf(stderr, "Error using LagerPolynom() :  order is too large\n");
	return vdouble(0);
}
//*/
double vdouble::LagerAlphaDeterminition(double& tend, double& EnergyPart)
{
	vdouble vInt, poly, vInt_tend, c, vderiv;
	int vIntLen, i, j,  N, result;
	double m, f, alpha;
	// Полиномиальные коэффициенты произведения полинома Лаггера самого на себя
	poly = conv(*this,*this);
	// интегрирование выражения 
	// poly.PolynomValues(alpha * t) * exp(-2 * alpha * t) * 2 * alpha;
	// по переменной t
	// в пределах от 0 до tend даёт значение EnergyPart
	vInt = poly;
	vIntLen = vInt.Length();
	for (i = 0; i < vIntLen; i++)
	{
		vInt[i] /= -1; //коэффициент перед переменной интегрирования в экспоненте
		if (i < vIntLen - 1)
			vInt[i + 1] -= vInt[i] * (vIntLen - i - 1) / 2;
	}
	// Теперь мы имеем трансцендентное уравнение
	// EnergyPart = vInt.PolynomValue(alpha * tend) * exp( - 2 * alpha * tend) - vInt.PolynomValue(0);
	// которое надо решить относительно alpha

/*	
vdouble vEnergyPart = vInt.PolynomValues(alpha * vtend) * exp( - 2 * alpha * vtend) - vInt.PolynomValue(0);
fprintf(stderr,"\nvEnergyPart = ");vEnergyPart.disp();
	
EnergyPart = vInt.PolynomValue(alpha * tend) * exp( - 2 * alpha * tend) - vInt.PolynomValue(0);
fprintf(stderr,"\nEnergyPart = %g", EnergyPart);
//*/	
	// сперва внесём tend в коэффициенты полинома vInt
	vInt_tend = vInt;
	m = 1.0;
	for (i = vIntLen - 1; i >= 0 ; i--)
	{
		vInt_tend[i] *= m ;//pow(tend, vIntLen -1-i);
		m *=tend;
	}
/*/
double dalpha = 0.2;
int Len = 20 / dalpha + 1;
vdouble	valpha = vdouble(Len);
	for(i=0; i<Len; i++)
		valpha[i] = i*dalpha;

fprintf(stderr, "valpha = ");valpha.disp();
fprintf(stderr, "vInt_tend = ");vInt_tend.disp();
fprintf(stderr, "vInt = ");vInt.disp();
//*/
	// имеем трансцендентное уравнение
	// vInt_tend.PolynomValue(alpha) * exp( - 2 * valpha * tend) - (vInt.PolynomValue(0) + EnergyPart) = 0.0;
	// которое решаем путём разложения левой части в степенной ряд по alpha

	// разлагаем левую часть в степенной ряд
	N = 100; // степень полинома разложения экспоненты
	c = vdouble(N);
	m = 1.0; // Коэффициент перед экспонентой
	f = 1.0;
	j = 0; //порядок производной
	double alpha0 = 0;
	// Значение ф-ции в alpha0
	c[N - 1] = vInt_tend.PolynomValue(alpha0) * exp( - 2 * alpha0 * tend) - (vInt.PolynomValue(0) + EnergyPart);
	j++;
	f *= (double)j;

	// Значение первой производной в alpha0
	vderiv = (- 2 * tend * vInt_tend).PolynomSumming(vInt_tend.PolynomDerivative());
	c[N - 2] = vderiv.PolynomValue(alpha0) * exp( - 2 * alpha0 * tend);
	j++;
	f *= (double)j;

	// Значения второй и следующих производных в alpha0
	for (i = N - 3; i >= 0 ; i--)
	{
		vderiv = (- 2 * tend * vderiv).PolynomSumming(vderiv.PolynomDerivative());
		c[i] = vderiv.PolynomValue(alpha0) * exp( - 2 * alpha0 * tend) / f;// Коэффициент интерполирующего полинома
		j++;
		f *= (double)j;// Факториал
		}
//fprintf(stderr, "c = ");
//c.disp();
/*
fprintf(stderr, "EnergyPart = ");
(vInt_tend.PolynomValues(valpha) * exp(-valpha *2*tend) - vInt.PolynomValue(0)).disp();		

fprintf(stderr, "Difference = ");
(c.PolynomSubsVariable(alpha0).PolynomValues(valpha) - (vInt_tend.PolynomValues(valpha) * exp(-2*tend*valpha) - vInt.PolynomValue(0) - EnergyPart)).disp();
//*/
	vdouble dr = vdouble(0);
	result = c.BernulliMinRealRoot(dr);
	if (result == 0)
	{
		alpha = dr[0];
		EnergyPart = vInt_tend.PolynomValue(alpha) * exp(-alpha *2*tend) - vInt.PolynomValue(0);		
//		fprintf(stderr, " alpha = %g\tEnergyPart = %g\n\n", alpha,EnergyPart);
	}
	else
	{
		alpha = 0.00000000001;
//		fprintf(stderr, " alpha = \tEnergyPart = \n\n");
	}
	vdouble v = vdouble(1);
	v[0] = - vInt.PolynomValue(0) - EnergyPart;
	vInt_tend.TranscendentNewtonRoot(alpha,- 2*tend, v);
		EnergyPart = vInt_tend.PolynomValue(alpha) * exp(-alpha *2*tend) - vInt.PolynomValue(0);		
//		fprintf(stderr, " alpha after Newton = %g\tEnergyPart = %g\n\n", alpha,EnergyPart);
	return alpha;
}
vdouble vdouble::LagerQuotients(int i0, vdouble& t, LagerStruct& lgstr, int flag_of_Inf, Vector<vdouble>& koefs, char * sNumDen, char * sRoots) // Вычисление коэффициентов Лагерра
{
	int i, q;
	char s[1024];
	if (m_length != t.m_length)
	{
		//fprintf(stderr, "Error using LagerQuotients() : lengthes of vectors must be equial\n");
		return vdouble(0);
	}
	double Q,
		t0,
		alpha,
		beta,
		epsilon,
		*pf,
		*pt, *ptau, ti,
		temp1, temp2,
		*pdt, *pdt_1,
		*plager0, *plager1, *plager2, *pl_, lni, *pl0, *pl1, *pl2,
		*vpl[3], // Массив трёх указателей
		an, bn, cn, dn,
		d, // Дискриминант //Максимально допустимые:
		goal_Error = 10.0, // среднеквадратичная ошибка реконструкции
		goal_Max_diff = 10.0; //максимальная ошибка реконструкции
	bool GoodRekonstr;
	
	int order,
		len,
		n,
		len_1;
		
	vdouble vQ = vdouble(0);

	t0 = t[i0];
	pt = t.pD + i0;
	pf = pD + i0;
	alpha = lgstr.alpha;
	beta = lgstr.beta;
	epsilon = lgstr.epsilon;
	int maxOrder = lgstr.maxOrder;


	len = m_length - i0;
	len_1 = len - 1;

	if ((pdt = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len_1*SD)) == NULL){MEMORY_ERROR}
	if ((plager0 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*SD)) == NULL){MEMORY_ERROR}
	if ((plager1 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*SD)) == NULL){MEMORY_ERROR}
	if ((plager2 = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*SD)) == NULL){MEMORY_ERROR}
	if ((ptau = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,len*SD)) == NULL){MEMORY_ERROR}

	//   Вычисление коэффициентов интегрированием
	for (i = 0; i< len; i++)
		*(ptau + i) = *(pt + i) - t0;

	for (i = 0; i< len_1; i++)
	{	*(pdt + i) = *(pt + 1) - *(pt); pt++;}
	pdt_1 = pdt - 1;

	vpl[0] = plager0; vpl[1] = plager1; vpl[2] = plager2;
	pl0 = plager0; pl1 = plager1; pl2 = plager2;


	Vector<vdouble> vLag(3);
	vdouble vrek(2);
	double tend = t.End() - t0;
	vdouble vInt, v;
	int vIntLen;
	double mean = 0.0;
	switch (flag_of_Inf)
	{
	case 0:
		mean = 0.0;break;
	case 1:
		v = (*this)[sequence(i0, m_length - 1)];
		mean = v.Mean();break;
	case 2:
		mean = this->End();break;
	}

//WriteRaporto("LagerQuotients 3\n");

	for (q = 0; q < 3; q++)
	{
		Q = 0.0; 
		pl_ = vpl[q];
		ti = *ptau;
		lni = LagerPolynom(q,alpha,beta,ti);
		temp1 = *pf * lni * exp((beta - alpha) * ti);
		*pl_ = lni;


		for(i = 1; i < len; i++)
		{
			ti = *(ptau + i);
			lni = LagerPolynom(q,alpha,beta,ti); // полином без экспоненты exp(-(alpha+beta)*t) и без нормирующего множителя sqrt(2.0*alpha)
			temp2 = *(pf + i) * lni * exp((beta - alpha) * ti); //  произведение сигнала на полином и на объединённые экспоненту и вес 
			*(pl_ + i) = lni;
			Q += (temp1 + temp2) * ( *(pdt_1 + i) );// интегрирование методом трапеций
			temp1 = temp2;
		}
		Q *= sqrt(alpha / 2.0); // умножение коэффициента на нормирующий множитель sqrt(2.0*alpha) и деление на 2

		// полиномиальные коэффициенты полинома Лагерра
		vLag[q] = vLagerPolynom(q);
		// вычисление поправки интегрирования от tend до бесконечности
		
		// Вектор Полинома интеграла
		vInt = vLag[q];
		vIntLen = vInt.m_length;
		// вычисление полинома интеграла
		for ( i = 0; i < vIntLen; i++)
		{
			
			vInt[i] /= beta - alpha; // коэффициент перед переменной интегрирования в экспоненте
			if (i + 1 < vIntLen)
				vInt[i + 1] -= vInt[i] * (vIntLen - i - 1);
		}
		Q += - mean * vInt.PolynomValue(alpha * tend) * exp((beta - alpha) * tend) * sqrt(2 * alpha);

		vQ.push_back(Q);
	}
//WriteRaporto("LagerQuotients 4\n");

	n = 2;
	order = 1;

	//===========================================================
	vdouble alphai,flip_betai, num, den;
	d = vQ.LagerDeterminant(alpha,beta,alphai,flip_betai,num,den);
	lgstr.fund_det = d;
//WriteRaporto("LagerQuotients 5\n");

	//=============================================================
	// Реконструкция сигнала путём обратного преобразования Лапласа
	vdouble f_rek;
	InvLaplace(num, den, t, f_rek, koefs, sRoots);

//WriteRaporto("LagerQuotients 6\n");

	// Вычисление среднеквадратичной ошибки реконструкции
	vdouble diffrence = *this - f_rek;
	double Error_rek, Max_diff;
	Error_rek = sqrt(diffrence.SquareSum() / m_length);
	Max_diff = diffrence.MaxAbs();
	GoodRekonstr = Error_rek <= goal_Error && Max_diff <= goal_Max_diff;
//WriteRaporto("LagerQuotients 7\n");
	if(GoodRekonstr || d <= epsilon)
	{
		vdouble num1, num0, den1, den0;
		num0 = num / den.End();
		den0 = den / den.End();
		num1 = num / den.End(-1);
		den1 = den / den.End(-1);

		sprintf(sNumDen, "");

		sprintf(s, "Numerator = \n");
		strcat(sNumDen, s);
		for (i = 0; i < num0.m_length; i ++)
		{
			sprintf(s, "    %lf", num0[i]);
			strcat(sNumDen, s);
		}

		sprintf(s, "\nDenominator = \n");
		strcat(sNumDen, s);
		for (i = 0; i < den0.m_length; i ++)
		{
			sprintf(s, "    %lf", den0[i]);
			strcat(sNumDen, s);
		}

		sprintf(s, "\nor Numerator = \n");
		strcat(sNumDen, s);
		for ( i = 0; i < num1.m_length; i ++)
		{
			sprintf(s, "    %lf", num1[i]);
			strcat(sNumDen, s);
		}

		sprintf(s, "\nDenominator = \n");
		strcat(sNumDen, s);
		for ( i = 0; i < den1.m_length; i ++)
		{
			sprintf(s, "    %lf", den1[i]);
			strcat(sNumDen, s);
		}
	}
	else
	{
//		fprintf(stderr,"alhai = "); alhai.disp();
//		fprintf(stderr,"flip_betai = "); flip_betai.disp();
//		fprintf(stderr,"Num = "); num.disp();
//		fprintf(stderr,"Den = "); den.disp();
//		fprintf(stderr, "\nSqu error of rek = %g, Max of diff = %g\n", Error_rek, Max_diff);
	}
	//=============================================================
//WriteRaporto("LagerQuotients 8\n");

	while (d > epsilon /*&& !GoodRekonstr*/ && order < maxOrder)
	{
//WriteRaporto("LagerQuotients 9\n");
		order++;
		for (q = 0; q < 2; q++)
		{
//WriteRaporto("LagerQuotients 10\n");
			n++;
			pl_ = pl0; pl0 = pl1; pl1 = pl2; pl2 = pl_;
			dn = (double)n;
			bn = ((double)(2*n-1)) / dn;
			an = -2.0 * alpha / dn;
			cn = ((double)(n-1)) / dn;
			vrek[0] = -2.0 / dn;; vrek[1] = bn;
			Q = 0.0;
			ti = *ptau;
			lni = (an * ti + bn) * (*pl1) - cn * (*pl0);// рекурентное вычисление значения полинома в точке ti
			temp1 = *pf * lni * exp((beta - alpha) * ti);
			*pl2 = lni;
//WriteRaporto("LagerQuotients 11\n");
			for (i = 1; i < len; i++)
			{
//WriteRaporto("LagerQuotients 12\n");
				ti = *(ptau + i);
				lni = (an * ti + bn) * (*(pl1 + i)) - cn * (*(pl0 + i));
				temp2 = *(pf + i) * lni * exp((beta - alpha) * ti);
				*(pl2 + i) = lni;
				Q += (temp1 + temp2) * ( *(pdt_1 + i) );
				temp1 = temp2;
				
			}
//WriteRaporto("LagerQuotients 13\n");
			Q *= sqrt(alpha / 2.0); vQ.push_back(Q);
			// рекурентное вычисление полиномиальных коэффициентов полинома Лагерра
			vLag[0] = vLag[1]; vLag[1] = vLag[2];
//WriteRaporto("LagerQuotients 14\n");
			vLag[2] = conv(vLag[1], vrek).PolynomSumming( - cn * vLag[0]);
//WriteRaporto("LagerQuotients 15\n");
//fprintf(stderr, "Polynmial quotients of %i order of LagerPolynom is = ", order * 2 + q - 1);
//vLag[2].disp();
			// вычисление поправки интегрирования от tend до бесконечности
			vInt = vLag[2];
			vIntLen = vInt.m_length;
			// вычисление полинома интеграла
			for ( i = 0; i < vIntLen; i++)
			{
				
				vInt[i] /= beta - alpha; // коэффициент перед переменной интегрирования в экспоненте
				if (i + 1 < vIntLen)
					vInt[i + 1] -= vInt[i] * (vIntLen - i - 1);
			}
			Q += - mean * vInt.PolynomValue(alpha * tend) * exp((beta - alpha) * tend) * sqrt(2 * alpha);
//WriteRaporto("LagerQuotients 16\n");
		}
	//		d = vQ.LagerDeterminant();
		//===========================================================
//WriteRaporto("LagerQuotients 17\n");
		vdouble alhai,flip_betai, num, den;
		d = vQ.LagerDeterminant(alpha,beta,alphai,flip_betai,num,den);
		lgstr.fund_det = d;
//WriteRaporto("LagerQuotients 18\n");

		lgstr.num = num;
		lgstr.den = den;
		lgstr.vQ = vQ;
		lgstr.alphai = alphai;
		lgstr.flip_betai = flip_betai;
//WriteRaporto("LagerQuotients 19\n");

		//=============================================================
		// Реконструкция сигнала путём обратного преобразования Лапласа
		vdouble f_rek;
		InvLaplace(num, den, t, f_rek, koefs, sRoots);
//WriteRaporto("LagerQuotients 20\n");
		// Вычисление среднеквадратичной ошибки реконструкции
		vdouble diffrence = *this - f_rek;
		double Error_rek, Max_diff;
		Error_rek = sqrt(diffrence.SquareSum() / m_length);
		Max_diff = diffrence.MaxAbs();
		GoodRekonstr = Error_rek <= goal_Error && Max_diff <= goal_Max_diff;
		if(GoodRekonstr || d <= epsilon)
		{
			vdouble num1, num0, den1, den0;
			num0 = num / den.End();
			den0 = den / den.End();
			num1 = num / den.End(-1);
			den1 = den / den.End(-1);

			sprintf(sNumDen, "");

			sprintf(s, "Numerator = \n");
			strcat(sNumDen, s);
			for (i = 0; i < num0.m_length; i ++)
			{
				sprintf(s, "    %lf", num0[i]);
				strcat(sNumDen, s);
			}

			sprintf(s, "\nDenominator = \n");
			strcat(sNumDen, s);
			for ( i = 0; i < den0.m_length; i ++)
			{
				sprintf(s, "    %lf", den0[i]);
				strcat(sNumDen, s);
			}

			sprintf(s, "\nor Numerator = \n");
			strcat(sNumDen, s);
			for ( i = 0; i < num1.m_length; i ++)
			{
				sprintf(s, "    %lf", num1[i]);
				strcat(sNumDen, s);
			}

			sprintf(s, "\nDenominator = \n");
			strcat(sNumDen, s);
			for ( i = 0; i < den1.m_length; i ++)
			{
				sprintf(s, "    %lf", den1[i]);
				strcat(sNumDen, s);
			}
		}
		else
		{
	//		fprintf(stderr,"alhai = "); alhai.disp();
	//		fprintf(stderr,"flip_betai = "); flip_betai.disp();
	//		fprintf(stderr,"Num = "); num.disp();
	//		fprintf(stderr,"Den = "); den.disp();
	//		fprintf(stderr, "\nSqu error of rek = %g, Max of diff = %g\n", Error_rek, Max_diff);
		}
	//=============================================================
	}
	HeapFree(GetProcessHeap(), 0,pdt);
	HeapFree(GetProcessHeap(), 0,ptau);
	HeapFree(GetProcessHeap(), 0,plager0);
	HeapFree(GetProcessHeap(), 0,plager1);
	HeapFree(GetProcessHeap(), 0,plager2);


//WriteRaporto("LagerQuotients end\n");

	return vQ;
}

double vdouble::LagerDeterminant()
{
	if (m_length%2 != 1)
	{ fprintf(stderr, "Error using vdouble::LagerDeterminant() :\n  lenght of vector must be odd\n");
		return 1.0e300;
	}
	double *p, *prC, *pDr;
	int C = 1 + m_length/2;
	vdouble FundamentalMatrix = vdouble(C*C);
	p = FundamentalMatrix.pD;
	for (int r = 0; r < C; r++)
	{
		prC = p + r*C;
		pDr = pD + r;
		for (int i = 0; i < C; i++)
			*(prC+i) = *(pDr + i);
	}
	double d = FundamentalMatrix.det();
	double fundamental = fabs(d/pow(MaxAbs(), (double)(C-1)));
/*	double d_old = FundamentalMatrix.det_old();
	fprintf(stderr,  "det = " << d << "  ";
	fprintf(stderr,  "det old= " << d_old << "  ";
	fprintf(stderr,  "fund = " << fundamental << endl;
*/
	return fundamental;
}
double vdouble::LagerDeterminant(double alpha, double beta, vdouble& alphai, vdouble& flip_betai, vdouble& num, vdouble& den)
{
	if (m_length%2 != 1)
	{ fprintf(stderr, "Error using vdouble::LagerDeterminant() :\n  lenght of vector must be odd\n");
		return 1.0e300;
	}
	double *p, *prC, *pDr, *pai, *pfbi, *pai_, *pfbi_, alpha2, _det;
	int C, C_1, i, j, r, c;
	C = 1 + m_length/2; C_1 = C - 1;
	vdouble FundamentalMatrix = vdouble(C,C);
	p = FundamentalMatrix.pD;
	
	for (r = 0; r < C; r++)
	{
		prC = p + r*C;
		pDr = pD + r;
		for (c = 0; c < C; c++)
			*(prC+c) = *(pDr + c);
	}


	vdouble zerC = zeros(C);
	/////////////////////////////////
	/*
	double *pM, *pb, *pMrC;
	vdouble M = vdouble(C,C_1), b = vdouble(C);
	pM = M.pD;
	for (r = 0; r < C; r++)
	{
		pMrC = pM + r*C_1;
		pDr = pD + r;
		for (c = 0; c < C_1; c++)
			*(pMrC+c) = *(pDr + c);
	}
	pb= b.pD;
	int i0 = m_length - C;
	for (r = 0; r < C; r++)
		*(pb + r) = - *(pD + r + i0);
	// */
	//////////////////////////////////////
	




	
	


	//////////////////////////////////
	FundamentalMatrix.sls_det(zerC, flip_betai, _det, true);	
//	AfxMessageBox("Lager det: flip_betai = " + flip_betai.disp_str());

//	flip_betai = (M.Tichonov(b), 1.0);


	double fundamental = fabs(_det/pow(MaxAbs(), (double)(C-1)));

	alphai = vdouble(C_1);
	pai = alphai.pD;
	pfbi = flip_betai.pD;
	alpha2 = sqrt(2.0 * alpha);
	for (i = 0; i < C_1; i++)
	{
		pai_ = pai + i;
		pfbi_ = pfbi + C_1 - i; 
		*pai_ = 0.0;
		for (j = 0; j <= i; j++)
		{
			*pai_ += *(pfbi_ + j) * *(pD + j);
		}
		*pai_ *= alpha2;
	}

	vdouble poly;
	den = zeros(C);
	num = zeros(C_1);

	vdouble Sa = vdouble(2); 
	vdouble S_b = vdouble(2); 

	Sa[0] = 1.0; Sa[1] = alpha + beta;
	S_b[0] = 1.0; S_b[1] = beta - alpha;


	for ( i = 0; i < C_1; i++)
	{
		poly = *(pai + i);
		for( j = 0; j < i; j++)
			poly = conv(poly,S_b);
		for( j = i+1; j < C_1; j++)
			poly = conv(poly,Sa);
		num += poly;
	}

	for ( i = 0; i < C; i++)
	{
		poly = *(pfbi + i);
		for( j = 0; j < i; j++)
			poly = conv(poly,Sa);
		for( j = i+1; j < C; j++)
			poly = conv(poly,S_b);
		den += poly;
	}
/*
	double den_end = den[den.Length() -2];

	den /= den_end;
	num /= den_end;
*/


	return fundamental;

}
int vdouble::InvLaplace(vdouble& num, vdouble& den, vdouble&t, vdouble& f_rekonstr, Vector<vdouble>& koefs, char * sRoots)
{
//WriteRaporto("InvLaplace 1\n");
	char s[1024];
	sprintf(sRoots,"\nRoots of denominator:\n");
//WriteRaporto("InvLaplace 1_\n");
	koefs.resize(0);
//WriteRaporto("InvLaplace 1 2\n");
//	koefs = Vector<vdouble>(0);
	int result = 0, res, i;
	double xD_, yD_, mD_, xN, yN, xk, yk, x, y;
//WriteRaporto("InvLaplace 1 3\n");
	vdouble droots_den, deriv_den; // Действительные корни знаменателя и производная его
//WriteRaporto("InvLaplace 1 4\n");
	Vector<complex> croots_den; //Комплексные корни знаменателя
//WriteRaporto("InvLaplace 1 5\n");
	deriv_den = den.PolynomDerivative(); //производная знаменателя
//WriteRaporto("InvLaplace 1 6\n");
	f_rekonstr = zeros(t.m_length); // реконструируемый сигнал
	// ============== Roots of denominator ==========================
	Vector<int> order_dr, order_cr;
//WriteRaporto("InvLaplace 2\n");
	res = den.roots(droots_den, croots_den,order_dr, order_cr);

//WriteRaporto("InvLaplace 3\n");

	droots_den.disp();


	if (res < 0) 
	{
		return -1;
	}
	if (res > 0) 
	{
		return 1;
	}
	if (Find(order_dr > 1).size > 0)
		return 2;
	if (Find(order_cr > 1).size > 0)
		return 3;
	// ============================================================
	if (croots_den.size > 0)
	{
		sprintf(s, "Complex roots(%i):\n", croots_den.size);
		strcat(sRoots, s);
	}
//суммируем оригиналы от комплексных корней
	for (i = 0; i < croots_den.size; i++)
	{
		complex N, D_, z; // комплексное значение числителя и производной знаменателя
		// комплексный корень
		x = croots_den[i].x;
		y = croots_den[i].y;
		z.x = x;
		z.y = y;
		// Вычисление коэффициента перед экспонентой
		N = num.PolynomValue(z);// Значение числителя в корне
		D_ = deriv_den.PolynomValue(z);// Значение производной знаменателя в корне
		// Деление значения числителя на значение производной знаменателя
		xD_ = D_.x; yD_ = D_.y;
		mD_ = xD_ * xD_ + yD_ * yD_;
		xN = N.x;
		yN = N.y;

		xk = (xN * xD_ + yN * yD_) / mD_;
		yk = (xD_ * yN - xN * yD_) / mD_;

		// ================= exp ============

		// ex = exp (x * t);
		// xe = ex * cos( y * t);
		// ye = ex * sin( y * t);
		// xf = xk * xe - yk * ye;
		f_rekonstr += 2.0 * (xk * cos(y * t) - yk * sin(y * t)) * exp(x * t);
		
		sprintf(s,  "N = %i:  %g  + i * %g   \t   abs = %g  \torder = %i\n",i , x, y, sqrt( x * x + y * y), order_cr[i]);
		strcat(sRoots, s);
		
		vdouble koef = vdouble(4);
		koef[0] = xk*2.0;
		koef[1] = - yk*2.0;
		koef[2] = x;
		koef[3] = y;
		koefs.push_back(koef);




	}
	if (droots_den.m_length > 0)
	{
		sprintf(s, "Real roots(%i):\n", droots_den.m_length);
		strcat(sRoots, s);
	}
	//суммируем оригиналы от действительных корней
	for (i = 0; i < droots_den.m_length; i++)
	{
		double N, D_; // действительное значение числителя и производной знаменателя
		// комплексный корень
		x = droots_den[i];
		// Вычисление коэффициента перед экспонентой
		N = num.PolynomValue(x);// Значение числителя в корне
		D_ = deriv_den.PolynomValue(x);// Значение производной знаменателя в корне
		// Деление значения числителя на значение производной знаменателя
		xk = N / D_;
		// ================= exp ============
		f_rekonstr += xk * exp(x * t);
		//fprintf(stderr, "InvLaplase += %g * exp(%g * t)\n", xk , x);
		sprintf(s, "N = %i:  %g\t\tabs = %g  \torder = %i\n",i , x, fabs(x), order_dr[i]);
		strcat(sRoots, s);

		vdouble koef = vdouble(2);
		koef[0] = xk;
		koef[1] = x;
		koefs.push_back(koef);
	}

//WriteRaporto("InvLaplace end\n");

	return result;
}



//============ Функции Линейной алгебры ============
vdouble vdouble::MatrixProduct(vdouble& x)
{
	if (this->m_dims != 2)
	{
		TCHAR str[512];
		stprintf_s(str, 512, _T("Error using double::MatrixProduct(vdouble& x) (m_dims(%d) != 2)"), this->m_dims);
		MessageBox(0, str,_T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return vdouble();
	}
	if (m_size[1] != x.m_length)
	{
		TCHAR str[512];
		stprintf_s(str, 512, _T("Error using double::MatrixProduct(vdouble& x)\n Size of vector muct be equial to matrix\nm_size[1]=%d x.m_length=%d"), m_size[1], x.m_length);
		MessageBox(0, str,
			_T("Error"), MB_OK | MB_ICONEXCLAMATION);
		return vdouble();
	}
	int rows = m_size[0],
		cols = m_size[1];
	vdouble y = zeros(rows);
	double *p, *py, *ypD;
	ypD = y.pD;
	for (int r = 0; r < rows; r++)
	{
		py = ypD + r;
		p = pD + r * cols; 
		for (int c = 0; c < cols; c++)
		{
			*py += *(p + c) * x[c];
//			*py += *(pD + r + c * rows) * x[c];
//			*py += *(pD + c + r * cols) * x[c];
		}
	}
	return y;
}


vdouble vdouble::MatrixWithMatrixProduct(vdouble& M)
// Матричное произведение матрицы размера R1 x C1 на матрицу размера R2 x C2 причём C1 = R2
{
	if (m_dims != 2)
	{
/*		AfxMessageBox("Error using double::MatrixWithMatrixProduct(vdouble& x) (m_dims != 2)");
		AfxThrowUserException();*/
		return vdouble();
	}
	if (M.m_dims != 2)
	{
/*		AfxMessageBox("Error using double::MatrixWithMatrixProduct(vdouble& x) (M.m_dims != 2)");
		AfxThrowUserException();*/
		return vdouble();
	}
	if (m_size[1] != M.m_size[0])
	{
/*		AfxMessageBox("Error using double::MatrixWithMatrixProduct(vdouble& x)\n (m_size[1] != M.m_size[0])");
		AfxThrowUserException();*/
		return vdouble();
	}
	int rows1 = m_size[0],
		cols1 = m_size[1],
		cols2 = M.m_size[1];
	vdouble y;
	y.resize(rows1,cols2,0.0);
	double *p, *py, *ypD, *pM;
	ypD = y.pD;
	pM = M.pD;
	for (int r1 = 0; r1 < rows1; r1++)
	{
		py = ypD + r1 * cols2;
		p = pD + r1 * cols1; 
		for (int c2 = 0; c2 < cols2; c2++)
		{
			for (int c1 = 0; c1 < cols1; c1++)
				*py += *(p + c1) * *(pM + c1 * cols2 + c2);
//				*py += *(p + c1) * M(c1, c2);
			py++;
		}
	}
	return y;
}


vdouble vdouble::TransponedMatrixProduct(vdouble& x)
{
	if (m_dims != 2)
	{
/*		AfxMessageBox("Error using double::TransponedMatrixProduct(vdouble& x) (m_dims != 2)");
		AfxThrowUserException();*/
		return vdouble();
	}
	if (m_size[0] != x.m_length)
	{
/*		AfxMessageBox("Error using double::TransponedMatrixProduct(vdouble& x)\n Size of vector muct be equial to matrix");
		AfxThrowUserException();*/
		return vdouble();
	}
	int rows = m_size[0],
		cols = m_size[1];
	vdouble y = zeros(cols);
	double *p, *py, *ypD;
	ypD = y.pD;
	for (int c = 0; c < cols; c++)
	{
		py = ypD + c;
		p = pD + c;
		for (int r = 0; r < rows; r++)
		{
			*py += *(p + r * cols) * x[r];
//			*py += *(pD + c + r * cols) * x[r];

//			*py += *(pD + r + c * rows) * x[r];
		}
	}
	return y;
}
vdouble vdouble::VectorsToMatrixProduct(vdouble& gor)
{
	int rows = m_length, 
		cols = gor.m_length;
	vdouble m = vdouble(rows,cols);
	double *pm, *pvert, *pgor;
	pm = m.pD;
	pvert = pD;
	pgor = gor.pD;
	for (int r = 0; r < rows; r++)
	{
		for (int c = 0; c < cols; c++)
			*(pm + c + r * cols) = *(pvert + r) * *(pgor + c);
	}
	return m;
}
vdouble vdouble::TichonovOld(vdouble& b)
{
	if (m_dims != 2)
	{
/*		AfxMessageBox("Error using double::Tichonov(vdouble& b) (m_dims != 2)");
		AfxThrowUserException();*/
		return vdouble();
	}
	if (m_size[0] < 1 || m_size[1] < 1)
	{
/*		AfxMessageBox("Error using double::Tichonov(vdouble& b)\n Size < 1");
		AfxThrowUserException();*/
		return vdouble();
	}
	if (m_size[0] != b.m_length)
	{
/*		CString str;
		str.Format("Size of vector %i must be equial to size of matrix = %i %i", b.m_length,m_size[0],m_size[1]);
		AfxMessageBox("Error using double::Tichonov(vdouble& b)\n " + str);
		AfxThrowUserException();*/
		return vdouble();
	}
	int 
		i, r, c,
		rows = m_size[0],
		cols = m_size[1];// число итераций на которые действует отмена настройки
	vdouble x, E = vdouble(rows), d2Fdx2 = vdouble(cols);
	double delta, 
		alpha, 
		abs_grad, 
		abs2grad, 
		dFdx, 
		epsilon = 1.0e-12,
		*pE, *pb, *px, *pb0, *pM, *p2;
	pb = b.pD;
	pE = E.pD;
	if (rows >= cols)
	{

		vdouble M = vdouble(cols, cols);
		vdouble b0 = vdouble(cols);
		pb0 = b0.pD;
		pM = M.pD;
		int len = cols * cols;

		for (i = 0; i < len; i++)
			*(pM + i) = *(pD + i);

		for (i = 0; i < cols; i++)
			*(pb0 + i) = *(pb + i);

		double det;
		//
		M.sls_det(b0,x,det);
		px = x.pD;
		//return x;
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			int rcols = r * cols;
			*(pE + r) = - *(pb + r);
			for (c = 0; c < cols; c++)
				*(pE + r) += *(px + c) * *(pD + c + rcols);
		}
		// Приближение
		delta = sqrt(E.SquareSum());
	}
	else
	{
		x = ones(cols);
		px = x.pD;
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			int rcols = r * cols;
			*(pE + r) = - *(pb + r);
			for (c = 0; c < cols; c++)
				*(pE + r) += *(px + c) * *(pD + c + rcols);
		}
		// Приближение
		delta = sqrt(E.SquareSum());
		// Регуляризационный коэффициент
		alpha = delta;
	}
	// Регуляризационный коэффициент
	alpha = 0.0;
	p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		*(p2 + c) = alpha;
		for (r = 0; r < rows; r++)
		{
			i = c + r * cols;
//			i = r + c * rows;
			*(p2 + c) += *(pD + i) * *(pD + i);
		}
		*(p2 + c) *= 2.0;
	}
	//Цикл подстройки


	int q = 0;
	do
	{
		q++;
		abs2grad = 0;
		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			// Вычисляем первую производную
			dFdx = alpha * *(px + c);
			for (r = 0; r < rows; r++)
			{
				i = c + r * cols;
//				i = r + c * rows;
				dFdx += *(pE + r) * *(pD + i);
			}
			dFdx *= 2.0;
			abs2grad += dFdx * dFdx;


			//Подстраиваем элемент вектора x
			*(px + c) -= 0.9 * dFdx / *(p2 + c);
			// Вектор невязки
			for (r = 0; r < rows; r++)
			{
				int rcols = r * cols;
				*(pE + r) = - *(pb + r);
				for (int C = 0; C < cols; C++)
					*(pE + r) += *(px + C) * *(pD + C + rcols);
			}
		}
		abs_grad = sqrt(abs2grad);
	}
	while(abs_grad > epsilon && q < 50000);
	return x;
}
vdouble vdouble::Tichonov(vdouble& b, bool AlphaNonZero)
{
	if (m_dims != 2)
	{
		MessageBox(0, _T("Error using double::Tichonov(vdouble& b) (m_dims != 2)"),
			_T("Error"),0);
        //ExitProcess(0);
		return vdouble();
	}
	if (m_size[0] < 1 || m_size[1] < 1)
	{
		MessageBox(0, _T("Error using double::Tichonov(vdouble& b)\n Size < 1"),
			_T("Error"),0);
        //ExitProcess(0);
		return vdouble();
	}
	if (m_size[0] != b.m_length)
	{
		TCHAR str[1024];
		stprintf_s(str, 1024, _T("Error using double::Tichonov(vdouble& b)\nSize of vector %i must be equial to size of matrix = %i %i"), b.m_length,m_size[0],m_size[1]);
		MessageBox(0, str,_T("Error"),0);
        //ExitProcess(0);
		return vdouble();
	}
	int 
		i, r, c,
		rows = m_size[0],
		cols = m_size[1],
//		max_epochs = 2,
//		maxq = 10000 / max_epochs,
		maxq = 1000, //
		MaxNotTurned = 10;// число итераций на которые действует отмена настройки
	double delta, // Приближение - норма векторав невязки
		alpha, // регуляризационный коэффициент
		alpha_old, // 
		xS, //
		part = 0.01, // доля от нормы вектора невязки, какую должен составлять регуляризационный коэффициент
		//part_down = 0.1, //
		mindFdx = 1.0e-12, // минимальное значение изменения функционала - ниже которого отменяется настройка для элемента решения на заданное число итераций
		//mindFdx_down = 0.1, //
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
	vdouble x, // вектор решения
		E(rows), // вектор невязки
		dFdx(cols), // отношения производных функционала по элементу вектора решения
		d2Fdx2(cols), // вектор второйпроизводной функционала по элементам решения
		dx(cols), // вектор величины подстройки весов на текущей итерации
		etha(cols, etha0), // вектор коэффициентов скорости обучения
		dF(cols), // вектор изменения функционала при подстройке каждого элемента решения
		vF(cols); // вектор функционала
	pb = b.pD;
	pE = E.pD;
	pdx = dx.pD;
	pvF = vF.pD;
	pdF = dF.pD;
	pdFdx = dFdx.pD;
	petha = etha.pD;
	// флаг настройки каждого элемента
	Vector<bool> ToTurn; 
	ToTurn.resize(cols,true);

	bool 
		NotFailed, // флаг того что настройка всех элементов оказалась удачной
		ToTurnAnyElement; // флаг необходимости настройки хоть одного элемента вектора решения
	
	if (rows >= cols)
	{

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
		alpha = 0.0;

	}
	else // если система недоопределена
	{
		x = ones(cols); // инициализируем вектор решения единицами
		px = x.pD;
		// Вектор невязки
		for (r = 0; r < rows; r++)
		{
			int rcols = r * cols;
			*(pE + r) = - *(pb + r);
			for (c = 0; c < cols; c++)
				*(pE + r) += *(px + c) * *(pD + c + rcols);
		}
		// Приближение
		delta = sqrt(E.SquareSum());
		// Регуляризационный коэффициент
		alpha = delta;
	}
	//Цикл подстройки
//	bool AlphaNonZero = true;
//	for (int epoch = 1; epoch <= max_epochs; epoch++)
//	{
//		alpha = 0.0;
	p2 = d2Fdx2.pD;
	//Вычисление второй производной
	for (c = 0; c < cols; c++)
	{
		*(p2 + c) = 0.0;// alpha;
		for (r = 0; r < rows; r++)
		{
			i = c + r * cols;
			*(p2 + c) += *(pD + i) * *(pD + i);
		}
		*(p2 + c) *= 2.0;
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
			xS = E.SquareSum() / x.SquareSum();
			xS = xS < .1 ? xS : .1;
			alpha = part *  xS;
		}
		else
			alpha = 0.;
		// Поправка второй производной
		for (c = 0; c < cols; c++)
			*(p2 + c) += 2.0*(alpha - alpha_old);

		// Перебираем все элементы x
		for (c = 0; c < cols; c++)
		{
			if ( ToTurn[c] || q % MaxNotTurned == 0)
			{
				ToTurnAnyElement = true;
				// Вычисляем первую производную
				*(pdFdx + c) = alpha * *(px + c);
				for (r = 0; r < rows; r++)
				{
					i = c + r * cols;
					*(pdFdx + c) += *(pE + r) * *(pD + i);
				}
				*(pdFdx + c) *= 2.0 / *(p2 + c);
				//
				if (q > 1)
				{
					//
					if ( fabs(*(pdFdx + c)) < mindFdx)
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
								min = fabs(*(pdFdx + i));
								max = min;
							}
							else
							{
								cur = fabs(*(pdFdx + i));
								min = cur < min ? cur : min;
								max = cur > max ? cur : max;
							}
						}
					}
					if (TurnedElements > 2)
					{
						cur = fabs(*(pdFdx + c));
						if (cur == min)	// изменение функционала (<0) минимально по абсолютной величине - т.о. минимально по модулю
						{
							// немного уменьшаем коэффициент скорости подстройки
							*(petha + c) *= little_down;
							// не вышли ли за пределы нижней границы?
							*(petha + c) = *(petha + c) < minetha ? minetha : *(petha + c);
						}
						else if (cur == max) // изменение функционала (<0) минимально по абсолютной величине - т.о. минимально  по модулю
						{
							// немного увеличиваем коэффициент скорости подстройки
							*(petha + c) *= little_up;
							// не вышли ли за пределы верхней границы?
							*(petha + c) = *(petha + c) > maxetha ? maxetha : *(petha + c);
						}
					}
				}


				// Алгоритм подстройки с использованием инерционного члена
				if (q == 1)
					*(pdx + c) = *(petha + c) * *(pdFdx + c);
				else // используем инерционный член
				{
					// предыдущий прирост умножаем на инерционный коэффициент
					*(pdx + c) *= inertio; 
					// результат суммируем с текущим приростом элемента вектора решения
					*(pdx + c) += *(petha + c) * *(pdFdx + c);
				}
				//Подстраиваем элемент вектора x
				*(px + c) -= *(pdx + c);
				// Вектор невязки
				for (r = 0; r < rows; r++)
				{
					int rcols = r * cols;
					*(pE + r) = - *(pb + r);
					for (int C = 0; C < cols; C++)
						*(pE + r) += *(px + C) * *(pD + C + rcols);
				}
#if 1
				// вычисляем функционал после подстройки очередного элемента вектора решения
				F = E.SquareSum() + alpha * x.SquareSum();
				if (q > 1)
				{
					// вектор изменения функционала за текущую итерацию
					*(pdF + c) = F - *(pvF + c);
					if ( *(pdF + c) > 0) // функционал вырос - текущая подстройка неудаяная
					{
						// восстанавливаем предыдущее значение инерционного члена
						*(pdx + c) -= *(petha + c) * *(pdFdx + c);
						*(pdx + c) /= inertio;
						// отменяем текущее изменение элемента вектора решения
						*(px + c) += *(petha + c) * *(pdFdx + c);
						// заново вычисляем вектор невязки
						for (r = 0; r < rows; r++)
						{
							int rcols = r * cols;
							*(pE + r) = - *(pb + r);
							for (int C = 0; C < cols; C++)
								*(pE + r) += *(px + C) * *(pD + C + rcols);
						}
						// восстанавливаем прежнее значение функционала
						F = *(pvF + c);
						// изменение функционала = 0
						*(pdF + c) = 0; 
						ToTurn[c] = true;
						NotFailed = false;
						if (*(petha + c) == minetha) // minetha завышено
						{
							minetha *= little_down;
						}
						if (*(petha + c) == maxetha) // maxetha завышено
						{
							maxetha *= little_down;
						}
						// радикально уменьшаем коэффициент скорости подстройки
						*(petha + c) *= much_down;

						// не вышли ли за пределы нижней границы?
						*(petha + c) = *(petha + c) < minetha ? minetha : *(petha + c);
					}
				}
				// Запоминаем вычисленный функционал в вектор
				*(pvF + c)  = F;
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

		if (q > 2 && dF.SquareSum() < 0.000001)
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
	return x;
}
int vdouble::pinv(vdouble& PinvMatrix)
{
	if (m_dims != 2)
	{
		MessageBox(0, _T("Error using double::pinv(vdouble& PinvMatrix) (m_dims != 2)"), _T("Error"), 0);
        //ExitProcess(0);
		return -1;
	}
	int rows = m_size[0], 
		cols = m_size[1],
		rows1 = rows + 1,
		q, 
		maxq = 10;
	double *pPinvMatrix,
		*pE, 
		error, //
		error_old, //
		derror, //
		epsilon = 1e-6, // 
		depsilon = 1e-6; // 
	vdouble v, //
		x, //
		F, //
		E; //
	PinvMatrix.resize(cols,rows);
	pPinvMatrix = PinvMatrix.pD;
	//
	for (int s = 0; s < rows; s++)
	{
		v.resize(rows, 0.0);
		v[s] = 1.0;
		x = this->Tichonov(v);
		for (int c = 0; c < cols; c++)
			*(pPinvMatrix + c * rows + s) = x[c];
			//PinvMatrix(c, s) = x[c];
	}
	//
	E.resize(rows,rows,0.0); pE = E.pD;
	for (int r = 0; r < rows; r++)
		*(pE + r * rows1) = 1.0;
	// F0
	F = E - this->MatrixWithMatrixProduct(PinvMatrix);
	F.m_dims = 2; 
//	F.m_size.resize(2); 
	F.m_size[0] = rows;F.m_size[1] = rows;

	error = sqrt(F.SquareSum());
	derror = 2 * depsilon;
	if (F.MaxAbs() < 1.0) //
	{
		q = 0;
		do
		{
			q++;
			error_old = error;
			PinvMatrix += PinvMatrix.MatrixWithMatrixProduct(F);
			F = E - this->MatrixWithMatrixProduct(PinvMatrix);
			F.m_dims = 2; 
//			F.m_size.resize(2); 
			F.m_size[0] = rows;F.m_size[1] = rows;

			error = sqrt(F.SquareSum());
			derror = error_old - error;
		}
		while(error > epsilon && fabs(derror) > depsilon && q < maxq);
	}
	else
		return +1;

	



	
	return 0;
}
vdouble vdouble::LinearInterp(vdouble &t)
{
	if (m_length != t.m_length)
	{
/*		AfxMessageBox("Eroor using vdouble::LinearInterp(vdouble &t) \n (m_lenght != t.m_length)");
		AfxThrowUserException();*/
		return vdouble();
	}
	vdouble M = vdouble(m_length,2);
	double *pM, *pt;
	pM = M.pD;
	pt = t.pD;
	int lenM = m_length * 2;
	for (int i = 0; i < lenM; i += 2)
	{
		*(pM + i) = 1.;
		*(pM + i + 1) = *(pt + i/2);
	}
	return M.Tichonov((*this));
}
vdouble vdouble::LinearInterp()
{
	vdouble M = vdouble(m_length,2);
	double *pM;
	pM = M.pD;
	int lenM = m_length * 2;

	for (int i = 0; i < lenM; i += 2)
	{
		*(pM + i) = 1.;
		*(pM + i + 1) = i/2;
	}
	return M.Tichonov((*this));
}
#if 0
void vdouble::Derivatives(vdouble& t, double dt,
						vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
						  vdouble& tau, 
						  vdouble& ma, vdouble& d1, vdouble& d2, 
						  int nPoints, int interp_order, bool uniform,
						  bool isEnd, int nPredict)// Первая и вторая производная
{
	int deriv_order = 2;
	if (m_length != t.m_length)
	{
/*		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n m_length (%i)!= t.m_length (%i)",
			m_length, t.m_length);
		AfxMessageBox(errstr);
		AfxThrowUserException();*/
		return;
	}
	if ( m_length <= nPoints)
	{
/*		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n m_length (%i) <=  nPoints (%i)",
			m_length,  nPoints);
		AfxMessageBox(errstr);
		AfxThrowUserException();*/
		return;

	}
	if ( m_length <= interp_order)
	{
/*		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n m_length (%i) <=  interp_order (%i)",
			m_length,  interp_order);
		AfxMessageBox(errstr);
		AfxThrowUserException();*/
		return;
	}
	if ( interp_order >= nPoints)
	{
/*		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n interp_order (%i) >=  nPoints (%i)",
			interp_order,  nPoints);
		AfxMessageBox(errstr);
		AfxThrowUserException();*/
		return;
	}
	if ( deriv_order > interp_order)
	{
/*		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n deriv_order (%i) >  interp_order (%i)",
			deriv_order,  interp_order);
		AfxMessageBox(errstr);
		AfxThrowUserException();*/
		return;
	}
	double *pT, *pt, 
		tend, 
		qt;
	int Len = m_length - nPoints + 1,
		N = interp_order + 1,
		r, c, j, rN;
	vdouble T, x, v;// error, dd;
	if (isEnd)
	{
		// Если длины векторов СС и производных не соответствуют необходимой, то эти вектора вычисляются заново
		if (Len != tau.m_length
			|| Len != ma.m_length 
			|| Len != d1.m_length
			|| Len != d2.m_length)
			isEnd = false;
	}
	if (!isEnd)
	{
		tau.resize(Len);
		ma.resize(Len);
		d1.resize(Len);
		d2.resize(Len);
	}
	// матрица временных интервалов, возведённых в степень столбца
	T.resize(nPoints,N);pT = T.pD;
	CString filename;
	if (nPredict == 0)
		filename.Format("C:/vdb/v%i_%i.vdb", N, nPoints);
	else
		filename.Format("C:/vdb_p/v%i_%i_%i.vdb",nPredict, N, nPoints);
	//error.resize(Len);
	//
	bool NewPinvT = false;
	if (pinvT.m_length == 0)
		NewPinvT = true;
	if (pinvT.m_dims != 2)
		NewPinvT = true;
	else
	{
		if (pinvT.m_size[0] != N || pinvT.m_size[1] != nPoints)
			NewPinvT = true;
	}
	// формирование матрицы временных интервалов
	qt = 2 / dt / (nPoints - 1); // коэффициент растяжки полиномов по оси времени
	if (uniform)
	{
		// формирование матрицы временных интервалов на равномерной сетке
		for (r = 0; r < nPoints; r++)
		{
			rN = r * N;
			*(pT + rN) = 1.;
			for(c = 1; c <= interp_order; c++)
				*(pT + rN + c) = pow((r - nPoints + 1 - nPredict)*qt*dt,(double)c);
		}
		if(NewPinvT)
		{
			bool toCalc = false;
			if (pinvT.Load(filename) != 0)
			{
				toCalc = true;
			}
			else
			{
				if (pinvT.m_length == 0)
					toCalc = true;
				if (pinvT.m_dims != 2)
					toCalc = true;
				else
				{
					if (pinvT.m_size[0] != N || pinvT.m_size[1] != nPoints)
						toCalc = true;
				}
			}
			if (toCalc)
			{
				T.pinv(pinvT);
				pinvT.Save(filename);
			}
		}
	}

	int j0;
	if (isEnd)
		j0 = Len - 1; // вычисляется лишь крайний элемент
	else 
		j0 = 0;

	for (j = j0; j < Len; j++)
	{
		pt = t.pD + j;
		tend = *(t.pD + j + nPoints - 1);
		// участок сигнала для интерполяции полиномами
		v = this->operator[](sequence(j, j + nPoints-1));
		// формирование матрицы временных интервалов на неравномерной сетке
		if (!uniform)
		{
			for (int r = 0; r < nPoints; r++)
			{
				rN = r * N;
				*(pT + rN) = 1.;
				for(int c = 1; c <= interp_order; c++)
					*(pT + rN + c) = pow((*(pt + r) - tend)*qt,(double)c);
			}
			// коэффициенты интерполяции полиномами
			x = T.Tichonov(v);
		}
		else
		{
			// коэффициенты интерполяции полиномами
			x = pinvT.MatrixProduct(v);
		}
		if (isEnd) // обновление векторов со сдвигом
		{
			tau << tend;
			ma << x[0];
			// вычисление производных в точке для которой локальная абцисса равна нулю
			d1 << x[1] * qt;
			d2 << x[2] * 2 * qt * qt;
		}
		else
		{
			tau[j] = tend;
			ma[j] = x[0];
			// вычисление производных в точке для которой локальная абцисса равна нулю
			d1[j] = x[1] * qt;
			d2[j] = x[2] * 2 * qt * qt;
			// ошибка интерполяции текущего участка сигнала
			//dd = T.MatrixProduct(x) - v;
			//error[j] = 100 * sqrt(dd.SquareSum() / v.SquareSum());
		}
	}
	//  средняя ошибка интерполяции
//	CString errmean;
//	errmean.Format("ErrorMean = %g", error.Mean());
//	AfxMessageBox(errmean);
//	AfxMessageBox("pinvT = " + pinvT.dispMatrix_str());
//	AfxMessageBox("T = " + T.dispMatrix_str());
//	AfxMessageBox("v = " + v.disp_str());
//	AfxMessageBox("x = " + x.disp_str());
//	AfxMessageBox("error = " + error.disp_str());

}
void vdouble::Derivative(vdouble& t, 
						vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
						 double& ma, double& d1, double& d2, 
						 int interp_order)// Первая и вторая производная
{
//	WriteRaporto((CString)" vdouble::Derivative:\t");
	if (m_length != t.m_length)
	{
		AfxMessageBox("Eroor using vdouble::Derivatives:\n(m_length != t.m_length)");
		AfxThrowUserException();
	}
	int N = interp_order + 1,
		rN;
	vdouble T;

	double *pT, *pt, 
		tend, 
		qt = 2 / (t[m_length - 1] - t[0]);
	vdouble x, v;

	bool NewPinvT = false;
	if (pinvT.m_length == 0)
		NewPinvT = true;
	if (pinvT.m_dims != 2)
		NewPinvT = true;
	else
	{
		if (pinvT.m_size[0] != N || pinvT.m_size[1] != m_length)
			NewPinvT = true;
	}
//	WriteRaporto((CString)" vdouble::Derivative NewPinvT:\t");
	if (NewPinvT)
	{
		T.resize(m_length,N);
		pT = T.pD;
		pt = t.pD;
		tend = *(t.pD  + m_length - 1);
		for (int r = 0; r < m_length; r++)
		{
			rN = r * N;
			*(pT + rN) = 1.;
			for(int c = 1; c <= interp_order; c++)
				*(pT + rN + c) = pow((*(pt + r) - tend)*qt,(double)c);
		}
		T.pinv(pinvT);
	}
//	WriteRaporto((CString)" vdouble::Derivative T.pinv(pinvT):\t");

//		AfxMessageBox("M = " + M.dispMatrix_str());
//	WriteRaporto((CString)" vdouble::Derivative if{}\t");
	x = pinvT.MatrixProduct(*this);
//	WriteRaporto((CString)" vdouble::Derivative Tichonov\t");
//		AfxMessageBox("x = " + x.disp_str());
	// moving averange
	ma = x[0];
	d1 = x[1] * qt;
	d2 = x[2] * 2 * qt * qt;
		// ошибка интерполяции текущего участка сигнала
//	vdouble dd = T.MatrixProduct(x) - *this;
//	double	error = 100 * sqrt(dd.SquareSum() / this->SquareSum());

//	WriteRaporto((CString)" vdouble::Derivative End\n");
	//  средняя ошибка интерполяции
//	CString errmean;
//	errmean.Format("ошибка интерполяции = %g", error);
//	AfxMessageBox(errmean);
//	AfxMessageBox("T = " + T.dispMatrix_str());
//	AfxMessageBox("x = " + x.disp_str());
}
void vdouble::NEMA(vdouble& t, vdouble& tau, 
				   vdouble& ema,  
				   vdouble& nema, int nPoints) //Нормированная Экспоненциальная скользящая средняя
{
	if (m_length != t.m_length)
	{
		CString errstr;
		errstr.Format("Error using vdouble::EMA:\n m_length (%i)!= t.m_length (%i)",
			m_length, t.m_length);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	if ( m_length <= nPoints)
	{
		CString errstr;
		errstr.Format("Error using vdouble::EMA:\n m_length (%i) <=  nPoints (%i)",
			m_length,  nPoints);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	int Len = m_length - nPoints + 1;
	double K = 2.0 / ((double)(nPoints + 1)),
		_K = 1 - K;

	nema.resize(Len);
	ema.resize(Len);
	tau.resize(Len);
	tau[0] = t[nPoints - 1];
	vdouble v;
	v = this->operator[](sequence(0, nPoints - 1));
	ema[0] = v.Mean();
	double sum = v.Sum();
	nema[0] = 1.0;
	int i = nPoints;
	for (int j = 1; j < Len; j++)
	{
	
		// tau[j] = *(t.pD + j + nPoints - 1);
		tau[j] = *(t.pD + i);
		ema[j] = K * *(pD + i) + _K * ema[j - 1];
		sum += *(pD + i);
		nema[j] = (nPoints + j) * ema[j] / sum;
		i++;
	}
}

void vdouble::EMA(vdouble& t, vdouble& tau, vdouble& ema, int nPoints) //Экспоненциальная скользящая средняя
{
	if (m_length != t.m_length)
	{
		CString errstr;
		errstr.Format("Error using vdouble::EMA:\n m_length (%i)!= t.m_length (%i)",
			m_length, t.m_length);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	if ( m_length <= nPoints)
	{
		CString errstr;
		errstr.Format("Error using vdouble::EMA:\n m_length (%i) <=  nPoints (%i)",
			m_length,  nPoints);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	int Len = m_length - nPoints + 1;
	double K = 2.0 / ((double)(nPoints + 1)),
		_K = 1 - K;

	ema.resize(Len);
	tau.resize(Len);
	tau[0] = t[nPoints - 1];
	vdouble v;
	v = this->operator[](sequence(0, nPoints - 1));
	ema[0] = v.Mean();
	int i = nPoints;
	for (int j = 1; j < Len; j++)
	{
	
		// tau[j] = *(t.pD + j + nPoints - 1);
		tau[j] = *(t.pD + i);
		ema[j] = K * *(pD + i) + _K * ema[j - 1];
		i++;
	}

}
int vdouble::Derivatives(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
						vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
						 vdouble& tDeriv, // вектор шкалы времени для производной - выходной параметр
						 vdouble& DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
						 int& i1, int& i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
						 int interp_order, // порядок интерполяционного полинома
						 int deriv_order, // порядок высшей производной
						 int nPoints, // число точек временного окна
						 double& qt, // коэффициент растяжки полиномов по оси времени - передаётся в функцию Derivative
						 bool uniform)// флаг равномерности временной сетки
{
	// Данная функция производит полный цикл вычисления производных
	if (m_length != t.m_length)
	{
		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n m_length (%i)!= t.m_length (%i)",
			m_length, t.m_length);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	if ( m_length <= nPoints)
	{
		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n m_length (%i) <=  nPoints (%i)",
			m_length,  nPoints);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	if ( m_length <= interp_order)
	{
		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n m_length (%i) <=  interp_order (%i)",
			m_length,  interp_order);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	if ( interp_order >= nPoints)
	{
		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n interp_order (%i) >=  nPoints (%i)",
			interp_order,  nPoints);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	if ( deriv_order > interp_order)
	{
		CString errstr;
		errstr.Format("Error using vdouble::Derivatives:\n deriv_order (%i) >  interp_order (%i)",
			deriv_order,  interp_order);
		AfxMessageBox(errstr);
		AfxThrowUserException();
	}
	double *pT, *pt, *pDeriv,
		t_center;

	int Len = m_length - nPoints + 1,
		N = interp_order + 1,
		db = nPoints / 2, // число индексов ведущего временного хвоста
		r, c, j, rN;
	//  номера первой и крайней точек вектора времени производной по шкале исходного сигнала
	i1 = db;
	i2 = Len + db - 1;

	vdouble T, x, v, error, dd;
	tDeriv.resize(Len);
	DerivativesMatrix.resize(Len,deriv_order);
	pDeriv = DerivativesMatrix.pD;
	// матрица временных интервалов, возведённых в степень столбца
	T.resize(nPoints,N);pT = T.pD;
	error.resize(Len);
	//
	vdouble d_t = t.DiffVector();
	double mindt = d_t.Min();
	qt = 4 / mindt / (nPoints - 1); // коэффициент растяжки полиномов по оси времени
	//
	bool NewPinvT = false;
	if (pinvT.m_length == 0)
		NewPinvT = true;
	if (pinvT.m_dims != 2)
		NewPinvT = true;
	else
	{
		if (pinvT.m_size[0] != N || pinvT.m_size[1] != nPoints)
			NewPinvT = true;
	}
	// если сетка равномерная формируем матрицу временных интервалов заранее до применения цикла
	if (uniform && NewPinvT)
	{
		double dtqt = mindt * qt;
		// формирование матрицы временных интервалов на равномерной сетке
		for (r = 0; r < nPoints; r++)
		{
			rN = r * N;
			*(pT + rN) = 1.;
			for(c = 1; c <= interp_order; c++)
				*(pT + rN + c) = pow((r - db)*dtqt,(double)c);
		}
		T.pinv(pinvT);
	}
//	AfxMessageBox("pinvT = " + pinvT.dispMatrix_str());
	//
	for (j = 0; j < Len; j++)
	{
		pt = t.pD + j;
		t_center = *(pt + db);
		tDeriv[j] = t_center;
		// участок сигнала для интерполяции полиномами
		v = this->operator[](sequence(j, j + nPoints-1));
		// формирование матрицы временных интервалов на неравномерной сетке
		if (!uniform)
		{
			for (int r = 0; r < nPoints; r++)
			{
				rN = r * N;
				*(pT + rN) = 1.;
				for(int c = 1; c <= interp_order; c++)
					*(pT + rN + c) = pow((*(pt + r) - t_center)*qt,(double)c);
			}
			// коэффициенты интерполяции полиномами
			x = T.Tichonov(v);
		}
		else
		{
			// коэффициенты интерполяции полиномами
			x = pinvT.MatrixProduct(v);
		}
		// ошибка интерполяции текущего участка сигнала
//		dd = v - T.MatrixProduct(x) ;
//		error[j] = 100 * sqrt(dd.SquareSum() / v.SquareSum());
		// вычисление производных в точке для которой локальная абцисса равна нулю
		for (int ord = 1; ord <= deriv_order; ord++)
		//	DerivativesMatrix(j,ord - 1) = x[ord] * (double)fact(ord) * pow(qt,(double)ord);
			*(pDeriv + j*deriv_order + ord - 1) = x[ord] * (double)fact(ord) * pow(qt,(double)ord);
		// Объяснение сущности предыдущей формулы -
		// получаем коэффициенты первой производной от интерполирующего полинома
		// и вычисляем значение производной в нуле 
		// и так для всех требующихся порядков производных
		//	for (int ord = 1; ord <= deriv_order; ord++)
		//	{
		//		x = x.PolynomDerivative();
		//	//	*(pDeriv + j*deriv_order + ord - 1) = x.PolynomValue(0.0);
		//		DerivativesMatrix(j,ord - 1) = x.PolynomValue(0.0);
		//	}
	}
	//  средняя ошибка интерполяции
//	CString errmean;
//	errmean.Format("ErrorMean = %g", error.Mean());
//	AfxMessageBox(errmean);
//	AfxMessageBox("DerivativesMatrix = " + DerivativesMatrix.dispMatrix_str());
//	AfxMessageBox("T = " + T.dispMatrix_str() +"\nv = " + v.disp_str() + "\nx = " + x.disp_str());
//	AfxMessageBox();
//	AfxMessageBox();
//	AfxMessageBox("error = " + error.disp_str());
	return 0;

}
int vdouble::Derivative(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
						vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
						 vdouble& tDeriv, // вектор шкалы времени для производной - выходной параметр
						 vdouble& DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
						 int& i1, int& i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
						 int interp_order, // порядок интерполяционного полинома
						 int deriv_order, // порядок высшей производной
						 int nPoints, // число точек временного окна
						 double& qt) // коэффициент растяжки полиномов по оси времени - передаётся из прежде вызванной функции Derivatives
{
	// Эта функция вызывается строго после применения к векторам 
	// сигнала и времени оператора vdouble << double
	// В результате применеия этой функции происходит 
	// смещение по оси времени на один элемент 
	// в массивах производных и в соответствующей шкале времени 
	// с обновлением поздних элементов этих массивов
//	WriteRaporto((CString)" vdouble::Derivative:\t");
	if (m_length != t.m_length)
	{
		AfxMessageBox("Eroor using vdouble::Derivatives:\n(m_length != t.m_length)");
		AfxThrowUserException();
	}
	int N = interp_order + 1,
		Len = m_length - nPoints + 1,
		db = nPoints / 2,
		j, rN;

	double *pT, *pt, *pDeriv,
		t_center;// error;
	vdouble x, v, T, dd;
	pt = t.pD;
	pDeriv = DerivativesMatrix.pD;
	// смещение по оси времени на один элемент 
	// в массивах производных  
	for (j = 0; j < Len - 1; j ++)
	{
		for (int ord = 0; ord < deriv_order; ord++)
			*(pDeriv + j*deriv_order + ord) = 
				*(pDeriv + (j + 1)*deriv_order + ord);
	}
	j = Len - 1;
	pt = t.pD + j;
	t_center = *(pt + db);
	// -//- и в соответствующей шкале времени
	tDeriv << t_center;
	//
	bool NewPinvT = false;
	if (pinvT.m_length == 0)
		NewPinvT = true;
	if (pinvT.m_dims != 2)
		NewPinvT = true;
	else
	{
		if (pinvT.m_size[0] != N || pinvT.m_size[1] != nPoints)
			NewPinvT = true;
	}
	// формирование матрицы временных интервалов
	if (NewPinvT)
	{
		T.resize(nPoints,N);pT = T.pD;
		for (int r = 0; r < nPoints; r++)
		{
			rN = r * N;
			*(pT + rN) = 1.;
			for(int c = 1; c <= interp_order; c++)
				*(pT + rN + c) = pow((*(pt + r) - t_center)*qt,(double)c);
		}
		T.pinv(pinvT);
	}
	// участок сигнала для интерполяции полиномами
	v = this->operator[](sequence(j, j + nPoints-1));
	// коэффициенты интерполяции полиномами
	x = pinvT.MatrixProduct(v);
	// ошибка интерполяции текущего участка сигнала
//	dd = T.MatrixProduct(x) - v;
//	error = 100 * sqrt(dd.SquareSum() / v.SquareSum());
	// вычисление производных в точке для которой локальная абцисса равна нулю
	for (int ord = 1; ord <= deriv_order; ord++)
		*(pDeriv + j*deriv_order + ord - 1) = x[ord] * (double)fact(ord) * pow(qt,(double)ord);
	//  средняя ошибка интерполяции
//	CString errmean;
//	errmean.Format("ошибка интерполяции = %g", error);
//	AfxMessageBox(errmean);
	return 0;
}
int vdouble::diff_Wp(vdouble& t, // ветор сигнала *this и вектор шкалы времени для сигнала
	vdouble& pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
	int denom_order, // порядок знаменателя передаточной функции
	int nPoints, // число точек временного окна для вычисления производной
	bool uniform, // флаг равномерной временной шкалы
	vdouble& denom, // коэффициенты знаменателя передаточной функции
	vdouble& num, // коэффициенты числителя передаточной функции
	vdouble& f_reconstr, // реконструированный сигнал
	double& er_deriv, // ошибка разложения сигнала по базису его производных
	double& er_reconstr)// ошибка реконтрукции сигнала
{
	int num_order = denom_order - 1,
		i1, i2,
		deriv_order = denom_order,
		interp_order = deriv_order + 2;
	double qt; 
	vdouble tDeriv,
		DerivativesMatrix,
		v, dd;
	this->Derivatives(t, // ветор сигнала *this и вектор шкалы времени для сигнала
		pinvT, // матрица - фильтр для вычисления производных, вычисленная псевдообращением матрицы временных интервалов
		tDeriv, // вектор шкалы времени для производной - выходной параметр
		DerivativesMatrix, // матрица производных размерностью tDeriv.m_lenght x deriv_order - выходной параметр
		i1, i2, // индексы первого и крайнего элементов вектора времени производных по шкале времени сигнала
		interp_order, // порядок интерполяционного полинома
		deriv_order, // порядок высшей производной
		nPoints, // число точек временного окна
		qt, // коэффициент растяжки полиномов по оси времени - передаётся в функцию Derivative
		uniform);
	// кусок сигнала с отрезанными хвостами в соответствии со шкалой времени для производной
	v = this->operator[](sequence(i1,i2));
	// вычисление коэффициентов разложения сигнала 
	// по базису его производных
	// этими коэффициентами инициализируем знаменатель передаточной функции
	denom = DerivativesMatrix.Tichonov( -v );
	// ошибка разложения сигнала по базису его производных
	dd = v + DerivativesMatrix.MatrixProduct(denom);
	er_deriv = 100 * sqrt( dd.SquareSum() / v.SquareSum() );
	// реконструкция коэффициентов числителя
	denom.b_reconstructor(num, tDeriv, v, t[0]);
	// реконструированный сигнал
	Vector<vdouble> koefs;
	CString sRoots;
	InvLaplace(num, denom, t, f_reconstr, koefs, sRoots);
	// ошибка реконтрукции сигнала
	dd = f_reconstr - *this;
	er_reconstr = 100 * sqrt( dd.SquareSum() / this->SquareSum() );
	double de = denom.End();
	num /= de;
	denom /= de;
	return 0;
}
#endif
double vdouble::det()
{
	int n = (int)sqrt((double)m_length);
	if (n*n != m_length)
	{
/*		fprintf(stderr, "Error using det(): n*n != m_length\n");
		AfxThrowUserException();*/
		return 1.0e300;
	}
	double _det;
	int n1, n_1, c, r, i, cc;
	double *p, mult, aii, *prn, *pcn;
	n1 = n+1; n_1 = n-1; _det = 1.0;
	if ((p = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length * SD)) == NULL) { MEMORY_ERROR2 }
	for (i = 0; i < m_length; i++) { *(p+i) = *(pD+i);}
	if (n == 1 && *p == 0.0)
	{
		_det = 0.0;
	}
	//=============== Формирование верхнетреугольной матрицы =============
	for ( c = 0; c < n_1; c ++) // Перебираем столбцы с левого по предпоследний
	{
	//========== Проверка отсутствия нуля на главной диагонали ======
		if(*(p + c*n1) == 0) //Если диагональный элемент нулевой
		{
			r = c + 1;
			while(*(p + r*n + c) == 0.0  && r < n)
			{
				r++;
			}
			if (r == n)
			{
				cc = c + 1; 
				r = c;
				while(*(p + r*n + cc) == 0.0 && cc < n)
				{
					cc++;
				}
				if ( cc == n)
				{
					HeapFree(GetProcessHeap(), 0,p);
					return 0.0; // столбец или строка из нулевых элементов
				}
				else
				{
					// Осуществляем перестановку столбцов: c-тый и сс-тый
					double temp, *pc, *pcc;
					pc = p + c;
					pcc = p + cc;
					for (i = 0; i < n; i++)
					{
						temp = *(pc + i*n);
						*(pc + i*n) = *(pcc + i*n);
						*(pcc + i*n) = temp;
					}
					_det *= -1.0;
				}
			}
			else
			{
				// Осуществляем перестановку строк : r-тую и с-тую
				double temp;
				pcn = p + c*n; prn = p + r*n;
				for (i = 0; i < n; i++)
				{
					temp = *pcn;
					*pcn = *prn;
					*prn = temp;
					pcn++; prn++;
				}
				_det *= -1.0;
			}
		}
		//====== Конец проверки отсутствия нуля на главной диагонали ======
		aii = *(p + c*n1); // Элемент на главной диагонали
		pcn = p + c*n;
		for (r = c + 1; r < n; r++) // по текущему столбцу вниз, начиная с поддиагонального эл-та
		{
			prn = p + r*n;
			mult = *(prn + c) / aii; // Множитель для корректировки r-той строки
			for (i = c; i < n; i++) // Добавляем к r-той строке с-тую, умноженную на корректирующий множитель
				*(prn + i) -= mult * *(pcn + i);
		}
	}
	for (c = 0; c < n; c++)
		_det *= *(p + c * n1);
	HeapFree(GetProcessHeap(), 0,p);
	return _det;
}
/*double vdouble::det_old()
{
	int n = sqrt(m_length);
	if (n*n != m_length)
	{
		fprintf(stderr, "Error using det(): n*n != m_length\n");
		return 1.0e300;
	}
	double _det;
	if (n == 2)
	{
		_det = *pD * *(pD + 3) - *(pD + 2) * *(pD + 1);
	}
	else
	{
		Vector<int> rows(n), cols(n);
		for (int i = 0; i < n; i++)
		{
			rows[i] = i;
			cols[i] = i;
		}
		_det = detfun(pD, n, n, rows, cols);
	}
	return _det;
}

*/
void WriteMatrix(const char * filename, const char * mode, const char * name, int rows, int cols, double *p)
{

	FILE *stream;
	// открываем бинарный файл для записи
	if ((stream = fopen(filename, mode)) == NULL)
	{
 		MessageBox(0, _T("Cannot open file for write.\n"),  _T("WriteMatrix"), 0);
		return;
	}
	// Записываем данные
	int r,c,i;
	bool asIntegers = false;
	fprintf(stream, "name = %s\n", name );
	fprintf(stream, "rows = %d\n", rows );
	fprintf(stream, "cols = %d\n", cols );
	for (r = 0; r < rows; r++)
	{
		for (c = 0; c < cols; c++)
		{
			i = c + r * cols;
			if(asIntegers)
			{
				if (*(p + i) >=0.0)
					fprintf(stream, " %d", (int)*(p + i) );
				else 
					fprintf(stream, "-%d", (int)fabs(*(p + i)) );
			}
			else
			{
				if (*(p + i) >=0.0)
					fprintf(stream, "   %7.4f", *(p + i) );
				else 
					fprintf(stream, "  -%7.4f", fabs(*(p + i)) );
			}
		}
		fprintf(stream, "\n");
	}
	fprintf(stream, "\n\n");
	// закрываем файл
	fclose(stream);
}
void vdouble::sls_det(vdouble& b, vdouble& x, double& _det, bool PrivateDesigion)
{
	//printf("vdouble::sls_det\n");
	int n = (int)sqrt((double)m_length);
	int n1, n_1, c, r, i, cc;
	double *p, mult, aii, *prn, *pcn, *pb, *px, *pxc, *pc;
	//=========================================================
	n1 = n+1; n_1 = n-1; _det = 1.0;
	x = vdouble(n);
	bool test_sls = true;


	//=========================================================
	if (n*n != m_length)
	{
		TCHAR strerr[255];
		stprintf_s(strerr, 255,  _T("Error using det(): n*n (%d) != m_length (%d)\n") , n, m_length);
		MessageBox(0,strerr, _T("sls_det"), 0);
		return;
	}
	if (n != b.m_length)
	{
		TCHAR strerr[255];
		stprintf_s(strerr, 255, _T("Error using det(): n (%d) != b.m_length (%d)\n"), n, b.m_length);
		MessageBox(0,strerr, _T("sls_det"),0);
		return;
	}
	//this->Write("d:\\sls_test.txt","wt", "M", false);


	//=========================================================
	Vector<int> indexes(n); 
	for(i = 0; i < n; i++) indexes[i] = i;
	bool reindexed = false;
	//=========================================================
	if ((pb = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n * SD)) == NULL) { MEMORY_ERROR0 }
	for (i = 0; i < n; i++) { *(pb+i) = *(b.pD+i);}
	if ((p = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length * SD)) == NULL) { MEMORY_ERROR0 }
	for (i = 0; i < m_length; i++) { *(p+i) = *(pD+i);}
	if (n == 1 && *p == 0.0)
	{
		_det = 0.0;
	}
	//=============== Формирование верхнетреугольной матрицы =============
	for ( c = 0; c < n_1; c ++) // Перебираем столбцы с левого по предпоследний
	{
		//WriteMatrix("d:\\sls_test.txt","at","p",n,n,p);
		//WriteMatrix("d:\\sls_test.txt","at","pb",n,1,pb);
		//========== Проверка отсутствия нуля на главной диагонали ======
		if(*(p + c*n1) == 0) //Если диагональный элемент нулевой
		{
			r = c + 1;
			while(*(p + r*n + c) == 0.0  && r < n)
			{
				r++;
			}
			if (r == n)
			{
				cc = c + 1; 
				r = c;
				while(*(p + r*n + cc) == 0.0 && cc < n)
				{
					cc++;
				}
				if ( cc == n)
				{
					_det = 0.0;
					break;
				}
				else
				{
					// Осуществляем перестановку столбцов: c-тый и сс-тый
					double temp, *pc, *pcc;
					pc = p + c;
					pcc = p + cc;
					for (i = 0; i < n; i++)
					{
						temp = *(pc + i*n);
						*(pc + i*n) = *(pcc + i*n);
						*(pcc + i*n) = temp;
					}

	
					i = indexes[c];
					indexes[c] = indexes[cc];
					indexes[cc] = i;
					reindexed = true;

					_det *= -1.0;	
				}
				//WriteMatrix("d:\\sls_test.txt","at","после перестановки столбцов \np",n,n,p);
				//WriteMatrix("d:\\sls_test.txt","at","pb",n,1,pb);
			}
			else
			{
				// Осуществляем перестановку строк : r-тую и с-тую
				double temp;
				pcn = p + c*n + c; 
				prn = p + r*n + c;
				for (i = c; i < n; i++)
				{
					temp = *pcn;
					*pcn = *prn;
					*prn = temp;
					pcn++; prn++;
				}
				// соответственно переставляем элементы столбца правых частей
				pcn = pb + c; 
				prn = pb + r;

					temp = *pcn;
					*pcn = *prn;
					*prn = temp;


				_det *= -1.0;
				//WriteMatrix("d:\\sls_test.txt","at","после перестановки строк \np",n,n,p);
				//WriteMatrix("d:\\sls_test.txt","at","pb",n,1,pb);
			}
		}
		//====== Конец проверки отсутствия нуля на главной диагонали ======
		aii = *(p + c*n1); // Элемент на главной диагонали
		pcn = p + c*n;
		for (r = c + 1; r < n; r++) // по текущему столбцу вниз, начиная с поддиагонального эл-та
		{
			prn = p + r*n;
			mult = *(prn + c) / aii; // Множитель для корректировки r-той строки
			for (i = c; i < n; i++) 
			{
				// Добавляем к r-той строке с-тую, умноженную на корректирующий множитель
				*(prn + i) -= mult * *(pcn + i);
			}				
			// Добавляем к r-тому элементу вектора правых частей  строке с-тый, умноженную на тот же множитель
			*(pb + r) -= mult * *(pb + c);
		}
	}

	if (_det != 0.0)
	{
		for (c = 0; c < n; c++)
			_det *= *(p + c * n1);
	}
	else
		test_sls = false;

	if (n > 1)
	{
		if (_det == 0.0 || PrivateDesigion)
		{
			double *p_, *pn_1;
			int rn;
			// Алгебраическое дополнение к временной матрице
			vdouble Ann = vdouble(n_1,n_1);
			p_ = Ann.pD; i = 0;
			for (r = 0; r < n_1; r++)
			{
				rn = r*n;
				for (c = 0; c < n_1; c++)
				{*(p_ + i) = *(pD + rn + c); i++;}
			}
			vdouble b2 = vdouble(n_1);
			p_ = b2.pD;
			pn_1 = pD + n_1;
			for (r = 0; r < n_1; r++)
				*(p_ + r) = *(b.pD + r) - *(pn_1 + r*n);
			double d;
			vdouble x_;

			Ann.sls_det(b2, x_, d);

			//x = (x_, 1.0);
			x = x_;
			x.push_back(1.0);
		}
		else
		{
			if (reindexed)
			{
				if ((px = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n * SD)) == NULL) {MEMORY_ERROR0}
			}
			else
			{
				px = x.pD;
			}
			for ( c = n_1; c>=0; c--)
			{
				pxc = px + c;
				*pxc = *(pb + c) / *(p + c*n1);
				pc = p + c;
				for(r = c - 1; r >=0; r--)
					*(pb + r) -= *pxc * *(pc + r*n);
			}
			if (reindexed) 
			{
				double *p_x;
				p_x = x.pD;
				for( i = 0; i < n; i++)
					*(p_x + i) = *(px + indexes[i]);
				HeapFree(GetProcessHeap(), 0,px);
			}
		}
	}
	if (n == 1)
	{
		if (_det != 0)
		{
			x[0] = *pb / *p;
		}
		else
		{
			fprintf(stderr, "Error sls_det() : _det = 0 and n = 1;\n");
			//x = vdouble(0);
			test_sls = false;
		}
	}
	HeapFree(GetProcessHeap(), 0,p);HeapFree(GetProcessHeap(), 0,pb);
	if (test_sls)
	{
		vdouble delta = this->MatrixProduct(x)-b;
		if (log10(delta.SquareSum()) > (-6) ) //допустимая точность шестой знак после запятой
		{
			char str[255];
			sprintf(str,"log10(delta.SquareSum()) = %lf", log10(delta.SquareSum()));
			printf("Warning: sls_det:\n %s\n", str);
		//	MessageBox(0,str,"Warning: sls_det",0);
		}
		//this->MatrixProduct(x).Write("d:\\sls_test.txt","at","test b");
		//(this->MatrixProduct(x)-b).Write("d:\\sls_test.txt","at","test b");
	}
	return;
}

vdouble vdouble::PolynomDerivative() const //Возвращает вектор полинома первой производной
{
	int len, i;
	double *p, k;
	vdouble deriv;
	len = m_length - 1;
	if (len > 0)
	{
		k = (double)len;
		deriv = vdouble(len);
		p = deriv.pD;
		for (i = 0; i < len; i++)
		{
			*(p + i) = *(pD + i) * k;
			k -= 1.0;
		}
	}
	else
	{
		deriv = zeros(1);
	}
	return deriv;
}
vdouble vdouble::PolynomSumming(const vdouble& v) const // Суммирование полиномов
{
	int malen, milen, vlen, i;
	double *pmi, *pma, *ps;

	vlen = v.m_length;
	bool bl = m_length > vlen;

	malen = bl ? m_length : vlen;
	milen = bl ? vlen : m_length;
	// Указатели на конец векторов
	pma   = bl ? pD + m_length - 1 : v.pD + vlen - 1;
	pmi   = bl ? v.pD + vlen - 1 : pD + m_length - 1;

	vdouble s = vdouble(malen);
	ps = s.pD + malen - 1;

	for ( i = 0; i < milen; i++)
		*(ps - i) = *(pmi - i) + *(pma - i);
	for ( i = milen; i < malen; i++)
		*(ps - i) = *(pma - i);
	return s;
}

void vdouble::PolynomDivide(const vdouble& divisor, vdouble& quotient, vdouble& remainder)// Производит деление на полином
{
	int dlen, qlen, rlen, iq, id, dlen_1, nnz;
	double *pd, *pq, *pr, *ptemp, qu;
	dlen = divisor.m_length; dlen_1 = dlen - 1;
	qlen = m_length - dlen + 1;
	rlen = dlen_1;

	quotient = vdouble(qlen);
	remainder = vdouble(rlen);
	pd = divisor.pD;
	pq = quotient.pD;
	pr = remainder.pD;
	if ((ptemp = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,dlen*SD)) == NULL) {MEMORY_ERROR0}
	for ( id = 0; id < dlen_1; id++)
		*(ptemp + id) = *(pD + id);
	for ( iq = 0; iq < qlen; iq++)
	{
		*(ptemp + dlen_1) = *(pD + iq + dlen_1);
		qu = *ptemp / *pd;
		*(pq + iq) = qu;
		for ( id = 1; id < dlen; id++)
			*(ptemp + id - 1) = *(ptemp + id) - *(pd + id) * qu;
	}
	for (id = 0; id < dlen_1; id++)
		*(pr + id) = *(ptemp + id);
	HeapFree(GetProcessHeap(), 0,ptemp);

	Vector<int> inz = Find(remainder != 0.0);
	nnz = inz.size;
	if (nnz == 0)
	{
		//Все элементы нулевые
		remainder = vdouble(0);
	}
	else
	{
		remainder = remainder[sequence(inz[0], remainder.m_length - 1)];
	}
}
int vdouble::PolynomDivideIntoThree_member(double& b, double c)// Производит деление на полином
{
	// производит деление полинома на трёхчлен, 
	// в котором первый коэффициент a равен 1,0,
	// второй коэффициент b неизвестен, - подлежит определению,
	// так чтобы полином делился нацело на трёхчлен
	// третий коэффициент c задаётся как аргумент функции.
	// В случае, если для данного полинома возможно подобрать 
	// трёхчлен с заданным третим коэффициентом ( это означает, что
	// произведение двух корней полинома равно c)
	// то функция возвращает 0 и определяет значение второго коэффициента
	// b, зная который можно найти два соответствующие корня:
	// комплексно сопряжённые или действительные, 
	// в случае неудачи при вычислениях функция возвращает -1
	// а в случае, если задаваемое число c не равно произведению 
	// двух корней полинома функция возвращает +1
	int qlen, iq, id;
	vdouble qu;
	// Предвтавляем второй коэффициент ках бином (1.0 0.0), зависящий от p
	vdouble p(2); p[0] = 1.0; p[1] = 0.0;
	// Делитель представляем в виде трёхмерного массива полиномов, зависящих от p
	Vector<vdouble> divisor = Vector<vdouble>(3);
	divisor[0] = 1.0;
	divisor[1] = p; // - p;
	divisor[2] = c;
	// Частное представляем в виде массива полиномов, зависящих от p
	qlen = m_length - 2;
	Vector<vdouble> quotient = Vector<vdouble>(qlen);
	// Остаток представляем в виде двухмерного массива полиномов, зависящих от p
	Vector<vdouble> remainder = Vector<vdouble>(2);
	Vector<vdouble> temp = Vector<vdouble>(3);
	for (id = 0; id < 2; id++)
		temp[id] = *(pD + id);
	for ( iq = 0; iq < qlen; iq++)
	{
		temp[2]  = *(pD + iq + 2);
		qu = temp[0] ;// / divisor[0];
		quotient[iq] = qu;
		for ( id = 1; id < 3; id++)
			temp[id - 1] = temp[id].PolynomSumming(- conv(divisor[id],qu));
	}
	for (id = 0; id < 2; id++)
		remainder[id] = temp[id];

	// Наибольший общий делитель двух полиномов
	vdouble divider;
/*
	fprintf(stderr,  "remainder[0].disp();";
	remainder[0].disp();
	fprintf(stderr,  "remainder[1].disp();";
	remainder[1].disp();
//*/
	if (remainder[0].m_length == 2)
	{
		b  = - remainder[0][1] / remainder[0][0];
	}
	else
	{
		if (remainder[0].PolynomGreatestCommonDivider(remainder[1], divider) < 0)
		{
			// Ошибка определения наибольшего общего делителя двух полиномов
			fprintf(stderr,"Error in PolynomDivideIntoThree_member() during PolynomGreatestCommonDivider()\n");
			return -1;
		}
//		fprintf(stderr,  "divider = ";divider.disp();
		Vector<int> inz = Find(divider != 0.0);
		divider = divider[sequence(inz[0],divider.m_length - 1)];
		divider = divider / divider[0];
		if (divider.m_length < 2)
		{
			// Заданное число с не соответствует произведению двух корней
			return 1;
		}
		if (divider.m_length == 2)
		{
			b = - divider[1] / divider[0];
		}
		else 
		{
			if (divider.m_length == 3)
			{
				// Ищем корни трёхчлена
				double D = divider[1] * divider[1] - 4.0 * divider[2];
				if (D < 0.0)
				{
					// комплексная пара корней
					return 1;
				}
				else
				{
					//действительные корни
					double sqrtD = sqrt(D);
					b = (- divider[1] + sqrtD) / 2.0;
				}
			}
			else
			{
				vdouble dr, uns;
				Vector<complex> cr;
				Bernulli_roots(dr, cr, uns);
				if (dr.m_length > 0)
				{
					b = dr[0];
				}
				else
				{
					return 1;
				}
			}
		}
	}
	return 0;
}

int vdouble::PolynomRootsSimple(vdouble& prs, vdouble& D)// Вычленяет кратные корни, получая полином с простыми корнями и соответствующий множитель
{
	int result;
	double epsilon = 0.1,
		control_epsilon = 1e-6;
	bool stop = false, Success;

	vdouble deriv, rem1, rem2, rem3, quot;
	deriv = PolynomDerivative();

	PolynomDivide(deriv, quot, rem1);
	rem2 = rem1;
	rem1 = deriv;
	this->PolynomDivide(rem1,quot,rem3);
	if ( !rem3.is_zeros(epsilon) )
	{
		do
		{
			rem1.PolynomDivide(rem2,quot,rem3);
			rem1 = rem2;
			rem2 = rem3; 
			this->PolynomDivide(rem1,quot,rem3);
//fprintf(stderr,"rem2 = "); rem2.disp();
//fprintf(stderr,"rem3 = "); rem3.disp();
		}
		while( !rem3.is_zeros(epsilon));
	}
	D = rem1;
	if (D.m_length > 0)
	{
		if (D[0] != 0.0)
		{
			D = D / D[0];
		}
	}
	PolynomDivide(D, prs, rem1);
	if (prs.m_length > 0)
	{
		if (prs[0] != 0.0)
		{
			prs /= prs[0];
		}
	}

	if ( !(rem1.m_length == 0 || rem1.is_zeros(control_epsilon) ) )
		Success = false;
	else
		Success = true;
	if (!Success)
	{
		result = -1;// Необходимо изменить начальное значение epsilon
		prs = *this; D = 1.0;
	}
	else
	{
		result = 0;
	}
	return result;
}
int vdouble::PolynomGreatestCommonDivider(vdouble& v, vdouble& divider)// Наибольший общий делитель двух полиномов
{
	//The greatest common divider
	bool bl, 
		Success,
		stop = false,
		go = true;
	int result, vlen = v.m_length;
	vdouble rem1, rem2, rem3, quot;
	double epsilon = 1.0e-16,
		control_epsilon = 1.0e-1,
		mepsilon = sqrt(10.0);


	// Указатели на объекты векторов большей и меньшей длины
	vdouble *pvma, *pvmi;
	bl = m_length > vlen;
	pvma = bl ? this : &v;
	pvmi = bl ? &v : this;
	
	do
	{
		if (stop) go = false;
		Success = true;

		pvma ->PolynomDivide(*pvmi, quot, rem1);
		if (rem1.m_length == 0 || rem1.is_zeros(epsilon) )
		{
			divider = *pvmi;
		}
		else
		{
			pvmi->PolynomDivide(rem1, quot, rem2);
			if ( !( rem2.m_length == 0 || rem2.is_zeros(epsilon) ) )
			{
				do
				{
					rem1.PolynomDivide(rem2,quot,rem3);
					rem1 = rem2; rem2 = rem3;
				}
				while( !( rem2.m_length == 0 || rem2.is_zeros(epsilon)) );
			}
			divider = rem1;
		}
		if (divider.m_length > 0)
		{
			// Проверки 
			pvma->PolynomDivide(divider,quot,rem1);
			if ( !(rem1.m_length == 0 || rem1.is_zeros(control_epsilon) ) )
			{	
				Success = false;
			}
			pvmi->PolynomDivide(divider,quot,rem1);
			if ( !(rem1.m_length == 0 || rem1.is_zeros(control_epsilon) ) )
			{
				Success = false;
			}
		}
		if (Success && divider.m_length >= 2)
		{
			go = false;
		}
		else
		{
			if (Success && divider.m_length < 2)
				epsilon *= mepsilon;
			else
			{
				epsilon /= mepsilon;
				stop = true;
			}
		}
	}
	while(go);
	if (!Success)
	{
		result = -1; // необходимо уменьшить начальное epsilon
	}
	else
	{	result = 0;
		// Приведение к удобному виду
		if (divider[0] != 0.0)
			divider = divider / divider[0];
	}
	return result;
}

double vdouble::PolynomValue(const double& a)// Возвращает значение полинома для заданной точки
{
	// Алгоритм Горнера
	double b;
	b = *pD;
	for (int i = 1; i < m_length; i++)
	{
		b *= a;
		b += *(pD + i);
	}
	return b;
}
complex vdouble::PolynomValue(complex& z)// Возвращает значение полинома для заданной точки
{
	complex b;
	double x, y, zx, zy;
	zx = z.x; zy = z.y;
	b.x = *pD;
	b.y = 0.0;
	for (int i = 1; i < m_length; i++)
	{
		//b *= z;
		x = b.x * zx - b.y * zy;
		y = b.x * zy + zx * b.y;
		b.x = x;
		b.y = y;
		//b += *(pD + i);
		b.x += *(pD + i);
	}
	return b;
}
vdouble vdouble::PolynomValues(vdouble& v)// Возвращает массив значений полинома для заданного массива точек 
{
	// Алгоритм Горнера
	vdouble b;
	b = vdouble(v.m_length,*pD);
	for (int i = 1; i < m_length; i++)
	{
		b *= v;
		b += *(pD + i);
	}
	return b;
}

Vector<double> vdouble::PolynomDerivativesValue(const double& a, int N)// Возвращает значение полинома и его производных порядка до N включительно для заданной точки. Если N = 0, вычисляет производные всех возможных порядков. Обобщенный метод Горнера
{
	if (N < 1 || N > m_length)
		N = m_length;
	Vector<double> pdv(N);
	int i, n, n2;
	for (n = 0; n < N; n++)
		pdv[n] = *pD;
	for(i = 1; i < m_length; i++)
	{
		pdv[0] *= a; pdv[0] += *(pD + i);
		n2 = N < m_length - i ? N : m_length - i;
		for (n = 1; n < n2; n++)
		{
			pdv[n] *= a; pdv[n] += pdv[n - 1]; 
		}
	}
	double f; f = 1.0;
	for (n = 1; n < N; n++)
	{
		f *= (double)n;
		pdv[n] *= f;
	}
	return pdv;
}
Vector<vdouble> vdouble::PolynomDerivativesValues(vdouble& v, int N)//Возвращает массивы значений полинома и его производных порядка до N включительно для заданного массива точек. Если N = 0, вычисляет производные всех возможных порядков.  Обобщенный метод Горнера
{
	if (N < 1 || N > m_length)
		N = m_length;
	Vector<vdouble> pdv(N);
	int i, n, n2;
	for (n = 0; n < N; n++)
		pdv[n] = vdouble(v.m_length,*pD);
	for(i = 1; i < m_length; i++)
	{
		pdv[0] *= v; pdv[0] += *(pD + i);
		n2 = N < m_length - i ? N : m_length - i;
		for (n = 1; n < n2; n++)
		{
			pdv[n] *= v; pdv[n] += pdv[n - 1]; 
		}
	}
	double f; f = 1.0;
	for (n = 1; n < N; n++)
	{
		f *= (double)n;
		pdv[n] *= f;
	}
	return pdv;
}
vdouble vdouble::PolynomSubsVariable(const double& a)// Производит замену переменной y = x - a 
{
	// Обобщенный метод Горнера
	int i, n, N, N_1;
	N = m_length; N_1 = N - 1;
	vdouble w(N);
	for (n = 0; n < N; n++)
		w[n] = *pD;
	for(i = 1; i < m_length; i++)
	{
		w[N_1] *= a; w[N_1] += *(pD + i);
		for (n = N - 2; n >= i; n--)
		{
			w[n] *= a; w[n] += w[n + 1]; 
		}
	}
	//Удаление ведущих нулей
	Vector<int> inz = Find(w != 0);
	w = w[sequence(inz[0], w.m_length - 1)];
	//Возвращает вектор полинома с замещённой переменной
	return w;
}
int vdouble::roots(vdouble& droot, Vector<complex>& croot,
				   Vector<int>& order_dr, Vector<int>& order_cr)// Вычисляет корни действительного полинома - действительные и комплексные, отдельно - кратные
{
	int i, nnz, inz_end, order_r0, drlen, crlen, D_old_len, 
		result, res = 0;
	double x, y, epsilon = 1.0e-12;
	vdouble prs, D, q, rem, d, dd, d_r;
	vdouble r0 = vdouble(0);
	complex z;
	Vector<complex> c_r;

	order_dr = Vector<int>(0);
	order_cr = Vector<int>(0);
	
	croot = Vector<complex>(0);
	droot = vdouble(0);
	vdouble unsolved = vdouble(0);

	vdouble c = *this;
	// индексы ненулевых элементов
	Vector<int> inz = Find(c != 0.0);
	nnz = inz.size;
	if (nnz == 0)
	{
		// All elementa are zero
		return 0;
	}
	inz_end = inz.End();
	// кратность нулевого корня
	order_r0 = m_length - 1 - inz_end;
	// Выделение лидирующих нулей и удаление их
	// Выделение замыкающих корней и сохранение их в векторе корней
	c = c[sequence(inz[0], inz_end)];
	c = c / c[0];
	double epsilon_control = 1.0e-2,
		epsilon2_control = epsilon_control * epsilon_control,
		mf, mdf, e;

	complex	zf,
		zdf;

	if (c.m_length > 1)
	{
		// Вычленение кратных корней
		c.PolynomRootsSimple(prs,D);
		vdouble deriv = prs.PolynomDerivative();
		//=========
		bool flag = true;
		double A = 0.0; //Действительная поправка
		vdouble solved;
		solved = 1.0;
		vdouble v = prs;
		vdouble dd = vdouble(2); dd[0] = 1.0;
		vdouble ddd = vdouble(3); ddd[0] = 1.0;
		int q1 = 0, q2 = 0, q3 = 0, Q = 1;


		while (v.m_length > 1 && flag)
		{
			if (v.m_length == 2)
			{
				x = - v[1] / v[0];
				droot.push_back(x);
				v = 1.0;
				result = 0;
			}
			if (v.m_length == 3)
			{
				double Discr;
				// Ищем корни трёхчлена
				Discr = v[1] * v[1] - 4.0 * v[2] * v[0];
				if (Discr < 0.0)
				{
					// комплексная пара корней
					x = - v[1] / 2.0 / v[0];
					y = sqrt(fabs(Discr)) / 2.0 / v[0];
					z.x = x; z.y = y; croot.push_back(z);
					v = 1.0;
				}
				else
				{
					//действительные корни
					double sqrtD = sqrt(Discr);
					for (int j = 0; j < 2; j++)
					{
						x = j == 0 ? (- v[1] + sqrtD) / 2.0 / v[0] : (- v[1] - sqrtD) / 2.0 / v[0];
						droot.push_back(x);
					}
					v = 1.0;
				}
				result = 0;
			}
			if (v.m_length > 3)
			{
				if (Q%2 == 1)
				{
					result = v.Bernulli_roots(d_r, c_r, unsolved);
					if (result < 0)
					{
						fprintf(stderr,"Error during Bernulli_roots()\n");
						return -1;
					}
				}
				if (Q%2 == 0)
				{
					result = v.Lobachevski_Greffe_roots(d_r,c_r,unsolved, epsilon_control);
					if (result < 0)
					{
						fprintf(stderr,"Error during Lobachevski_Greffe_roots()\n");
						return -1;
					}
				}
			
				int sol = 0;

				//Сохранение решения с учётом действительной поправки
				for ( i = 0; i < d_r.m_length; i++)
				{
					x = (d_r[i] + A);

					// Настройка
					prs.PolynomNewtonRoot(x);
					// Проверка
					e = fabs(prs.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
					if (e < epsilon_control)
					{
						dd[1] = - x;
						solved = conv(solved, dd);
						solved = solved / solved[0];

						droot.push_back(x);
						sol++;


					}
					else
					{
						fprintf(stderr, "Error (in roots) = %g of found real root = %g \n",e, x);
					}
				}
				for ( i = 0; i < c_r.size; i++)
				{
					complex z;
					double x, y;
					x = c_r[i].x + A;
					y = c_r[i].y;
					z.x = x; z.y = y;

					// Настройка
					prs.PolynomNewtonRoot(z);

					// Проверка
					zf = prs.PolynomValue(z);
					zdf = deriv.PolynomValue(z);
					mf = zf.x * zf.x + zf.y * zf.y;
					mdf = zdf.x * zdf.x + zdf.y * zdf.y;
					e = mf / mdf;
					if ( e < epsilon2_control)
					{

						ddd[1] = -2.0*x; 
						ddd[2] = x*x + y*y;
						solved = conv(solved,ddd);
						croot.push_back(z);
						sol++;
					}
					else
						fprintf(stderr,"Error (in roots) = %g of complex root = %g + i*%g verification\n", e, x, y);
				}
				if (sol == 0)
				{
					if (result == 1 || result == 0)
					{
						result = 3;
					}
				}

				prs.PolynomDivide(solved, unsolved, rem);

				
				// Удаление ведущих нулей в нерешенном остатке полинома
				inz = Find(unsolved != 0.0);
				unsolved = unsolved[sequence(inz[0], unsolved.m_length - 1)];
				unsolved = unsolved / unsolved[0];
				

				//Назначение нового полинома для решения (если надо с заменой переменной)
				if (result == 0) // найдены все корни
				{
					flag = false; //выход из цикла
				}
				if (result == 1) // найден по меньшей мере один корень
				{
					q3 = 0; q2 = 0;
					A = 0.0;
					v = unsolved;
				}
				//корни трудноотделяемы 
				if (result == 2) //и есть указание на наличие комплексных корней
				{
					q2++;
					q3 = 0;
					//замена переменной
					if (q2%2==1)
					{
						A = pow(unsolved.End(),1.0 /( (double)unsolved.m_length -1.0));
						v = unsolved.PolynomSubsVariable(A);
					}
					if (q2%2==0)
					{
						A = - pow(unsolved.End(),1.0 /( (double)unsolved.m_length -1.0));
						v = unsolved.PolynomSubsVariable(A);
					}
				}
				if (result == 3) // другие варианты
				{
					int N = 10;
								
					q3++; q2 = 0;
					if (q3%N==1)
					{
						//замена переменной
						A = pow(unsolved.End(), 1.0 /( (double)unsolved.m_length -1.0));
						v = unsolved.PolynomSubsVariable(A);
					}
					if (q3%N==2)
					{
						A = 0.0;
						v = unsolved;
					}

					if (q3%N==3)
					{
						//замена переменной
						A = - pow(unsolved.End(),1.0 /( (double)unsolved.m_length -1.0));
						v = unsolved.PolynomSubsVariable(A);
					}
					if (q3%N==4)
					{
						A = 0.0;
						v = unsolved;
					}
					if (q3%N > 4)
					{
						//замена переменной используя генератор случайных чисел
						double minAbs, maxAbs, dAbs, a;
						minAbs = unsolved.MinAbsRoots();
						maxAbs = 10.0 * minAbs;// unsolved.MaxAbsRoots();
						dAbs = maxAbs - minAbs;
						a = minAbs + dAbs * (((double)rand()) / 32767.0);

						A = ((double)pow(-1.0,rand())) * a;
						fprintf(stderr, " A = %g " , A );
						v = unsolved.PolynomSubsVariable(A);
					}
					if (q3%N==N - 1)
					{
						Q++;
						A = 0.0;
						v = unsolved;
					}
					if (q3%N==0)
					{
						flag = false;
						fprintf(stderr, "\nFunction roots did not solved the polynom completelly\nUnsolved = ") ; unsolved.disp();
					}
				}
			}
		}	// 1822261       54-58-75 (ami)
		res = unsolved.m_length > 1 ? 1 : 0;
		//==========
		drlen = droot.m_length;
		crlen = croot.size;
		//==========
		// кратность действительных корней
		order_dr = Vector<int>(drlen);
		for ( i = 0; i < drlen; i++)
			order_dr[i] = 1;
		// кратность комплексных корней
		order_cr = Vector<int>(crlen);
		for ( i = 0; i < crlen; i++)
			order_cr[i] = 1;
		d = vdouble(2); d[0] = 1.0;
		dd = vdouble(3); dd[0] = 1.0;

		D_old_len = D.m_length + 1;
		while(D.m_length > 1 && (D_old_len != D.m_length) )
		{
			//Вычисление кратности действительных и комплексных корней
			D_old_len = D.m_length;
			for ( i = 0; i < drlen; i++)
			{
				if ( fabs(D.PolynomValue(droot[i])) < epsilon_control)
				{
					order_dr[i] += 1;
					d[1] = -droot[i];
					D.PolynomDivide(d, q, rem);
					D = q;
				}
			}
			for ( i = 0; i < crlen; i++)
			{
				z = D.PolynomValue(croot[i]);
				x = croot[i].x; y = croot[i].y;
				if ( fabs(z.x) < epsilon_control && fabs(z.y) < epsilon_control)
				{	
					order_cr[i] += 1;
					dd[1] = - 2.0 * x;
					dd[2] = x * x + y * y;
					D.PolynomDivide(dd, q, rem);
					D = q;
				}
			}
		}
        if (D.m_length > 1)
		{
			fprintf (stderr, "Not all multiply roots are detected\n D.disp = ");
			D.disp();
		}
	}
	if (order_r0 > 0)
	{
		order_dr.push_back(order_r0);
		droot.push_back(0.0);
	}
	return res;
}


int vdouble::Lobachevski_Greffe_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved,const double& epsilon_control)//Вычисляет действительные и комплексные корни действительного полинома методом Лобачевского - Греффе (для полиномов с вычленёнными кратными корнями)
{
	dr = vdouble(0);
	cr = Vector<complex>(0);
	long double lepsilon = 1.0e-4;
	double maxLoops = 15.0;
	Vector<int> inz;// 
	// Максимально допустимый десятичный логарифм для данной машинной точности
	long double maxlog10 = LDBL_MAX_EXP * log10l(_LDBL_RADIX);
	Vector<bool> fd,// Флаг отделившихся действительных корней
		fsr, // Флаг удовлетворительного отделения корней
		fc;	//Флаг пары комплексных корней
	long double *pa, *pai, *pd, *pdi, *pl, *pli, *pbd, *pbdi;
	Vector<long double>a, d, l, bd;
	int i, j, j2, len, result;
	bool *pfd, *pfdi, *pfc, *pfci,
		stopRoots, stopDigits, toQuadri, stopMaxLoops, NonSelectedRoots, toSolve;
	long double b,//квадрат исходного коэффициента
		c, //дополнительная удвоенная сумма
		e, //относительная величина удвоенных сумм
		maxlog, 
		tlog;
	double pw, log_abs_r, e1, e2, x, y, p, D, sqrtD, q,
		abs_r, epsilon2_control = epsilon_control * epsilon_control, mf, mdf,
		*pv;
	vdouble quot, rem, A, v, deriv,  solved;
	solved = 1.0;
	complex z, zf, zdf;
	// Коэффициенты текущего полинома
	v = *this / *pD;
	vdouble dd = vdouble(2); dd[0] = 1.0;// Вектор бинома удаляемого действительного корня
	vdouble ddd = vdouble(3); ddd[0] = 1.0;// Вектор трёхчлена удаляемой пары комплексных корней

	//============= решение текущего полинома ========================
	//длина и указатель текущего полинома
	len = v.m_length; pv = v.pD;
	a = Vector<long double>(len);// Вектор исходных коэффициентов
	d = Vector<long double>(len);// Вектор квадрированных коэффициентов
	bd = Vector<long double>(len);// Отношение квадрата предыдущего коэффициента к итоговому
	l = Vector<long double>(len);// Вектор десятичных логарифмов
	fd = Vector<bool>(len);
	fsr = Vector<bool>(len);
	fc = Vector<bool>(len);
	// Points initialising
	pa = a.data;
	pd = d.data;
	pbd = bd.data;
	pl = l.data;
	pfd = fd.data;
	pfc = fc.data;
	//копирование текущего полинома в вектор исходных коэффициентов
	for (i = 0; i < len; i++)
	{
		*(pa + i) = (long double)(*(pv + i));
		*(pfc + i) = false;
		fsr[i] = false;
	}
	
	vdouble cr2 = vdouble(0);// Квадраты модулей отделённых комплексных пар корней
	vdouble dr2 = vdouble(0);// Произведения двух плохо отделимых действительных корней

	//цикл квадрирования корней текущего полинома:
	pw = -1.0; // Показатель степени 2
	do
	{
		pw +=1.0;
		stopRoots = true;
		stopMaxLoops = pw > maxLoops ? true : false;
		for (i = 0; i < len; i++)
		{
			j2 = i + 1 < len - i ? i + 1 : len - i;
			pai = pa + i;
			pdi = pd + i;
			pbdi = pbd + i;
			pli = pl + i;

			pfdi = pfd + i;
			pfci = pfc + i;

			//Квадрат исходного коэффициента
			b = * pai * *pai;
			//Дополнительные удвоенные суммы
			c = 0.0;
			for (j = 1; j < j2; j++)
				c += ((long double)(2*pow(-1.0,j))) * *(pai - j) * *(pai + j);
			//Итоговый коэффициент
			*pdi = b + c;
			if (*pdi != 0.0)
			{
				*pbdi = b / *pdi;
			}
			else
			{
				*pbdi = 0.0;
			}
			//Вычисление флагов отделения корней
			if (b != 0)
			{
				//Относительная величина удвоенных сумм
				e = c / b;
				//Флаг действительного корня
				*pfdi = fabsl(e) < lepsilon || fabs(*pbdi - 1.0) < 0.1;
				//Флаг пары комплексных корней - коэффициент меняет знак
				*pfci = (*pfci || *pdi < 0.0) && pw > 3.0 && !(*pfdi);
			}
			else
			{
				//Флаг действительного корня
				*pfdi = false;
			}
			stopRoots = stopRoots && (*pfdi || *pfci);
			if (*pdi != 0.0)
			{
				*pli = log10l(fabsl(*pdi));//десятичный логарифм
			}
			else
			{
				*pli = 0.0;
			}
		}
		// Вычисления флага ограничения машинной точности
		maxlog = 0.0;
		for ( i = 0; i< len; i++)
		{
			tlog = fabsl(*(pl + i));
			maxlog = maxlog > tlog ? maxlog : tlog;
		}
		for ( i = 1; i< len; i++)
		{
			pli = pl + i;
			tlog = fabsl(*pli - *(pli - 1));
			maxlog = maxlog > tlog ? maxlog : tlog;
		}
		stopDigits = maxlog >= maxlog10 / 2.25;
		toQuadri = !stopRoots && !stopDigits && !stopMaxLoops;
//  a.disp();
		if (toQuadri)
		{
			//Присвоение исходным коэффициентам квадрированных значений
			a = d;
		}
		else
		{
			long double l1, dl;
			bool nonfirst = false,
				pastSecond = false;
			NonSelectedRoots = true;
			int i1, count = 0;
			for ( i = 0; i < len; i++)
			{
				if ( *(pfd + i))
				{
					count++;
					pli = pl + i;
					// Логарифмируем исходные коэффициенты на последней итерации
					*pli = log10l(*(pa + i));
					if (nonfirst)
					{
						if (pastSecond)
							NonSelectedRoots = NonSelectedRoots && fabs((*pli - l1)/((double)(i - i1)) - dl) < 1.0e-4;
						dl = (*pli - l1)/((double)(i - i1));
						pastSecond = true;
					}
					l1 = *pli; i1 = i;
					nonfirst = true;
				}
			}
			if (count < 3)
				NonSelectedRoots = false;
		}
	}
	while(toQuadri);
/*			fd.disp();
			fc.disp();
			bd.disp();
			a.disp();
			l.disp();
			*/
	bool IsComplexRoots = Find(fc).size > 0;

//fprintf (stderr, " pw = %g,stopDig = %i, stopRoots = %i, stopLoops = %i ", pw, stopDigits, stopRoots,stopMaxLoops);
//fprintf(stderr, " IsComplex = %i, NonSel = %i ", IsComplexRoots, NonSelectedRoots);

	if(!NonSelectedRoots)
	{
		// Вычисление действительных корней
		for ( i = 1; i < len; i++)
		{
			if (fd[i - 1] && fd[i])
			{
				// корень действительный
				log_abs_r = ((double)(l[i] - l[i - 1])) / pow(2.0, pw);
				abs_r = pow(10.0,log_abs_r);
//				fprintf( stderr, "abs_r = %g \n",abs_r);
				// Определение знака корня методом подстановки в текущий полином
				deriv = v.PolynomDerivative();//Коэффициенты полинома производной
				e1 = fabs(v.PolynomValue(abs_r)) / fabs(deriv.PolynomValue(abs_r));
				e2 = fabs(v.PolynomValue( - abs_r)) / fabs(deriv.PolynomValue( - abs_r));
				x = e1 < e2 ? abs_r : - abs_r;
				// Уточнение значения корня методом Ньютона
				this->PolynomNewtonRoot(x);
				// Проверка
				e = fabs(v.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
				if (e < epsilon_control)
				{
					dd[1] = - x;
					solved = conv(solved, dd);
					v.PolynomDivide(dd,quot,rem);
					v = quot;
					dr.push_back(x);
				}
				else
				{
					fprintf(stderr, "Error (1 1) = %g of found real root = %g \n",e, x);
					fprintf (stderr, " Lina method for real two-member !!!\n");
/*					if (v.m_length > 2)
					{
						result = v.PolynomLinaDivider(dd);
						fprintf (stderr, " Lina result = %i\n", result);
						if (result == 0)
						{
							x = - dd[1];
							// Проверка
							e = fabs(v.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
							if (e < epsilon_control)
							{
								dd[1] = - x;
								solved = conv(solved, dd);
								v.PolynomDivide(dd,quot,rem);
								v = quot;
								dr.push_back(x);
							}
							else
								fprintf(stderr, "Error (Lina) = %g of found real root = %g \n",e, x);
						}
					}
*/
				}
			}
		}
		//Вычисление модуля произведения двух плохо отделимых действительных корней
		// Вычисление хорошо отделимых комплексных корней
		for ( i = 2; i < len; i++)
		{
			if (fd[i - 2] && !fd[i - 1] && fd[i])
			{
				// квадрат модуля пары комплексных корней либо модуль произведения действительных корней
				log_abs_r = ((double)(l[i] - l[i - 2])) / pow(2.0, pw);
				abs_r = pow(10.0,log_abs_r);
				result = v.PolynomDivideIntoThree_member(p, abs_r);
				if (result < 0)
				{
					fprintf(stderr, " Error in Lobachevski_Greffe_roots() during PolynomDivideIntoThree_member() \n");
					return -1;
				}
				if (result == 0)
				{
					q = abs_r;
					toSolve = true;
				}
				if (result > 0)
				{
					//Пробуем деление на трёхчлен с отрицательным значением третьего коэффициента
					result = v.PolynomDivideIntoThree_member(p, - abs_r);
					if (result < 0)
					{
						fprintf(stderr, " Error in Lobachevski_Greffe_roots() during PolynomDivideIntoThree_member() \n");
						return -1;
					}
					if (result == 0)
					{
						q = - abs_r;
						toSolve = true;
					}
					if (result > 0 && v.m_length > 3) 
					{
						// Lina3 algorithm
						p = 0.0; q = abs_r;
						result = v.PolynomLinaThree_memberDivider(p,q);
						if (result < 0)
						{
							fprintf(stderr, " Error in Lobachevski_Greffe_roots() during PolynomLinaThree_memberDivider(p,q) \n");
							return -1;
						}
						if (result == 0)
						{
							toSolve = true;
						}
						if (result > 0)
						{
							// Lina3 algorithm
							p = 0.0; q = - abs_r;
							result = v.PolynomLinaThree_memberDivider(p,q);
							if (result < 0)
							{
								fprintf(stderr, " Error in Lobachevski_Greffe_roots() during PolynomLinaThree_memberDivider(p,q) \n");
								return -1;
							}
							if (result == 0)
							{
								toSolve = true;
							}
							if (result > 0)
							{
								toSolve = false;
								fprintf(stderr, "Two roots are unsolved during Logachevski method\n");
							}
						}
					}
				}
				if (toSolve)
				{
					// Ищем корни трёхчлена
					D = p*p - 4.0 * q;
					if (D < 0.0)
					{
						// комплексная пара корней
						x = - p / 2.0;
						y = sqrt(fabs(D)) / 2.0;
						z.x = x;
						z.y = y;
						// Настройка комплексных корней методом Ньютона
						this->PolynomNewtonRoot(z);
						x = z.x; y = z.y;
						// Проверка
						zf = v.PolynomValue(z);
						deriv = v.PolynomDerivative();//Коэффициенты полинома производной
						zdf = deriv.PolynomValue(z);
						mf = zf.x * zf.x + zf.y * zf.y;
						mdf = zdf.x * zdf.x + zdf.y * zdf.y;
						e = mf / mdf;
						if ( e < epsilon2_control)
						{
							ddd[1] = -2.0 * x; ddd[2] = x * x + y * y;
							v.PolynomDivide(ddd, quot, rem);
							solved = conv(solved,ddd);
							v.PolynomDivide(ddd,quot,rem);
							v = quot;
							cr.push_back(z);
						}
						else
							fprintf(stderr,"Error (1 0 1) = %g of complex root = %g + i*%g verification\n", e, x, y);
					}
					else
					{
						//действительные корни
						sqrtD = sqrt(D);
						for (j = 0; j < 2; j++)
						{
							x = j == 0 ? (- p + sqrtD) / 2.0  : (- p - sqrtD) / 2.0;
							// Уточнение значения корня методом Ньютона
							this->PolynomNewtonRoot(x);
							// Проверка
							deriv = v.PolynomDerivative();//Коэффициенты полинома производной
							e = fabs(v.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
							if (e < epsilon_control)
							{
								dd[1] = - x;
								solved = conv(solved, dd);
								v.PolynomDivide(dd,quot,rem);
								v=quot;
								dr.push_back(x);
							}
							else
							{
								fprintf(stderr, "Error1 (1 0 1) = %g of found real root = %g \n",e, x);
							}
						}
					}
				}
			}
		}
	}
	inz = Find(v != 0.0);
	v = v[sequence(inz[0],v.m_length - 1)];
	unsolved = v / v[0];
//fprintf(stderr, " unsolved in LobGreff  = ") ;unsolved.disp();
	if (true/*NonSelectedRoots && !IsComplexRoots*/)
	{
		// близкие по модулю действительные корни
		Vector<int> inzfd = Find(fd); // indexes of nonzeros of fd
		int ord;
		long double binom_quot, binom_quot1, binom_quot2;
		bool isRealRoots;

		for (i = 1; i < inzfd.size; i++)
		{
			// порядок 
			ord = inzfd[i] - inzfd[i - 1];
			if (ord > 1)
			{
				isRealRoots = true;
				for ( j = inzfd[i - 1] + 1; j < inzfd[i]; j++)
				{
					binom_quot = (long double)BinominalQuotient(j - inzfd[i - 1], ord);
					isRealRoots = isRealRoots && fabsl(binom_quot - bd[j]) / binom_quot < 0.2;
				}
				if (isRealRoots)
				{
					for ( j = inzfd[i - 1] + 1; j <= inzfd[i]; j++)
					{
						binom_quot1 = (long double)BinominalQuotient(j - inzfd[i - 1] - 1, ord);
						binom_quot2 = (long double)BinominalQuotient(j - inzfd[i - 1], ord);
						log_abs_r = ((double)( (l[j] - log10l(binom_quot2) ) - (l[j - 1] - log10l(binom_quot1) ) )) / pow(2.0, pw);
						abs_r = pow(10.0,log_abs_r);
						//======
						// Определение знака корня методом подстановки в текущий полином
						e1 = fabs(unsolved.PolynomValue(abs_r)) / fabs(deriv.PolynomValue(abs_r));
						e2 = fabs(unsolved.PolynomValue( - abs_r)) / fabs(deriv.PolynomValue( - abs_r));
						x = e1 < e2 ? abs_r : - abs_r;
						// Уточнение значения корня методом Ньютона
						this->PolynomNewtonRoot(x);dd[1] = - x;
						// Проверка
						deriv = unsolved.PolynomDerivative();
						e = fabs(unsolved.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
						if (e < epsilon_control)
						{
							solved = conv(solved, dd);
							dr.push_back(x);
							unsolved.PolynomDivide(dd,quot,rem);
							unsolved = quot;

						}
						else
						{
		//					fprintf(stderr, "Error (isReal) = %g of found real root = %g \n", e, x);
						}

					}
				}
				if (!isRealRoots && ord < len - 1 ) 
				{
					fprintf(stderr, " Lina Real is necessary!!!\n");
/*					vdouble ff = zeros(ord + 1);
					ff[0] = 1;
					ff[ord] = abs_r;
					result = unsolved.PolynomLinaDivider(ff);
					fprintf(stderr, "result of unsolved.PolynomLinaDivider(ff) = %i\n", result);
					if (result == 0)
					{
						unsolved.PolynomDivide(ff,quot,rem);
						fprintf(stderr,"Lina Divider = "); 
						ff.disp();
						fprintf(stderr,"Quotient of Lina Divider = "); 
						quot.disp();
						fprintf(stderr,"Remainder = "); 
						rem.disp();

					}
					if (result > 0 )
					{
						ff[ord] = - abs_r;
						result = unsolved.PolynomLinaDivider(ff);
						fprintf(stderr, "result of unsolved.PolynomLinaDivider(ff) = %i\n", result);
						if (result == 0)
						{
							unsolved.PolynomDivide(ff,quot,rem);
							fprintf(stderr,"Lina Divider = "); 
							ff.disp();
							fprintf(stderr,"Quotient of Lina Divider = "); 
							quot.disp();
							fprintf(stderr,"Remainder = "); 
							rem.disp();
						}

					}
					*/
				}
			}
		}
	}
	solved = solved / solved[0];

	int unsolvlen = unsolved.m_length;
	if (unsolvlen < 2 && Find(abs(solved - *this) > epsilon_control).size == 0)
		result = 0;// найдены все корни
	else
	{
		if (unsolvlen < len)
			result = 1;		// найден по меньшей мере один корень
		if (unsolvlen == len) // не найден ни один корень
		{
			
			if (NonSelectedRoots && IsComplexRoots)
				result = 2;// корни неотделимы и есть указание на комплексные корни
			else
				result = 3;// другие случаи


		}
	}
/*	if (result == 3)
	{
		fprintf(stderr, "Multi  Lina - necessary!!!\n");
		for (j = 2; j < unsolved.m_length-2; j++)
		{
			vdouble ff = zeros(j);
			ff[0] = 1.0;
			ff[j - 1] = 1.0;
			int res = unsolved.PolynomLinaDivider(ff);
			if (res == 0)
			{
				unsolved.PolynomDivide(ff,quot,rem);
				if (rem.is_zeros(epsilon_control) )
				{
					vdouble *pvsol, *pvun, d_r;
					Vector<complex> c_r;
					Vector<int> or_dr, or_cr;

					bool bl = quot.m_length < ff.m_length;

					pvsol = bl ? &(quot) : &(ff);
					pvun = !bl ? &(quot) : &(ff);
fprintf(stderr, "for solve = "); pvsol->disp();
					pvsol->roots(d_r, c_r, or_dr,or_cr);
					for (i = 0; i < d_r.m_length; i++)
						dr.push_back(d_r[i]);
					for (i = 0; i < c_r.size; i++)
						cr.push_back(c_r[i]);
					result = 1;
				}
			}
		}
	}*/
	return result;
}
int vdouble::Bernulli_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& depsilon)
{
	//Вычисляет действительные и комплексные корни действительного полинома методом Бернулли (для полиномов с вычленёнными кратными корнями)
	int result, i, len, len1, len0, k, k1, k2, k3, maxLoops = 100000, mink = 4, j, j2, inv = 0, unsolvlen;
	double mjuk, tk, Sk, Sk_1, x, y, xx, e, mf, mdf, c,
		epsilon_control = 1.0e-5,
		epsilon2_control = epsilon_control * epsilon_control,
		rel1, rel1_old, d_rel1, d_rel1_old, dd_rel1,
		rel2, rel2_old, d_rel2, d_rel2_old, dd_rel2,
		rel_ro2, rel_ro2_old, d_rel_ro2, d_rel_ro2_old, dd_rel_ro2,
		rel_2x, rel_2x_old, d_rel_2x, d_rel_2x_old, dd_rel_2x,
		maxLog = 250.0;
	bool nonfirst1, pastsecond1, 
		nonfirst2, pastsecond2, 
		nonfirst3, pastsecond3, pastthird3,
		stop1, stop2, stop3, stopDig,
		stopDig1, stopDig2, stopDig3,
		stopMaxLoops, inversed = false, toInverse = true;

	inversed = true;// Proverka
	complex z, zf, zdf;
	vdouble dd(2), ddd(3); dd[0] = 1.0; ddd[0] = 1.0;
	vdouble solved, quot, rem;
	solved= 1.0;

	dr = vdouble(0);
	cr = Vector<complex>(0);
	vdouble v = *this, mju, deriv;
	Vector<int> inz = Find( v != 0.0);
	v = v[sequence(inz[0], m_length - 1)];
	len0 = v.m_length;
	do
	{
		inv++;
		len1 = v.m_length;
		if (inversed) v = v / v[len1 - 1]; else v = v / v[0];
		bool toSolve, go;
		do
		{
			len = v.m_length;
			deriv = v.PolynomDerivative();
			mju = zeros(len);
			k = 0;
			nonfirst1 = false, pastsecond1 = false, 
				nonfirst2 = false, pastsecond2 = false, 
				nonfirst3 = false, pastsecond3 = false, pastthird3 = false,
				stop1 = false, stop2 = false, stop3 = false, stopDig = false,
				stopDig1 = false, stopDig2 = false, stopDig3 = false;
				
			do
			{
				k++;
				if (k < len) mju[k - 1] = (double)k;
				mjuk =0.0;
				if (inversed)
				{
					for (i = 1; i < len; i++)
						mjuk -= v[len - i - 1] * mju[i - 1];
				}
				else
				{
					for (i = 1; i < len; i++)
						mjuk -= v[i] * mju[i - 1];
				}
				if (mjuk != 0.0)
					stopDig = stopDig || fabs(log10(fabs(mjuk))) > maxLog;
				else
				{
					if (k > mink + len)
						stopDig = true;
				}
				if (len > 1 && !stopDig1 && mju[0] != 0.0)
				{
					rel1 = mjuk / mju[0];
					if (rel1 != 0.0) 
						stopDig1 = stopDig1 || log10(fabs(rel1)) > maxLog;
					if (nonfirst1 && !stopDig1)
					{
						d_rel1 = fabs(rel1 - rel1_old);
						if (d_rel1 != 0.0) 
							stopDig1 = stopDig1 || log10(fabs(d_rel1)) > maxLog;
						if (pastsecond1 && !stopDig1)
						{
							dd_rel1 = fabs(d_rel1_old - d_rel1);
							stop1 = d_rel1 <= depsilon &&  dd_rel1 <= depsilon && k - k1 == 1;
						}
						pastsecond1 = true;
						if (!stopDig1)
							d_rel1_old = d_rel1;

					}
					nonfirst1 = true;
					if (!stopDig1)
						rel1_old = rel1;
					else
						rel1 = rel1_old;
					k1 = k;

				}
				if (len > 2 && k%2 == 0 && !stopDig2 && mju[1] != 0.0 )
				{
					rel2 = mjuk / mju[1];
					if (rel2 != 0.0)
						stopDig2 = stopDig2 || log10(fabs(rel2)) > maxLog;
					if (nonfirst2 && !stopDig2)
					{
						d_rel2 = fabs(rel2 - rel2_old);
						if (d_rel2 != 0.0) 
							stopDig2 = stopDig2 || log10(fabs(d_rel2)) > maxLog;
						if (pastsecond2 && !stopDig2)
						{
							dd_rel2 = fabs(d_rel2_old - d_rel2);
							stop2 = d_rel2 <= depsilon &&  dd_rel2 <= depsilon && k - k2 == 2;
						}
						pastsecond2 = true;
						if (!stopDig2)
							d_rel2_old = d_rel2;

					}
					nonfirst2 = true;
					if (!stopDig2)
						rel2_old = rel2;
					else
						rel2 = rel2_old;
					k2 = k;

				}

				if (len > 2 && !stopDig3)
				{
					Sk = mju[0] * mju[0] - mjuk * mju[1];
					tk = mju[0] * mju[1] - mjuk * mju[2];

					if (Sk != 0.0)
						stopDig3 = stopDig3 || log10(fabs(Sk)) > maxLog;
					if (tk != 0.0)
						stopDig3 = stopDig3 || log10(fabs(tk)) > maxLog;
					if (nonfirst3 && !stopDig3)
					{
						if (Sk_1 != 0.0)
						{
							rel_ro2 = Sk / Sk_1;
							rel_2x = tk / Sk_1;
							
							if (rel_ro2 != 0.0)
								stopDig3 = stopDig3 || log10(fabs(rel_ro2)) > maxLog;
							if (rel_2x != 0.0)
								stopDig3 = stopDig3 || log10(fabs(rel_2x)) > maxLog;
							if (pastsecond3 && !stopDig3)
							{
								d_rel_ro2 = fabs(rel_ro2_old - rel_ro2);
								d_rel_2x = fabs(rel_2x_old - rel_2x);
								if (d_rel_ro2 != 0.0)
									stopDig3 = stopDig3 || log10(fabs(d_rel_ro2)) > maxLog;
								if (d_rel_2x != 0.0)
									stopDig3 = stopDig3 || log10(fabs(d_rel_2x)) > maxLog;
								if (pastthird3 && !stopDig3)
								{
									dd_rel_ro2 = fabs(d_rel_ro2_old - d_rel_ro2);
									dd_rel_2x = fabs(d_rel_2x_old - d_rel_2x);
									stop3 =dd_rel_2x <= depsilon 
										&& d_rel_2x <= depsilon 
										&& dd_rel_ro2 <= depsilon 
										&& d_rel_ro2 <= depsilon
										&& rel_ro2 > 0.0
										&& k - k3 == 1;
								}
								pastthird3 = true;
								if (!stopDig3)
								{
									d_rel_ro2_old = d_rel_ro2;
									d_rel_2x_old = d_rel_2x;
								}
							}
							pastsecond3 = true;
							if (!stopDig3)
							{
								rel_ro2_old = rel_ro2;
								rel_2x_old = rel_2x;
							}
							else
							{
								rel_ro2 = rel_ro2_old;
								rel_2x = rel_2x_old;
							}
						}
					}
					nonfirst3 = true;
					if (!stopDig3)
						Sk_1 = Sk;
					k3 = k;
				}
				mjuk >> mju;
				if (k < len + mink)
				{
					stop1 = false; stop2 = false; stop3 = false;
				}
				stopMaxLoops = k > maxLoops;
				stopDig = stopDig || (stopDig1 && stopDig2 && stopDig3);
				go = !stop1 && !stop2 && !stop3 && !stopDig && !stopMaxLoops;
//		fprintf(stderr, "mjuk=%g,go=%i,st1=%i,st2=%i,st3=%i,k=%i,d_ro2=%g,dd_ro2=%g,ro2=%g\n", mjuk, go, stop1, stop2, stop3, k,d_rel_ro2,dd_rel_ro2,rel_ro2);
		}
			while(go);
//	fprintf(stderr, "mjuk=%g,go=%i,st1=%i,st2=%i,st3=%i,k=%i,d_ro2=%g,dd_ro2=%g,ro2=%g\n", mjuk, go, stop1, stop2, stop3, k,d_rel_ro2,dd_rel_ro2,rel_ro2);
//	fprintf(stderr, " rel1 = %g, rel2 = %g, rel_ro2 = %g, rel_2x = %g\n\n",rel1, rel2, rel_ro2, rel_2x );
//	v.disp();
			if (stop1 || stop2)
			{
				xx = stop2 ? sqrt(fabs(rel2)) : rel1;
				j2 = stop2 ? 2 : 1;
//	j2 = 2;// !!!
				for (j = 0; j < j2; j++)
				{
					if (inversed)
						x = j == 0 ? 1.0 / xx : - 1.0 / xx;
					else
						x = j == 0 ? xx : - xx;

					// Уточнение значения корня методом Ньютона
					this->PolynomNewtonRoot(x);
					// Проверка
					deriv = v.PolynomDerivative();//Коэффициенты полинома производной
					e = fabs(v.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
					if (e < epsilon_control)
					{
						dd[1] = - x;
						solved = conv(solved, dd);
						v.PolynomDivide(dd,quot,rem);
						v=quot;
						dr.push_back(x);
					}
					else
					{
						if(DEBUGGING)
						{
							fprintf(stderr, "Error Bernulli = %g of found real root = %g \n",e, x);
						}
					}
				}
			}
			else
			{
				if (stop3)
				{
					x = rel_2x / 2.0;
					y = sqrt(fabs(rel_ro2 - x * x));
					if (inversed)
					{
						c = x * x + y * y;
						x = x / c;
						y = y / c;
					}
					z.x = x;
					z.y = y;
					// Настройка комплексных корней методом Ньютона
					this->PolynomNewtonRoot(z);
					x = z.x; y = z.y;
					// Проверка
					zf = v.PolynomValue(z);
					deriv = v.PolynomDerivative();//Коэффициенты полинома производной
					zdf = deriv.PolynomValue(z);
					mf = zf.x * zf.x + zf.y * zf.y;
					mdf = zdf.x * zdf.x + zdf.y * zdf.y;
					e = mf / mdf;
					if ( e < epsilon2_control)
					{
						ddd[1] = -2.0 * x; ddd[2] = x * x + y * y;
						v.PolynomDivide(ddd, quot, rem);
						solved = conv(solved,ddd);
						v.PolynomDivide(ddd,quot,rem);
						v = quot;
						cr.push_back(z);
					}
					else
					{
						if(DEBUGGING)
						{
							fprintf(stderr,"Error Bernulli = %g of complex root = %g + i*%g verification\n", e, x, y);
						}
					}
				}

			}
			toSolve = v.m_length > 1 && v.m_length < len;
		}
		while(toSolve);
		unsolved = v;
		unsolvlen = unsolved.m_length;
		if (unsolvlen < 2/* && Find(abs(solved - *this) > depsilon).size == 0*/)
			result = 0;// найдены все корни
		else
		{
			if (unsolvlen < len1)
				result = 1;		// найден по меньшей мере один корень
			if (unsolvlen == len1) // не найден ни один корень
				result = 2;// корни неотделимы и есть указание на комплексные корни
		}
		inversed ^= true;
		if ( (result == 2 && inv > 1) || result == 0)
			toInverse = false;
	}
	while(toInverse);
	unsolved = v;
	unsolvlen = unsolved.m_length;
	if (unsolvlen < 2)
		result = 0;// найдены все корни
	else
	{
		if (unsolvlen < len0)
			result = 1;		// найден по меньшей мере один корень
		if (unsolvlen == len0) // не найден ни один корень
			result = 3;// корни неотделимы и есть указание на комплексные корни
	}
	return result;
}
int vdouble::BernulliMinRealRoot(vdouble& dr, const double& depsilon)
{
	//Вычисляет минимальный по модулю действительный корень действительного полинома методом Бернулли (для полиномов с вычленёнными кратными корнями)
	int result, i, len, len1, len0, k, k1, k2, k3, maxLoops = 100000, mink = 4, j, j2;
	double mjuk, tk, Sk, Sk_1, x, y, xx, e, mf, mdf, c,
		epsilon_control = 1.0e-3,
		epsilon2_control = epsilon_control * epsilon_control,
		rel1, rel1_old, d_rel1, d_rel1_old, dd_rel1,
		rel2, rel2_old, d_rel2, d_rel2_old, dd_rel2,
		rel_ro2, rel_ro2_old, d_rel_ro2, d_rel_ro2_old, dd_rel_ro2,
		rel_2x, rel_2x_old, d_rel_2x, d_rel_2x_old, dd_rel_2x,
		maxLog = 250.0;
	bool nonfirst1, pastsecond1, 
		nonfirst2, pastsecond2, 
		nonfirst3, pastsecond3, pastthird3,
		stop1, stop2, stop3, stopDig,
		stopDig1, stopDig2, stopDig3,isError = false,
		stopMaxLoops, inversed = false, toInverse = true;

	inversed = true;// Proverka
	complex z, zf, zdf;
	vdouble dd(2), ddd(3); dd[0] = 1.0; ddd[0] = 1.0;
	vdouble solved, quot, rem;
	solved = 1.0;
	dr = vdouble(0);
Vector<complex>	cr = Vector<complex>(0);
	vdouble v = *this, mju, deriv;
	Vector<int> inz = Find( v != 0.0);
	v = v[sequence(inz[0], m_length - 1)];
	len0 = v.m_length;
	len1 = v.m_length;
	if (inversed) v = v / v[len1 - 1]; else v = v / v[0];
	bool toSolve, go;
	do
	{
		len = v.m_length;
		deriv = v.PolynomDerivative();
		mju = zeros(len);
		k = 0;
		nonfirst1 = false, pastsecond1 = false, 
		nonfirst2 = false, pastsecond2 = false, 
		nonfirst3 = false, pastsecond3 = false, pastthird3 = false,
		stop1 = false, stop2 = false, stop3 = false, stopDig = false,
		stopDig1 = false, stopDig2 = false, stopDig3 = false;
			
		do
		{
			k++;
			if (k < len) mju[k - 1] = (double)k;
			mjuk =0.0;
			if (inversed)
			{
				for (i = 1; i < len; i++)
					mjuk -= v[len - i - 1] * mju[i - 1];
			}
			else
			{
				for (i = 1; i < len; i++)
					mjuk -= v[i] * mju[i - 1];
			}
			if (mjuk != 0.0)
				stopDig = stopDig || fabs(log10(fabs(mjuk))) > maxLog;
			else
			{
				if (k > mink + len)
					stopDig = true;
			}
			if (len > 1 && !stopDig1 && mju[0] != 0.0)
			{
				rel1 = mjuk / mju[0];
				if (rel1 != 0.0) 
					stopDig1 = stopDig1 || log10(fabs(rel1)) > maxLog;
				if (nonfirst1 && !stopDig1)
				{
					d_rel1 = fabs(rel1 - rel1_old);
					if (d_rel1 != 0.0) 
						stopDig1 = stopDig1 || log10(fabs(d_rel1)) > maxLog;
					if (pastsecond1 && !stopDig1)
					{
						dd_rel1 = fabs(d_rel1_old - d_rel1);
						stop1 = d_rel1 <= depsilon &&  dd_rel1 <= depsilon && k - k1 == 1;
					}
					pastsecond1 = true;
					if (!stopDig1)
						d_rel1_old = d_rel1;
				}
				nonfirst1 = true;
				if (!stopDig1)
					rel1_old = rel1;
				else
					rel1 = rel1_old;
				k1 = k;
			}
			if (len > 2 && k%2 == 0 && !stopDig2 && mju[1] != 0.0 )
			{
				rel2 = mjuk / mju[1];
				if (rel2 != 0.0)
					stopDig2 = stopDig2 || log10(fabs(rel2)) > maxLog;
				if (nonfirst2 && !stopDig2)
				{
					d_rel2 = fabs(rel2 - rel2_old);
					if (d_rel2 != 0.0) 
						stopDig2 = stopDig2 || log10(fabs(d_rel2)) > maxLog;
					if (pastsecond2 && !stopDig2)
					{
						dd_rel2 = fabs(d_rel2_old - d_rel2);
						stop2 = d_rel2 <= depsilon &&  dd_rel2 <= depsilon && k - k2 == 2;
					}
					pastsecond2 = true;
					if (!stopDig2)
						d_rel2_old = d_rel2;
				}
				nonfirst2 = true;
				if (!stopDig2)
					rel2_old = rel2;
				else
					rel2 = rel2_old;
				k2 = k;
			}
			if (len > 2 && !stopDig3)
			{
				Sk = mju[0] * mju[0] - mjuk * mju[1];
				tk = mju[0] * mju[1] - mjuk * mju[2];
				if (Sk != 0.0)
					stopDig3 = stopDig3 || log10(fabs(Sk)) > maxLog;
				if (tk != 0.0)
					stopDig3 = stopDig3 || log10(fabs(tk)) > maxLog;
				if (nonfirst3 && !stopDig3)
				{
					if (Sk_1 != 0.0)
					{
						rel_ro2 = Sk / Sk_1;
						rel_2x = tk / Sk_1;
						
						if (rel_ro2 != 0.0)
							stopDig3 = stopDig3 || log10(fabs(rel_ro2)) > maxLog;
						if (rel_2x != 0.0)
							stopDig3 = stopDig3 || log10(fabs(rel_2x)) > maxLog;
						if (pastsecond3 && !stopDig3)
						{
							d_rel_ro2 = fabs(rel_ro2_old - rel_ro2);
							d_rel_2x = fabs(rel_2x_old - rel_2x);
							if (d_rel_ro2 != 0.0)
								stopDig3 = stopDig3 || log10(fabs(d_rel_ro2)) > maxLog;
							if (d_rel_2x != 0.0)
								stopDig3 = stopDig3 || log10(fabs(d_rel_2x)) > maxLog;
							if (pastthird3 && !stopDig3)
							{
								dd_rel_ro2 = fabs(d_rel_ro2_old - d_rel_ro2);
								dd_rel_2x = fabs(d_rel_2x_old - d_rel_2x);
								stop3 =dd_rel_2x <= depsilon 
									&& d_rel_2x <= depsilon 
									&& dd_rel_ro2 <= depsilon 
									&& d_rel_ro2 <= depsilon
									&& rel_ro2 > 0.0
									&& k - k3 == 1;
							}
							pastthird3 = true;
							if (!stopDig3)
							{
								d_rel_ro2_old = d_rel_ro2;
								d_rel_2x_old = d_rel_2x;
							}
						}
						pastsecond3 = true;
						if (!stopDig3)
						{
							rel_ro2_old = rel_ro2;
							rel_2x_old = rel_2x;
						}
						else
						{
							rel_ro2 = rel_ro2_old;
							rel_2x = rel_2x_old;
						}
					}
				}
				nonfirst3 = true;
				if (!stopDig3)
					Sk_1 = Sk;
				k3 = k;
			}
			mjuk >> mju;
			if (k < len + mink)
			{
				stop1 = false; stop2 = false; stop3 = false;
			}
			stopMaxLoops = k > maxLoops;
			stopDig = stopDig || (stopDig1 && stopDig2 && stopDig3);
			go = !stop1 && !stop2 && !stop3 && !stopDig && !stopMaxLoops;
		}
		while(go);

		if (stop1 || stop2)
		{
			xx = stop2 ? sqrt(fabs(rel2)) : rel1;
			j2 = stop2 ? 2 : 1;

			for (j = 0; j < j2; j++)
			{
				if (inversed)
					x = j == 0 ? 1.0 / xx : - 1.0 / xx;
				else
					x = j == 0 ? xx : - xx;
				// Уточнение значения корня методом Ньютона
				this->PolynomNewtonRoot(x);
				// Проверка
				deriv = v.PolynomDerivative();//Коэффициенты полинома производной
				e = fabs(v.PolynomValue(x)) / fabs(deriv.PolynomValue(x));
				if (e < epsilon_control)
				{
					dd[1] = - x;
					solved = conv(solved, dd);
					v.PolynomDivide(dd,quot,rem);
					v=quot;
					dr.push_back(x);
				}
				else
				{
					isError = true;
					if(DEBUGGING)
					{
						fprintf(stderr, "Error Bernulli = %g of found real root = %g \n",e, x);
					}
				}
			}
		}
		else
		{
			if (stop3)
			{
				x = rel_2x / 2.0;
				y = sqrt(fabs(rel_ro2 - x * x));
				if (inversed)
				{
					c = x * x + y * y;
					x = x / c;
					y = y / c;
				}
				z.x = x;
				z.y = y;
				// Настройка комплексных корней методом Ньютона
				this->PolynomNewtonRoot(z);
				x = z.x; y = z.y;
				// Проверка
				zf = v.PolynomValue(z);
				deriv = v.PolynomDerivative();//Коэффициенты полинома производной
				zdf = deriv.PolynomValue(z);
				mf = zf.x * zf.x + zf.y * zf.y;
				mdf = zdf.x * zdf.x + zdf.y * zdf.y;
				e = mf / mdf;
				if ( e < epsilon2_control)
				{
					ddd[1] = -2.0 * x; ddd[2] = x * x + y * y;
					v.PolynomDivide(ddd, quot, rem);
					solved = conv(solved,ddd);
					v.PolynomDivide(ddd,quot,rem);
					v = quot;
					cr.push_back(z);
				}
				else
				{
					isError = true;
					if(DEBUGGING)
					{
						fprintf(stderr,"Error Bernulli = %g of complex root = %g + i*%g verification\n", e, x, y);
					}
				}
			}
			else
				isError = true;
		}
		toSolve = dr.m_length < 1 && !isError;
	}
	while(toSolve);
	if (dr.m_length < 1)
		result = -1;
	else
		result = 0;// найден корень
	return result;
}
int vdouble::PolynomNewtonRoot(complex& z, const double& epsilon)
{
	int maxLoops = 100,
		q = 0;
	double x, y, xd, yd, xdz, ydz, md, min_md, mf, mf0;
	complex zn, fz, fdz;
	vdouble deriv = PolynomDerivative();// Коэффициенты полинома производной
	zn = z;// текущее значение корня
	double depsilon = epsilon * epsilon;
	
	fz = PolynomValue(zn);// текущее значение функции
	fdz = deriv.PolynomValue(zn);// текущее значение производной
	x = fz.x; y = fz.y; xd = fdz.x; yd = fdz.y;
	md = xd * xd + yd * yd; // квадрат модуля производной
	min_md = md;// минимум квадрата модуля производной
	mf0 = x * x + y * y;// Начальное значение квадрата модуля функции
	bool go = true;
	do
	{
		q++;
		// Деление значения функции на значение производной
		xdz = ( x * xd + y * yd) / md;
		ydz = ( xd * y - x * yd) / md;
		// Поправка значения корня
		if (fabs(xdz) >= fabs(zn.x))
		{
			do
			{
				xdz /= 10;
			}
			while (fabs(xdz) >= fabs(zn.x));
		}
		if (fabs(ydz) >= fabs(zn.y))
		{
			do
			{
				ydz /= 10;
			}
			while (fabs(ydz) >= fabs(zn.y));
		}
		zn.x -= xdz; zn.y -= ydz;

		fz = PolynomValue(zn);// текущее значение функции
		fdz = deriv.PolynomValue(zn);// текущее значение производной
		x = fz.x; y = fz.y; xd = fdz.x; yd = fdz.y;
		md = xd * xd + yd * yd; // квадрат модуля производной
		min_md = min_md < md ? min_md : md;// минимум квадрата модуля производной
		mf = x * x + y * y;// квадрат модуля значения функции
	}
	while(mf / min_md > depsilon && q < maxLoops && go);
	int result;
	if (mf0 >= mf && mf / min_md <= depsilon)
	{
		z = zn;	//уточнение значения корня в случае 
		result = 0;  // Успеха выполнения функции
	}
	else
	{
		if (mf0 >= mf && mf / min_md > depsilon)
		{
			z = zn;	//уточнение значения корня в случае 
			result = 1;  // Успеха выполнения функции, 
						// но всё же заданная точность не достигнута
		}
	}
	if (mf0 < mf)
	{
		result = -1; // Неудача 
	}
//	fprintf(stderr, " mf0 = %g, mf = %g,e = %g, q = %i\n", mf0, mf, sqrt(mf / min_md), q);
	return result;
}
int vdouble::TranscendentNewtonRoot(double& x, double k, vdouble& v, const double& epsilon)
{
	// имеем трансцендентное уравнение
	// this->PolynomValue(x) * exp(k * x) + v.PolynomValue(x) = 0.0;
	int maxLoops = 1000,
		q = 0;
	double md, min_md, mf, mf0, xn, fx, fdx, dxn;
	vdouble deriv1 = PolynomDerivative();// Коэффициенты полинома производной
	vdouble deriv2 = v.PolynomDerivative();// Коэффициенты полинома производной
	xn = x;// текущее значение корня

	fx = PolynomValue(xn) * exp(k * xn) + v.PolynomValue(xn);// текущее значение функции
	fdx = (PolynomValue(xn) * k + 
		deriv1.PolynomValue(xn)) * exp(k * xn) + 
		deriv2.PolynomValue(xn);// текущее значение производной
	md = fabs(fdx); // модуль производной
	min_md = md;// минимум модуля производной
	mf0 = fabs(fx);// модуль значения функции
	do
	{
//		if(q%50==0)
//fprintf(stderr," x = %g, fx = %g, fdx = %g, q = %i\n\n", xn,fx, fdx, q);
		q++;
		// Деление значения функции на значение производной
		// Поправка значения корня
		dxn = fx / fdx;
		if (fabs(dxn) >= fabs(xn))
		{
			do
			{
				dxn /= 10;
			}
			while (fabs(dxn) >= fabs(xn));
		}
		xn -= dxn;
		fx = PolynomValue(xn) * exp(k * xn) + v.PolynomValue(xn);// текущее значение функции
		fdx = (PolynomValue(xn) * k + 
			deriv1.PolynomValue(xn)) * exp(k * xn) + 
			deriv2.PolynomValue(xn);// текущее значение производной
//if (fabs(fdx)<0.1)
//fprintf(stderr,"fdx = (%g + %g) * %g + %g\n",PolynomValue(xn) * k, deriv1.PolynomValue(xn), exp(k * xn), deriv2.PolynomValue(xn));
		md = fabs(fdx); // модуль производной
		min_md = min_md < md ? min_md : md;// минимум модуля производной
		mf = fabs(fx);// модуль значения функции
	}
	while(mf / min_md > epsilon && q < maxLoops);
	int result;
	if (mf0 >= mf && mf / min_md <= epsilon)
	{
		x = xn;	//уточнение значения корня в случае 
		result = 0; // Успеха выполнения функции
	}
	else
	{
		if (mf0 >= mf && mf / min_md > epsilon)
		{
			x = xn;	//уточнение значения корня в случае 
			result = 1; // Успеха выполнения функции, 
						// но всё же заданная точность не достигнута

		}
	}
	if (mf0 < mf)
	{
		result = -1; // Неудача 
	}
//	fprintf(stderr, " mf0 = %g, mf = %g,e = %g, q = %i\n", mf0, mf, mf / min_md,q);
	return result;
}
int vdouble::PolynomNewtonRoot(double& dr, const double& epsilon)
{
	int maxLoops = 100,
		q = 0;
	double md, min_md, mf, mf0, xn, fx, fdx, dxn;
	vdouble deriv = PolynomDerivative();// Коэффициенты полинома производной
	xn = dr;// текущее значение корня

	fx = PolynomValue(xn);// текущее значение функции
	fdx = deriv.PolynomValue(xn);// текущее значение производной
	md = fabs(fdx); // модуль производной
	min_md = md;// минимум модуля производной
	mf0 = fabs(fx);// модуль значения функции
	do
	{
		q++;
		// Деление значения функции на значение производной
		// Поправка значения корня
		dxn = fx / fdx;
		if (fabs(dxn) >= fabs(xn))
		{
			do
			{
				dxn /= 10;
			}
			while (fabs(dxn) >= fabs(xn));
		}
		xn -= dxn;
		fx = PolynomValue(xn);// текущее значение функции
		fdx = deriv.PolynomValue(xn);// текущее значение производной

		md = fabs(fdx); // модуль производной
		min_md = min_md < md ? min_md : md;// минимум модуля производной
		mf = fabs(fx);// модуль значения функции
	}
	while(mf / min_md > epsilon && q < maxLoops);
	int result;
	if (mf0 >= mf && mf / min_md <= epsilon)
	{
		dr = xn;	//уточнение значения корня в случае 
		result = 0; // Успеха выполнения функции
	}
	else
	{
		if (mf0 >= mf && mf / min_md > epsilon)
		{
			dr = xn;	//уточнение значения корня в случае 
			result = 1; // Успеха выполнения функции, 
						// но всё же заданная точность не достигнута

		}
	}
	if (mf0 < mf)
	{
		result = -1; // Неудача 
	}
//	fprintf(stderr, " mf0 = %g, mf = %g,e = %g, q = %i\n", mf0, mf, mf / min_md,q);
	return result;
}
int vdouble::PolynomLinaThree_memberDivider(double& p, double& q)
{
	// нахождение квадратичного делителя заданного многочлена методом Лина
	vdouble v, qu, r, d1, d2, deriv;
	vdouble d0 = vdouble(3); d0[0] = 1.0; d0[1] = p; d0[2] = q;
	Vector<int> inz;
	v = *this;
	inz = Find(v != 0.0);
	v = v[sequence(inz[0], m_length - 1)];

	if (3 >= v.m_length)
	{
		fprintf (stderr, " Error of length in PolynomLinaThree_memberDivider() \n d0.m_length = %i, v.m_length = %i\n", d0.m_length, v.m_length);
		return -1;
	}
	double x0, y0, x1, y1, x2, y2, D0, D1, D2, c, x_2, y_2, ex, ey, mf, mdf, e, 
		epsilon = 1.0e-8, epsilon2 = epsilon * epsilon;
	complex z0, z1, z2, z_2, dz, chisl, znam, zf, zdf ;
	D0 = p * p - 4.0 * q;
	bool go;
	int k = 0;
	do
	{
		k++;
		go = k < 1000;

		vdouble d0_0 = vdouble::append(d0, 0.0);
		v.PolynomDivide( d0_0, qu, r);

		d1 = r / r[0];
		D1 = d1[1] * d1[1] - 4.0 * d1[2];

		vdouble d1_0 = vdouble::append(d1, 0.0);
		v.PolynomDivide( d1_0, qu, r); d2 = r / r[0];

		D2 = d2[1] * d2[1] - 4.0 * d2[2];
		if (D0 < 0 && D1 < 0 && D2 < 0)
		{
			z0.x = - d0[1] / 2.0; z0.y = sqrt(fabs(D0)) / 2.0;
			z1.x = - d1[1] / 2.0; z1.y = sqrt(fabs(D1)) / 2.0;
			z2.x = - d2[1] / 2.0; z2.y = sqrt(fabs(D2)) / 2.0;

			// дельта-квадрат Процесс Эйткена для улучшения сходимости
			// z_2 = z2 - (z2 - z1)^2 / (z0 + z2 - 2*z1);
			znam.x = z0.x + z2.x - 2.0 * z1.x;
			znam.y = z0.y + z2.y - 2.0 * z1.y;

			dz.x = z2.x - z1.x; dz.y = z2.y - z1.y;

			chisl.x = dz.x * dz.x - dz.y * dz.y;
			chisl.y = 2.0 * dz.x * dz.y;

			c = znam.x * znam.x + znam.y * znam.y;

			z_2.x = z2.x + (znam.x * chisl.x + znam.y * chisl.y) / c;
			z_2.y = z2.y + (znam.x * chisl.y - chisl.x * znam.y) / c;

			// Проверка
			zf = v.PolynomValue(z_2);
			deriv = v.PolynomDerivative();//Коэффициенты полинома производной
			zdf = deriv.PolynomValue(z_2);
			mf = zf.x * zf.x + zf.y * zf.y;
			mdf = zdf.x * zdf.x + zdf.y * zdf.y;
			e = mf / mdf;
			if ( e < epsilon2)
			{
				p = - 2.0 * z_2.x;
				q = z_2.x * z_2.x + z_2.y * z_2.y;
				return 0;
			}
			else
			{
				d0 = d2; D0 = D2;
			}
		}
		else
		{
			if (D0 >= 0 && D1 >= 0 && D2 >= 0)
			{
				x0 = (- d0[1] + sqrt(D0)) / 2.0; 
				y0 = (- d0[1] - sqrt(D0)) / 2.0; 
				x1 = (- d1[1] + sqrt(D1)) / 2.0; 
				y1 = (- d1[1] - sqrt(D1)) / 2.0; 
				x2 = (- d2[1] + sqrt(D2)) / 2.0; 
				y2 = (- d2[1] - sqrt(D2)) / 2.0; 
				
				// дельта-квадрат Процесс Эйткена для улучшения сходимости
				x_2 = x2 - (x2 - x1) * (x2 - x1) / (x0 + x2 - 2*x1);
				y_2 = y2 - (y2 - y1) * (y2 - y1) / (y0 + y2 - 2*y1);
				// Verification
				deriv = v.PolynomDerivative();//Коэффициенты полинома производной
				ex = fabs(v.PolynomValue(x_2)) / fabs(deriv.PolynomValue(x_2));
				ey = fabs(v.PolynomValue(y_2)) / fabs(deriv.PolynomValue(y_2));
				if ( ex < epsilon && ey < epsilon )
				{
					p = - x_2 - y_2;
					q = x_2 * y_2;
					return 0;
				}
				else
				{
					d0 = d2; D0 = D2;
				}

			}
			else
			{
				// Смесь комплексных и действительных квадратичных делителей 
				// Процесс Эйткена применять нельзя
				d0 = d2; D0 = D2;
			}
		}

	}
	while (go);
	return 1;
}
int vdouble::PolynomLinaDivider(vdouble& d)
{
	// нахождение делителя любой степени заданного многочлена методом Лина
	vdouble v, q, r, d0, d1, dd;
	Vector<int> inz;
	v = *this;
	inz = Find(v != 0.0);
	v = v[sequence(inz[0], m_length - 1)];
	inz = Find(d != 0.0);
	d0 = d[sequence(inz[0], d.m_length - 1)];
	d0 = d0 / d0[0];
	if (d0.m_length >= v.m_length)
	{
		fprintf (stderr, " Error of length in PolynomLinaDivider()\n");
		return -1;
	}
	double e,
		epsilon = 1.0e-8;
	bool go;
	int k = 0;
	do
	{
		k++;
		go = k < 1000;

		vdouble d0_0 = vdouble::append(d0, 0.0);
		v.PolynomDivide( d0_0, q, r); d1 = r / r[0];

		dd = (d1 - d0);
		e = sqrt(dd.SquareSum());
		if ( e < epsilon )
		{
			d = d1;
			return 0;
		}
		else
		{
			d0 = d1;
		}
	}
	while (go);
	return 1;
}

double vdouble::MaxAbsRoots()
{
	double A, a, R;
	A = fabs(*(pD + 1));
	for (int i = 2; i < m_length; i++)
	{
		a = fabs(*(pD + i));
		A = A > a ? A : a;
	}
	R = 1.0 + A / (fabs(*pD));
	return R;
}
double vdouble::MinAbsRoots()
{
	double B, b, r;
	B = fabs(*pD);
	for ( int i = 1; i < m_length - 1; i++)
	{
		b = fabs( *(pD + i));
		B = B > b ? B : b;
	}
	r = 1.0 / ( 1.0 + B / fabs( *(pD + m_length - 1)) );
	return r;
}


vdouble vdouble::vLagerPolynom(int n)
{
	vdouble v = vdouble(n+1);
	switch(n)
	{
	case 0: 
		v[0] = 1.0;
		break;
	case 1: 
		v[0] = - 2.0; v[1] = 1.0;
		break;
	case 2: 
		v[0] = 2.0; v[1] = - 4.0; v[2] = 1.0;
		break;
	}
	return v;
}

double vdouble::LagerAlphaDeterm(int maxOrder, double tend, double EnergyPart)
{
	// Функция аналитически вычисляет значение альфа, 
	// удовлетворяющее условию, что на участке от нуля 
	// до верхнего предела интегрирования tend умещается 
	// EnergyPart от суммарной энергии полинома 
	// максимального порядка maxOrder, вычисленной с весом
	double alpha, dn, cn, bn;
	int q;
	Vector<vdouble> vLag(3);
	vdouble vrek(2);
	int n, order;
	for (q = 0; q < 3; q++)
	{
		// полиномиальные коэффициенты полинома Лагерра
		vLag[q] = vLagerPolynom(q);
		alpha = vLag[q].LagerAlphaDeterminition(tend, EnergyPart);
/*
		// разлагаем экспоненту в степенной ряд
	//	N = vIntLen + 10; // степень полинома разложения экспоненты
		c = vdouble(N);
		m = 1.0; // Коэффициент перед экспонентой
		f = 1.0;
		j = 0; //порядок производной
		for (i = N - 1; i >= 0 ; i--)
		{
			c[i] = m / f;// Коэффициент интерполирующего полинома
			m *= -2.0 * tend; // Умножение на коэффициент внутри экспоненты
			j++;
			f *= (double)j;
		}
//fprintf(stderr, "c2 = ");
//c.disp();

*/
	}
	n = 2;
	order = 1;
	while (order < maxOrder)
	{
		order++;
		for (q = 0; q < 2; q++)
		{
			n++;
			dn = (double)n;
			bn = ((double)(2*n-1)) / dn;
			cn = ((double)(n-1)) / dn;
			vrek[0] = -2.0 / dn;; vrek[1] = bn;
			// рекурентное вычисление полиномиальных коэффициентов полинома Лагерра
			vLag[0] = vLag[1]; vLag[1] = vLag[2];
			vLag[2] = conv(vLag[1], vrek).PolynomSumming( - cn * vLag[0]);
			// вычисление поправки интегрирования от tend до бесконечности
			alpha = vLag[2].LagerAlphaDeterminition(tend,EnergyPart);
		}
	}
	return alpha;
}

vdouble dsequence(double d0, double dstep, double dend)
{
	long Len = (int)floor((dend - d0) / dstep)+1;
	vdouble seq = vdouble(Len);
	double *p;
	p = seq.pD;
	for (int i = 0; i< Len; i++)
		*(p + i) = d0 + i * dstep;
	return seq;
}

vdouble dsequence(double d0, long Len, double dend)
{
	double dstep = (dend - d0) / (Len - 1);
	vdouble seq = vdouble(Len);
	double *p;
	p = seq.pD;
	for (int i = 0; i< Len; i++)
		*(p + i) = d0 + i * dstep;
	return seq;
}
vdouble dsequence(double d0, double dstep, long Len)
{
	vdouble seq = vdouble(Len);
	double *p;
	p = seq.pD;
	for (int i = 0; i< Len; i++)
		*(p + i) = d0 + i * dstep;
	return seq;
}



#if 0
double vdouble::FirstLocalMaxFrom(int j)
{
	if (j < 0 || j >= m_length)
	{
		CString errstr;
		errstr.Format(" m_length = %i index = %i", m_length, j);
		AfxMessageBox("Error using vdouble::FirstLocalMaxFrom(int j):\n (j < 0 || j >= m_length)\n" + errstr);
		AfxThrowUserException();
	}
	double Max = *(pD + j);
	int i = j + 1;
	while (i < m_length && *(pD + i) >= Max)
	{
		Max = *(pD + i);
		i++;
	}
	return Max;
}

double vdouble::FirstLocalMinFrom(int j)
{
	if (j < 0 || j >= m_length)
	{
		CString errstr;
		errstr.Format(" m_length = %i index = %i", m_length, j);
		AfxMessageBox("Error using vdouble::FirstLocalMinFrom(int j):\n (j < 0 || j >= m_length)\n" + errstr);
		AfxThrowUserException();
	}
	double Min = *(pD + j);
	int i = j + 1;
	while (i < m_length && *(pD + i) <= Min)
	{
		Min = *(pD + i);
		i++;
	}
	return Min;
}
double vdouble::MinFrom(int j)
{
	if (j < 0 || j >= m_length)
	{
		CString errstr;
		errstr.Format(" m_length = %i index = %i", m_length, j);
		AfxMessageBox("Error using vdouble::MinFrom(int j):\n (j < 0 || j >= m_length)\n" + errstr);
		AfxThrowUserException();
	}
	double Min = *(pD + j);
	int i = j + 1;
	while (i < m_length)
	{
		Min = *(pD + i) < Min ? *(pD + i) : Min;
		i++;
	}
	return Min;
}
double vdouble::MaxFrom(int j)
{
	if (j < 0 || j >= m_length)
	{
		CString errstr;
		errstr.Format(" m_length = %i index = %i", m_length, j);
		AfxMessageBox("Error using vdouble::MinFrom(int j):\n (j < 0 || j >= m_length)\n" + errstr);
		AfxThrowUserException();
	}
	double Max = *(pD + j);
	int i = j + 1;
	while (i < m_length)
	{
		Max = *(pD + i) > Max ? *(pD + i) : Max;
		i++;
	}
	return Max;
}
#endif
void vdouble::Rand(double minBorder, double maxBorder)
{
	for (int i = 0; i< m_length; i++)
		*(pD + i) = minBorder + (((double)rand()) / RAND_MAX) * (maxBorder - minBorder);
}
#if 0
int vdouble::b_reconstructor(vdouble& b, vdouble& tt, vdouble& xx, double t0)
{
	// реконструкция коэффициентов числителя передаточной функции 
	// по  известному знаменателю (*this)  
	// а также по отклику на delta - импульс в момент t0
	int Len = tt.m_length;
	if (xx.m_length != tt.m_length)
	{
		CString strerr;
		strerr.Format("Еrror during vdouble::b_reconstructor: \n (xx.m_length (%i) != tt.m_length (%i))", 
			xx.m_length, tt.m_length);
		AfxMessageBox(strerr);
		AfxThrowUserException();
	}
	// При вычислении обратного преобразования Лапласа достаточно вічислить корни знаменателя только один раз
	// vdouble numerator = *this;
	int result = 0, 
		b_len = m_length - 1,
		res, 
		i;
	double xD_, yD_, mD_, xN, yN, xk, yk, x, y, *pM, *pM_ord;
	vdouble droots_den, // Действительные корни знаменателя 
		deriv_den,  // и производная его
		f_reconstr; // реконструкция сигнала
	Vector<complex> croots_den; //Комплексные корни знаменателя
	deriv_den = this->PolynomDerivative(); //производная знаменателя
	// ============== Roots of denominator ==========================
	Vector<int> order_dr, order_cr;
	res = this->roots(droots_den, croots_den,order_dr, order_cr);
	// ==============================================================
	if (res < 0) 
	{
		return -1;
	}
	if (res > 0) 
	{
		return 1;
	}
	if (Find(order_dr > 1).size > 0)
		return 2;
	if (Find(order_cr > 1).size > 0)
		return 3;
	vdouble M, 
		numerator, 
		t = tt - t0;
	M.resize(Len,b_len); pM = M.pD;

	// ============================================================
	for ( int ord = 0; ord < b_len; ord++)
	{
		numerator.resize(b_len, 0.0);
		numerator[ord] = 1.0;
		f_reconstr.resize(Len, 0.0); // реконструируемый сигнал
		//суммируем оригиналы от комплексных корней
		for (i = 0; i < croots_den.size; i++)
		{
			complex N, D_, z; // комплексное значение числителя и производной знаменателя
			// комплексный корень
			x = croots_den[i].x;
			y = croots_den[i].y;
			z.x = x;
			z.y = y;
			// Вычисление коэффициента перед экспонентой
			N = numerator.PolynomValue(z);// Значение числителя в корне
			D_ = deriv_den.PolynomValue(z);// Значение производной знаменателя в корне
			// Деление значения числителя на значение производной знаменателя
			xD_ = D_.x; yD_ = D_.y;
			mD_ = xD_ * xD_ + yD_ * yD_;
			xN = N.x;
			yN = N.y;

			xk = (xN * xD_ + yN * yD_) / mD_;
			yk = (xD_ * yN - xN * yD_) / mD_;

			// ================= exp ============

			// ex = exp (x * t);
			// xe = ex * cos( y * t);
			// ye = ex * sin( y * t);
			// xf = xk * xe - yk * ye;
			f_reconstr += 2.0 * (xk * cos(y * t) - yk * sin(y * t)) * exp(x * t);
		}
		//суммируем оригиналы от действительных корней
		for (i = 0; i < droots_den.m_length; i++)
		{
			double N, D_; // действительное значение числителя и производной знаменателя
			// комплексный корень
			x = droots_den[i];
			// Вычисление коэффициента перед экспонентой
			N = numerator.PolynomValue(x);// Значение числителя в корне
			D_ = deriv_den.PolynomValue(x);// Значение производной знаменателя в корне
			// Деление значения числителя на значение производной знаменателя
			xk = N / D_;
			// ================= exp ============
			f_reconstr += xk * exp(x * t);
		}
		pM_ord = pM + ord;
		for (int i = 0; i < Len; i++)
			*(pM_ord + i * b_len)  = f_reconstr[i];
//			M(i, ord) = f_reconstr[i];
	}
	b = M.Tichonov(xx);
	return 0;


}
#endif
//DEL int vdouble::dwt(vdouble& t, vdouble& tsd,
//DEL 				 vdouble &dh, vdouble &dg, 
//DEL 				 vdouble &s, vdouble &d)
//DEL {
//DEL 	if (m_length != t.m_length)
//DEL 	{
//DEL 		char str[255];
//DEL 		sprintf(str, "Error using vdouble::dwt()\n"
//DEL 			"m_length(%i) != t.m_length(%i)",
//DEL 			m_length, t.m_length);
//DEL 		MessageBox(0, str, "vdouble::dwt 1", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	int len_h = dh.m_length,
//DEL 		len_s_right = 1,
//DEL 		len_s = m_length/2 - len_h/2 + 1;
//DEL 	if (len_h != dg.m_length)
//DEL 	{
//DEL 		char str[255];
//DEL 		sprintf(str, "Error using vdouble::dwt():\nlen_h(%i) != dg.m_length(%i)", 
//DEL 			len_h,dg.m_length);
//DEL 		MessageBox(0, str, "vdouble::dwt", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	if (len_s < 0)
//DEL 	{
//DEL 		char s[1024];
//DEL 		sprintf(s, "Error using vdouble::dwt():\nlen_s(%i) < 0\n Выберите меньший уровень разложения", 
//DEL 			len_s);
//DEL 		MessageBox(0, s, "vdouble::dwt", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	double 
//DEL 		*ps, *pd, *ptsd, *pt,
//DEL 		*ph, *pg;
//DEL 
//DEL 	tsd.resize(len_s);
//DEL 	s.resize(len_s, 0.0);
//DEL 	d.resize(len_s, 0.0);
//DEL 
//DEL 	ph = dh.pD; 
//DEL 	pg = dg.pD;
//DEL 	pt = t.pD;
//DEL 	ptsd = tsd.pD + len_s - 1;
//DEL 	ps = s.pD + len_s - 1;
//DEL 	pd = d.pD + len_s - 1;
//DEL 
//DEL 	int ind, i, j/*, k ,
//DEL 		ind0 = m_length%2 */ ;
//DEL 	// центральные коэффициенты
//DEL 	for (i = m_length - 1; i >= len_h-1; i -= 2)// && k >= 0
//DEL 	{
//DEL 		*ptsd = *(pt + i - len_h + 1);
//DEL 		ind = i;// индекс сигнала, используемый в операции свёртки
//DEL 		for (j = len_h - 1; j >= 0; j--)// индекс элемента вейвлет фильтра
//DEL 		{
//DEL 			if (ind < 0)
//DEL 			{
//DEL 				*ps  += *(ph + j) * *pD;
//DEL 				*pd  += *(pg + j) * *pD;
//DEL 			}
//DEL 			else
//DEL 			{
//DEL 				if (ind < m_length)
//DEL 				{
//DEL 					*ps  += *(ph + j) * *(pD + ind);
//DEL 					*pd  += *(pg + j) * *(pD + ind);
//DEL 				}
//DEL 				else
//DEL 				{
//DEL 					*ps  += *(ph + j) * *(pD + m_length - 1);
//DEL 					*pd  += *(pg + j) * *(pD + m_length - 1);
//DEL 				}
//DEL 			}
//DEL 			ind--;
//DEL 		}
//DEL 		ps--;pd--;ptsd--;
//DEL 	}
//DEL 	// ===========
//DEL 	//   test tsd
//DEL 	// ===========
//DEL 	for (i = 0; i < tsd.Length(); i++)
//DEL 	{
//DEL 		if ( i == 0)
//DEL 		{
//DEL 		}
//DEL 		else
//DEL 		{
//DEL 			if (tsd[i] > tsd[i-1])
//DEL 			{
//DEL 			}
//DEL 			else
//DEL 			{
//DEL 				char str[255];
//DEL 				sprintf(str, "i = %d tsd[i] (%f) !> tsd[i-1] (%f)",i,  tsd[i],  tsd[i-1]);
//DEL 				MessageBox(0, str, "dwt 1 test tsd", 0);
//DEL 			}
//DEL 		}
//DEL 
//DEL 	}
//DEL 	// ===========
//DEL 	//   test tsd
//DEL 	// ===========
//DEL 	return 1;
//DEL }

int vdouble::dwt(Vector<int>& t, Vector<int>& tsd,
				 vdouble &dh, 
				 vdouble &s)
{
	if (m_length != t.Size())
	{
		TCHAR str[255];
		stprintf_s(str, 255, _T("Error using vdouble::dwt()\n")
			_T("m_length(%i) != t.Size(%i)"),
			m_length, t.Size());
		MessageBox(0, str, _T("vdouble::dwt 2"), 0);
		return 0;
	}
	int len_h = dh.m_length,
		//len_s_right = 1,
		// длина разложения определяется 
		// сколько раз фильтр может полностью 
		// уложиться на сигнале со сдвигом 2 
		len_s = (m_length - len_h)/2 + 1;

	if (len_s < 0)
	{
		TCHAR s[1024];
		stprintf_s(s, 1024, _T("Error using vdouble::dwt():\nlen_s(%i) < 0\n Выберите меньший уровень разложения"), 
			len_s);
		MessageBox(0, s, _T("vdouble::dwt 2"), 0);
		return 0;
	}
	double 
		*ps, 
		*ph;
	// выделяем память под коэффициенты 
	// и их временные отметки 
	// и обнуляем коэффициенты
	tsd.resize(len_s);
	s.resize(len_s, 0.0);
	int
		*pt,
		*ptsd;

	ph = dh.pD; 
	pt = t.data;
	// устанавливаем динамические указатели 
	// на конец вектора коэффициентов и их временных отметок
	ptsd = tsd.data + len_s - 1;
	ps = s.pD + len_s - 1;

	int ind, i, j/*, k ,*/
		// если при укладке фильтра на сигнале 
		// остаётся один элемент, то мы это должны учесть.
		//ind0 = (m_length - len_h)%2
		;
	// центральные коэффициенты
	for (i = m_length - 1; i >= len_h-1; i -= 2)// движемся по сигналу с конца на начало с шагом 2
	{
		// временная привязка вейвлет коэффициента - к началу фильтра ?
		*ptsd = *(pt + i - len_h + 1);
		ind = i;// индекс сигнала, используемый в операции свёртки
		for (j = len_h - 1; j >= 0; j--)// индекс элемента вейвлет фильтра
		{
			// производим свёртку фильтра с сигналом
			if (ind < 0)
			{
				// на всякий случай если индекс выйдет за пределы
				*ps  += *(ph + j) * *pD;
			}
			else
			{
				if (ind < m_length)
				{
					// основная точка свёртки
					*ps  += *(ph + j) * *(pD + ind);
				}
				else
				{
					// на всякий случай если индекс выйдет за пределы
					*ps  += *(ph + j) * *(pD + m_length - 1);
				}
			}
			ind--;
		}
		ps--;ptsd--;
	}
	// ===========
	//   test tsd
	// ===========
	for (i = 0; i < tsd.Size(); i++)
	{
		if ( i == 0)
		{
		}
		else
		{
			if (tsd[i] > tsd[i-1])
			{
			}
			else
			{
				TCHAR str[255];
				stprintf_s(str, 255, _T("i = %d tsd[i] (%d) !> tsd[i-1] (%d)"), i,  tsd[i],  tsd[i-1]);
				MessageBox(0, str, _T("dwt 2 test tsd"), 0);
			}
		}

	}
	// ===========
	//   test ts
	// ===========
	return 1;
}


//DEL int vdouble::dwt(vdouble& t,
//DEL 		 int left_h2, int right_h2, vdouble &dh,  
//DEL 		 int left_g2, int right_g2, vdouble &dg, 
//DEL 		 vdouble& ts, vdouble &s, 
//DEL 		 vdouble& td, vdouble &d)
//DEL {
//DEL 	if (m_length != t.m_length)
//DEL 	{
//DEL 		char str[200];
//DEL 		wsprintf(str,"Error using vdouble::dwt()\n"
//DEL 			"m_length(%i) != t.m_length(%i)",
//DEL 			m_length, t.m_length);
//DEL 		MessageBox(0,str, "dwt 3",0);
//DEL 		return 0;
//DEL 	}
//DEL 	int len_h = dh.m_length,
//DEL 		len_s = m_length/2 - len_h/2 + 1 + left_h2 + right_h2,
//DEL 		len_d = m_length/2 - len_h/2 + 1 + left_g2 + right_g2;
//DEL 	if (len_h != dg.m_length)
//DEL 	{
//DEL 		char s[200];
//DEL 		wsprintf(s,"Error using vdouble::dwt():\nlen_h(%i) != dg.m_length(%i)", 
//DEL 			len_h,dg.m_length);
//DEL 		MessageBox(0,s, "dwt 3", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	if (len_s < 0)
//DEL 	{
//DEL 		char s[200];
//DEL 		wsprintf(s,"Error using vdouble::dwt():\nlen_s(%i) < 0\n Выберите меньший уровень разложения", 
//DEL 			len_s);
//DEL 		MessageBox(0,s, "dwt 3", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	double 
//DEL 		*ps, *pd, *pts, *ptd, *pt,
//DEL 		*ph, *pg;
//DEL 	double dt = t.DiffVector().Min();
//DEL 
//DEL 	ts.resize(len_s);
//DEL 	td.resize(len_d);
//DEL 	s.resize(len_s, 0.0);
//DEL 	d.resize(len_d, 0.0);
//DEL 
//DEL 
//DEL 	ph = dh.pD; 
//DEL 	pg = dg.pD;
//DEL 	pt = t.pD;
//DEL 	pts = ts.pD + len_s - 1;
//DEL 	ptd = td.pD + len_d - 1;
//DEL 	ps = s.pD + len_s - 1;
//DEL 	pd = d.pD + len_d - 1;
//DEL 
//DEL 	int ind, i, j, it;
//DEL 	for (i = m_length-1+2*right_h2; i >= len_h-1-2*left_h2; i -= 2)
//DEL 	{
//DEL 		it = i - len_h + 1;
//DEL 		if (it < 0)
//DEL 			*pts = *pt + dt*it;
//DEL 		else
//DEL 		{
//DEL 			if (it < m_length)
//DEL 				*pts = *(pt + it);
//DEL 			else
//DEL 				*pts = *(pt - 1 + m_length) + dt*(it-m_length+1);
//DEL 		}
//DEL 		ind = i;// индекс сигнала, используемый в операции свёртки
//DEL 		for (j = len_h - 1; j >= 0; j--)// индекс элемента вейвлет фильтра
//DEL 		{
//DEL 			if (ind < 0)
//DEL 				*ps  += *(ph + j) * *pD;
//DEL 			else
//DEL 			{
//DEL 				if (ind < m_length)
//DEL 					*ps  += *(ph + j) * *(pD + ind);
//DEL 				else
//DEL 					*ps  += *(ph + j) * *(pD + m_length - 1);
//DEL 			}
//DEL 			ind--;
//DEL 		}
//DEL 		ps--; pts--;
//DEL 	}
//DEL 
//DEL 	for (i = m_length-1+2*right_g2; i >= len_h-1-2*left_g2; i -= 2)// && k >= 0
//DEL 	{
//DEL 		it = i - len_h + 1;
//DEL 		if (it < 0)
//DEL 			*ptd = *pt + dt*it;
//DEL 		else
//DEL 		{
//DEL 			if (it < m_length)
//DEL 				*ptd = *(pt + it);
//DEL 			else
//DEL 				*ptd = *(pt - 1 + m_length) + dt*(it-m_length+1);
//DEL 		}
//DEL 		ind = i;// индекс сигнала, используемый в операции свёртки
//DEL 		for (j = len_h - 1; j >= 0; j--)// индекс элемента вейвлет фильтра
//DEL 		{
//DEL 			if (ind < 0)
//DEL 				*pd  += *(pg + j) * *pD;
//DEL 			else
//DEL 			{
//DEL 				if (ind < m_length)
//DEL 					*pd  += *(pg + j) * *(pD + ind);
//DEL 				else
//DEL 					*pd  += *(pg + j) * *(pD + m_length - 1);
//DEL 			}
//DEL 			ind--;
//DEL 		}
//DEL 		pd--; ptd--;
//DEL 	}
//DEL 	// ===========
//DEL 	//   test ts
//DEL 	// ===========
//DEL 	for (i = 0; i < ts.Length(); i++)
//DEL 	{
//DEL 		if ( i == 0)
//DEL 		{
//DEL 		}
//DEL 		else
//DEL 		{
//DEL 			if (ts[i] > ts[i-1])
//DEL 			{
//DEL 			}
//DEL 			else
//DEL 			{
//DEL 				char str[255];
//DEL 				sprintf(str, "i = %d ts[i] (%f) !> ts[i-1] (%f)",i,  ts[i],  ts[i-1]);
//DEL 				MessageBox(0, str, "dwt 3 test ts", 0);
//DEL 			}
//DEL 		}
//DEL 
//DEL 	}
//DEL 	// ===========
//DEL 	//   test ts
//DEL 	// ===========
//DEL 	// ===========
//DEL 	//   test td
//DEL 	// ===========
//DEL 	for (i = 0; i < td.Length(); i++)
//DEL 	{
//DEL 		if ( i == 0)
//DEL 		{
//DEL 		}
//DEL 		else
//DEL 		{
//DEL 			if (td[i] > td[i-1])
//DEL 			{
//DEL 			}
//DEL 			else
//DEL 			{
//DEL 				char str[255];
//DEL 				sprintf(str, "i = %d td[i] (%f) !>  td[i-1] (%f)",i,  td[i],   td[i-1]);
//DEL 				MessageBox(0, str, "dwt 3 test td", 0);
//DEL 			}
//DEL 		}
//DEL 
//DEL 	}
//DEL 	// ===========
//DEL 	//   test ts
//DEL 	// ===========
//DEL 	return 1;
//DEL }



int vdouble::dwt(int J,
				 Vector<int>& t,
		 int left_h, int right_h, vdouble &dh,  
		 Vector<int>& ts, vdouble &s)
{
	if (m_length != t.Size())
	{
		TCHAR str[S_LEN];
		stprintf_s(str, S_LEN, _T("Error using vdouble::dwt()\n")
			_T("m_length(%i) != t.Size(%i)"),
			m_length, t.Size());
		MessageBox(0,str, _T("dwt 4"),0);
		return 0;
	}
	int len_h = dh.m_length;

	// конечный индекс сигнала, используемый на первом шаге свёртки
	// его нужно задать так чтобы нулевой элемент фильтра 
	// при движении фильтра влево (с шагом два) 
	// совпал с начальным индексом сигнала
	int i0 = 
		m_length - 1	// от индекс крайнего правого элемента сигнала
		+ right_h		// сдвигаем фильтр вправо на величину правого хвоста
						
		+ ((abs(len_h-right_h)%2) ^ (m_length%2));	// 
												// сдвигаем фильтр на единицу вправо 
												// если:
												// 1){длина сигнала нечётна}
												// XOR (исключающее или
												// 2)(len_s-right_h) - это рабочая часть фильтра 
												// в правом положении. 
												// Если она нечётна

												// если оба чётны или оба нечётны, тогда не сдвигаем фильтр
		

	int istop = len_h-1-left_h;
/*
	printf("((abs(len_h-right_h)_2) ^ (m_length_2)) = %d\n", ((abs(len_h-right_h)%2) ^ (m_length%2)));

	printf("dwt:\nm_length = %d right_h = %d len_s = %d i0 = %d \n", m_length, right_h, len_s, i0);
	printf("istop = %d len_h = %d left_h = %d\n", istop, len_h, left_h);
*/
	int
#if 0
		// длина разложения определяется 
		// сколько раз фильтр без левого и правого хвоста может полностью 
		// уложиться на сигнале со сдвигом 2 
		len_s = (m_length - len_h + left_h + right_h)/2 + 1 ;
#else
		len_s = (i0-istop+2)/2;
#endif

	if (len_s <= 0)
	{
		TCHAR s[S_LEN];
		stprintf_s(s, S_LEN, _T("Error using vdouble::dwt():\nlen_s(%i) < 0\n Выберите меньший уровень разложения"), 
			len_s);
		MessageBox(0,s, _T("dwt 4"), 0);
		return 0;
	}
	double 
		*ps,
		*ph;

	int
		*pts,  
		*pt;

	// выделяем память под коэффициенты 
	// и их временные отметки 
	// и обнуляем коэффициенты
	ts.resize(len_s);
	s.resize(len_s, 0.0);

	int dt_ind = int(pow(2.0,J));

	printf("dt_ind = %d\n", dt_ind );


	ph	= dh.pD; 
	pt	= t.data;
	// устанавливаем динамические указатели 
	// на конец вектора коэффициентов и их временных отметок
	pts = ts.data + len_s - 1;
	ps	= s.pD + len_s - 1;

	int ind, i, j, it;


	// движемся по сигналу с конца на начало с шагом 2
	for (i = i0; i >= istop; i -= 2)
	{
		// временная привязка вейвлет коэффициента - к началу фильтра ?
		// нет!!!
		// временной индекс вейвлет коэффициента должен быть 
		// равен нулю, в том элементарном шаге свёртки, когда
		// нулевой индекс фильтра находится напротив 
		// нулевого индекса сигнала
		// 
		// это индекс временной шкалы
		it = i - len_h + 1;

		if (it < 0)
		{
			
			*pts = *pt + it*dt_ind;

			//printf("(it(%d) < 0)\n", it);
			//printf("*pts(%d) = *pt(%d) + it(%d)*dt_ind(%d);\n", *pts, *pt, it, dt_ind);
		}
		else
		{
			if (it < m_length)
			{
				*pts = *(pt + it);
				
				//printf("*pts(%d) = *pt(%d) + it(%d);\n", *pts, *pt, it);
			}
			else
			{
				*pts = *(pt - 1 + m_length) + (it-m_length+1)*dt_ind;


				//printf("*pts(%d) = *(pt(%d) - 1 + m_length(%d)) + (it(%d)-m_length(%d)+1)*dt_ind(%d);\n", 
				//	*pts, *pt, m_length, it, m_length, dt_ind);
			}
		}

		ind = i;// индекс сигнала, используемый в операции свёртки
		for (j = len_h - 1; j >= 0; j--)// индекс элемента вейвлет фильтра
		{
			if (ind < 0)
				*ps  += *(ph + j) * *pD;
			else
			{
				if (ind < m_length)
					*ps  += *(ph + j) * *(pD + ind);
				else
					*ps  += *(ph + j) * *(pD + m_length - 1);
			}
			ind--;
		}
		ps--; pts--;
	}
	// ===========
	//   test ts
	// ===========
	for (i = 0; i < ts.Size(); i++)
	{
		if ( i == 0 )
		{
		}
		else
		{
			if (ts[i] > ts[i-1])
			{
			}
			else
			{

				/*for (int ii = 0; ii < ts.Size(); ii++)
					printf("%d ", ts[ii]);
				printf("\n");*/
				TCHAR str[255];
				stprintf_s(str, 255, _T("J = %d\ni = %d ts[i] (%d) !> ts[i-1] (%d)"),J, i,  ts[i],  ts[i-1]);
				MessageBox(0, str, _T("dwt 4 test ts"), 0);
			}
		}

	}
	// ===========
	//   test ts
	// ===========

	return 1;
}
#define TEST_IDWT 1
int vdouble::idwt(int J,
				  Vector<int>&  new_t, int left, int right,
				  vdouble &rh,Vector<int>& ts, 
				  vdouble &s, bool isLow)
{
	int len_h = rh.m_length,
		len_s = s.m_length;

	if (len_s != ts.Size())
	{
		TCHAR s[S_LEN];
		stprintf_s(s, S_LEN, _T("Error using vdouble::idwt():\nlen_s(%i) != ts.Size(%i)"), 
			len_s, ts.Size());
		MessageBox(0,s,_T(""), 0);
		return -1;
	}
	int len1_2 = len_s - len_h/2
#if TEST_IDWT
		- len_h%2 
#endif
		+ 1,
		ind, j;

	if (len1_2+(left+right)/2 < 0)
	{
		TCHAR s[S_LEN];
		stprintf_s(s, S_LEN, _T("Error using vdouble::idwt():\nlen_s - len_h/2- len_h%%2+1+(left+right)/2(%d) < 0\n Выберите меньший уровень разложения"), 
			len1_2+(left+right)/2);
		MessageBox(0,s,_T(""),0);
		return 0;
	}
#if 1
	this->resize(2 * (len1_2+(left+right)/2), 0.0);
	new_t.resize(2 * (len1_2+(left+right)/2));
#else
	this->resize(2 * (len1_2+left/2+right/2), 0.0);
	new_t.resize(2 * (len1_2+left/2+right/2));
#endif

	double *ps, *ph,  *p, sk;
	int *pts, *pnewt;


	ph = rh.pD; 
	ps = s.pD;
	pts = ts.data;

	int dt_ind = int(pow(2.0,J));

#if 1
	pnewt = new_t.data + 2*(right/2);
	p = pD + 2*(right/2);

	// 2*k+1+2*(right/2) < m_length
	int max2k = m_length - 1 - 2*(right/2);

int i = 0;
	for (int k = -right/2; 2*k < max2k; k++)
	{
		int it = k + len_h/2 - 1;

		if (it < 0)
		{
			*(pnewt+2*k) = *pts + 2*it*dt_ind;
		}
		else
		{
			if (it < len_s)
			{
				*(pnewt+2*k) = *(pts + it);
			}
			else
			{
				*(pnewt+2*k) = *(pts - 1 + len_s) + 2*(it-len_s+1)*dt_ind;
			}
		}
		*(pnewt+2*k+1) = *(pnewt+2*k) + dt_ind;

		ind = k;
#if TEST_IDWT		
		for ( j = len_h - 1; j > 0; j-=2)
#else
		for ( j = len_h - 2; j>= 0; j-=2)
#endif
		{
			if (ind < 0)
			{
				sk = isLow? *ps : 0;
			}
			else
			{
				if (ind < len_s)
				{
					sk = *(ps + ind);
				}
				else
				{
					sk = isLow? *(ps+len_s-1) : 0;
				}
			}

			if (2*k+2*(right/2) < 0)
				MessageBox(0,_T("2*k+right < 0"),_T(""),0);

			if (2*k+2*(right/2)+1 >= m_length)
			{
				TCHAR str[255];
				stprintf_s(str, 255, _T("2*k(%d)+2*right(%d)/2+1(%d) >= m_length(%d)"),k,right,2*k+2*(right/2)+1, m_length);
				MessageBox(0,str,_T(""),0);
			}

#if TEST_IDWT		
			*(p+2*k) += 2*( *(ph+j-1) * sk);
			*(p+2*k+1) += 2*(*(ph+j) * sk);
#else
			*(p+2*k) += 2*( *(ph+j) * sk);
			*(p+2*k+1) += 2*(*(ph+j+1) * sk);
#endif
			ind ++;
		}		
#if TEST_IDWT		
		if (j == 0)
			*(p + 2 * k) += 2 * (*(ph) * sk);
#endif
	}
#else
	pnewt = new_t.pD;
	p = pD;

	for (int k = -right1_2; k < len1_2+left1_2; k++)
	{
		int it = k + (len_hg-2)/2;
		if (it < 0)
			*pnewt = *pt + dt*it;
		else
		{
			if (it < len_sd)
				*pnewt = *(pt + it);
			else
				*pnewt = *(pt - 1 + len_sd) + 2*dt*(it-len_sd+1);
		}
		*(pnewt+1) = *pnewt + dt;
		pnewt++;pnewt++;

		ind = k;
		for ( j = len_hg - 2; j>= 0; j-=2)
		{
			if (ind < 0)
			{
				sk_or_dk = isLow? *psd : 0;
			}
			else
			{
				if (ind < len_s)
				{
					sk_or_dk = *(psd + ind);
				}
				else
				{
					sk_or_dk = isLow? *(psd+len_sd-1) : 0;
				}
			}

			*p += 2*( *(phg+j) * sk_or_dk); p++;
			*p += 2*(*(phg+j+1) * sk_or_dk); p++;
			ind ++;
		}
		
	}
#endif
	// ===========
	// test new_t
	// ===========
	for ( i = 0; i < new_t.Size(); i++)
	{
		if ( i == 0)
		{
		}
		else
		{
			if (new_t[i] > new_t[i-1])
			{
			}
			else
			{
				TCHAR str[255];
				stprintf_s(str, 255, _T("J = %d\ni = %d new_t[i] (%d) !> new_t[i-1] (%d)"),J, i, new_t[i],  new_t[i-1]);
				MessageBox(0, str, _T("idwt 1"), 0);
			}
		}

	}
	// ===========
	// end of test
	// ===========
	return 1;
}

#if 0
int vdouble::idwt_(
				  int left, int right,
				  vdouble &rh, 
				  vdouble &s)
{
	int len_h = rh.m_length,
		len_s = s.m_length;


	int len1_2 = len_s - len_h/2
#if TEST_IDWT
		- len_h%2 
#endif
		+ 1,
		ind, j;

	if (len1_2+(left+right)/2 < 0)
	{
		char s[S_LEN];
		sprintf_s(s, S_LEN, "Error using vdouble::idwt():\len_s - len_h/2- len_h\%2+1+(left+right)/2(%d) < 0\n Выберите меньший уровень разложения", 
			len1_2+(left+right)/2);
		MessageBox(0,s,"",0);
		return 0;
	}
#if 1
	this->resize(2 * (len1_2+(left+right)/2), 0.0);
#else
	this->resize(2 * (len1_2+left/2+right/2), 0.0);
#endif

	double *ps, *ph,  *p, sk;


	ph = rh.pD; 
	ps = s.pD;

	p = pD + 2*(right/2);

	// 2*k+1+2*(right/2) < m_length
	int max2k = m_length - 1 - 2*(right/2);

	for (int k = -right/2; 2*k < max2k; k++)
	{
		ind = k;
#if TEST_IDWT		
		for ( j = len_h - 1; j > 0; j-=2)
#else
		for ( j = len_h - 2; j>= 0; j-=2)
#endif
		{
			if (ind < 0)
			{
				//printf("ind(%d) < 0 ", ind);
				sk = 0.0;
			}
			else
			{
				if (ind < len_s)
				{
					sk = *(ps + ind);
				}
				else
				{
					//printf("ind(%d) >= len_s(%d) ", ind, len_s);
					sk = 0.0;
				}
			}
/*
			if (2*k+2*(right/2) < 0)
				MessageBox(0,"2*k+right < 0","",0);

			if (2*k+2*(right/2)+1 >= m_length)
			{
				char str[255];
				sprintf(str, "2*k(%d)+2*right(%d)/2+1(%d) >= m_length(%d)",k,right,2*k+2*(right/2)+1, m_length);
				MessageBox(0,str,"",0);
			}*/

#if TEST_IDWT		
			*(p+2*k) += 2*( *(ph+j-1) * sk);
			*(p+2*k+1) += 2*(*(ph+j) * sk);
#else
			*(p+2*k) += 2*( *(ph+j) * sk);
			*(p+2*k+1) += 2*(*(ph+j+1) * sk);
#endif
			ind ++;
		}		
#if TEST_IDWT		
		if (j == 0)
			*(p + 2 * k) += 2 * (*(ph) * sk);
#endif
	}
	return 1;
}

#endif
int vdouble::idwt(
				  int left, int right,
				  vdouble &rh, 
				  vdouble &s)
{
	int len_h = rh.m_length,
		len_s = s.m_length;

	int len1_2 = len_s - len_h/2
		- len_h%2 
		+ 1,
		ind, j;

	if (len1_2+(left+right)/2 < 0)
	{
		TCHAR s[S_LEN];
		stprintf_s(s, S_LEN, _T("Error using vdouble::idwt():\nlen_s - len_h/2- len_h%%2+1+(left+right)/2(%d) < 0\n Выберите меньший уровень разложения"), 
			len1_2+(left+right)/2);
		MessageBox(0,s,_T(""),0);
		return 0;
	}
	this->resize(2 * (len1_2+(left+right)/2), 0.0);

	double *ps, *ph,  *p, sk;

	ph = rh.pD; 
	ps = s.pD;

	p = pD + 2*(right/2);

	// 2*k+1+2*(right/2) < m_length
	int max2k = m_length - 1 - 2*(right/2);

	for (int k = -right/2; 2*k < max2k; k++)
	{
		ind = k;
		for ( j = len_h - 1; j > 0; j-=2)
		{
			if (ind < 0)
			{
				sk = 0.0;
			}
			else
			{
				if (ind < len_s)
				{
					sk = *(ps + ind);
				}
				else
				{
					sk = 0.0;
				}
			}

			*(p+2*k) += 2*( *(ph+j-1) * sk);
			*(p+2*k+1) += 2*(*(ph+j) * sk);
			ind ++;
		}		
		if (j == 0)
			*(p + 2 * k) += 2 * (*(ph) * sk);
	}
	return 1;
}

//DEL int vdouble::idwt(vdouble& ts, vdouble& td, vdouble&  tau, vdouble &rh, vdouble &rg, vdouble &s, vdouble &d)
//DEL 
//DEL {
//DEL 	int len_h = rh.m_length,
//DEL 		len_s = s.m_length,
//DEL 		len_d = d.m_length;
//DEL 	if (len_h != rg.m_length)
//DEL 	{
//DEL 		char s[255];
//DEL 		sprintf(s,"Error using vdouble::idwt():\nlen_h(%i) != rg.m_length(%i)", 
//DEL 			len_h,rg.m_length);
//DEL 		MessageBox(0, s, "vdouble::idwt", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	if (len_s != d.m_length)
//DEL 	{
//DEL 		char s[255];
//DEL 		sprintf(s,"Error using vdouble::idwt():\nlen_s(%i) != d.m_length(%i)", 
//DEL 			len_s,d.m_length);
//DEL 		MessageBox(0, s, "vdouble::idwt", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	if (len_s != ts.m_length)
//DEL 	{
//DEL 		char s[255];
//DEL 		sprintf(s,"Error using vdouble::idwt():\nlen_s(%i) != ts.m_length(%i)", 
//DEL 			len_s,ts.m_length);
//DEL 		MessageBox(0, s, "vdouble::idwt", 0);
//DEL 		return 0;
//DEL 
//DEL 	}
//DEL 	if (len_d != td.m_length)
//DEL 	{
//DEL 		char s[255];
//DEL 		sprintf(s,"Error using vdouble::idwt():\nlen_d(%i) != td.m_length(%i)", 
//DEL 			len_d,td.m_length);
//DEL 		MessageBox(0, s, "vdouble::idwt", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	if (len_s < len_h/2)
//DEL 	{
//DEL 		char s[255];
//DEL 		sprintf(s,"Error using vdouble::idwt():\nlen_s(%i) < len_h/2(%i)\n Выберите меньший уровень разложения", 
//DEL 			len_s, len_h/2);
//DEL 		MessageBox(0, s, "vdouble::idwt", 0);
//DEL 		return 0;
//DEL 	}
//DEL 	int len1_2 = len_s - len_h/2 - len_h%2 + 1,
//DEL 		ind, j;
//DEL 
//DEL 	this->resize(2 * (len1_2), 0.0);
//DEL 	tau.resize(2 * (len1_2));
//DEL 
//DEL 	double *ps,	*pd, *ph, *pg, *pts, *ptd, *ptau, *p;
//DEL 	double dt = ts.DiffVector().MinPositive() / 2.0;
//DEL 
//DEL 	ph = rh.pD; 
//DEL 	pg = rg.pD;
//DEL 	ps = s.pD;
//DEL 	pd = d.pD;
//DEL 	pts = ts.pD;
//DEL 	ptd = td.pD;
//DEL 	ptau = tau.pD;
//DEL 	p = pD;
//DEL 
//DEL #if 1
//DEL 	for (int k = 0; k < len1_2; k++)
//DEL 	{
//DEL 		*(ptau + 2 * k) = *(pts + k + (len_h-2)/2);
//DEL 		*(ptau + 2 * k + 1) = *(ptau + 2 * k) + dt;
//DEL /*		*(ptau + 2 * k + 1) = (
//DEL 			*(pt + k   + (len_h-2)/2) + 
//DEL 			*(pt + k+1 + (len_h-2)/2))/2.0;*/
//DEL 		ind = 0;
//DEL 		for ( j = len_h - 2; j>= 0; j-=2)
//DEL 		{
//DEL 			*(pD + 2 * k) += 2 *
//DEL 				(*(ph + j) * *(ps + k + ind) +
//DEL 				 *(pg + j) * *(pd + k + ind));
//DEL 			*(pD + 2 * k + 1) += 2 *
//DEL 				(*(ph + j + 1) * *(ps + k + ind) +
//DEL 				 *(pg + j + 1) * *(pd + k + ind));
//DEL 			ind ++;
//DEL 		}
//DEL 		
//DEL 	}
//DEL #else
//DEL 	for (int k = 0; k < len1_2; k++)
//DEL 	{
//DEL 		*(ptau) = *(pt + k + (len_h-2)/2);
//DEL 		*(++ptau) = *(ptau) + dt;++ptau;
//DEL 		ind = k;
//DEL 		for ( j = len_h - 2; j>= 0; j-=2)
//DEL 		{
//DEL 			*(p++) += 2 *
//DEL 				(*(ph + j) * *(ps + ind) +
//DEL 				 *(pg + j) * *(pd + ind));
//DEL 			*(p++) += 2 *
//DEL 				(*(ph + j + 1) * *(ps + ind) +
//DEL 				 *(pg + j + 1) * *(pd + ind));
//DEL 			ind ++;
//DEL 		}
//DEL 		
//DEL 	}
//DEL #endif
//DEL 	// ===========
//DEL 	// test tau
//DEL 	// ===========
//DEL 	for (int i = 0; i < tau.Length(); i++)
//DEL 	{
//DEL 		if ( i == 0)
//DEL 		{
//DEL 		}
//DEL 		else
//DEL 		{
//DEL 			if (tau[i] > tau[i-1])
//DEL 			{
//DEL 			}
//DEL 			else
//DEL 			{
//DEL 				char str[255];
//DEL 				sprintf(str, "i = %d tau[i] (%f) !> tau[i-1] (%f)", i, tau[i],  tau[i-1]);
//DEL 				MessageBox(0, str, "idwt 2", 0);
//DEL 			}
//DEL 		}
//DEL 
//DEL 	}
//DEL 	// ===========
//DEL 	// end of test
//DEL 	// ===========
//DEL 	return 1;
//DEL }

int vdouble::idwt(int J, Vector<int>& ts, Vector<int>&  tau, vdouble &rh, vdouble &s)

{
	int len_h = rh.m_length,
		len_s = s.m_length;

	if (len_s != ts.size)
	{
		TCHAR s[255];
		stprintf_s(s, 255,_T("Error using vdouble::idwt():\nlen_s(%i) != ts.size(%i)"), 
			len_s,ts.size);
		MessageBox(0, s, _T("vdouble::idwt"), 0);
		return 0;

	}

	if (len_s < len_h/2)
	{
		TCHAR s[255];
		stprintf_s(s, 255, _T("Error using vdouble::idwt():\nlen_s(%i) < len_h/2(%i)\n Выберите меньший уровень разложения"), 
			len_s, len_h/2);
		MessageBox(0, s, _T("vdouble::idwt"), 0);
		return 0;
	}
	// половина длины реконструкции
	int len1_2 = len_s - len_h/2
#if TEST_IDWT
		- len_h%2 
#endif
		+ 1,
		ind, j;

	this->resize(2 * (len1_2), 0.0);
	tau.resize(2 * (len1_2));

	double *ps,	*ph,  *p;
	int *pts,  *ptau;

	ph = rh.pD; 
	ps = s.pD;
	pts = ts.data;
	ptau = tau.data;
	p = pD;
	int dt_ind = int(pow(2.0,J));

#if 1
	for (int k = 0; k < len1_2; k++)
	{
		*(ptau + 2 * k) = *(pts + k + (len_h-2)/2);
		*(ptau + 2 * k + 1) = *(ptau + 2 * k) + dt_ind;
		ind = 0;
#if TEST_IDWT		
		for ( j = len_h - 1; j > 0; j-=2)
		{
			*(pD + 2 * k)     += 2 * (*(ph + j - 1)     * *(ps + k + ind));
			*(pD + 2 * k + 1) += 2 * (*(ph + j )        * *(ps + k + ind));
			ind ++;
		}
		if (j == 0)
			*(pD + 2 * k)     += 2 * (*(ph)     * *(ps + k + ind));
#else
		for ( j = len_h - 2; j>= 0; j-=2)
		{
			*(pD + 2 * k)     += 2 * (*(ph + j)     * *(ps + k + ind));
			*(pD + 2 * k + 1) += 2 * (*(ph + j + 1) * *(ps + k + ind));
			ind ++;
		}
#endif
	}
#else
	for (int k = 0; k < len1_2; k++)
	{
		*(ptau) = *(pt + k + (len_h-2)/2);
		*(++ptau) = *(ptau) + dt;++ptau;
		ind = k;
		for ( j = len_h - 2; j>= 0; j-=2)
		{
			*(p++) += 2 *
				(*(ph + j) * *(ps + ind) +
				 *(pg + j) * *(pd + ind));
			*(p++) += 2 *
				(*(ph + j + 1) * *(ps + ind) +
				 *(pg + j + 1) * *(pd + ind));
			ind ++;
		}
		
	}
#endif
	// ===========
	// test tau
	// ===========
	for (int i = 0; i < tau.Size(); i++)
	{
		if ( i == 0)
		{
		}
		else
		{
			if (tau[i] > tau[i-1])
			{
			}
			else
			{
				TCHAR str[255];
				stprintf_s(str, 255, _T("i = %d tau[i] (%d) !> tau[i-1] (%d)"), i, tau[i],  tau[i-1]);
				MessageBox(0, str, _T("idwt 3"), 0);
			}
		}

	}
	// ===========
	// end of test
	// ===========
	return 1;
}

//%******************VITALY N. PASYUGA**********************
//%***************LAST REVISION 22.10.2001*******************
/*
#define WF_HAAR							1
#define WF_DAUBECHIES					2
#define WF_SYMLETS						3
#define WF_COIFLETS						4
#define WF_BIORTOGONAL					5
#define WF_MY_BIORTOGONAL				6
#define WF_BIORTOGONAL_NONSTANDART		7
#define WF_DISCRETE_MEYER				8
*/


/*
int vdouble::WaveletDecomposition(
	  int wf, // флаг вейвлета
	  int order, // порядок вейвлета
	  int& maxLevel, // максимальный уровенть разложения
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<vdouble>& vs) // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
{
WriteRaporto((CString)"WaveletDecomposition()\n");

	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;
	vdouble dh, dg, rh, rg,	d, s;

	WaveletFilters(wf,order,
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);
	int len_h = dh.Length();
WriteRaporto((CString)"WaveletDecomposition(WaveletFilters)\n");

int left = len_h/2+2;
	maxLevel = 0;
	while (m_length/(int)pow(2.0, (double)(maxLevel+2)) > left)
		maxLevel++;

	vd.resize(maxLevel);
	vs.resize(maxLevel);

	vdouble d0,// обнулённые в центре d- коэффициентов, необходимые для восстановления высокочастотной составляющей сигнала на каждом уровне декомпозиции
		d1;// обнулённые с хвостов d- коэффициентов, необходимые для восстановления низкочастотной составляющей сигнала, отделённой на каждом уровне декомпозиции
	vdouble s0;
	// Производим декомпозицию сигнала - получаем s- и d- коэффициенты
	// на каждом уровне разложения
WriteRaporto((CString)"WaveletDecomposition(resize)\n");
	vdouble current = *this;
WriteRaporto((CString)"WaveletDecomposition(*this)\n");
	for(int j = 0; j < maxLevel; j++)
	{
		current.dwt(j, dh,dg,vs[j],vd[j]);
		current = vs[j];
WriteRaporto((CString)"WaveletDecomposition(current.dwt)\n");
	}
WriteRaporto((CString)"WaveletDecomposition({})\n");
	return 0;
}
*/

int vdouble::WaveletDecomposition(vdouble* pt,
	  int wf, // флаг вейвлета
	  int order, // порядок вейвлета
	  int orderBiorthogonalDecomposition, // порядок вейвлета
	  int maxLevel, // максимальный уровенть разложения
	  Vector<Vector<int> >& vtau_s_ind, 
	  Vector<vdouble>& vtau_s,
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_d_ind, 
	  Vector<vdouble>& vtau_d,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_S_ind, 
	  Vector<vdouble>& vtau_S,
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<Vector<int> >& vtau_F_ind,
	  Vector<vdouble>& vtau_F,
	  Vector<vdouble>& vFast) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
{
	int i, j;
	if (pt && m_length != pt->m_length)
	{
		TCHAR str[255];
		stprintf_s(str, 255, _T("Error using vdouble::WaveletDecomposition()\n")
			_T("m_length(%i) != pt->m_length(%i)"),
			m_length, pt->m_length);
		MessageBox(0,str,_T("WaveletDecomposition"),0);
		return 0;
	}

	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;

	vdouble dh, dg, rh, rg,	d, s;

	WaveletFilters(wf,order,orderBiorthogonalDecomposition,
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);
	int len_h = dh.Length();
	
	//==========================================
	Vector<int> t_ind;
	t_ind.resize(this->m_length);
	for (i = 0; i < t_ind.Size(); i++)
	{
		t_ind[i] = i;
	}
	//==========================================

	vtau_s_ind.resize(maxLevel); 
	vtau_d_ind.resize(maxLevel); 
	vtau_S_ind.resize(maxLevel); 
	vtau_F_ind.resize(maxLevel);
	//==========================================

	vtau_s.resize(maxLevel);
	vs.resize(maxLevel);
	vtau_d.resize(maxLevel);
	vd.resize(maxLevel);

	vtau_S.resize(maxLevel);
	vSlow.resize(maxLevel);
	vtau_F.resize(maxLevel);
	vFast.resize(maxLevel);

	vdouble v0_s, v0_d;
	// Производим декомпозицию сигнала - получаем s- и d- коэффициенты
	// на каждом уровне разложения
	vdouble 
		* current;
	Vector<int>	
		* current_t_ind;
	current = this,
	current_t_ind = &t_ind;
	for(int j = 0; j < maxLevel; j++)
	{
		// этот вариант предусмотрен для случая биортогональных фильтров 
		// у которых длина высокочастотного и низкочастотного фильтра наравная
		if(!current->dwt(*current_t_ind, vtau_s_ind[j], dh,vs[j]))
			return 0;
		if(!current->dwt(*current_t_ind, vtau_d_ind[j], dg,vd[j]))
			return 0;

		current = &vs[j];
		current_t_ind = &vtau_s_ind[j];

		//==========================================
		if (pt)
		{
			vtau_s[j].resize(vtau_s_ind[j].Size());
			for (i = 0; i < vtau_s_ind[j].Size();  i++)
			{
				int ind = vtau_s_ind[j][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_s[j][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_s[j][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_s[j][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
			vtau_d[j].resize(vtau_d_ind[j].Size());
			for ( i = 0; i < vtau_d_ind[j].Size();  i++)
			{
				int ind = vtau_d_ind[j][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_d[j][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_d[j][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_d[j][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
		}
	}
	// Производим восстановление низкочастотных и высокочастотных составляющих сигнала на каждом уровне разложения
	for (int J = maxLevel - 1; J >= 0; J--)
	{
		vdouble 
			current_s = vs[J],
			current_d = vd[J];
		Vector<int>
			* current_ts_ind,
			* current_td_ind;
		current_ts_ind = &vtau_s_ind[J],
		current_td_ind = &vtau_d_ind[J];

		Vector <int> vnewtau_S_ind, vnewtau_F_ind;
		for (j = J; j >= 0; j--)
		{
			vSlow[J].idwt(j, *current_ts_ind, vnewtau_S_ind, rh, current_s);
			current_s = vSlow[J];
			vtau_S_ind[J] = vnewtau_S_ind;
			current_ts_ind = &vtau_S_ind[J];

			if ( j == J)
			{
				if(!vFast[J].idwt(j, *current_td_ind, vnewtau_F_ind, rg, current_d))
					return 0;
				current_d = vFast[J];
			}
			else
			{
				if(!vFast[J].idwt(j, *current_td_ind, vnewtau_F_ind, rh, current_d))
					return 0;
				current_d = vFast[J];
			}
			vtau_F_ind[J] = vnewtau_F_ind;
			current_td_ind = &vtau_F_ind[J];
		}
		if (pt)
		{
			//==========================================
			vtau_S[J].resize(vtau_S_ind[J].Size());
			for (i = 0; i < vtau_S_ind[J].Size();  i++)
			{
				int ind = vtau_S_ind[J][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_S[J][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_S[J][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_S[J][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
			vtau_F[J].resize(vtau_F_ind[J].Size());
			for ( i = 0; i < vtau_F_ind[J].Size();  i++)
			{
				int ind = vtau_F_ind[J][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_F[J][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_F[J][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_F[J][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
		}
	}

	return 1;
}

int vdouble::WaveletDecomposition(vdouble* pt,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int left_h,
	  int right_h,
	  int left_g,
	  int right_g,
	  int maxLevel, // максимальный уровенть разложения
	  Vector<Vector<int> >& vtau_s_ind, 
	  Vector<vdouble>& vtau_s,
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_d_ind, 
	  Vector<vdouble>& vtau_d,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_S_ind, 
	  Vector<vdouble>& vtau_S,
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<Vector<int> >& vtau_F_ind,
	  Vector<vdouble>& vtau_F,
	  Vector<vdouble>& vFast) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
{
	int i, j;
	if (pt && m_length != pt->m_length)
	{
		TCHAR str[S_LEN];
		stprintf_s(str, S_LEN, _T("Error using vdouble::WaveletDecomposition()\n")
			_T("m_length(%i) != pt->m_length(%i)"),
			m_length, pt->m_length);
		MessageBox(0,str,_T(""),0);
		return -1;
	}


	vdouble d, s;
	int len_h = dh.Length();

	//==========================================
	Vector<int> t_ind;
	t_ind.resize(this->m_length);
	for (i = 0; i < t_ind.Size(); i++)
	{
		t_ind[i] = i;
	}
	//==========================================

	vtau_s_ind.resize(maxLevel); 
	vtau_d_ind.resize(maxLevel); 
	vtau_S_ind.resize(maxLevel); 
	vtau_F_ind.resize(maxLevel);
	//==========================================

	vtau_s.resize(maxLevel);
	vs.resize(maxLevel);
	vtau_d.resize(maxLevel);
	vd.resize(maxLevel);
	vtau_S.resize(maxLevel);
	vSlow.resize(maxLevel);
	vtau_F.resize(maxLevel);
	vFast.resize(maxLevel);

	vdouble 
		* current;
	Vector<int>	
		* current_t_ind;
	current = this,
	current_t_ind = &t_ind;
	// Производим декомпозицию сигнала - получаем s- и d- коэффициенты
	// на каждом уровне разложения
printf("decomposition starts current->Length() = %d\n", current->Length());
	for(j = 0; j < maxLevel; j++)
	{


		// этот вариант предусмотрен для случая биортогональных фильтров 
		// у которых длина высокочастотного и низкочастотного фильтра неравная
		if(!current->dwt(j, *current_t_ind, left_h, right_h, dh,
			vtau_s_ind[j], vs[j]))
			return 0;
		if(!current->dwt(j, *current_t_ind, left_g, right_g, dg,
			vtau_d_ind[j], vd[j]))
			return 0;

		printf("j = %d len of: current = %d , vs[j] = %d, vd[j] = %d\n", j, current->Length(), vs[j].Length(), vd[j].Length());

		current = &vs[j];
		current_t_ind = &vtau_s_ind[j];

		if(pt)
		{
			//==========================================
			vtau_s[j].resize(vtau_s_ind[j].Size());
			for (i = 0; i < vtau_s_ind[j].Size();  i++)
			{
				int ind = vtau_s_ind[j][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_s[j][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_s[j][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_s[j][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
			vtau_d[j].resize(vtau_d_ind[j].Size());
			for ( i = 0; i < vtau_d_ind[j].Size();  i++)
			{
				int ind = vtau_d_ind[j][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_d[j][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_d[j][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_d[j][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
		}
	}

printf("reconstruction starts\n");

	// Производим восстановление низкочастотных и высокочастотных составляющих сигнала на каждом уровне разложения
	for (int J = maxLevel - 1; J >= 0; J--)
	{
		vdouble 
			current_s = vs[J],
			current_d = vd[J];
		Vector<int>
			* current_ts_ind,
			* current_td_ind;
		current_ts_ind = &vtau_s_ind[J],
		current_td_ind = &vtau_d_ind[J];
		
		printf("J = %d len of: current_s = %d  current_d = %d \n", J, current_s.Length(), current_d.Length());

		Vector <int> vnewtau_S_ind, vnewtau_F_ind;

		for (j = J; j >= 0; j--)
		{

			vSlow[J].idwt(j, vnewtau_S_ind, left_h, right_h, rh , *current_ts_ind, current_s, false);
			current_s = vSlow[J];
			vtau_S_ind[J] = vnewtau_S_ind;
			current_ts_ind = &vtau_S_ind[J];
		
			printf("j = %d len of: vSlow[J] = %d\n", j, vSlow[J].Length());

			if ( j == J)
			{
				if(!vFast[J].idwt(j, vnewtau_F_ind, left_g, right_g, rg, *current_td_ind, current_d, false))
					return 0;
				current_d = vFast[J];
			}
			else
			{
				if(!vFast[J].idwt(j, vnewtau_F_ind, left_h, right_h, rh, *current_td_ind, current_d, false))
					return 0;
				current_d = vFast[J];
			}
			vtau_F_ind[J] = vnewtau_F_ind;
			current_td_ind = &vtau_F_ind[J];
		}
		if (pt)
		{
			//==========================================
			vtau_S[J].resize(vtau_S_ind[J].Size());
			for (i = 0; i < vtau_S_ind[J].Size();  i++)
			{
				int ind = vtau_S_ind[J][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_S[J][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_S[J][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_S[J][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
			vtau_F[J].resize(vtau_F_ind[J].Size());
			for ( i = 0; i < vtau_F_ind[J].Size();  i++)
			{
				int ind = vtau_F_ind[J][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_F[J][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_F[J][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_F[J][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
		}
	}
	return 1;
}
int vdouble::WaveletDecomposition1(vdouble* pt,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int left_h,
	  int right_h,
	  int left_g,
	  int right_g,
	  int maxLevel, // максимальный уровенть разложения
	  Vector<Vector<int> >& vtau_s_ind, 
	  Vector<vdouble>& vtau_s,
	  Vector<vdouble>& vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_d_ind, 
	  Vector<vdouble>& vtau_d,
	  Vector<vdouble>& vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  Vector<Vector<int> >& vtau_S_ind, 
	  Vector<vdouble>& vtau_S,
	  Vector<vdouble>& vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  Vector<Vector<int> >& vtau_F_ind,
	  Vector<vdouble>& vtau_F,
	  Vector<vdouble>& vFast) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
{
	int i, j;
	if (pt && m_length != pt->m_length)
	{
		TCHAR str[S_LEN];
		stprintf_s(str, S_LEN, _T("Error using vdouble::WaveletDecomposition()\n")
			_T("m_length(%i) != pt->m_length(%i)"),
			m_length, pt->m_length);
		MessageBox(0,str,_T(""),0);
		return -1;
	}


	vdouble d, s;
	int len_h = dh.Length();

	//==========================================
	Vector<int> t_ind;
	t_ind.resize(this->m_length);
	for (i = 0; i < t_ind.Size(); i++)
	{
		t_ind[i] = i;
	}
	//==========================================

	vtau_s_ind.resize(maxLevel); 
	vtau_d_ind.resize(maxLevel); 
	vtau_S_ind.resize(maxLevel); 
	vtau_F_ind.resize(maxLevel);
	//==========================================

	vtau_s.resize(maxLevel);
	vs.resize(maxLevel);
	vtau_d.resize(maxLevel);
	vd.resize(maxLevel);
	vtau_S.resize(maxLevel);
	vSlow.resize(maxLevel);
	vtau_F.resize(maxLevel);
	vFast.resize(maxLevel);

	vdouble 
		* current;
	Vector<int>	
		* current_t_ind;
	current = this,
	current_t_ind = &t_ind;
	// Производим декомпозицию сигнала - получаем s- и d- коэффициенты
	// на каждом уровне разложения
printf("decomposition starts current->Length() = %d\n", current->Length());
printf("left_h %d right_h %d left_g %d right_g %d\n",
	   left_h, right_h, left_g, right_g);

cout << "Do you want to reenter?" << endl;
char ans; cin >> ans;
if (ans == 'y' || ans == 'Y')
{
	cout << "len_h = " << len_h << endl;

	cout << "left_h?" << endl;
	cin >> left_h;

	cout << "right_h?" << endl;
	cin >> right_h;

	cout << "left_g?" << endl;
	cin >> left_g;

	cout << "right_g?" << endl;
	cin >> right_g;
}

	for(j = 0; j < maxLevel; j++)
	{
		// этот вариант предусмотрен для случая биортогональных фильтров 
		// у которых длина высокочастотного и низкочастотного фильтра неравная
		if(!current->dwt(j, *current_t_ind, left_h, right_h, dh,
			vtau_s_ind[j], vs[j]))
			return 0;
		if(!current->dwt(j, *current_t_ind, left_g, right_g, dg,
			vtau_d_ind[j], vd[j]))
			return 0;

		for (int ii = 0; ii < vs[j].Length(); ii++)
			vs[j][ii] = 0.0;
		for (int ii = 0; ii < vd[j].Length(); ii++)
			vd[j][ii] = 0.0;

		//if (j == maxLevel - 1)
		//if (j == 1)
		{
			vs[j][0] = 1.0;
			vs[j][vs[j].Length()/4-1] = 2.0;
			vs[j][vs[j].Length()/2-1] = 3.0;
			vs[j][3*vs[j].Length()/4-1] = 2.0;
			vs[j][vs[j].Length()-1] = 1.0;
		}		
		{
			vd[j][0] = 1.0;
			vd[j][vd[j].Length()/4-1] = 2.0;
			vd[j][vd[j].Length()/2-1] = 3.0;
			vd[j][3*vd[j].Length()/4-1] = 2.0;
			vd[j][vd[j].Length()-1] = 1.0;
		}


		printf("j = %d len of: current = %d , vs[j] = %d, vd[j] = %d\n", j, current->Length(), vs[j].Length(), vd[j].Length());

		current = &vs[j];
		current_t_ind = &vtau_s_ind[j];

		if(pt)
		{
			//==========================================
			vtau_s[j].resize(vtau_s_ind[j].Size());
			for (i = 0; i < vtau_s_ind[j].Size();  i++)
			{
				int ind = vtau_s_ind[j][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_s[j][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_s[j][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_s[j][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
			vtau_d[j].resize(vtau_d_ind[j].Size());
			for ( i = 0; i < vtau_d_ind[j].Size();  i++)
			{
				int ind = vtau_d_ind[j][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_d[j][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_d[j][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_d[j][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
		}
	}

printf("reconstruction starts\n");

	// Производим восстановление низкочастотных и высокочастотных составляющих сигнала на каждом уровне разложения
	for (int J = maxLevel - 1; J >= 0; J--)
	{
		vdouble 
			current_s = vs[J],
			current_d = vd[J];
		Vector<int>
			* current_ts_ind,
			* current_td_ind;
		current_ts_ind = &vtau_s_ind[J],
		current_td_ind = &vtau_d_ind[J];
		
		printf("J = %d len of: current_s = %d  current_d = %d \n", J, current_s.Length(), current_d.Length());

		Vector <int> vnewtau_S_ind, vnewtau_F_ind;

		for (j = J; j >= 0; j--)
		{

			vSlow[J].idwt(j, vnewtau_S_ind, left_h, right_h, rh , *current_ts_ind, current_s, false);
			current_s = vSlow[J];
			vtau_S_ind[J] = vnewtau_S_ind;
			current_ts_ind = &vtau_S_ind[J];
		
			printf("j = %d len of: vSlow[J] = %d\n", j, vSlow[J].Length());

			if ( j == J)
			{
				if(!vFast[J].idwt(j, vnewtau_F_ind, left_g, right_g, rg, *current_td_ind, current_d, false))
					return 0;
				current_d = vFast[J];
			}
			else
			{
				if(!vFast[J].idwt(j, vnewtau_F_ind, left_h, right_h, rh, *current_td_ind, current_d, false))
					return 0;
				current_d = vFast[J];
			}
			vtau_F_ind[J] = vnewtau_F_ind;
			current_td_ind = &vtau_F_ind[J];
		}
		if (pt)
		{
			//==========================================
			vtau_S[J].resize(vtau_S_ind[J].Size());
			for (i = 0; i < vtau_S_ind[J].Size();  i++)
			{
				int ind = vtau_S_ind[J][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_S[J][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_S[J][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_S[J][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
			vtau_F[J].resize(vtau_F_ind[J].Size());
			for ( i = 0; i < vtau_F_ind[J].Size();  i++)
			{
				int ind = vtau_F_ind[J][i];
				if (ind >= 0 && ind < m_length)
				{
					vtau_F[J][i] = pt->operator [](ind);
				}
				else
				{
					if (ind < 0)
						vtau_F[J][i] = pt->operator [](0);
					if (ind >= m_length)
						vtau_F[J][i] = pt->operator [](m_length-1);
				}
			}
			//==========================================
		}
	}
	return 1;
}
void w_fipsi(vdouble& fh,vdouble& fg,
			 int nf1,int nf2,int ng1,int ng2,int d,
			 vdouble& XF,vdouble& FI,vdouble& XP,vdouble& PSI)
{
	int i, j;
	vdouble P, P1;
	FI = fh*2; PSI = fg*2; 
	int lenh = nf1+nf2+1;
	int leng = ng1+ng2+1;
	if (d==1)
	{
		XF = dsequence(double(-nf1), 1.0,double(nf2));
		XF /= 2; 
		XP = dsequence(double(-ng1), 1.0, double(ng2)); 
		XP /= 2;
	}
	else if (d==2)
	{
		P1.resize(2*leng - 1, 0.0);
		for (i = 0; i < leng; i++)
			P1[2*i] = fg[i];
		P.resize(2*lenh - 1, 0.0);
		for (i = 0; i < lenh;i++)
			P[2*i] = fh[i];
		PSI=2*conv(P1,FI);
		FI=2*conv(P,FI);
		XP = dsequence(double(-(nf1+2*ng1)), 1.0, double(ng2)); 
		XP/=4;
		XF=dsequence(double(-3*nf1), 1.0 ,double(3*nf2)); 
		XF/=4;
	}
	else
	{
		for (j=2; j < d; j++)
		{
			int pow_two = (int)pow(2.0,(j-1));
			P.resize(pow_two*(lenh - 1) + 1, 0.0);
			for (int i = 0; i < lenh;i++)
				P[pow_two*i] = fh[i];
			FI=2*conv(P,FI);
		}
		int pow_two = (int)pow(2.0,(d-1));
		P1.resize(pow_two*(leng - 1) + 1, 0.0);
		for (i = 0; i < leng;i++)
			P1[pow_two*i] = fg[i];

		P.resize(pow_two*(lenh - 1) + 1, 0.0);
		for (i = 0; i < lenh;i++)
			P[pow_two*i] = fh[i];
		
		PSI=2*conv(P1,FI);
		FI=2*conv(P,FI);

		XP=dsequence(double(-(nf1+ng1)*pow(2.0,(d-1))+nf1), 1.0, double((nf2+ng2)*pow(2.0,(d-1))-nf2));
		XF=dsequence(double(-nf1*pow(2.0,d)+nf1), 1.0, double(nf2*pow(2.0,d)-nf2));
		double divider = pow(2.,d);
		XP/=divider;XF/=divider;
	}

}
int WaveletGetLeftRight(
	  int& wf, // флаг вейвлета
	  int& order, // порядок вейвлета
	  int& orderBiorthogonalDecomposition,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g)
{
	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;

	WaveletFilters(wf,order,orderBiorthogonalDecomposition, 
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);

	// Находим хвосты фильтра, которые нужно обрубить справа фильтра и слева фильтра, чтобы число коэффициентов было кратно двум, а число реконструированных элемекнтов сигнал аудваивалось
	// Для этого надо соблюсти следующие условия:
	// левый и правый хвосты должны быть чётными
	// их сумма должна быть на два меньше длины фильтра

	vdouble dh2    = pow(dh,2.0);
	vdouble dg2    = pow(dg,2.0);

	int len_h = dh.Length();
	int len_g = dg.Length();

	double maxh2 = 0;
	int left__h, right__h;
	for (left__h = 0, right__h = len_h - 2; right__h >= 0 ; left__h+=2, right__h-=2)
	{
		double temp = 0.0;
		for (int i = left__h; i < len_h - right__h; i++)
			temp += dh2[i];

		if (temp > maxh2)
		{
			maxh2 = temp;
			left_h = left__h;
			right_h = right__h;
		}
	}
#if 1
	double maxg2 = 0;
	int left__g, right__g;
	for (left__g = 0, right__g = len_g - 2; right__g >= 0 ; left__g+=2, right__g-=2)
	{
		double temp = 0.0;
		for (int i = left__g; i < len_g - right__g; i++)
			temp += dg2[i];

		if (temp > maxg2)
		{
			maxg2 = temp;
			left_g = left__g;
			right_g = right__g;
		}
	}
#else
	left_g = left_h;
	right_g = right_h;
#endif
	return 0;
}

int WaveletEpsilon(
	  int& wf, // флаг вейвлета
	  int& order, // порядок вейвлета
	  int& orderBiorthogonalDecomposition,
	  double& wEpsilon,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g)
{
	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;

	WaveletFilters(wf,order,orderBiorthogonalDecomposition, 
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);

	// Находим хвосты фильтра, которые можно обрубить теряя не более epsilon точности
	vdouble dh2    = pow(dh,2.0);
	vdouble dg2    = pow(dg,2.0);
	vdouble fdh2   = fliplr(dh2);
	vdouble fdg2   = fliplr(dg2);
	vdouble csdh2  = dh2.CumSum();
	vdouble csdg2  = dg2.CumSum();
	vdouble csfdh2 = fdh2.CumSum();
	vdouble csfdg2 = fdg2.CumSum();
	Vector<int> v_left_h  = Find(csdh2  < wEpsilon);
	Vector<int> v_left_g  = Find(csdg2  < wEpsilon);
	Vector<int> v_right_h = Find(csfdh2 < wEpsilon);
	Vector<int> v_right_g = Find(csfdg2 < wEpsilon);

	left_h  = v_left_h.Size()  > 0 ? v_left_h.End()  : 0;
	left_g  = v_left_g.Size()  > 0 ? v_left_g.End()  : 0;
	right_h = v_right_h.Size() > 0 ? v_right_h.End() : 0;
	right_g = v_right_g.Size() > 0 ? v_right_g.End() : 0;
	return 0;
}

void vdouble::Covariation(vdouble &v1, vdouble &v2, int len)
{
//WriteRaporto("Covariation 1\n");
	int len1, len2, i, j, milen, malen, delta_len, k;
	double *pDi, *pmai, *pmi, *pma;
	len1 = v1.m_length;
	len2 = v2.m_length;

	if (len < 0)
		len = 0;

	bool bl = len1 <= len2;

	pmi = bl ? v1.pD : v2.pD;
	pma = bl ? v2.pD : v1.pD;
	milen = bl ? len1 : len2;
	malen = bl ? len2 : len1;

	delta_len = malen - milen;

	if (len > milen)
		len = milen;

	this->resize(len); 

	for (i = 0; i < delta_len; i++)
	{
		pDi = pD + i; pmai = pma + i; * pDi = 0.0;
		for (j = 0; j < milen; j++)
			*pDi += *(pmi + j) * *(pmai + j);
		*pDi /= milen;
	}
	for (i = delta_len; i < len; i++)
	{
		pDi = pD + i; pmai = pma + i; * pDi = 0.0;
		k = milen - i + delta_len;
		for (j = 0; j < k; j++) 
			*pDi += *(pmi + j) * *(pmai + j);
		*pDi /= k;
	}
//WriteRaporto("Covariation end\n");
}

void vdouble::ReverseCovariation(vdouble &v1, vdouble &v2, int len)
{
//WriteRaporto("ReverseCovariation 1\n");
	int len1, len2, i, j, milen, malen, delta_len, k;
	double *pDi, *pmai, *pmi, *pmi_, *pma;
	len1 = v1.m_length;
	len2 = v2.m_length;

//	bool toRevRez = true;
	if (len < 0)
		len = 0;

	bool bl = len1 <= len2;

	pmi = bl ? v1.pD : v2.pD;
	pma = bl ? v2.pD : v1.pD;
	milen = bl ? len1 : len2;
	malen = bl ? len2 : len1;

	delta_len = malen - milen;

	if (len > milen)
		len = milen;

	this->resize(len); 

	pmi_ = pmi + milen-1; 

	for (i = 0; i < delta_len; i++)
	{
//		if (toRevRez)
//			pDi = pD + len - 1 - i; 
//		else
			pDi = pD + i; 
		pmai = pma + malen-1-i; 
		*pDi = 0.0;
		for (j = 0; j < milen; j++)
			*pDi += *(pmi_ - j) * *(pmai - j);
		*pDi /= milen;
	}
	for (i = delta_len; i < len; i++)
	{
//		if (toRevRez)
//			pDi = pD + len - 1 - i; 
//		else
			pDi = pD + i; 
		pmai = pma + malen-1-i; 
		*pDi = 0.0;
		k = milen - i + delta_len;
		for (j = 0; j < k; j++) 
			*pDi += *(pmi_ - j) * *(pmai - j);
		*pDi /= k;
	}
//WriteRaporto("ReverseCovariation end\n");
}

void vdouble::Sequence(double d0, double dstep, double dend)
{
	int Len = (int)floor((dend - d0) / dstep)+1;
	this->resize(Len);
	for (int i = 0; i< Len; i++)
		*(pD + i) = d0 + i * dstep;
}

int vdouble::GetDims()
{
	return m_dims;
}

int vdouble::GetSize(int dim)
{
	if (dim < m_dims)
		return m_size[dim];
	else
		return -1;
}




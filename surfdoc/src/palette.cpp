// palette.cpp: implementation of the APalette class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "palette.h"
#include "colormap.h"
#include "..\..\tools\src\errorexit.h"
#include ".\palette.h"
extern HINSTANCE hInst;   // текущий экземпляр
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

APalette::APalette()
{
	m_len		= 0;
	m_red		= NULL;
	m_green		= NULL;
	m_blue		= NULL;
	m_part		= NULL;

}

APalette::~APalette()
{
	Free();
}

APalette::APalette(int len, COLORREF *colors)
{
	Allocate(len);
	double p = 1.0 / (len-1);
	for(int i = 0; i < len; i++)
	{
		m_red[i]	= GetRValue(colors[i]);
		m_green[i]	= GetGValue(colors[i]);
		m_blue[i]	= GetBValue(colors[i]);
		m_part[i]	= i * p;
	}
}

APalette::APalette(int rows, BYTE *pPalette)
{
	Allocate(rows);
	double p = 1.0 / (rows-1);
	for(int r = 0; r < rows; r++)
	{
		m_red[r]	= pPalette[3*r+0];
		m_green[r]	= pPalette[3*r+1];
		m_blue[r]	= pPalette[3*r+2];
		m_part[r]	= r * p;
	}
}

void APalette::Allocate(const int len) 
{


	m_len		= len;
	if (m_len < 0)
		m_len = 0;	
	
	m_red		= new BYTE[m_len]; //(BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len);
	m_green		= new BYTE[m_len]; //(BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len);
	m_blue		= new BYTE[m_len]; //(BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len);
	m_part		= new double[m_len]; //(double *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len*sizeof(double));
}

void APalette::Free()
{
	if (m_red) 		delete[] m_red; //HeapFree(GetProcessHeap(), 0, m_red);
	if (m_green) 	delete[] m_green;//HeapFree(GetProcessHeap(), 0, m_green);
	if (m_blue) 	delete[] m_blue;//HeapFree(GetProcessHeap(), 0, m_blue);
	if (m_part) 	delete[] m_part;//HeapFree(GetProcessHeap(), 0, m_part);
	m_len = 0;
}

void APalette::Init(int rows, BYTE *pPalette)
{
	Free();
	Allocate(rows);
	double p = 1.0 / (rows-1);
	for(int r = 0; r < rows; r++)
	{
		m_red[r]	= pPalette[3*r+0];
		m_green[r]	= pPalette[3*r+1];
		m_blue[r]	= pPalette[3*r+2];
		m_part[r]	= r * p;
	}

}

void APalette::Init(int len, COLORREF *colors)
{
	Free();
	Allocate(len);
	double p = 1.0 / (len-1);
	for(int i = 0; i < len; i++)
	{
		m_red[i]	= GetRValue(colors[i]);
		m_green[i]	= GetGValue(colors[i]);
		m_blue[i]	= GetBValue(colors[i]);
		m_part[i]	= i * p;
	}

}

void APalette::InitLast(COLORREF color)
{
	if (m_len)
	{
		m_red[m_len-1]		= GetRValue(color);
		m_green[m_len-1]	= GetGValue(color);
		m_blue[m_len-1]		= GetBValue(color);
		m_part[m_len-1]		= 1.0;
	}
}

void APalette::InitFirst(COLORREF color)
{
	if (m_len)
	{
		m_red[0]		= GetRValue(color);
		m_green[0]		= GetGValue(color);
		m_blue[0]		= GetBValue(color);
		m_part[0]		= 0.0;
	}
}

void APalette::InitItem(int nitem, COLORREF color)
{
	if (m_len && (nitem >=0 && nitem < m_len))
	{
		m_red[nitem]		= GetRValue(color);
		m_green[nitem]		= GetGValue(color);
		m_blue[nitem]		= GetBValue(color);
		m_part[nitem]		= double(nitem) / double(m_len - 1);
	}
}

void APalette::Interpolate()
{
	for (int i = 1; i < m_len-1; i++)
	{
		float part = float(i) / float(m_len-1);
		m_part [i]		= part;
		m_red  [i]		= m_red[0]   + BYTE(0.5+(part) * float(int (m_red  [m_len-1]) - int(m_red  [0]) ));
		m_green[i]		= m_green[0] + BYTE(0.5+(part) * float(int (m_green[m_len-1]) - int(m_green[0]) ));
		m_blue [i]		= m_blue[0]  + BYTE(0.5+(part) * float(int (m_blue [m_len-1]) - int(m_blue [0]) ));
	}
}

COLORREF APalette::GetColor(unsigned int i)
{
	if (i >= 0 && i < m_len)
		return RGB(m_red[i], m_green[i], m_blue[i]);
	else
		return 0;

}

COLORREF APalette::GetColor(double part)
{
	if (part >= 0 && part < 1.0)
	{
		UINT i = UINT(part * double(m_len-1)); 
		double p = (part - m_part[i]) / (m_part[i+1] - m_part[i]);

		BYTE red	= m_red[i]		+ BYTE(p * double(m_red[i+1]	- m_red[i]));
		BYTE green	= m_green[i]	+ BYTE(p * double(m_green[i+1]	- m_green[i]));
		BYTE blue	= m_blue[i]		+ BYTE(p * double(m_blue[i+1]	- m_blue[i]));

		return RGB(red, green, blue);
	}
	else
		return 0;

}

COLORREF APalette::GetColorWithAlpha(double part, int alpha)
{
	if (part >= 0 && part < 1.0)
	{
		UINT i = UINT(part * double(m_len-1)); 
		double p = (part - m_part[i]) / (m_part[i+1] - m_part[i]);

		BYTE red	= m_red[i]		+ BYTE(p * double(m_red[i+1]	- m_red[i]));
		BYTE green	= m_green[i]	+ BYTE(p * double(m_green[i+1]	- m_green[i]));
		BYTE blue	= m_blue[i]		+ BYTE(p * double(m_blue[i+1]	- m_blue[i]));

		return RGBA(red, green, blue, alpha);
	}
	else
		return 0;

}

COLORREF APalette::GetColorWithAlpha(unsigned int i, int alpha)
{
	if (i >= 0 && i < m_len)
		return RGBA(m_red[i], m_green[i], m_blue[i], alpha);
	else
		return 0;

}

int APalette::GetLen() const 
{
	return m_len;
}

void APalette::Extract(int m)
{
	int i, _len		= m_len;
	BYTE * _red		= (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len);
	BYTE * _green	= (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len);
	BYTE * _blue	= (BYTE *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len);
	double * _part	= (double *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, m_len*sizeof(double));

	for(i = 0; i < _len; i++)
	{
		_red[i]		= m_red[i];
		_green[i]	= m_green[i];
		_blue[i]	= m_blue[i];
		_part[i]	= m_part[i];
	}
	Free();
	Allocate((_len-1)*m+1);
	for(i = 0; i < _len; i++)
	{
		for (int q = 0; q < m; q ++)
		{
			m_red  [m*i+q]		= _red  [i] + BYTE(0.5+((float(q) / float(m)) * float(int (_red  [i+1]) - int(_red  [i]) )));
			m_green[m*i+q]		= _green[i] + BYTE(0.5+((float(q) / float(m)) * float(int (_green[i+1]) - int(_green[i]) )));
			m_blue [m*i+q]		= _blue [i] + BYTE(0.5+((float(q) / float(m)) * float(int (_blue [i+1]) - int(_blue [i]) )));
			m_part [m*i+q]		= _part [i] + (float(q) / float(m)) * float(int (_part [i+1]) - int(_part [i]) );
		}
	}
	if (_red) 		HeapFree(GetProcessHeap(), 0, _red);
	if (_green) 	HeapFree(GetProcessHeap(), 0, _green);
	if (_blue) 		HeapFree(GetProcessHeap(), 0, _blue);
	if (_part) 		HeapFree(GetProcessHeap(), 0, _part);

}
// static
int APalette::InitPalette(APalette* me, UINT nColormap)
{

#ifdef DO_RAPORT
char str[255];
sprintf(str, 
	"APalette::InitPalette(APalette* me = %x, UINT nColormap = %d)\n",
	me, nColormap);
WriteRaporto(str);
#endif

	HANDLE hRes2;
	HRSRC  hRsrc2;
	
	//Данные палитры из ресурсов
	if(!(hRsrc2 = FindResource( 
		hInst, 
		colormaps[nColormap],
		RT_RCDATA  )))
	{
		ErrorExit("FindResource3",false);
		return 0;
	}
#ifdef DO_RAPORT
sprintf(str, 
	"hRsrc2 = FindResource = %x\n",
	hRsrc2);
WriteRaporto(str);
#endif
	if(!(hRes2 = LoadResource(
		hInst, 
		hRsrc2)))
	{
		ErrorExit("LoadResourse2",0);
		return 0;
	}

#ifdef DO_RAPORT
sprintf(str, 
	"hRes2 = LoadResource = %x\n",
	hRes2);
WriteRaporto(str);
#endif

	LPVOID pPaletteData = LockResource( hRes2 );
	if (!pPaletteData)
	{
		ErrorExit("LockResource2",0);
		return 0;
	}

#ifdef DO_RAPORT
sprintf(str, 
	"pPaletteData = LockResource = %x\n",
	pPaletteData);
WriteRaporto(str);
#endif
	
	// из  заголовка считываем число строк и колонок
	int RowsP, ColsP;
	RowsP = *((int *)pPaletteData);
	ColsP = *((int *)pPaletteData+1);
	//получаем указатель на данные palette
	BYTE*  pPaletteValues = 
		(BYTE*)((int*)pPaletteData + 2);

#ifdef DO_RAPORT
sprintf(str, 
	"RowsP = %d ColsP = %d pPaletteValues = %x\n",
	RowsP, ColsP, pPaletteValues);
WriteRaporto(str);
#endif

	me->Init(RowsP,pPaletteValues);

#ifdef DO_RAPORT
sprintf(str, 
	"APalette::InitPalette end\n");
WriteRaporto(str);
#endif
	return RowsP;
}
/*
APalette::APalette(const APalette &ob)
{
	int len = ob.m_len;
	Allocate(len);
	double p = 1.0 / (len-1);
	for(unsigned int i = 0; i < len; i++)
	{
		m_red[i]	= ob.m_red[i];
		m_green[i]	= ob.m_green[i];
		m_blue[i]	= ob.m_blue[i];
		m_part[i]	= i * p;
	}
}
*/
/*
APalette& APalette::operator=(const APalette& ob)
{
	if (this == &ob)
		return *this;

	int len = ob.m_len;
	Allocate(len);
	double p = 1.0 / (len-1);
	for(unsigned int i = 0; i < len; i++)
	{
		m_red[i]	= ob.m_red[i];
		m_green[i]	= ob.m_green[i];
		m_blue[i]	= ob.m_blue[i];
		m_part[i]	= i * p;
	}
	return *this;
}
*/
void APalette::Init(const APalette& ob)
{
	this->Free();
	this->Allocate(ob.GetLen());
	double p = 1.0 / (m_len-1);
	for(unsigned int i = 0; i < m_len; i++)
	{
		m_red[i]	= ob.m_red[i];
		m_green[i]	= ob.m_green[i];
		m_blue[i]	= ob.m_blue[i];
		m_part[i]	= i * p;
	}
}

APalette::APalette(const APalette& ob)
{
	this->Init(ob);
}

APalette& APalette::operator=(const APalette& ob)
{
	if (this == &ob)
		return *this;

	this->Init(ob);

	return *this;
}
Archive& operator <<(Archive& ar, APalette& ob)
{
	ar << ob.m_len;
	//ar.Write((unsigned char *)&ob.m_part,  ob.m_len*sizeof(double));
	//ar.Write((unsigned char *)&ob.m_red,   ob.m_len*sizeof(BYTE));
	//ar.Write((unsigned char *)&ob.m_green, ob.m_len*sizeof(BYTE));
	//ar.Write((unsigned char *)&ob.m_blue,  ob.m_len*sizeof(BYTE));
	for (int i = 0; i < ob.m_len; i++)
	{
		ar << ob.m_part[i];
		ar << ob.m_red[i];
		ar << ob.m_green[i];
		ar << ob.m_blue[i];
	}
	return ar;
}
Archive& operator >>(Archive& ar, APalette& ob)
{
//printf("Archive& operator >>(Archive& ar, APalette& ob)\n");
	ob.Free();
//printf("Archive& operator >>(Archive& ar, APalette& ob) 1\n");
	ar >> ob.m_len;
//printf("Archive& operator >>(Archive& ar, APalette& ob) ob.m_len = %u\n", ob.m_len);
	if (ob.m_len < 0)
	{
		char errstr[255];
		sprintf(errstr, "error while reading of palette object: ob.m_len = %d", ob.m_len);
		throw errstr;
	}
	ob.Allocate(ob.m_len);
//printf("Archive& operator >>(Archive& ar, APalette& ob) 2\n");
	//ar.Read((unsigned char *)&ob.m_part,  ob.m_len*sizeof(double));
	//ar.Read((unsigned char *)&ob.m_red,   ob.m_len*sizeof(BYTE));
	//ar.Read((unsigned char *)&ob.m_green, ob.m_len*sizeof(BYTE));
	//ar.Read((unsigned char *)&ob.m_blue,  ob.m_len*sizeof(BYTE));
	for (int i = 0; i < ob.m_len; i++)
	{
		ar >> ob.m_part[i];
		ar >> ob.m_red[i];
		ar >> ob.m_green[i];
		ar >> ob.m_blue[i];
	}
//printf("Archive& operator >>(Archive& ar, APalette& ob) end\n");
	return ar;
}



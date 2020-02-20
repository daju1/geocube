// palette.h: interface for the APalette class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PALETTE_H__6C4BE9C1_C04A_4A0F_959E_BFCE034E4327__INCLUDED_)
#define AFX_PALETTE_H__6C4BE9C1_C04A_4A0F_959E_BFCE034E4327__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef _MSC_VER
#include "..\..\stdAfx.h"
#endif
#include "Archive.h"

class APalette /*: public Object*/
{
	unsigned int m_len;
	double 
		* m_part;
	BYTE 
		* m_red, 
		* m_green, 
		* m_blue;
public:
	//APalette& operator=(const APalette& ob);
	//APalette(const APalette& ob);
	void Extract(int m);
	int GetLen() const;

	COLORREF GetColorWithAlpha(unsigned int i, int alpha);
	COLORREF GetColor(unsigned int color_index);

	COLORREF GetColorWithAlpha(double part, int alpha);
	COLORREF GetColor(double part);

	void Interpolate();
	void InitItem(int nitem, COLORREF color);
	void InitFirst(COLORREF color);
	void InitLast( COLORREF color);
	void Init(int len, COLORREF *colors);
	void Init(int rows, BYTE *pPalette);
	void Free();
	void Allocate(const int len);
	APalette(int rows, BYTE * pPalette);
	APalette(int len, COLORREF *colors);
	APalette();
	virtual ~APalette();
	static int InitPalette(APalette* me, UINT nColormap);
	void Init(const APalette& ob);
	APalette(const APalette& ob);
	APalette& operator=(const APalette& ob);


	friend Archive& operator <<(Archive& ar, APalette& ob);
	friend Archive& operator >>(Archive& ar, APalette& ob);
};

#endif // !defined(AFX_PALETTE_H__6C4BE9C1_C04A_4A0F_959E_BFCE034E4327__INCLUDED_)

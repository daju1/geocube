// GraphsView.h : interface of the CGraphsView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHSVIEW_H__9DBD1EAD_FF8D_4FF9_906A_B2FC1D4C91CC__INCLUDED_)
#define AFX_GRAPHSVIEW_H__9DBD1EAD_FF8D_4FF9_906A_B2FC1D4C91CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CGraphsDoc;

class CGraphsView
{
	HANDLE  m_hEventDrawReady;
	HDC  hMemDC;
	HBITMAP hBitmap;
	//bool bBitmapCreated;
	int bmWidth, bmHeight;

	CGraphsDoc *m_pDocument;
	unsigned short m_yPos;
	unsigned short m_xPos;
	//int m_Len;
	int m_iLast;
	int m_iFirst;
	int m_iDoc;
	bool m_bRight;
#ifdef EXTERN_FONTS_AND_PENS
	//===== Перо для рисования
	HPEN m_boxPen, m_gridPen, m_linePen;
	//===== Два типа шрифтов
	HFONT m_hTitleFont, m_hFont;
	HFONT m_hPrintTitleFont, m_hPrintFont;
#endif

// Attributes
public:
	void Draw(HDC hdc, RECT& rect);
	bool OnSize(HWND hWnd);
	BOOL OnPaint(HWND hWnd,    LPPAINTSTRUCT lpPaint);
	void OnResizeGraphsCount(HWND hWnd);
	void DrawToPrinter(HDC hDC);
	void SetFullZoom(HWND hWnd);
	void OnLButtonDownMouseMove(HWND hWnd, unsigned short xPos, unsigned short yPos);
	void OnRButtonDownMouseMove(HWND hWnd, unsigned short xPos, unsigned short yPos);
	void OnLButtonDown(HWND hWnd, unsigned short xPos, unsigned short yPos);
	void OnRButtonDown(HWND hWnd, unsigned short xPos, unsigned short yPos);
	double m_SizeTotal_cy;
	void VerticalZoom(HWND hWnd, int zDelta, bool isButton);
	void HorizontalZoom(HWND hWnd, int zDelta);
	HENHMETAFILE hMetaFile;
	tagSIZE m_SizeTotal;
	CGraphsView();

	void DrawToMetaFile(HWND hWnd);  // overridden to draw this view
	void DrawToMetaFile2(HWND hWnd);  // overridden to draw this view
	void OnCreate(int iDoc, CGraphsDoc* pDoc); // called first time after construct
	VOID VScroll( HWND hWnd, WORD wScroll );
	VOID HScroll( HWND hWnd, WORD wScroll );

//	RECT m_TotalRect;
	double m_shift_ya;
	double m_shift_yb;
	int m_nCurVertPos;
	int m_nCurHorzPos;
	double m_scale_y;
	void DrawWithMemToWindow(HWND hWnd);
	void DrawToWindow(HWND hWnd, bool toInvalidate);
	virtual ~CGraphsView();

};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_GRAPHSVIEW_H__9DBD1EAD_FF8D_4FF9_906A_B2FC1D4C91CC__INCLUDED_)

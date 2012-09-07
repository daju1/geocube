// OGView.h : interface of the COGView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGVIEW_H__FD4ECFF5_BCCF_4E90_B761_A58F449A2EFD__INCLUDED_)
#define AFX_OGVIEW_H__FD4ECFF5_BCCF_4E90_B761_A58F449A2EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "OGDoc.h"
//class COGDoc;
//#include "PropDlg.h"
class CPropDlg;
class COGView : public CView
{
protected: // create from serialization only
	COGView();
	DECLARE_DYNCREATE(COGView)

// Attributes
public:
	CPropDlg * m_pDlg;
	COGDoc* GetDocument();

// Operations
public:
	static u_int s_nViews;
	u_int m_nView;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGView)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~COGView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
public:
	void AnimateStop();
	void AnimateGraphic();
	void RefreshOG(bool isfull = true);
	void InitOG();
	//======= ����� ������ ������
	long		m_BkClr;			// ���� ���� ����
	int			m_LightParam[11];// ��������� ���������
	HGLRC		m_hRC;				// �������� OpenGL
	HDC			m_hdc; 			// �������� Windows
	GLfloat	m_AngleX;			// ���� �������� ������ ��� X
	GLfloat	m_AngleY;			// ���� �������� ������ ��� Y
	GLfloat	m_AngleView;		// ���� �����������
	GLfloat	m_dx;				// ����� �������� ����� X
	GLfloat	m_dy;				// ����� �������� ����� Y
	GLfloat	m_xTrans;			// C������� ����� X
	GLfloat	m_yTrans;			// C������� ����� Y
	GLfloat	m_zTrans;			// C������� ����� Z
	GLenum		m_FillMode;		// ����� ���������� ���������
	bool		m_bCaptured;		// ������� ������� ����
	bool		m_bRightButton;	// ���� ������ ������ ����
	bool		m_bQuad;			// ���� ������������� GL_QUAD
	CPoint		m_pt;				// ������� ������� ����


	//====== ����� ������ ������
	//====== ���������� �����������
	void DrawScene();
	//====== ��������� ���������� ���������
	void SetLight();
	//====== ��������� ������ �� ���������� ���������
	void SetLightParam (short lp, int nPos);
	//====== ����������� ����������� ���������� ���������
	void GetLightParams(int *pPos);
	//====== ��������� ������ � ������ ������ 
	void SetBkColor();

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COGView)
	afx_msg void OnWindowPosChanging(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	afx_msg void OnWindowPosChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditBackground();
	afx_msg void OnEditProperties();
	afx_msg void OnViewQuad();
	afx_msg void OnUpdateViewQuad(CCmdUI* pCmdUI);
	afx_msg void OnViewFill();
	afx_msg void OnUpdateViewFill(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditProperties(CCmdUI* pCmdUI);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in OGView.cpp
inline COGDoc* COGView::GetDocument()
   { return (COGDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGVIEW_H__FD4ECFF5_BCCF_4E90_B761_A58F449A2EFD__INCLUDED_)

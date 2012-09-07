// GraphsDoc.h : interface of the CGraphsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPHSDOC_H__4ABDA399_0C2C_46EF_9C32_B788B4C6A945__INCLUDED_)
#define AFX_GRAPHSDOC_H__4ABDA399_0C2C_46EF_9C32_B788B4C6A945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParamDlg.h"
//#include "StdAfx.h"
#include "vdouble.h"
#include "systemnnet.h"
#include "OutLagFrm.h"
#include "WaveDlg.h"	// Added by ClassView


class CGraphsDoc : public CDocument
{
	//===== Вспомогательные классы будут пользоваться данными
	friend class CGraph;
	friend class CParamDlg;
	friend class CWaveDlg;

private:
	bool m_bIsFirstTick;
	//===== Изменение размерности задачи
	void ReinitVectorsPoints();
	void InitGraphics(vdouble& vx, vdouble& vy, bool toDraw, bool toAdd, bool toScaleX = true, bool toScaleY = false);
	void InitGraphics(Vector<vdouble>& vx, Vector<vdouble>& vy, bool OneGraphic, bool toDraw, bool toAdd, bool toScaleX = true, bool toScaleY = false);
protected: // create from serialization only
	CGraphsDoc();
	DECLARE_DYNCREATE(CGraphsDoc)
	COutLagFrm* m_pOutWnd;

public:
	Vector<Vector<CpVDPoints> > m_vpPoints;
	Vector<CpVDPoints> 
		m_vpPoints1;// 

	int m_radioRec;
	double m_wEpsilon,
		m_wEpsilon0;

	int m_wf,
		m_wOrder,
		m_maxLevel,
		m_wf0,
		m_wOrder0;

	vdouble m_dh, m_dg, m_rh, m_rg;


	int m_left_h;
	int m_right_h;
	int m_left_g;
	int m_right_g;

	Vector<vdouble> 
	  m_vtsd,
	  m_vts,
	  m_vtd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  m_vtSF,
	  m_vtSlow,
	  m_vtFast,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  m_vFast; // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
			 
	vdouble m_vxFI,m_vFI,m_vxPSI,m_vPSI;

	bool m_isOutWnd;
	int m_i0,
		m_SignalNumber,
		m_MaxOrder,
		m_Len,
		m_LenPredict;


	double	m_t0,
		m_dt,
		m_tend,
		m_t2end,
		m_alpha,
		m_beta,
		m_epsilon,
		m_fund_det;
	double m_error,
		m_PredictError,
		m_alpha_det;
	vdouble 
		m_T,	
		m_T2,	
		m_t,
		m_TPredict,	
		m_T2Predict,	
		m_tPredict,

		m_Cov,
		m_tCov,

		m_vQ,
		m_alphai,
		m_flip_betai,
		m_num,
		m_den;
	
	SystemNnet m_Nnet;
	LagerStruct m_lgstr;
	TrainParam m_tp;
	CString m_sAnaliticEquation;
	CString m_sRoots;
	CString m_sNumDen;
	CParamDlg *m_pDlg;	// Немодальный диалог параметров
	CView *m_pView;
	void SetTime();
	void AddSignal();
	void Solve();
	void TrainNnet();
	void AlphaDeterminition();
	void OutWindow();

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGraphsDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void WaveletEpsilonApply();
	void WaveletDisplay();
	CWaveDlg* m_pWaveDlg;
	void OnWaveletApply();
//	CWavParam* m_pWawDlg;
	void WaveletApply();
	void OnTick(int v);
	void CovariationAnalize();
	void CovariationApply();
	void SaveAnaliticalString();
	void AnaliticalString();
	void SetTimeEnd();
	void OnImport();
	void OnImport2();
	virtual ~CGraphsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void OnFileExport();
	void OnFileExport2();

// Generated message map functions
protected:
	//{{AFX_MSG(CGraphsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	afx_msg void OnEditParameters(void);
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CGraphsDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAPHSDOC_H__4ABDA399_0C2C_46EF_9C32_B788B4C6A945__INCLUDED_)

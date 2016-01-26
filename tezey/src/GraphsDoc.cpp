// GraphsDoc.cpp : implementation of the CGraphsDoc class
//

#include "StdAfx.h"
#include "raporto.h"
#include "GraphsDoc.h"
#include "GraphsView.h"
#include "XYZBuffer.h"
#include "../../wintools/src/winsurf.h"
#include "../../winplot/src/winplot.h"

extern vdouble dsequence(double d0, long Len, double dend);
extern Vector<int> sequence(int i1, int i2); // Возвращает последовательность целых чисел от i1 до i2
extern void /*vdouble::*/WaveletFilters(int wf, // флаг типа вейвлетов
									int order, // порядоак вейвлета
									int orderBiorthogonalDecomposition,
	int& nd1, int& nd2, vdouble& d_h,
	int& ngd1, int& ngd2, vdouble& d_g,
	int& nr1, int& nr2, vdouble& r_h, 
	int& ngr1, int& ngr2,vdouble& r_g,
	int& n00, double& m00);
extern void datevec(double dn, SYSTEMTIME& tm);
extern void w_fipsi(vdouble& fh,vdouble& fg,
			 int nf1,int nf2,int ng1,int ng2,int d,
			 vdouble& XF,vdouble& FI,vdouble& XP,vdouble& PSI);

extern double datenum(SYSTEMTIME tm);

extern Vector<CGraphsDoc> vDoc;
extern double Median(double *p, int len); // Возврашает median элементов вектора
extern double datenum(int y, int mo, int d, int h, int mi, int s, int milli);

#include "../../winplot//src/winplot.h"
#include "GraphsDoc.h"
#include "map.h"

#define SHOW_WAV_KOEF
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif*/
//void WriteRaporto(LPSTR s)

/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc



/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc construction/destruction

CGraphsDoc::CGraphsDoc()
{
}

CGraphsDoc::~CGraphsDoc()
{
	if (m_sAnaliticEquation) 
		HeapFree(GetProcessHeap(), 0, m_sAnaliticEquation);
	if (m_sRoots) 
		HeapFree(GetProcessHeap(), 0, m_sRoots);
	if (m_sNumDen)
		HeapFree(GetProcessHeap(), 0, m_sNumDen);
}


void CGraphsDoc::OnCreate()
{
WriteRaporto("CGraphsDoc::OnCreate() 1\n");
	m_wEpsilon0 = 0.0;
	m_wf0 = 0;
	m_wOrder0 = 0;
	m_wOrderBiorthogonalDecomposition0 = 0;
	m_wInputSigalType = 0;

	m_left_h = 0;
	m_right_h = 0;
	m_left_g = 0;
	m_right_g = 0;

	m_wf = 3;
	m_wOrder = 3;
	m_wOrderBiorthogonalDecomposition = 1;
	m_maxLevel = 5;
	m_wEpsilon = 0.01;
	
	m_bWavShowLow = true;
	m_bWavShowHigh = false;

	m_wRadioRec = 0;

	m_bIsFirstTick = true;

	m_i0 = 0;
	m_SignalNumber = 10;
	m_MaxOrder = 5;
	m_isOutWnd = false;

	m_t0 = - 60*1.*1.;
	m_dt = 1./60.;
	m_tend = 0;
	m_t2end = m_tend;
	m_alpha = 2.0;
	m_beta = 0.0;
	m_epsilon = 0.00001;

	m_nInstrumentNumber1 = 1;
	m_nInstrumentNumber2 = 0;

#ifndef NEW_VECT_COMMON_PARAMS
#else
	m_vtCommonParams.OnCreate(0);
	m_vvCommonParams.OnCreate(0);
#endif



#ifndef DRAW_OLD_VECTOR_VDPOINTS
	m_vPoints.OnCreate(0);
	m_vPoints1.OnCreate(0);
#endif
//	SetTime(3600+1);

	ReinitVectorsPoints();

	m_sAnaliticEquation = (char * )HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,1024*32);
	m_sRoots			= (char * )HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,1024*32);
	m_sNumDen			= (char * )HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,1024*32);

	m_tp.epochs = 100;
	m_tp.goalE = 0.0000001;
	m_tp.goalQ = 0.0000001;
	m_tp.min_grad = 1e-14;
	m_tp.show = 100;
	m_tp.full_turn = 5;


WriteRaporto("CGraphsDoc::OnCreate() end\n");

}

void CGraphsDoc::ReinitVectorsPoints(double minY, double maxY)
{
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	CpVDPoints pVDPoints;
	pVDPoints.px = &m_t;
	pVDPoints.py = &m_T;
//	pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = maxY;
	pVDPoints.minY = minY;
	pVDPoints.maxX = m_t.Max();
	pVDPoints.minX = m_t.Min();
	pVDPoints.toDraw = true;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);

	if(m_vPoints1.msgSize() > 0)
		m_vPoints1.clearMsg();

	m_vPoints1.AddMsg(&pVDPoints);



#else
	m_vpPoints1.resize(1);
	m_vpPoints1[0].px = &m_t;
	m_vpPoints1[0].py = &m_T;
	m_vpPoints1[0].pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	m_vpPoints1[0].maxY = maxY;
	m_vpPoints1[0].minY = minY;
	m_vpPoints1[0].maxX = m_t.Max();
	m_vpPoints1[0].minX = m_t.Min();
	m_vpPoints1[0].toDraw = true;
#endif
}

void CGraphsDoc::ReinitVectorsPoints()
{
#if 0
#ifndef DRAW_OLD_VECTOR_VDPOINTS
WriteRaporto("ReinitVectorsPoints\n");
	if(m_vPoints1.msgSize() > 0)
		m_vPoints1.clearMsg();
WriteRaporto("ReinitVectorsPoints 2\n");
	CpVDPoints pVDPoints;
	pVDPoints.px = &m_t;
	pVDPoints.py = &m_T;
//	pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&m_T)->Max();
	pVDPoints.minY = (&m_T)->Min();
	pVDPoints.maxX = (&m_t)->Max();
	pVDPoints.minX = (&m_t)->Min();
	pVDPoints.toDraw = true;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);


	m_vPoints1.AddMsg(&pVDPoints);
WriteRaporto("ReinitVectorsPoints end\n");

#else
	m_vpPoints1.resize(1);
	m_vpPoints1[0].px = &m_t;
	m_vpPoints1[0].py = &m_T;
	m_vpPoints1[0].pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	m_vpPoints1[0].maxY = (&m_T)->Max();
	m_vpPoints1[0].minY = (&m_T)->Min();
	m_vpPoints1[0].maxX = (&m_t)->Max();
	m_vpPoints1[0].minX = (&m_t)->Min();
	m_vpPoints1[0].toDraw = true;
#endif
#else
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if(m_vPoints1.msgSize() > 0)
		m_vPoints1.clearMsg();
WriteRaporto("ReinitVectorsPoints 2\n");
	CpVDPoints pVDPoints;

	pVDPoints.px = &m_t;
	pVDPoints.py = &m_T;
//	pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&m_T)->Max();
	pVDPoints.minY = (&m_T)->Min();
	pVDPoints.maxX = (&m_t)->Max();
	pVDPoints.minX = (&m_t)->Min();
	pVDPoints.toDraw = true;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);
	m_vPoints1.AddMsg(&pVDPoints);

	pVDPoints.px = &m_tPredict;
	pVDPoints.py = &m_TPredict;
	pVDPoints.maxY = (&m_TPredict)->Max();
	pVDPoints.minY = (&m_TPredict)->Min();
	pVDPoints.maxX = (&m_tPredict)->Max();
	pVDPoints.minX = (&m_tPredict)->Min();
	pVDPoints.toDraw = false;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);
	m_vPoints1.AddMsg(&pVDPoints);

		
	pVDPoints.px = &m_t;
	pVDPoints.py = &m_Nnet.m_Y;
//	pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&m_Nnet.m_Y)->Max();
	pVDPoints.minY = (&m_Nnet.m_Y)->Min();
	pVDPoints.maxX = (&m_t)->Max();
	pVDPoints.minX = (&m_t)->Min();
	pVDPoints.toDraw = true;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);
	m_vPoints1.AddMsg(&pVDPoints);

	pVDPoints.px = &m_tPredict;
	pVDPoints.py = &m_Nnet.m_YPredict;
	pVDPoints.maxY = (&m_Nnet.m_YPredict)->Max();
	pVDPoints.minY = (&m_Nnet.m_YPredict)->Min();
	pVDPoints.maxX = (&m_tPredict)->Max();
	pVDPoints.minX = (&m_tPredict)->Min();
	pVDPoints.toDraw = false;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);
	m_vPoints1.AddMsg(&pVDPoints);

	pVDPoints.px = &m_t;
	pVDPoints.py = &m_T2;
//	pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&m_T2)->Max();
	pVDPoints.minY = (&m_T2)->Min();
	pVDPoints.maxX = (&m_t)->Max();
	pVDPoints.minX = (&m_t)->Min();
	pVDPoints.toDraw = false;
	pVDPoints.notGist = true;
	pVDPoints.bTimeScale = true;
	strcpy(pVDPoints.szTitle, m_sTitle);
	strcpy(pVDPoints.szXLabel, m_sXLabel);
	strcpy(pVDPoints.szYLabel, m_sYLabel);
	m_vPoints1.AddMsg(&pVDPoints);

WriteRaporto("ReinitVectorsPoints end\n");
#else
	m_vpPoints1.resize(7);
	for(int i = 0; i < 6; i+=2)
	{
		m_vpPoints1[i].px = &m_t;
		m_vpPoints1[i + 1].px = &m_tPredict;
		m_vpPoints1[i].toDraw = true;
		m_vpPoints1[i + 1].toDraw = true;
	}
	m_vpPoints1[0].pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
	m_vpPoints1[0].py = &m_T;				//m_vpPoints1[0].toDraw = false;
	m_vpPoints1[0].maxY = (&m_T)->Max();
	m_vpPoints1[0].minY = (&m_T)->Min();
	m_vpPoints1[0].maxX = (&m_t)->Max();
	m_vpPoints1[0].minX = (&m_t)->Min();

	m_vpPoints1[1].py = &m_TPredict;		m_vpPoints1[1].toDraw = false;
	m_vpPoints1[1].maxY = m_TPredict.Max();
	m_vpPoints1[1].minY = m_TPredict.Min();
	m_vpPoints1[1].maxX = m_tPredict.Max();
	m_vpPoints1[1].minX = m_tPredict.Min();

	m_vpPoints1[2].py = &m_Nnet.m_Y;		m_vpPoints1[2].toDraw = false;
	m_vpPoints1[2].maxY = m_Nnet.m_Y.Max();
	m_vpPoints1[2].minY = m_Nnet.m_Y.Min();
	m_vpPoints1[2].maxX = m_Nnet.m_t.Max();
	m_vpPoints1[2].minX = m_Nnet.m_t.Min();

	m_vpPoints1[3].py = &m_Nnet.m_YPredict;	m_vpPoints1[3].toDraw = false;
	m_vpPoints1[3].maxY = m_Nnet.m_YPredict.Max();
	m_vpPoints1[3].minY = m_Nnet.m_YPredict.Min();
	m_vpPoints1[3].maxX = m_Nnet.m_tPredict.Max();
	m_vpPoints1[3].minX = m_Nnet.m_tPredict.Min();

	m_vpPoints1[4].py = &m_T2;				m_vpPoints1[4].toDraw = false;
	m_vpPoints1[4].maxY = m_T2.Max();
	m_vpPoints1[4].minY = m_T2.Min();
	m_vpPoints1[4].maxX = m_t.Max();
	m_vpPoints1[4].minX = m_t.Min();

	m_vpPoints1[5].py = &m_T2Predict;		m_vpPoints1[4].toDraw = false;
	m_vpPoints1[5].maxY = m_T2Predict.Max();
	m_vpPoints1[5].minY = m_T2Predict.Min();
	m_vpPoints1[5].maxX = m_tPredict.Max();
	m_vpPoints1[5].minX = m_tPredict.Min();

	m_vpPoints1[6].py = &m_Cov;				
	m_vpPoints1[6].maxY = m_Cov.Max();
	m_vpPoints1[6].minY = m_Cov.Min();
	m_vpPoints1[6].maxX = m_tCov.Max();
	m_vpPoints1[6].minX = m_tCov.Min();
	m_vpPoints1[6].px = &m_tCov;		
	m_vpPoints1[6].toDraw = false;
#endif
#endif
}



void CGraphsDoc::AlphaDeterminition()
{
	m_tend = m_t.End() - m_t[0];
	m_alpha_det = m_t.LagerAlphaDeterm(m_MaxOrder, m_tend, .95);
}
void CGraphsDoc::SetTime(int _len)
{
	SYSTEMTIME time;
	GetTime(&time);
	double t = datenum(time);
	double dt = 1./3600./24.;

	m_Len = _len;
	m_Len2 = 0;
//	m_vtime.resize(m_Len);

	m_T.resize(m_Len,0.0);	
	m_t.resize(m_Len,0.0);	
	//m_t = dsequence(1., 1./(m_Len-1), 2.);
	for (int i = m_Len - 1; i>=0; i--)
		m_t[i] = t - dt*i;
}


void CGraphsDoc::SetTime()
{
	int i;
	m_Len = (int)((m_tend - m_t0) / m_dt) + 1;
	m_LenPredict = (int)((m_t2end - m_tend) / m_dt);
	m_T.resize(m_Len,0.0);	
	m_T2.resize(m_Len,0.0);	
	m_t.resize(m_Len,0.0);

	SYSTEMTIME tm;
	GetTime(&tm);
//	m_vtime.resize(m_Len, tm);
//	double t = datenum(tm);


	m_TPredict.resize(m_LenPredict, 0.0);	
	m_T2Predict.resize(m_LenPredict, 0.0);	
	m_tPredict.resize(m_LenPredict);

	for(i=0; i < m_Len; i++)
	{
		m_t[i] = i*m_dt + m_t0;
	}

	for(i=0; i < m_LenPredict; i++)
		m_tPredict[i] = (i-1)*m_dt + m_tend;

	m_Nnet.Init(m_t,m_T,m_tPredict,m_TPredict);
	ReinitVectorsPoints();
}
void CGraphsDoc::AddSignal()
{	
	m_Nnet.DeleteAll();
	m_Nnet.Init(m_t,m_T,m_tPredict,m_TPredict);
	ReinitVectorsPoints();
//	UpdateAllViews(m_pView);
}
void CGraphsDoc::LagerSolve(bool bIncludeRealRoots)
{	
WriteRaporto("LagerSolve 1\n");
	int flag_of_Inf = 0;

//	m_Nnet.DeleteAll();

//	m_Nnet.Init(m_t,m_T,m_tPredict,m_TPredict);

	m_lgstr.alpha = m_alpha;
	m_lgstr.beta = m_beta;
	m_lgstr.epsilon = m_epsilon;
	m_lgstr.maxOrder = m_MaxOrder;
	m_Nnet.LagerInitialization(m_i0,m_lgstr,flag_of_Inf, m_sNumDen, m_sAnaliticEquation, m_sRoots, bIncludeRealRoots);


/*	ReinitVectorsPoints();

#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if( m_vPoints1.SetCurrentMsgOnFirst() )
	{
		do
		{
			if(m_vPoints1.GetCurrentMsgIndex() == 2
				|| m_vPoints1.GetCurrentMsgIndex() == 3)
				m_vPoints1.GetCurrentMsg().toDraw = true;
		}
		while(m_vPoints1.IncrementCurrentMsg() );
	}
#else
	m_vpPoints1[2].toDraw = true;
	m_vpPoints1[3].toDraw = true;
#endif

//	UpdateAllViews(m_pView);
*/
	m_PredictError = m_Nnet.m_EPredict;
	m_error = m_lgstr.error;
	m_fund_det = m_lgstr.fund_det;

	m_vQ = m_lgstr.vQ;
	m_alphai = m_lgstr.alphai;
	m_flip_betai = m_lgstr.flip_betai;
	m_num = m_lgstr.num;
	m_den = m_lgstr.den;

/*	m_vQ.Write("D:\\LAGERS/m_vQ.txt");
	m_alphai.Write("D:\\LAGERS/m_alphai.txt");
	m_flip_betai.Write("D:\\LAGERS/m_flip_betai.txt");
	m_num.Write("D:\\LAGERS/m_num.txt");
	m_den.Write("D:\\LAGERS/m_den.txt");*/
WriteRaporto("LagerSolve end\n");
}

void CGraphsDoc::TrainNnet()
{
	m_Nnet.Default();

	m_tp.epochs = 100 / (m_Nnet.m_nModelCount + m_Nnet.m_nLagerCount);
	if (m_Len > 1000)
		m_tp.epochs /= 10;

	m_tp.goalE = 0.0000001;
	m_tp.goalQ = 0.0000001;

	m_tp.min_grad = 1e-14;
	m_tp.show = 100;
	m_tp.full_turn = 5;

	m_Nnet.Train(m_tp, m_sNumDen, m_sAnaliticEquation, m_sRoots, false);
	m_Nnet.SimulNnet();
	m_Nnet.ErrorNnet();

/*	ReinitVectorsPoints();
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if( m_vPoints1.SetCurrentMsgOnFirst() )
	{
		do
		{
			if(m_vPoints1.GetCurrentMsgIndex() == 2
				|| m_vPoints1.GetCurrentMsgIndex() == 3)
				m_vPoints1.GetCurrentMsg().toDraw = true;
		}
		while(m_vPoints1.IncrementCurrentMsg() );
	}
#else
	m_vpPoints1[2].toDraw = true;
	m_vpPoints1[3].toDraw = true;
#endif
//	UpdateAllViews(m_pView);*/
	m_error = m_Nnet.m_E;
	m_PredictError = m_Nnet.m_EPredict;
}

/*
void CGraphsDoc::OnEditParameters(void)
{
	//===== Если диалог не открыт,
	if (!m_pDlg)
	{
		//===== Динамически создаем объект диалогового класса
		m_pDlg = new CParamDlg(this);
		//===== и после этого создаем окно диалога 
		m_pDlg->Create(IDD_PARAM);
		
	}
}

void CGraphsDoc::OutWindow()
{
	if(m_isOutWnd)
		return;
/////////////////////////////

	COutLagFrm* pFrame = new COutLagFrm;
	m_pOutWnd = pFrame;
	m_pOutWnd->m_pGraphsDoc = this;
	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);


	// The one and only window has been initialized, so show and update it.
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	
	m_isOutWnd = true;

	/////////////////////////////
}

*/
void CGraphsDoc::OnImport()
{
	m_Len = m_t.Length();
	if (m_Len > 0)
	{
		m_tend = m_t.End();
		m_t0 = m_t[0];
	}
	m_LenPredict = 0;
	m_TPredict = vdouble(0);	
	m_tPredict = vdouble(0);

	AddSignal();
}
void CGraphsDoc::OnImport2()
{
	OnImport();
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if( m_vPoints1.SetCurrentMsgOnFirst() )
	{
		do
		{
			if(m_vPoints1.GetCurrentMsgIndex() == 4)
				m_vPoints1.GetCurrentMsg().toDraw = false;
		}
		while( m_vPoints1.IncrementCurrentMsg() );
	}
#else
	m_vpPoints1[4].toDraw = false;
#endif
}

void CGraphsDoc::SetTimeEnd()
{
	int len = m_Len + m_LenPredict;
	vdouble t(len), T(len);
	int i = 0;
	for (; i < m_Len; i++)
	{
		t[i] = m_t[i];
		T[i] = m_T[i];
	}
	i = m_Len;
	for (int j = 0; j < m_LenPredict; j++)
	{
		t[i] = m_tPredict[j];
		T[i] = m_TPredict[j];
		i++;
	}
	Vector<int> vi = Find(m_tend >= t),
		viPredict = Find(m_tend < t);
	m_t = t[vi];
	m_T = T[vi];
	m_tPredict = t[viPredict];
	m_TPredict = T[viPredict];
	m_Len = m_t.Length();
	m_LenPredict = m_tPredict.Length();

	ReinitVectorsPoints();
//	UpdateAllViews(m_pView);
}
void CGraphsDoc::OnFileExport() 
{
	// TODO: Add your command handler code here
/*	CFileDialog dlg(false);
	CString str, name, ext, path;

	str += "Coma Separated Values (*.csv)";
	str += (TCHAR)NULL;
	str += "*.csv";
	str += (TCHAR)NULL;

	str += "All files (*.*)";
	str += (TCHAR)NULL;
	str += "*.*";
	str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = str;
	dlg.m_ofn.nFilterIndex = 0;
	dlg.m_ofn.lpstrTitle = "Экспорт...";

	if(dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		name = dlg.GetFileName();
		ext = dlg.GetFileExt();
		if (path.Find(".") < 0)
		{
			if (dlg.m_ofn.nFilterIndex == 1)
				path += ".csv";
		}
	}
	else 
	//если пользователь выбрал отмена - выходим
		return;

	FILE *stream;
	if ((stream = fopen(path,"wt")) == NULL)
	{
		AfxMessageBox("Cannot open file.\n");
		return;
	}
	CString s;
	for (int i = 0; i < m_Len; i++)
	{
		s.Format("%g, %g\n", m_t[i], m_T[i]);
		fprintf(stream,s);
	}
	for (i = 0; i < m_LenPredict; i++)
	{
		s.Format("%g, %g\n", m_tPredict[i], m_TPredict[i]);
		fprintf(stream,s);
	}
	fclose(stream);*/
}
void CGraphsDoc::OnFileExport2() 
{
/*	// TODO: Add your command handler code here
	CFileDialog dlg(false);
	CString str, name, ext, path;

	str += "Coma Separated Values (*.csv)";
	str += (TCHAR)NULL;
	str += "*.csv";
	str += (TCHAR)NULL;

	str += "All files (*.*)";
	str += (TCHAR)NULL;
	str += "*.*";
	str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = str;
	dlg.m_ofn.nFilterIndex = 0;
	dlg.m_ofn.lpstrTitle = "Экспорт...";

	if(dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		name = dlg.GetFileName();
		ext = dlg.GetFileExt();
		if (path.Find(".") < 0)
		{
			if (dlg.m_ofn.nFilterIndex == 1)
				path += ".csv";
		}
	}
	else 
	//если пользователь выбрал отмена - выходим
		return;

	FILE *stream;
	if ((stream = fopen(path,"wt")) == NULL)
	{
		AfxMessageBox("Cannot open file.\n");
		return;
	}
	CString s;
	if (m_T2.Length() == m_Len)
	{
		for (int i = 0; i < m_Len; i++)
		{
			s.Format("%g, %g, %g\n", m_t[i], m_T[i], m_T2[i]);
			fprintf(stream,s);
		}
	}
	else
	{
		for (int i = 0; i < m_Len; i++)
		{
			s.Format("%g, %g\n", m_t[i], m_T[i]);
			fprintf(stream,s);
		}
	}
#if 0
	for (i = 0; i < m_LenPredict; i++)
	{
		s.Format("%g, %g\n", m_tPredict[i], m_TPredict[i]);
		fprintf(stream,s);
	}
#endif
	fclose(stream);*/
}
/*
void CGraphsDoc::AnaliticalString()
{
	AfxMessageBox(m_sNumDen + m_sAnaliticEquation + m_sRoots, 0);
}
*/
/*
void CGraphsDoc::SaveAnaliticalString()
{
	CFileDialog dlg(false);
	CString str, name, ext, path;

	str += "Text file (*.txt)";
	str += (TCHAR)NULL;
	str += "*.txt";
	str += (TCHAR)NULL;

	str += "All files (*.*)";
	str += (TCHAR)NULL;
	str += "*.*";
	str += (TCHAR)NULL;

	dlg.m_ofn.lpstrFilter = str;
	dlg.m_ofn.nFilterIndex = 0;
	dlg.m_ofn.lpstrTitle = "Сохранение аналитического результата...";

	if(dlg.DoModal() == IDOK)
	{
		path = dlg.GetPathName();
		name = dlg.GetFileName();
		ext = dlg.GetFileExt();
		if (path.Find(".") < 0)
		{
			if (dlg.m_ofn.nFilterIndex == 1)
				path += ".txt";
		}
	}
	else 
	//если пользователь выбрал отмена - выходим
		return;

	FILE *stream;
	if ((stream = fopen(path,"wt")) == NULL)
	{
		AfxMessageBox("Cannot open file.\n");
		return;
	}
	fprintf(stream, m_sNumDen + m_sAnaliticEquation + m_sRoots);
	fclose(stream);

}
*/
void CGraphsDoc::CovariationApply(unsigned int type)
{
	double 
		t1 = m_t[0]>m_t2[0] ? m_t[0]:m_t2[0],
		t2 = m_t.End() < m_t2.End() ? m_t.End() : m_t2.End();

	// шаг времени интерполяции 1 сек
	m_dt = 1.0 / 24.0/3600;
	vdouble n, x1, x2,
		tt = dsequence(t1, m_dt,t2);

	// 
	int 
		// Длина вектора времени
		Len = tt.Length(),
		// длина окна для ковариации 
		L = 3600,
		// шаг смещения окна
		step = L/2,
		// Число проходов ковариации		
		N = (Len - L) / step + 1,
		// Длина результата ковариации
		len_cov = (L+1)/2;

	m_vCov.resize(N);
	m_vtCov.resize(N);


	vdouble T1 = linterp(m_t,m_T,tt);
	vdouble T2 = linterp(m_t2,m_T2,tt);


	switch(type)
	{
	case 0:
		{
			covar(tt,T1, T2,  m_tCov, m_Cov);
			plot(m_tCov,m_Cov,"Ковариация","","",true,true,0,false);
			int flag_of_Inf = 0;

			m_NnetCov.DeleteAll();

			m_NnetCov.Init(m_tCov,m_Cov,m_tPredict,m_TPredict);

			m_lgstr.alpha = m_alpha;
			m_lgstr.beta = m_beta;
			m_lgstr.epsilon = m_epsilon;
			m_lgstr.maxOrder = m_MaxOrder;
			m_NnetCov.LagerInitialization(m_i0,m_lgstr,flag_of_Inf, m_sNumDen, m_sAnaliticEquation, m_sRoots,
				true);
			plot_(m_NnetCov.m_t,m_NnetCov.m_Y,"Ковариация","","",true,true,0,false);
		}
		break;
	case 1:
		{
			covar(tt,log10(T1), log10(T2),  m_tCov, m_Cov);
			plot(m_tCov,m_Cov,"Ковариация","","",true,true,0,false);
		}
		break;
	case 2:
		{
			vdouble 
				tw,
				m;
			tw.resize(N);
			//m.resize(N,len_cov);
			m.resize(len_cov,N);
			Vector<int> indexes;

			for (int n = 0; n < N; n++)
			{
				indexes = sequence(n*step, L + n*step);
				covar(tt[indexes], T1[indexes], T2[indexes],  
					m_tCov, m_Cov);
				// время середины окна 
				tw[n] = tt[n*step+L/2];
				for (int i = 0; i < len_cov; i++)
					//m(n, i) = m_Cov[i];
					m(i, n) = m_Cov[i];
			}
/*
			char str[511];
			sprintf(str, 
				"Len = %d, N = %d, L= %d, m_Cov.Length() = %d indexes.Size() = %d",
				Len, N, L, m_Cov.Length(), indexes.Size());
			MessageBox(0,str,"",0);
			plot(m_tCov,m_Cov,"Ковариация","","",true,true,0,false);
*/
			//WinSurf(x1,m_tCov,m);
			WinSurf(m_tCov,tw,m);
		}
		break;
	case 3:
		{
			Vector<int> indexes;
			m_vNnetCov.resize(N);
			for (int n = 0; n < N; n++)
			{
				indexes = sequence(n*step, L + n*step);
				covar(tt[indexes], T1[indexes], T2[indexes],  
					m_vtCov[n], m_vCov[n]);
				plot(m_vtCov[n],m_vCov[n],"","","",true,true,0,false);
				// время середины окна 
				m_vNnetCov[n].DeleteAll();

				m_vNnetCov[n].Init(m_vtCov[n],m_vCov[n]);
				int flag_of_Inf = 0;

				m_lgstr.alpha = m_alpha;
				m_lgstr.beta = m_beta;
				m_lgstr.epsilon = m_epsilon;
				m_lgstr.maxOrder = m_MaxOrder;
				m_vNnetCov[n].LagerInitialization(m_i0,m_lgstr,flag_of_Inf, m_sNumDen, m_sAnaliticEquation, m_sRoots,
					true);
				plot_(
					m_vNnetCov[n].m_t,
					m_vNnetCov[n].m_Y,"","","",true,true,0,false);
			}
		}
		break;
	}

}

void CGraphsDoc::CovariationAnalize()
{
	m_t = m_tCov;
	m_T = m_Cov;
	m_T2 = m_Cov;
	m_TPredict.resize(0);
	m_T2Predict.resize(0);
	m_tPredict.resize(0);

#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if( m_vPoints1.SetCurrentMsgOnFirst() )
	{
		do
		{
			if(m_vPoints1.GetCurrentMsgIndex() == 4
				|| m_vPoints1.GetCurrentMsgIndex() == 6)
				m_vPoints1.GetCurrentMsg().toDraw = false;
		}
		while(m_vPoints1.IncrementCurrentMsg() );
	}
#else
	m_vpPoints1[4].toDraw = false;
	m_vpPoints1[6].toDraw = false;
#endif
//	UpdateAllViews(m_pView);

}

void CGraphsDoc::OnTick(SYSTEMTIME tm, int v)
{
WriteRaporto("OnTick 1\n");
	double a = double(v);
	if (m_bIsFirstTick)
	{
WriteRaporto("OnTick m_bIsFirstTick\n");
		m_T.resize(m_T.Length(), a);
		m_bIsFirstTick = false;
		/*for(int i = 1; i < 6; i++)
		{
			m_vpPoints1[i].toDraw = false;
		}*/
	}
	//m_vpPoints1[0].maxY = m_vpPoints1[0].maxY > a ? m_vpPoints1[0].maxY : a ;
	//m_vpPoints1[0].minY = m_vpPoints1[0].minY < a ? m_vpPoints1[0].minY : a ;
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	if( m_vPoints1.SetCurrentMsgOnFirst() )
	{
		do
		{
			if(m_vPoints1.GetCurrentMsgIndex() == 0)
			{
				m_vPoints1.GetCurrentMsg().maxY = m_T.Max();
				m_vPoints1.GetCurrentMsg().minY = m_T.Min();
				m_vPoints1.GetCurrentMsg().maxX = m_t.Max();
				m_vPoints1.GetCurrentMsg().minX = m_t.Min();
			}
		}
		while(m_vPoints1.IncrementCurrentMsg() );
	}
#else
	m_vpPoints1[0].maxY = m_T.Max();
	m_vpPoints1[0].minY = m_T.Min();
	m_vpPoints1[0].maxX = m_t.Max();
	m_vpPoints1[0].minX = m_t.Min();
#endif
	m_T << a;
//	m_vtime << time;
	double t = datenum(tm);
	m_t << t;
WriteRaporto("OnTick end\n");
}
extern void WaveletNames(int wf, // флаг типа вейвлетов
	int order, // порядоак вейвлета
	int orderBiorthogonalDecomposition,
	char * name);

void CGraphsDoc::WaveletApply()
{
	vdouble *input_vector, *input_t;
	input_vector = NULL;
	input_t		 = NULL;
	// =============================================================================
	// ========================== Select the input signal ==========================
	// =============================================================================
	int g = 0;
	if (this->m_vPoints.SetCurrentVectOnFirst())
	{
		do
		{
			bool toDisp = this->m_vPoints.GetCurrentVect().GetVectorCheck();
			bool toCheck = false;
			if (toDisp)
			{
				if (g == m_wInputSigalType)
				{
					input_vector = this->m_vPoints.GetCurrentVect().GetFirstMsg().py;
					input_t		 = this->m_vPoints.GetCurrentVect().GetFirstMsg().px;
					break;
				}
				g++;
			}
		}
		// Перемещаем текущий внутренний вектор
		while(this->m_vPoints.IncrementCurrentVect());
	}
	// =============================================================================
	// =============================================================================
	//========================================
	char name[1024];
	WaveletNames(m_wf, // флаг типа вейвлетов
		m_wOrder, // порядоак вейвлета
		m_wOrderBiorthogonalDecomposition,
		name);
	Vector<Vector<int> > 
		vtau_s_ind, 
		vtau_d_ind, 
		vtau_S_ind, 
		vtau_F_ind;
	//========================================
	if(input_vector && input_vector->WaveletDecomposition(input_t,
		m_wf, // флаг вейвлета
	  m_wOrder, // порядок вейвлета
	  m_wOrderBiorthogonalDecomposition,
	  m_maxLevel, // максимальный уровенть разложения
	  vtau_s_ind,
	  m_vts,
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  vtau_d_ind, 
	  m_vtd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  vtau_S_ind,
	  m_vtSlow,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  vtau_F_ind,
	  m_vtFast,
	  m_vFast)) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	{
		char title[1024];
		if (m_wRadioRec == 1)
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low Wavelet Coefficients of %s by %s", 
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vts, m_vs,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true,  2, true
				);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High Wavelet Coefficients of %s by %s", 
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtd, m_vd, 
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel,
				true, true,  2, false);
			}
		}
		else
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low Wavelet Reconstruction of %s by %s", 
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtSlow, m_vSlow,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true,  2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High Wavelet Reconstruction of %s by %s", 
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtFast, m_vFast,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true,  2, false);
			}
		}
	}
	else
	{
		char str[255];
		sprintf(str, "NULL\nm_wInputSigalType = %d m_vPoints.vectSize() = %d m_vPoints.msgSize() = %d\ninput_vector = %x input_t = %x", 
			m_wInputSigalType, 
			m_vPoints.vectSize(),
			m_vPoints.msgSize(), (DWORD)input_vector, (DWORD)input_t);
		MessageBox(0,str,"WaveletApply()", 0);
	}
}

#ifndef DRAW_OLD_VECTOR_VDPOINTS


int CGraphsDoc::plot (vdouble& vx, vdouble& vy, 
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{
	int vect_count = m_vPoints.CreateNewVect();

	CpVDPoints pVDPoints;


	strcpy(pVDPoints.szTitle, sTitle);
	strcpy(pVDPoints.szXLabel, sXLabel);
	strcpy(pVDPoints.szYLabel, sYLabel);

	pVDPoints.px = &vx;
	pVDPoints.py = &vy;
//	pVDPoints.pt = &m_vtime;			//m_vpPoints1[0].toDraw = false;
//	pVDPoints.pt = NULL;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&vy)->Max();
	pVDPoints.minY = (&vy)->Min();
	pVDPoints.maxX = (&vx)->Max();
	pVDPoints.minX = (&vx)->Min();
	pVDPoints.toDraw = true;
	pVDPoints.toScaleX = toScaleX;
	pVDPoints.toScaleY = toScaleY;
	pVDPoints.notGist = notGist;
	pVDPoints.bTimeScale = bTimeScale	;


	m_vPoints.AddMsgToLastVect(&pVDPoints);

	return vect_count-1;
}

void CGraphsDoc::plot_(vdouble& vx, vdouble& vy, 
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{

	CpVDPoints pVDPoints;
	pVDPoints.px = &vx;
	pVDPoints.py = &vy;
//	pVDPoints.pt = &m_vtime;			//m_vpPoints1[0].toDraw = false;
//	pVDPoints.pt = NULL;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&vy)->Max();
	pVDPoints.minY = (&vy)->Min();
	pVDPoints.maxX = (&vx)->Max();
	pVDPoints.minX = (&vx)->Min();
	pVDPoints.toDraw = true;
	pVDPoints.toScaleX = toScaleX;
	pVDPoints.toScaleY = toScaleY;
	pVDPoints.notGist = notGist;
	pVDPoints.bTimeScale = bTimeScale	;
	strcat(pVDPoints.szTitle, sTitle);
	strcpy(pVDPoints.szXLabel, sXLabel);
	strcpy(pVDPoints.szYLabel, sYLabel);

	m_vPoints.AddMsgToLastVect(&pVDPoints);
}

void CGraphsDoc::plots_3(Vector<vdouble>& vx, Vector<vdouble>& vy, 
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{
	for (int j = 0; j < vx.Size(); j++)
	{
		char title[1024];
		sprintf(title, "%s level = %d",sTitle, j+1);
		plot_3(vx[j], vy[j], 
		title, sXLabel, sYLabel,
		bTimeScale, notGist, toScaleX, toScaleY);
	}
}
void CGraphsDoc::plot_3(vdouble& vx, vdouble& vy, 
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{
	int len = vx.Length();

	vdouble v;

	m_vvCommonParams.CreateNewVect();
	m_vvCommonParams.GetLastVect().AddMsg(&v);
	m_vvCommonParams.GetLastVect().GetLastMsg().resize(len);
	
	m_vtCommonParams.CreateNewVect();
	m_vtCommonParams.GetLastVect().AddMsg(&v);
	m_vtCommonParams.GetLastVect().GetLastMsg().resize(len);

	for(int i = 0; i < len; i++)
	{
		m_vtCommonParams.GetLastVect().GetLastMsg().operator[](i) = vx[i];
		m_vvCommonParams.GetLastVect().GetLastMsg().operator[](i) = vy[i];
	}
	int iplot = plot(
		m_vtCommonParams.GetLastVect().GetLastMsg(), 
		m_vvCommonParams.GetLastVect().GetLastMsg(),
		sTitle, sXLabel, sYLabel, 
		bTimeScale,notGist,toScaleX,toScaleY);
	m_vvCommonParams.GetLastVect().SetVectorData((long)iplot);
}


void CGraphsDoc::plot_3_(vdouble& vx, vdouble& vy, 
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{
	int len = vx.Length();

	vdouble v;

//	m_vvCommonParams.CreateNewVect();
	m_vvCommonParams.GetLastVect().AddMsg(&v);
	m_vvCommonParams.GetLastVect().GetLastMsg().resize(len);
	
//	m_vtCommonParams.CreateNewVect();
	m_vtCommonParams.GetLastVect().AddMsg(&v);
	m_vtCommonParams.GetLastVect().GetLastMsg().resize(len);

	for(int i = 0; i < len; i++)
	{
		m_vtCommonParams.GetLastVect().GetLastMsg().operator[](i) = vx[i];
		m_vvCommonParams.GetLastVect().GetLastMsg().operator[](i) = vy[i];
	}


	plot_(
		m_vtCommonParams.GetLastVect().GetLastMsg(), 
		m_vvCommonParams.GetLastVect().GetLastMsg(),
		sTitle, sXLabel, sYLabel, 
		bTimeScale,notGist,toScaleX,toScaleY);
}
void CGraphsDoc::plot_2(int iParam, int len,
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{
//	MessageBox(0,"1","plot_", 0);
	CpVDPoints pVDPoints;
	vdouble *px;
	vdouble *py;
	vect<class vdouble> * ptvect;
	vect<class vdouble> * pvvect;
	vdouble v;
	if (m_vvCommonParams.vectSize() > iParam && m_vvCommonParams.vectSize() > iParam)
	{
		m_vvCommonParams(iParam)->AddMsg(&v);
		m_vvCommonParams(iParam)->GetLastMsg().resize(len);
		
		m_vtCommonParams(iParam)->AddMsg(&v);
		m_vtCommonParams(iParam)->GetLastMsg().resize(len);
		int	iplot = m_vvCommonParams(iParam)->GetVectorData();
		if (iplot > -1)
		{
			ptvect = m_vtCommonParams(iParam);
			pvvect = m_vvCommonParams(iParam);


				//MessageBox(0,str,"",0);
			px = ptvect->GetLastMsgPtr(); 
			py = pvvect->GetLastMsgPtr();
/*
			plot_(
				vDoc[idoc].m_vtCommonParams(iParam)->GetLastMsg(), 
				vDoc[idoc].m_vvCommonParams(iParam)->GetLastMsg(),iplot,title, "", "", true,true,lpSelectFileDlgData->scaleModeX,false);
*/

		//	pVDPoints.pt = &m_vtime;			//m_vpPoints1[0].toDraw = false;
		//	pVDPoints.pt = NULL;				//m_vpPoints1[0].toDraw = false;
			/*pVDPoints.maxY = py->Max();
			pVDPoints.minY = py->Min();
			pVDPoints.maxX = px->Max();
			pVDPoints.minX = px->Min();*/
			pVDPoints.maxY = 1.0;
			pVDPoints.minY = 0.0;
			pVDPoints.maxX = 1.0;
			pVDPoints.minX = 0.0;
			pVDPoints.toDraw = true;
			pVDPoints.toScaleX = toScaleX;
			pVDPoints.toScaleY = toScaleY;
			pVDPoints.notGist = notGist;
			pVDPoints.bTimeScale = bTimeScale	;
			strcpy(pVDPoints.szTitle, sTitle);
			strcpy(pVDPoints.szXLabel, sXLabel);
			strcpy(pVDPoints.szYLabel, sYLabel);

			pVDPoints.px = px;
			pVDPoints.py = py;

			m_vPoints.AddMsgToIndexedVect(iplot, &pVDPoints);
		}
	}
		
//	if(m_vPoints(iplot))
//		m_vPoints(iplot)->AddMsg(&pVDPoints);
//	MessageBox(0,"end","plot_", 0);
}

void CGraphsDoc::plot (Vector<vdouble>& vx, Vector<vdouble>& vy, bool bTimeScale, bool notGist, short toScaleX, bool toScaleY)
{
	int nGraphs = vx.Size();
	if (nGraphs != vy.Size())
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::plots\n vx.Size(%i) != vy.Size(%i)",
			vx.Size(), vy.Size());
		MessageBox(0,s,"plots", 0);
		return;
	}
	if (nGraphs < 0)
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::plots\n (nGraphs(%i) < 0)",
			nGraphs);
		MessageBox(0,s,"plots", 0);
		return;
	}
	m_vPoints.CreateNewVect();
	for (int i = 0; i < nGraphs; i++)
	{
		CpVDPoints pVDPoints;
		pVDPoints.px = vx.data + i;
		pVDPoints.py = vy.data + i;
//		pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
		pVDPoints.maxY = (vy.data + i)->Max();
		pVDPoints.minY = (vy.data + i)->Min();
		pVDPoints.maxX = (vx.data + i)->Max();
		pVDPoints.minX = (vx.data + i)->Min();
		pVDPoints.toDraw = true;
		pVDPoints.toScaleX = toScaleX;
		pVDPoints.toScaleY = toScaleY;
		pVDPoints.notGist = notGist;
		pVDPoints.bTimeScale = bTimeScale;
		

		m_vPoints.AddMsgToLastVect(&pVDPoints);
	}
}
void CGraphsDoc::plots(Vector<vdouble>& vx, Vector<vdouble>& vy, 
					   bool bTimeScale, bool notGist, short toScaleX, bool toScaleY, char * sTitle, char * sX, char * sY)
{
	int nGraphs = vx.Size();
	if (nGraphs != vy.Size())
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::plots\n vx.Size(%i) != vy.Size(%i)",
			vx.Size(), vy.Size());
		MessageBox(0,s,"plots", 0);
		return;
	}
	if (nGraphs < 0)
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::plots\n (nGraphs(%i) < 0)",
			nGraphs);
		MessageBox(0,s,"plots", 0);
		return;
	}
	
	char str[31];
	for (int i = 0; i < nGraphs; i++)
	{
		CpVDPoints pVDPoints;
		pVDPoints.px = vx.data + i;
		pVDPoints.py = vy.data + i;
//		pVDPoints.pt = &m_vtime;				//m_vpPoints1[0].toDraw = false;
		pVDPoints.maxY = (vy.data + i)->Max();
		pVDPoints.minY = (vy.data + i)->Min();
		pVDPoints.maxX = (vx.data + i)->Max();
		pVDPoints.minX = (vx.data + i)->Min();
		pVDPoints.toDraw = true;
		pVDPoints.toScaleX = toScaleX;
		pVDPoints.toScaleY = toScaleY;
		pVDPoints.notGist = notGist;
		pVDPoints.bTimeScale = bTimeScale;	
		
		if (sTitle)
		{
			strcpy(pVDPoints.szTitle, sTitle);
			sprintf (str, " level = %d", i+1);
			strcat(pVDPoints.szTitle, str);
		}

		if (sX) strcpy(pVDPoints.szXLabel, sX);
		if (sY) strcpy(pVDPoints.szYLabel, sY);


		m_vPoints.CreateNewVect();
		m_vPoints.AddMsgToLastVect(&pVDPoints);
	}
}
#else
void CGraphsDoc::InitGraphics(Vector<vdouble>& vx, Vector<vdouble>& vy, bool OneGraphic, bool toDraw, short toScaleX, bool toScaleY)
{
	int nGraphs = vx.Size();
	if (nGraphs != vy.Size())
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::InitGraphics\n vx.Size(%i) != vy.Size(%i)",
			vx.Size(), vy.Size());
		MessageBox(0,s,"InitGraphics", 0);
		return;
	}
	if (nGraphs < 0)
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::InitGraphics\n (nGraphs(%i) < 0)",
			nGraphs);
		MessageBox(0,s,"InitGraphics", 0);
		return;
	}
	if (OneGraphic)
	{
		m_vpPoints.resize(1);
		m_vpPoints[0].resize(nGraphs);
		for (int i = 0; i < nGraphs; i++)
		{
			m_vpPoints[0][i].pt = &m_vtime;
			m_vpPoints[0][i].px = &vx.data[i];
			m_vpPoints[0][i].py = &vy.data[i];
			m_vpPoints[0][i].maxY = (&vy.data[i])->Max();
			m_vpPoints[0][i].minY = (&vy.data[i])->Min();
			m_vpPoints[0][i].maxX = (&vx.data[i])->Max();
			m_vpPoints[0][i].minX = (&vx.data[i])->Min();
			m_vpPoints[0][i].toDraw = toDraw;
			m_vpPoints[0][i].toScaleX = toScaleX;
			m_vpPoints[0][i].toScaleY = toScaleY;
		}
	}
	else
	{
		m_vpPoints.resize(nGraphs);
		for (int i = 0; i < nGraphs; i++)
		{
			m_vpPoints[i].resize(1);
			m_vpPoints[i][0].pt = &m_vtime;
			m_vpPoints[i][0].px = vx.data + i;
			m_vpPoints[i][0].py = vy.data + i;
			m_vpPoints[i][0].maxY = (vy.data + i)->Max();
			m_vpPoints[i][0].minY = (vy.data + i)->Min();
			m_vpPoints[i][0].maxX = (vx.data + i)->Max();
			m_vpPoints[i][0].minX = (vx.data + i)->Min();
			m_vpPoints[i][0].toDraw = toDraw;
			m_vpPoints[i][0].toScaleX = toScaleX;
			m_vpPoints[i][0].toScaleY = toScaleY;
		}
	}
}

void CGraphsDoc::InitGraphics(Vector<vdouble>& vx1, Vector<vdouble>& vy1, bool OneGraphic1, bool toDraw1, short toScaleX1, bool toScaleY1,
							  Vector<vdouble>& vx2, Vector<vdouble>& vy2, bool OneGraphic2, bool toDraw2, short toScaleX2, bool toScaleY2)
{
WriteRaporto("InitGraphics 1\n");
	int nGraphs1 = vx1.Size();
	if (nGraphs1 != vy1.Size())
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::InitGraphics\n vx.Size(%i) != vy.Size(%i)",
			vx1.Size(), vy1.Size());
		MessageBox(0,s,"InitGraphics", 0);
		return;
	}
	if (nGraphs1 < 0)
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::InitGraphics\n (nGraphs(%i) < 0)",
			nGraphs1);
		MessageBox(0,s,"InitGraphics", 0);
		return;
	}
	int nGraphs2 = vx2.Size();
	if (nGraphs2 != vy2.Size())
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::InitGraphics\n vx.Size(%i) != vy.Size(%i)",
			vx2.Size(), vy2.Size());
		MessageBox(0,s,"InitGraphics", 0);
		return;
	}
	if (nGraphs2 < 0)
	{
		char s[200];
		wsprintf(s,"Error using CGraphsDoc::InitGraphics\n (nGraphs(%i) < 0)",
			nGraphs2);
		MessageBox(0,s,"InitGraphics", 0);
		return;
	}
WriteRaporto("InitGraphics 2\n");
	if (OneGraphic1 && OneGraphic2)
	{
		m_vpPoints.resize(2);
		m_vpPoints[0].resize(nGraphs1);
		m_vpPoints[1].resize(nGraphs2);
		for (int i = 0; i < nGraphs1; i++)
		{
			m_vpPoints[0][i].pt = &m_vtime;
			m_vpPoints[0][i].px = &vx1.data[i];
			m_vpPoints[0][i].py = &vy1.data[i];
			m_vpPoints[0][i].maxY = (&vy1.data[i])->Max();
			m_vpPoints[0][i].minY = (&vy1.data[i])->Min();
			m_vpPoints[0][i].maxX = (&vx1.data[i])->Max();
			m_vpPoints[0][i].minX = (&vx1.data[i])->Min();
			m_vpPoints[0][i].toDraw = toDraw1;
			m_vpPoints[0][i].toScaleX = toScaleX1;
			m_vpPoints[0][i].toScaleY = toScaleY1;
		}
		for (i = 0; i < nGraphs2; i++)
		{
			m_vpPoints[1][i].pt = &m_vtime;
			m_vpPoints[1][i].px = &vx2.data[i];
			m_vpPoints[1][i].py = &vy2.data[i];
			m_vpPoints[1][i].maxY = (&vy2.data[i])->Max();
			m_vpPoints[1][i].minY = (&vy2.data[i])->Min();
			m_vpPoints[1][i].maxX = (&vx2.data[i])->Max();
			m_vpPoints[1][i].minX = (&vx2.data[i])->Min();
			m_vpPoints[1][i].toDraw = toDraw2;
			m_vpPoints[1][i].toScaleX = toScaleX2;
			m_vpPoints[1][i].toScaleY = toScaleY2;
		}
	}
WriteRaporto("InitGraphics 3\n");
	if (!OneGraphic1 && !OneGraphic2)
	{
WriteRaporto("InitGraphics 2 if 1\n");
		m_vpPoints.resize(nGraphs1 + nGraphs2);
WriteRaporto("InitGraphics 2 if 2\n");
		for (int i = 0; i < nGraphs1; i++)
		{
			m_vpPoints[i].resize(1);
			m_vpPoints[i][0].pt = &m_vtime;
			m_vpPoints[i][0].px = vx1.data + i;
			m_vpPoints[i][0].py = vy1.data + i;
			m_vpPoints[i][0].maxY = (vy1.data + i)->Max();
			m_vpPoints[i][0].minY = (vy1.data + i)->Min();
			m_vpPoints[i][0].maxX = (vx1.data + i)->Max();
			m_vpPoints[i][0].minX = (vx1.data + i)->Min();
			m_vpPoints[i][0].toDraw = toDraw1;
			m_vpPoints[i][0].toScaleX = toScaleX1;
			m_vpPoints[i][0].toScaleY = toScaleY1;
		}
WriteRaporto("InitGraphics 2 if 3\n");
		for (i = 0; i < nGraphs2; i++)
		{
			m_vpPoints[nGraphs1 + i].resize(1);
			m_vpPoints[nGraphs1 + i][0].pt = &m_vtime;
			m_vpPoints[nGraphs1 + i][0].px = vx2.data + i;
			m_vpPoints[nGraphs1 + i][0].py = vy2.data + i;
			m_vpPoints[nGraphs1 + i][0].maxY = (vy2.data + i)->Max();
			m_vpPoints[nGraphs1 + i][0].minY = (vy2.data + i)->Min();
			m_vpPoints[nGraphs1 + i][0].maxX = (vx2.data + i)->Max();
			m_vpPoints[nGraphs1 + i][0].minX = (vx2.data + i)->Min();
			m_vpPoints[nGraphs1 + i][0].toDraw = toDraw2;
			m_vpPoints[nGraphs1 + i][0].toScaleX = toScaleX2;
			m_vpPoints[nGraphs1 + i][0].toScaleY = toScaleY2;
		}
WriteRaporto("InitGraphics 2 if end\n");
	}
WriteRaporto("InitGraphics 4\n");
	if (!OneGraphic1 && OneGraphic2)
	{
		m_vpPoints.resize(nGraphs1 + 1);
		for (int i = 0; i < nGraphs1; i++)
		{
			m_vpPoints[i].resize(1);
			m_vpPoints[i][0].pt = &m_vtime;
			m_vpPoints[i][0].px = vx1.data + i;
			m_vpPoints[i][0].py = vy1.data + i;
			m_vpPoints[i][0].maxY = (vy1.data + i)->Max();
			m_vpPoints[i][0].minY = (vy1.data + i)->Min();
			m_vpPoints[i][0].maxX = (vx1.data + i)->Max();
			m_vpPoints[i][0].minX = (vx1.data + i)->Min();
			m_vpPoints[i][0].toDraw = toDraw1;
			m_vpPoints[i][0].toScaleX = toScaleX1;
			m_vpPoints[i][0].toScaleY = toScaleY1;
		}
		m_vpPoints[nGraphs1].resize(nGraphs2);
		for (i = 0; i < nGraphs2; i++)
		{
			m_vpPoints[nGraphs1][i].px = vx2.data + i;
			m_vpPoints[nGraphs1][i].pt = &m_vtime;
			m_vpPoints[nGraphs1][i].py = vy2.data + i;
			m_vpPoints[nGraphs1][i].maxY = (vy2.data + i)->Max();
			m_vpPoints[nGraphs1][i].minY = (vy2.data + i)->Min();
			m_vpPoints[nGraphs1][i].maxX = (vx2.data + i)->Max();
			m_vpPoints[nGraphs1][i].minX = (vx2.data + i)->Min();
			m_vpPoints[nGraphs1][i].toDraw = toDraw2;
			m_vpPoints[nGraphs1][i].toScaleX = toScaleX2;
			m_vpPoints[nGraphs1][i].toScaleY = toScaleY2;
		}
	}
WriteRaporto("InitGraphics 5\n");
	if (OneGraphic1 && !OneGraphic2)
	{
		m_vpPoints.resize(1 + nGraphs2);
		m_vpPoints[0].resize(nGraphs1);
		for (int i = 0; i < nGraphs1; i++)
		{
			m_vpPoints[0][i].pt = &m_vtime;
			m_vpPoints[0][i].px = vx1.data + i;
			m_vpPoints[0][i].py = vy1.data + i;
			m_vpPoints[0][i].maxY = (vy1.data + i)->Max();
			m_vpPoints[0][i].minY = (vy1.data + i)->Min();
			m_vpPoints[0][i].maxX = (vx1.data + i)->Max();
			m_vpPoints[0][i].minX = (vx1.data + i)->Min();
			m_vpPoints[0][i].toDraw = toDraw1;
			m_vpPoints[0][i].toScaleX = toScaleX1;
			m_vpPoints[0][i].toScaleY = toScaleY1;
		}
		for (i = 0; i < nGraphs2; i++)
		{
			m_vpPoints[i + 1].resize(1);
			m_vpPoints[i + 1][0].pt = &m_vtime;
			m_vpPoints[i + 1][0].px = vx2.data + i;
			m_vpPoints[i + 1][0].py = vy2.data + i;
			m_vpPoints[i + 1][0].maxY = (vy2.data + i)->Max();
			m_vpPoints[i + 1][0].minY = (vy2.data + i)->Min();
			m_vpPoints[i + 1][0].maxX = (vx2.data + i)->Max();
			m_vpPoints[i + 1][0].minX = (vx2.data + i)->Min();
			m_vpPoints[i + 1][0].toDraw = toDraw2;
			m_vpPoints[i + 1][0].toScaleX = toScaleX2;
			m_vpPoints[i + 1][0].toScaleY = toScaleY2;
		}
	}
WriteRaporto("InitGraphics end\n");
}

void CGraphsDoc::InitGraphic(Vector<SYSTEMTIME>& vtime, vdouble& vx, vdouble& vy, bool toDraw, bool toScaleX, bool toScaleY, bool notGist)
{
	int nGraphs = 1;
	int size = m_vpPoints.Size();

	Vector<Vector<CpVDPoints> > vpPoints;
	vpPoints.resize(size);

	for(int j = 0; j<size; j++)
	{
		vpPoints[j].resize(m_vpPoints[j].Size());
		for(int i = 0; i < m_vpPoints[j].Size(); i++)
		{
			vpPoints[j][i].maxX		= m_vpPoints[j][i].maxX;
			vpPoints[j][i].minX		= m_vpPoints[j][i].minX;
			vpPoints[j][i].maxY		= m_vpPoints[j][i].maxY;
			vpPoints[j][i].minY		= m_vpPoints[j][i].minY;
			vpPoints[j][i].pt		= m_vpPoints[j][i].pt;
			vpPoints[j][i].px		= m_vpPoints[j][i].px;
			vpPoints[j][i].py		= m_vpPoints[j][i].py;
			vpPoints[j][i].toDraw	= m_vpPoints[j][i].toDraw;
			vpPoints[j][i].notGist	= m_vpPoints[j][i].notGist;
			vpPoints[j][i].toScaleX = m_vpPoints[j][i].toScaleX;
			vpPoints[j][i].toScaleX = m_vpPoints[j][i].toScaleX;
		}
	}

	m_vpPoints.resize(size + 1);

	for(j = 0; j<size; j++)
	{
		m_vpPoints[j].resize(vpPoints[j].Size());
		for(int i = 0; i < m_vpPoints[j].Size(); i++)
		{
			m_vpPoints[j][i].maxX		= vpPoints[j][i].maxX;
			m_vpPoints[j][i].minX		= vpPoints[j][i].minX;
			m_vpPoints[j][i].maxY		= vpPoints[j][i].maxY;
			m_vpPoints[j][i].minY		= vpPoints[j][i].minY;
			m_vpPoints[j][i].pt			= vpPoints[j][i].pt;
			m_vpPoints[j][i].px			= vpPoints[j][i].px;
			m_vpPoints[j][i].py			= vpPoints[j][i].py;
			m_vpPoints[j][i].toDraw		= vpPoints[j][i].toDraw;
			m_vpPoints[j][i].notGist	= vpPoints[j][i].notGist;
			m_vpPoints[j][i].toScaleX	= vpPoints[j][i].toScaleX;
			m_vpPoints[j][i].toScaleX	= vpPoints[j][i].toScaleX;
		}
	}

	m_vpPoints[size].resize(nGraphs);
	for (int i = 0; i < nGraphs; i++)
	{
		m_vpPoints[size][i].notGist = notGist;
		m_vpPoints[size][i].pt = &vtime;
		m_vpPoints[size][i].px = &vx;
		m_vpPoints[size][i].py = &vy;
		m_vpPoints[size][i].maxY = (&vy)->Max();
		m_vpPoints[size][i].minY = (&vy)->Min();
		m_vpPoints[size][i].maxX = (&vx)->Max();
		m_vpPoints[size][i].minX = (&vx)->Min();
		m_vpPoints[size][i].toDraw = toDraw;
		m_vpPoints[size][i].toScaleX = toScaleX;
		m_vpPoints[size][i].toScaleY = toScaleY;
	}
}
#endif
void CGraphsDoc::OnWaveletApply()
{
	/*
	//===== Если диалог не открыт,
#if 1
	if (!m_pWaveDlg)
	{
		//===== Динамически создаем объект диалогового класса
		m_pWaveDlg = new CWaveDlg(this);
		m_pWaveDlg->Create(IDD_WAV_PARAM);
	}
	//===== и после этого создаем окно диалога 
#else
	if (!m_pWaveDlg)
	{
		//===== Динамически создаем объект диалогового класса
		m_pWaveDlg = new CWaveDlg(this);
	}
	if (m_pWaveDlg->DoModal()==IDOK)
		WaveletApply();
#endif
*/
}

void CGraphsDoc::WaveletDisplay()
{
	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;
	vdouble dh, dg, rh, rg,	d, s;

	WaveletFilters(m_wf,m_wOrder, m_wOrderBiorthogonalDecomposition,
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);

	w_fipsi(dh,dg,
			 nd1,nd2,ngd1,ngd2,7,
			 m_vxFI,m_vFI,m_vxPSI,m_vPSI);
	//========================================
	char name[1024];
	WaveletNames(m_wf, // флаг типа вейвлетов
		m_wOrder, // порядоак вейвлета
		m_wOrderBiorthogonalDecomposition,
		name);
	//========================================
	char title[2048];
	sprintf(title, "Display of high frequency wavelet %s", name);
	plot_3(m_vxFI,  m_vFI, 
		title, "", "",
		false,  true, 0, false);

	sprintf(title, "Display of low frequency wavelet %s", name);
	plot_3(m_vxPSI, m_vPSI,
		title, "", "",
		false, true, 1,  false);

}	
void CGraphsDoc::LagerDisplay()
{
	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;
	vdouble dh, dg, rh, rg,	d, s;

	WaveletFilters(m_wf,m_wOrder, m_wOrderBiorthogonalDecomposition,
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);

	w_fipsi(dh,dg,
			 nd1,nd2,ngd1,ngd2,7,
			 m_vxFI,m_vFI,m_vxPSI,m_vPSI);

//	DeleteCalculatedPlots();
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	plot(m_vxFI,  m_vFI, 
		"Дісплей високочастотного вейвлет фільтру", "", "",
		false,  true, 0, false);
	plot(m_vxPSI, m_vPSI,
		"Дісплей низькочастотного вейвлет фільтру", "", "",
		false, true, 1,  false);
#else
	InitGraphic(m_vtime, m_vxFI, m_vFI, true, false, false, true);
	InitGraphic(m_vtime, m_vxPSI, m_vPSI, true, true, false, true);
#endif

}	


void CGraphsDoc::WaveletEpsilonApply()
{
	vdouble *input_vector, *input_t;
	input_vector = NULL;
	input_t		 = NULL;
	// =============================================================================
	// ========================== Select the input signal ==========================
	// =============================================================================
	int g = 0;
	if (this->m_vPoints.SetCurrentVectOnFirst())
	{
		do
		{
			bool toDisp = this->m_vPoints.GetCurrentVect().GetVectorCheck();
			bool toCheck = false;
			if (toDisp)
			{
				if (g == m_wInputSigalType)
				{
					input_vector = this->m_vPoints.GetCurrentVect().GetFirstMsg().py;
					input_t		 = this->m_vPoints.GetCurrentVect().GetFirstMsg().px;
					break;
				}
				g++;
			}
		}
		// Перемещаем текущий внутренний вектор
		while(this->m_vPoints.IncrementCurrentVect());
	}
	// =============================================================================
	// =============================================================================
	// =============================================================================


	if (m_wf0 != m_wf || 
		m_wOrder0 != m_wOrder || 
		m_wEpsilon0 != m_wEpsilon ||
		m_wOrderBiorthogonalDecomposition0 != m_wOrderBiorthogonalDecomposition)
	{
		WaveletEpsilon(
		  m_wf, // флаг вейвлета
		  m_wOrder, // порядок вейвлета
		  m_wOrderBiorthogonalDecomposition,
		  m_wEpsilon,
		  m_dh,
		  m_dg, 
		  m_rh,
		  m_rg,
		  m_left_h,
		  m_right_h,
		  m_left_g,
		  m_right_g);

		m_wf0 = m_wf; 
		m_wOrder0 = m_wOrder; 
		m_wEpsilon0 = m_wEpsilon;
		m_wOrderBiorthogonalDecomposition0 = m_wOrderBiorthogonalDecomposition;
	}
	//========================================
	char name[1024];
	WaveletNames(m_wf, // флаг типа вейвлетов
		m_wOrder, // порядоак вейвлета
		m_wOrderBiorthogonalDecomposition,
		name);
	//========================================
	  Vector<Vector<int> > 
		vtau_s_ind, 
		vtau_d_ind, 
		vtau_S_ind, 
		vtau_F_ind;
	if( input_vector && input_vector->WaveletDecomposition(input_t,
	  m_dh,
	  m_dg, 
	  m_rh,
	  m_rg,
	  m_left_h,
	  m_right_h,
	  m_left_g,
	  m_right_g,
	  m_maxLevel, // максимальный уровенть разложения
	  vtau_s_ind,
	  m_vts,
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  vtau_d_ind, 
	  m_vtd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  vtau_S_ind,
	  m_vtSlow,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  vtau_F_ind,
	  m_vtFast,
	  m_vFast)) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	{
		char title[1024];
		if (m_wRadioRec == 1)
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low (with epsilon = %0.2f) Wavelet Coefficients of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vts, m_vs,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High (with epsilon = %0.2f) Wavelet Coefficients of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtd, m_vd,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2,  false);
			}
		}
		else
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low (with epsilon = %0.2f) Wavelet Reconstruction of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtSlow, m_vSlow,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High (with epsilon = %0.2f) Wavelet Reconstruction of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtFast, m_vFast,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2,  false);
			}
		}
	}
	else
		MessageBox(0,"NULL","WaveletEpsilonApply()", 0);

}


void CGraphsDoc::WaveletApply1()
{
	vdouble *input_vector, *input_t;
	input_vector = NULL;
	input_t		 = NULL;
	// =============================================================================
	// ========================== Select the input signal ==========================
	// =============================================================================
	int g = 0;
	if (this->m_vPoints.SetCurrentVectOnFirst())
	{
		do
		{
			bool toDisp = this->m_vPoints.GetCurrentVect().GetVectorCheck();
			bool toCheck = false;
			if (toDisp)
			{
				if (g == m_wInputSigalType)
				{
					input_vector = this->m_vPoints.GetCurrentVect().GetFirstMsg().py;
					input_t		 = this->m_vPoints.GetCurrentVect().GetFirstMsg().px;
					break;
				}
				g++;
			}
		}
		// Перемещаем текущий внутренний вектор
		while(this->m_vPoints.IncrementCurrentVect());
	}
	// =============================================================================
	// =============================================================================
	// =============================================================================


	/*if (m_wf0 != m_wf || 
		m_wOrder0 != m_wOrder || 
		m_wOrderBiorthogonalDecomposition0 != m_wOrderBiorthogonalDecomposition)
	{*/
		WaveletGetLeftRight(
		  m_wf, // флаг вейвлета
		  m_wOrder, // порядок вейвлета
		  m_wOrderBiorthogonalDecomposition,
		  m_dh,
		  m_dg, 
		  m_rh,
		  m_rg,
		  m_left_h,
		  m_right_h,
		  m_left_g,
		  m_right_g);

		/*m_wf0 = m_wf; 
		m_wOrder0 = m_wOrder; 
		m_wOrderBiorthogonalDecomposition0 = m_wOrderBiorthogonalDecomposition;
	}*/
	//========================================
	char name[1024];
	WaveletNames(m_wf, // флаг типа вейвлетов
		m_wOrder, // порядоак вейвлета
		m_wOrderBiorthogonalDecomposition,
		name);
	//========================================
	  Vector<Vector<int> > 
		vtau_s_ind, 
		vtau_d_ind, 
		vtau_S_ind, 
		vtau_F_ind;
	if( input_vector && input_vector->WaveletDecomposition1(input_t,
	  m_dh,
	  m_dg, 
	  m_rh,
	  m_rg,
	  m_left_h,
	  m_right_h,
	  m_left_g,
	  m_right_g,
	  m_maxLevel, // максимальный уровенть разложения
	  vtau_s_ind,
	  m_vts,
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  vtau_d_ind, 
	  m_vtd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  vtau_S_ind,
	  m_vtSlow,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  vtau_F_ind,
	  m_vtFast,
	  m_vFast)) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	{
		char title[1024];
		if (m_wRadioRec == 1)
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low (with epsilon = %0.2f) Wavelet Coefficients of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vts, m_vs,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High (with epsilon = %0.2f) Wavelet Coefficients of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtd, m_vd,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2,  false);
			}
		}
		else
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low (with epsilon = %0.2f) Wavelet Reconstruction of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtSlow, m_vSlow,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High (with epsilon = %0.2f) Wavelet Reconstruction of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtFast, m_vFast,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2,  false);
			}
		}
	}
	else
		MessageBox(0,"NULL","WaveletEpsilonApply()", 0);

}



void CGraphsDoc::WaveletApply2()
{
	vdouble *input_vector, *input_t;
	input_vector = NULL;
	input_t		 = NULL;
	// =============================================================================
	// ========================== Select the input signal ==========================
	// =============================================================================
	int g = 0;
	if (this->m_vPoints.SetCurrentVectOnFirst())
	{
		do
		{
			bool toDisp = this->m_vPoints.GetCurrentVect().GetVectorCheck();
			bool toCheck = false;
			if (toDisp)
			{
				if (g == m_wInputSigalType)
				{
					input_vector = this->m_vPoints.GetCurrentVect().GetFirstMsg().py;
					input_t		 = this->m_vPoints.GetCurrentVect().GetFirstMsg().px;
					break;
				}
				g++;
			}
		}
		// Перемещаем текущий внутренний вектор
		while(this->m_vPoints.IncrementCurrentVect());
	}
	// =============================================================================
	// =============================================================================
	// =============================================================================


	/*if (m_wf0 != m_wf || 
		m_wOrder0 != m_wOrder || 
		m_wOrderBiorthogonalDecomposition0 != m_wOrderBiorthogonalDecomposition)
	{*/
		WaveletGetLeftRight(
		  m_wf, // флаг вейвлета
		  m_wOrder, // порядок вейвлета
		  m_wOrderBiorthogonalDecomposition,
		  m_dh,
		  m_dg, 
		  m_rh,
		  m_rg,
		  m_left_h,
		  m_right_h,
		  m_left_g,
		  m_right_g);

		/*m_wf0 = m_wf; 
		m_wOrder0 = m_wOrder; 
		m_wOrderBiorthogonalDecomposition0 = m_wOrderBiorthogonalDecomposition;
	}*/
	//========================================
	char name[1024];
	WaveletNames(m_wf, // флаг типа вейвлетов
		m_wOrder, // порядоак вейвлета
		m_wOrderBiorthogonalDecomposition,
		name);
	//========================================
	  Vector<Vector<int> > 
		vtau_s_ind, 
		vtau_d_ind, 
		vtau_S_ind, 
		vtau_F_ind;
	if( input_vector && input_vector->WaveletDecomposition(input_t,
	  m_dh,
	  m_dg, 
	  m_rh,
	  m_rg,
	  m_left_h,
	  m_right_h,
	  m_left_g,
	  m_right_g,
	  m_maxLevel, // максимальный уровенть разложения
	  vtau_s_ind,
	  m_vts,
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  vtau_d_ind, 
	  m_vtd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  vtau_S_ind,
	  m_vtSlow,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  vtau_F_ind,
	  m_vtFast,
	  m_vFast)) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	{
		char title[1024];
		if (m_wRadioRec == 1)
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low (with epsilon = %0.2f) Wavelet Coefficients of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vts, m_vs,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High (with epsilon = %0.2f) Wavelet Coefficients of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtd, m_vd,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2,  false);
			}
		}
		else
		{
			if (this->m_bWavShowLow)
			{
				sprintf(title, "Low (with epsilon = %0.2f) Wavelet Reconstruction of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtSlow, m_vSlow,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2, true);
			}
			if (this->m_bWavShowHigh)
			{
				sprintf(title, "High (with epsilon = %0.2f) Wavelet Reconstruction of %s by %s", m_wEpsilon,
					this->m_vPoints.GetCurrentVect().GetFirstMsg().szTitle, name);
				plots_3(m_vtFast, m_vFast,
				title, 
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szXLabel,
				this->m_vPoints.GetCurrentVect().GetFirstMsg().szYLabel, 
				true, true, 2,  false);
			}
		}
	}
	else
		MessageBox(0,"NULL","WaveletEpsilonApply()", 0);

}



bool CGraphsDoc::Covariation(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, bool toReverse)
{
WriteRaporto("Covariation 1\n");
#ifdef USE_WAVELETS

	int nlevels = pDoc1->m_vFast.Size();
	if (nlevels != pDoc1->m_vtFast.Size())
		return 0;
	if (nlevels != pDoc2->m_vFast.Size())
		return 0;
	if (nlevels != pDoc2->m_vtFast.Size())
		return 0;
	vdouble C, K1, K2;
WriteRaporto("Covariation 2\n");

	m_vCov.resize(nlevels);
WriteRaporto("Covariation 3\n");
	m_vtCov.resize(nlevels);
WriteRaporto("Covariation 4\n");

	

	for (int lev = 0; lev < nlevels; lev++)
	{
		int len1 = pDoc1->m_vFast[lev].Length();
		if (len1 != pDoc1->m_vtFast[lev].Length())
			return 0;
		int len2 = pDoc2->m_vFast[lev].Length();
		if (len2 != pDoc2->m_vtFast[lev].Length())
			return 0;

		int L = len1/2;
		if (toReverse)
			m_vCov[lev].ReverseCovariation( pDoc1->m_vFast[lev], pDoc2->m_vFast[lev], L);
		else
			m_vCov[lev].Covariation( pDoc1->m_vFast[lev], pDoc2->m_vFast[lev], L);
		m_vtCov[lev].Sequence(0, pDoc1->m_dt, pDoc1->m_dt*(L-1));

	}

	nlevels = pDoc1->m_vSlow.Size();
	if (nlevels != pDoc1->m_vtSlow.Size())
		return 0;
	if (nlevels != pDoc2->m_vSlow.Size())
		return 0;
	if (nlevels != pDoc2->m_vtSlow.Size())
		return 0;

	m_vCov2.resize(nlevels);
	m_vtCov2.resize(nlevels);

	

	for (lev = 0; lev < nlevels; lev++)
	{
		int len1 = pDoc1->m_vSlow[lev].Length();
		if (len1 != pDoc1->m_vtSlow[lev].Length())
			return 0;
		int len2 = pDoc2->m_vSlow[lev].Length();
		if (len2 != pDoc2->m_vtSlow[lev].Length())
			return 0;

		int L = len1/2;

		double mean1 = pDoc1->m_vSlow[lev].Mean();
		double mean2 = pDoc2->m_vSlow[lev].Mean();

		if (toReverse)
			m_vCov2[lev].ReverseCovariation( pDoc1->m_vSlow[lev] - mean1, pDoc2->m_vSlow[lev] - mean2, L);
		else
			m_vCov2[lev].Covariation( pDoc1->m_vSlow[lev] - mean1, pDoc2->m_vSlow[lev] - mean2, L);
		m_vtCov2[lev].Sequence(0, pDoc1->m_dt, pDoc1->m_dt*(L-1));

	}
	InitGraphics(m_vtCov2, m_vCov2, false, true, false, false,
				m_vtCov, m_vCov, false, true, false, false);
#endif// USE_WAVELETS

	int len1 = pDoc1->m_T.Length();
	if (len1 != pDoc1->m_t.Length())
		return 0;
	int len2 = pDoc2->m_T.Length();
	if (len2 != pDoc2->m_t.Length())
		return 0;

	int L = len1/2;

	double mean1 = pDoc1->m_T.Mean();
	double mean2 = pDoc2->m_T.Mean();

	if (toReverse)
		m_T.ReverseCovariation( pDoc1->m_T - mean1, pDoc2->m_T - mean2, L);
	else
		m_T.Covariation( pDoc1->m_T - mean1, pDoc2->m_T - mean2, L);
	m_t.Sequence(0, pDoc1->m_dt, pDoc1->m_dt*(L-1));
//	LagerSolve();
WriteRaporto("Covariation end\n");
	return 1;
}

void CGraphsDoc::resize(int _len)
{
WriteRaporto("CGraphsDoc::resize 1\n");
	m_Len = _len;
	m_T.resize(m_Len);	
WriteRaporto("CGraphsDoc::resize 2\n");
	m_t.resize(m_Len);
WriteRaporto("CGraphsDoc::resize 3\n");
//	m_vtime.resize(m_Len);
WriteRaporto("CGraphsDoc::resize end\n");
}
void CGraphsDoc::resize2(int _len)
{
	m_Len2 = _len;
	m_T2.resize(m_Len2);	
	m_t2.resize(m_Len2);
//	m_vtime.resize(m_Len2);
}
void CGraphsDoc::InitLagerNnet(int nparam)
{
	if (nparam < m_vvCommonParams.vectSize())
	{
		m_Nnet.DeleteAll();

		m_Nnet.Init(
			m_vtCommonParams(nparam)->GetLastMsg(), 
			m_vvCommonParams(nparam)->GetLastMsg(),
			0.0);
	}
}
void CGraphsDoc::LagerResultPlot()
{
#if 1
	int len = m_Nnet.m_t.Length();
	vdouble v;

	m_vvCommonParams.CreateNewVect();
	m_vtCommonParams.CreateNewVect();

	m_vvCommonParams.GetLastVect().AddMsg(&v);
	m_vvCommonParams.GetLastVect().GetLastMsg().resize(len);
	
	m_vtCommonParams.GetLastVect().AddMsg(&v);
	m_vtCommonParams.GetLastVect().GetLastMsg().resize(len);
	for (int i = 1; i < len; i++)
	{
		m_vtCommonParams.GetLastVect().GetLastMsg()[i] = m_Nnet.m_t[i];
		m_vvCommonParams.GetLastVect().GetLastMsg()[i] = m_Nnet.m_T[i];
	}
	plot(
		m_vtCommonParams.GetLastVect().GetLastMsg(), 
		m_vvCommonParams.GetLastVect().GetLastMsg(),
		"", "", "", 
		false,true,0,false);

	m_vvCommonParams.GetLastVect().AddMsg(&v);
	m_vvCommonParams.GetLastVect().GetLastMsg().resize(len);
	
	m_vtCommonParams.GetLastVect().AddMsg(&v);
	m_vtCommonParams.GetLastVect().GetLastMsg().resize(len);
	for (int i = 1; i < len; i++)
	{
		m_vtCommonParams.GetLastVect().GetLastMsg()[i] = m_Nnet.m_t[i];
		m_vvCommonParams.GetLastVect().GetLastMsg()[i] = m_Nnet.m_Y[i];
	}
	plot_(
		m_vtCommonParams.GetLastVect().GetLastMsg(), 
		m_vvCommonParams.GetLastVect().GetLastMsg(),
		"", "", "", 
		false,true,0,false);
#else

	plot(
		m_Nnet.m_t, 
		m_Nnet.m_T, 
		"", "", "", 
		false,true,0,false);
	plot_(
		m_Nnet.m_t, 
		m_Nnet.m_Y, 
		"", "", "", 
		false,true,0,false);
#endif
}

void CGraphsDoc::SetEarthQuakesSkale(short skaleModeX, double B0, double L0, double near_r, double magnitudeBorder, double depthIntervalMin, double depthIntervalMax)
{
	double 
		a = 6378245.,
		b = 6356863.0188,
		e = sqrt(a*a - b*b) / a;


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// Artjuhovka
	//double L0 = (36. + 30./60.) * PI / 180;
	//double B0 = (49. + 40./60.) * PI / 180;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// Antarktida
	//double L0 = -(63. + 46./60.+ 59./3600.) * PI / 180;
	//double B0 = -(65. + 02./60.+ 36./3660.) * PI / 180;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	distance(B0 * PI / 180, L0 * PI / 180, m_Beq * PI / 180, m_Leq * PI / 180,
			  m_Aeq, m_Req);

#if 0
			  double 
		N0 = a / ( sqrt(1. - e*e * sin(B0)*sin(B0)) ),
		x0 = N0 * cos(B0) * cos(L0),
		y0 = N0 * cos(B0) * sin(L0),
		z0 = N0 * sin(B0) * (1 - e*e);

	vdouble 
		N = a/(sqrt(1.- e*e * sin(m_Beq)*sin(m_Beq)) ),
		x = N0 * cos(m_Beq * PI / 180) * cos(m_Leq * PI / 180),
		y = N0 * cos(m_Beq * PI / 180) * sin(m_Leq * PI / 180),
		z = N0 * sin(m_Beq * PI / 180) * (1 - e*e);

	m_Req = sqrt( (x-x0)*(x-x0) + (y-y0)*(y-y0) + (z-z0)*(z-z0) );
	//m_req = m_Meq / sqrt(a*m_Req);
#endif
//	m_req = a * m_Meq / sqrt(a*m_Req);
	m_req = m_Meq * exp(-m_Req/(a*PI));
	//m_req = log10(a*a*a *a*pow(10, m_Meq) / m_Req / m_Req / m_Req / m_Req);
	
	/*char str[255];
	sprintf(str, "ceil(0.5) = %lf floor(0.5) = %lf",
		ceil(0.5), floor(0.5)); // ceil(0.5) = 1.0, floor(0.5) = 0.0
	MessageBox(0,str,"",0);*/

/*		m_tDayEq,					// посуточная шкала времени для землетрясений
		m_nFonEqPerDay,				// число фоновых землетрясений за сутки
		m_nLargeEqPerDay,			// число крупных землетрясений в сутки

		m_nFonEqPerFirstHalfDay,	// число фоновых землетрясений в первую половину суток
		m_nLargeEqPerFirstHalfDay,	// число крупных землетрясений в первую половину суток
		
		m_nFonEqPerSecondHalfDay,   // число фоновых землетрясений во вторую половину суток
		m_nLargeEqPerSecondHalfDay, // число крупных землетрясений во вторую половину суток
		
		// сортировка землетрясений на Запад от долготы пункта наблюдения

		m_nFonEqPerDay_West,			// число фоновых землетрясений за сутки
		m_nLargeEqPerDay_West,			// число крупных землетрясений в сутки

		m_nFonEqPerFirstHalfDay_West,	// число фоновых землетрясений в первую половину суток
		m_nLargeEqPerFirstHalfDay_West,	// число крупных землетрясений в первую половину суток
		
		m_nFonEqPerSecondHalfDay_West,   // число фоновых землетрясений во вторую половину суток
		m_nLargeEqPerSecondHalfDay_West, // число крупных землетрясений во вторую половину суток

		// сортировка землетрясений на Восток от долготы пункта наблюдения

		m_nFonEqPerDay_East,				// число фоновых землетрясений за сутки
		m_nLargeEqPerDay_East,			// число крупных землетрясений в сутки

		m_nFonEqPerFirstHalfDay_East,	// число фоновых землетрясений в первую половину суток
		m_nLargeEqPerFirstHalfDay_East,	// число крупных землетрясений в первую половину суток
		
		m_nFonEqPerSecondHalfDay_East,   // число фоновых землетрясений во вторую половину суток
		m_nLargeEqPerSecondHalfDay_East, // число крупных землетрясений во вторую половину суток
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	double L0 = (36. + 30./60.) * PI / 180;
	double B0 = (49. + 40./60.) * PI / 180;
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

*/

	// посуточная шкала времени для землетрясений
	m_tDayEq = dsequence(floor(m_tEarthQuakes[0]), 1.0, floor(m_tEarthQuakes.End()));
	int days = m_tDayEq.Length();

	m_nFonEqPerDay.resize(days, 0.0);
	m_nLargeEqPerDay.resize(days, 0.0);
	m_nFonEqPerFirstHalfDay.resize(days, 0.0);
	m_nLargeEqPerFirstHalfDay.resize(days, 0.0);
	m_nFonEqPerSecondHalfDay.resize(days, 0.0);
	m_nLargeEqPerSecondHalfDay.resize(days, 0.0);

	m_nFonEqPerDay_East.resize(days, 0.0);
	m_nLargeEqPerDay_East.resize(days, 0.0);
	m_nFonEqPerFirstHalfDay_East.resize(days, 0.0);
	m_nLargeEqPerFirstHalfDay_East.resize(days, 0.0);
	m_nFonEqPerSecondHalfDay_East.resize(days, 0.0);
	m_nLargeEqPerSecondHalfDay_East.resize(days, 0.0);

	m_nNearFonEqPerDay.resize(days, 0.0);
	m_nNearLargeEqPerDay.resize(days, 0.0);

	m_nFonEqPerDay_West.resize(days, 0.0);
	m_nLargeEqPerDay_West.resize(days, 0.0);
	m_nFonEqPerFirstHalfDay_West.resize(days, 0.0);
	m_nLargeEqPerFirstHalfDay_West.resize(days, 0.0);
	m_nFonEqPerSecondHalfDay_West.resize(days, 0.0);
	m_nLargeEqPerSecondHalfDay_West.resize(days, 0.0);

	m_eqMinMagnitude.resize(days, 0.0); //Магнитуды землетрясений
	m_eqMeanMagnitude.resize(days, 0.0); //Магнитуды землетрясений
	m_eqMaxMagnitude.resize(days, 0.0); //Магнитуды землетрясений
	m_eqNearMaxMagnitude.resize(days, 0.0); //Магнитуды землетрясений

	m_eqMinH.resize(days, 0.0); //Глубины землетрясений
	m_eqMeanH.resize(days, 0.0); //Глубины землетрясений
	m_eqMaxH.resize(days, 0.0); //Глубины землетрясений


	m_eqMinAzimut.resize(days, 0.0); // Азимуты направлений на эпицентры
	m_eqMeanAzimut.resize(days, 0.0); // Азимуты направлений на эпицентры
	m_eqMaxAzimut.resize(days, 0.0); // Азимуты направлений на эпицентры

	m_eqMinDistance.resize(days, 0.0); // расстояние до эпицентров
	m_eqMeanDistance.resize(days, 0.0); // расстояние до эпицентров
	m_eqMaxDistance.resize(days, 0.0); // расстояние до эпицентров

	m_eqLargestB.resize(days, 0.0); //Геодезические широты эпицентров землетрясений
	m_eqLargestL.resize(days, 0.0); //Геодезические долготы эпицентров землетрясений
	m_eqLargestH.resize(days, 0.0); //
	m_eqNearLargestB.resize(days, 0.0); //
	m_eqNearLargestL.resize(days, 0.0); //
	m_eqNearLargestH.resize(days, 0.0); //
	m_eqLargestAzimut.resize(days, 0.0);
	m_eqLargestAzimut2.resize(days, 0.0);
	m_eqLargestDistance.resize(days, 0.0);

	this->m_magnitudeBorder = magnitudeBorder;//4.8;
	double logn0 = L0/PI*180;

	int d = 0;
	int j = 0;// index in a day
	int j_near = 0;// index in a day
	this->m_near_r = near_r;
	this->m_depthIntervalMax = depthIntervalMax;
	this->m_depthIntervalMin = depthIntervalMin;

	for (int i = 0; i < m_tEarthQuakes.Length(); i++)
	{
		if (m_Aeq[i] < 0.0)
		{
			m_Aeq[i] += 2*PI;
		} 
		// пока начало суток текущего землетрясения больше дня статистики увеличиваем номер дня статистики

		while ( floor(m_tEarthQuakes[i]) > m_tDayEq[d])
		{
			// new day
			d++;
			j = 0;
			j_near = 0;
		}
		// если расстояни от точки наблюдения до эпицентра меньше радиуса near_r км, 
		// то набираем статисику near
		if (m_Req[i] < near_r * 1000 )
		{
			if (j_near == 0)
			{
				m_eqNearMaxMagnitude [d]	= m_Meq[i]; //Магнитуды землетрясений
				m_eqNearLargestH[d] = m_Heq[i]; //
				m_eqNearLargestB[d]	= m_Beq[i]; //Геодезические широты эпицентров землетрясений
				m_eqNearLargestL[d] = m_Leq[i]; //Геодезические долготы эпицентров землетрясений
			}
			else
			{
				if(m_eqNearMaxMagnitude [d] < m_Meq[i])//Магнитуды землетрясений
				{
					m_eqNearMaxMagnitude [d] = m_Meq[i]; 
					m_eqNearLargestB[d]	= m_Beq[i]; //Геодезические широты эпицентров землетрясений
					m_eqNearLargestL[d] = m_Leq[i]; //Геодезические долготы эпицентров землетрясений
					m_eqNearLargestH[d] = m_Heq[i]; //
					//m_eqNearLargestAzimut[d] = m_Aeq[i];
					//m_eqNearLargestDistance[d] = m_Req[i];
				}
			}
			if (m_Meq[i] < this->m_magnitudeBorder)
				m_nNearFonEqPerDay[d] += 1.0;
			else
				m_nNearLargeEqPerDay[d] += 1.0;
		}
		if (j == 0)
		{
			// start dayly statistic
			m_eqMinMagnitude [d]	= m_Meq[i]; //Магнитуды землетрясений
			m_eqMeanMagnitude[d]	= m_Meq[i]; //Магнитуды землетрясений
			m_eqMaxMagnitude [d]	= m_Meq[i]; //Магнитуды землетрясений

			m_eqLargestB[d] = m_Beq[i]; //Геодезические широты эпицентров землетрясений
			m_eqLargestL[d] = m_Leq[i]; //Геодезические долготы эпицентров землетрясений
			m_eqLargestH[d] = m_Heq[i]; //
			m_eqLargestAzimut[d] = m_Aeq[i];
			m_eqLargestDistance[d] = m_Req[i];

			m_eqMinH[d]		= m_Heq[i]; //Глубины землетрясений
			m_eqMeanH[d]	= m_Heq[i]; //Глубины землетрясений
			m_eqMaxH[d]		= m_Heq[i]; //Глубины землетрясений

			// Азимуты направлений на эпицентры
			m_eqMinAzimut[d]		= m_Aeq[i]; // Азимуты направлений на эпицентры
			m_eqMeanAzimut[d]		= m_Aeq[i]; // Азимуты направлений на эпицентры
			m_eqMaxAzimut[d]		= m_Aeq[i]; // Азимуты направлений на эпицентры

			// расстояние до эпицентров
			m_eqMinDistance[d]		= m_Req[i]; // расстояние до эпицентров
			m_eqMeanDistance[d]		= m_Req[i]; // расстояние до эпицентров
			m_eqMaxDistance[d]		= m_Req[i]; // расстояние до эпицентров
		}
		else
		{
			if(m_eqMinMagnitude [d] > m_Meq[i])//Магнитуды землетрясений
				m_eqMinMagnitude [d] = m_Meq[i]; 
			m_eqMeanMagnitude[d] += m_Meq[i]; //Магнитуды землетрясений
			if(m_eqMaxMagnitude [d] < m_Meq[i])//Магнитуды землетрясений
			{
				m_eqMaxMagnitude [d] = m_Meq[i]; 
				m_eqLargestB[d]	= m_Beq[i]; //Геодезические широты эпицентров землетрясений
				m_eqLargestL[d] = m_Leq[i]; //Геодезические долготы эпицентров землетрясений
				m_eqLargestH[d] = m_Heq[i]; //
				m_eqLargestAzimut[d] = m_Aeq[i];
				m_eqLargestDistance[d] = m_Req[i];
			}


			if(m_eqMinH[d]	> m_Heq[i]) //Глубины землетрясений
				m_eqMinH[d] = m_Heq[i];
			m_eqMeanH[d] += m_Heq[i]; //Глубины землетрясений
			if(m_eqMaxH[d]	< m_Heq[i]) //Глубины землетрясений
				m_eqMaxH[d] = m_Heq[i];

			// Азимуты направлений на эпицентры
			if(m_eqMinAzimut[d] > m_Aeq[i]) // Азимуты направлений на эпицентры
				m_eqMinAzimut[d] = m_Aeq[i];
			m_eqMeanAzimut[d] += m_Aeq[i]; // Азимуты направлений на эпицентры
			if(m_eqMaxAzimut[d] < m_Aeq[i]) // Азимуты направлений на эпицентры
				m_eqMaxAzimut[d] = m_Aeq[i];

			// расстояние до эпицентров
			if(m_eqMinDistance[d] > m_Req[i]) // расстояние до эпицентров
				m_eqMinDistance[d] = m_Req[i];
			m_eqMeanDistance[d] += m_Req[i]; // расстояние до эпицентров
			if(m_eqMaxDistance[d] < m_Req[i]) // расстояние до эпицентров
				m_eqMaxDistance[d] = m_Req[i];
		}



		if (m_Meq[i] < this->m_magnitudeBorder)
		 m_nFonEqPerDay[d] += 1.0;
		else
		 m_nLargeEqPerDay[d] += 1.0;

		double timeofday = m_tEarthQuakes[i] - floor(m_tEarthQuakes[i]);
		if (timeofday < 0.5) // FirstHalfDay
		{
			if (m_Meq[i] < this->m_magnitudeBorder)
			 m_nFonEqPerFirstHalfDay[d] += 1.0;
			else
			 m_nLargeEqPerFirstHalfDay[d] += 1.0;
		}
		else
		{
			if (m_Meq[i] < this->m_magnitudeBorder)
			 m_nFonEqPerSecondHalfDay[d] += 1.0;
			else
			 m_nLargeEqPerSecondHalfDay[d] += 1.0;
		}

		bool isEast;
		if (logn0 > 0.0)
		{
			isEast = m_Leq[i] > 0.0 ? m_Leq[i] > logn0 : m_Leq[i] < -180.+logn0;
		}
		else
		{
			isEast = m_Leq[i] > 0.0 ? m_Leq[i] < 180.+logn0 : m_Leq[i] > logn0;
		}
		if (isEast)
		{
			if (m_Meq[i] < this->m_magnitudeBorder)
			 m_nFonEqPerDay_East[d] += 1.0;
			else
			 m_nLargeEqPerDay_East[d] += 1.0;

			double timeofday = m_tEarthQuakes[i] - floor(m_tEarthQuakes[i]);
			if (timeofday < 0.5) // FirstHalfDay
			{
				if (m_Meq[i] < this->m_magnitudeBorder)
				 m_nFonEqPerFirstHalfDay_East[d] += 1.0;
				else
				 m_nLargeEqPerFirstHalfDay_East[d] += 1.0;
			}
			else
			{
				if (m_Meq[i] < this->m_magnitudeBorder)
				 m_nFonEqPerSecondHalfDay_East[d] += 1.0;
				else
				 m_nLargeEqPerSecondHalfDay_East[d] += 1.0;
			}
		}
		else
		{
			if (m_Meq[i] < this->m_magnitudeBorder)
			 m_nFonEqPerDay_West[d] += 1.0;
			else
			 m_nLargeEqPerDay_West[d] += 1.0;

			double timeofday = m_tEarthQuakes[i] - floor(m_tEarthQuakes[i]);
			if (timeofday < 0.5) // FirstHalfDay
			{
				if (m_Meq[i] < this->m_magnitudeBorder)
				 m_nFonEqPerFirstHalfDay_West[d] += 1.0;
				else
				 m_nLargeEqPerFirstHalfDay_West[d] += 1.0;
			}
			else
			{
				if (m_Meq[i] < this->m_magnitudeBorder)
				 m_nFonEqPerSecondHalfDay_West[d] += 1.0;
				else
				 m_nLargeEqPerSecondHalfDay_West[d] += 1.0;
			}
		}
		j++;
	}
	
	m_eqMeanDistance		/= (m_nFonEqPerDay+m_nLargeEqPerDay);
	m_eqMeanAzimut			/= (m_nFonEqPerDay+m_nLargeEqPerDay);
	m_eqMeanMagnitude		/= (m_nFonEqPerDay+m_nLargeEqPerDay);
	m_eqMeanH				/= (m_nFonEqPerDay+m_nLargeEqPerDay);

	m_eqMeanH *= -1.0;
	m_eqMinH *= -1.0;
	m_eqMaxH *= -1.0;
	
	m_eqMinAzimut		*= 180. / PI; // Азимуты направлений на эпицентры
	m_eqMeanAzimut		*= 180. / PI; // Азимуты направлений на эпицентры
	m_eqMaxAzimut		*= 180. / PI; // Азимуты направлений на эпицентры
	m_eqLargestAzimut 	*= 180. / PI;

	double az = m_eqLargestAzimut[days-1];

	for (int i = days-1; i >=0 ; i--)
	{
		if (m_eqMaxMagnitude[i] >= 5.8)
		{
			az = m_eqLargestAzimut2[i] = m_eqLargestAzimut[i];
		}
		else
		{
			m_eqLargestAzimut2[i] = az;
		}
	}

	m_eqLargestH *= -1.0; //
	m_eqNearLargestH *= -1.0; //

/*	plot(m_tDayEq, m_nFonEqPerDay,
		"Число фоновых землетрясений","","",
		true, true, 1, false);
	plot(m_tDayEq, m_nLargeEqPerDay,
		"Число крупных землетрясений","","",
		true, true, 1, false);*/

	char title[255];
	sprintf(title, "Число фоновых и крупных (>=%1.1f) землетрясений",  
		this->m_magnitudeBorder);

	plot_3(m_tDayEq, m_nFonEqPerDay,
		title,"","",
		true, true, skaleModeX, false);
	plot_3_(m_tDayEq, m_nLargeEqPerDay,
		"","","",
		true, true, skaleModeX, false);

/*	plot(m_tDayEq, m_nFonEqPerDay,
		"Число фоновых землетрясений","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_nLargeEqPerDay,
		"Число крупных землетрясений","","",
		true, true, skaleModeX, false);

	m_nEqPerDay = m_nFonEqPerDay + m_nLargeEqPerDay;

	plot(m_tDayEq, m_nEqPerDay,
		"Суммарное число землетрясений","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_nFonEqPerFirstHalfDay,
		"Число фоновых и крупных землетрясений первая половина суток","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerFirstHalfDay,
		"","","",
		true, true, skaleModeX, false);


	plot(m_tDayEq, m_nFonEqPerSecondHalfDay,
		"Число фоновых и крупных землетрясений вторая половина суток","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerSecondHalfDay,
		"","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_nFonEqPerDay_East,
		"Число фоновых и крупных землетрясений к востоку от долготы точки наблюдения","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerDay_East,
		"","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_nFonEqPerFirstHalfDay_East,
		"Число фоновых и крупных землетрясений первая половина суток к востоку от долготы точки наблюдения","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerFirstHalfDay_East,
		"","","",
		true, true, skaleModeX, false);


	plot(m_tDayEq, m_nFonEqPerSecondHalfDay_East,
		"Число фоновых и крупных землетрясений вторая половина суток к востоку от долготы точки наблюдения","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerSecondHalfDay_East,
		"","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_nFonEqPerDay_West,
		"Число фоновых и крупных землетрясений к западу от долготы точки наблюдения","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerDay_West,
		"","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_nFonEqPerFirstHalfDay_West,
		"Число фоновых и крупных землетрясений первая половина суток к западу от долготы точки наблюдения","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerFirstHalfDay_West,
		"","","",
		true, true, skaleModeX, false);


	plot(m_tDayEq, m_nFonEqPerSecondHalfDay_West,
		"Число фоновых и крупных землетрясений вторая половина суток к западу от долготы точки наблюдения","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_nLargeEqPerSecondHalfDay_West,
		"","","",
		true, true, skaleModeX, false);
*/
	plot_3(m_tDayEq, m_eqMaxMagnitude,
		"Магнитуда мощнейшего за день землетрясения","","",
		true, true, skaleModeX, false);
//	plot_(m_tDayEq, m_eqMeanMagnitude,
//		"","","",
//		true, true, skaleModeX, false);
//	plot_(m_tDayEq, m_eqMinMagnitude,
//		"","","",
//		true, true, skaleModeX, false);

	plot_3(m_tDayEq, m_eqLargestH,
		"Глубина мощнейшего за день землетрясения","","",
		true, true, skaleModeX, false);
/*
	plot(m_tDayEq, m_eqLargestB,
		"Широта мощнейшего за день землетрясения","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_eqLargestL,
		"Долгота мощнейшего за день землетрясения","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_eqLargestDistance,
		"Расстояние в метрах до мощнейшего за день землетрясения","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_eqLargestAzimut,
		"Азимут на мощнейшее за день землетрясение","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_eqLargestAzimut2,
		"Азимут2 на мощнейшее за день землетрясение","","",
		true, true, skaleModeX, false);



	plot(m_tDayEq, m_eqMaxH,
		"Масимальная, минимальная и средняя глубина эпицентра","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_eqMeanH,
		"","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_eqMinH,
		"","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_eqMaxAzimut,
		"Масимальный, минимальный и средний азимут из точки наблюдения к эпицентрам","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_eqMeanAzimut,
		"","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_eqMinAzimut,
		"","","",
		true, true, skaleModeX, false);

	plot(m_tDayEq, m_eqMaxDistance,
		"Масимальное, минимальное и среднее расстояние от точки наблюдения до эпицентров","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_eqMeanDistance,
		"","","",
		true, true, skaleModeX, false);
	plot_(m_tDayEq, m_eqMinDistance,
		"","","",
		true, true, skaleModeX, false);

*/


	sprintf(title, "Число фоновых и крупных (>=%1.1f) землетрясений в радиусе %d км от %d широты %d долготы",  
		this->m_magnitudeBorder,
		int(near_r), int(B0), int(L0));
	plot_3(m_tDayEq, m_nNearFonEqPerDay,
		title,"","",
		true, true, skaleModeX, false);
	plot_3_(m_tDayEq, m_nNearLargeEqPerDay,
		"","","",
		true, true, skaleModeX, false);
	sprintf(title, "Магнитуда мощнейшего за день землетрясения в радиусе %d км от %d широты %d долготы", int(near_r), int(B0), int(L0));
	plot_3(m_tDayEq, m_eqNearMaxMagnitude,
		title,"","",
		true, true, skaleModeX, false);
	sprintf(title, "Глубина мощнейшего за день землетрясения в радиусе %d км от %d широты %d долготы", int(near_r), int(B0), int(L0));
	plot_3(m_tDayEq, m_eqNearLargestH,
		title,"","",
		true, true, skaleModeX, false);




#ifndef DRAW_OLD_VECTOR_VDPOINTS
/*	plot(m_tEarthQuakes, m_req,
		"Магнитуды землетрясений, приведенные к расстоянию","","",
		true, false, true, false);
//	plot(m_tEarthQuakes, m_Aeq,
//		"Азимут из пункта наблюдения на эпицентр землетрясения","","",
//		true, false, true, false);
	plot(m_tEarthQuakes, m_Meq,
		"Магнитуды землетрясений","","",
		true, false, true, false);
	plot(m_tEarthQuakes, m_Heq,
		"Глубины землетрясений","","",
		true, false, true, false);
//	plot(m_tEarthQuakes, m_Req,
//		"Расстояние от эпицентра до точки наблюдения","","",
//		true, false, true, false);
//	plot(m_tEarthQuakes, m_Beq,
//		"Геодезические широты эпицентров землетрясений","","",
//		true, false, true, false);
//	plot(m_tEarthQuakes, m_Leq,
//		"Геодезические долготы эпицентров землетрясений","","",
//		true, false, true, false);*/
#else
	InitGraphic(m_vtimeEarthQuakes, m_tEarthQuakes,m_TEarthQuakes, true, true, false, false);
#endif
}
void CGraphsDoc::LogariphmOfDispersion()
{
WriteRaporto("LogariphmOfDispersion()\n");
	double nonZeroMin;
	bool wasInit = false;

	for(int i = 0; i < m_Disp.Length(); i++)
	{
		if(!wasInit)
		{
			if(m_Disp[i] > 0)
			{
				nonZeroMin = m_Disp[i];
				wasInit = true;
			}
		}
		else
		{
			if(m_Disp[i] > 0)
			{
				nonZeroMin = m_Disp[i] < nonZeroMin ? m_Disp[i] : nonZeroMin;
			}
		}
	}
	double log10_nonZeroMin = log10(nonZeroMin);
	m_LogDisp.resize(m_Disp.Length());

	for(int i = 0; i < m_Disp.Length(); i++)
	{
		if(m_Disp[i] > 0)
		{
			m_LogDisp[i] = log10(m_Disp[i]);
		}
		else
		{
			m_LogDisp[i] = log10_nonZeroMin;
		}
	}




WriteRaporto("LogariphmOfDispersion() 2\n");
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	plot(m_t, m_LogDisp,
		"","","",true, true, 1, false);
#else
	InitGraphic(m_vtime, m_t,m_LogD, true, true, false, true);
#endif
WriteRaporto("LogariphmOfDispersion() end\n");
}

void CGraphsDoc::LogariphmOfSignal2()
{
	m_LogT2 = log10(m_T2);
	plot(m_t2, m_LogT2,
		"Логарифм активности сигнала 2","","",
		true,true, 1, false);
}
void CGraphsDoc::LogariphmOfSignal()
{
WriteRaporto("LogariphmOfSignal()\n");
	double nonZeroMin;
	bool wasInit = false;

	for(int i = 0; i< m_T.Length(); i++)
	{
		if(!wasInit)
		{
			if(m_T[i] > 0)
			{
				nonZeroMin = m_T[i];
				wasInit = true;
			}
		}
		else
		{
			if(m_T[i] > 0)
			{
				nonZeroMin = m_T[i] < nonZeroMin ? m_T[i] : nonZeroMin;
			}
		}
	}
	double log10_nonZeroMin = log10(nonZeroMin);
	m_LogT.resize(m_T.Length());

	for(int i = 0; i< m_T.Length(); i++)
	{
		if(m_T[i] > 0)
		{
			m_LogT[i] = log10(m_T[i]);
		}
		else
		{
			m_LogT[i] = log10_nonZeroMin;
		}
	}




WriteRaporto("LogariphmOfSignal() 2\n");
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	//plot(m_vtime, m_t, m_LogT, true, true, false);
	plot(m_t, m_LogT,
		"Логарифм активності","","",
		true,true, 1, false);
#else
	InitGraphic(m_vtime, m_t,m_LogT, true, true, false, true);
#endif
WriteRaporto("LogariphmOfSignal() end\n");
}

void CGraphsDoc::DeleteCalculatedPlots()
{
	m_vPoints.clearVect();
}

void CGraphsDoc::SetDispersionPlot()
{
	plot(m_t, m_Disp,
		"","","",
		true, true, 1, false);

}

void CGraphsDoc::LogariphmOfFiltredSignal2()
{
	m_LogTFiltred2 = log10(m_TFiltred2);
	plot(m_tFiltred2, m_LogTFiltred2,
		"Логарифм вейвлет фильтрации активности 2", 
		"", "Логарифм активности",
		true, true, 1, false);
}
void CGraphsDoc::LogariphmOfFiltredSignal()
{
WriteRaporto("LogariphmOfFiltredSignal()\n");
	double nonZeroMin;
	bool wasInit = false;

	for(int i = 0; i< m_TFiltred.Length(); i++)
	{
		if(!wasInit)
		{
			if(m_TFiltred[i] > 0)
			{
				nonZeroMin = m_TFiltred[i];
				wasInit = true;
			}
		}
		else
		{
			if(m_TFiltred[i] > 0)
			{
				nonZeroMin = m_TFiltred[i] < nonZeroMin ? m_TFiltred[i] : nonZeroMin;
			}
		}
	}
	double log10_nonZeroMin = log10(nonZeroMin);
	m_LogTFiltred.resize(m_TFiltred.Length());

	for(int i = 0; i< m_TFiltred.Length(); i++)
	{
		if(m_TFiltred[i] > 0)
		{
			m_LogTFiltred[i] = log10(m_TFiltred[i]);
		}
		else
		{
			m_LogTFiltred[i] = log10_nonZeroMin;
		}
	}
WriteRaporto("LogariphmOfFiltredSignal() 2\n");
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	plot(m_tFiltred, m_LogTFiltred,
		"Логарифм вейвлет фільтрації активності", 
		"", "Логарифм активності",
		true, true, 1, false);
#else
	InitGraphic(m_vtime, m_t,m_LogT, true, true, false, true);
#endif
WriteRaporto("LogariphmOfFiltredSignal() end\n");
}

void CGraphsDoc::Energy()
{
	vdouble sum = (
		vDoc[0].m_LogT+
		vDoc[1].m_LogT+
		vDoc[2].m_LogT)/3.0;

	m_Energy = zeros(sum.Length());
	for (int i = 0; i < m_Energy.Length(); i++)
		if (sum[i]!=0)
			m_Energy[i] = m_LogT[i]/sum[i];

	plot(m_t, m_Energy,
		"Енергія XYZ","","",
		true, true, 1, false);
}

void CGraphsDoc::EnergyOfFiltred()
{
	vdouble sum = (
		vDoc[0].m_LogTFiltred+
		vDoc[1].m_LogTFiltred+
		vDoc[2].m_LogTFiltred)/3.0;

	m_EnergyOfFiltred = zeros(sum.Length());
	for (int i = 0; i < m_EnergyOfFiltred.Length(); i++)
		if (sum[i]!=0)
			m_EnergyOfFiltred[i] = m_LogTFiltred[i]/sum[i];




	plot(m_tLogTFiltred, m_EnergyOfFiltred,
		"Енергія фільтрації XYZ","","",
		true, true, 1, false);

}

void CGraphsDoc::FiltredEnergy()
{

}

void CGraphsDoc::FiltredEnergyOfFiltred()
{

}

void CGraphsDoc::SurfTwoInstruments()
{
	double 
		t1 = m_t[0]>m_t2[0] ? m_t[0]:m_t2[0],
		t2 = m_t.End() < m_t2.End() ? m_t.End() : m_t2.End();

	vdouble n, x1, x2,
		tt = dsequence(t1, 1.0 / 24.0/3600,t2);
	vdouble T1 = linterp(m_t,m_T,tt);
	vdouble T2 = linterp(m_t2,m_T2,tt);

	hist2(log10(T1), log10(T2), 100, 100,   n,  x1, x2);

	WinSurf(x1 , x2 , n);

}

void CGraphsDoc::Plot3DTwoInstruments()
{
	double 
		t1 = m_t[0]>m_t2[0] ? m_t[0]:m_t2[0],
		t2 = m_t.End() < m_t2.End() ? m_t.End() : m_t2.End();

	vdouble n, x1, x2,
		tt = dsequence(t1, 1.0 / 24.0/3600,t2);
	vdouble T1 = linterp(m_t,m_T,tt);
	vdouble T2 = linterp(m_t2,m_T2,tt);


	WinSurf(log10(T1) , log10(T2) , tt);

}

void CGraphsDoc::CorrectTimeScale()
{
	vdouble 
		diff_t = m_t.DiffVector(),
		t2 = m_t[sequence(0,m_t.Length()-2)];

	double 
		mean = diff_t.Mean(),
		fabs_mean = fabs(mean);

	vdouble abs_diff_t_mean = abs(diff_t - mean);

	Vector<bool> vbl = abs_diff_t_mean < fabs_mean;
	Vector<int> indexes = Find(vbl);

	m_T2 = diff_t[indexes];
	m_t2 = t2[indexes];

	double dt = m_T2.Median();
	char str[50];
	sprintf(str,"mean dt = %lf", dt*3600*24);
	MessageBox(0,str,"",0);

	m_T2 *= 3600*24;

	plot(m_t2, m_T2,"","","",true, true, 1, false);
	bool loop_flag = true, for_flag = true;

	int i = diff_t.Length() - 1;

	int n_corr = 0;

	while ( i > 0 )
	{
#if 0
		if (diff_t[i] < 0.0)
		{
	/*char str[250];
	sprintf(str," i = %d diff_t[i] = %lf m_t[i] = %lf m_t[i+1]=%lf", i, diff_t[i], m_t[i], m_t[i+1]);
	MessageBox(0,str,"diff_t[i] < 0.0",0);*/
			m_t[i] += diff_t[i] - dt;
			diff_t[i] -= diff_t[i] - dt;
			if (i>0)
				diff_t[i-1] += diff_t[i] - dt;
#else
		if (diff_t[i] <= 0.0)
		{
	/*char str[250];
	sprintf(str," i = %d diff_t[i] = %lf m_t[i] = %lf m_t[i+1]=%lf", i, diff_t[i], m_t[i], m_t[i+1]);
	MessageBox(0,str,"diff_t[i] < 0.0",0);*/
			m_t[i] = m_t[i+1] - dt;
			diff_t = m_t.DiffVector();
			n_corr++;


#endif
	/*sprintf(str," i = %d diff_t[i] = %lf m_t[i] = %lf m_t[i+1]=%lf", i, diff_t[i], m_t[i], m_t[i+1]);
	MessageBox(0,str,"",0);*/

			}
			i--;
		}

	if (n_corr > 0)
	{
		char ss[255];
		sprintf(ss, "Выполнено %d корректировок", n_corr);
		MessageBox(0,ss,"CorrectTimeScale",0);
	}

	
}

void CGraphsDoc::AngleLog3(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle)
{
	
	m_XYZ3AngleLog = atan2(m_LogT, sqrt((pDoc1->m_LogT*pDoc1->m_LogT)+(pDoc2->m_LogT*pDoc2->m_LogT)))*180/PI;
	plot(m_t, m_XYZ3Angle,
		szTitle,"","",
		true,true, 1, false);

}
void CGraphsDoc::AngleLog32(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle1, LPCSTR szTitle2)
{
	
	m_XYZ3AngleLog = atan2(m_LogT, sqrt((pDoc1->m_LogT*pDoc1->m_LogT)+(pDoc2->m_LogT*pDoc2->m_LogT)))*180/PI;
	m_XYZ3AngleLog2 = atan2(m_LogT2, sqrt((pDoc1->m_LogT2*pDoc1->m_LogT2)+(pDoc2->m_LogT2*pDoc2->m_LogT2)))*180/PI;
	plot(m_t, m_XYZ3AngleLog,
		szTitle1,"","",
		true,true, 1, false);
	plot(m_t2, m_XYZAngleLog2,
		szTitle2,"","",
		true,true, 1, false);

}

void CGraphsDoc::AngleLog(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle)
{
	
	m_XYZAngleLog = atan2(pDoc1->m_LogT, pDoc2->m_LogT)*180/PI;
	plot(m_t, m_XYZAngleLog,
		szTitle,"","",
		true,true, 1, false);

}
void CGraphsDoc::AngleLog2(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle1, LPCSTR szTitle2)
{
	
	m_XYZAngleLog = atan2(pDoc1->m_LogT, pDoc2->m_LogT)*180/PI;
	m_XYZAngleLog2 = atan2(pDoc1->m_LogT2, pDoc2->m_LogT2)*180/PI;
	plot(m_t, m_XYZAngleLog,
		szTitle1,"","",
		true,true, 1, false);
	plot(m_t2, m_XYZAngleLog2,
		szTitle2,"","",
		true,true, 1, false);

}

void CGraphsDoc::Angle3(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle)
{
	
	m_XYZ3Angle = atan2(m_T, sqrt((pDoc1->m_T*pDoc1->m_T)+(pDoc2->m_T*pDoc2->m_T)))*180/PI;
	plot(m_t, m_XYZ3Angle,
		szTitle,"","",
		true,true, 1, false);

}
void CGraphsDoc::Angle32(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle1, LPCSTR szTitle2)
{
	
	m_XYZ3Angle = atan2(m_T, sqrt((pDoc1->m_T*pDoc1->m_T)+(pDoc2->m_T*pDoc2->m_T)))*180/PI;
	m_XYZ3Angle2 = atan2(m_T2, sqrt((pDoc1->m_T2*pDoc1->m_T2)+(pDoc2->m_T2*pDoc2->m_T2)))*180/PI;
	plot(m_t, m_XYZ3Angle,
		szTitle1,"","",
		true,true, 1, false);
	plot(m_t2, m_XYZAngle2,
		szTitle2,"","",
		true,true, 1, false);

}

void CGraphsDoc::Angle(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle)
{
	
	m_XYZAngle = atan2(pDoc1->m_T, pDoc2->m_T)*180/PI;
	plot(m_t, m_XYZAngle,
		szTitle,"","",
		true,true, 1, false);

}
void CGraphsDoc::Angle2(CGraphsDoc *pDoc1, CGraphsDoc *pDoc2, LPCSTR szTitle1, LPCSTR szTitle2)
{
	
	m_XYZAngle = atan2(pDoc1->m_T, pDoc2->m_T)*180/PI;
	m_XYZAngle2 = atan2(pDoc1->m_T2, pDoc2->m_T2)*180/PI;
	plot(m_t, m_XYZAngle,
		szTitle1,"","",
		true,true, 1, false);
	plot(m_t2, m_XYZAngle2,
		szTitle2,"","",
		true,true, 1, false);

}

void CGraphsDoc::HistOfSignal()
{
	// построение гистограммы по сигналу, по временным интервалам и по логарифму временных интервалов.
	long 
		N_T			= 1000,
		N_log_T		= 1000,
		N_tau		= 1000,
		N_log_tau	= 1000;

	double 
		dt = 1.0,
		max_T = m_T.Max(),
		min_T = m_T.Min(),
		min_tau = dt / max_T,
		max_tau = 0.0;
	if (min_T > 0)
		max_tau = dt / min_T;
	else
	{
		int zero_count = 0,
			max_zero_count = 0;
		for(int i = 0; i < m_T.Length();i++)
		{
			if (m_T[i] == 0)
			{
				zero_count++;
			}
			else
			{
				if (zero_count > max_zero_count)
					max_zero_count = zero_count;
				zero_count = 0;
			}
		}
		max_tau = dt*max_zero_count;
	}

	double 
		min_log_tau = log10(min_tau),
		max_log_tau = log10(max_tau);


	vdouble 
		hist_vector_tau(N_tau, 0.0),
		hist_vector_log_tau(N_log_tau, 0.0),
		hist_vector_T(N_T, 0.0),
		hist_vector_log_T(N_log_T, 0.0);

	double 
		step_tau = (max_tau - min_tau) / N_tau,
		step_log_tau = (log10(max_tau) - log10(min_tau)) / N_log_tau,
		step_T = (max_T - min_T) / N_T,
		step_log_T = (log10(max_T) - log10(min_T)) / N_log_T;

	double tau;
	bool collect_zeros = false;
	int 
		hist_tau_index,
		hist_log_tau_index;

	for (int i = 0; i < m_T.Length(); i++)
	{
		if( m_T[i] > 0.0)
		{
			if(collect_zeros)
			{
				hist_tau_index = int((tau - min_tau)/(max_tau - min_tau)*double(N_tau-1));
				if(hist_tau_index >= 0 && hist_tau_index < N_tau)
					hist_vector_tau[hist_tau_index] += 1.0;

				hist_log_tau_index = int((log10(tau) - min_log_tau)/(max_log_tau - min_log_tau)*double(N_log_tau-1));
				if(hist_log_tau_index >= 0 && hist_log_tau_index < N_log_tau)
					hist_vector_log_tau[hist_log_tau_index] += 1.0;
			}
			tau = dt / m_T[i];
			hist_tau_index = int((tau - min_tau)/(max_tau - min_tau)*double(N_tau-1));
			if(hist_tau_index >= 0 && hist_tau_index < N_tau)
				hist_vector_tau[hist_tau_index] += m_T[i];

			hist_log_tau_index = int((log10(tau) - min_log_tau)/(max_log_tau - min_log_tau)*double(N_log_tau-1));
				if(hist_log_tau_index >= 0 && hist_log_tau_index < N_log_tau)
					hist_vector_log_tau[hist_log_tau_index] += m_T[i];
		}
		else
		{
			if (!collect_zeros)
			{
				tau = dt;
				collect_zeros = true;
			}
			else
			{
				tau += dt;
			}

		}
	}
	m_tHist = dsequence(min_log_tau, N_log_tau, max_log_tau);
	m_Hist  = hist_vector_log_tau;

	char str[255];
	sprintf(str, "max_tau = %lf min_tau = %lf ", max_tau, min_tau);
	MessageBox(0, str, "", 0);

	plot(m_tHist, m_Hist,
		"Гистограмма интевалов между импульсами сигнала","","",
		false,true, 0, false);



}
void CGraphsDoc::HistOfSignal_old()
{
	double *p;

	if ((p = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_T.Length()*sizeof(double))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"createCommonFile()", 0);
		return;
	}
	for (int i = 0; i < m_T.Length(); i++)
	{
		p[i] = m_T[i];
	}
	double mean = m_T.Mean(),
		median = m_T.Median_sort(),
		median2 = Median(p,m_T.Length());


	char str[225];
	sprintf(str,"mean = %lf median = %lf median2 = %lf", mean, median, median2);
	MessageBox(0,str,"",0);

	m_LogT = log10(m_T);
	hist(m_LogT, 100, m_Hist, m_tHist);
	plot(m_tHist, m_Hist,
		"Гистограмма логарифма сигнала","","",
		false,true, false, false);

	m_LogT.resize(m_T.Length());

	for (int i = 0; i < m_T.Length(); i++)
	{
		if (m_T[i] == 0)
			m_LogT[i] = 1.0;
		else
			m_LogT[i] = 1./(m_T[i]);
	}
	
	hist(m_LogT, 100, m_Hist, m_tHist);
	plot(m_tHist, m_Hist,
		"Гистограмма обратного сигнала","","",
		false,true, false, false);
//		false,false, false, false);
	if(p)
		HeapFree(GetProcessHeap(), 0,p);

}

void CGraphsDoc::HistOfEarthQuakes()
{
	m_tHistEarthQuakes = dsequence(0.0+0.05, 0.1, 9.9+0.05);
	hist(m_Meq, m_HistEarthQuakes, m_tHistEarthQuakes);
	plot(m_tHistEarthQuakes, m_HistEarthQuakes,
		"Гистограмма магнитуд землетрясений","","",
		false,true, 0, false);
//		false,false, false, false);

}

void CGraphsDoc::HistOfAngle()
{
	hist(m_XYZAngle, 100, m_HistXYZAngle, m_tHistXYZAngle);
	plot(m_tHistXYZAngle, m_HistXYZAngle,
		"Гистограмма отношения, приведённого к углу","","",
		false,true, 0, false);
//		false,false, false, false);

}

void CGraphsDoc::RefreshPlotsData()
{
	if (m_vPoints.SetCurrentVectOnFirst())
	{
		do
		{
			//if (m_pDocument->m_vPoints.GetCurrentVect().GetVectorCheck())
			//{
			if (m_vPoints.GetCurrentVect().SetCurrentMsgOnFirst())
			{
				do
				{
//					void *p = 
					// CpVDPoints * pPoints = &m_vPoints.GetCurrentVect().GetCurrentMsg();
					// vdouble *px = m_vPoints.GetCurrentVect().GetCurrentMsg().px;
					m_vPoints.GetCurrentVect().GetCurrentMsg().minX = 
						m_vPoints.GetCurrentVect().GetCurrentMsg().px->Min(); 

					m_vPoints.GetCurrentVect().GetCurrentMsg().maxX =
						m_vPoints.GetCurrentVect().GetCurrentMsg().px->Max(); 

					m_vPoints.GetCurrentVect().GetCurrentMsg().minY; 
						m_vPoints.GetCurrentVect().GetCurrentMsg().py->Min(); 

					m_vPoints.GetCurrentVect().GetCurrentMsg().maxY; 
						m_vPoints.GetCurrentVect().GetCurrentMsg().py->Max(); 

				}
				// Перемещаем текущий внутренний вектор
				while(m_vPoints.GetCurrentVect().IncrementCurrentMsg());
	//MessageBox(0,"10","RefreshPlotsData", 0);

			}

		}
		// Перемещаем текущий внутренний вектор
		while(m_vPoints.IncrementCurrentVect());
	//MessageBox(0,"11","RefreshPlotsData", 0);

	}
/*	CpVDPoints pVDPoints;
	pVDPoints.px = &vx;
	pVDPoints.py = &vy;
//	pVDPoints.pt = &m_vtime;			//m_vpPoints1[0].toDraw = false;
//	pVDPoints.pt = NULL;				//m_vpPoints1[0].toDraw = false;
	pVDPoints.maxY = (&vy)->Max();
	pVDPoints.minY = (&vy)->Min();
	pVDPoints.maxX = (&vx)->Max();
	pVDPoints.minX = (&vx)->Min();
	pVDPoints.toDraw = true;
	pVDPoints.toScaleX = toScaleX;
	pVDPoints.toScaleY = toScaleY;
	pVDPoints.notGist = notGist;
	pVDPoints.bTimeScale = bTimeScale	;
	strcpy(pVDPoints.szTitle, sTitle);
	strcpy(pVDPoints.szXLabel, sXLabel);
	strcpy(pVDPoints.szYLabel, sYLabel);*/
	//MessageBox(0,"end","RefreshPlotsData", 0);

}
extern HRESULT SaveFileDlg(HWND hWnd, LPTSTR lpstrFile, TCHAR filter[], DWORD& nFilterIndex);
extern char directory[];
void CGraphsDoc::SaveEarthQuakesPerDay(HWND hWnd)
{
	TCHAR /*file[256],*/ lpstrFile[256];
	sprintf(lpstrFile, "%s\\earthquakes_per_day.txt", directory);
	MessageBox(0, lpstrFile, "", 0);
	DWORD nFilterIndex = 0;
	TCHAR filter[] =     
                         TEXT("Text (*.txt)\0*.txt\0")
                         TEXT("All Files (*.*)\0*.*\0");
	SaveFileDlg(hWnd, lpstrFile, filter, nFilterIndex);

	FILE *stream;
	stream = fopen(lpstrFile,"wt");

	fprintf(stream,"time");
	fprintf(stream,"\t\"Magnitude of the lagest earthquake per day\"");
	fprintf(stream,"\t\"Number of Small Earthquakes (< %1.1f) per day\"", this->m_magnitudeBorder);
	fprintf(stream,"\t\"Number of Large Earthquakes (>=%1.1f) per day\"", this->m_magnitudeBorder);

	fprintf(stream,"\t\"Latitude of the lagest earthquake per day\"");
	fprintf(stream,"\t\"Lognitude of the lagest earthquake per day\"");
	fprintf(stream,"\t\"Depth of the lagest earthquake per day\"");

	fprintf(stream,"\n");

	int days = m_tDayEq.Length();

	for (int d = 0; d < days; d++)
	{
		fprintf(stream,"%lf", m_tDayEq[d]);
		fprintf(stream,"\t%lf", m_eqMaxMagnitude[d]);
		fprintf(stream,"\t%lf", m_nFonEqPerDay[d]);
		fprintf(stream,"\t%lf", m_nLargeEqPerDay[d]);

		fprintf(stream,"\t%lf", m_eqLargestB[d]);
		fprintf(stream,"\t%lf", m_eqLargestL[d]);
		fprintf(stream,"\t%lf", m_eqLargestH[d]);
	
		fprintf(stream,"\n");
	}
	fclose(stream);

}

void CGraphsDoc::SaveNearEarthQuakes(HWND hWnd, double B0, double L0, double near_r, double magnitudeBorder, double depthIntervalMin, double depthIntervalMax)
{
//	distance(B0, L0, m_Beq * PI / 180, m_Leq * PI / 180,
//			  m_Aeq, m_Req);
	double t0_excel = datenum(1900,1,1,0,0,0,0)-2;


	TCHAR /*file[256],*/ lpstrFile[256];
	sprintf(lpstrFile, "%s\\earthquakes_per_day_in_%d_km_from_%d_%d.txt", directory, int(near_r), int(B0), int(L0));
	MessageBox(0, lpstrFile, "", 0);
	DWORD nFilterIndex = 0;
	TCHAR filter[] =     
                         TEXT("Text (*.txt)\0*.txt\0")
                         TEXT("All Files (*.*)\0*.*\0");
	SaveFileDlg(hWnd, lpstrFile, filter, nFilterIndex);

	FILE *stream;
/*	stream = fopen(lpstrFile,"wt");

	fprintf(stream,"time");
	fprintf(stream,"\t\"Magnitude of the lagest earthquake per day\"");
	fprintf(stream,"\t\"Number of Small Earthquakes (< %1.1f) per day\"", this->m_magnitudeBorder);
	fprintf(stream,"\t\"Number of Large Earthquakes (>=%1.1f) per day\"", this->m_magnitudeBorder);

	fprintf(stream,"\t\"Latitude of the lagest earthquake per day\"");
	fprintf(stream,"\t\"Lognitude of the lagest earthquake per day\"");
	fprintf(stream,"\t\"Depth of the lagest earthquake per day\"");

	fprintf(stream,"\n");

	int days = m_tDayEq.Length();

	for (int d = 0; d < days; d++)
	{
		fprintf(stream,"%lf", m_tDayEq[d] - t0_excel);
		fprintf(stream,"\t%lf", m_eqNearMaxMagnitude[d]);
		fprintf(stream,"\t%lf", m_nNearFonEqPerDay[d]);
		fprintf(stream,"\t%lf", m_nNearLargeEqPerDay[d]);

		fprintf(stream,"\t%lf", m_eqNearLargestB[d]);
		fprintf(stream,"\t%lf", m_eqNearLargestL[d]);
		fprintf(stream,"\t%lf", m_eqNearLargestH[d]);
	
		fprintf(stream,"\n");
	}
	fclose(stream);*/

	sprintf(lpstrFile, "%s\\earthquakes_in_%d_km_from_%d_%d.txt", directory, int(near_r), int(B0), int(L0));

	stream = fopen(lpstrFile,"wt");
	fprintf(stream,"time");
 	fprintf(stream,"\t\"Lognitude\"");
	fprintf(stream,"\t\"Latitude\"");
	fprintf(stream,"\t\"Magnitude\"");
	fprintf(stream,"\t\"Depth\"\n");
	Vector<int> indexes = Find(m_Req <= near_r*1000);
	for (int i = 0; i < indexes.Size(); i++)
	{
		fprintf(stream,
			"%lf\t %lf\t%lf\t%lf\t%lf\n",
			m_tEarthQuakes[indexes[i]] - t0_excel, 
			m_Leq[indexes[i]], m_Beq[indexes[i]], 
			m_Meq[indexes[i]], m_Heq[indexes[i]]
			);

	}
	fclose(stream);
	vdouble
		x = m_Leq[indexes],
		y = m_Beq[indexes];
	WinPlot(x,y);

	sprintf(lpstrFile, "%s\\large_earthquakes_%1.1f_in_%d_km_from_%d_%d.txt", 
		directory, this->m_magnitudeBorder,
		int(near_r), int(B0), int(L0));

	stream = fopen(lpstrFile,"wt");
	fprintf(stream,"time");
 	fprintf(stream,"\t\"Lognitude\"");
	fprintf(stream,"\t\"Latitude\"");
	fprintf(stream,"\t\"Magnitude of Large Earthquakes\"");
	fprintf(stream,"\t\"Depth\"\n");

	indexes = Find(m_Req <= near_r*1000 && m_Meq >= this->m_magnitudeBorder);
	for (int i = 0; i < indexes.Size(); i++)
	{
		fprintf(stream,
			"%lf\t %lf\t%lf\t%lf\t%lf\n",
			m_tEarthQuakes[indexes[i]] - t0_excel, 
			m_Leq[indexes[i]], m_Beq[indexes[i]], 
			m_Meq[indexes[i]], m_Heq[indexes[i]]
			);

	}
/*	for (i = 0; i < m_Req.Length(); i++)
	{
		fprintf(stream,"%lf\t%lf\t%lf\t%lf\n",m_Req[i], m_Aeq[i], B0, L0);
	}*/

	x = m_Leq[indexes];
	y = m_Beq[indexes];
	WinPlot(x,y);
	fclose(stream);
	//********************************************
	sprintf(lpstrFile, "%s\\large_earthquakes_%1.1f_depth_min_%d_max_%d_in_%d_km_from_%d_%d.txt", 
	directory, this->m_magnitudeBorder,
	(int)this->m_depthIntervalMin,
	(int)this->m_depthIntervalMax,
	int(near_r), int(B0), int(L0));

	stream = fopen(lpstrFile,"wt");
	fprintf(stream,"time");
 	fprintf(stream,"\t\"Lognitude\"");
	fprintf(stream,"\t\"Latitude\"");
	fprintf(stream,"\t\"Magnitude of Large Earthquakes\"");
	fprintf(stream,"\t\"Depth\"\n");

	indexes = Find(
		m_Req <= near_r*1000 
		&& m_Meq >= this->m_magnitudeBorder
		&& m_Heq >= this->m_depthIntervalMin
		&& m_Heq <= this->m_depthIntervalMax
		);
	for (int i = 0; i < indexes.Size(); i++)
	{
		fprintf(stream,
			"%lf\t %lf\t%lf\t%lf\t%lf\n",
			m_tEarthQuakes[indexes[i]] - t0_excel, 
			m_Leq[indexes[i]], m_Beq[indexes[i]], 
			m_Meq[indexes[i]], m_Heq[indexes[i]]
			);

	}
/*	for (i = 0; i < m_Req.Length(); i++)
	{
		fprintf(stream,"%lf\t%lf\t%lf\t%lf\n",m_Req[i], m_Aeq[i], B0, L0);
	}*/

	x = m_Leq[indexes];
	y = m_Beq[indexes];
	WinPlot(x,y);
	fclose(stream);

}

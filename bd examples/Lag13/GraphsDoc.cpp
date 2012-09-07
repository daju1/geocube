// GraphsDoc.cpp : implementation of the CGraphsDoc class
//

#include "stdafx.h"
#include "Graphs.h"
extern Vector<int> sequence(int i1, int i2); // Возвращает последовательность целых чисел от i1 до i2
extern void /*vdouble::*/WaveletFilters(int wf, // флаг типа вейвлетов
									int order, // порядоак вейвлета
	int& nd1, int& nd2, vdouble& d_h,
	int& ngd1, int& ngd2, vdouble& d_g,
	int& nr1, int& nr2, vdouble& r_h, 
	int& ngr1, int& ngr2,vdouble& r_g,
	int& n00, double& m00);
extern void w_fipsi(vdouble& fh,vdouble& fg,
			 int nf1,int nf2,int ng1,int ng2,int d,
			 vdouble& XF,vdouble& FI,vdouble& XP,vdouble& PSI);
extern int WaveletEpsilon(
	  int& wf, // флаг вейвлета
	  int& order, // порядок вейвлета
	  double& wEpsilon,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g);

#include "GraphsDoc.h"

#define SHOW_WAV_KOEF

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//void WriteRaporto(LPSTR s)
void WriteRaporto(LPCTSTR s)
{
//	return;
	FILE *stream;
	// открываем бинарный файл для записи
	if ((stream = fopen("raporto.log","at")) == NULL)
	{
//		AfxMessageBox("Cannot open file for write.\n");
		return;
	}
	fprintf(stream, s);
	// закрываем файл
	fclose(stream);

}

/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc

IMPLEMENT_DYNCREATE(CGraphsDoc, CDocument)

BEGIN_MESSAGE_MAP(CGraphsDoc, CDocument)
	//{{AFX_MSG_MAP(CGraphsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP



	ON_COMMAND(ID_SERVISE_WAVELET, OnWaveletApply)
	ON_COMMAND(ID_SERVISE_ANALIZECOV, CovariationAnalize)
	ON_COMMAND(ID_SERVISE_COVARIATION, CovariationApply)
	ON_COMMAND(ID_FILE_EXPORT, OnFileExport)
	ON_COMMAND(ID_FILE_EXPORT2, OnFileExport2)
	ON_COMMAND(ID_EDIT_PARAMETRS, OnEditParameters)
	ON_COMMAND(ID_FILE_SEND_MAIL, OnFileSendMail)
	ON_UPDATE_COMMAND_UI(ID_FILE_SEND_MAIL, OnUpdateFileSendMail)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGraphsDoc, CDocument)
	//{{AFX_DISPATCH_MAP(CGraphsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//      DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IGraphs to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {5D31465D-A513-47D2-92B3-6127EBCB046E}
static const IID IID_IGraphs =
{ 0x5d31465d, 0xa513, 0x47d2, { 0x92, 0xb3, 0x61, 0x27, 0xeb, 0xcb, 0x4, 0x6e } };

BEGIN_INTERFACE_MAP(CGraphsDoc, CDocument)
	INTERFACE_PART(CGraphsDoc, IID_IGraphs, Dispatch)
END_INTERFACE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc construction/destruction

CGraphsDoc::CGraphsDoc()
{
	m_wEpsilon0 = 0.0;
	m_wf0 = 0;
	m_wOrder0 = 0;

	m_left_h = 0;
	m_right_h = 0;
	m_left_g = 0;
	m_right_g = 0;

	m_wf = 3;
	m_wOrder = 3;
	m_maxLevel = 5;
	m_wEpsilon = 0.1;

	m_radioRec = 0;

	m_bIsFirstTick = true;

	m_i0 = 0;
	m_SignalNumber = 10;
	m_MaxOrder = 5;
	m_isOutWnd = false;

	m_t0 = 0.;
	m_dt = .1;
	m_tend = 60;
	m_t2end = 60;
	m_alpha = 2.0;
	m_beta = 0.0;
	m_epsilon = 0.00001;

	m_pDlg = 0;
	m_pWaveDlg = 0;
	m_pView = 0;

	ReinitVectorsPoints();
	EnableAutomation();

	AfxOleLockApp();
}
void CGraphsDoc::ReinitVectorsPoints()
{
	m_vpPoints1.resize(7);
	for(int i = 0; i < 6; i+=2)
	{
		m_vpPoints1[i].px = &m_t;
		m_vpPoints1[i + 1].px = &m_tPredict;
		m_vpPoints1[i].toDraw = true;
		m_vpPoints1[i + 1].toDraw = true;
	}
	m_vpPoints1[0].py = &m_T;				//m_vpPoints1[0].toDraw = false;
	m_vpPoints1[1].py = &m_TPredict;		//m_vpPoints1[1].toDraw = false;
	m_vpPoints1[2].py = &m_Nnet.m_Y;		m_vpPoints1[2].toDraw = false;
	m_vpPoints1[3].py = &m_Nnet.m_YPredict;	m_vpPoints1[3].toDraw = false;
	
	m_vpPoints1[4].py = &m_T2;				//m_vpPoints1[4].toDraw = false;
	m_vpPoints1[5].py = &m_T2Predict;		//m_vpPoints1[4].toDraw = false;

	m_vpPoints1[6].py = &m_Cov;				
	m_vpPoints1[6].px = &m_tCov;		
	m_vpPoints1[6].toDraw = false;

}

CGraphsDoc::~CGraphsDoc()
{
	AfxOleUnlockApp();
	if(m_isOutWnd)
		delete m_pOutWnd;
}

BOOL CGraphsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc serialization

void CGraphsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc diagnostics

#ifdef _DEBUG
void CGraphsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGraphsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CGraphsDoc commands
/////////////////////////////////////////////////////////////////////////////
// CMultiDocDoc

/////////////////////////////////////////////////////////////////////////////
// CMultiDocDoc construction/destruction


void CGraphsDoc::AlphaDeterminition()
{
	m_alpha_det = m_t.LagerAlphaDeterm(m_MaxOrder, m_tend, .999);
}
void CGraphsDoc::SetTime()
{
	m_Len = (int)((m_tend - m_t0) / m_dt) + 1;
	m_LenPredict = (int)((m_t2end - m_tend) / m_dt);
	m_T = zeros(m_Len);	
	m_T2 = zeros(m_Len);	
	m_t = zeros(m_Len);
	m_TPredict = zeros(m_LenPredict);	
	m_T2Predict = zeros(m_LenPredict);	
	m_tPredict = vdouble(m_LenPredict);

	for(int i=0; i < m_Len; i++)
		m_t[i] = i*m_dt + m_t0;
	for(i=0; i < m_LenPredict; i++)
		m_tPredict[i] = (i-1)*m_dt + m_tend;
	m_Nnet = SystemNnet(m_t,m_T,m_tPredict,m_TPredict);
	ReinitVectorsPoints();
	UpdateAllViews(m_pView);
}
void CGraphsDoc::AddSignal()
{	
	m_Nnet.DeleteAll();
	m_Nnet = SystemNnet(m_t,m_T,m_tPredict,m_TPredict);
	ReinitVectorsPoints();
	UpdateAllViews(m_pView);
}
void CGraphsDoc::Solve()
{	
	int flag_of_Inf = 0;

	m_Nnet.DeleteAll();

	m_Nnet = SystemNnet(m_t,m_T,m_tPredict,m_TPredict);

	m_lgstr.alpha = m_alpha;
	m_lgstr.beta = m_beta;
	m_lgstr.epsilon = m_epsilon;
	m_lgstr.maxOrder = m_MaxOrder;
	m_Nnet.LagerInitialization(m_i0,m_lgstr,flag_of_Inf, m_sNumDen, m_sAnaliticEquation, m_sRoots);
	ReinitVectorsPoints();
	m_vpPoints1[2].toDraw = true;
	m_vpPoints1[3].toDraw = true;

	UpdateAllViews(m_pView);

	m_PredictError = m_Nnet.m_EPredict;
	m_error = m_lgstr.error;
	m_fund_det = m_lgstr.fund_det;

	m_vQ = m_lgstr.vQ;
	m_alphai = m_lgstr.alphai;
	m_flip_betai = m_lgstr.flip_betai;
	m_num = m_lgstr.num;
	m_den = m_lgstr.den;

	m_vQ.Write("D:\\LAGERS/m_vQ.txt");
	m_alphai.Write("D:\\LAGERS/m_alphai.txt");
	m_flip_betai.Write("D:\\LAGERS/m_flip_betai.txt");
	m_num.Write("D:\\LAGERS/m_num.txt");
	m_den.Write("D:\\LAGERS/m_den.txt");
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

	ReinitVectorsPoints();
	m_vpPoints1[2].toDraw = true;
	m_vpPoints1[3].toDraw = true;
	UpdateAllViews(m_pView);
	m_error = m_Nnet.m_E;
	m_PredictError = m_Nnet.m_EPredict;
}
/*
BOOL CGraphsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
//	Solve();
	return TRUE;
}*/



/////////////////////////////////////////////////////////////////////////////
// CMultiDocDoc serialization



/////////////////////////////////////////////////////////////////////////////
// CMultiDocDoc commands

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
	m_vpPoints1[4].toDraw = false;
}

void CGraphsDoc::SetTimeEnd()
{
	int len = m_Len + m_LenPredict;
	vdouble t(len), T(len);
	for (int i = 0; i < m_Len; i++)
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
	UpdateAllViews(m_pView);
}
void CGraphsDoc::OnFileExport() 
{
	// TODO: Add your command handler code here
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
	fclose(stream);
}
void CGraphsDoc::OnFileExport2() 
{
	// TODO: Add your command handler code here
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
	fclose(stream);
}

void CGraphsDoc::AnaliticalString()
{
	AfxMessageBox(m_sNumDen + m_sAnaliticEquation + m_sRoots, 0);
}

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

void CGraphsDoc::CovariationApply()
{
	int L = m_T.Length()/2;

	vdouble C = conv(m_T, fliplr(m_T2));
	vdouble K1=C[sequence(m_Len-1, m_Len-2+L)];
	vdouble K2=fliplr(dsequence(double(m_Len-L), 1.0, double(m_Len-1)));

	m_Cov  = K1/K2;
	m_tCov = dsequence(0, m_dt, m_dt*(L-1));


	m_vpPoints1[6].toDraw = true;
	UpdateAllViews(m_pView);
}

void CGraphsDoc::CovariationAnalize()
{
	m_t = m_tCov;
	m_T = m_Cov;
	m_T2 = m_Cov;
	m_TPredict.resize(0);
	m_T2Predict.resize(0);
	m_tPredict.resize(0);

	m_vpPoints1[4].toDraw = false;
	m_vpPoints1[6].toDraw = false;
	UpdateAllViews(m_pView);

}

void CGraphsDoc::OnTick(int v)
{
WriteRaporto("OnTick 1\n");
	double a = double(v);
	if (m_bIsFirstTick)
	{
WriteRaporto("OnTick m_bIsFirstTick\n");
//WriteRaporto(m_T.disp_str());
		m_T.resize(m_T.Length(), a);
//WriteRaporto(m_T.disp_str());
		m_bIsFirstTick = false;
		for(int i = 1; i < 6; i++)
		{
			m_vpPoints1[i].toDraw = false;
		}
	}

	m_T << a;

//	WaveletApply();
//	WaveletEpsilonApply();
WriteRaporto("OnTick 2\n");

//	UpdateAllViews(m_pView);
WriteRaporto("OnTick end\n");
}

void CGraphsDoc::WaveletApply()
{

	if(m_T.WaveletDecomposition(m_t,
		m_wf, // флаг вейвлета
	  m_wOrder, // порядок вейвлета
	  m_maxLevel, // максимальный уровенть разложения
	  m_vtsd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  m_vtSF,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  m_vFast)) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	{

		if (m_radioRec == 1)
		{
			InitGraphics(m_vtsd, m_vs, false, true, false, true, true);
			InitGraphics(m_vtsd, m_vd, false, true, true, true, false);
		}
		else
		{
			InitGraphics(m_vtSF, m_vSlow, false, true, false, true, true);
			InitGraphics(m_vtSF, m_vFast, false, true, true, true, false);
		}
	}

	UpdateAllViews(m_pView);

}
void CGraphsDoc::InitGraphics(Vector<vdouble>& vx, Vector<vdouble>& vy, bool OneGraphic, bool toDraw, bool toAdd, bool toScaleX, bool toScaleY)
{
	int nGraphs = vx.Size();
	if (nGraphs != vy.Size())
	{
		CString s;
		s.Format("Error using CGraphsDoc::InitGraphics\n vx.Size(%i) != vy.Size(%i)",
			vx.Size(), vy.Size());
		AfxMessageBox(s);
		AfxThrowUserException();
	}
	if (nGraphs < 0)
	{
		CString s;
		s.Format("Error using CGraphsDoc::InitGraphics\n (nGraphs(%i) < 0)",
			nGraphs);
		AfxMessageBox(s);
		AfxThrowUserException();
	}
	if (!toAdd)
	{
		if (OneGraphic)
		{
			m_vpPoints.resize(1);
			m_vpPoints[0].resize(nGraphs);
			for (int i = 0; i < nGraphs; i++)
			{
				m_vpPoints[0][i].px = &vx.data[i];
				m_vpPoints[0][i].py = &vy.data[i];
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
				m_vpPoints[i][0].px = vx.data + i;
				m_vpPoints[i][0].py = vy.data + i;
				m_vpPoints[i][0].toDraw = toDraw;
				m_vpPoints[i][0].toScaleX = toScaleX;
				m_vpPoints[i][0].toScaleY = toScaleY;
			}
		}
	}
	else //if (toAdd)
	{
		CpVDPoints pv;
		Vector< CpVDPoints> vpv;
		if (OneGraphic)
		{
			for (int i = 0; i < nGraphs; i++)
			{
				pv.px = &vx.data[i];
				pv.py = &vy.data[i];
				pv.toDraw = toDraw;
				pv.toScaleX = toScaleX;
				pv.toScaleY = toScaleY;
				m_vpPoints[0].push_back(pv);
			}
		}
		else
		{
			for (int i = 0; i < nGraphs; i++)
			{
				vpv.resize(1);
				vpv[0].px = vx.data + i;
				vpv[0].py = vy.data + i;
				vpv[0].toDraw = toDraw;
				vpv[0].toScaleX = toScaleX;
				vpv[0].toScaleY = toScaleY;

				m_vpPoints.push_back(vpv);
			}
		}
	}
}
void CGraphsDoc::InitGraphics(vdouble& vx, vdouble& vy, bool toDraw, bool toAdd, bool toScaleX, bool toScaleY)
{
	int nGraphs = 1;

	if (!toAdd)
	{
		m_vpPoints.resize(1);
		m_vpPoints[0].resize(nGraphs);
		for (int i = 0; i < nGraphs; i++)
		{
			m_vpPoints[0][i].px = &vx;
			m_vpPoints[0][i].py = &vy;
			m_vpPoints[0][i].toDraw = toDraw;
			m_vpPoints[0][i].toScaleX = toScaleX;
			m_vpPoints[0][i].toScaleY = toScaleY;
		}
	}
	else //if (toAdd)
	{
		CpVDPoints pv;
		Vector< CpVDPoints> vpv;
		vpv.resize(1);
		for (int i = 0; i < nGraphs; i++)
		{
			pv.px = &vx;
			pv.py = &vy;
			pv.toDraw = toDraw;
			pv.toScaleX = toScaleX;
			pv.toScaleY = toScaleY;
			vpv[0] = pv;
		}
		m_vpPoints.push_back(vpv);
	}
}

void CGraphsDoc::OnWaveletApply()
{
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

}

void CGraphsDoc::WaveletDisplay()
{
	double m00;
	int n00, nd1, nd2, ngd1, ngd2, nr1, nr2, ngr1, ngr2;
	vdouble dh, dg, rh, rg,	d, s;

	WaveletFilters(m_wf,m_wOrder,
		nd1,nd2,dh,
		ngd1,ngd2,dg,
		nr1,nr2,rh,
		ngr1,ngr2,rg,
		n00,m00);

	w_fipsi(dh,dg,
			 nd1,nd2,ngd1,ngd2,7,
			 m_vxFI,m_vFI,m_vxPSI,m_vPSI);


	InitGraphics(m_vxFI, m_vFI, true, false, false);
	InitGraphics(m_vxPSI, m_vPSI, true, true, false);
	UpdateAllViews(m_pView);

}	


void CGraphsDoc::WaveletEpsilonApply()
{
WriteRaporto("WaveletEpsilonApply 1\n");

	if (m_wf0 != m_wf || m_wOrder0 != m_wOrder || m_wEpsilon0 != m_wEpsilon)
	{
WriteRaporto("WaveletEpsilonApply if\n");
		WaveletEpsilon(
		  m_wf, // флаг вейвлета
		  m_wOrder, // порядок вейвлета
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
	}
WriteRaporto("WaveletEpsilonApply 2\n");

	if( m_T.WaveletDecomposition(m_t,
	  m_dh,
	  m_dg, 
	  m_rh,
	  m_rg,
	  m_left_h,
	  m_right_h,
	  m_left_g,
	  m_right_g,
	  m_maxLevel, // максимальный уровенть разложения
	  m_vtd,
	  m_vd, // контейнер для хранения d- коэффициентов на каждом уровне декомпозиции
	  m_vts,
	  m_vs, // контейнер для хранения s- коэффициентов на каждом уровне декомпозиции
	  m_vtSlow,
	  m_vSlow, // контейнер для хранения низкочастотной составляющей сигнала на каждом уровне разложения
	  m_vtFast,
	  m_vFast)) // контейнер для хранения высокочастотных составляющих сигнала, отделённых на каждом уровне разложения
	{
WriteRaporto("WaveletEpsilonApply if 2\n");
		if (m_radioRec == 1)
		{
			InitGraphics(m_vts, m_vs, false, true, false, true, true);
			InitGraphics(m_vtd, m_vd, false, true, true, true, false);
		}
		else
		{
			//InitGraphics(m_vtSlow, m_vSlow, false, true, false, true, true);
			InitGraphics(m_vtFast, m_vFast, false, true, true, true, false);
		}
WriteRaporto("WaveletEpsilonApply if 2 }\n");
	}
WriteRaporto("WaveletEpsilonApply 3\n");
//	UpdateAllViews(m_pView);

WriteRaporto("WaveletEpsilonApply end\n");

}



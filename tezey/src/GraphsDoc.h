// GraphsDoc.h : interface of the CGraphsDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(GRAPHSDOC_H__4ABDA399_0C2C_46EF_9C32_B788B4C6A945__INCLUDED_)
#define GRAPHSDOC_H__4ABDA399_0C2C_46EF_9C32_B788B4C6A945__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "WaveDlg.h"	// Added by ClassView
//#include "ParamDlg.h"
//#include "StdAfx.h"
#include "systemnnet.h"
//#include "OutLagFrm.h"
#include "DPoint.h"
#include "../../array/src/vect.h"


 class CGraphsDoc 
{
	//===== Вспомогательные классы будут пользоваться данными
	friend class CGraph;
//	friend class CParamDlg;
//	friend class CWaveDlg;

private:
	bool m_bIsFirstTick;
	//===== Изменение размерности задачи

protected: // create from serialization only

public:

#ifndef DRAW_OLD_VECTOR_VDPOINTS
	int plot (vdouble& vx, vdouble& vy,
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel, 
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY);
	void plot_ (vdouble& vx, vdouble& vy,
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel, 
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY);
	void plot_2 (int iparam, int len,
		LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel, 
		bool bTimeScale, bool notGist, short toScaleX, bool toScaleY);
	//void plot (Vector<SYSTEMTIME>& vtime, vdouble& vx, vdouble& vy, bool notGist, short toScaleX, bool toScaleY);
	void plot (Vector<vdouble>& vx, Vector<vdouble>& vy, bool bTimeScale, bool notGist/* = true*/, short toScaleX/* = true*/, bool toScaleY/* = false*/);
	void plots(Vector<vdouble>& vx, Vector<vdouble>& vy, bool bTimeScale, bool notGist/* = true*/, short toScaleX/* = true*/, bool toScaleY/* = false*/,
		char * sTitle = NULL, char * sX = NULL, char * sY = NULL);
	void plot_3(vdouble& vx, vdouble& vy, 
			LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
			bool bTimeScale, bool notGist, short toScaleX, bool toScaleY);
	void plot_3_(vdouble& vx, vdouble& vy, 
			LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
			bool bTimeScale, bool notGist, short toScaleX, bool toScaleY);
	void plots_3(Vector<vdouble>& vx, Vector<vdouble>& vy, 
			LPCTSTR sTitle, LPCTSTR sXLabel, LPCTSTR sYLabel,
			bool bTimeScale, bool notGist, short toScaleX, bool toScaleY);

#else
	void InitGraphic(Vector<SYSTEMTIME>& vtime, vdouble& vx, vdouble& vy, bool toDraw, short toScaleX, bool toScaleY, bool notGist);
	void InitGraphics(Vector<vdouble>& vx, Vector<vdouble>& vy, bool OneGraphic, bool toDraw, short toScaleX = true, bool toScaleY = false);
	void InitGraphics(Vector<vdouble>& vx1, Vector<vdouble>& vy1, bool OneGraphic1, bool toDraw1, short toScaleX1, bool toScaleY1,
					  Vector<vdouble>& vx2, Vector<vdouble>& vy2, bool OneGraphic2, bool toDraw2, short toScaleX2, bool toScaleY2);
#endif

	void ReinitVectorsPoints(double minY, double maxY);
	void ReinitVectorsPoints();
	char m_sTitle[255];
	char m_sXLabel[255];
	char m_sYLabel[255];
	CGraphsDoc();
#ifndef DRAW_OLD_VECTOR_VDPOINTS
	vect<CpVDPoints> m_vPoints1;
	vect<CpVDPoints> m_vPoints;
//	vect<bool> m_btoPlotPoints;
#else
	Vector<Vector<CpVDPoints> > m_vpPoints;
	Vector<CpVDPoints> 
		m_vpPoints1;//
#endif

	int m_wRadioRec;
	double m_wEpsilon,
		m_wEpsilon0;

	int m_wf,
		m_wOrder,
		m_wOrderBiorthogonalDecomposition,
		m_maxLevel,
		m_wInputSigalType,
		m_wf0,
		m_wOrder0,
		m_wOrderBiorthogonalDecomposition0;
	bool m_bWavShowLow,
		m_bWavShowHigh;

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
		m_Len2,
		m_LenPredict;

//	Vector<SYSTEMTIME> m_vtime,
//		m_vtimeEarthQuakes;


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

	Vector<vdouble> 
		m_vCov,
		m_vtCov,
		m_vCov2,
		m_vtCov2;

//	vdouble m_tCommonParams;
//#ifndef NEW_VECT_COMMON_PARAMS
//	Vector<vdouble> m_vCommonParams;
//#else
	vect<vdouble> m_vtCommonParams;
	vect<vdouble> m_vvCommonParams;
//#endif

	vdouble 
		m_T,
		m_Disp,// дисперсия сигнала
		m_LogT,	
		m_LogT2,	
		m_LogDisp,	
		m_T2,	
		m_t,
		m_t2,
		m_TPredict,	
		m_T2Predict,	
		m_tPredict,

		m_tHist,
		m_Hist,

		m_tHistEarthQuakes,
		m_HistEarthQuakes,

		m_tHistXYZAngle,
		m_HistXYZAngle,


		m_XYZAngle,
		m_XYZAngle2,

		m_XYZ3Angle,
		m_XYZ3Angle2,

		m_XYZAngleLog,
		m_XYZAngleLog2,

		m_XYZ3AngleLog,
		m_XYZ3AngleLog2,
        

		m_tEarthQuakes,
		m_Heq, //Глубины землетрясений
		m_eqMinH, //Глубины землетрясений
		m_eqMeanH, //Глубины землетрясений
		m_eqMaxH, //Глубины землетрясений

		m_Meq, //Магнитуды землетрясений
		m_eqMinMagnitude, //Магнитуды землетрясений
		m_eqMeanMagnitude, //Магнитуды землетрясений
		m_eqMaxMagnitude, //Магнитуды землетрясений
		m_eqNearMaxMagnitude, //Магнитуды землетрясений

		m_Beq, //Геодезические широты эпицентров землетрясений
		m_Leq, //Геодезические долготы эпицентров землетрясений

		m_eqLargestB, //Геодезические широты эпицентров землетрясений
		m_eqLargestL, //Геодезические долготы эпицентров землетрясений
		m_eqLargestH, //
		m_eqNearLargestB, //
		m_eqNearLargestL, //
		m_eqNearLargestH, //
		m_eqLargestAzimut, //
		m_eqLargestAzimut2, //
		m_eqLargestDistance, //

		m_Aeq, // Азимуты направлений на эпицентры
		m_eqMinAzimut, // Азимуты направлений на эпицентры
		m_eqMeanAzimut, // Азимуты направлений на эпицентры
		m_eqMaxAzimut, // Азимуты направлений на эпицентры

		m_Req, // расстояние до эпицентров
		m_eqMinDistance, // расстояние до эпицентров
		m_eqMeanDistance, // расстояние до эпицентров
		m_eqMaxDistance, // расстояние до эпицентров

		m_req, // магнитуды приведенные по удалению

		m_tDayEq,					// посуточная шкала времени для землетрясений
		m_nFonEqPerDay,				// число фоновых землетрясений за сутки
		m_nLargeEqPerDay,			// число крупных землетрясений в сутки
		m_nEqPerDay,				// суммарное число землетрясений в сутки

		m_nNearFonEqPerDay,				// число фоновых землетрясений за сутки
		m_nNearLargeEqPerDay,			// число крупных землетрясений в сутки
		m_nNearEqPerDay,				// суммарное число землетрясений в сутки

		m_nFonEqPerFirstHalfDay,	// число фоновых землетрясений в первую половину суток
		m_nLargeEqPerFirstHalfDay,	// число крупных землетрясений в первую половину суток
		
		m_nFonEqPerSecondHalfDay,   // число фоновых землетрясений во вторую половину суток
		m_nLargeEqPerSecondHalfDay, // число крупных землетрясений во вторую половину суток

		// сортировка землетрясений на Запад от долготы пункта наблюдения

		m_nFonEqPerDay_West,				// число фоновых землетрясений за сутки
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


		m_Energy,
		m_EnergyOfFiltred,
		m_FiltredEnergy,
		m_FiltredEnergyOfFiltred,

		m_TFiltred,
		m_tFiltred,

		m_LogTFiltred,
		m_tLogTFiltred,

		m_TFiltred2,
		m_tFiltred2,

		m_LogTFiltred2,
		m_tLogTFiltred2,

		m_DispFiltred,
		m_tDispFiltred,

		m_LogDispFiltred,
		m_tLogDispFiltred,

		m_Cov,
		m_tCov,

		m_vQ,
		m_alphai,
		m_flip_betai,
		m_num,
		m_den;

	double m_near_r,// радиус вокруг точи наблюдения для вычленения ближайших землетрясений нутри радиуса
		m_magnitudeBorder, 
		m_depthIntervalMin, 
		m_depthIntervalMax;
	int
		m_nInstrumentNumber1,
		m_nInstrumentNumber2;
	
	SystemNnet 
		m_Nnet,
		m_Nnet2,
		m_NnetCov;
	Vector<SystemNnet>
		m_vNnetCov;
	LagerStruct m_lgstr;
	TrainParam m_tp;
	char * m_sAnaliticEquation;
	char * m_sRoots;
	char * m_sNumDen;

//	CParamDlg *m_pDlg;	// Немодальный диалог параметров
//	CView *m_pView;
	void SetTime();
	void SetTime(int _len);
	void AddSignal();
	void LagerSolve(bool bIncludeRealRoots);
	void TrainNnet();
	void AlphaDeterminition();
public:
	void SaveNearEarthQuakes(HWND hWnd, double B0, double L0, double near_r, double magnitudeBorder, double depthIntervalMin, double depthIntervalMax);
	void SaveEarthQuakesPerDay(HWND hWnd);
	void RefreshPlotsData();
	void HistOfAngle();
	void HistOfEarthQuakes();
	void HistOfSignal();
	void HistOfSignal_old();
	void AngleLog3(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle);
	void AngleLog32(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle1, LPCSTR szTitle2);
	void AngleLog(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle);
	void AngleLog2(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle1, LPCSTR szTitle2);
	void Angle3(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle);
	void Angle32(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle1, LPCSTR szTitle2);
	void Angle(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle);
	void Angle2(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, LPCSTR szTitle1, LPCSTR szTitle2);
	void CorrectTimeScale();
	void Plot3DTwoInstruments();
	void SurfTwoInstruments();
	void FiltredEnergyOfFiltred();
	void FiltredEnergy();
	void EnergyOfFiltred();
	void Energy();
	void LogariphmOfFiltredSignal();
	void LogariphmOfFiltredSignal2();
	void SetDispersionPlot();
	void DeleteCalculatedPlots();
	void LogariphmOfDispersion();
	void LogariphmOfSignal();
	void LogariphmOfSignal2();
	void SetEarthQuakesSkale(short skaleModeX, double B0, double L0, double near_r, double magnitudeBorder, double depthIntervalMin, double depthIntervalMax);
	void resize(int _len);
	void resize2(int _len);
	void CGraphsDoc::InitLagerNnet(int nparam);
	void CGraphsDoc::LagerResultPlot();
	bool Covariation(CGraphsDoc* pDoc1, CGraphsDoc* pDoc2, bool toReverse);
	void OnCreate();
	void WaveletApply1();
	void WaveletApply2();
	void WaveletEpsilonApply();
	void WaveletDisplay();
	void LagerDisplay();
//	CWaveDlg* m_pWaveDlg;
	void OnWaveletApply();
//	CWavParam* m_pWawDlg;
	void WaveletApply();
	void OnTick(SYSTEMTIME time, int v);
	void CovariationAnalize();
	void CovariationApply(unsigned int type);
//	void SaveAnaliticalString();
//	void AnaliticalString();
	void SetTimeEnd();
	void OnImport();
	void OnImport2();
	virtual ~CGraphsDoc();
#ifdef _DEBUG
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void OnFileExport();
	void OnFileExport2();

// Generated message map functions
protected:
//	afx_msg void OnEditParameters(void);
};
#endif // !defined(GRAPHSDOC_H__4ABDA399_0C2C_46EF_9C32_B788B4C6A945__INCLUDED_)

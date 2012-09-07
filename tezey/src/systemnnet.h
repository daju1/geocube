// systemnnet.h
#if !defined(_SYSTEMNNET_)
#define _SYSTEMNNET_

#include "../../array/src/vdouble.h"

struct TrainParam // ��������� ���������� �������� ���������
{
	int epochs;  // ������������ ����� ����
	double goalE; // ������� �������� ������������������ ������
	double goalQ; //  ������� �������� ������������ �������� ������
	double min_grad; // ����������� ������ ���������
	int show; // ����� ���� ��� ������ �� ����� ����������� ��������
	int full_turn; // ����� ���� ����� ������� ������������ ������ ��������� ���� (���� ���������� �� ���� �������) 
//	double time; // ������������ ����� ��������
};

class TargetLoader
{
	friend class SystemNnet;
	vdouble m_T,
		m_t;
	int m_len;
public:
	TargetLoader(const char * filename);
	int Length(){return m_len;} // ���������� ����� �������

};


class SystemNnet;//�������� ���������� ������ BaseModel

class BaseModel
{

private:

public:
	void OnCreate();
	int m_type;// ��� ������� ������
	int m_ParamCount;// ����� ������������� ����������
	SystemNnet* m_pNnet;//��������� �� ������ ��������� ������ SystemNnet
	                    //���������� � ���� ������ ������ ������ BaseModel
	int m_q; // ���������� ����� ������ ������ � �������
	vdouble m_y, // ������ ������ ������
		m_par, // ������ ������������� ����������
		m_vkp,// ������ ������������� �������� ��������� ����������
		m_dydpar,
		m_d2ydpar,
		m_ParamGradient,
		m_yPredict;
	double m_kp, 
		m_kp1, 
		m_kp2, 
		m_kp3, 
		m_kpMax,
		m_kpMin;//����������� �������� ��������� ����������
//�������-�����
	Vector<bool> m_toTurn;
	BaseModel(SystemNnet* _pNnet, int _type);//�����������
	BaseModel();
	BaseModel(const BaseModel& rhs)
	{
		m_ParamGradient = rhs.m_ParamGradient;
	
		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_toTurn = rhs.m_toTurn;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;
	}
	~BaseModel();//de ��������
	void InitModel();//������������� ���������� ������ �������� ���� ������� ��������� ���������� � 1
	void InitModel(int init);//������������� ���������� ������ �������� ���� ������� ��������� ���������� � init
	void TurnModel(bool toTurnAllParam = true);//��������� ���������� ������
	void ModelSignal();//������������� (���������) ������� ������
	void ModelSignalDerivatives(int npar);
	BaseModel& operator=(const BaseModel& rhs)
	{
		if (this == &rhs)
			return *this;
		m_ParamGradient = rhs.m_ParamGradient;
	
		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_toTurn = rhs.m_toTurn;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;
		return *this;

	}

};
typedef BaseModel* PBM;

class LagerModel
{

private:

public:
	int m_i0,
		m_len,
		m_lenPredict;
	int m_type;// ��� ������� ������
	int m_ParamCount;// ����� ������������� ����������
	SystemNnet* m_pNnet;//��������� �� ������ ��������� ������ SystemNnet
	                    //���������� � ���� ������ ������ ������ BaseModel
	int m_q; // ���������� ����� ������ ������ � �������
	vdouble m_t,
		m_tPredict,
		m_y, // ������ ������ ������
		m_par, // ������ ������������� ����������
		m_vkp,// ������ ������������� �������� ��������� ����������
		m_ParamGradient,
		m_yPredict,
		m_dydpar,
		m_d2ydpar;
	Vector<bool> m_toTurn;
	double m_t0,
		m_kp, 
		m_kp1, 
		m_kp2, 
		m_kp3, 
		m_kpMax,//����������� �������� ��������� ����������
		m_kpMin,
		*m_pt,
		*m_ptPredict,
		*m_py,
		*m_pyPredict;

		//�������-�����
	LagerModel();//�����������
	LagerModel(SystemNnet* _pNnet, int _i0, int _type, int _ParamCount);//�����������
	LagerModel(const LagerModel& rhs)
	{
		m_ParamGradient = rhs.m_ParamGradient;
		m_i0 = rhs.m_i0;
		m_len = rhs.m_len;
		m_lenPredict = rhs.m_lenPredict;
		m_t0 = rhs.m_t0;
			
		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_toTurn = rhs.m_toTurn;

		m_pLagerSignal = rhs.m_pLagerSignal;
		m_pLagerSignalDerivatives = rhs.m_pLagerSignalDerivatives;
	if(m_type == 1 )
	{
		void (LagerModel::*m_pLagerSignal) () = &LagerModel::LagerSignal1;
		void (LagerModel::*m_pLagerSignalDerivatives) (int npar) = &LagerModel::LagerSignalDerivatives1;
	}
	if(m_type == 3 )
	{
		void (LagerModel::*m_pLagerSignal) () = &LagerModel::LagerSignal3;
		void (LagerModel::*m_pLagerSignalDerivatives) (int npar) = &LagerModel::LagerSignalDerivatives3;
	}

		m_t = rhs.m_t;
		m_tPredict = rhs.m_tPredict;
		m_pt = m_t.pD;
		m_ptPredict = m_tPredict.pD;

		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_py = m_y.pD;
		m_pyPredict = m_yPredict.pD;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;

	}

	~LagerModel();//de ��������
	void InitLager();//������������� ���������� ������ �������� ���� ������� ��������� ���������� � 1
	void InitLager(int init);//������������� ���������� ������ �������� ���� ������� ��������� ���������� � init
	void TurnLager(bool toTurnAllParam = true);//��������� ���������� ������
	void LagerSignal1();//������������� (���������) ������� ������
	void LagerSignal3();//������������� (���������) ������� ������
	void (LagerModel::*m_pLagerSignal)();// ��������� �� ���� �� ������� ��������� �������
	void LagerSignalDerivatives1(int npar);
	void LagerSignalDerivatives3(int npar);
	void (LagerModel::*m_pLagerSignalDerivatives)(int npar);//��������� �� ���� �� ������� ����������� �������
	LagerModel& operator=(const LagerModel& rhs)
	{
		if (this == &rhs)
			return *this;
		m_ParamGradient = rhs.m_ParamGradient;
		m_i0 = rhs.m_i0;
		m_len = rhs.m_len;
		m_lenPredict = rhs.m_lenPredict;
		m_t0 = rhs.m_t0;

		m_pLagerSignal = rhs.m_pLagerSignal;
		m_pLagerSignalDerivatives = rhs.m_pLagerSignalDerivatives;

		m_type=rhs.m_type;
		m_ParamCount=rhs.m_ParamCount;
		m_pNnet = rhs.m_pNnet;
		m_q=rhs.m_q;
		m_toTurn = rhs.m_toTurn;

		m_t = rhs.m_t;
		m_tPredict = rhs.m_tPredict;
		m_pt = m_t.pD;
		m_ptPredict = m_tPredict.pD;

		m_y=rhs.m_y;
		m_yPredict=rhs.m_yPredict;
		m_py = m_y.pD;
		m_pyPredict = m_yPredict.pD;

		m_dydpar = rhs.m_dydpar;
		m_d2ydpar = rhs.m_d2ydpar;

		m_par=rhs.m_par;
		m_vkp=rhs.m_vkp;
		m_kp=rhs.m_kp;
		m_kp1=rhs.m_kp1;
		m_kp2=rhs.m_kp2;
		m_kp3=rhs.m_kp3;
		m_kpMax=rhs.m_kpMax;
		m_kpMin=rhs.m_kpMin;
		return *this;
	}
};

typedef LagerModel* PLM;

class SystemNnet
{
public:
	void Init();
	int m_len;//����� ����� �������, ������������ � �������� �� ��������� 
	int m_lenPredict;//����� ����� �������, ������������ ��� ���������������
	int m_nModelCount;//����� ������� � �������
	int m_nLagerCount;//����� ������� � �������
	
	vdouble m_vkl,
		m_vkh, // ������ ������������� �������� ��������� ����� m_h
		m_t,// ����� �������
		m_T,// ������� ������
		m_Y,// �������� ������ ����
		m_h,// ���� ������ ������ � �������
		m_l,
		m_ModelGradient, // ������ ������� ���������� ��� ������ ������
		m_LagerGradient,
		m_ModelEffect, // ������ ������������� �������
		m_LagerEffect,
		m_tPredict, // ����� ������� ��� ��������
		m_TPredict, // ������� ������ ��� ��������
		m_YPredict, // �������� ������ ���� ��� ��������
		m_dEdY, // ������� ������ ������ �� ������
		m_dEdY_Predict; // ������� ������ ������ �� ������ ��� ��������

	Vector<BaseModel> m_vModel;// ������ �������� ������ BaseModel
	Vector<LagerModel> m_vLagerModel;// ������ �������� ������ BaseLager
	Vector<bool> m_toTurn, 
		m_toTurnLager;
	double m_E, // ������ ����
		m_EPredict, // ������ ��������
		m_kh, // ��������� ����������� �������� ��������� ����� m_h
		m_kl,
		m_kh1, // ��������� ��� �������� ������� m_vkh, ���� ��� ���������� ���� ������ �����������
		m_kl1,
		m_kh2, // ��������� ��� �������� ������� m_vkh, ���� ��� ���������� ���� �������� ������ �� ������ ���������
		m_kl2,
		m_kh3, // ��������� ��� �������� ������� m_vkh, ���� ��� ���������� ���� �������� ������ �� ������ ����������
		m_kl3,
		m_khMax, // ����������� ���������� ����������� �������� ��������� ����� m_h
		m_klMax,
		m_khMin, // ����������� ���������� ����������� �������� ��������� ����� m_h
		m_klMin,
		m_Gradient, // �������� ����
		m_MaxAbs_dEdY, // ������������ �� ������ ������ ����� ���� �����
		m_MaxAbs_dEdY_Predict, // ������������ �� ������ ������ ����� ���������� �����
		m_PredictedPart; // ���� ������� ��� ��������: 0 <= m_PredictedPart < 1
		
	// �����������
	SystemNnet(){Init();} // 
	SystemNnet(int _len); // ������� �����������
	SystemNnet(int _len, int _lenPredict); // ������� �����������
	void Init(TargetLoader& TL, const double _PredictedPart); // ����������� �� ������������ �� ����� �������� �������
	void Init(vdouble& _t, vdouble& _T, const double _PredictedPart = 0.0); // ����������� �� �������� �������
	void Init(vdouble& _t, vdouble& _T, vdouble& _t_Predict, vdouble& _T_Predict); // ����������� �� �������� �������
	~SystemNnet(); // ����������
	PBM AddModel(int _type); // ���������� ������ ����������� ���� � �������
	PLM AddLager(int _i0, int type, int ParamCount, double h);
	int LagerInitialization(int i0, LagerStruct& lgstr, int flag_of_Inf,
		char * sNumDen,char * sAnaliticEquation, char * sRoots, bool bIncludeRealRoots);
	void DeleteModels(Vector<bool>& vbl); // �������� ������� �� �������
	void DeleteLagers(Vector<bool>& vbl);
	void DeleteAll();
	void Default();
	void ModelEffect(int modelNumber)
	{
		if ( modelNumber >= 0 && modelNumber < m_nModelCount)
			m_ModelEffect[modelNumber] = ( (m_dEdY + m_h[modelNumber] * m_vModel[modelNumber].m_y).SquareSum() -
				m_dEdY.SquareSum()) / m_len;
	}
	void LagerEffect(int lagerNumber)
	{
		if ( lagerNumber >= 0 && lagerNumber < m_nLagerCount)
			m_LagerEffect[lagerNumber] = ( (m_dEdY + m_l[lagerNumber] * m_vLagerModel[lagerNumber].m_y).SquareSum() -
				m_dEdY.SquareSum()) / m_len;
	}
	void ModelEffect()
	{
		ErrorNnet();
		vdouble dEdY = m_T - m_Y;
		for (int q = 0; q < m_nModelCount; q++)
			m_ModelEffect[q] = ((dEdY + m_h[q] * m_vModel[q].m_y).SquareSum() / m_len - m_E);
	}
	void LagerEffect()
	{
		ErrorNnet();
		vdouble dEdY = m_T - m_Y;
		for (int q = 0; q < m_nLagerCount; q++)
			m_LagerEffect[q] = ((dEdY + m_l[q] * m_vLagerModel[q].m_y).SquareSum() / m_len - m_E);
	}
//	void AddModelsFrom(SystemNnet& sn); // ���������� � ������� ������� ���� ������� �� ���������� �������
	void SimulNnet(); //��������� (���������) ������� ����
	void SimulNnet1(int _LagerNumber); // to delete in future
	void SimulNnetLager(int _LagerNumber);// fast simul nnet after turning of one lager model
	void SimulNnetModel(int _ModelNumber); // fast simul nnet after turning of one model
	void SimulNnetLager(int _LagerNumber, double old_h);// fast simul nnet after turning of one lager model
	void SimulNnetModel(int _ModelNumber, double old_h); // fast simul nnet after turning of one model
	void ErrorNnet();//������ ����

	void TurnNnet(bool toTurnAllParam = true);//��������� ����
	void Train(TrainParam& tp, char* sNumDen, char*  sAnaliticEquation, char*  sRoots, bool toTurnAllParam = true);

	void AddInitGarmonicModels(int maxGarmonicOrder);

	//void PaintNnet();//��������� ��������� ������� ����
//	void AddInitGarmonicModel();
///	void AddInitModels(int maxOrder);

};
#endif
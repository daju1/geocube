//#include "StdAfx.h"

#if !defined(_VDOUBLE_)
#define _VDOUBLE_

#define PI		3.14159265358979323846
#define SD      8 // = (sizeof(double)) - ��������� ��� ������� ����������
//#define COPY_CONSTR false
#define MEMORY_ERROR AfxMessageBox("Error using vdouble: not enough memory\n");return vdouble(0);
#define MEMORY_ERROR0 AfxMessageBox( "Error using vdouble: not enough memory\n");return;
#define MEMORY_ERROR2 AfxMessageBox( "Error using vdouble: not enough memory\n");return 1.0e300;

#define  DEBUGGING false
#include <cfloat>
#include "complex.h"

#define WF_HAAR							1
#define WF_DAUBECHIES					2
#define WF_SYMLETS						3
#define WF_COIFLETS						4
#define WF_BIORTOGONAL					5
#define WF_MY_BIORTOGONAL				6
#define WF_BIORTOGONAL_NONSTANDART		7
#define WF_DISCRETE_MEYER				8

//#include <exception>
struct LagerStruct;
class vdouble // ����� ������� ������������ ����� double
{
	friend class CGraph;
	friend class LagerModel;
private:
	int m_length; // ����� �������
	int m_dims;
	Vector<int> m_size;
	bool m_isgorizontal; // ���� ����������������
	double *pD; // ��������� �� ���������� ������ ������������ 
			// ����� double
public:
	int idwt(vdouble&  new_t, int left1_2, int right1_2, vdouble &rh_or_rg,vdouble& current_ts_or_td, vdouble &s_or_d, bool isLow);
	int idwt(vdouble& t, vdouble&  tau, vdouble &rh, vdouble &rg, vdouble &s, vdouble &d);
	int dwt(vdouble& t,
		 int left_h2, int right_h2, vdouble &dh,  
		 int left_g2, int right_g2, vdouble &dg, 
		 vdouble& ts, vdouble &s, 
		 vdouble& td, vdouble &d);
	int dwt(vdouble& t, vdouble& tsd, vdouble&dh, vdouble& dg, vdouble&s, vdouble&d);
//	int dwt(int j, vdouble &dh, vdouble &dg, vdouble &s, vdouble &d);
	int b_reconstructor(vdouble& b, vdouble& tt, vdouble& xx, double t0); 	// ������������� ������������� ��������� ������������ ������� 
			// ��  ���������� ����������� (*this)  
			// � ����� �� ������� �� delta - ������� � ������ t0

	void Rand(double minBorder, double maxBorder);
	double FirstLocalMinFrom(int j);
	double FirstLocalMaxFrom(int j);
	Vector<int> Size(){return m_size;}
	static unsigned int m_nConstructions; // ����� ��� ���������� �������������
	static unsigned int m_nDestructions; // ����� ��� ���������� ������������
	static size_t m_szMemory; // ����� ���������� ������������ ������

	vdouble(); // ����������� �� ��������� - ������ ������ ������� ������� �����
	vdouble(vdouble& src); // ����������� ����������� - ������ ������ ������� ������� �����
	vdouble(int _length);// ����������� - ������ ������ ������� �������� �����
	vdouble(double array[], int _length/* = sizeof(array)/sizeof(double)*/);// ����������� - ������ ������ �� ������� ����� double
	vdouble(double& array, int _length/* = sizeof(array)/sizeof(double)*/);// ����������� - ������ ������ �� ������� ����� double
	vdouble(int _length, const double& ra);// ����������� - ������ ������ ������� �������� �����, ���������� ���� ��������� ���������� ��������
	int Save(const char * filename);//
	int Write(const char * filename);//
	int Load(const char * filename);//

	vdouble(int rows, int cols); // ����������� ��������� �������
	vdouble(int rows, int cols, int tabs); // ����������� ��������� �������
	vdouble(Vector<int>& vsize); // ����������� ����������� �������

	void resize(int _length);// 
	void resize(int _length, const double& ra);// 
	void resize(int rows, int cols); // 
	void resize(int rows, int cols, const double& ra); // ��������� �������
	void resize(int rows, int cols, int tabs); // 
	void resize(Vector<int>& vsize); // 

	virtual ~vdouble(); // ���������� ��������� ������������ ������

	friend vdouble inline zeros(int _length);// ������ ������ �������� ����� �� �����
	friend vdouble inline ones(int _length); // ������ ������ �������� ����� �� ������

	int Length(){return m_length;} // ���������� ����� �������
	bool IsGorizontal(){return m_isgorizontal;} // ���������� ���� ����������������
	
	void disp(); // ������� �������� ��������� � ���������� ����
	void dispWithIndex();
	void dispSquareMatrix();// ������� �������� ��������� ���������� ������� � ���������� ����

	CString disp_str();
	CString dispMatrix_str();
	
	bool is_zeros(); // ������, ���� ��� �������� - ����� ����
	bool is_zeros(const double& epsilon);// ������, ���� ������ ���� ��������� �� ��������� epsilon

	double& operator[](int index); // ���������� ������� �� ��������� �������
	vdouble operator[](Vector<int>& ind); // ���������� ������-������� �� ��������� ������� ��������
	vdouble operator()(Vector<int>& vrows, Vector<int>& vcols);
//	vdouble vdouble::operator[](Vector<Vector<int> >& ind); // ���������� ������-������� �� ��������� ������� �������� �� ������ �����������
	double& operator()(int index); // ���������� ������� �� ��������� �������

	double& operator()(int row,int col); // ���������� ������� ��������� ������� �� ��������� �������
	double& operator()(int row, int col, int tab); // ���������� ������� ��������� ������� �� �������� �������� ������ � �������
	double& operator()(Vector<int>& indexes); // ���������� ������� ��������� ������� �� �������� �������� ������ � �������

	vdouble& operator=(vdouble& rhs); // ������������� �������� ������������
	vdouble& operator=(const double& ra);
	vdouble& SummingFrom(int i0, vdouble& rhs);// // ������������ ������������ � �������� ��������� � ������������� ������� � ���������� ������ ��������
	vdouble& operator+=(vdouble& rhs);// ������������ ������������ � �������� ��������� � �������������
	vdouble& operator+=(const double& ra);
	
	vdouble& operator-=(vdouble& rhs);// ������������ ��������� ������� ��������� � �������������
	vdouble& operator-=(const double& ra);
	
	vdouble& operator*=(vdouble& rhs);// ������������ ��������� �� ������ ��������� � �������������
	vdouble& operator*=(const double& ra);
	
	vdouble& operator/=(vdouble& rhs);// ������������ ������� �� ������ ��������� � �������������
	vdouble& operator/=(const double& ra);// ������� �� ������������ ����� � �������������

	friend vdouble inline operator+(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator+(const double& a, vdouble& ob2);
	friend vdouble inline operator+(vdouble& ob1, const double& a);

	friend vdouble inline operator-(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator-(const double& a, vdouble& ob2);
	friend vdouble inline operator-(vdouble& ob1, const double& a);

	friend vdouble inline operator^(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator^(const double& a, vdouble& ob2);
	friend vdouble inline operator^(vdouble& ob1, const double& a);
	
	friend vdouble inline pow(vdouble& ob1, vdouble& ob2);
	friend vdouble inline pow(const double& a, vdouble& ob2);
	friend vdouble inline pow(vdouble& ob1, const double& a);

	friend vdouble inline operator*(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator*(const double& a, vdouble& ob2);
	friend vdouble inline operator*(vdouble& ob1, const double& a);

	friend vdouble inline operator/(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator/(const double& a, vdouble& ob2);
	friend vdouble inline operator/(vdouble& ob1, const double& a);

	friend vdouble inline operator,(vdouble& ob1, vdouble& ob2);
	friend vdouble inline operator,(const double& a, vdouble& ob2);
	friend vdouble inline operator,(vdouble& ob1, const double& a);
	
	friend vdouble inline operator+(vdouble& ob);
	friend vdouble inline operator-(vdouble& ob);

	friend vdouble inline log(vdouble& ob);
	friend vdouble inline log10(vdouble& ob);
	friend vdouble inline abs(vdouble& ob);

	friend vdouble inline acos(vdouble& ob);
	friend vdouble inline asin(vdouble& ob);
	friend vdouble inline atan(vdouble& ob);
	friend vdouble inline atan2(vdouble& x, vdouble& y);

	friend vdouble inline cos(vdouble& ob);
	friend vdouble inline cosh(vdouble& ob);
	friend vdouble inline sin(vdouble& ob);
	friend vdouble inline sinh(vdouble& ob);
	friend vdouble inline tan(vdouble& ob);
	friend vdouble inline tanh(vdouble& ob);
	friend vdouble inline exp(vdouble& ob);
	friend vdouble inline sqrt(vdouble& ob);

	friend vdouble inline floor(vdouble& ob);
	friend vdouble inline ceil(vdouble& ob);

	friend Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator>(const double& a, vdouble& ob);
	friend Vector<bool> inline operator>(vdouble& ob, const double& a);

	friend Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator>=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator>=(vdouble& ob, const double& a);

	friend Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator<(const double& a, vdouble& ob);
	friend Vector<bool> inline operator<(vdouble& ob, const double& a);

	friend Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator<=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator<=(vdouble& ob, const double& a);

	friend Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator==(const double& a, vdouble& ob);
	friend Vector<bool> inline operator==(vdouble& ob, const double& a);

	friend Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2);
	friend Vector<bool> inline operator!=(const double& a, vdouble& ob);
	friend Vector<bool> inline operator!=(vdouble& ob, const double& a);
	
	friend vdouble inline fliplr(vdouble& ob);

	friend void inline operator<<(vdouble& ob, const double& a);
	friend void inline operator>>(const double& a, vdouble& ob);

	friend void inline operator<<(CArchive& ar, vdouble& v);
	friend void inline operator>>(CArchive& ar, vdouble& v);

	friend vdouble inline conv(vdouble& v1, vdouble& v2);
	friend vdouble dsequence(double d0, double dstep, double dend);

	void Resetting(); // �������� ��� �������� �������
	double& End(); // ���������� ��������� ������� �������
	double& End(int n); // ���������� n- �� ������� ������� � �����
		// n < 0
	vdouble Select(Vector<int>& indexes); // ���������� ����� ������, ������� �������� �� ������� �������
	vdouble Select(Vector<bool>& vbl); // ���������� ����� ������, ������� �������� �� ������� �������
	void LocalMaximums(vdouble& LocMax, Vector<int>& indexes); // ��������� ������ ��������� ���������� � ������������� ������ �� ��������
	void LocalMaximums(int n, vdouble& LocMax, Vector<int>& indexes);// ��������� ������ ��������� ���������� � ������������� ������ �� ��������
	void LocalMaximumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes);// ��������� ������ ��������� ���������� � ������������� ������ �� ��������

	void LocalMinimums(vdouble& LocMin, Vector<int>& indexes);// ��������� ������ ��������� ��������� � ������������� ������ �� ��������
	void LocalMinimums(int n, vdouble& LocMin, Vector<int>& indexes);// ��������� ������ ��������� ��������� � ������������� ������ �� ��������
	void LocalMinimumsWithBorders(int n, vdouble& LocMax, Vector<int>& indexes);// ��������� ������ ��������� ���������� � ������������� ������ �� ��������
	bool IsEndLocalMin(int n = 3);
	bool IsEndLocalMax(int n = 3);
	bool IsEndDecreaseDown(int n = 3);
	bool IsEndGrowUp(int n = 3);

	double Max(); // ���������� �a���������� ������� �������
	double Min(); // ���������� ����������� ������� �������
	double MaxFrom(int j);
	double MinFrom(int j);
	double MaxAbs(); // ���������� �a���������� �� ����������� �������� ������� �������
	double MinAbs(); // ���������� ����������� �� ����������� �������� ������� �������
	double Mean(); // ���������� ������� �������������� ��������� �������
	double Root_mean_square_Dismissal(); // ���������� ������������������ ����������
	double Sum(); // ���������� ����� ��������� �������
	double SquareSum(); // ���������� ����� ��������� ��������� �������
	double SquareSumFrom(int i0); // ���������� ����� ��������� ��������� �������, ������� � i0
	void push_back(double a);// ��������� ������� � ����� �������
	void push_front(double a); // ��������� ������� � ������ �������
	void DeleteEnd(); // ������� 1 ��������� ������� �������
	void DeleteEnd(int n); // ������� n ��������� ��������� �������
	void DeleteElement(int index); // ������� index-��� ������� �������
	void DeleteElements(Vector<bool>& vbl); // ������� �������� �������
	void DeleteAll(); // ������� ��� �������� �������

	vdouble CumMeanSquareSum();// ���������� ������ ������������ ������������ ����, ���������� �� ������ �������� � ����������� �����
	vdouble CumMeanSquareSumFrom(int i0);// ���������� ������ ������������ ������������ ����, ���������� �� ������ �������� � ����������� �����, ������� � i0
	vdouble CumSum(); // ���������� ������ ������������ ����
	vdouble CumMeanSum(); // ���������� ������ ������������ ����, ���������� �� ������ ��������
	vdouble CumMeanSumFrom(int i0); // ���������� ������ ������������ ����, ���������� �� ������ ��������, ������� � i0
	vdouble DiffVector();// ������ �������� ��������� (���������� ������ �� 1 ������)
	vdouble SumVector();//������ �������� ���� (���� � �������� ������) - �����. ����. �� 1 ������
	double Trapz(vdouble& t); // �������������� ������� �������� �� ������������� ��������� �����

	double ScalarProduct(vdouble& rhs); // ���������� ��������� ������������ �� ������ � ���������
	double ScalarProductFrom(int i0, vdouble& rhs); // ���������� ��������� ������������ �� ������ � ��������� ������� � ���������� ������ ��������
	void FourierTransform(vdouble& t, vdouble& omega, vdouble& A, vdouble& fi ); // ����� ��������������

	//============ ������� ������ - ������������ �������������� ============
	vdouble vLagerPolynom(int n);
	double LagerAlphaDeterm(int maxOrder, double tend, double EnergyPart = 0.95);
	double LagerAlphaDeterminition(double& tend, double& EnergyPart);
	vdouble LagerQuotients(int i0, vdouble& t, LagerStruct& lgstr, int flag_of_Inf, Vector<vdouble>& koefs, CString& sNumDen, CString& sRoots); // ���������� ������������� �������

	double LagerDeterminant(); // ��������� ����������� ������� ��������� ��������� ������ ������������� �������
	double vdouble::LagerDeterminant(double alpha, double beta, vdouble& alphai, vdouble& flip_betai, vdouble& num, vdouble& den);// ��������� ����������� ������� ��������� ��������� ������ ������������� �������, � ����� ������������ ������������ �-���
	int InvLaplace(vdouble& num, vdouble& den, vdouble& t, vdouble& f_rekonstr, Vector<vdouble>& koefs, CString& sRoots); // �������� �������������� �������� ��� ����� ���������

	//============ ������� �������� ������� ============
	vdouble MatrixProduct(vdouble& x);// ��������� ������������ ������� ������� R x C �� ������������ ������ ������ C 
										// ���������� ������ ������ R
	vdouble MatrixWithMatrixProduct(vdouble& x); // ��������� ������������ ������� ������� R1 x C1 �� ������� ������� R2 x C2 ������ C1 = R2
	vdouble TransponedMatrixProduct(vdouble& x);// ��������� ������������ ������� ������� R x C �� ������������ ������ ������ R 
										// ���������� ������ ������ C
	vdouble VectorsToMatrixProduct(vdouble& gor); // ��������� ������������ ������������� ������� ������ R
												// �� �������������� ������ ������ C 
												// ���������� ������� �������� R x C
	vdouble TichonovOld(vdouble& b);
	vdouble Tichonov(vdouble& b); // ������� ������� �������� ��������� ������� ������������� ��������
	int pinv(vdouble& pinvMatrix);// ��������������� �������
	vdouble LinearInterp(vdouble &t);
	vdouble LinearInterp();

	void EMA(vdouble& t, vdouble& tau, vdouble& ema, int nPoint); //���������������� ���������� �������
	void NEMA(vdouble& t, vdouble& tau, 
		vdouble& ema,  vdouble& nema, int nPoints); //������������� ���������������� ���������� �������
	void Derivatives(vdouble& t, 
		double dt,
		vdouble& pinvT, // ������� - ������ ��� ���������� �����������, ����������� ���������������� ������� ��������� ����������
		vdouble& tau, 
		vdouble& ma, vdouble& d1, vdouble& d2, 
		int nPoint, int interp_order, 
		bool uniform,
		bool isEnd = false, int nPredict = 0);// ������ � ������ �����������
	void Derivative(vdouble& t, 
		vdouble& pinvT, // ������� - ������ ��� ���������� �����������, ����������� ���������������� ������� ��������� ����������
		double& ma, double& d1, double& d2, // ���������� ������� � ������ � ������ �����������
		int interp_order);
	int Derivatives(vdouble& t, // ����� ������� *this � ������ ����� ������� ��� �������
		vdouble& pinvT, // ������� - ������ ��� ���������� �����������, ����������� ���������������� ������� ��������� ����������
		vdouble& tDeriv, // ������ ����� ������� ��� ����������� - �������� ��������
		vdouble& DerivativesMatrix, // ������� ����������� ������������ tDeriv.m_lenght x deriv_order - �������� ��������
		int& i1, int& i2, // ������� ������� � �������� ��������� ������� ������� ����������� �� ����� ������� �������
		int interp_order, // ������� ����������������� ��������
		int deriv_order, // ������� ������ �����������
		int nPoints, // ����� ����� ���������� ����
		double& qt, // ����������� �������� ��������� �� ��� ������� - ��������� �� ������ ��������� ������� Derivatives
		bool uniform);// ���� ������������� ��������� �����
	int Derivative(vdouble& t, // ����� ������� *this � ������ ����� ������� ��� �������
		vdouble& pinvT, // ������� - ������ ��� ���������� �����������, ����������� ���������������� ������� ��������� ����������
		vdouble& tDeriv, // ������ ����� ������� ��� ����������� - �������� ��������
		vdouble& DerivativesMatrix, // ������� ����������� ������������ tDeriv.m_lenght x deriv_order - �������� ��������
		int& i1, int& i2, // ������� ������� � �������� ��������� ������� ������� ����������� �� ����� ������� �������
		int interp_order, // ������� ����������������� ��������
		int deriv_order, // ������� ������ �����������
		int nPoints, // ����� ����� ���������� ����
		double& qt); // ����������� �������� ��������� �� ��� ������� - ��������� �� ������ ��������� ������� Derivatives
	int diff_Wp(vdouble& t, // ����� ������� *this � ������ ����� ������� ��� �������
		vdouble& pinvT, // ������� - ������ ��� ���������� �����������, ����������� ���������������� ������� ��������� ����������
		int denom_order, // ������� ����������� ������������ �������
		int nPoints, // ����� ����� ���������� ���� ��� ���������� �����������
		bool uniform, // ���� ����������� ��������� �����
		vdouble& denom, // ������������ ����������� ������������ �������
		vdouble& num, // ������������ ��������� ������������ �������
		vdouble& f_reconstr, // ������������������ ������
		double& er_deriv, // ������ ���������� ������� �� ������ ��� �����������
		double& er_reconstr);// ������ ������������ �������
	double det(); // �����������
	void sls_det(vdouble& b, vdouble& x, double& _det, bool PrivateDesigion = false);//������� �������� ������� ��������� ������� ������
//	vdouble A(int j); // �������������� ����������

	vdouble PolynomDerivative();//���������� ������ �������� ������ �����������
	vdouble PolynomSumming(vdouble& v); // ������������ ���������
	void PolynomDivide(const vdouble& divisor, vdouble& quotient, vdouble& remainder);// ���������� ������� �� �������
	int PolynomDivideIntoThree_member(double& b, double c);// ���������� ������� �������� �� �������, � ������� ������ ����������� b �������� �����������,
	int PolynomRootsSimple(vdouble& prs, vdouble& D);// ��������� ������� �����, ������� ������� � �������� ������� � ��������������� ���������
	int PolynomGreatestCommonDivider(vdouble& v, vdouble& divider);// ���������� ����� �������� ���� ���������
	double PolynomValue(const double& a);// ���������� �������� �������� ��� �������� �����
	complex PolynomValue(complex& z);// ���������� �������� �������� ��� �������� �����
	vdouble PolynomValues(vdouble& a);// ���������� ������ �������� �������� ��� ��������� ������� ����� 
	Vector<double> PolynomDerivativesValue(const double& a, int N = 0);// ���������� �������� �������� � ��� ����������� ������� �� N ������������ ��� �������� �����. ���� N = 0, ��������� ����������� ���� ��������� ��������. ���������� ����� �������
	Vector<vdouble> PolynomDerivativesValues(vdouble& a, int N = 0);//���������� ������� �������� �������� � ��� ����������� ������� �� N ������������ ��� ��������� ������� �����. ���� N = 0, ��������� ����������� ���� ��������� ��������.  ���������� ����� �������
	vdouble PolynomSubsVariable(const double& a);// ���������� ������ ���������� y = x - a 
//	double MaxAbsRoots();// ������������ ������ ������ ��������
//	double MinAbsRoots();// ����������� ������ ������ ��������
	int roots(vdouble& dr, Vector<complex>& cr, Vector<int>& order_dr, Vector<int>& order_cr);// ��������� ����� ��������������� �������� - �������������� � �����������, �������� - �������
	int Lobachevski_Greffe_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& epsilon_control = 1.0e-2);//��������� �������������� � ����������� ����� ��������������� �������� ������� ������������ - ������ (��� ��������� � ����������� �������� �������)
	int Bernulli_roots(vdouble& dr, Vector<complex>& cr, vdouble& unsolved, const double& depsilon = 1.0e-8);//��������� �������������� � ����������� ����� ��������������� �������� ������� �������� (��� ��������� � ����������� �������� �������)
	int BernulliMinRealRoot(vdouble& dr, const double& depsilon = 1.0e-8);
	int PolynomNewtonRoot(complex& z, const double& epsilon = 1.0e-14);// ��������� ������������ ����� 
	int PolynomNewtonRoot(double& dr, const double& epsilon = 1.0e-16);// ��������� ��������������� �����
	int TranscendentNewtonRoot(double& x, double k, vdouble& v, const double& epsilon = 1.0e-16);// ��������� ������� ���������������� ��������� this->PolynomValue(x) * exp(k * x) + v.PolynomValue(x) = 0.0;
	int PolynomLinaThree_memberDivider(double& p, double& q); // ���������� ������������� �������� ��������� ���������� ������� ����
	int PolynomLinaDivider(vdouble& d); // ���������� �������� ����� ������� ��������� ���������� ������� ����
	double MaxAbsRoots(); // ���������� ����������� ��������� ������ ����� ��������
	double MinAbsRoots(); // ���������� ���������� ��������� ������ ����� ��������
	int WaveletDecomposition(vdouble& t,
	  int wf, // ���� ��������
	  int order, // ������� ��������
	  int& maxLevel, // ������������ �������� ����������
	  Vector<vdouble>& vtau,
	  Vector<vdouble>& vd, // ��������� ��� �������� d- ������������� �� ������ ������ ������������
	  Vector<vdouble>& vs, // ��������� ��� �������� s- ������������� �� ������ ������ ������������
	  Vector<vdouble>& vtauSF,
	  Vector<vdouble>& vSlow, // ��������� ��� �������� �������������� ������������ ������� �� ������ ������ ����������
	  Vector<vdouble>& vFast); // ��������� ��� �������� ��������������� ������������ �������, ��������� �� ������ ������ ����������
	int WaveletDecomposition(vdouble& t,
	  vdouble& dh,
	  vdouble& dg, 
	  vdouble& rh,
	  vdouble& rg,
	  int& left_h,
	  int& right_h,
	  int& left_g,
	  int& right_g,
	  int& maxLevel, // ������������ �������� ����������
	  Vector<vdouble>& vtd,
	  Vector<vdouble>& vd, // ��������� ��� �������� d- ������������� �� ������ ������ ������������
	  Vector<vdouble>& vts,
	  Vector<vdouble>& vs, // ��������� ��� �������� s- ������������� �� ������ ������ ������������
	  Vector<vdouble>& vtSlow,
	  Vector<vdouble>& vSlow, // ��������� ��� �������� �������������� ������������ ������� �� ������ ������ ����������
	  Vector<vdouble>& vtFast,
	  Vector<vdouble>& vFast); // ��������� ��� �������� ��������������� ������������ �������, ��������� �� ������ ������ ����������
/*
	int vdouble::WaveletDecomposition(int wf, // ���� ��������
	  int order, // ������� ��������
	  int& maxLevel, // ������������ �������� ����������
	  Vector<vdouble>& vd, // ��������� ��� �������� d- ������������� �� ������ ������ ������������
	  Vector<vdouble>& vs); // ��������� ��� �������� s- ������������� �� ������ ������ ������������
*/
};

struct LagerStruct
{
	double alpha; // alpha - �������� ����������� �������� �������
	double beta; // beta - �������� ����������� �������� �������
	double epsilon; // ������������ ������ ������������ ��������������� ������� ���������
	int maxOrder; // ����������� ���������� �������

	vdouble vQ;// ������������ ���������� �� ��������
	vdouble alphai; // ������������� ���������
	vdouble flip_betai; // ������������� ����������� (����������)
	vdouble num;// ��������� ������������ �������
	vdouble den;// ����������� ������������ �������
	double error;// ������ �������������
	double fund_det;// ����������� ��������������� ������� ���������

};


//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////

//##1
vdouble inline operator+(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr, "Error using operator+ : the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr, "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) + *(pv2+i);
	}
	return tempOb;
}

vdouble inline operator+(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) + a;
	}
	return tempOb;
}

vdouble inline operator+(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) + a;
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//1
vdouble inline operator-(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr, "Error using operator-: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr, "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) - *(pv2+i);
	}
	return tempOb;
}

//3

vdouble inline operator-(const double& a, vdouble& ob2)
{
	int len = ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob2.m_isgorizontal;
	double *pv, *pr; 
	pv = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a - *(pv+i);
	}
	return tempOb;
}

//5

vdouble inline operator-(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) - a;
	}
	return tempOb;
}

//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble inline operator^(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using operator^: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv1+i) , *(pv2+i) );
	}
	return tempOb;
}

//3
vdouble inline operator^(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(a,*(pv+i));
	}
	return tempOb;
}

//5
vdouble inline operator^(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv+i),a);
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
//1
vdouble inline pow(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using pow(): the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv1+i) , *(pv2+i) );
	}
	return tempOb;
}
//3
vdouble inline pow(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(a,*(pv+i));
	}
	return tempOb;
}
//5
vdouble inline pow(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = pow(*(pv+i),a);
	}
	return tempOb;
}
///////////////////////////////
//1
vdouble inline operator*(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using operator*: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) * *(pv2+i) ;
	}
	return tempOb;
}

//3
vdouble inline operator*(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a * *(pv+i);
	}
	return tempOb;
}
//4
vdouble inline operator*(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) =  *(pv+i) * a ;
	}
	return tempOb;
}
///////////////////////////////
///////////////////////////////
//1
vdouble inline operator/(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,  "Error using operator/: the lengthes of the vectors must be the same\n");
		return vdouble(0);
	}
	if (ob1.m_isgorizontal != ob2.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv1+i) / *(pv2+i) ;
	}
	return tempOb;
}
//3
vdouble inline operator/(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a / *(pv+i);
	}
	return tempOb;
}
//5
vdouble inline operator/(vdouble& ob, const double& a)
{
//	ob.WriteRaporto((CString)" operator/(vdouble& ob, const double& a) \t");
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i) / a;
	}
//ob.WriteRaporto((CString)" operator/ End \n");
	return tempOb;
}
///////////////////////////////
///////////////////////////////
//1
vdouble inline operator,(vdouble& ob1, vdouble& ob2)
{
	int len1 = ob1.m_length;
	int len = len1 + ob2.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob1.m_isgorizontal;
	double *pv1, *pv2, *pr; 
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = tempOb.pD;
	for(int i=0;i<len1;i++)
	{
		*(pr+i) = *(pv1+i);
	}
	for(i=len1; i<len; i++)
	{
		*(pr+i) = *(pv2+i);
	}
	return tempOb;
}
//3
vdouble inline operator,(const double& a, vdouble& ob)
{
	int len = ob.m_length + 1;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	*pr = a;
	for(int i=1;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	return tempOb;
}
//5
vdouble inline operator,(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	vdouble tempOb=vdouble(len+1);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = *(pv+i);
	}
	*(pr+len) = a;
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline operator+(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = +(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline operator-(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = -(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
vdouble inline log(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = log(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline log10(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = log10(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline abs(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = fabs(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline acos(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = acos(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline asin(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = asin(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline atan(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = atan(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////

vdouble inline atan2(vdouble& x, vdouble& y)
{
	int len = x.m_length;
	if (len != y.m_length)
	{
		fprintf(stderr,  "Error using atan2: the lengthes of the vectors must be the same\n");
		return vdouble(0);

	}
	if (x.m_isgorizontal != y.m_isgorizontal)
	{
		fprintf(stderr,  "Error: each vector must be vertical or gorizontal\n");
		return vdouble(0);
	}
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=x.m_isgorizontal;
	double *px, *py, *pr; 
	px = x.pD;
	py = y.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = atan2(*(px+i) , *(py+i));
	}
	return tempOb;
}

//////////////////////////////////////////////////////////////
vdouble inline cos(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = cos(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline cosh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = cosh(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sin(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sin(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sinh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sinh(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline tan(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = tan(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline tanh(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = tanh(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline sqrt(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = sqrt(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
vdouble inline exp(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = ::exp(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline floor(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = floor(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
vdouble inline ceil(vdouble& ob)
{
	int len = ob.m_length;
	vdouble tempOb;tempOb.resize(len);
	tempOb.m_isgorizontal=ob.m_isgorizontal;
	double *pv, *pr; 
	pv = ob.pD;
	pr = tempOb.pD;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = ceil(*(pv+i));
	}
	return tempOb;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator>(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) > (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator>(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a > (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) > a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator>=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator>=(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) >= (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator>=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a >= (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator>=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) >= a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator<(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator<(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) < (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator<(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a < (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator<(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) < a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator<=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator<=(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) <= (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator<=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a <= (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator<=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) <= a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
Vector<bool> inline operator==(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator==(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) == (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator==(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a == (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator==(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) == a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
Vector<bool> inline operator!=(vdouble& ob1, vdouble& ob2)
{
	int len = ob1.m_length;
	if (len != ob2.m_length)
	{
		fprintf(stderr,"Error using vdouble operator!=(vdouble& ob1, vdouble& ob2):\n");
		fprintf(stderr,"Lengthes of compared vectors = %i, %i must be equial",
			ob1.m_length, ob2.m_length);
		Vector<bool> vb_err;
		return vb_err;
	}
	Vector<bool> vbl(len);
	double *pv1, *pv2; 
	bool *pr;
	pv1 = ob1.pD;
	pv2 = ob2.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv1+i)) != (*(pv2+i));
	}
	return vbl;
}
Vector<bool> inline operator!=(const double& a, vdouble& ob)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = a != (*(pv+i));
	}
	return vbl;
}

Vector<bool> inline operator!=(vdouble& ob, const double& a)
{
	int len = ob.m_length;
	Vector<bool> vbl(len);
	double *pv; 
	bool *pr;
	pv = ob.pD;
	pr = vbl.data;
	for(int i=0;i<len;i++)
	{
		*(pr+i) = (*(pv+i)) != a;
	}
	return vbl;
}
//////////////////////////////////////////////////////////////
vdouble inline fliplr(vdouble& ob)
{
	vdouble v;
	int len = ob.m_length;
	v.resize(len);
	double *pv, *pob;
	pv = v.pD;
	pob = ob.pD + len - 1;
	for (int i = 0; i < len; i++)
	{
		*(pv + i) = *pob;
		pob--;
	}
	return v;
}
//////////////////////////////////////////////////////////////
void inline operator<<(vdouble& ob, const double& a)
{
	int len_1 = ob.m_length - 1;
	if ( len_1 < 0)
		return;
	double *pv, *pr; 
	pv = ob.pD + 1;
	pr = ob.pD;
	for (int i = 0; i < len_1; i++)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr + len_1) = a;
}
void inline operator>>(const double& a, vdouble& ob)
{
	int len_1 = ob.m_length - 1;
	if ( len_1 < 0)
		return;
	double *pv, *pr; 
	pv = ob.pD - 1;
	pr = ob.pD;
	for (int i = len_1; i > 0; i--)
	{
		*(pr + i) = *(pv+i);
	}
	*(pr) = a;
}
vdouble inline conv(vdouble& v1, vdouble& v2)
{
	int len, len1, len2, i, j, milen, malen;
	double *pc, *pci, *pmai, *pmi, *pma;
	len1 = v1.m_length;
	len2 = v2.m_length;

	len = len1 + len2 - 1;
	if (len < 0)
		len = 0;

	vdouble c = vdouble(len); pc = c.pD;

	bool bl = len1 <= len2;

	pmi = bl ? v1.pD : v2.pD;
	pma = bl ? v2.pD : v1.pD;
	milen = bl ? len1 : len2;
	malen = bl ? len2 : len1;

	for (i = 0; i < milen; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = 0; j <= i; j++)
			*pci += *(pmi + j) * *(pmai - j);
	}
	for (i = milen; i < malen; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = 0; j < milen; j++)
			*pci += *(pmi + j) * *(pmai - j);
	}
	for (i = malen; i < len; i++)
	{
		pci = pc + i; pmai = pma + i; * pci = 0.0;
		for (j = i - malen +1; j < milen; j++) 
			*pci += *(pmi + j) * *(pmai - j);
	}
	return c;
	
}
void inline operator<<(CArchive& ar, vdouble& v)
{
	ar << v.m_length;
	ar << v.m_dims;
	for (int dim = 0; dim < v.m_dims; dim++)
		ar << v.m_size[dim];

	double *vpD;
	vpD = v.pD;

	for (int i = 0; i < v.m_length; i++)
		ar << *(vpD + i);

}
void inline operator>>(CArchive& ar, vdouble& v)
{
	ar >> v.m_length;
	ar >> v.m_dims;
	v.m_size = Vector<int>(v.m_dims);
	for (int dim = 0; dim < v.m_dims; dim++)
		ar >> v.m_size[dim];

	vdouble::m_nConstructions++;

	if ((v.pD = (double*)malloc(v.m_length*SD)) == NULL && v.m_length != 0)
	{
		v.m_length = 0;
		AfxMessageBox("operator>>(CArchive& ar, vdouble& v) - Not enough memory");
		AfxThrowMemoryException();
		return;
	};
	vdouble::m_szMemory +=v.m_length*SD;
	v.m_isgorizontal=true;

	double *vpD;
	vpD = v.pD;

	for (int i = 0; i < v.m_length; i++)
		ar >> *(vpD + i);

}

//##2
#endif

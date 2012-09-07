// OGDoc.cpp : implementation of the COGDoc class
//

#include "stdafx.h"
//#include "OG.h"

#include "OGDoc.h"
#include "OGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

u_int COGDoc::s_nDocs = 0;

/////////////////////////////////////////////////////////////////////////////
// COGDoc

IMPLEMENT_DYNCREATE(COGDoc, CDocument)

BEGIN_MESSAGE_MAP(COGDoc, CDocument)
	//{{AFX_MSG_MAP(COGDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_COMMAND(ID_READ_DATA, OnReadData)
	ON_COMMAND(ID_ANIMATE_GRAPHIC, AnimateGraphic)
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGDoc construction/destruction

COGDoc::COGDoc()
{
	m_nDoc = s_nDocs;
	s_nDocs++;

	m_nSurfs = 3;

	m_vcPointsSurf.resize(m_nSurfs);
	m_vxSize.resize(m_nSurfs);
	m_vySize.resize(m_nSurfs);
	for (int s = 0; s < m_nSurfs; s++)
		m_vcPointsSurf[s].resize(0);
	m_cPoints2.resize(0);
	// TODO: add one-time construction code here

}

COGDoc::~COGDoc()
{
}
inline void MinMax (float d, float& Min, float& Max)
{
	//====== ������������ ���������� �� ������ ���������
	if (d > Max)
		Max = d;			// ���������� �� ��������
	else if (d < Min)
		Min = d;			// ���������� �� �������
}
Vector <CPoint3D> lorenz(float X_int, float Y_int, float Z_int, float time_step, int iterations)
{
	//EnterCriticalSection( &theApp.cs );
	Vector <CPoint3D> output_vector;
	output_vector.resize(iterations);
#if 0
	float 
		sigma = 10.f,
		gamma = 28.f,
		beta = float(8.f/3.f);
#else
	float 
		sigma = 10.f,
		gamma = 28.f,
		beta = float(8.f/3.f);
#endif
	float 
		x_star,
		y_star,
		z_star;
	for ( int i = 0; i < iterations; i++)
	{
		x_star = X_int + (-sigma*X_int + sigma*Y_int)*time_step;
		y_star = Y_int + (gamma*X_int - Y_int - Z_int*X_int)*time_step;
		z_star = Z_int + (-beta*Z_int + X_int * Y_int) * time_step;
		X_int = x_star;
		Y_int = y_star;
		Z_int = z_star;
		output_vector[i] = CPoint3D (x_star, y_star, z_star);
	}
	//LeaveCriticalSection( &theApp.cs );
	return output_vector;


}

BOOL COGDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COGDoc serialization

void COGDoc::Serialize(CArchive& ar)
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
// COGDoc diagnostics

#ifdef _DEBUG
void COGDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COGDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COGDoc commands
void COGDoc::DefaultGraphic()
{
	//EnterCriticalSection( &theApp.cs );
	//====== ������� ����� �����
	for (int s = 0; s < m_nSurfs; s++)
	{
		m_vxSize[s] = m_vySize[s] = 65;
		//====== ������� ����� �����

		//====== ����� ����� �� ������� ������ ����� �����
		UINT	nz = m_vySize[s] - 1,
				nx = m_vxSize[s] - 1;

		// ������ ����� � ������ ��� �������� �������� �������
		DWORD nSize = m_vxSize[s] * m_vySize[s] * sizeof(float)
							+ 2*sizeof(UINT);

		//====== ��������� ����� ��� �������� ������
		BYTE *buff = new BYTE[nSize+1];

		//====== ���������� �� ���� ���������� ������ ����
		UINT *p = (UINT*)buff;

		//====== ��������� ������ ������ ����
		*p++ = m_vxSize[s];
		*p++ = m_vySize[s];

		//====== ������ ��� ���������, ��� ��� ������
		//====== ���������� ���������� ������������ �����
		float *pf = (float*)p;

		//=== �������������� ��������� ������������ ���������
		double	fi = atan(1.)*6;
				m_kx = fi/nx,
				m_kz = fi/nz;

		//====== � ������� ����� ������� �� ����� �����
		//=== ��������� � �������� � ����� ������ ���� float
		for (UINT i=0;  i<m_vySize[s];  i++)
		{
			for (UINT j=0;  j<m_vxSize[s];  j++)
			{
				*pf++ = float (10*s + sin(m_kz*(i-nz/2.))
								* sin(m_kx*(j-nx/2.)));
			}
		}
		//====== �������� ������������� ������� m_cPointsSurf
		SetGraphPoints (s, buff, nSize);

		//=== ���������� ��� ����, ����� ������ �������
		//=== ���� ���� ������� �������� � ����
		DWORD nBytes;

		//=== �������� � �������� ����� ������ sin.dat
		HANDLE hFile = CreateFile(_T("sin.dat"), GENERIC_WRITE,
						0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

		//====== ������ � ���� ����� ������
		WriteFile(hFile,(LPCVOID)buff, nSize,&nBytes, 0);

		//====== ��������� ����
		CloseHandle(hFile);


		//====== ����������� ��������� �����
		delete [] buff;
		//LeaveCriticalSection( &theApp.cs );
	}

}
void COGDoc::SetGraphPoints(int s, BYTE* buff, DWORD nSize)
{


	//EnterCriticalSection( &theApp.cs );
	//====== ��������� � ����������� ������ ������
	//====== ��������� �� ���� ���������� ������ ����
	UINT *p = (UINT*)buff;

	//=== �������� ������ ������ ����, ������� ���������
	m_vxSize[s] = *p;
	m_vySize[s] = *++p;

	//====== �������� �� ������������������
	if (m_vxSize[s]<2 || m_vySize[s]<2 || 
			m_vxSize[s]*m_vySize[s]*sizeof(float)
			+ 2 * sizeof(UINT) != nSize)
	{
		AfxMessageBox(_T("������ �������������"));
		return;
	}

	//====== �������� ������ ����������
	//====== ��� ���� ��� ������ �����������
	m_vcPointsSurf[s].resize(m_vxSize[s]*m_vySize[s]);

		

	if (m_vcPointsSurf[s].empty())
	{
		AfxMessageBox(_T("�� �������� ���������� ������"));
		return;
	}

	//====== ���������� � ����� ������� �� ������
	//====== � �������� ���������������
	float	x, z,
			//====== ��������� ������ ��������
			*pf   = (float*)++p,
			fMinY = *pf,
			fMaxY = *pf,
			right = (m_vxSize[s]-1)/2.f,
			left  = -right,
			rear  = (m_vySize[s]-1)/2.f,
			front = -rear, 
			range = (right + rear)/2.f;

	UINT	i, j, n;

	//?????====== ���������� ������� ������������� �������
	m_fRangeY = range;
	m_fRangeX = float(m_vxSize[s]);
	m_fRangeZ = float(m_vySize[s]);

	//??????====== �������� ������ ����� ��� Z
//	m_zTrans = -1.5f * m_fRangeZ;

	//====== ���������� ���������� ����� (X-Z)
	//====== � ��������� � ���������� Y �� ������
	for (z=front, i=0, n=0;  i<m_vySize[s];  i++, z+=1.f)
	{
		for (x=left, j=0;  j<m_vxSize[s];  j++, x+=1.f, n++)
		{
			MinMax (*pf, fMinY, fMaxY);
			m_vcPointsSurf[s][n] = CPoint3D(x,z,*pf++);
		}
	}

	//====== ��������������� �������
	float zoom = fMaxY > fMinY ? range/(fMaxY-fMinY)
									 : 1.f;

	for (n=0;  n<m_vxSize[s]*m_vySize[s];  n++)
	{
		m_vcPointsSurf[s][n].y = zoom * (m_vcPointsSurf[s][n].y - fMinY)
							- range/2.f;
	}
	m_cPoints2 = lorenz(0.1f, 0.1f, 0.1f, 0.01f, 1000);
/*	CString str,s;
	for(int  ii =0; ii < m_cPoints2.size(); ii++)
	{
		s.Format("\n%g, %g, %g", m_cPoints2[ii].x, m_cPoints2[ii].y, m_cPoints2[ii].z);
		str += s;
	}
	FILE * stream;
	stream = fopen("C:\\lorenz.txt", "wt");
	fprintf(stream, str);
	fclose(stream);*/
	//LeaveCriticalSection( &theApp.cs );

}

//====== ������� ����������������� ������ ������
bool COGDoc::DoRead(HANDLE hFile)
{
	//EnterCriticalSection( &theApp.cs );
	//====== ������� ������ ������ �����
	DWORD nSize = GetFileSize (hFile, 0);

	//=== ���� �� ������� ���������� ������, GetFileSize
	//====== ���������� 0xFFFFFFFF
	if (nSize == 0xFFFFFFFF)
	{
		GetLastError();
		AfxMessageBox(_T("������������ ������ �����"));
		CloseHandle(hFile);
		return false;
	}

	//=== ������� ��������� ����� �������� � ���� ����
	BYTE *buff = new BYTE[nSize+1];

	//====== ��������� ������ �������� ������
	if (!buff)
	{
		AfxMessageBox(_T("������� ������� ������ �����"));
		CloseHandle(hFile);
		return false;
	}

	//====== �������� ������ �����
	DWORD nBytes;
	//====== ������� �������� ����
	ReadFile (hFile, buff, nSize, &nBytes, 0);
	CloseHandle(hFile);

	//====== ���� ������� ��������� ������� ����� ����
	if (nSize != nBytes)
	{
		AfxMessageBox(_T("������ ��� ������ �����"));
		return false;
	}

	//====== ��������� ����� �����������
	for (int s = 0; s < m_nSurfs; s++)
		SetGraphPoints (s, buff, nSize);

	//====== ������������ ���������� ������
	delete [] buff;
	//====== ���������� �����
	//LeaveCriticalSection( &theApp.cs );
	return true;
}


void COGDoc::ReadData()
{
	//EnterCriticalSection( &theApp.cs );
	//=== ������, � ������� ����� ������� �������� ����
	TCHAR szFile[MAX_PATH] = { 0 };

	//====== ������ �������� ������������ ������
	TCHAR *szFilter =TEXT("Graphics Data Files (*.dat)\0")
						TEXT("*.dat\0")
						TEXT("All Files\0")
						TEXT("*.*\0");

	//====== �������� ������� ����������	
	TCHAR szCurDir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH-1,szCurDir);

	//=== ��������� ������, ������������ �������� ��������
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(OPENFILENAME));

	//====== ��������� ���������� �������� �������
	ofn.lStructSize	= sizeof(OPENFILENAME);
	//====== ����-�������� �������
	ofn.hwndOwner = NULL;//GetSafeHwnd();
	ofn.lpstrFilter	= szFilter;
	//====== ������ ������ ������� (������� � �������)
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= szFile;
	ofn.nMaxFile		= sizeof(szFile);
	//====== ��������� ���� �������
	ofn.lpstrTitle	= _T("������� ���� � �������");
	ofn.nMaxFileTitle = sizeof (ofn.lpstrTitle);
	//====== ������ ����� ������� (������ � Win2K)
	ofn.Flags			= OFN_EXPLORER;

	//====== �������� � ����� �������
	//=== � ������ ������� GetOpenFileName ���������� 0
	if (GetOpenFileName(&ofn))
	{
		// ������� ������� ����, ������� ������ ������������
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ,
				FILE_SHARE_READ, 0, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, 0);

		//=== � ������ ������� CreateFile ���������� -1
		if (hFile == (HANDLE)-1)
		{
			AfxMessageBox(_T("�� ������� ������� ����"));
			return;
		}

		//====== ������� �������� ������ � ������� 
		if (!DoRead(hFile))
			return;

		//====== �������� ������ �����������
		POSITION posView;
		COGView * pView;
		posView = GetFirstViewPosition();
		while (posView !=NULL)
		{
			pView = (COGView*) GetNextView(posView);
		}

		pView->SendMessage(WM_USER + 10, 0, 0);
		//DrawScene();

		//====== ����������� ���� OpenGL
		//Invalidate(FALSE);
		UpdateAllViews(pView);
	}
	//LeaveCriticalSection( &theApp.cs );
}
void COGDoc::OnReadData() 
{
	ReadData();
}


void COGDoc::AnimateGraphic()
{
	for (int s = 0; s < m_nSurfs; s++)
	{
		//====== ����� ����� �� ������� ������ ����� �����
		UINT	nz = m_vySize[s] - 1,
				nx = m_vxSize[s] - 1;
		//=== �������������� ��������� ������������ ���������
		double	fi = atan(1.)*6;
	//			m_kx = fi/nx;
	//			m_kz = fi/nz;
		unsigned int i, j, n;
		float	x, z, 
				f = float (10*s + sin(m_kz*(0-nz/2.))
								* sin(m_kx*(0-nx/2.))),
				fMinY = f,
				fMaxY = f,
				right = (m_vxSize[s]-1)/2.f,
				left  = -right,
				rear  = (m_vySize[s]-1)/2.f,
				front = -rear, 
				range = (right + rear)/2.f;
		//====== � ������� ����� ������� �� ����� �����
		//=== ��������� � �������� � ����� ������ ���� float
		//====== ���������� ���������� ����� (X-Z)
		//====== � ��������� � ���������� Y �� ������
		for (z=front, i=0, n=0;  i<m_vySize[s];  i++, z+=1.f)
		{
			for (x=left, j=0;  j<m_vxSize[s];  j++, x+=1.f, n++)
			{
				f = float (10*s + sin(m_kz*(i-nz/2.))
								* sin(m_kx*(j-nx/2.)));
				m_vcPointsSurf[s][n] = CPoint3D(x,z,f);
			}
		}
		m_kz += .01f;
		m_kx += .01f;
	}
}

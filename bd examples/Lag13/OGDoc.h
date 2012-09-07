// OGDoc.h : interface of the COGDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_)
#define AFX_OGDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//========== ��������������� �����
class CPoint3D
{
public:
	//====== ���������� �����
	float x;
	float y;
	float z;

	//====== ����� �������������
	CPoint3D () 
	{
 	x = y = z = 0.f;
 }

	CPoint3D (float c1, float c2, float c3)
	{
		x = c1;
		z = c2;
		y = c3;
	}
	//====== �������� ����������
	CPoint3D& operator= (const CPoint3D& pt)
	{
		x = pt.x;	z = pt.z;	y = pt.y;
		return *this;
	}

	//====== ����������� �����������
	CPoint3D (const CPoint3D& pt)
	{
		*this = pt;
	}
};


class COGDoc : public CDocument
{
protected: // create from serialization only
	DECLARE_DYNCREATE(COGDoc)

// Attributes
public:
	COGDoc();
	static u_int s_nDocs;
	u_int m_nDoc;
	int m_nSurfs;
	//====== ������ ������ �����������
	Vector<Vector <CPoint3D> >
		m_vcPointsSurf;
//		m_cPoints,
	Vector <CPoint3D> m_cPoints2;
	Vector<UINT>	m_vxSize;		// ������� ������ ���� ����� X
	Vector<UINT>	m_vySize;		// ������� ������ ���� ����� Y
	GLfloat	m_fRangeX;		// ������ ������� ����� X
	GLfloat	m_fRangeY;		// ������ ������� ����� Y
	GLfloat	m_fRangeZ;		// ������ ������� ����� Z
	//====== �������� ������� �� ���������
	void DefaultGraphic();
	//====== �������� ������� �� ������ �� ������
	void SetGraphPoints(int s, BYTE* buff, DWORD nSize);
	//====== ������ ������ �� �����
	bool DoRead(HANDLE hFile);
	//====== ������ � ������ ������
	void ReadData();
	double m_kx, m_kz;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COGDoc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	void AnimateGraphic();
	virtual ~COGDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(COGDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnReadData();
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OGDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_)

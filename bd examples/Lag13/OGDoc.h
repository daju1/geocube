// OGDoc.h : interface of the COGDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_OGDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_)
#define AFX_OGDOC_H__5112A148_40FF_4E8D_9A93_12C6F8E2B994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//========== Вспомогательный класс
class CPoint3D
{
public:
	//====== Координаты точки
	float x;
	float y;
	float z;

	//====== Набор конструкторов
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
	//====== Операция присвоения
	CPoint3D& operator= (const CPoint3D& pt)
	{
		x = pt.x;	z = pt.z;	y = pt.y;
		return *this;
	}

	//====== Конструктор копирования
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
	//====== Массив вершин поверхности
	Vector<Vector <CPoint3D> >
		m_vcPointsSurf;
//		m_cPoints,
	Vector <CPoint3D> m_cPoints2;
	Vector<UINT>	m_vxSize;		// Текущий размер окна вдоль X
	Vector<UINT>	m_vySize;		// Текущий размер окна вдоль Y
	GLfloat	m_fRangeX;		// Размер объекта вдоль X
	GLfloat	m_fRangeY;		// Размер объекта вдоль Y
	GLfloat	m_fRangeZ;		// Размер объекта вдоль Z
	//====== Создание графика по умолчанию
	void DefaultGraphic();
	//====== Создание массива по данным из буфера
	void SetGraphPoints(int s, BYTE* buff, DWORD nSize);
	//====== Чтение данных из файла
	bool DoRead(HANDLE hFile);
	//====== Работа с файлом данных
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

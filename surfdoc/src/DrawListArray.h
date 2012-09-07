// DrawListArray.h: interface for the DrawListArray class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRAWLISTARRAY_H__A13D74D5_0ADE_49BA_8715_3604DBE1CCE3__INCLUDED_)
#define AFX_DRAWLISTARRAY_H__A13D74D5_0ADE_49BA_8715_3604DBE1CCE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Primitive3D.h"

class SurfDoc;


class DrawListArray  
{
//	bool m_bPaintOneObject;
	static GLuint m_nToPaint;
	static GLuint m_nParameters;
	static vector<bool> m_bDrawParam;

//	vector<PRIMITIVE_PTR> m_vPrimitivePtrs;
//	vector<LPVOID> m_vPtrs;
//	vector<int> m_vTypes;

	enum paint_mode { all, one, profile, parameter };

	static paint_mode paintMode;


	static SurfDoc * m_pSurfDoc;

//	GLuint  * m_pListArray;

	static vector<GLuint> m_etcListArray;

	static vector<GLuint> m_surfacesListArray;
	static vector<PRIMITIVE_PTR> m_surfacesPtrArray;

	static vector<GLuint> m_linesListArray;
	static vector<PRIMITIVE_PTR> m_linesPtrArray;

	static vector<GLuint> m_cutlinesListArray;
	static vector<PRIMITIVE_PTR> m_cutlinesPtrArray;

	static vector<GLuint> m_drillsListArray;
	static vector<PRIMITIVE_PTR> m_drillsPtrArray;

	static vector<GLuint> m_stringsListArray;
	static vector<PRIMITIVE_PTR> m_stringsPtrArray;

	static GLuint GetNewListNumber();
	static GLuint m_ngl_lists;
//	vect<unsigned int> m_vListArray;
public:
	friend LRESULT CALLBACK DlgProcSurfToPaint( HWND hDlg, UINT uMsg,
								  WPARAM wParam, LPARAM lParam );
	// inline:
//	void SetPaintOneObject(bool yes){m_bPaintOneObject = yes;}
//	bool GetPaintOneObject(){return m_bPaintOneObject;}
	static GLuint GetLinesListNumber()	{return (GLuint)m_linesListArray.size();}
	static GLuint GetListNumber()	{return m_ngl_lists;}
	static PRIMITIVE_PTR SetObjectToPaint(GLuint ntopaint);
	static GLuint GetObjectToPaint(){return m_nToPaint;}
	static void SetParametersNumber(GLuint n){
		m_nParameters = n;
		m_bDrawParam.resize(n, true);
	}
	static GLuint GetParametrNumber(){return m_nParameters;}
	static void SetPaintMode(DrawListArray::paint_mode mode)
	{
		DrawListArray::paintMode = mode;
	}
	//
//	void Alloc();
//	void Free();
	//void BuildListArray();
	static void glDeleteLists();
	static void glCallLists();
	static GLuint glNewList ();
	static void OnCreate(SurfDoc * pSurfDoc);

	DrawListArray();
	virtual ~DrawListArray();

};



#endif // !defined(AFX_DRAWLISTARRAY_H__A13D74D5_0ADE_49BA_8715_3604DBE1CCE3__INCLUDED_)

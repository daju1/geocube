// DrawListArray.cpp: implementation of the DrawListArray class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "DrawListArray.h"
//#include "raporto.h"
#include "winsurftree.h"
#include "SurfDoc.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
DrawListArray::paint_mode DrawListArray::paintMode = DrawListArray::all;

SurfDoc * DrawListArray::m_pSurfDoc;

vector<GLuint> DrawListArray::m_etcListArray;

vector<GLuint> DrawListArray::m_surfacesListArray;
vector<PRIMITIVE_PTR> DrawListArray::m_surfacesPtrArray;

vector<GLuint> DrawListArray::m_linesListArray;
vector<PRIMITIVE_PTR> DrawListArray::m_linesPtrArray;

vector<GLuint> DrawListArray::m_cutlinesListArray;
vector<PRIMITIVE_PTR> DrawListArray::m_cutlinesPtrArray;

vector<GLuint> DrawListArray::m_drillsListArray;
vector<PRIMITIVE_PTR> DrawListArray::m_drillsPtrArray;

vector<GLuint> DrawListArray::m_stringsListArray;
vector<PRIMITIVE_PTR> DrawListArray::m_stringsPtrArray;

GLuint DrawListArray::m_nToPaint;
GLuint DrawListArray::m_nParameters;
vector<bool> DrawListArray::m_bDrawParam;
GLuint DrawListArray::m_ngl_lists;


DrawListArray::DrawListArray()
{
//	this->m_nParameters = 1;
//	m_pListArray = NULL;
//	m_bPaintOneObject = false;
//	m_nCount = 0;
	m_ngl_lists = 0;
	m_nToPaint = 0;
	// #############################
	m_nParameters = 0;
	m_bDrawParam.resize(0, true);
	// #############################


}

DrawListArray::~DrawListArray()
{
	glDeleteLists();
}

void DrawListArray::OnCreate(SurfDoc * pSurfDoc)
{
	m_pSurfDoc = pSurfDoc;
//	m_vListArray.OnCreate(0);
}

GLuint DrawListArray::GetNewListNumber()
{
//char str[255];
//sprintf(str, "m_ngl_lists = %d GetNewListNumber() 0\n", m_ngl_lists);
//WriteRaporto(str);
//	m_ngl_lists++;
//sprintf(str, "m_ngl_lists = %d GetNewListNumber() 1\n", m_ngl_lists);
//WriteRaporto(str);
	GLuint List = FIRST_HARD_LIST+N_HARD_LISTS + (++m_ngl_lists);

//sprintf(str, "List = %d GetNewListNumber() 2\n", List);
//WriteRaporto(str);

	if (List == FIRST_FONT_LIST_BITMAPS)
	{
		char str[1024];
		sprintf(str, "Error: NewListNumber = %u over than %u ", List, FIRST_FONT_LIST_BITMAPS);
		MessageBox(0, str, "GetNewListNumber", 0);
	}
	return List;
}

GLuint DrawListArray::glNewList()
{
//char str[255];
//sprintf(str, "m_ngl_lists = %d DrawListArray::glNewList()\n", m_ngl_lists);
//WriteRaporto(str);
	GLuint List = GetNewListNumber();
//sprintf(str, "List = %d glNewList()\n", List);
//WriteRaporto(str);
	::glNewList(List, GL_COMPILE);
	return List;
}
// функции обратного вызова дл€ изображени€ объектов
// тут мы пр€мо используем номер в рисующем OpenGL списке, передаваемый в виде lParam
/*void __cdecl Func (HWND hwndTreeView, HTREEITEM hParentItem, HTREEITEM hItem, LPARAM id, LPARAM lParam)
{
	if (hParentItem != TVI_ROOT)
		// дл€ корневого потомка первого поколени€ 
		// не вызываем функцию обратного вызова
		// поскольку это означает пустую ветвь не наполненную объектами
	{
		UINT List = (UINT) lParam;
		if (List > 0) ::glCallList(List);
	}
}*/
// а здесь сложнее - в lParam содержитс€ указатель 
// на объект графического примитива, от класса которого 
// порождены классы - потомки более сложных графических объектов
// мы можем номер в рисующем OpenGL списке пр€мо через указатель 
// на графический примитив
// а можем, пользу€сь тем, что 
// в id содержитс€ идентификатор типа объекта
// произвеси динамическое преобразование указател€ из указател€ 
// на примитив в указатель на конкретный тип графического объекта
static void /*__cdecl*/ Draw_Func (HWND hwndTreeView, HTREEITEM hParentItem, HTREEITEM /*hItem*/, LPARAM lParam)
{
	if (hParentItem != TVI_ROOT)
		// дл€ корневого потомка первого поколени€ 
		// не вызываем функцию обратного вызова
		// поскольку это означает пустую ветвь не наполненную объектами
	{
//printf("lParam = %d\n", lParam);
		Object * pObject = reinterpret_cast<Object *> (lParam);
//printf("pObject = x%08x %s\n", pObject, Object::ObjectTypeToString(pObject->GetObjectType()));
		
		if (pObject)
		{
			if (!pObject->GetLayer() || 
				((unsigned int)pObject->GetLayer())==0xdddddddd || 
				(pObject->GetLayer() && pObject->GetLayer()->bChecked))
			{
				pObject->OnPaint();
			}
		}
	}
}
void DrawListArray::glCallLists()
{
//char str[255];
//sprintf(str, "m_ngl_lists = %d glCallLists()\n", m_ngl_lists);
//WriteRaporto(str);
#if 1
	switch (DrawListArray::paintMode)
	{
	case all:
		{
#if 0
			for (
				UINT List = FIRST_HARD_LIST+N_HARD_LISTS + 1; 
			List <= FIRST_HARD_LIST+N_HARD_LISTS         + m_ngl_lists; 
			List++)
				::glCallList(List);	
#else
			//printf("TreeView_EnumCheckedItems\n");
			//TreeView_EnumCheckedItems(DrawListArray::m_pSurfDoc->hwndTV, TVI_ROOT, 0, &Draw_Func, &Checking);
			TreeView_EnumCheckedItems(DrawListArray::m_pSurfDoc->hwndTV, TVI_ROOT, 0, &Draw_Func);
#endif
		}
		break;
	case one:
		{
			UINT List = FIRST_HARD_LIST+N_HARD_LISTS      +1 + m_nToPaint;
			::glCallList(List);	
		}
		break;
	case profile:
		{
			UINT nprofile = m_nToPaint;
			for (UINT nparam = 0; nparam < m_nParameters; nparam++)
			{
				if (m_bDrawParam[nparam])
				{
					UINT List = FIRST_HARD_LIST+N_HARD_LISTS + 1 + nprofile * m_nParameters + nparam;
					::glCallList(List);	
				}
			}
		}
		break;
	case parameter:
		{
			UINT nProfiles = m_ngl_lists / m_nParameters;
			UINT nparam = m_nToPaint;
			for ( UINT nprofile = 0; nprofile < nProfiles; nprofile++)
			{
				UINT List = FIRST_HARD_LIST+N_HARD_LISTS + 1 + nprofile * m_nParameters + nparam;
				::glCallList(List);	
				}
		}
		break;
	}
#else
	vector <GLuint>::iterator Iter;

	switch (DrawListArray::paintMode)
	{
	case all:
		{
			for ( Iter = m_linesListArray.begin( ) ; Iter != m_linesListArray.end( ) ; Iter++ )
				::glCallList(*Iter);	
		}
		break;
	case one:
		{
			UINT List = m_linesListArray[m_nToPaint];
			::glCallList(List);	
		}
		break;
	case profile:
		{
			UINT nprofile = m_nToPaint;
			for (UINT nparam = 0; nparam < m_nParameters; nparam++)
			{
				if (m_bDrawParam[nparam])
				{
					UINT List = m_linesListArray[nprofile * m_nParameters + nparam];
					::glCallList(List);	
				}
			}
		}
		break;
	case parameter:
		{
			UINT nProfiles = m_ngl_lists / m_nParameters;
			UINT nparam = m_nToPaint;
			for ( UINT nprofile = 0; nprofile < nProfiles; nprofile++)
			{
				UINT List = m_linesListArray[nprofile * m_nParameters + nparam];
				::glCallList(List);	
			}
		}
		break;
	}
	for ( Iter = m_surfacesListArray.begin( ) ; Iter != m_surfacesListArray.end( ) ; Iter++ )
		::glCallList(*Iter);	
	for ( Iter = m_drillsListArray.begin( ) ; Iter != m_drillsListArray.end( ) ; Iter++ )
		::glCallList(*Iter);	
	for ( Iter = m_cutlinesListArray.begin( ) ; Iter != m_cutlinesListArray.end( ) ; Iter++ )
		::glCallList(*Iter);	
	for ( Iter = m_stringsListArray.begin( ) ; Iter != m_stringsListArray.end( ) ; Iter++ )
		::glCallList(*Iter);	
//	for ( Iter = m_etcListArray.begin( ) ; Iter != m_etcListArray.end( ) ; Iter++ )
//		::glCallList(*Iter);	
#endif
//sprintf(str, "m_ngl_lists = %d glCallLists()\n", m_ngl_lists);
//WriteRaporto(str);
}
PRIMITIVE_PTR DrawListArray::SetObjectToPaint(GLuint ntopaint)
{
//char str[255];
//sprintf(str, "m_ngl_lists = %d SetObjectToPaint()\n", m_ngl_lists);
//WriteRaporto(str);
	m_nToPaint = ntopaint;
	vector<PRIMITIVE_PTR>::iterator Iter;
	switch (DrawListArray::paintMode)
	{
	case all:
		{
			for (
				Iter = m_linesPtrArray.begin( ) ; 
			Iter != m_linesPtrArray.end( ) ; Iter++ )
				return (*Iter);	
		}
		break;
	case one:
		{
			return m_linesPtrArray[m_nToPaint];
		}
		break;
	case profile:
		{
			UINT nprofile = m_nToPaint;
			for (UINT nparam = 0; nparam < m_nParameters; nparam++)
			{
				if (m_bDrawParam[nparam])
				{
					return m_linesPtrArray[nprofile * m_nParameters + nparam];
				}
			}
		}
		break;
	case parameter:
		{
			UINT nProfiles = m_ngl_lists / m_nParameters;
			UINT nparam = m_nToPaint;
			for ( UINT nprofile = 0; nprofile < nProfiles; nprofile++)
			{
				return m_linesPtrArray[nprofile * m_nParameters + nparam];
			}
		}
		break;
	}
//sprintf(str, "m_ngl_lists = %d SetObjectToPaint()\n", m_ngl_lists);
//WriteRaporto(str);
	return NULL;
}

void DrawListArray::glDeleteLists()
{
//char str[255];
//sprintf(str, "m_ngl_lists = %d glDeleteLists()0\n", m_ngl_lists);
//WriteRaporto(str);

	::glDeleteLists(FIRST_HARD_LIST+1,N_HARD_LISTS + (GLsizei) m_ngl_lists);

//sprintf(str, "m_ngl_lists = %d glDeleteLists()1\n", m_ngl_lists);
//WriteRaporto(str);

	m_ngl_lists = 0;

//sprintf(str, "m_ngl_lists = %d glDeleteLists()2\n", m_ngl_lists);
//WriteRaporto(str);
}

/*
void DrawListArray::Free()
{
	m_etcListArray.resize(0);

	m_surfacesListArray.resize(0);
	m_surfacesPtrArray.resize(0);

	m_linesListArray.resize(0);
	m_linesPtrArray.resize(0);

	m_cutlinesListArray.resize(0);
	m_cutlinesPtrArray.resize(0);

	m_drillsListArray.resize(0);
	m_drillsPtrArray.resize(0);

	m_stringsListArray.resize(0);
	m_stringsPtrArray.resize(0);

//	if (m_pListArray) 	HeapFree(GetProcessHeap(), 0, m_pListArray);
//	m_pListArray = NULL;
}

void DrawListArray::Alloc()
{
//	m_pListArray	= (GLuint  *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, 
//		sizeof(GLuint)*m_ngl_lists);
}
**/

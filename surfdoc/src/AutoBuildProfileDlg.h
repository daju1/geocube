// AutoBuildProfileDlg.h: interface for the AutoBuildProfileDlg class.
//
//////////////////////////////////////////////////////////////////////
#if !VIEW_ONLY_VERSION

#if !defined(AFX_AUTO_BUILD_PROFILE_DLG__H__DE99B0CB_C734_4929_BA45_8ED0234DF8C7__INCLUDED_)
#define AFX_AUTO_BUILD_PROFILE_DLG__H__DE99B0CB_C734_4929_BA45_8ED0234DF8C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "../../kohonen/src/kohonendlg.h"
//#include "../../array/src/sorting.h"
//#include "./generic.h"

#include "../../auto_build_3D/picks_search.h"
#include "AutoBuildProfileWnd.h"

struct FilesInDirectory
{
	int nFilesInDirectory;
	char **vFileNames;
	int *vFileNameLengthes;

	char szFileFilter[16];
	short nFileFilterID;
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	DWORD nFilterIndex;
#endif
};


class AutoBuildProfileDlg0  
{
protected:
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	friend LRESULT APIENTRY AutoBuildProfileWndSubclassProc(
		HWND hwnd, 
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam) ;
    HWND					hDlg;
#else
public:
    QWidget*				hDlg;
protected:
#endif

	FilesInDirectory		m_files_in_dir;
	char szFile		[4098];			// buffer for file name
	char directory	[2048];			// for dir name
	char szPath		[4098];			// buffer for file name
	char filename	[1024];

	AutoBuildProfile * p_auto_build_profile;
	bool consol;
	bool num_col_file_selected;

	AutoBuildProfileWnd	m_plotWnd;


public:

	void UseWholeDirectory();
	bool OpenFileDialog(void);

	virtual bool HandlingOfInputFiles() = 0;


    AutoBuildProfileDlg0()
    {
        hDlg = NULL;
    }
    virtual ~AutoBuildProfileDlg0()
    {

    }
};


class AutoBuildProfileDlg  : public AutoBuildProfileDlg0
{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	friend LRESULT APIENTRY AutoBuildProfileWndSubclassProc(
		HWND hwnd, 
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam) ;
#endif
public:
	auto_build_parametrs& m_ab;
	int m_extremums_filter_type;
	void OnDestroy();
	void OnButtonOK();
	void OnInitDialog();
    void OnButtonBrowseNumColomn();
	void ShowWindows_RelatedWith_CheckUseLocals();
	void ShowWindows_RelatedWith_Windows_Cycles();
	void ShowWindows_RelatedWith_Windows_Cycles2();

	bool HandlingOfInputFiles();

	AutoBuildProfileDlg(bool _consol, AutoBuildProfile * auto_build_profile, auto_build_parametrs& ab);
	virtual ~AutoBuildProfileDlg();
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	friend LRESULT CALLBACK DlgProcAutoBuildProfile( HWND hDlg, UINT uMsg,
								  WPARAM wParam, LPARAM lParam );
#endif
};

class AutoBuildProfileDlg1 : public AutoBuildProfileDlg0
{
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	friend LRESULT APIENTRY AutoBuildProfileWndSubclassProc(
		HWND hwnd, 
		UINT uMsg, 
		WPARAM wParam, 
		LPARAM lParam) ;
#endif

public:
	auto_build_parametrs& m_ab;
	int m_extremums_filter_type;
	void OnDestroy();
	void OnButtonOK();
	void OnInitDialog();
    void OnButtonBrowseNumColomn();
	void ShowWindows_RelatedWith_CheckUseLocals();
	void ShowWindows_RelatedWith_Windows_Cycles();
	void ShowWindows_RelatedWith_Windows_Cycles2();

	bool HandlingOfInputFiles();

	AutoBuildProfileDlg1(bool _consol, AutoBuildProfile * auto_build_profile, auto_build_parametrs& ab);
	virtual ~AutoBuildProfileDlg1();
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
	friend LRESULT CALLBACK DlgProcAutoBuildProfile1( HWND hDlg, UINT uMsg,
								  WPARAM wParam, LPARAM lParam );
#endif
};


#endif // !defined(AFX_POLYOTYNNETDLG_H__DE99B0CB_C734_4929_BA45_8ED0234DF8C7__INCLUDED_)

#endif /*!VIEW_ONLY_VERSION*/

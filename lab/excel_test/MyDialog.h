
#include <windows.h>
	
#include "../../excel_connect/src/MyExcel.h"

class MyDlg  
{
	friend LRESULT APIENTRY AutoBuildProfileWndSubclassProc(
    HWND hwnd, 
    UINT uMsg, 
    WPARAM wParam, 
    LPARAM lParam) ;
	HWND					hDlg;

	bool consol;

	char szFile		[4098];			// buffer for file name
	char directory	[2048];			// for dir name
	char szPath		[4098];			// buffer for file name
	char filename	[1024];

	MyExcel m_excel;


public:
	void OnDestroy();
	void OnButtonOK();
	void OnInitDialog();
	void OnButtonBroseNumColomn();

	void UseWholeDirectory();
	bool OpenFileDialog(void);
	bool HandlingOfInputFiles();

	MyDlg(bool _consol);
	virtual ~MyDlg();
	friend LRESULT CALLBACK MyDlgProc( HWND hDlg, UINT uMsg,
								  WPARAM wParam, LPARAM lParam );
};




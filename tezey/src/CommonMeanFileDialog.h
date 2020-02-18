// CommonMeanFileDialog.h: interface for the CommonMeanFileDialog class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMMONMEANFILEDIALOG_H__6B56B797_EC73_4682_8951_417923F24AEA__INCLUDED_)
#define AFX_COMMONMEANFILEDIALOG_H__6B56B797_EC73_4682_8951_417923F24AEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../tools/src/readfile.h"

struct OpenFilesToCommonData
{
    bool bUseWholeDirectory;
};

struct StartFinishDateDlgData
{
	HWND hwndParent;
	short startYear;
	short startMonth;
	short startDay;
	short finishYear;
	short finishMonth;
	short finishDay;	
	short shPeriodFlag;
	short shPeriodFlagMinStart;
	short shPeriodFlagMinEnd;
	short shPeriodFlagHoursStart;
	short shPeriodFlagHoursEnd;
	short shPeriodFlagHalfOfDay;
	short shFormatFlag;
	char delim;
	WORD delimID;

	bool bToCutPagesExcel;

	bool bMin;
	bool bMedian;
	bool bMean;
	bool bDisp;
	bool bMax;
	bool bPolarization;
	bool bInvPolarization;

	bool bMinAngle;
	bool bMedianAngle;
	bool bMeanAngle;
	bool bDispAngle;
	bool bMaxAngle;
	bool bPolarizationAngle;
	bool bInvPolarizationAngle;

	bool bMinAngle3;
	bool bMedianAngle3;
	bool bMeanAngle3;
	bool bDispAngle3;
	bool bMaxAngle3;
	bool bPolarizationAngle3;
	bool bInvPolarizationAngle3;

	bool bMinAngle4;
	bool bMedianAngle4;
	bool bMeanAngle4;
	bool bDispAngle4;
	bool bMaxAngle4;
	bool bPolarizationAngle4;
	bool bInvPolarizationAngle4;

	bool bMinXYZ;
	bool bMedianXYZ;
	bool bMeanXYZ;
	bool bDispXYZ;
	bool bMaxXYZ;
	bool bPolarizationXYZ;
	bool bInvPolarizationXYZ;

	bool bReverseAngles;
	bool bMeanPerDay;
	short nPribor;
	char  szPath_in[255];

	int nFilesInDirectory;
	char **vFileNames;
	int *vFileNameLengthes;

	short fileFormat;
	bool thisIsLocalTime;
	int localTimeOffsetHours;

	char szFileFilter[16];
	short nFileFilterID;

	short nHowUseFilePath;
};

struct CommonMeanFileData
{
	HWND hwndParent;
	short startYear;
	short startMonth;
	short startDay;
	short finishYear;
	short finishMonth;
	short finishDay;	
	short shPeriodFlag;
	short shPeriodFlagMinStart;
	short shPeriodFlagMinEnd;
	short shPeriodFlagHoursStart;
	short shPeriodFlagHoursEnd;
	short shPeriodFlagHalfOfDay;
//	short shFormatFlag;
	char delim;
	WORD delimID;

	bool bToCutPagesExcel;

	bool bMin;
	bool bMedian;
	bool bMean;
	bool bDisp;
	bool bAsim;
	bool bExcess;
	bool bMax;
	bool bPolarization;
	bool bInvPolarization;

	bool bMinAngle;
	bool bMedianAngle;
	bool bMeanAngle;
	bool bDispAngle;
	bool bMaxAngle;
	bool bPolarizationAngle;
	bool bInvPolarizationAngle;

	bool bMinAngle3;
	bool bMedianAngle3;
	bool bMeanAngle3;
	bool bDispAngle3;
	bool bMaxAngle3;
	bool bPolarizationAngle3;
	bool bInvPolarizationAngle3;

	bool bMinAngle4;
	bool bMedianAngle4;
	bool bMeanAngle4;
	bool bDispAngle4;
	bool bMaxAngle4;
	bool bPolarizationAngle4;
	bool bInvPolarizationAngle4;

	bool bMinXYZ;
	bool bMedianXYZ;
	bool bMeanXYZ;
	bool bDispXYZ;
	bool bMaxXYZ;
	bool bPolarizationXYZ;
	bool bInvPolarizationXYZ;

	bool bReverseAngles;
	bool bMeanPerDay;
	short nPribor;
//	char  szPath_in[255];

	int nFilesInDirectory;
	char **vFileNames;
	int *vFileNameLengthes;

	short fileFormat;
	bool thisIsLocalTime;
	int localTimeOffsetHours;

	short timeFormat;

	char szFileFilter[16];
	DWORD nFilterIndex;

	short nHowUseFilePath;
};


class CommonMeanFileDialog  
{
	friend INT_PTR CALLBACK DlgProc1( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
	friend INT_PTR CALLBACK DlgProc2( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
	friend INT_PTR CALLBACK DlgProc3( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
	// Массив описаний страниц блокнота Wizard
//	PROPSHEETPAGE *   psheetPage;
	int to_disp_msgbox;

	OpenFilesToCommonData	oftcd;
	DelimiterData			dd;
	CommonMeanFileData		cmfd;
	short					outputTimeFormat;

	HWND hWnd;
	char szFile		[4098];			// buffer for file name
	char directory	[2048];			// for dir name
	char szPath		[4098];			// buffer for file name

	vector<vector<cell> >	* pcells;
	vector<string>			* pnames_of_colomns;
	char					* filename;

	size_t					rows, cols;

	int n; // length of buffer string line
	char* szBuff; // buffer string line
	char* szBuff_old; // buffer string line
	char* title;

public:
	void cutting_of_output_file(
		FILE * stream2,
		int jj, // rows on excel file
		int kk, // pages on excel file
		char *directory_out,
		char *filename_out,
		char *filename_out_temp,
		int nPribor,
		char *sFormat,
		char *sPeriod,
		char *sExt
		);
	void EnableControls3(HWND hDlg, BOOL bEnable);
	void EnableControls2(HWND hDlg, BOOL bEnable);
	void createCommonFile();
	void createCommonFile2(size_t nInputs);
	CommonMeanFileDialog(HWND hwnd);
	virtual ~CommonMeanFileDialog();
	void UseWholeDirectory(HWND hDlg);
	void UseTheSelectedFile(HWND hDlg);
	bool TestAndStartHandlingOfInputFiles(HWND hDlg, bool toCorrect_time_sequence);
	void OnCreate(void);
	bool OpenFileDlg(void);
};

#endif // !defined(AFX_COMMONMEANFILEDIALOG_H__6B56B797_EC73_4682_8951_417923F24AEA__INCLUDED_)

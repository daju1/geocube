#if !defined(GENERIC_H__B2179A6F_INCLUDED_)
#define GENERIC_H__B2179A6F_INCLUDED_
// Идентификатор, отличающийся от всех идентификаторов меню.
//...........................................
#define ID_CHILDWINDOW 1000
void printDailyRaport(bool toPrint = true);
void createCommonFile();

typedef struct
{
	short scaleModeX;
	bool bIsSignal2Checked;
	char szFileFilter[16];
	char szSelectFileDlgName[230];
}	SELECTFILEDLGDATA, *LPSELECTFILEDLGDATA;

typedef struct
{
	HWND hWnd;
	bool notAddToExistingPlots;

	bool thisIsLocalTime;
	int localTimeOffsetHours;

	bool bUse_Header;

	bool bUse_timeFormat;
	short timeFormat;
	bool bUse_t1;
	bool bUse_t2;
	bool bUseIndexedTimeScale;

	bool bDispOn3docs;

	bool bIgnoreFirstLines;
	int nLinesToIgnore;

	char delim;
	int delimID;
	bool bUseAllCols;
	int nMaxCols;

	char filename[512];

	short startYear;
	short startMonth;
	short startDay;
	short finishYear;
	short finishMonth;
	short finishDay;
	double startTime;
	double finishTime;
	bool bUseStartFinishDate;

	LPSELECTFILEDLGDATA lpSelectFileDlgData;
}	POLYOTYFILEDLGDATA, *LPPOLYOTYFILEDLGDATA;

int importExcelCommonFileParam(LPPOLYOTYFILEDLGDATA lpPolyotyDlgData);

LRESULT CALLBACK ChildWndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK About  (HWND, UINT, WPARAM, LPARAM);
typedef struct
{
	char szPath[255];
	char directory[255];
	char filename[127];
	char ext[31];
	char szFileFilter[16];
	short SaveAsFileType;
}	SAVEASFILEDLGDATA, *LPSAVEASFILEDLGDATA;

int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
					 LPTSTR lpCmdLine, int nCmdShow );

#endif//

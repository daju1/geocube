#ifndef READ_FILE_H_
#define READ_FILE_H_
#include "../stdafx.h"
#include "../../array/src/Vector.h"
#include "../../array/src/Vdouble.h"

#define USE_STRING_IN_THE_CELL	1
#define CELL_S_N_CHARS			8

struct cell
{
	int 
		row,
		col;
#if USE_STRING_IN_THE_CELL
	string str;
#else
	char s[CELL_S_N_CHARS];
#endif
	double value;
};

struct DelimiterData
{
	bool bTab;
	bool bSpace;
	bool bComma;
	bool bCommaPoint;
	bool bOther;
	char charOther;

	bool bUseManyDelimitersAsOne;
};
void ParseLine(int iLine, char *szBuff, char *title, size_t bytes_line, DelimiterData dd,
		  vector<cell>* out_cells, vector<string> *out_strings, vector<double> *out_values, double *out_v);
int ReadDatFile(HWND hWnd, char * fpath, char* filename, vector<vector<double> > *pvectors, vector<string> * pnames);
int ReadInputFile(char * fname, vdouble& x, vdouble& y);
int GetDelimiterFromID(int delimID);
int ReadInputFile(char * fname, Vector<vdouble>& vv, int delim);
int ReadCellFile(HWND hWnd, char * fpath, char* filename, vector<vector<cell> > *pvectors, vector<string> * pnames, char delim );
int ReadCellFile(HWND hWnd, char * fpath, char* filename, vector<vector<cell> > *pvectors, vector<string> * pnames, DelimiterData dd, unsigned int max_rows_to_read );

int ReadDatFile(const char * filename, vector<double> & x, vector<double> & y, vector<double> & z);
int ReadDatFile(const char * filename, vdouble& x, vdouble& y, vdouble& z);
int ReadDatFile(const char * filename, vdouble& x, vdouble& y);
int ReadBlnFile(const char * filename, vdouble& x, vdouble& y, int& inside);
int ReadBlnFile(const char * filename, vdouble& x, vdouble& y, vdouble& z, int& inside);
int ReadBlnFile(const char * filename, vector<double>& x, vector<double>& y, int& inside);
int ReadBlnFile(const char * filename, vector<double>& x, vector<double>& y, vector<double>& z, int& inside);
int ReadBlnFile(const char * filename, vector<vector<vector<double> > > * vvvd, vector<int> * vinside);

int ReadCoordinateFromFile(const char * filename, double& f);


#endif

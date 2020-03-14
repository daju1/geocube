#pragma once

#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <windows.h>
#endif
#include <string>

using namespace std ;

#include "TrialDataDef.h"

struct plot_data_2d
{
	double x;
	double y;
	string sx;
	string sy;
	plot_data_2d()
	{
		x = 0.0;
		y = 0.0;
		sx = "";
		sy = "";
	}	
	plot_data_2d(double vx, double vy)
	{
		x = vx;
		y = vy;
		sx = "";
		sy = "";
	}		
	plot_data_2d(double vx, double vy, string s_x)
	{
		x = vx;
		y = vy;
		sx = s_x;
		sy = "";
	}	
	plot_data_2d(double vx, double vy, string s_x, string s_y)
	{
		x = vx;
		y = vy;
		sx = s_x;
		sy = s_y;
	}
	bool operator<(const plot_data_2d& rhs)
	{
		return x < rhs.x;
	}
};

#include <vector>
using namespace std;

class PlotData;
struct LinInterp
{
	double m_a0;
	double m_a1;
	double xmin;
	double xmax;
	COLORREF line_color;
	int line_style;
	int line_width;

	LinInterp();
	LinInterp(double a0, double a1);
	void Draw(PlotData * plot_data, HDC hDC);
};
struct LogInterp
{
	double m_C;
	double m_A;
	double m_x0;
	double xmin;
	double xmax;
	COLORREF line_color;
	int line_style;
	int line_width;

	LogInterp();
	LogInterp(double A, double C, double x0);
	void Draw(PlotData * plot_data, HDC hDC);
};
struct HypInterp
{
	// y = A / (x + x0)
	double m_A;
	double m_x0;
	double xmin;
	double xmax;
	COLORREF line_color;
	int line_style;
	int line_width;

	HypInterp();
	HypInterp(double A, double x0);
	void Draw(PlotData * plot_data, HDC hDC);
};
struct LinVertical
{
	double m_x;
	COLORREF line_color;
	int line_style;
	int line_width;

	LinVertical();
	LinVertical(double x);
	void Draw(PlotData * plot_data, HDC hDC);
};
struct axes_draw
{
	string str;
	SIZE sz;
	int x,y;
	double v;

	bool not_fixed;

	int draw_x;
	int draw_y;

	int left; // давление (нахлёст) слева
	int right; // давление справа

	int top; // давление сверху
	int bottom; // давление снизу


	void borders(axes_draw& rhs);
	void borders2(axes_draw& rhs);


	axes_draw(const char * s, SIZE _sz, int _x, int _y, double _v/* = 0*/)
	{
		if (!s || !strlen(s)) { str = ""; }
		else { str = s; }

		sz = _sz;
		x = _x;
		y = _y;

		v = _v;

		left = 0;
		right = 0;

		square = 0;
		not_fixed = true;
	}
	~axes_draw()
	{
//		if(str) delete[] str;
	}
	bool operator<(const axes_draw& rhs)
	{
		return x < rhs.x;
	}
	short square;
	void I();
	void II();
	void III();
	void IV();
};


struct plot_line
{

	bool line_plot;
	double min_x,min_y,max_x,max_y;
	vector<plot_data_2d> data;

	plot_line();
	void SetCenterAndScale(void);
	void Draw(PlotData * plot_data, HDC hDC, int lt, int rt, int tp, int bm, vector<axes_draw> & v_axes_draw_x, vector<axes_draw> & v_axes_draw_y, bool & to_draw_y);
	void Draw(PlotData * plot_data, HDC hDC);

	COLORREF line_color;
	int line_style;
	int line_width;

	enum label_precision
	{
		no = 0,
		one = 1,
		two, three, four, five, six, seven, eight, nine, ten
	};

	label_precision prec;
};

class PlotData
{
public:
	PlotData();
	~PlotData();

	bool x_ax_not_dubl;
	bool use_sx;
	bool use_sy;
	bool use_plot;
	int y_dir;
	static int plot_height;

	//bool x_log_scale;

	//vector<plot_data_2d> data;
	vector<plot_line> plot_lines;

	string title;
	string xlabel;
	string ylabel;
	//===== Текущие размеры окна графика
	tagSIZE m_Size;
	//===== Экранные координаты центра окна
	tagPOINT m_Center;
	//===== Переход к логическим координатам точек
	int MapToLogX (HDC hDC, double d);
	int MapToLogY (HDC hDC, double d);
	//===== Два типа шрифтов
	//HFONT m_TitleFont, m_Font, m_font, m_YLabelFont;
	//DrawPlot(hdc, x, y);	
	void Draw (HDC hDC,	tagRECT r, tagRECT margin);
	//===== Заголовок и наименования осей
	//char m_sTitle[255], m_sX[255], m_sY[255];
	//===== Высота буквы (зависит от шрифта)
	//int		m_LH,
	//===== Толщина пера
	//		m_Width;
	//void InitFonts();

		
	void SetCenterAndScale(void);

	double minx,miny,maxx,maxy;
	bool zero_min_x, zero_min_y;

	bool set_max_x;
	double max_x_to_set;

	vector<double> additional_x_for_scale;
	vector<double> additional_y_for_scale;


	vector<HypInterp> hyp_interp;
	vector<LogInterp> log_interp;
	vector<LinInterp> lin_interp;
	vector<LinVertical> lin_vertical;

	/*
	bool use_log_interp;
	double log_interp_a0;
	double log_interp_a1;
*/

	LOGFONT * GetTitleFont();
	LOGFONT * GetXLabelFont();
	LOGFONT * GetYLabelFont();
	LOGFONT * GetXAxesFont();
	LOGFONT * GetYAxesFont();


	static LOGFONT TitleFont;
	static LOGFONT XLabelFont;
	static LOGFONT YLabelFont;
	static LOGFONT XAxesFont;
	static LOGFONT YAxesFont;

	static void InitTitleFont();
	static void InitXLabelFont();
	static void InitYLabelFont();
	static void InitXAxesFont();
	static void InitYAxesFont();

};
#define max_str_len_val_printf_fmtstr 24
struct fmtstr
{
private:
	string s;	//string;
	bool nl;	//follow new line?
	bool astab;
	short * pf;	//flag of format
public:

	fmtstr(string str, short * flag, bool newline, bool as_tab)
	{
		s = str;
		pf = flag;
		nl = newline;
		astab = as_tab;
	}

	bool AsTab()
	{
		return astab;
	}

	bool NewLine()
	{
		return nl;
	}

	string& String()
	{
		return s;
	}

		
	static LOGFONT LogFont0;
	static LOGFONT LogFont1;
	static LOGFONT LogFont2;
	static LOGFONT LogFont3;

	static void InitFont0();
	static void InitFont1();
	static void InitFont2();
	static void InitFont3();

	LOGFONT * GetFont();
		
	COLORREF GetColor();
};

class LabData
{
public:
	vector <fmtstr> text;
	PlotData plot_data;
	static void SetPlotHeight(int h)
	{
		PlotData::plot_height = h;
	}
};
void DeleteEndZeros(char * str);

#include <windows.h>
#include <math.h>
#include <gdiplus.h>
using namespace Gdiplus;

#include "stdafx.h"
#include "LabPlotData.h"
#include "BaseLab.h"

#include "float.h"


#define SHTRICH_HEIGHT 3


//===== ƒол€ окна, занимаема€ графиком
#define PLOT_DATA_SCALE_X 0.8

#define PLOT_WITH_TEXT 0

LOGFONT fmtstr::LogFont0;
LOGFONT fmtstr::LogFont1;
LOGFONT fmtstr::LogFont2;
LOGFONT fmtstr::LogFont3;

LOGFONT * fmtstr::GetFont()
{
	if (pf)
	{
		switch(*pf)
		{
		case TRIAL_VALUE_DEFINED:
			return &LogFont1;
		case TRIAL_VALUE_DEFINED_CANNOT_EXCLUDED:
			return &LogFont1;
		case TRIAL_VALUE_DEFINED_CAN_EXCLUDED_ONLY_BY_MINSQLIN:
			return &LogFont1;

		case TRIAL_VALUE_INCLUDED:
			return &LogFont2;
		case TRIAL_VALUE_INCLUDED_TO_MINSQLIN:
			return &LogFont2;

		case TRIAL_VALUE_EXCLUDED:
			return &LogFont3;
		case TRIAL_VALUE_EXCLUDED_BY_MINSQLIN:
			return &LogFont3;
		case TRIAL_VALUE_EXCLUDED_AS_CONNECTED:
			return &LogFont3;
		default:
			return &LogFont0;
		}
	}
	return &LogFont0;
}

	
COLORREF fmtstr::GetColor()
{
	if (pf)
	{
		switch(*pf)
		{
		case TRIAL_VALUE_DEFINED:
			return RGB(0,0,0);
		case TRIAL_VALUE_DEFINED_CANNOT_EXCLUDED:
			return RGB(0,0,0);
		case TRIAL_VALUE_DEFINED_CAN_EXCLUDED_ONLY_BY_MINSQLIN:
			return RGB(0,0,0);

		case TRIAL_VALUE_INCLUDED:
			return RGB(0,200,0);
		case TRIAL_VALUE_INCLUDED_TO_MINSQLIN:
			return RGB(0,0,200);

		case TRIAL_VALUE_EXCLUDED:
			return RGB(200,0,0);
		case TRIAL_VALUE_EXCLUDED_BY_MINSQLIN:
			return RGB(200,0,200);

		case TRIAL_VALUE_EXCLUDED_AS_CONNECTED:
			return RGB(200,100,0);

		default:
			return RGB(0,0,0);
		}
	}
	return RGB(0,0,0);
}
#define height_of_font 18
void fmtstr::InitFont0()
{
	LogFont0.lfHeight				= height_of_font; // height of font
	LogFont0.lfWidth				= 0;  // average character width
	LogFont0.lfEscapement			= 0;  // angle of escapement
	LogFont0.lfOrientation			= 0;  // base-line orientation angle
	LogFont0.lfWeight				= 200;// font weight 
	LogFont0.lfItalic				= 0;  // italic attribute option
	LogFont0.lfUnderline			= 0;  // underline attribute option
	LogFont0.lfStrikeOut			= 0;  // strikeout attribute option
	LogFont0.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	//LogFont0.lfCharSet				= RUSSIAN_CHARSET;		// character set identifier
	
	LogFont0.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	LogFont0.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	LogFont0.lfQuality				= DEFAULT_QUALITY;		// output quality
	LogFont0.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(LogFont0.lfFaceName,		"Times New Roman");				// typeface name
}
void fmtstr::InitFont1()
{
	LogFont1.lfHeight				= height_of_font; // height of font
	LogFont1.lfWidth				= 0;  // average character width
	LogFont1.lfEscapement			= 0;  // angle of escapement
	LogFont1.lfOrientation			= 0;  // base-line orientation angle
	LogFont1.lfWeight				= 200;// font weight 
	LogFont1.lfItalic				= 0;  // italic attribute option
	LogFont1.lfUnderline			= 0;  // underline attribute option
	LogFont1.lfStrikeOut			= 0;  // strikeout attribute option
	LogFont1.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	//LogFont1.lfCharSet				= RUSSIAN_CHARSET;		// character set identifier
	
	LogFont1.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	LogFont1.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	LogFont1.lfQuality				= DEFAULT_QUALITY;		// output quality
	LogFont1.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(LogFont1.lfFaceName,		"Times New Roman");				// typeface name
}
void fmtstr::InitFont2()
{
	LogFont2.lfHeight				= height_of_font; // height of font
	LogFont2.lfWidth				= 0;  // average character width
	LogFont2.lfEscapement			= 0;  // angle of escapement
	LogFont2.lfOrientation			= 0;  // base-line orientation angle
	LogFont2.lfWeight				= 900;// font weight 
	LogFont2.lfItalic				= 0;  // italic attribute option
	LogFont2.lfUnderline			= 1;  // underline attribute option
	LogFont2.lfStrikeOut			= 0;  // strikeout attribute option
	LogFont2.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	//LogFont2.lfCharSet				= RUSSIAN_CHARSET;		// character set identifier
	
	LogFont2.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	LogFont2.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	LogFont2.lfQuality				= DEFAULT_QUALITY;		// output quality
	LogFont2.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	//strcpy(LogFont2.lfFaceName,		"Courier New");				// typeface name
	strcpy(LogFont2.lfFaceName,		"Times New Roman");				// typeface name
}
void fmtstr::InitFont3()
{
	LogFont3.lfHeight				= height_of_font; // height of font
	LogFont3.lfWidth				= 0;  // average character width
	LogFont3.lfEscapement			= 0;  // angle of escapement
	LogFont3.lfOrientation			= 0;  // base-line orientation angle
	LogFont3.lfWeight				= 900;// font weight 
	LogFont3.lfItalic				= 0;  // italic attribute option
	LogFont3.lfUnderline			= 0;  // underline attribute option
	LogFont3.lfStrikeOut			= 0;  // strikeout attribute option
	LogFont3.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	//LogFont3.lfCharSet				= RUSSIAN_CHARSET;		// character set identifier
	
	LogFont3.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	LogFont3.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	LogFont3.lfQuality				= DEFAULT_QUALITY;		// output quality
	LogFont3.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	//strcpy(LogFont3.lfFaceName,		"Courier New");				// typeface name
	strcpy(LogFont3.lfFaceName,		"Times New Roman");				// typeface name
}

LOGFONT PlotData::TitleFont;
LOGFONT PlotData::XLabelFont;
LOGFONT PlotData::YLabelFont;
LOGFONT PlotData::XAxesFont;
LOGFONT PlotData::YAxesFont;

void PlotData::InitTitleFont()
{
	PlotData::TitleFont.lfHeight				= 18; // height of font
	PlotData::TitleFont.lfWidth				= 0;  // average character width
	PlotData::TitleFont.lfEscapement			= 0;  // angle of escapement
	PlotData::TitleFont.lfOrientation			= 0;  // base-line orientation angle
	PlotData::TitleFont.lfWeight				= 200;// font weight 
	PlotData::TitleFont.lfItalic				= 0;  // italic attribute option
	PlotData::TitleFont.lfUnderline			= 0;  // underline attribute option
	PlotData::TitleFont.lfStrikeOut			= 0;  // strikeout attribute option
	PlotData::TitleFont.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	
	PlotData::TitleFont.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	PlotData::TitleFont.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	PlotData::TitleFont.lfQuality				= DEFAULT_QUALITY;		// output quality
	PlotData::TitleFont.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(PlotData::TitleFont.lfFaceName,		"Times New Roman");				// typeface name
}
void PlotData::InitXLabelFont()
{
	PlotData::XLabelFont.lfHeight				= 14; // height of font
	PlotData::XLabelFont.lfWidth				= 0;  // average character width
	PlotData::XLabelFont.lfEscapement			= 0;  // angle of escapement
	PlotData::XLabelFont.lfOrientation			= 0;  // base-line orientation angle
	PlotData::XLabelFont.lfWeight				= 200;// font weight 
	PlotData::XLabelFont.lfItalic				= 0;  // italic attribute option
	PlotData::XLabelFont.lfUnderline			= 0;  // underline attribute option
	PlotData::XLabelFont.lfStrikeOut			= 0;  // strikeout attribute option
	PlotData::XLabelFont.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	
	PlotData::XLabelFont.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	PlotData::XLabelFont.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	PlotData::XLabelFont.lfQuality				= DEFAULT_QUALITY;		// output quality
	PlotData::XLabelFont.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(PlotData::XLabelFont.lfFaceName,		"Times New Roman");				// typeface name
}
void PlotData::InitYLabelFont()
{
	PlotData::YLabelFont.lfHeight				= 14; // height of font
	PlotData::YLabelFont.lfWidth				= 0;  // average character width
	PlotData::YLabelFont.lfEscapement			= 900;  // angle of escapement
	PlotData::YLabelFont.lfOrientation			= 0;  // base-line orientation angle
	PlotData::YLabelFont.lfWeight				= 200;// font weight 
	PlotData::YLabelFont.lfItalic				= 0;  // italic attribute option
	PlotData::YLabelFont.lfUnderline			= 0;  // underline attribute option
	PlotData::YLabelFont.lfStrikeOut			= 0;  // strikeout attribute option
	PlotData::YLabelFont.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	
	PlotData::YLabelFont.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	PlotData::YLabelFont.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	PlotData::YLabelFont.lfQuality				= DEFAULT_QUALITY;		// output quality
	PlotData::YLabelFont.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(PlotData::YLabelFont.lfFaceName,		"Times New Roman");				// typeface name
}
void PlotData::InitXAxesFont()
{
	PlotData::XAxesFont.lfHeight				= 14; // height of font
	PlotData::XAxesFont.lfWidth				= 0;  // average character width
	PlotData::XAxesFont.lfEscapement			= 0;  // angle of escapement
	PlotData::XAxesFont.lfOrientation			= 0;  // base-line orientation angle
	PlotData::XAxesFont.lfWeight				= 200;// font weight 
	PlotData::XAxesFont.lfItalic				= 0;  // italic attribute option
	PlotData::XAxesFont.lfUnderline			= 0;  // underline attribute option
	PlotData::XAxesFont.lfStrikeOut			= 0;  // strikeout attribute option
	PlotData::XAxesFont.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	
	PlotData::XAxesFont.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	PlotData::XAxesFont.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	PlotData::XAxesFont.lfQuality				= DEFAULT_QUALITY;		// output quality
	PlotData::XAxesFont.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(PlotData::XAxesFont.lfFaceName,		"Times New Roman");				// typeface name
}
void PlotData::InitYAxesFont()
{
	PlotData::YAxesFont.lfHeight				= 14; // height of font
	PlotData::YAxesFont.lfWidth				= 0;  // average character width
	PlotData::YAxesFont.lfEscapement			= 0;  // angle of escapement
	PlotData::YAxesFont.lfOrientation			= 0;  // base-line orientation angle
	PlotData::YAxesFont.lfWeight				= 200;// font weight 
	PlotData::YAxesFont.lfItalic				= 0;  // italic attribute option
	PlotData::YAxesFont.lfUnderline			= 0;  // underline attribute option
	PlotData::YAxesFont.lfStrikeOut			= 0;  // strikeout attribute option
	PlotData::YAxesFont.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	
	PlotData::YAxesFont.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	PlotData::YAxesFont.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	PlotData::YAxesFont.lfQuality				= DEFAULT_QUALITY;		// output quality
	PlotData::YAxesFont.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(PlotData::YAxesFont.lfFaceName,		"Times New Roman");				// typeface name
}
LinInterp::LinInterp()
{

	m_a0 = 0.0;
	m_a1 = 0.0;
	xmin = -DBL_MAX;
	xmax = DBL_MAX;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}
LinInterp::LinInterp(double a0, double a1)
{
	m_a0 = a0;
	m_a1 = a1;
	xmin = -DBL_MAX;
	xmax = DBL_MAX;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}

void LinInterp::Draw(PlotData * plot_data, HDC hDC)
{
	double px,py;
	int x,y;

	HPEN pen = CreatePen(this->line_style, this->line_width, this->line_color);
	HPEN penold = (HPEN__ *)SelectObject(hDC, pen);

		px = (this->xmin - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
		if (px < - 0.5)
		{
			px = - 0.5;
			py = (this->m_a0 + plot_data->minx * this->m_a1 - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;
		}
		else
			py = (this->m_a0 + this->xmin * this->m_a1 - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

		x = plot_data->MapToLogX(hDC, px);
		y = plot_data->MapToLogY(hDC, py);
        
		MoveToEx(hDC, x, y, NULL);

		px = (this->xmax - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
		if (px > 0.5) 
		{
			px = 0.5;
			py = (this->m_a0 + plot_data->maxx * this->m_a1 - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;
		}
		else
			py = (this->m_a0 + this->xmax * this->m_a1 - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

		x = plot_data->MapToLogX(hDC, px);
		y = plot_data->MapToLogY(hDC, py);			
		
		LineTo(hDC, x, y);


	SelectObject (hDC, penold);
	DeleteObject(pen);
}

LogInterp::LogInterp()
{

	m_A = 0.0;
	m_C = 0.0;
	m_x0 = 0.0;
	xmin = -DBL_MAX;
	xmax = DBL_MAX;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}
LogInterp::LogInterp(double A, double C, double x0)
{
	m_A = A;
	m_C = C;
	m_x0 = x0;

	xmin = -DBL_MAX;
	xmax = DBL_MAX;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}

void LogInterp::Draw(PlotData * plot_data, HDC hDC)
{
	double px,py;
	int x,y;

	HPEN pen = CreatePen(this->line_style, this->line_width, this->line_color);
	HPEN penold = (HPEN__ *)SelectObject(hDC, pen);

	double MinX = max(plot_data->minx, this->xmin);
	double MaxX = min(plot_data->maxx, this->xmax);

		double X = MinX;
		double Y = this->m_C - this->m_A * log(X + this->m_x0);

		px = (X - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
		/*if (px < - 0.5)
		{
			px = - 0.5;
			py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;
		}
		else*/
			py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

		bool moved = false;

		//if (py >= -0.5 && py <=0.5)
		{
			x = plot_data->MapToLogX(hDC, px);
			y = plot_data->MapToLogY(hDC, py);
		    
			MoveToEx(hDC, x, y, NULL);
			moved = true;
		}

		int maxj = 100;

		for (int j = 1; j <= maxj; j++)
		{

			X = MinX + (double (j) / double (maxj)) * (MaxX - MinX);
			Y = this->m_C - this->m_A * log(X + this->m_x0);

			//px = (X - minx) / (maxx - minx) - 0.5;
			//py = ((this->log_interp_a0 + log(X) * this->log_interp_a1) - miny) / (maxy - miny) - 0.5;

			px = (X - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
			/*if (px > 0.5) 
			{
				px = 0.5;
				py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;
			}
			else*/
				py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

			//if (py >= -0.5 && py <=0.5)
			{
				x = plot_data->MapToLogX(hDC, px);
				y = plot_data->MapToLogY(hDC, py);			
				
				if (moved)
					LineTo(hDC, x, y);
				else
				{
					MoveToEx(hDC, x, y, NULL);
					moved = true;
				}
			}

		
		}

	SelectObject (hDC, penold);
	DeleteObject(pen);
}

HypInterp::HypInterp()
{

	m_A = 0.0;
	m_x0 = 0.0;
	xmin = -DBL_MAX;
	xmax = DBL_MAX;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}
HypInterp::HypInterp(double A, double x0)
{
	m_A = A;
	m_x0 = x0;

	xmin = -DBL_MAX;
	xmax = DBL_MAX;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}

void HypInterp::Draw(PlotData * plot_data, HDC hDC)
{
	double px,py;
	int x,y;

	HPEN pen = CreatePen(this->line_style, this->line_width, this->line_color);
	HPEN penold = (HPEN__ *)SelectObject(hDC, pen);

	double MinX = max(plot_data->minx, this->xmin);
	double MaxX = min(plot_data->maxx, this->xmax);

		double X = MinX;
		double Y = this->m_A / (X + this->m_x0);

		px = (X - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
		/*if (px < - 0.5)
		{
			px = - 0.5;
			py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;
		}
		else*/
			py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

		bool moved = false;

		//if (py >= -0.5 && py <=0.5)
		{
			x = plot_data->MapToLogX(hDC, px);
			y = plot_data->MapToLogY(hDC, py);
		    
			MoveToEx(hDC, x, y, NULL);
			moved = true;
		}

		int maxj = 100;

		for (int j = 1; j <= maxj; j++)
		{

			X = MinX + (double (j) / double (maxj)) * (MaxX - MinX);
			Y = this->m_A / (X + this->m_x0);

			//px = (X - minx) / (maxx - minx) - 0.5;
			//py = ((this->log_interp_a0 + log(X) * this->log_interp_a1) - miny) / (maxy - miny) - 0.5;

			px = (X - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
			/*if (px > 0.5) 
			{
				px = 0.5;
				py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;
			}
			else*/
				py = (Y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

			//if (py >= -0.5 && py <=0.5)
			{
				x = plot_data->MapToLogX(hDC, px);
				y = plot_data->MapToLogY(hDC, py);			
				
				if (moved)
					LineTo(hDC, x, y);
				else
				{
					MoveToEx(hDC, x, y, NULL);
					moved = true;
				}
			}

		
		}

	SelectObject (hDC, penold);
	DeleteObject(pen);
}

LinVertical::LinVertical()
{
	m_x = 0.0;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}
LinVertical::LinVertical(double x)
{
	m_x = x;
	this->line_style = PS_SOLID;
	this->line_color = RGB(0,200,0);
	this->line_width = 0;
}
void LinVertical::Draw(PlotData * plot_data, HDC hDC)
{
	double px,py;
	int x,y;

	HPEN pen = CreatePen(this->line_style, this->line_width, this->line_color);
	HPEN penold = (HPEN__ *)SelectObject(hDC, pen);

		px = (this->m_x - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;		
		py = 0.5;

		x = plot_data->MapToLogX(hDC, px);
		y = plot_data->MapToLogY(hDC, py);
        
		MoveToEx(hDC, x, y, NULL);

		py = - 0.5;

		y = plot_data->MapToLogY(hDC, py);			
		
		LineTo(hDC, x, y);

	SelectObject (hDC, penold);
	DeleteObject(pen);
}


plot_line::plot_line()
{
	data.resize(0);
	this->line_plot = true;

	this->line_style = PS_SOLID;
	this->line_color = RGB(255,100,0);
	this->line_width = 0;

	this->prec = plot_line::label_precision::three;
}

PlotData::PlotData()
{
	this->x_ax_not_dubl = false;
	this->use_sx = false;
	this->use_sy = false;
	this->use_plot = false;
	this->y_dir = +1;

	this->zero_min_x = true;
	this->zero_min_y = true;

	set_max_x = false;
	max_x_to_set = 0.0;



/*	use_lin_interp = false;
	lin_interp_a0 = 0.0;
	lin_interp_a1 = 0.0;
	lin_interp_xmin = -DBL_MAX;
	lin_interp_xmax = DBL_MAX;

	use_lin_interp2 = false;
	lin_interp2_a0 = 0.0;
	lin_interp2_a1 = 0.0;
	lin_interp2_xmin = -DBL_MAX;
	lin_interp2_xmax = DBL_MAX;
*/
//	use_log_interp = false;
//	log_interp_a0 = 0.0;
//	log_interp_a1 = 0.0;

	

}
int PlotData::plot_height = 200;


PlotData::~PlotData()
{
}
int PlotData::MapToLogX (HDC hDC, double d)
{
	return m_Center.x + int (PLOT_DATA_SCALE_X * m_Size.cx * d);
}

int PlotData::MapToLogY (HDC hDC, double d)
{
	HFONT fontold, fontnew;

	fontnew = ::CreateFontIndirect(GetXLabelFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);
	SIZE szXLabel;	
	if (!GetTextExtentPoint32(hDC,           // handle to DC
		"0",  // text string
		1,      // characters in string
		&szXLabel      // string size
		))
	{
	}
	SelectObject (hDC,fontold);
	DeleteObject (fontnew);

	fontnew = ::CreateFontIndirect(GetXAxesFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);
	SIZE szXAxes;	
	if (!GetTextExtentPoint32(hDC,           // handle to DC
		"0",  // text string
		1,      // characters in string
		&szXAxes      // string size
		))
	{
	}
	SelectObject (hDC,fontold);
	DeleteObject (fontnew);

	fontnew = ::CreateFontIndirect(GetYAxesFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);
	SIZE szYAxes;	
	if (!GetTextExtentPoint32(hDC,           // handle to DC
		"0",  // text string
		1,      // characters in string
		&szYAxes      // string size
		))
	{
	}
	SelectObject (hDC,fontold);
	DeleteObject (fontnew);

	fontnew = ::CreateFontIndirect(GetYLabelFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);
	SIZE szYLabel;	
	if (!GetTextExtentPoint32(hDC,           // handle to DC
		"0",  // text string
		1,      // characters in string
		&szYLabel      // string size
		))
	{
	}
	SelectObject (hDC,fontold);
	DeleteObject (fontnew);


	fontnew = ::CreateFontIndirect(GetTitleFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);
	SIZE szTitle;	
	if (!GetTextExtentPoint32(hDC,           // handle to DC
		"Title",  // text string
		5,      // characters in string
		&szTitle      // string size
		))
	{
	}
	SelectObject (hDC,fontold);
	DeleteObject (fontnew);	
	
	double x_axes_size_y = szXAxes.cy + 3*SHTRICH_HEIGHT-1;
	double plot_data_scale_y = 1.0 - double((szYAxes.cy + SHTRICH_HEIGHT) + (szTitle.cy + SHTRICH_HEIGHT) + x_axes_size_y + (szXLabel.cy + SHTRICH_HEIGHT)) / double(m_Size.cy);
	

	double delta_y = 0.0;
	if (this->y_dir == -1)
	{
		delta_y = ( (szTitle.cy + SHTRICH_HEIGHT) + (szXLabel.cy + SHTRICH_HEIGHT) + x_axes_size_y)
			+ 0.5 * plot_data_scale_y * m_Size.cy - 0.5 * m_Size.cy;
	}
	else
	{
		delta_y = ( (szTitle.cy + SHTRICH_HEIGHT) + (szYAxes.cy + SHTRICH_HEIGHT))
			+ 0.5 * plot_data_scale_y * m_Size.cy - 0.5 * m_Size.cy;
	}
	return m_Center.y + delta_y - this->y_dir * (int (plot_data_scale_y * m_Size.cy * d));
}
void plot_line::SetCenterAndScale(void)
{
	min_x = min_y = DBL_MAX;
	max_x = max_y = -DBL_MAX;
	
	for (size_t n1 = 0; n1 < data.size();n1++)
	{
		if (data[n1].x < min_x) min_x = data[n1].x;
		if (data[n1].x > max_x) max_x = data[n1].x;
		
		if (data[n1].y < min_y) min_y = data[n1].y;
		if (data[n1].y > max_y) max_y = data[n1].y;
	}
}

void PlotData::SetCenterAndScale(void)
{
	minx = miny = DBL_MAX;
	maxx = maxy = -DBL_MAX;
	
	for (size_t n1 = 0; n1 < plot_lines.size(); n1++)
	{
		plot_lines[n1].SetCenterAndScale();

		if (plot_lines[n1].min_x < minx) minx = plot_lines[n1].min_x;
		if (plot_lines[n1].max_x > maxx) maxx = plot_lines[n1].max_x;
		
		if (plot_lines[n1].min_y < miny) miny = plot_lines[n1].min_y;
		if (plot_lines[n1].max_y > maxy) maxy = plot_lines[n1].max_y;
	}

	for (size_t n1 = 0; n1 < additional_x_for_scale.size(); n1++)
	{
		if (additional_x_for_scale[n1] < minx) minx = additional_x_for_scale[n1];
		if (additional_x_for_scale[n1] > maxx) maxx = additional_x_for_scale[n1];
	}

	for (size_t n1 = 0; n1 < additional_y_for_scale.size(); n1++)
	{
		if (additional_y_for_scale[n1] < miny) miny = additional_y_for_scale[n1];
		if (additional_y_for_scale[n1] > maxy) maxy = additional_y_for_scale[n1];
	}

	if (this->zero_min_y && miny > 0.0) miny = 0.0;
	if (this->zero_min_x && minx > 0.0) minx = 0.0;

	if (this->set_max_x) maxx = max_x_to_set;
}

//axes_draw::sort_mode axes_draw::s_sort_mode = axes_draw::sort_mode::by_x;
LOGFONT * PlotData::GetTitleFont()
{
	return &PlotData::TitleFont;
}
LOGFONT * PlotData::GetXLabelFont()
{
	return &PlotData::XLabelFont;
}
LOGFONT * PlotData::GetYLabelFont()
{
	return &PlotData::YLabelFont;
}
LOGFONT * PlotData::GetXAxesFont()
{
	return &PlotData::XAxesFont;
}
LOGFONT * PlotData::GetYAxesFont()
{
	return &PlotData::YAxesFont;
}

void axes_draw::I()
{
	// I
	this->square = 1;
	this->draw_x = this->x + SHTRICH_HEIGHT;
	this->draw_y = this->y + SHTRICH_HEIGHT;	
}

void axes_draw::II()
{
	// II
	this->square = 2;
	this->draw_x = this->x + SHTRICH_HEIGHT;
	this->draw_y = this->y - this->sz.cy - SHTRICH_HEIGHT;
}

void axes_draw::III()
{
	// III
	this->square = 3;
	this->draw_x = this->x - this->sz.cx - SHTRICH_HEIGHT;
	this->draw_y = this->y - this->sz.cy - SHTRICH_HEIGHT;	
}

void axes_draw::IV()
{
	// IV
	this->square = 4;
	this->draw_x = this->x - this->sz.cx - SHTRICH_HEIGHT;
	this->draw_y = this->y + SHTRICH_HEIGHT;	
}



void plot_line::Draw(PlotData * plot_data, HDC hDC, int lt, int rt, int tp, int bm, vector<axes_draw> & v_axes_draw_x, vector<axes_draw> & v_axes_draw_y, bool & to_draw_y)
{
	std::sort(data.begin(), data.end());

	HFONT fontold, fontnew;
	double px,py;
	int x,y;
	char str[1024];
	SIZE sz;	

	for (int i = 0; i < (int)data.size(); i++)
	{
		px = (data[i].x - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
		py = (data[i].y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

		x = plot_data->MapToLogX(hDC, px);
		y = plot_data->MapToLogY(hDC, py);

		MoveToEx(hDC, x, bm, NULL);
		LineTo(hDC, x, bm + plot_data->y_dir*SHTRICH_HEIGHT);

		if (plot_data->use_sx && strlen(data[i].sx.c_str()))
		{
			sprintf(str, "%s", data[i].sx.c_str());
		}
		else
		{
			sprintf(str, "%f", data[i].x); DeleteEndZeros(str); 
		}

		fontnew = ::CreateFontIndirect(plot_data->GetXAxesFont());
		fontold = (HFONT__ *)SelectObject(hDC,fontnew);

		if (!GetTextExtentPoint32(hDC,           // handle to DC
			str,  // text string
			strlen(str),      // characters in string
			&sz      // string size
			))
		{
		}

		SelectObject (hDC,fontold);
		DeleteObject (fontnew);

		bool to_add_x_axes = true;

		if (!this->line_plot || plot_data->x_ax_not_dubl)
		{
			for (vector<axes_draw>::iterator it = v_axes_draw_x.begin();
				it != v_axes_draw_x.end(); it++)
			{
				if ((*it).v == data[i].x)
				{
					to_add_x_axes = false;
				}
			}
		}

		if (to_add_x_axes)
			v_axes_draw_x.push_back(axes_draw(str,sz,x,bm + plot_data->y_dir*SHTRICH_HEIGHT, data[i].x));

		MoveToEx(hDC, lt, y, NULL);
		LineTo(hDC, lt-3, y);

		if (plot_data->use_sy && strlen(data[i].sy.c_str()))
		{
			sprintf(str, "%s", data[i].sy.c_str());
		}
		else
		{

			switch(this->prec)
			{
			case plot_line::label_precision::no:                
				sprintf(str, "");
				break;
			case plot_line::label_precision::one:                
				sprintf(str, "%0.1f", data[i].y);
				break;
			case plot_line::label_precision::two:                
				sprintf(str, "%0.2f", data[i].y);
				break;
			case plot_line::label_precision::three:                
				sprintf(str, "%0.3f", data[i].y);
				break;
			case plot_line::label_precision::four:                
				sprintf(str, "%0.4f", data[i].y);
				break;
			case plot_line::label_precision::five:                
				sprintf(str, "%0.5f", data[i].y);
				break;
			case plot_line::label_precision::six:                
				sprintf(str, "%0.6f", data[i].y);
				break;
			case plot_line::label_precision::seven:                
				sprintf(str, "%0.7f", data[i].y);
				break;
			case plot_line::label_precision::eight:                
				sprintf(str, "%0.8f", data[i].y);
				break;
			case plot_line::label_precision::nine:                
				sprintf(str, "%0.9f", data[i].y);
				break;
			case plot_line::label_precision::ten:                
				sprintf(str, "%0.10f", data[i].y);
				break;
			default:
				sprintf(str, "%0.3f", data[i].y);
			}
			//char err[128];
			//sprintf(err, "this->prec = %d", (int)this->prec);
			//MessageBox(0, str, err, 0);
			DeleteEndZeros(str); 
		}

		fontnew = ::CreateFontIndirect(plot_data->GetYAxesFont());
		fontold = (HFONT__ *)SelectObject(hDC,fontnew);

		if (!GetTextExtentPoint32(hDC,           // handle to DC
			str,  // text string
			strlen(str),      // characters in string
			&sz      // string size
			))
		{
		}
		SelectObject (hDC,fontold);
		DeleteObject (fontnew);

		v_axes_draw_y.push_back(axes_draw(str,sz,x,y, data[i].y));
	}

	if (this->line_plot)
	{
		if (plot_data->y_dir == 1)
		{
			for (int i = 0; i < (int)v_axes_draw_y.size(); i++)
			{
				if (i == 0)
				{
					if (v_axes_draw_y[i].v < v_axes_draw_y[i+1].v)
					{
						// рост
						// III
						v_axes_draw_y[i].III();
					}
					else
					{
						// падение
						// II
						v_axes_draw_y[i].II();
					}
				}
				else if (i == (int)v_axes_draw_y.size() - 1)
				{
					if (v_axes_draw_y[i].v > v_axes_draw_y[i-1].v)
					{
						// рост
						// III
						v_axes_draw_y[i].III();
					}
					else
					{
						// падение
						// II
						v_axes_draw_y[i].II();
					}		
				}
				else
				{
					if (v_axes_draw_y[i].v > v_axes_draw_y[i-1].v && v_axes_draw_y[i].v < v_axes_draw_y[i+1].v)
					{
						// рост
						// III
						v_axes_draw_y[i].III();
					}
					else if (v_axes_draw_y[i].v < v_axes_draw_y[i-1].v && v_axes_draw_y[i].v > v_axes_draw_y[i+1].v)
					{
						//printf("flow %s\n",v_axes_draw_y[i]->str);
						// падение
						// II
						v_axes_draw_y[i].II();
					}
					else if (v_axes_draw_y[i].v > v_axes_draw_y[i-1].v && v_axes_draw_y[i].v > v_axes_draw_y[i+1].v)
					{
						//printf("max %s\n",v_axes_draw_y[i]->str);
						//максимум
						if (v_axes_draw_y[i-1].v > v_axes_draw_y[i+1].v)
						{
							// на фоне падени€
							// II
							v_axes_draw_y[i].II();
						}
						else
						{
							// на фоне роста
							// III
							v_axes_draw_y[i].III();
						}
					}
					else if (v_axes_draw_y[i].v < v_axes_draw_y[i-1].v && v_axes_draw_y[i].v < v_axes_draw_y[i+1].v)
					{
						//минимум
						if (v_axes_draw_y[i-1].v > v_axes_draw_y[i+1].v)
						{
							// на фоне падени€
							// IV
							v_axes_draw_y[i].IV();
						}
						else
						{				
							// на фоне роста
							// I
							v_axes_draw_y[i].I();
						}
					}
					else
					{
						v_axes_draw_y[i].I();
					}
				}
			}	

		}
		else
		{
			for (int i = 0; i < (int)v_axes_draw_y.size(); i++)
			{
				if (i == 0)
				{
					if (v_axes_draw_y[i].v * plot_data->y_dir < v_axes_draw_y[i+1].v * plot_data->y_dir)
					{
						// рост
						// I
						v_axes_draw_y[i].I();
					}
					else
					{
						// падение
						// IV
						v_axes_draw_y[i].IV();
					}
				}
				else if (i == (int)v_axes_draw_y.size() - 1)
				{
					if (v_axes_draw_y[i].v * plot_data->y_dir > v_axes_draw_y[i-1].v * plot_data->y_dir)
					{
						// рост
						// I
						v_axes_draw_y[i].I();
					}
					else
					{
						// падение
						// IV
						v_axes_draw_y[i].IV();
					}		
				}
				else
				{
					if (v_axes_draw_y[i].v * plot_data->y_dir > v_axes_draw_y[i-1].v * plot_data->y_dir && v_axes_draw_y[i].v * plot_data->y_dir < v_axes_draw_y[i+1].v * plot_data->y_dir)
					{
						// рост
						// I
						v_axes_draw_y[i].I();
					}
					else if (v_axes_draw_y[i].v * plot_data->y_dir < v_axes_draw_y[i-1].v * plot_data->y_dir && v_axes_draw_y[i].v * plot_data->y_dir > v_axes_draw_y[i+1].v * plot_data->y_dir)
					{
						//printf("flow %s\n",v_axes_draw_y[i]->str);
						// падение
						// IV
						v_axes_draw_y[i].IV();
					}
					else if (v_axes_draw_y[i].v * plot_data->y_dir > v_axes_draw_y[i-1].v * plot_data->y_dir && v_axes_draw_y[i].v * plot_data->y_dir > v_axes_draw_y[i+1].v * plot_data->y_dir)
					{
						//printf("max %s\n",v_axes_draw_y[i]->str);
						//максимум
						if (v_axes_draw_y[i-1].v * plot_data->y_dir > v_axes_draw_y[i+1].v * plot_data->y_dir)
						{
							// на фоне падени€
							// IV
							v_axes_draw_y[i].IV();
						}
						else
						{
							// на фоне роста
							// III
							v_axes_draw_y[i].III();
						}
					}
					else if (v_axes_draw_y[i].v * plot_data->y_dir < v_axes_draw_y[i-1].v * plot_data->y_dir && v_axes_draw_y[i].v * plot_data->y_dir < v_axes_draw_y[i+1].v * plot_data->y_dir)
					{
						//минимум
						if (v_axes_draw_y[i-1].v * plot_data->y_dir > v_axes_draw_y[i+1].v * plot_data->y_dir)
						{
							// на фоне падени€
							// IV
							v_axes_draw_y[i].IV();
						}
						else
						{				
							// на фоне роста
							// I
							v_axes_draw_y[i].I();
						}
					}
					else
						v_axes_draw_y[i].I();

				}
			}	
		}
	}
	if (this->line_plot)
	{	
		to_draw_y = true;
	}
}
void plot_line::Draw(PlotData * plot_data, HDC hDC)
{
	HPEN pen = CreatePen(this->line_style, this->line_width, this->line_color);
	HPEN penold = (HPEN__ *)SelectObject(hDC, pen);
	
	double px,py;
	int x,y;
	for (int i = 0; i < (int)data.size(); i++)
	{
		px = (data[i].x - plot_data->minx) / (plot_data->maxx - plot_data->minx) - 0.5;
		py = (data[i].y - plot_data->miny) / (plot_data->maxy - plot_data->miny) - 0.5;

		x = plot_data->MapToLogX(hDC, px);
		y = plot_data->MapToLogY(hDC, py);

		if (this->line_plot)
		{
			if (i == 0)
			{
				MoveToEx(hDC, x, y, NULL);
			}
			else
			{
				LineTo(hDC, x, y);
			}
		}

		SetPixel(hDC, x-1, y-1, line_color);
		SetPixel(hDC, x-1, y, line_color);
		SetPixel(hDC, x-1, y+1, line_color);

		SetPixel(hDC, x, y-1, line_color);
		SetPixel(hDC, x, y+1, line_color);

		SetPixel(hDC, x+1, y-1, line_color);
		SetPixel(hDC, x+1, y, line_color);
		SetPixel(hDC, x+1, y+1, line_color);
	}
	SelectObject (hDC, penold);
	DeleteObject(pen);

}


void axes_draw::borders(axes_draw& rhs)
{
	/*printf("this->str.c_str() = %s %d\t", this->str.c_str(), this->square);
	printf("draw_x = %d\t", this->draw_x);
	printf("draw_y = %d\t", this->draw_y);

	printf("sz.cx = %d\t", this->sz.cx);
	printf("sz.cy = %d\n", this->sz.cy);

	printf("rhs.  str.c_str() = %s %d\t", rhs.str.c_str(), rhs.square);
	printf("draw_x = %d\t", rhs.draw_x);
	printf("draw_y = %d\t", rhs.draw_y);

	printf("sz.cx = %d\t", rhs.sz.cx);
	printf("sz.cy = %d\n", rhs.sz.cy);*/

	if( fabs(double(this->draw_x - rhs.draw_x)) < max(this->sz.cx, rhs.sz.cx) 
		&& 
		fabs(double(this->draw_y - rhs.draw_y)) < max(this->sz.cy, rhs.sz.cy) )
	{
		//printf("!!!\n");
		if (this->draw_y < rhs.draw_y)
		{
			if (rhs.square == 3 && rhs.not_fixed)
				rhs.I();
			if (rhs.square == 2 && rhs.not_fixed)
				rhs.IV();

			if (this->square == 4 && this->not_fixed)
				this->II();
			if (this->square == 1 && this->not_fixed)
				this->III();
		}
		else
		{
			if (this->square == 3 && this->not_fixed)
				this->I();
			if (this->square == 2 && this->not_fixed)
				this->IV();

			if (rhs.square == 4 && rhs.not_fixed)
				rhs.II();
			if (rhs.square == 1 && rhs.not_fixed)
				rhs.III();
		}
		/*printf("this->str.c_str() = %s %d\t", this->str.c_str(), this->square);
		printf("draw_x = %d\t", this->draw_x);
		printf("draw_y = %d\t", this->draw_y);

		printf("sz.cx = %d\t", this->sz.cx);
		printf("sz.cy = %d\n", this->sz.cy);

		printf("rhs.  str.c_str() = %s %d\t", rhs.str.c_str(), rhs.square);
		printf("draw_x = %d\t", rhs.draw_x);
		printf("draw_y = %d\t", rhs.draw_y);

		printf("sz.cx = %d\t", rhs.sz.cx);
		printf("sz.cy = %d\n", rhs.sz.cy);

		printf("!\n");*/
	}
}

void axes_draw::borders2(axes_draw& rhs)
{
	if( fabs(double(this->draw_x - rhs.draw_x)) < max(this->sz.cx, rhs.sz.cx) 
		&& 
		fabs(double(this->draw_y - rhs.draw_y)) < max(this->sz.cy, rhs.sz.cy) )
	{
		if (this->draw_y < rhs.draw_y)
		{
			this->draw_y = rhs.draw_y - this->sz.cy;
			this->not_fixed = false;
		}
	}
}

void PlotData::Draw(HDC hDC, tagRECT r, tagRECT margin)
{
	HFONT fontold, fontnew;
	//====== — помощью контекста устройства
	//====== узнаем адрес окна, его использующего
//	int nDC = SaveDC(hDC);
	double px,py;
	int x,y;
	SIZE sz;	

	//====== —оздаем черное перо дл€ изображени€ рамки
	HPEN boxPen = CreatePen(PS_SOLID, 0, COLORREF(0));
	HPEN gridPen = CreatePen(PS_SOLID, 0, RGB(92,200,178));
//	HPEN linePen = CreatePen(PS_SOLID, 0, line_color);
//	HPEN interpPen = CreatePen(PS_SOLID, 0, RGB(0,200,0));
//	HPEN interpPen2 = CreatePen(PS_DOT, 0, RGB(100,200,0));
	
	//====== ”точн€ем размеры окна
	m_Size.cx = r.right - r.left;
	m_Size.cy = r.bottom - r.top;

	HPEN penold = (HPEN__ *)SelectObject(hDC, boxPen);

	MoveToEx(hDC, r.left, r.bottom, NULL);
	LineTo(hDC, r.left, r.top);
	LineTo(hDC, r.right, r.top);
	LineTo(hDC, r.right, r.bottom);
	LineTo(hDC, r.left, r.bottom);

	SelectObject (hDC, penold);

	m_Center.x = (r.right + r.left)/2;
	m_Center.y = (r.bottom + r.top)/2;	

	for (vector<LinVertical>::iterator it = this->lin_vertical.begin(); 
		it != this->lin_vertical.end(); it++)
	{
		(*it).Draw(this, hDC);
	}

	for (vector<LinInterp>::iterator it = this->lin_interp.begin(); 
		it != this->lin_interp.end(); it++)
	{
		(*it).Draw(this, hDC);
	}

	for (vector<LogInterp>::iterator it = this->log_interp.begin(); 
		it != this->log_interp.end(); it++)
	{
		(*it).Draw(this, hDC);
	}

	for (vector<HypInterp>::iterator it = this->hyp_interp.begin(); 
		it != this->hyp_interp.end(); it++)
	{
		(*it).Draw(this, hDC);
	}

	//====== ѕреобразуем координаты рамки
	int lt = MapToLogX(hDC, -0.5),
		rt = MapToLogX(hDC, 0.5),
		tp = MapToLogY(hDC, 0.5),
		bm = MapToLogY(hDC, -0.5);
	 
	penold = (HPEN__ *)SelectObject(hDC, gridPen);

	MoveToEx(hDC, lt, bm, NULL);
	LineTo(hDC, lt, tp);
	LineTo(hDC, rt, tp);
	LineTo(hDC, rt, bm);
	LineTo(hDC, lt, bm);

	vector<axes_draw> v_axes_draw_x;
	vector<axes_draw> v_axes_draw_y;

	////////////////////////////////////////////////////
	bool to_draw_y = false;

	for (vector<plot_line>::iterator it = this->plot_lines.begin();
		it != this->plot_lines.end(); it++)
	{
		(*it).Draw(this, hDC, lt, rt, tp, bm, v_axes_draw_x, v_axes_draw_y, to_draw_y);
	}

		
	std::sort(v_axes_draw_x.begin(), v_axes_draw_x.end());
	std::sort(v_axes_draw_y.begin(), v_axes_draw_y.end());

	
	////////////////////////////////////////////////////




	for (int i = 0; i < (int)v_axes_draw_x.size(); i++)
	{
		v_axes_draw_x[i].draw_x = v_axes_draw_x[i].x - v_axes_draw_x[i].sz.cx/2;
		if (this->y_dir == -1)
			v_axes_draw_x[i].draw_y = bm-3*SHTRICH_HEIGHT+1 - v_axes_draw_x[i].sz.cy ;
		else
			v_axes_draw_x[i].draw_y = bm+3*SHTRICH_HEIGHT-1;

	}	

	int j = 0;

	while (true)
	{
		j++;
		for (int i = 0; i < (int)v_axes_draw_x.size(); i++)
		{		
			v_axes_draw_x[i].left = 0;
			v_axes_draw_x[i].right = 0;
		}
		for (int i = 0; i < (int)v_axes_draw_x.size(); i++)
		{
			if (i > 0)
			{
				v_axes_draw_x[i].left = 3 + v_axes_draw_x[i-1].draw_x + v_axes_draw_x[i-1].sz.cx - v_axes_draw_x[i].draw_x;
				if (v_axes_draw_x[i].left < 0)
					v_axes_draw_x[i].left = 0;
			}

			if (i < (int)v_axes_draw_x.size()-1)
			{
				v_axes_draw_x[i].right = 3 + v_axes_draw_x[i].draw_x + v_axes_draw_x[i].sz.cx - v_axes_draw_x[i+1].draw_x;
				if (v_axes_draw_x[i].right < 0)
					v_axes_draw_x[i].right = 0;
			}
		}
		bool good = true;
		for (int i = 0; i < (int)v_axes_draw_x.size(); i++)
		{
			if ( !v_axes_draw_x[i].left && v_axes_draw_x[i].right)
			{
				good = false;
				v_axes_draw_x[i].draw_x -= 3;//v_axes_draw_x[i]->right;
				if (v_axes_draw_x[i].draw_x < margin.left)
					v_axes_draw_x[i].draw_x = margin.left;
			}
			if ( v_axes_draw_x[i].left && !v_axes_draw_x[i].right)
			{
				good = false;
				v_axes_draw_x[i].draw_x += 3;//v_axes_draw_x[i]->left;
			}
		}
		if (good || j > 100)
			break;
	}

	fontnew = ::CreateFontIndirect(GetXAxesFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);

	for (int i = 0; i < (int)v_axes_draw_x.size(); i++)
	{
		MoveToEx(hDC, v_axes_draw_x[i].x, bm+this->y_dir*SHTRICH_HEIGHT, NULL);
		LineTo(hDC, v_axes_draw_x[i].draw_x + v_axes_draw_x[i].sz.cx/2, bm+2*this->y_dir*SHTRICH_HEIGHT);
		LineTo(hDC, v_axes_draw_x[i].draw_x + v_axes_draw_x[i].sz.cx/2, bm+3*this->y_dir*SHTRICH_HEIGHT);
		TextOut(hDC, v_axes_draw_x[i].draw_x, v_axes_draw_x[i].draw_y, v_axes_draw_x[i].str.c_str(), (int)strlen(v_axes_draw_x[i].str.c_str()));
	}

	SelectObject (hDC,fontold);
	DeleteObject (fontnew);


	SelectObject (hDC, penold);



	fontnew = ::CreateFontIndirect(this->GetYAxesFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);

	if (to_draw_y)
	{	
		int n = this->plot_lines.size();		
		for (int i = 0; i+n-1 < (int)v_axes_draw_y.size(); i+=n)
		{
			for (int j1 = 0; j1 < n; j1++)
			{
				for (int j2 = 0; j2 < j1; j2++)
				{
					v_axes_draw_y[i+j1].borders(v_axes_draw_y[i+j2]);
				}
			}
			if ((i/n) < v_axes_draw_x.size())
			{
				for (int j1 = 0; j1 < n; j1++)
				{
					v_axes_draw_y[i+j1].borders2(v_axes_draw_x[(i/n)]);
				}
			}
			for (int j1 = 0; j1 < n; j1++)
			{
				for (int j2 = 0; j2 < j1; j2++)
				{
					v_axes_draw_y[i+j1].borders(v_axes_draw_y[i+j2]);
				}
			}
		}
		for (int i = 0; i < (int)v_axes_draw_y.size(); i++)
		{
			TextOut(hDC, v_axes_draw_y[i].draw_x, v_axes_draw_y[i].draw_y, v_axes_draw_y[i].str.c_str(), (int)strlen(v_axes_draw_y[i].str.c_str()));
		}
	}

	SelectObject (hDC,fontold);
	DeleteObject (fontnew);	

	v_axes_draw_y.clear();
	v_axes_draw_x.clear();

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// Title

	x = MapToLogX(hDC, 0.0);
	y = MapToLogY(hDC, 0.5);

	fontnew = ::CreateFontIndirect(GetTitleFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);

	SIZE szTitle;
	if (!GetTextExtentPoint32(hDC,           // handle to DC
		this->title.c_str(),  // text string
		strlen(this->title.c_str()),      // characters in string
		&szTitle      // string size
		))
	{
	}

	TextOut(hDC, x - szTitle.cx/2, r.top + SHTRICH_HEIGHT, this->title.c_str(), (int)strlen(this->title.c_str()));

	SelectObject (hDC,fontold);
	DeleteObject (fontnew);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// XLabel

	fontnew = ::CreateFontIndirect(GetXLabelFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);

	if (!GetTextExtentPoint32(hDC,           // handle to DC
		this->xlabel.c_str(),  // text string
		strlen(this->xlabel.c_str()),      // characters in string
		&sz      // string size
		))
	{
	}

	if (this->y_dir == -1)
	{
		TextOut(hDC, r.right - sz.cx - 3 * SHTRICH_HEIGHT, r.top + 2 * SHTRICH_HEIGHT + szTitle.cy, this->xlabel.c_str(), (int)strlen(this->xlabel.c_str()));
	}
	else
	{
		TextOut(hDC, r.right - sz.cx - 3 * SHTRICH_HEIGHT, r.bottom - SHTRICH_HEIGHT - sz.cy, this->xlabel.c_str(), (int)strlen(this->xlabel.c_str()));
	}

	SelectObject (hDC,fontold);
	DeleteObject (fontnew);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// YLabel
	x = MapToLogX(hDC, -0.5);
	y = MapToLogY(hDC,  0.0);

	fontnew = ::CreateFontIndirect(GetYLabelFont());
	fontold = (HFONT__ *)SelectObject(hDC,fontnew);

	if (!GetTextExtentPoint32(hDC,           // handle to DC
		this->ylabel.c_str(),  // text string
		strlen(this->ylabel.c_str()),      // characters in string
		&sz      // string size
		))
	{
	}
	TextOut(hDC, x - sz.cy - 2 * SHTRICH_HEIGHT, y + sz.cx / 2, this->ylabel.c_str(), (int)strlen(this->ylabel.c_str()));

	SelectObject (hDC,fontold);
	DeleteObject (fontnew);

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

//	penold = (HPEN__ *)SelectObject(hDC, linePen);

	////////////////////////////////////////////////////

	for (vector<plot_line>::iterator it = this->plot_lines.begin();
		it != this->plot_lines.end(); it++)
	{
		(*it).Draw(this, hDC);
	}
	
	////////////////////////////////////////////////////

	SelectObject (hDC, penold);

	DeleteObject(boxPen);
	DeleteObject(gridPen);
//	DeleteObject(linePen);
//	DeleteObject(interpPen);



	//====== ¬осстанавливаем инструменты GDI
	//RestoreDC(hDC, nDC);
}

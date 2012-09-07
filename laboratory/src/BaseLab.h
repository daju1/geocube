#pragma once

#include "LabPlotData.h"


class BaseObject
{
	vector<LONG> vSx;
	vector<LONG> vSy;
public:
	void Paint(
		vector<LabData> & labdata,
		HWND hWnd, HDC hdc, 
		RECT margin, 
		SIZE & text_size,
		bool text_size_do_not_determined);

	void Paint(
		vector<fmtstr> & text,
		HWND hWnd, HDC hdc, 
		RECT margin, 
		SIZE & text_size,
		bool text_size_do_not_determined);

	static bool paint_as_tab;

	virtual void SetSizeAndPosOfContextWindow(HWND hWnd, int CX, int CY) = 0;
	
	void PropSaveEmf(bool context_with_plot, char * fn_emf);

	virtual void PrintfProperties(vector<fmtstr> & text) = 0;
	virtual void PrintfProperties(vector<LabData> & labdata) = 0;


};

class BaseLab : public BaseObject
{

public:
	
	static LOGFONT lf_Label;        // logical font structure
	static void InitFont();

	virtual void PropSave(bool context_with_plot) = 0;
	virtual void Passport() = 0;

	virtual void Properties() = 0;

	enum language
	{
		russian = 1,
		ukrainian
	};

	static language PassportLanguage; 


};
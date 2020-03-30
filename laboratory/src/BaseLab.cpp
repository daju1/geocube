#include "baselab.h"

LOGFONT BaseLab::lf_Label;        // logical font structure
void BaseLab::InitFont()
{
	lf_Label.lfHeight				= 16; // height of font
	lf_Label.lfWidth				= 0;  // average character width
	lf_Label.lfEscapement			= 0;  // angle of escapement
	lf_Label.lfOrientation			= 0;  // base-line orientation angle
	lf_Label.lfWeight				= 200;// font weight 
	lf_Label.lfItalic				= 0;  // italic attribute option
	lf_Label.lfUnderline			= 0;  // underline attribute option
	lf_Label.lfStrikeOut			= 0;  // strikeout attribute option
//	lf_Label.lfCharSet				= DEFAULT_CHARSET;		// character set identifier
	lf_Label.lfCharSet				= RUSSIAN_CHARSET;		// character set identifier
	
	lf_Label.lfOutPrecision			= OUT_RASTER_PRECIS;	// output precision
	lf_Label.lfClipPrecision		= CLIP_DEFAULT_PRECIS;	// clipping precision 
	lf_Label.lfQuality				= DEFAULT_QUALITY;		// output quality
	lf_Label.lfPitchAndFamily		= FF_DONTCARE;			// pitch and family
	strcpy(lf_Label.lfFaceName,		"Times New Roman");				// typeface name
}
bool BaseObject::paint_as_tab = true;
void BaseObject::Paint(
		vector<fmtstr> & text,
		HWND hWnd, HDC hdc, 
		RECT margin, 
		SIZE & text_size,
		bool text_size_do_not_determined)
{
	if (BaseObject::paint_as_tab)
	{
		//SIZE Sz;
		SIZE sz;

		bool nl = true;

		int col = 0, cols = 0;
		int row = 0, rows = 0;
				


		HFONT fontold, fontnew;
		
		long interval_x = 10;
		long interval_y = 1;

		if (text_size_do_not_determined)
		{
			nl = true;
			for (vector<fmtstr>::iterator it = text.begin();
				it != text.end(); it++)
			{	
				if (nl)
				{
					col = 0;
					rows++;
				}
				else
				{
					col++;
				}	

				if ((*it).NewLine())
				{
					nl = true;	
				}
				else
				{
					nl = false;	
				}

				if (cols < col+1)
					cols = col+1;
			}

			vSx.resize(cols);
			vSy.resize(rows);


			for (col = 0; col < cols; col++)
			{
				vSx[col] = 0;
			}			
			for (row = 0; row < rows; row++)
			{
				vSy[row] = 0;
			}

			col = 0;
			row = -1;
			nl = true;

			long non_tab_cx = 0;
			long Szcx;

			for (vector<fmtstr>::iterator it = text.begin();
				it != text.end(); it++)
			{				
				fontnew = ::CreateFontIndirect((*it).GetFont());
				fontold = (HFONT__ *)SelectObject(hdc,fontnew);
				
				if (!GetTextExtentPoint32(hdc,           // handle to DC
					(*it).String().c_str(),  // text string
					strlen((*it).String().c_str()),      // characters in string
					&sz      // string size
					))
				{
				}
				SelectObject (hdc,fontold);
				DeleteObject (fontnew);

				if (nl)
				{
					col = 0;
					row++;
				}
				else
				{
					col++;
				}	

				if (vSy[row] < sz.cy)
					vSy[row] = sz.cy;

				if ((*it).AsTab())
				{
					if (vSx[col] < sz.cx)
						vSx[col] = sz.cx;
				}
				else
				{
					if (nl)
					{
						Szcx = sz.cx + interval_x;
					}
					else
					{
						Szcx += sz.cx + interval_x;
					}	

					if ((*it).NewLine())
					{
						if (Szcx > non_tab_cx) non_tab_cx = Szcx;
					}
				}

				if ((*it).NewLine())
				{
					nl = true;
				}
				else
				{
					nl = false;
				}
			}

			text_size.cx = 0;
			text_size.cy = 0;

			for (col = 0; col < cols; col++)
			{
				text_size.cx += vSx[col] + interval_x;
			}			
			for (row = 0; row < rows; row++)
			{					
				text_size.cy += vSy[row] + interval_y;
			}

			if (text_size.cx < non_tab_cx)
				text_size.cx = non_tab_cx;

			text_size.cx += margin.left + margin.right;
			text_size.cy += margin.top + margin.bottom;

			text_size_do_not_determined = false;


			if (hWnd) this->SetSizeAndPosOfContextWindow(hWnd, text_size.cx+3, text_size.cy);
		}


		//if(hdc)
		{
			col = 0;
			row = -1;
			nl = true;

			int x = margin.left, y = margin.top;
			for (vector<fmtstr>::iterator it = text.begin();
				it != text.end(); it++)
			{	
				fontnew = ::CreateFontIndirect((*it).GetFont());
				fontold = (HFONT__ *)SelectObject(hdc,fontnew);

				if (!GetTextExtentPoint32(hdc,           // handle to DC
					(*it).String().c_str(),  // text string
					strlen((*it).String().c_str()),      // characters in string
					&sz      // string size
					))
				{
				}
				
				SetTextColor(hdc, (*it).GetColor());

				TextOut(hdc, 
					x,
					y, 
					(*it).String().c_str(), 
					strlen((*it).String().c_str())
					);
	            
				SetTextColor(hdc, 0);

				SelectObject (hdc,fontold);
				DeleteObject (fontnew);



				if (nl)
				{
					col = 0;
					row++;
				}
				else
				{
					col++;
				}	


				if ((*it).NewLine())
				{
					y += vSy[row] + interval_y;
					x = margin.left;
					nl = true;
				}
				else
				{
					if ((*it).AsTab())
						x += vSx[col] + interval_x;
					else
						x += sz.cx + interval_x;;
					nl = false;
				}	


			}		
		}
	}
	else
	{
		SIZE Sz;
		SIZE sz;

		bool nl = true;

		HFONT fontold, fontnew;
		
		long interval = 1;

		if (text_size_do_not_determined)
		{
			for (vector<fmtstr>::iterator it = text.begin();
				it != text.end(); it++)
			{				
				fontnew = ::CreateFontIndirect((*it).GetFont());
				fontold = (HFONT__ *)SelectObject(hdc,fontnew);
				
				if (!GetTextExtentPoint32(hdc,           // handle to DC
					(*it).String().c_str(),  // text string
					strlen((*it).String().c_str()),      // characters in string
					&sz      // string size
					))
				{
				}
				SelectObject (hdc,fontold);
				DeleteObject (fontnew);

				if (nl)
				{
					Sz = sz;
				}
				else
				{
					Sz.cx += sz.cx;
					if (Sz.cy < sz.cy)
						Sz.cy = sz.cy;
				}	

				if ((*it).NewLine())
				{
					if (Sz.cx > text_size.cx) text_size.cx = Sz.cx;
					text_size.cy += Sz.cy + interval;
					nl = true;	
				}
				else
				{
					nl = false;
				}
			}
			text_size_do_not_determined = false;

			text_size.cx += margin.left + margin.right;
			text_size.cy += margin.top + margin.bottom;

			if (hWnd) this->SetSizeAndPosOfContextWindow(hWnd, text_size.cx+3, text_size.cy);
		}


		//if(hdc)
		{
			nl = true;
			int x = margin.left, y = margin.top;
			for (vector<fmtstr>::iterator it = text.begin();
				it != text.end(); it++)
			{	
				fontnew = ::CreateFontIndirect((*it).GetFont());
				fontold = (HFONT__ *)SelectObject(hdc,fontnew);

				if (!GetTextExtentPoint32(hdc,           // handle to DC
					(*it).String().c_str(),  // text string
					strlen((*it).String().c_str()),      // characters in string
					&sz      // string size
					))
				{
				}
				
				SetTextColor(hdc, (*it).GetColor());

				TextOut(hdc, 
					x,
					y, 
					(*it).String().c_str(), 
					strlen((*it).String().c_str())
					);
	            
				SetTextColor(hdc, 0);

				SelectObject (hdc,fontold);
				DeleteObject (fontnew);

				if (nl)
				{
					Sz = sz;
				}
				else
				{
					Sz.cx += sz.cx;
					if (Sz.cy < sz.cy)
						Sz.cy = sz.cy;
				}

				if ((*it).NewLine())
				{
					y += Sz.cy + interval;
					x = margin.left;
					nl = true;
				}
				else
				{
					x += sz.cx;
					nl = false;
				}	

			}		
		}
	}
}

void BaseObject::Paint(
		vector<LabData> & labdata,
		HWND hWnd, HDC hdc, 
		RECT margin, 
		SIZE & text_size,
		bool text_size_do_not_determined)
{
	if (BaseObject::paint_as_tab)
	{
		//SIZE Sz;
		SIZE sz;

		bool nl = true;

		int col = 0, cols = 0;
		int row = 0, rows = 0;
				


		HFONT fontold, fontnew;
		
		long interval_x = 10;
		long interval_y = 1;

		if (text_size_do_not_determined)
		{
			nl = true;
			for (vector<LabData>::iterator it_ld = labdata.begin();
				it_ld != labdata.end(); it_ld++)
			{
				for (vector<fmtstr>::iterator it = (*it_ld).text.begin();
					it != (*it_ld).text.end(); it++)
				{	
				if (nl)
				{
					col = 0;
					rows++;
				}
				else
				{
					col++;
				}	

				if ((*it).NewLine())
				{
					nl = true;	
				}
				else
				{
					nl = false;	
				}

				if (cols < col+1)
					cols = col+1;
				}

			}

			vSx.resize(cols);
			vSy.resize(rows);


			for (col = 0; col < cols; col++)
			{
				vSx[col] = 0;
			}			
			for (row = 0; row < rows; row++)
			{
				vSy[row] = 0;
			}

			col = 0;
			row = -1;
			nl = true;

			long non_tab_cx = 0;
			long Szcx;

			text_size.cx = 0;
			text_size.cy = 0;

			for (vector<LabData>::iterator it_ld = labdata.begin();
				it_ld != labdata.end(); it_ld++)
			{
				for (vector<fmtstr>::iterator it = (*it_ld).text.begin();
					it != (*it_ld).text.end(); it++)
				{				
					fontnew = ::CreateFontIndirect((*it).GetFont());
					fontold = (HFONT__ *)SelectObject(hdc,fontnew);
					
					if (!GetTextExtentPoint32(hdc,           // handle to DC
						(*it).String().c_str(),  // text string
						strlen((*it).String().c_str()),      // characters in string
						&sz      // string size
						))
					{
					}
					SelectObject (hdc,fontold);
					DeleteObject (fontnew);

					if (nl)
					{
						col = 0;
						row++;
					}
					else
					{
						col++;
					}	

					if (vSy[row] < sz.cy)
						vSy[row] = sz.cy;

					if ((*it).AsTab())
					{
						if (vSx[col] < sz.cx)
							vSx[col] = sz.cx;
					}
					else
					{
						if (nl)
						{
							Szcx = sz.cx + interval_x;
						}
						else
						{
							Szcx += sz.cx + interval_x;
						}	

						if ((*it).NewLine())
						{
							if (Szcx > non_tab_cx) non_tab_cx = Szcx;
						}
					}

					if ((*it).NewLine())
					{
						nl = true;
					}
					else
					{
						nl = false;
					}
				}

				if ((*it_ld).plot_data.use_plot)
				{
					(*it_ld).plot_data.SetCenterAndScale();
					text_size.cy += (*it_ld).plot_data.plot_height + interval_y; 
				}
			}
				

			for (col = 0; col < cols; col++)
			{
				text_size.cx += vSx[col] + interval_x;
			}			
			for (row = 0; row < rows; row++)
			{					
				text_size.cy += vSy[row] + interval_y;
			}

			if (text_size.cx < non_tab_cx)
				text_size.cx = non_tab_cx;

			text_size.cx += margin.left + margin.right;
			text_size.cy += margin.top + margin.bottom;

			text_size_do_not_determined = false;


			if (hWnd) this->SetSizeAndPosOfContextWindow(hWnd, text_size.cx+3, text_size.cy);
		}


		//if(hdc)
		{
			col = 0;
			row = -1;
			nl = true;

			int x = margin.left, y = margin.top;

			for (vector<LabData>::iterator it_ld = labdata.begin();
				it_ld != labdata.end(); it_ld++)
			{
				for (vector<fmtstr>::iterator it = (*it_ld).text.begin();
					it != (*it_ld).text.end(); it++)
				{	
					fontnew = ::CreateFontIndirect((*it).GetFont());
					fontold = (HFONT__ *)SelectObject(hdc,fontnew);

					if (!GetTextExtentPoint32(hdc,           // handle to DC
						(*it).String().c_str(),  // text string
						strlen((*it).String().c_str()),      // characters in string
						&sz      // string size
						))
					{
					}
					
					SetTextColor(hdc, (*it).GetColor());

					TextOut(hdc, 
						x,
						y, 
						(*it).String().c_str(), 
						strlen((*it).String().c_str())
						);
		            
					SetTextColor(hdc, 0);

					SelectObject (hdc,fontold);
					DeleteObject (fontnew);



					if (nl)
					{
						col = 0;
						row++;
					}
					else
					{
						col++;
					}	


					if ((*it).NewLine())
					{
						y += vSy[row] + interval_y;
						x = margin.left;
						nl = true;
					}
					else
					{
						if ((*it).AsTab())
							x += vSx[col] + interval_x;
						else
							x += sz.cx + interval_x;;
						nl = false;
					}	
				}

				if ((*it_ld).plot_data.use_plot)
				{
					tagRECT r;
					r.left = margin.left;
					r.right = text_size.cx+3 - margin.left - margin.right;
					r.top = y;
					r.bottom = y + (*it_ld).plot_data.plot_height;

					(*it_ld).plot_data.Draw(hdc, r, margin);

					y += (*it_ld).plot_data.plot_height + interval_y; 
				}
			}		
		}
	}
	else
	{
		SIZE Sz;
		SIZE sz;
		bool nl = true;
		HFONT fontold, fontnew;
		
		long interval = 1;

		if (text_size_do_not_determined)
		{
			for (vector<LabData>::iterator it_ld = labdata.begin();
				it_ld != labdata.end(); it_ld++)
			{
				for (vector<fmtstr>::iterator it = (*it_ld).text.begin();
					it != (*it_ld).text.end(); it++)
				{				
					fontnew = ::CreateFontIndirect((*it).GetFont());
					fontold = (HFONT__ *)SelectObject(hdc,fontnew);
					if (!GetTextExtentPoint32(hdc,           // handle to DC
						(*it).String().c_str(),  // text string
						strlen((*it).String().c_str()),      // characters in string
						&sz      // string size
						))
					{
					}
					SelectObject (hdc,fontold);
					DeleteObject (fontnew);

					if (nl)
					{
						Sz = sz;
					}
					else
					{
						Sz.cx += sz.cx;
						if (Sz.cy < sz.cy)
							Sz.cy = sz.cy;
					}	

					if ((*it).NewLine())
					{
						if (Sz.cx > text_size.cx) text_size.cx = Sz.cx;
						text_size.cy += Sz.cy + interval;
						nl = true;
					}
					else
					{
						nl = false;
					}
				}
				if ((*it_ld).plot_data.use_plot)
				{
					(*it_ld).plot_data.SetCenterAndScale();
					text_size.cy += (*it_ld).plot_data.plot_height + interval; 
				}
			}
			text_size_do_not_determined = false;

			text_size.cx += margin.left + margin.right;
			text_size.cy += margin.top + margin.bottom;

			if (hWnd) this->SetSizeAndPosOfContextWindow(hWnd, text_size.cx+3, text_size.cy);


		}

		//if(hdc)
		{
			nl = true;
			int x = margin.left, y = margin.top;

			for (vector<LabData>::iterator it_ld = labdata.begin();
				it_ld != labdata.end(); it_ld++)
			{
				for (vector<fmtstr>::iterator it = (*it_ld).text.begin();
					it != (*it_ld).text.end(); it++)
				{
					fontnew = ::CreateFontIndirect((*it).GetFont());
					fontold = (HFONT__ *)SelectObject(hdc,fontnew);
					if (!GetTextExtentPoint32(hdc,           // handle to DC
						(*it).String().c_str(),  // text string
						strlen((*it).String().c_str()),      // characters in string
						&sz      // string size
						))
					{
					}

					SetTextColor(hdc, (*it).GetColor());

					TextOut(hdc, 
						x,
						y, 
						(*it).String().c_str(), 
						strlen((*it).String().c_str())
						);

					SetTextColor(hdc, 0);

					SelectObject (hdc,fontold);
					DeleteObject (fontnew);

					if (nl)
					{
						Sz = sz;
					}
					else
					{
						Sz.cx += sz.cx;
						if (Sz.cy < sz.cy)
							Sz.cy = sz.cy;
					}

					if ((*it).NewLine())
					{
						y += Sz.cy + interval;
						x = margin.left;
						nl = true;
					}
					else
					{
						x += sz.cx;
						nl = false;
					}
				}
				if ((*it_ld).plot_data.use_plot)
				{
					tagRECT r;
					r.left = margin.left;
					r.right = text_size.cx+3 - margin.left - margin.right;
					r.top = y;
					r.bottom = y + (*it_ld).plot_data.plot_height;

					(*it_ld).plot_data.Draw(hdc, r, margin);

					y += (*it_ld).plot_data.plot_height + interval; 
				}
			}
			
			SelectObject (hdc,fontold);
			DeleteObject (fontnew);
		}
	}
}





//void ErrorExit(LPTSTR lpszFunction, bool toExitProcess);
#include "../../tools/src/errorexit.h"

void BaseObject::PropSaveEmf(bool context_with_plot, char * fn_emf)
{
	static RECT margin; 
	//##################################################
	margin.left = 10;
	margin.right = 10;
	margin.top = 10;
	margin.bottom = 10;
	//##################################################

	HDC hDC;

	PRINTDLG pd;
	
	// Initialize PRINTDLG
	ZeroMemory(&pd, sizeof(pd));
	pd.lStructSize = sizeof(pd);
	pd.hwndOwner   = NULL;
	pd.hDevMode    = NULL;     // Don't forget to free or store hDevMode
	pd.hDevNames   = NULL;     // Don't forget to free or store hDevNames

	pd.Flags       = 
		PD_RETURNDEFAULT
	; 
	
	if (PrintDlg(&pd)!=TRUE) 
	{
		// GDI calls to render output.
		// что нибудб печатаем... 
		// BeginPrinting(hwnd, &pd);
		return;
	}	

//	DOCINFO di;
	
	if(!pd.hDevNames)
	{
		MessageBox(0,"!psd->hDevNames","BeginPrinting", 0);
		return ;
	}

	if(!pd.hDevMode)
	{
		MessageBox(0,"!psd->hDevMode","BeginPrinting", 0);
		return ;
	}

	// Получаем указатели на две структуры с установками.
	DEVNAMES FAR *lpDevNames =
		(DEVNAMES FAR *)::GlobalLock(pd.hDevNames);
	
	DEVMODE FAR *lpDevMode =
		(DEVMODE FAR *)::GlobalLock(pd.hDevMode);

	
	LPSTR szPrinterName = (LPTSTR)lpDevNames +
		lpDevNames->wDeviceOffset;
	
	LPSTR szDriverName = (LPTSTR)lpDevNames +
		lpDevNames->wDriverOffset;

	LPSTR szOutputPortName = (LPTSTR)lpDevNames +
		lpDevNames->wOutputOffset;

	// Создать контекст устройства для принтера, 
	// на котором должна быть выполнена печать.
	//........................................
	hDC = CreateDC( 
		szDriverName,//"WINSPOOL", 
		szPrinterName,
		szOutputPortName, 
		lpDevMode			//pDevModeUser 
		);	

	int  iWidthMM, iHeightMM, iWidthPels, iHeightPels;
	double  iMMPerPelX, iMMPerPelY;

	// Вычислить размер клиентской области в единицах 
	// длины 0,01 мм.
	//................................................
	iWidthMM    = GetDeviceCaps(hDC, HORZSIZE);
	iHeightMM   = GetDeviceCaps(hDC, VERTSIZE);
	iWidthPels  = GetDeviceCaps(hDC, HORZRES);
	iHeightPels = GetDeviceCaps(hDC, VERTRES);


	iMMPerPelX = double(iWidthMM * 100)/iWidthPels;
	iMMPerPelY = double(iHeightMM * 100)/iHeightPels;

	vector<LabData> labdata;
	vector<fmtstr> text;
	switch (context_with_plot)
	{
	case false:
		this->PrintfProperties(text);
		break;
	case true:
		this->PrintfProperties(labdata);
		break;
	}

	SIZE text_size;
	text_size.cx = 0;
	text_size.cy = 0;
	
	switch (context_with_plot)
	{
	case false:
		this->Paint(text, NULL, hDC, margin, text_size, true);
		break;
	case true:
		this->Paint(labdata, NULL, hDC, margin, text_size, true);
		break;
	}

	RECT rect;
	rect.left = 0;
	rect.top = 0;
	rect.right = LONG((text_size.cx+3) * iMMPerPelX);
	rect.bottom = LONG(text_size.cy * iMMPerPelY);

	// Создать расширенный метафайл.
	//.............................
	HENHMETAFILE hMetaFile = NULL;
	HDC  hMetaDC;
	hMetaDC = CreateEnhMetaFile( hDC, fn_emf, &rect,  "Sparse Matrix Structure" );
	if ( hMetaDC )
	{		
		switch (context_with_plot)
		{
		case false:
			this->Paint(text, NULL, hMetaDC, margin, text_size, false);
			break;
		case true:
			this->Paint(labdata, NULL, hMetaDC, margin, text_size, false);
			break;
		}
		hMetaFile = CloseEnhMetaFile( hMetaDC );
	}
	else
		ErrorExit("CreateEnhMetaFile",false);
	
	if(hMetaFile)
		DeleteEnhMetaFile(hMetaFile);
}



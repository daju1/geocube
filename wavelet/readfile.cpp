#include "StdAfx.h"
#include "readfile.h"
//#include "../datenum.h"

int ReadInputFile(char * fname, vdouble& x, vdouble& y)
{
	FILE * stream;
	const unsigned int n = 1023;
	char szBuff[n];

	// open the file
	if ((stream = fopen(fname,"rt")) == NULL)
	{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	int i = 0;
	double X,Y;
	while (!feof(stream))
	{
		char * ch;
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			int rez = sscanf(szBuff,"%lf\t%lf",
							&X, &Y);
			if (rez == 2 && rez != EOF)
			{
				i++;
			}
			else
			{
				rez = sscanf(szBuff,"%lf,%lf",
								&X, &Y);
				if (rez == 2 && rez != EOF)
				{
					i++;
				}
				else
				{
					rez = sscanf(szBuff,"%lf;%lf",
									&X, &Y);
					if (rez == 2 && rez != EOF)
					{
						i++;
					}
				}
			}

		}
	}
	fclose(stream);
	int len = i;
	x.resize(len);
	y.resize(len);
	if ((stream = fopen(fname,"rt")) == NULL)
	{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}
	i = 0;
	while (!feof(stream))
	{
		char * ch;
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			int rez = sscanf(szBuff,"%lf\t%lf",
							&X, &Y);
			if (rez == 2 && rez != EOF)
			{
				x[i] = X;
				y[i] = Y;
				i++;
			}
			else
			{
				rez = sscanf(szBuff,"%lf,%lf",
								&X, &Y);
				if (rez == 2 && rez != EOF)
				{
					x[i] = X;
					y[i] = Y;
					i++;
				}
				else
				{
					rez = sscanf(szBuff,"%lf;%lf",
						&X, &Y);
					if (rez == 2 && rez != EOF)
					{
						x[i] = X;
						y[i] = Y;
						i++;
					}
				}
			}

		}
	}
	fclose(stream);
	return 0;
}

int GetDelimiterFromID(int delimID)
{		
	int delim;
	switch(delimID)
	{
	case 0:
		delim = '\t';
		break;
	case 1:
		delim = ' ';
		break;
	case 2:
		delim = ',';
		break;
	case 3:
		delim = ';';
		break;
	}
	return delim;
}

int ReadInputFile(char * fname, Vector<vdouble>& vv, int delim)
{
	FILE * stream;
	const int n=16384; // length of buffer string line
	char* szBuff; // buffer string line

	if ((szBuff = (char *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n*sizeof(char))) == NULL)
	{
		MessageBox(0, "vX - Not enough memory",
			"importExcelCommonFileParam()", 0);
		return 0;
	}

	char * ch;
	char *p1, *p2;
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed



	double 
		value;

	bool bUse_Header = true;


	printf("opening the input file %s\n", fname);

	// open the file
	if ((stream = fopen(fname,"rt")) == NULL)
	{
		MessageBox(0, "Cannot open input file.\n", "Import", 
			MB_OK | MB_ICONINFORMATION);
		return -1;
	}

	// Gets the file descriptor associated with a stream.
	int fd = _fileno(stream);
	// Get the length of a file in bytes
	cb = _filelength(fd);

		char title[512];
		int nParams = 0, bytes_line, bytes_param;
		// if first line is line of headers
		if (bUse_Header && !feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);

				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
					{
						printf("|"); fflush(stdout);
					}
				}

				p1 = szBuff;
				while ((p2 = strchr(p1,delim)) != NULL)
				{
					strncpy(title, p1, p2-p1);
					title[p2-p1] = '\0';
					//MessageBox(0, p2, title, 0);
					p1 = p2+1;
					nParams++;
				}
				if (p1-szBuff < bytes_line)
				{
					strcpy(title, p1);
					//MessageBox(0, title," p1-szBuff < bytes " , 0);
					nParams++;
				}
			}
		}

		// scan all lines to know length of file
		int len = 0;
		while (!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
					{
						printf("|"); fflush(stdout);
					}
				}
				p1 = szBuff;
				len++;
			}
		}
printf("len = %d nParams = %d\n", len, nParams);fflush(stdout);

		fclose(stream);

		vv.resize(nParams);
		for (int col = 0; col < nParams; col++)
			vv[col].resize(len);
//		vt.resize(len);

/*		char errstr[255];
		sprintf(errstr,"len = %d nParams = %d bytes_line = %d", len, nParams, bytes_line);
		MessageBox(0,errstr,"import()",0);
*/
		if( len == 0)
		{
			MessageBox(0,"Файл не содержит информации надлежащего формата", "Import",0);
			return 0;
		}


		// open the file again
		if ((stream = fopen(fname,"rt")) == NULL)
		{
			MessageBox(0, "Cannot open input file.\n", "Import", 
				MB_OK | MB_ICONINFORMATION);
			return 0;
		}
				

		// read the first line and define memory and titles for plots
		if (!feof(stream))
		{
			ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				//MessageBox(0, szBuff, "", 0);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						printf("|"); 
				}
				p1 = szBuff;

				int ncol = 0;

				//int iParam = 0;
				while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff < bytes_line )
				{
					ncol++;
					if ((p2 = strchr(p1,delim)) != NULL)
					{
						bytes_param = p2-p1+1;
					}
					else
					{
						bytes_param = strlen(p1);
					}
					strncpy(title, p1, bytes_param);
					title[bytes_param-1] = '\0';
					//MessageBox(0, p2, title, 0);

					if ((p2 = strchr(p1,delim)) != NULL)
					{
						p1 = p2+1;
					}
					else
						p1 = szBuff + bytes_line;
				}
			}
		}

		// read all lines and remember data in plot vectors
		int i = 0;
		while (!feof(stream))
		{
			if ((i == 0 && bUse_Header) || i > 0)
				ch = fgets(szBuff,n,stream);
			if( ch != NULL && strlen(szBuff) > 1)
			{
				bytes_line = strlen(ch);
				// calculate progress
				cb_read += bytes_line;
				if (cb_read - cb_disp > 2048) 
				{
				   // Advance the current position of the
				   // progress bar by the increment. 
					int todisp = (cb_read - cb_disp) / 2048;
					cb_disp += todisp*2048;
					for (int idisp = 0; idisp < todisp; idisp++)
						printf("|"); 
				}
				p1 = szBuff;

				if (true)
				{
					int ncol = 0;


					while ((p2 = strchr(p1,delim)) != NULL || p1-szBuff < bytes_line)
					{
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							bytes_param = p2-p1+1;
						}
						else
						{
							bytes_param = strlen(p1);
						}
						strncpy(title, p1, bytes_param);
						title[bytes_param-1] = '\0';

						if (true/*bUseAllCols || ncol <= nMaxCols*/)
						{
							//MessageBox(0, p1, title, 0);
							value = atof(title);
							if (value == 0.0)
								value = double(atoi(title));

							vv[ncol][i] = value;
						}
						if ((p2 = strchr(p1,delim)) != NULL)
						{
							p1 = p2+1;
						}
						else
							p1 = szBuff + bytes_line;
						ncol++;
					}
					i++;
				}
			}
		}
		fclose(stream);
		printf("\nthe input file was read\n");
	if(szBuff)
		HeapFree(GetProcessHeap(), 0,szBuff);
	return 0;
}

// anomklass.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "./../tools/src/readfile.h"
#include "./../tools/src/filedlg.h"
#include "./../array/src/sorting.h"

#include "./../kohonen/src/KohonenDlg.h"


extern char szPath[];
extern char directory[];
HINSTANCE hInst;

int _tmain(int argc, _TCHAR* argv[])
{
	size_t min_len = 7;
	bool bScale = true;
	int n_int_points = 50;
	// Загружаем файл результатов вычисления аномалий
	if (OpenFileDlg(NULL, 
		"Data Result (*.dat)\0*.dat\0"
		"All files Result\0*.*\0") == S_OK)
	{
		printf("reading of result file\n%s\n", szPath);
		//##############################################################
		//блок чтения файла
		vector<vector<cell> > * pcells_result = new vector<vector<cell> >;
		vector<string> * pnames_of_colomns_result = new vector<string>;

		int delim = ',';

		char* filename_result = new char[256];
		ReadCellFile(NULL, szPath, NULL, filename_result, pcells_result, pnames_of_colomns_result, delim );
		//блок чтения файла
		//##############################################################
		int rows_result = pcells_result->size();
		int cols_result = pnames_of_colomns_result->size();

printf("rows_result = %d\n", rows_result);
printf("cols_result = %d\n", cols_result);

		for (size_t c = 0; c < cols_result; c++)
			printf("col_result[%d] = %s\n", c, (*pnames_of_colomns_result).operator [](c).c_str());
		
		

		
		// Загружаем файл исходных сигналов
		if (OpenFileDlg(NULL, 
			"CSV Sources (*.csv)\0*.csv\0"
			"Data Sources (*.dat)\0*.dat\0"
			"All files Sources \0*.*\0") == S_OK)
		{
			printf("reading of sources file\n%s\n", szPath);
			//##############################################################
			//блок чтения файла
			vector<vector<cell> > * pcells_sources = new vector<vector<cell> >;
			vector<string> * pnames_of_colomns_sources = new vector<string>;

			int delim = ',';

			char* filename_sources = new char[256];
			ReadCellFile(NULL, szPath, NULL, filename_sources, pcells_sources, pnames_of_colomns_sources, delim );
			//блок чтения файла
			//##############################################################
			int rows_sources = pcells_sources->size();
			int cols_sources = pnames_of_colomns_sources->size();

	printf("rows_sources = %d\n", rows_sources);
	printf("cols_sources = %d\n", cols_sources);

			for (size_t c = 0; c < cols_sources; c++)
				printf("col_sources[%d] = %s\n", c, (*pnames_of_colomns_sources).operator [](c).c_str());
		
			int n_examples = 0;// = rows_result ;//+1
			for ( int r = 0; r < rows_result; r++)
			{
				size_t   j1 = (size_t) (*pcells_result).operator [](r).operator [](6).value;
				size_t   j2 = (size_t) (*pcells_result).operator [](r).operator [](7).value;
				
				size_t j_1 = min(j1,j2);
				size_t j_2 = max(j1,j2);
				size_t len = j_2 - j_1;

				if(len >= min_len)
				{
					n_examples++;
				}
			}

			double **M = AllocDoubleMat(n_examples, n_int_points);
			double * vX = new double [n_examples];
			double * vY = new double [n_examples];
			double * vZ = new double [n_examples];

			int i_example = 0;

			for ( int r = 0; r < rows_result; r++)
			{
				//printf("i_example = %d\n", i_example);
				// выделяем память под интерполяцию
				//###################################################################
				double X = (*pcells_result).operator [](r).operator [](0).value;
				double Y = (*pcells_result).operator [](r).operator [](1).value;
				double Z = (*pcells_result).operator [](r).operator [](2).value;

				size_t icol = (size_t) (*pcells_result).operator [](r).operator [](5).value;
				size_t   j1 = (size_t) (*pcells_result).operator [](r).operator [](6).value;
				size_t   j2 = (size_t) (*pcells_result).operator [](r).operator [](7).value;
				
				//size_t level = (size_t) (*pcells_result).operator [](r).operator [](8).value;
				size_t j_1 = min(j1,j2);
				size_t j_2 = max(j1,j2);
				size_t len = j_2 - j_1;

				if(len >= min_len)
				{
					double * v = new double [len];

					for (size_t i = 0, j = j_1; j < j_2; j++, i++)
					{
						v[i] = (*pcells_sources)[j][icol].value;
					}
					//linterp(int nx, double* py, int nxx, double* pyy)
					linterp(len, v, n_int_points, M[i_example]);
					if (bScale) Scale(n_int_points, M[i_example]);

					vX[i_example] = X;
					vY[i_example] = Y;
					vZ[i_example] = Z;

					i_example++;

					delete [] v;
				}
			}
			static KohonenDlg * khd = new KohonenDlg(n_examples, vX, vY, vZ, n_int_points, M, filename_sources, true);		// ...right after the dialog is closed?
			FreeDoubleMat(M);
			delete [] filename_sources;
			delete [] vX;
			delete [] vY;
			delete [] vZ;
			//if (khd != NULL) delete khd;
		}

		delete [] filename_result;
	}
	return 0;
}


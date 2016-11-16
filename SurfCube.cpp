// SurfCube.cpp : Defines the entry point for the application.
//
#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afx.h>
#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <iostream>

#define TRACE              printf



#include "stdafx.h"
#include ".\wintools\src\winsurf.h"
#include "mylicense.h"

HINSTANCE hInst;								// current instance

#define TEST_SLAU 0
#if TEST_SLAU
#include "array/src/slau.h"
#endif

	
void test_min_sq_holesski();


#define TEST 0
#if TEST
#include "./array/src/matrixes.h"

//#include "blnProfile3d.h"
//#include ".\collection.h"
//#include "vect.h"
#include "surfdoc/src/archive.h"
#define BUFF_SIZE 5
#endif
#if 1

#include "logger/CrashDumper.h"
#include "logger/Logger.h"
#include "logger/ThreadName.h"
#include "logger/DispatcherFile.h"
#include "logger/DispatcherConsole.h"
#include "../../lab/lab/SysLogManager.h"

//#include "SvnRevision.h"
#define SVN_REVISION_LAST 35
#define SVN_REVISION_LAST_STR "1.0.0.35 modified"
#define SVN_REVISION_LOCAL_MODIFICATION 1

void run_log()
{
   INFO("SurfCube Running");
}

void init_logger()
{
   // Инициализация имени главного потока
   Logger::ThreadName  thread_name("Main");

   // Инициализация менеджера папок и имен файлов
   sys::LogManager::instance();

   // Установка краш-дамппера
   Logger::CrashDumper crash_dumper(Logger::MINI_DUMP_FULL, SVN_REVISION_LAST, SVN_REVISION_LOCAL_MODIFICATION);

   // Начальная инициализация логера
   using namespace Logger;
   Journal::instance().register_dispatcher(DispatcherPtr( new DispatcherFile( sys::LogManager::instance().get_log_file_name().string())));

   //if (TRUE != m_bService)
      Journal::instance().register_dispatcher(DispatcherPtr( new DispatcherConsole()));

   Journal::instance().set_log_level(Logger::LL_INFO);
   Journal::instance().start();

   do
   {
      //ConfigManager::instance().init(sys::LogManager::instance().get_root_directory() / "config\\dbproxy.ini");
      //unsigned int log_level = ConfigManager::instance().get_value_int("Debug", "LogLevel", Logger::LL_INFO);

      // Переинициализация логгера
      //Journal::instance().set_log_level((Logger::LogLevel)log_level);

   } while (0);

   run_log();
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])
{
	init_logger();

	int nRetCode = 0;

	// initialize MFC and print and error on failure
	if (!AfxWinInit(::GetModuleHandle(NULL), NULL, ::GetCommandLine(), 0))
	{
		// TODO: change error code to suit your needs
		cerr << _T("Fatal Error: MFC initialization failed") << endl;
		nRetCode = 1;
	}
	else
	{
		// Initialize OLE libraries
		if (!AfxOleInit())
		{
//			AfxMessageBox(IDP_OLE_INIT_FAILED);
			return FALSE;
		}

		COleTemplateServer::RegisterAll();
		COleObjectFactory::UpdateRegistryAll();
		CoInitialize(NULL);

		// TODO: code your application's behavior here.
//		CString strHello;
//		strHello.LoadString(IDS_HELLO);
//		cout << (LPCTSTR)strHello << endl;

		hInst = AfxGetInstanceHandle();

	//	OnSomeAction();
		WinSurf();

		//MyDlg * dlg = new MyDlg(true);

		CoUninitialize();

	}

	return nRetCode;
}
#else
#ifdef _CONSOLE
int __cdecl main()
{
		test_min_sq_holesski();
		return 0;

	/*
void GetAlpha3(double fi, double h_per_d, double & alpha3);
	double fi;
	double h_per_d;
	double alpha3;
	bool go = true;
	while (go)
	{
		cout << "fi" << endl;
		cin >> fi;
		cout << "h_per_d" << endl;
		cin >> h_per_d;
		GetAlpha3(fi, h_per_d, alpha3);
		cout << "alpha3 = " << alpha3 << endl << endl;
	}*/
	/*
void GetAlpha4(double fi, double d, double & alpha4);
	double fi;
	double d;
	double alpha4;
	bool go = true;
	while (go)
	{
		cout << "fi" << endl;
		cin >> fi;
		cout << "d" << endl;
		cin >> d;
		GetAlpha4(fi, d, alpha4);
		cout << "alpha4 = " << alpha4 << endl << endl;
	}*/
	//if (!CheckMyLicense()){return FALSE;} 
/*
	c = '.';
		printf ("%c ->  %d\n", c, c);

	c = 47;
		printf ("%c ->  %d\n", c, c);
	for ( int c = '0'; c <= '9'; c++)
		printf ("%c ->  %d\n", c, c);
	cout << "isdigit('0') = " << isdigit('0') << endl;;
	cout << "isdigit('1') = " << isdigit('1') << endl;;
	cout << "isdigit('2') = " << isdigit('2') << endl;;
	cout << "isdigit('3') = " << isdigit('3') << endl;;
	cout << "isdigit('4') = " << isdigit('4') << endl;;
	cout << "isdigit('5') = " << isdigit('5') << endl;;
	cout << "isdigit('6') = " << isdigit('6') << endl;;
	cout << "isdigit('7') = " << isdigit('7') << endl;;
	cout << "isdigit('8') = " << isdigit('8') << endl;;
	cout << "isdigit('9') = " << isdigit('9') << endl;;
	cout << "isdigit('.') = " << isdigit('.') << endl;;
	cout << "isdigit(',') = " << isdigit(',') << endl;;
	cout << "isdigit(' ') = " << isdigit(' ') << endl;;
	cout << "isdigit('a') = " << isdigit('a') << endl;;
	cout << "isalpha('0') = " << isalpha('0') << endl;;
	cout << "isalpha('.') = " << isalpha('.') << endl;;
	cout << "isalpha(' ') = " << isalpha(' ') << endl;;
	cout << "isdigit('ф') = " << isdigit('ф') << endl;;
	cout << "isalpha('ф') = " << isalpha('ф') << endl;;
	*/
	hInst = GetModuleHandle(NULL);
#if TEST
	/*
	HWND hWnd = (HWND) 0x001E00A4;
    int X = 0,
    int Y = 0,
    int nWidth = 500,
    int nHeight = 500;
	BOOL bRepaint = 1;
	MoveWindow(hWnd,
    X,
    Y,
    nWidth,
    nHeight,
    bRepaint
);
	return 0;*/
	long Nz = 382;
	long Ny = 45;
	long Nx = 52;
#if 1
printf("1\n");
	long **** Ivert = Alloc4DMat<long> (Nz,Ny,Nx,12);
printf("2\n");

	long nz,ny,nx, i, j = 0;
	for (nx = 0; nx < Nx; nx++)
		for(ny = 0; ny < Ny; ny++)
			for(nz = 0; nz < Nz; nz++)
				for(i = 0; i < 12; i++)
				{
					Ivert[nz][ny][nx][i] = j++;
				}

	for (nx = 0; nx < Nx; nx++)
		for(ny = 0; ny < Ny; ny++)
			for(nz = 0; nz < Nz; nz++)
				for(i = 0; i < 12; i++)
				{
					printf("%d\t", Ivert[nz][ny][nx][i]);
				}

	Free4DMat<long>(Ivert);
#else


	long *** Ivert = Alloc3DMat<long> (Nz,Ny,Nx);

	long nz,ny,nx, i, j = 0;
	for (nx = 0; nx < Nx; nx++)
		for(ny = 0; ny < Ny; ny++)
			for(nz = 0; nz < Nz; nz++)
				{
					Ivert[nz][ny][nx] = j++;
				}

	for (nx = 0; nx < Nx; nx++)
		for(ny = 0; ny < Ny; ny++)
			for(nz = 0; nz < Nz; nz++)
				{
					printf("%d\t", Ivert[nz][ny][nx]);
				}

	Free3DMat<long>(Ivert);
#endif
	return 0;


	char filename[512];
	sprintf(filename, "d://test.dat");
	char buff[BUFF_SIZE];

	double m1[10];
	double m2[10];
	char str1[256];
	char str2[256];
	sprintf(str1, "Test string for file saving\t\yes!!!");
	printf(str1);
	printf("\n");
	for(size_t i = 0; i < sizeof(m1)/sizeof(double); i++)
	{
		m1[i] = double(i);
		printf("m1[%u] = %f\n", i, m1[i]);
	}
	{
		AFile f;
		if( !f.Open( filename, GENERIC_WRITE, TRUNCATE_EXISTING) ) {
			MessageBox(0, "Unable to open file" , filename, MB_OK);
			return 0;
		}
		Archive ar( &f, Archive::store, BUFF_SIZE, buff );

		ar.WriteString(str1);
		ar.Write((unsigned char*)m1,sizeof(m1));
		ar.Close();
		f.Close();
 	}
	{
		AFile f;
		if( !f.Open( filename, GENERIC_READ, OPEN_EXISTING) ) {
			MessageBox(0, "Unable to open file" , filename, MB_OK);
			return false;
		}
		Archive ar( &f, Archive::load, BUFF_SIZE, buff );
		try
		{
			ar.ReadString(str2, 255);
			ar.Read((unsigned char*)m2,sizeof(m2));
		}
		catch(char * str)
		{
			MessageBox(0,str,"",0);
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		catch(...)
		{
			MessageBox(0,"unknown error of archive read","",0);
		}
		
		ar.Close();
		f.Close();
	}
	printf(str2);
	printf("\n");
	for(size_t i = 0; i < sizeof(m2)/sizeof(double); i++)
	{
		printf("m2[%u] = %f\n", i, m2[i]);
	}


#else
#if TEST_SLAU

	sparse_row rw;
	rw.plus(5, 1.255);
	sparse_row rw2(rw);
	//return 0;


	size_t N = 2, n = 1;
	vector<vector<double> > a;
	vector<double> b;
	vector<double> x, x_;

	a.resize(N+n);
	b.resize(N+n);

	vdouble A, B, X;
	A.resize(int(N+n),int(N));
	B.resize(N+n);
#if 1
	vector<sparse_row> sa;
	sa.resize(N+n);
#else
	vector<sparse_row> sa(N+n);
#endif

	for(size_t r = 0; r < N+n; r++)
	{
		a[r].resize(N);
		for(size_t c = 0; c < N; c++)
		{
			
			a[r][c] = (double) rand() / (double) RAND_MAX;
			//a[r][c] = c+r;
			A(r,c) = a[r][c];
			sa[r].plus(c, a[r][c]);
		}
		//b[r] = 1;
		b[r] = (double) rand() / (double) RAND_MAX;
		B(r) = b[r];
	}


//	print_slau(a, N, b, "");

	double epsilon = 0.0000000001;
/*	if (!lesgausssolve(a, N, b, x, epsilon))
		printf("system was not solved\n");

	if (!lesgausssolve(a, N+1, N, b, x, epsilon))
		printf("system was not solved\n");*/

	if (!lesgausssolve_find_max(a, N+n, N, b, x, epsilon))
		printf("system was not solved\n");

	if (!lesgausssolve(sa, N+n, N, b, x_, epsilon))
		printf("system was not solved\n");
/*
	if (!lesgausssolve_find_max_norm(a, N+n, N, b, x, epsilon))
		printf("system was not solved\n");
*/
	/*double det;
	A.sls_det(B,X,det);
	printf ("det = %f\n", det);
*/

	for (size_t r = 0; r < sa.size(); r++)
	{
		sa[r].clear();
	}


	X = A.Tichonov(B,true);

	for(size_t c = 0; c < N; c++)
	{
		printf("x[%u] = %e\tX(%u) = %e\tx_[%u] = %e\n", c, x[c], c, X(int(c)), c, x_[c]);
	}

	// Вектор невязки
	size_t rows = a.size();
	vector<double> E1(rows), E2(rows), E3(rows);
	for (r = 0; r < rows; r++)
	{
		E1[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E2[r] = - b[r]; // элемент вектора правых частей со знакомминус
		E3[r] = - b[r]; // элемент вектора правых частей со знакомминус
		for (size_t c = 0; c < a[r].size(); c++)
		{			
			E1[r] += x[c] * a[r][c]; // суммируем поэлементно произведения искомого вектора на строку
			E2[r] += X(c) * a[r][c]; // суммируем поэлементно произведения искомого вектора на строку
			E3[r] += x_[c] * a[r][c]; // суммируем поэлементно произведения искомого вектора на строку
		}
	}


	printf("E1 = %e E2 = %e E3 = %e\n", SquareSum(E1), SquareSum(E2), SquareSum(E3));

#else


#if 0
//#include "stdio.h" 
//#include "windows.h" 

//int main(int argc, char* argv[]) 
//{ 
#if 0
// ";PWD=password"

static char lpszConnect[512];
sprintf(lpszConnect, ";PWD=");
        static char * szPassword = lpszConnect + 5; 
        ZeroMemory(szPassword, sizeof(szPassword)); 

        static char szAlphabet[256]; 
        //strcpy(szAlphabet, "ABC"); 
		strcpy(szAlphabet, "abcdefgijhklmnopqrstuvwxyz"); 

        static unsigned char bAlphabet[256]; 
        ZeroMemory(bAlphabet, sizeof(bAlphabet)); 

        int i = 0, k = 0; 
        while (TRUE) 
        { 
                bAlphabet[k] = (unsigned char)szAlphabet[i]; 
                if (!szAlphabet[i]) 
                        break; 
                k = (unsigned char)szAlphabet[i]; 
                i++; 
        } 

        while (TRUE) 
        { 
                __asm 
                { 
                    pushad 
                    mov edi,offset szPassword 
                    mov ebx,offset bAlphabet 
                L1: movzx eax,byte ptr [edi] 
                    xlat 
                    cmp al,0 
                    je L3 
                    mov [edi],al 
                    jmp L5 

                L3: xlat 
                    stosb 
                    jmp L1 

                L5: popad 
                } 
                printf("%s\n", lpszConnect); 
        } 
#else
        static char szPassword[256]; 
        ZeroMemory(szPassword, sizeof(szPassword)); 

        static char szAlphabet[256]; 
        //strcpy(szAlphabet, "ABC"); 
		strcpy(szAlphabet, "abcdefgijhklmnopqrstuvwxyz"); 

        static unsigned char bAlphabet[256]; 
        ZeroMemory(bAlphabet, sizeof(bAlphabet)); 

        int i = 0, k = 0; 
        while (TRUE) 
        { 
                bAlphabet[k] = (unsigned char)szAlphabet[i]; 
                if (!szAlphabet[i]) 
                        break; 
                k = (unsigned char)szAlphabet[i]; 
                i++; 
        } 

        while (TRUE) 
        { 
                __asm 
                { 
                    pushad 
                    mov edi,offset szPassword 
                    mov ebx,offset bAlphabet 
                L1: movzx eax,byte ptr [edi] 
                    xlat 
                    cmp al,0 
                    je L3 
                    mov [edi],al 
                    jmp L5 

                L3: xlat 
                    stosb 
                    jmp L1 

                L5: popad 
                } 
                printf("%s\n", szPassword); 
        } 
#endif
 //       return 0; 
//} 
#else

#if 1
	test_min_sq_holesski();
#else
	WinSurf();
#endif

#endif
#endif
#endif
	return 0;
}
#else
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{
	//if (!CheckMyLicense()) return FALSE;
	hInst = hInstance;
	WinSurf();
	return 0;
}
#endif
#endif

#include "./../surfdoc/src/archive.h"
#include "./../array/src/slau.h"

void Transponate(vector<sparse_row > & a, size_t cols, vector<sparse_row> & at);
template <class T> bool StoreMatrix(char * filename, vector<T>& m, long cols);
template <class T> void LoadMatrix(char * filename, vector<T>& m, long & cols);

void test_min_sq_holesski()
{
#define BUFF_SIZE 1024
void SparseStructureToMetafile(char * fn_spm, char * fn_emf);
bool FormMinSquareMatrix(char * fn_operator_wav, char * fn_min_sq_mat, double alpha);
bool Holesski3(const char * fn_min_sq_mat, const char * fn_Lt, char * dir, long j_start, double alpha);
void ErrorOfInverseProblemSolving(bool to_print, char * fn_operator, vector<double> & b, vector<double> & sol, string name, vector <double> & b_rec);
bool InverseProblem_Solving (bool to_print, const char * fn_operator_transponed, const char * fn_min_sq_mat, const char * fn_Lt, vector<double> b, vector<double> & sol, double alpha, vector<double> sol_mean);
bool InverseProblem_Solving (bool to_print, const char * fn_operator_transponed, 
							 const char * fn_min_sq_mat, 
							 const char * fn_L, 
							 const char * fn_U, 
							 const char * fn_P, 
							 vector<double> b, vector<double> & sol, double alpha, vector<double> sol_mean);

bool LUP_in_operative_memory(const char * fn_min_sq_mat, const char * fn_L, const char * fn_U, const char * fn_P, const char * dir, double alpha);

	char dir_out[4098];
	char common_directory[1024];
	sprintf(common_directory, "C://LABORO", common_directory);
	
	char fn_min_sq_mat[4098];
	char fn_Lt[4098];
	char fn_L[4098];
	char fn_U[4098];
	char fn_P[4098];

	int n = 0;
	sprintf(dir_out, "%s\\test_min_sq", common_directory);
	while (!CreateDirectory(dir_out, NULL))
	{
		sprintf(dir_out, "%s\\test_min_sq(%d)", common_directory, ++n);
	}

	double alpha_min_sq = 1e-3;
	bool alpha_to_holesski = 1;
	cout << "alpha_to_holesski" << endl;
	cin >> alpha_to_holesski;


	bool to_calculi_holesski = 1;
	cout << "Enter to_calculi_holesski" << endl;
	cin >> to_calculi_holesski;

	char fn_operator[4098];
	// начало расчётного блока
	//DoMyMethod3W(type, granicy_kak_glubina, description, mmd3, w3, ab,X,Y,Z, to_fill_matrix);
	//if (/*to_fill_matrix*/true)
	//{
		sprintf(fn_operator, "%s\\operator.spm", dir_out);

	char fn_operator_transponed[4098];
		sprintf(fn_operator_transponed, "%s\\operator_transponed.spm", dir_out);

		//int smoof_power = 1024;
		//int smoof_power = 4096;
		//int smoof_power = 8;


	printf ("fn_operator = %s\n", fn_operator);
	//fprintf (description, "smoof_power = %d\n", smoof_power);

		printf("Filling of matrix\n");
		// формируем матрицу оператора прямой задачи, 
		// число строк равно длине сигнала 
		// (или суммарной длине нескольких сигналов - 
		// нескольких профилей на одной или, ещё лучше, на разных высотах)
		// на вход оператора подаётся геологическая структура 
		// источников геополяритонного сигнала
		// на выходе оператора имеем мощность излучения (сигнал) на профилях
		//{
			AFile f;
			if( !f.Open( fn_operator, GENERIC_WRITE, TRUNCATE_EXISTING) ) 
			{
				if( !f.Open( fn_operator, GENERIC_WRITE, CREATE_NEW) ) 
				{
					MessageBox(0, "Filling the matrix 3D\nUnable to open file" , fn_operator, MB_OK);
					return;
				}
			}			
			char buff[BUFF_SIZE];
			Archive ar( &f, Archive::store, BUFF_SIZE, buff );

			long rows = 8;
			long cols = 5;

			// записываем размерность матрицы
			ar << rows; 
			ar << cols;

			// а теперь саму матрицу - построчно!!

			for (long r = 0; r < rows; r++)
			{
				//ar << m[r];

				for (long c = 0; c < cols; c++)
				{
					double value = 1+r+c;
					ar << c;
					ar << value;

					printf("%f ", value);


				}
				//признак конца записи строки
				long i = -1;
				double value = 0.0;
				ar << i;
				ar << value;

				printf("\n");

			}
			ar.Close();
			f.Close();
		//}



	vector<sparse_row> m;
	long _cols;
	LoadMatrix<sparse_row>(fn_operator, m, _cols);
	vector<sparse_row> at;
	Transponate(m, _cols, at);

	long transponed_cols = rows;

	StoreMatrix(fn_operator_transponed, at, transponed_cols);

	/*Grid4 * cube = ShowCube(mmd);
		char fn[1024]; 
		sprintf(fn, "%s\\cube.cub", 
			dir_out);
		SaveAsSurfer7Grid4(fn, cube);*/

	//}

	//printf("The matrix is filled!!!\n");

//	if (!CheckMyLicense()) return false;        

	if (/*to_calculi_min_sq_mat*/true)
	{
		SparseStructureToMetafile(fn_operator, "operator_struct.emf");

		//sprintf(mmd3.fn_min_sq_mat, "%s\\op_wav_min_sq_%f.spm", dir_out, mmd3.alpha_min_sq);					
		sprintf(fn_min_sq_mat, "%s\\op_min_sq_%f.spm", dir_out, 
			alpha_to_holesski ? 0.0 : alpha_min_sq);					
		//if (!FormMinSquareMatrix(mmd3.fn_operator_wav, mmd3.fn_min_sq_mat, mmd3.alpha_min_sq))
		if (!FormMinSquareMatrix(fn_operator_transponed, fn_min_sq_mat, 
			alpha_to_holesski ? 0.0 : alpha_min_sq))
		{
			printf("Error while FormMinSquareMatrix()\n");
			return;
		}
	}

	if (to_calculi_holesski)
	{
#if 0
		//SparseStructureToMetafile(mmd3.fn_min_sq_mat);
		SparseStructureToMetafile(fn_min_sq_mat, "min_sq_mat_struct.emf");
#endif

		long j_start = 0;


		sprintf(fn_Lt, "%s\\Lt.spm", dir_out);
#if 1
		if (!Holesski3(fn_min_sq_mat, 
			fn_Lt, 
			dir_out, j_start, alpha_to_holesski ? alpha_min_sq : 0.0))
		{
			printf("Error while Holesski3()\n");
			return;
		}
#else
		// BUG do not work!!!
		if (!Holesski3_in_operative_memory(mmd3.fn_min_sq_mat, mmd3.fn_Lt, dir_out))
		{
			printf("Error while Holesski3()\n");
			continue;
			//return false;
		}
#endif

	}
	else
	{
		sprintf(fn_L, "%s\\L.spm", dir_out);
		sprintf(fn_U, "%s\\U.spm", dir_out);
		sprintf(fn_P, "%s\\P.ind", dir_out);
		
		if (!LUP_in_operative_memory(fn_min_sq_mat, 
			fn_L, 
			fn_U, 
			fn_P, 
			dir_out, 
			alpha_to_holesski ? alpha_min_sq : 0.0))
		{
			printf("Error while LUP()\n");
			return;
			//return false;
		}
	}


			vector <double> rec_signal;

			vector<double> signal(rows);
for (long r = 0; r < rows; r++)
{
signal[r] = r+1;
printf ("b[%u] = %f\n", r, signal[r]);
}

	printf("Start of solve the inverse problem\n");

	// находим решение обратной задачи в S области
	vector<double> sol(cols);
	vector<double> sol_mean(cols, 0.0);
	double alpha = 0.0;
//#if SPARSE_OUT_W
		
	if (to_calculi_holesski)
	{
		if (!InverseProblem_Solving(true, fn_operator_transponed, fn_min_sq_mat, fn_Lt, signal, sol, alpha, sol_mean))
		{
		}
	}
	else
	{
		if (!InverseProblem_Solving(true, fn_operator_transponed, fn_min_sq_mat, 
			fn_L,
			fn_U,
			fn_P,
			signal, sol, alpha, sol_mean))
		{
		}
	}
//#endif
for (long c = 0; c < cols; c++)
{
printf ("x[%u] = %f\n", c, sol[c]);
}

printf("The inverse problem is solved!!!\n");
	printf("Form the frequency matrix from the inverse problem solving!!!\n");

	//vector<double> rec_signal_S;
	//printf("Error of solve the inverse problem in S region\n");
	//ErrorOfInverseProblemSolving(mmd.fn_operator_wav, signal, sol_S, name, rec_signal_S);




	ErrorOfInverseProblemSolving(true, fn_operator, signal, sol, "name", rec_signal);





		
	

				







}
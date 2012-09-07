// OGDoc.cpp : implementation of the COGDoc class
//

#include "stdafx.h"
//#include "OG.h"

#include "OGDoc.h"
#include "OGView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

u_int COGDoc::s_nDocs = 0;

/////////////////////////////////////////////////////////////////////////////
// COGDoc

IMPLEMENT_DYNCREATE(COGDoc, CDocument)

BEGIN_MESSAGE_MAP(COGDoc, CDocument)
	//{{AFX_MSG_MAP(COGDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	ON_COMMAND(ID_READ_DATA, OnReadData)
	ON_COMMAND(ID_ANIMATE_GRAPHIC, AnimateGraphic)
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COGDoc construction/destruction

COGDoc::COGDoc()
{
	m_nDoc = s_nDocs;
	s_nDocs++;

	m_nSurfs = 3;

	m_vcPointsSurf.resize(m_nSurfs);
	m_vxSize.resize(m_nSurfs);
	m_vySize.resize(m_nSurfs);
	for (int s = 0; s < m_nSurfs; s++)
		m_vcPointsSurf[s].resize(0);
	m_cPoints2.resize(0);
	// TODO: add one-time construction code here

}

COGDoc::~COGDoc()
{
}
inline void MinMax (float d, float& Min, float& Max)
{
	//====== Корректируем переданные по ссылке параметры
	if (d > Max)
		Max = d;			// Претендент на максимум
	else if (d < Min)
		Min = d;			// Претендент на минимум
}
Vector <CPoint3D> lorenz(float X_int, float Y_int, float Z_int, float time_step, int iterations)
{
	//EnterCriticalSection( &theApp.cs );
	Vector <CPoint3D> output_vector;
	output_vector.resize(iterations);
#if 0
	float 
		sigma = 10.f,
		gamma = 28.f,
		beta = float(8.f/3.f);
#else
	float 
		sigma = 10.f,
		gamma = 28.f,
		beta = float(8.f/3.f);
#endif
	float 
		x_star,
		y_star,
		z_star;
	for ( int i = 0; i < iterations; i++)
	{
		x_star = X_int + (-sigma*X_int + sigma*Y_int)*time_step;
		y_star = Y_int + (gamma*X_int - Y_int - Z_int*X_int)*time_step;
		z_star = Z_int + (-beta*Z_int + X_int * Y_int) * time_step;
		X_int = x_star;
		Y_int = y_star;
		Z_int = z_star;
		output_vector[i] = CPoint3D (x_star, y_star, z_star);
	}
	//LeaveCriticalSection( &theApp.cs );
	return output_vector;


}

BOOL COGDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// COGDoc serialization

void COGDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// COGDoc diagnostics

#ifdef _DEBUG
void COGDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void COGDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// COGDoc commands
void COGDoc::DefaultGraphic()
{
	//EnterCriticalSection( &theApp.cs );
	//====== Размеры сетки узлов
	for (int s = 0; s < m_nSurfs; s++)
	{
		m_vxSize[s] = m_vySize[s] = 65;
		//====== Размеры сетки узлов

		//====== Число ячеек на единицу меньше числа узлов
		UINT	nz = m_vySize[s] - 1,
				nx = m_vxSize[s] - 1;

		// Размер файла в байтах для хранения значений функции
		DWORD nSize = m_vxSize[s] * m_vySize[s] * sizeof(float)
							+ 2*sizeof(UINT);

		//====== Временный буфер для хранения данных
		BYTE *buff = new BYTE[nSize+1];

		//====== Показываем на него указателем целого типа
		UINT *p = (UINT*)buff;

		//====== Размещаем данные целого типа
		*p++ = m_vxSize[s];
		*p++ = m_vySize[s];

		//====== Меняем тип указателя, так как дальше
		//====== собираемся записывать вещественные числа
		float *pf = (float*)p;

		//=== Предварительно вычисляем коэффициенты уравнения
		double	fi = atan(1.)*6;
				m_kx = fi/nx,
				m_kz = fi/nz;

		//====== В двойном цикле пробега по сетке узлов
		//=== вычисляем и помещаем в буфер данные типа float
		for (UINT i=0;  i<m_vySize[s];  i++)
		{
			for (UINT j=0;  j<m_vxSize[s];  j++)
			{
				*pf++ = float (10*s + sin(m_kz*(i-nz/2.))
								* sin(m_kx*(j-nx/2.)));
			}
		}
		//====== Создание динамического массива m_cPointsSurf
		SetGraphPoints (s, buff, nSize);

		//=== Переменная для того, чтобы узнать сколько
		//=== байт было реально записано в файл
		DWORD nBytes;

		//=== Создание и открытие файла данных sin.dat
		HANDLE hFile = CreateFile(_T("sin.dat"), GENERIC_WRITE,
						0,0,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,0);

		//====== Запись в файл всего буфера
		WriteFile(hFile,(LPCVOID)buff, nSize,&nBytes, 0);

		//====== Закрываем файл
		CloseHandle(hFile);


		//====== Освобождаем временный буфер
		delete [] buff;
		//LeaveCriticalSection( &theApp.cs );
	}

}
void COGDoc::SetGraphPoints(int s, BYTE* buff, DWORD nSize)
{


	//EnterCriticalSection( &theApp.cs );
	//====== Готовимся к расшифровке данных буфера
	//====== Указываем на него указателем целого типа
	UINT *p = (UINT*)buff;

	//=== Выбираем данные целого типа, сдвигая указатель
	m_vxSize[s] = *p;
	m_vySize[s] = *++p;

	//====== Проверка на непротиворечивость
	if (m_vxSize[s]<2 || m_vySize[s]<2 || 
			m_vxSize[s]*m_vySize[s]*sizeof(float)
			+ 2 * sizeof(UINT) != nSize)
	{
		AfxMessageBox(_T("Данные противоречивы"));
		return;
	}

	//====== Изменяем размер контейнера
	//====== При этом его данные разрушаются
	m_vcPointsSurf[s].resize(m_vxSize[s]*m_vySize[s]);

		

	if (m_vcPointsSurf[s].empty())
	{
		AfxMessageBox(_T("Не возможно разместить данные"));
		return;
	}

	//====== Подготовка к циклу пробега по буферу
	//====== и процессу масштабирования
	float	x, z,
			//====== Считываем первую ординату
			*pf   = (float*)++p,
			fMinY = *pf,
			fMaxY = *pf,
			right = (m_vxSize[s]-1)/2.f,
			left  = -right,
			rear  = (m_vySize[s]-1)/2.f,
			front = -rear, 
			range = (right + rear)/2.f;

	UINT	i, j, n;

	//?????====== Вычисление размаха изображаемого объекта
	m_fRangeY = range;
	m_fRangeX = float(m_vxSize[s]);
	m_fRangeZ = float(m_vySize[s]);

	//??????====== Величина сдвига вдоль оси Z
//	m_zTrans = -1.5f * m_fRangeZ;

	//====== Генерируем координаты сетки (X-Z)
	//====== и совмещаем с ординатами Y из буфера
	for (z=front, i=0, n=0;  i<m_vySize[s];  i++, z+=1.f)
	{
		for (x=left, j=0;  j<m_vxSize[s];  j++, x+=1.f, n++)
		{
			MinMax (*pf, fMinY, fMaxY);
			m_vcPointsSurf[s][n] = CPoint3D(x,z,*pf++);
		}
	}

	//====== Масштабирование ординат
	float zoom = fMaxY > fMinY ? range/(fMaxY-fMinY)
									 : 1.f;

	for (n=0;  n<m_vxSize[s]*m_vySize[s];  n++)
	{
		m_vcPointsSurf[s][n].y = zoom * (m_vcPointsSurf[s][n].y - fMinY)
							- range/2.f;
	}
	m_cPoints2 = lorenz(0.1f, 0.1f, 0.1f, 0.01f, 1000);
/*	CString str,s;
	for(int  ii =0; ii < m_cPoints2.size(); ii++)
	{
		s.Format("\n%g, %g, %g", m_cPoints2[ii].x, m_cPoints2[ii].y, m_cPoints2[ii].z);
		str += s;
	}
	FILE * stream;
	stream = fopen("C:\\lorenz.txt", "wt");
	fprintf(stream, str);
	fclose(stream);*/
	//LeaveCriticalSection( &theApp.cs );

}

//====== Функция непосредственного чтения данных
bool COGDoc::DoRead(HANDLE hFile)
{
	//EnterCriticalSection( &theApp.cs );
	//====== Сначала узнаем размер файла
	DWORD nSize = GetFileSize (hFile, 0);

	//=== Если не удалось определить размер, GetFileSize
	//====== возвращает 0xFFFFFFFF
	if (nSize == 0xFFFFFFFF)
	{
		GetLastError();
		AfxMessageBox(_T("Некорректный размер файла"));
		CloseHandle(hFile);
		return false;
	}

	//=== Создаем временный буфер размером в весь файл
	BYTE *buff = new BYTE[nSize+1];

	//====== Обработка отказа выделить память
	if (!buff)
	{
		AfxMessageBox(_T("Слишком большой размер файла"));
		CloseHandle(hFile);
		return false;
	}

	//====== Реальный размер файла
	DWORD nBytes;
	//====== Попытка прочесть файл
	ReadFile (hFile, buff, nSize, &nBytes, 0);
	CloseHandle(hFile);

	//====== Если реально прочитано меньшее число байт
	if (nSize != nBytes)
	{
		AfxMessageBox(_T("Ошибка при чтении файла"));
		return false;
	}

	//====== Генерация точек изображения
	for (int s = 0; s < m_nSurfs; s++)
		SetGraphPoints (s, buff, nSize);

	//====== Освобождение временного буфера
	delete [] buff;
	//====== Возвращаем успех
	//LeaveCriticalSection( &theApp.cs );
	return true;
}


void COGDoc::ReadData()
{
	//EnterCriticalSection( &theApp.cs );
	//=== Строка, в которую будет помещен файловый путь
	TCHAR szFile[MAX_PATH] = { 0 };

	//====== Строка фильтров демонстрации файлов
	TCHAR *szFilter =TEXT("Graphics Data Files (*.dat)\0")
						TEXT("*.dat\0")
						TEXT("All Files\0")
						TEXT("*.*\0");

	//====== Выявляем текущую директорию	
	TCHAR szCurDir[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH-1,szCurDir);

	//=== Структура данных, используемая файловым диалогом
	OPENFILENAME ofn;
	ZeroMemory(&ofn,sizeof(OPENFILENAME));

	//====== Установка параметров будущего диалога
	ofn.lStructSize	= sizeof(OPENFILENAME);
	//====== Окно-владелец диалога
	ofn.hwndOwner = NULL;//GetSafeHwnd();
	ofn.lpstrFilter	= szFilter;
	//====== Индекс строки фильтра (начиная с единицы)
	ofn.nFilterIndex	= 1;
	ofn.lpstrFile		= szFile;
	ofn.nMaxFile		= sizeof(szFile);
	//====== Заголовок окна диалога
	ofn.lpstrTitle	= _T("Найдите файл с данными");
	ofn.nMaxFileTitle = sizeof (ofn.lpstrTitle);
	//====== Особый стиль диалога (только в Win2K)
	ofn.Flags			= OFN_EXPLORER;

	//====== Создание и вызов диалога
	//=== В случае неудачи GetOpenFileName возвращает 0
	if (GetOpenFileName(&ofn))
	{
		// Попытка открыть файл, который должен существовать
		HANDLE hFile = CreateFile(ofn.lpstrFile, GENERIC_READ,
				FILE_SHARE_READ, 0, OPEN_EXISTING,
				FILE_ATTRIBUTE_NORMAL, 0);

		//=== В случае неудачи CreateFile возвращает -1
		if (hFile == (HANDLE)-1)
		{
			AfxMessageBox(_T("Не удалось открыть файл"));
			return;
		}

		//====== Попытка прочесть данные о графике 
		if (!DoRead(hFile))
			return;

		//====== Создание нового изображения
		POSITION posView;
		COGView * pView;
		posView = GetFirstViewPosition();
		while (posView !=NULL)
		{
			pView = (COGView*) GetNextView(posView);
		}

		pView->SendMessage(WM_USER + 10, 0, 0);
		//DrawScene();

		//====== Перерисовка окна OpenGL
		//Invalidate(FALSE);
		UpdateAllViews(pView);
	}
	//LeaveCriticalSection( &theApp.cs );
}
void COGDoc::OnReadData() 
{
	ReadData();
}


void COGDoc::AnimateGraphic()
{
	for (int s = 0; s < m_nSurfs; s++)
	{
		//====== Число ячеек на единицу меньше числа узлов
		UINT	nz = m_vySize[s] - 1,
				nx = m_vxSize[s] - 1;
		//=== Предварительно вычисляем коэффициенты уравнения
		double	fi = atan(1.)*6;
	//			m_kx = fi/nx;
	//			m_kz = fi/nz;
		unsigned int i, j, n;
		float	x, z, 
				f = float (10*s + sin(m_kz*(0-nz/2.))
								* sin(m_kx*(0-nx/2.))),
				fMinY = f,
				fMaxY = f,
				right = (m_vxSize[s]-1)/2.f,
				left  = -right,
				rear  = (m_vySize[s]-1)/2.f,
				front = -rear, 
				range = (right + rear)/2.f;
		//====== В двойном цикле пробега по сетке узлов
		//=== вычисляем и помещаем в буфер данные типа float
		//====== Генерируем координаты сетки (X-Z)
		//====== и совмещаем с ординатами Y из буфера
		for (z=front, i=0, n=0;  i<m_vySize[s];  i++, z+=1.f)
		{
			for (x=left, j=0;  j<m_vxSize[s];  j++, x+=1.f, n++)
			{
				f = float (10*s + sin(m_kz*(i-nz/2.))
								* sin(m_kx*(j-nx/2.)));
				m_vcPointsSurf[s][n] = CPoint3D(x,z,f);
			}
		}
		m_kz += .01f;
		m_kx += .01f;
	}
}

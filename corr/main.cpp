// main.c

#include <stdio.h>
#include <float.h>

#include <string.h>

#include <stdlib.h>

#include <math.h>



int ReadInputFile1(char * fname)
{
	FILE * stream;
	const unsigned int n = 1023;
	char szBuff[n];

	// open the file
	if ((stream = fopen(fname,"rt")) == NULL)
	{
		printf("Cannot open input file.\n");
		return -1;
	}
	int i = 0;
	double X,Y,Z;
	long t;
	double SX,SY,SZ;

	while (!feof(stream))
	{
		char * ch;
		ch = fgets(szBuff,n,stream);	
		if( ch != NULL && strlen(szBuff) > 1)
		{
			int rez = sscanf(szBuff,
				"%lf;%lf;%lf;%ld;%lf;%lf;%lf",					
				&X, &Y, &Z, &t, &SX, &SY, &SZ);

			if (rez == 7 && rez != EOF)
			{
				i++;
			}
			

		}
	}
	fclose(stream);
	return i;
}



int ReadInputFile2(char * fname, double * x, double * y, double * z, double * sx, double * sy, double * sz)
{
	FILE * stream;
	const unsigned int n = 1023;
	char szBuff[n];
	int i = 0;
	double X,Y,Z;
	long t;
	double SX,SY,SZ;

	if ((stream = fopen(fname,"rt")) == NULL)
	{
		printf("Cannot open input file.\n");
		return -1;
	}
	i = 0;
	while (!feof(stream))
	{
		char * ch;
		ch = fgets(szBuff,n,stream);
		if( ch != NULL && strlen(szBuff) > 1)
		{
			int rez = sscanf(szBuff,
				"%lf;%lf;%lf;%ld;%lf;%lf;%lf",					
				&X, &Y, &Z, &t, &SX, &SY, &SZ);

			if (rez == 7 && rez != EOF)
			{
				x[i] = X;
				y[i] = Y;
				z[i] = Z;
				sx[i] = SX;
				sy[i] = SY;
				sz[i] = SZ;
				i++;
			}
			

		}
	}
	fclose(stream);
	return 0;
}
#define HEAP_ZERO_MEMORY ( 0x8 )
double **Alloc2DMat (size_t size1, size_t size2) 
{
    double **v;
    size_t k;
	v = (double **)malloc( size1 * sizeof( double * ) );
    v[0] = (double *) malloc( size1 * size2 * sizeof (double));
    for (k = 1; k < size1; k ++) v[k] = v[k - 1] + size2;
    return (v);	
}

void Free2DMat(double ** v)
{
	if (v[0]) free( v[0] );
	if (v) free( v );
}

double ***Alloc3DMat (size_t npages, size_t nrows, size_t ncols) 
{
    double ***v;
    size_t page, row;
	// выделяем память под указатели на страницы
	v = (double ***)malloc(	npages * sizeof( double ** ) );

	if (v == NULL)
	{
		printf("Not enough memory for %u * sizeof( double ** ) = %d bytes", npages, npages * sizeof( double ** ) );
	}
	// выделяем память под указатели на строки
    v[0] = (double **) malloc( npages * nrows * sizeof (double*));

 	if (v[0] == NULL)
	{
		printf("Not enough memory for %u * %u * sizeof( double* ) = %u bytes", npages, nrows, npages * nrows * sizeof (double*) );
	}
	// выделяем память под указатели на элементы строк
    v[0][0] = (double *) malloc( npages * nrows * ncols * sizeof (double));

 	if (v[0][0] == NULL)
	{
		printf("Not enough memory for %u * %u * %u * sizeof( double ) = %u bytes", npages, nrows, ncols, npages * nrows * ncols * sizeof (double) );
	}

	for (page = 0; page < npages; page ++)
	{
		// указателям на страницы присваиваем значения 
		// указателей на первую строку на каждой странице
		if (page > 0)
		{
			v[page] = v[page - 1] + nrows;
			v[page][0] = v[page - 1][0] + nrows*ncols;
		}
		for (row = 1; row < nrows; row++)
		{
			// указателям на строки присваиваем 
			// значения указателей на первый элемент в каждой строке
			v[page][row] = v[page][row-1] + ncols;
		}
	}
	return (v);	
}
void Free3DMat(double *** v)
{
	if (v && v[0] && v[0][0]) free( v[0][0] );
	if (v && v[0]) free( v[0] );
	if (v) free( v );
}

int SaveAsSurferGrid7(const char * file, 
	long nRow, long nCol, 
	double xLL, double yLL,
	double xSize, double ySize,
	double zMin, double zMax,
	double ** z)
{

	
	FILE *stream;
	
	if ((stream = fopen(file,"wb")) == NULL)
	{
		
		printf("Cannot open output file.%s\n", file);
		return -1;
	}
	size_t wrote;

	// Записываем
	long headerID = 0x42525344;
	wrote = fwrite(&headerID, sizeof(long), 1, stream);

	long headerSize = 4;
	wrote = fwrite(&headerSize, sizeof(long), 1, stream);

	long Version = 4;
	wrote = fwrite(&Version, sizeof(long), 1, stream);
		
	long gridID = 0x44495247;
	wrote = fwrite(&gridID, sizeof(long), 1, stream);
	
	long gridSize = 72;
	wrote = fwrite(&gridSize, sizeof(long), 1, stream);


	//long nRow = yi.Length();// number of rows in the grid
	wrote = fwrite(&nRow, sizeof(long), 1, stream);


	//long nCol = xi.Length();// number of columns in the grid
	wrote = fwrite(&nCol, sizeof(long), 1, stream);


	//double xLL = xi[0];// X coordinate of the lower left corner of the grid
	wrote = fwrite(&xLL, sizeof(double), 1, stream);


	//double yLL = yi[0];// Y coordinate of the lower left corner of the grid
	wrote = fwrite(&yLL, sizeof(double), 1, stream);


	//double xSize = xi[1] - xi[0];// spacing between adjacent nodes in the X direction (between columns)
	wrote = fwrite(&xSize, sizeof(double), 1, stream);


	//double ySize = yi[1] - yi[0];// spacing between adjacent nodes in the Y direction (between rows)
	wrote = fwrite(&ySize, sizeof(double), 1, stream);


	//double zMin = zi.Min();// minimum Z value within the grid
	wrote = fwrite(&zMin, sizeof(double), 1, stream);


	//double zMax = zi.Max();// maximum Z value within the grid
	wrote = fwrite(&zMax, sizeof(double), 1, stream);


	double Rotation = 0.0;// not currently used
	wrote = fwrite(&Rotation, sizeof(double), 1, stream);


	double BlankValue = 1.70141e38;// nodes are blanked if greater or equal to this value
	wrote = fwrite(&BlankValue, sizeof(double), 1, stream);

	long dataID = 0x41544144;
	wrote = fwrite(&dataID, sizeof(long), 1, stream);

	long dataSize = nRow*nCol*sizeof(double);
	wrote = fwrite(&dataSize, sizeof(long), 1, stream);

	//wrote = fwrite(zi_.pD, sizeof(double), nRow*nCol, stream);
	for (long r = 0; r < nRow; r++)
	{
#if 1
		for (long c = 0; c < nCol; c++)
		{
			wrote = fwrite(&z[r][c], sizeof(double), 1, stream);

		}
#else
		wrote = fwrite(zi_.pD + r*nCol,  sizeof(double), nCol, stream);
#endif
	}

	fclose(stream);



	return 0;
}


void FillingTheMatrix3D_with_napravlennosty_diagramm_dipol(
					  double k_oslablenie,// коэффициент ослабления
					  double **** m,// указатель на три матрицы njuXr, njuYr, njuZr
					  double **** R,// указатель на три матрицы rx, ry, rz
					  long rows, long cols, long pages,
					  double x0, double y0, double z0,
					  double delta_x, double delta_y, double delta_z,				
					  long signal_len,
					  double * X,
					  double * Y,
					  double * Z,
					  double pw_dnp//,
					  //vector<vector<anten_direction> > & A
	
					  )
{

	/*
Прямая и обратная задача в УИМПЗ

1)	Направления рамочных антенн X, Y и Z задаются как вектора нормали: 
AX(1,0,0), AY(0,1,0) и AZ(0,0,1) соответственно.
2)	Координата источника излучения xi, yi, zi
3)	Его мощность W
4)	Его эллипсоид поляризации зададим отношением широтной компоненты амплитуды вектора напряжённости излучаемого переменного магнитного поля к его долготной компоненте PEW/NS. 
5)	Координата измерения излучения x, y, z
6)	Проводим вектор луча от источника к точке измерения L (x-xi, y-yi, z-zi)
7)	Модуль вектора луча |L| даёт расстояние, пройденное сигналом
8)	Ослабление сигнала вычисляем через коэффициент ослабления k_oslablenie : exp ( - k_oslablenie * |L|)

Вывод формулы для коэффициента выхода антенны, учитывая диаграмму направленности антенн и эллипсоид 
поляризации электромагнитного луча. Эллипсоид поляризации определяем по вектору напряжённости 
амплитуды переменного магнитного поля, образующего ЭМ волну. 

Допустим, что ЭМ волна от источника излучения xi, yi, zi 
распространяется снизу вверх вертикально, а нормаль антенны AZ(0,0,1) 
тоже расположена вертикально. Поток электромагнитной индукции или магнитный поток 
(проверить применение какого термина уместнее), вызванный вектором напряжённости 
магнитного поля рассматриваемого луча в силу геометрических причин не будет 
пересекать контур, поэтому коэффициент выхода антенны будет равен нулю. 

Рассмотрим взаимодействие этой же волны с антенной AX(1,0,0), 
нормаль которой расположена вдоль оси X, то есть по широте. Контур 
этой антенны будет нормально (под прямым углом) пересечён иксовой (широтной) 
компонентой эллипсоида поляризации рассматриваемого луча ЭМ волны. Т.о. 
коэффициент выхода антенны будет равен широтной компоненте эллипсоида 
поляризации, т.е. PEW/NS.

Теперь рассмотрим взаимодействие той же волны с антенной AY(0,1,0), 
нормаль которой расположена вдоль оси Y, то есть по долготе. Контур этой антенны 
будет нормально пересечён игрековой (долготной) компонентой эллипсоида поляризации 
рассматриваемого луча ЭМ волны. Т.о. коэффициент выхода антенны будет равен 1.0 / PEW/NS.

9)	Учитываем диаграмму направленности. При допущении, что электромагнитный луч не 
поляризован, используя закон электромагнитной индукции для контура, вводим коэффициент 
равный sin(phi) в степени n, где n равно 1 или 2, а phi – угол между векторами луча и 
нормалью антенны AX, AY или AZ. Определяем сперва cos(phi) через скалярное произведение 
AL векторов луча L и антенной нормали A (ax,ay,az). 
Вычисляем AL = |A|*|L|* cos(phi) = ax*(x-xi) + ay*(y-yi) + az*(z-zi). 
Откуда (зная, что |A| = 1): cos(phi) = (ax*(x-xi) + ay*(y-yi) + az*(z-zi)) / |L|.

Приближение неполяризованного луча позволяет произвести более подробную 
реконструкцию распределения мощности излучателей в пространстве. 
Но не даёт возможности произвести анализ анизотропии излучения горных пород.



Физически правильно рассматривать кристалл излучающей горной породы 
как комбинацию трёх взаимно-перпендикулярных излучающий диполей (IDX IDY IDZ).

Но для целей удобства анализа приёма этого излучения рамочной 
антенной допустим, что нам известно (если нам не известно, 
то оно наверняка известно специалистам по физике твёрдого тела) 
математическое преобразование от трёх взаимно-перпендикулярных 
излучающий диполей (IDX IDY IDZ) к трём взаимно-перпендикулярным 
излучающим контурам (IHX IHY IHZ). Поэтому мы в ходе решения 
обратной задачи будем искать распределение в пространстве горной 
породы излучающих контуров (IHX IHY IHZ), а переход от них к 
физически правильным излучающим диполям предоставим физикам-интерпретаторам.

Для начала предположим, что мы имеем дело с одним излучающим контуром.

Диаграмма направленности излучающего контура?

Диаграмма направленности пары излучающего и принимающего контуров?



	*/
	double 
		xi,yi,zi, 

		rx, rx2, 
		ry, ry2, 
		rz, rz2,

		len, phi, 

		phi_k, value;
	long j,p,r,C,i;
	//long signal_len = X.size(); // длина сигнала 

	int a; //номер антены 
	//AX(1,0,0),		a = 0
	//AY(0,1,0)			a = 1
	//и AZ(0,0,1)		a = 2

	// степень диаграммы направленности приёмника
	//int pw_dnp = 2;

    //минимальное значение, которое вносится в оператор прямой задачи    
	//double min_value = 0.03;
	//double min_value = 1e-16;

	//double k_phi_max = (PI/2.0)/atan(1.0/2.0*k);

	double k1 = 1.0;
	printf("Filling of matrix\n");
	// формируем матрицу оператора прямой задачи, 
	// число строк равно УТРОЕННОЙ длине сигнала, 
	// т.к. мы ищем ОПЕРАТОР ПРЯМОЙ ЗАДАЧИ ДЛЯ ТРЁХ АНТЕН
	// (или суммарной длине нескольких сигналов - 
	// нескольких профилей на одной или, ещё лучше, на разных высотах)
	// на вход оператора подаётся геологическая структура 
	// источников геополяритонного сигнала
	// на выходе оператора имеем мощность излучения (сигнал) на профилях
	// НА АНТЕНАХ AX(1,0,0), AY(0,1,0) и AZ(0,0,1) 

	// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
	double z_min = z0 - pages * delta_z;

	//double sum_operator_value_x = 0.0;
	//double sum_operator_value_y = 0.0;
	//double sum_operator_value_z = 0.0;
	//double hi, w, sum_operator_z_per_xy;
	if (m && R) // если дана матрица, пишем в неё (в оперативную память)
	{
		//(*m).resize(signal_len * 3);
		*m = Alloc3DMat(3, signal_len, rows * cols * pages);
		*R = Alloc3DMat(3, signal_len, rows * cols * pages);

		for (a = 0; a < 3; a++)// перебираем 3 антены
		{
			int ax = a == 0;
			int ay = a == 1;
			int az = a == 2;
			for (j = 0; j < signal_len; j++)
			{
				//double ax = A[a][j].ax;
				//double ay = A[a][j].ay;
				//double az = A[a][j].az;

				printf("Filling of matrix %ld %ld a=%d ax=%d ay=%d az=%d\n", j + a * signal_len, signal_len * 3, a, ax, ay, az);		


				int putted_in_row = 0;
				
				for (p = 0; p < pages; p++)
				{						
				//printf("Filling of matrix \t%ld %ld     %d\n", p, pages, putted_in_row);

				
					//zi = z0 - p * delta_z;// это неверно!!!
					// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
					//zi = z0 - (p+1) * delta_z;
					zi = z_min + p * delta_z;

					//hi = z0 - zi; w = spm.Apply(hi);

					rz = (Z[j]-zi);
					rz2 = rz * rz;

					//часть пути луча, на котором происходит затухание
					double part_of_len = (z0 - zi) / rz;
					
					for (r = 0; r < rows; r++)
					{
						
						yi = y0 + r * delta_y;
						ry = Y[j]-yi;
						ry2 = ry*ry;
						
						for (C = 0; C < cols; C++)
						{
							// индекс в строке матрицы оператора прямой задачи
							i = p * rows * cols + r * cols + C;
							// координата геологического источника
							xi = x0 + C * delta_x;
							rx = (X[j]-xi);
							rx2 = rx * rx;
							// расстояние от геологического источника
							// до приёмника на профиле
							len = sqrt(
								rx2 + 
								ry2 + 
								rz2 
								);
							// коэффициент выхода диаграммы направленности nju_fi
							// угол между направлением на источник и нормалью к антене
							phi = acos((ax*rx + ay*ry + az*rz) / len);
							phi_k = pow(sin(phi), pw_dnp);

							// 
							//if (wave_type == 1)	
							k1 = (1.0 / pow(len, pw_dnp));
							value = k1 * exp ( - k_oslablenie * pw_dnp * part_of_len * len) * phi_k;



								//if (value == 0.0)
								//{
								//	value = DBL_MIN;
								//}

								// добавление элемента в разреженную строку
								//(*m)[j].put(i, value);
								(*m)[a][j][i] = value;
								(*R)[0][j][i] = rx;
								(*R)[1][j][i] = ry;
								(*R)[2][j][i] = rz;

								putted_in_row++;

								//sum_operator_value_x += ax * value * w;
								//sum_operator_value_y += ay * value * w;
								//sum_operator_value_z += az * value * w;
							

						}
					}
				}
			}
		}
	}


	//printf("sum_operator_value_x = %e\n", sum_operator_value_x);
	//printf("sum_operator_value_y = %e\n", sum_operator_value_y);
	//printf("sum_operator_value_z = %e\n", sum_operator_value_z);

	//sum_operator_z_per_xy = 2. * sum_operator_value_z / (sum_operator_value_x + sum_operator_value_y);
	//printf("sum_operator_z_per_xy = %f\n", sum_operator_z_per_xy);
}


void SavingResultGrid(
	const char * path,
	const char * name,
	double * weighted_korr,
	long rows, long cols, long pages, 
	double x0, double y0, double z_min,
	double delta_x, double delta_y, double delta_z,				
	bool to_reduce_x, bool to_reduce_y, 
	bool only_positive)
{
	double kMin = DBL_MAX;
	double kMax = -DBL_MAX;
	
	if (to_reduce_x)//cols==1
	{
		double ** w_g = Alloc2DMat (pages, rows);
		for(long c = 0; c < cols; c++)
		{
			for(long r = 0; r < rows; r++)
			{
				for(long P = 0; P < pages; P++)
				{
					// индекс в строке матрицы оператора прямой задачи
					long i = P * rows * cols + r * cols + c;					
					w_g[P][r] = weighted_korr[i];

					if (only_positive && w_g[P][r] < 0) w_g[P][r] = 0.0;

					if (w_g[P][r] > kMax) kMax = w_g[P][r];
					if (w_g[P][r] < kMin) kMin = w_g[P][r];

										
				}
			}
		}
		char file[512];
		sprintf(file, "%s\\%s_redx.grd", path, name);


		SaveAsSurferGrid7(file, 
			pages, rows, 
			y0, z_min, 
			delta_y, delta_z, 
			only_positive ? 0.0 : kMin, kMax,
			w_g);

		Free2DMat(w_g);	
	}

	if (to_reduce_y)//rows==1
	{
		double ** w_g = Alloc2DMat (pages, cols);
		for(long c = 0; c < cols; c++)
		{
			for(long r = 0; r < rows; r++)
			{
				for(long P = 0; P < pages; P++)
				{
					// индекс в строке матрицы оператора прямой задачи
					long i = P * rows * cols + r * cols + c;					
					w_g[P][c] = weighted_korr[i];					

					if (only_positive && w_g[P][c] < 0) w_g[P][c] = 0.0;

					if (w_g[P][c] > kMax) kMax = w_g[P][c];
					if (w_g[P][c] < kMin) kMin = w_g[P][c];

				}
			}
		}
		char file[512];
		sprintf(file, "%s\\%s_redy.grd", path, name);


		SaveAsSurferGrid7(file, 
			pages, cols, 
			x0, z_min, 
			delta_x, delta_z, 
			only_positive ? 0.0 : kMin, kMax,
			w_g);

		Free2DMat(w_g);	
	}


	printf("kMax = %e\n", kMax);
	printf("kMin = %e\n", kMin);
}


/*

void GetMinMaxXYOfData(long signal_len,

				   double * X,
				   double * Y,				   
				   
				   double & min_X,
				   double & max_X,
				   double & min_Y, 
				   double & max_Y
  
				   )
{
	min_X = DBL_MAX;
	max_X = -DBL_MAX;
	min_Y = DBL_MAX;
	max_Y = -DBL_MAX;

	for (int i = 0; i < signal_len; i++)
	{
		if (min_X > X[i]) min_X = X[i];
		if (min_Y > Y[i]) min_Y = Y[i];

		if (max_X < X[i]) max_X = X[i];
		if (max_Y < Y[i]) max_Y = Y[i];
	}
}

*/



//#include <vector>
//using namespace std;

#define va_size 3

int weighted_corr_calc(const char * pathin, const char * pathout, const char * fn)
{

	short a1, a2, ia1, ia2;  //vector<short> va;
	//va.push_back(0);//x
	//va.push_back(1);//y
	//va.push_back(2);//z

	short * va = (short*)malloc(va_size*sizeof(short));
	//va[0] = 0;
	//va[1] = 1;
	//va[2] = 2;
	va[0] = 0;
	va[1] = 1;
	va[2] = 2;




	char sz_path_of_file[4096];			
	sprintf(sz_path_of_file, "%s\\%s.csv", pathin, fn);



	int len = ReadInputFile1(sz_path_of_file);
	double * x = (double*)malloc(len*sizeof(double));
	double * y = (double*)malloc(len*sizeof(double));
	double * z = (double*)malloc(len*sizeof(double));

	//double * sx = (double*)malloc(len*sizeof(double));
	//double * sy = (double*)malloc(len*sizeof(double));
	//double * sz = (double*)malloc(len*sizeof(double));
	
	double ** W = Alloc2DMat (3, len);

	double ** g = Alloc2DMat (len, len);

	ReadInputFile2(sz_path_of_file, x, y, z, W[0], W[1], W[2]);

	double * mean = (double*)malloc(3*sizeof(double));
	double * cov = (double*)malloc(3*sizeof(double));

	for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены
		mean[a1] = 0.0;
		for (long r = 0; r < len; r++){
			mean[a1] += W[a1][r];
		}
		mean[a1] /= len;

		printf("mean = %f\n",mean);

		cov[a1] = 0.0;
		for (long r = 0; r < len; r++){
			cov[a1] += (W[a1][r]-mean[a1])*(W[a1][r]-mean[a1]);
		}
		cov[a1] /= len;
		printf("cov[%d] = %f\n", a1, cov[a1]);

	}

	if (false)
	{
	for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены


		double zMin = DBL_MAX;
		double zMax = -DBL_MAX;

		for (long r = 0; r < len; r++)
		{

			for (long c = 0; c < len; c++)
			{
				g[r][c] = (W[a1][r]-mean[a1])*(W[a1][c]-mean[a1])/cov[a1];

				//if (g[r][c] < 0) g[r][c] = 0.0;

				if (g[r][c] > zMax) zMax = g[r][c];
				if (g[r][c] < zMin) zMin = g[r][c];
			}
		}

		printf("zMax = %f\n",zMax);
		printf("zMin = %f\n",zMin);
		char file[512];
		sprintf(file, "%s\\%s_%c.grd", pathout, fn, 'x'+a1);


		SaveAsSurferGrid7(file, 
			len, len, 
			0.0, 0.0,
			1.0, 1.0,
			zMin, zMax,
			g);
	}
	}

	bool to_center = true;
	if (to_center)
	{
		for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены



			for (long r = 0; r < len; r++)
			{
				W[a1][r] -= mean[a1];			
			}


		}	
	}

	long rows = 40;
	long cols = 40;
	long pages = 40;



	double min_X, max_X, min_Y, max_Y;				
	//GetMinMaxXYOfData(x, y, len, min_X, max_X, min_Y, max_Y);
	min_X = DBL_MAX;
	max_X = -DBL_MAX;
	min_Y = DBL_MAX;
	max_Y = -DBL_MAX;

	for (int i = 0; i < len; i++)
	{
		if (min_X > x[i]) min_X = x[i];
		if (min_Y > y[i]) min_Y = y[i];

		if (max_X < x[i]) max_X = x[i];
		if (max_Y < y[i]) max_Y = y[i];
	}

	double 
		DX = max_X - min_X, 
		DY = max_Y - min_Y; 

	double dx_and_dy_per_DZ = 2.0;
	bool granicy_kak_glubina = false;

	double z0 = 130;
	double z_min = -2870;
	double DZ = z0 - z_min;



	double dx = DZ * dx_and_dy_per_DZ;
	double dy = DZ * dx_and_dy_per_DZ;


	double delta__x = DX - dx * int (granicy_kak_glubina);
	double delta__y = DY - dy * int (granicy_kak_glubina);
	double delta__z = z0 - z_min;


	// на случай редукции к двумерному случаю
	bool to_reduce_x = (DX - dx) < 0.0;
	bool to_reduce_y = (DY - dy) < 0.0;

	if (to_reduce_x) {cols = 1; delta__x = 0.0;}
	if (to_reduce_y) {rows = 1; delta__y = 0.0;}

	double x0 = to_reduce_x ? (min_X+max_X)/2.0 : min_X + 0.5 * dx * int (granicy_kak_glubina);
	double y0 = to_reduce_y ? (min_Y+max_Y)/2.0 : min_Y + 0.5 * dy * int (granicy_kak_glubina);

	double delta_x = to_reduce_x ? 0.0 : delta__x / (cols - 1);
	double delta_y = to_reduce_y ? 0.0 : delta__y / (rows - 1);

	// опускаем верхнюю страницу куба под дневную поверхность на глубину delta_z
	double delta_z = delta__z / pages;


	double *** R;// rx,ry,rz

	double *** m;// три матрицы njuXr, njuYr, njuZr
	printf("Filling of matrix\n");
	// формируем матрицу оператора прямой задачи, 
	// число строк равно длине сигнала 
	// (или суммарной длине нескольких сигналов - 
	// нескольких профилей на одной или, ещё лучше, на разных высотах)
	// на вход оператора подаётся геологическая структура 
	// источников геополяритонного сигнала
	// на выходе оператора имеем мощность излучения (сигнал) на профилях

	double k_oslablenie = 0.00023025;
	
	// степень диаграммы направленности приёмника
	double pw_dnp = 2.0;
	bool only_positive = false;
	bool all_to_all = true;
	double min_radius_kvadrat = 10000;
	
	FillingTheMatrix3D_with_napravlennosty_diagramm_dipol(
		k_oslablenie, 
		&m, &R,
		rows, cols, pages,
		x0, y0, z0,
		delta_x, delta_y, delta_z,
		len, x, y, z, pw_dnp);

	long signal_len = len; // длина сигнала 
	long operator_rows = signal_len; // длина сигнала 
	long operator_cols = rows * cols * pages;


	if (false)
	{

		double ** MA = Alloc2DMat (operator_rows, operator_cols);
		for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены


			double zMin = DBL_MAX;
			double zMax = -DBL_MAX;

			for (long r = 0; r < operator_rows; r++)
			{

				for (long c = 0; c < operator_cols; c++)
				{
					MA[r][c] = m[a1][r][c];		

					if (MA[r][c] > zMax) zMax = MA[r][c];
					if (MA[r][c] < zMin) zMin = MA[r][c];
				}
			}

			printf("zMax = %e\n",zMax);
			printf("zMin = %e\n",zMin);
			char file[512];
			sprintf(file, "%s\\%s_MA_%c.grd", pathout, fn, 'x'+a1);

			printf("%s\n", file);

			SaveAsSurferGrid7(file, 
				operator_rows, operator_cols, 
				0.0, 0.0,
				1.0, 1.0,
				zMin, zMax,
				MA);
		}
		Free2DMat(MA);
	}
		


	double * weighted_D1 = (double*)malloc(operator_cols*sizeof(double));
	double * weighted_D2 = (double*)malloc(operator_cols*sizeof(double));
	double * weighted_cov = (double*)malloc(operator_cols*sizeof(double));
	double * weighted_korr = (double*)malloc(operator_cols*sizeof(double));

	
	// считаем коэффициенты корреляции 



	double ** M1 = Alloc2DMat (3, operator_cols);
	double ** M2 = Alloc2DMat (3, operator_cols);


	for (long c = 0; c < operator_cols; c++) //длина геологической структуры
	{

		long N = 0;
#if 0
		double m1 = 0.0, m2 = 0.0;


		M1[0][c] = 0.0;
		M1[1][c] = 0.0;
		M1[2][c] = 0.0;

		M2[0][c] = 0.0;
		M2[1][c] = 0.0;
		M2[2][c] = 0.0;



		for (long r1 = 0; r1 < operator_rows; r1++){ // длина сигнала по одной антене
			for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены
				for (long r2 = r1+1; r2 < operator_rows; r2++){ // длина сигнала по одной антене
					for (ia2 = 0; ia2 < va_size; ia2++) { a2 = va[ia2]; // перебираем 3 антены
						

						if (all_to_all || fabs
						  ( (R[0][r1][c]*R[0][r1][c])+(R[1][r1][c]*R[1][r1][c])//radi1
						    -
						    (R[0][r2][c]*R[0][r2][c])+(R[1][r2][c]*R[1][r2][c])//radi2
						  ) < min_radius_kvadrat)
						{
							m1 += m[a1][r1][c] * W[a1][r1];
							m2 += m[a2][r2][c] * W[a2][r2];
							N++;

							M1[a1][c] += m[a1][r1][c] * W[a1][r1];
							M2[a2][c] += m[a2][r2][c] * W[a2][r2];

						}

					}
				}
			}
		}
		m1 /= N;
		m2 /= N;

		M1[0][c] /= N;
		M1[1][c] /= N;
		M1[2][c] /= N;

		M2[0][c] /= N;
		M2[1][c] /= N;
		M2[2][c] /= N;

#else


		M1[0][c] = 0.0;
		M1[1][c] = 0.0;
		M1[2][c] = 0.0;

		M2[0][c] = 0.0;
		M2[1][c] = 0.0;
		M2[2][c] = 0.0;
		

		for (long r1 = 0; r1 < operator_rows; r1++){ // длина сигнала по одной антене
			for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены
			
						M1[a1][c] += m[a1][r1][c] * W[a1][r1];
						
				
			}
		}


				for (long r2 = 0; r2 < operator_rows; r2++){ // длина сигнала по одной антене
					for (ia2 = 0; ia2 < va_size; ia2++) { a2 = va[ia2]; // перебираем 3 антены
			
						M2[a2][c] += m[a2][r2][c] * W[a2][r2];
					}
				}
		

		M1[0][c] /= operator_rows;
		M1[1][c] /= operator_rows;
		M1[2][c] /= operator_rows;

		M2[0][c] /= operator_rows;
		M2[1][c] /= operator_rows;
		M2[2][c] /= operator_rows;
#endif
		weighted_D1[c] = 0.0;
		weighted_D2[c] = 0.0;
		weighted_cov[c] = 0.0;
		weighted_korr[c] = 0.0;
		N = 0;

		for (long r1 = 0; r1 < operator_rows; r1++){ // длина сигнала по одной антене
			for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены
				for (long r2 = r1+1; r2 < operator_rows; r2++){ // длина сигнала по одной антене
					for (ia2 = 0; ia2 < va_size; ia2++) { a2 = va[ia2]; // перебираем 3 антены



						if (all_to_all || fabs
						  ( (R[0][r1][c]*R[0][r1][c])+(R[1][r1][c]*R[1][r1][c])//radi1
						    -
						    (R[0][r2][c]*R[0][r2][c])+(R[1][r2][c]*R[1][r2][c])//radi2
						  ) < min_radius_kvadrat)
						{


#if 1
#if 0
							double v1 = m[a1][r1][c] * W[a1][r1] - m1;
							double v2 = m[a2][r2][c] * W[a2][r2] - m2;
#else
							double v1 = m[a1][r1][c] * W[a1][r1] - M1[a1][c];
							double v2 = m[a2][r2][c] * W[a2][r2] - M2[a2][c];
#endif
#else
							double v1 = m[a1][r1][c] * W[a1][r1] - mean[a1];
							double v2 = m[a2][r2][c] * W[a2][r2] - mean[a2];
#endif
							weighted_D1[c] += v1 * v1;
							weighted_D2[c] += v2 * v2;
							weighted_cov[c] += v1 * v2;
							N++;

		//printf("%d %d %d %d %e %e %e %e %e\n", 
		//	a1, a2, r1, r2, v1, v2, v1 * v2, weighted_cov[c]);	
						}

					}
				}
			}
		}
		//рассчитываем коэффициент корреляции k_corr[c] для текущего элемента геологической структуры;
		double sigma_sigma = sqrt(weighted_D1[c] * weighted_D2[c]);
		if (sigma_sigma != 0.0)
			weighted_korr[c] = weighted_cov[c] / sigma_sigma;
		else
			weighted_korr[c] = 0.0;

		printf("wk %ld %ld %ld %e %e %e %e\n", 
			c, operator_cols, N, weighted_cov[c], weighted_D1[c], weighted_D2[c], weighted_korr[c]);	
	
		if (false)
		{

		for (ia1 = 0; ia1 < va_size; ia1++) { a1 = va[ia1]; // перебираем 3 антены


			double zMin = DBL_MAX;
			double zMax = -DBL_MAX;

			for (long r1 = 0; r1 < len; r1++)
			{

				for (long r2 = 0; r2 < len; r2++)
				{
					g[r1][r2] = sqrt(m[a1][r1][c] * m[a1][r2][c]);

		

					if (g[r1][r2] > zMax) zMax = g[r1][r2];
					if (g[r1][r2] < zMin) zMin = g[r1][r2];
				}
			}

			printf("zMax = %e\n",zMax);
			printf("zMin = %e\n",zMin);
			char file[512];
			sprintf(file, "%s\\u002p0008s00_N_%c_%d.grd", pathout, 'x'+a1, c);

			if (c%10 == 0 && false)

			SaveAsSurferGrid7(file, 
				len, len, 
				0.0, 0.0,
				1.0, 1.0,
				zMin, zMax,
				g);
		}
		}		
	}

	char file[512];
	sprintf(file, "%s_weighted_korr", fn);
	SavingResultGrid(pathout, file,
		weighted_korr,
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		only_positive);
if (false)
{

	sprintf(file, "%s_M1x", fn);
	SavingResultGrid(pathout, file,
		M1[0],
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		only_positive);


	sprintf(file, "%s_M1y", fn);
	SavingResultGrid(pathout, file,
		M1[1],
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		false);


	sprintf(file, "%s_M1z", fn);
	SavingResultGrid(pathout, file,
		M1[2],
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		false);



	sprintf(file, "%s_M2x", fn);
	SavingResultGrid(pathout, file,
		M2[0],
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		false);


	sprintf(file, "%s_M2y", fn);
	SavingResultGrid(pathout, file,
		M2[1],
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		false);


	sprintf(file, "%s_M2z", fn);
	SavingResultGrid(pathout, file,
		M2[2],
		rows, cols, pages, 
		x0, y0, z_min,
		delta_x, delta_y, delta_z,				
		to_reduce_x, to_reduce_y, 
		false);
}


	Free2DMat(M1);
	Free2DMat(M2);

	Free2DMat(g);
	Free2DMat(W);

	free(va);

	free(x);
	free(y);
	free(z);

	free(mean);
	free(cov);

	free(weighted_D1);
	free(weighted_D2);

	free(weighted_cov);
	free(weighted_korr);


	//free(sx);
	//free(sy);
	//free(sz);


	return 0;

}


int main(void)

{
	char fn[512];
	for (int n = 1; n <= 14; n++)
	{				
		sprintf(fn, "u002p00%02ds00_N", n);
		weighted_corr_calc(
			"D:\\__dipol\\rovno_u002", 
			"D:\\__dipol\\rovno_u002\\weighted_corr_N",
			fn);
		
	}
	for (int n = 1; n <= 11; n++)
	{				
		sprintf(fn, "u001p00%02ds00_E", n);
		weighted_corr_calc(
			"D:\\__dipol\\rovno_u001", 
			"D:\\__dipol\\rovno_u001\\weighted_corr_E",
			fn);
		
	}
	/*weighted_corr_calc(
		"D:\\__dipol\\rovno_u002p0008", 
		"D:\\__dipol\\rovno_u002p0008",
		"u002p0008s00_N");*/

	return 0;

}

#include "stdafx.h"
#include "gauss_linear_equations.h"

//============ Функции Линейной алгебры ============
vector<double> MatrixProduct(vector<vector<double> > M, vector<double>& x)
{

/*	if (m_size[1] != x.m_length)
	{
		MessageBox(0, "Error using double::MatrixProduct(vdouble& x)\n Size of vector muct be equial to matrix",
			"Error",0);
		ExitProcess(0);
		return vdouble();
	}
	int rows = m_size[0],
		cols = m_size[1];*/

	int rows = M.size();
	int cols;
	for (int i = 0; i < rows; i++)
	{
		cols = M[i].size();
		if(cols != x.size() )
		{
			printf("Error using Matrix product: matrix dimensions mismach \n");
			return vector<double>(0);
		}
	}

	vector<double> y;
	y.resize(rows, 0.0);
//	double *p, *py, *ypD;
//	ypD = y.pD;
	for (int r = 0; r < rows; r++)
	{
//		py = ypD + r;
//		p = pD + r * cols; 
		for (int c = 0; c < cols; c++)
		{
			y[r] += M[r][c] * x[c];
//			*py += *(p + c) * x[c];
//			*py += *(pD + r + c * rows) * x[c];
//			*py += *(pD + c + r * cols) * x[c];
		}
	}
	return y;
}
double ScalarProduct(vector<double>& v1, vector<double>& v2)
{
	if  (v1.size() != v2.size())
	{
		char errstr[1023];
		sprintf (errstr,"%s\n%s\n%d != %d",
			"Error using ScalarProduct(): ",
			"the lengthes of the vectors must be the same",
			v1.size(), v2.size());
//		MessageBox(0,errstr, "Error", 0);
		printf("Error using Scalar product: %s\n", errstr);
//		ExitProcess(0);
		return 0;
	}
//	double *p1, *p2;
//	p2=pD;p1=rhs.pD;
	double _ScalarProduct = 0;
	for(int i=0;i<v1.size();i++)
	{
		_ScalarProduct += v1[i] * v2[i];
	}
	return _ScalarProduct;
}


vector<double> sls_det(vector<vector<double> > M, vector<double> b, double& _det/*, bool PrivateDesigion*/)
{
//	int n = (int)sqrt(m_length);
	int n = M.size();
	int n1, n_1, c, r, i, cc;
	for (i = 0; i < n; i++)
	{
		if(M[i].size() != n)
		{
			printf("Error using sls_det: not square matrix M\n");
			return vector<double>(0);
		}
	}
	double
		//*p, 
		mult, 
		aii;
		//, *prn, *pcn, *pb, *px, *pxc, *pc;
	//=========================================================
	n1 = n+1; n_1 = n-1; _det = 1.0;
	vector<double> x;
	x.resize(n);


	//=========================================================
/*	if (n*n != m_length)
	{
		char strerr[255];
		sprintf(strerr, "Error using det(): n*n (%d) != m_length (%d)\n" , n, m_length);
		MessageBox(0,strerr,"sls_det",0);
		return;
	}*/
	if (n != b.size())
	{
		char strerr[255];
		sprintf(strerr, "Error using det(): n (%d) != b.size (%d)\n", n, b.size);
		//MessageBox(0,strerr,"sls_det",0);
		printf("Error using sls_det: %s", strerr);
		return vector<double>(0);
	}
	//this->Write("d:\\sls_test.txt","wt", "M", false);


	//=========================================================
	vector<int> indexes(n); 
	for(i = 0; i < n; i++) indexes[i] = i;
	bool reindexed = false;
	//=========================================================
//	if ((pb = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n * SD)) == NULL) { MEMORY_ERROR0 }
//	for (i = 0; i < n; i++) { *(pb+i) = *(b.pD+i);}
//	if ((p = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,m_length * SD)) == NULL) { MEMORY_ERROR0 }
//	for (i = 0; i < m_length; i++) { *(p+i) = *(pD+i);}
	if (n == 1 && M[0][0] == 0.0)
	{
		_det = 0.0;
	}
	//=============== Формирование верхнетреугольной матрицы =============
	for ( c = 0; c < n_1; c ++) // Перебираем столбцы с левого по предпоследний
	{
		//WriteMatrix("d:\\sls_test.txt","at","p",n,n,p);
		//WriteMatrix("d:\\sls_test.txt","at","pb",n,1,pb);
		//========== Проверка отсутствия нуля на главной диагонали ======
//		if(*(p + c*n1) == 0) //Если диагональный элемент нулевой
		if(M[c][c] == 0) //Если диагональный элемент нулевой
		{
			r = c + 1;
//			while(*(p + r*n + c) == 0.0  && r < n)
			while(M[r][c] == 0.0  && r < n)
			{
				r++;
			}
			if (r == n)
			{
				cc = c + 1; 
				r = c;
//				while(*(p + r*n + cc) == 0.0 && cc < n)
				while(M[r][cc] == 0.0 && cc < n)
				{
					cc++;
				}
				if ( cc == n)
				{
					_det = 0.0;
					break;
				}
				else
				{
					// Осуществляем перестановку столбцов: c-тый и сс-тый
					double temp;//, *pc, *pcc;
//					pc = p + c;
//					pcc = p + cc;
					for (i = 0; i < n; i++)
					{
//						temp = *(pc + i*n);
//						*(pc + i*n) = *(pcc + i*n);
//						*(pcc + i*n) = temp;
						temp = M[i][c];
						M[i][c] = M[i][cc];
						M[i][cc] = temp;
					}

	
					i = indexes[c];
					indexes[c] = indexes[cc];
					indexes[cc] = i;
					reindexed = true;

					_det *= -1.0;	
				}
				//WriteMatrix("d:\\sls_test.txt","at","после перестановки столбцов \np",n,n,p);
				//WriteMatrix("d:\\sls_test.txt","at","pb",n,1,pb);
			}
			else
			{
				// Осуществляем перестановку строк : r-тую и с-тую
				double temp;
//				pcn = p + c*n + c; 
//				prn = p + r*n + c;
				for (i = c; i < n; i++)
				{
//					temp = *pcn;
//					*pcn = *prn;
//					*prn = temp;
//					pcn++; prn++;
					temp = M[c][i];
					M[c][i] = M[r][i];
					M[r][i] = temp;
//					pcn++; prn++;
				}
				// соответственно переставляем элементы столбца правых частей
//				pcn = pb + c; 
//				prn = pb + r;
//
//					temp = *pcn;
//					*pcn = *prn;
//					*prn = temp;

					temp = b[c];
					b[c] = b[r];
					b[r] = temp;


				_det *= -1.0;
				//WriteMatrix("d:\\sls_test.txt","at","после перестановки строк \np",n,n,p);
				//WriteMatrix("d:\\sls_test.txt","at","pb",n,1,pb);
			}
		}
		//====== Конец проверки отсутствия нуля на главной диагонали ======
//		aii = *(p + c*n1); // Элемент на главной диагонали
		aii = M[c][c]; // Элемент на главной диагонали
//		pcn = p + c*n;
		for (r = c + 1; r < n; r++) // по текущему столбцу вниз, начиная с поддиагонального эл-та
		{
//			prn = p + r*n;
//			mult = *(prn + c) / aii; // Множитель для корректировки r-той строки
			mult = M[r][c] / aii; // Множитель для корректировки r-той строки
			for (i = c; i < n; i++) 
			{
				// Добавляем к r-той строке с-тую, умноженную на корректирующий множитель
//				*(prn + i) -= mult * *(pcn + i);
				M[r][i] -= mult * M[c][i];
			}				
			// Добавляем к r-тому элементу вектора правых частей  строке с-тый, умноженную на тот же множитель
//			*(pb + r) -= mult * *(pb + c);
			b[r] -= mult * b[c];
		}
	}

	if (_det != 0.0)
	{
		for (c = 0; c < n; c++)
//			_det *= *(p + c * n1);
			_det *= M[c][c];
	}
	vector<double> * px;
	if (n > 1)
	{
		if (_det == 0.0 /*|| PrivateDesigion*/)
		{
/*			double *p_, *pn_1;
			int rn;
			// Алгебраическое дополнение к временной матрице
			vdouble Ann = vdouble(n_1*n_1);
			p_ = Ann.pD; i = 0;
			for (r = 0; r < n_1; r++)
			{
				rn = r*n;
				for (c = 0; c < n_1; c++)
				{*(p_ + i) = *(pD + rn + c); i++;}
			}
			vdouble b2 = vdouble(n_1);
			p_ = b2.pD;
			pn_1 = pD + n_1;
			for (r = 0; r < n_1; r++)
				*(p_ + r) = *(b.pD + r) - *(pn_1 + r*n);
			double d;
			vdouble x_;
			Ann.sls_det(b2, x_, d);
			x = (x_, 1.0);*/
		}
		else
		{
			if (reindexed)
			{
//				if ((px = (double*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,n * SD)) == NULL) {MEMORY_ERROR0}
				px = new vector<double>;
				px->resize(n);
			}
			else
			{
//				px = x.pD;
				px = &x;
			}
			for ( c = n_1; c>=0; c--)
			{
//				pxc = px + c;
//				*pxc = *(pb + c) / *(p + c*n1);
				px->operator [] (c) = b[c] / M[c][c];
//				pc = p + c;
				for(r = c - 1; r >=0; r--)
//					*(pb + r) -= *pxc * *(pc + r*n);
					b[r] -= px->operator [] (c) * M[r][c];
			}
			if (reindexed) 
			{
//				double *p_x;
//				p_x = x.pD;
				for( i = 0; i < n; i++)
//					*(p_x + i) = *(px + indexes[i]);
					x[i] = px->operator [] (indexes[i]);
//				HeapFree(GetProcessHeap(), 0,px);
				delete px;
			}
		}
	}
	if (n == 1)
	{
		if (_det != 0)
		{
//			x[0] = *pb / *p;
			x[0] = b[0] / M[0][0];
		}
		else
		{
			fprintf(stderr, "Error sls_det() : _det = 0 and n = 1;\n");
			x = vector<double>(0);
		}
	}
//	HeapFree(GetProcessHeap(), 0,p);HeapFree(GetProcessHeap(), 0,pb);
//	vdouble delta = this->MatrixProduct(x)-b;
	vector<double> delta = MatrixProduct(M,x);
	if (delta.size() == b.size() )
	{
		double SquareSum = 0.0;
		for (int i = 0; i < b.size(); i++)
		{
			delta[i] -= b[i];
			SquareSum += delta[i] * delta[i];
		}
		if (log10(SquareSum) > (-6) ) //допустимая точность шестой знак после запятой
		{
			char str[255];
			sprintf(str,"log10(delta.SquareSum()) = %lf", log10(SquareSum));
		//	MessageBox(0,str,"Warning: sls_det",0);
			printf("Warning: sls_det: %s", str);
		}
	}
//	if (log10(delta.SquareSum()) > (-6) ) //допустимая точность шестой знак после запятой
	//this->MatrixProduct(x).Write("d:\\sls_test.txt","at","test b");
	//(this->MatrixProduct(x)-b).Write("d:\\sls_test.txt","at","test b");
	return x;
}

bool 
#if USE_CONTOUR
fill_grid_with_contour
#else
fill_grid_without_contour
#endif
(Grid * grid, 
			   std::vector<geometry2D::Point>& vs, 
			   vector<double>& x, vector<double>& y, vector<double>& z,
			   double& min_z, double& max_z, griddata_3_param * param)
{
	printf("Start of filling the grid? basing on %u %u %u %u input points\n", vs.size(), x.size(), y.size(), z.size());
#if FILL_GRID_TEST
	bool test = true;
#endif
	// вычисляем триангуляцию Делоне
	Dictionary<EdgeEx*> * out_edges = new Dictionary<EdgeEx*>(edgeCmpEx);
	List<PolygonEx*> * trias = delaunayTriangulateEx(vs, out_edges);

#if FILL_GRID_TEST
	if (test)
	{
		size_t index = 0;
		for (trias->first(); !trias->isHead(); trias->next(),index++)
		{
			trias->val()->index = index;
		}

		char bln_file[1024];
		TCHAR filter[] =   
			TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
			TEXT("All Files (*.*)\0*.*\0");
		
		sprintf(bln_file, "after_delaunay_trias");
		DWORD nFilterIndex = 0;
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SavePolygonesExAsBln(trias, bln_file);
		}
		sprintf(bln_file, "after_delaunay_out_edges");
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SaveEdgesExAsBln(*out_edges, bln_file);
		}
	}
#endif

	int ftf = 2;
	if (param)
	{
		ftf = param->ftf;
	}
	else
	{
		cout << "enter filtering of triangulation flag [0,1,2]" << endl;
		cin >> ftf;
	}

    // Фильтруем полигоны от "плохих" краевых треугольников		
	switch (ftf)
	{
	case 1:
		FilteringPolygonesEx1(trias, out_edges);
		break;
	case 2:
		FilteringPolygonesEx2(trias, out_edges);
		break;
	}

#if FILL_GRID_TEST
	if (test)
	{
		char bln_file[1024];
		TCHAR filter[] =   
			TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
			TEXT("All Files (*.*)\0*.*\0");
		
		sprintf(bln_file, "after_filtering_trias");
		DWORD nFilterIndex = 0;
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SavePolygonesExAsBln(trias, bln_file);
		}
		sprintf(bln_file, "after_filtering_out_edges");
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SaveEdgesExAsBln(*out_edges, bln_file);
		}
	}
#endif

#if USE_CONTOUR
    // Получаем замкнутый контур внешней границы
	List<EdgeEx*> * contour = GetContourOfPolygonesEx2(trias);

	if (!contour)
	{
		MessageBox(0, "Error: !contour", "fill_grid", MB_OK);
		return false;
	}

	// Из каждой вершины внешней границы проводим вовне биссектрисы
	double len_biss;
	if (param)
	{
		switch(param->m_len_biss_type)
		{
                case griddata_3_param_len_biss_type_user_defined:
			len_biss = param->len_biss;
			break;
                case griddata_3_param_len_biss_type_min_edges_len:
			len_biss = GetMinLenOfEdges(contour);
			break;
                case griddata_3_param_len_biss_type_mean_edges_len:
			len_biss = GetMeanLenOfEdges(contour);
			break;
                case griddata_3_param_len_biss_type_median_edges_len:
			len_biss = GetMedianLenOfEdges(contour);
			break;
                case griddata_3_param_len_biss_type_max_edges_len:
			len_biss = GetMaxLenOfEdges(contour);
			break;
		}
	}
	else
	{
		int _len_bis_type = 0;
		cout << "enter bissectriss length type: [0,1,2,3,4]" << endl;
		cout << "0 - user defined" << endl;
		cout << "1 - min_edges_len" << endl;
		cout << "2 - min_edges_len" << endl;
		cout << "3 - min_edges_len" << endl;
		cout << "4 - max_edges_len" << endl;
		cin >> _len_bis_type;
		switch(_len_bis_type)
		{
                case griddata_3_param_len_biss_type_user_defined:
			{
				cout << "enter bissectriss length" << endl;
				cin >> len_biss;
			}
			break;
                case griddata_3_param_len_biss_type_min_edges_len:
			len_biss = GetMinLenOfEdges(contour);
			break;
                case griddata_3_param_len_biss_type_mean_edges_len:
			len_biss = GetMeanLenOfEdges(contour);
			break;
                case griddata_3_param_len_biss_type_median_edges_len:
			len_biss = GetMedianLenOfEdges(contour);
			break;
                case griddata_3_param_len_biss_type_max_edges_len:
			len_biss = GetMaxLenOfEdges(contour);
			break;
		}
	}
	List<EdgeEx*> * biss = MakeBissectrissToContour(contour, len_biss);

#if FILL_GRID_TEST
	if (test)
	{
		char bln_file[1024];
		TCHAR filter[] =   
			TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
			TEXT("All Files (*.*)\0*.*\0");
		
		DWORD nFilterIndex = 0;

		sprintf(bln_file, "biss0");
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SaveEdgesAsBln(biss, bln_file);
		}
	}
#endif

	//biss = CorrectBissectriss2(biss);

	// Вокруг контура внешней границы, базируясь на внешних биссектриссах формируем массив экстраполяционных полигонов
	vector<geometry2D::Point> * poly_contour_base_points = new vector<geometry2D::Point>; // список базовых точек для экстраполяционных полигонов
	List<PolygonEx*> * poly_contour = GetContourOfExtraPolygones(contour, biss, poly_contour_base_points, 1);

#endif /*USE_CONTOUR*/
	// Итак, мы имеем N треугольников экстраполяции
	int N_trias = trias->length();
printf("N_trias = trias->length() %d\n", N_trias );
	// построенных на n точках
	// int n = x.size();
	// А также L полигонов экстраполяционных
#if USE_CONTOUR
	int N_contour = poly_contour->length();
printf("N_contour = poly_contour->length() %d\n", N_contour );
#endif
	// каждый треугольник мы будем аппроксимировать уравнением (1):
	// f(x,y):= c0 + c1*(x-xj)   + c2*(y-yj)          + 
	//				 c3*(x-xj)^2 + c4*(x-xj)*(y-yj)   + c5*(y-yj)^2        + 
	//				 c6*(x-xj)^3 + c7*(x-xj)^2*(y-yj) + c8*(x-xj)*(y-yj)^2 + c9*(y-yj)^3;

	// diff(f(x,y),x)   = c1+2*c3*(x-xj)+c4*(y-yj)+3*c6*(x-xj)^2+2*c7*(x-xj)*(y-yj)+c8*(y-yj)^2
	// diff(f(x,y),y)   = c2+c4*(x-xj)+2*c5*(y-yj)+c7*(x-xj)^2+2*c8*(x-xj)*(y-yj)+3*c9*(y-yj)^2
	// diff(f(x,y),x,x) = 2*c3+6*c6*(x-xj)+2*c7*(y-yj)
	// diff(f(x,y),y,y) = 2*c5+2*c8*(x-xj)+6*c9*(y-yj)
	// diff(f(x,y),x,y) = c4+2*c7*(x-xj)+2*c8*(y-yj)

	// Итак у нас 10 * N + 10 * L неизвестных коэффициентов
	int cols;
	//int order = 3;
	int order_t = 3;
//#if USE_CONTOUR	
	int order_c = 3;
//#endif
	//double row_weight = 1.0;
	double alpha_t0 = 0.1;
	double alpha_t1 = 0.1;					
	double alpha_tn = 0.1;	
#if USE_CONTOUR	
	double alpha_c0 = 0.1;
	double alpha_c1 = 0.1;					
	double alpha_cn = 0.1;		
#endif
	long dij = 1;



	if (param)
	{
		order_t = param->order_t;
#if USE_CONTOUR	
		order_c = param->order_c;
#endif
		//row_weight = param->row_weight;
		alpha_t0 = param->alpha_t0;
		alpha_t1 = param->alpha_t1;
		alpha_tn = param->alpha_tn;		
#if USE_CONTOUR	
		alpha_c0 = param->alpha_c0;
		alpha_c1 = param->alpha_c1;
		alpha_cn = param->alpha_cn;
#endif
		dij = param->dij;
	}
	else
	{
		cout << "enter order_t [1, 2, 3, 4] of trias interpolation" << endl;
		cin >> order_t;

		if (order_t > 1)
		{
			cout << "enter alpha_t0 [0.1] regularization koefficient for 0 pw koefficients" << endl;
			cin >> alpha_t0;
			cout << "enter alpha_t1 [0.0] regularization koefficient for 1 pw koefficients" << endl;
			cin >> alpha_t1;
			cout << "enter alpha_tn [0.1] regularization koefficient for 1 pw koefficients" << endl;
			cin >> alpha_tn;
		}
#if USE_CONTOUR	

		cout << "enter order_c [1, 2, 3, 4] of contour polygons interpolation" << endl;
		cin >> order_c;

		if (order_c > order_t)
		{
			order_c = order_t;
		}

		if (order_c > 1)
		{
			cout << "enter alpha_c0 [0.1] regularization koefficient for 0 pw koefficients" << endl;
			cin >> alpha_c0;
			cout << "enter alpha_c1 [0.0] regularization koefficient for 1 pw koefficients" << endl;
			cin >> alpha_c1;
			cout << "enter alpha_cn [0.1] regularization koefficient for 1 pw koefficients" << endl;
			cin >> alpha_cn;
		}
#endif
		cout << "enter dij for filtering [..., -4, -3, -2, -1, 0, 1, 2, 3, 4, ...]" << endl;
		cin >> dij;
	}

	finite_element_par fep;
	finite_element_par fepbc;
	if (param)
	{
		fep = param->fep;
		fepbc = param->fepbc;
	}
	else
	{
		fep.add_non_fault = true;
		fep.alpha_non_fault = 1.0;
		fep.add_first_der_n = true;
		fep.alpha_der_n = 0.1;
		fep.add_first_der_x_or_y = false;
		fep.add_first_der_x = false;
		fep.add_first_der_y = false;
		fep.alpha_der_xy = 0.1;

		cout << "fep.alpha_der_n [0.1] of finite element parameters" << endl;
		cin >> fep.alpha_der_n;

		
		if (false)
		{

			cout << "add_non_fault [0, 1] of finite element parameters" << endl;
			cin >> fep.add_non_fault;

			cout << "add_first_der_n [0, 1] of finite element parameters" << endl;
			cin >> fep.add_first_der_n;

			cout << "add_first_der_x_or_y [0, 1] of finite element parameters" << endl;
			cin >> fep.add_first_der_x_or_y;

			if (!fep.add_first_der_x_or_y)
			{
				cout << "add_first_der_x [0, 1] of finite element parameters" << endl;
				cin >> fep.add_first_der_x;

				cout << "add_first_der_y [0, 1] of finite element parameters" << endl;
				cin >> fep.add_first_der_y;
			}
		}


		fepbc.add_non_fault = true;
		fepbc.alpha_non_fault = 0.5;
		fepbc.add_first_der_n = false;
		fepbc.alpha_der_n = 0.1;
		fepbc.add_first_der_x_or_y = false;
		fepbc.add_first_der_x = false;
		fepbc.add_first_der_y = false;
		fepbc.alpha_der_xy = 0.1;

		cout << "fepbc.alpha_non_fault [0.5] of boundary finite element parameters" << endl;
		cin >> fepbc.alpha_non_fault;

		cout << "fepbc.add_first_der_n [0, 1] of boundary finite element parameters" << endl;
		cin >> fepbc.add_first_der_n;

		if(fepbc.add_first_der_n)
		{
			cout << "fepbc.alpha_der_n [0.1] of boundary finite element parameters" << endl;
			cin >> fepbc.alpha_der_n;
		}

	}
	//size_t nk = 0;
	size_t nk_t = 0;
	size_t nk_c = 0;
	switch(order_t)
	{
	case 1:
		nk_t = 3;
		break;
	case 2:
		nk_t = 6;
		break;
	case 3:
		nk_t = 10;
		break;
	case 4:
		nk_t = 15;
		break;
	}
#if USE_CONTOUR	
	switch(order_c)
	{
	case 1:
		nk_c = 3;
		break;
	case 2:
		nk_c = 6;
		break;
	case 3:
		nk_c = 10;
		break;
	case 4:
		nk_c = 15;
		break;
	}
#endif
	cols = (int)nk_t * N_trias
#if USE_CONTOUR	
		+ (int)nk_c * N_contour
#endif
		;
	vector<double> sol(cols, 0.0); // вектор решения
	vector<double> valpha(cols, 0.0); // вектор регуряризационных коэффициентов

	List<PolygonEx*> poly;
	// список базовых точек для триангуляционных треугольников
	vector<geometry2D::Point> base_points;
	vector<double> base_points_z;
	size_t index = 0;
	for (trias->first(); !trias->isHead(); trias->next(),index++)
	{
		trias->val()->index = index;
		poly.append(trias->val());

                PolygonEx * p = trias->val();

		geometry2D::Point pt_intersect; bool pt_intersect_calculed = false;

		List<Edge*> * edges_biss = new List<Edge*>;

		int i = 0;
		if (i < p->size())
		{		
                        Edge e_1 = p->edge(); p->advance(CLOCKWISE); i++;
			if (i < p->size())
			{
                                Edge e_2 = p->edge();	p->advance(CLOCKWISE); i++;
                                AppendBissectriss(edges_biss, &e_1, &e_2, 1.0);
				if (i < p->size())
				{
                                        Edge e_3 = p->edge();	p->advance(CLOCKWISE); i++;
                                        AppendBissectriss(edges_biss, &e_2, &e_3, 1.0);
				}
			}
		}

		edges_biss->first();

		if( !edges_biss->isHead() )
		{
			Edge* b_1 = edges_biss->val();
			edges_biss->next();
			if ( !edges_biss->isHead() )
			{
				Edge* b_2 = edges_biss->val();
				double f;
				b_1->intersect(*b_2, f);
				pt_intersect = b_1->point(f);
				pt_intersect_calculed = true;
			}
		}
        
		delete edges_biss;

		if (pt_intersect_calculed)            
			base_points.push_back(pt_intersect);
		else
		{
			base_points.push_back(trias->val()->point());
			//MessageBox(0, "!pt_intersect_calculed", "fill_grid", MB_OK);
			printf("fill_grid\t!pt_intersect_calculed\n");
		}

		// инициализируем линейные коэффициенты
		// линейная интерполяция - первое приближение
		//sol[index*10+0];//c0
		//sol[index*10+1];//c1
		//sol[index*10+2];//c2
			
		geometry2D::Point ptj = base_points[index];
		size_t index_10 = index*nk_t;

			
		vector<sparse_row> m; 
		// и вектор правых частей 
		vector<double> b;


		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			geometry2D::Point pt = p->point();

			if (pt != ptj && pt.index > -1 && pt.index < (int)z.size())
			{			
				// добавляем строку в уравнение
				
				sparse_row row; 
				row.clear();

				row.put(0, 1.0);//с0
				row.put(1, pt.x - ptj.x);//с1
				row.put(2, pt.y - ptj.y);//с2

				m.push_back(row);
				b.push_back(z[pt.index]);
				
			}
		}

		print_slau(m,b,"slau");


		vector<double> xx;
		if (lesgausssolve_find_max(m, (int)m.size(), 3, b, xx, 0.0))
		{
			sol[index_10+0] = xx[0];//c0
			sol[index_10+1] = xx[1];//c1
			sol[index_10+2] = xx[2];//c2

			valpha[index_10+0] = alpha_t0;//c0
			valpha[index_10+1] = alpha_t1;//c1
			valpha[index_10+2] = alpha_t1;//c2

			for (size_t nk = 3; nk < nk_t; nk++)
				valpha[index_10+nk] = alpha_tn;//cn

#if 0
			printf("[%f %f %f]\n", xx[0], xx[1], xx[2]);
			vector<double> bb(m.size());
			for (size_t r = 0; r < m.size(); r++)
			{
				bb[r] = m[r].ScalarProduct(xx);
				printf("bb[%u] = %f b[%u] = %f delta = %e\n", r, bb[r], r, b[r], bb[r]-b[r]);
			}
#endif
		}
		else
		{
			printf("system was not solved\n");
		}
		double bpz = sol[index_10+0] ;//+ sol[index_10+1] * ptj.x + sol[index_10+2] * ptj.y;
		base_points_z.push_back(bpz);
	}
#if USE_CONTOUR
	vector<geometry2D::Point>::iterator itp;
	List<EdgeEx*> * boundary_edges = new List<EdgeEx*>;
	for (contour->first(), poly_contour->first(), itp = poly_contour_base_points->begin(); 
		!contour->isHead() && !poly_contour->isHead() && itp != poly_contour_base_points->end(); 
		contour->next(), poly_contour->next(), itp++, index++)
	{
		poly_contour->val()->index = index;
		base_points.push_back((*itp));
		poly.append(poly_contour->val());

		//size_t index_10 = index*nk;
		size_t index_10 = N_trias*nk_t + (index-N_trias)*nk_c;

		EdgeEx * ex = contour->val();
		// указатель на полигон контурный
		PolygonEx * pc = ex->LeftPolygon();
		for (int i = 0; i < pc->size(); i++)
		{
			pc->advance(CLOCKWISE);
			EdgeEx * e = new EdgeEx(pc->edge());
			if (e->org != ex->org && 
				e->org != ex->dest && 
				e->dest != ex->org && 
				e->dest != ex->dest)
			{
				e->RightPolygon(pc);
				e->LeftPolygon(NULL);
				boundary_edges->append(e);
			}

		}
		// указазатель на соответствующий внутренний треугольник
		PolygonEx * tr = ex->RightPolygon();
		// ищем в треугольнике противоположную точку
		geometry2D::Point tr_pt;
		for (int i = 0; i < tr->size(); i++)
		{
			tr->advance(CLOCKWISE);
			geometry2D::Point pt = tr->point();
			if (pt != ex->org && pt != ex->dest)
			{	
				tr_pt = pt;				
			}
		}

		if (tr_pt.index > -1 && tr_pt.index < (int)z.size()
			&&
			ex->dest.index > -1 && ex->dest.index < (int)z.size())
		{						
			vector<sparse_row> m; 
			// и вектор правых частей 
			vector<double> b;
			// добавляем строку в уравнение
			sparse_row row; 

			// базовая точка != ex->org

			// tr_pt.x

			row.clear();        
			row.put(0, 1.0);//с0
			row.put(1, tr_pt.x - (*itp).x);//с1
			row.put(2, tr_pt.y - (*itp).y);//с2		
			m.push_back(row);b.push_back(z[tr_pt.index]);

			// ex->dest

			row.clear();        
			row.put(0, 1.0);//с0
			row.put(1, ex->dest.x - (*itp).x);//с1
			row.put(2, ex->dest.y - (*itp).y);//с2		
			m.push_back(row);b.push_back(z[ex->dest.index]);

			// ex->org
			
			row.clear();        
			row.put(0, 1.0);//с0
			row.put(1, ex->org.x - (*itp).x);//с1
			row.put(2, ex->org.y - (*itp).y);//с2		
			m.push_back(row);b.push_back(z[ex->org.index]);
			
			vector<double> xx;
			if (lesgausssolve_find_max(m, (int)m.size(), 3, b, xx, 0.0))
			{
				sol[index_10+0] = xx[0];//c0
				sol[index_10+1] = xx[1];//c1
				sol[index_10+2] = xx[2];//c2

				valpha[index_10+0] = alpha_c0;//c0
				valpha[index_10+1] = alpha_c1;//c1
				valpha[index_10+2] = alpha_c1;//c2

				for (size_t nk = 3; nk < nk_c; nk++)
					valpha[index_10+nk] = alpha_cn;//cn

#if 0
				printf("[%f %f %f]\n", xx[0], xx[1], xx[2]);
				vector<double> bb(m.size());
				for (size_t r = 0; r < m.size(); r++)
				{
					bb[r] = m[r].ScalarProduct(xx);
					printf("bb[%u] = %f b[%u] = %f delta = %e\n", r, bb[r], r, b[r], bb[r]-b[r]);
				}
#endif
			}
			else
			{
				printf("system was not solved\n");
			}
		}
		double bpz = sol[index_10+0] ;//+ sol[index_10+1] * (*itp).x + sol[index_10+2] * (*itp).y;
		base_points_z.push_back(bpz);
	}

#if 0
	for( biss->first(); !biss->isHead(); biss->next())
	{
		EdgeEx* ex = biss->val();

		//test
		PolygonEx * p1 = ex->LeftPolygon();
		PolygonEx * p2 = ex->RightPolygon();
		if(p1 && p2)
		{
			size_t index1 = p1->index < p2->index ? p1->index : p2->index;
			size_t index2 = p1->index < p2->index ? p2->index : p1->index;
			printf ("biss %u %u\n", index1, index2);
		}
	}
#endif


#if FILL_GRID_TEST
	if (test)
	{
		char bln_file[1024];
		TCHAR filter[] =   
			TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
			TEXT("All Files (*.*)\0*.*\0");
		
		sprintf(bln_file, "poly_contour");
		DWORD nFilterIndex = 0;
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SavePolygonesExAsBln(poly_contour, bln_file);
		}
		sprintf(bln_file, "contour");
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SaveEdgesAsBln(contour, bln_file);
		}
		sprintf(bln_file, "biss");
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			SaveEdgesAsBln(biss, bln_file);
		}
	}
#endif

#endif

	if (order_t > 1)
	{
		// Наша цель составить матрицу с числом строк S
		vector<sparse_row> M; 
		// и вектор правых частей 
		vector<double> B;
		// Для каждого треугольника будем подставлять координаты двух дополнительных точек
		//
		for (trias->first(); 
			!trias->isHead(); 
			trias->next())
		{
			PolygonEx * p = trias->val();
			AddRowsToEquation_(N_trias, order_t, order_c, nk_t, nk_c/*, row_weight*/, M, cols, B, z, p, base_points);
		}

		printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));
	#if USE_CONTOUR
		// Для каждого экстраполяционного треугольника подставим координаты одной дополнительной точки
		for (poly_contour->first(); 
			!poly_contour->isHead(); 
			poly_contour->next())
		{
			PolygonEx * p = poly_contour->val();
			AddRowsToEquation_(N_trias, order_t, order_c, nk_t, nk_c/*, row_weight*/, M, cols, B, z, p, base_points);
		}

	#endif
		
		// число точных уравнений
		size_t prec_eqns = M.size();
		

		printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));


		// каждое ребро треугольника и экстраполяционного 
		// полигона позволяет ввести параметрическую систему 
		// координат. Каждое ребро начинается в начальной точке 
		// (x_org, y_org)
		// и заканчивается в конечной точке
		// (x_dest, y_dest). 
		// Параметрическая переменная t изменяется 
		// при движении по прямой вдоль ребра т.о., 
		// что t=0.0 в точке начала ребра и t = 1.0 
		// в точке конца ребра
		// x(t) = x_org + (x_dest - x_org)*t
		// y(t) = y_org + (y_dest - y_org)*t

		// теперь наша задача записать такие дополнительные уравнения, 
		// которые означают непрерывность ф-ции вдоль каждого ребра 
		// и вдоль каждого экстраполяционного луча
		// А также непрерывность её первой и второй производной

		// f(t) := 
		// f(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
		// zj+
		// c1*(x_org-xj+(x_dest-x_org)*t)+
		// c2*(y_org-yj+(y_dest-y_org)*t)+
		// c3*(x_org-xj+(x_dest-x_org)*t)^2+
		// c4*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
		// c5*(y_org-yj+(y_dest-y_org)*t)^2+
		// c6*(x_org-xj+(x_dest-x_org)*t)^3+
		// c7*(x_org-xj+(x_dest-x_org)*t)^2*(y_org-yj+(y_dest-y_org)*t)+
		// c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)^2+
		// c9*(y_org-yj+(y_dest-y_org)*t)^3


		// diff_x(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
		// c1+
		// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
		// c4*(y_org-yj+(y_dest-y_org)*t)+
		// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
		// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
		// c8*(y_org-yj+(y_dest-y_org)*t)^2
	    
		// diff_y(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
		// c2+
		// c4*(x_org-xj+(x_dest-x_org)*t)+
		// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
		// c7*(x_org-xj+(x_dest-x_org)*t)^2+
		// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
		// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

		// diff_xx(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
		// 2*c3+
		// 6*c6*(x_org-xj+(x_dest-x_org)*t)+
		// 2*c7*(y_org-yj+(y_dest-y_org)*t)
	    
		// diff_yy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
		// 2*c5+
		// 2*c8*(x_org-xj+(x_dest-x_org)*t)+
		// 6*c9*(y_org-yj+(y_dest-y_org)*t)

		// diff_xy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
		// c4+
		// 2*c7*(x_org-xj+(x_dest-x_org)*t)+
		// 2*c8*(y_org-yj+(y_dest-y_org)*t)

		// перебираем все внутренние рёбра
//		EdgeEx * ex_;
		List<EdgeEx *> *out_edges_ = new List<EdgeEx *>;

		out_edges->inorder(AppendToList, out_edges_);
		printf("inordered\n");

	#if FILL_GRID_TEST
		if (test)
		{
			char bln_file[1024];
			TCHAR filter[] =   
				TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
				TEXT("All Files (*.*)\0*.*\0");
			
			sprintf(bln_file, "after_filtering_out_edges_");
			DWORD nFilterIndex = 0;
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				SaveEdgesAsBln(out_edges_, bln_file);
			}
		}
	#endif

#if FILL_GRID_TEST

		char bln_file[1024];
		TCHAR filter[] =   
			TEXT("Bln triangulation file file (*.bln)\0*.bln\0")
			TEXT("All Files (*.*)\0*.*\0");

		FILE * bln_non_added = NULL;
		sprintf(bln_file, "non_added_equations2_to_edges");
		DWORD nFilterIndex = 0;
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			bln_non_added = fopen(bln_file, "wt");
		}



		FILE * bln_added = NULL;
		sprintf(bln_file, "added_equations2_to_edges");
		if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
		{
			bln_added = fopen(bln_file, "wt");
		}
#endif


		for( out_edges_->first(); !out_edges_->isHead(); out_edges_->next())
		{
			EdgeEx* ex = out_edges_->val();
			if(!AddRowsToEquation2_(N_trias, order_t, order_c, nk_t, nk_c, M, cols, B, z, ex, base_points, fep))
			{
#if !USE_CONTOUR
				AddBoundaryConditionRowsToEquation2_(N_trias, order_t, order_c, nk_t, nk_c, M, cols, B, z, sol, ex, base_points, fepbc);
#endif
#if FILL_GRID_TEST
				if (bln_non_added)
				{
					save_Edge(ex, bln_non_added);
				}
			}
			else
			{
				if (bln_added)
				{
					save_Edge(ex, bln_added);
				}
#endif
			}
		}

		printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));
	#if USE_CONTOUR
		// перебираем все рёбра контура
		for( contour->first(); !contour->isHead(); contour->next())
		{
			EdgeEx* ex = contour->val();
			if(!AddRowsToEquation2_(N_trias, order_t, order_c, nk_t, nk_c, M, cols, B, z, ex, base_points, fep))
			{

#if FILL_GRID_TEST
				if (bln_non_added)
				{
					save_Edge(ex, bln_non_added);
				}
			}
			else
			{
				if (bln_added)
				{
					save_Edge(ex, bln_added);
				}
#endif
			}
		}
		printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));

		// перебираем все биссектриссы
		for( biss->first(); !biss->isHead(); biss->next())
		{
			EdgeEx* ex = biss->val();
			if(!AddRowsToEquation2_(N_trias, order_t, order_c, nk_t, nk_c, M, cols, B, z, ex, base_points, fep))
			{							
#if FILL_GRID_TEST
				if (bln_non_added)
				{
					save_Edge(ex, bln_non_added);
				}
			}
			else
			{
				if (bln_added)
				{
					save_Edge(ex, bln_added);
				}
#endif
			}
		}
		for( boundary_edges->first(); !boundary_edges->isHead(); boundary_edges->next())
		{
			EdgeEx* ex = boundary_edges->val();
			AddBoundaryConditionRowsToEquation2_(N_trias, order_t, order_c, nk_t, nk_c, M, cols, B, z, sol, ex, base_points, fepbc);
		}
#if FILL_GRID_TEST
		if(bln_non_added)fclose(bln_non_added);
		if(bln_added)fclose(bln_added);
#endif
	#endif
		size_t real_cols_number = GetRealColsNumber(M, cols);
		printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), real_cols_number);
		
		if ((int)real_cols_number < cols)
		{
			char err[2048];
			sprintf(err, "real_cols_number %u < cols %u", real_cols_number, cols);
			MessageBox(0, err, "fill_grid", MB_OK);
		if (!SLAU (M, cols, B, false, false, 100, sol, true)) return false;
			return false;
		}
	//MessageBox(0,"","",0);
	#if FILL_GRID_TEST
		if (test)
		{
			char bln_file[1024];
			TCHAR filter[] =   
				TEXT("Dat (*.dat)\0*.dat\0")
				TEXT("All Files (*.*)\0*.*\0");
			
			sprintf(bln_file, "base_points_z");
			DWORD nFilterIndex = 0;
			if (SaveFileDlg(0, bln_file, filter, nFilterIndex) == S_OK)
			{
				FILE * stream = fopen(bln_file, "wt");
				if (stream)
				{
					for (size_t i=0; i < base_points_z.size(); i++)
					{

						fprintf(stream, "%f,%f,%f\n", 
							base_points[i].x,
							base_points[i].y,
							base_points_z[i]);
					}
					fclose(stream);
				}
			}
		}
	#endif


		int slau_method = 0;
		if (param)
		{	
			slau_method = param->slau_method;
		}
		else
		{
			cout << "enter slau_method 0 - SLAU9 1 - SLAU_excl" << endl;
			cin >> slau_method;
		}

		switch (slau_method)
		{
		case 0:
			if (!SLAU9(M, cols, valpha, B, sol))
			{
				Tichonov(cols, M, B, sol, valpha);
			}
			break;
		case 1:
			if (!SLAU_excl(prec_eqns,
				M,
				cols, valpha,
				B,
				sol))
			{
				//if (!SLAU9(M, cols, valpha, B, sol))
				//{
					Tichonov(cols, M, B, sol, valpha);
				//}
			}
			break;
		case 2:
			Tichonov(cols, M, B, sol, valpha);
			break;

		}




		//Tichonov(M, cols, B, x, true);
		//if (!SLAU3(M, cols, B, sol)){}
		//if (!SLAU4(M, cols, nk, 2, B, sol)){}
		//if (!SLAU10(M, cols, valpha, B, sol)){}
	//	if (!SLAU9(M, cols, valpha, B, sol)){}
		//if (!SLAU8(M, cols, 0.1, B, sol)){}
		//if (!SLAU6(M, cols, nk, base_points_z, B, sol)){}
		//if (!SLAU7(M, cols, nk, base_points_z, B, sol)){}
		//if (!SLAU5(M, cols, B, sol)){}
		//if (!SLAU (M, cols, B, sol)) return false;

#if SPARSE_ROW_EX
		if (false)
		{	
			// Наша цель составить матрицу с числом строк S
			vector<sparse_row> M2; 
			// и вектор правых частей 
			vector<double> B2;
			for (size_t r = 0; r < M.size(); r++)
			{
				if (M[r]._order == 0)
				{
					M2.push_back(M[r]);
					B2.push_back(B[r]);
				}
			}
			if (!SLAU (M2, cols, B2, sol)) return false;
		}
#endif
		//SLAU2(M, cols, B, sol);
		///SLAU_block(M, cols, 9, B, sol);
	}


	//*********************************************************************************
	//*********************************************************************************
	//*********************************************************************************
	//*********************************************************************************
	//*********************************************************************************
	geometry2D::Point a;
	double z_value;
	poly.first();

	if(grid)
	{
		if (dij == 0)
		{
			double min_quad_size = min(grid->gridSection.xSize, grid->gridSection.ySize);
			for (long ii = 0; ii < grid->gridSection.nCol; ii++)
			{
				printf("ii = %ld m = %ld\n", ii, grid->gridSection.nCol);
				double x_i = grid->gridSection.xLL + ii*grid->gridSection.xSize;
				for (long jj = 0; jj < grid->gridSection.nRow; jj++)
				{
					double y_j = grid->gridSection.yLL + jj*grid->gridSection.ySize;

					a.x = x_i;
					a.y = y_j;
						
					geometry2D::PolygonEx* p = NULL;
					bool found = false;

					for (int _i = 0; _i < poly.length(); poly.next() )
					{
						if(!poly.isHead())
						{
							p = poly.val();

							int result = pointInPolygon(a, *p);

							if (result == INSIDE || result == BOUNDARY)
							{
								found = true;
								break;
							}
							_i++;
						}
					}


					if (p && found)
					{
						z_value = GetValue_(N_trias, order_t, order_c, nk_t, nk_c, sol, cols, z, a, p, base_points);
						if (max_z < z_value) max_z = z_value;
						if (min_z > z_value) min_z = z_value;
					}
					else
						z_value = BLANK_VALUE;

					// полученное значение z_value записываем в грид
					grid->gridSection.z[jj][ii] = z_value;
				}
			}
		}
		else
		{
			bool as_ma = true;
			if (dij < 0)
			{
				dij *= -1;
				as_ma = false;
			}

			point_polygon ** pp = Alloc2DMat<point_polygon>(grid->gridSection.nRow, grid->gridSection.nCol);
			double min_quad_size = min(grid->gridSection.xSize, grid->gridSection.ySize);
			for (long ii = 0; ii < grid->gridSection.nCol; ii++)
			{
				printf("ii = %ld m = %ld\n", ii, grid->gridSection.nCol);
				double x_i = grid->gridSection.xLL + ii*grid->gridSection.xSize;
				for (long jj = 0; jj < grid->gridSection.nRow; jj++)
				{
					double y_j = grid->gridSection.yLL + jj*grid->gridSection.ySize;

					a.x = x_i;
					a.y = y_j;

					pp[jj][ii].a = a;
						
					geometry2D::PolygonEx* p = NULL;
					bool found = false;

					for (int _i = 0; _i < poly.length(); poly.next() )
					{
						if(!poly.isHead())
						{
							p = poly.val();

							int result = pointInPolygon(a, *p);

							if (result == INSIDE || result == BOUNDARY)
							{
								found = true;
								break;
							}
							_i++;
						}
					}

					if (p && found)
					{
						pp[jj][ii].p = p;
					}
					else
						pp[jj][ii].p = NULL;
				}
			}
			for (long ii = 0; ii < grid->gridSection.nCol; ii++)
			{
				printf("ii = %ld m = %ld\n", ii, grid->gridSection.nCol);
				for (long jj = 0; jj < grid->gridSection.nRow; jj++)
				{
					if (pp[jj][ii].p)
					{
						size_t nnn = 0;
						z_value = 0.0;
						for (long iii = ii-dij; iii <= ii+dij; iii++)
						{
							for (long jjj = jj-dij; jjj <= jj+dij; jjj++)
							{
								if (iii > 0 && jjj > 0 && iii < grid->gridSection.nCol && jjj < grid->gridSection.nRow)
								{
									if (pp[jjj][iii].p)
									{
										z_value += GetValue_(N_trias, order_t, order_c, nk_t, nk_c, sol, cols, z, as_ma ? pp[jjj][iii].a : pp[jj][ii].a, pp[jjj][iii].p, base_points);
										nnn++;
									}
								}
							}
						}
						if (nnn > 0)
						{
							z_value /= nnn;
							if (max_z < z_value) max_z = z_value;
							if (min_z > z_value) min_z = z_value;
						}
						else
							z_value = BLANK_VALUE;
					}
					else
						z_value = BLANK_VALUE;

					// полученное значение z_value записываем в грид
					grid->gridSection.z[jj][ii] = z_value;
				}
			}
			Free2DMat<point_polygon>(pp);
		}
		return true;
	}
	return false;
}


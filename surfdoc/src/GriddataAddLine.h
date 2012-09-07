void GridData::_AddLineToInput_(Line3D * line)
{
printf("GridData::AddLineToInput\n");
	if (line 
#if INTERPOLATION
		&& line->GetPointsNumber() > 1
#endif
		)
	{
		long id_point = this->m_input_points.SetCurrentMsgOnLast() ? this->m_input_points.GetCurrentMsg().id_point + 1 : 1;
#if INTERPOLATION
		vector<double> v_distances;
		for (unsigned int i1 = 0, i2 = 1; i2 < line->GetPointsNumber(); i1++, i2++)
		{
			CPoint3 pt1 = line->GetDocumentPoint(i1);
			CPoint3 pt2 = line->GetDocumentPoint(i2);

			double Dx = pt2.x - pt1.x;
			double Dy = pt2.y - pt1.y;
			double Dz = pt2.z - pt1.z;

			double D = sqrt(Dx*Dx + Dy*Dy + Dz*Dz);
			v_distances.push_back(D);
		}

		std::sort(v_distances.begin(), v_distances.end());

		size_t dist_len = v_distances.size();
		size_t i = dist_len/2;
		double d_median = v_distances[i];

#endif
		COLORREF color = line->GetColor();
		for (unsigned int i1 = 0, i2 = 1; i2 < line->GetPointsNumber(); i1++, i2++)
		{
			ThePoint3D point(this->m_pSurfDoc);

			CPoint3 pt1 = line->GetDocumentPoint(i1);
			CPoint3 pt2 = line->GetDocumentPoint(i2);
			if (i1 == 0)
			{
				this->m_input_points.AddMsg(&point);
				this->m_input_points.GetLastMsg().InitPoints(&pt1, 1, color);
				this->m_input_points.GetLastMsg().id_point = id_point++;
			}
#if INTERPOLATION
			// interpolation
			double Dx = pt2.x - pt1.x;
			double Dy = pt2.y - pt1.y;
			double Dz = pt2.z - pt1.z;

			double D = sqrt(Dx*Dx + Dy*Dy + Dz*Dz);
			if (D >= d_median)
			{
				double dx = Dx /(GridData::s_number_line_interpolated_points+1);
				double dy = Dy /(GridData::s_number_line_interpolated_points+1);
				double dz = Dz /(GridData::s_number_line_interpolated_points+1);

				for (size_t i = 0; i < GridData::s_number_line_interpolated_points; i++)
				{
					CPoint3 pti;
					pti.bVisible = true;
					pti.x = pt1.x + i*dx;
					pti.y = pt1.y + i*dy;
					pti.z = pt1.z + i*dz;

					this->m_input_points.AddMsg(&point);
					this->m_input_points.GetLastMsg().InitPoints(&pti, 1, color);
					this->m_input_points.GetLastMsg().id_point = id_point++;
				}
			}
#endif
			this->m_input_points.AddMsg(&point);
			this->m_input_points.GetLastMsg().InitPoints(&pt2, 1, color);
			this->m_input_points.GetLastMsg().id_point = id_point++;
		}
		this->m_input_points_ObjectList.Init(this->m_input_points, this);
	}
}


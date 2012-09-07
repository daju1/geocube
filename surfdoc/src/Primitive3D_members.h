size_t Primitive3D<MY_CPOINT>::AddBrokePoints(Profile3D * on)
{
	size_t sum_added = 0;
	double dist_to_plane1;		
	double dist_to_plane2;		
	CPoint2 p1;
	CPoint2 p2;
	int interval1;
	int interval2;
	for (size_t ipoint = 0; ipoint+1 < GetPointsNumber(); ipoint++)
	{
		bool result1 = on->Projection(m_vdPoints[ipoint  ], p1, dist_to_plane1, interval1);
		bool result2 = on->Projection(m_vdPoints[ipoint+1], p2, dist_to_plane2, interval2);
		if (result1 && result2 && interval1 != interval2)
		{
			printf("interval1 %d interval2 %d ipoint %d\n", interval1, interval2, ipoint);
			size_t added = on->AddBrokePoints(this, 
							   ipoint, 
							   p1, p2, 
							   interval1, interval2);

			ipoint		+= added;
			sum_added	+= added;
			printf("ipoint %d added %d sum_added %d\n", ipoint, added, sum_added);
		}
	}
	return sum_added;
}


void Primitive3D<MY_CPOINT>::Close()
{
	vector<MY_CPOINT>::iterator iter_v;
	vector<MY_CPOINT>::iterator iter_d;
	
	iter_v = m_vvPoints.begin();
	iter_d = m_vdPoints.begin(); 

	if (iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end() ) 
	{
		if ( (*iter_d) != m_vdPoints.back())
		{
			m_vvPoints.push_back(*iter_v);
			m_vdPoints.push_back(*iter_d);
			m_nPoints++;
		}
	}
}
void Primitive3D<MY_CPOINT>::UnClose()
{
	vector<MY_CPOINT>::iterator iter_v;
	vector<MY_CPOINT>::iterator iter_d;
	
	iter_v = m_vvPoints.begin();
	iter_d = m_vdPoints.begin(); 

	if (iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end() ) 
	{
		if ( (*iter_d) == m_vdPoints.back())
		{
			m_nPoints--;
			m_vvPoints.erase(iter_v + m_nPoints);
			m_vdPoints.erase(iter_d + m_nPoints);
		}
	}
}
bool Primitive3D<MY_CPOINT>::UnClose(int pos)
{
	if (pos < 0) return false;

	vector<MY_CPOINT>::iterator iter_v;
	vector<MY_CPOINT>::iterator iter_d;
	
	iter_v = m_vvPoints.begin();
	iter_d = m_vdPoints.begin(); 

	if (iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end() ) 
	{
		if ( (*iter_d) == m_vdPoints.back())
		{
			if (pos + 1 >= m_nPoints) return false;

			m_nPoints--;
			m_vvPoints.erase(iter_v + m_nPoints);
			m_vdPoints.erase(iter_d + m_nPoints);

			if (pos == m_nPoints - 1) return true;
			for (int i = 0; i <= pos; i++)
			{
				iter_v = m_vvPoints.begin();
				iter_d = m_vdPoints.begin(); 
				
				if (iter_v != m_vvPoints.end() && iter_d != m_vdPoints.end() ) 
				{		
					MY_CPOINT v = (*iter_v);
					MY_CPOINT d = (*iter_d);
					
					m_vvPoints.erase(iter_v);
					m_vdPoints.erase(iter_d);

					m_vvPoints.push_back(v);
					m_vdPoints.push_back(d);
				}
			}
			return true;
		}
	}
	return false;
}




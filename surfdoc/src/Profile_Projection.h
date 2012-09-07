

bool Profile3D::Projection(MY_CPOINT& in, CPoint2& profile, double & dist_to_plane)
{	 
	//printf("Profile::Projection\n");
	CPoint3 out;
	dist_to_plane = DBL_MAX;
	bool result = false;

	size_t len = (*ptpa).size();
	//=============================================
	for (size_t i = 0; i + 1 < len; i++)
	{	
		double A,B,C,D;
		CPoint2 p1,p2;

		p1.x = (*ptpa)[i].xMap;   p1.y = (*ptpa)[i].yMap;
		p2.x = (*ptpa)[i+1].xMap; p2.y = (*ptpa)[i+1].yMap;

		double xp1 = (*ptpa)[i].xProfile; 
		double xp2 = (*ptpa)[i+1].xProfile;

		if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
		{
			double t = -(A*in.x + B*in.y + C*in.z + D)
				/
				(A*A + B*B + C*C);

			if (fabs(t) < dist_to_plane)
			{
				dist_to_plane = fabs(t);

				out.x = in.x + A*t;
				out.y = in.y + B*t;
				out.z = in.z + C*t;

				result = true;

				//if (t == 0.0) on_plane = true;

				double Dx = p2.x - p1.x;
				double Dy = p2.y - p1.y;
				double part;

				if (fabs(Dx) > fabs(Dy))
				{
					part = (out.x - p1.x) / Dx;
				}
				else
				{
					part = (out.y - p1.y) / Dy;
				}
				profile.x = xp1 + part * (xp2 - xp1);
				profile.y = out.z;
			}
		}			
	}
	//printf("Profile::Projection in = [%f %f %f] profile = [%f %f]\n", in.x, in.y, in.z, profile.x, profile.y);
	return result;
}





bool Profile3D::Projection(MY_CPOINT& in, CPoint2& profile, double & dist_to_plane, int & interval)
{	 
	//printf("Profile::Projection\n");
	CPoint3 out;
	dist_to_plane = DBL_MAX;
	bool result = false;
	interval = -1;

	size_t len = (*ptpa).size();
	//=============================================
	for (size_t i = 0; i + 1 < len; i++)
	{	
		double A,B,C,D;
		CPoint2 p1,p2;

		p1.x = (*ptpa)[i].xMap;   p1.y = (*ptpa)[i].yMap;
		p2.x = (*ptpa)[i+1].xMap; p2.y = (*ptpa)[i+1].yMap;

		double xp1 = (*ptpa)[i].xProfile; 
		double xp2 = (*ptpa)[i+1].xProfile;

		if (0 == GetVerticalPlaneFromTwoPoints(p1,p2,A,B,C,D))
		{
			double t = -(A*in.x + B*in.y + C*in.z + D)
				/
				(A*A + B*B + C*C);

			if (fabs(t) < dist_to_plane)
			{
				dist_to_plane = fabs(t);
				interval = i;

				out.x = in.x + A*t;
				out.y = in.y + B*t;
				out.z = in.z + C*t;

				result = true;

				//if (t == 0.0) on_plane = true;

				double Dx = p2.x - p1.x;
				double Dy = p2.y - p1.y;
				double part;

				if (fabs(Dx) > fabs(Dy))
				{
					part = (out.x - p1.x) / Dx;
				}
				else
				{
					part = (out.y - p1.y) / Dy;
				}
				profile.x = xp1 + part * (xp2 - xp1);
				profile.y = out.z;
			}
		}			
	}
	//printf("Profile::Projection in = [%f %f %f] profile = [%f %f]\n", in.x, in.y, in.z, profile.x, profile.y);
	return result;
}
size_t Profile3D::AddBrokePoints(Primitive3D<MY_CPOINT> * primitive, 
							   size_t ipoint, 
							   CPoint2 p1, CPoint2 p2, 
							   int interval1, int interval2)
{	 
	size_t result = 0;
	if (p2.x == p1.x) return result;

	//int min_interval = min (interval1, interval2);
	//int max_interval = max (interval1, interval2);

	size_t len = (*ptpa).size();
	if (interval2 > interval1)
	{
		//=============================================
		for (size_t i = interval1; i < interval2 && i + 1 < len; i++)
		{	
			CPoint2 p; 
			p.x = (*ptpa)[i+1].xProfile;
			MY_CPOINT p3;
			p3.x = (*ptpa)[i+1].xMap;
			p3.y = (*ptpa)[i+1].yMap;
			if (p.x != p1.x && p.x != p2.x)
			{
				double mu = (p.x - p1.x) / (p2.x-p1.x);
				p.y = p1.y + mu * (p2.y - p1.y);
				p3.z = p.y;
				if (primitive)
				{
					primitive->Insert(ipoint + (++result), p3);
				}
			}
		}
	}
	else
	{
		// (interval1 > interval2)
		for (int i = int(interval1); i > int(interval2) && i + 1 < int(len) && i >= 0; i--)
		{	
			CPoint2 p; 
			p.x = (*ptpa)[i].xProfile;
			MY_CPOINT p3;
			p3.x = (*ptpa)[i].xMap;
			p3.y = (*ptpa)[i].yMap;

			if (p.x != p1.x && p.x != p2.x)
			{
				double mu = (p.x - p1.x) / (p2.x-p1.x);
				p.y = p1.y + mu * (p2.y - p1.y);
				p3.z = p.y;
				if (primitive)
				{				
					primitive->Insert(ipoint + (++result), p3);
				}
			}
		}
	}
	return result;
}






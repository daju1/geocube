// map.h


#ifndef _MAP_FUN_22_555GGGG
#define _MAP_FUN_22_555GGGG

void distance(double lat1, double lon1, vdouble lat2, vdouble lon2,
			  vdouble& az, vdouble& dist)
{
	
	// параметры земного элипсоида
	double a = 6378245;
	double b = 6356863.0188;
	double e = sqrt (pow(a,2.0) - pow(b,2.0)) / a;



	// широта
	//lat1 = [pi/2 -1]
	//lat2 = [0 1]
	// долгота
	//lon1 = [0 1]
	//lon2 = [0 -1]

	// azimuth азимут
	az = zeros(lat2.Length());     // Preallocate memory for output
	// приведенные широты
	double par1 =  0; //zeros(size(lat1));
	vdouble par2 = zeros(lat2.Length());

	double degepsilon = 1.0E-6,
		epsilon = degepsilon*PI/180; // Set tolerance to the pole


	// Identify those cases where a pole is a starting
	// point or a destination, and those cases where it is not

	// Идентифицируйте те случаи где полюс - начальная 
	// точка или расположение, и те случаи где нет


	// indx1 = find(lat1 >= pi/2-epsilon); % north pole starts
	// indx2 = find(lat1 <= epsilon-pi/2); % south pole starts
	// Vector<int> indx3 = Find(lat2 >= PI/2.0-epsilon); % north pole ends
	// Vector<int> indx4 = Find(lat2 <= epsilon-PI/2.0); % south pole ends

	//Vector<int> indx=1:prod(size(az));           % Все случаи
	//indx([indx1;indx2;indx3;indx4])=[];  %   less the special ones - менее специальный случаи

	// Handle the special cases.  For example, anything starting
	// at the north pole must go south (pi).  Starting point
	// has priority in degenerate cases; i.e. when going from
	// north pole to north pole, result will be pi, not zero.

	// Обработка специальных случаев.  Например, что-нибудь начиная 
	// в северный полюс должно пойти югом (pi).  Отправной Пункт 
	// имеет приоритет в случаях дегенерата; то есть ходя от 
	// северного полюса до северного полюса, результат будет pi, не нулем.
	if (lat1 >= PI/2.0-epsilon)// north pole starts
	{
		// Обработка специальных случаев. 
		// Приведенная широта на полюсах равна геодезическкой
		par1 = PI/2.0;//u2
		for(int i = 0; i < lat2.Length(); i++)
		{
			az[i] = 0; // Depart going north - Уезжайте на север
		}
	}
	else
	{
		if (lat1 <= epsilon-PI/2.0)// south pole starts
		{
			// Приведенная широта на полюсах равна геодезическкой
			par1 = -PI/2.0;//u2
			for(int i = 0; i < lat2.Length(); i++)
			{
				az[i] = PI; // Depart going south - Уезжайте на юг
			}
		}
		else
		{
			//  приведенная широта исходной точки
			par1 = atan (b/a * tan(lat1));     //  Conversion formula
			for(int i = 0; i < lat2.Length(); i++)
			{
				if (lat2[i] >= PI/2.0-epsilon) // north pole ends
				{
					//  Arrive going north
					az[i] = 0;
					par2[i] = PI/2.0;//u2
				}
				else 
				{
					if (lat2[i] <= epsilon-PI/2.0) // south pole ends
					{
						//  Arrive going south Прибудьте на юг
						az[i] = PI;
						par2[i] = -PI/2.0;//u2
					}
					else
					{
						//  Compute the bearing for either a spherical or elliptical geoid.
						//  Вычислите влияние для или сферический или эллиптический geoid
						//  Note that for a sphere, ratio = 1, par1 = lat1, par2 = lat2
						//  and fact4 = 0.


						//  Parametric latitudes - приведенные широты
						par2[i] = atan (b/a * tan(lat2[i]));//  Conversion formula

						// ratio = minaxis(geoid) / geoid(1);  
						// Semiminor/semimajor (b/a)
						double ratio = b/a;
						ratio = pow(ratio,2.0);

						double fact1 = cos(lat2[i]) * sin(lon2[i]-lon1);
						double fact2 = ratio * cos(lat1) * sin(lat2[i]);
						double fact3 = sin(lat1) * cos(lat2[i]) * cos(lon2[i]-lon1);
						double fact4 = (1-ratio) * sin(lat1) * cos(lat2[i]) * cos(par1) / cos(par2[i]);
						az[i] = atan2(fact1,fact2-fact3+fact4);
					}
				}
			}
		}
	}


	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	// Euler radius of curvature
	// Радиус кривизны Эйлера
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	//  Compute the mid-latitude point Вычислите широту средней точки

    vdouble latmid = lat1 + (lat2 - lat1)/2;

	//  Compute the azimuth азимут уже вычислен

	//  Compute the meridional and transverse radii of curvature
	// Вычислите меридиональный и поперечный (первого вертикала) радиусы кривизны


	// rho = rcurve('meridian',geoid,latmid,'radians');
	//  Meridional radius of curvature    (M)
       
	double num = a * (1-pow(e,2.0));
	vdouble den = 1 - pow((e * sin(latmid)),2.0);
	vdouble rho = num / pow(den,1.5);

	// nu  = rcurve('transverse',geoid,latmid,'radians');
    // Transverse radius of curvature (N)

    //den = 1 - (e * sin(latmid)).^2;
	vdouble nu  = a / sqrt(den);
    
	//  Compute the radius of the arc from point 1 to point 2
	// Вычислите радиус дуги из точки 1, в точку 2
	//  Ref:  Maling, p. 76.
	//  Reference: D. H. Maling, Coordinate Systems and Map
	//             Projections, 2nd Edition Pergamon Press, 1992, pp.. 77-79.

	den = rho * pow(sin(az),2.0) + nu * pow(cos(az),2.0);
	vdouble r = rho * nu / den;

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	//  Compute the cartesian coordinates of the points on the ellipsoid
	//  Вычислите декартов координаты точек в эллипсоиде
	//  (Note that because of the z calculation, this is not a simple sph2cart calc)

    double x1 = a * cos(par1) * cos(lon1);
	double y1 = a * cos(par1) * sin(lon1);
	double z1 = b * sin(par1);

    vdouble x2 = a * cos(par2) * cos(lon2);
	vdouble y2 = a * cos(par2) * sin(lon2);
	vdouble z2 = b * sin(par2);

	//  Compute the chord length. Длина хорды. Can't use norm function because
	//  x1, x2, etc may already be vectors or matrices

    vdouble k = sqrt( pow((x1-x2),2.0) +  pow((y1-y2),2.0) +  pow((z1-z2),2.0) );

	//  Now compute the correction factor, and then the range
	//  Теперь Вычислите показатель коррекции, и затем дипазон
	//  The correction factor breaks down as the eccentricity gets
	//  large for an ellipsoid.  (ie:  exceeds 0.2)
	//  Показатель коррекции ломается если эксцентричность получается 
	//  большой для эллипсоида.  (т.е.: превышает 0.2)


    // r = rsphere('euler',lat1,lon1,lat2,lon2,geoid,'radians');
	vdouble delta = pow(k,3.0) / (24.0*pow(r,2.0)) + 3.0*pow(k,5.0) / (640.0*pow(r,4.0));
	dist = k + delta;

}
#endif //#if !defined(_MAP_FUN_22_)
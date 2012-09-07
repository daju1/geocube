// griddata.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "gauss_linear_equations.h"

int griddata(vector<double> x, vector<double> y, vector<double> z, vector<double> xi, vector<double> yi, vector<double>& zi)
{
	int len = x.size();
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		//MessageBox(0, errstr,"Error using driddata",0);
		printf ("Error using driddata: %s\n", errstr);
		return -1;
	}
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	//sortrows21(x, y, z);

	COORDINATES * pxyz = new COORDINATES[len];

	for (int i = 0; i < len; i++)
	{
		pxyz[i].x = x[i];
		pxyz[i].y = y[i];
		pxyz[i].z = z[i];
	}

	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );
	for (i = 0; i < len; i++)
	{
		x[i] = pxyz[i].x;
		y[i] = pxyz[i].y;
		z[i] = pxyz[i].z;
	}
	delete[] pxyz;

	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
#if 0
	double myeps = x.MaxAbs();
	if (myeps < y.MaxAbs()) myeps = y.MaxAbs();
	myeps *= pow(pow(10,-32), 1./3.);

	Vector<bool> vb = 
		abs(x.DiffVector()) < myeps && abs(y.DiffVector()) < myeps;

	if(Find(vb).Size() > 0)
	{
		MessageBox(0,"Griddata:DuplicateDataPoints","Warning",0);
	}
#endif
	//----------------------------------------------------------
	//function [xi,yi,zi] = gdatav4(x,y,z,xi,yi)
	//GDATAV4 MATLAB 4 GRIDDATA interpolation

	//   Reference:  David T. Sandwell, Biharmonic spline
	//   interpolation of GEOS-3 and SEASAT altimeter
	//   data, Geophysical Research Letters, 2, 139-142,
	//   1987.  Describes interpolation using value or
	//   gradient of value in any dimension.

	// xy = x(:) + y(:)*sqrt(-1);

	// Determine distances between points
	//vdouble d(len, len);
	vector<vector<double> > d;
	d.resize(len);

	//d = xy(:,ones(1,length(xy)));
	//d = abs(d - d.');
	// n = size(d,1);
	int  j;
	for (i = 0; i < len; i++)
	{
		d[i] .resize(len);
		for (j = 0; j < len; j++)
		{
			d[i][j] = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
		}
	}
	//d.Write("d://_.txt","at","d");

	// Replace zeros along diagonal with ones (so these don't show up in the
	// find below or in the Green's function calculation).
	// d(1:n+1:prod(size(d))) = ones(1,n);
	for (i = 0; i < len; i++)
	{
		d[i][i] = 1.0;
	}

	//d.Write("d://_.txt","at","d");
	// non = find(d == 0);

	//Vector<int> non = Find(d == 0);
	vector<int> r0, c0; //row and col of zeros elements of d
	vector<double>::iterator result;
	for (i = 0; i < len; i++)
	{
		while (  (result = find( d[i].begin(), d[i].end(), 0.0 )) != d[i].end())
		{
			int r = i; 
			int c = result - d[i].begin();
			if (r < c)
			{
				r0.push_back(r);
				c0.push_back(c);
			}
		}
	}
	int non_size = r0.size();
	//if ~isempty(non),
	if (non_size > 0 )
	{
		/*int non_size = non.Size();
		// If we've made it to here, then some points aren't distinct.  Remove
		// the non-distinct points by averaging.
		// [r,c] = find(d == 0);
		// vdouble instead Vector <int>
		vdouble r(non_size), c(non_size);
		for (i = 0; i < non_size; i++)
		{
			r[i] = non[i] / len;
			c[i] = non[i] % len;
		}
		// k = find(r < c);
		Vector<int> k = Find(r < c);
		//r = r(k); c = c(k); % Extract unique (row,col) pairs
		r = r[k];
		c = c[k];*/
		//v = (z(r) + z(c))/2; % Average non-distinct pairs
		vector<double> v(non_size);
		for (i = 0; i < non_size; i++)
		{
			v[i] = 0.5*(z[int(r0[i])] + z[int(c0[i])]);
		}
		/*
		rep = find(diff(c)==0);
		if ~isempty(rep), % More than two points need to be averaged.
		runs = find(diff(diff(c)==0)==1)+1;
		for i=1:length(runs),
		  k = find(c==c(runs(i))); % All the points in a run
		  v(runs(i)) = mean(z([r(k);c(runs(i))])); % Average (again)
		end
		end
		*/

		//z(r) = v;
		for (i = 0; i < non_size; i++)
		{
			z[int(r0[i])] = v[i];
		}
		/*
		if ~isempty(rep),
		z(r(runs)) = v(runs); % Make sure average is in the dataset
		end
		*/

		// Now remove the extra points.
		//x(c) = [];
		//y(c) = [];
		//z(c) = [];

		sort( c0.begin( ), c0.end( ) );

		for (i = non_size-1; i >= 0; i--)
		{
			x.erase(x.begin()+int(c0[i]));
			y.erase(y.begin()+int(c0[i]));
			z.erase(z.begin()+int(c0[i]));
		}

		len -= non_size;

		// Determine distances between points

		d.resize(len);

		//d = xy(:,ones(1,length(xy)));
		//d = abs(d - d.');
		// n = size(d,1);
		int  j;
		for (i = 0; i < len; i++)
		{
			d[i] .resize(len);
			for (j = 0; j < len; j++)
			{
				d[i][j] = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
			}
		}

		//xy(c,:) = [];
		//xy(:,c) = [];
		//d(c,:) = [];
		//d(:,c) = [];

		/*
		% Determine the non distinct points
		ndp = sort([r;c]);
		ndp(find(ndp(1:length(ndp)-1)==ndp(2:length(ndp)))) = [];

		warning('MATLAB:griddata:NonDistinctPoints',['Averaged %d non-distinct ' ...
				'points.\n         Indices are: %s.'],length(ndp),num2str(ndp'))
				*/
	}

	// Determine weights for interpolation
	//g = (d.^2) .* (log(d)-1);   % Green's function.
	vector<vector<double> > g;// (len,len);
	g.resize(len);

	for (i = 0; i < len; i++)
	{
		g[i] .resize(len);
		for(j = 0; j < len; j++)
		{
			g[i][j] = pow(d[i][j], 2.0) * (log(d[i][j])-1.0);
		}
	}
		
	//g.Write("d://_.txt","at","g");
	// Fixup value of Green's function along diagonal
	//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
	for (i = 0; i < len; i++)
	{
		g[i][i] = 0.0;
	}
	//g.Write("d://_.txt","at","g");
	//weights = g \ z(:);
	/*
	vdouble pinvG;
	g.pinv(pinvG);
	//pinvG.Write("d://_.txt","at","pinvG");

	vdouble weights = pinvG.MatrixProduct(z);

	//weights.Write("d://_.txt","at","weights");
	*/
#if 0
	vdouble weights = g.Tichonov(z);
#else
	double det;
	vector<double> weights = sls_det(g, z, det);
#endif
//	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 

	//weights.Write("d://_.txt","at","weights");

	//[m,n] = size(xi);
	int m = xi.size();
	int n = yi.size();
	if (m != n)
	{
		printf("Error using griddata xi.size(%d) != yi.size(%s)", xi.size(), yi.size() );
		return -1;
	}
	zi.resize(n,0.0);
	/*
	jay = sqrt(-1);
	xy = xy.';
	*/


	// Evaluate at requested points (xi,yi).  Loop to save memory.
//	d.resize(len);
//	g.resize(len);
	vector<double> dd, gg;
	dd.resize(len);
	gg.resize(len);
	int k;
//	for (i = 0; i < m; i++)
//	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < len; k++)
			{
//				d[k] = sqrt( pow(x[k] - xi[i], 2.0) + pow(y[k] - yi[j], 2.0) );
				dd[k] = sqrt( pow(x[k] - xi[j], 2.0) + pow(y[k] - yi[j], 2.0) );
				if (dd[k] == 0.0)
					//Value of Green's function at zero
					gg[k] = 0.0;
				else
					//Green's function.
					gg[k] = pow(dd[k], 2.0) * (log(dd[k])-1.0);
			}
			//g.Write("d://_.txt","at","{{g}}");
			zi[j] = ScalarProduct(gg, weights);
		}
//	}
		
	//zi.Write("d://_.txt","at","zi");
	/*
	for i=1:m
	  for j=1:n
		d = abs(xi(i,j)+jay*yi(i,j) - xy);
		mask = find(d == 0);
		if length(mask)>0, d(mask) = ones(length(mask),1); end
		g = (d.^2) .* (log(d)-1);   % Green's function.
		% Value of Green's function at zero
		if length(mask)>0, g(mask) = zeros(length(mask),1); end
		zi(i,j) = g * weights;
	  end
	end
	*/

	//----------------------------------------------------------
	return 0;

}

int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	return 0;
}


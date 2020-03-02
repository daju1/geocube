

#ifdef _MSC_VER
#include <windows.h>
#include <gdiplus.h>
using namespace Gdiplus;
#endif
#include "StdAfx.h"

#include "interp.h"
#include "../../array/src/sorting.h"
#include "../../array/src/vect.h"
#include "../../surfdoc/src/Grid.h"
#include "../../surfdoc/src/Line3D.h"
#include "matrixes.h"
#include "Vdouble.h"
#include "sorting.h"
#include "slau.h"

#include "../../tools/src/filedlg.h"

				


#include "../../geometry2D/Point.h"
#include "../../geometry2D/Vertex.h"
#include "../../geometry2D/Edge.h"
#include "../../geometry2D/Polygon.h"
#include "../../geometry2D/PolygonEx.h"
#include "../../geometry2D/List.h"
#include "../../geometry2D/delaunay.h"
#include "../../geometry2D/belong.h"

using namespace geometry2D;


points_sort_mode point_with_distance::s_points_sort_mode = point_with_distance_points_sort_mode_by_dist;


extern HINSTANCE hInst;   // текущий экземпляр


int cubicInterp3(int nx, int ny, int nz, double ***x,double ***y,double ***z,double ***v, 
				 int nxi, int nyi, int nzi, double ***xi,double ***yi,double ***zi,double ***F,double ExtrapVal)
{

	//%------------------------------------------------------
	//function F = cubic(arg1,arg2,arg3,arg4,arg5,arg6,arg7,ExtrapVal)
	//%CUBIC 3-D Tricubic data interpolation.
	//%   CUBIC(...) is the same as LINEAR(....) except that it uses
	//%   cubic interpolation.
	//%   
	//%   See also INTERP3.
	//
	//%   Based on "Cubic Convolution Interpolation for Digital Image
	//%   Processing", Robert G. Keys, IEEE Trans. on Acoustics, Speech, and
	//%   Signal Processing, Vol. 29, No. 6, Dec. 1981, pp. 1153-1160.
	//


	//elseif nargin==8, % cubic(x,y,z,v,s,t,w), X, Y and Z specified.

	//  [nrows,ncols,npages] = size(arg4);
	int npages = nz;
	int nrows = ny;
	int ncols = nx;
	int r,c,p;

	if (nrows < 3 || ncols < 3 || npages < 3)
	{
		char str[255];
		sprintf (str, "interp3:cubic:sizeZsq','Z %d by %d by %d must be at least 3-by-3-by3.", nrows, ncols,npages);
		MessageBox(0, str, "cubicInterp2",0);
		return -1;
	}

	double ***s = AllocDouble3DMat (nzi, nyi, nxi);
	double ***t = AllocDouble3DMat (nzi, nyi, nxi);
	double ***w = AllocDouble3DMat (nzi, nyi, nxi);

	//  mx = numel(arg1); my = numel(arg2); mz = numel(arg3);
	//  s = 1 + (arg5-arg1(1))/(arg1(mx)-arg1(1))*(ncols-1);
	//  t = 1 + (arg6-arg2(1))/(arg2(my)-arg2(1))*(nrows-1);
	//  w = 1 + (arg7-arg3(1))/(arg3(mz)-arg3(1))*(npages-1);

	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				s[p][r][c] = 1.0 + (xi[p][r][c]-x[0][0][0])/(x[npages-1][nrows-1][ncols-1]-x[0][0][0])*(ncols-1);
				t[p][r][c] = 1.0 + (yi[p][r][c]-y[0][0][0])/(y[npages-1][nrows-1][ncols-1]-y[0][0][0])*(nrows-1);
				w[p][r][c] = 1.0 + (zi[p][r][c]-z[0][0][0])/(z[npages-1][nrows-1][ncols-1]-z[0][0][0])*(npages-1);
			}
		}
	}


	//if ~isequal(size(s),size(t),size(w)),
	//  error('MATLAB:interp3:cubic:XIYIZISizeMismatch',...
	//        'XI, YI and ZI must be the same size.');
	//end

	//% Check for out of range values of s and set to 1
	//sout = find((s<1)|(s>ncols));
	//if length(sout)>0, s(sout) = ones(size(sout)); end

	//% Check for out of range values of t and set to 1
	//tout = find((t<1)|(t>nrows));
	//if length(tout)>0, t(tout) = ones(size(tout)); end

	//% Check for out of range values of w and set to 1
	//wout = find((w<1)|(w>npages));
	//if length(wout)>0, w(wout) = ones(size(wout)); end
	vect<int> sout_p, sout_r, sout_c;
	vect<int> tout_p, tout_r, tout_c;
	vect<int> wout_p, wout_r, wout_c;

	sout_p.OnCreate();
	sout_r.OnCreate();
	sout_c.OnCreate();

	tout_p.OnCreate();
	tout_r.OnCreate();
	tout_c.OnCreate();

	wout_p.OnCreate();
	wout_r.OnCreate();
	wout_c.OnCreate();


	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				if ((s[p][r][c] < 1.0 ) | (s[p][r][c] > ncols))
				{
					s[p][r][c] = 1.0;
					sout_p.AddMsg(&p);
					sout_r.AddMsg(&r);
					sout_c.AddMsg(&c);
				}
				if ((t[p][r][c] < 1.0 ) | (t[p][r][c] > nrows))
				{
					t[p][r][c] = 1.0;
					tout_p.AddMsg(&p);
					tout_r.AddMsg(&r);
					tout_c.AddMsg(&c);
				}
				if ((w[p][r][c] < 1.0 ) | (w[p][r][c] > nrows))
				{
					w[p][r][c] = 1.0;
					wout_p.AddMsg(&p);
					wout_r.AddMsg(&r);
					wout_c.AddMsg(&c);
				}
			}
		}
	}

	//% Matrix element indexing
	//nw = (nrows+2)*(ncols+2);
	int nw = (nrows+2)*(ncols+2);
	//ndx = floor(t)+floor(s-1)*(nrows+2)+floor(w-1)*nw;
	int ***ndx = AllocInteger3DMat (nzi, nyi, nxi);
	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				ndx[p][r][c] = int(floor(t[p][r][c])+floor(s[p][r][c]-1)*(nrows+2)+
					floor(w[p][r][c]-1)*nw);
			}
		}
	}

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(s), d = s; else d = find(s==ncols); end
	//s(:) = (s - floor(s));
	vect<int> d_p, d_r, d_c;
	d_p.OnCreate();
	d_r.OnCreate();
	d_c.OnCreate();
	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				if (s[p][r][c] == ncols)
				{
					d_p.AddMsg(&p);
					d_r.AddMsg(&r);
					d_c.AddMsg(&c);
				}
				s[p][r][c] = s[p][r][c] - floor(s[p][r][c]);			
			}
		}
	}
	//if length(d)>0, s(d) = s(d)+1; ndx(d) = ndx(d)-nrows-2; end
	if(
		d_p.SetCurrentMsgOnFirst() &&
		d_r.SetCurrentMsgOnFirst() &&
		d_c.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			p = d_p.GetCurrentMsg();
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			s[p][r][c] = s[p][r][c] + 1.0;
			ndx[p][r][c] = ndx[p][r][c] - nrows-2;
		}
		while(
			d_p.IncrementCurrentMsg() && 
			d_r.IncrementCurrentMsg() && 
			d_c.IncrementCurrentMsg());
	}

	d_p.clearMsg();
	d_r.clearMsg();
	d_c.clearMsg();

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(t), d = t; else d = find(t==nrows); end
	//t(:) = (t - floor(t));
	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				if (t[p][r][c] == nrows)
				{
					d_p.AddMsg(&p);
					d_r.AddMsg(&r);
					d_c.AddMsg(&c);
				}
				t[p][r][c] = t[p][r][c] - floor(t[p][r][c]);			
			}
		}
	}
	//if length(d)>0, t(d) = t(d)+1; ndx(d) = ndx(d)-1; end
	if(
		d_p.SetCurrentMsgOnFirst() &&
		d_r.SetCurrentMsgOnFirst() &&
		d_c.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			p = d_p.GetCurrentMsg();
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			t[p][r][c] = t[p][r][c] + 1.0;
			ndx[p][r][c] = ndx[p][r][c] - 1;
		}
		while(
			d_p.IncrementCurrentMsg() && 
			d_r.IncrementCurrentMsg() && 
			d_c.IncrementCurrentMsg());
	}

	d_p.clearMsg();
	d_r.clearMsg();
	d_c.clearMsg();

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(w), d = w; else d = find(w==npages); end
	//w(:) = (w - floor(w));
	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				if (w[p][r][c] == npages)
				{
					d_p.AddMsg(&p);
					d_r.AddMsg(&r);
					d_c.AddMsg(&c);
				}
				w[p][r][c] = w[p][r][c] - floor(w[p][r][c]);			
			}
		}
	}
	//if length(d)>0, w(d) = w(d)+1; ndx(d) = ndx(d)-nw; end
	if(
		d_p.SetCurrentMsgOnFirst() &&
		d_r.SetCurrentMsgOnFirst() &&
		d_c.SetCurrentMsgOnFirst()
		)
	{
		do
		{
			p = d_p.GetCurrentMsg();
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			w[p][r][c] = w[p][r][c] + 1.0;
			ndx[p][r][c] = ndx[p][r][c] - nw;
		}
		while(
			d_p.IncrementCurrentMsg() && 
			d_r.IncrementCurrentMsg() && 
			d_c.IncrementCurrentMsg());
	}

	//d = []; % Reclaim memory
	d_p.clearMsg();
	d_r.clearMsg();
	d_c.clearMsg();


	//% Expand v so interpolation is valid at the boundaries.
	//  vv = zeros(size(arg4)+2);
	double ***vv = AllocDouble3DMat (npages+2, nrows+2, ncols+2);
	for (p = 0; p < npages+2; p++)
	{
		for (r = 0; r < nrows+2; r++)
		{
			for (c = 0; c < ncols+2; c++)
			{
				 vv[p][r][c] = 0.0;			
			}
		}
	}
	//  vv(2:nrows+1,2:ncols+1,2:npages+1) = arg4;
	for (p = 0; p < npages; p++)
	{
		for (r = 0; r < nrows; r++)
		{
			for (c = 0; c < ncols; c++)
			{
				 vv[p+1][r+1][c+1] = v[p][r][c];			
			}
		}
	}


	//vv(1,:,:)        = 3*vv(2,:,:)       -3*vv(3,:,:)     +vv(4,:,:); % Y edges
	for (p = 0; p < npages+2; p++)
	{
		for (c = 0; c < ncols+2; c++)
		{
			 vv[p][0][c] = 3.*vv[p][1][c] - 3.*vv[p][2][c] + vv[p][3][c];			
		}
	}
	//vv(nrows+2,:,:)  = 3*vv(nrows+1,:,:) -3*vv(nrows,:,:) +vv(nrows-1,:,:);
	for (p = 0; p < npages+2; p++)
	{
		for (c = 0; c < ncols+2; c++)
		{
			 vv[p][nrows+1][c] = 3.*vv[p][nrows][c] - 3.*vv[p][nrows-1][c] + vv[p][nrows-2][c];			
		}
	}
	//vv(:,1,:)        = 3*vv(:,2,:)       -3*vv(:,3,:)     +vv(:,4,:); % X edges
	for (p = 0; p < npages+2; p++)
	{
		for (r = 0; r < nrows+2; r++)
		{
			 vv[p][r][0] = 3.*vv[p][r][1] - 3.*vv[p][r][2] + vv[p][r][3];			
		}
	}
	//vv(:,ncols+2,:)  = 3*vv(:,ncols+1,:) -3*vv(:,ncols,:) +vv(:,ncols-1,:);
	for (p = 0; p < npages+2; p++)
	{
		for (r = 0; r < nrows+2; r++)
		{
			 vv[p][r][ncols+1] = 3.*vv[p][r][ncols] - 3.*vv[p][r][ncols-1] + vv[p][r][ncols-2];			
		}
	}
	//vv(:,:,1)        = 3*vv(:,:,2)       -3*vv(:,:,3)     +vv(:,:,4); % Z edges
	for (r = 0; r < nrows+2; r++)
	{
		for (c = 0; c < ncols+2; c++)
		{
			 vv[0][r][c] = 3.*vv[1][r][c] - 3.*vv[2][r][c] + vv[3][r][c];			
		}
	}
	//vv(:,:,npages+2) = 3*vv(:,:,npages+1)-3*vv(:,:,npages)+vv(:,:,npages-1);
	for (r = 0; r < nrows+2; r++)
	{
		for (c = 0; c < ncols+2; c++)
		{
			 vv[npages+1][r][c] = 3.*vv[npages][r][c] - 3.*vv[npages-1][r][c] + vv[npages-2][r][c];			
		}
	}
	//nrows = nrows+2; ncols = ncols+2; npages = npages+2;
	nrows = nrows+2; ncols = ncols+2; npages = npages+2;


	//% Now interpolate using computationally efficient algorithm.
	//F = zeros(size(s));
	//double *** F = AllocDouble3DMat (nzi, nyi, nxi);
	double *** ww = AllocDouble3DMat (nzi, nyi, nxi);
	double *** ss = AllocDouble3DMat (nzi, nyi, nxi);
	double *** tt = AllocDouble3DMat (nzi, nyi, nxi);
	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				 F[p][r][c] = 0.0;			
			}
		}
	}
//for iw = 0:3,
//  ww = localevaluate(w,iw);
//  for is = 0:3,
//    ss = localevaluate(s,is);
//    for it = 0:3,
//      tt = localevaluate(t,it);
//      F(:) = F + vv(ndx+(it+is*nrows+iw*nw)).*ss.*tt.*ww;
//    end
//  end
//end
	for (int iw = 0; iw <= 3; iw++)
	{
		localevaluate ( nzi, nyi, nxi, ww, w, iw);
		for (int is = 0; is <= 3; is++)
		{
			localevaluate ( nzi, nyi, nxi, ss, s, is);
			for (int it = 0; it <= 3; it++)
			{
				localevaluate ( nzi, nyi, nxi, tt, t, it);
				for (p = 0; p < nzi; p++)
				{
					for (r = 0; r < nyi; r++)
					{
						for (c = 0; c < nxi; c++)
						{
							 F[p][r][c] = F[p][r][c] + 
								 vv[0][0][ndx[p][r][c]+(it+is*nrows+iw*nw)] *
								 ss[p][r][c] * tt[p][r][c] *ww[p][r][c];
						}
					}
				}
			}
		}
	}
	//F(:) = F/8;
	for (p = 0; p < nzi; p++)
	{
		for (r = 0; r < nyi; r++)
		{
			for (c = 0; c < nxi; c++)
			{
				 F[p][r][c] = F[p][r][c] / 8.;
			}
		}
	}

	//% Now set out of range values to NaN.
	//if length(sout)>0, F(sout) = ExtrapVal; end
	if(
		sout_p.SetCurrentMsgOnFirst() && 
		sout_r.SetCurrentMsgOnFirst() && 
		sout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			p = sout_p.GetCurrentMsg();
			r = sout_r.GetCurrentMsg();
			c = sout_c.GetCurrentMsg();
			F[p][r][c] = ExtrapVal;
		}
		while(
			sout_p.IncrementCurrentMsg() && 
			sout_r.IncrementCurrentMsg() && 
			sout_c.IncrementCurrentMsg());
	}
	//if length(tout)>0, F(tout) = ExtrapVal; end
	if(
		tout_p.SetCurrentMsgOnFirst() && 
		tout_r.SetCurrentMsgOnFirst() && 
		tout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			p = tout_p.GetCurrentMsg();
			r = tout_r.GetCurrentMsg();
			c = tout_c.GetCurrentMsg();
			F[p][r][c] = ExtrapVal;
		}
		while(
			tout_p.IncrementCurrentMsg() && 
			tout_r.IncrementCurrentMsg() && 
			tout_c.IncrementCurrentMsg());
	}
	//if length(wout)>0, F(wout) = ExtrapVal; end
	if(
		wout_p.SetCurrentMsgOnFirst() && 
		wout_r.SetCurrentMsgOnFirst() && 
		wout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			p = wout_p.GetCurrentMsg();
			r = wout_r.GetCurrentMsg();
			c = wout_c.GetCurrentMsg();
			F[p][r][c] = ExtrapVal;
		}
		while(
			wout_p.IncrementCurrentMsg() && 
			wout_r.IncrementCurrentMsg() && 
			wout_c.IncrementCurrentMsg());
	}

	//%%%%%%% THIS NEEDS TO BE MODIFIED %%%%%%%%%%%%%%%
	FreeDouble3DMat(s);
	FreeDouble3DMat(t);
	FreeDouble3DMat(w);
	FreeInteger3DMat(ndx);
	FreeDouble3DMat(vv);
	FreeDouble3DMat(ss);
	FreeDouble3DMat(tt);
	FreeDouble3DMat(ww);
	return 0;
}

//%------------------------------------------------------
int cubicInterp2(int nx, int ny, double **x,double **y,double **z, 
				 int nxi, int nyi, double **xi,double **yi,double **zi,double ExtrapVal)

{

	//%CUBIC 2-D bicubic data interpolation.
	//%   CUBIC(...) is the same as LINEAR(....) except that it uses
	//%   bicubic interpolation.
	//%   
	//%   This function needs about 7-8 times SIZE(XI) memory to be available.
	//%
	//%   See also LINEAR.

	//%   Clay M. Thompson 4-26-91, revised 7-3-91, 3-22-93 by CMT.

	//%   Based on "Cubic Convolution Interpolation for Digital Image
	//%   Processing", Robert G. Keys, IEEE Trans. on Acoustics, Speech, and
	//%   Signal Processing, Vol. 29, No. 6, Dec. 1981, pp. 1153-1160.


	// nargin==6, % cubic(x,y,z,s,t), X and Y specified.
	int nrows = ny;
	int ncols = nx;
	int r,c;

	double **s = AllocDoubleMat (nyi, nxi);
	double **t = AllocDoubleMat (nyi, nxi);

	//mx = numel(arg1); my = numel(arg2);
	//s = 1 + (arg4-arg1(1))/(arg1(mx)-arg1(1))*(ncols-1);
	//t = 1 + (arg5-arg2(1))/(arg2(my)-arg2(1))*(nrows-1);

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			s[r][c] = 1.0 + (xi[r][c]-x[0][0])/(x[nrows-1][ncols-1]-x[0][0])*(ncols-1);
			t[r][c] = 1.0 + (yi[r][c]-y[0][0])/(y[nrows-1][ncols-1]-y[0][0])*(nrows-1);
		}
	}

	if (nrows < 3 || ncols < 3)
	{
		char str[255];
		sprintf (str, "interp2:cubic:sizeZsq','Z %d by %d must be at least 3-by-3.", nrows, ncols);
		MessageBox(0, str, "cubicInterp2",0);
		return -1;
	}

	//if ~isequal(size(s),size(t)),
	//	 error('MATLAB:interp2:cubic:XIandYISizeMismatch','XI and YI must be the same size.');


	//% Check for out of range values of s and set to 1
	//sout = find((s<1)|(s>ncols));
	//if length(sout)>0, s(sout) = ones(size(sout)); end
	//% Check for out of range values of t and set to 1
	//tout = find((t<1)|(t>nrows));
	//if length(tout)>0, t(tout) = ones(size(tout)); end
	vect<int> sout_r, sout_c;
	vect<int> tout_r, tout_c;
	sout_r.OnCreate();
	sout_c.OnCreate();
	tout_r.OnCreate();
	tout_c.OnCreate();
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			if ((s[r][c] < 1.0 ) | (s[r][c] > ncols))
			{
				s[r][c] = 1.0;
				sout_r.AddMsg(&r);
				sout_c.AddMsg(&c);
			}
			if ((t[r][c] < 1.0 ) | (t[r][c] > nrows))
			{
				t[r][c] = 1.0;
				tout_r.AddMsg(&r);
				tout_c.AddMsg(&c);
			}
		}
	}

	//% Matrix element indexing
	//ndx = floor(t)+floor(s-1)*(nrows+2);
	int **ndx = AllocIntegerMat (nyi, nxi);

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			ndx[r][c] = int(floor(t[r][c])+floor(s[r][c]-1)*(nrows+2));
		}
	}

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(s), d = s; else d = find(s==ncols); end
	//s(:) = (s - floor(s));
	vect<int> d_r, d_c;
	d_r.OnCreate();
	d_c.OnCreate();
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			if (s[r][c] == ncols)
			{
				d_r.AddMsg(&r);
				d_c.AddMsg(&c);
			}
			s[r][c] = s[r][c] - floor(s[r][c]);			
		}
	}

	//if length(d)>0, s(d) = s(d)+1; ndx(d) = ndx(d)-nrows-2; end
	if(d_r.SetCurrentMsgOnFirst() && d_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			s[r][c] = s[r][c] + 1.0;
			ndx[r][c] = ndx[r][c] - nrows-2;
		}
		while(d_r.IncrementCurrentMsg() && d_c.IncrementCurrentMsg());
	}

	d_r.clearMsg();
	d_c.clearMsg();

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(t), d = t; else d = find(t==nrows); end
	//t(:) = (t - floor(t));
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			if (t[r][c] == nrows)
			{
				d_r.AddMsg(&r);
				d_c.AddMsg(&c);
			}
			t[r][c] = t[r][c] - floor(t[r][c]);			
		}
	}

	//if length(d)>0, t(d) = t(d)+1; ndx(d) = ndx(d)-1; end
	if(d_r.SetCurrentMsgOnFirst() && d_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			t[r][c] = t[r][c] + 1.0;
			ndx[r][c] = ndx[r][c] - 1;
		}
		while(d_r.IncrementCurrentMsg() && d_c.IncrementCurrentMsg());
	}

	//d = [];
	d_r.clearMsg();
	d_c.clearMsg();

	
	//if nargin==6,
	//% Expand z so interpolation is valid at the boundaries.
	//zz = zeros(size(arg3)+2);
	double **zz = AllocDoubleMat (nrows+2, ncols+2);
	for (r = 0; r < nrows+2; r++)
	{
		for (c = 0; c < ncols+2; c++)
		{
			 zz[r][c] = 0.0;			
		}
	}

	//zz(1,2:ncols+1) = 3*arg3(1,:)-3*arg3(2,:)+arg3(3,:);
	for (c = 0; c < ncols; c++)
	{
		 zz[0][c+1] = 3.* z[0][c] - 3.*z[1][c] + z[2][c];			
	}

	//zz(2:nrows+1,2:ncols+1) = arg3;
	for (r = 0; r < nrows; r++)
	{
		for (c = 0; c < ncols; c++)
		{
			 zz[r+1][c+1] = z[r][c];			
		}
	}

	//zz(nrows+2,2:ncols+1) = 3*arg3(nrows,:)-3*arg3(nrows-1,:)+arg3(nrows-2,:);
	for (c = 0; c < ncols; c++)
	{
		 zz[nrows+1][c+1] = 3.*z[nrows-1][c]-3.*z[nrows-2][c]+z[nrows-3][c];			
	}

	//zz(:,1) = 3*zz(:,2)-3*zz(:,3)+zz(:,4);
	for (r = 0; r < nrows+2; r++)
	{
		 zz[r][0] = 3.*zz[r][1]-3.*zz[r][2]+zz[r][3];			
	}

	//zz(:,ncols+2) = 3*zz(:,ncols+1)-3*zz(:,ncols)+zz(:,ncols-1);
	for (r = 0; r < nrows+2; r++)
	{
		 zz[r][ncols+1] = 3.*zz[r][ncols]-3.*zz[r][ncols-1]+zz[r][ncols-2];			
	}
	//nrows = nrows+2; ncols = ncols+2;
	nrows = nrows+2; ncols = ncols+2;




	//% Now interpolate using computationally efficient algorithm.
	double **t0 = AllocDoubleMat (nyi, nxi);
	double **t1 = AllocDoubleMat (nyi, nxi);
	double **t2 = AllocDoubleMat (nyi, nxi);
	//t0 = ((2-t).*t-1).*t;
	//t1 = (3*t-5).*t.*t+2;
	//t2 = ((4-3*t).*t+1).*t;
	//t(:) = (t-1).*t.*t;
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			t0[r][c] = ((2.- t[r][c])*t[r][c] - 1.)*t[r][c];
			t1[r][c] = (3.* t[r][c] - 5.)*t[r][c]*t[r][c] + 2.0;
			t2[r][c] = ((4. - 3.*t[r][c])*t[r][c] + 1.)*t[r][c];
			t[r][c] = (t[r][c] - 1.)*t[r][c]*t[r][c];
		}
	}


	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//F     = ( zz(ndx).*t0 + zz(ndx+1).*t1 + zz(ndx+2).*t2 + zz(ndx+3).*t ) ...
			//		.* (((2-s).*s-1).*s);
			zi[r][c] = ( 
				zz[(ndx[r][c]-1  ) % nrows][(ndx[r][c]-1  ) / nrows] * t0[r][c] + 
				zz[(ndx[r][c]-1+1) % nrows][(ndx[r][c]-1+1) / nrows] * t1[r][c] + 
				zz[(ndx[r][c]-1+2) % nrows][(ndx[r][c]-1+2) / nrows] * t2[r][c] + 
				zz[(ndx[r][c]-1+3) % nrows][(ndx[r][c]-1+3) / nrows] * t[r][c] ) *
				(((2. - s[r][c])*s[r][c] - 1.)*s[r][c]);

		}
	}			

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//ndx(:) = ndx + nrows;
			ndx[r][c] = ndx[r][c] + nrows;
		}
	}			

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//F(:)  = F + ( zz(ndx).*t0 + zz(ndx+1).*t1 + zz(ndx+2).*t2 + zz(ndx+3).*t ) ...
			//		.* ((3*s-5).*s.*s+2);
			zi[r][c] = zi[r][c] + ( 
				zz[(ndx[r][c]-1  ) % nrows][(ndx[r][c]-1  ) / nrows] * t0[r][c] + 
				zz[(ndx[r][c]-1+1) % nrows][(ndx[r][c]-1+1) / nrows] * t1[r][c] + 
				zz[(ndx[r][c]-1+2) % nrows][(ndx[r][c]-1+2) / nrows] * t2[r][c] + 
				zz[(ndx[r][c]-1+3) % nrows][(ndx[r][c]-1+3) / nrows] * t[r][c] ) * 
				((3.* s[r][c] - 5.)*s[r][c]*s[r][c] + 2.);
		}
	}			

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//ndx(:) = ndx + nrows;
			ndx[r][c] = ndx[r][c] + nrows;
		}
	}			

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//F(:)  = F + ( zz(ndx).*t0 + zz(ndx+1).*t1 + zz(ndx+2).*t2 + zz(ndx+3).*t ) ...
			//		.* (((4-3*s).*s+1).*s);
			zi[r][c] = zi[r][c] + ( 
				zz[(ndx[r][c]-1  ) % nrows][(ndx[r][c]-1  ) / nrows] * t0[r][c] + 
				zz[(ndx[r][c]-1+1) % nrows][(ndx[r][c]-1+1) / nrows] * t1[r][c] + 
				zz[(ndx[r][c]-1+2) % nrows][(ndx[r][c]-1+2) / nrows] * t2[r][c] + 
				zz[(ndx[r][c]-1+3) % nrows][(ndx[r][c]-1+3) / nrows] * t[r][c] ) * 
				(((4.- 3.* s[r][c]) * s[r][c] + 1.) * s[r][c]);
		}
	}			

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//ndx(:) = ndx + nrows;
			ndx[r][c] = ndx[r][c] + nrows;
		}
	}			

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//F(:)  = F + ( zz(ndx).*t0 + zz(ndx+1).*t1 + zz(ndx+2).*t2 + zz(ndx+3).*t ) ...
			//	   .* ((s-1).*s.*s);
			//F(:) = F/4;
			zi[r][c]  = zi[r][c] + ( 
				zz[(ndx[r][c]-1  ) % nrows][(ndx[r][c]-1) / nrows] * t0[r][c] + 
				zz[(ndx[r][c]-1+1) % nrows][(ndx[r][c]-1+1) / nrows] * t1[r][c] + 
				zz[(ndx[r][c]-1+2) % nrows][(ndx[r][c]-1+2) / nrows] * t2[r][c] + 
				zz[(ndx[r][c]-1+3) % nrows][(ndx[r][c]-1+3) / nrows] * t[r][c] ) * 
				((s[r][c] - 1.) * s[r][c] * s[r][c]);

			zi[r][c] = zi[r][c]/4.0;
		}
	}			

	//% Now set out of range values to NaN.
	//if length(sout)>0, F(sout) = ExtrapVal; end
	if(sout_r.SetCurrentMsgOnFirst() && sout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = sout_r.GetCurrentMsg();
			c = sout_c.GetCurrentMsg();
			zi[r][c] = ExtrapVal;
		}
		while(sout_r.IncrementCurrentMsg() && sout_c.IncrementCurrentMsg());
	}

	//if length(tout)>0, F(tout) = ExtrapVal; end
	if(tout_r.SetCurrentMsgOnFirst() && tout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = tout_r.GetCurrentMsg();
			c = tout_c.GetCurrentMsg();
			zi[r][c] = ExtrapVal;
		}
		while(tout_r.IncrementCurrentMsg() && tout_c.IncrementCurrentMsg());
	}

	//%%%%%%% THIS NEEDS TO BE MODIFIED %%%%%%%%%%%%%%%
	FreeDoubleMat(s);
	FreeDoubleMat(t);
	FreeIntegerMat(ndx);
	FreeDoubleMat(zz);
	FreeDoubleMat(t0);
	FreeDoubleMat(t1);
	FreeDoubleMat(t2);
	return 0;
}
//%------------------------------------------------------
int linearInterp2(int nx, int ny, double **x,double **y,double **z, 
				 int nxi, int nyi, double **xi,double **yi,double **zi,double ExtrapVal)
{
	//%LINEAR 2-D bilinear data interpolation.
	//%   ZI = LINEAR(X,Y,Z,XI,YI) uses bilinear interpolation to
	//%   find ZI, the values of the underlying 2-D function in Z at the points
	//%   in matrices XI and YI.  Matrices X and Y specify the points at which 
	//%   the data Z is given.  X and Y can also be vectors specifying the 
	//%   abscissae for the matrix Z as for MESHGRID. In both cases, X
	//%   and Y must be equally spaced and monotonic.
	//%
	//%   Values of NaN are returned in ZI for values of XI and YI that are 
	//%   outside of the range of X and Y.
	//%
	//%   If XI and YI are vectors, LINEAR returns vector ZI containing
	//%   the interpolated values at the corresponding points (XI,YI).
	//%
	//%   ZI = LINEAR(Z,XI,YI) assumes X = 1:N and Y = 1:M, where
	//%   [M,N] = SIZE(Z).
	//%
	//%   ZI = LINEAR(Z,NTIMES) returns the matrix Z expanded by interleaving
	//%   bilinear interpolates between every element, working recursively
	//%   for NTIMES.  LINEAR(Z) is the same as LINEAR(Z,1).
	//%
	//%   This function needs about 4 times SIZE(XI) memory to be available.
	//%
	//%   See also INTERP2, CUBIC.



	// nargin==6, % linear(x,y,z,s,t), X and Y specified.
	int nrows = ny;
	int ncols = nx;
	int r,c;

	double **s = AllocDoubleMat (nyi, nxi);
	double **t = AllocDoubleMat (nyi, nxi);


	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			s[r][c] = 1.0 + (xi[r][c]-x[0][0])/(x[nrows-1][ncols-1]-x[0][0])*(ncols-1);
			t[r][c] = 1.0 + (yi[r][c]-y[0][0])/(y[nrows-1][ncols-1]-y[0][0])*(nrows-1);
		}
	}

	if (nrows < 3 || ncols < 3)
	{
		char str[255];
		sprintf (str, "interp2:cubic:sizeZsq','Z %d by %d must be at least 3-by-3.", nrows, ncols);
		MessageBox(0, str, "cubicInterp2",0);
		return -1;
	}

	//if ~isequal(size(s),size(t)),
	//	 error('MATLAB:interp2:cubic:XIandYISizeMismatch','XI and YI must be the same size.');


	//% Check for out of range values of s and set to 1
	//sout = find((s<1)|(s>ncols));
	//if length(sout)>0, s(sout) = ones(size(sout)); end
	//% Check for out of range values of t and set to 1
	//tout = find((t<1)|(t>nrows));
	//if length(tout)>0, t(tout) = ones(size(tout)); end
	vect<int> sout_r, sout_c;
	vect<int> tout_r, tout_c;
	sout_r.OnCreate();
	sout_c.OnCreate();
	tout_r.OnCreate();
	tout_c.OnCreate();
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			if ((s[r][c] < 1.0 ) | (s[r][c] > ncols))
			{
				s[r][c] = 1.0;
				sout_r.AddMsg(&r);
				sout_c.AddMsg(&c);
			}
			if ((t[r][c] < 1.0 ) | (t[r][c] > nrows))
			{
				t[r][c] = 1.0;
				tout_r.AddMsg(&r);
				tout_c.AddMsg(&c);
			}
		}
	}

	//% Matrix element indexing
	//ndx = floor(t)+floor(s-1)*(nrows+2);
	//ndx = floor(t)+floor(s-1)*nrows;

	int **ndx = AllocIntegerMat (nyi, nxi);

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			ndx[r][c] = int(floor(t[r][c])+floor(s[r][c]-1)*nrows);
		}
	}

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(s), d = s; else d = find(s==ncols); end
	//s(:) = (s - floor(s));
	vect<int> d_r, d_c;
	d_r.OnCreate();
	d_c.OnCreate();
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			if (s[r][c] == ncols)
			{
				d_r.AddMsg(&r);
				d_c.AddMsg(&c);
			}
			s[r][c] = s[r][c] - floor(s[r][c]);			
		}
	}

	//if length(d)>0, s(d) = s(d)+1; ndx(d) = ndx(d)-nrows-2; end
	//if length(d)>0, s(d) = s(d)+1; ndx(d) = ndx(d)-nrows; end

	if(d_r.SetCurrentMsgOnFirst() && d_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			s[r][c] = s[r][c] + 1.0;
			ndx[r][c] = ndx[r][c] - nrows;
		}
		while(d_r.IncrementCurrentMsg() && d_c.IncrementCurrentMsg());
	}

	d_r.clearMsg();
	d_c.clearMsg();

	//% Compute intepolation parameters, check for boundary value.
	//if isempty(t), d = t; else d = find(t==nrows); end
	//t(:) = (t - floor(t));
	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			if (t[r][c] == nrows)
			{
				d_r.AddMsg(&r);
				d_c.AddMsg(&c);
			}
			t[r][c] = t[r][c] - floor(t[r][c]);			
		}
	}

	//if length(d)>0, t(d) = t(d)+1; ndx(d) = ndx(d)-1; end
	if(d_r.SetCurrentMsgOnFirst() && d_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = d_r.GetCurrentMsg();
			c = d_c.GetCurrentMsg();
			t[r][c] = t[r][c] + 1.0;
			ndx[r][c] = ndx[r][c] - 1;
		}
		while(d_r.IncrementCurrentMsg() && d_c.IncrementCurrentMsg());
	}

	//d = [];
	d_r.clearMsg();
	d_c.clearMsg();

	




	//F =  ( arg3(ndx).*(1-t) + arg3(ndx+1).*t ).*(1-s) + ...
	//   ( arg3(ndx+nrows).*(1-t) + arg3(ndx+(nrows+1)).*t ).*s;

	for (r = 0; r < nyi; r++)
	{
		for (c = 0; c < nxi; c++)
		{
			//F     = ( zz(ndx).*t0 + zz(ndx+1).*t1 + zz(ndx+2).*t2 + zz(ndx+3).*t ) ...
			//		.* (((2-s).*s-1).*s);
			zi[r][c] = ( 
				z[(ndx[r][c]-1  ) % nrows][(ndx[r][c]-1  ) / nrows] * (1.0-t[r][c]) + 
				z[(ndx[r][c]-1+1) % nrows][(ndx[r][c]-1+1) / nrows] * t[r][c] ) * 
				(1.0 - s[r][c]) + (
				z[(ndx[r][c]-1+nrows) % nrows][(ndx[r][c]-1+nrows) / nrows] * (1.0-t[r][c]) + 
				z[(ndx[r][c]-1+nrows+1) % nrows][(ndx[r][c]-1+nrows+1) / nrows] * t[r][c] ) *
				s[r][c];

		}
	}			


	//% Now set out of range values to NaN.
	//if length(sout)>0, F(sout) = ExtrapVal; end
	if(sout_r.SetCurrentMsgOnFirst() && sout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = sout_r.GetCurrentMsg();
			c = sout_c.GetCurrentMsg();
			zi[r][c] = ExtrapVal;
		}
		while(sout_r.IncrementCurrentMsg() && sout_c.IncrementCurrentMsg());
	}

	//if length(tout)>0, F(tout) = ExtrapVal; end
	if(tout_r.SetCurrentMsgOnFirst() && tout_c.SetCurrentMsgOnFirst())
	{
		do
		{
			r = tout_r.GetCurrentMsg();
			c = tout_c.GetCurrentMsg();
			zi[r][c] = ExtrapVal;
		}
		while(tout_r.IncrementCurrentMsg() && tout_c.IncrementCurrentMsg());
	}

	//%%%%%%% THIS NEEDS TO BE MODIFIED %%%%%%%%%%%%%%%
	FreeDoubleMat(s);
	FreeDoubleMat(t);
	FreeIntegerMat(ndx);
	return 0;
}
#if 0
int griddata(HWND hwndParent, vdouble& x, vdouble& y, vdouble& z, 
			 vdouble& xi, vdouble& yi, vdouble& zi)
{
	int len = x.Length();
	if ( len != y.Length() || len != z.Length() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.Length(), z.Length());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}


	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed


printf("griddata 0\n");
	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(hwndParent, &rcClient); 
	GetWindowRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
			 (LPSTR) NULL, 
			 //WS_CHILD | WS_VISIBLE,
			 WS_POPUPWINDOW,
			 //0, 0,
			 rcClient.left, rcClient.bottom-cyVScroll,
			 rcClient.right, cyVScroll, 
			 //hwndParent, 
			 NULL,
			 
			 (HMENU) 0, hInst, NULL); 

	ShowWindow(hwndPB,1);
printf("griddata 1\n");

	// Gets the file descriptor associated with a stream.
	//int fd = _fileno(stream);
	// Get the length of a file in bytes
	cb = xi.Length() * yi.Length()+5;


	// Set the range and increment of the progress
	// bar. 

	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, cb)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
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

		printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
printf("griddata 2\n");

	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );
	for (i = 0; i < len; i++)
	{
		x[i] = pxyz[i].x;
		y[i] = pxyz[i].y;
		z[i] = pxyz[i].z;

		printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
	delete[] pxyz;
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
printf("griddata 3\n");
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================

	double DX = x.Max()-x.Min();
	double DY = y.Max()-y.Min();
	double myeps = max(DX,DY);
	
	myeps *= pow(pow(10.0,-32), 1./3.);
printf("myeps = %f\n", myeps);

	Vector<bool> vb = 
		abs(x.DiffVector()) < myeps && abs(y.DiffVector()) < myeps;

	if(Find(vb).Size() > 0)
	{
printf("Find(vb).Size() = %d len = %d\n", Find(vb).Size(), len);
		MessageBox(0,"Griddata:DuplicateDataPoints","Warning",0);
	}
printf("griddata 5\n");
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
	vdouble d(len, len);
	//d = xy(:,ones(1,length(xy)));
	//d = abs(d - d.');
	// n = size(d,1);
	int  j;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
		}
	}
printf("griddata 6\n");
	//d.Write("d://_.txt","at","d");

	// Replace zeros along diagonal with ones (so these don't show up in the
	// find below or in the Green's function calculation).
	// d(1:n+1:prod(size(d))) = ones(1,n);
	for (i = 0; i < len; i++)
	{
		d(i,i) = 1.0;
	}
printf("griddata 7\n");
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
	//d.Write("d://_.txt","at","d");
	// non = find(d == 0);
	Vector<int> non = Find(d == 0);
	//if ~isempty(non),
printf("griddata 8\n");
	if (false && non.Size() > 0 )
	{
printf("griddata (non.Size() > 0 )\n");
		int non_size = non.Size();
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
		c = c[k];
		//v = (z(r) + z(c))/2; % Average non-distinct pairs
		vdouble v (r.Length());
		for (i = 0; i < r.Length(); i++)
		{
			v[i] = 0.5*(z[int(r[i])] + z[int(c[i])]);
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
		for (i = 0; i < r.Length(); i++)
		{
			z[int(r[i])] = v[i];
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
		for (i = 0; i < c.Length(); i++)
		{
			x.DeleteElement(int(c[i]));
			y.DeleteElement(int(c[i]));
			z.DeleteElement(int(c[i]));
		}

		len = x.Length();

		// Determine distances between points
		d.resize(len, len);
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
			{
				d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
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
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
printf("griddata 9\n");

	// Determine weights for interpolation
	//g = (d.^2) .* (log(d)-1);   % Green's function.
	vdouble g (len,len);
	for (i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
		}
	}
printf("griddata 10\n");
		
	//g.Write("d://_.txt","at","g");
	// Fixup value of Green's function along diagonal
	//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
	for (i = 0; i < len; i++)
	{
		g(i,i) = 0.0;
	}
printf("griddata 11\n");
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
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
	vdouble weights;
	double det;
	g.sls_det(z,weights,det);
#endif
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
printf("griddata 12\n");

	//weights.Write("d://_.txt","at","weights");

	//[m,n] = size(xi);
	int m = xi.Length();
	int n = yi.Length();
	zi.resize(n,m,0.0);
	/*
	jay = sqrt(-1);
	xy = xy.';
	*/

printf("griddata 13\n");

	// Evaluate at requested points (xi,yi).  Loop to save memory.
	d.resize(len);
	g.resize(len);
	int k;
	for (i = 0; i < m; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < len; k++)
			{
				d[k] = sqrt( pow(x[k] - xi[i], 2.0) + pow(y[k] - yi[j], 2.0) );
				if (d[k] == 0.0)
					//Value of Green's function at zero
					g[k] = 0.0;
				else
					//Green's function.
					g[k] = pow(d[k], 2.0) * (log(d[k])-1.0);
			}
			//g.Write("d://_.txt","at","{{g}}");
			zi(j,i) = g.ScalarProduct(weights);
		SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
		}
	}
		
	DestroyWindow(hwndPB);
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
printf("griddata end\n");

	//----------------------------------------------------------
	return 0;

}


#endif

size_t do_quads_indexation(size_t len,			
						   vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid,
			 vector<vector<vector<COORDINATES> > >& w, long m_1, long n_1)
{
	if (grid)
	{
		//пространственная индексация - делим площадку на клетки и в каждую клетку складываем координаты попадающих в неё точек
		w.resize(m_1);
		for (long ii = 0; ii < m_1; ii++)
		{
			w[ii].resize(n_1);
			for (long jj = 0; jj < n_1; jj++)
			{
				w[ii][jj].resize(0);
			}
		}

		for (size_t k = 0; k < len; k++)
		{
			long ii = long((x[k] - grid->gridSection.xLL) / grid->gridSection.xSize);
			long jj = long((y[k] - grid->gridSection.yLL) / grid->gridSection.ySize);
			
			if (ii >= 0 && ii < m_1 && jj >= 0 && jj < n_1)
			{
				COORDINATES crd;
				crd.x = x[k];
				crd.y = y[k];
				crd.z = z[k];

				w[ii][jj].push_back(crd);
			}
		}

		size_t start_size = 0;

		for (long ii = 0; ii < m_1; ii++)
		{
			for (long jj = 0; jj < n_1; jj++)
			{
				start_size += w[ii][jj].size();
			}
		}

		return start_size;
	}
	return 0;
}



size_t remove_repeate_points(double myeps, vector<vector<vector<COORDINATES> > >& w, long m_1, long n_1)
{
	// убираем повторяющиеся точки

	//Рассмотрим основные этапы предложенного способа. 
	//На этапе обработки совпадающих точек в XY-пространстве 
	//учитывается соотношение объема ис-ходных данных и объема 
	//восстановленной сети. Если это соотношение невели-ко, то в 
	//целях минимизации временных затрат целесообразно разрядить 
	//исход-ную сеть точек без существенного ущерба для точности 
	//восстановления. Эта обработка особенно необходима в случае 
	//кластерного расположения исходных точек. Для этого можно 
	//удалить точки, расстояние между которым превышает заданное 
	//значение.
	//Суть предложенного алгоритма удаления совпадающих точек: 
	//для каждой точки исходного набора выполняется поиск точек, 
	//попадающих в окружность с центром в этой точке и заданным 
	//радиусом. В исходный набор точек вносится новая точка с 
	//усредненными XY-координатами (для текущей точки и 
	//найден-ной группы точек) и значением признака, 
	//вычисленным по выбранному прави-лу. Текущая точка 
	//и найденная группа точек из исходного набора исключаются. 
	//Алгоритм продолжает свою работу до тех пор, пока не дойдет 
	//до конца исход-ного набора точек.
	
	for (long ii = 0; ii < m_1; ii++)
	{
		for (long jj = 0; jj < n_1; jj++)
		{
e_start_of_cell:
			printf ("W[%d][%d].size()=%d\n", ii, jj, w[ii][jj].size());
			for (long k = 0; k < (long)w[ii][jj].size(); k++)
			{
				// тут мы выбрали текущую точку
				// printf ("W[%d][%d].size()=%d\t", ii, jj, W[ii][jj].size());
				vector<prostranstven_index> V;
				V.clear();
				// будем искать расстояния от текущей точки до точек, попадающих в её квадрат и в соседние квадраты
				for (long ii_ = ii - 1; ii_ <= ii + 1; ii_++)
				{
					for (long jj_ = jj - 1; jj_ <= jj + 1; jj_++)
					{
						if (ii_ >= 0 && ii_ < m_1 && jj_ >= 0 && jj_ < n_1)
						{
							for (long k_ = 0; k_ < (long)w[ii_][jj_].size(); k_++)
							{
								if (!(ii == ii_ && jj == jj_ && k == k_))
								{
									double dist2 = sqrt(
										pow(w[ii_][jj_][k_].x - w[ii][jj][k].x,2.0)
										+
										pow(w[ii_][jj_][k_].y - w[ii][jj][k].y,2.0)
										);

									if (dist2 < myeps)
									{
										prostranstven_index pi;

										pi.ii = ii_;
										pi.jj = jj_;
										pi.k  = k_;

										pi.x = w[ii_][jj_][k_].x;
										pi.y = w[ii_][jj_][k_].y;
										pi.z = w[ii_][jj_][k_].z;

										V.push_back(pi);
									}
								}
							}
						}
					}
				}
				//printf ("V.size() = %d\n",V.size());
				if (V.size() > 0)
				{
					// усредняем совпадающие точки
					double mean_X = w[ii][jj][k].x;
					double mean_Y = w[ii][jj][k].y;
					double mean_Z = w[ii][jj][k].z;

					for (size_t iv = 0; iv < V.size(); iv++)
					{
						mean_X += V[iv].x;
						mean_Y += V[iv].y;
						mean_Z += V[iv].z;
					}

					mean_X /= V.size()+1;
					mean_Y /= V.size()+1;
					mean_Z /= V.size()+1;

					w[ii][jj][k].x = mean_X;
					w[ii][jj][k].y = mean_Y;
					w[ii][jj][k].z = mean_Z;

					// удаляем точки
					for (int iv = (int)V.size()-1; iv >= 0; iv--)
					{
						vector<COORDINATES>::iterator ic;
						long k_;
						for (ic = w[V[iv].ii][V[iv].jj].begin(),k_=0; ic != w[V[iv].ii][V[iv].jj].end(); ic++,k_++)
						{
							if (k_ == V[iv].k)
							{
								printf("erasing %d %d %d \n",
									V[iv].ii, V[iv].jj, V[iv].k);

								w[V[iv].ii][V[iv].jj].erase(ic);
								break;
							}
						}
						
					}

					// и возвращаемся к началу цикла обработки клетки
					goto e_start_of_cell;
				}
			}
		}
	}


	size_t end_size = 0;

	for (long ii = 0; ii < m_1; ii++)
	{
		for (long jj = 0; jj < n_1; jj++)
		{
			end_size += w[ii][jj].size();
		}
	}
	return end_size;
}
bool get_quads_points(double x_i, double y_j, long ii, long jj, vector<vector<vector<COORDINATES> > >& w, long m_1, long n_1, vector<point_with_distance>& pts )
{
	if(ii >= 0 && ii < m_1 && jj >= 0 && jj < n_1)
	{
		size_t len = w[ii][jj].size();
		for(size_t k = 0; k < len; k++)
		{
			point_with_distance pwd;

			pwd.x = w[ii][jj][k].x;
			pwd.y = w[ii][jj][k].y;
			pwd.z = w[ii][jj][k].z;

			double dx = pwd.x - x_i;
			double dy = pwd.y - y_j;

			pwd.dist = sqrt(
				pow(dx, 2.0) 
				+
				pow(dy, 2.0) 
				);

			double cosine = dx / pwd.dist;

			pwd.angle = dy > 0 ? acos (cosine) : - acos (cosine);


			pts.push_back(pwd);
		}
		return true;
	}
	return false;
}
void get_quads_contour_points(long r, double x_i, double y_j, long ii, long jj, vector<vector<vector<COORDINATES> > >& w, long m_1, long n_1, vector<point_with_distance>& pts)
{
	//обход по контуру с плечом r вокруг точки

	// четыре цикла
	long iii,jjj;

	iii = ii + r;
	for (jjj = jj + r; jjj > jj - r - 1; jjj--)
		get_quads_points(x_i, y_j, iii, jjj, w, m_1, n_1, pts);

	jjj = jj - r - 1;
	for (iii = ii + r; iii > ii - r - 1; iii--)
		get_quads_points(x_i, y_j, iii, jjj, w, m_1, n_1, pts);

	iii = ii - r - 1;
	for (jjj = jj - r - 1; jjj < jj + r; jjj++)
		get_quads_points(x_i, y_j, iii, jjj, w, m_1, n_1, pts);

	jjj = jj + r;
	for (iii = ii - r - 1; iii < ii + r; iii++)
		get_quads_points(x_i, y_j, iii, jjj, w, m_1, n_1, pts);

}


double Green_fun(double x_i, double y_j,
				 size_t _use_points,
				 vector<point_with_distance>& pts)
{
	static vdouble d;
	static vdouble g;

	static vdouble D;
	static vdouble G;

	static vdouble weights;

	int use_points = (int) _use_points;

	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	//double z_value = 0.000000;

	if (use_points > 1) 
	{
		//printf("use_points = %d\n", use_points);

		d.resize(use_points, use_points);				
		g.resize(use_points, use_points);

		D.resize(use_points);				
		G.resize(use_points);

		//d = xy(:,ones(1,length(xy)));
		//d = abs(d - d.');
		// n = size(d,1);
		int  i,j;
		for (i = 0; i < use_points; i++)
		{
			for (j = 0; j < use_points; j++)
			{
				d(i,j) = sqrt( 
					pow(pts[i].x - pts[j].x, 2.0) 
					+ 
					pow(pts[i].y - pts[j].y, 2.0) 
					);
			}
		}
		//d.Write("d://_.txt","at","d");

		// Replace zeros along diagonal with ones (so these don't show up in the
		// find below or in the Green's function calculation).
		// d(1:n+1:prod(size(d))) = ones(1,n);
		for (i = 0; i < use_points; i++)
		{
			d(i,i) = 1.0;
		}

		// Determine weights for interpolation
		//g = (d.^2) .* (log(d)-1);   % Green's function.
		for (i = 0; i < use_points; i++)
		{
			for(j = 0; j < use_points; j++)
			{
				g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
			}
		}
			
		//g.Write("d://_.txt","at","g");
		// Fixup value of Green's function along diagonal
		//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
		for (i = 0; i < use_points; i++)
		{
			g(i,i) = 0.0;
		}


		double det;
		vdouble z_(use_points);
		for(i = 0; i < use_points; i++)
			z_[i] = pts[i].z;
		g.sls_det(z_,weights,det);

		//weights.Write("d://_.txt","at","weights");

		//[m,n] = size(xi);
		// Evaluate at requested points (xi,yi).  Loop to save memory.

		for (int k = 0; k < use_points; k++)
		{
			//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
			D[k] = sqrt( pow(pts[k].x - x_i, 2.0) + pow(pts[k].y - y_j, 2.0) );
			if (D[k] == 0.0)
				//Value of Green's function at zero
				G[k] = 0.0;
			else
				//Green's function.
				G[k] = pow(D[k], 2.0) * (log(D[k])-1.0);
		}
		//}
		//g.Write("d://_.txt","at","{{g}}");
		z_value = G.ScalarProduct(weights);
	}

	return z_value;

}


double Green_fun(double x_i, double y_j, double delta_phi,
				 size_t _use_points,
				 vector<point_with_distance>& pts)
{
	vector<point_with_distance> pts_;

	static vdouble d;
	static vdouble g;

	static vdouble D;
	static vdouble G;

	static vdouble weights;

	//double z_value = 0.000000;
	if (_use_points > 0) 
	{

		//vector<point_with_distance>::iterator it_stop = pts.begin()+use_points;
        point_with_distance::s_points_sort_mode = point_with_distance_points_sort_mode_by_angle;
		std::sort(pts.begin(), pts.begin()+_use_points);

//		double distN;
		double delta_angle_pre, delta_angle_post;

		size_t use_points_1 = _use_points - 1;


		for (size_t i = 0; i < _use_points; i++)
		{
			//printf("pts[%d].angle = %f\tpts[%d].dist = %f\n", i, 180*pts[i].angle/PI, i, pts[i].dist);

			if(i > 0)
			{
				delta_angle_pre = pts[i].angle - pts[i-1].angle;
				if (delta_angle_pre < delta_phi && pts[i].dist >= pts[i-1].dist)
					continue;
			}
			else//i == 0
			{
				delta_angle_pre = pts[0].angle - pts[use_points_1].angle + 2*PI;
				if (delta_angle_pre < delta_phi && pts[0].dist >= pts[use_points_1].dist)
					continue;
			}

			if (i < use_points_1)
			{
				delta_angle_post = pts[i+1].angle - pts[i].angle;
				if (delta_angle_post < delta_phi && pts[i].dist >= pts[i+1].dist)
					continue;
			}
			else//i == use_points_1 == use_points - 1
			{
				delta_angle_post = pts[0].angle - pts[i].angle + 2*PI;
				if (delta_angle_post < delta_phi && pts[i].dist >= pts[0].dist)
					continue;
			}



			//if (pts[i].dist == 0.0) return pts[i].z;
			//distN = pow(pts[i].dist, pw);
			//sum_num += pts[i].z / distN;
			//sum_den += 1.0 / distN;


			pts_.push_back(pts[i]);
		}
	}

	int use_points = (int) pts_.size();

	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
	
	if (use_points > 0) 
	{

		//printf("use_points = %d\n", use_points);

		d.resize(use_points, use_points);				
		g.resize(use_points, use_points);

		D.resize(use_points);				
		G.resize(use_points);

		//d = xy(:,ones(1,length(xy)));
		//d = abs(d - d.');
		// n = size(d,1);
		int  i,j;
		for (i = 0; i < use_points; i++)
		{
			for (j = 0; j < use_points; j++)
			{
				d(i,j) = sqrt( 
					pow(pts_[i].x - pts_[j].x, 2.0) 
					+ 
					pow(pts_[i].y - pts_[j].y, 2.0) 
					);
			}
		}
		//d.Write("d://_.txt","at","d");

		// Replace zeros along diagonal with ones (so these don't show up in the
		// find below or in the Green's function calculation).
		// d(1:n+1:prod(size(d))) = ones(1,n);
		for (i = 0; i < use_points; i++)
		{
			d(i,i) = 1.0;
		}

		// Determine weights for interpolation
		//g = (d.^2) .* (log(d)-1);   % Green's function.
		for (i = 0; i < use_points; i++)
		{
			for(j = 0; j < use_points; j++)
			{
				g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
			}
		}
			
		//g.Write("d://_.txt","at","g");
		// Fixup value of Green's function along diagonal
		//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
		for (i = 0; i < use_points; i++)
		{
			g(i,i) = 0.0;
		}


		double det;
		vdouble z_(use_points);
		for(i = 0; i < use_points; i++)
			z_[i] = pts_[i].z;
		g.sls_det(z_,weights,det);

		//weights.Write("d://_.txt","at","weights");

		//[m,n] = size(xi);
		// Evaluate at requested points (xi,yi).  Loop to save memory.

		for (int k = 0; k < use_points; k++)
		{
			//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
			D[k] = sqrt( pow(pts_[k].x - x_i, 2.0) + pow(pts_[k].y - y_j, 2.0) );
			if (D[k] == 0.0)
				//Value of Green's function at zero
				G[k] = 0.0;
			else
				//Green's function.
				G[k] = pow(D[k], 2.0) * (log(D[k])-1.0);
		}
		//}
		//g.Write("d://_.txt","at","{{g}}");
		z_value = G.ScalarProduct(weights);
	}

	return z_value;

}


double dist_fun(double x_i, double y_j, double pw, double delta_phi,
				 size_t use_points,
				 vector<point_with_distance>& pts)
{
	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double sum_num = 0.0, sum_den = 0.0;
	if (use_points > 0) 
	{

		//vector<point_with_distance>::iterator it_stop = pts.begin()+use_points;
        point_with_distance::s_points_sort_mode = point_with_distance_points_sort_mode_by_angle;
		std::sort(pts.begin(), pts.begin()+use_points);

		double distN;
		double delta_angle_pre, delta_angle_post;

		size_t use_points_1 = use_points - 1;


		for (size_t i = 0; i < use_points; i++)
		{
			//printf("pts[%d].angle = %f\tpts[%d].dist = %f\n", i, 180*pts[i].angle/PI, i, pts[i].dist);

			if(i > 0)
			{
				delta_angle_pre = pts[i].angle - pts[i-1].angle;
				if (delta_angle_pre < delta_phi && pts[i].dist >= pts[i-1].dist)
					continue;
			}
			else//i == 0
			{
				delta_angle_pre = pts[0].angle - pts[use_points_1].angle + 2*PI;
				if (delta_angle_pre < delta_phi && pts[0].dist >= pts[use_points_1].dist)
					continue;
			}

			if (i < use_points_1)
			{
				delta_angle_post = pts[i+1].angle - pts[i].angle;
				if (delta_angle_post < delta_phi && pts[i].dist >= pts[i+1].dist)
					continue;
			}
			else//i == use_points_1 == use_points - 1
			{
				delta_angle_post = pts[0].angle - pts[i].angle + 2*PI;
				if (delta_angle_post < delta_phi && pts[i].dist >= pts[0].dist)
					continue;
			}

			if (pts[i].dist == 0.0) return pts[i].z;
			distN = pow(pts[i].dist, pw);
			sum_num += pts[i].z / distN;
			sum_den += 1.0 / distN;

		}	
		z_value = sum_num / sum_den;
	}
	else
		printf ("warning: use_points == 0!!1\n");

	return z_value;
}
double dist_fun(double x_i, double y_j, double pw, double add_pw, double delta_phi,
				 size_t use_points,
				 vector<point_with_distance>& pts)
{
	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double sum_num = 0.0, sum_den = 0.0;
	if (use_points > 0) 
	{

		//vector<point_with_distance>::iterator it_stop = pts.begin()+use_points;
        point_with_distance::s_points_sort_mode = point_with_distance_points_sort_mode_by_angle;
		std::sort(pts.begin(), pts.begin()+use_points);

		double distN;
		double delta_angle_pre, delta_angle_post, delta_angle;
		double delta_dist_pre, delta_dist_post, delta_dist;

		size_t use_points_1 = use_points - 1;
		double nn;
		double dpw;

		double max_dist = -DBL_MAX;
		double min_dist = DBL_MAX;

		for (size_t i = 0; i < use_points; i++)
		{
			if(pts[i].dist > max_dist) max_dist = pts[i].dist;
			if(pts[i].dist < min_dist) min_dist = pts[i].dist;
		}

		double dist_diapazon = max_dist - min_dist;

		double c = 1.0 / dist_diapazon; // коэффициент перед логистической сигмоидой

		for (size_t i = 0; i < use_points; i++)
		{
			//printf("pts[%d].angle = %f\tpts[%d].dist = %f\n", i, 180*pts[i].angle/PI, i, pts[i].dist);
			dpw = 0.0;

			if(i > 0)
			{
				delta_angle_pre = pts[i].angle - pts[i-1].angle;
				delta_dist_pre = pts[i].dist - pts[i-1].dist;
				if (delta_angle_pre < delta_phi && pts[i].dist >= pts[i-1].dist)
					dpw+=add_pw;
			}
			else//i == 0
			{
				delta_angle_pre = pts[0].angle - pts[use_points_1].angle + 2*PI;
				delta_dist_pre = pts[0].dist - pts[use_points_1].dist;
				if (delta_angle_pre < delta_phi && pts[0].dist >= pts[use_points_1].dist)
					dpw+=add_pw;
			}

			if (i < use_points_1)
			{
				delta_angle_post = pts[i+1].angle - pts[i].angle;
				delta_dist_post = pts[i+1].dist - pts[i].dist;
				if (delta_angle_post < delta_phi && pts[i].dist >= pts[i+1].dist)
					dpw+=add_pw;
			}
			else//i == use_points_1 == use_points - 1
			{
				delta_angle_post = pts[0].angle - pts[i].angle + 2*PI;
				delta_dist_post = pts[0].dist - pts[i].dist;
				if (delta_angle_post < delta_phi && pts[i].dist >= pts[0].dist)
					dpw+=add_pw;
			}

			if (pts[i].dist == 0.0) return pts[i].z;

			delta_angle = min(delta_angle_pre, delta_angle_post);
			delta_dist = delta_dist_pre + delta_dist_post;

			nn = 1.0 + 1.0/(1.0 + exp(-c*delta_dist)) * ((pw*delta_phi)/delta_angle);

//			if (nn > 10.0)
//				nn = 10.0;

      

			distN = pow(pts[i].dist, pw+dpw);
			//distN = pts[i].dist / nn;

			sum_num += pts[i].z / distN;
			sum_den += 1.0      / distN;

		}	
		z_value = sum_num / sum_den;
	}
	else
		printf ("warning: use_points == 0!!1\n");

	return z_value;
}
double dist_fun(double x_i, double y_j, double pw,
				 size_t use_points,
				 vector<point_with_distance>& pts)
{
	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double sum_num = 0.0, sum_den = 0.0;
	if (use_points > 0) 
	{
		double distN;
		for (size_t i = 0; i < use_points; i++)
		{
			if (pts[i].dist == 0.0) return pts[i].z;
			distN = pow(pts[i].dist, pw);
			sum_num += pts[i].z / distN;
			sum_den += 1.0 / distN;
		}	
		z_value = sum_num / sum_den;
	}
	else
		printf ("warning: use_points == 0!!1\n");

	return z_value;
}
/*double dist_fun(double x_i, double y_j,
				 size_t use_points,
				 vector<point_with_distance>& pts)
{
	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double sum_num = 0.0, sum_den = 0.0;
	if (use_points > 0) 
	{
		for (size_t i = 0; i < use_points; i++)
		{
			if (pts[i].dist == 0.0) return pts[i].z;
			sum_num += pts[i].z / pts[i].dist;
			sum_den += 1.0 / pts[i].dist;
		}	
		z_value = sum_num / sum_den;
	}
	else
		printf ("warning: use_points == 0!!1\n");

	return z_value;
}
double dist2_fun(double x_i, double y_j,
				 size_t use_points,
				 vector<point_with_distance>& pts)
{
	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double sum_num = 0.0, sum_den = 0.0;
	if (use_points > 0) 
	{
		double dist2;
		for (size_t i = 0; i < use_points; i++)
		{
			if (pts[i].dist == 0.0) return pts[i].z;
			dist2 = pts[i].dist * pts[i].dist;
			sum_num += pts[i].z / dist2;
			sum_den += 1.0 / dist2;
		}	
		z_value = sum_num / sum_den;
	}
	else
		printf ("warning: use_points == 0!!1\n");

	return z_value;
}

double dist3_fun(double x_i, double y_j,
				 size_t use_points,
				 vector<point_with_distance>& pts)
{
	double z_value = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value

	double sum_num = 0.0, sum_den = 0.0;
	if (use_points > 0) 
	{
		double dist3;
		for (size_t i = 0; i < use_points; i++)
		{
			if (pts[i].dist == 0.0) return pts[i].z;
			dist3 = pts[i].dist * pts[i].dist * pts[i].dist;
			sum_num += pts[i].z / dist3;
			sum_den += 1.0 / dist3;
		}	
		z_value = sum_num / sum_den;
	}
	else
		printf ("warning: use_points == 0!!1\n");

	return z_value;
}*/
bool fill_grid(Grid * grid, 
			   vector<vector<vector<COORDINATES> > >& w, long m_1, long n_1,			   		
			   double& min_z, double& max_z,
			   size_t max_len, griddata_2_param * param)
{
	int dist_fun_number = 0;
	double pw = 3.0, add_pw = 0.5, delta_phi = 30.0;
	
	if (param)
	{
		dist_fun_number = param->dist_fun_number;
		switch(dist_fun_number)
		{
		case 1:
			//z_value = dist_fun(x_i, y_j, pw, use_points, pts);
			pw = param->pw;
			break;
		case 2:
			//z_value = dist_fun(x_i, y_j, pw, delta_phi*PI/180.0, use_points, pts);
			pw = param->pw;
			delta_phi = param->delta_phi;
			break;
		case 3:
			//z_value = dist_fun(x_i, y_j, pw, add_pw, delta_phi*PI/180.0, use_points, pts);
			pw = param->pw;
			add_pw = param->add_pw;
			delta_phi = param->delta_phi;
			break;
		case 4:
			//z_value = Green_fun(x_i, y_j, use_points, pts);
			break;
		case 5:
			//z_value = Green_fun(x_i, y_j, delta_phi*PI/180.0, use_points, pts);
			delta_phi = param->delta_phi;
			break;
		default:
			return false;
		}
	}
	else
	{
		cout << "dist_fun_number [1, 2, 3, 4, 5]:" << endl;
		cout << "1 - dist_fun(x_i, y_j, pw, use_points, pts)" << endl;
		cout << "2 - dist_fun(x_i, y_j, pw, delta_phi*PI/180.0, use_points, pts)" << endl;
		cout << "3 - dist_fun(x_i, y_j, pw, add_pw, delta_phi*PI/180.0, use_points, pts)" << endl;
		cout << "4 - Green_fun(x_i, y_j, use_points, pts)" << endl;
		cout << "5 - Green_fun(x_i, y_j, delta_phi*PI/180.0, use_points, pts)" << endl;
		cin >> dist_fun_number;


		switch(dist_fun_number)
		{
		case 1:
			//z_value = dist_fun(x_i, y_j, pw, use_points, pts);
			cout << "enter pw:" << endl;
			cin >> pw;
			break;
		case 2:
			//z_value = dist_fun(x_i, y_j, pw, delta_phi*PI/180.0, use_points, pts);
			cout << "enter pw:" << endl;
			cin >> pw;
			cout << "enter delta_phi:" << endl;
			cin >> delta_phi;
			break;
		case 3:
			//z_value = dist_fun(x_i, y_j, pw, add_pw, delta_phi*PI/180.0, use_points, pts);
			cout << "enter pw:" << endl;
			cin >> pw;
			cout << "enter add_pw:" << endl;
			cin >> add_pw;
			cout << "enter delta_phi:" << endl;
			cin >> delta_phi;
			break;
		case 4:
			//z_value = Green_fun(x_i, y_j, use_points, pts);
			break;
		case 5:
			//z_value = Green_fun(x_i, y_j, delta_phi*PI/180.0, use_points, pts);
			cout << "enter delta_phi:" << endl;
			cin >> delta_phi;
			break;
		default:
			return false;
		}
	}
	if(grid)
	{
		double min_quad_size = min(grid->gridSection.xSize, grid->gridSection.ySize);
		for (long ii = 0; ii < grid->gridSection.nCol; ii++)
		{
			printf("ii = %ld m = %ld\n", ii, grid->gridSection.nCol);
			double x_i = grid->gridSection.xLL + ii*grid->gridSection.xSize;
			for (long jj = 0; jj < grid->gridSection.nRow; jj++)
			{
				double y_j = grid->gridSection.yLL + jj*grid->gridSection.ySize;

				vector<point_with_distance> pts;

				pts.clear();

                point_with_distance::s_points_sort_mode = point_with_distance_points_sort_mode_by_dist;
					
				size_t npts = 0;

				for (long r = 0;;r++)
				{
					// максимальный допустимый радиус, внутри которого мы можем брать точки
					// это нужно вследствие двух причин: непрямоугольности 
					// (в общем случае) клетки и удалённости угловых частей прямоугольника
					// максимальный допустимый радиус должен быть равен минимальному ребру прямоугольника
					double max_R = min_quad_size * (r + 1);
					get_quads_contour_points(r, x_i, y_j, ii, jj, w, m_1, n_1, pts);

					std::sort(pts.begin(), pts.end());

					// теперь ищем сколько и какие точки попадают внутрь 
					// максимального допустимого радиуса
					
					npts = 0;
// что быстрее???
#if 0

					for (vector<point_with_distance>::iterator ipts = pts.begin();
						ipts != pts.end(); ipts++)
					{
						if ((*ipts).dist <= max_R)
							npts++;
						else
							break;
					}
#else
					for (npts = 0; npts < pts.size(); npts++)
					{
						if (pts[npts].dist > max_R)
							break;
					}
#endif

					if (npts >= max_len)
						break;
				}

				//здесь мы нашли некоторое количество use_points ближайших точек
				size_t use_points = npts < max_len ? npts : max_len;

				// тут мы можем выбрать тот или иной алгоритм 
				// вычисления z_value - значения в текущей точке сетки 

				double z_value = 0;

				switch(dist_fun_number)
				{
				case 1:
					z_value = dist_fun(x_i, y_j, pw, use_points, pts);
					break;
				case 2:
					z_value = dist_fun(x_i, y_j, pw, delta_phi*PI/180.0, use_points, pts);
					break;
				case 3:
					z_value = dist_fun(x_i, y_j, pw, add_pw, delta_phi*PI/180.0, use_points, pts);
					break;
				case 4:
					z_value = Green_fun(x_i, y_j, use_points, pts);
					break;
				case 5:
					z_value = Green_fun(x_i, y_j, delta_phi*PI/180.0, use_points, pts);
					break;
				}


				// полученное значение z_value записываем в грид
				grid->gridSection.z[jj][ii] = z_value;
				if (z_value != BLANK_VALUE)
				{
					if (max_z < z_value) max_z = z_value;
					if (min_z > z_value) min_z = z_value;
				}
			}
		}
		return true;
	}
	return false;
}
int griddata_2(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void * _param, bool to_allocate)

{					
	// ищем max_len ближайших точек
	size_t max_len = 8;
	griddata_2_param * param = reinterpret_cast<griddata_2_param *>(_param);
	
	if (param)
	{
		max_len = param->max_len;
	}
	else
	{
		cout << "enter max_len(8):" << endl;
		cin >> max_len;
	}

	size_t len = x.size();
	
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;

	if (grid)
	{
		//long m = (*xi).Length();
		//long n = (*yi).Length();
		//long m = grid->gridSection.nCol;
		//long n = grid->gridSection.nRow;

		long m_1 = grid->gridSection.nCol-1;
		long n_1 = grid->gridSection.nRow-1;

		if (m_1 < 0 || n_1 < 0)
			return -2;

		//(*zi).resize(n, m, 0.0);
		if (to_allocate)
			grid->gridSection.z = AllocDoubleMat(grid->gridSection.nRow, grid->gridSection.nCol);
		grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
		double min_z = DBL_MAX;
		double max_z = -DBL_MAX;

		//координаты чётырёх углов площадки
		double x0 = grid->gridSection.xLL;
		double y0 = grid->gridSection.yLL;
		double xm = grid->gridSection.xLL + (grid->gridSection.nCol-1)*grid->gridSection.xSize;
		double yn = grid->gridSection.yLL + (grid->gridSection.nRow-1)*grid->gridSection.ySize;
		
		//Площадь плошадки
		double S = fabs((xm-x0)*(yn-y0));

		//средняя плотность точек
		double plotnost_t = double(len) / S;

		//матожидание расстояния между каждой точкой и ближайшей к ней соседней
		double delta_ma = 0.5 / sqrt(plotnost_t);

		// радиус внутри которого ищем ближайшие точки
		double R = delta_ma*5.0;

		//пространственная индексация - делим площадку на клетки и в каждую клетку складываем координаты попадающих в неё точек
		vector<vector<vector<COORDINATES> > > W;
		size_t start_size = do_quads_indexation(len, x, y, z, grid, W, m_1, n_1);

		double myeps = max(fabs(xm-x0), fabs(yn-y0));
		printf("myeps0 = %f\n", myeps);
		myeps *= pow(pow(10.0,-32), 1./3.);
		//myeps *= 0.005;
		printf("myeps = %f\n", myeps);

		// убираем повторяющиеся точки
		size_t end_size = remove_repeate_points(myeps, W, m_1, n_1);

		printf("start_size = %u end_size =%u\n", start_size, end_size);

		if (!fill_grid(grid, W, m_1, n_1, 		
			   min_z, max_z,
			   max_len, param))
		{
			return -1;
		}

		grid->gridSection.zMax = max_z;
		grid->gridSection.zMin = min_z;

		grid->faultSection.nTraces = 0;
		grid->faultSection.nVertices = 0;
		grid->faultSection.traces = NULL;
		grid->faultSection.vertexes = NULL;

		return 0;
	}
	return -1;
}





bool get_tria_points(geometry2D::PolygonEx* p, double x_i, double y_j, vector<double>& z, vector<point_with_distance>& pts )
{
	if (p)
	{
		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			//******************************
			point_with_distance pwd;
			pwd.x = p->point().x;
			pwd.y = p->point().y;
			pwd.z = z[p->point().index];

			double dx = pwd.x - x_i;
			double dy = pwd.y - y_j;
			
			pwd.dist = sqrt(
				pow(dx, 2.0) 
				+
				pow(dy, 2.0) 
				);
			
			double cosine = dx / pwd.dist;
	        
			pwd.angle = dy > 0 ? acos (cosine) : - acos (cosine);
			
			pts.push_back(pwd);
		}
		return true;
	}
	return false;
}

/*double GetValue(int order, vector<double> & sol,	// формируемая матрица
					   size_t cols, 
					  vector<double> & z,			// отметки высот
					  geometry2D::Point pt,		// дополнительная точка, 
					  // которая должна удовлетворять 
					  // уравнению кубической интерполяции
					  PolygonEx * p,
					  vector<Point> &base_points
					  )
{
	size_t nk;
	switch(order)
	{
		case 2:
            nk = 5;
			break;
		case 3:
            nk = 9;
			break;
	}

	geometry2D::Point ptj;		// базовая точка
	size_t index = p->index;
	ptj = base_points[index];
	size_t index_9 = index*nk;

	if (!(ptj.index > -1) || !(ptj.index < z.size()))
	{
		char err[1024];
		sprintf(err, "(!(ptj.index (%d) > -1) || !(ptj.index < z.size(%u)))", ptj.index, z.size());
		MessageBox(0, err, "GetValue", MB_OK);
		return BLANK_VALUE;
	}

	if (index_9+nk-1 >= cols)
	{
		char err[1024];
		sprintf(err, "index_9+nk-1 (%u) >= cols (%u)", index_9+nk-1, cols);
		MessageBox(0, err, "GetValue", MB_OK);
		return BLANK_VALUE;
	}		

	double zz;
	switch (order)
	{
	case 2:
		{
			zz = z[ptj.index] +
				sol[index_9+0] * ( pt.x - ptj.x) + //с1
				sol[index_9+1] * ( pt.y - ptj.y) + //с2
				
				sol[index_9+2] * (pt.x - ptj.x) * (pt.x - ptj.x) +//с3
				sol[index_9+3] * (pt.x - ptj.x) * (pt.y - ptj.y) +//с4
				sol[index_9+4] * (pt.y - ptj.y) * (pt.y - ptj.y);//с5				
		}
		break;	
	case 3:
		{
			zz = z[ptj.index] +
				sol[index_9+0] * ( pt.x - ptj.x) + //с1
				sol[index_9+1] * ( pt.y - ptj.y) + //с2
				
				sol[index_9+2] * (pt.x - ptj.x) * (pt.x - ptj.x) +//с3
				sol[index_9+3] * (pt.x - ptj.x) * (pt.y - ptj.y) +//с4
				sol[index_9+4] * (pt.y - ptj.y) * (pt.y - ptj.y) +//с5
				
				sol[index_9+5] * (pt.x - ptj.x) * (pt.x - ptj.x) * (pt.x - ptj.x) +//с6
				sol[index_9+6] * (pt.x - ptj.x) * (pt.x - ptj.x) * (pt.y - ptj.y) +//с7
				sol[index_9+7] * (pt.x - ptj.x) * (pt.y - ptj.y) * (pt.y - ptj.y) +//с8
				sol[index_9+8] * (pt.y - ptj.y) * (pt.y - ptj.y) * (pt.y - ptj.y);//с9
		}
		break;
	}

	return zz;
}*/

double GetValue_(int N_trias, int order_t, int order_c, 
				 size_t nk_t, size_t nk_c,				 
				 vector<double> & sol,	// формируемая матрица
					   size_t cols, 
					  vector<double> & z,			// отметки высот
					  geometry2D::Point pt,		// дополнительная точка, 
					  // которая должна удовлетворять 
					  // уравнению кубической интерполяции
					  PolygonEx * p,
					  vector<geometry2D::Point> &base_points
					  )
{

	geometry2D::Point ptj;		// базовая точка
	size_t index = p->index;
	ptj = base_points[index];
	size_t index_10 = (int)index < N_trias ? index*nk_t : N_trias*nk_t + (index-N_trias)*nk_c;
	size_t nk = (int)index < N_trias ? nk_t : nk_c;
	int order = (int)index < N_trias ? order_t : order_c;

	if (index_10+nk-1 >= cols)
	{
		char err[1024];
		sprintf(err, "index_10+nk-1 (%u) >= cols (%u)", index_10+nk-1, cols);
		MessageBox(0, err, "GetValue_", MB_OK);
		return BLANK_VALUE;
	}		

	double dx = pt.x - ptj.x;
	double dy = pt.y - ptj.y;

	double zz;
	switch (order)
	{
	case 1:
		{
			zz = 
				sol[index_10+0] +
				sol[index_10+1] * dx + //с1
				sol[index_10+2] * dy ; //с2		
		}
		break;	
	case 2:
		{
			zz = 
				sol[index_10+0] +
				sol[index_10+1] * dx + //с1
				sol[index_10+2] * dy + //с2
				
				sol[index_10+3] * dx * dx +//с3
				sol[index_10+4] * dx * dy +//с4
				sol[index_10+5] * dy * dy;//с5				
		}
		break;	
	case 3:
		{
			zz = 
				sol[index_10+0] +
				sol[index_10+1] * dx + //с1
				sol[index_10+2] * dy + //с2
				
				sol[index_10+3] * dx * dx +//с3
				sol[index_10+4] * dx * dy +//с4
				sol[index_10+5] * dy * dy +//с5
				
				sol[index_10+6] * dx * dx * dx +//с6
				sol[index_10+7] * dx * dx * dy +//с7
				sol[index_10+8] * dx * dy * dy +//с8
				sol[index_10+9] * dy * dy * dy ;//с9
		}
		break;
	case 4:
		{
			zz = 
				sol[index_10+0] +
				sol[index_10+1] * dx + //с1
				sol[index_10+2] * dy + //с2
				
				sol[index_10+3] * dx * dx +//с3
				sol[index_10+4] * dx * dy +//с4
				sol[index_10+5] * dy * dy +//с5
				
				sol[index_10+6] * dx * dx * dx +//с6
				sol[index_10+7] * dx * dx * dy +//с7
				sol[index_10+8] * dx * dy * dy +//с8
				sol[index_10+9] * dy * dy * dy +//с9

				sol[index_10+10] * dx * dx * dx * dx +//с10
				sol[index_10+11] * dx * dx * dx * dy +//с11
				sol[index_10+12] * dx * dx * dy * dy +//с12
				sol[index_10+13] * dx * dy * dy * dy +//с13
				sol[index_10+14] * dy * dy * dy * dy ;//с14
		}
		break;
	}

	return zz;
}

#define USE_SECOND_DERIVATIVES_EQUATIONS 1
/*
void AddRowsToEquation(int order, 
					   vector<sparse_row> & M,	// формируемая матрица
					   size_t cols, 
					  vector<double> & B,			// формируемый вектор правых частей
					  vector<double> & z,			// отметки высот
					  PolygonEx * p,
					  vector<Point> &base_points
					  )
{
	geometry2D::Point ptj;		// базовая точка
	geometry2D::Point pt;		// дополнительная точка, 
					  // которая должна удовлетворять 
					  // уравнению кубической интерполяции


	size_t nk;
	switch(order)
	{
		case 2:
            nk = 5;
			break;
		case 3:
            nk = 9;
			break;
	}

	size_t index = p->index;
	ptj = base_points[index];
	size_t index_9 = index*nk;

	if (!(ptj.index > -1) || !(ptj.index < z.size()))
	{
		char err[1024];
		sprintf(err, "(!(ptj.index (%d) > -1) || !(ptj.index < z.size(%u)))", ptj.index, z.size());
		MessageBox(0, err, "AddRowsToEquation", MB_OK);
		return;
	}

	if (index_9+nk-1 >= cols)
	{
		char err[1024];
		sprintf(err, "index_9+nk-1 (%u) >= cols (%u)", index_9+nk-1, cols);
		MessageBox(0, err, "AddRowsToEquation", MB_OK);
		return;
	}		

	for (int i = 0; i < p->size(); i++)
	{
		p->advance(CLOCKWISE);
		Point pt = p->point();

		//AddRowToEquation(M, cols, B, z, ptj, pt, index_9);			
		if (pt != ptj && pt.index > -1 && pt.index < z.size())
		{			
			// добавляем строку в уравнение
			
			sparse_row row; 
			row.clear();

			switch(order)
			{
			case 3:
				row.put(index_9+5, (pt.x - ptj.x) * (pt.x - ptj.x) * (pt.x - ptj.x));//с6
				row.put(index_9+6, (pt.x - ptj.x) * (pt.x - ptj.x) * (pt.y - ptj.y));//с7
				row.put(index_9+7, (pt.x - ptj.x) * (pt.y - ptj.y) * (pt.y - ptj.y));//с8
				row.put(index_9+8, (pt.y - ptj.y) * (pt.y - ptj.y) * (pt.y - ptj.y));//с9
			case 2:
				row.put(index_9+0, pt.x - ptj.x);//с1
				row.put(index_9+1, pt.y - ptj.y);//с2

				row.put(index_9+2, (pt.x - ptj.x) * (pt.x - ptj.x));//с3
				row.put(index_9+3, (pt.x - ptj.x) * (pt.y - ptj.y));//с4
				row.put(index_9+4, (pt.y - ptj.y) * (pt.y - ptj.y));//с5
			}
			

#if SPARSE_ROW_EX
			row._order = 0;
#endif
			M.push_back(row);
			B.push_back(z[pt.index] - z[ptj.index]);
			
		}
	}
}

void AddRowsToEquation2(int order,
						vector<sparse_row> & M,	// формируемая матрица
					   size_t cols,
					  vector<double> & B,			// формируемый вектор правых частей
					  vector<double> & z,			// отметки высот
					  EdgeEx * ex,
					  vector<Point> &base_points)
{
	PolygonEx * p1 = ex->LeftPolygon();
	PolygonEx * p2 = ex->RightPolygon();
	if(p1 && p2)
	{
		size_t nk;
		switch(order)
		{
			case 2:
				nk = 5;
				break;
			case 3:
				nk = 9;
				break;
		}

		size_t index1 = p1->index < p2->index ? p1->index : p2->index;
		size_t index2 = p1->index < p2->index ? p2->index : p1->index;

		size_t index1_9 = index1*nk;
		size_t index2_9 = index2*nk;

		printf("AddRowsToEquation2 %u %u %u %u\n", index1, index2, index1_9, index2_9);

		if (index1_9+nk-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index1_9+8 (%u) >= cols (%u)", index1_9+nk-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx ", MB_OK);
			return;
		}		
		if (index2_9+nk-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index2_9+8 (%u) >= cols (%u)", index2_9+nk-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx ", MB_OK);
			return;
		}

		double x_org = ex->org.x;
		double y_org = ex->org.y;

		double x_dest = ex->dest.x;
		double y_dest = ex->dest.y;

		double x_len = x_dest - x_org;
		double y_len = y_dest - y_org;

		// базовые точки для обоих полигонов
		Point pt1j = base_points[index1];
		Point pt2j = base_points[index2];

		int ind1 = pt1j.index;
		int ind2 = pt2j.index;

		if (ind1 >= z.size() || ind1 < 0)
		{
			char err[1024];
			sprintf(err, "ind1 (%d) >= z.size() (%u) || ind1 < 0", ind1, z.size());
			MessageBox(0, err, "AddRowsToEquation EdgeEx ", MB_OK);
			return;
		}		
		if (ind2 >= z.size() || ind2 < 0)
		{
			char err[1024];
			sprintf(err, "ind2 (%d) >= z.size() (%u) || ind2 < 0", ind2, z.size());
			MessageBox(0, err, "AddRowsToEquation EdgeEx ", MB_OK);
			return;
		}
		double x_org_x1j = x_org - pt1j.x;
		double y_org_y1j = y_org - pt1j.y;

		double x_org_x2j = x_org - pt2j.x;
		double y_org_y2j = y_org - pt2j.y;

		sparse_row row;

		bool add_non_fault = true;
		bool add_second_der = false;

		bool add_first_der_x = true;
		bool add_first_der_y = true;

		//наклон ребра
#if 1
		double fabs_slope = fabs(ex->slope());

		if (fabs_slope > 1.0)
		{
			add_first_der_x = true;
			add_first_der_y = false;
		}
		else
		{
			add_first_der_x = false;
			add_first_der_y = true;
		}
#endif
		if (add_non_fault)
		{
#if SPARSE_ROW_EX
			row._order = 0;
#endif
			switch (order)
			{
			case 2:
				{
					// f(t) := 
					// (c3*x_len^2+c4*x_len*y_len+c5*y_len^2)*t^2+
					// (c1*x_len+2*c3*x_org_xj*x_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj+c2*y_len+2*c5*y_org_yj*y_len)*t+
					// zj + c1*x_org_xj+c2*y_org_yj+c4*x_org_xj*y_org_yj+c3*x_org_xj^2+c5*y_org_yj^2
					row.clear();	
					// zj + c1*x_org_xj + c2*y_org_yj + c4*x_org_xj*y_org_yj + c3*x_org_xj^2
					row.put(index1_9+0, x_org_x1j);//с1
					row.put(index1_9+1, y_org_y1j);//с2

					row.put(index1_9+2, (x_org_x1j) * (x_org_x1j));//с3
					row.put(index1_9+3, (x_org_x1j) * (y_org_y1j));//с4
					row.put(index1_9+4, (y_org_y1j) * (y_org_y1j));//с5
					

					row.put(index2_9+0, - (x_org_x2j));//с1
					row.put(index2_9+1, - (y_org_y2j));//с2

					row.put(index2_9+2, - (x_org_x2j) * (x_org_x2j));//с3
					row.put(index2_9+3, - (x_org_x2j) * (y_org_y2j));//с4
					row.put(index2_9+4, - (y_org_y2j) * (y_org_y2j));//с5
					

					M.push_back(row);	B.push_back(z[ind2] - z[ind1]);
					
					row.clear();	
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//)*t
					// (c1*x_len+2*c3*x_org_xj*x_len+c2*y_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj)*t+

					row.put(index1_9+0, x_len);//с1
					row.put(index1_9+1, y_len);//с2

					row.put(index1_9+2, 2.0 * x_org_x1j * x_len);//с3
					row.put(index1_9+3, x_len * y_org_y1j + x_org_x1j * y_len);//с4
					row.put(index1_9+4, 2.0 * y_org_y1j * y_len);//с5
					

					row.put(index2_9+0, - x_len);//с1
					row.put(index2_9+1, - y_len);//с2

					row.put(index2_9+2, - 2.0 * x_org_x2j * x_len);//с3
					row.put(index2_9+3, - (x_len * y_org_y2j + x_org_x2j * y_len));//с4
					row.put(index2_9+4, - 2.0 * y_org_y2j * y_len);//с5



					M.push_back(row);	B.push_back(0.0);
								
					row.clear();	
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					row.put(index1_9+2, x_len * x_len);//с3
					row.put(index1_9+3, x_len * y_len);//с4
					row.put(index1_9+4, y_len * y_len);//с5

					row.put(index2_9+2, - x_len * x_len);//с3
					row.put(index2_9+3, - x_len * y_len);//с4
					row.put(index2_9+4, - y_len * y_len);//с5
					
					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 3:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// f(t) := 
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

					// = 

					//(c8*x_len*y_len^2+c6*x_len^3+c7*x_len^2*y_len+c9*y_len^3)*t^3+
					//(c4*x_len*y_len+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c8*x_org_xj*y_len^2+c5*y_len^2+3*c9*y_org_yj*y_len^2+3*c6*x_org_xj*x_len^2+c7*x_len^2*y_org_yj+2*c8*x_len*y_org_yj*y_len)*t^2+
					//(c8*x_len*y_org_yj^2 + c2*y_len + c4*x_len*y_org_yj + c7*x_org_xj^2*y_len + c1*x_len+c4*x_org_xj*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c3*x_org_xj*x_len+2*c8*x_org_xj*y_org_yj*y_len+3*c6*x_org_xj^2*x_len+3*c9*y_org_yj^2*y_len+2*c5*y_org_yj*y_len)*t+
					//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3

					row.clear();	
					//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3
					row.put(index1_9+0, x_org_x1j);//с1
					row.put(index1_9+1, y_org_y1j);//с2

					row.put(index1_9+2, (x_org_x1j) * (x_org_x1j));//с3
					row.put(index1_9+3, (x_org_x1j) * (y_org_y1j));//с4
					row.put(index1_9+4, (y_org_y1j) * (y_org_y1j));//с5
					
					row.put(index1_9+5, (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с6
					row.put(index1_9+6, (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с7
					row.put(index1_9+7, (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с8
					row.put(index1_9+8, (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с9

					row.put(index2_9+0, - (x_org_x2j));//с1
					row.put(index2_9+1, - (y_org_y2j));//с2

					row.put(index2_9+2, - (x_org_x2j) * (x_org_x2j));//с3
					row.put(index2_9+3, - (x_org_x2j) * (y_org_y2j));//с4
					row.put(index2_9+4, - (y_org_y2j) * (y_org_y2j));//с5
					
					row.put(index2_9+5, - (x_org_x2j) * (x_org_x2j) * (x_org_x2j));//с6
					row.put(index2_9+6, - (x_org_x2j) * (x_org_x2j) * (y_org_y2j));//с7
					row.put(index2_9+7, - (x_org_x2j) * (y_org_y2j) * (y_org_y2j));//с8
					row.put(index2_9+8, - (y_org_y2j) * (y_org_y2j) * (y_org_y2j));//с9

					M.push_back(row);	B.push_back(z[ind2] - z[ind1]);
					
					row.clear();	
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//2*c5*y_org_yj*y_len
					//3*c6*x_org_xj^2*x_len+
					//c7*x_org_xj^2*y_len + 
					//2*c7*x_org_xj*x_len*y_org_yj+
					//c8*x_len*y_org_yj^2 + 
					//2*c8*x_org_xj*y_org_yj*y_len+
					//3*c9*y_org_yj^2*y_len+
					//)*t

					row.put(index1_9+0, x_len);//с1
					row.put(index1_9+1, y_len);//с2

					row.put(index1_9+2, 2.0 * x_org_x1j * x_len);//с3
					row.put(index1_9+3, x_len * y_org_y1j + x_org_x1j * y_len);//с4
					row.put(index1_9+4, 2.0 * y_org_y1j * y_len);//с5
					
					row.put(index1_9+5, 3.0 * x_org_x1j * x_org_x1j * x_len);//с6
					row.put(index1_9+6, x_org_x1j * x_org_x1j * y_len + 2.0 * x_org_x1j * x_len * y_org_y1j);//с7
					row.put(index1_9+7, x_len * y_org_y1j * y_org_y1j + 2.0 * x_org_x1j * y_len * y_org_y1j);//с8
					row.put(index1_9+8, 3.0 * y_org_y1j * y_org_y1j * y_len);//с9

					row.put(index2_9+0, - x_len);//с1
					row.put(index2_9+1, - y_len);//с2

					row.put(index2_9+2, - 2.0 * x_org_x2j * x_len);//с3
					row.put(index2_9+3, - (x_len * y_org_y2j + x_org_x2j * y_len));//с4
					row.put(index2_9+4, - 2.0 * y_org_y2j * y_len);//с5

					row.put(index2_9+5, - (3.0 * x_org_x2j * x_org_x2j * x_len));//с6
					row.put(index2_9+6, - (x_org_x2j * x_org_x2j * y_len + 2.0 * x_org_x2j * x_len * y_org_y2j));//с7
					row.put(index2_9+7, - (x_len * y_org_y2j * y_org_y2j + 2.0 * x_org_x2j * y_len * y_org_y2j));//с8
					row.put(index2_9+8, - (3.0 * y_org_y2j * y_org_y2j * y_len));//с9


					M.push_back(row);	B.push_back(0.0);
								
					row.clear();	
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					row.put(index1_9+2, x_len * x_len);//с3
					row.put(index1_9+3, x_len * y_len);//с4
					row.put(index1_9+4, y_len * y_len);//с5
					
					row.put(index1_9+5, 3.0 * x_org_x1j * x_len * x_len);//с6
					row.put(index1_9+6, x_len * x_len * y_org_y1j + 2.0 * x_org_x1j * x_len * y_len);//с7
					row.put(index1_9+7, x_org_x1j * y_len * y_len + 2.0 * y_org_y1j * x_len * y_len);//с8
					row.put(index1_9+8, 3.0 * y_org_y1j * y_len * y_len);//с9


					row.put(index2_9+2, - x_len * x_len);//с3
					row.put(index2_9+3, - x_len * y_len);//с4
					row.put(index2_9+4, - y_len * y_len);//с5
					
					row.put(index2_9+5, - (3.0 * x_org_x2j * x_len * x_len));//с6
					row.put(index2_9+6, - (x_len * x_len * y_org_y2j + 2.0 * x_org_x2j * x_len * y_len));//с7
					row.put(index2_9+7, - (x_org_x2j * y_len * y_len + 2.0 * y_org_y2j * x_len * y_len));//с8
					row.put(index2_9+8, - (3.0 * y_org_y2j * y_len * y_len));//с9

					M.push_back(row);	B.push_back(0.0);


					row.clear();	
					//(c8*x_len*y_len^2 + c6*x_len^3 + c7*x_len^2*y_len + c9*y_len^3)*t^3+
					row.put(index1_9+5, x_len * x_len * x_len);//с6
					row.put(index1_9+6, x_len * x_len * y_len);//с7
					row.put(index1_9+7, x_len * y_len * y_len);//с8
					row.put(index1_9+8, y_len * y_len * y_len);//с9

					row.put(index2_9+5, - x_len * x_len * x_len);//с6
					row.put(index2_9+6, - x_len * x_len * y_len);//с7
					row.put(index2_9+7, - x_len * y_len * y_len);//с8
					row.put(index2_9+8, - y_len * y_len * y_len);//с9

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
		}

		if(add_first_der_x)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			switch (order)
			{
			case 2:
				{
					// the first derivative
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_x(t) := 
					// c1+
					// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
					// c4*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// c8*(y_org-yj+(y_dest-y_org)*t)^2

					// = 
					//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
					//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
					//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

					row.clear();	
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.put(index1_9+0, 1.0);//с1

					row.put(index1_9+2, 2.0 * x_org_x1j);//с3
					row.put(index1_9+3,       y_org_y1j);//с4
					

					row.put(index2_9+0, - 1.0);//с1

					row.put(index2_9+2, - 2.0 * x_org_x2j);//с3
					row.put(index2_9+3, -       y_org_y2j);//с4
					

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//2*c3*x_len+
					//c4*y_len+
					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					row.put(index1_9+2, 2.0 * x_len);//с3
					row.put(index1_9+3,       y_len);//с4
					

					row.put(index2_9+2, - 2.0 * x_len);//с3
					row.put(index2_9+3, -       y_len);//с4
					

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 3:
				{
					// the first derivative
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_x(t) := 
					// c1+
					// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
					// c4*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// c8*(y_org-yj+(y_dest-y_org)*t)^2

					// = 
					//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
					//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
					//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

					row.clear();	
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.put(index1_9+0, 1.0);//с1

					row.put(index1_9+2, 2.0 * x_org_x1j);//с3
					row.put(index1_9+3,       y_org_y1j);//с4
					
					row.put(index1_9+5, 3.0 * x_org_x1j * x_org_x1j);//с6
					row.put(index1_9+6, 2.0 * x_org_x1j * y_org_y1j);//с7
					row.put(index1_9+7,       y_org_y1j * y_org_y1j);//с8

					row.put(index2_9+0, - 1.0);//с1

					row.put(index2_9+2, - 2.0 * x_org_x2j);//с3
					row.put(index2_9+3, -       y_org_y2j);//с4
					
					row.put(index2_9+5, - 3.0 * x_org_x2j * x_org_x2j);//с6
					row.put(index2_9+6, - 2.0 * x_org_x2j * y_org_y2j);//с7
					row.put(index2_9+7, -       y_org_y2j * y_org_y2j);//с8

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//2*c3*x_len+
					//c4*y_len+
					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					row.put(index1_9+2, 2.0 * x_len);//с3
					row.put(index1_9+3,       y_len);//с4
					
					row.put(index1_9+5, 6.0 * x_org_x1j * x_len);//с6
					row.put(index1_9+6, 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len));//с7
					row.put(index1_9+7, 2.0 * y_org_y1j * y_len);//с8

					row.put(index2_9+2, - 2.0 * x_len);//с3
					row.put(index2_9+3, -       y_len);//с4
					
					row.put(index2_9+5, - 6.0 * x_org_x2j * x_len);//с6
					row.put(index2_9+6, - 2.0 * (x_org_x2j * y_len + y_org_y2j * x_len));//с7
					row.put(index2_9+7, - 2.0 * y_org_y2j * y_len);//с8

					M.push_back(row);	B.push_back(0.0);


					row.clear();	
					//(3*c6*x_len^2 + 2*c7*x_len*y_len + c8*y_len^2)*t^2+

					row.put(index1_9+5, 3.0 * x_len * x_len);//с6
					row.put(index1_9+6, 2.0 * x_len * y_len);//с7
					row.put(index1_9+7,       y_len * y_len);//с8

					row.put(index2_9+5, - 3.0 * x_len * x_len);//с6
					row.put(index2_9+6, - 2.0 * x_len * y_len);//с7
					row.put(index2_9+7, -       y_len * y_len);//с8

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
		}

		if(add_first_der_y)
		{	
			switch (order)
			{
			case 2:
				{
					row._order = 1;
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_y(t) := 
					// c2+
					// c4*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
					// c7*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

					// = 

					//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
					//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
					//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

					row.clear();	
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					row.put(index1_9+1, 1.0);//с2

					row.put(index1_9+3,       x_org_x1j);//с4
					row.put(index1_9+4, 2.0 * y_org_y1j);//с5
					

					row.put(index2_9+1, - 1.0);//с2

					row.put(index2_9+3, -       x_org_x2j);//с4
					row.put(index2_9+4, - 2.0 * y_org_y2j);//с5
					

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					row.put(index1_9+3,       x_len);//с4
					row.put(index1_9+4, 2.0 * y_len);//с5
					

					row.put(index2_9+3, -       x_len);//с4
					row.put(index2_9+4, - 2.0 * y_len);//с5
					

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 3:
				{
					row._order = 1;
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_y(t) := 
					// c2+
					// c4*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
					// c7*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

					// = 

					//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
					//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
					//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

					row.clear();	
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					row.put(index1_9+1, 1.0);//с2

					row.put(index1_9+3,       x_org_x1j);//с4
					row.put(index1_9+4, 2.0 * y_org_y1j);//с5
					
					row.put(index1_9+6,       x_org_x1j * x_org_x1j);//с7
					row.put(index1_9+7, 2.0 * x_org_x1j * y_org_y1j);//с8
					row.put(index1_9+8, 3.0 * y_org_y1j * y_org_y1j);//с9

					row.put(index2_9+1, - 1.0);//с2

					row.put(index2_9+3, -       x_org_x2j);//с4
					row.put(index2_9+4, - 2.0 * y_org_y2j);//с5
					
					row.put(index2_9+6, -       x_org_x2j * x_org_x2j);//с7
					row.put(index2_9+7, - 2.0 * x_org_x2j * y_org_y2j);//с8
					row.put(index2_9+8, - 3.0 * y_org_y2j * y_org_y2j);//с9

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					row.put(index1_9+3,       x_len);//с4
					row.put(index1_9+4, 2.0 * y_len);//с5
					
					row.put(index1_9+6, 2.0 * x_org_x1j * x_len);//с7
					row.put(index1_9+7, 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len) );//с8
					row.put(index1_9+8, 6.0 * y_org_y1j * y_len);//с9

					row.put(index2_9+3, -       x_len);//с4
					row.put(index2_9+4, - 2.0 * y_len);//с5
					
					row.put(index2_9+6, - 2.0 * x_org_x2j * x_len);//с7
					row.put(index2_9+7, - 2.0 * (x_org_x2j * y_len + y_org_y2j * x_len) );//с8
					row.put(index2_9+8, - 3.0 * y_org_y2j * y_len);//с9

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(c7*x_len^2 + 2*c8*x_len*y_len + 3*c9*y_len^2)*t^2+

					row.put(index1_9+6,       x_len * x_len);//с7
					row.put(index1_9+7, 2.0 * x_len * y_len);//с8
					row.put(index1_9+8, 3.0 * y_len * y_len);//с9

					row.put(index2_9+6, - 2.0 * x_len * x_len);//с7
					row.put(index2_9+7, - 2.0 * x_len * y_len);//с8
					row.put(index2_9+8, - 3.0 * y_len * y_len);//с9

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
		}
		if(add_second_der)
		{
			row._order = 2;

#if USE_SECOND_DERIVATIVES_EQUATIONS
			switch(order)
			{
			case 2:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_xx(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c3+
					// 6*c6*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c7*(y_org-yj+(y_dest-y_org)*t)

					// = 

					//(6*c6*x_len+2*c7*y_len)*t+
					//2*c3+6*c6*x_org_xj+2*c7*y_org_yj

					row.clear();	
					//2*c3 + 6*c6*x_org_xj + 2*c7*y_org_yj
					row.put(index1_9+2, 2.0);//с3				

					row.put(index2_9+2, - 2.0);//с3				

					M.push_back(row);	B.push_back(0.0);
					

					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_yy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c5+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)+
					// 6*c9*(y_org-yj+(y_dest-y_org)*t)

					// = 

					// (2*c8*x_len+6*c9*y_len)*t+
					//2*c5+2*c8*x_org_xj+6*c9*y_org_yj

					row.clear();	
					//2*c5 + 2*c8*x_org_xj + 6*c9*y_org_yj
					row.put(index1_9+4, + 2.0);//с5				

					row.put(index2_9+4, - 2.0);//с5				

					M.push_back(row);	B.push_back(0.0);
					

					
					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_xy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// c4+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c8*(y_org-yj+(y_dest-y_org)*t)

					// =
					
					//(2*c7*x_len+2*c8*y_len)*t+
					//c4+2*c7*x_org_xj+2*c8*y_org_yj

					row.clear();
					//c4 + 2*c7*x_org_xj + 2*c8*y_org_yj
					row.put(index1_9+3, + 1.0);//с4				

					row.put(index2_9+3, - 1.0);//с4				

					M.push_back(row);	B.push_back(0.0);

				}
				break;
			case 3:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_xx(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c3+
					// 6*c6*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c7*(y_org-yj+(y_dest-y_org)*t)

					// = 

					//(6*c6*x_len+2*c7*y_len)*t+
					//2*c3+6*c6*x_org_xj+2*c7*y_org_yj

					row.clear();	
					//2*c3 + 6*c6*x_org_xj + 2*c7*y_org_yj
					row.put(index1_9+2, 2.0);//с3				
					row.put(index1_9+5, 6.0 * x_org_x1j);//с6
					row.put(index1_9+6, 2.0 * y_org_y1j);//с7

					row.put(index2_9+2, - 2.0);//с3				
					row.put(index2_9+5, - 6.0 * x_org_x2j);//с6
					row.put(index2_9+6, - 2.0 * y_org_y2j);//с7

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					//(6*c6*x_len + 2*c7*y_len)*t+
					row.put(index1_9+5, 6.0 * x_len);//с6
					row.put(index1_9+6, 2.0 * y_len);//с7

					row.put(index2_9+5, - 6.0 * x_len);//с6
					row.put(index2_9+6, - 2.0 * y_len);//с7

					M.push_back(row);	B.push_back(0.0);
					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_yy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c5+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)+
					// 6*c9*(y_org-yj+(y_dest-y_org)*t)

					// = 

					// (2*c8*x_len+6*c9*y_len)*t+
					//2*c5+2*c8*x_org_xj+6*c9*y_org_yj

					row.clear();	
					//2*c5 + 2*c8*x_org_xj + 6*c9*y_org_yj
					row.put(index1_9+4, + 2.0);//с5				
					row.put(index1_9+7, + 2.0 * x_org_x1j);//с8
					row.put(index1_9+8, + 6.0 * y_org_y1j);//с9

					row.put(index2_9+4, - 2.0);//с5				
					row.put(index2_9+7, - 2.0 * x_org_x2j);//с8
					row.put(index2_9+8, - 6.0 * y_org_y2j);//с9

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					// (2*c8*x_len + 6*c9*y_len)*t+
					row.put(index1_9+7, + 2.0 * x_len);//с8
					row.put(index1_9+8, + 6.0 * y_len);//с9

					row.put(index2_9+7, - 2.0 * x_len);//с8
					row.put(index2_9+8, - 6.0 * y_len);//с9

					M.push_back(row);	B.push_back(0.0);
					
					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_xy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// c4+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c8*(y_org-yj+(y_dest-y_org)*t)

					// =
					
					//(2*c7*x_len+2*c8*y_len)*t+
					//c4+2*c7*x_org_xj+2*c8*y_org_yj

					row.clear();
					//c4 + 2*c7*x_org_xj + 2*c8*y_org_yj
					row.put(index1_9+3, + 1.0);//с4				
					row.put(index1_9+6, + 2.0 * x_org_x1j);//с7
					row.put(index1_9+7, + 2.0 * y_org_y1j);//с8

					row.put(index2_9+3, - 1.0);//с4				
					row.put(index2_9+6, - 2.0 * x_org_x2j);//с7
					row.put(index2_9+7, - 2.0 * y_org_y2j);//с8

					M.push_back(row);	B.push_back(0.0);

					row.clear();
					//(2*c7*x_len + 2*c8*y_len)*t+
					row.put(index1_9+6, + 2.0 * x_len);//с7
					row.put(index1_9+7, + 2.0 * y_len);//с8

					row.put(index2_9+6, - 2.0 * x_len);//с7
					row.put(index2_9+7, - 2.0 * y_len);//с8

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
#endif
		}
	}
	else
		printf ("!AddRowsToEquation2 ! (p1 && p2)\n");
}

*/

void AddRowsToEquation_(int N_trias, int order_t, int order_c, 
						size_t nk_t, size_t nk_c,						
						//double _weight,
					   vector<sparse_row> & M,	// формируемая матрица
					   size_t cols, 
					  vector<double> & B,			// формируемый вектор правых частей
					  vector<double> & z,			// отметки высот
					  PolygonEx * p,
					  vector<geometry2D::Point> &base_points
					  )
{
	geometry2D::Point ptj;		// базовая точка
	geometry2D::Point pt;		// дополнительная точка, 
					  // которая должна удовлетворять 
					  // уравнению кубической интерполяции
	size_t index = p->index;
	ptj = base_points[index];
	size_t index_10 = (int)index < N_trias ? index*nk_t : N_trias*nk_t + (index-N_trias)*nk_c;

	size_t nk = (int)index < N_trias ? nk_t : nk_c;
	int order = (int)index < N_trias ? order_t : order_c;



	if (index_10+nk-1 >= cols)
	{
		char err[1024];
		sprintf(err, "index_10+nk-1 (%u) >= cols (%u)", index_10+nk-1, cols);
		MessageBox(0, err, "AddRowsToEquation_", MB_OK);
		return;
	}		

	for (int i = 0; i < p->size(); i++)
	{
		p->advance(CLOCKWISE);
		geometry2D::Point pt = p->point();

		//AddRowToEquation(M, cols, B, z, ptj, pt, index_9);			
		if (pt != ptj && pt.index > -1 && pt.index < (int)z.size())
		{			
			double dx = pt.x - ptj.x;
			double dy = pt.y - ptj.y;

			// добавляем строку в уравнение
			
			sparse_row row; 
			row.clear();

			switch(order)
			{
			case 4:
				row.put(index_10+10, dx * dx * dx * dx);//с6
				row.put(index_10+11, dx * dx * dx * dy);//с7
				row.put(index_10+12, dx * dx * dy * dy);//с8
				row.put(index_10+13, dx * dy * dy * dy);//с8
				row.put(index_10+14, dy * dy * dy * dy);//с9
			case 3:
				row.put(index_10+6, dx * dx * dx);//с6
				row.put(index_10+7, dx * dx * dy);//с7
				row.put(index_10+8, dx * dy * dy);//с8
				row.put(index_10+9, dy * dy * dy);//с9
			case 2:
				row.put(index_10+3, dx * dx);//с3
				row.put(index_10+4, dx * dy);//с4
				row.put(index_10+5, dy * dy);//с5
			case 1:
				row.put(index_10+0, 1.0);//с0
				row.put(index_10+1, dx);//с1
				row.put(index_10+2, dy);//с2
			}
			
#if SPARSE_ROW_EX
			row._order = 0;
//			row._weight = _weight;
#endif
			M.push_back(row);
			B.push_back(z[pt.index]);
			
		}
	}
}

void AddRowsToEquation2__(int order,
						vector<sparse_row> & M,	// формируемая матрица
					   size_t cols,
					  vector<double> & B,			// формируемый вектор правых частей
					  vector<double> & z,			// отметки высот
					  EdgeEx * ex,
					  vector<geometry2D::Point> &base_points)
{
	PolygonEx * p1 = ex->LeftPolygon();
	PolygonEx * p2 = ex->RightPolygon();
	if(p1 && p2)
	{
		size_t nk;
		switch(order)
		{
			case 2:
				nk = 6;
				break;
			case 3:
				nk = 10;
				break;
			case 4:
				nk = 15;
				break;
		}

		size_t index1 = p1->index < p2->index ? p1->index : p2->index;
		size_t index2 = p1->index < p2->index ? p2->index : p1->index;

		size_t index1_10 = index1*nk;
		size_t index2_10 = index2*nk;

		printf("AddRowsToEquation2 %u %u %u %u\n", index1, index2, index1_10, index2_10);

		if (index1_10+nk-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index1_10+8 (%u) >= cols (%u)", index1_10+nk-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx _", MB_OK);
			return;
		}		
		if (index2_10+nk-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index2_10+nk-1 (%u) >= cols (%u)", index2_10+nk-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx _", MB_OK);
			return;
		}

		double x_org = ex->org.x;
		double y_org = ex->org.y;

		double x_dest = ex->dest.x;
		double y_dest = ex->dest.y;

		double x_len = x_dest - x_org;
		double y_len = y_dest - y_org;

		// базовые точки для обоих полигонов
		geometry2D::Point pt1j = base_points[index1];
		geometry2D::Point pt2j = base_points[index2];

		double x_org_x1j = x_org - pt1j.x;
		double y_org_y1j = y_org - pt1j.y;

		double x_org_x2j = x_org - pt2j.x;
		double y_org_y2j = y_org - pt2j.y;

		sparse_row row;

		bool add_non_fault = true;
		bool add_second_der = false;

		bool add_first_der_x = true;
		bool add_first_der_y = true;

		//наклон ребра

		double fabs_slope = fabs(ex->slope());

		if (fabs_slope > 1.0)
		{
			add_first_der_x = true;
			add_first_der_y = false;
		}
		else
		{
			add_first_der_x = false;
			add_first_der_y = true;
		}
		if (add_non_fault)
		{
#if SPARSE_ROW_EX
			row._order = 0;
#endif
			switch (order)
			{
			case 2:
				{
					// f(t) := 
					// (c3*x_len^2+c4*x_len*y_len+c5*y_len^2)*t^2+
					// (c1*x_len+2*c3*x_org_xj*x_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj+c2*y_len+2*c5*y_org_yj*y_len)*t+
					// zj + c1*x_org_xj+c2*y_org_yj+c4*x_org_xj*y_org_yj+c3*x_org_xj^2+c5*y_org_yj^2
					row.clear();	
					// zj + c1*x_org_xj + c2*y_org_yj + c4*x_org_xj*y_org_yj + c3*x_org_xj^2
					row.put(index1_10+0, 1.0);//с0
					row.put(index1_10+1, x_org_x1j);//с1
					row.put(index1_10+2, y_org_y1j);//с2

					row.put(index1_10+3, (x_org_x1j) * (x_org_x1j));//с3
					row.put(index1_10+4, (x_org_x1j) * (y_org_y1j));//с4
					row.put(index1_10+5, (y_org_y1j) * (y_org_y1j));//с5
					

					row.put(index2_10+0, - 1.0);//с0
					row.put(index2_10+1, - (x_org_x2j));//с1
					row.put(index2_10+2, - (y_org_y2j));//с2

					row.put(index2_10+3, - (x_org_x2j) * (x_org_x2j));//с3
					row.put(index2_10+4, - (x_org_x2j) * (y_org_y2j));//с4
					row.put(index2_10+5, - (y_org_y2j) * (y_org_y2j));//с5
					

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//)*t
					// (c1*x_len+2*c3*x_org_xj*x_len+c2*y_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj)*t+

					row.put(index1_10+1, x_len);//с1
					row.put(index1_10+2, y_len);//с2

					row.put(index1_10+3, 2.0 * x_org_x1j * x_len);//с3
					row.put(index1_10+4, x_len * y_org_y1j + x_org_x1j * y_len);//с4
					row.put(index1_10+5, 2.0 * y_org_y1j * y_len);//с5
					

					row.put(index2_10+1, - x_len);//с1
					row.put(index2_10+2, - y_len);//с2

					row.put(index2_10+3, - 2.0 * x_org_x2j * x_len);//с3
					row.put(index2_10+4, - (x_len * y_org_y2j + x_org_x2j * y_len));//с4
					row.put(index2_10+5, - 2.0 * y_org_y2j * y_len);//с5



					M.push_back(row);	B.push_back(0.0);
					row.clear();	
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					row.put(index1_10+3, x_len * x_len);//с3
					row.put(index1_10+4, x_len * y_len);//с4
					row.put(index1_10+5, y_len * y_len);//с5

					row.put(index2_10+3, - x_len * x_len);//с3
					row.put(index2_10+4, - x_len * y_len);//с4
					row.put(index2_10+5, - y_len * y_len);//с5
					
					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 3:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// f(t) := 
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

					// = 

					//(c8*x_len*y_len^2+c6*x_len^3+c7*x_len^2*y_len+c9*y_len^3)*t^3+
					//(c4*x_len*y_len+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c8*x_org_xj*y_len^2+c5*y_len^2+3*c9*y_org_yj*y_len^2+3*c6*x_org_xj*x_len^2+c7*x_len^2*y_org_yj+2*c8*x_len*y_org_yj*y_len)*t^2+
					//(c8*x_len*y_org_yj^2 + c2*y_len + c4*x_len*y_org_yj + c7*x_org_xj^2*y_len + c1*x_len+c4*x_org_xj*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c3*x_org_xj*x_len+2*c8*x_org_xj*y_org_yj*y_len+3*c6*x_org_xj^2*x_len+3*c9*y_org_yj^2*y_len+2*c5*y_org_yj*y_len)*t+
					//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3

					row.clear();	
					//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3
					row.put(index1_10+0, 1.0);//с0
					row.put(index1_10+1, x_org_x1j);//с1
					row.put(index1_10+2, y_org_y1j);//с2

					row.put(index1_10+3, (x_org_x1j) * (x_org_x1j));//с3
					row.put(index1_10+4, (x_org_x1j) * (y_org_y1j));//с4
					row.put(index1_10+5, (y_org_y1j) * (y_org_y1j));//с5
					
					row.put(index1_10+6, (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с6
					row.put(index1_10+7, (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с7
					row.put(index1_10+8, (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с8
					row.put(index1_10+9, (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с9

					row.put(index2_10+0, - 1.0);//с0
					row.put(index2_10+1, - (x_org_x2j));//с1
					row.put(index2_10+2, - (y_org_y2j));//с2

					row.put(index2_10+3, - (x_org_x2j) * (x_org_x2j));//с3
					row.put(index2_10+4, - (x_org_x2j) * (y_org_y2j));//с4
					row.put(index2_10+5, - (y_org_y2j) * (y_org_y2j));//с5
					
					row.put(index2_10+6, - (x_org_x2j) * (x_org_x2j) * (x_org_x2j));//с6
					row.put(index2_10+7, - (x_org_x2j) * (x_org_x2j) * (y_org_y2j));//с7
					row.put(index2_10+8, - (x_org_x2j) * (y_org_y2j) * (y_org_y2j));//с8
					row.put(index2_10+9, - (y_org_y2j) * (y_org_y2j) * (y_org_y2j));//с9

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//2*c5*y_org_yj*y_len
					//3*c6*x_org_xj^2*x_len+
					//c7*x_org_xj^2*y_len + 
					//2*c7*x_org_xj*x_len*y_org_yj+
					//c8*x_len*y_org_yj^2 + 
					//2*c8*x_org_xj*y_org_yj*y_len+
					//3*c9*y_org_yj^2*y_len+
					//)*t

					row.put(index1_10+1, x_len);//с1
					row.put(index1_10+2, y_len);//с2

					row.put(index1_10+3, 2.0 * x_org_x1j * x_len);//с3
					row.put(index1_10+4, x_len * y_org_y1j + x_org_x1j * y_len);//с4
					row.put(index1_10+5, 2.0 * y_org_y1j * y_len);//с5
					
					row.put(index1_10+6, 3.0 * x_org_x1j * x_org_x1j * x_len);//с6
					row.put(index1_10+7, x_org_x1j * x_org_x1j * y_len + 2.0 * x_org_x1j * x_len * y_org_y1j);//с7
					row.put(index1_10+8, x_len * y_org_y1j * y_org_y1j + 2.0 * x_org_x1j * y_len * y_org_y1j);//с8
					row.put(index1_10+9, 3.0 * y_org_y1j * y_org_y1j * y_len);//с9

					row.put(index2_10+1, - x_len);//с1
					row.put(index2_10+2, - y_len);//с2

					row.put(index2_10+3, - 2.0 * x_org_x2j * x_len);//с3
					row.put(index2_10+4, - (x_len * y_org_y2j + x_org_x2j * y_len));//с4
					row.put(index2_10+5, - 2.0 * y_org_y2j * y_len);//с5

					row.put(index2_10+6, - (3.0 * x_org_x2j * x_org_x2j * x_len));//с6
					row.put(index2_10+7, - (x_org_x2j * x_org_x2j * y_len + 2.0 * x_org_x2j * x_len * y_org_y2j));//с7
					row.put(index2_10+8, - (x_len * y_org_y2j * y_org_y2j + 2.0 * x_org_x2j * y_len * y_org_y2j));//с8
					row.put(index2_10+9, - (3.0 * y_org_y2j * y_org_y2j * y_len));//с9


					M.push_back(row);	B.push_back(0.0);
								
					row.clear();	
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					row.put(index1_10+3, x_len * x_len);//с3
					row.put(index1_10+4, x_len * y_len);//с4
					row.put(index1_10+5, y_len * y_len);//с5
					
					row.put(index1_10+6, 3.0 * x_org_x1j * x_len * x_len);//с6
					row.put(index1_10+7, x_len * x_len * y_org_y1j + 2.0 * x_org_x1j * x_len * y_len);//с7
					row.put(index1_10+8, x_org_x1j * y_len * y_len + 2.0 * y_org_y1j * x_len * y_len);//с8
					row.put(index1_10+9, 3.0 * y_org_y1j * y_len * y_len);//с9


					row.put(index2_10+3, - x_len * x_len);//с3
					row.put(index2_10+4, - x_len * y_len);//с4
					row.put(index2_10+5, - y_len * y_len);//с5
					
					row.put(index2_10+6, - (3.0 * x_org_x2j * x_len * x_len));//с6
					row.put(index2_10+7, - (x_len * x_len * y_org_y2j + 2.0 * x_org_x2j * x_len * y_len));//с7
					row.put(index2_10+8, - (x_org_x2j * y_len * y_len + 2.0 * y_org_y2j * x_len * y_len));//с8
					row.put(index2_10+9, - (3.0 * y_org_y2j * y_len * y_len));//с9

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(c8*x_len*y_len^2 + c6*x_len^3 + c7*x_len^2*y_len + c9*y_len^3)*t^3+
					row.put(index1_10+6, x_len * x_len * x_len);//с6
					row.put(index1_10+7, x_len * x_len * y_len);//с7
					row.put(index1_10+8, x_len * y_len * y_len);//с8
					row.put(index1_10+9, y_len * y_len * y_len);//с9

					row.put(index2_10+6, - x_len * x_len * x_len);//с6
					row.put(index2_10+7, - x_len * x_len * y_len);//с7
					row.put(index2_10+8, - x_len * y_len * y_len);//с8
					row.put(index2_10+9, - y_len * y_len * y_len);//с9

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 4:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// f(t) := 
					//c0+
					//c1*(x_org+(x_dest-x_org)*t-xj)+
					//c2*(y_org+(y_dest-y_org)*t-yj)+
					//c3*(x_org+(x_dest-x_org)*t-xj)^2+
					//c4*(x_org+(x_dest-x_org)*t-xj)*(y_org+(y_dest-y_org)*t-yj)+
					//c5*(y_org+(y_dest-y_org)*t-yj)^2+
					//c6*(x_org+(x_dest-x_org)*t-xj)^3+
					//c7*(x_org+(x_dest-x_org)*t-xj)^2*(y_org+(y_dest-y_org)*t-yj)+
					//c8*(x_org+(x_dest-x_org)*t-xj)*(y_org+(y_dest-y_org)*t-yj)^2+
					//c9*(y_org+(y_dest-y_org)*t-yj)^3+
					//c10*(x_org+(x_dest-x_org)*t-xj)^4+
					//c11*(x_org+(x_dest-x_org)*t-xj)^3*(y_org+(y_dest-y_org)*t-yj)+
					//c12*(x_org+(x_dest-x_org)*t-xj)^2*(y_org+(y_dest-y_org)*t-yj)^2+
					//c13*(x_org+(x_dest-x_org)*t-xj)*(y_org+(y_dest-y_org)*t-yj)^3+
					//c14*(y_org+(y_dest-y_org)*t-yj)^4

					// = 

					//(c8*x_len*y_len^2+c6*x_len^3+c7*x_len^2*y_len+c9*y_len^3)*t^3+
					//(c4*x_len*y_len+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c8*x_org_xj*y_len^2+c5*y_len^2+3*c9*y_org_yj*y_len^2+3*c6*x_org_xj*x_len^2+c7*x_len^2*y_org_yj+2*c8*x_len*y_org_yj*y_len)*t^2+
					//(c8*x_len*y_org_yj^2 + c2*y_len + c4*x_len*y_org_yj + c7*x_org_xj^2*y_len + c1*x_len+c4*x_org_xj*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c3*x_org_xj*x_len+2*c8*x_org_xj*y_org_yj*y_len+3*c6*x_org_xj^2*x_len+3*c9*y_org_yj^2*y_len+2*c5*y_org_yj*y_len)*t+
					//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3


					// =

					// (c10*x_len^4+c14*y_len^4+c12*x_len^2*y_len^2+c13*x_len*y_len^3+c11*x_len^3*y_len)*t^4+
					// (c11*x_len^3*y_org_yj+c7*x_len^2*y_len+c9*y_len^3+4*c10*x_org_xj*x_len^3+2*c12*x_org_xj*x_len*y_len^2+2*c12*x_len^2*y_org_yj*y_len+4*c14*y_org_yj*y_len^3+3*c11*x_org_xj*x_len^2*y_len+c13*x_org_xj*y_len^3+c6*x_len^3+3*c13*x_len*y_org_yj*y_len^2+c8*x_len*y_len^2)*t^3+
					// (3*c11*x_org_xj^2*x_len*y_len+c4*x_len*y_len+c12*x_org_xj^2*y_len^2+c8*x_org_xj*y_len^2+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c7*x_len^2*y_org_yj+c12*x_len^2*y_org_yj^2+3*c6*x_org_xj*x_len^2+c5*y_len^2+2*c8*x_len*y_org_yj*y_len+6*c10*x_org_xj^2*x_len^2+3*c11*x_org_xj*x_len^2*y_org_yj+4*c12*x_org_xj*x_len*y_org_yj*y_len+3*c13*x_org_xj*y_org_yj*y_len^2+3*c9*y_org_yj*y_len^2+3*c13*x_len*y_org_yj^2*y_len+6*c14*y_org_yj^2*y_len^2)*t^2+
					// (2*c5*y_org_yj*y_len+c4*x_len*y_org_yj+3*c11*x_org_xj^2*x_len*y_org_yj+c13*x_len*y_org_yj^3+c4*x_org_xj*y_len+c11*x_org_xj^3*y_len+2*c8*x_org_xj*y_org_yj*y_len+c1*x_len+3*c6*x_org_xj^2*x_len+2*c12*x_org_xj*x_len*y_org_yj^2+c8*x_len*y_org_yj^2+c7*x_org_xj^2*y_len+c2*y_len+4*c10*x_org_xj^3*x_len+3*c13*x_org_xj*y_org_yj^2*y_len+3*c9*y_org_yj^2*y_len+2*c3*x_org_xj*x_len+4*c14*y_org_yj^3*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c12*x_org_xj^2*y_org_yj*y_len)*t+
					// c0+c10*x_org_xj^4+c3*x_org_xj^2+c5*y_org_yj^2+c6*x_org_xj^3+c14*y_org_yj^4+c13*x_org_xj*y_org_yj^3+c11*x_org_xj^3*y_org_yj+c12*x_org_xj^2*y_org_yj^2+c4*x_org_xj*y_org_yj+c2*y_org_yj+c7*x_org_xj^2*y_org_yj+c8*x_org_xj*y_org_yj^2+c1*x_org_xj+c9*y_org_yj^3

					row.clear();	
					// c0+
					// c1*x_org_xj+
					// c2*y_org_yj+
					// c3*x_org_xj^2+
					// c4*x_org_xj*y_org_yj+
					// c5*y_org_yj^2+
					// c6*x_org_xj^3+
					// c7*x_org_xj^2*y_org_yj+
					// c8*x_org_xj*y_org_yj^2+
					// c9*y_org_yj^3
					// c10*x_org_xj^4+
					// c11*x_org_xj^3*y_org_yj+
					// c12*x_org_xj^2*y_org_yj^2+
					// c13*x_org_xj*y_org_yj^3+
					// c14*y_org_yj^4+

					row.put(index1_10+0, 1.0);//с0
					row.put(index1_10+1, x_org_x1j);//с1
					row.put(index1_10+2, y_org_y1j);//с2

					row.put(index1_10+3, (x_org_x1j) * (x_org_x1j));//с3
					row.put(index1_10+4, (x_org_x1j) * (y_org_y1j));//с4
					row.put(index1_10+5, (y_org_y1j) * (y_org_y1j));//с5
					
					row.put(index1_10+6, (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с6
					row.put(index1_10+7, (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с7
					row.put(index1_10+8, (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с8
					row.put(index1_10+9, (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с9

					row.put(index1_10+10, (x_org_x1j) * (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с10
					row.put(index1_10+11, (x_org_x1j) * (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с11
					row.put(index1_10+12, (x_org_x1j) * (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с12
					row.put(index1_10+13, (x_org_x1j) * (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с13
					row.put(index1_10+14, (y_org_y1j) * (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с14

					row.put(index2_10+0, - 1.0);//с0
					row.put(index2_10+1, - (x_org_x2j));//с1
					row.put(index2_10+2, - (y_org_y2j));//с2

					row.put(index2_10+3, - (x_org_x2j) * (x_org_x2j));//с3
					row.put(index2_10+4, - (x_org_x2j) * (y_org_y2j));//с4
					row.put(index2_10+5, - (y_org_y2j) * (y_org_y2j));//с5
					
					row.put(index2_10+6, - (x_org_x2j) * (x_org_x2j) * (x_org_x2j));//с6
					row.put(index2_10+7, - (x_org_x2j) * (x_org_x2j) * (y_org_y2j));//с7
					row.put(index2_10+8, - (x_org_x2j) * (y_org_y2j) * (y_org_y2j));//с8
					row.put(index2_10+9, - (y_org_y2j) * (y_org_y2j) * (y_org_y2j));//с9

					row.put(index2_10+10, - (x_org_x2j) * (x_org_x2j) * (x_org_x2j) * (x_org_x2j));//с10
					row.put(index2_10+11, - (x_org_x2j) * (x_org_x2j) * (x_org_x2j) * (y_org_y2j));//с11
					row.put(index2_10+12, - (x_org_x2j) * (x_org_x2j) * (y_org_y2j) * (y_org_y2j));//с12
					row.put(index2_10+13, - (x_org_x2j) * (y_org_y2j) * (y_org_y2j) * (y_org_y2j));//с13
					row.put(index2_10+14, - (y_org_y2j) * (y_org_y2j) * (y_org_y2j) * (y_org_y2j));//с14

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//2*c5*y_org_yj*y_len
					//3*c6*x_org_xj^2*x_len+
					//c7*x_org_xj^2*y_len + 
					//2*c7*x_org_xj*x_len*y_org_yj+
					//c8*x_len*y_org_yj^2 + 
					//2*c8*x_org_xj*y_org_yj*y_len+
					//3*c9*y_org_yj^2*y_len+
					//)*t

										
					// (
					// c1*x_len+
					// c2*y_len+

					// 2*c3*x_org_xj*x_len+
					// c4*x_len*y_org_yj+
					// c4*x_org_xj*y_len+
					// 2*c5*y_org_yj*y_len+

					// 3*c6*x_org_xj^2*x_len+
					// c7*x_org_xj^2*y_len+
					// 2*c7*x_org_xj*x_len*y_org_yj+
					// c8*x_len*y_org_yj^2+
					// 2*c8*x_org_xj*y_org_yj*y_len+
					// 3*c9*y_org_yj^2*y_len+

					// 4*c10*x_org_xj^3*x_len+
					// c11*x_org_xj^3*y_len+
					// 3*c11*x_org_xj^2*x_len*y_org_yj+
					// 2*c12*x_org_xj*x_len*y_org_yj^2+
					// 2*c12*x_org_xj^2*y_org_yj*y_len
					// c13*x_len*y_org_yj^3+
					// 3*c13*x_org_xj*y_org_yj^2*y_len+
					// 4*c14*y_org_yj^3*y_len+
					// )*t+


					row.put(index1_10+1, x_len);//с1
					row.put(index1_10+2, y_len);//с2

					row.put(index1_10+3, 2.0 * x_org_x1j * x_len);//с3
					row.put(index1_10+4, x_len * y_org_y1j + x_org_x1j * y_len);//с4
					row.put(index1_10+5, 2.0 * y_org_y1j * y_len);//с5
					
					row.put(index1_10+6, 3.0 * x_org_x1j * x_org_x1j * x_len);//с6
					row.put(index1_10+7, x_org_x1j * x_org_x1j * y_len + 2.0 * x_org_x1j * x_len * y_org_y1j);//с7
					row.put(index1_10+8, x_len * y_org_y1j * y_org_y1j + 2.0 * x_org_x1j * y_len * y_org_y1j);//с8
					row.put(index1_10+9, 3.0 * y_org_y1j * y_org_y1j * y_len);//с9

					row.put(index1_10+10, 
						4.0 * x_org_x1j * x_org_x1j * x_org_x1j * x_len);//с10
					row.put(index1_10+11, 
						x_org_x1j * x_org_x1j * x_org_x1j * y_len + 
						3.0 * x_org_x1j * x_org_x1j * x_len * y_org_y1j);//с11
					row.put(index1_10+12, 
						2.0 * x_org_x1j*x_len*y_org_y1j*y_org_y1j + 
						2.0 * x_org_x1j*x_org_x1j*y_org_y1j*y_len);//с12
					row.put(index1_10+13, 
						x_len * y_org_y1j * y_org_y1j * y_org_y1j + 
						3.0 * x_org_x1j * y_len * y_org_y1j * y_org_y1j);//с13
					row.put(index1_10+14, 
						4.0 * y_org_y1j * y_org_y1j * y_org_y1j * y_len);//с14

					row.put(index2_10+1, - x_len);//с1
					row.put(index2_10+2, - y_len);//с2

					row.put(index2_10+3, - 2.0 * x_org_x2j * x_len);//с3
					row.put(index2_10+4, - (x_len * y_org_y2j + x_org_x2j * y_len));//с4
					row.put(index2_10+5, - 2.0 * y_org_y2j * y_len);//с5

					row.put(index2_10+6, - (3.0 * x_org_x2j * x_org_x2j * x_len));//с6
					row.put(index2_10+7, - (x_org_x2j * x_org_x2j * y_len + 2.0 * x_org_x2j * x_len * y_org_y2j));//с7
					row.put(index2_10+8, - (x_len * y_org_y2j * y_org_y2j + 2.0 * x_org_x2j * y_len * y_org_y2j));//с8
					row.put(index2_10+9, - (3.0 * y_org_y2j * y_org_y2j * y_len));//с9
					
					row.put(index2_10+10, 
						-4.0 * x_org_x2j * x_org_x2j * x_org_x2j * x_len);//с10
					row.put(index2_10+11, 
						-x_org_x2j * x_org_x2j * x_org_x2j * y_len - 
						3.0 * x_org_x2j * x_org_x2j * x_len * y_org_y2j);//с11
					row.put(index2_10+12, 
						-2.0 * x_org_x2j*x_len*y_org_y2j*y_org_y2j - 
						2.0 * x_org_x2j*x_org_x2j*y_org_y2j*y_len);//с12
					row.put(index2_10+13, 
						-x_len * y_org_y2j * y_org_y2j * y_org_y2j - 
						3.0 * x_org_x2j * y_len * y_org_y2j * y_org_y2j);//с13
					row.put(index2_10+14, 
						-4.0 * y_org_y2j * y_org_y2j * y_org_y2j * y_len);//с14



					M.push_back(row);	B.push_back(0.0);
								
					row.clear();	
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					// (
					// c3*x_len^2+
					// c4*x_len*y_len+
					// c5*y_len^2+

					// 3*c6*x_org_xj*x_len^2+
					// c7*x_len^2*y_org_yj+
					// 2*c7*x_org_xj*x_len*y_len+
					// c8*x_org_xj*y_len^2+
					// 2*c8*x_len*y_org_yj*y_len+
					// 3*c9*y_org_yj*y_len^2+

					// 6*c10*x_org_xj^2*x_len^2+
					// 3*c11*x_org_xj^2*x_len*y_len+
					// 3*c11*x_org_xj*x_len^2*y_org_yj+
					// c12*x_org_xj^2*y_len^2+
					// c12*x_len^2*y_org_yj^2+
					// 4*c12*x_org_xj*x_len*y_org_yj*y_len+
					// 3*c13*x_org_xj*y_org_yj*y_len^2+
					// 3*c13*x_len*y_org_yj^2*y_len+
					// 6*c14*y_org_yj^2*y_len^2
					// )*t^2+
					row.put(index1_10+3, x_len * x_len);//с3
					row.put(index1_10+4, x_len * y_len);//с4
					row.put(index1_10+5, y_len * y_len);//с5
					
					row.put(index1_10+6, 3.0 * x_org_x1j * x_len * x_len);//с6
					row.put(index1_10+7, 
						x_len * x_len * y_org_y1j 
						+ 2.0 * x_org_x1j * x_len * y_len);//с7
					row.put(index1_10+8, 
						x_org_x1j * y_len * y_len + 
						2.0 * y_org_y1j * x_len * y_len);//с8
					row.put(index1_10+9, 3.0 * y_org_y1j * y_len * y_len);//с9

					row.put(index1_10+10, 
						6.0 * x_org_x1j * x_org_x1j * x_len * x_len);//с10
					row.put(index1_10+11, 
						3.0 * x_len * y_len * x_org_x1j * x_org_x1j 
						+ 3.0 * x_org_x1j * x_len * x_len * y_org_y1j);//с11
					row.put(index1_10+12, 
						x_org_x1j * x_org_x1j * y_len * y_len + 
						y_org_y1j * y_org_y1j * x_len * x_len + 
						4.0 * x_org_x1j * y_org_y1j * x_len * y_len);//с12
					row.put(index1_10+13, 
						3.0 * x_org_x1j * y_org_y1j * y_len * y_len + 
						3.0 * y_org_y1j * y_org_y1j * x_len * y_len);//с13
					row.put(index1_10+14, 
						6.0 * y_org_y1j * y_org_y1j * y_len * y_len);//с14


					row.put(index2_10+3, - x_len * x_len);//с3
					row.put(index2_10+4, - x_len * y_len);//с4
					row.put(index2_10+5, - y_len * y_len);//с5
					
					row.put(index2_10+6, - (3.0 * x_org_x2j * x_len * x_len));//с6
					row.put(index2_10+7, - (x_len * x_len * y_org_y2j + 2.0 * x_org_x2j * x_len * y_len));//с7
					row.put(index2_10+8, - (x_org_x2j * y_len * y_len + 2.0 * y_org_y2j * x_len * y_len));//с8
					row.put(index2_10+9, - (3.0 * y_org_y2j * y_len * y_len));//с9


					row.put(index2_10+10, 
						- 6.0 * x_org_x2j * x_org_x2j * x_len * x_len);//с10
					row.put(index2_10+11, 
						- 3.0 * x_len * y_len * x_org_x2j * x_org_x2j 
						- 3.0 * x_org_x2j * x_len * x_len * y_org_y2j);//с11
					row.put(index2_10+12, 
						- x_org_x2j * x_org_x2j * y_len * y_len 
						- y_org_y2j * y_org_y2j * x_len * x_len 
						- 4.0 * x_org_x2j * y_org_y2j * x_len * y_len);//с12
					row.put(index2_10+13, 
						- 3.0 * x_org_x2j * y_org_y2j * y_len * y_len
						- 3.0 * y_org_y2j * y_org_y2j * x_len * y_len);//с13
					row.put(index2_10+14, 
						- 6.0 * y_org_y2j * y_org_y2j * y_len * y_len);//с14

					M.push_back(row);	B.push_back(0.0);


					row.clear();	
					//(c8*x_len*y_len^2 + c6*x_len^3 + c7*x_len^2*y_len + c9*y_len^3)*t^3+
					
					// (
					// c6*x_len^3+
					// c7*x_len^2*y_len+
					// c8*x_len*y_len^2
					// c9*y_len^3+

					// 4*c10*x_org_xj*x_len^3+
					// c11*x_len^3*y_org_yj+
					// 3*c11*x_org_xj*x_len^2*y_len+
					// 2*c12*x_org_xj*x_len*y_len^2+
					// 2*c12*x_len^2*y_org_yj*y_len+
					// c13*x_org_xj*y_len^3+
					// 3*c13*x_len*y_org_yj*y_len^2+
					// 4*c14*y_org_yj*y_len^3+
					// )*t^3+
					row.put(index1_10+6, x_len * x_len * x_len);//с6
					row.put(index1_10+7, x_len * x_len * y_len);//с7
					row.put(index1_10+8, x_len * y_len * y_len);//с8
					row.put(index1_10+9, y_len * y_len * y_len);//с9

					row.put(index1_10+10, 
						+ 4.0 * x_org_x1j * x_len * x_len * x_len);//с10
					row.put(index1_10+11, 
						+ x_len * x_len * x_len * y_org_y1j 
						+ 3.0 * x_org_x1j * x_len * x_len * y_len);//с11
					row.put(index1_10+12, 
						+ 2.0 * x_org_x1j * x_len * y_len * y_len 
						+ 2.0 * x_len * x_len  * y_org_y1j * y_len);//с12
					row.put(index1_10+13, 
						+ x_org_x1j * y_len * y_len * y_len 
						+ 3.0 * x_len * y_org_y1j * y_len * y_len);//с13
					row.put(index1_10+14, 
						+ 4.0 * y_org_y1j * y_len * y_len * y_len);//с14

					row.put(index2_10+6, - x_len * x_len * x_len);//с6
					row.put(index2_10+7, - x_len * x_len * y_len);//с7
					row.put(index2_10+8, - x_len * y_len * y_len);//с8
					row.put(index2_10+9, - y_len * y_len * y_len);//с9

					row.put(index2_10+10, 
						- 4.0 * x_org_x2j * x_len * x_len * x_len);//с10
					row.put(index2_10+11, 
						- x_len * x_len * x_len * y_org_y2j 
						- 3.0 * x_org_x2j * x_len * x_len * y_len);//с11
					row.put(index2_10+12, 
						- 2.0 * x_org_x2j * x_len * y_len * y_len 
						- 2.0 * x_len * x_len  * y_org_y2j * y_len);//с12
					row.put(index2_10+13, 
						- x_org_x2j * y_len * y_len * y_len
						- 3.0 * x_len * y_org_y2j * y_len * y_len);//с13
					row.put(index2_10+14, 
						- 4.0 * y_org_y2j * y_len * y_len * y_len);//с14

					M.push_back(row);	B.push_back(0.0);

					row.clear();
					// (
					// c10*x_len^4+
					// c11*x_len^3*y_len
					// c12*x_len^2*y_len^2+
					// c13*x_len*y_len^3+
					// c14*y_len^4+
					// )*t^4+

					row.put(index1_10+10, 
						+ x_len * x_len * x_len * x_len);//с10
					row.put(index1_10+11, 
						+ x_len * x_len * x_len * y_len);//с11
					row.put(index1_10+12, 
						+ x_len * x_len * y_len * y_len);//с12
					row.put(index1_10+13, 
						+ x_len * y_len * y_len * y_len);//с13
					row.put(index1_10+14, 
						+ y_len * y_len * y_len * y_len);//с14

					row.put(index2_10+10, 
						- x_len * x_len * x_len * x_len);//с10
					row.put(index2_10+11, 
						- x_len * x_len * x_len * y_len);//с11
					row.put(index2_10+12, 
						- x_len * x_len * y_len * y_len);//с12
					row.put(index2_10+13, 
						- x_len * y_len * y_len * y_len);//с13
					row.put(index2_10+14, 
						- y_len * y_len * y_len * y_len);//с14

					
					M.push_back(row);	B.push_back(0.0);

				}
				break;
			}
		}

		if(add_first_der_x)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			switch (order)
			{
			case 2:
				{
					// the first derivative
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_x(t) := 
					// c1+
					// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
					// c4*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// c8*(y_org-yj+(y_dest-y_org)*t)^2

					// = 
					//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
					//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
					//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

					row.clear();	
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.put(index1_10+1, 1.0);//с1

					row.put(index1_10+3, 2.0 * x_org_x1j);//с3
					row.put(index1_10+4,       y_org_y1j);//с4
					

					row.put(index2_10+1, - 1.0);//с1

					row.put(index2_10+3, - 2.0 * x_org_x2j);//с3
					row.put(index2_10+4, -       y_org_y2j);//с4
					

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//2*c3*x_len+
					//c4*y_len+
					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					row.put(index1_10+3, 2.0 * x_len);//с3
					row.put(index1_10+4,       y_len);//с4
					

					row.put(index2_10+3, - 2.0 * x_len);//с3
					row.put(index2_10+4, -       y_len);//с4
					

					M.push_back(row);	B.push_back(0.0);

				}
				break;
			case 3:
				{
					// the first derivative
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_x(t) := 
					// c1+
					// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
					// c4*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// c8*(y_org-yj+(y_dest-y_org)*t)^2

					// = 
					//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
					//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
					//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

					row.clear();	
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.put(index1_10+1, 1.0);//с1

					row.put(index1_10+3, 2.0 * x_org_x1j);//с3
					row.put(index1_10+4,       y_org_y1j);//с4
					
					row.put(index1_10+6, 3.0 * x_org_x1j * x_org_x1j);//с6
					row.put(index1_10+7, 2.0 * x_org_x1j * y_org_y1j);//с7
					row.put(index1_10+8,       y_org_y1j * y_org_y1j);//с8

					row.put(index2_10+1, - 1.0);//с1

					row.put(index2_10+3, - 2.0 * x_org_x2j);//с3
					row.put(index2_10+4, -       y_org_y2j);//с4
					
					row.put(index2_10+6, - 3.0 * x_org_x2j * x_org_x2j);//с6
					row.put(index2_10+7, - 2.0 * x_org_x2j * y_org_y2j);//с7
					row.put(index2_10+8, -       y_org_y2j * y_org_y2j);//с8

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//2*c3*x_len+
					//c4*y_len+

					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					row.put(index1_10+3, 2.0 * x_len);//с3
					row.put(index1_10+4,       y_len);//с4
					
					row.put(index1_10+6, 6.0 * x_org_x1j * x_len);//с6
					row.put(index1_10+7, 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len));//с7
					row.put(index1_10+8, 2.0 * y_org_y1j * y_len);//с8

					row.put(index2_10+3, - 2.0 * x_len);//с3
					row.put(index2_10+4, -       y_len);//с4
					
					row.put(index2_10+6, - 6.0 * x_org_x2j * x_len);//с6
					row.put(index2_10+7, - 2.0 * (x_org_x2j * y_len + y_org_y2j * x_len));//с7
					row.put(index2_10+8, - 2.0 * y_org_y2j * y_len);//с8

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(3*c6*x_len^2 + 2*c7*x_len*y_len + c8*y_len^2)*t^2+

					row.put(index1_10+6, 3.0 * x_len * x_len);//с6
					row.put(index1_10+7, 2.0 * x_len * y_len);//с7
					row.put(index1_10+8,       y_len * y_len);//с8

					row.put(index2_10+6, - 3.0 * x_len * x_len);//с6
					row.put(index2_10+7, - 2.0 * x_len * y_len);//с7
					row.put(index2_10+8, -       y_len * y_len);//с8

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 4:
				{
					// the first derivative
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_x(t) := 
					// c1+
					// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
					// c4*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// c8*(y_org-yj+(y_dest-y_org)*t)^2

					// = 
					//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
					//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
					//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

					// (3*c11*x_len^2*y_len+c13*y_len^3+4*c10*x_len^3+2*c12*x_len*y_len^2)*t^3+
					// (c8*y_len^2+3*c11*x_len^2*y_org_yj+2*c12*x_org_xj*y_len^2+3*c6*x_len^2+2*c7*x_len*y_len+4*c12*x_len*y_org_yj*y_len+6*c11*x_org_xj*x_len*y_len+3*c13*y_org_yj*y_len^2+12*c10*x_org_xj*x_len^2)*t^2+
					// (2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+2*c3*x_len+c4*y_len+2*c8*y_org_yj*y_len+12*c10*x_org_xj^2*x_len+3*c13*y_org_yj^2*y_len+6*c6*x_org_xj*x_len+4*c12*x_org_xj*y_org_yj*y_len+6*c11*x_org_xj*x_len*y_org_yj+3*c11*x_org_xj^2*y_len+2*c12*x_len*y_org_yj^2)*t+
					// c1+2*c3*x_org_xj+c4*y_org_yj+3*c6*x_org_xj^2+2*c7*x_org_xj*y_org_yj+4*c10*x_org_xj^3+c8*y_org_yj^2+2*c12*x_org_xj*y_org_yj^2+3*c11*x_org_xj^2*y_org_yj+c13*y_org_yj^3

					row.clear();	
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					
					// c1+
					// 2*c3*x_org_xj+
					// c4*y_org_yj+
					// 3*c6*x_org_xj^2+
					// 2*c7*x_org_xj*y_org_yj+
					// c8*y_org_yj^2+

					// 4*c10*x_org_xj^3+
					// 3*c11*x_org_xj^2*y_org_yj+
					// 2*c12*x_org_xj*y_org_yj^2+
					// c13*y_org_yj^3
					row.put(index1_10+1, 1.0);//с1

					row.put(index1_10+3, 2.0 * x_org_x1j);//с3
					row.put(index1_10+4,       y_org_y1j);//с4
					
					row.put(index1_10+6, 3.0 * x_org_x1j * x_org_x1j);//с6
					row.put(index1_10+7, 2.0 * x_org_x1j * y_org_y1j);//с7
					row.put(index1_10+8,       y_org_y1j * y_org_y1j);//с8

					row.put(index1_10+10, 4.0 * x_org_x1j * x_org_x1j * x_org_x1j);//с10
					row.put(index1_10+11, 3.0 * x_org_x1j * x_org_x1j * y_org_y1j);//с11
					row.put(index1_10+12, 2.0 * x_org_x1j * y_org_y1j * y_org_y1j);//с12
					row.put(index1_10+13,       y_org_y1j * y_org_y1j * y_org_y1j);//с13

					row.put(index2_10+1, - 1.0);//с1

					row.put(index2_10+3, - 2.0 * x_org_x2j);//с3
					row.put(index2_10+4, -       y_org_y2j);//с4
					
					row.put(index2_10+6, - 3.0 * x_org_x2j * x_org_x2j);//с6
					row.put(index2_10+7, - 2.0 * x_org_x2j * y_org_y2j);//с7
					row.put(index2_10+8, -       y_org_y2j * y_org_y2j);//с8

					row.put(index2_10+10, - 4.0 * x_org_x2j * x_org_x2j * x_org_x2j);//с10
					row.put(index2_10+11, - 3.0 * x_org_x2j * x_org_x2j * y_org_y2j);//с11
					row.put(index2_10+12, - 2.0 * x_org_x2j * y_org_y2j * y_org_y2j);//с12
					row.put(index2_10+13, -       y_org_y2j * y_org_y2j * y_org_y2j);//с13

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//2*c3*x_len+
					//c4*y_len+
					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					// (
					// 2*c3*x_len+
					// c4*y_len+

					// 6*c6*x_org_xj*x_len+
					// 2*c7*x_org_xj*y_len+
					// 2*c7*x_len*y_org_yj+
					// 2*c8*y_org_yj*y_len+

					// 12*c10*x_org_xj^2*x_len+
					// 6*c11*x_org_xj*x_len*y_org_yj+
					// 3*c11*x_org_xj^2*y_len+
					// 4*c12*x_org_xj*y_org_yj*y_len+
					// 2*c12*x_len*y_org_yj^2
					// 3*c13*y_org_yj^2*y_len+
					// )*t+

					row.put(index1_10+3, 2.0 * x_len);//с3
					row.put(index1_10+4,       y_len);//с4
					
					row.put(index1_10+6, 6.0 * x_org_x1j * x_len);//с6
					row.put(index1_10+7, 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len));//с7
					row.put(index1_10+8, 2.0 * y_org_y1j * y_len);//с8

					row.put(index1_10+10, 12.0 * x_org_x1j * x_org_x1j * x_len);//с10
					row.put(index1_10+11, 
						+ 6.0 * x_org_x1j * x_len * y_org_y1j 
						+ 3.0 * x_org_x1j * x_org_x1j * y_len);//с11
					row.put(index1_10+12, 
						+ 4.0 * x_org_x1j * y_org_y1j * y_len 
						+ 2.0 * x_len * y_org_y1j * y_org_y1j);//с12
					row.put(index1_10+13, 3.0 * y_org_y1j * y_org_y1j * y_len);//с13

					row.put(index2_10+3, - 2.0 * x_len);//с3
					row.put(index2_10+4, -       y_len);//с4
					
					row.put(index2_10+6, - 6.0 * x_org_x2j * x_len);//с6
					row.put(index2_10+7, - 2.0 * (x_org_x2j * y_len + y_org_y2j * x_len));//с7
					row.put(index2_10+8, - 2.0 * y_org_y2j * y_len);//с8

					row.put(index2_10+10, - 12.0 * x_org_x2j * x_org_x2j * x_len);//с10
					row.put(index2_10+11, 
						- 6.0 * x_org_x2j * x_len * y_org_y2j 
						- 3.0 * x_org_x2j * x_org_x2j * y_len);//с11
					row.put(index2_10+12, 
						- 4.0 * x_org_x2j * y_org_y2j * y_len 
						- 2.0 * x_len * y_org_y2j * y_org_y2j);//с12
					row.put(index2_10+13, - 3.0 * y_org_y2j * y_org_y2j * y_len);//с13

					M.push_back(row);	B.push_back(0.0);


					row.clear();	
					//(3*c6*x_len^2 + 2*c7*x_len*y_len + c8*y_len^2)*t^2+

					// (
					// 3*c6*x_len^2+
					// 2*c7*x_len*y_len+
					// c8*y_len^2+

					// 12*c10*x_org_xj*x_len^2
					// 6*c11*x_org_xj*x_len*y_len+
					// 3*c11*x_len^2*y_org_yj+
					// 4*c12*x_len*y_org_yj*y_len+
					// 2*c12*x_org_xj*y_len^2+
					// 3*c13*y_org_yj*y_len^2+
					// )*t^2+

					row.put(index1_10+6, 3.0 * x_len * x_len);//с6
					row.put(index1_10+7, 2.0 * x_len * y_len);//с7
					row.put(index1_10+8,       y_len * y_len);//с8

					row.put(index1_10+10, 12.0 * x_org_x1j * x_len * x_len);//с10
					row.put(index1_10+11, 
						+ 6.0 * x_org_x1j * x_len * y_len 
						+ 3.0 * x_len * x_len * y_org_y1j);//с11
					row.put(index1_10+12, 
						+ 4.0 * x_len * y_org_y1j * y_len 
						+ 2.0 * x_org_x1j * y_len * y_len);//с12
					row.put(index1_10+13, 3.0 * y_org_y1j * y_len * y_len);//с13

					row.put(index2_10+6, - 3.0 * x_len * x_len);//с6
					row.put(index2_10+7, - 2.0 * x_len * y_len);//с7
					row.put(index2_10+8, -       y_len * y_len);//с8

					row.put(index2_10+10, - 12.0 * x_org_x2j * x_len * x_len);//с10
					row.put(index2_10+11, 
						- 6.0 * x_org_x2j * x_len * y_len 
						- 3.0 * x_len * x_len * y_org_y2j);//с11
					row.put(index2_10+12, 
						- 4.0 * x_len * y_org_y2j * y_len 
						- 2.0 * x_org_x2j * y_len * y_len);//с12
					row.put(index2_10+13, - 3.0 * y_org_y2j * y_len * y_len);//с13

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					// (
					// 4*c10*x_len^3+
					// 3*c11*x_len^2*y_len+
					// 2*c12*x_len*y_len^2
					// c13*y_len^3+
					// )*t^3+

					row.put(index1_10+10, + 4.0 * x_len * x_len * x_len);//с10
					row.put(index1_10+11, + 3.0 * x_len * x_len * y_len);//с11
					row.put(index1_10+12, + 2.0 * x_len * y_len * y_len);//с12
					row.put(index1_10+13, +       y_len * y_len * y_len);//с13

					row.put(index2_10+10, - 4.0 * x_len * x_len * x_len);//с10
					row.put(index2_10+11, - 3.0 * x_len * x_len * y_len);//с11
					row.put(index2_10+12, - 2.0 * x_len * y_len * y_len);//с12
					row.put(index2_10+13, -       y_len * y_len * y_len);//с13

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
		}

		if(add_first_der_y)
		{	
			switch (order)
			{
			case 2:
				{
#if SPARSE_ROW_EX
					row._order = 1;
#endif
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_y(t) := 
					// c2+
					// c4*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
					// c7*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

					// = 

					//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
					//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
					//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

					row.clear();	
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					row.put(index1_10+2, 1.0);//с2

					row.put(index1_10+4,       x_org_x1j);//с4
					row.put(index1_10+5, 2.0 * y_org_y1j);//с5
					

					row.put(index2_10+2, - 1.0);//с2

					row.put(index2_10+4, -       x_org_x2j);//с4
					row.put(index2_10+5, - 2.0 * y_org_y2j);//с5
					

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					row.put(index1_10+4,       x_len);//с4
					row.put(index1_10+5, 2.0 * y_len);//с5
					

					row.put(index2_10+4, -       x_len);//с4
					row.put(index2_10+5, - 2.0 * y_len);//с5
					

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 3:
				{
#if SPARSE_ROW_EX
					row._order = 1;
#endif
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_y(t) := 
					// c2+
					// c4*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
					// c7*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

					// = 

					//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
					//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
					//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

					row.clear();	
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					row.put(index1_10+2, 1.0);//с2

					row.put(index1_10+4,       x_org_x1j);//с4
					row.put(index1_10+5, 2.0 * y_org_y1j);//с5
					
					row.put(index1_10+7,       x_org_x1j * x_org_x1j);//с7
					row.put(index1_10+8, 2.0 * x_org_x1j * y_org_y1j);//с8
					row.put(index1_10+9, 3.0 * y_org_y1j * y_org_y1j);//с9

					row.put(index2_10+2, - 1.0);//с2

					row.put(index2_10+4, -       x_org_x2j);//с4
					row.put(index2_10+5, - 2.0 * y_org_y2j);//с5
					
					row.put(index2_10+7, -       x_org_x2j * x_org_x2j);//с7
					row.put(index2_10+8, - 2.0 * x_org_x2j * y_org_y2j);//с8
					row.put(index2_10+9, - 3.0 * y_org_y2j * y_org_y2j);//с9

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					row.put(index1_10+4,       x_len);//с4
					row.put(index1_10+5, 2.0 * y_len);//с5
					
					row.put(index1_10+7, 2.0 * x_org_x1j * x_len);//с7
					row.put(index1_10+8, 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len) );//с8
					row.put(index1_10+9, 6.0 * y_org_y1j * y_len);//с9

					row.put(index2_10+4, -       x_len);//с4
					row.put(index2_10+5, - 2.0 * y_len);//с5
					
					row.put(index2_10+7, - 2.0 * x_org_x2j * x_len);//с7
					row.put(index2_10+8, - 2.0 * (x_org_x2j * y_len + y_org_y2j * x_len) );//с8
					row.put(index2_10+9, - 3.0 * y_org_y2j * y_len);//с9

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(c7*x_len^2 + 2*c8*x_len*y_len + 3*c9*y_len^2)*t^2+

					row.put(index1_10+7,       x_len * x_len);//с7
					row.put(index1_10+8, 2.0 * x_len * y_len);//с8
					row.put(index1_10+9, 3.0 * y_len * y_len);//с9

					row.put(index2_10+7, - 2.0 * x_len * x_len);//с7
					row.put(index2_10+8, - 2.0 * x_len * y_len);//с8
					row.put(index2_10+9, - 3.0 * y_len * y_len);//с9

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 4:
				{
#if SPARSE_ROW_EX
					row._order = 1;
#endif
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_y(t) := 
					// c2+
					// c4*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
					// c7*(x_org-xj+(x_dest-x_org)*t)^2+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
					// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

					// = 

					//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
					//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
					//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

					// (4*c14*y_len^3+2*c12*x_len^2*y_len+c11*x_len^3+3*c13*x_len*y_len^2)*t^3+
					// (c7*x_len^2+2*c12*x_len^2*y_org_yj+3*c11*x_org_xj*x_len^2+3*c9*y_len^2+6*c13*x_len*y_org_yj*y_len+12*c14*y_org_yj*y_len^2+3*c13*x_org_xj*y_len^2+2*c8*x_len*y_len+4*c12*x_org_xj*x_len*y_len)*t^2+
					// (2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+2*c7*x_org_xj*x_len+12*c14*y_org_yj^2*y_len+3*c11*x_org_xj^2*x_len+2*c12*x_org_xj^2*y_len+6*c9*y_org_yj*y_len+4*c12*x_org_xj*x_len*y_org_yj+c4*x_len+3*c13*x_len*y_org_yj^2+6*c13*x_org_xj*y_org_yj*y_len)*t+
					// c2+c11*x_org_xj^3+c4*x_org_xj+2*c5*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2+2*c8*x_org_xj*y_org_yj+4*c14*y_org_yj^3+2*c12*x_org_xj^2*y_org_yj+3*c13*x_org_xj*y_org_yj^2

					row.clear();	
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					// c2+

					// c4*x_org_xj+
					// 2*c5*y_org_yj+

					// c7*x_org_xj^2+
					// 2*c8*x_org_xj*y_org_yj+
					// 3*c9*y_org_yj^2+

					// c11*x_org_xj^3+
					// 2*c12*x_org_xj^2*y_org_yj+
					// 3*c13*x_org_xj*y_org_yj^2
					// 4*c14*y_org_yj^3+

					row.put(index1_10+2, 1.0);//с2

					row.put(index1_10+4,       x_org_x1j);//с4
					row.put(index1_10+5, 2.0 * y_org_y1j);//с5
					
					row.put(index1_10+7,       x_org_x1j * x_org_x1j);//с7
					row.put(index1_10+8, 2.0 * x_org_x1j * y_org_y1j);//с8
					row.put(index1_10+9, 3.0 * y_org_y1j * y_org_y1j);//с9

					row.put(index1_10+11,       x_org_x1j * x_org_x1j * x_org_x1j);//с11
					row.put(index1_10+12, 2.0 * x_org_x1j * x_org_x1j * y_org_y1j);//с12
					row.put(index1_10+13, 3.0 * x_org_x1j * y_org_y1j * y_org_y1j);//с13
					row.put(index1_10+14, 4.0 * y_org_y1j * y_org_y1j * y_org_y1j);//с14

					row.put(index2_10+2, - 1.0);//с2

					row.put(index2_10+4, -       x_org_x2j);//с4
					row.put(index2_10+5, - 2.0 * y_org_y2j);//с5
					
					row.put(index2_10+7, -       x_org_x2j * x_org_x2j);//с7
					row.put(index2_10+8, - 2.0 * x_org_x2j * y_org_y2j);//с8
					row.put(index2_10+9, - 3.0 * y_org_y2j * y_org_y2j);//с9

					row.put(index2_10+11, -       x_org_x2j * x_org_x2j * x_org_x2j);//с11
					row.put(index2_10+12, - 2.0 * x_org_x2j * x_org_x2j * y_org_y2j);//с12
					row.put(index2_10+13, - 3.0 * x_org_x2j * y_org_y2j * y_org_y2j);//с13
					row.put(index2_10+14, - 4.0 * y_org_y2j * y_org_y2j * y_org_y2j);//с14

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					// (
					// c4*x_len+
					// 2*c5*y_len+

					// 2*c7*x_org_xj*x_len+
					// 2*c8*x_org_xj*y_len+
					// 2*c8*x_len*y_org_yj+
					// 6*c9*y_org_yj*y_len+

					// 3*c11*x_org_xj^2*x_len+
					// 2*c12*x_org_xj^2*y_len+
					// 4*c12*x_org_xj*x_len*y_org_yj+
					// 3*c13*x_len*y_org_yj^2+
					// 6*c13*x_org_xj*y_org_yj*y_len
					// 12*c14*y_org_yj^2*y_len+
					// )*t+
					
					row.put(index1_10+4,       x_len);//с4
					row.put(index1_10+5, 2.0 * y_len);//с5
					
					row.put(index1_10+7, 2.0 * x_org_x1j * x_len);//с7
					row.put(index1_10+8, 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len) );//с8
					row.put(index1_10+9, 6.0 * y_org_y1j * y_len);//с9

					row.put(index1_10+11, 
						+ 3.0 * x_org_x1j * x_org_x1j * x_len);//с11
					row.put(index1_10+12, 
						+ 2.0 * x_org_x1j * x_org_x1j * y_len
						+ 4.0 * x_org_x1j * x_len * y_org_y1j
						);//с12
					row.put(index1_10+13, 
						+ 3.0 * x_len * y_org_y1j * y_org_y1j
						+ 6.0 * x_org_x1j * y_org_y1j * y_len
						);//с13
					row.put(index1_10+14, 
						+ 12.0 * y_org_y1j * y_org_y1j * y_len);//с14

					row.put(index2_10+4, -       x_len);//с4
					row.put(index2_10+5, - 2.0 * y_len);//с5
					
					row.put(index2_10+7, - 2.0 * x_org_x2j * x_len);//с7
					row.put(index2_10+8, - 2.0 * (x_org_x2j * y_len + y_org_y2j * x_len) );//с8
					row.put(index2_10+9, - 3.0 * y_org_y2j * y_len);//с9

					row.put(index2_10+11, 
						- 3.0 * x_org_x2j * x_org_x2j * x_len);//с11
					row.put(index2_10+12, 
						- 2.0 * x_org_x2j * x_org_x2j * y_len
						- 4.0 * x_org_x2j * x_len * y_org_y2j
						);//с12
					row.put(index2_10+13, 
						- 3.0 * x_len * y_org_y2j * y_org_y2j
						- 6.0 * x_org_x2j * y_org_y2j * y_len
						);//с13
					row.put(index2_10+14, 
						- 12.0 * y_org_y2j * y_org_y2j * y_len);//с14

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					//(c7*x_len^2 + 2*c8*x_len*y_len + 3*c9*y_len^2)*t^2+

					// (
					// c7*x_len^2+
					// 2*c8*x_len*y_len+
					// 3*c9*y_len^2+

					// 3*c11*x_org_xj*x_len^2+
					// 2*c12*x_len^2*y_org_yj+
					// 4*c12*x_org_xj*x_len*y_len
					// 3*c13*x_org_xj*y_len^2+
					// 6*c13*x_len*y_org_yj*y_len+
					// 12*c14*y_org_yj*y_len^2+
					// )*t^2+

					row.put(index1_10+7,       x_len * x_len);//с7
					row.put(index1_10+8, 2.0 * x_len * y_len);//с8
					row.put(index1_10+9, 3.0 * y_len * y_len);//с9

					row.put(index1_10+11, 
						+ 3.0 * x_org_x1j * x_len * x_len);//с11
					row.put(index1_10+12, 
						+ 2.0 * x_len * x_len * y_org_y1j
						+ 4.0 * x_org_x1j * x_len * y_len
						);//с12
					row.put(index1_10+13, 
						+ 3.0 * x_org_x1j * y_len * y_len
						+ 6.0 * x_len * y_org_y1j * y_len
						);//с13
					row.put(index1_10+14, 
						+ 12.0 * y_org_y1j * y_len * y_len);//с14

					row.put(index2_10+7, - 2.0 * x_len * x_len);//с7
					row.put(index2_10+8, - 2.0 * x_len * y_len);//с8
					row.put(index2_10+9, - 3.0 * y_len * y_len);//с9

					row.put(index2_10+11, 
						- 3.0 * x_org_x2j * x_len * x_len);//с11
					row.put(index2_10+12, 
						- 2.0 * x_len * x_len * y_org_y2j
						- 4.0 * x_org_x2j * x_len * y_len
						);//с12
					row.put(index2_10+13, 
						- 3.0 * x_org_x2j * y_len * y_len
						- 6.0 * x_len * y_org_y2j * y_len
						);//с13
					row.put(index2_10+14, 
						- 12.0 * y_org_y2j * y_len * y_len);//с14

					M.push_back(row);	B.push_back(0.0);

					row.clear();	
					// (
					// c11*x_len^3+
					// 2*c12*x_len^2*y_len+
					// 3*c13*x_len*y_len^2
					// 4*c14*y_len^3+
					// )*t^3+

					row.put(index1_10+11, 
						+ x_len * x_len * x_len);//с11
					row.put(index1_10+12, 
						+ 2.0 * x_len * x_len * y_len);//с12
					row.put(index1_10+13, 
						+ 3.0 * x_len * y_len * y_len);//с13
					row.put(index1_10+14, 
						+ 4.0 * y_len * y_len * y_len);//с14

					row.put(index2_10+11, 
						- x_len * x_len * x_len);//с11
					row.put(index2_10+12, 
						- 2.0 * x_len * x_len * y_len);//с12
					row.put(index2_10+13, 
						- 3.0 * x_len * y_len * y_len);//с13
					row.put(index2_10+14, 
						- 4.0 * y_len * y_len * y_len);//с14

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
		}
		if(add_second_der)
		{
#if SPARSE_ROW_EX
			row._order = 2;
#endif

#if USE_SECOND_DERIVATIVES_EQUATIONS
			switch(order)
			{
			case 2:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_xx(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c3+
					// 6*c6*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c7*(y_org-yj+(y_dest-y_org)*t)

					// = 

					//(6*c6*x_len+2*c7*y_len)*t+
					//2*c3+6*c6*x_org_xj+2*c7*y_org_yj

					row.clear();	
					//2*c3 + 6*c6*x_org_xj + 2*c7*y_org_yj
					row.put(index1_10+3, 2.0);//с3				

					row.put(index2_10+3, - 2.0);//с3				

					M.push_back(row);	B.push_back(0.0);
					

					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_yy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c5+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)+
					// 6*c9*(y_org-yj+(y_dest-y_org)*t)

					// = 

					// (2*c8*x_len+6*c9*y_len)*t+
					//2*c5+2*c8*x_org_xj+6*c9*y_org_yj

					row.clear();	
					//2*c5 + 2*c8*x_org_xj + 6*c9*y_org_yj
					row.put(index1_10+5, + 2.0);//с5				

					row.put(index2_10+5, - 2.0);//с5				

					M.push_back(row);	B.push_back(0.0);
					

					
					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_xy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// c4+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c8*(y_org-yj+(y_dest-y_org)*t)

					// =
					
					//(2*c7*x_len+2*c8*y_len)*t+
					//c4+2*c7*x_org_xj+2*c8*y_org_yj

					row.clear();
					//c4 + 2*c7*x_org_xj + 2*c8*y_org_yj
					row.put(index1_10+4, + 1.0);//с4				

					row.put(index2_10+4, - 1.0);//с4				

					M.push_back(row);	B.push_back(0.0);

				}
				break;
			case 3:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_xx(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c3+
					// 6*c6*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c7*(y_org-yj+(y_dest-y_org)*t)

					// = 

					//(6*c6*x_len+2*c7*y_len)*t+
					//2*c3+6*c6*x_org_xj+2*c7*y_org_yj

					row.clear();	
					//2*c3 + 6*c6*x_org_xj + 2*c7*y_org_yj
					row.put(index1_10+3, 2.0);//с3				
					row.put(index1_10+6, 6.0 * x_org_x1j);//с6
					row.put(index1_10+7, 2.0 * y_org_y1j);//с7

					row.put(index2_10+3, - 2.0);//с3				
					row.put(index2_10+6, - 6.0 * x_org_x2j);//с6
					row.put(index2_10+7, - 2.0 * y_org_y2j);//с7

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					//(6*c6*x_len + 2*c7*y_len)*t+
					row.put(index1_10+6, 6.0 * x_len);//с6
					row.put(index1_10+7, 2.0 * y_len);//с7

					row.put(index2_10+6, - 6.0 * x_len);//с6
					row.put(index2_10+7, - 2.0 * y_len);//с7

					M.push_back(row);	B.push_back(0.0);
					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_yy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c5+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)+
					// 6*c9*(y_org-yj+(y_dest-y_org)*t)

					// = 

					// (2*c8*x_len+6*c9*y_len)*t+
					//2*c5+2*c8*x_org_xj+6*c9*y_org_yj

					row.clear();	
					//2*c5 + 2*c8*x_org_xj + 6*c9*y_org_yj
					row.put(index1_10+5, + 2.0);//с5				
					row.put(index1_10+8, + 2.0 * x_org_x1j);//с8
					row.put(index1_10+9, + 6.0 * y_org_y1j);//с9

					row.put(index2_10+5, - 2.0);//с5				
					row.put(index2_10+8, - 2.0 * x_org_x2j);//с8
					row.put(index2_10+9, - 6.0 * y_org_y2j);//с9

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					// (2*c8*x_len + 6*c9*y_len)*t+
					row.put(index1_10+8, + 2.0 * x_len);//с8
					row.put(index1_10+9, + 6.0 * y_len);//с9

					row.put(index2_10+8, - 2.0 * x_len);//с8
					row.put(index2_10+9, - 6.0 * y_len);//с9

					M.push_back(row);	B.push_back(0.0);
					
					
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_xy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// c4+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c8*(y_org-yj+(y_dest-y_org)*t)

					// =
					
					//(2*c7*x_len+2*c8*y_len)*t+
					//c4+2*c7*x_org_xj+2*c8*y_org_yj

					row.clear();
					//c4 + 2*c7*x_org_xj + 2*c8*y_org_yj
					row.put(index1_10+4, + 1.0);//с4				
					row.put(index1_10+7, + 2.0 * x_org_x1j);//с7
					row.put(index1_10+8, + 2.0 * y_org_y1j);//с8

					row.put(index2_10+4, - 1.0);//с4				
					row.put(index2_10+7, - 2.0 * x_org_x2j);//с7
					row.put(index2_10+8, - 2.0 * y_org_y2j);//с8

					M.push_back(row);	B.push_back(0.0);

					row.clear();
					//(2*c7*x_len + 2*c8*y_len)*t+
					row.put(index1_10+7, + 2.0 * x_len);//с7
					row.put(index1_10+8, + 2.0 * y_len);//с8

					row.put(index2_10+7, - 2.0 * x_len);//с7
					row.put(index2_10+8, - 2.0 * y_len);//с8

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			case 4:
				{
					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************

					// diff_xx(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c3+
					// 6*c6*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c7*(y_org-yj+(y_dest-y_org)*t)

					// = 

					//(6*c6*x_len+2*c7*y_len)*t+
					//2*c3+6*c6*x_org_xj+2*c7*y_org_yj

					// (12*c10*x_len^2+6*c11*x_len*y_len+2*c12*y_len^2)*t^2+
					// (6*c6*x_len+24*c10*x_org_xj*x_len+6*c11*x_org_xj*y_len+6*c11*x_len*y_org_yj+2*c7*y_len+4*c12*y_org_yj*y_len)*t+
					// 2*c3+6*c6*x_org_xj+2*c7*y_org_yj+6*c11*x_org_xj*y_org_yj+12*c10*x_org_xj^2+2*c12*y_org_yj^2

					row.clear();	
					//2*c3 + 6*c6*x_org_xj + 2*c7*y_org_yj

					// 2*c3+
					// 6*c6*x_org_xj+
					// 2*c7*y_org_yj+

					// 12*c10*x_org_xj^2+
					// 6*c11*x_org_xj*y_org_yj+
					// 2*c12*y_org_yj^2
					row.put(index1_10+3, 2.0);//с3				
					row.put(index1_10+6, 6.0 * x_org_x1j);//с6
					row.put(index1_10+7, 2.0 * y_org_y1j);//с7

					row.put(index1_10+10, 12.0 * x_org_x1j * x_org_x1j);//с10
					row.put(index1_10+11, 6.0 * x_org_x1j * y_org_y1j);//с11
					row.put(index1_10+12, 2.0 * y_org_y1j * y_org_y1j);//с12

					row.put(index2_10+3, - 2.0);//с3				
					row.put(index2_10+6, - 6.0 * x_org_x2j);//с6
					row.put(index2_10+7, - 2.0 * y_org_y2j);//с7

					row.put(index2_10+10, - 12.0 * x_org_x2j * x_org_x2j);//с10
					row.put(index2_10+11, - 6.0 * x_org_x2j * y_org_y2j);//с11
					row.put(index2_10+12, - 2.0 * y_org_y2j * y_org_y2j);//с12

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					//(6*c6*x_len + 2*c7*y_len)*t+

					// (
					// 6*c6*x_len+
					// 2*c7*y_len+

					// 24*c10*x_org_xj*x_len+
					// 6*c11*x_org_xj*y_len+
					// 6*c11*x_len*y_org_yj+
					// 4*c12*y_org_yj*y_len
					// )*t+
					row.put(index1_10+6, 6.0 * x_len);//с6
					row.put(index1_10+7, 2.0 * y_len);//с7

					row.put(index1_10+10, 
						+ 24.0 * x_org_x1j * x_len);//с10
					row.put(index1_10+11, 
						+ 6.0 * x_org_x1j * y_len
						+ 6.0 * x_len * y_org_y1j
						);//с11
					row.put(index1_10+12, 
						+ 4.0 * y_org_y1j * y_len);//с12

					row.put(index2_10+6, - 6.0 * x_len);//с6
					row.put(index2_10+7, - 2.0 * y_len);//с7

					row.put(index2_10+10, 
						- 24.0 * x_org_x2j * x_len);//с10
					row.put(index2_10+11, 
						- 6.0 * x_org_x2j * y_len
						- 6.0 * x_len * y_org_y2j
						);//с11
					row.put(index2_10+12, 
						- 4.0 * y_org_y2j * y_len);//с12

					M.push_back(row);	B.push_back(0.0);
					
					
					row.clear();	
					// (
					// 12*c10*x_len^2+
					// 6*c11*x_len*y_len+
					// 2*c12*y_len^2
					// )*t^2+

					row.put(index1_10+10, 
						+ 12.0 * x_len * x_len);//с10
					row.put(index1_10+11, 
						+ 6.0 * x_len * y_len);//с11
					row.put(index1_10+12, 
						+ 2.0 * y_len * y_len);//с12

					row.put(index2_10+10, 
						- 12.0 * x_len * x_len);//с10
					row.put(index2_10+11, 
						- 6.0 * x_len * y_len);//с11
					row.put(index2_10+12, 
						- 2.0 * y_len * y_len);//с12

					M.push_back(row);	B.push_back(0.0);

					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_yy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// 2*c5+
					// 2*c8*(x_org-xj+(x_dest-x_org)*t)+
					// 6*c9*(y_org-yj+(y_dest-y_org)*t)

					// = 

					// (2*c8*x_len+6*c9*y_len)*t+
					//2*c5+2*c8*x_org_xj+6*c9*y_org_yj

					// (2*c12*x_len^2+6*c13*x_len*y_len+12*c14*y_len^2)*t^2+
					// (2*c8*x_len+4*c12*x_org_xj*x_len+6*c13*x_org_xj*y_len+6*c13*x_len*y_org_yj+6*c9*y_len+24*c14*y_org_yj*y_len)*t+
					// 2*c5+2*c8*x_org_xj+6*c9*y_org_yj+6*c13*x_org_xj*y_org_yj+2*c12*x_org_xj^2+12*c14*y_org_yj^2

					row.clear();	
					//2*c5 + 2*c8*x_org_xj + 6*c9*y_org_yj
					
					// 2*c5+
					// 2*c8*x_org_xj+
					// 6*c9*y_org_yj+

					// 2*c12*x_org_xj^2+
					// 6*c13*x_org_xj*y_org_yj+
					// 12*c14*y_org_yj^2
					row.put(index1_10+5, + 2.0);//с5				
					row.put(index1_10+8, + 2.0 * x_org_x1j);//с8
					row.put(index1_10+9, + 6.0 * y_org_y1j);//с9

					row.put(index1_10+12, 2.0 * x_org_x1j * x_org_x1j);//с12
					row.put(index1_10+13, 6.0 * x_org_x1j * y_org_y1j);//с13
					row.put(index1_10+14, 12.0 * y_org_y1j * y_org_y1j);//с14

					row.put(index2_10+5, - 2.0);//с5				
					row.put(index2_10+8, - 2.0 * x_org_x2j);//с8
					row.put(index2_10+9, - 6.0 * y_org_y2j);//с9

					row.put(index2_10+12, - 2.0 * x_org_x2j * x_org_x2j);//с12
					row.put(index2_10+13, - 6.0 * x_org_x2j * y_org_y2j);//с13
					row.put(index2_10+14, - 12.0 * y_org_y2j * y_org_y2j);//с14

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					// (2*c8*x_len + 6*c9*y_len)*t+

					// (
					// 2*c8*x_len+
					// 6*c9*y_len+

					// 4*c12*x_org_xj*x_len+
					// 6*c13*x_org_xj*y_len+
					// 6*c13*x_len*y_org_yj+
					// 24*c14*y_org_yj*y_len
					// )*t+
					row.put(index1_10+8, + 2.0 * x_len);//с8
					row.put(index1_10+9, + 6.0 * y_len);//с9

					row.put(index1_10+12, 
						+ 4.0 * x_org_x1j * x_len);//с12
					row.put(index1_10+13, 
						+ 6.0 * x_org_x1j * y_len
						+ 6.0 * x_len * y_org_y1j
						);//с13
					row.put(index1_10+14, 
						+ 24.0 * y_org_y1j * y_len);//с14

					row.put(index2_10+8, - 2.0 * x_len);//с8
					row.put(index2_10+9, - 6.0 * y_len);//с9

					row.put(index2_10+12, 
						- 4.0 * x_org_x2j * x_len);//с12
					row.put(index2_10+13, 
						- 6.0 * x_org_x2j * y_len
						- 6.0 * x_len * y_org_y2j
						);//с13
					row.put(index2_10+14, 
						- 24.0 * y_org_y2j * y_len);//с14

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();	
					// (
					// 2*c12*x_len^2+
					// 6*c13*x_len*y_len+
					// 12*c14*y_len^2
					// )*t^2+
					
					row.put(index1_10+10, 
						+ 2.0 * x_len * x_len);//с10
					row.put(index1_10+11, 
						+ 6.0 * x_len * y_len);//с11
					row.put(index1_10+12, 
						+ 12.0 * y_len * y_len);//с12

					row.put(index2_10+10, 
						- 2.0 * x_len * x_len);//с10
					row.put(index2_10+11, 
						- 6.0 * x_len * y_len);//с11
					row.put(index2_10+12, 
						- 12.0 * y_len * y_len);//с12

					M.push_back(row);	B.push_back(0.0);

					// добавляем строку в уравнение
					//*****************************************************************************************
					//*****************************************************************************************
					// diff_xy(x_org+(x_dest-x_org)*t,y_org+(y_dest-y_org)*t) := 
					// c4+
					// 2*c7*(x_org-xj+(x_dest-x_org)*t)+
					// 2*c8*(y_org-yj+(y_dest-y_org)*t)

					// =
					
					//(2*c7*x_len+2*c8*y_len)*t+
					//c4+2*c7*x_org_xj+2*c8*y_org_yj

					// (3*c11*x_len^2+4*c12*x_len*y_len+3*c13*y_len^2)*t^2+
					// (2*c7*x_len+6*c11*x_org_xj*x_len+4*c12*x_org_xj*y_len+4*c12*x_len*y_org_yj+2*c8*y_len+6*c13*y_org_yj*y_len)*t+
					// c4+2*c7*x_org_xj+2*c8*y_org_yj+4*c12*x_org_xj*y_org_yj+3*c11*x_org_xj^2+3*c13*y_org_yj^2

					row.clear();
					//c4 + 2*c7*x_org_xj + 2*c8*y_org_yj

					// c4+
					// 2*c7*x_org_xj+
					// 2*c8*y_org_yj+

					// 3*c11*x_org_xj^2+
					// 4*c12*x_org_xj*y_org_yj+
					// 3*c13*y_org_yj^2
					row.put(index1_10+4, + 1.0);//с4				
					row.put(index1_10+7, + 2.0 * x_org_x1j);//с7
					row.put(index1_10+8, + 2.0 * y_org_y1j);//с8

					row.put(index1_10+11, 3.0 * x_org_x1j * x_org_x1j);//с11
					row.put(index1_10+12, 4.0 * x_org_x1j * y_org_y1j);//с12
					row.put(index1_10+13, 3.0 * y_org_y1j * y_org_y1j);//с13

					row.put(index2_10+4, - 1.0);//с4				
					row.put(index2_10+7, - 2.0 * x_org_x2j);//с7
					row.put(index2_10+8, - 2.0 * y_org_y2j);//с8

					row.put(index2_10+11, - 3.0 * x_org_x2j * x_org_x2j);//с11
					row.put(index2_10+12, - 4.0 * x_org_x2j * y_org_y2j);//с12
					row.put(index2_10+13, - 3.0 * y_org_y2j * y_org_y2j);//с13

					M.push_back(row);	B.push_back(0.0);

					row.clear();
					//(2*c7*x_len + 2*c8*y_len)*t+
					
					// (
					// 2*c7*x_len+
					// 2*c8*y_len+

					// 6*c11*x_org_xj*x_len+
					// 4*c12*x_org_xj*y_len+
					// 4*c12*x_len*y_org_yj+
					// 6*c13*y_org_yj*y_len
					// )*t+
					row.put(index1_10+7, + 2.0 * x_len);//с7
					row.put(index1_10+8, + 2.0 * y_len);//с8

					row.put(index1_10+11, 
						+ 6.0 * x_org_x1j * x_len);//с11
					row.put(index1_10+12, 
						+ 4.0 * x_org_x1j * y_len
						+ 4.0 * x_len * y_org_y1j
						);//с12
					row.put(index1_10+13, 
						+ 6.0 * y_org_y1j * y_len);//с13

					row.put(index2_10+7, - 2.0 * x_len);//с7
					row.put(index2_10+8, - 2.0 * y_len);//с8

					row.put(index2_10+11, 
						+ 6.0 * x_org_x2j * x_len);//с11
					row.put(index2_10+12, 
						+ 4.0 * x_org_x2j * y_len
						+ 4.0 * x_len * y_org_y2j
						);//с12
					row.put(index2_10+13, 
						+ 6.0 * y_org_y2j * y_len);//с13

					M.push_back(row);	B.push_back(0.0);
					
					row.clear();
					// (3*c11*x_len^2 + 4*c12*x_len*y_len + 3*c13*y_len^2)*t^2+
					
					row.put(index1_10+11, 
						+ 3.0 * x_len * x_len);//с11
					row.put(index1_10+12, 
						+ 4.0 * x_len * y_len);//с12
					row.put(index1_10+13, 
						+ 3.0 * y_len * y_len);//с13

					row.put(index2_10+11, 
						- 3.0 * x_len * x_len);//с11
					row.put(index2_10+12, 
						- 4.0 * x_len * y_len);//с12
					row.put(index2_10+13, 
						- 3.0 * y_len * y_len);//с13

					M.push_back(row);	B.push_back(0.0);
				}
				break;
			}
#endif
		}
	}
	else
		printf ("!AddRowsToEquation2 ! (p1 && p2)\n");
}


// заполняем строку 
void FillRow_NonFault(sparse_row & row, // заполняемая строка
					  int order, // порялок полигона
					  int pw_t, // степень при t
					  size_t index1_10, // начальный индекс
					  double x_org_x1j,
					  double y_org_y1j,
					  double x_len,
					  double y_len,
					  double m) // множитель знака и наклона
{
	switch (order)
	{
	case 1:
		{
			// f(t) := 
			// (c3*x_len^2+c4*x_len*y_len+c5*y_len^2)*t^2+
			// (c1*x_len+2*c3*x_org_xj*x_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj+c2*y_len+2*c5*y_org_yj*y_len)*t+
			// zj + c1*x_org_xj+c2*y_org_yj+c4*x_org_xj*y_org_yj+c3*x_org_xj^2+c5*y_org_yj^2
			switch(pw_t)
			{
			case 0:
				{
					// zj + c1*x_org_xj + c2*y_org_yj + c4*x_org_xj*y_org_yj + c3*x_org_xj^2
					row.plus(index1_10+0, m * 1.0);//с0
					row.plus(index1_10+1, m * x_org_x1j);//с1
					row.plus(index1_10+2, m * y_org_y1j);//с2
				}
				break;
			case 1:
				{		
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//)*t
					// (c1*x_len+2*c3*x_org_xj*x_len+c2*y_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj)*t+

					row.plus(index1_10+1,  m * x_len);//с1
					row.plus(index1_10+2,  m * y_len);//с2
				}
				break;
			}
		}
		break;
	case 2:
		{
			// f(t) := 
			// (c3*x_len^2+c4*x_len*y_len+c5*y_len^2)*t^2+
			// (c1*x_len+2*c3*x_org_xj*x_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj+c2*y_len+2*c5*y_org_yj*y_len)*t+
			// zj + c1*x_org_xj+c2*y_org_yj+c4*x_org_xj*y_org_yj+c3*x_org_xj^2+c5*y_org_yj^2
			switch(pw_t)
			{
			case 0:
				{
					// zj + c1*x_org_xj + c2*y_org_yj + c4*x_org_xj*y_org_yj + c3*x_org_xj^2
					row.plus(index1_10+0, m * 1.0);//с0
					row.plus(index1_10+1, m * x_org_x1j);//с1
					row.plus(index1_10+2, m * y_org_y1j);//с2

					row.plus(index1_10+3, m * (x_org_x1j) * (x_org_x1j));//с3
					row.plus(index1_10+4, m * (x_org_x1j) * (y_org_y1j));//с4
					row.plus(index1_10+5, m * (y_org_y1j) * (y_org_y1j));//с5
				}
				break;
			case 1:
				{		
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//)*t
					// (c1*x_len+2*c3*x_org_xj*x_len+c2*y_len+c4*x_org_xj*y_len+c4*x_len*y_org_yj)*t+

					row.plus(index1_10+1,  m * x_len);//с1
					row.plus(index1_10+2,  m * y_len);//с2

					row.plus(index1_10+3,  m * 2.0 * x_org_x1j * x_len);//с3
					row.plus(index1_10+4,  m * (x_len * y_org_y1j + x_org_x1j * y_len));//с4
					row.plus(index1_10+5,  m * 2.0 * y_org_y1j * y_len);//с5
				}
				break;
			case 2:
				{
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					row.plus(index1_10+3, m * x_len * x_len);//с3
					row.plus(index1_10+4, m * x_len * y_len);//с4
					row.plus(index1_10+5, m * y_len * y_len);//с5
				}
				break;
			}
		}
		break;
	case 3:
		{
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************
			// f(t) := 
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

			// = 

			//(c8*x_len*y_len^2+c6*x_len^3+c7*x_len^2*y_len+c9*y_len^3)*t^3+
			//(c4*x_len*y_len+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c8*x_org_xj*y_len^2+c5*y_len^2+3*c9*y_org_yj*y_len^2+3*c6*x_org_xj*x_len^2+c7*x_len^2*y_org_yj+2*c8*x_len*y_org_yj*y_len)*t^2+
			//(c8*x_len*y_org_yj^2 + c2*y_len + c4*x_len*y_org_yj + c7*x_org_xj^2*y_len + c1*x_len+c4*x_org_xj*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c3*x_org_xj*x_len+2*c8*x_org_xj*y_org_yj*y_len+3*c6*x_org_xj^2*x_len+3*c9*y_org_yj^2*y_len+2*c5*y_org_yj*y_len)*t+
			//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3

			switch(pw_t)
			{
			case 0:
				{
					//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3
					row.plus(index1_10+0, m * 1.0);//с0
					row.plus(index1_10+1, m * x_org_x1j);//с1
					row.plus(index1_10+2, m * y_org_y1j);//с2

					row.plus(index1_10+3, m * (x_org_x1j) * (x_org_x1j));//с3
					row.plus(index1_10+4, m * (x_org_x1j) * (y_org_y1j));//с4
					row.plus(index1_10+5, m * (y_org_y1j) * (y_org_y1j));//с5
					
					row.plus(index1_10+6, m * (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с6
					row.plus(index1_10+7, m * (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с7
					row.plus(index1_10+8, m * (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с8
					row.plus(index1_10+9, m * (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с9
				}
				break;
			case 1:
				{
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//2*c5*y_org_yj*y_len
					//3*c6*x_org_xj^2*x_len+
					//c7*x_org_xj^2*y_len + 
					//2*c7*x_org_xj*x_len*y_org_yj+
					//c8*x_len*y_org_yj^2 + 
					//2*c8*x_org_xj*y_org_yj*y_len+
					//3*c9*y_org_yj^2*y_len+
					//)*t

					row.plus(index1_10+1, m * x_len);//с1
					row.plus(index1_10+2, m * y_len);//с2

					row.plus(index1_10+3, m * 2.0 * x_org_x1j * x_len);//с3
					row.plus(index1_10+4, m * (x_len * y_org_y1j + x_org_x1j * y_len));//с4
					row.plus(index1_10+5, m * 2.0 * y_org_y1j * y_len);//с5
					
					row.plus(index1_10+6, m * 3.0 * x_org_x1j * x_org_x1j * x_len);//с6
					row.plus(index1_10+7, m * (x_org_x1j * x_org_x1j * y_len + 2.0 * x_org_x1j * x_len * y_org_y1j));//с7
					row.plus(index1_10+8, m * (x_len * y_org_y1j * y_org_y1j + 2.0 * x_org_x1j * y_len * y_org_y1j));//с8
					row.plus(index1_10+9, m * 3.0 * y_org_y1j * y_org_y1j * y_len);//с9
				}
				break;
			case 2:
				{
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					row.plus(index1_10+3, m * x_len * x_len);//с3
					row.plus(index1_10+4, m * x_len * y_len);//с4
					row.plus(index1_10+5, m * y_len * y_len);//с5
					
					row.plus(index1_10+6, m * 3.0 * x_org_x1j * x_len * x_len);//с6
					row.plus(index1_10+7, m * (x_len * x_len * y_org_y1j + 2.0 * x_org_x1j * x_len * y_len));//с7
					row.plus(index1_10+8, m * (x_org_x1j * y_len * y_len + 2.0 * y_org_y1j * x_len * y_len));//с8
					row.plus(index1_10+9, m * 3.0 * y_org_y1j * y_len * y_len);//с9
				}
				break;
			case 3:
				{
					//(c8*x_len*y_len^2 + c6*x_len^3 + c7*x_len^2*y_len + c9*y_len^3)*t^3+
					row.plus(index1_10+6, m * x_len * x_len * x_len);//с6
					row.plus(index1_10+7, m * x_len * x_len * y_len);//с7
					row.plus(index1_10+8, m * x_len * y_len * y_len);//с8
					row.plus(index1_10+9, m * y_len * y_len * y_len);//с9
				}
				break;
			}
		}
		break;
	case 4:
		{
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************
			// f(t) := 
			//c0+
			//c1*(x_org+(x_dest-x_org)*t-xj)+
			//c2*(y_org+(y_dest-y_org)*t-yj)+
			//c3*(x_org+(x_dest-x_org)*t-xj)^2+
			//c4*(x_org+(x_dest-x_org)*t-xj)*(y_org+(y_dest-y_org)*t-yj)+
			//c5*(y_org+(y_dest-y_org)*t-yj)^2+
			//c6*(x_org+(x_dest-x_org)*t-xj)^3+
			//c7*(x_org+(x_dest-x_org)*t-xj)^2*(y_org+(y_dest-y_org)*t-yj)+
			//c8*(x_org+(x_dest-x_org)*t-xj)*(y_org+(y_dest-y_org)*t-yj)^2+
			//c9*(y_org+(y_dest-y_org)*t-yj)^3+
			//c10*(x_org+(x_dest-x_org)*t-xj)^4+
			//c11*(x_org+(x_dest-x_org)*t-xj)^3*(y_org+(y_dest-y_org)*t-yj)+
			//c12*(x_org+(x_dest-x_org)*t-xj)^2*(y_org+(y_dest-y_org)*t-yj)^2+
			//c13*(x_org+(x_dest-x_org)*t-xj)*(y_org+(y_dest-y_org)*t-yj)^3+
			//c14*(y_org+(y_dest-y_org)*t-yj)^4

			// = 

			//(c8*x_len*y_len^2+c6*x_len^3+c7*x_len^2*y_len+c9*y_len^3)*t^3+
			//(c4*x_len*y_len+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c8*x_org_xj*y_len^2+c5*y_len^2+3*c9*y_org_yj*y_len^2+3*c6*x_org_xj*x_len^2+c7*x_len^2*y_org_yj+2*c8*x_len*y_org_yj*y_len)*t^2+
			//(c8*x_len*y_org_yj^2 + c2*y_len + c4*x_len*y_org_yj + c7*x_org_xj^2*y_len + c1*x_len+c4*x_org_xj*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c3*x_org_xj*x_len+2*c8*x_org_xj*y_org_yj*y_len+3*c6*x_org_xj^2*x_len+3*c9*y_org_yj^2*y_len+2*c5*y_org_yj*y_len)*t+
			//zj + c1*x_org_xj + c2*y_org_yj + c3*x_org_xj^2 + c5*y_org_yj^2 + c6*x_org_xj^3 + c7*x_org_xj^2*y_org_yj + c8*x_org_xj*y_org_yj^2 + c4*x_org_xj*y_org_yj + c9*y_org_yj^3


			// =

			// (c10*x_len^4+c14*y_len^4+c12*x_len^2*y_len^2+c13*x_len*y_len^3+c11*x_len^3*y_len)*t^4+
			// (c11*x_len^3*y_org_yj+c7*x_len^2*y_len+c9*y_len^3+4*c10*x_org_xj*x_len^3+2*c12*x_org_xj*x_len*y_len^2+2*c12*x_len^2*y_org_yj*y_len+4*c14*y_org_yj*y_len^3+3*c11*x_org_xj*x_len^2*y_len+c13*x_org_xj*y_len^3+c6*x_len^3+3*c13*x_len*y_org_yj*y_len^2+c8*x_len*y_len^2)*t^3+
			// (3*c11*x_org_xj^2*x_len*y_len+c4*x_len*y_len+c12*x_org_xj^2*y_len^2+c8*x_org_xj*y_len^2+c3*x_len^2+2*c7*x_org_xj*x_len*y_len+c7*x_len^2*y_org_yj+c12*x_len^2*y_org_yj^2+3*c6*x_org_xj*x_len^2+c5*y_len^2+2*c8*x_len*y_org_yj*y_len+6*c10*x_org_xj^2*x_len^2+3*c11*x_org_xj*x_len^2*y_org_yj+4*c12*x_org_xj*x_len*y_org_yj*y_len+3*c13*x_org_xj*y_org_yj*y_len^2+3*c9*y_org_yj*y_len^2+3*c13*x_len*y_org_yj^2*y_len+6*c14*y_org_yj^2*y_len^2)*t^2+
			// (2*c5*y_org_yj*y_len+c4*x_len*y_org_yj+3*c11*x_org_xj^2*x_len*y_org_yj+c13*x_len*y_org_yj^3+c4*x_org_xj*y_len+c11*x_org_xj^3*y_len+2*c8*x_org_xj*y_org_yj*y_len+c1*x_len+3*c6*x_org_xj^2*x_len+2*c12*x_org_xj*x_len*y_org_yj^2+c8*x_len*y_org_yj^2+c7*x_org_xj^2*y_len+c2*y_len+4*c10*x_org_xj^3*x_len+3*c13*x_org_xj*y_org_yj^2*y_len+3*c9*y_org_yj^2*y_len+2*c3*x_org_xj*x_len+4*c14*y_org_yj^3*y_len+2*c7*x_org_xj*x_len*y_org_yj+2*c12*x_org_xj^2*y_org_yj*y_len)*t+
			// c0+c10*x_org_xj^4+c3*x_org_xj^2+c5*y_org_yj^2+c6*x_org_xj^3+c14*y_org_yj^4+c13*x_org_xj*y_org_yj^3+c11*x_org_xj^3*y_org_yj+c12*x_org_xj^2*y_org_yj^2+c4*x_org_xj*y_org_yj+c2*y_org_yj+c7*x_org_xj^2*y_org_yj+c8*x_org_xj*y_org_yj^2+c1*x_org_xj+c9*y_org_yj^3

			switch(pw_t)
			{
			case 0:
				{
					// c0+
					// c1*x_org_xj+
					// c2*y_org_yj+
					// c3*x_org_xj^2+
					// c4*x_org_xj*y_org_yj+
					// c5*y_org_yj^2+
					// c6*x_org_xj^3+
					// c7*x_org_xj^2*y_org_yj+
					// c8*x_org_xj*y_org_yj^2+
					// c9*y_org_yj^3
					// c10*x_org_xj^4+
					// c11*x_org_xj^3*y_org_yj+
					// c12*x_org_xj^2*y_org_yj^2+
					// c13*x_org_xj*y_org_yj^3+
					// c14*y_org_yj^4+

					row.plus(index1_10+0, m * 1.0);//с0
					row.plus(index1_10+1, m * x_org_x1j);//с1
					row.plus(index1_10+2, m * y_org_y1j);//с2

					row.plus(index1_10+3, m * (x_org_x1j) * (x_org_x1j));//с3
					row.plus(index1_10+4, m * (x_org_x1j) * (y_org_y1j));//с4
					row.plus(index1_10+5, m * (y_org_y1j) * (y_org_y1j));//с5
					
					row.plus(index1_10+6, m * (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с6
					row.plus(index1_10+7, m * (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с7
					row.plus(index1_10+8, m * (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с8
					row.plus(index1_10+9, m * (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с9

					row.plus(index1_10+10, m * (x_org_x1j) * (x_org_x1j) * (x_org_x1j) * (x_org_x1j));//с10
					row.plus(index1_10+11, m * (x_org_x1j) * (x_org_x1j) * (x_org_x1j) * (y_org_y1j));//с11
					row.plus(index1_10+12, m * (x_org_x1j) * (x_org_x1j) * (y_org_y1j) * (y_org_y1j));//с12
					row.plus(index1_10+13, m * (x_org_x1j) * (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с13
					row.plus(index1_10+14, m * (y_org_y1j) * (y_org_y1j) * (y_org_y1j) * (y_org_y1j));//с14
				}
				break;
			case 1:
				{
					//(
					//c1*x_len+
					//c2*y_len + 
					//2*c3*x_org_xj*x_len+
					//c4*x_len*y_org_yj + 
					//c4*x_org_xj*y_len+
					//2*c5*y_org_yj*y_len
					//3*c6*x_org_xj^2*x_len+
					//c7*x_org_xj^2*y_len + 
					//2*c7*x_org_xj*x_len*y_org_yj+
					//c8*x_len*y_org_yj^2 + 
					//2*c8*x_org_xj*y_org_yj*y_len+
					//3*c9*y_org_yj^2*y_len+
					//)*t

										
					// (
					// c1*x_len+
					// c2*y_len+

					// 2*c3*x_org_xj*x_len+
					// c4*x_len*y_org_yj+
					// c4*x_org_xj*y_len+
					// 2*c5*y_org_yj*y_len+

					// 3*c6*x_org_xj^2*x_len+
					// c7*x_org_xj^2*y_len+
					// 2*c7*x_org_xj*x_len*y_org_yj+
					// c8*x_len*y_org_yj^2+
					// 2*c8*x_org_xj*y_org_yj*y_len+
					// 3*c9*y_org_yj^2*y_len+

					// 4*c10*x_org_xj^3*x_len+
					// c11*x_org_xj^3*y_len+
					// 3*c11*x_org_xj^2*x_len*y_org_yj+
					// 2*c12*x_org_xj*x_len*y_org_yj^2+
					// 2*c12*x_org_xj^2*y_org_yj*y_len
					// c13*x_len*y_org_yj^3+
					// 3*c13*x_org_xj*y_org_yj^2*y_len+
					// 4*c14*y_org_yj^3*y_len+
					// )*t+


					row.plus(index1_10+1, m * x_len);//с1
					row.plus(index1_10+2, m * y_len);//с2

					row.plus(index1_10+3, m * 2.0 * x_org_x1j * x_len);//с3
					row.plus(index1_10+4, m * (x_len * y_org_y1j + x_org_x1j * y_len));//с4
					row.plus(index1_10+5, m * 2.0 * y_org_y1j * y_len);//с5
					
					row.plus(index1_10+6, m * 3.0 * x_org_x1j * x_org_x1j * x_len);//с6
					row.plus(index1_10+7, m * (x_org_x1j * x_org_x1j * y_len + 2.0 * x_org_x1j * x_len * y_org_y1j));//с7
					row.plus(index1_10+8, m * (x_len * y_org_y1j * y_org_y1j + 2.0 * x_org_x1j * y_len * y_org_y1j));//с8
					row.plus(index1_10+9, m * 3.0 * y_org_y1j * y_org_y1j * y_len);//с9

					row.plus(index1_10+10, m * 
						4.0 * x_org_x1j * x_org_x1j * x_org_x1j * x_len);//с10
					row.plus(index1_10+11, m * 
						(x_org_x1j * x_org_x1j * x_org_x1j * y_len + 
						3.0 * x_org_x1j * x_org_x1j * x_len * y_org_y1j));//с11
					row.plus(index1_10+12, m * 
						(2.0 * x_org_x1j*x_len*y_org_y1j*y_org_y1j + 
						2.0 * x_org_x1j*x_org_x1j*y_org_y1j*y_len));//с12
					row.plus(index1_10+13, m * 
						(x_len * y_org_y1j * y_org_y1j * y_org_y1j + 
						3.0 * x_org_x1j * y_len * y_org_y1j * y_org_y1j));//с13
					row.plus(index1_10+14, m * 
						4.0 * y_org_y1j * y_org_y1j * y_org_y1j * y_len);//с14
				}
				break;
			case 2:
				{
					//(
					//c3*x_len^2+
					//c4*x_len*y_len+
					//c5*y_len^2+
					//3*c6*x_org_xj*x_len^2+
					//c7*x_len^2*y_org_yj+
					//2*c7*x_org_xj*x_len*y_len+
					//c8*x_org_xj*y_len^2+
					//2*c8*x_len*y_org_yj*y_len
					//3*c9*y_org_yj*y_len^2+
					//)*t^2+

					// (
					// c3*x_len^2+
					// c4*x_len*y_len+
					// c5*y_len^2+

					// 3*c6*x_org_xj*x_len^2+
					// c7*x_len^2*y_org_yj+
					// 2*c7*x_org_xj*x_len*y_len+
					// c8*x_org_xj*y_len^2+
					// 2*c8*x_len*y_org_yj*y_len+
					// 3*c9*y_org_yj*y_len^2+

					// 6*c10*x_org_xj^2*x_len^2+
					// 3*c11*x_org_xj^2*x_len*y_len+
					// 3*c11*x_org_xj*x_len^2*y_org_yj+
					// c12*x_org_xj^2*y_len^2+
					// c12*x_len^2*y_org_yj^2+
					// 4*c12*x_org_xj*x_len*y_org_yj*y_len+
					// 3*c13*x_org_xj*y_org_yj*y_len^2+
					// 3*c13*x_len*y_org_yj^2*y_len+
					// 6*c14*y_org_yj^2*y_len^2
					// )*t^2+
					row.plus(index1_10+3, m * x_len * x_len);//с3
					row.plus(index1_10+4, m * x_len * y_len);//с4
					row.plus(index1_10+5, m * y_len * y_len);//с5
					
					row.plus(index1_10+6, m * 3.0 * x_org_x1j * x_len * x_len);//с6
					row.plus(index1_10+7, m * 
						(x_len * x_len * y_org_y1j 
						+ 2.0 * x_org_x1j * x_len * y_len));//с7
					row.plus(index1_10+8, m * 
						(x_org_x1j * y_len * y_len + 
						2.0 * y_org_y1j * x_len * y_len));//с8
					row.plus(index1_10+9, m * 3.0 * y_org_y1j * y_len * y_len);//с9

					row.plus(index1_10+10, m * 
						6.0 * x_org_x1j * x_org_x1j * x_len * x_len);//с10
					row.plus(index1_10+11, m * 
						(3.0 * x_len * y_len * x_org_x1j * x_org_x1j 
						+ 3.0 * x_org_x1j * x_len * x_len * y_org_y1j));//с11
					row.plus(index1_10+12, m * 
						(x_org_x1j * x_org_x1j * y_len * y_len + 
						y_org_y1j * y_org_y1j * x_len * x_len + 
						4.0 * x_org_x1j * y_org_y1j * x_len * y_len));//с12
					row.plus(index1_10+13, m * 
						(3.0 * x_org_x1j * y_org_y1j * y_len * y_len + 
						3.0 * y_org_y1j * y_org_y1j * x_len * y_len));//с13
					row.plus(index1_10+14, m * 
						6.0 * y_org_y1j * y_org_y1j * y_len * y_len);//с14
				}
				break;
			case 3:	
				{
					//(c8*x_len*y_len^2 + c6*x_len^3 + c7*x_len^2*y_len + c9*y_len^3)*t^3+
					
					// (
					// c6*x_len^3+
					// c7*x_len^2*y_len+
					// c8*x_len*y_len^2
					// c9*y_len^3+

					// 4*c10*x_org_xj*x_len^3+
					// c11*x_len^3*y_org_yj+
					// 3*c11*x_org_xj*x_len^2*y_len+
					// 2*c12*x_org_xj*x_len*y_len^2+
					// 2*c12*x_len^2*y_org_yj*y_len+
					// c13*x_org_xj*y_len^3+
					// 3*c13*x_len*y_org_yj*y_len^2+
					// 4*c14*y_org_yj*y_len^3+
					// )*t^3+
					row.plus(index1_10+6, m * x_len * x_len * x_len);//с6
					row.plus(index1_10+7, m * x_len * x_len * y_len);//с7
					row.plus(index1_10+8, m * x_len * y_len * y_len);//с8
					row.plus(index1_10+9, m * y_len * y_len * y_len);//с9

					row.plus(index1_10+10, m * 
						4.0 * x_org_x1j * x_len * x_len * x_len);//с10
					row.plus(index1_10+11, m * 
						(x_len * x_len * x_len * y_org_y1j 
						+ 3.0 * x_org_x1j * x_len * x_len * y_len));//с11
					row.plus(index1_10+12, m * 
						(2.0 * x_org_x1j * x_len * y_len * y_len 
						+ 2.0 * x_len * x_len  * y_org_y1j * y_len));//с12
					row.plus(index1_10+13, m * 
						(x_org_x1j * y_len * y_len * y_len 
						+ 3.0 * x_len * y_org_y1j * y_len * y_len));//с13
					row.plus(index1_10+14, m * 
						4.0 * y_org_y1j * y_len * y_len * y_len);//с14
				}
				break;
			case 4:
				{
					// (
					// c10*x_len^4+
					// c11*x_len^3*y_len
					// c12*x_len^2*y_len^2+
					// c13*x_len*y_len^3+
					// c14*y_len^4+
					// )*t^4+

					row.plus(index1_10+10, m * 
						x_len * x_len * x_len * x_len);//с10
					row.plus(index1_10+11, m * 
						x_len * x_len * x_len * y_len);//с11
					row.plus(index1_10+12, m * 
						x_len * x_len * y_len * y_len);//с12
					row.plus(index1_10+13, m * 
						x_len * y_len * y_len * y_len);//с13
					row.plus(index1_10+14, m * 
						y_len * y_len * y_len * y_len);//с14
				}
				break;
			}
		}
		break;
	}
}
void FillRow_diff_x(sparse_row & row, // заполняемая строка
					  int order, // порялок полигона
					  int pw_t, // степень при t
					  size_t index1_10, // начальный индекс
					  double x_org_x1j,
					  double y_org_y1j,
					  double x_len,
					  double y_len,
					  double m) // множитель знака и наклона
{
	switch (order)
	{
	case 1:
		{
			// the first derivative
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************
			// diff_x(t) := 
			// c1+
			// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
			// c4*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// c8*(y_org-yj+(y_dest-y_org)*t)^2

			// = 
			//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
			//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
			//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.plus(index1_10+1, m * 1.0);//с1
				}
				break;
			}
		}
		break;
	case 2:
		{
			// the first derivative
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************
			// diff_x(t) := 
			// c1+
			// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
			// c4*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// c8*(y_org-yj+(y_dest-y_org)*t)^2

			// = 
			//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
			//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
			//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.plus(index1_10+1, m * 1.0);//с1

					row.plus(index1_10+3, m * 2.0 * x_org_x1j);//с3
					row.plus(index1_10+4, m *       y_org_y1j);//с4
				}
				break;
			case 1:
				{
					//(
					//2*c3*x_len+
					//c4*y_len+
					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					row.plus(index1_10+3, m * 2.0 * x_len);//с3
					row.plus(index1_10+4, m *       y_len);//с4
				}
				break;
			}
		}
		break;
	case 3:
		{
			// the first derivative
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************
			// diff_x(t) := 
			// c1+
			// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
			// c4*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// c8*(y_org-yj+(y_dest-y_org)*t)^2

			// = 
			//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
			//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
			//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					row.plus(index1_10+1, m * 1.0);//с1

					row.plus(index1_10+3, m * 2.0 * x_org_x1j);//с3
					row.plus(index1_10+4, m *       y_org_y1j);//с4
					
					row.plus(index1_10+6, m * 3.0 * x_org_x1j * x_org_x1j);//с6
					row.plus(index1_10+7, m * 2.0 * x_org_x1j * y_org_y1j);//с7
					row.plus(index1_10+8, m *       y_org_y1j * y_org_y1j);//с8
				}
				break;
			case 1:
				{
					//(
					//2*c3*x_len+
					//c4*y_len+

					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					row.plus(index1_10+3, m * 2.0 * x_len);//с3
					row.plus(index1_10+4, m *       y_len);//с4
					
					row.plus(index1_10+6, m * 6.0 * x_org_x1j * x_len);//с6
					row.plus(index1_10+7, m * 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len));//с7
					row.plus(index1_10+8, m * 2.0 * y_org_y1j * y_len);//с8
				}
				break;
			case 2:
				{
					//(3*c6*x_len^2 + 2*c7*x_len*y_len + c8*y_len^2)*t^2+

					row.plus(index1_10+6, m * 3.0 * x_len * x_len);//с6
					row.plus(index1_10+7, m * 2.0 * x_len * y_len);//с7
					row.plus(index1_10+8, m *       y_len * y_len);//с8
				}
				break;
			}
		}
		break;
	case 4:
		{
			// the first derivative
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************
			// diff_x(t) := 
			// c1+
			// 2*c3*(x_org-xj+(x_dest-x_org)*t)+
			// c4*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c6*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c7*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// c8*(y_org-yj+(y_dest-y_org)*t)^2

			// = 
			//(3*c6*x_len^2+2*c7*x_len*y_len+c8*y_len^2)*t^2+
			//(2*c3*x_len+6*c6*x_org_xj*x_len+2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+c4*y_len+2*c8*y_org_yj*y_len)*t+
			//c1+2*c3*x_org_xj+c4*y_org_yj+2*c7*x_org_xj*y_org_yj+3*c6*x_org_xj^2+c8*y_org_yj^2

			// (3*c11*x_len^2*y_len+c13*y_len^3+4*c10*x_len^3+2*c12*x_len*y_len^2)*t^3+
			// (c8*y_len^2+3*c11*x_len^2*y_org_yj+2*c12*x_org_xj*y_len^2+3*c6*x_len^2+2*c7*x_len*y_len+4*c12*x_len*y_org_yj*y_len+6*c11*x_org_xj*x_len*y_len+3*c13*y_org_yj*y_len^2+12*c10*x_org_xj*x_len^2)*t^2+
			// (2*c7*x_org_xj*y_len+2*c7*x_len*y_org_yj+2*c3*x_len+c4*y_len+2*c8*y_org_yj*y_len+12*c10*x_org_xj^2*x_len+3*c13*y_org_yj^2*y_len+6*c6*x_org_xj*x_len+4*c12*x_org_xj*y_org_yj*y_len+6*c11*x_org_xj*x_len*y_org_yj+3*c11*x_org_xj^2*y_len+2*c12*x_len*y_org_yj^2)*t+
			// c1+2*c3*x_org_xj+c4*y_org_yj+3*c6*x_org_xj^2+2*c7*x_org_xj*y_org_yj+4*c10*x_org_xj^3+c8*y_org_yj^2+2*c12*x_org_xj*y_org_yj^2+3*c11*x_org_xj^2*y_org_yj+c13*y_org_yj^3

			switch(pw_t)
			{
			case 0:
				{
					//c1 + 2*c3*x_org_xj + c4*y_org_yj + 2*c7*x_org_xj*y_org_yj + 3*c6*x_org_xj^2 + c8*y_org_yj^2
					
					// c1+
					// 2*c3*x_org_xj+
					// c4*y_org_yj+
					// 3*c6*x_org_xj^2+
					// 2*c7*x_org_xj*y_org_yj+
					// c8*y_org_yj^2+

					// 4*c10*x_org_xj^3+
					// 3*c11*x_org_xj^2*y_org_yj+
					// 2*c12*x_org_xj*y_org_yj^2+
					// c13*y_org_yj^3
					row.plus(index1_10+1, m * 1.0);//с1

					row.plus(index1_10+3, m * 2.0 * x_org_x1j);//с3
					row.plus(index1_10+4, m *       y_org_y1j);//с4
					
					row.plus(index1_10+6, m * 3.0 * x_org_x1j * x_org_x1j);//с6
					row.plus(index1_10+7, m * 2.0 * x_org_x1j * y_org_y1j);//с7
					row.plus(index1_10+8, m *       y_org_y1j * y_org_y1j);//с8

					row.plus(index1_10+10, m * 4.0 * x_org_x1j * x_org_x1j * x_org_x1j);//с10
					row.plus(index1_10+11, m * 3.0 * x_org_x1j * x_org_x1j * y_org_y1j);//с11
					row.plus(index1_10+12, m * 2.0 * x_org_x1j * y_org_y1j * y_org_y1j);//с12
					row.plus(index1_10+13, m *       y_org_y1j * y_org_y1j * y_org_y1j);//с13
				}
				break;
			case 1:
				{
					//(
					//2*c3*x_len+
					//c4*y_len+
					//6*c6*x_org_xj*x_len+
					//2*c7*x_org_xj*y_len+
					//2*c7*x_len*y_org_yj+
					//2*c8*y_org_yj*y_len
					//)*t+

					// (
					// 2*c3*x_len+
					// c4*y_len+

					// 6*c6*x_org_xj*x_len+
					// 2*c7*x_org_xj*y_len+
					// 2*c7*x_len*y_org_yj+
					// 2*c8*y_org_yj*y_len+

					// 12*c10*x_org_xj^2*x_len+
					// 6*c11*x_org_xj*x_len*y_org_yj+
					// 3*c11*x_org_xj^2*y_len+
					// 4*c12*x_org_xj*y_org_yj*y_len+
					// 2*c12*x_len*y_org_yj^2
					// 3*c13*y_org_yj^2*y_len+
					// )*t+

					row.plus(index1_10+3, m * 2.0 * x_len);//с3
					row.plus(index1_10+4, m *       y_len);//с4
					
					row.plus(index1_10+6, m * 6.0 * x_org_x1j * x_len);//с6
					row.plus(index1_10+7, m * 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len));//с7
					row.plus(index1_10+8, m * 2.0 * y_org_y1j * y_len);//с8

					row.plus(index1_10+10, m * 12.0 * x_org_x1j * x_org_x1j * x_len);//с10
					row.plus(index1_10+11, m * 
						( 6.0 * x_org_x1j * x_len * y_org_y1j 
						+ 3.0 * x_org_x1j * x_org_x1j * y_len));//с11
					row.plus(index1_10+12, m * 
						( 4.0 * x_org_x1j * y_org_y1j * y_len 
						+ 2.0 * x_len * y_org_y1j * y_org_y1j));//с12
					row.plus(index1_10+13, m * 3.0 * y_org_y1j * y_org_y1j * y_len);//с13
				}
				break;
			case 2:
				{
					//(3*c6*x_len^2 + 2*c7*x_len*y_len + c8*y_len^2)*t^2+

					// (
					// 3*c6*x_len^2+
					// 2*c7*x_len*y_len+
					// c8*y_len^2+

					// 12*c10*x_org_xj*x_len^2
					// 6*c11*x_org_xj*x_len*y_len+
					// 3*c11*x_len^2*y_org_yj+
					// 4*c12*x_len*y_org_yj*y_len+
					// 2*c12*x_org_xj*y_len^2+
					// 3*c13*y_org_yj*y_len^2+
					// )*t^2+

					row.plus(index1_10+6, m * 3.0 * x_len * x_len);//с6
					row.plus(index1_10+7, m * 2.0 * x_len * y_len);//с7
					row.plus(index1_10+8, m *       y_len * y_len);//с8

					row.plus(index1_10+10, m * 12.0 * x_org_x1j * x_len * x_len);//с10
					row.plus(index1_10+11, m * 
						( 6.0 * x_org_x1j * x_len * y_len 
						+ 3.0 * x_len * x_len * y_org_y1j));//с11
					row.plus(index1_10+12, m * 
						( 4.0 * x_len * y_org_y1j * y_len 
						+ 2.0 * x_org_x1j * y_len * y_len));//с12
					row.plus(index1_10+13, m * 3.0 * y_org_y1j * y_len * y_len);//с13
				}
				break;
			case 3:
				{
					// (
					// 4*c10*x_len^3+
					// 3*c11*x_len^2*y_len+
					// 2*c12*x_len*y_len^2
					// c13*y_len^3+
					// )*t^3+

					row.plus(index1_10+10, m * 4.0 * x_len * x_len * x_len);//с10
					row.plus(index1_10+11, m * 3.0 * x_len * x_len * y_len);//с11
					row.plus(index1_10+12, m * 2.0 * x_len * y_len * y_len);//с12
					row.plus(index1_10+13, m *       y_len * y_len * y_len);//с13
				}
				break;
			}
		}
		break;
	}
}
void FillRow_diff_y(sparse_row & row, // заполняемая строка
					  int order, // порялок полигона
					  int pw_t, // степень при t
					  size_t index1_10, // начальный индекс
					  double x_org_x1j,
					  double y_org_y1j,
					  double x_len,
					  double y_len,
					  double m) // множитель знака и наклона
{
	switch (order)
	{
	case 1:
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************

			// diff_y(t) := 
			// c2+
			// c4*(x_org-xj+(x_dest-x_org)*t)+
			// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
			// c7*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

			// = 

			//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
			//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
			//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2
					row.plus(index1_10+2, m * 1.0);//с2
				}
				break;
			}
		}
		break;
	case 2:
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************

			// diff_y(t) := 
			// c2+
			// c4*(x_org-xj+(x_dest-x_org)*t)+
			// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
			// c7*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

			// = 

			//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
			//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
			//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					row.plus(index1_10+2, m * 1.0);//с2

					row.plus(index1_10+4, m *       x_org_x1j);//с4
					row.plus(index1_10+5, m * 2.0 * y_org_y1j);//с5
				}
				break;
			case 1:
				{
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					row.plus(index1_10+4, m *       x_len);//с4
					row.plus(index1_10+5, m * 2.0 * y_len);//с5
				}
				break;
			}
		}
		break;
	case 3:
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************

			// diff_y(t) := 
			// c2+
			// c4*(x_org-xj+(x_dest-x_org)*t)+
			// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
			// c7*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

			// = 

			//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
			//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
			//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					row.plus(index1_10+2, m * 1.0);//с2

					row.plus(index1_10+4, m *       x_org_x1j);//с4
					row.plus(index1_10+5, m * 2.0 * y_org_y1j);//с5
					
					row.plus(index1_10+7, m *       x_org_x1j * x_org_x1j);//с7
					row.plus(index1_10+8, m * 2.0 * x_org_x1j * y_org_y1j);//с8
					row.plus(index1_10+9, m * 3.0 * y_org_y1j * y_org_y1j);//с9
				}
				break;
			case 1:
				{
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					row.plus(index1_10+4, m *       x_len);//с4
					row.plus(index1_10+5, m * 2.0 * y_len);//с5
					
					row.plus(index1_10+7, m * 2.0 * x_org_x1j * x_len);//с7
					row.plus(index1_10+8, m * 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len) );//с8
					row.plus(index1_10+9, m * 6.0 * y_org_y1j * y_len);//с9
				}
				break;

			case 2:
				{
					//(c7*x_len^2 + 2*c8*x_len*y_len + 3*c9*y_len^2)*t^2+

					row.plus(index1_10+7, m *       x_len * x_len);//с7
					row.plus(index1_10+8, m * 2.0 * x_len * y_len);//с8
					row.plus(index1_10+9, m * 3.0 * y_len * y_len);//с9
				}
				break;
			}
		}
		break;
	case 4:
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// добавляем строку в уравнение
			//*****************************************************************************************
			//*****************************************************************************************

			// diff_y(t) := 
			// c2+
			// c4*(x_org-xj+(x_dest-x_org)*t)+
			// 2*c5*(y_org-yj+(y_dest-y_org)*t)+
			// c7*(x_org-xj+(x_dest-x_org)*t)^2+
			// 2*c8*(x_org-xj+(x_dest-x_org)*t)*(y_org-yj+(y_dest-y_org)*t)+
			// 3*c9*(y_org-yj+(y_dest-y_org)*t)^2

			// = 

			//(c7*x_len^2+2*c8*x_len*y_len+3*c9*y_len^2)*t^2+
			//(c4*x_len+2*c7*x_org_xj*x_len+2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+6*c9*y_org_yj*y_len)*t+
			//c2+c4*x_org_xj+2*c5*y_org_yj+2*c8*x_org_xj*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2

			// (4*c14*y_len^3+2*c12*x_len^2*y_len+c11*x_len^3+3*c13*x_len*y_len^2)*t^3+
			// (c7*x_len^2+2*c12*x_len^2*y_org_yj+3*c11*x_org_xj*x_len^2+3*c9*y_len^2+6*c13*x_len*y_org_yj*y_len+12*c14*y_org_yj*y_len^2+3*c13*x_org_xj*y_len^2+2*c8*x_len*y_len+4*c12*x_org_xj*x_len*y_len)*t^2+
			// (2*c8*x_org_xj*y_len+2*c8*x_len*y_org_yj+2*c5*y_len+2*c7*x_org_xj*x_len+12*c14*y_org_yj^2*y_len+3*c11*x_org_xj^2*x_len+2*c12*x_org_xj^2*y_len+6*c9*y_org_yj*y_len+4*c12*x_org_xj*x_len*y_org_yj+c4*x_len+3*c13*x_len*y_org_yj^2+6*c13*x_org_xj*y_org_yj*y_len)*t+
			// c2+c11*x_org_xj^3+c4*x_org_xj+2*c5*y_org_yj+c7*x_org_xj^2+3*c9*y_org_yj^2+2*c8*x_org_xj*y_org_yj+4*c14*y_org_yj^3+2*c12*x_org_xj^2*y_org_yj+3*c13*x_org_xj*y_org_yj^2

			switch(pw_t)
			{
			case 0:
				{
					//c2 + c4*x_org_xj + 2*c5*y_org_yj + 2*c8*x_org_xj*y_org_yj + c7*x_org_xj^2 + 3*c9*y_org_yj^2

					// c2+

					// c4*x_org_xj+
					// 2*c5*y_org_yj+

					// c7*x_org_xj^2+
					// 2*c8*x_org_xj*y_org_yj+
					// 3*c9*y_org_yj^2+

					// c11*x_org_xj^3+
					// 2*c12*x_org_xj^2*y_org_yj+
					// 3*c13*x_org_xj*y_org_yj^2
					// 4*c14*y_org_yj^3+

					row.plus(index1_10+2, m * 1.0);//с2

					row.plus(index1_10+4, m *       x_org_x1j);//с4
					row.plus(index1_10+5, m * 2.0 * y_org_y1j);//с5
					
					row.plus(index1_10+7, m *       x_org_x1j * x_org_x1j);//с7
					row.plus(index1_10+8, m * 2.0 * x_org_x1j * y_org_y1j);//с8
					row.plus(index1_10+9, m * 3.0 * y_org_y1j * y_org_y1j);//с9

					row.plus(index1_10+11, m *       x_org_x1j * x_org_x1j * x_org_x1j);//с11
					row.plus(index1_10+12, m * 2.0 * x_org_x1j * x_org_x1j * y_org_y1j);//с12
					row.plus(index1_10+13, m * 3.0 * x_org_x1j * y_org_y1j * y_org_y1j);//с13
					row.plus(index1_10+14, m * 4.0 * y_org_y1j * y_org_y1j * y_org_y1j);//с14
				}
				break;
			case 1:
				{
					//(
					//c4*x_len+
					//2*c5*y_len+
					//2*c7*x_org_xj*x_len+
					//2*c8*x_org_xj*y_len+
					//2*c8*x_len*y_org_yj+
					//6*c9*y_org_yj*y_len
					//)*t+

					// (
					// c4*x_len+
					// 2*c5*y_len+

					// 2*c7*x_org_xj*x_len+
					// 2*c8*x_org_xj*y_len+
					// 2*c8*x_len*y_org_yj+
					// 6*c9*y_org_yj*y_len+

					// 3*c11*x_org_xj^2*x_len+
					// 2*c12*x_org_xj^2*y_len+
					// 4*c12*x_org_xj*x_len*y_org_yj+
					// 3*c13*x_len*y_org_yj^2+
					// 6*c13*x_org_xj*y_org_yj*y_len
					// 12*c14*y_org_yj^2*y_len+
					// )*t+
					
					row.plus(index1_10+4, m *       x_len);//с4
					row.plus(index1_10+5, m * 2.0 * y_len);//с5
					
					row.plus(index1_10+7, m * 2.0 * x_org_x1j * x_len);//с7
					row.plus(index1_10+8, m * 2.0 * (x_org_x1j * y_len + y_org_y1j * x_len) );//с8
					row.plus(index1_10+9, m * 6.0 * y_org_y1j * y_len);//с9

					row.plus(index1_10+11, m * 
						3.0 * x_org_x1j * x_org_x1j * x_len);//с11
					row.plus(index1_10+12, m * 
						( 2.0 * x_org_x1j * x_org_x1j * y_len
						+ 4.0 * x_org_x1j * x_len * y_org_y1j)
						);//с12
					row.plus(index1_10+13, m * 
						( 3.0 * x_len * y_org_y1j * y_org_y1j
						+ 6.0 * x_org_x1j * y_org_y1j * y_len)
						);//с13
					row.plus(index1_10+14, m * 
						12.0 * y_org_y1j * y_org_y1j * y_len);//с14
				}
				break;
			case 2:
				{
					//(c7*x_len^2 + 2*c8*x_len*y_len + 3*c9*y_len^2)*t^2+

					// (
					// c7*x_len^2+
					// 2*c8*x_len*y_len+
					// 3*c9*y_len^2+

					// 3*c11*x_org_xj*x_len^2+
					// 2*c12*x_len^2*y_org_yj+
					// 4*c12*x_org_xj*x_len*y_len
					// 3*c13*x_org_xj*y_len^2+
					// 6*c13*x_len*y_org_yj*y_len+
					// 12*c14*y_org_yj*y_len^2+
					// )*t^2+

					row.plus(index1_10+7, m *       x_len * x_len);//с7
					row.plus(index1_10+8, m * 2.0 * x_len * y_len);//с8
					row.plus(index1_10+9, m * 3.0 * y_len * y_len);//с9

					row.plus(index1_10+11, m * 
						 3.0 * x_org_x1j * x_len * x_len);//с11
					row.plus(index1_10+12, m * 
						( 2.0 * x_len * x_len * y_org_y1j
						+ 4.0 * x_org_x1j * x_len * y_len)
						);//с12
					row.plus(index1_10+13, m * 
						( 3.0 * x_org_x1j * y_len * y_len
						+ 6.0 * x_len * y_org_y1j * y_len)
						);//с13
					row.plus(index1_10+14, m * 
						12.0 * y_org_y1j * y_len * y_len);//с14
				}
				break;
			case 3:
				{
					// (
					// c11*x_len^3+
					// 2*c12*x_len^2*y_len+
					// 3*c13*x_len*y_len^2
					// 4*c14*y_len^3+
					// )*t^3+

					row.plus(index1_10+11, m * 
						x_len * x_len * x_len);//с11
					row.plus(index1_10+12, m * 
						2.0 * x_len * x_len * y_len);//с12
					row.plus(index1_10+13, m * 
						3.0 * x_len * y_len * y_len);//с13
					row.plus(index1_10+14, m * 
						4.0 * y_len * y_len * y_len);//с14
				}
				break;
			}

		}
		break;
	}
}


bool AddRowsToEquation2_(int N_trias, int order_t, int order_c, 
						 size_t nk_t, size_t nk_c,
						vector<sparse_row> & M,	// формируемая матрица
					   size_t cols,
					  vector<double> & B,			// формируемый вектор правых частей
					  vector<double> & z,			// отметки высот
					  EdgeEx * ex,
					  vector<geometry2D::Point> &base_points,
					  finite_element_par & fep)
{
	PolygonEx * p1 = ex->LeftPolygon();
	PolygonEx * p2 = ex->RightPolygon();
	if(p1 && p2)
	{
		size_t index1 = p1->index < p2->index ? p1->index : p2->index;
		size_t index2 = p1->index < p2->index ? p2->index : p1->index;

		//size_t index1_10 = index1*nk;
		//size_t index2_10 = index2*nk;

		size_t index1_10 = (int)index1 < N_trias ? index1*nk_t : N_trias*nk_t + (index1-N_trias)*nk_c;
		size_t index2_10 = (int)index2 < N_trias ? index2*nk_t : N_trias*nk_t + (index2-N_trias)*nk_c;

		printf("AddRowsToEquation2 %u %u %u %u\n", index1, index2, index1_10, index2_10);

		size_t nk1 = (int)index1 < N_trias ? nk_t : nk_c;
		int order1 = (int)index1 < N_trias ? order_t : order_c;

		size_t nk2 = (int)index2 < N_trias ? nk_t : nk_c;
		int order2 = (int)index2 < N_trias ? order_t : order_c;

		if (index1_10+nk1-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index1_10+nk1-1 (%u) >= cols (%u)", index1_10+nk1-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx _", MB_OK);
			return false;
		}		
		if (index2_10+nk2-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index2_10+nk2-1 (%u) >= cols (%u)", index2_10+nk2-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx _", MB_OK);
			return false;
		}

		double x_org = ex->org.x;
		double y_org = ex->org.y;

		double x_dest = ex->dest.x;
		double y_dest = ex->dest.y;

		double x_len = x_dest - x_org;
		double y_len = y_dest - y_org;

		// базовые точки для обоих полигонов
		geometry2D::Point pt1j = base_points[index1];
		geometry2D::Point pt2j = base_points[index2];

		double x_org_x1j = x_org - pt1j.x;
		double y_org_y1j = y_org - pt1j.y;

		double x_org_x2j = x_org - pt2j.x;
		double y_org_y2j = y_org - pt2j.y;

		sparse_row row;

		bool add_non_fault = fep.add_non_fault;
		bool add_first_der_n = fep.add_first_der_n;

		//наклон ребра
		bool add_first_der_x = true;
		bool add_first_der_y = true;

		if (fep.add_first_der_x_or_y)
		{
			//наклон ребра

			double fabs_slope = fabs(ex->slope());

			if (fabs_slope > 1.0)
			{
				add_first_der_x = true;
				add_first_der_y = false;
			}
			else
			{
				add_first_der_x = false;
				add_first_der_y = true;
			}
		}
		else
		{
			add_first_der_x = fep.add_first_der_x;
			add_first_der_y = fep.add_first_der_y;
		}

		EdgeEx ex_rot = *ex;
		ex_rot.rot();
		geometry2D::Point n = ex_rot.dest - ex_rot.org;
		double inv_nlen = 1.0 / n.length();
		n = inv_nlen * n;

		// n.x = dx/dn
		// n.y = dy/dn

		// df/dn = (df/dx)*(dx/dn) + (df/dy)*(dy/dn)

		int max_order = max(order1,order2);
		if (add_non_fault)
		{
#if SPARSE_ROW_EX
			row._order = 0;
#endif
			for (int pw_t = 0; pw_t <= max_order; pw_t++)
			{
				row.clear();
				FillRow_NonFault(row, order1, pw_t, 
						index1_10, x_org_x1j, y_org_y1j, x_len, y_len, fep.alpha_non_fault);
				FillRow_NonFault(row, order2, pw_t, 
						index2_10, x_org_x2j, y_org_y2j, x_len, y_len, -fep.alpha_non_fault);
				M.push_back(row);	B.push_back(0.0);
			}
		}

		

		if(add_first_der_n)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			for (int pw_t = 0; pw_t < max_order; pw_t++)
			{
				row.clear();
				FillRow_diff_x(row, order1, pw_t, 
						index1_10, x_org_x1j, y_org_y1j, x_len, y_len, n.x*fep.alpha_der_n);
				FillRow_diff_y(row, order1, pw_t, 
						index1_10, x_org_x1j, y_org_y1j, x_len, y_len, n.y*fep.alpha_der_n);
				FillRow_diff_x(row, order2, pw_t, 
						index2_10, x_org_x2j, y_org_y2j, x_len, y_len, -n.x*fep.alpha_der_n);
				FillRow_diff_y(row, order2, pw_t, 
						index2_10, x_org_x2j, y_org_y2j, x_len, y_len, -n.y*fep.alpha_der_n);
				M.push_back(row);	B.push_back(0.0);
			}
		}
		if(add_first_der_x)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			for (int pw_t = 0; pw_t < max_order; pw_t++)
			{
				row.clear();
				FillRow_diff_x(row, order1, pw_t, 
						index1_10, x_org_x1j, y_org_y1j, x_len, y_len, fep.alpha_der_xy);
				FillRow_diff_x(row, order2, pw_t, 
						index2_10, x_org_x2j, y_org_y2j, x_len, y_len, -fep.alpha_der_xy);
				M.push_back(row);	B.push_back(0.0);
			}
		}
		if(add_first_der_y)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			for (int pw_t = 0; pw_t < max_order; pw_t++)
			{
				row.clear();
				FillRow_diff_y(row, order1, pw_t, 
						index1_10, x_org_x1j, y_org_y1j, x_len, y_len, fep.alpha_der_xy);
				FillRow_diff_y(row, order2, pw_t, 
						index2_10, x_org_x2j, y_org_y2j, x_len, y_len, -fep.alpha_der_xy);
				M.push_back(row);	B.push_back(0.0);
			}
		}
		return true;
	}
	else
	{
		char str[255];
#pragma warning( disable : 4313 )
		sprintf(str, "!AddRowsToEquation2 ! (p1 && p2)\n p1 = %x p2 = %x\n", p1, p2);
#pragma warning( default : 4313 )
		printf (str);
		//MessageBox(0, str, "AddRowsToEquation2", 0);
		return false;
	}
}

bool AddBoundaryConditionRowsToEquation2_(int N_trias, int order_t, int order_c, 
						 size_t nk_t, size_t nk_c,
						vector<sparse_row> & M,	// формируемая матрица
					   size_t cols,
					  vector<double> & B,			// формируемый вектор правых частей
					  vector<double> & z,			// отметки высот
					  vector<double> & sol,			// решение содержащее коэффициенты линейной интерполяции
					  EdgeEx * ex,
					  vector<geometry2D::Point> &base_points,
					  finite_element_par & fep)
{
	PolygonEx * p1 = ex->LeftPolygon();
	PolygonEx * p2 = ex->RightPolygon();
	if( (!p1 && p2) || (p1 && !p2) )
	{
		PolygonEx * p = NULL;
		if (p1) p = p1;
		if (p2) p = p2;

		size_t index = p->index;

		size_t index_10 = (int)index < N_trias ? index*nk_t : N_trias*nk_t + (index-N_trias)*nk_c;

		printf("AddRowsToEquation2 %u %u\n", index, index_10);

		size_t nk = (int)index < N_trias ? nk_t : nk_c;
		int order = (int)index < N_trias ? order_t : order_c;

		if (index_10+nk-1 >= cols)
		{
			char err[1024];
			sprintf(err, "index_10+nk-1 (%u) >= cols (%u)", index_10+nk-1, cols);
			MessageBox(0, err, "AddRowsToEquation EdgeEx _", MB_OK);
			return false;
		}		


		double x_org = ex->org.x;
		double y_org = ex->org.y;

		double x_dest = ex->dest.x;
		double y_dest = ex->dest.y;

		double x_len = x_dest - x_org;
		double y_len = y_dest - y_org;

		// базовые точки для обоих полигонов
		geometry2D::Point ptj = base_points[index];

		double x_org_xj = x_org - ptj.x;
		double y_org_yj = y_org - ptj.y;

		sparse_row row;

		bool add_non_fault = fep.add_non_fault;
		bool add_first_der_n = fep.add_first_der_n;

		//наклон ребра
		bool add_first_der_x = true;
		bool add_first_der_y = true;

		if (fep.add_first_der_x_or_y)
		{
			//наклон ребра

			double fabs_slope = fabs(ex->slope());

			if (fabs_slope > 1.0)
			{
				add_first_der_x = true;
				add_first_der_y = false;
			}
			else
			{
				add_first_der_x = false;
				add_first_der_y = true;
			}
		}
		else
		{
			add_first_der_x = fep.add_first_der_x;
			add_first_der_y = fep.add_first_der_y;
		}

		EdgeEx ex_rot = *ex;
		ex_rot.rot();
		geometry2D::Point n = ex_rot.dest - ex_rot.org;
		double inv_nlen = 1.0 / n.length();
		n = inv_nlen * n;

		// n.x = dx/dn
		// n.y = dy/dn

		// df/dn = (df/dx)*(dx/dn) + (df/dy)*(dy/dn)
		// Коэффициенты при t для линейного решения
		double c0 = sol[index_10 + 0];
		double c1 = sol[index_10 + 1];
		double c2 = sol[index_10 + 2];
		double b;
		int pw_t;

		//int max_order = max(order1,order2);
		if (add_non_fault)
		{
#if SPARSE_ROW_EX
			row._order = 0;
#endif
			// t^0
			pw_t = 0;
			b = c0 + c1*x_org_xj + c2*y_org_yj;
			row.clear();
			FillRow_NonFault(row, order, pw_t, 
					index_10, x_org_xj, y_org_yj, x_len, y_len, fep.alpha_non_fault);
			M.push_back(row);	B.push_back(b*fep.alpha_non_fault);
			// t^1
			pw_t = 1;
			b = c1*x_len + c2*y_len;
			row.clear();
			FillRow_NonFault(row, order, pw_t, 
					index_10, x_org_xj, y_org_yj, x_len, y_len, fep.alpha_non_fault);
			M.push_back(row);	B.push_back(b*fep.alpha_non_fault);

			// приравниваем нулю коэффициенты при высших степенях t : t^2, t^3,..
			for (pw_t = 2; pw_t <= order; pw_t++)
			{
				row.clear();
				FillRow_NonFault(row, order, pw_t, 
						index_10, x_org_xj, y_org_yj, x_len, y_len, fep.alpha_non_fault);
				M.push_back(row);	B.push_back(0.0);
			}
		}

		if(add_first_der_n)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// t^0
			pw_t = 0;
			b = n.x*c1 + n.y*c2;
			row.clear();
			FillRow_diff_x(row, order, pw_t, 
					index_10, x_org_xj, y_org_yj, x_len, y_len, n.x*fep.alpha_der_n);
			FillRow_diff_y(row, order, pw_t, 
					index_10, x_org_xj, y_org_yj, x_len, y_len, n.y*fep.alpha_der_n);
			M.push_back(row);	B.push_back(b*fep.alpha_der_n);
			for (pw_t = 1; pw_t < order; pw_t++)
			{
				row.clear();
				FillRow_diff_x(row, order, pw_t, 
						index_10, x_org_xj, y_org_yj, x_len, y_len, n.x*fep.alpha_der_n);
				FillRow_diff_y(row, order, pw_t, 
						index_10, x_org_xj, y_org_yj, x_len, y_len, n.y*fep.alpha_der_n);
				M.push_back(row);	B.push_back(0.0);
			}
		}
		if(add_first_der_x)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// t^0
			pw_t = 0;
			b = c1;
			row.clear();
			FillRow_diff_x(row, order, pw_t, 
					index_10, x_org_xj, y_org_yj, x_len, y_len, 1.0*fep.alpha_der_xy);
			M.push_back(row);	B.push_back(b*fep.alpha_der_xy);
			for (pw_t = 1; pw_t < order; pw_t++)
			{
				row.clear();
				FillRow_diff_x(row, order, pw_t, 
						index_10, x_org_xj, y_org_yj, x_len, y_len, 1.0*fep.alpha_der_xy);
				M.push_back(row);	B.push_back(0.0);
			}
		}
		if(add_first_der_y)
		{
#if SPARSE_ROW_EX
			row._order = 1;
#endif
			// t^0
			pw_t = 0;
			b = c2;
			row.clear();
			FillRow_diff_y(row, order, pw_t, 
					index_10, x_org_xj, y_org_yj, x_len, y_len, 1.0*fep.alpha_der_xy);
			M.push_back(row);	B.push_back(b*fep.alpha_der_xy);
			for (pw_t = 1; pw_t < order; pw_t++)
			{
				row.clear();
				FillRow_diff_y(row, order, pw_t, 
						index_10, x_org_xj, y_org_yj, x_len, y_len, 1.0*fep.alpha_der_xy);
				M.push_back(row);	B.push_back(0.0);
			}
		}
		return true;
	}

	return false;
}

void AppendToList(EdgeEx * ex, void * _list)
{
	List<EdgeEx*> * lst = (List<EdgeEx*> *)_list;
	if (ex->LeftPolygon() || ex->RightPolygon())
		lst->append(ex);
}

struct min_col_range
{
	int i1, i2;
	size_t size;
};

#define FILL_GRID_TEST 0

/*bool fill_grid_9(Grid * grid, 
			   std::vector<geometry2D::Point>& vs, 
			   vector<double>& x, vector<double>& y, vector<double>& z,
			   double& min_z, double& max_z)
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

    // Фильтруем полигоны от "плохих" краевых треугольников		
	if (false)
		FilteringPolygonesEx1(trias, out_edges);
	else
		FilteringPolygonesEx2(trias, out_edges);

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

    // Получаем замкнутый контур внешней границы
	List<EdgeEx*> * contour = GetContourOfPolygonesEx2(trias);

	// Из каждой вершины внешней границы проводим вовне биссектрисы
	List<EdgeEx*> * biss = MakeBissectrissToContour(contour, GetMaxLenOfEdges(contour));
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

	biss = CorrectBissectriss3(biss);

	// Вокруг контура внешней границы, базируясь на внешних биссектриссах формируем массив экстраполяционных полигонов
	vector<Point> * poly_contour_base_points = new vector<Point>; // список базовых точек для экстраполяционных полигонов
	List<PolygonEx*> * poly_contour = GetContourOfExtraPolygones(contour, biss, poly_contour_base_points, 0);


	// Итак, мы имеем N треугольников экстраполяции
	int N = trias->length();
printf("N = trias->length() %d\n", N );
	// построенных на n точках
	// int n = x.size();
	// А также L полигонов экстраполяционных
	int L = poly_contour->length();
printf("L = poly_contour->length() %d\n", L );

	// каждый треугольник мы будем аппроксимировать уравнением (1):
	// f(x,y):= zj + c1*(x-xj)   + c2*(y-yj)          + 
	//				 c3*(x-xj)^2 + c4*(x-xj)*(y-yj)   + c5*(y-yj)^2        + 
	//				 c6*(x-xj)^3 + c7*(x-xj)^2*(y-yj) + c8*(x-xj)*(y-yj)^2 + c9*(y-yj)^3;

	// diff(f(x,y),x)   = c1+2*c3*(x-xj)+c4*(y-yj)+3*c6*(x-xj)^2+2*c7*(x-xj)*(y-yj)+c8*(y-yj)^2
	// diff(f(x,y),y)   = c2+c4*(x-xj)+2*c5*(y-yj)+c7*(x-xj)^2+2*c8*(x-xj)*(y-yj)+3*c9*(y-yj)^2
	// diff(f(x,y),x,x) = 2*c3+6*c6*(x-xj)+2*c7*(y-yj)
	// diff(f(x,y),y,y) = 2*c5+2*c8*(x-xj)+6*c9*(y-yj)
	// diff(f(x,y),x,y) = c4+2*c7*(x-xj)+2*c8*(y-yj)

	// Итак у нас 9 * N + 9 * L неизвестных коэффициентов
	int cols;
	int order = 2;
	switch(order)
	{
		case 2:
            cols = 5 * N + 5 * L;
			break;
		case 3:
            cols = 9 * N + 9 * L;
			break;
	}
	vector<double> sol(cols, 0.0); // вектор решения

	List<PolygonEx*> poly;
	// список базовых точек для триангуляционных треугольников
	vector<Point> base_points;
	size_t index = 0;
	for (trias->first(); !trias->isHead(); trias->next(),index++)
	{
		trias->val()->index = index;
		base_points.push_back(trias->val()->point());
		poly.append(trias->val());
#if 0
		// инициализируем линейные коэффициенты
		// линейная интерполяция - первое приближение
		//sol[index*9+0];//c1
		//sol[index*9+1];//c2

			
		Point ptj = base_points[index];
		size_t index_9 = index*9;

		PolygonEx * p = trias->val();

			
		vector<sparse_row> m; 
		// и вектор правых частей 
		vector<double> b;


		for (int i = 0; i < p->size(); i++)
		{
			p->advance(CLOCKWISE);
			Point pt = p->point();

			if (pt != ptj && pt.index > -1 && pt.index < z.size())
			{			
				// добавляем строку в уравнение
				
				sparse_row row; 
				row.clear();

				row.put(0, pt.x - ptj.x);//с1
				row.put(1, pt.y - ptj.y);//с2

				m.push_back(row);
				b.push_back(z[pt.index] - z[ptj.index]);
				
			}
		}


		vector<double> x;
		if (lesgausssolve_find_max(m, m.size(), 2, b, x, 0.0))
		{
			sol[index_9+0] = x[0];//c1
			sol[index_9+1] = x[1];//c2
		}
		else
		{
			printf("system was not solved\n");
		}
#endif
	}
	vector<Point>::iterator itp;
	for (contour->first(), poly_contour->first(), itp = poly_contour_base_points->begin(); 
		!contour->isHead() && !poly_contour->isHead() && itp != poly_contour_base_points->end(); 
		contour->next(), poly_contour->next(), itp++, index++)
	{
		poly_contour->val()->index = index;
		base_points.push_back((*itp));
		poly.append(poly_contour->val());
#if 0
		size_t index_9 = index*9;

		EdgeEx * ex = contour->val();
		// указатель на полигон контурный
		// PolygonEx * pc = ex->LeftPolygon();
		// указазатель на соответствующий внутренний треугольник
		PolygonEx * tr = ex->RightPolygon();
		// ищем в треугольнике противоположную точку
		Point tr_pt;
		for (int i = 0; i < tr->size(); i++)
		{
			tr->advance(CLOCKWISE);
			Point pt = tr->point();
			if (pt != ex->org && pt != ex->dest)
			{	
				tr_pt = pt;				
			}
		}

		if (tr_pt.index > -1 && tr_pt.index < z.size()
			&&
			ex->dest.index > -1 && ex->dest.index < z.size())
		{						
			vector<sparse_row> m; 
			// и вектор правых частей 
			vector<double> b;
			// добавляем строку в уравнение
			sparse_row row; 

			// базовая точка == ex->org

			row.clear();        
			row.put(0, tr_pt.x - (*itp).x);//с1
			row.put(1, tr_pt.y - (*itp).y);//с2		
			m.push_back(row);b.push_back(z[tr_pt.index] - z[(*itp).index]);

			// ex->dest

			row.clear();        
			row.put(0, ex->dest.x - (*itp).x);//с1
			row.put(1, ex->dest.y - (*itp).y);//с2		
			m.push_back(row);b.push_back(z[ex->dest.index] - z[(*itp).index]);
			
			vector<double> x;
			if (lesgausssolve_find_max(m, m.size(), 2, b, x, 0.0))
			{
				sol[index_9+0] = x[0];//c1
				sol[index_9+1] = x[1];//c2
			}
			else
			{
				printf("system was not solved\n");
			}
		}
#endif
	}

#if 1
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
		AddRowsToEquation(order, M, cols, B, z, p, base_points);
	}

	printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));

	// Для каждого экстраполяционного треугольника подставим координаты одной дополнительной точки
	for (poly_contour->first(); 
		!poly_contour->isHead(); 
		poly_contour->next())
	{
		PolygonEx * p = poly_contour->val();
		AddRowsToEquation(order, M, cols, B, z, p, base_points);
	}

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
	EdgeEx * ex_;
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
	//int qqqq = 0;
	for( out_edges_->first(); !out_edges_->isHead(); out_edges_->next())
	{
		EdgeEx* ex = out_edges_->val();
		AddRowsToEquation2(order, M, cols, B, z, ex, base_points);
	}

	printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));

	// перебираем все рёбра контура
	for( contour->first(); !contour->isHead(); contour->next())
	{
		EdgeEx* ex = contour->val();
		AddRowsToEquation2(order, M, cols, B, z, ex, base_points);
	}
	printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), GetRealColsNumber(M,cols));

	// перебираем все биссектриссы
	for( biss->first(); !biss->isHead(); biss->next())
	{
		EdgeEx* ex = biss->val();
		AddRowsToEquation2(order, M, cols, B, z, ex, base_points);
	}

	size_t real_cols_number = GetRealColsNumber(M, cols);
	printf("cols = %d, rows = %u, real_cols_number = %u\n", cols, M.size(), real_cols_number);
	
	if (real_cols_number < cols)
	{
		char err[2048];
		sprintf(err, "real_cols_number %u < cols %u", real_cols_number, cols);
		MessageBox(0, err, "fill_grid", MB_OK);
	if (!SLAU (M, cols, B, sol)) return false;
		return false;
	}
MessageBox(0,"","",0);

	//Tichonov(M, cols, B, x, true);
	if (!SLAU5(M, cols, B, sol)){}
	//if (!SLAU (M, cols, B, sol)) return false;

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
	//SLAU2(M, cols, B, sol);
	///SLAU_block(M, cols, 9, B, sol);
#if 0
	return;
	printf("pre find mincol\n");

	for (size_t i = 0; i < M.size(); i++)
	{
		M[i].FindMinCol();
		M[i].FindMaxCol();
	}
	printf("pre sort\n");

	std::sort(M.begin(), M.end(), sparse_row_greater);
	printf("post sort\n");
	
	vector<min_col_range> mc_range(cols);
	{	
		size_t i = 0;
		for (int j = 0; j < cols; j++)
		{
			while (i < M.size())
			{
				if (M[i].min_col > j)
				{
					break;
				}
				else
					if (M[i].min_col < j)
					{
					}
					else
					{
					}
			}
		}
	}

	//for (size_t i = 0; i < M.size(); i++)
	//{
	//	printf("i = %d\tM[i].min_col = %u\t, M[i].max_col = %u\n", i, M[i].min_col, M[i].max_col);
	//}

	char dat_file[1024];
	TCHAR filter[] =   
		TEXT("Dat (*.dat)\0*.dat\0")
		TEXT("All Files (*.*)\0*.*\0");
	sprintf(dat_file, "MatrixMinMaxCol");
	DWORD nFilterIndex = 0;
	if (SaveFileDlg(0, dat_file, filter, nFilterIndex) == S_OK)
	{
		SaveMatrixMinMaxCol(M, dat_file);
	}

	vector<sparse_row> m(cols); 
	vector<double> b(cols); 


	int i = M.size()-1;
	for (int j = cols-1; j >= 0; j--)
	{
		bool set = false;
		printf("j=%d\t",j);
		while ( i >= 0 )
		{
			if (M[i].min_col == j)
			//if (M[i].min_col <= j)
			{
				printf("i=%d\tM[i].min_col = %u\n",i, M[i].min_col);
				m[j] = M[i];b[j] = B[i];i--;set = true;
				break;
			}
			else
			if (M[i].min_col < j)
			{
				if (M[i][j] != 0.0)
				{
					printf("i=%d\tM[i].min_col = %u\n",i, M[i].min_col);
					m[j] = M[i];b[j] = B[i];i--;set = true;
					break;
				}
				else
					i--;
			}
			else
			{
				printf("i=%d\tM[i].min_col %u > j %d\n",i, M[i].min_col, j);
				i--;
			}
		}
	}

	printf("cols = %d, rows = %u\n", cols, m.size());
	printf("pre solve\n");

	double epsilon =0.00000000001;
//if (!lesgausssolve_find_max(M, M.size(), cols, B, x, epsilon))
//		printf("system was not solved\n");

//	if (!lesgausssolve(M, cols + 10 < M.size() ? cols + 10 : M.size(), cols, B, x, epsilon))
//		printf("system was not solved\n");
	if (!lesgausssolve_find_max(m, m.size(), cols, b, x, epsilon))
		printf("system was not solved\n");

return;
#endif
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
					z_value = GetValue(order, sol, cols, z, a, p, base_points);


					if (max_z < z_value) max_z = z_value;
					if (min_z > z_value) min_z = z_value;
				}
				else
					z_value = BLANK_VALUE;

				// полученное значение z_value записываем в грид
				grid->gridSection.z[jj][ii] = z_value;
			}
		}
		return true;
	}
	return false;
}
*/
struct point_polygon
{
	geometry2D::Point	   a;
	geometry2D::PolygonEx* p;
};

int getTriangulationContour(vector<double>& x, vector<double>& y, 
							int ftf, 
							bool use_biss, double len_biss, 
							Line3D * outline, CPoint3 * base_point )
{

	size_t len = x.size();
	
	if ( len != y.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d) and y(%d) must be equial",
			len, y.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;

	std::vector<geometry2D::Point> vs(len);

	for (size_t i = 0; i < len; i++)
	{
		vs[i].x = x[i];
		vs[i].y = y[i];
		vs[i].index = (int)i;
	}

	// вычисляем триангуляцию Делоне
	Dictionary<EdgeEx*> * out_edges = new Dictionary<EdgeEx*>(edgeCmpEx);
	List<PolygonEx*> * trias = delaunayTriangulateEx(vs, out_edges);

#if 0

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
#endif
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



    // Получаем замкнутый контур внешней границы
	List<EdgeEx*> * contour = GetContourOfPolygonesEx2(trias);

	if (!use_biss)
	{
		for (contour->first(); 
			!contour->isHead(); 
			contour->next())
		{
			EdgeEx * ex = contour->val();
			if (ex)
			{
				if (outline)
					outline->PushBack(CPoint3(ex->org.x, ex->org.y, 0.0, true));
			}
		}
	}
	else
	{
		// Из каждой вершины внешней границы проводим вовне биссектрисы		
		List<EdgeEx*> * biss = MakeBissectrissToContour(contour, len_biss);

		// Вокруг контура внешней границы, базируясь на внешних биссектриссах формируем 
		// новый контур внешней границы
		for ( biss->first(); 
			!biss->isHead(); 
			biss->next() )
		{
			EdgeEx * b = biss->val();
			if (b)
			{
				if (outline)
					outline->PushBack(CPoint3(b->dest.x, b->dest.y, 0.0, true));
			}
		}
	}

	if (outline) 
		outline->Close();

	if (base_point)
	{
		geometry2D::Point pt_intersect;
		if (GetContourInsidePoint(trias, pt_intersect))
		{
			base_point->x = pt_intersect.x;
			base_point->y = pt_intersect.y;
			base_point->z = 0.0;

			base_point->bVisible = true;
			base_point->flag = 0;

			return 1;
		}
		else 
			return 0;
	}
	return 0;
}

#define USE_CONTOUR 0
#include "fill_grid.h"
#pragma warning (disable:4005)
#define USE_CONTOUR 1
#pragma warning (default:4005)
#include "fill_grid.h"

void FillDefaultParam(griddata_2_param &param)
{
	param.max_len = 8;
	param.dist_fun_number = 3;
	param.pw = 3.0;
	param.delta_phi = 45.0;
	param.add_pw = 0.5;

	//param.dist_fun_number = 4;
}
void FillDefaultParam(griddata_3_param &param)
{

		param.use_contour = true;
	// флаг отфильтровывания периферийных "плохих" треугольников в триангуляции Делоне
	// 0 - отфильтровывания не происходит
	// 1 - отфильтровывание по "щадящему" алгоритму
	// 2 - отфильтровывание по более жёсткому алгоритму
	// м.б. 3 - отфильтровывание по "разъедающему" алгоритму
	param.ftf = 0; // filtering of triangulation flag

	// порядок интерполяции:
	// внутренних треугольников
	param.order_t = 2;// ;
	// и контурных полигонов
	param.order_c = 2;// ;

	// регуляризационные коэффициенты alpha, с помощью которых 
	// мы будем стараться приближаться к линейной интерполяции

	// alpha с нулём воздействуют на коэффициенты интерполяции с нулевой степенью 
	//		(Этот коэффициент будет "придавливать" центральную точку полигона)
	// alpha с единицей воздействуют на коэффициенты интерполяции с первой степенью 
	//		(этот коэффициент будет "придавливать" периферию полигона)

	// эти коэффициенты относятся к внутренним треугольникам
	param.alpha_t0 = 0.1;// ;
	param.alpha_t1 = 1.0;//;	
	param.alpha_tn = 1.0;//;	


	// эти коэффициенты относятся к контурным полигонам
	param.alpha_c0 = 0.1;//;
	param.alpha_c1 = 1.0;//;
	param.alpha_cn = 1.0;//;

	// коэффициент задающий сглажтвание
	// если ноль, сглаживания не происходит
	// если положительный, происходит сглаживание по методу "скользящего среднего", тогда dij определяет размер окна
	// если отрицательный, тогда на стыках полигонов происходит усреднение интерполяционных значений для разных полигонов по отношению к текущей точке
	param.dij = 1;//1;
	//double row_weight;// = 1.0;
	
	param.fep.add_non_fault = true;
	param.fep.alpha_non_fault = 1.0;
	param.fep.add_first_der_n = true;
	param.fep.alpha_der_n = 0.1;
	param.fep.add_first_der_x_or_y = false;
	param.fep.add_first_der_x = false;
	param.fep.add_first_der_y = false;
	param.fep.alpha_der_xy = 0.1;
	

	param.fepbc.add_non_fault = true;
	param.fepbc.alpha_non_fault = 0.5;
	param.fepbc.add_first_der_n = false;
	param.fepbc.alpha_der_n = 0.1;
	param.fepbc.add_first_der_x_or_y = false;
	param.fepbc.add_first_der_x = false;
	param.fepbc.add_first_der_y = false;
	param.fepbc.alpha_der_xy = 0.1;								  

	param.slau_method = 0;//SLAU9
	//param.slau_method = 1;//SLAU_excl
	param.slau_method = 2;//Tihonov

    param.m_len_biss_type = griddata_3_param_len_biss_type_user_defined;
	param.len_biss = 1.0;

}

void FilterGridMinMax(vector<double>& z, Grid * grid, double part_of_range_low, double part_of_range_high)
{
	double maxz = -DBL_MAX;
	double minz = DBL_MAX;
	for (size_t i = 0; i < z.size(); i++)
	{
		if (maxz < z[i]) maxz = z[i];
		if (minz > z[i]) minz = z[i];
	}

	if (!grid) return;
	if (maxz == -DBL_MAX) return;
	if (minz == DBL_MAX) return;

	double range = maxz - minz;
	double high_border = maxz + range * part_of_range_high;
	double low_border  = minz - range * part_of_range_low;

	for (long ii = 0; ii < grid->gridSection.nCol; ii++)
	{
		for (long jj = 0; jj < grid->gridSection.nRow; jj++)
		{
			if (grid->gridSection.z[jj][ii] > high_border) grid->gridSection.z[jj][ii] = BLANK_VALUE;
			else 
			{
				if (grid->gridSection.z[jj][ii] < low_border) grid->gridSection.z[jj][ii] = BLANK_VALUE;
			}
		}
	}
}
void MultiplyCube(Grid4 * grid, const double m)
{
	if (!grid) return;

	for (long p = 0; p < grid->grid4Section.nPag; p++)
	{
		for (long c = 0; c < grid->grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid->grid4Section.nRow; r++)
			{
				if (grid->grid4Section.v[p][r][c] != BLANK_VALUE)
				{
					grid->grid4Section.v[p][r][c] = m * grid->grid4Section.v[p][r][c];
				}
			}
		}
	}
}

void FilterCubeMinMax(Grid4 * grid, double minv, double maxv)
{

	if (!grid) return;
	if (maxv == -DBL_MAX) return;
	if (minv == DBL_MAX) return;

	for (long p = 0; p < grid->grid4Section.nPag; p++)
	{
		for (long c = 0; c < grid->grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid->grid4Section.nRow; r++)
			{
				if (grid->grid4Section.v[p][r][c] > maxv) grid->grid4Section.v[p][r][c] = BLANK_VALUE;
				else 
				{
					if (grid->grid4Section.v[p][r][c] < minv) grid->grid4Section.v[p][r][c] = BLANK_VALUE;
				}
			}
		}
	}
}


void FilterGridMinMax(vector<double>& v, Grid4 * grid, double part_of_range_low, double part_of_range_high)
{
	double maxv = -DBL_MAX;
	double minv = DBL_MAX;
	for (size_t i = 0; i < v.size(); i++)
	{
		if (maxv < v[i]) maxv = v[i];
		if (minv > v[i]) minv = v[i];
	}

	if (!grid) return;
	if (maxv == -DBL_MAX) return;
	if (minv == DBL_MAX) return;

	double range = maxv - minv;
	double high_border = maxv + range * part_of_range_high;
	double low_border  = minv - range * part_of_range_low;

	for (long p = 0; p < grid->grid4Section.nPag; p++)
	{
		for (long c = 0; c < grid->grid4Section.nCol; c++)
		{
			for (long r = 0; r < grid->grid4Section.nRow; r++)
			{
				if (grid->grid4Section.v[p][r][c] > high_border) grid->grid4Section.v[p][r][c] = BLANK_VALUE;
				else 
				{
					if (grid->grid4Section.v[p][r][c] < low_border) grid->grid4Section.v[p][r][c] = BLANK_VALUE;
				}
			}
		}
	}
}

int griddata_3(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void * _param, bool to_allocate)

{					
	griddata_3_param * param = reinterpret_cast<griddata_3_param *>(_param);
	// тут осуществляем триангуляционный алгоритм

	size_t len = x.size();
	
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;

	std::vector<geometry2D::Point> vs(len);

	for (size_t i = 0; i < len; i++)
	{
		vs[i].x = x[i];
		vs[i].y = y[i];
		vs[i].index = (int)i;
	}

	if (grid)
	{
		//long m = (*xi).Length();
		//long n = (*yi).Length();
		//long m = grid->gridSection.nCol;
		//long n = grid->gridSection.nRow;

		//long m_1 = grid->gridSection.nCol-1;
		//long n_1 = grid->gridSection.nRow-1;

		//if (m_1 < 0 || n_1 < 0)
		//	return -2;

		//(*zi).resize(n, m, 0.0);
		if (to_allocate)
			grid->gridSection.z = AllocDoubleMat(grid->gridSection.nRow, grid->gridSection.nCol);
		grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
		double min_z = DBL_MAX;
		double max_z = -DBL_MAX;

		//координаты чётырёх углов площадки
		double x0 = grid->gridSection.xLL;
		double y0 = grid->gridSection.yLL;
		double xm = grid->gridSection.xLL + (grid->gridSection.nCol-1)*grid->gridSection.xSize;
		double yn = grid->gridSection.yLL + (grid->gridSection.nRow-1)*grid->gridSection.ySize;

		bool use_contour;
		if (param)
			use_contour = param->use_contour;
		else
		{
			cout << "enter use_contour [0,1]" << endl;
			cin >> use_contour;
		}


		if(use_contour)
		{
			if(!fill_grid_with_contour(grid, 
				vs, 
				x, y, z,
				min_z, max_z, param))
			{
				if (to_allocate)
					FreeDoubleMat(grid->gridSection.z);
				return -1;
			}
		}
		else
		{
			if(!fill_grid_without_contour(grid, 
				vs, 
				x, y, z,
				min_z, max_z, param))
			{
				if (to_allocate)
					FreeDoubleMat(grid->gridSection.z);
				return -1;
			}
		}
		/*
		//Площадь плошадки
		double S = fabs((xm-x0)*(yn-y0));

		//средняя плотность точек
		double plotnost_t = double(len) / S;

		//матожидание расстояния между каждой точкой и ближайшей к ней соседней
		double delta_ma = 0.5 / sqrt(plotnost_t);

		// радиус внутри которого ищем ближайшие точки
		double R = delta_ma*5.0;

		//пространственная индексация - делим площадку на клетки и в каждую клетку складываем координаты попадающих в неё точек
		vector<vector<vector<COORDINATES> > > W;
		size_t start_size = do_quads_indexation(len, x, y, z, grid, W, m_1, n_1);

		double myeps = max(fabs(xm-x0), fabs(yn-y0));
		printf("myeps0 = %f\n", myeps);
		myeps *= pow(pow(10.0,-32), 1./3.);
		//myeps *= 0.005;
		printf("myeps = %f\n", myeps);

		// убираем повторяющиеся точки
		size_t end_size = remove_repeate_points(myeps, W, m_1, n_1);

		printf("start_size = %u end_size =%u\n", start_size, end_size);

		fill_grid(grid, W, m_1, n_1, 		
			   min_z, max_z,
			   max_len);
			   */

		grid->gridSection.zMax = max_z;
		grid->gridSection.zMin = min_z;

		grid->faultSection.nTraces = 0;
		grid->faultSection.nVertices = 0;
		grid->faultSection.traces = NULL;
		grid->faultSection.vertexes = NULL;

	}
	return 0;
}

int partial_gridding(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, int max_len, int (* griddata_fun)(HWND , vector<double>& , vector<double>& , vector<double>& , Grid * ), bool to_allocate)
{
					
	// ищем max_len ближайших точек

	static size_t partial_grid_calling = 0;
	partial_grid_calling++;
	int len = (int)x.size();
printf("partial_gridding len = %d partial_grid_calling = %u\n", len, partial_grid_calling);
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;

	if (grid)
	{
		//long m = (*xi).Length();
		//long n = (*yi).Length();
		long m = grid->gridSection.nCol;
		long n = grid->gridSection.nRow;

		//(*zi).resize(n, m, 0.0);
		if (to_allocate)
			grid->gridSection.z = AllocDoubleMat(n, m);
		grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
		double min_z = DBL_MAX;
		double max_z = -DBL_MAX;

		/*
		jay = sqrt(-1);
		xy = xy.';
		*/

				
		vdouble weights;

				
		vdouble d(max_len, max_len);				
		vdouble g (max_len,max_len);

		vdouble D(max_len);				
		vdouble G(max_len);

		index_for_sort * id = new index_for_sort[len];
						
		for (int k = 0; k < len; k++)
		{
			id[k].i = k;
			id[k].sort_val = 0.0;
		}

//		int k;
		for (long ii = 0; ii < m; ii++)
		{
			printf("ii = %ld m = %ld\n", ii, m);

			for (long jj = 0; jj < n; jj++)
			{
				double x_i = grid->gridSection.xLL + ii*grid->gridSection.xSize;
				double y_j = grid->gridSection.yLL + jj*grid->gridSection.ySize;

				// ищем max_len ближайших точек
				/*for (int k = 0; k < len; k++)
				{
					id[k].i = k;
					id[k].sort_val = sqrt( pow(x[k] - x_i, 2.0) + pow(y[k] - y_j, 2.0) );
				}*/				
				for (int k = 0; k < len; k++)
				{
					//id[k].i = k;
					id[k].sort_val = sqrt( pow(x[id[k].i] - x_i, 2.0) + pow(y[id[k].i] - y_j, 2.0) );
				}

				bool is_sorted = true;
				if (ii == 0 && jj == 0) 
					is_sorted = false;
				else
				{
					for (int k = 1; k < len; k++)
					{
						if (id[k].sort_val < id[k-1].sort_val)
						{
							is_sorted = false;
							break;
						}
					}
				}

				if (!is_sorted)
				{						
					qsort( (void *)id, (size_t)len, sizeof(index_for_sort), compare_index_for_sort );
					
					//d = xy(:,ones(1,length(xy)));
					//d = abs(d - d.');
					// n = size(d,1);
					int  i, j;
					for (i = 0; i < max_len; i++)
					{
						for (j = 0; j < max_len; j++)
						{
							d(i,j) = sqrt( 
								pow(x[id[i].i] - x[id[j].i], 2.0) + pow(y[id[i].i] - y[id[j].i], 2.0) );
						}
					}
					//d.Write("d://_.txt","at","d");

					// Replace zeros along diagonal with ones (so these don't show up in the
					// find below or in the Green's function calculation).
					// d(1:n+1:prod(size(d))) = ones(1,n);
					for (i = 0; i < max_len; i++)
					{
						d(i,i) = 1.0;
					}


					// Determine weights for interpolation
					//g = (d.^2) .* (log(d)-1);   % Green's function.
					for (i = 0; i < max_len; i++)
					{
						for(j = 0; j < max_len; j++)
						{
							g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
						}
					}
						
					//g.Write("d://_.txt","at","g");
					// Fixup value of Green's function along diagonal
					//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
					for (i = 0; i < max_len; i++)
					{
						g(i,i) = 0.0;
					}


					double det;
					vdouble z_(max_len);
					for(i = 0; i < max_len; i++)
						z_[i] = z[id[i].i];
					g.sls_det(z_,weights,det);

					//weights.Write("d://_.txt","at","weights");

					//[m,n] = size(xi);
					// Evaluate at requested points (xi,yi).  Loop to save memory.

					for (int k = 0; k < max_len; k++)
					{
						//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
						D[k] = sqrt( pow(x[id[k].i] - x_i, 2.0) + pow(y[id[k].i] - y_j, 2.0) );
						if (D[k] == 0.0)
							//Value of Green's function at zero
							G[k] = 0.0;
						else
							//Green's function.
							G[k] = pow(D[k], 2.0) * (log(D[k])-1.0);
					}
				}
				//g.Write("d://_.txt","at","{{g}}");
				double z_value = G.ScalarProduct(weights);
				//(*zi)(j,i) = g.ScalarProduct(weights);
				grid->gridSection.z[jj][ii] = z_value;
				if (max_z < z_value) max_z = z_value;
				if (min_z > z_value) min_z = z_value;
			}
		}

		grid->gridSection.zMax = max_z;
		grid->gridSection.zMin = min_z;

		grid->faultSection.nTraces = 0;
		grid->faultSection.nVertices = 0;
		grid->faultSection.traces = NULL;
		grid->faultSection.vertexes = NULL;

		delete [] id;
	}






	//(* griddata_fun)(hwndParent, x, y, z, grid);

	return 0;

}


int partial_gridding2(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, int max_len, int (* griddata_fun)(HWND , vector<double>& , vector<double>& , vector<double>& , Grid * , void * , bool), bool to_allocate)
{
					
	// ищем max_len ближайших точек

	static size_t partial_grid_calling = 0;
	partial_grid_calling++;
	int len = (int)x.size();
printf("partial_gridding len = %d partial_grid_calling = %u\n", len, partial_grid_calling);
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;



	if (grid)
	{
		//long m = (*xi).Length();
		//long n = (*yi).Length();
		long m = grid->gridSection.nCol;
		long n = grid->gridSection.nRow;

		//(*zi).resize(n, m, 0.0);
		if (to_allocate)
			grid->gridSection.z = AllocDoubleMat(n, m);
		grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
		double min_z = DBL_MAX;
		double max_z = -DBL_MAX;

		/*
		jay = sqrt(-1);
		xy = xy.';
		*/

		//координаты чётырёх углов площадки
		double x0 = grid->gridSection.xLL;
		double y0 = grid->gridSection.yLL;
		double xm = grid->gridSection.xLL + (grid->gridSection.nCol-1)*grid->gridSection.xSize;
		double yn = grid->gridSection.yLL + (grid->gridSection.nRow-1)*grid->gridSection.ySize;
		
		//Площадь плошадки
		double S = fabs((xm-x0)*(yn-y0));

		//средняя плотность точек
		double plotnost_t = double(len) / S;

		//матожидание расстояния между каждой точкой и ближайшей к ней соседней
		double delta_ma = 0.5 / sqrt(plotnost_t);

		// радиус внутри которого ищем ближайшие точки
		double R = delta_ma*5.0;

		double z_value;
				
		vdouble weights;
				
		vdouble d;				
		vdouble g;

		vdouble D;				
		vdouble G;

		index_for_sort * id = new index_for_sort[len];
						
		for (int k = 0; k < len; k++)
		{
			id[k].i = k;
			id[k].sort_val = 0.0;
		}

//		int k;
		for (long ii = 0; ii < m; ii++)
		{
			printf("ii = %ld m = %ld\n", ii, m);

			for (long jj = 0; jj < n; jj++)
			{
				double x_i = grid->gridSection.xLL + ii*grid->gridSection.xSize;
				double y_j = grid->gridSection.yLL + jj*grid->gridSection.ySize;

				// ищем max_len ближайших точек
				/*for (int k = 0; k < len; k++)
				{
					id[k].i = k;
					id[k].sort_val = sqrt( pow(x[k] - x_i, 2.0) + pow(y[k] - y_j, 2.0) );
				}*/				
				for (int k = 0; k < len; k++)
				{
					//id[k].i = k;
					id[k].sort_val = sqrt( pow(x[id[k].i] - x_i, 2.0) + pow(y[id[k].i] - y_j, 2.0) );
				}

				
				qsort( (void *)id, (size_t)len, sizeof(index_for_sort), compare_index_for_sort );
									
				for (int k = 0; k < len; k++)
				{
					if (id[k].sort_val > R)
					{
						max_len = k;
						break;
					}
				}

				if (max_len > 1) 
				{
					printf("max_len = %d\n", max_len);

					d.resize(max_len, max_len);				
					g.resize(max_len, max_len);

					D.resize(max_len);				
					G.resize(max_len);

					//d = xy(:,ones(1,length(xy)));
					//d = abs(d - d.');
					// n = size(d,1);
					int  i, j;
					for (i = 0; i < max_len; i++)
					{
						for (j = 0; j < max_len; j++)
						{
							d(i,j) = sqrt( 
								pow(x[id[i].i] - x[id[j].i], 2.0) + pow(y[id[i].i] - y[id[j].i], 2.0) );
						}
					}
					//d.Write("d://_.txt","at","d");

					// Replace zeros along diagonal with ones (so these don't show up in the
					// find below or in the Green's function calculation).
					// d(1:n+1:prod(size(d))) = ones(1,n);
					for (i = 0; i < max_len; i++)
					{
						d(i,i) = 1.0;
					}

					// Determine weights for interpolation
					//g = (d.^2) .* (log(d)-1);   % Green's function.
					for (i = 0; i < max_len; i++)
					{
						for(j = 0; j < max_len; j++)
						{
							g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
						}
					}
						
					//g.Write("d://_.txt","at","g");
					// Fixup value of Green's function along diagonal
					//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
					for (i = 0; i < max_len; i++)
					{
						g(i,i) = 0.0;
					}


					double det;
					vdouble z_(max_len);
					for(i = 0; i < max_len; i++)
						z_[i] = z[id[i].i];
					g.sls_det(z_,weights,det);

					//weights.Write("d://_.txt","at","weights");

					//[m,n] = size(xi);
					// Evaluate at requested points (xi,yi).  Loop to save memory.

					for (int k = 0; k < max_len; k++)
					{
						//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
						D[k] = sqrt( pow(x[id[k].i] - x_i, 2.0) + pow(y[id[k].i] - y_j, 2.0) );
						if (D[k] == 0.0)
							//Value of Green's function at zero
							G[k] = 0.0;
						else
							//Green's function.
							G[k] = pow(D[k], 2.0) * (log(D[k])-1.0);
					}
					//}
					//g.Write("d://_.txt","at","{{g}}");
					z_value = G.ScalarProduct(weights);
				}
				else
					z_value = grid->gridSection.BlankValue;

				//(*zi)(j,i) = g.ScalarProduct(weights);
				grid->gridSection.z[jj][ii] = z_value;
				if (max_z < z_value) max_z = z_value;
				if (min_z > z_value) min_z = z_value;
			}
		}

		grid->gridSection.zMax = max_z;
		grid->gridSection.zMin = min_z;

		grid->faultSection.nTraces = 0;
		grid->faultSection.nVertices = 0;
		grid->faultSection.traces = NULL;
		grid->faultSection.vertexes = NULL;

		delete [] id;
	}






	//(* griddata_fun)(hwndParent, x, y, z, grid);

	return 0;

}

int griddata_v4(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void *, bool to_allocate)
{
	int len = (int)x.size();
printf("griddata_v4 len = %d\n", len); //fflush(stdout);
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;

//	int max_len = 20;

//	if (len > max_len)
//	{
//		return partial_gridding2(hwndParent, x, y, z, grid, max_len, griddata_v4, to_allocate);
//	}

#define PROGRESS_WND_ON_GRIDDATA 0
#if PROGRESS_WND_ON_GRIDDATA
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed

printf("griddata 0\n");
	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(hwndParent, &rcClient); 
	GetWindowRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
			 (LPSTR) NULL, 
			 //WS_CHILD | WS_VISIBLE,
			 WS_POPUPWINDOW,
			 //0, 0,
			 rcClient.left, rcClient.bottom-cyVScroll,
			 rcClient.right, cyVScroll, 
			 //hwndParent, 
			 NULL,
			 
			 (HMENU) 0, hInst, NULL); 

	ShowWindow(hwndPB,1);
printf("griddata 1\n");

	// Gets the file descriptor associated with a stream.
	//int fd = _fileno(stream);
	// Get the length of a file in bytes

	if (grid)
		cb = grid->gridSection.nCol * grid->gridSection.nRow + 5;
	else
		cb = 0;

	// Set the range and increment of the progress
	// bar. 

	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, cb)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//sortrows21(x, y, z);

	COORDINATES * pxyz = new COORDINATES[len];

	int i;
	for (i = 0; i < len; i++)
	{
		pxyz[i].x = x[i];
		pxyz[i].y = y[i];
		pxyz[i].z = z[i];

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
printf("griddata 2\n");

	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );

	for (i = 0; i < len; i++)
	{
		x[i] = pxyz[i].x;
		y[i] = pxyz[i].y;
		z[i] = pxyz[i].z;

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	printf("griddata 3\n");
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	double DX = pxyz[len-1].x-pxyz[0].x;
	double DY = pxyz[len-1].y-pxyz[0].y;

printf("pxyz[len-1].x %f pxyz[0].x %f \n", pxyz[len-1].x, pxyz[0].x, DX);
printf("pxyz[len-1].y %f pxyz[0].y %f \n", pxyz[len-1].y, pxyz[0].y, DY);
	
	delete[] pxyz;

	double myeps = max(DX,DY);
printf("myeps0 = %f\n", myeps);

	myeps *= pow(pow(10.0,-32), 1./3.);

printf("myeps = %f\n", myeps);

	//Vector<bool> vb = 
	//	abs(x.DiffVector()) < myeps && abs(y.DiffVector()) < myeps;


	vector<int> v_i;
	int j,n = (int)x.size();
	for (i = 0; i < n-1; i++)
	{
		for (j = i+1; j < n; j++)
			if (fabs(x[j]-x[i]) < myeps && fabs(y[j]-y[i]) < myeps)
				v_i.push_back(i);
	}


	if(v_i.size() > 0)
	{
printf("Find(vb).Size() = %d len = %d\n", v_i.size(), len);
		MessageBox(0,"Griddata:DuplicateDataPoints","Warning",0);
	}

printf("griddata 5\n");
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
	vdouble d(len, len);
	//d = xy(:,ones(1,length(xy)));
	//d = abs(d - d.');
	// n = size(d,1);
//	int  j;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
		}
	}
printf("griddata 6\n");
	//d.Write("d://_.txt","at","d");

	// Replace zeros along diagonal with ones (so these don't show up in the
	// find below or in the Green's function calculation).
	// d(1:n+1:prod(size(d))) = ones(1,n);
	for (i = 0; i < len; i++)
	{
		d(i,i) = 1.0;
	}
printf("griddata 7\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//d.Write("d://_.txt","at","d");
	// non = find(d == 0);
	Vector<int> non = Find(d == 0);
	//if ~isempty(non),
printf("griddata 8\n");
	if (non.Size() > 0 )
	{
printf("griddata (non.Size() > 0 )\n");
		int non_size = non.Size();
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
		c = c[k];
		//v = (z(r) + z(c))/2; % Average non-distinct pairs
		vdouble v (r.Length());
		for (i = 0; i < r.Length(); i++)
		{
			v[i] = 0.5*(z[int(r[i])] + z[int(c[i])]);
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

		//сортировка по с
		COORDINATES * prcv = new COORDINATES[r.Length()];
		for (i = 0; i < r.Length(); i++)
		{
			prcv[i].x = r[i];
			prcv[i].y = c[i];
			prcv[i].z = v[i];
		}

		qsort((void*)prcv, (size_t)r.Length(), sizeof(COORDINATES), compare_Y );

		for (i = 0; i < r.Length(); i++)
		{
			r[i] = prcv[i].x;
			c[i] = prcv[i].y;
			v[i] = prcv[i].z;
		}

		vdouble c_diff_vect = c.DiffVector();
		Vector<bool> zero_c_diff_vect = c_diff_vect == 0.0;
		Vector<int> rep = Find(zero_c_diff_vect); //ищем повторяющиеся точки

		if (rep.Size() > 0)// более двух точек должны быть усреднены
		{
			vdouble vzero_c_diff_vect(zero_c_diff_vect.Size());
			for (i = 0; i < zero_c_diff_vect.Size(); i++)
			{
				vzero_c_diff_vect[i] = double(zero_c_diff_vect[i]);
			}
			vdouble vv2 = vzero_c_diff_vect.DiffVector();
			Vector<int> runs = Find(vv2 == 1);
			for (i = 0; i < runs.Size(); i++)
			{
				runs[i] += 1;
				Vector<int> k = Find(c == c[runs[i]]);//индексы всех повторяющихся точек
				double mean_z = z[(size_t)c[runs[i]]];
				for(j = 0; j < k.Size(); j++)
				{
					mean_z += z[(size_t)r[k[j]]];
				}
				mean_z /= k.Size()+1;
				v[runs[i]] = mean_z;				
			}			
		}



		//z(r) = v;
		for (i = 0; i < r.Length(); i++)
		{
			z[int(r[i])] = v[i];
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
		/*for (i = 0; i < c.Length(); i++)
		{
			x.DeleteElement(int(c[i]));
			y.DeleteElement(int(c[i]));
			z.DeleteElement(int(c[i]));
		}*/

		//Удаление лишних элементов
		vector<double>::iterator it_x, it_y, it_z;

		it_x = x.begin();
		it_y = y.begin();
		it_z = z.begin();

		double c_pre = 0;
		bool was_erased = false;
		for (i = 0; i < c.Length(); i++)
		{
			for(int j = (int)c_pre + int(was_erased); j < c[i]; j++)
			{
				it_x++; it_y++; it_z++;
			}
			if( i > 0 && c[i] == c_pre)
			{
				// повторяющийся индекс - не производим удаления
			}
			else
			{
				//deleting
				if (it_x != x.end() && it_y != y.end() && it_z != z.end())
				{
					it_x = x.erase(it_x);
					it_y = y.erase(it_y);
					it_z = z.erase(it_z);
				}
			}
			c_pre = c[i];
		}

		len = (int)x.size();

		// Determine distances between points
		d.resize(len, len);
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
			{
				d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
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
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif
printf("griddata 9\n");

	// Determine weights for interpolation
	//g = (d.^2) .* (log(d)-1);   % Green's function.
	vdouble g (len,len);
	for (i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
		}
	}
printf("griddata 10\n");
		
	//g.Write("d://_.txt","at","g");
	// Fixup value of Green's function along diagonal
	//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
	for (i = 0; i < len; i++)
	{
		g(i,i) = 0.0;
	}
printf("griddata 11\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
	vdouble weights;
	double det;
	vdouble z_((int)z.size());
	for(i = 0; i < (int)z.size(); i++)
		z_[i] = z[i];
	g.sls_det(z_,weights,det);
#endif
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
printf("griddata 12\n");

	//weights.Write("d://_.txt","at","weights");

	//[m,n] = size(xi);



	if (grid)
	{
		//long m = (*xi).Length();
		//long n = (*yi).Length();
		long m = grid->gridSection.nCol;
		long n = grid->gridSection.nRow;

		//(*zi).resize(n, m, 0.0);
		if (to_allocate)
			grid->gridSection.z = AllocDoubleMat(n, m);
		grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
		
		double min_z = DBL_MAX;
		double max_z = -DBL_MAX;

		/*
		jay = sqrt(-1);
		xy = xy.';
		*/

		// Evaluate at requested points (xi,yi).  Loop to save memory.
		d.resize(len);
		g.resize(len);
		int k;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				double x_i = grid->gridSection.xLL + i*grid->gridSection.xSize;
				double y_j = grid->gridSection.yLL + j*grid->gridSection.ySize;
				for (k = 0; k < len; k++)
				{
					//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
					d[k] = sqrt( pow(x[k] - x_i, 2.0) + pow(y[k] - y_j, 2.0) );
					if (d[k] == 0.0)
						//Value of Green's function at zero
						g[k] = 0.0;
					else
						//Green's function.
						g[k] = pow(d[k], 2.0) * (log(d[k])-1.0);
				}
				//g.Write("d://_.txt","at","{{g}}");
				double z_value = g.ScalarProduct(weights);
				//(*zi)(j,i) = g.ScalarProduct(weights);
				grid->gridSection.z[j][i] = z_value;
				if (max_z < z_value) max_z = z_value;
				if (min_z > z_value) min_z = z_value;
#if PROGRESS_WND_ON_GRIDDATA	
				SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
			}
		}

		grid->gridSection.zMax = max_z;
		grid->gridSection.zMin = min_z;

		grid->faultSection.nTraces = 0;
		grid->faultSection.nVertices = 0;
		grid->faultSection.traces = NULL;
		grid->faultSection.vertexes = NULL;
	}



#if PROGRESS_WND_ON_GRIDDATA	
	DestroyWindow(hwndPB);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
printf("griddata end\n");

	//----------------------------------------------------------
	return 0;

}
int correct_dublicate(vector<double>& x, vector<double>& y, vector<double>& z)
{
	size_t i, len = x.size();
printf("correct_dublicate = %u\n", x.size());
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%u), y(%u) and z(%u) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using correct_dublicate",0);
		return -1;
	}



	COORDINATES * pxyz = new COORDINATES[len];

	for (i = 0; i < (int)len; i++)
	{
		pxyz[i].x = x[i];
		pxyz[i].y = y[i];
		pxyz[i].z = z[i];

	}

	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );

	for (i = 0; i < (int)len; i++)
	{
		x[i] = pxyz[i].x;
		y[i] = pxyz[i].y;
		z[i] = pxyz[i].z;
	}
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	double DX = pxyz[len-1].x-pxyz[0].x;
	double DY = pxyz[len-1].y-pxyz[0].y;
	
	delete[] pxyz;

	double myeps = max(DX,DY);

printf("myeps0 = %e\n", myeps);

	myeps *= pow(pow(10.0,-32), 1./3.);

printf("myeps = %e\n", myeps);

	vector <int> w (len, 1);
	for (size_t i0 = 0; i0 < x.size(); i0++)
	{
		size_t i1 = i0+1;
		while (i1 < x.size())
		{
			if (fabs(x[i0] - x[i1]) < myeps && fabs(y[i0]-y[i1]) < myeps)
			{
printf("erasing %u %u \n", i0, i1);
printf("erasing (%f %f) &&  (%f %f) \n", x[i0],x[i1],y[i0],y[i1]);

				x[i0] = (x[i0]*w[i0] + x[i1]*w[i1]) / (w[i0] + w[i1]);
				y[i0] = (y[i0]*w[i0] + y[i1]*w[i1]) / (w[i0] + w[i1]);
				z[i0] = (z[i0]*w[i0] + z[i1]*w[i1]) / (w[i0] + w[i1]);
				w[i0] += w[i1];

				x.erase(x.begin() + i1);
				y.erase(y.begin() + i1);
				z.erase(z.begin() + i1);
				w.erase(w.begin() + i1);
			}
			else
			{
				i1++;
			}
		}
	}
printf("correct_dublicate = %u\n", x.size());
}
int griddata(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid,
			 vdouble * xi, vdouble * yi, vdouble * zi, bool to_allocate)
{
	int i, len = (int)x.size();
printf("griddata len = %d\n", len);
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;


#define PROGRESS_WND_ON_GRIDDATA 0
#if PROGRESS_WND_ON_GRIDDATA
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed

printf("griddata 0\n");
	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(hwndParent, &rcClient); 
	GetWindowRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
			 (LPSTR) NULL, 
			 //WS_CHILD | WS_VISIBLE,
			 WS_POPUPWINDOW,
			 //0, 0,
			 rcClient.left, rcClient.bottom-cyVScroll,
			 rcClient.right, cyVScroll, 
			 //hwndParent, 
			 NULL,
			 
			 (HMENU) 0, hInst, NULL); 

	ShowWindow(hwndPB,1);
printf("griddata 1\n");

	// Gets the file descriptor associated with a stream.
	//int fd = _fileno(stream);
	// Get the length of a file in bytes
	if(xi && xi)
		cb = (*xi).Length() * (*yi).Length() + 5;
	else 
	{
		if (grid)
			cb = grid->gridSection.nCol * grid->gridSection.nRow + 5;
		else
			cb = 0;
	}


	// Set the range and increment of the progress
	// bar. 

	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, cb)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//sortrows21(x, y, z);

	COORDINATES * pxyz = new COORDINATES[len];

	for (i = 0; i < len; i++)
	{
		pxyz[i].x = x[i];
		pxyz[i].y = y[i];
		pxyz[i].z = z[i];

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
printf("griddata 2\n");

	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );

	for (i = 0; i < len; i++)
	{
		x[i] = pxyz[i].x;
		y[i] = pxyz[i].y;
		z[i] = pxyz[i].z;

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	printf("griddata 3\n");
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	double DX = pxyz[len-1].x-pxyz[0].x;
	double DY = pxyz[len-1].y-pxyz[0].y;

printf("pxyz[len-1].x %f pxyz[0].x %f \n", pxyz[len-1].x, pxyz[0].x, DX);
printf("pxyz[len-1].y %f pxyz[0].y %f \n", pxyz[len-1].y, pxyz[0].y, DY);
	
	delete[] pxyz;

	double myeps = max(DX,DY);
printf("myeps0 = %f\n", myeps);

	myeps *= pow(pow(10.0,-32), 1./3.);

printf("myeps = %f\n", myeps);

	//Vector<bool> vb = 
	//	abs(x.DiffVector()) < myeps && abs(y.DiffVector()) < myeps;
	vector<int> v_i;
	int j,n = (int)x.size();
	for (i = 0; i < n-1; i++)
	{
		for (j = i+1; j < n; j++)
			if (fabs(x[j]-x[i]) < myeps && fabs(y[j]-y[i]) < myeps)
				v_i.push_back(i);
	}



	if(v_i.size() > 0)
	{
printf("Find(vb).Size() = %d len = %d\n", v_i.size(), len);
		MessageBox(0,"Griddata:DuplicateDataPoints","Warning",0);
	}

printf("griddata 5\n");
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
	vdouble d(len, len);
	//d = xy(:,ones(1,length(xy)));
	//d = abs(d - d.');
	// n = size(d,1);
//	int  j;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
		}
	}
printf("griddata 6\n");
	//d.Write("d://_.txt","at","d");

	// Replace zeros along diagonal with ones (so these don't show up in the
	// find below or in the Green's function calculation).
	// d(1:n+1:prod(size(d))) = ones(1,n);
	for (i = 0; i < len; i++)
	{
		d(i,i) = 1.0;
	}
printf("griddata 7\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//d.Write("d://_.txt","at","d");
	// non = find(d == 0);
	Vector<int> non = Find(d == 0);
	//if ~isempty(non),
printf("griddata 8\n");
	if (non.Size() > 0 )
	{
printf("griddata (non.Size() > 0 )\n");
		int non_size = non.Size();
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
		c = c[k];
		//v = (z(r) + z(c))/2; % Average non-distinct pairs
		vdouble v (r.Length());
		for (i = 0; i < r.Length(); i++)
		{
			v[i] = 0.5*(z[int(r[i])] + z[int(c[i])]);
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

		//сортировка по с
		COORDINATES * prcv = new COORDINATES[r.Length()];
		for (i = 0; i < r.Length(); i++)
		{
			prcv[i].x = r[i];
			prcv[i].y = c[i];
			prcv[i].z = v[i];
		}

		qsort((void*)prcv, (size_t)r.Length(), sizeof(COORDINATES), compare_Y );

		for (i = 0; i < r.Length(); i++)
		{
			r[i] = prcv[i].x;
			c[i] = prcv[i].y;
			v[i] = prcv[i].z;
		}

		vdouble c_diff_vect = c.DiffVector();
		Vector<bool> zero_c_diff_vect = c_diff_vect == 0.0;
		Vector<int> rep = Find(zero_c_diff_vect); //ищем повторяющиеся точки

		if (rep.Size() > 0)// более двух точек должны быть усреднены
		{
			vdouble vzero_c_diff_vect(zero_c_diff_vect.Size());
			for (i = 0; i < zero_c_diff_vect.Size(); i++)
			{
				vzero_c_diff_vect[i] = double(zero_c_diff_vect[i]);
			}
			vdouble vv2 = vzero_c_diff_vect.DiffVector();
			Vector<int> runs = Find(vv2 == 1);
			for (i = 0; i < runs.Size(); i++)
			{
				runs[i] += 1;
				Vector<int> k = Find(c == c[runs[i]]);//индексы всех повторяющихся точек
				double mean_z = z[(size_t)c[runs[i]]];
				for(j = 0; j < k.Size(); j++)
				{
					mean_z += z[(size_t)r[k[j]]];
				}
				mean_z /= k.Size()+1;
				v[runs[i]] = mean_z;				
			}			
		}



		//z(r) = v;
		for (i = 0; i < r.Length(); i++)
		{
			z[int(r[i])] = v[i];
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
		/*for (i = 0; i < c.Length(); i++)
		{
			x.DeleteElement(int(c[i]));
			y.DeleteElement(int(c[i]));
			z.DeleteElement(int(c[i]));
		}*/

		//Удаление лишних элементов
		vector<double>::iterator it_x, it_y, it_z;

		it_x = x.begin();
		it_y = y.begin();
		it_z = z.begin();

		double c_pre = 0;
		bool was_erased = false;
		for (i = 0; i < c.Length(); i++)
		{
			for(int j = (int)c_pre + int(was_erased); j < c[i]; j++)
			{
				it_x++; it_y++; it_z++;
			}
			if( i > 0 && c[i] == c_pre)
			{
				// повторяющийся индекс - не производим удаления
			}
			else
			{
				//deleting
				if (it_x != x.end() && it_y != y.end() && it_z != z.end())
				{
					it_x = x.erase(it_x);
					it_y = y.erase(it_y);
					it_z = z.erase(it_z);
				}
			}
			c_pre = c[i];
		}

		len = (int)x.size();

		// Determine distances between points
		d.resize(len, len);
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
			{
				d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
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
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif
printf("griddata 9\n");

	// Determine weights for interpolation
	//g = (d.^2) .* (log(d)-1);   % Green's function.
	vdouble g (len,len);
	for (i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
		}
	}
printf("griddata 10\n");
		
	//g.Write("d://_.txt","at","g");
	// Fixup value of Green's function along diagonal
	//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
	for (i = 0; i < len; i++)
	{
		g(i,i) = 0.0;
	}
printf("griddata 11\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
	vdouble weights;
	double det;
	vdouble z_((int)z.size());
	for(i = 0; i < (int)z.size(); i++)
		z_[i] = z[i];
	g.sls_det(z_,weights,det);
#endif
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
printf("griddata 12\n");

	//weights.Write("d://_.txt","at","weights");

	//[m,n] = size(xi);


	if(xi && xi && zi)
	{
		long m = (*xi).Length();
		long n = (*yi).Length();

		(*zi).resize(n, m, 0.0);
		/*
		jay = sqrt(-1);
		xy = xy.';
		*/

		// Evaluate at requested points (xi,yi).  Loop to save memory.
		d.resize(len);
		g.resize(len);
		int k;
		for (i = 0; i < m; i++)
		{
			for (j = 0; j < n; j++)
			{
				for (k = 0; k < len; k++)
				{
					d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
					if (d[k] == 0.0)
						//Value of Green's function at zero
						g[k] = 0.0;
					else
						//Green's function.
						g[k] = pow(d[k], 2.0) * (log(d[k])-1.0);
				}
				//g.Write("d://_.txt","at","{{g}}");
				(*zi)(j,i) = g.ScalarProduct(weights);
#if PROGRESS_WND_ON_GRIDDATA	
				SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
			}
		}
	}
	else 
	{
		if (grid)
		{
			//long m = (*xi).Length();
			//long n = (*yi).Length();
			long m = grid->gridSection.nCol;
			long n = grid->gridSection.nRow;

			//(*zi).resize(n, m, 0.0);
			if (to_allocate)
				grid->gridSection.z = AllocDoubleMat(n, m);
			grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
			
			double min_z = DBL_MAX;
			double max_z = -DBL_MAX;

			/*
			jay = sqrt(-1);
			xy = xy.';
			*/

			// Evaluate at requested points (xi,yi).  Loop to save memory.
			d.resize(len);
			g.resize(len);
			int k;
			for (i = 0; i < m; i++)
			{
				for (j = 0; j < n; j++)
				{
					double x_i = grid->gridSection.xLL + i*grid->gridSection.xSize;
					double y_j = grid->gridSection.yLL + j*grid->gridSection.ySize;
					for (k = 0; k < len; k++)
					{
						//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
						d[k] = sqrt( pow(x[k] - x_i, 2.0) + pow(y[k] - y_j, 2.0) );
						if (d[k] == 0.0)
							//Value of Green's function at zero
							g[k] = 0.0;
						else
							//Green's function.
							g[k] = pow(d[k], 2.0) * (log(d[k])-1.0);
					}
					//g.Write("d://_.txt","at","{{g}}");
					double z_value = g.ScalarProduct(weights);
					//(*zi)(j,i) = g.ScalarProduct(weights);
					grid->gridSection.z[j][i] = z_value;
					if (max_z < z_value) max_z = z_value;
					if (min_z > z_value) min_z = z_value;
#if PROGRESS_WND_ON_GRIDDATA	
					SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
				}
			}

			grid->gridSection.zMax = max_z;
			grid->gridSection.zMin = min_z;

			grid->faultSection.nTraces = 0;
			grid->faultSection.nVertices = 0;
			grid->faultSection.traces = NULL;
			grid->faultSection.vertexes = NULL;
		}
	}


#if PROGRESS_WND_ON_GRIDDATA	
	DestroyWindow(hwndPB);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
printf("griddata end\n");

	//----------------------------------------------------------
	return 0;

}
int griddata(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, 
			 Grid * grid, void *, bool to_allocate)
{
	int i, len = (int)x.size();
printf("griddata len = %d\n", len);
	if ( len != y.size() || len != z.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d) and z(%d) must be equial",
			len, y.size(), z.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;


#define PROGRESS_WND_ON_GRIDDATA 0
#if PROGRESS_WND_ON_GRIDDATA
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed

printf("griddata 0\n");
	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(hwndParent, &rcClient); 
	GetWindowRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
			 (LPSTR) NULL, 
			 //WS_CHILD | WS_VISIBLE,
			 WS_POPUPWINDOW,
			 //0, 0,
			 rcClient.left, rcClient.bottom-cyVScroll,
			 rcClient.right, cyVScroll, 
			 //hwndParent, 
			 NULL,
			 
			 (HMENU) 0, hInst, NULL); 

	ShowWindow(hwndPB,1);
printf("griddata 1\n");

	// Gets the file descriptor associated with a stream.
	//int fd = _fileno(stream);
	// Get the length of a file in bytes
	if(xi && xi)
		cb = (*xi).Length() * (*yi).Length() + 5;
	else 
	{
		if (grid)
			cb = grid->gridSection.nCol * grid->gridSection.nRow + 5;
		else
			cb = 0;
	}


	// Set the range and increment of the progress
	// bar. 

	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, cb)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//sortrows21(x, y, z);

	COORDINATES * pxyz = new COORDINATES[len];

	for (i = 0; i < len; i++)
	{
		pxyz[i].x = x[i];
		pxyz[i].y = y[i];
		pxyz[i].z = z[i];

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
printf("griddata 2\n");

	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_Y );
	qsort( (void *)pxyz, (size_t)len, sizeof(COORDINATES), compare_X );

	for (i = 0; i < len; i++)
	{
		x[i] = pxyz[i].x;
		y[i] = pxyz[i].y;
		z[i] = pxyz[i].z;

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	printf("griddata 3\n");
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	double DX = pxyz[len-1].x-pxyz[0].x;
	double DY = pxyz[len-1].y-pxyz[0].y;

printf("pxyz[len-1].x %f pxyz[0].x %f \n", pxyz[len-1].x, pxyz[0].x, DX);
printf("pxyz[len-1].y %f pxyz[0].y %f \n", pxyz[len-1].y, pxyz[0].y, DY);
	
	delete[] pxyz;

	double myeps = max(DX,DY);
printf("myeps0 = %f\n", myeps);

	myeps *= pow(pow(10.0,-32), 1./3.);

printf("myeps = %f\n", myeps);

	//Vector<bool> vb = 
	//	abs(x.DiffVector()) < myeps && abs(y.DiffVector()) < myeps;
	vector<int> v_i;
	int j,n = (int)x.size();
	for (i = 0; i < n-1; i++)
	{
		for (j = i+1; j < n; j++)
			if (fabs(x[j]-x[i]) < myeps && fabs(y[j]-y[i]) < myeps)
				v_i.push_back(i);
	}



	if(v_i.size() > 0)
	{
printf("Find(vb).Size() = %d len = %d\n", v_i.size(), len);
		MessageBox(0,"Griddata:DuplicateDataPoints","Warning",0);
	}

printf("griddata 5\n");
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
	vdouble d(len, len);
	//d = xy(:,ones(1,length(xy)));
	//d = abs(d - d.');
	// n = size(d,1);
//	int  j;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
		}
	}
printf("griddata 6\n");
	//d.Write("d://_.txt","at","d");

	// Replace zeros along diagonal with ones (so these don't show up in the
	// find below or in the Green's function calculation).
	// d(1:n+1:prod(size(d))) = ones(1,n);
	for (i = 0; i < len; i++)
	{
		d(i,i) = 1.0;
	}
printf("griddata 7\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//d.Write("d://_.txt","at","d");
	// non = find(d == 0);
	Vector<int> non = Find(d == 0);
	//if ~isempty(non),
printf("griddata 8\n");
	if (non.Size() > 0 )
	{
printf("griddata (non.Size() > 0 )\n");
		int non_size = non.Size();
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
		c = c[k];
		//v = (z(r) + z(c))/2; % Average non-distinct pairs
		vdouble v (r.Length());
		for (i = 0; i < r.Length(); i++)
		{
			v[i] = 0.5*(z[int(r[i])] + z[int(c[i])]);
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

		//сортировка по с
		COORDINATES * prcv = new COORDINATES[r.Length()];
		for (i = 0; i < r.Length(); i++)
		{
			prcv[i].x = r[i];
			prcv[i].y = c[i];
			prcv[i].z = v[i];
		}

		qsort((void*)prcv, (size_t)r.Length(), sizeof(COORDINATES), compare_Y );

		for (i = 0; i < r.Length(); i++)
		{
			r[i] = prcv[i].x;
			c[i] = prcv[i].y;
			v[i] = prcv[i].z;
		}

		vdouble c_diff_vect = c.DiffVector();
		Vector<bool> zero_c_diff_vect = c_diff_vect == 0.0;
		Vector<int> rep = Find(zero_c_diff_vect); //ищем повторяющиеся точки

		if (rep.Size() > 0)// более двух точек должны быть усреднены
		{
			vdouble vzero_c_diff_vect(zero_c_diff_vect.Size());
			for (i = 0; i < zero_c_diff_vect.Size(); i++)
			{
				vzero_c_diff_vect[i] = double(zero_c_diff_vect[i]);
			}
			vdouble vv2 = vzero_c_diff_vect.DiffVector();
			Vector<int> runs = Find(vv2 == 1);
			for (i = 0; i < runs.Size(); i++)
			{
				runs[i] += 1;
				Vector<int> k = Find(c == c[runs[i]]);//индексы всех повторяющихся точек
				double mean_z = z[(size_t)c[runs[i]]];
				for(j = 0; j < k.Size(); j++)
				{
					mean_z += z[(size_t)r[k[j]]];
				}
				mean_z /= k.Size()+1;
				v[runs[i]] = mean_z;				
			}			
		}



		//z(r) = v;
		for (i = 0; i < r.Length(); i++)
		{
			z[int(r[i])] = v[i];
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
		/*for (i = 0; i < c.Length(); i++)
		{
			x.DeleteElement(int(c[i]));
			y.DeleteElement(int(c[i]));
			z.DeleteElement(int(c[i]));
		}*/

		//Удаление лишних элементов
		vector<double>::iterator it_x, it_y, it_z;

		it_x = x.begin();
		it_y = y.begin();
		it_z = z.begin();

		double c_pre = 0;
		bool was_erased = false;
		for (i = 0; i < c.Length(); i++)
		{
			for(int j = (int)c_pre + int(was_erased); j < c[i]; j++)
			{
				it_x++; it_y++; it_z++;
			}
			if( i > 0 && c[i] == c_pre)
			{
				// повторяющийся индекс - не производим удаления
			}
			else
			{
				//deleting
				if (it_x != x.end() && it_y != y.end() && it_z != z.end())
				{
					it_x = x.erase(it_x);
					it_y = y.erase(it_y);
					it_z = z.erase(it_z);
				}
			}
			c_pre = c[i];
		}

		len = (int)x.size();

		// Determine distances between points
		d.resize(len, len);
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
			{
				d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) );
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
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif
printf("griddata 9\n");

	// Determine weights for interpolation
	//g = (d.^2) .* (log(d)-1);   % Green's function.
	vdouble g (len,len);
	for (i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
		}
	}
printf("griddata 10\n");
		
	//g.Write("d://_.txt","at","g");
	// Fixup value of Green's function along diagonal
	//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
	for (i = 0; i < len; i++)
	{
		g(i,i) = 0.0;
	}
printf("griddata 11\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
	vdouble weights;
	double det;
	vdouble z_((int)z.size());
	for(i = 0; i < (int)z.size(); i++)
		z_[i] = z[i];
	g.sls_det(z_,weights,det);
#endif
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
printf("griddata 12\n");

	//weights.Write("d://_.txt","at","weights");

	//[m,n] = size(xi);



	{
		if (grid)
		{
			//long m = (*xi).Length();
			//long n = (*yi).Length();
			long m = grid->gridSection.nCol;
			long n = grid->gridSection.nRow;

			//(*zi).resize(n, m, 0.0);
			if (to_allocate)
				grid->gridSection.z = AllocDoubleMat(n, m);
			grid->gridSection.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
			
			double min_z = DBL_MAX;
			double max_z = -DBL_MAX;

			/*
			jay = sqrt(-1);
			xy = xy.';
			*/

			// Evaluate at requested points (xi,yi).  Loop to save memory.
			d.resize(len);
			g.resize(len);
			int k;
			for (i = 0; i < m; i++)
			{
				for (j = 0; j < n; j++)
				{
					double x_i = grid->gridSection.xLL + i*grid->gridSection.xSize;
					double y_j = grid->gridSection.yLL + j*grid->gridSection.ySize;
					for (k = 0; k < len; k++)
					{
						//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
						d[k] = sqrt( pow(x[k] - x_i, 2.0) + pow(y[k] - y_j, 2.0) );
						if (d[k] == 0.0)
							//Value of Green's function at zero
							g[k] = 0.0;
						else
							//Green's function.
							g[k] = pow(d[k], 2.0) * (log(d[k])-1.0);
					}
					//g.Write("d://_.txt","at","{{g}}");
					double z_value = g.ScalarProduct(weights);
					//(*zi)(j,i) = g.ScalarProduct(weights);
					grid->gridSection.z[j][i] = z_value;
					if (max_z < z_value) max_z = z_value;
					if (min_z > z_value) min_z = z_value;
#if PROGRESS_WND_ON_GRIDDATA	
					SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
				}
			}

			grid->gridSection.zMax = max_z;
			grid->gridSection.zMin = min_z;

			grid->faultSection.nTraces = 0;
			grid->faultSection.nVertices = 0;
			grid->faultSection.traces = NULL;
			grid->faultSection.vertexes = NULL;
		}
	}


#if PROGRESS_WND_ON_GRIDDATA	
	DestroyWindow(hwndPB);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
printf("griddata end\n");

	//----------------------------------------------------------
	return 0;

}




int griddata4(HWND hwndParent, vector<double>& x, vector<double>& y, vector<double>& z, vector<double>& v, 
			 Grid4 * grid, void *, bool to_allocate)
{
	int i, len = (int)x.size();
printf("griddata len = %d\n", len);
	if ( len != y.size() || len != z.size()  || len != v.size() )
	{
		char errstr[1024];
		sprintf(errstr, 
			"lengthes of vectors x(%d), y(%d), z(%d) and v(%d) must be equial",
			len, y.size(), z.size(), v.size());
		MessageBox(0, errstr,"Error using driddata",0);
		return -1;
	}

	if (len < 2)
		return -1;


#define PROGRESS_WND_ON_GRIDDATA 0
#if PROGRESS_WND_ON_GRIDDATA
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	RECT rcClient;  // Client area of parent window 
	int cyVScroll;  // Height of scroll bar arrow 
	HWND hwndPB;    // Handle of progress bar 
	DWORD cb,		// Size of file and count of
	  cb_read = 0,  // bytes read 
	  cb_disp = 0;  // bytes displayed

printf("griddata 0\n");
	// Ensure that the common control DLL is loaded
	// and create a progress bar along the bottom of
	// the client area of the parent window. 
	// Base the height of the progress bar on the
	// height of a scroll bar arrow. 
	InitCommonControls(); 
	GetClientRect(hwndParent, &rcClient); 
	GetWindowRect(hwndParent, &rcClient); 
	cyVScroll = GetSystemMetrics(SM_CYVSCROLL); 
	hwndPB = CreateWindowEx(WS_EX_TOPMOST, PROGRESS_CLASS,
			 (LPSTR) NULL, 
			 //WS_CHILD | WS_VISIBLE,
			 WS_POPUPWINDOW,
			 //0, 0,
			 rcClient.left, rcClient.bottom-cyVScroll,
			 rcClient.right, cyVScroll, 
			 //hwndParent, 
			 NULL,
			 
			 (HMENU) 0, hInst, NULL); 

	ShowWindow(hwndPB,1);
printf("griddata 1\n");

	// Gets the file descriptor associated with a stream.
	//int fd = _fileno(stream);
	// Get the length of a file in bytes
	if(xi && xi)
		cb = (*xi).Length() * (*yi).Length() + 5;
	else 
	{
		if (grid)
			cb = grid->gridSection.nCol * grid->gridSection.nRow + 5;
		else
			cb = 0;
	}


	// Set the range and increment of the progress
	// bar. 

	SendMessage(hwndPB, PBM_SETRANGE, 0,
				MAKELPARAM(0, cb)); 
	SendMessage(hwndPB, PBM_SETSTEP, (WPARAM) 1, 0); 
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//sortrows21(x, y, z);

	COORDINATES4 * pxyzv = new COORDINATES4[len];

	for (i = 0; i < len; i++)
	{
		pxyzv[i].x = x[i];
		pxyzv[i].y = y[i];
		pxyzv[i].z = z[i];
		pxyzv[i].v = v[i];

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
printf("griddata 2\n");

	qsort( (void *)pxyzv, (size_t)len, sizeof(COORDINATES4), compare4_Z );
	qsort( (void *)pxyzv, (size_t)len, sizeof(COORDINATES4), compare4_Y );
	qsort( (void *)pxyzv, (size_t)len, sizeof(COORDINATES4), compare4_X );
#if 0
	for (i = 0; i < len; i++)
	{
		x[i] = pxyzv[i].x;
		y[i] = pxyzv[i].y;
		z[i] = pxyzv[i].z;
		v[i] = pxyzv[i].v;

		//printf("[%f %f %f]\n", x[i], y[i], z[i]);
	}
#endif

#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	printf("griddata 3\n");
	//==============================================================
	//==============================================================
	//==============================================================
	//==============================================================
	double DX = pxyzv[len-1].x-pxyzv[0].x;
	double DY = pxyzv[len-1].y-pxyzv[0].y;
	double DZ = pxyzv[len-1].z-pxyzv[0].z;

printf("pxyzv[len-1].x %f pxyzv[0].x %f DX = %f\n", pxyzv[len-1].x, pxyzv[0].x, DX);
printf("pxyzv[len-1].y %f pxyzv[0].y %f DY = %f\n", pxyzv[len-1].y, pxyzv[0].y, DY);
printf("pxyzv[len-1].z %f pxyzv[0].z %f DZ = %f\n", pxyzv[len-1].z, pxyzv[0].z, DZ);
	
	delete[] pxyzv;

	double myeps = max(max(DX,DY),fabs(DZ));
printf("myeps0 = %f\n", myeps);

	myeps *= pow(pow(10.0,-32), 1./3.);

printf("myeps = %e\n", myeps);

	//Vector<bool> vb = 
	//	abs(x.DiffVector()) < myeps && abs(y.DiffVector()) < myeps;
	vector<int> v_i;
	int j,n = (int)x.size();
	for (i = 0; i < n-1; i ++)
	{
		for (j = i+1; j < n; j++)
		{
			if (fabs(x[j]-x[i]) < myeps && fabs(y[j]-y[i]) < myeps && fabs(z[j]-z[i]) < myeps)
			{
				v_i.push_back(i);
				printf("dublicate points i = %d, j = %d\n", i, j);
				printf("x[i] = %e, y[i] = %e, z[i] = %e, v[i] = %e\n", x[i], y[i], z[i], v[i]);
				printf("x[j] = %e, y[j] = %e, z[j] = %e, v[j] = %e\n", x[j], y[j], z[j], v[j]);
				printf("fabs(x[j]-x[i]) = %e, fabs(y[j]-y[i]) = %e, fabs(z[j]-z[i]) = %e\n", fabs(x[j]-x[i]), fabs(y[j]-y[i]), fabs(z[j]-z[i]));
				printf("v[j] = %e, v[i] = %e, fabs(v[j]-v[i]) = %e\n", v[j], v[i], fabs(v[j]-v[i]));
			}
		}
	}

	/*for (i = 0; i < n-1; i ++)
	{
		printf("%f, %f, %f, %f\n", x[i], y[i], z[i], v[i]);
	}*/

	if(v_i.size() > 0)
	{
printf("Find(vb).Size() = %d len = %d\n", v_i.size(), len);
		MessageBox(0,"Griddata:DuplicateDataPoints","Warning",0);
	}

printf("griddata 5\n");
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
	vdouble d(len, len);
	//d = xy(:,ones(1,length(xy)));
	//d = abs(d - d.');
	// n = size(d,1);
//	int  j;
	for (i = 0; i < len; i++)
	{
		for (j = 0; j < len; j++)
		{
			d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) + pow(z[i] - z[j], 2.0) );
		}
	}
printf("griddata 6\n");
	//d.Write("d://_.txt","at","d");

	// Replace zeros along diagonal with ones (so these don't show up in the
	// find below or in the Green's function calculation).
	// d(1:n+1:prod(size(d))) = ones(1,n);
	for (i = 0; i < len; i++)
	{
		d(i,i) = 1.0;
	}
printf("griddata 7\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
	//d.Write("d://_.txt","at","d");
	// non = find(d == 0);
	Vector<int> non = Find(d == 0);
	//if ~isempty(non),
printf("griddata 8\n");
	if (non.Size() > 0 )
	{
printf("griddata (non.Size() > 0 )\n");
		int non_size = non.Size();
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
		c = c[k];
		//v = (z(r) + z(c))/2; % Average non-distinct pairs
		vdouble w (r.Length());
		for (i = 0; i < r.Length(); i++)
		{
			w[i] = 0.5*(v[int(r[i])] + v[int(c[i])]);
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

		//сортировка по с
		COORDINATES * prcv = new COORDINATES[r.Length()];
		for (i = 0; i < r.Length(); i++)
		{
			prcv[i].x = r[i];
			prcv[i].y = c[i];
			prcv[i].z = w[i];
		}

		qsort((void*)prcv, (size_t)r.Length(), sizeof(COORDINATES), compare_Y );

		for (i = 0; i < r.Length(); i++)
		{
			r[i] = prcv[i].x;
			c[i] = prcv[i].y;
			w[i] = prcv[i].z;
		}

		vdouble c_diff_vect = c.DiffVector();
		Vector<bool> zero_c_diff_vect = c_diff_vect == 0.0;
		Vector<int> rep = Find(zero_c_diff_vect); //ищем повторяющиеся точки

		if (rep.Size() > 0)// более двух точек должны быть усреднены
		{
			vdouble vzero_c_diff_vect(zero_c_diff_vect.Size());
			for (i = 0; i < zero_c_diff_vect.Size(); i++)
			{
				vzero_c_diff_vect[i] = double(zero_c_diff_vect[i]);
			}
			vdouble vv2 = vzero_c_diff_vect.DiffVector();
			Vector<int> runs = Find(vv2 == 1);
			for (i = 0; i < runs.Size(); i++)
			{
				runs[i] += 1;
				Vector<int> k = Find(c == c[runs[i]]);//индексы всех повторяющихся точек
				double mean_z = z[(size_t)c[runs[i]]];
				for(j = 0; j < k.Size(); j++)
				{
					mean_z += z[(size_t)r[k[j]]];
				}
				mean_z /= k.Size()+1;
				w[runs[i]] = mean_z;				
			}			
		}



		//z(r) = v;
		for (i = 0; i < r.Length(); i++)
		{
			v[int(r[i])] = w[i];
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
		/*for (i = 0; i < c.Length(); i++)
		{
			x.DeleteElement(int(c[i]));
			y.DeleteElement(int(c[i]));
			z.DeleteElement(int(c[i]));
		}*/

		//Удаление лишних элементов
		vector<double>::iterator it_x, it_y, it_z, it_v;

		it_x = x.begin();
		it_y = y.begin();
		it_z = z.begin();
		it_v = v.begin();

		double c_pre = 0;
		bool was_erased = false;
		for (i = 0; i < c.Length(); i++)
		{
			for(int j = (int)c_pre + int(was_erased); j < c[i]; j++)
			{
				it_x++; it_y++; it_z++;
			}
			if( i > 0 && c[i] == c_pre)
			{
				// повторяющийся индекс - не производим удаления
			}
			else
			{
				//deleting
				if (it_x != x.end() && it_y != y.end() && it_z != z.end() && it_v != v.end())
				{
					it_x = x.erase(it_x);
					it_y = y.erase(it_y);
					it_z = z.erase(it_z);
					it_v = v.erase(it_v);
				}
			}
			c_pre = c[i];
		}

		len = (int)x.size();

		// Determine distances between points
		d.resize(len, len);
		for (i = 0; i < len; i++)
		{
			for (j = 0; j < len; j++)
			{
				d(i,j) = sqrt( pow(x[i] - x[j], 2.0) + pow(y[i] - y[j], 2.0) + pow(z[i] - z[j], 2.0) );
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
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif
printf("griddata 9\n");

	// Determine weights for interpolation
	//g = (d.^2) .* (log(d)-1);   % Green's function.
	vdouble g (len,len);
	for (i = 0; i < len; i++)
	{
		for(j = 0; j < len; j++)
		{
			g(i,j) = pow(d(i,j), 2.0) * (log(d(i,j))-1.0);
		}
	}
printf("griddata 10\n");
		
	//g.Write("d://_.txt","at","g");
	// Fixup value of Green's function along diagonal
	//g(1:size(d,1)+1:prod(size(d))) = zeros(size(d,1),1);
	for (i = 0; i < len; i++)
	{
		g(i,i) = 0.0;
	}
printf("griddata 11\n");
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
	vdouble weights;
	double det;
	vdouble v_((int)v.size());
	for(i = 0; i < (int)v.size(); i++)
		v_[i] = v[i];
	g.sls_det(v_,weights,det);
#endif
#if PROGRESS_WND_ON_GRIDDATA
	SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
printf("griddata 12\n");

	//weights.Write("d://_.txt","at","weights");
	//v_._printf("v_");
	//g._printf("g");
	//weights._printf("weights");
	//MessageBox(0,"","",0);

	//[m,n] = size(xi);



	{
		if (grid)
		{
			//long m = (*xi).Length();
			//long n = (*yi).Length();
			//long m = grid->gridSection.nCol;
			//long n = grid->gridSection.nRow;

			//(*zi).resize(n, m, 0.0);
			if (to_allocate)
				grid->grid4Section.v = Alloc3DMat<double>(grid->grid4Section.nPag, grid->grid4Section.nRow, grid->grid4Section.nCol);
			grid->grid4Section.BlankValue = BLANK_VALUE;//1.70141e38;// nodes are blanked if greater or equal to this value
			
			double min_v = DBL_MAX;
			double max_v = -DBL_MAX;

			/*
			jay = sqrt(-1);
			xy = xy.';
			*/

			// Evaluate at requested points (xi,yi).  Loop to save memory.
			d.resize(len);
			g.resize(len);
			int k;
			for(long p = 0; p < grid->grid4Section.nPag; p++)
			{
printf("griddata p = %ld %ld\n", p, grid->grid4Section.nPag);
				double z_p = grid->grid4Section.zLL + p*grid->grid4Section.zSize;
				for(long r = 0; r < grid->grid4Section.nRow; r++)
				{
					double y_r = grid->grid4Section.yLL + r*grid->grid4Section.ySize;
					for(long c = 0; c < grid->grid4Section.nCol; c++)
					{
						double x_c = grid->grid4Section.xLL + c*grid->grid4Section.xSize;
						for (k = 0; k < len; k++)
						{
							//d[k] = sqrt( pow(x[k] - (*xi)[i], 2.0) + pow(y[k] - (*yi)[j], 2.0) );
							d[k] = sqrt( pow(x[k] - x_c, 2.0) + pow(y[k] - y_r, 2.0) + pow(z[k] - z_p, 2.0) );
							if (d[k] == 0.0)
								//Value of Green's function at zero
								g[k] = 0.0;
							else
								//Green's function.
								g[k] = pow(d[k], 2.0) * (log(d[k])-1.0);
						}
						//g.Write("d://_.txt","at","{{g}}");
						//g._printf("g");
						double v_value = g.ScalarProduct(weights);

						//printf("v_value = %f\n", v_value);
						//(*zi)(j,i) = g.ScalarProduct(weights);
						grid->grid4Section.v[p][r][c] = v_value;
						if (max_v < v_value) max_v = v_value;
						if (min_v > v_value) min_v = v_value;
#if PROGRESS_WND_ON_GRIDDATA	
						SendMessage(hwndPB, PBM_STEPIT, 0, 0); 
#endif /*PROGRESS_WND_ON_GRIDDATA*/
					}
				}
			}

			grid->grid4Section.vMax = max_v;
			grid->grid4Section.vMin = min_v;

//			grid->faultSection.nTraces = 0;
//			grid->faultSection.nVertices = 0;
//			grid->faultSection.traces = NULL;
//			grid->faultSection.vertexes = NULL;
		}
	}


#if PROGRESS_WND_ON_GRIDDATA	
	DestroyWindow(hwndPB);
#endif /*PROGRESS_WND_ON_GRIDDATA*/
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
printf("griddata end\n");

	//----------------------------------------------------------
	return 0;

}

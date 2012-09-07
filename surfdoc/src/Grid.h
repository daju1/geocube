// Grid.h: interface for the CGrid class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRID_H__68253D2E_C955_4BA1_8005_23D050633EB1__INCLUDED_)
#define AFX_GRID_H__68253D2E_C955_4BA1_8005_23D050633EB1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../array/src/vdouble.h"
#include <iostream> 
using namespace std;

#define FAST_GRID_LOADING 1

#define BLANK_VALUE 170141000918782800000000000000000000000.000000

struct Trace
{ 
	long iFirst;// 0-based index into the vertex array for the first vertex of this trace
	long nPts;  // number of vertices in this trace
};

struct Vertex
{
	double x;// X coordinate of the vertex
	double y;// Y coordinate of the vertex
};
struct CubeSize
{
	friend Archive& operator <<(Archive& ar, CubeSize& ob);
	friend Archive& operator >>(Archive& ar, CubeSize& ob);

	long nPag; // number of pages in the grid    (Nz)
	long nRow; // number of rows in the grid       (Ny)
	long nCol; // number of columns in the grid    (Nx)
	double xLL; // X coordinate of the lower left corner of the grid
	double yLL; // Y coordinate of the lower left corner of the grid
	double zLL; // Y coordinate of the lower left corner of the grid
	double xSize; // spacing between adjacent nodes in the X direction (between columns)
	double ySize; // spacing between adjacent nodes in the Y direction (between rows)
	double zSize; // spacing between adjacent nodes in the Z direction (between pages)

	double xMax()
	{
		return xLL + (nCol - 1) * xSize;
	}	
	double yMax()
	{
		return yLL + (nRow - 1) * ySize;
	}
	double zMax()
	{
		return zLL + (nPag - 1) * zSize;
	}
	CubeSize()
	{
		defined = false;
	}
	bool Defined(){return defined;}
	void Define(long npag,long nrow,long ncol,double xll,double yll,double zll,double xsize,double ysize,double zsize)
	{
		nPag	= npag; // number of columns in the grid    (Nz)
		nRow	= nrow; // number of rows in the grid       (Ny)
		nCol	= ncol; // number of columns in the grid    (Nx)
		xLL		= xll; // X coordinate of the lower left corner of the grid
		yLL		= yll; // Y coordinate of the lower left corner of the grid
		zLL		= zll; // Y coordinate of the lower left corner of the grid
		xSize	= xsize; // spacing between adjacent nodes in the X direction (between columns)
		ySize	= ysize; // spacing between adjacent nodes in the Y direction (between rows)
		zSize	= zsize; // spacing between adjacent nodes in the Y direction (between rows)
		defined = true;
	}
	void Define(CubeSize & cs)
	{
		nPag	= cs.nPag; // number of columns in the grid    (Nz)
		nRow	= cs.nRow; // number of rows in the grid       (Ny)
		nCol	= cs.nCol; // number of columns in the grid    (Nx)
		xLL		= cs.xLL; // X coordinate of the lower left corner of the grid
		yLL		= cs.yLL; // Y coordinate of the lower left corner of the grid
		zLL		= cs.zLL; // Y coordinate of the lower left corner of the grid
		xSize	= cs.xSize; // spacing between adjacent nodes in the X direction (between columns)
		ySize	= cs.ySize; // spacing between adjacent nodes in the Y direction (between rows)
		zSize	= cs.zSize; // spacing between adjacent nodes in the Y direction (between rows)
		defined = true;
	}

	void Printf();
	void Define(double minx, double miny, double minz, double maxx, double maxy, double maxz);
	void Undefine(){defined = false;}
private:
	bool defined;
	
};

typedef struct
{
	long nRow; // number of rows in the grid
	long nCol; // number of columns in the grid
	double xLL; // X coordinate of the lower left corner of the grid
	double yLL; // Y coordinate of the lower left corner of the grid
	double xSize; // spacing between adjacent nodes in the X direction (between columns)
	double ySize; // spacing between adjacent nodes in the Y direction (between rows)
	double zMin; // minimum Z value within the grid
	double zMax; // maximum Z value within the grid
	double Rotation; // not currently used
	double BlankValue; // nodes are blanked if greater or equal to this value
	double **z;
	bool InitSize(CubeSize & cube_size, short zflag)
	{
		if (cube_size.Defined())
		{
			switch(zflag)
			{
			case 3:
			case 0:
				{
					nRow		= cube_size.nRow; // number of rows in the grid       (Ny)
					nCol		= cube_size.nCol; // number of columns in the grid    (Nx)
					xLL			= cube_size.xLL; // X coordinate of the lower left corner of the grid
					yLL			= cube_size.yLL; // Y coordinate of the lower left corner of the grid
					xSize		= cube_size.xSize; // spacing between adjacent nodes in the X direction (between columns)
					ySize		= cube_size.ySize; // spacing between adjacent nodes in the Y direction (between rows)
				}
				break;
			case 1: // x - z
				{
					nRow		= cube_size.nRow; // number of rows in the grid       (Ny)
					nCol		= cube_size.nPag; // number of columns in the grid    (Nx)
					xLL			= cube_size.zLL; // X coordinate of the lower left corner of the grid
					yLL			= cube_size.yLL; // Y coordinate of the lower left corner of the grid
					xSize		= cube_size.zSize; // spacing between adjacent nodes in the X direction (between columns)
					ySize		= cube_size.ySize; // spacing between adjacent nodes in the Y direction (between rows)
				}
				break;
			case 2: // y - z
				{
					nRow		= cube_size.nPag; // number of rows in the grid       (Ny)
					nCol		= cube_size.nCol; // number of columns in the grid    (Nx)
					xLL			= cube_size.xLL; // X coordinate of the lower left corner of the grid
					yLL			= cube_size.zLL; // Y coordinate of the lower left corner of the grid
					xSize		= cube_size.xSize; // spacing between adjacent nodes in the X direction (between columns)
					ySize		= cube_size.zSize; // spacing between adjacent nodes in the Y direction (between rows)
				}
				break;
			default:
				return false;
			}
			Rotation	= 0; // not currently used
			BlankValue	= BLANK_VALUE; // nodes are blanked if greater or equal to this value
			return true;
		}
		return false;
	}
	bool IsTheSameSize(CubeSize & cube_size)
	{
		if (cube_size.Defined())
		{
			return 
				nRow		== cube_size.nRow  && // number of rows in the grid       (Ny)
				nCol		== cube_size.nCol  && // number of columns in the grid    (Nx)
				xLL			== cube_size.xLL   && // X coordinate of the lower left corner of the grid
				yLL			== cube_size.yLL   && // Y coordinate of the lower left corner of the grid
				xSize		== cube_size.xSize && // spacing between adjacent nodes in the X direction (between columns)
				ySize		== cube_size.ySize; // spacing between adjacent nodes in the Y direction (between rows)
		}
		return false;
	}
	bool IsTheSameSize(CubeSize & cube_size, double epsilon)
	{
		if (cube_size.Defined())
		{
			return 
				nRow		== cube_size.nRow  && // number of rows in the grid       (Ny)
				nCol		== cube_size.nCol  && // number of columns in the grid    (Nx)
				fabs(xLL-cube_size.xLL) < epsilon   && // X coordinate of the lower left corner of the grid
				fabs(yLL-cube_size.yLL) < epsilon   && // Y coordinate of the lower left corner of the grid
				fabs(xSize-cube_size.xSize) < epsilon && // spacing between adjacent nodes in the X direction (between columns)
				fabs(ySize-cube_size.ySize) < epsilon; // spacing between adjacent nodes in the Y direction (between rows)
		}
		return false;
	}
	void Printf()
	{
		cout << "GridSection::Printf()" << endl;
		cout << endl;
		cout << "nRow = " << nRow << endl;	
		cout << "nCol = " << nCol << endl;	
		cout << endl;
		cout << "xLL = " << xLL << endl;	
		cout << "yLL = " << yLL << endl;	
		cout << endl;
		cout << "xSize = " << xSize << endl;	
		cout << "ySize = " << ySize << endl;	
		cout << endl;
	}
}
SURFER7GRIDSECTION, FAR *LPSURFER7GRIDSECTION;
typedef struct
{
	long nPag; // number of columns in the grid    (Nz)
	long nRow; // number of rows in the grid       (Ny)
	long nCol; // number of columns in the grid    (Nx)
	double xLL; // X coordinate of the lower left corner of the grid
	double yLL; // Y coordinate of the lower left corner of the grid
	double zLL; // Y coordinate of the lower left corner of the grid
	double xSize; // spacing between adjacent nodes in the X direction (between columns)
	double ySize; // spacing between adjacent nodes in the Y direction (between rows)
	double zSize; // spacing between adjacent nodes in the Y direction (between rows)
	double vMin; // minimum V value within the grid
	double vMax; // maximum V value within the grid
	double Rotation; // not currently used
	double BlankValue; // nodes are blanked if greater or equal to this value
	double ***v;
	bool InitSize(CubeSize & cube_size)
	{
		if (cube_size.Defined())
		{
			nPag		= cube_size.nPag; // number of columns in the grid    (Nz)
			nRow		= cube_size.nRow; // number of rows in the grid       (Ny)
			nCol		= cube_size.nCol; // number of columns in the grid    (Nx)
			xLL			= cube_size.xLL; // X coordinate of the lower left corner of the grid
			yLL			= cube_size.yLL; // Y coordinate of the lower left corner of the grid
			zLL			= cube_size.zLL; // Y coordinate of the lower left corner of the grid
			xSize		= cube_size.xSize; // spacing between adjacent nodes in the X direction (between columns)
			ySize		= cube_size.ySize; // spacing between adjacent nodes in the Y direction (between rows)
			zSize		= cube_size.zSize; // spacing between adjacent nodes in the Y direction (between rows)
			Rotation	= 0; // not currently used
			BlankValue	= BLANK_VALUE; // nodes are blanked if greater or equal to this value
			return true;
		}
		return false;
	}
	bool IsTheSameSize(CubeSize & cube_size)
	{
		if (cube_size.Defined())
		{
			return 
				nPag		== cube_size.nPag  && // number of columns in the grid    (Nz)
				nRow		== cube_size.nRow  && // number of rows in the grid       (Ny)
				nCol		== cube_size.nCol  && // number of columns in the grid    (Nx)
				xLL			== cube_size.xLL   && // X coordinate of the lower left corner of the grid
				yLL			== cube_size.yLL   && // Y coordinate of the lower left corner of the grid
				zLL			== cube_size.zLL   && // Y coordinate of the lower left corner of the grid
				xSize		== cube_size.xSize && // spacing between adjacent nodes in the X direction (between columns)
				ySize		== cube_size.ySize && // spacing between adjacent nodes in the Y direction (between rows)
				zSize		== cube_size.zSize; // spacing between adjacent nodes in the Y direction (between rows)
		}
		return false;
	}
	void Printf()
	{
		cout << "Lattice::Printf()" << endl;
		cout << endl;
		cout << "nPag = " << nPag << endl;	
		cout << "nRow = " << nRow << endl;	
		cout << "nCol = " << nCol << endl;	
		cout << endl;
		cout << "xLL = " << xLL << endl;	
		cout << "yLL = " << yLL << endl;	
		cout << "zLL = " << zLL << endl;	
		cout << endl;
		cout << "xSize = " << xSize << endl;	
		cout << "ySize = " << ySize << endl;	
		cout << "zSize = " << zSize << endl;	
		cout << endl;
	}
}
SURFER7GRID4SECTION, FAR *LPSURFER7GRID4SECTION;

typedef struct
{
	double xLL; // X coordinate of the lower left corner of the grid
	double yLL; // Y coordinate of the lower left corner of the grid
	double zLL; // Y coordinate of the lower left corner of the grid
	double xSize; // spacing between adjacent nodes in the X direction (between columns)
	double ySize; // spacing between adjacent nodes in the Y direction (between rows)
	double zSize; // spacing between adjacent nodes in the Y direction (between rows)
}
SURFER7GRID4ZOOM, FAR *LPSURFER7GRID4ZOOM;
typedef struct
{
	//A Fault Info section describes the fault geometry used to create the grid. 
	//Fault Info sections have the following format:
	long nTraces;		//	number of fault traces (polylines)
	long nVertices;		//	total number of vertices in all the traces
	
	//data section
	//variable-sized data block consisting of an array of Trace structures 
	//immediately followed by the array of vertices
	// A Data section containing an array of Trace structures 
	//and an array of Vertex structures must immediately follow a Fault Info section. 
	//The number of Trace structures in the array is nTraces, 
	//and the number of Vertex structures is nVertices.


	// Trace structure:
	//	long iFirst			0-based index into the vertex array for the first vertex of this trace
	//	long nPts			number of vertices in this trace
	Trace * traces;


	//Vertex structure:
	//	double x			X coordinate of the vertex
	//	double y			Y coordinate of the vertex
	Vertex * vertexes;
}
SURFER7FAULTSECTION, FAR *LPSURFER7FAULTSECTION;
struct Grid
{
	SURFER7GRIDSECTION gridSection;
	SURFER7FAULTSECTION faultSection;
};
#define KEY_GRID_VERSION 2
struct key_grid
{
	long id_surf;
	BYTE podoshva;
	string key; //ключевое имя геоэлемента
	string surfname; //имя поверхности подошвы этого геоэлемента
	//Grid * grid;// грид подошвы геоэлемента
	key_grid()
	{
		surfname = "";
		key = "";
		//grid = NULL;
		id_surf = -1;
		podoshva = 0;
	}	
	key_grid(long _id_surf, BYTE _podoshva, const char * surf, const char * k)
	{
		id_surf = _id_surf;
		surfname = surf;
		key = k;
		//grid = NULL;
		podoshva = _podoshva;
	}
	key_grid(long _id_surf, BYTE _podoshva, string surf, string k)
	{
		id_surf = _id_surf;
		surfname = surf;
		key = k;
		//grid = NULL;
		podoshva = _podoshva;
	}
};
Archive& operator <<(Archive& ar, key_grid& ob);
Archive& operator >>(Archive& ar, key_grid& ob);

struct key_z
{
	string key;
	double z;
	key_z(const char * k, double Z)
	{
		key = k;
		z = Z;
	}
	key_z(string k, double Z)
	{
		key = k;
		z = Z;
	}
};
void FreeGrid(Grid* pgrid);
void FreeGrid(Grid & pgrid);
struct Grid4
{
	SURFER7GRID4SECTION grid4Section;
	SURFER7GRID4ZOOM grid4Zoom;
	//SURFER7FAULT3SECTION fault3Section;
};

Archive& operator <<(Archive& ar, Grid4& ob);
Archive& operator >>(Archive& ar, Grid4& ob);

int SaveAsSurferGrid7(HWND hWnd, LPCTSTR lpstrFile, 
					  long nRow, 
					  long nCol, 
					  double xLL, // X coordinate of the lower left corner of the grid
					  double yLL, // Y coordinate of the lower left corner of the grid
					  double xSize, // spacing between adjacent nodes in the X direction (between columns)
					  double ySize, // spacing between adjacent nodes in the Y direction (between rows)
					  double zMin, // minimum Z value within the grid
					  double zMax, // maximum Z value within the grid
					  double ** z, int ** visible);
int SaveAsSurferGrid7(HWND hWnd, LPCTSTR lpstrFile, vdouble& xi, vdouble& yi, vdouble& zi, vdouble& visible);
int ImportSurfer7Grid(char *file, Grid* pgrid, bool to_allocate = true);
int ImportSurfer7Grid4(char *file, Grid4* pgrid);
int ImportDigitalModel(Grid* pgrid,
	long nRow,
	long nCol,
	double xLL,
	double yLL,
	double xSize,
	double ySize,
	double zMin,
	double zMax);

int ImportDigitalModelHeader(long& nRow, long& nCol, double& xLeft, double& xRight, double& yLow, double& yHigh, double& zMin, double& zMax);

int SaveAsSurfer7Grid(const char *file, Grid* pgrid);
int SaveAsSurfer7Grid4(const char *file, Grid4* pgrid);
int SaveAsVTK(const char *file, Grid4* pgrid, bool view);

void UpdateExtremums(SURFER7GRIDSECTION & grid);
//#if !FAST_GRID_LOADING
class CGrid  
{
	vdouble 
		//x,y,z, //input data file vectors
		xi,yi,zi, visible, // grid vectors and matrices
		xc,yc; // contour bln data vectors
	friend class SurfDoc;
	friend class GridProfile3D;
public:
	double GetYMax();
	double GetYMin();
	double GetXMax();
	double GetXMin();
	HWND hwndParent;
	int SaveAsSurferGrid7( LPCTSTR lpstrFile);
	int SetVisiblePointsInContour();
	int ReadContourBlnFile();
	void Init(Grid* pGrid);
	CGrid();
	CGrid(HWND hwnd);
	virtual ~CGrid();

};

//#endif
#endif // !defined(AFX_GRID_H__68253D2E_C955_4BA1_8005_23D050633EB1__INCLUDED_)

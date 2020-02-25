#pragma once
enum crd_translation_mode
{
        crd_translation_mode_xyz = 0,
        crd_translation_mode_yz,
        crd_translation_mode_xz,
        crd_translation_mode_xy,
        crd_translation_mode_along_plane
};
class CrdTranslator
{
public:
	double a;
	double b;
	double c;
	double d;
	double minX;
	double minY;
	double minZ;
	double maxX;
	double maxY;
	double maxZ;



	crd_translation_mode m_crd_translation_mode;

	CrdTranslator()
	{
                m_crd_translation_mode = crd_translation_mode_xyz;
	}

	void DoTranslation(double x1, double y1, double z1, double& x2, double& y2, double& z2)
	{
		switch(m_crd_translation_mode)
		{
                case crd_translation_mode_xyz:
			DoTranslation_XYZ(x1, y1, z1, x2, y2, z2);
			break;
                case crd_translation_mode_yz:
			DoTranslation_YZ(x1, y1, z1, x2, y2, z2);
			break;
                case crd_translation_mode_xz:
			DoTranslation_XZ(x1, y1, z1, x2, y2, z2);
			break;
                case crd_translation_mode_xy:
			DoTranslation_XY(x1, y1, z1, x2, y2, z2);
			break;
                case crd_translation_mode_along_plane:
			DoTranslation_along_plane(x1, y1, z1, x2, y2, z2);
			break;
		}
	}
private:
	void DoTranslation_XYZ(double x1, double y1, double z1, double& x2, double& y2, double& z2)
	{
		x2 = x1;
		y2 = y1;
		z2 = z1;
	}
	void DoTranslation_YZ(double x1, double y1, double z1, double& x2, double& y2, double& z2)
	{
		x2 = y1;
		y2 = z1;
		z2 = 0.0;
	}
	void DoTranslation_XZ(double x1, double y1, double z1, double& x2, double& y2, double& z2)
	{
		x2 = x1;
		y2 = z1;
		z2 = 0.0;
	}
	void DoTranslation_XY(double x1, double y1, double z1, double& x2, double& y2, double& z2)
	{
		x2 = x1;
		y2 = y1;
		z2 = 0.0;
	}
	void DoTranslation_along_plane(double x1, double y1, double z1, double& x2, double& y2, double& z2)
	{
		// plane angle
		double cosinus = sqrt(a*a + b*b + c*c) / sqrt(a*a + b*b);
		double x0, y0; 
		{
			// запись bln файла в координатах плоскости сечения
			if (a != 0.0 && b != 0)
			{
				if(fabs(a) < fabs(b))
				{
					x0 = minX;
					y0 = - (
						a * x0 +
						c * minZ +
						d)
						/ b;
				}
				else
				{
					y0 = minY;
					x0 = - (
						b * y0 +
						c * minZ +
						d)
						/ a;
				}
			}
			else
			{
				if (a == 0.0 && b != 0)
				{
					x0 = minX;
					y0 = - (
						a * x0 +
						c * minZ +
						d)
						/ b;
				}
				if (a != 0.0 && b == 0)
				{
					y0 = minY;
					x0 = - (
						b * y0 +
						c * minZ +
						d)
						/ a;
				}
				if (a == 0.0 && b == 0)
				{
					y0 = minY;
					x0 = minX;
					
					x2 = x1;
					y2 = y1;
					z2 = 0.0;
				}
			}
			if(! (a == 0.0 && b == 0))
			{
				x2 = sqrt((x1 - x0)*(x1 - x0) + (y1 - y0)*(y1 - y0)); 					
				y2 = z1 * cosinus;
				z2 = 0.0;
			}
		}
	}
};
#include "../../tools/src/filedlg.h"
bool InitTranslator(CrdTranslator& translator, SSaveProfData &sprData);
bool InitTranslator(CrdTranslator& translator, SSaveProfData &sprData,
							double a, double b, double c, double d,
							double minX, double minY, double minZ,
							double maxX, double maxY, double maxZ);

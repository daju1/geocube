#include "..\..\surfdoc\src\points.h"
#include "v3d.h"

void calc_select_line(int mouse_x, int mouse_y, int height, //текущая высота окна.
					  CPoint3& p1, CPoint3& p2);
bool calc_select_line(int mouse_x, int mouse_y, int height, //текущая высота окна.
					  CPoint3& p3);

bool intersect_triangle_line(v3d<double>  v1, // вершины треугольника.
                             v3d<double>  v2,
                             v3d<double>  v3,
                             v3d<double>  n,  // нормаль треугольника.
                             v3d<double>  p1, // первый конец отрезка.
                             v3d<double>  p2, // второй конец отрезка.
                             v3d<double>& pc); // возвращаемая точка пересечения.
int f1_sgn(const double& k); // - функция, вычисляющая знак числа.

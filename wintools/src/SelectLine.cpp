#include "StdAfx.h"
#include "SelectLine.h"

#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>

//Автор: Курковский Александр 

//В этой статье я хочу ещё раз вернуться к проблеме выделения объектов 3D сцены 
//с помощью курсора мыши. Основная масса способов решения этой задачи основана 
//на вычислении так называемого селектирующего отрезка СО (или луча), проходящего 
//через точку наблюдения и координаты курсора мыши в мировой системе координат МСК. 
//После чего все объекты сцены тестируются на пересечение с этим отрезком и в 
//зависимости от результата тестирования - выделяются (например, окрашиваются 
//особым цветом). Наибольшие трудности обычно вызывает процесс перевода оконных 
//координат курсора в соответствующие ему мировые координаты, которые зависят от 
//текущих матриц преобразований (GL_MODELVIEW, GL_PROJECTION), текущих размеров 
//окна и параметров viewport-a (аргументов последней команды glViewport(...)). 

//Читая книгу [1] я наткнулся на очень простой и изящный способ решения этой задачи 
//в OpenGL приложении с помощью замечательной команды gluUnProject(...), 
//о существовании которой раньше я ничего не знал. Для тех, кто уже знаком с этой 
//командой, весь текст, приводимый далее, будет неинтересен. Для тех же, кто с ней 
//не знаком или не читал книгу [1], приведу куски кода, демонстрирующие использование 
//этой команды. 

//Итак, функция gluUnProject, прототип которой находится в файле glu.h имеет вид: 
/*
int APIENTRY gluUnProject (
    GLdouble       winx, 
    GLdouble       winy, 
    GLdouble       winz, 
    const GLdouble modelMatrix[16], 
    const GLdouble projMatrix[16], 
    const GLint    viewport[4], 
    GLdouble       *objx, 
    GLdouble       *objy, 
    GLdouble       *objz); 
	*/
//, где
//winx, winy - x,y координаты курсора мыши в системе координат viewport-a.
//winz - z координата курсора мыши. Задаётся в пределах -1..+1
//(-1 для ближней плоскости отсечения и +1 для дальней).
//modelMatrix - текущая матрица видового преобразования.
//projMatrix - текущая матрица проективного преобразования.
//viewport - текущие параметры viewport-a.
//objx,objy,objz - возвращаемые мировые координаты. 

//Далее приведу текст функции, которая по оконным координатам курсора 
//вычисляет мировые координаты концов селектирующего отрезка СО, который можно 
//использовать для выделения объектов сцены. 


void calc_select_line(int mouse_x, int mouse_y, int height, //текущая высота окна.
					  CPoint3& p1, CPoint3& p2)
{
  // mouse_x, mouse_y  - оконные координаты курсора мыши.
  // p1, p2            - возвращаемые параметры - концы селектирующего отрезка,
  //                     лежащие соответственно на ближней и дальней плоскостях
  //                     отсечения.
  GLint    viewport[4];    // параметры viewport-a.
  GLdouble projection[16]; // матрица проекции.
  GLdouble modelview[16];  // видовая матрица.
  GLdouble vx,vy,vz;       // координаты курсора мыши в системе координат viewport-a.
  GLdouble wx,wy,wz;       // возвращаемые мировые координаты.

  glGetIntegerv(GL_VIEWPORT,viewport);           // узнаём параметры viewport-a.
  glGetDoublev(GL_PROJECTION_MATRIX,projection); // узнаём матрицу проекции.
  glGetDoublev(GL_MODELVIEW_MATRIX,modelview);   // узнаём видовую матрицу.
  // переводим оконные координаты курсора в систему координат viewport-a.
  vx = mouse_x;
  vy = height - mouse_y - 1; // где height - текущая высота окна.

  // вычисляем ближний конец селектирующего отрезка.
  vz = -1;
  gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);
  p1 = CPoint3(wx,wy,wz);
  // вычисляем дальний конец селектирующего отрезка.
  vz = 1;
  gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);
  p2 = CPoint3(wx,wy,wz);
}

//Вот и всё! 
//Если Вам не требуется тестировать объекты сцены на пересечение с СО, 
//а лишь нужно узнать мировые координаты видимой точки поверхности объекта, 
//лежащей под курсором мыши, то в качестве параметра vz следует подставить 
//соответствующее данному пикселю значение буфера глубины. Узнать его можно при помощи команды: 
//	glReadPixels(vx, vy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &vz); 
bool calc_select_line(int mouse_x, int mouse_y, int height, //текущая высота окна.
					  CPoint3& p3)
{
  // mouse_x, mouse_y  - оконные координаты курсора мыши.
  // p1, p2            - возвращаемые параметры - концы селектирующего отрезка,
  //                     лежащие соответственно на ближней и дальней плоскостях
  //                     отсечения.
  GLint    viewport[4];    // параметры viewport-a.
  GLdouble projection[16]; // матрица проекции.
  GLdouble modelview[16];  // видовая матрица.
  GLdouble vx,vy;       // координаты курсора мыши в системе координат viewport-a.
  GLdouble wx,wy,wz;       // возвращаемые мировые координаты.

  glGetIntegerv(GL_VIEWPORT,viewport);           // узнаём параметры viewport-a.
  glGetDoublev(GL_PROJECTION_MATRIX,projection); // узнаём матрицу проекции.
  glGetDoublev(GL_MODELVIEW_MATRIX,modelview);   // узнаём видовую матрицу.
  // переводим оконные координаты курсора в систему координат viewport-a.
  vx = mouse_x;
  vy = height - mouse_y - 1; // где height - текущая высота окна.

  float VZ;

  glReadPixels(vx, vy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &VZ); 
printf("VZ = %f\n", VZ);
  gluUnProject(vx, vy, VZ, modelview, projection, viewport, &wx, &wy, &wz);
  p3 = CPoint3(wx,wy,wz);
  if (VZ == 1.0 || VZ == -1.0)
	  return false;
  else
	  return true;
}

//Если объект сцены состоит из треугольников, то для проверки пересечения 
//треугольника с СО можно воспользоватьс функцией: 

bool intersect_triangle_line(v3d<double>  v1, // вершины треугольника.
                             v3d<double>  v2,
                             v3d<double>  v3,
                             v3d<double>  n,  // нормаль треугольника.
                             v3d<double>  p1, // первый конец отрезка.
                             v3d<double>  p2, // второй конец отрезка.
                             v3d<double>& pc) // возвращаемая точка пересечения.
{
  // вычисляем расстояния между концами отрезка и плоскостью треугольника.
  //float r1 = n & (p1 - v1);
  //float r2 = n & (p2 - v1);
  double r1 = n.spr(p1 - v1);
  double r2 = n.spr(p2 - v1);
  // если оба конца отрезка лежат по одну сторону от плоскости, то отрезок
  // не пересекает треугольник.
  if( f1_sgn(r1) == f1_sgn(r2) ) return FALSE;
  // вычисляем точку пересечения отрезка с плоскостью треугольника.
  v3d<double> ip = (p1 + ((p2 - p1) * (-r1 / (r2 - r1))));
  // проверяем, находится ли точка пересечения внутри треугольника.
  //if( (((v2 - v1) ^ (ip - v1)) & n) <= 0) return FALSE; 
  //if( (((v3 - v2) ^ (ip - v2)) & n) <= 0) return FALSE;
  //if( (((v1 - v3) ^ (ip - v3)) & n) <= 0) return FALSE;
  if( (n.spr((v2 - v1).vpr(ip - v1)) ) <= 0) return FALSE; 
  if( (n.spr((v3 - v2).vpr(ip - v2)) ) <= 0) return FALSE;
  if( (n.spr((v1 - v3).vpr(ip - v3)) ) <= 0) return FALSE;
  pc = ip; return TRUE; 
}

//Здесь: 
//Операции с векторами " & " и " ^ " обозначают соответственно Dot Product и Cross Product. 
//C++ Копировать 

int f1_sgn(const double& k) // - функция, вычисляющая знак числа.
{
  if( k > 0 ) return 1;
  if( k < 0 ) return -1;
  return 0;
}
//Литература: 
//[1] - "OpenGL графика в проектах DELPHI" М.Краснов. (стр. 314)


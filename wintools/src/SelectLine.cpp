#include "StdAfx.h"
#include "SelectLine.h"

#include <gl\gl.h>
#include <gl\glu.h>
//#include <gl\glaux.h>

//�����: ���������� ��������� 

//� ���� ������ � ���� ��� ��� ��������� � �������� ��������� �������� 3D ����� 
//� ������� ������� ����. �������� ����� �������� ������� ���� ������ �������� 
//�� ���������� ��� ����������� �������������� ������� �� (��� ����), ����������� 
//����� ����� ���������� � ���������� ������� ���� � ������� ������� ��������� ���. 
//����� ���� ��� ������� ����� ����������� �� ����������� � ���� �������� � � 
//����������� �� ���������� ������������ - ���������� (��������, ������������ 
//������ ������). ���������� ��������� ������ �������� ������� �������� ������� 
//��������� ������� � ��������������� ��� ������� ����������, ������� ������� �� 
//������� ������ �������������� (GL_MODELVIEW, GL_PROJECTION), ������� �������� 
//���� � ���������� viewport-a (���������� ��������� ������� glViewport(...)). 

//����� ����� [1] � ��������� �� ����� ������� � ������� ������ ������� ���� ������ 
//� OpenGL ���������� � ������� ������������� ������� gluUnProject(...), 
//� ������������� ������� ������ � ������ �� ����. ��� ���, ��� ��� ������ � ���� 
//��������, ���� �����, ���������� �����, ����� �����������. ��� ��� ��, ��� � ��� 
//�� ������ ��� �� ����� ����� [1], ������� ����� ����, ��������������� ������������� 
//���� �������. 

//����, ������� gluUnProject, �������� ������� ��������� � ����� glu.h ����� ���: 
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
//, ���
//winx, winy - x,y ���������� ������� ���� � ������� ��������� viewport-a.
//winz - z ���������� ������� ����. ������� � �������� -1..+1
//(-1 ��� ������� ��������� ��������� � +1 ��� �������).
//modelMatrix - ������� ������� �������� ��������������.
//projMatrix - ������� ������� ������������ ��������������.
//viewport - ������� ��������� viewport-a.
//objx,objy,objz - ������������ ������� ����������. 

//����� ������� ����� �������, ������� �� ������� ����������� ������� 
//��������� ������� ���������� ������ �������������� ������� ��, ������� ����� 
//������������ ��� ��������� �������� �����. 


void calc_select_line(int mouse_x, int mouse_y, int height, //������� ������ ����.
					  CPoint3& p1, CPoint3& p2)
{
  // mouse_x, mouse_y  - ������� ���������� ������� ����.
  // p1, p2            - ������������ ��������� - ����� �������������� �������,
  //                     ������� �������������� �� ������� � ������� ����������
  //                     ���������.
  GLint    viewport[4];    // ��������� viewport-a.
  GLdouble projection[16]; // ������� ��������.
  GLdouble modelview[16];  // ������� �������.
  GLdouble vx,vy,vz;       // ���������� ������� ���� � ������� ��������� viewport-a.
  GLdouble wx,wy,wz;       // ������������ ������� ����������.

  glGetIntegerv(GL_VIEWPORT,viewport);           // ����� ��������� viewport-a.
  glGetDoublev(GL_PROJECTION_MATRIX,projection); // ����� ������� ��������.
  glGetDoublev(GL_MODELVIEW_MATRIX,modelview);   // ����� ������� �������.
  // ��������� ������� ���������� ������� � ������� ��������� viewport-a.
  vx = mouse_x;
  vy = height - mouse_y - 1; // ��� height - ������� ������ ����.

  // ��������� ������� ����� �������������� �������.
  vz = -1;
  gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);
  p1 = CPoint3(wx,wy,wz);
  // ��������� ������� ����� �������������� �������.
  vz = 1;
  gluUnProject(vx, vy, vz, modelview, projection, viewport, &wx, &wy, &wz);
  p2 = CPoint3(wx,wy,wz);
}

//��� � ��! 
//���� ��� �� ��������� ����������� ������� ����� �� ����������� � ��, 
//� ���� ����� ������ ������� ���������� ������� ����� ����������� �������, 
//������� ��� �������� ����, �� � �������� ��������� vz ������� ���������� 
//��������������� ������� ������� �������� ������ �������. ������ ��� ����� ��� ������ �������: 
//	glReadPixels(vx, vy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &vz); 
bool calc_select_line(int mouse_x, int mouse_y, int height, //������� ������ ����.
					  CPoint3& p3)
{
  // mouse_x, mouse_y  - ������� ���������� ������� ����.
  // p1, p2            - ������������ ��������� - ����� �������������� �������,
  //                     ������� �������������� �� ������� � ������� ����������
  //                     ���������.
  GLint    viewport[4];    // ��������� viewport-a.
  GLdouble projection[16]; // ������� ��������.
  GLdouble modelview[16];  // ������� �������.
  GLdouble vx,vy;       // ���������� ������� ���� � ������� ��������� viewport-a.
  GLdouble wx,wy,wz;       // ������������ ������� ����������.

  glGetIntegerv(GL_VIEWPORT,viewport);           // ����� ��������� viewport-a.
  glGetDoublev(GL_PROJECTION_MATRIX,projection); // ����� ������� ��������.
  glGetDoublev(GL_MODELVIEW_MATRIX,modelview);   // ����� ������� �������.
  // ��������� ������� ���������� ������� � ������� ��������� viewport-a.
  vx = mouse_x;
  vy = height - mouse_y - 1; // ��� height - ������� ������ ����.

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

//���� ������ ����� ������� �� �������������, �� ��� �������� ����������� 
//������������ � �� ����� �������������� ��������: 

bool intersect_triangle_line(v3d<double>  v1, // ������� ������������.
                             v3d<double>  v2,
                             v3d<double>  v3,
                             v3d<double>  n,  // ������� ������������.
                             v3d<double>  p1, // ������ ����� �������.
                             v3d<double>  p2, // ������ ����� �������.
                             v3d<double>& pc) // ������������ ����� �����������.
{
  // ��������� ���������� ����� ������� ������� � ���������� ������������.
  //float r1 = n & (p1 - v1);
  //float r2 = n & (p2 - v1);
  double r1 = n.spr(p1 - v1);
  double r2 = n.spr(p2 - v1);
  // ���� ��� ����� ������� ����� �� ���� ������� �� ���������, �� �������
  // �� ���������� �����������.
  if( f1_sgn(r1) == f1_sgn(r2) ) return FALSE;
  // ��������� ����� ����������� ������� � ���������� ������������.
  v3d<double> ip = (p1 + ((p2 - p1) * (-r1 / (r2 - r1))));
  // ���������, ��������� �� ����� ����������� ������ ������������.
  //if( (((v2 - v1) ^ (ip - v1)) & n) <= 0) return FALSE; 
  //if( (((v3 - v2) ^ (ip - v2)) & n) <= 0) return FALSE;
  //if( (((v1 - v3) ^ (ip - v3)) & n) <= 0) return FALSE;
  if( (n.spr((v2 - v1).vpr(ip - v1)) ) <= 0) return FALSE; 
  if( (n.spr((v3 - v2).vpr(ip - v2)) ) <= 0) return FALSE;
  if( (n.spr((v1 - v3).vpr(ip - v3)) ) <= 0) return FALSE;
  pc = ip; return TRUE; 
}

//�����: 
//�������� � ��������� " & " � " ^ " ���������� �������������� Dot Product � Cross Product. 
//C++ ���������� 

int f1_sgn(const double& k) // - �������, ����������� ���� �����.
{
  if( k > 0 ) return 1;
  if( k < 0 ) return -1;
  return 0;
}
//����������: 
//[1] - "OpenGL ������� � �������� DELPHI" �.�������. (���. 314)


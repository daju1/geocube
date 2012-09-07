#include "StdAfx.h"
#include "iso.h"
#include "..\..\commonOG.h"
#include "../../array/src/matrixes.h"

void getNorm(double v1[3], double v2[3], double out[3]);
// пример marching cubes algorithm
// это лишь фрагмент кода, демонстрирующий собственно алгоритм
// этот фрагмент НЕ скомпилируется самостоятельно
/*
// 3D точка
typedef struct {
  double x, y, z;
} xyz;

// 3D треугольник
typedef struct {
   xyz p[3];
} TRIANGLE;

// 3D кубик (ячейка)
typedef struct {
   xyz p[8];      // координаты вершин кубика
   double val[8]; // значения функции в вершинах
} GRIDCELL;
*/
// таблица номеров пересекающихся с изоповерхностью ребер
// i-й бит в j-м элементе соответствует i-му ребру для j-й конфигурации
//   вершин (т.е. j-му расположению вершин относительно изоповерхности)
int edgeTable[256] = {
  0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
  0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
  0x190, 0x99 , 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
  0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
  0x230, 0x339, 0x33 , 0x13a, 0x636, 0x73f, 0x435, 0x53c,
  0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
  0x3a0, 0x2a9, 0x1a3, 0xaa , 0x7a6, 0x6af, 0x5a5, 0x4ac,
  0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
  0x460, 0x569, 0x663, 0x76a, 0x66 , 0x16f, 0x265, 0x36c,
  0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
  0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0xff , 0x3f5, 0x2fc,
  0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
  0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x55 , 0x15c,
  0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
  0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0xcc ,
  0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
  0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
  0xcc , 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
  0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
  0x15c, 0x55 , 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
  0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
  0x2fc, 0x3f5, 0xff , 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
  0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
  0x36c, 0x265, 0x16f, 0x66 , 0x76a, 0x663, 0x569, 0x460,
  0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
  0x4ac, 0x5a5, 0x6af, 0x7a6, 0xaa , 0x1a3, 0x2a9, 0x3a0,
  0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
  0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x33 , 0x339, 0x230,
  0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
  0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x99 , 0x190,
  0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
  0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x0   
};

// таблица номеров вершин генерируемых граней
int triTable[256][16] = {
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 2, 10, 0, 2, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {2, 8, 3, 2, 10, 8, 10, 9, 8, -1, -1, -1, -1, -1, -1, -1},
  {3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 11, 2, 8, 11, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 9, 0, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 11, 2, 1, 9, 11, 9, 8, 11, -1, -1, -1, -1, -1, -1, -1},
  {3, 10, 1, 11, 10, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 10, 1, 0, 8, 10, 8, 11, 10, -1, -1, -1, -1, -1, -1, -1},
  {3, 9, 0, 3, 11, 9, 11, 10, 9, -1, -1, -1, -1, -1, -1, -1},
  {9, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 3, 0, 7, 3, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, 9, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 1, 9, 4, 7, 1, 7, 3, 1, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 10, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 4, 7, 3, 0, 4, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1},
  {9, 2, 10, 9, 0, 2, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
  {2, 10, 9, 2, 9, 7, 2, 7, 3, 7, 9, 4, -1, -1, -1, -1},
  {8, 4, 7, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {11, 4, 7, 11, 2, 4, 2, 0, 4, -1, -1, -1, -1, -1, -1, -1},
  {9, 0, 1, 8, 4, 7, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
  {4, 7, 11, 9, 4, 11, 9, 11, 2, 9, 2, 1, -1, -1, -1, -1},
  {3, 10, 1, 3, 11, 10, 7, 8, 4, -1, -1, -1, -1, -1, -1, -1},
  {1, 11, 10, 1, 4, 11, 1, 0, 4, 7, 11, 4, -1, -1, -1, -1},
  {4, 7, 8, 9, 0, 11, 9, 11, 10, 11, 0, 3, -1, -1, -1, -1},
  {4, 7, 11, 4, 11, 9, 9, 11, 10, -1, -1, -1, -1, -1, -1, -1},
  {9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 5, 4, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 5, 4, 1, 5, 0, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {8, 5, 4, 8, 3, 5, 3, 1, 5, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 10, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 0, 8, 1, 2, 10, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
  {5, 2, 10, 5, 4, 2, 4, 0, 2, -1, -1, -1, -1, -1, -1, -1},
  {2, 10, 5, 3, 2, 5, 3, 5, 4, 3, 4, 8, -1, -1, -1, -1},
  {9, 5, 4, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 11, 2, 0, 8, 11, 4, 9, 5, -1, -1, -1, -1, -1, -1, -1},
  {0, 5, 4, 0, 1, 5, 2, 3, 11, -1, -1, -1, -1, -1, -1, -1},
  {2, 1, 5, 2, 5, 8, 2, 8, 11, 4, 8, 5, -1, -1, -1, -1},
  {10, 3, 11, 10, 1, 3, 9, 5, 4, -1, -1, -1, -1, -1, -1, -1},
  {4, 9, 5, 0, 8, 1, 8, 10, 1, 8, 11, 10, -1, -1, -1, -1},
  {5, 4, 0, 5, 0, 11, 5, 11, 10, 11, 0, 3, -1, -1, -1, -1},
  {5, 4, 8, 5, 8, 10, 10, 8, 11, -1, -1, -1, -1, -1, -1, -1},
  {9, 7, 8, 5, 7, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 3, 0, 9, 5, 3, 5, 7, 3, -1, -1, -1, -1, -1, -1, -1},
  {0, 7, 8, 0, 1, 7, 1, 5, 7, -1, -1, -1, -1, -1, -1, -1},
  {1, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 7, 8, 9, 5, 7, 10, 1, 2, -1, -1, -1, -1, -1, -1, -1},
  {10, 1, 2, 9, 5, 0, 5, 3, 0, 5, 7, 3, -1, -1, -1, -1},
  {8, 0, 2, 8, 2, 5, 8, 5, 7, 10, 5, 2, -1, -1, -1, -1},
  {2, 10, 5, 2, 5, 3, 3, 5, 7, -1, -1, -1, -1, -1, -1, -1},
  {7, 9, 5, 7, 8, 9, 3, 11, 2, -1, -1, -1, -1, -1, -1, -1},
  {9, 5, 7, 9, 7, 2, 9, 2, 0, 2, 7, 11, -1, -1, -1, -1},
  {2, 3, 11, 0, 1, 8, 1, 7, 8, 1, 5, 7, -1, -1, -1, -1},
  {11, 2, 1, 11, 1, 7, 7, 1, 5, -1, -1, -1, -1, -1, -1, -1},
  {9, 5, 8, 8, 5, 7, 10, 1, 3, 10, 3, 11, -1, -1, -1, -1},
  {5, 7, 0, 5, 0, 9, 7, 11, 0, 1, 0, 10, 11, 10, 0, -1},
  {11, 10, 0, 11, 0, 3, 10, 5, 0, 8, 0, 7, 5, 7, 0, -1},
  {11, 10, 5, 7, 11, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 3, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 0, 1, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 8, 3, 1, 9, 8, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
  {1, 6, 5, 2, 6, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 6, 5, 1, 2, 6, 3, 0, 8, -1, -1, -1, -1, -1, -1, -1},
  {9, 6, 5, 9, 0, 6, 0, 2, 6, -1, -1, -1, -1, -1, -1, -1},
  {5, 9, 8, 5, 8, 2, 5, 2, 6, 3, 2, 8, -1, -1, -1, -1},
  {2, 3, 11, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {11, 0, 8, 11, 2, 0, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, 9, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1, -1, -1, -1},
  {5, 10, 6, 1, 9, 2, 9, 11, 2, 9, 8, 11, -1, -1, -1, -1},
  {6, 3, 11, 6, 5, 3, 5, 1, 3, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 11, 0, 11, 5, 0, 5, 1, 5, 11, 6, -1, -1, -1, -1},
  {3, 11, 6, 0, 3, 6, 0, 6, 5, 0, 5, 9, -1, -1, -1, -1},
  {6, 5, 9, 6, 9, 11, 11, 9, 8, -1, -1, -1, -1, -1, -1, -1},
  {5, 10, 6, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 3, 0, 4, 7, 3, 6, 5, 10, -1, -1, -1, -1, -1, -1, -1},
  {1, 9, 0, 5, 10, 6, 8, 4, 7, -1, -1, -1, -1, -1, -1, -1},
  {10, 6, 5, 1, 9, 7, 1, 7, 3, 7, 9, 4, -1, -1, -1, -1},
  {6, 1, 2, 6, 5, 1, 4, 7, 8, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 5, 5, 2, 6, 3, 0, 4, 3, 4, 7, -1, -1, -1, -1},
  {8, 4, 7, 9, 0, 5, 0, 6, 5, 0, 2, 6, -1, -1, -1, -1},
  {7, 3, 9, 7, 9, 4, 3, 2, 9, 5, 9, 6, 2, 6, 9, -1},
  {3, 11, 2, 7, 8, 4, 10, 6, 5, -1, -1, -1, -1, -1, -1, -1},
  {5, 10, 6, 4, 7, 2, 4, 2, 0, 2, 7, 11, -1, -1, -1, -1},
  {0, 1, 9, 4, 7, 8, 2, 3, 11, 5, 10, 6, -1, -1, -1, -1},
  {9, 2, 1, 9, 11, 2, 9, 4, 11, 7, 11, 4, 5, 10, 6, -1},
  {8, 4, 7, 3, 11, 5, 3, 5, 1, 5, 11, 6, -1, -1, -1, -1},
  {5, 1, 11, 5, 11, 6, 1, 0, 11, 7, 11, 4, 0, 4, 11, -1},
  {0, 5, 9, 0, 6, 5, 0, 3, 6, 11, 6, 3, 8, 4, 7, -1},
  {6, 5, 9, 6, 9, 11, 4, 7, 9, 7, 11, 9, -1, -1, -1, -1},
  {10, 4, 9, 6, 4, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 10, 6, 4, 9, 10, 0, 8, 3, -1, -1, -1, -1, -1, -1, -1},
  {10, 0, 1, 10, 6, 0, 6, 4, 0, -1, -1, -1, -1, -1, -1, -1},
  {8, 3, 1, 8, 1, 6, 8, 6, 4, 6, 1, 10, -1, -1, -1, -1},
  {1, 4, 9, 1, 2, 4, 2, 6, 4, -1, -1, -1, -1, -1, -1, -1},
  {3, 0, 8, 1, 2, 9, 2, 4, 9, 2, 6, 4, -1, -1, -1, -1},
  {0, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {8, 3, 2, 8, 2, 4, 4, 2, 6, -1, -1, -1, -1, -1, -1, -1},
  {10, 4, 9, 10, 6, 4, 11, 2, 3, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 2, 2, 8, 11, 4, 9, 10, 4, 10, 6, -1, -1, -1, -1},
  {3, 11, 2, 0, 1, 6, 0, 6, 4, 6, 1, 10, -1, -1, -1, -1},
  {6, 4, 1, 6, 1, 10, 4, 8, 1, 2, 1, 11, 8, 11, 1, -1},
  {9, 6, 4, 9, 3, 6, 9, 1, 3, 11, 6, 3, -1, -1, -1, -1},
  {8, 11, 1, 8, 1, 0, 11, 6, 1, 9, 1, 4, 6, 4, 1, -1},
  {3, 11, 6, 3, 6, 0, 0, 6, 4, -1, -1, -1, -1, -1, -1, -1},
  {6, 4, 8, 11, 6, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {7, 10, 6, 7, 8, 10, 8, 9, 10, -1, -1, -1, -1, -1, -1, -1},
  {0, 7, 3, 0, 10, 7, 0, 9, 10, 6, 7, 10, -1, -1, -1, -1},
  {10, 6, 7, 1, 10, 7, 1, 7, 8, 1, 8, 0, -1, -1, -1, -1},
  {10, 6, 7, 10, 7, 1, 1, 7, 3, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 6, 1, 6, 8, 1, 8, 9, 8, 6, 7, -1, -1, -1, -1},
  {2, 6, 9, 2, 9, 1, 6, 7, 9, 0, 9, 3, 7, 3, 9, -1},
  {7, 8, 0, 7, 0, 6, 6, 0, 2, -1, -1, -1, -1, -1, -1, -1},
  {7, 3, 2, 6, 7, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {2, 3, 11, 10, 6, 8, 10, 8, 9, 8, 6, 7, -1, -1, -1, -1},
  {2, 0, 7, 2, 7, 11, 0, 9, 7, 6, 7, 10, 9, 10, 7, -1},
  {1, 8, 0, 1, 7, 8, 1, 10, 7, 6, 7, 10, 2, 3, 11, -1},
  {11, 2, 1, 11, 1, 7, 10, 6, 1, 6, 7, 1, -1, -1, -1, -1},
  {8, 9, 6, 8, 6, 7, 9, 1, 6, 11, 6, 3, 1, 3, 6, -1},
  {0, 9, 1, 11, 6, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {7, 8, 0, 7, 0, 6, 3, 11, 0, 11, 6, 0, -1, -1, -1, -1},
  {7, 11, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 0, 8, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, 9, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {8, 1, 9, 8, 3, 1, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
  {10, 1, 2, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 10, 3, 0, 8, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
  {2, 9, 0, 2, 10, 9, 6, 11, 7, -1, -1, -1, -1, -1, -1, -1},
  {6, 11, 7, 2, 10, 3, 10, 8, 3, 10, 9, 8, -1, -1, -1, -1},
  {7, 2, 3, 6, 2, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {7, 0, 8, 7, 6, 0, 6, 2, 0, -1, -1, -1, -1, -1, -1, -1},
  {2, 7, 6, 2, 3, 7, 0, 1, 9, -1, -1, -1, -1, -1, -1, -1},
  {1, 6, 2, 1, 8, 6, 1, 9, 8, 8, 7, 6, -1, -1, -1, -1},
  {10, 7, 6, 10, 1, 7, 1, 3, 7, -1, -1, -1, -1, -1, -1, -1},
  {10, 7, 6, 1, 7, 10, 1, 8, 7, 1, 0, 8, -1, -1, -1, -1},
  {0, 3, 7, 0, 7, 10, 0, 10, 9, 6, 10, 7, -1, -1, -1, -1},
  {7, 6, 10, 7, 10, 8, 8, 10, 9, -1, -1, -1, -1, -1, -1, -1},
  {6, 8, 4, 11, 8, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 6, 11, 3, 0, 6, 0, 4, 6, -1, -1, -1, -1, -1, -1, -1},
  {8, 6, 11, 8, 4, 6, 9, 0, 1, -1, -1, -1, -1, -1, -1, -1},
  {9, 4, 6, 9, 6, 3, 9, 3, 1, 11, 3, 6, -1, -1, -1, -1},
  {6, 8, 4, 6, 11, 8, 2, 10, 1, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 10, 3, 0, 11, 0, 6, 11, 0, 4, 6, -1, -1, -1, -1},
  {4, 11, 8, 4, 6, 11, 0, 2, 9, 2, 10, 9, -1, -1, -1, -1},
  {10, 9, 3, 10, 3, 2, 9, 4, 3, 11, 3, 6, 4, 6, 3, -1},
  {8, 2, 3, 8, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1},
  {0, 4, 2, 4, 6, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 9, 0, 2, 3, 4, 2, 4, 6, 4, 3, 8, -1, -1, -1, -1},
  {1, 9, 4, 1, 4, 2, 2, 4, 6, -1, -1, -1, -1, -1, -1, -1},
  {8, 1, 3, 8, 6, 1, 8, 4, 6, 6, 10, 1, -1, -1, -1, -1},
  {10, 1, 0, 10, 0, 6, 6, 0, 4, -1, -1, -1, -1, -1, -1, -1},
  {4, 6, 3, 4, 3, 8, 6, 10, 3, 0, 3, 9, 10, 9, 3, -1},
  {10, 9, 4, 6, 10, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 9, 5, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 3, 4, 9, 5, 11, 7, 6, -1, -1, -1, -1, -1, -1, -1},
  {5, 0, 1, 5, 4, 0, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
  {11, 7, 6, 8, 3, 4, 3, 5, 4, 3, 1, 5, -1, -1, -1, -1},
  {9, 5, 4, 10, 1, 2, 7, 6, 11, -1, -1, -1, -1, -1, -1, -1},
  {6, 11, 7, 1, 2, 10, 0, 8, 3, 4, 9, 5, -1, -1, -1, -1},
  {7, 6, 11, 5, 4, 10, 4, 2, 10, 4, 0, 2, -1, -1, -1, -1},
  {3, 4, 8, 3, 5, 4, 3, 2, 5, 10, 5, 2, 11, 7, 6, -1},
  {7, 2, 3, 7, 6, 2, 5, 4, 9, -1, -1, -1, -1, -1, -1, -1},
  {9, 5, 4, 0, 8, 6, 0, 6, 2, 6, 8, 7, -1, -1, -1, -1},
  {3, 6, 2, 3, 7, 6, 1, 5, 0, 5, 4, 0, -1, -1, -1, -1},
  {6, 2, 8, 6, 8, 7, 2, 1, 8, 4, 8, 5, 1, 5, 8, -1},
  {9, 5, 4, 10, 1, 6, 1, 7, 6, 1, 3, 7, -1, -1, -1, -1},
  {1, 6, 10, 1, 7, 6, 1, 0, 7, 8, 7, 0, 9, 5, 4, -1},
  {4, 0, 10, 4, 10, 5, 0, 3, 10, 6, 10, 7, 3, 7, 10, -1},
  {7, 6, 10, 7, 10, 8, 5, 4, 10, 4, 8, 10, -1, -1, -1, -1},
  {6, 9, 5, 6, 11, 9, 11, 8, 9, -1, -1, -1, -1, -1, -1, -1},
  {3, 6, 11, 0, 6, 3, 0, 5, 6, 0, 9, 5, -1, -1, -1, -1},
  {0, 11, 8, 0, 5, 11, 0, 1, 5, 5, 6, 11, -1, -1, -1, -1},
  {6, 11, 3, 6, 3, 5, 5, 3, 1, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 10, 9, 5, 11, 9, 11, 8, 11, 5, 6, -1, -1, -1, -1},
  {0, 11, 3, 0, 6, 11, 0, 9, 6, 5, 6, 9, 1, 2, 10, -1},
  {11, 8, 5, 11, 5, 6, 8, 0, 5, 10, 5, 2, 0, 2, 5, -1},
  {6, 11, 3, 6, 3, 5, 2, 10, 3, 10, 5, 3, -1, -1, -1, -1},
  {5, 8, 9, 5, 2, 8, 5, 6, 2, 3, 8, 2, -1, -1, -1, -1},
  {9, 5, 6, 9, 6, 0, 0, 6, 2, -1, -1, -1, -1, -1, -1, -1},
  {1, 5, 8, 1, 8, 0, 5, 6, 8, 3, 8, 2, 6, 2, 8, -1},
  {1, 5, 6, 2, 1, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 3, 6, 1, 6, 10, 3, 8, 6, 5, 6, 9, 8, 9, 6, -1},
  {10, 1, 0, 10, 0, 6, 9, 5, 0, 5, 6, 0, -1, -1, -1, -1},
  {0, 3, 8, 5, 6, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {10, 5, 6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {11, 5, 10, 7, 5, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {11, 5, 10, 11, 7, 5, 8, 3, 0, -1, -1, -1, -1, -1, -1, -1},
  {5, 11, 7, 5, 10, 11, 1, 9, 0, -1, -1, -1, -1, -1, -1, -1},
  {10, 7, 5, 10, 11, 7, 9, 8, 1, 8, 3, 1, -1, -1, -1, -1},
  {11, 1, 2, 11, 7, 1, 7, 5, 1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 3, 1, 2, 7, 1, 7, 5, 7, 2, 11, -1, -1, -1, -1},
  {9, 7, 5, 9, 2, 7, 9, 0, 2, 2, 11, 7, -1, -1, -1, -1},
  {7, 5, 2, 7, 2, 11, 5, 9, 2, 3, 2, 8, 9, 8, 2, -1},
  {2, 5, 10, 2, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1},
  {8, 2, 0, 8, 5, 2, 8, 7, 5, 10, 2, 5, -1, -1, -1, -1},
  {9, 0, 1, 5, 10, 3, 5, 3, 7, 3, 10, 2, -1, -1, -1, -1},
  {9, 8, 2, 9, 2, 1, 8, 7, 2, 10, 2, 5, 7, 5, 2, -1},
  {1, 3, 5, 3, 7, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 7, 0, 7, 1, 1, 7, 5, -1, -1, -1, -1, -1, -1, -1},
  {9, 0, 3, 9, 3, 5, 5, 3, 7, -1, -1, -1, -1, -1, -1, -1},
  {9, 8, 7, 5, 9, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {5, 8, 4, 5, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1},
  {5, 0, 4, 5, 11, 0, 5, 10, 11, 11, 3, 0, -1, -1, -1, -1},
  {0, 1, 9, 8, 4, 10, 8, 10, 11, 10, 4, 5, -1, -1, -1, -1},
  {10, 11, 4, 10, 4, 5, 11, 3, 4, 9, 4, 1, 3, 1, 4, -1},
  {2, 5, 1, 2, 8, 5, 2, 11, 8, 4, 5, 8, -1, -1, -1, -1},
  {0, 4, 11, 0, 11, 3, 4, 5, 11, 2, 11, 1, 5, 1, 11, -1},
  {0, 2, 5, 0, 5, 9, 2, 11, 5, 4, 5, 8, 11, 8, 5, -1},
  {9, 4, 5, 2, 11, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {2, 5, 10, 3, 5, 2, 3, 4, 5, 3, 8, 4, -1, -1, -1, -1},
  {5, 10, 2, 5, 2, 4, 4, 2, 0, -1, -1, -1, -1, -1, -1, -1},
  {3, 10, 2, 3, 5, 10, 3, 8, 5, 4, 5, 8, 0, 1, 9, -1},
  {5, 10, 2, 5, 2, 4, 1, 9, 2, 9, 4, 2, -1, -1, -1, -1},
  {8, 4, 5, 8, 5, 3, 3, 5, 1, -1, -1, -1, -1, -1, -1, -1},
  {0, 4, 5, 1, 0, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {8, 4, 5, 8, 5, 3, 9, 0, 5, 0, 3, 5, -1, -1, -1, -1},
  {9, 4, 5, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 11, 7, 4, 9, 11, 9, 10, 11, -1, -1, -1, -1, -1, -1, -1},
  {0, 8, 3, 4, 9, 7, 9, 11, 7, 9, 10, 11, -1, -1, -1, -1},
  {1, 10, 11, 1, 11, 4, 1, 4, 0, 7, 4, 11, -1, -1, -1, -1},
  {3, 1, 4, 3, 4, 8, 1, 10, 4, 7, 4, 11, 10, 11, 4, -1},
  {4, 11, 7, 9, 11, 4, 9, 2, 11, 9, 1, 2, -1, -1, -1, -1},
  {9, 7, 4, 9, 11, 7, 9, 1, 11, 2, 11, 1, 0, 8, 3, -1},
  {11, 7, 4, 11, 4, 2, 2, 4, 0, -1, -1, -1, -1, -1, -1, -1},
  {11, 7, 4, 11, 4, 2, 8, 3, 4, 3, 2, 4, -1, -1, -1, -1},
  {2, 9, 10, 2, 7, 9, 2, 3, 7, 7, 4, 9, -1, -1, -1, -1},
  {9, 10, 7, 9, 7, 4, 10, 2, 7, 8, 7, 0, 2, 0, 7, -1},
  {3, 7, 10, 3, 10, 2, 7, 4, 10, 1, 10, 0, 4, 0, 10, -1},
  {1, 10, 2, 8, 7, 4, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 9, 1, 4, 1, 7, 7, 1, 3, -1, -1, -1, -1, -1, -1, -1},
  {4, 9, 1, 4, 1, 7, 0, 8, 1, 8, 7, 1, -1, -1, -1, -1},
  {4, 0, 3, 7, 4, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {4, 8, 7, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {9, 10, 8, 10, 11, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 0, 9, 3, 9, 11, 11, 9, 10, -1, -1, -1, -1, -1, -1, -1},
  {0, 1, 10, 0, 10, 8, 8, 10, 11, -1, -1, -1, -1, -1, -1, -1},
  {3, 1, 10, 11, 3, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 2, 11, 1, 11, 9, 9, 11, 8, -1, -1, -1, -1, -1, -1, -1},
  {3, 0, 9, 3, 9, 11, 1, 2, 9, 2, 11, 9, -1, -1, -1, -1},
  {0, 2, 11, 8, 0, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {3, 2, 11, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {2, 3, 8, 2, 8, 10, 10, 8, 9, -1, -1, -1, -1, -1, -1, -1},
  {9, 10, 2, 0, 9, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {2, 3, 8, 2, 8, 10, 0, 1, 8, 1, 10, 8, -1, -1, -1, -1},
  {1, 10, 2, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {1, 3, 8, 9, 1, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 9, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {0, 3, 8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
  {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

// линейная интерполяция - поиск точки пересечения ребра и изоповерхности
// isolevel - изоуровень
// p1, p2 - начало и конец ребра
// valp1, valp2 - соответствующие им значения функции

CPoint3 VertexInterp(double isolevel, CPoint3 &p1, CPoint3 &p2, double valp1, double valp2) {
  double mu;
  CPoint3 p;

  // точка пересечения совпадает с p1?
  if (fabs(isolevel - valp1) < 0.00001)
    return(p1);

  // точка пересечения совпадает с p2?
  if (fabs(isolevel - valp2) < 0.00001)
    return(p2);

  // значение функции не меняется на всем отрезке?
  if (fabs(valp1 - valp2) < 0.00001)
    return(p1);

  // собственно линейная интерполяция
  mu = (isolevel - valp1) / (valp2 - valp1);
  p.x = p1.x + mu * (p2.x - p1.x);
  p.y = p1.y + mu * (p2.y - p1.y);
  p.z = p1.z + mu * (p2.z - p1.z);

  return(p);
}

CPoint3 VertexInterp(double isolevel, Grid4 * cube, 
				  long nx1, long ny1, long nz1, 
				  long nx2, long ny2, long nz2, bool view
				  )
{
	double valp1 = cube->grid4Section.v[nz1][ny1][nx1];
	double valp2 = cube->grid4Section.v[nz2][ny2][nx2];
	// собственно линейная интерполяция
	double mu;
	CPoint3 p;
/*
*/

	double x1,x2, y1,y2, z1,z2;
	if (view)
	{
		x1 = cube->grid4Zoom.xLL + nx1 * cube->grid4Zoom.xSize;
		x2 = cube->grid4Zoom.xLL + nx2 * cube->grid4Zoom.xSize;
		
		y1 = cube->grid4Zoom.yLL + ny1 * cube->grid4Zoom.ySize;
		y2 = cube->grid4Zoom.yLL + ny2 * cube->grid4Zoom.ySize;
		
		z1 = cube->grid4Zoom.zLL + nz1 * cube->grid4Zoom.zSize;
		z2 = cube->grid4Zoom.zLL + nz2 * cube->grid4Zoom.zSize;
	}
	else
	{
		x1 = cube->grid4Section.xLL + nx1 * cube->grid4Section.xSize;
		x2 = cube->grid4Section.xLL + nx2 * cube->grid4Section.xSize;
		
		y1 = cube->grid4Section.yLL + ny1 * cube->grid4Section.ySize;
		y2 = cube->grid4Section.yLL + ny2 * cube->grid4Section.ySize;
		
		z1 = cube->grid4Section.zLL + nz1 * cube->grid4Section.zSize;
		z2 = cube->grid4Section.zLL + nz2 * cube->grid4Section.zSize;
	}
	/*
	// точка пересечения совпадает с p1?
	if (fabs(isolevel - valp1) < 0.00001)
	{
		p.x = x1;
		p.y = y1;
		p.z = z1;
		return(p);
	}

  // точка пересечения совпадает с p2?
  if (fabs(isolevel - valp2) < 0.00001)
	{
		p.x = x2;
		p.y = y2;
		p.z = z2;
		return(p);
	}*/
	//printf("[v1 = %f v2 = %f fd  = %f]\t", valp1, valp1, fabs(valp1 - valp2));
	//printf("[%f %f %f]\t", x1, y1, z1);
	//printf("[%f %f %f]\t", x2, y2, z2);
  // значение функции не меняется на всем отрезке?
  if (fabs(valp1 - valp2) < 0.00001)
	{
		p.x = (x1+x2)/2.0;
		p.y = (y1+y2)/2.0;
		p.z = (z1+z2)/2.0;
		return(p);
	}

	mu = (isolevel - valp1) / (valp2 - valp1);

	p.x = x1 + mu * (x2 - x1);
	p.y = y1 + mu * (y2 - y1);
	p.z = z1 + mu * (z2 - z1);
	//printf("VertexInterp [%f %f %f] mu %f\n", p.x, p.y, p.z, mu);
	return(p);

}
// эта функция возвращает количество сгенерированных граней, максимум 5 штук
// массив triangles будет заполнен собственно гранями
// если ячейка находится целиком под или над изоповерхностью, возвращается 0

// grid - ячейка, которую надо обработать алгоритмом
// isolevel - изоуровень
// triangles - массив, куда будут сохраняться генерируемые грани

void Polygonise(double isolevel, Grid4 * cube, 
				long nx, long ny, long nz, 
				long **** Ivert,
				int& ntria, TRIA * tria, 
				int& nvert, VERT * vert, 
				COLORREF c, 
				bool view) 
{
  int i;
  int cubeindex;
  long ivert[12];
  //xyz vertlist[12];

  // определяем номер конфигурации вершин
  /*
  cubeindex = 0;
  if (grid.val[0] < isolevel) cubeindex |= 1;
  if (grid.val[1] < isolevel) cubeindex |= 2;
  if (grid.val[2] < isolevel) cubeindex |= 4;
  if (grid.val[3] < isolevel) cubeindex |= 8;
  if (grid.val[4] < isolevel) cubeindex |= 16;
  if (grid.val[5] < isolevel) cubeindex |= 32;
  if (grid.val[6] < isolevel) cubeindex |= 64;
  if (grid.val[7] < isolevel) cubeindex |= 128;*/

  if (cube == NULL) return;

  if (cube->grid4Section.v[nz][ny][nx] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz][ny][nx+1] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz][ny+1][nx+1] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz][ny+1][nx] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz+1][ny][nx] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz+1][ny][nx+1] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz+1][ny+1][nx+1] == BLANK_VALUE) return;
  if (cube->grid4Section.v[nz+1][ny+1][nx] == BLANK_VALUE) return;

  cubeindex = 0;
  if (cube->grid4Section.v[nz][ny][nx] < isolevel) cubeindex |= 1;				// 0
  if (cube->grid4Section.v[nz][ny][nx+1] < isolevel) cubeindex |= 2;			// 1
  if (cube->grid4Section.v[nz][ny+1][nx+1] < isolevel) cubeindex |= 4;			// 2
  if (cube->grid4Section.v[nz][ny+1][nx] < isolevel) cubeindex |= 8;			// 3
  if (cube->grid4Section.v[nz+1][ny][nx] < isolevel) cubeindex |= 16;			// 4
  if (cube->grid4Section.v[nz+1][ny][nx+1] < isolevel) cubeindex |= 32;			// 5
  if (cube->grid4Section.v[nz+1][ny+1][nx+1] < isolevel) cubeindex |= 64;		// 6
  if (cube->grid4Section.v[nz+1][ny+1][nx] < isolevel) cubeindex |= 128;		// 7
  // кубик находится целиком под или над изоповерхностью?
  if (edgeTable[cubeindex] == 0)
     return;

  bool calc_vert;

  // считаем точки пересечения изоповерхности и кубика
  if (edgeTable[cubeindex] & 1)
  {
	  calc_vert = false;
	  //vertlist[0] = VertexInterp(isolevel,grid.p[0],grid.p[1],grid.val[0],grid.val[1]);
	  if(ny == 0 && nz == 0)
	  {
		  ivert[0] = nvert++; calc_vert = true;
	  }
	  else if (ny == 0 && nz != 0)
	  {
		  ivert[0] = Ivert[nz-1][ny][nx][4];
	  }
	  else if (ny != 0 && nz == 0)
	  {
		  ivert[0] = Ivert[nz][ny-1][nx][2];
	  }
	  else if (ny != 0 && nz != 0)
	  {
		  ivert[0] = Ivert[nz-1][ny-1][nx][6];
	  }
	  if(ivert[0] < 0){ivert[0] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][0] = ivert[0];
	  if (calc_vert && vert)
	  {
		  vert[ivert[0]].c = c;
		  vert[ivert[0]].v = VertexInterp(isolevel, cube, nx, ny, nz, nx+1, ny, nz, view);
		  //= VertexInterp(isolevel,grid.p[0],grid.p[1],grid.val[0],grid.val[1]);
	  }

  }
  if (edgeTable[cubeindex] & 2)
  {
	  calc_vert = false;
	  if (nz == 0)
	  {
		  ivert[1] = nvert++; calc_vert = true;
	  }
	  else
	  {
		  ivert[1] = Ivert[nz-1][ny][nx][5];
	  }
	  if(ivert[1] < 0){ivert[1] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][1] = ivert[1];
	  if (calc_vert && vert)
	  {
		  vert[ivert[1]].c = c;
		  vert[ivert[1]].v = VertexInterp(isolevel, cube, nx+1, ny, nz, nx+1, ny+1, nz, view);
	  }
	  //vertlist[1] = VertexInterp(isolevel,grid.p[1],grid.p[2],grid.val[1],grid.val[2]);
  }
  if (edgeTable[cubeindex] & 4)
  {
	  calc_vert = false;
	  if (nz == 0)
	  {
		  ivert[2] = nvert++; calc_vert = true;
	  }
	  else
	  {
		  ivert[2] = Ivert[nz-1][ny][nx][6];
	  }
	  if(ivert[2] < 0){ivert[2] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][2] = ivert[2];
	  if (calc_vert && vert)
	  {
		  vert[ivert[2]].c = c;
		  vert[ivert[2]].v = VertexInterp(isolevel, cube, nx+1, ny+1, nz, nx, ny+1, nz, view);
	  }
	  //vertlist[2] = VertexInterp(isolevel,grid.p[2],grid.p[3],grid.val[2],grid.val[3]);
  }
  if (edgeTable[cubeindex] & 8)
  {
	  calc_vert = false;
	  if(nx == 0 && nz == 0)
	  {
		  ivert[3] = nvert++; calc_vert = true;
	  }
	  else if (nx == 0 && nz != 0)
	  {
		  ivert[3] = Ivert[nz-1][ny][nx][7];
	  }
	  else if (nx != 0 && nz == 0)
	  {
		  ivert[3] = Ivert[nz][ny][nx-1][1];
	  }
	  else if (nx != 0 && nz != 0)
	  {
		  ivert[3] = Ivert[nz-1][ny][nx-1][5];
	  }
	  if(ivert[3] < 0){ivert[3] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][3] = ivert[3];
	  if (calc_vert && vert)
	  {
		  vert[ivert[3]].c = c;
		  vert[ivert[3]].v = VertexInterp(isolevel, cube, nx, ny+1, nz, nx, ny, nz, view);
	  }
	  //vertlist[3] = VertexInterp(isolevel,grid.p[3],grid.p[0],grid.val[3],grid.val[0]);
  }
  if (edgeTable[cubeindex] & 16)
  {
	  calc_vert = false;
	  if (ny == 0)
	  {
		  ivert[4] = nvert++; calc_vert = true;
	  }
	  else
	  {
		  ivert[4] = Ivert[nz][ny-1][nx][6];
	  }
	  if(ivert[4] < 0){ivert[4] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][4] = ivert[4];
	  if (calc_vert && vert)
	  {
		  vert[ivert[4]].c = c;
		  vert[ivert[4]].v = VertexInterp(isolevel, cube, nx, ny, nz+1, nx+1, ny, nz+1, view);
	  }
	  //vertlist[4] = VertexInterp(isolevel,grid.p[4],grid.p[5],grid.val[4],grid.val[5]);
  }
  if (edgeTable[cubeindex] & 32)
  {
	  ivert[5] = nvert++; 
	  Ivert[nz][ny][nx][5] = ivert[5];
	  if (vert)
	  {
		  vert[ivert[5]].c = c;
		  vert[ivert[5]].v = VertexInterp(isolevel, cube, nx+1, ny, nz+1, nx+1, ny+1, nz+1, view);
	  }
	  //vertlist[5] = VertexInterp(isolevel,grid.p[5],grid.p[6],grid.val[5],grid.val[6]);
  }
  if (edgeTable[cubeindex] & 64)
  {
	  ivert[6] = nvert++; 
	  Ivert[nz][ny][nx][6] = ivert[6];
	  if (vert)
	  {
		  vert[ivert[6]].c = c;
		  vert[ivert[6]].v = VertexInterp(isolevel, cube, nx+1, ny+1, nz+1, nx, ny+1, nz+1, view);
	  }
	  //vertlist[6] = VertexInterp(isolevel,grid.p[6],grid.p[7],grid.val[6],grid.val[7]);
  }
  if (edgeTable[cubeindex] & 128)
  {
	  calc_vert = false;
	  if (nx == 0)
	  {
		  ivert[7] = nvert++; calc_vert = true;
	  }
	  else
	  {
		  ivert[7] = Ivert[nz][ny][nx-1][5];
	  }
	  if(ivert[7] < 0){ivert[7] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][7] = ivert[7];
	  if (calc_vert && vert)
	  {
		  vert[ivert[7]].c = c;
		  vert[ivert[7]].v = VertexInterp(isolevel, cube, nx, ny+1, nz+1, nx, ny, nz+1, view);
	  }
	  //vertlist[7] = VertexInterp(isolevel,grid.p[7],grid.p[4],grid.val[7],grid.val[4]);
  }
  if (edgeTable[cubeindex] & 256)
  {
	  calc_vert = false;
	  if(nx == 0 && ny == 0)
	  {
		  ivert[8] = nvert++; calc_vert = true;
	  }
	  else if (nx == 0 && ny != 0)
	  {
		  ivert[8] = Ivert[nz][ny-1][nx][11];
	  }
	  else if (nx != 0 && ny == 0)
	  {
		  ivert[8] = Ivert[nz][ny][nx-1][9];
	  }
	  else if (nx != 0 && ny != 0)
	  {
		  ivert[8] = Ivert[nz][ny-1][nx-1][10];
	  }
	  if(ivert[8] < 0){ivert[8] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][8] = ivert[8];
	  if (calc_vert && vert)
	  {
		  vert[ivert[8]].c = c;
		  vert[ivert[8]].v = VertexInterp(isolevel, cube, nx, ny, nz, nx, ny, nz+1, view);
	  }
	  //vertlist[8] = VertexInterp(isolevel,grid.p[0],grid.p[4],grid.val[0],grid.val[4]);
  }
  if (edgeTable[cubeindex] & 512)
  {
	  calc_vert = false;
	  if (ny == 0)
	  {
		  ivert[9] = nvert++; calc_vert = true;
	  }
	  else
	  {
		  ivert[9] = Ivert[nz][ny-1][nx][10];
	  }
	  if(ivert[9] < 0){ivert[9] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][9] = ivert[9];
	  if (calc_vert && vert)
	  {
		  vert[ivert[9]].c = c;
		  vert[ivert[9]].v = VertexInterp(isolevel, cube, nx+1, ny, nz, nx+1, ny, nz+1, view);
	  }
	  //vertlist[9] = VertexInterp(isolevel,grid.p[1],grid.p[5],grid.val[1],grid.val[5]);
  }
  if (edgeTable[cubeindex] & 1024)
  {
	  ivert[10] = nvert++; 
	  Ivert[nz][ny][nx][10] = ivert[10];
	  if (vert)
	  {
		  vert[ivert[10]].c = c;
		  vert[ivert[10]].v = VertexInterp(isolevel, cube, nx+1, ny+1, nz, nx+1, ny+1, nz+1, view);
	  }
	  //vertlist[10] = VertexInterp(isolevel,grid.p[2],grid.p[6],grid.val[2],grid.val[6]);
  }
  if (edgeTable[cubeindex] & 2048)
  {
	  calc_vert = false;
	  if (nx == 0)
	  {
		  ivert[11] = nvert++; calc_vert = true;
	  }
	  else
	  {
		  ivert[11] = Ivert[nz][ny][nx-1][10];
	  }
	  if(ivert[11] < 0){ivert[11] = nvert++; calc_vert = true;}
	  Ivert[nz][ny][nx][11] = ivert[11];
	  if (calc_vert && vert)
	  {
		  vert[ivert[11]].c = c;
		  vert[ivert[11]].v = VertexInterp(isolevel, cube, nx, ny+1, nz, nx, ny+1, nz+1, view);
	  }
	  //vertlist[11] = VertexInterp(isolevel,grid.p[3],grid.p[7],grid.val[3],grid.val[7]);
  }

  // создаем грани

  for (i=0; triTable[cubeindex][i] != -1; i += 3) {
    //triangles[ntriang].p[0] = vertlist[triTable[cubeindex][i  ]];
    //triangles[ntriang].p[1] = vertlist[triTable[cubeindex][i+1]];
    //triangles[ntriang].p[2] = vertlist[triTable[cubeindex][i+2]];
	  if (tria)
	  {
		  tria[ntria].i1 = ivert[triTable[cubeindex][i  ]];
		  tria[ntria].i2 = ivert[triTable[cubeindex][i+1]];
		  tria[ntria].i3 = ivert[triTable[cubeindex][i+2]];
	  
		  if(vert)
		  {
			  //===== Вычисление вектора нормали
			  double d1[3], d2[3], norm[3];
#if 0
			  d1[0] = vert[tria[ntria].i2].v.x-vert[tria[ntria].i1].v.x;
			  d1[1] = vert[tria[ntria].i2].v.y-vert[tria[ntria].i1].v.y;
			  d1[2] = vert[tria[ntria].i2].v.z-vert[tria[ntria].i1].v.z;

              
			  d2[0] = vert[tria[ntria].i1].v.x-vert[tria[ntria].i3].v.x;
			  d2[1] = vert[tria[ntria].i1].v.y-vert[tria[ntria].i3].v.y;
			  d2[2] = vert[tria[ntria].i1].v.z-vert[tria[ntria].i3].v.z;
#else
			  d1[0] = vert[tria[ntria].i1].v.x-vert[tria[ntria].i2].v.x;
			  d1[1] = vert[tria[ntria].i1].v.y-vert[tria[ntria].i2].v.y;
			  d1[2] = vert[tria[ntria].i1].v.z-vert[tria[ntria].i2].v.z;

              
			  d2[0] = vert[tria[ntria].i2].v.x-vert[tria[ntria].i3].v.x;
			  d2[1] = vert[tria[ntria].i2].v.y-vert[tria[ntria].i3].v.y;
			  d2[2] = vert[tria[ntria].i2].v.z-vert[tria[ntria].i3].v.z;
#endif
			  getNorm(d1,d2,norm);
			  vert[tria[ntria].i1].n = CPoint3(norm[0],norm[1],norm[2]);
			  vert[tria[ntria].i2].n = CPoint3(norm[0],norm[1],norm[2]);
			  vert[tria[ntria].i3].n = CPoint3(norm[0],norm[1],norm[2]);
		  }
	  }	  
	  ntria++;
  }
}
void DrawIzoSurface(double isolevel, Grid4 * cube, COLORREF c)
{
	//printf("DrawIzoSurface isolevel = %f\n", isolevel);
	if (cube == NULL) return;
	long Nz = cube->grid4Section.nPag;
	long Ny = cube->grid4Section.nRow;
	long Nx = cube->grid4Section.nCol;
	//long **** Ivert = Alloc4DMat<long> (Nz,Ny,Nx,12, -1);// here  error on memcpy!!!!
	long **** Ivert = Alloc4DMat<long> (Nz,Ny,Nx,12);
	int ntria = 0;
	int nvert = 0;
	long nz,ny,nx;

	for (nx = 0; nx < Nx-1; nx++)
		for(ny = 0; ny < Ny-1; ny++)
			for(nz = 0; nz < Nz-1; nz++)
				for (long i = 0; i < 12; i++)
					Ivert[nz][ny][nx][i] = -1;

	for (nx = 0; nx < Nx-1; nx++)
		for(ny = 0; ny < Ny-1; ny++)
			for(nz = 0; nz < Nz-1; nz++)
				Polygonise(isolevel, cube, 
				nx, ny, nz, Ivert,
				ntria, NULL, 
				nvert, NULL, 
				c,
				true);

	//printf("DrawIzoSurface ntria = %d\n", ntria);
	//printf("DrawIzoSurface nvert = %d\n", nvert);
	TRIA * tria = new TRIA [ntria];
	VERT * vert = new VERT [nvert]; 
	int ntria2 = 0;
	int nvert2 = 0;
	for (nx = 0; nx < Nx-1; nx++)
		for(ny = 0; ny < Ny-1; ny++)
			for(nz = 0; nz < Nz-1; nz++)
				Polygonise(isolevel, cube, 
				nx, ny, nz, Ivert,
				ntria2, tria, 
				nvert2, vert, 
				c,
				true);
	//====== Задание адресов трех массивов (вершин,
	//====== нормалей и цветов),
	//====== а также шага перемещения по ним
	glVertexPointer(3, GL_PRECISION, sizeof(VERT), &vert->v);
	glNormalPointer(GL_PRECISION, sizeof(VERT), &vert->n);
	glColorPointer(4, GL_UNSIGNED_BYTE, sizeof(VERT), &vert->c);
			
	//m_nglListNumber = m_pSurfDoc->m_DrawListArray.glNewList();
	//====== Формирование списка рисующих команд
	glDrawElements(GL_TRIANGLES, 3*ntria, GL_UNSIGNED_INT, tria);			
	//glEndList();
	
	//== Освобождение памяти, так как список сформирован
	delete [] vert;
	delete [] tria;
	Free4DMat<long>(Ivert);
}


bool DrawIzoSurfaceToDxf(dimeModel & model, const dimeLayer * layer,
						 dimeBlock * block,
						 double isolevel, Grid4 * cube, COLORREF c, bool view)
{
	//printf("DrawIzoSurface isolevel = %f\n", isolevel);
	if (cube == NULL) return false;
	long Nz = cube->grid4Section.nPag;
	long Ny = cube->grid4Section.nRow;
	long Nx = cube->grid4Section.nCol;
	//long **** Ivert = Alloc4DMat<long> (Nz,Ny,Nx,12, -1);// here  error on memcpy!!!!
	long **** Ivert = Alloc4DMat<long> (Nz,Ny,Nx,12);
	int ntria = 0;
	int nvert = 0;
	long nz,ny,nx;

	for (nx = 0; nx < Nx-1; nx++)
		for(ny = 0; ny < Ny-1; ny++)
			for(nz = 0; nz < Nz-1; nz++)
				for (long i = 0; i < 12; i++)
					Ivert[nz][ny][nx][i] = -1;

	for (nx = 0; nx < Nx-1; nx++)
		for(ny = 0; ny < Ny-1; ny++)
			for(nz = 0; nz < Nz-1; nz++)
				Polygonise(isolevel, cube, 
				nx, ny, nz, Ivert,
				ntria, NULL, 
				nvert, NULL, 
				c,
				view);

	if (!ntria)
		return false;

	//printf("DrawIzoSurface ntria = %d\n", ntria);
	//printf("DrawIzoSurface nvert = %d\n", nvert);
	TRIA * tria = new TRIA [ntria];
	VERT * vert = new VERT [nvert]; 
	int ntria2 = 0;
	int nvert2 = 0;
	for (nx = 0; nx < Nx-1; nx++)
		for(ny = 0; ny < Ny-1; ny++)
			for(nz = 0; nz < Nz-1; nz++)
				Polygonise(isolevel, cube, 
				nx, ny, nz, Ivert,
				ntria2, tria, 
				nvert2, vert, 
				c, view);


	for (int itria = 0; itria < ntria; itria++)
	{
		print_solid_triangle(tria[itria], vert, model, layer, block, c);
		//print_filled_triangle(tria[itria], vert, model, layer, block, c);
	}

	//== Освобождение памяти, так как список сформирован
	delete [] vert;
	delete [] tria;
	Free4DMat<long>(Ivert);
	return true;
}


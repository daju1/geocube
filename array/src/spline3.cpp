#include "StdAfx.h"
#include "spline3.h"
/*
(*************************************************************************
Этот модуль содержит две функции - Spline3BuildTable и Spline3Interpolate.

Процедура Spline3BuildTable служит  для  постройки  таблицы  коэффициентов
кубического сплайна по заданным точкам и граничным условиям, накладываемым
на производные. Функция принимает параметры:
    N       - число отрезков разбиения, не меньше одного.
    DiffN   - тип граничного условия. "1" соответствует граничным условиям
              накладываемым на первые производные, "2" - на вторые.
    xs      - массив абсцисс опорных точек с номерами от 0 до n.
    ys      - массив ординат опорных точек с номерами от 0 до n.
    BoundL  - левое граничное условие. Если DiffN равно 1, то первая произ-
              водная  на  левой  границе  равна BoundL, иначе BoundL равна
              вторая.
    BoundR  - аналогично BoundL
Функция возвращает:
    ctbl    - в этот массив помещается таблица коэффициентов сплайна.


Функция Spline3Interpolate по построенной таблице коэффициентов  вычисляет
значение интерполируемой функции в заданной точке. Параметры:
    N       - число отрезков разбиения
    c       - таблица коэффициентов, построенная функцией
    X       - точка, в которой ведем расчет

*************************************************************************)
*/



void spline3buildtable(int n,
     int diffn,
     ap::real_1d_array x,
     ap::real_1d_array y,
     double boundl,
     double boundr,
     ap::real_2d_array& ctbl)
{
    bool c;
    int e;
    int g;
    double tmp;
    int nxm1;
    int i;
    int j;
    double dx;
    double dxj;
    double dyj;
    double dxjp1;
    double dyjp1;
    double dxp;
    double dyp;
    double yppa;
    double yppb;
    double pj;
    double b1;
    double b2;
    double b3;
    double b4;

    g = (n+1)/2;
    do
    {
        i = g;
        do
        {
            j = i-g;
            c = true;
            do
            {
                if( x(j)<=x(j+g) )
                {
                    c = false;
                }
                else
                {
                    tmp = x(j);
                    x(j) = x(j+g);
                    x(j+g) = tmp;
                    tmp = y(j);
                    y(j) = y(j+g);
                    y(j+g) = tmp;
                }
                j = j-1;
            }
            while(j>=0&&c);
            i = i+1;
        }
        while(i<=n);
        g = g/2;
    }
    while(g>0);
    ctbl.setbounds(0, 4, 0, n);
    n = n+1;
    if( diffn==1 )
    {
        b1 = 1;
        b2 = double(6)/double(x(1)-x(0))*((y(1)-y(0))/(x(1)-x(0))-boundl);
        b3 = 1;
        b4 = double(6)/double(x(n-1)-x(n-2))*(boundr-(y(n-1)-y(n-2))/(x(n-1)-x(n-2)));
    }
    else
    {
        b1 = 0;
        b2 = 2*boundl;
        b3 = 0;
        b4 = 2*boundr;
    }
    nxm1 = n-1;
    if( n>=2 )
    {
        if( n>2 )
        {
            dxj = x(1)-x(0);
            dyj = y(1)-y(0);
            j = 2;
            while(j<=nxm1)
            {
                dxjp1 = x(j)-x(j-1);
                dyjp1 = y(j)-y(j-1);
                dxp = dxj+dxjp1;
                ctbl(1,j-1) = dxjp1/dxp;
                ctbl(2,j-1) = 1-ctbl(1,j-1);
                ctbl(3,j-1) = 6*(dyjp1/dxjp1-dyj/dxj)/dxp;
                dxj = dxjp1;
                dyj = dyjp1;
                j = j+1;
            }
        }
        ctbl(1,0) = -double(b1)/double(2);
        ctbl(2,0) = double(b2)/double(2);
        if( n!=2 )
        {
            j = 2;
            while(j<=nxm1)
            {
                pj = ctbl(2,j-1)*ctbl(1,j-2)+2;
                ctbl(1,j-1) = -ctbl(1,j-1)/pj;
                ctbl(2,j-1) = (ctbl(3,j-1)-ctbl(2,j-1)*ctbl(2,j-2))/pj;
                j = j+1;
            }
        }
        yppb = (b4-b3*ctbl(2,nxm1-1))/(b3*ctbl(1,nxm1-1)+2);
        i = 1;
        while(i<=nxm1)
        {
            j = n-i;
            yppa = ctbl(1,j-1)*yppb+ctbl(2,j-1);
            dx = x(j)-x(j-1);
            ctbl(3,j-1) = double((yppb-yppa)/dx)/double(6);
            ctbl(2,j-1) = double(yppa)/double(2);
            ctbl(1,j-1) = (y(j)-y(j-1))/dx-(ctbl(2,j-1)+ctbl(3,j-1)*dx)*dx;
            yppb = yppa;
            i = i+1;
        }
        for(i = 1; i <= n; i++)
        {
            ctbl(0,i-1) = y(i-1);
            ctbl(4,i-1) = x(i-1);
        }
    }
}


double spline3interpolate(int n, const ap::real_2d_array& c, double x)
{
    double result;
    int i;
    int l;
    int half;
    int first;
    int middle;

    l = n;
    first = 0;
    while(l>0)
    {
        half = l/2;
        middle = first+half;
        if( c(4,middle)<x )
        {
            first = middle+1;
            l = l-half-1;
        }
        else
        {
            l = half;
        }
    }
    i = first-1;
    if( i<0 )
    {
        i = 0;
    }
    result = c(0,i)+(x-c(4,i))*(c(1,i)+(x-c(4,i))*(c(2,i)+c(3,i)*(x-c(4,i))));
    return result;
}



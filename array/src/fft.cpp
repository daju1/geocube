#include "StdAfx.h"
#include "fft.h"




/************************************************
Этот модуль сгенерирован транслятором AlgoPascal.
************************************************/

void fastfouriertransform(ap::real_1d_array& a, int nn, bool inversefft)
{
    int ii;
    int jj;
    int n;
    int mmax;
    int m;
    int j;
    int istep;
    int i;
    int isign;
    double wtemp;
    double wr;
    double wpr;
    double wpi;
    double wi;
    double theta;
    double tempr;
    double tempi;

    if( inversefft )
    {
        isign = -1;
    }
    else
    {
        isign = 1;
    }
    n = 2*nn;
    j = 1;
    for(ii = 1; ii <= nn; ii++)
    {
        i = 2*ii-1;
        if( j>i )
        {
            tempr = a(j-1);
            tempi = a(j);
            a(j-1) = a(i-1);
            a(j) = a(i);
            a(i-1) = tempr;
            a(i) = tempi;
        }
        m = n/2;
        while(m>=2&&j>m)
        {
            j = j-m;
            m = m/2;
        }
        j = j+m;
    }
    mmax = 2;
    while(n>mmax)
    {
        istep = 2*mmax;
        theta = double(2*ap::pi())/double(isign*mmax);
        wpr = -2.0*ap::sqr(sin(0.5*theta));
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for(ii = 1; ii <= mmax/2; ii++)
        {
            m = 2*ii-1;
            for(jj = 0; jj <= (n-m)/istep; jj++)
            {
                i = m+jj*istep;
                j = i+mmax;
                tempr = wr*a(j-1)-wi*a(j);
                tempi = wr*a(j)+wi*a(j-1);
                a(j-1) = a(i-1)-tempr;
                a(j) = a(i)-tempi;
                a(i-1) = a(i-1)+tempr;
                a(i) = a(i)+tempi;
            }
            wtemp = wr;
            wr = wr*wpr-wi*wpi+wr;
            wi = wi*wpr+wtemp*wpi+wi;
        }
        mmax = istep;
    }
    if( inversefft )
    {
        for(i = 1; i <= 2*nn; i++)
        {
            a(i-1) = double(a(i-1))/double(nn);
        }
    }
}



void realfastfouriertransform(ap::real_1d_array& a, int tnn, bool inversefft)
{
    double twr;
    double twi;
    double twpr;
    double twpi;
    double twtemp;
    double ttheta;
    int i;
    int i1;
    int i2;
    int i3;
    int i4;
    double c1;
    double c2;
    double h1r;
    double h1i;
    double h2r;
    double h2i;
    double wrs;
    double wis;
    int nn;
    int ii;
    int jj;
    int n;
    int mmax;
    int m;
    int j;
    int istep;
    int isign;
    double wtemp;
    double wr;
    double wpr;
    double wpi;
    double wi;
    double theta;
    double tempr;
    double tempi;

    if( tnn==1 )
    {
        return;
    }
    if( !inversefft )
    {
        ttheta = double(2*ap::pi())/double(tnn);
        c1 = 0.5;
        c2 = -0.5;
    }
    else
    {
        ttheta = double(2*ap::pi())/double(tnn);
        c1 = 0.5;
        c2 = 0.5;
        ttheta = -ttheta;
        twpr = -2.0*ap::sqr(sin(0.5*ttheta));
        twpi = sin(ttheta);
        twr = 1.0+twpr;
        twi = twpi;
        for(i = 2; i <= tnn/4+1; i++)
        {
            i1 = i+i-1;
            i2 = i1+1;
            i3 = tnn+3-i2;
            i4 = i3+1;
            wrs = twr;
            wis = twi;
            h1r = c1*(a(i1-1)+a(i3-1));
            h1i = c1*(a(i2-1)-a(i4-1));
            h2r = -c2*(a(i2-1)+a(i4-1));
            h2i = c2*(a(i1-1)-a(i3-1));
            a(i1-1) = h1r+wrs*h2r-wis*h2i;
            a(i2-1) = h1i+wrs*h2i+wis*h2r;
            a(i3-1) = h1r-wrs*h2r+wis*h2i;
            a(i4-1) = -h1i+wrs*h2i+wis*h2r;
            twtemp = twr;
            twr = twr*twpr-twi*twpi+twr;
            twi = twi*twpr+twtemp*twpi+twi;
        }
        h1r = a(0);
        a(0) = c1*(h1r+a(1));
        a(1) = c1*(h1r-a(1));
    }
    if( inversefft )
    {
        isign = -1;
    }
    else
    {
        isign = 1;
    }
    n = tnn;
    nn = tnn/2;
    j = 1;
    for(ii = 1; ii <= nn; ii++)
    {
        i = 2*ii-1;
        if( j>i )
        {
            tempr = a(j-1);
            tempi = a(j);
            a(j-1) = a(i-1);
            a(j) = a(i);
            a(i-1) = tempr;
            a(i) = tempi;
        }
        m = n/2;
        while(m>=2&&j>m)
        {
            j = j-m;
            m = m/2;
        }
        j = j+m;
    }
    mmax = 2;
    while(n>mmax)
    {
        istep = 2*mmax;
        theta = double(2*ap::pi())/double(isign*mmax);
        wpr = -2.0*ap::sqr(sin(0.5*theta));
        wpi = sin(theta);
        wr = 1.0;
        wi = 0.0;
        for(ii = 1; ii <= mmax/2; ii++)
        {
            m = 2*ii-1;
            for(jj = 0; jj <= (n-m)/istep; jj++)
            {
                i = m+jj*istep;
                j = i+mmax;
                tempr = wr*a(j-1)-wi*a(j);
                tempi = wr*a(j)+wi*a(j-1);
                a(j-1) = a(i-1)-tempr;
                a(j) = a(i)-tempi;
                a(i-1) = a(i-1)+tempr;
                a(i) = a(i)+tempi;
            }
            wtemp = wr;
            wr = wr*wpr-wi*wpi+wr;
            wi = wi*wpr+wtemp*wpi+wi;
        }
        mmax = istep;
    }
    if( inversefft )
    {
        for(i = 1; i <= 2*nn; i++)
        {
            a(i-1) = double(a(i-1))/double(nn);
        }
    }
    if( !inversefft )
    {
        twpr = -2.0*ap::sqr(sin(0.5*ttheta));
        twpi = sin(ttheta);
        twr = 1.0+twpr;
        twi = twpi;
        for(i = 2; i <= tnn/4+1; i++)
        {
            i1 = i+i-1;
            i2 = i1+1;
            i3 = tnn+3-i2;
            i4 = i3+1;
            wrs = twr;
            wis = twi;
            h1r = c1*(a(i1-1)+a(i3-1));
            h1i = c1*(a(i2-1)-a(i4-1));
            h2r = -c2*(a(i2-1)+a(i4-1));
            h2i = c2*(a(i1-1)-a(i3-1));
            a(i1-1) = h1r+wrs*h2r-wis*h2i;
            a(i2-1) = h1i+wrs*h2i+wis*h2r;
            a(i3-1) = h1r-wrs*h2r+wis*h2i;
            a(i4-1) = -h1i+wrs*h2i+wis*h2r;
            twtemp = twr;
            twr = twr*twpr-twi*twpi+twr;
            twi = twi*twpr+twtemp*twpi+twi;
        }
        h1r = a(0);
        a(0) = h1r+a(1);
        a(1) = h1r-a(1);
    }
}


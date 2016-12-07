#include "stdafx.h"
#include "datenum.h"
#include <math.h>
double datenum(int y, int mo, int d, int h, int mi, int s, int milli)
	{
	//cumsum([0;31;28;31;30;31;30;31;31;30;31;30;31])
	static int cumdpm[13];
	cumdpm[0] = 0;
	cumdpm[1] = cumdpm[0] + 31;
	cumdpm[2] = cumdpm[1] + 28;
	cumdpm[3] = cumdpm[2] + 31;
	cumdpm[4] = cumdpm[3] + 30;
	cumdpm[5] = cumdpm[4] + 31;
	cumdpm[6] = cumdpm[5] + 30;
	cumdpm[7] = cumdpm[6] + 31;
	cumdpm[8] = cumdpm[7] + 31;
	cumdpm[9] = cumdpm[8] + 30;
	cumdpm[10] = cumdpm[9] + 31;
	cumdpm[11] = cumdpm[10] + 30;
	cumdpm[12] = cumdpm[11] + 31;
	int n;
	n = 365*y +                   // Convert year, month, day to date number
	  (int)ceil((double)y/4.0)-(int)ceil((double)y/100.0)+(int)ceil((double)y/400.0) + cumdpm[mo-1] + 
		((mo > 2) && ((y%4 == 0 && y%100 != 0) || y%400 == 0)) + d;
	double dn;
	int secs;
	if (h!=0 || mi!=0 || s!=0)
	{
		secs = (h*3600+mi*60+s);
		dn = (double)n + ((double)secs)/86400.0;
		dn += double(milli)/86400000.;
	}
	else
	{
		secs = 0;
		dn = (double)n;
	}
	return dn;
}

double datenum(SYSTEMTIME tm)
{
	WORD y   =  tm.wYear;
	int mo   = 	(int)tm.wMonth;
	int h    = 	(int)tm.wHour;
	int mi   = 	(int)tm.wMinute;
	int s    =  (int)tm.wSecond;
	int milli=  (int)tm.wMilliseconds;

	//cumsum([0;31;28;31;30;31;30;31;31;30;31;30;31])
	static int cumdpm[13];
	cumdpm[0] = 0;
	cumdpm[1] = cumdpm[0] + 31;
	cumdpm[2] = cumdpm[1] + 28;
	cumdpm[3] = cumdpm[2] + 31;
	cumdpm[4] = cumdpm[3] + 30;
	cumdpm[5] = cumdpm[4] + 31;
	cumdpm[6] = cumdpm[5] + 30;
	cumdpm[7] = cumdpm[6] + 31;
	cumdpm[8] = cumdpm[7] + 31;
	cumdpm[9] = cumdpm[8] + 30;
	cumdpm[10] = cumdpm[9] + 31;
	cumdpm[11] = cumdpm[10] + 30;
	cumdpm[12] = cumdpm[11] + 31;
	int n;
	n = 365*int(y)     // Convert year, month, day to date number
		+(int)ceil((double)y/4.0)
		-(int)ceil((double)y/100.0)
		+(int)ceil((double)y/400.0)
		+cumdpm[mo-1]
		+((mo > 2) && ((y%4 == 0 && y%100 != 0) || y%400 == 0)) 
		+(int)tm.wDay;
	double dn;
	int secs;

	if (h!=0 || mi!=0 || s!=0 || milli!=0)
	{
		secs = (h*3600+mi*60+s);
		dn = (double)n + ((double)secs)/86400.;
		dn += double(tm.wMilliseconds)/86400000.;
	}
	else
	{
		secs = 0;
		dn = (double)n;
	}
	return dn;
}
void numdate(double dn, int& h, int& mi, int& s, int& milli)
{
	int n = int(dn);
	double tm = dn - n;
	double dsecs = tm*86400.0;
	int secs = int(dsecs);
	milli = int(1000.*(dsecs - secs));
	h = secs/3600;
	secs -= h*3600;
	mi = secs/60;
	secs -= mi*60;
	s = secs;
}
void datevec(double dn, int& y, int& mo, int& d, int& h, int& mi, int& s, int& milli)
{
	static int cumdpm[13];
	cumdpm[0] = 0;
	cumdpm[1] = cumdpm[0] + 31;
	cumdpm[2] = cumdpm[1] + 28;
	cumdpm[3] = cumdpm[2] + 31;
	cumdpm[4] = cumdpm[3] + 30;
	cumdpm[5] = cumdpm[4] + 31;
	cumdpm[6] = cumdpm[5] + 30;
	cumdpm[7] = cumdpm[6] + 31;
	cumdpm[8] = cumdpm[7] + 31;
	cumdpm[9] = cumdpm[8] + 30;
	cumdpm[10] = cumdpm[9] + 31;
	cumdpm[11] = cumdpm[10] + 30;
	cumdpm[12] = cumdpm[11] + 31;

	int n = int(dn);

	double time = dn - n; 
	int secs = int(time*86400);
	milli = WORD((time*86400. - secs)*1000);
	h = secs/3600;
	secs -= h*3600;
	mi = secs/60;
	secs -= mi*60;
	s = secs;

	if (n<=366)
    		y=0;
	else
    		y = int(double(n)/(366));

	int rn, feb29;
	bool add;
	
	do
	{
		rn = n - (365*y
        	+int(ceil(double(y)/4.0))
        	-int(ceil(double(y)/100.0))
        	+int(ceil(double(y)/400.0))
        	);
		feb29=(y%4 == 0 && y%100 != 0) || y%400 == 0 ? 1 : 0; //текущий год - високосный год
		add = rn > 365+feb29;
		if (add)
			y++;
	}
	while (add);
	mo = 1;
	bool flag;
	feb29=0;

	do
	{
    		if (mo<12)
			flag = cumdpm[mo]+feb29<rn;
		else
			flag=false;
		if (flag)
			mo++;            
		if (mo == 2)
			feb29=(y%4 == 0 && y%100 != 0) || y%400 == 0 ? 1 : 0; //текущий год - високосный год
	}
	while (flag);

	if(mo==1)
		d=rn;
    else if(mo==2)
		d=rn-cumdpm[mo-1];
	else if(mo>2)
		d=rn-cumdpm[mo-1]-feb29;
}
void datevec(double dn, SYSTEMTIME& tm)
{
	WORD y;
	int mo;
	static WORD cumdpm[13];
	cumdpm[0] = 0;
	cumdpm[1] = cumdpm[0] + 31;
	cumdpm[2] = cumdpm[1] + 28;
	cumdpm[3] = cumdpm[2] + 31;
	cumdpm[4] = cumdpm[3] + 30;
	cumdpm[5] = cumdpm[4] + 31;
	cumdpm[6] = cumdpm[5] + 30;
	cumdpm[7] = cumdpm[6] + 31;
	cumdpm[8] = cumdpm[7] + 31;
	cumdpm[9] = cumdpm[8] + 30;
	cumdpm[10] = cumdpm[9] + 31;
	cumdpm[11] = cumdpm[10] + 30;
	cumdpm[12] = cumdpm[11] + 31;

	int n = int(dn);

	tm.wDayOfWeek = WORD((n+5)%7);

	double time = dn - n; 
	int secs = int(time*86400.);
	tm.wMilliseconds = WORD((time*86400. - secs)*1000);
	tm.wHour = WORD(secs/3600);
	secs -= int(tm.wHour)*3600;
	tm.wMinute = WORD(secs/60);
	secs -= int(tm.wMinute)*60;
	tm.wSecond = WORD(secs);

	if (n<=366)
    		y=0;
	else
    		y = WORD(double(n)/(366));

	WORD rn, feb29;
	bool add;
	
	do
	{
		rn = WORD(n - (365*int(y)
        	+int(ceil(double(y)/4.0))
        	-int(ceil(double(y)/100.0))
        	+int(ceil(double(y)/400.0))
        	));
		feb29=(y%4 == 0 && y%100 != 0) || y%400 == 0 ? 1 : 0; //текущий год - високосный год
		add = rn > 365+feb29;
		if (add)
			y++;
	}
	while (add);
	mo = 1;
	bool flag;
	feb29=0;

	do
	{
    		if (mo<12)
			flag = cumdpm[mo]+feb29<rn;
		else
			flag=false;
		if (flag)
			mo++;            
		if (mo == 2)
			feb29=(y%4 == 0 && y%100 != 0) || y%400 == 0 ? 1 : 0; //текущий год - високосный год
	}
	while (flag);

	if(mo==1)
		tm.wDay=rn;
    else if(mo==2)
		tm.wDay=rn-cumdpm[mo-1];
	else if(mo>2)
		tm.wDay=rn-cumdpm[mo-1]-feb29;

	tm.wMonth = WORD(mo);
	tm.wYear  = y;
}


void date_test()
{
	double dn;
	int y,mo, d, h, mi,s, milli;
	for (double t = 1; t<800000.; t+=1.)
	{
		datevec(t,y,mo,d,h,mi,s, milli);
		dn = datenum(y,mo,d,h,mi,s, milli);
		if( t!=dn)
		{
			char err[255];
			sprintf_s(err, 255, "t (%g) != dn(%g)\n %d:%d:%d %d:%d:%d\0", t,dn, y,mo,d,h,mi,s);
			MessageBox(0,err,"date test",0);
		}
	}
	MessageBox(0,"ok","date test",0);
}

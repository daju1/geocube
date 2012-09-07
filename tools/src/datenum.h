//datenum.h
#if !defined(_DATENUM_FUN_22_)
#define _DATENUM_FUN_22_

double datenum(int y, int mo, int d, int h, int mi, int s, int milli);

double datenum(SYSTEMTIME tm);

void numdate(double dn, int& h, int& mi, int& s, int& milli);

void datevec(double dn, int& y, int& mo, int& d, int& h, int& mi, int& s, int& milli);

void datevec(double dn, SYSTEMTIME& tm);


void date_test();

#endif
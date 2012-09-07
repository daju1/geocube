#include "stdafx.h"
#include "ParseTimeString.h"
#include "../../tools/src/datenum.h"

bool ParseTimeString(const char* title, short timeFormat, bool thisIsLocalTime,	int localTimeOffsetHours,
					 int& y,int& mo,int& d,int& h,int& mi,int& s,int& milli, double& t)
{
	if (timeFormat < 3)
		t = atof(title);
	else
	{
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		if (timeFormat == 3)
		{
			int rez = sscanf(title,"\"%d-%d-%d %d:%d:%d\"",
				&y, &mo, &d, &h, &mi, &s);
			if (rez == 6 && rez != EOF)
			{
				milli = 0;
				t = datenum(y, mo, d, h, mi, s, milli);
			}
			else
			{
				char str[4800];
				sprintf(str, "Error of parcing db time format !!!");
				MessageBox(0,str,"Parse Time String Error", MB_OK | MB_ICONEXCLAMATION);
				return false;
			}
		}
		// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	}

	switch (timeFormat)
	{
	case 0:// excel time
		{
			double t0 = datenum(1900,1,1,0,0,0,0)-2;
			if(thisIsLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			datevec(t+t0,y,mo,d,h,mi,s,milli);
		}
		break;
	case 1:// matlab time
		{
			double t0 = 0.;
			if(thisIsLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			datevec(t+t0,y,mo,d,h,mi,s,milli);
		}
		break;
	case 2:// unix time
		{
			// ак преобразовать unix time в TDateTime
			//unix timestamp представл€ет собой число секунд начина€ с 1.01.1970 
			//const 
			//    SecPerDay = 86400;
			//    Offset1970 = 25569;
			//function UnixTimeToDateTime(UnixTime : LongInt): TDate;
			//    Result := DateTimeToStr(UnixTime / SecPerDay + Offset1970);
			//function DateTimeToUnixTime(DelphiDate : TDate) : LongInt;
			//    Result := Trunc((DelphiDate - Offset1970) * SecPerDay);

			//≈сли необходима корректировка зимнего/летнего времени, то ее следует сделать самосто€тельно. 
			double t0 = datenum(1970,1,1,0,0,0,0);
			if(thisIsLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			datevec(t/86400.0 + t0,y,mo,d,h,mi,s,milli);
		}
		break;
	case 3:// db time
		{
			double t0 = 0.0;
			if(thisIsLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			datevec(t + t0,y,mo,d,h,mi,s,milli);
		}
		break;
	}
	return true;
}
void printTimeString(FILE * stream, short timeFormat, double t, bool translateIntoLocalTime, int localTimeOffsetHours)
{
	switch (timeFormat)
	{
	case 0:// excel time
		{
			double t0 = datenum(1900,1,1,0,0,0,0)-2;
			if(translateIntoLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			fprintf(stream, "%.8f", t-t0);
		}
		break;
	case 1:// matlab time
		{
			double t0 = 0.;
			if(translateIntoLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			fprintf(stream, "%.8f", t-t0);
		}
		break;
	case 2:// unix time
		{
			// ак преобразовать unix time в TDateTime
			//unix timestamp представл€ет собой число секунд начина€ с 1.01.1970 
			//const 
			//    SecPerDay = 86400;
			//    Offset1970 = 25569;
			//function UnixTimeToDateTime(UnixTime : LongInt): TDate;
			//    Result := DateTimeToStr(UnixTime / SecPerDay + Offset1970);
			//function DateTimeToUnixTime(DelphiDate : TDate) : LongInt;
			//    Result := Trunc((DelphiDate - Offset1970) * SecPerDay);

			//≈сли необходима корректировка зимнего/летнего времени, то ее следует сделать самосто€тельно. 
			double t0 = datenum(1970,1,1,0,0,0,0);
			if(translateIntoLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			fprintf(stream, "%f", (t-t0) * 86400.0);
		}
		break;
	case 3:// db time
		{
			double t0 = 0.0;
			int y, mo, d, h, mi, s, milli;
			if(translateIntoLocalTime)
				t0 -= double(localTimeOffsetHours)/24.0;
			datevec(t - t0,y,mo,d,h,mi,s,milli);
			fprintf(stream, "\"%d-%d-%d %d:%d:%d\"", y, mo, d, h, mi, s );
		}
		break;
	}
}

void InitTimeFormatComboBox(HWND hDlg, int nIDComboBox)
{
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
	SendDlgItemMessage( hDlg, nIDComboBox, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"excel time: in days since 1.1.1900");
	SendDlgItemMessage( hDlg, nIDComboBox, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"matlab time: in days since 1.1.0001");
	SendDlgItemMessage( hDlg, nIDComboBox, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"unix time: in secs since 1.1.1970");
	SendDlgItemMessage( hDlg, nIDComboBox, CB_ADDSTRING, 0,
		(LPARAM)(LPCTSTR)"db time: yyyy-mm-dd hh:mm:ss");
	// @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
}

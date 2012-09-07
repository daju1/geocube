bool ParseTimeString(const char* title, short timeFormat, bool thisIsLocalTime,	int localTimeOffsetHours,
					 int& y,int& mo,int& d,int& h,int& mi,int& s,int& milli, double& t);
void InitTimeFormatComboBox(HWND hDlg, int nIDComboBox);
void printTimeString(FILE * stream, short timeFormat, double t, 
					 bool translateIntoLocalTime = false, int localTimeOffsetHours = 0);


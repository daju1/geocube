#define COMMON_RAPORT
//#undef COMMON_RAPORT

void WriteRaportoB(LPCTSTR s);
void WriteRaportoA(LPCTSTR file, LPCTSTR s);



#define DO_RAPORT
//#undef DO_RAPORT

#ifdef DO_RAPORT
#ifdef COMMON_RAPORT
#define WriteRaporto(s)  WriteRaportoB(s)
#else
#define WriteRaporto(s)  WriteRaportoA(__FILE__, s)
#endif
#else
#define WriteRaporto NULL;
#endif

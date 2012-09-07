
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the GSTAT_DLL_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// GSTAT_DLL_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef GSTAT_DLL_EXPORTS
#define GSTAT_DLL_API __declspec(dllexport)
#else
#define GSTAT_DLL_API __declspec(dllimport)
#endif

// This class is exported from the gstat_dll.dll
//class GSTAT_DLL_API CGstat_dll {
//public:
//	CGstat_dll(void);
	// TODO: add your methods here.
//};

extern GSTAT_DLL_API int nGstat_dll;

GSTAT_DLL_API int fnGstat_dll(void);

int __declspec(dllexport) map_convert(int argc, char *argv[]);
int __declspec(dllexport) gstat_main(int argc, char *argv[]);
void __declspec(dllexport) parse_gstatrc(void);

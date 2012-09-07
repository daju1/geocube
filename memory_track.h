#ifndef MEMORY_TRACK_H_
#define MEMORY_TRACK_H_

#include "StdAfx.h"
//#include <windows.h>

#ifdef _DEBUG
#if USE_MEMORY_TRACK

typedef struct alloc_info {
  void* address;
  DWORD	size;
  char	file[64];
  DWORD	line;
} ALLOC_INFO;

typedef vector<ALLOC_INFO*> AllocList;


void AddTrack(void* addr,  DWORD asize,  const char *fname, DWORD lnum);
void RemoveTrack(void* addr);
void DumpUnfreed();

#pragma warning (disable:4291)


inline void * __cdecl operator new(unsigned int size, 
								   const char *file, int line)
{
	void *ptr = (void *)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,size);
	AddTrack(ptr, size, file, line);
	return(ptr);      
}  

inline void __cdecl operator delete(void *p)
{
	RemoveTrack(p);
	HeapFree(GetProcessHeap(), 0, p);
}

#endif //USE_MEMORY_TRACK
#endif /*_DEBUG*/ 
#endif /*MEMORY_TRACK_H_*/

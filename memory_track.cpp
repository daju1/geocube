#include "StdAfx.h"
#include "memory_track.h"
#include "raporto.h"
#ifdef _DEBUG
#if USE_MEMORY_TRACK

AllocList *allocList = NULL;

void AddTrack(void* addr,  DWORD asize,  const char *fname, DWORD lnum)
{
	ALLOC_INFO *info;

	if(!allocList) {
		allocList = (AllocList *)HeapAlloc(GetProcessHeap(), 
			HEAP_ZERO_MEMORY,sizeof(AllocList));

	}

	info = (ALLOC_INFO *)HeapAlloc(GetProcessHeap(), 
			HEAP_ZERO_MEMORY,sizeof(ALLOC_INFO));


	info->address = addr;
	strncpy(info->file, fname, 63);
	info->line = lnum;
	info->size = asize;

	allocList->push_back(info);
};

void RemoveTrack(void* addr)
{
	vector<ALLOC_INFO*>::iterator i;
	if(!allocList)
		return;
	for(i = allocList->begin(); i != allocList->end(); i++)
	{
		if((*i)->address == addr)
		{
			allocList->erase((i));
			break;
		}
	}
};

void DumpUnfreed()
{
	
	vector<ALLOC_INFO*>::iterator i;
	DWORD totalSize = 0;
	char buf[1024];
	
	if(!allocList)
		return;
	
	for(i = allocList->begin(); i != allocList->end(); i++)
	{
		sprintf(buf, "%-50s:\t\tLINE %d,\t\tADDRESS %d\t%d unfreed\n",
			(*i)->file, (*i)->line, (DWORD)(*i)->address, (*i)->size);
		OutputDebugString(buf);
//WriteRaporto(buf);
		totalSize += (*i)->size;
	}
	
	sprintf(buf, "--------------------------------------------------\n");
	OutputDebugString(buf);
//WriteRaporto(buf);
	sprintf(buf, "Total Unfreed: %d bytes\n", totalSize);
	OutputDebugString(buf);
//WriteRaporto(buf);

};
#endif
#endif

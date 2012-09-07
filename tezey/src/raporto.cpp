#include <stdio.h>
//#include <windows.h>
#include "StdAfx.h"

void WriteRaportoB(LPCTSTR s)
{
	FILE *stream;
	// открываем бинарный файл для записи
	if ((stream = fopen("D:\\raporto.log","at")) == NULL)
	{
		MessageBox(0,"Cannot open file for write.\n", "WriteRaporto", 0);
		return;
	}
	fprintf(stream, s);
	// закрываем файл
	fclose(stream);
}
void WriteRaportoA(LPCTSTR file, LPCTSTR s)
{
WriteRaportoB("WriteRaportoA 1\n");
	static unsigned long line = 0;
	line++;
	
	FILE *stream;
	// открываем бинарный файл для записи
	static char filename[200];
	/////////////////////////////////////////////////
	char *p1, *p2, *p;
	size_t pos_of_flash = 0;
	p1 = strrchr(file,'\\');
	p2 = strrchr(file,'/');

	if (p1 && p2)
		p = p1>p2 ? p1 : p2;
	if (!p1 && p2)
		p = p2;
	if (p1 && !p2)
		p = p1;
	if (!p1 && !p2)
		p = NULL;

#if 1
	if (p)
		pos_of_flash = int(p - file) / sizeof(char);
	/////////////////////////////////////////////////
	int pos_of_point = int(strlen(file));
	p = strrchr(file,'.');
	if (p)
		pos_of_point = int(p - file) / sizeof(char);
	/////////////////////////////////////////////////
	static char ss[100];
	int i,j;

	for (i = pos_of_flash+1, j = 0; 
	i < pos_of_point && j < 9; 
	i++, j++)
		ss[j] = file[i];
	ss[j] = '\0';

	strcpy (filename, "C:\\Variation/raporto/rap_\0");
	strcat (filename, ss);
	strcat (filename, ".log\0");
#else
	strcpy (filename, "C:\\Variation/raporto/rap_\0");
	if (p)
		strcat (filename, p);
	else
	{
WriteRaportoB("WriteRaportoA return 1\n");
		return;
	}
	p = strrchr(filename,'.');
	if (p)
		strcpy (p, ".log\0");
	else
	{
WriteRaportoB("WriteRaportoA return 2\n");
		return;
	}
#endif
//	MessageBox(0, filename, "", 0);
	if ((stream = fopen(filename,"at")) == NULL)
	{
		char err[200];
		strcpy(err, "Cannot open file for write.\n");
		strcat(err,filename);

		MessageBox(0,err, "WriteRaporto", 0);
		return;
	}
	static char sline[24];
	wsprintf(sline, "%lu\t\0", line);
	fprintf(stream, sline);
	fprintf(stream, s);
	// закрываем файл
	fclose(stream);
WriteRaportoB("WriteRaportoA end\n");
}

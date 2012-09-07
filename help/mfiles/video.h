// ��������� ���������������

#ifndef __EXAMPLE_VIDEO_H
#define __EXAMPLE_VIDEO_H

#include <conio.h>  // ��� outp()
#include <string.h> // ��� memset() � memcpy()
#include <stdlib.h> // ��� malloc()

#define XSIZE 320   // ������ ������ �� �����������
#define YSIZE 200   // ������ ������ �� ���������
#define DIST  XSIZE // ���������� �� ������ �� ������

char *exampleTexture; // ��������
char *videoBuffer;    // ����������

#ifdef __WATCOMC__
char *videoMem = (char*)0xA0000L; // ��������� �� �����������
#endif

#ifdef __BORLANDC__
#include <dos.h>                       // ��� MK_FP()
char far *videoMem = MK_FP(0xA000, 0); // ��������� �� �����������
#endif

void initPalette();

#ifdef __WATCOMC__
// ������� ��������� ������� ����������� ��� Watcom C
extern void setVideoMode(int mode);
#pragma aux setVideoMode = " int 10h " parm [eax] modify [eax];
#endif

#ifdef __BORLANDC__
// ������� ��������� ������� ����������� ��� Borland C
void setVideoMode(int mode) {
  _asm { mov ax,mode; int 10h; }
}
#endif

// ������������� ������������ � �����������
void initVideo() {
  exampleTexture = malloc(65535L); // ������� ������ ��� ��������
  videoBuffer    = malloc(64000L); // ������� ������ ��� ����������
  setVideoMode(0x13);              // ��������� ���������� 320x200x256c
}

// ����� ������� � ��������� �����
void doneVideo() {
  setVideoMode(0x03);
}

// ������� ��������� ����������� �������� ��������
void makeTexture() {
  int i, j;
  char *d = exampleTexture;

  for (i = 0; i < 256; i++)
    for (j = 0; j < 256; j++)
      *d++ = 0x80 ^ ((i ^ j) >> 1);
}

// ������� ������������� ������� ��������� �������� �����
void initPalette() {
  int i;

  outp(0x3C8, 0x00);
  for (i = 0; i < 256; i++) {
    outp(0x3C9, 0);
    outp(0x3C9, i >> 2);
    outp(0x3C9, 0);
  }
}

// ������� ������� �����������
void clearVideoBuffer() {
  memset(videoBuffer, 0, 64000L);
}

// ������� ����������� ����������� � �����������
void showVideoBuffer() {
  memcpy(videoMem, videoBuffer, 64000L);
}

#endif

//***********************************************************//
// Demo:    PickObject Demo
// Author:  terror
//***********************************************************//
#pragma once
typedef unsigned int uint;
#define LIGHTMAP_SIZE						32
#define LIGHTMAP_SCALED_SIZE		16

struct ImageJPG_t
{
	int RowSpan;
	int Width;
	int Height;
	unsigned char *data;
};

bool UploadImage ( char *filename, uint &TexID , int *psizeX = NULL, int *psizeY = NULL);
bool UploadMemImage ( byte *mem, int w, int h, uint &TexID );
void DeleteTexture  ( uint &TexID );
void DeleteTextures ( int num, uint *TexID );
bool CheckFile ( char *filename );
void ShowFileError ( char *error );

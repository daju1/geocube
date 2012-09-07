//***********************************************************//
// Demo:    PickObject Demo
// Author:  terror
//***********************************************************//
#include "StdAfx.h"
#include  <Windows.h>
#include  <stdio.h>
#include  "texture.h"
#include	<gl/gl.h>
#include	<gl/glu.h>
#include  "utils.h"
#include  "jpglib.h"


void ShowFileError ( char *error )
{
	char f[256] = "";
	strcpy ( f, "File not found: " );
	strcat ( f, error );
	MessageBox ( 0, f, "Error", MB_OK | MB_ICONEXCLAMATION );
}

bool CheckFile ( char *filename )
{
	FILE *file = NULL;
	file = fopen ( filename,"r" );
	if ( file == NULL )
	{
		ShowFileError ( filename );
		return false;
	}
	fclose ( file );
	return true;
}


void DecodeJPG ( jpeg_decompress_struct* cinfo, ImageJPG_t &pImageData )
{
	jpeg_read_header(cinfo, TRUE);
	jpeg_start_decompress(cinfo);

	pImageData.RowSpan = cinfo->image_width * cinfo->num_components;
	pImageData.Width   = cinfo->image_width;
	pImageData.Height  = cinfo->image_height;
	NEW_ARRAY_MEM ( pImageData.data, byte, pImageData.RowSpan * pImageData.Height );

	unsigned char** rowPtr = new unsigned char*[pImageData.Height];
	for (int i = 0; i < pImageData.Height; i++)
		rowPtr[i] = &(pImageData.data[i*pImageData.RowSpan]);

	int rowsRead = 0;
	while (cinfo->output_scanline < cinfo->output_height) 
	{
		rowsRead += jpeg_read_scanlines(cinfo, &rowPtr[rowsRead], cinfo->output_height - rowsRead);
	}

	delete [] rowPtr;
	jpeg_finish_decompress(cinfo);
}


bool LoadJPG ( const char *filename, ImageJPG_t &pImageData )
{
	struct jpeg_decompress_struct cinfo;
	FILE *pFile;
	if((pFile = fopen(filename, "rb")) == NULL) 
	{
		MessageBox ( 0, "Cant load JPG file", "Error", MB_OK );
		return false;
	}
	jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_stdio_src(&cinfo, pFile);
	DecodeJPG(&cinfo, pImageData);
	jpeg_destroy_decompress(&cinfo);
	fclose(pFile);

	return true;
}


bool UploadImage ( char *filename, uint &TexID, int *psizeX, int *psizeY )
{
	ImageJPG_t  jpg;
	TexID = 0;

	if ( !CheckFile ( filename ))
		return false;

	#define GL_TEXTURE_MAX_ANISOTROPY_EXT     0x84FE
	LoadJPG ( filename, jpg );
	glGenTextures		( 1, &TexID );
	glBindTexture		(	GL_TEXTURE_2D, TexID );
	glPixelStorei		( GL_UNPACK_ALIGNMENT, 1 );
	glTexEnvi				( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameterf ( GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR );
	gluBuild2DMipmaps ( GL_TEXTURE_2D, 3, jpg.Width, jpg.Height,
											GL_RGB, GL_UNSIGNED_BYTE, jpg.data );

	if (psizeX) *psizeX = jpg.Width;
	if (psizeY) *psizeY = jpg.Height;

	DELETE_ARRAY_MEM ( jpg.data );

	return true;
}


bool UploadMemImage ( byte *mem, int w, int h, uint &TexID )
{
	if ( TexID )
		glDeleteTextures ( 1, &TexID );

	TexID = 0;
	glGenTextures		( 1, &TexID );
	glBindTexture		(	GL_TEXTURE_2D, TexID );
	glPixelStorei		( GL_UNPACK_ALIGNMENT, 1 );
	glTexEnvi				( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	glTexParameteri ( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );

	int scaled_width  = LIGHTMAP_SCALED_SIZE;
	int scaled_height = LIGHTMAP_SCALED_SIZE;
	int lsize = (LIGHTMAP_SIZE*LIGHTMAP_SIZE*3);
	int ssize = (scaled_width*scaled_height*3);
	byte *scaled=NULL;
	NEW_ARRAY_MEM ( scaled, byte, ssize );

	gluScaleImage ( GL_RGB, LIGHTMAP_SIZE, LIGHTMAP_SIZE, GL_UNSIGNED_BYTE, mem, scaled_width, scaled_height, GL_UNSIGNED_BYTE, scaled );
	glTexImage2D ( GL_TEXTURE_2D, 0, 3, scaled_width,
																			scaled_height, 0, GL_RGB, GL_UNSIGNED_BYTE,
																			scaled );
	DELETE_ARRAY_MEM ( scaled );
	glTexEnvi ( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	return true;
}


void DeleteTexture ( uint &TexID )
{
	if ( TexID != NULL )
	{
		glDeleteTextures ( 1, &TexID );
		TexID = NULL;
	}
}

void DeleteTextures ( int num, uint *TexID )
{
	for ( int i = 0; i < num; i++ )
	{
		DeleteTexture ( TexID[i] );
	}
}


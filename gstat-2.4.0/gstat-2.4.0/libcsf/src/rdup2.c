
/*
 * rdup2.c 
 */
#ifndef lint  
static const char *rcs_id = 
 "$Header: /home/pcrtree/SRC.RCS/libs/csf/RCS/rdup2.c,v 2.1 1996/12/29 19:35:21 cees Exp $";
#endif

#include "csf.h"
#include "csfimpl.h"


/* create a new map by cloning another one
 * Rdup creates a new empty map from the specifications of another map.
 * No cell values are copied. It uses a call to Rcreate to create the
 * map. See Rcreate for legal values of the args cellRepr and valueScale.
 * returns the map handle of the newly created map or NULL in case of an
 * error
 *
 * Merrno
 * NOT_RASTER plus the Merrno codes of Rcreate
 *
 * EXAMPLE
 * .so examples/dupbool.tr
 */
MAP  *Rdup(
	const char *toFile, /* file name of map to be created */
	const MAP *from,    /* map to clone from */
	CSF_CR cellRepr,     /* cell representation of new map  */
	CSF_VS dataType)   /* datatype/valuescale of new map  */
{
	MAP *newMap = NULL; /* set NULL for goto error */

	CHECKHANDLE_GOTO(from, error);

	/* check if mapType is T_RASTER */
	if (from->main.mapType != T_RASTER)
	{
		M_ERROR(NOT_RASTER);
		goto error;
	}

	newMap = Rcreate(toFile,
	                 from->raster.nrRows,
			 from->raster.nrCols,
        		 cellRepr, 
        		 dataType, 
        		 from->main.projection, 
        		 from->raster.xUL,
        		 from->raster.yUL,
        		 from->raster.angle,
        		 from->raster.cellSizeX);

error:
	return newMap ;
}

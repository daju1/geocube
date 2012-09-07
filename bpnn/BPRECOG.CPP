/*
*-----------------------------------------------------------------------------
*	file:	bprecog.c
*	desc:	recognizing program
*	by:	patrick ko
*	date:	20 aug 1991
*	revi:	v1.32u 26 apr 1992
*-----------------------------------------------------------------------------
*/

#include "common_nn.h"
#include "nntype.h"
#include "bprecogv.h"
#include "BPnnet.h"

int main( int	argc, char	**argv )
{
	BPnnet bpnnet;
	return bpnnet.recog_main(argc, argv);
}


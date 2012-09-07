/*
*-----------------------------------------------------------------------------
*	file:	bptrain.c
*	desc:	back propagation Multi Layer Perceptron (MLP) training
*	by:	patrick ko
*	date:	02 aug 1991
*	revi:	v1.32u 26 apr 1992
*	revi:	v1.33u 19 nov 1992 - cparser.c bug fixed
*-----------------------------------------------------------------------------
*/
#include "common_nn.h"
#include "nntype.h"
#include "bptrainv.h"
#include "BPnnet.h"

int	main( int	argc,char	** argv)
{
	BPnnet bpnnet;
	return bpnnet.train_main(argc, argv);
}



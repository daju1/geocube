// BPnnet.h: interface for the BPnnet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BPNNET_H__7F97E569_1274_4299_86DE_7258E0FF00A8__INCLUDED_)
#define AFX_BPNNET_H__7F97E569_1274_4299_86DE_7258E0FF00A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define MAXHIDDEN	128
#include "nntype.h"
#include <time.h>
#include <stdio.h>

//#include	<values.h>
#define MAXINT 0x7FFFFFFF


#define	REAL	double
#define	INT	int


class BPnnet  
{
	REAL	ETA;
	REAL	MOMENTUM;
	REAL	LAMBDA;
	INTEGER	REPINTERVAL;
	REAL	TOLER;
	// ========================================
	// for zooming
	REAL min, delta, 
		ai, // start of input interval
		bi, // finish of input interval
		ao, // start of output interval
		bo; // finish of output interval
	// ========================================
	time_t	last;
	time_t	This;
	time_t	temp;
	/*
	*	default seed values
	*/
	INT	x;
	INT	y;
	INT	z;
	int	cmdtblsize;
	int	cmdargc;
	int	cmdcnt;
	char	**cmdargv;

	REAL	UB;
	REAL	LB;

	INTEGER	hiddencnt;
	REAL	trainerr;
	INTEGER	report;
	long int	tdump;

	VECTOR	**inputvect;
	VECTOR	**targtvect;
	VECTOR	**inputzoom;
	VECTOR	**targtzoom;
	INTEGER	timer;

	char	*tname;
	/*
	*	dump file name with default
	*/
	char	*dname;
	char	*dinname;

	char	*tfilename;

	/*
	*	default dump file name
	*/
	char	*dfilename;
	char	*ofilename;

	INTEGER	hidden[MAXHIDDEN];
	INTEGER	output;
	INTEGER	input;
	INTEGER	totalhidden;
	INTEGER	totalpatt;
public:
	void nn_dumpout2(INTEGER i, FILE * fp, NET *nn );
	void zoomtrainvect();
	int recog_main( int argc, char **argv );
	int getrecogvect( char *recogfile );
	int recog_parse();
	int recog_usage();
	int train_main( int argc,char ** argv);
	void nn_dumpout(FILE	* fp, NET	*nn );
	void nn_load( FILE	*fp, NET	*nn );
	void nn_dump(FILE	* fp, NET	*nn );
	void l_load( FILE	*fp, LAYER	*ly );
	void l_dump(FILE	* fp, LAYER	*ly );
	void u_loadweight(FILE	* fp, UNIT	*unit );
	void u_dumpweight( FILE	*fp, UNIT	*unit );
	void v_load( FILE	*fp, VECTOR	*vp );
	void v_dump( FILE	*fp, VECTOR	*vp);
	void BPnnet::nnbp_dweightcalc( NET	*net,INTEGER np, INTEGER fire );
	void BPnnet::nnbp_coeffadapt(NET	* net );
	REAL BPnnet::nnbp_backward(NET	* net, VECTOR	*inpvect, VECTOR	*tarvect );
	void BPnnet::nnbp_init( NET	*net );
	void BPnnet::nnbp_forward( NET	*net, VECTOR	*inpvect );
	REAL BPnnet::nnbp_train1(NET	* net, VECTOR	** inpvect, VECTOR	** tarvect, INTEGER	np, REAL LastError );
	void BPnnet::nnbp_report(INTEGER cnt, REAL error );
	REAL BPnnet::nnbp_train( 
					NET* net, 
					VECTOR	** inpvect, 
					VECTOR	**tarvect, 
					INTEGER np, 
					REAL err, 
					REAL eta, 
					REAL momentum, 
					INTEGER report, 
					long int tdump, 
					char * dfilename );
	long int timer_stop( );
	void timer_restart( );
	int cmdinit( int	argc, char	**argv);
	int cmdsearch( char	*str, char *rest );
	INT rndmize();
	REAL rnd();
	LAYER * l_creat( INTEGER	dimlayer, INTEGER	dimwgtvect );
	UNIT * u_creat( INTEGER	dimwgtvect );
	VECTOR *v_rand( VECTOR	*v );
	VECTOR * v_fill( VECTOR	*v, REAL	m );
	NET * nn_creat( 
		INTEGER		totallayer,
		INTEGER		diminput,
		INTEGER 	dimoutput,
		INTEGER		* dimother);
	VECTOR * v_creat( INTEGER dim );
	int gettrainvect( char *tname );
	int error( int	errno);
	int cmdget( char 	*rest);
	void train_parce();
	void train_usage();
	BPnnet();
	virtual ~BPnnet();

};

#endif // !defined(AFX_BPNNET_H__7F97E569_1274_4299_86DE_7258E0FF00A8__INCLUDED_)

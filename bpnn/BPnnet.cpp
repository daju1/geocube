// BPnnet.cpp: implementation of the BPnnet class.
//
//////////////////////////////////////////////////////////////////////
#include <time.h>
#include <math.h>

#include "BPnnet.h"
#include "common_nn.h"

#define	VERSION		"1.33u"
#define	PROGNAME	"bprecog"
#define	AUTHOR		"Patrick KO Shu Pui"
#define	DATE		"19th November, 1992."





#define CP_START	1
#define	CP_GETCMDLINE	2
#define	CP_GETRSPLINE	3
#define	CP_CMDSEARCH	4
#define	CP_RETURN	5
/*
*-----------------------------------------------------------------------------
*	file:		nnmath.h
*	desc:		nnmath.c header
*	by:			patrick ko
*	date:		2 aug 1991
*-----------------------------------------------------------------------------
*/

#define	sigmoid( netpj )	(1.0 / (1.0 + exp(-1.0 * (netpj))))
//#define	sigmoid( netpj )	(netpj / (0.1 + fabs(netpj)))


/*
*-----------------------------------------------------------------------------
*	file:	cparser.h
*	desc:	simple command parser
*	by:	patrick ko
*	date:	22 aug 91
*-----------------------------------------------------------------------------
*/

#define	CMD_NULL	0

typedef	struct	{
	int	cmdno;
	char	* cmdstr;
	}       CMDTBL;


#define	CMD_DIMINPUT		1
#define	CMD_DIMOUTPUT		2
#define	CMD_DIMHIDDENY		3
#define	CMD_DIMHIDDEN		4
#define	CMD_TRAINFILE		5
#define	CMD_TOTALPATT		6
#define	CMD_DUMPFILE		7
#define CMD_DUMPIN		8
#define	CMD_RECOGFILE		9
#define	CMD_OUTFILE		10
#define	CMD_TRAINERR		11
#define	CMD_TOLER		12
#define	CMD_REPORT		13
#define CMD_TIMER		14
#define CMD_TDUMP		15
#define	CMD_WPOS		16
#define	CMD_WNEG		17
#define	CMD_COMMENT		18



#define	NNMALLOC	0
#define NNTFRERR	1
#define NNTFIERR	2
#define NNIOLAYER	3
#define NN2MANYLAYER	4
#define NN2FEWPATT	5
#define	NN2MANYHIDDEN	6
#define	NNOUTNOTOPEN	7
#define	NNRFRERR	8


#define MAXFLOAT 3.40282347E+38F
#define MINFLOAT 1.17549435E-38F


#define	LAMBDA0	0.1



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BPnnet::BPnnet()
{
	ETA = ETA_DEFAULT;
	MOMENTUM = ALPHA_DEFAULT;
	LAMBDA = LAMBDA_DEFAULT;
	REPINTERVAL = 0;
	TOLER = TOLER_DEFAULT;
	// ========================================
	// for zooming
	ai = 0.1; // start of input interval
	bi = 0.9; // finish of input interval
	ao = 0.1; // start of output interval
	bo = 0.9; // finish of output interval
	// ========================================
	hiddencnt = 0;
	totalpatt = 0;
	trainerr = ERROR_DEFAULT;
	report = 0;
	timer = 0;
	tdump = 1;//интервал времени в секундах самосохранения нейросети

	UB= 0.3;
	LB=-0.3;

	cmdtblsize = 0;
	cmdargc = 0;
	cmdcnt = 0;
	/*
	*	default seed values
	*/
	x = 1;
	y = 10000;
	z = 3000;
	/*
	*	dump file name with default
	*/
	tname = new char[128];
	dname = new char[128];
	dinname = new char[128];
	strcpy(dname, "bptrain.dmp");
	strcpy(dinname, "polyot.dmp");

	tfilename = new char[128];

	/*
	*	default dump file name
	*/
	dfilename = new char[128];
	ofilename = new char[128];
	strcpy(dfilename, "bptrain.dmp");
	strcpy(ofilename, "bprecog.out");

}

BPnnet::~BPnnet()
{
	delete[] tname;
	delete[] dname;
	delete[] dinname;

}

void BPnnet::train_usage()
{
	printf( "%s %s - by %s\n", PROGNAME, VERSION, AUTHOR );
	printf( "Copyright (c) 1992 All Rights Reserved. %s\n\n", DATE );
	printf( "Description: backprop neural net training with adaptive coefficients\n");
	printf( "Usage: %s @file -i=# -o=# -hh=# {-h=#} -samp=# -ftrain=<fn>\n", PROGNAME);
	printf( "[-fdump=<fn>] [-fdumpin=<fn>] -r=# [-t] [-tdump=#] [-w+=# -w-=#]\n" );
	printf( "[-err=] [-torerr=] [// ...]\n");
	printf( "Example: " );
	printf( "create and train a 2x4x3x1 dimension NN with 10 samples\n");
	printf( "%s -i=2 -o=1 -hh=2 -h=4 -h=3 -err=0.01 ", PROGNAME );
	printf( "-ftrain=input.trn -samp=10\n" );
	printf( "Where:\n" );
	printf( "-i=,-o=     dimension of input/output layer\n" );
	printf( "-hh=        number of hidden layers\n" );
	printf( "-h=         each hidden layer dimension (may be multiple)\n" );
	printf( "-ftrain=    name of train file containing inputs and targets\n" );
	printf( "-fdump=     name of output weights dump file\n" );
	printf( "-fdumpin=   name of input weights dump file (if any)\n");
	printf( "-samp=      number of train input patterns in train file\n" );
	printf( "-r=         report training status interval\n" );
	printf( "-t          time the training (good for non-Unix)\n" );
	printf( "-tdump=     time for periodic dump (specify seconds)\n");
	printf( "-w+=        initial random weight upper bound\n" );
	printf( "-w-=        initial random weight lower bound\n" );
	printf( "-err=       mean square per unit train error ");
	printf( "(def=%f)\n", ERROR_DEFAULT );
	printf( "-torerr=    tolerance error (def=%f)\n", TOLER_DEFAULT);
	exit (0);
}
/*
*-----------------------------------------------------------------------------
*	file:	cparser.c
*	desc:	simple command parser
*	by:	patrick ko
*	date:	22 aug 91 v0.1
*	revi:	26 feb 92 v0.2; response file feature
*	revi:	27 may 92 v0.3; fix the multiple response file bug
*-----------------------------------------------------------------------------
*/

void BPnnet::train_parce()
{
	int	cmd;
	char	rest[128];
	int	resti;
	long	restl;

	while ((cmd = cmdget( rest ))!= -1)
		{

		resti = atoi(rest);
		restl = atol(rest);
		switch (cmd)
			{
			case CMD_DIMINPUT:
				input = resti; break;
			case CMD_DIMOUTPUT:
				output = resti; break;
			case CMD_DIMHIDDENY:
				if (input <= 0 || output <= 0)
					{
					error( NNIOLAYER );
					}
				if (resti > MAXHIDDEN)
					{
					error( NN2MANYLAYER );
					}
				totalhidden = resti; break;
			case CMD_DIMHIDDEN:
				if (hiddencnt >= totalhidden)
					{
					/*
					* hidden layers more than specified
					*/
					break;
					}
				hidden[hiddencnt++] = resti;
				break;
			case CMD_TRAINFILE:
				strcpy( tname, rest );
				break;
			case CMD_TOTALPATT:
				totalpatt = resti;
				break;
			case CMD_DUMPFILE:
				strcpy( dname, rest );
				break;
			case CMD_DUMPIN:
				strcpy( dinname, rest );
				break;
			case CMD_TRAINERR:
				trainerr = atof( rest );
				break;
			case CMD_TOLER:
				TOLER = atof( rest );
				break;
			case CMD_REPORT:
				report = resti;
				break;
			case CMD_TIMER:
				timer = 1;
				break;
			case CMD_TDUMP:
				tdump = restl;
				break;
			case CMD_WPOS:
				UB = atof(rest);
				break;
			case CMD_WNEG:
				LB = atof(rest);
				break;
			case CMD_COMMENT:
				break;
			case CMD_NULL:
				printf( "%s: unknown command [%s]\n", PROGNAME, rest );
				exit (2);
				break;
			}
		}
		if (hiddencnt < totalhidden)
			{
			printf("hiddencnt = %d totalhidden = %d\n", hiddencnt, totalhidden);
			error( NN2MANYHIDDEN );
			}
}

/*
*------------------------------------------------------------------------------
*	funct:	cmdget
*	desct:	get a command either from command line or response file
*	given:	rest = rest of the command line string
*		e.g. if a command is "-example=" and in the command line
*		we have "-example=32787" then rest will contain "32787".
*	retrn:	the command token specified in cparser.h (you defined)
*
*	state table:
*
*		START  GETCMD  GETRSP  SEARCH  RETURN
*	START	x      fsp=0   fsp!=0  x       x
*	GETCMD	x      x       @       not @   no cmd 
*	GETRSP	no cmd x       x       cmd     x
*	SEARCH  x      x       x       x       result
*	RETURN  x      x       x       x       x
*------------------------------------------------------------------------------
*/

int BPnnet::cmdget(char *rest)
{
	int	i, j;
	int	state, result;
	char	cmdstr[129], *rspname;
	static FILE *frsp;

	state = CP_START;
	result = -1;
	*cmdstr = 0;

	while (1)
		{
		switch (state)
		{
		case CP_START:
		if (frsp == NULL)
			state = CP_GETCMDLINE;
		else
			state = CP_GETRSPLINE;
		break;

		case CP_GETCMDLINE:
		if ((cmdcnt >= cmdargc - 1))
			{
			state = CP_RETURN;
			result = -1;
			}
		else
			{
			/* test for response file */
			rspname = *(cmdargv + cmdcnt + 1);
			cmdcnt++;
			if (*rspname == '@')
			{
			rspname++;
				if ((frsp = fopen(rspname, "r")) == NULL)
				{
				fprintf(stderr, "rsp file open fails\n");
				exit (1);
				}
				else
				state = CP_GETRSPLINE;
				}
			else
			{
				strcpy( cmdstr, *(cmdargv + cmdcnt) );
				state = CP_CMDSEARCH;	
			}
			}
		break;

		case CP_GETRSPLINE:
		for (;!strlen(cmdstr) && !feof(frsp);)
			{
			fgets(cmdstr, 128, frsp);
			for (i=j=0; i<strlen(cmdstr); i++)
				{
				if (!isspace(cmdstr[i]))
					{
					cmdstr[j++] = cmdstr[i];
					}
				}
			cmdstr[j] = 0;
			}
		if (feof(frsp))
			{
			fclose(frsp);
			frsp = NULL;
			}
		if (strlen(cmdstr))
			state = CP_CMDSEARCH;
		else 
			state = CP_START;
		break;
	
		case CP_CMDSEARCH:
		result = cmdsearch( cmdstr, rest );
		state = CP_RETURN;
		break;

		case CP_RETURN:
		return (result);
		}
		}
}
/*
*----------------------------------------------------------------------------
*	file:	nnerror.c
*	desc:	define all errors
*	by:	patrick ko
*	date:	2 aug 91
*----------------------------------------------------------------------------
*/


struct error_item 
{
	int	error;
	char *errmsg;
};

static struct error_item errtbl[] =

{
	{ NNMALLOC,	"malloc error" },
	{ NNTFRERR,	"train file reading error" },
	{ NNRFRERR,	"recognition file reading error" },
	{ NNTFIERR,	"train file input error" },
	{ NNIOLAYER,	"input/output layer must be specified first" },
	{ NN2MANYLAYER,	"hidden layer more than specified" },
	{ NN2FEWPATT,	"no training pattern" },
	{ NN2MANYHIDDEN,"too many hidden layers specfied" },
	{ NNOUTNOTOPEN,	"output file cannot be opened" }
};

int BPnnet::error(int errno)
{
	if (errno > 0)
		printf( "nnerror %d: %s\n", errno, errtbl[errno-1].errmsg );
	else
		printf( "nnerror %d\n", errno);
	exit (errno);
}

int BPnnet::gettrainvect(char *tname)
{
	int	i, j, cnt;
	VECTOR	*tmp;
	FILE	*ft;



	ft = fopen( tname, "r" );
	if (ft == NULL)
		{
		error( NNTFRERR );
		}

	inputvect = (VECTOR **) malloc( sizeof(VECTOR *) * totalpatt );
	targtvect = (VECTOR **) malloc( sizeof(VECTOR *) * totalpatt );


	if (totalpatt <= 0)
		{
		error( NN2FEWPATT );
		}
	for (i=0; i<totalpatt; i++)
		{
		/*
		*	allocate input patterns
		*/
		tmp = v_creat( input );
		for (j=0; j<input; j++)
			{
			cnt = fscanf( ft, "%lf", &tmp->vect[j] );
			if (cnt < 1)
				{
				error( NNTFIERR );
				}
			}
		*(inputvect + i) = tmp;

		tmp = v_creat( output );
		for (j=0; j<output; j++)
			{
			cnt = fscanf( ft, "%lf", &tmp->vect[j] );
			if (cnt < 1)
				{
				error( NNTFIERR );
				}
			}
		*(targtvect + i) = tmp;
		}
	fclose( ft );
	return 0;

}
/*
*-----------------------------------------------------------------------------
*	file:	nncreat.c
*	desc:	create a fully connected neural net
*	by:	patrick ko
*	date:	v1.1u - 02 aug 91
*	revi:	v1.2b - 15 jan 92, adaptive coefficients (beta)
*		v1.3u - 17 jan 92, revised data structures
*-----------------------------------------------------------------------------
*/
/*
*=============================================================================
*	funct:	v_creat 
*	dscpt:	create an allocated VECTOR object
*	given:	dim = dimension of the vector
*	retrn:	allocated VECTOR
*=============================================================================
*/

VECTOR * BPnnet::v_creat(INTEGER dim)
{
	VECTOR	*vtmp;
	INTEGER	i;

	if ((vtmp = (VECTOR *)malloc(sizeof(VECTOR))) == NULL)
		{
		error( NNMALLOC );
		}
	else
		{
		DimVect(vtmp) = dim;
		if ((Vect(vtmp) = (REAL *)malloc(sizeof(REAL) * dim)) == NULL)
			{
			error( NNMALLOC );
			}
		else
			{
			v_fill(vtmp, 0.0);
			return (vtmp);
			}
		}

}
/*
*=============================================================================
*	funct:	nn_creat
*	dscpt:	creat an nn object
*	given:	totallayer = total number of hidden and output layers
*		diminput = dimension of inputlayer
*		dimother = dimension of other layers
*	retrn:	allocated NET
*=============================================================================
*/
NET * BPnnet::nn_creat( 
INTEGER		totallayer,
INTEGER		diminput,
INTEGER 	dimoutput,
INTEGER		* dimother)
{
	INTEGER	i;
	INTEGER	dimwt;
	NET	*nntmp;
	INTEGER	dimlayer;

	/* malloc the NET struct */

	if ((nntmp= (NET *)malloc(sizeof(NET))) == NULL)
		{
		error( NNMALLOC );
		}
	else
		{

		/* malloc the LAYER *'s	*/

		DimNet(nntmp) = totallayer;
		if ((nntmp->layer = (LAYER **)malloc(sizeof(LAYER *) * DimNet(nntmp))) == NULL)
			{
			error( NNMALLOC );
			}
		else
			{
			/*
			* dimension of first layer's wgt vector
			* is equal to dimension of input vector
			*/
			dimwt = diminput;

			for (i=0; i<DimNet(nntmp); i++)
				{
				if (i == DimNet(nntmp)-1)
					{
					dimlayer = dimoutput;
					}
				else
					{
					dimlayer = *(dimother + i);
					}

				Layer(nntmp,i) = l_creat( dimlayer, dimwt );

				/*
				* dimension of this layer's wgt vector is equal
				* to dimension of previous layer's out vector
				*/
				dimwt = dimlayer;
				}

			return (nntmp);
			}
		}
}


/*
*=============================================================================
*	funct:	v_fill 
*	dscpt:	fill all dim of a vector with a value
*	given:	v = vector, m = value
*	retrn:	v
*=============================================================================
*/
VECTOR * BPnnet::v_fill( VECTOR	*v, REAL	m )
{
	int	i;

	for (i=0; i<DimVect(v); i++)
		{
		Vi(v,i) = m;
		}
	return (v);
}

/*
*=============================================================================
*	funct:	v_rand
*	dscpt:	fill a vector with random value (default 0.5 - 1.5)
*	given:	v = vector
*	retrn:	v
*=============================================================================
*/
VECTOR *BPnnet::v_rand( VECTOR	*v )
{
	INTEGER	i;

	for (i=0; i<DimVect(v); i++)
		{
		Vi(v,i) = rnd() * (UB-LB) + LB;
		}
	return (v);
}


/*
*=============================================================================
*	funct:	u_creat
*	dscpt:	create an allocated UNIT
*	given:	dimwgtvect = dimension of the unit's weight vector
*	retrn:	allocated UNIT
*=============================================================================
*/
UNIT * BPnnet::u_creat( INTEGER	dimwgtvect )
{
	UNIT	*utmp;

	if ((utmp=(UNIT *)malloc(sizeof(UNIT))) == NULL)
		{
		error(NNMALLOC);
		}
	else
		{
		vWeight(utmp) = v_creat( dimwgtvect );
		v_rand( vWeight(utmp) );
		vdWeight1(utmp) = v_creat( dimwgtvect );
		vdWeight2(utmp) = v_creat( dimwgtvect );
		vDO(utmp) = v_creat( dimwgtvect );

		Out(utmp) = 0.0;
		Net(utmp) = 0.0;
		Dlt(utmp) = 0.0;
		nDlt(utmp)= 0.0;
		Bias(utmp) = rnd() / 5000.0 ;
		dBias1(utmp) = 0.0;
		dBias2(utmp) = 0.0;

		/* allocation successful */
		return (utmp);
		}
}



/*
*=============================================================================
*	funct:	l_creat
*	dscpt:	create an allocated LAYER object
*	given:	dimlayer = number of units in this layer
*		dimwgtvect = dimension of the weight vector of each unit
*	retrn:	allocated LAYER
*=============================================================================
*/
LAYER * BPnnet::l_creat( INTEGER	dimlayer, INTEGER	dimwgtvect )
{
	LAYER	*ltmp;
	INTEGER	i;

	if ((ltmp= (LAYER *)malloc(sizeof(LAYER))) == NULL)
		{
		error(NNMALLOC);
		}
	else
		{
		DimLayer(ltmp) = dimlayer;
		if ((ltmp->unit= (UNIT **)malloc(sizeof(UNIT *) * dimlayer)) == NULL)
			{
			error(NNMALLOC);
			}
		else
			{
			for (i=0; i<dimlayer; i++)
				{
				Unit(ltmp,i) = u_creat( dimwgtvect );
				}

			/* allocation successful */
			return (ltmp);
			}

		}
}
/*
*-----------------------------------------------------------------------------
*	file:		random.c
*	desc:		routine for a very-long-cycle random-number sequences
*	by:		patrick ko shu pui
*	date:		6 sep 1991
*	comment:
*
*	this random number generator was proved to generate random sequences
*	between 0 to 1 which if 100 numbers were calculated every second, it
*	would NOT repeat itself for over 220 years.
*
*	reference:
*
*	Wichmann B.A. and I.D. Hill. "Building A Random Number Generator."
*	Byte Magazine. March 1987. pp.127.
*
*	remark:		this C routine is a freeware
*
*	ko053@cucs19.cs.cuhk.hk	Internet 
*	BiG Programming Club (since 1987), Hong Kong, 6:700/132 FidoNet
*	[852] 654-8751
*-----------------------------------------------------------------------------
*/
/*
*=============================================================================
*	funct:		rnd
*	dscpt:		return a random number of range 0-1
*	given:		nothing
*	retrn:		the random number
*	cmmnt:		you may use prandomize to change the seeds
*=============================================================================
*/
REAL BPnnet::rnd()
{
	REAL	temp;

	/*
	*	first generator
	*/
	x = 171 * (x % 177) - 2 * (x / 177);
	if (x < 0)
		{
		x += 30269;
		}

	/*
	*	second generator
	*/
	y = 172 * (y % 176) - 35 * (y / 176);
	if (y < 0)
		{
		y += 30307;
		}

	/*
	*	third generator
	*/
	z = 170 * (z % 178) - 63 * (z / 178);
	if (z < 0)
		{
		z += 30323;
		}

	/*
	*	combine to give function value
	*/
	temp = x/30269.0 + y/30307.0 + z/30323.0;

	return (temp - (INT)temp);
}
/*
*=============================================================================
*	funct:		rndmize
*	dscpt:		generating random number seeds
*	given:		nothing
*	retrn:		nothing
*=============================================================================
*/
INT BPnnet::rndmize()
{
	time_t	timer;

	x = time( &timer ) % MAXINT;
	y = (x * x) % MAXINT;
	z = (y * y) % MAXINT;

	return 0;
}

/*
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
* * *				E X A M P L E
* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
*/
/*
int main()
{
	int 	i;

	rndmize();

	for (i=0; i<100; i++)
		{
		printf("%f,", rnd() );
		}
}
*/

CMDTBL	cmdtbl[] =
	{
	{CMD_DIMINPUT,		"-i="},
	{CMD_DIMOUTPUT,		"-o="},
	{CMD_DIMHIDDENY,	"-hh="},
	{CMD_DIMHIDDEN,		"-h="},
	{CMD_TRAINFILE,		"-ftrain="},
	{CMD_TOTALPATT,		"-samp="},
	{CMD_DUMPIN,		"-fdumpin="},
	{CMD_DUMPFILE,		"-fdump="},
	{CMD_RECOGFILE,		"-frecog="},
	{CMD_OUTFILE,		"-fout="},
	{CMD_TRAINERR,		"-err="},
	{CMD_TOLER,		"-torerr="},
	{CMD_REPORT,		"-r="},
	{CMD_TDUMP,		"-tdump="},
	{CMD_TIMER,		"-t"},
	{CMD_WPOS,		"-w+="},
	{CMD_WNEG,		"-w-="},
	{CMD_COMMENT,		"//"}
	};


int BPnnet::cmdsearch(char *str, char *rest)
{
	int	i, l;
	
	for (i=0; i<cmdtblsize; i++)
		{
		l = strlen( cmdtbl[i].cmdstr );
		if (!memcmp(str, cmdtbl[i].cmdstr, l))
			{
			strcpy( rest, str + l );
			return (cmdtbl[i].cmdno);
			}
		}
	strcpy( rest, str );
	return (CMD_NULL);
}

int BPnnet::cmdinit(int argc, char **argv)
{
	cmdtblsize = sizeof(cmdtbl) / sizeof(cmdtbl[0]);
	cmdargc = argc;
	cmdargv = argv;
	return 0;
}
/*
*-----------------------------------------------------------------------------
*	file:	timer.c
*	desc:	time a program in secs
*	by:	patrick ko
*	date:	18 jan 92
*-----------------------------------------------------------------------------
*/
void BPnnet::timer_restart()
{
	time( &last );

}

long int BPnnet::timer_stop()
{
	time( &This );
	temp = This - last;
	last = This;

	return ((long int)temp);
}
/*
*-----------------------------------------------------------------------------
*	file:	nntrain.c
*	desc:	train a fully connected neural net by backpropagation
*	by:	patrick ko
*	date:	2 aug 91
*	revi:	v1.2b - 15 jan 92, adaptive coefficients
*		v1.3u - 18 jan 92, revised data structures
*		v1.31u - 20 jan 92, periodic dump, weights retrieval
*-----------------------------------------------------------------------------
*/


/*
*=============================================================================
*	funct:	nnbp_train
*	dscpt:	train a neural net using backpropagation
*	given:	net = the neural net
*		inpvect = 1 input vector ( 1 train pattern )
*		tarvect = 1 target vector ( 1 target pattern )
*		np = number of patterns
*		err = error
*		eta, momentum
*		report = dump info interval (no.of train cycles), 0=not dump
*		tdump = no of seconds for periodic dump, 0=not dump
*		dfilename = period dump file name
*	retrn:	measure of error
*=============================================================================
*/
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
				char * dfilename )
{
	REAL	Error;
	REAL	Error_pre;
	INTEGER	cnt;
	time_t	lasttime, thistime;
	FILE	*fdump;


	cnt = 0;
	REPINTERVAL = report;
	ETA = eta;
	MOMENTUM = momentum;
	Error_pre = MAXFLOAT;
	Error = MAXFLOAT;
	if (tdump)
		time(&lasttime);

	while (Error > err)
		{
		cnt++;
		Error = nnbp_train1( net, inpvect, tarvect, np, Error );

		if (report)
			nnbp_report(cnt, Error);
		if (tdump)
			{
			if (((thistime = time(&thistime)) - lasttime) >= tdump)
				{
				fdump = fopen( dfilename, "w" );
				nn_dump( fdump, net );
				fclose(fdump);
				lasttime = thistime;
				}
			}
		if(Error < 0.0)
		{
			printf("break zero step\n");
			break;
		}
		Error_pre = Error;
		}
	printf("Error = %f\n", Error);
	return (Error);
}

/*
*=============================================================================
*	funct:	nnbp_report
*	dscpt:	print report lines to terminal
*	given:	cnt = number of train cycles
*		error = overall energy
*	retrn:	nothing
*=============================================================================
*/
void BPnnet::nnbp_report(INTEGER cnt, REAL error )
{
	if (!(cnt%REPINTERVAL))
		{
		printf("nntrain: cycle= %d, MSE/Unit =%4.12f\n", cnt, error );
		fflush(stdout);
		}
}

/*
*=============================================================================
*	funct:	nnbp_train1
*	dscpt:	train a neural net 1 cycle using backpropagation
*	given:	net = the neural net
*		inpvect = 1 set of input vectors
*		tarvect = 1 set of target vectors
*		np = number of patterns
*		LastError = energy at last cycle
*	retrn:	measure of error after this train cycle
*=============================================================================
*/
REAL BPnnet::nnbp_train1(NET	* net, VECTOR	** inpvect, VECTOR	** tarvect, INTEGER	np, REAL LastError )
{
	REAL	Error;
	INTEGER	i;
	INTEGER	fire=0;

	Error = 0.0;
	nnbp_init( net );
	for (i=0; i<np; i++)
		{
		nnbp_forward( net, *(inpvect + i));
		Error += nnbp_backward( net, *(inpvect + i), *(tarvect + i));
		}
	Error = Error / np / DimNetOut(net);
	/*
	* coefficients adaptation and dWeight calculations
	*/
	if (Error <= LastError + TOLER )
		{

		/* weights will be updated, go ahead */

		fire = 1;
		nnbp_coeffadapt( net );
		nnbp_dweightcalc( net, np, fire );
		if(Error == LastError)
		{
			printf("break1\n");
			return (-1.0);
		}
		return (Error);
		}
	else
		{

		/* weights will not be updated, backtrack */
printf("/* weights will not be updated, backtrack */\n");
		fire = 0;
		ETA *= BACKTRACK_STEP;		/* half the ETA */
		ETA = ground(ETA,ETA_FLOOR);
		MOMENTUM = ETA * LAMBDA;
		nnbp_dweightcalc( net, np, fire );
		return (LastError);
		}
}

/*
*=============================================================================
*	funct:	nnbp_forward (pass)
*	dscpt:	forward pass calculation
*	given:	net = the neural net
*		inpvect = 1 input vector ( 1 train pattern )
*	retrn:	nothing
*	cmmnt:	net's output Out(J) calculated at every unit
*=============================================================================
*/
void BPnnet::nnbp_forward( NET	*net, VECTOR	*inpvect )
{
	LAYER	*I, *input;
	UNIT	*J;
	INTEGER	i, j, k;
	REAL	sum, out;

	/* phase 1 - forward compute output value Out's */

	input = NULL;

	/* For each layer I in the network */

	for (i=0; i<DimNet(net); i++)
		{
		I = Layer(net,i);

		/* For each unit J in the layer */

		for (j=0; j<DimLayer(I); j++)
			{
			J = Unit(I,j);
			Net(J) = Bias(J) + dBias1(J); /* add bias */
			for (k=0; k<DimvWeight(J); k++)
				{
				if (i==0)
					out = Vi(inpvect,k);
				else
					out = Out(Unit(input,k));

				Net(J) += (Weight(J,k) + dWeight1(J,k)) * out;
				}
			Out(J) = sigmoid(Net(J));
//printf("%f ", Net(J));
//printf("%f ", Out(J));
			}
		input = I;
//printf("\n");
///fflush(stdout);
	}
}


void BPnnet::nnbp_init( NET	*net )
{
	LAYER	*I;
	UNIT	*J;
	INTEGER	i, j, k;

	i = DimNet(net);

	while (i--)
		{
		I = Layer(net,i);
		for (j=0; j<DimLayer(I); j++)
			{
			J = Unit(I,j);
			nDlt(J) = 0.0;
			for (k=0; k<DimvWeight(J); k++)
				{
				DO(J,k) = 0.0;
				}
			}
		}
}

/*
*=============================================================================
*	funct:	nnbp_backward
*	dscpt:	backward pass calculation
*	given:	net = the neural net
*		inpvect = 1 input vector ( 1 train pattern )
*		tarvect = 1 target vector
*	retrn:	Ep * 2
*	cmmnt:	net's weight and bias adjusted at every layer
*=============================================================================
*/
REAL BPnnet::nnbp_backward(NET	* net, VECTOR	*inpvect, VECTOR	*tarvect )
{
	LAYER	*I, *F, *B;
	UNIT	*J, *JF;
	INTEGER	i, j, k;
	REAL	sum, out;
	REAL	Ep, diff;

	Ep = 0.0;

	/*
	*	phase 2 - target comparison and back propagation
	*/
	i = DimNet(net) - 1;
	F = I = Layer(net,i);
	B = Layer(net,i - 1);

	/*
	*	Delta rule 1 - OUTPUT LAYER
	*	dpj = (tpj - opj) * f'(netpj)
	*/
	for (j=0; j<DimLayer(I); j++)
		{
		J = Unit(I,j);
		diff = Vi(tarvect,j) - Out(J);
		Dlt(J) = diff * Out(J) * (1.0 - Out(J));

		nDlt(J) += Dlt(J);	/* accumulate Dpj's */

		for (k=0; k<DimvWeight(J); k++)
			{
			if (i==0)
				out = Vi(inpvect,k);
			else
				out = Out(Unit(B,k));
			DO(J,k) += Dlt(J) * out;
			}

		Ep += diff * diff;
		}

	--i;
	while (i >= 0)
		{
		I = Layer(net,i);		/* current layer */
		B = Layer(net,i - 1);
		/*
		*	delta rule 2 - HIDDEN LAYER:
		*	dpj = f'(netpj) * SUMMATEk( Dpk * Wkj )
		*/
		for (j=0; j<DimLayer(I); j++)
			{
			J = Unit(I,j);
			sum = 0.0;
			for (k=0; k<DimLayer(F); k++)
				{
				JF = Unit(F,k);
				sum += Dlt(JF) * (Weight(JF,j)+dWeight1(JF,j));
				}
			Dlt(J) = Out(J) * (1.0 - Out(J)) * sum;
			nDlt(J) += Dlt(J);

			for (k=0; k<DimvWeight(J); k++)
				{
				if (i==0)
					out = Vi(inpvect,k);
				else
					out = Out(Unit(B,k));
				DO(J,k) += Dlt(J) * out;
				}
			}
		F = I;
		i--;
		}

	return (Ep);
}

void BPnnet::nnbp_coeffadapt(NET	* net )
{
	LAYER	*I, *B;
	UNIT	*J;
	INTEGER	n, i, j, k;
	REAL	EW, ME, MW, costh;

	EW = ME = MW = 0.0;
	i = DimNet(net);

	while (i--)
		{
		I = Layer(net,i);
		for (j=0; j<DimLayer(I); j++)
			{
			J = Unit(I,j);
			for (k=0; k<DimvWeight(J); k++)
				{
				ME += DO(J,k) * DO(J,k);
				MW += dWeight1(J,k) * dWeight1(J,k);
				EW += DO(J,k) * dWeight1(J,k);
				}
			}
		}

	ME = sqrt(ME);		/* modulus of cost funct vector E */
	MW = sqrt(MW);		/* modulus of delta weight vector dWn-1*/

	ME = ground(ME,ME_FLOOR);		/* constraints */
	MW = ground(MW,MW_FLOOR);		/* constraints */

	costh = EW / (ME * MW);

	/* coefficients adaptation !!! */

	ETA = ETA * (1.0 + 0.5 * costh);
	ETA = ground(ETA,ETA_FLOOR);
	LAMBDA = LAMBDA0 * ME / MW;
	MOMENTUM = ETA * LAMBDA;
}

void BPnnet::nnbp_dweightcalc( NET	*net,INTEGER np, INTEGER fire )
{
	LAYER	*I;
	UNIT	*J;
	INTEGER	n, i, j, k;

	i = DimNet(net);

	/* calculate dWeights for every unit */

	while (i--)
		{
		I = Layer(net,i);
		for (j=0; j<DimLayer(I); j++)
			{
			J = Unit(I,j);
			nDlt(J) /= np;
			for (k=0; k<DimvWeight(J); k++)
				{
				DO(J,k) /= np;
				if (fire)
					{
					/* commit weight change */
					Weight(J,k) += dWeight1(J,k);

					/* dW n-2 = dW n-1 */
					dWeight2(J,k) = dWeight1(J,k);
					}
				dWeight1(J,k) = ETA * DO(J,k) + MOMENTUM * dWeight2(J,k);

				}
			if (fire)
				{
				Bias(J) += dBias1(J);
				dBias2(J) = dBias1(J);
				}
			dBias1(J) = ETA * nDlt(J) + MOMENTUM * dBias2(J);
			}
		}
}
/*
*-----------------------------------------------------------------------------
*	file:	nndump.c
*	desc:	dump structures in nntype.h
*	by:	patrick ko
*	date:	13 aug 1991
*	revi:	v1.2b - 15 jan 1992, coefficient adaptation
*		v1.3u - 18 jan 1992, revised data structures
*-----------------------------------------------------------------------------
*/
void	BPnnet::v_dump( FILE	*fp, VECTOR	*vp)
{
	INTEGER	i;

	for (i=0; i<DimVect(vp); i++)
		{
		fprintf( fp, "%f ", vp->vect[i] );
		}

	fprintf( fp, "\n" );
}

void	BPnnet::v_load( FILE	*fp, VECTOR	*vp )
{
	INTEGER	i;

	for (i=0; i<DimVect(vp); i++)
		{
		fscanf( fp, "%lf ", &vp->vect[i] );
		}
}

void	BPnnet::u_dumpweight( FILE	*fp, UNIT	*unit )
{
	v_dump( fp, vWeight(unit) );
	fprintf(fp, "%f \n", Bias(unit));
}

void	BPnnet::u_loadweight(FILE	* fp, UNIT	*unit )
{
	v_load( fp, vWeight(unit) );
	fscanf(fp, "%lf \n", &Bias(unit));
}

void	BPnnet::l_dump(FILE	* fp, LAYER	*ly )
{
	INTEGER	i;

	for (i=0; i<DimLayer(ly); i++)
		{
		u_dumpweight( fp, Unit(ly,i) );
		}

}

void	BPnnet::l_load( FILE	*fp, LAYER	*ly )
{
	INTEGER	i;

	for (i=0; i<DimLayer(ly); i++)
		{
		u_loadweight( fp, Unit(ly,i) );
		}
}

void	BPnnet::nn_dump(FILE	* fp, NET	*nn )
{
	INTEGER	i;


	for (i=0; i<DimNet(nn); i++)
	{
		l_dump( fp, Layer(nn,i) );
	}
	for (int j=0; j<input; j++)
	{
		// min and delta for inputs
		v_dump(fp,inputzoom[j]);
	}
	for (j=0; j<output; j++)
	{
		// min and delta for outputs
		v_dump(fp,targtzoom[j]);
	}
	
}

void	BPnnet::nn_load( FILE	*fp, NET	*nn )
{
	INTEGER	i;

	for (i=0; i<DimNet(nn); i++)
		{
		l_load( fp, Layer(nn,i) );
		}
	//============================================================================
	//============================================================================
	// готовим вектора значений, необходимых для масштабирования входов и выходов
	inputzoom = (VECTOR **) malloc( sizeof(VECTOR *) * input );
	targtzoom = (VECTOR **) malloc( sizeof(VECTOR *) * output );
	VECTOR * tmp;
	for (int j=0; j<input; j++)
	{
		tmp = v_creat( 2 );
		*(inputzoom + j) = tmp;
	}
	for (j=0; j<output; j++)
	{
		tmp = v_creat( 2 );
		*(targtzoom + j) = tmp;
	}
	//============================================================================
	//============================================================================
	//============================================================================
	for (j=0; j<input; j++)
	{
		// min and delta for inputs
		v_load(fp,inputzoom[j]);
	}
	for (j=0; j<output; j++)
	{
		// min and delta for outputs
		v_load(fp,targtzoom[j]);
	}
}

void	BPnnet::nn_dumpout(FILE	* fp, NET	*nn )
{
	INTEGER	i, j;
	LAYER	*I;
	UNIT	*J;
	REAL out_value;

	I = Layer(nn,DimNet(nn)-1);
	// zooming
	for (j=0; j<DimLayer(I); j++)
		{
		J = Unit(I,j);
		out_value = Out(J);
		//================================
		// dezooming of output
		min		= targtzoom[j]->vect[0];
		delta	= targtzoom[j]->vect[1];
		out_value = min + delta*(out_value - ao) / (bo - ao);
		//================================
		fprintf( fp, "%f ",  out_value);
		}
	fprintf( fp, "\n" );
}

int BPnnet::train_main(int argc, char **argv)
{
	NET	*nn;
	FILE	*fdump;
	
	printf("train_main argc = %d\n", argc);

	if (argc < 2)
		{
		train_usage();
		}
	else
		{
		cmdinit( argc, argv );
		train_parce();
		}

	/* create a neural net */
	//============================================================================
	//============================================================================
	//============================================================================
	int i, j;
	printf("totalpatt = %d\ntotalhidden = %d input = %d output = %d\n",
		totalpatt, totalhidden, input, output);

	for (j = 0; j < totalhidden; j++)
		printf("hidden[%d] = %d\n", j, hidden[j]);
	//============================================================================
	//============================================================================
	//============================================================================
	nn = nn_creat( totalhidden + 1, input, output, hidden );
	//============================================================================
	//============================================================================
	//============================================================================
	printf("tname = %s\n", tname);
	//============================================================================
	//============================================================================
	//============================================================================
	gettrainvect( tname );
	//============================================================================
	//============================================================================
	zoomtrainvect();
	//============================================================================

	/* read last dump, if any */
	if (*dinname != NULL)
	{
		printf( "%s: opening dump file [%s] ...\n", PROGNAME, dinname);
		if ((fdump = fopen( dinname, "r" )) != NULL)
		{
			nn_load( fdump, nn );
			fclose( fdump );
		}
	}

	printf( "%s: start\n", PROGNAME );

	if (timer)
		timer_restart();
	/*
	* the default training error, ..., etc can be incorporated into
	* the interface - if you like.
	*/
	nnbp_train( nn, inputvect, targtvect, totalpatt,
	trainerr, ETA_DEFAULT, ALPHA_DEFAULT, report, tdump, dname );

	if (timer)
		printf("%s: time elapsed = %ld secs\n", PROGNAME, timer_stop());

	printf( "%s: dump neural net to [%s]\n", PROGNAME, dname );

	fdump = fopen( dname, "w" );
	nn_dump( fdump, nn );
	fclose(fdump);
	//==============================================================
	//==============================================================
	//==============================================================
	FILE *fout;
	fout = fopen( ofilename, "w" );
	if (fout == NULL)
		{
		error (NNOUTNOTOPEN);
		}
	for (i=0; i<totalpatt; i++)
		{
//printf("i = %d\n",i);
//flash();
//char jjj;
//scanf("%c", &jjj);
		nnbp_forward( nn, *(inputvect + i) );
		nn_dumpout( fout, nn );
		nn_dumpout2(i, fout, nn );

		}
	fclose( fout );
	return 0;
}

int BPnnet::recog_usage()
{
	printf( "%s %s - by %s\n", PROGNAME, VERSION, AUTHOR );
	printf( "(C)Copyright 1992 All Rights Reserved. %s\n\n", DATE );
	printf( "Description: backprop neural net recognition\n");
	printf( "Usage:\n%s @file -i=# -o=# -hh=# {-h=#} -samp=# -frecog=<fn> [-fdump=<fn>] -fout=<fn>\n\n", PROGNAME );
	printf( "Examples:\n" );
	printf( "Recognize 2 patterns in myinput.rgn with the NN created in bptrain example 1\n" );
	printf( "and generate a result file result.out:\n" );
	printf( "%s -i=2 -o=1 -hh=2 -h=3 -h=4 -samp=2 -frecog=myinput.rgn -fout=result.out\n", PROGNAME );
	printf( "\n" );
	printf( "Where\n\n" );
	printf( "-i=         dimension of input layer\n" );
	printf( "-o=         dimension of output layer\n" );
	printf( "-hh=        number of hidden layers\n" );
	printf( "-h=         each hidden layer dimension (may be multiple)\n" );
	printf( "-samp=      number of train input patterns in train file\n" );
	printf( "-frecog=    name of recog file containing inputs\n" );
	printf( "-fdump=     name of neural net file dumped by bptrain\n" );
	printf( "-fout=      name of recognition result file\n" );
	exit (1);
}

int BPnnet::recog_parse()
{
	int	cmd;
	char	rest[128];
	int	resti;

	while ((cmd = cmdget( rest ))!= -1)
		{
		resti = atoi(rest);
		switch (cmd)
			{
			case CMD_DIMINPUT:
				input = resti; break;
			case CMD_DIMOUTPUT:
				output = resti; break;
			case CMD_DIMHIDDENY:
				if (input <= 0 || output <= 0)
					{
					error( NNIOLAYER );
					}
				if (resti > MAXHIDDEN)
					{
					error( NN2MANYLAYER );
					}
				totalhidden = resti; break;
			case CMD_DIMHIDDEN:
				if (hiddencnt >= totalhidden)
					{
					/*
					* hidden layers more than specified
					*/
					break;
					}
				hidden[hiddencnt++] = resti;
				break;
			case CMD_RECOGFILE:
				strcpy( tfilename, rest );
				break;
			case CMD_TOTALPATT:
				totalpatt = resti;
				break;
			case CMD_DUMPFILE:
				strcpy( dfilename, rest );
				break;
			case CMD_OUTFILE:
				strcpy( ofilename, rest );
				break;
			case CMD_COMMENT:
				break;
			case CMD_NULL:
				printf( "unknown command [%s]\n", rest );
				exit (2);
				break;
			}
		}
		if (hiddencnt < totalhidden)
			{
			error( NN2MANYHIDDEN );
			}
	return 0;
}

int BPnnet::getrecogvect(char *recogfile)
{
	int	i, j, cnt;
	VECTOR	*tmp;
	FILE	*ft;


	ft = fopen( recogfile, "r" );
	if (ft == NULL)
		{
		error( NNRFRERR );
		}

	inputvect = (VECTOR **) malloc( sizeof(VECTOR *) * totalpatt );

	for (i=0; i<totalpatt; i++)
		{
		/*
		*	allocate input patterns
		*/
		tmp = v_creat( input );
		for (j=0; j<input; j++)
			{
			cnt = fscanf( ft, "%lf", &tmp->vect[j] );
			if (cnt < 1)
				{
				error( NNTFIERR );
				}
			}
		*(inputvect + i) = tmp;
		}
	fclose( ft );
	return 0;
}

int BPnnet::recog_main(int argc, char **argv)
{
	INTEGER	i;
	NET	*nn;
	FILE	*fdump, *fout;

	if (argc < 2)
		{
		recog_usage();
		}
	else
		{
		cmdinit( argc, argv );
		recog_parse();
		}

	/*
	*	create a neural net
	*/
	nn = nn_creat( totalhidden + 1, input, output, hidden );

	printf( "opening dump file [%s] ...\n", dfilename );
	fdump = fopen( dfilename, "r" );
	nn_load( fdump, nn );
	fclose( fdump );

	printf( "start recognizing...\n" );
	getrecogvect( tfilename );
	//============================================================================
	//============================================================================
	//============================================================================
	// zooming
	int j;
	for (i = 0; i < totalpatt; i++)
	{
		for (j=0; j<input; j++)
		{
			min		= inputzoom[j]->vect[0];
			delta	= inputzoom[j]->vect[1];
			inputvect[i]->vect[j] = 
				ai + (bi - ai)*(inputvect[i]->vect[j] - min) / delta;
		}
	}
	//============================================================================
	//============================================================================
	//============================================================================

	fout = fopen( ofilename, "w" );
	if (fout == NULL)
		{
		error (NNOUTNOTOPEN);
		}
	for (i=0; i<totalpatt; i++)
		{
		nnbp_forward( nn, *(inputvect + i) );
		nn_dumpout( fout, nn );
		}
	fclose( fout );
	return 0;

}

void BPnnet::zoomtrainvect()
{
	INTEGER i, j;
	//============================================================================
	// готовим вектора значений, необходимых для масштабирования входов и выходов
	inputzoom = (VECTOR **) malloc( sizeof(VECTOR *) * input );
	targtzoom = (VECTOR **) malloc( sizeof(VECTOR *) * output );
	VECTOR * tmp;
	for (j=0; j<input; j++)
	{
		tmp = v_creat( 2 );
		*(inputzoom + j) = tmp;
	}
	for (j=0; j<output; j++)
	{
		tmp = v_creat( 2 );
		*(targtzoom + j) = tmp;
	}
	//============================================================================
	//============================================================================
	//============================================================================
	for (i = 0; i < totalpatt; i++)
	{
		for (j=0; j<input; j++)
		{
			if (i == 0)
			{
				// min
				inputzoom[j]->vect[0] = inputvect[i]->vect[j];
				// max
				inputzoom[j]->vect[1] = inputvect[i]->vect[j];
			}
			else
			{
				// min
				if (inputzoom[j]->vect[0] > inputvect[i]->vect[j])
					inputzoom[j]->vect[0] = inputvect[i]->vect[j];
				// max
				if (inputzoom[j]->vect[1] < inputvect[i]->vect[j])
					inputzoom[j]->vect[1] = inputvect[i]->vect[j];
			}
		}
		for (j=0; j<output; j++)
		{
			if (i == 0)
			{
				// min
				targtzoom[j]->vect[0] = targtvect[i]->vect[j];
				// max
				targtzoom[j]->vect[1] = targtvect[i]->vect[j];
			}
			else
			{
				// min
				if (targtzoom[j]->vect[0] > targtvect[i]->vect[j])
					targtzoom[j]->vect[0] = targtvect[i]->vect[j];
				// max
				if (targtzoom[j]->vect[1] < targtvect[i]->vect[j])
					targtzoom[j]->vect[1] = targtvect[i]->vect[j];
			}
		}
	}
	//============================================================================
	//============================================================================
	for (j=0; j<input; j++)
	{
		// from max to delta
		inputzoom[j]->vect[1] -= inputzoom[j]->vect[0];
	}
	for (j=0; j<output; j++)
	{
		// from max to delta
		targtzoom[j]->vect[1] -= targtzoom[j]->vect[0];
	}
	//============================================================================
	//============================================================================
	//============================================================================
	//============================================================================
	// zooming

	for (i = 0; i < totalpatt; i++)
	{
		for (j=0; j<input; j++)
		{
			min		= inputzoom[j]->vect[0];
			delta	= inputzoom[j]->vect[1];
			inputvect[i]->vect[j] = 
				ai + (bi - ai)*(inputvect[i]->vect[j] - min) / delta;
#if 0
			printf("zoomed input[%d][%d] = %f\n", i, j, inputvect[i]->vect[j]);
#endif
		}
		for (j=0; j<output; j++)
		{
			min		= targtzoom[j]->vect[0];
			delta	= targtzoom[j]->vect[1];
			targtvect[i]->vect[j] = 
				ao + (bo - ao)*(targtvect[i]->vect[j] - min) / delta;
#if 0
			printf("zoomed targt[%d][%d] = %f\n", i, j, targtvect[i]->vect[j]);
#endif
		}
	}
	//============================================================================
	//============================================================================

}

void BPnnet::nn_dumpout2(INTEGER	i, FILE *fp, NET *nn)
{
	INTEGER	j;
	LAYER	*I;
	UNIT	*J;
	REAL out_value, targ_value;

	I = Layer(nn,DimNet(nn)-1);
	// zooming
	for (j=0; j<DimLayer(I); j++)
		{
		J = Unit(I,j);
		out_value = Out(J);
		//================================
		// dezooming of output
		min		= targtzoom[j]->vect[0];
		delta	= targtzoom[j]->vect[1];
		out_value = min + delta*(out_value - ao) / (bo - ao);
		//================================
		targ_value = min + delta*(targtvect[i]->vect[j] - ao) / (bo - ao);
		//================================
		printf( "%f %f %f\t",  out_value, targ_value, out_value - targ_value);
		}
	printf( "\n" );

}

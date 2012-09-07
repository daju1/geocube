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

/*
*	#define your own commands here starting from 1
*	-* modifiable *-
*/

#define	CMD_INPUT			1
#define	CMD_OUTPUT_COEF		2
#define	CMD_OUTPUT_RECON	3
#define	CMD_WAV_FILTER		4
#define	CMD_WAV_ORDER		5
#define	CMD_WAV_ORDER2		6
#define	CMD_MAXLEVEL		7
#define CMD_NCOL	     	8
#define	CMD_NTCOL			9
#define	CMD_IDELIMID	   	10
#define	CMD_ODELIMID		11
#define	CMD_TOLER	    	12
#define	CMD_REPORT	    	13
#define CMD_TIMER	    	14
#define CMD_TDUMP	    	15
#define	CMD_WPOS	    	16
#define	CMD_WNEG		    17
#define	CMD_COMMENT	    	18

#define	NNMALLOC	0
#define NNTFRERR	1
#define NNTFIERR	2
#define NNIOLAYER	3
#define NN2MANYLAYER	4
#define NN2FEWPATT	5
#define	NN2MANYHIDDEN	6
#define	NNOUTNOTOPEN	7
#define	NNRFRERR	8

#ifdef	__TURBOC__

int	cmdsearch		(char *, char *);
int	cmdinit			(int, char **);
int 	cmdget			(char *);

#else

//int	cmdsearch		( );
//int	cmdinit			( );
//int 	cmdget			( );
int	cmdsearch		(char *, char *);
int	cmdinit			(int, char **);
int 	cmdget			(char *);

#endif

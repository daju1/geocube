/******************************************************************************/
/*                                                                            */
/*            ROUTINES FOR MULTIPLE NEURAL NETWORKS MANAGEMENT                */
/*       (routines for ERROR BACK PROPAGATION training are included)          */
/*                                                                            */
/*                      Version  3.2 (32 bits/16 bits)                        */
/*                       Copyright by Daniele Denaro                          */
/******************************************************************************/

/* Switch depending on hardware and compilators */
/* B16 (DOS ) B32 (DOS 32 bits ,UNIX etc.) */

//# define B16                      /* modify depending on hardware or compil.  */
# define B32                      /* modify depending on hardware or compil.  */

/******************************************************************************/
/*                                                                            */
/*  Abstract of library   functionalities :                                   */
/*     - Nets create   in memory ; one or more nets different too             */
/*     - Save and load all nets on/from file                                  */
/*     - Net compute (input propagate)                                        */
/*     - Net training with  EBP (Error Back Propagation)                      */
/*                                                                            */
/*  Each net can have any number of layers .                                  */
/*                                                                            */
/*  Each layer can have any number of nodes .                                 */
/*                                                                            */
/*  Each node can have any number of links with others nodes .                */
/*                                                                            */
/*  Nodes are automatically numbered with progressive number in net .         */
/*                                                                            */
/*  One can choose a different activation function for each node. There are   */
/*  ten types of activation function : 6 defined and 3 for user definition.   */
/*  For each node it's also possible to define another function, named action,*/
/*  which is called after the activation function.                            */
/*                                                                            */
/*                                                                            */
/*  Range of principals values                                                */
/*                                                                            */
/*  Maximum values:                                                           */
/*                                                                            */
/*     - Maximum net number     : 1000 (in this release)                      */
/*     - Maximum layer number   : 99  (in  a  net)                            */
/*     - Maximum node number    : 7FFFFFFF(hex) (in a net)                    */
/*                                                                            */
/*  Minimum values:                                                           */
/*                                                                            */
/*     - First net              : 1                                           */
/*     - First layer in a net   : 0 (input layer)                             */
/*     - First node  in a net   : 1                                           */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   Neural network architecture:                                             */
/*                                                                            */
/*                                                                            */
/*   Network m                                                                */
/*             /|\                                                            */
/*   Layer n    |                                                             */
/*       ---------------            Each layer is automatically linked with   */
/*             /|\                  next layer and all nodes of layer i are   */
/*              |                   linked with all nodes of layer i+1.       */
/*    ----------------------                                                  */
/*              :                   Network creation :                        */
/*              :                   - by function <createnet> ;               */
/*              :                     we however need to define the structure */
/*   Layer 1    :                     of all nets list,first by <createstruct>*/
/*    ----------------------          This structure can be defined if we know*/
/*             /|\                    the total number of nets and the maximum*/
/*   Layer 0    |                     layer number for each net.              */
/*     --------------------         - it's also possible to define the struct.*/
/*             /|\                    of net list and all nets in the same    */
/*              |                     time,by the function <creteallnet> , if */
/*                                    the nets have the same size.            */
/*                                  - we can save or load all nets by function*/
/*                                    <savenet> or <loadnet> .                */
/*   Layer i                          That  functions are relative to all nets*/
/*             /|\                    but the total number of nets can be     */
/*   Node k     |                     reduced by the function <wmnet>.        */
/*    +-------------------+           Nets loading doesn't need structure of  */
/*    |       status      |           nets list and overwrite it if exist.    */
/*    |--activ. function--|.......                                            */
/*    |        inp        |                                                   */
/*    +-------------------+                                                   */
/*             /|\                  Other warning on creation functions:      */
/*              |                   for default , weights are initialised with*/
/*                                  a random value between -.4 and +.4, and   */
/*                                  bias for all nodes are 0.                 */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/* Warning:                                                                   */
/*    although the library is optimized for simple forward networks, it's     */
/*    possible create and manage very complex network using functions for     */
/*    single node or single layer.                                            */
/*    Version 4 was implemented for optimize manage for complex network       */
/*    (ie. complex layers links, contest memory, recursive link etc.)         */
/******************************************************************************/

/******************************************************************************/
/*                                                                            */
/*   Net elaboration and training                                             */
/*                                                                            */
/*   Forward propagation:                                                     */
/*                                                                            */
/*   Basic function is <propagate> ; this function forward propagate net from */
/*   layer A to layer  B.                                                     */
/*   For each node of a layer the activation function is calculated on input  */
/*   value and result (status of activation) is added at input of pointed node*/
/*   after scaling by weight factor.                                          */
/*                                                                            */
/*   The function <compute> is more general; she call previous function       */
/*   between first and last layer. We have to supply input values and after   */
/*   we can obtain the output values.                                         */
/*                                                                            */
/*   <produce> is the most general function    ; she need file of input values*/
/*   and produce a file of ouput values.                                      */
/*   Input file format : n-ple of input values (corresp. at n inp. of layer 0)*/
/*                                                                            */
/*                                                                            */
/*   Backward training :                                                      */
/*                                                                            */
/*   Basic function is <backprop> ; this function apply the EBP rule from     */
/*   layer B to layer A .                                                     */
/*   For each node of a layer the error value is calculated on basis of error */
/*   at next layer and at the same time weigts  are corrected     .           */
/*   At end , error at layer A is loss.                                       */
/*   We can backpropagate only error without weigts correction by function    */
/*   <backproperr> instead of previous function; but in this case we must use */
/*   the function <cancerr> after, because buffers for forward and backward   */
/*   are partially coincident .                                               */
/*   For default bias is not modified , but it's possible do it by function   */
/*   <param> . By this function it's possible also modify   the learning and  */
/*   moment coefficients (for default 0.8 and 0.5) .                          */
/*                                                                            */
/*   Function <learn> is more general ; she call previous function for all    */
/*   layer of net.                                                            */
/*                                                                            */
/*   <train> is the most general function ; she need the trainer file  and    */
/*   produce average quadratic error. She reed the trainer file for ep times  */
/*   (where ep = 1 for default) .                                             */
/*   Trainer file format : n-pla (input values)   m-pla (exact out values)    */
/*   (where n = nodes at layer 0  , m= nodes at last layer )                  */
/*                                                                            */
/*                                                                            */
/*                                                                            */
/******************************************************************************/

//#define float double

# ifdef B16
# define far far
# define LONG long
# define CLOCK_PS 18.2
# define ALLOCA farcalloc
# define LIBERA farfree
# include <dos.h>
# include <malloc.h>
# endif

# ifdef B32
# define far
# define LONG  int
# define ALLOCA calloc
# define LIBERA free
# define CLOCK_PS 100
# endif

# include <stdio.h>
# include <math.h>
# include <stdlib.h>

/******************************************************************************/

# define MAX_RAND 0x7FFF

# define NULLO 0


# define NOMEM    1
# define NOFILEI  2
# define NOFILEO  3
# define NODIM    4
# define NONODO   5
# define TOOCOLL  6
# define NOLIV    7
# define TOOLIV   8
# define NOMEMV   9
# define NOFILEES 10
# define ERRESE   11
# define NOTRETE  12
# define NOTLIV   13
# define NONUMR   14
# define TOONET   15
# define NOSTRUCT 16
# define CREARETE 17

/*****************************************************************************/

static char fileinp[255]="nnetsinp.dat";  /* file di caricamento rete     */
static char fileout[255]="nnetsout.dat";  /* file di scaricamento rete    */
static char fileese[255]="nettrain.dat";  /* file di esempi               */

static int      nep=1;                    /* numero epoche di addestram.  */
static float    minerr=0;                 /* errore minimo di convergenza */
static float    epsl= 0.8;                /* cost. apprendimento          */
static float    alfa= 0.5;                /* coeff. di momento            */
static float    randa=-0.4;               /* estremo inf. gen. rand. pesi */
static float    randb=0.4;                /* estremo sup. gen. rand. pesi */
static int      numr= 1;                  /* num. della rete in consideraz.*/
static int      flgbias=0;      /* no*/   /* flag per la correzione del bias*/
static int      flgdeb=2;                 /* flag visualizz. (def=mass.)  */

static int      flgrete=0;                /* flag di rete definita*/
static int      flgstrr=0;                /* flag di struttura reti definita*/
/*****************************************************************************/


/*****************************************************************************/
/*  Struttura delle reti in memoria :                                         */
/*                                                                            */
/*               +-------+           rete 1                    rete n         */
/*               | rete 1|-------------|      nodi      :          +--------+ */
/*    livelli  |-|       |             |---> +--------+ :  +-----+ | nodo 1 | */
/*    +-----+<-| |-------|        link       | nodo 1 | :  |-----| |        | */
/*    |-----|    |       |       +------+<---|        | :  |-----| |--------| */
/*    |-----|    |       |       |------|    |--------| :  |-----| :        : */
/*    |-----|    :       :       |------|    :        : :  |-----| |--------| */
/*    :     :    :       :       |------|    :        : :  :     : | nodo n | */
/*    :     :    |       |       :      :    |--------| :  |-----| |        | */
/*    |-----|    |-------|       |------|  |-| nodo n | :  |-----| +--------+ */
/*    |-----|    | rete n|--|    |------|<-| |        | :  +-----+            */
/*    |-----|<---|       |  |    |------|    +--------+ :                     */
/*    |-----|    +-------+  |    +------+               :            ^        */
/*    |-----|               |                           :            |        */
/*    +-----+               |----------------------------------------|        */
/*                                                                            */
/******************************************************************************/


					  /* vettore di dimens. = totr+1 */
static struct rete                        /* struttura di supporto reti    */
{
  LONG d1;                                /* numero massimo di nodo */
  LONG d2;                                /* numero totale di collegamenti */
  struct nodo /*far*/ *nodo;                  /* puntatore alla struttura nodi */
  struct coll /*far*/ *inicoll;               /* puntatore alla struttura colleg.*/
  int  maxliv;                            /* livello massimo */
  struct livello /*far*/ *liv;                /* puntatore alla struttura livelli*/
};
					  /* vettore di dimens. = totl */
static struct livello                     /* struttura livelli */
{
  LONG sn;                                /* minimo nodo del livello */
  LONG en;                                /* massimo nodo del livello */
};

				/* vettore di dimens. = d1 (piu' prec. d1+1)*/
static struct  nodo             /* struttura del nodo */
{
  float bias;                   /* soglia */
  float dbias;                  /* variaz. della soglia del passo prec.*/
  float inp;                    /* input del ciclo precedente (util. da funz)*/
  float stato;                  /* stato ; aggiornato da funz */
  int  far (*funz)();           /* funzione di trasferimento */
  int  far (*azione)();         /* eventuale azione */
  LONG  ncoll;                  /* numero dei collegamenti in uscita */
  struct coll far *coll;        /* puntatore al vettore collegamenti */
}  ;
				/* vettore di dimens. = d2 */
static struct coll              /* struttura collegamenti */
{
  float peso;                   /* peso del collegamento */
  float dp;                     /* variazione del peso nel passo prec.*/
  LONG nodo;                    /* nodo puntato */
}  ;



static struct rete    far *r;      /* puntatore al primo elemento di rete*/
static struct livello far *iniliv; /* puntatore al primo elemento di livello*/

static int  totr;                /* massimo numero di rete */
static LONG totl;                /* numero totale di livelli */

static char copyright[]="C.o.py.ri.ght b.y D.a.n.i.e.l.e D.e.n.a.r.o";

/*************************  FUNCTIONS DECLARATIONS **************************/

int   loadnet(char *fileinp);
			/* Load all networks from file <fileinp> to memory  */
			/* In the same time create structure for nets list  */
			/* Par. inp.: fileinp (file name)                   */
			/*            if fileinp="" default = nnetsinp.dat  */

int   savenet(char *fileout);
			/* Save all networks from memory to file <fileout>  */
			/* Par. inp.: fileout (file name)                   */
			/*            if fileout="" default = nnetsout.dat  */

int   createallnet(int tn,int nlay,LONG vn[],char vf[][10],char va[][10]);
			/* Create <tn> same nets in memory and the structure*/
			/* that describe them.                              */
			/* Links between layers are wholes and the weight   */
			/* are initialized with a value between ra=-.4 and  */
			/* rb=+.4 (see function <param> for ra and rb def.) */
			/* Par. inp.:tn   (total nets)                      */
			/*           nliv (max layer)                       */
			/*           vn[] (array of tot. nodes for each lay)*/
			/*           vf[] (array of a.fun name for each lay)*/
			/*           va[] (array of act. name for each lay) */

int   createstruct(int tn,int vlay[]);
			/* Create the structure that describe list of all   */
			/* networks. We need create this before create      */
			/* single net.                                      */
			/* It is possible to define nets with different lay */
			/* Par. inp.: tn     (total nets )                  */
			/*            vlay[] (array of max lay for each net)*/

int   createnet(int net,LONG vn[],char vf[][10],char va[][10]);
			/* Create single net .                              */
			/* (structure of nets list must already exist)      */
			/* We can define total nodes , activation function  */
			/* and action for each layer of net.                */
			/* Par. inp.: net   (net number or id)              */
			/*            vn[]  (array of total nodes for lay)  */
			/*            vf[]  (array of a.fun. name for lay)  */
			/*            va[]  (array of act. name for lay)    */

int   ininet(int net);
			/* Overwrite weigts with random number between <ra> */
			/* and <rb> (see function <param> )                 */
			/* Par. inp.: net   (net number)                    */

int   copynet(int nta,int ntb);
			/* Copy net A to net B .                            */
			/* Warning: because the function sequencialy copy   */
			/* characteristics from    A nodes to B nodes, if   */
			/* A e B nets are not the same the result can be    */
			/* unpredictible .                                  */
			/* Par. inp.: nta   (net A )                        */
			/*            ntb   (net B )                        */

int   cancnets();
			/* Dealloc memory for all nets and structure        */


int   param(char *name, char *val);
			/* Modify global parameters     .                   */
			/* Parameters names :                               */
			/* ne (epochs number for   EBP;           def. 1)   */
			/* er (min q. error for stop EBP;         def. 0)   */
			/* ep (learning coefficient for EBP;      def. 0.8) */
			/* mo (momentum coefficient for EBP;      def. 0.5) */
			/* ra (weigts random gener. start value ; def.-0.4) */
			/* rb (weigts random gener. end value   ; def. 0.4) */
			/* fb (flag bias training; 1=yes        ; def. 0)   */
			/* fd (flag verbose    ;                  def. 1)   */
			/* Par. inp.: name  (param. name)                   */
			/*            val   (ascii value)                   */

int   produce(int net,char *finpdat, char *foutdat);
			/* The most general function for net forward        */
			/* computation.                                     */
			/* Read input values(of layer 0) from file <finpdat>*/
			/* and write output values(of last layer) on file   */
			/* <foutdat>.                                       */
			/* (function <produce> call function <compute>)     */
			/* Par. inp.: net     (net number)                  */
			/*            finpdat (input file name)             */
			/*                     if *finpdat = "" def.= stdinp*/
			/*            foutdat (output file name)            */
			/*                     if *foutdat = "" def.= stdout*/

  float compute(int net,float vinp[],float vout[],float vdat[]);
			/* Forward computation for a net.                   */
			/* Read input values (of layer 0) from the array    */
			/* <vinp>  ,  write output values (of last layer)   */
			/* on the array <vout> and compare <vout> with      */
			/* <vdat> values (expected values) , at last, over- */
			/* write <vdat> with error (for next EBP phase).    */
			/* Warning: vinp[1] is input for first node of lay 0*/
			/* and vout[1] is status of first node of last layer*/
			/* Return value is the average quadratic error for  */
			/* output nodes .                                   */
			/* (function <compute> call function <propagate>)   */
			/* Par. inp.: net    (net number)                   */
			/*            vinp[] (array of input data)          */
			/*            vdat[] (array of out expected  )      */
			/* Par. out.: vout[] (array of out data)            */
			/*            vdat[] (array of out errors)          */
			/* Return   : average q. error                      */

    int   propagate(int net,int laya,int layb);
			/* Propagate input from layer A to layer B          */
			/* Par. inp.: net  (net number)                     */
			/*            laya (layer numer)                    */
			/*            layb (layer number)                   */

float train(int net,char *filetrain);
			/* The most general function for EBP training.      */
			/* Read couple of values for input nodes and output */
			/* expected values from file <*filetrain>, and      */
			/* modify weigts applying EBP rule .                */
			/* The function has 2 phases : first call <compute> */
			/* to propagate input and after call <learn> to     */
			/* apply EBP rule.                                  */
			/* Training is repeated for <ne> cycles (see <param>*/
			/* (function <train> call <compute> and <learn> )   */
			/* Par. inp.: net  (net number)                     */
			/*            filetrain (file trainer name)         */
			/*                if *filetrain="" def.=nettrain.dat*/
			/* Return   : total averege q. error                */

  int   learn(int net,float verr[]);
			/* Function for net EBP training.                   */
			/* Read error  values (out computed - out expected) */
			/* from array <verr> and apply EBP rule at whole   */
			/* net,backpropagating error and modifying weigts . */
			/* Warning: verr[1] is error of first node of last  */
			/* layer.                                           */
			/* (function <learn> call function <backprop>)      */
			/* Par. inp.: net    (net number)                   */
			/*            verr[] (errors array)                 */

    int   backprop(int net,int laya,int layb);
			/* Backpropagate errors and modify weigts from layer*/
			/* B to layer A .                                   */
			/* We must write errors buffers of layer B before   */
			/* to call this function (see function <werrl>)     */
			/* Par. inp.: net  (net number)                     */
			/*            laya (layer number  )                 */
			/*            layb (layer number    )               */

int  backproperr(int net,int laya,int layb);
			/* Backpropagate errors but don't modify weigts .   */
			/* Warning: this function don't clear errors buffers*/
			/* Par. inp.: net  (net number)                     */
			/*            laya (layer number)                   */
			/*            layb (layer number)                   */

int  cancerr(int net,int laya,int layb);
			/* Clear errors buffers.                            */
			/* We must call this function after <backproperr>   */
			/* because errors buffers are partialy utilized by  */
			/* forward propagation.                             */
			/* Par. inp.: net  (net number)                     */
			/*            laya (layer number)                   */
			/*            layb (layer number)                   */


/******************* Functions for single node  or layer *********************/

/* In this functions <net> is net number and <nn> is node number            */

/* Warn.: we can dinamicaly modify max layer number or total node link,but  */
/*        only reducing the initial values.                                 */

/* Net functions                                                            */

int   rmnet(int *totnet);
			/* Read max net number   (total nets)               */

int   wmnet(int totnet);
			/* Reduce total nets                                */

int   rmlay(int net,int *mlay);
			/* Read max layer number of a net                   */

int   totnn(int net, LONG *tnode);
			/* Read total node number of a net                  */

int   wmlay(int net,int mlay);
			/* Reduce max layer number of a net                 */

int   rlay(int net,int nlay,LONG *sn,LONG *en);
			/* Read start and end node number of a layer        */

/* Next 12 functions are dedicated to layer nodes management in groups.     */
/* Therefore I/O buffer is an array ; first element is alwais [1] (not [0]).*/
/* If the array dimension is < than we need, return value is -1 , but       */
/* element are readed or writed as possible.                                */
/* (<nlay..> is the layer number,  <dim> is the array dimension of buffer)  */

int   rstatl(int net,int nlay,float stat[],int dim);
			/* Read nodes status of layer <nlay> to array <stat>*/

int   wstatl(int net,int nlay,float stat[],int dim);
			/* Modify nodes status of layer <nlay> from <stat>  */

int   rinpl(int net,int nlay,float inp[],int dim);
			/* Read nodes inp of layer <nlay> to array <inp>    */

int   winpl(int net,int nlay,float inp[],int dim);
			/* Modify nodes inp of layer <nlay> from <inp> val. */

int   rerrl(int net,int nlay,float err[],int dim);
			/* Read backprop. error at layer <nlay> to <err>    */

int   werrl(int net,int nlay,float err[],int dim);
			/* Modify error buffer at layer <nlay> from <err>   */

int   rbiasl(int net,int nlay,float bias[],int dim);
			/* Read nodes bias of layer <nlay> to array <bias>  */

int   wbiasl(int net,int nlay,float bias[],int dim);
			/* Modify nodes bias of layer <nlay> from <bias>    */

int   rwgtl(int net,LONG nn,int nlayp,float wgt[],int dim);
			/* Read weigts of node <nn> linked with lay <nlayp> */

int   wwgtl(int net,LONG nn,int nlayp,float wgt[],int dim);
			/* Modify weigts of node <nn> linked with <nlayp>   */

int   rwgtil(int net,LONG npp,int nlaya,float wgt[],int dim);
			/* Read weigts of links at node <npp> from <nlaya>  */

int   wwgtil(int net,LONG npp,int nlaya,float wgt[],int dim);
			/* Modify weigts of links at node <npp> from <nlaya>*/

/* Single node functions                                                    */

int   rstat(int net,LONG nn,float *stat);
			/* Read node activation status                      */

int   rbias(int net,LONG nn,float *bias);
			/* Read node bias                                   */

int   rinp(int net,LONG nn,float *inp);
			/* Read node input                                  */

int   rerr(int net,LONG nn,float *err);
			/* Read node error in EBP phase                     */

int   rfun(int net,LONG nn,char fun[10],char ac[10]);
			/* Read function and action names of a node         */

int   wstat(int net,LONG nn,float stat);
			/* Modify node activation status                    */

int   winp(int net,LONG nn,float inp);
			/* Modify node input                                */

int   werr(int net,LONG nn,float err);
			/* Modify node error in EBP phase                   */

int   wbias(int net,LONG nn,float bias);
			/* Modify node bias                                 */

int   wfun(int net,LONG nn,char fun[10],char ac[10]);
			/* Modify node function and action                  */

int   rnconn(int net,LONG nn,LONG *ncl);
			/* Read total number of links                       */

int   rconn(int net,LONG nn,LONG cl,float *wgt ,LONG *np);
			/* Read node pointed and weigt of <cl> link         */
			/* (Warn.: links for a node are numbered from 0 )   */

int   wwgt(int net,LONG nn,LONG cl,float wgt);
			/* Modify weigt of <cl> link                        */
			/* (Warn.: links for a node are numbered from 0 )   */

int   wnodp(int net,LONG nn,LONG cl,LONG np);
			/* Modify node pointed by <cl> link                 */
			/* (Warn.: links for a node are numbered from 0 )   */

int   wnconn(int net,LONG nn,LONG ncl);
			/* Modify the total number of links                 */
			/* (Warn.: links for a node are numbered from 0 )   */
			/* (Warn.: we can only reduce total original links) */
/*****************************************************************************/

/********************* ACTIVATION FUNCTIONS NAMES ****************************/
/*                                                                            */
/*   f1  : Unitary function : copy input to activation status                 */
/*   f2  : Same as f1 but with memory : add 1/2 previous status to input      */
/*   f3  : Sigmoid function with positiv and negativ value (0 centred)        */
/*   f4  : Same as f3 but with memory                                         */
/*   f5  : Sigmoid function with only positiv value (.5 centred)              */
/*   f6  : Same as f5 but with memory                                         */
/*                                                                            */
/*   f7  : User defined (see below)                                           */
/*   f8  : User defined (see below)                                           */
/*   f9  : User defined (see below)                                           */
/*   f10 : User defined (see below)                                           */
/*                                                                            */
/*   f13 : Sigmoid function as f3 but calculated (more exact but slower )     */
/*   f15 : Sigmoid function as f5 but calculated (more exact but slower )     */
/*                                                                            */
/*   Warning :                                                                */
/*   Sigmoid funct.(f3<->f6) and derivatives are founded  by look table (for  */
/*   more speed) with .01 resolution.                                         */
/******************************************************************************/

/*********************** ACTIONS AND USER DEFINED FUNCTION ********************/


extern  int  a1(int net,LONG nn) ;
extern  int  a2(int net,LONG nn) ;
extern  int  a3(int net,LONG nn) ;
extern  int  a4(int net,LONG nn) ;
extern  int  a5(int net,LONG nn) ;
extern  int  a6(int net,LONG nn) ;

extern  int  f7(int net,LONG nn,int f,float *d) ;
extern  int  f8(int net,LONG nn,int f,float *d) ;
extern  int  f9(int net,LONG nn,int f,float *d) ;
extern  int  f10(int net,LONG nn,int f,float *d) ;

/* Parameters definition :                                                    */
/*            net  : net number                                               */
/*            nn   : node number                                              */
/*            f    : flag function/derivative (0 func. , 1 der. for EBP phase)*/
/*            *d   : buffer for return value of derivative                    */

/* Example of user definited function (unitary function):                     */
/*                                                                            */
/* f7(int net,LONG nn, int f, float *d)                                       */
/*  {float buff;                                                              */
/*   if (f==0) {rinp(net,nn,&buff);wstat(net,nn,buff);winp(net,nn,0);return;} */
/*   if (f==1) {*d =1;return;}                                                */
/*  }                                                                         */

/******************************************************************************/

/********************** Funzioni di supporto **********************************/

static void  motore(int nr,LONG strn, LONG stpn);
static void  ebp   (int nr,LONG strn, LONG stpn);
static char  far *allocamem(LONG n,LONG s);
static int   deallocamem();
static int   scantok(char tok[255],FILE *fp);
static int   poschar(char *buff,char ch);
static int   copys(char *buff,char *buff2,int lastpos);
static void  errmess(int cod);
static float sigma(float x);
static float sigma2(float x);
static float dsig(float x);
static float dsig2(float x);
static void  far *carfunz(char *tok);
static char  *leggefunz(int (*fun)());
static float randab(float ra,float rb);
static void  fine();

/******************************************************************************/

/******************************************************************************/
/*           Creazione , salvataggio e caricamento di tutte le reti           */
/******************************************************************************/

/******************************************************************************/
/*                   Nets saving and loading                                  */
/*                                                                            */
/* File format of nets saved  :                                               */
/*                                                                            */
/*                                                                            */
/* first record : "totnets"/max_net_num/total_layers/                         */
/* other record : "nnet"/net_num/total_nodes/total_links/                     */
/*           or : "lay"/layer_num/                                            */
/*           or : "node"/node_num/input/bias/stat/fun_name/ac_name/           */
/*           or : "conn"/pointed_node;weight/...../pointed_node;weight/       */
/* example :                                                                  */
/*                totnets/10/300/                                             */
/*                  nnet/1/12/36/                                             */
/*                   lay/0/                                                   */
/*                    node/1/0/0/0/f1/0/                                      */
/*                    conn/10;0.66/11;0.3331/12;0.001/                        */
/*                        :                                                   */
/*                        :                                                   */
/*                                                                            */
/* - it's possible to continue record on more lines                           */
/* - each field end with / character                                          */
/* - input,bias,status,weigt are float , other integer                        */
/* - fun_name and ac_name are strings                                         */
/******************************************************************************/

/*************************** CARICA LA RETE da fileinp ************************/

loadnet(filei)
char *filei;
{
  char tok[255];
  char tok2[255];
  char far *rets;
  struct livello far *pliv;
  struct livello far *liv;
  struct nodo far *nodo;
  int ret,nr;
  int nliv;
  LONG nn;LONG vd1;LONG vd2;LONG h;
  LONG maxnn;
  FILE    *fp;

  if (strlen(filei) != 0) strcpy(fileinp,filei);
  fp= fopen(fileinp,"r");
  if (fp == (void *)NULLO) {errmess(NOFILEI); fine();}

  if (flgstrr > 0) {deallocamem();flgstrr=0;}
  for (;;)
  {
  ret=scantok(tok,fp);if (ret == NULLO) {errmess(NOTRETE);fine();}
  if (strncmp(tok,"totnets",7) == 0)
    {
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NOTRETE);fine();}
      totr=atoi(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NOTLIV);fine();}
      totl=atol(tok);
      break;
    }
  }
  rets=allocamem(totr+1,sizeof(struct rete));
  if ((long)rets == NULLO) {errmess(NOMEM);fine();}
  r=(struct rete *)rets;
  rets=allocamem(totl+1,sizeof(struct livello));
  if ((long)rets == NULLO) {errmess(NOMEM);fine();}
  iniliv=(struct livello *)rets;
  flgstrr=1;

  nr=1;
  pliv=iniliv;

  for (;;)
  {
    ret=scantok(tok,fp);if (ret == NULLO) break;

    if (strncmp(tok,"nnet",4) == 0)
    {
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONUMR);fine();}
      nr=atoi(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NODIM); fine();}
      (r+nr)->d1=atol(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NODIM); fine();}
      (r+nr)->d2=atol(tok);

      rets=allocamem((r+nr)->d1+1,sizeof(struct nodo));
      if ((long)rets == NULLO) {errmess(NOMEM);fine();}
      (r+nr)->nodo = (struct nodo *)rets;
      rets=allocamem((r+nr)->d2,sizeof(struct coll));
      if ((long)rets == NULLO) {errmess(NOMEM);fine();}
      (r+nr)->inicoll = (struct coll *)rets;vd2=0;

      (r+nr)->maxliv=0;
      (r+nr)->liv=pliv;
      liv=(r+nr)->liv;
      nodo=(r+nr)->nodo;
      vd1=0;vd2=0;
      flgrete++;
    }

    if (strncmp(tok,"lay",3) == 0)
    {
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NOLIV);fine();}
      nliv=atoi(tok); if (nliv > 99) {errmess(TOOLIV);fine();}
      (liv+nliv)->sn=0;
      if (nliv > (r+nr)->maxliv) (r+nr)->maxliv = nliv;
      pliv=pliv+1;
    }

    if (strncmp(tok,"node",4) == 0)
    {
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONODO);fine();}
      nn = atol(tok);if (vd1<nn) vd1=nn;
      if (nn == 0) {errmess(NONODO);fine();}
      if (nn > (r+nr)->d1) {errmess(NONODO);fine();}
      if ((liv+nliv)->sn == 0) {(liv+nliv)->sn=nn; }
      (liv+nliv)->en=nn;
      h=0;
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONODO);fine();}
      (*(nodo+nn)).inp = atof(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONODO);fine();}
      (*(nodo+nn)).bias = atof(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONODO);fine();}
      (*(nodo+nn)).stato = atof(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONODO);fine();}
      (*(nodo+nn)).funz = carfunz(tok);
      ret=scantok(tok,fp);if (ret == NULLO) {errmess(NONODO);fine();}
      (*(nodo+nn)).azione = carfunz(tok);
      (*(nodo+nn)).ncoll=0;
      (*(nodo+nn)).dbias=0;
      continue;
    }
    if (strncmp(tok,"conn",4) == 0) continue;
    ret=poschar(tok,';');if (ret != -1)
    {
      if (h==0) {(*(nodo+nn)).coll = (r+nr)->inicoll+vd2;}
      vd2++;if (vd2 > (r+nr)->d2) {errmess(TOOCOLL);fine();}
      (*(nodo+nn)).ncoll++ ;
      copys(tok2,tok,ret-1);
      (*((*(nodo+nn)).coll+h)).nodo = atol(tok2);
      copys(tok2,tok+ret+1,strlen(tok)-ret-1);
      (*((*(nodo+nn)).coll+h)).peso = atof(tok2);
      (*((*(nodo+nn)).coll+h)).dp = 0;
      h++;
    }
  }
  fclose(fp);
  return 0;
}


/*************************  SCARICA LA RETE sul file fileout ******************/

savenet(fileo)
char *fileo;
{
  LONG ncol=0;LONG nn, h;
  int nliv,nr;
  char *leggefunz();
  FILE *fp;
  struct livello far *liv;
  struct nodo far *nodo;
  struct coll far *coll;
  if (strlen(fileo) != 0) strcpy(fileout,fileo);
  fp = fopen(fileout,"w");
  if (fp == (void *)NULLO) {errmess(NOFILEO); fine();}

  fprintf (fp,"totnets/%d/%ld/\n",totr,totl);
  for (nr=1;nr<=totr;nr++)
  {
   liv=(r+nr)->liv;
   nodo=(r+nr)->nodo;
   fprintf(fp,"\nnnet/%d/%ld/%ld/\n",nr,(r+nr)->d1,(r+nr)->d2);
   for (nliv=0; nliv<=(r+nr)->maxliv; nliv++)
   {
    fprintf (fp,"lay/%d/\n",nliv);
    for(nn=(liv+nliv)->sn; nn<=(liv+nliv)->en; nn++)
    {
     fprintf (fp,"  node/%ld/%06.4f/%06.4f/%06.4f/%s/%s/\n",
	   nn,
	   (*(nodo+nn)).inp,
	   (*(nodo+nn)).bias,
	   (*(nodo+nn)).stato,
	   leggefunz((*(nodo+nn)).funz),
	   leggefunz((*(nodo+nn)).azione));
    fprintf (fp,"    conn/");
    for (h=0; h<(*(nodo+nn)).ncoll; h++)
      {
	fprintf (fp,"%ld;%06.4f/",
	(*((*(nodo+nn)).coll+h)).nodo,
	(*((*(nodo+nn)).coll+h)).peso);
	ncol++; if (ncol > 6) {fprintf (fp,"\n        ");ncol=0;}
      }
    if (ncol <= 6) {fprintf (fp,"\n");ncol=0;}
   }
   }
   }
   fclose(fp);
   return 0;
}

/*************************  CREA RETI TUTTE UGUALI ****************************/

createallnet(tr,nliv,vn,vf,va)
int tr;
int nliv;
LONG vn[];
char vf[][10];
char va[][10];
{
  int nr;
  int vliv[1000];
  if (tr > 1000) {errmess(TOONET);fine();}
  for (nr=1;nr<=tr;nr++) {vliv[nr]=nliv;}
  createstruct(tr,vliv);
  for (nr=1;nr<=totr;nr++) {createnet(nr,vn,vf,va);}
  return 0;
}

/*************************  CREA LA STRUTTURA PER LE RETI *********************/

createstruct(tr,vliv)
int tr;
int vliv[];
{
  int i;
  struct livello far *pliv;
  char  far *rets;
  totl=0;
  totr=tr;
  for (i=1;i<=totr;i++) { totl=totl+vliv[i]+1;  }
  rets=allocamem(totr+1,sizeof(struct rete));
  if ((long)rets == NULLO) {errmess(NOMEM);fine();}
  r=(struct rete *)rets;
  rets=allocamem(totl+1,sizeof(struct livello));

  if ((long)rets == NULLO) {errmess(NOMEM);fine();}
  iniliv=(struct livello *)rets;
  pliv=iniliv;
  for (i=1;i<=totr;i++)
  {
   (r+i)->maxliv=vliv[i];
   (r+i)->liv=pliv;
   pliv=pliv+vliv[i]+1;
  }
  flgstrr=1;
  return 0;
}

/*************************  CREA LA SINGOLA RETE ******************************/

createnet(nr,vn,vf,va)
int nr;
LONG vn[];
char vf[][10];
char va[][10];
{
  int i,tcoll,nliv;
  LONG cnn,nn,h,ni;
  char far *rets;
  struct nodo    far *nodo;
  struct coll    far *inicoll;
  struct livello far *liv;

  if (flgstrr == 0) {errmess(NOSTRUCT);fine();}
  if (nr > totr) {errmess(CREARETE);fine();}
  cnn=1;tcoll=0;
  liv=(r+nr)->liv;
  nliv=(r+nr)->maxliv;
  for (i=0;i<=nliv;i++)
  {
    (liv+i)->sn=cnn;
    cnn=cnn+vn[i];
    (liv+i)->en=cnn-1;
    if (i != nliv) {tcoll=tcoll+(vn[i] * vn[i+1]);}
  }
  (r+nr)->d1=cnn-1;
  (r+nr)->d2=tcoll;
  rets=allocamem((r+nr)->d1+1,sizeof(struct nodo));
  if (rets == NULLO) {errmess(NOMEM);fine();}
  (r+nr)->nodo = (struct nodo *)rets;
  nodo=(r+nr)->nodo;
  rets=allocamem((r+nr)->d2+1,sizeof(struct coll));
  if (rets == NULLO) {errmess(NOMEM);fine();}
  (r+nr)->inicoll = (struct coll *)rets;
  inicoll = (r+nr)->inicoll;
  tcoll=0;
  for (i=0;i<=nliv;i++)
  {
    for (nn=(liv+i)->sn; nn<=(liv+i)->en; nn++)
    {
      (*(nodo+nn)).dbias=0;
      (*(nodo+nn)).bias=0;
      (*(nodo+nn)).inp=0;
      (*(nodo+nn)).stato=0;
      (*(nodo+nn)).funz=carfunz(vf[i]);
      (*(nodo+nn)).azione=carfunz(va[i]);
      (*(nodo+nn)).ncoll=0;
      (*(nodo+nn)).coll=inicoll+tcoll;
      if (i < nliv)
      {
      h=0;
      for (ni=(liv+i+1)->sn; ni<=(liv+i+1)->en; ni++)
      {
	(*((*(nodo+nn)).coll+h)).nodo = ni;
	(*((*(nodo+nn)).coll+h)).peso = randab(randa,randb);
	(*((*(nodo+nn)).coll+h)).dp = 0;
	tcoll++;h++;
      }
      (*(nodo+nn)).ncoll=h;
      }
    }
  }
 flgrete++;
 return 0;
}

/*************************  REINIZIALIZZA E COPIA RETI ************************/

ininet(int nr)
{
  LONG nn,h;
  struct nodo    far *nodo;
  if (flgstrr == 0) {errmess(NOSTRUCT);fine();}
  if (nr > totr) return -1;
  nodo=(r+nr)->nodo;
  for (nn=1; nn<=(r+nr)->d1; nn++)
  {
      (*(nodo+nn)).dbias=0;
      (*(nodo+nn)).bias=0;
      (*(nodo+nn)).inp=0;
      (*(nodo+nn)).stato=0;
      for (h=0;h<(*(nodo+nn)).ncoll;h++)
      {
	(*((*(nodo+nn)).coll+h)).peso = randab(randa,randb);
	(*((*(nodo+nn)).coll+h)).dp = 0;
      }
   }
   return 0;
}

copynet(int nra,int nrb)
{
  LONG nn,h;
  struct nodo   far *nodoa;
  struct nodo   far *nodob;
  if (flgstrr == 0) {errmess(NOSTRUCT);fine();}
  if (nra > totr) return -1;
  if (nrb > totr) return -1;
  nodoa=(r+nra)->nodo;
  nodob=(r+nrb)->nodo;
  for (nn=1; nn<=(r+nra)->d1; nn++)
  {
      if (nn > (r+nrb)->d1) return -1;
      (*(nodob+nn)).dbias=0;
      (*(nodob+nn)).bias=(*(nodoa+nn)).bias;
      (*(nodob+nn)).funz=(*(nodoa+nn)).funz;
      (*(nodob+nn)).azione=(*(nodoa+nn)).azione;
      (*(nodob+nn)).inp=0;
      (*(nodob+nn)).stato=0;
      for (h=0;h<(*(nodoa+nn)).ncoll;h++)
      {
	if (h > (*(nodob+nn)).ncoll) break;
	(*((*(nodob+nn)).coll+h)).peso = (*((*(nodoa+nn)).coll+h)).peso;
	(*((*(nodob+nn)).coll+h)).dp = 0;
      }
   }
   return 0;
}

cancnets()
{
  deallocamem();
  return 0;
}

/*************************  ROUTINES PER L'ALLOCAZIONE DELLA MEMORIA **********/

char far *allocamem(LONG n,LONG s)
{
  char far *iseg;
  if (flgdeb>0) printf("Alloc  %d  bytes ",n*s);
# ifdef B16
    if (n*s > 0xFFFF) return(NULLO);
# endif
  iseg = ALLOCA(n,s);
  if (flgdeb>0) {if ((long)iseg != 0) printf("   starting %p\r\n",iseg);}
  return(iseg);
}

deallocamem()
{
  int nr;
  for (nr=1;nr<=totr;nr++)
    {
     if ((r+nr)->nodo != NULLO)  LIBERA((void far *)(r+nr)->nodo);
     if ((r+nr)->inicoll != NULLO) LIBERA((void far *)(r+nr)->inicoll);
    }
  if ( r != NULLO) LIBERA((void far *)r);
  if ( iniliv != NULLO) LIBERA((void far *)iniliv);
  return 0;
}

/*************************  ROUTINES DI SUPPORTO ******************************/

scantok(char tok[255],FILE *fp)
{
  int i,len;
  char ch;
  i=0;tok[0]='\0';
  for(;;)
  {
    ch=getc(fp);
    if (ch == EOF) {len=NULLO; break;}
    if ((ch == '/') || isspace(ch))
      {if (i>0) { tok[i]='\0';len=i;i=0;break;} else continue; }
    tok[i]=ch;i++;tok[i]='\0';if (i>254) return NULLO;
  }
  return(len);
}

poschar(char *buff,char ch)
{
  int i;
  for (i=0;i<strlen(buff);i++)
   {if (*(buff+i) == ch)  return(i);}
  return(-1);
}

copys(char *buff1,char *buff2,int lastpos)
{
  int i;
  for (i=0;i<=lastpos;i++) *(buff1+i) = *(buff2+i);
  *(buff1+lastpos+1) =0;
  return 0;
}

float randab(float ra,float rb)
{
 float num;
 num = rand()&0x7FFF; num = num/MAX_RAND;
 return (num * (rb-ra) + ra);
}

/******************************************************************************/
/*                             Nucleo operativo                               */
/******************************************************************************/

/*********************** ELABORAZIONE ATTRAVERSO I LIVELLI ********************/

produce(nr,inpdat,outdat)
int nr;
char *inpdat;
char *outdat;
{
 int ret,maxliv;
 LONG i,ninp,nout;
 float *rets;
 float *vinp,*vout,*vdat;
 FILE *fpinp;
 FILE *fpout;
 struct livello far *liv;
 if (nr > totr) {errmess(CREARETE);fine();}
 liv=(r+nr)->liv;
 maxliv=(r+nr)->maxliv;
 if (strlen(inpdat)==0) fpinp=stdin;
  else
  {fpinp=fopen(inpdat,"r");
  if (fpinp==NULLO) printf("Non puo' aprire il file di dati %s\r\n",inpdat);
  return -1;}
 if (strlen(outdat)==0) fpout=stdout;
  else
  {fpout=fopen(outdat,"w");
  if (fpout==NULLO) printf("Non puo' aprire il file di dati %s\r\n",outdat);
  return -1;}
 if (flgrete < nr) {printf("\n Caric. prima la rete (o crearla) !");return -1;}
  ninp=(liv+0)->en-(liv+0)->sn+1; nout=(liv+maxliv)->en-(liv+maxliv)->sn+1;
  rets=calloc(ninp+1,sizeof(*vinp));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vinp=rets;
  rets=calloc(nout+1,sizeof(*vout));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vout=rets;
  rets=calloc(nout+1,sizeof(*vdat));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vdat=rets;

 for (;;)
 {
   printf("\n>");
   for (i=1;i<=ninp;i++)
       {ret=fscanf(fpinp,"%f",&vinp[i]);if (ret < 1) goto fine;}
   compute(nr,vinp,vout,vdat);
   for (i=1;i<=nout;i++) fprintf(fpout,"\n%7.3f",vout[i]);
 }
 fine:
 free(vinp);free(vout);free(vdat);
 return 0;
}


float compute(nr,vinp,vout,vdat)
int nr;
float vinp[];
float vout[];
float vdat[];
{
 int maxliv;
 LONG i,nl,k;
 float err,errq;
 struct nodo far *nodo;
 struct livello far *liv;
 errq=0;
  if (nr > totr) {errmess(CREARETE);fine();}
 nodo=(r+nr)->nodo;
 maxliv=(r+nr)->maxliv;
 liv=(r+nr)->liv;
 for (i=(liv+0)->sn; i<=(liv+0)->en; i++)
   {k=i-(liv+0)->sn+1; (*(nodo+i)).inp=vinp[k]; }
 propagate(nr,0,maxliv);
 for (i=(liv+maxliv)->sn; i<=(liv+maxliv)->en; i++)
   {
   k=i-(liv+maxliv)->sn+1;
   vout[k]=(*(nodo+i)).stato;
   err=(vout[k] - vdat[k]) ;vdat[k]=err;
   errq=errq+(float)pow((double)err,(double)2);
   }
 return(errq/k);
}

propagate(int nr,int liva,int livb)
{
 int nl;
 LONG strn,stpn;
 struct livello far *liv;
 if (nr > totr) {errmess(CREARETE);fine();}
 liv=(r+nr)->liv;
 for (nl=liva ;nl<=livb; nl++)
   {strn=(liv+nl)->sn;stpn=(liv+nl)->en;motore(nr,strn,stpn);}
 return 0;
}


/********************** CORREZIONE ALL'INDIETRO *******************************/


param(char *nome,char *val)
{
 if (strncmp(nome,"ne",2) == 0) {nep=atoi(val);return 0;}
 if (strncmp(nome,"er",2) == 0) {minerr=atof(val);return 0;}
 if (strncmp(nome,"ep",2) == 0) {epsl=atof(val);return 0;}
 if (strncmp(nome,"mo",2) == 0) {alfa=atof(val);return 0;}
 if (strncmp(nome,"ra",2) == 0) {randa=atof(val);return 0;}
 if (strncmp(nome,"rb",2) == 0) {randb=atof(val);return 0;}
 if (strncmp(nome,"fb",2) == 0) {flgbias=atoi(val);return 0;}
 if (strncmp(nome,"fd",2) == 0) {flgdeb=atoi(val);return 0;}
 return -1;
}


float train(nr,fileese)
int nr;
char *fileese;
{
  int ret,maxliv;
  char tok[255];
  LONG ep,ninp,nout,es,i,nn;
  float *vinp,*vout,*vdat;
  float err, errep;
  float *rets;
  FILE    *fp;
  struct livello far *liv;
  if (nr > totr) {errmess(CREARETE);fine();}
  liv=(r+nr)->liv;
  maxliv=(r+nr)->maxliv;
  ninp=(liv+0)->en-(liv+0)->sn+1; nout=(liv+maxliv)->en-(liv+maxliv)->sn+1;
  rets=calloc(ninp+1,sizeof(*vinp));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vinp=rets;
  rets=calloc(nout+1,sizeof(*vout));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vout=rets;
  rets=calloc(nout+1,sizeof(*vdat));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vdat=rets;
  fp = fopen(fileese,"r");
  if (fp == NULLO) {errmess(NOFILEES); fine();}
  for (ep=1;ep<=nep;ep++)
  {
   errep=0;es=0;
   for (;;)
   {
    if (scantok(tok,fp) == NULLO) break;
    vinp[1]=atof(tok) ;
    for (i=2;i<=ninp;i++)
    {
      if (scantok(tok,fp) == NULLO) {errmess(ERRESE);fine();}
      vinp[i]=atof(tok) ;
    }
    for (i=1;i<=nout;i++)
    {
      if (scantok(tok,fp) == NULLO) {errmess(ERRESE);fine();}
      vdat[i]=atof(tok) ;
    }
    err=compute(nr,vinp,vout,vdat);
    learn(nr,vdat);
    errep=errep+err;
    es++;
   }
  rewind(fp);
  errep=errep/es;
  if (errep <= minerr) break;
  if (flgdeb>=2) printf("\n Epoch      %5ld    Aver.q.err. %7.4f ",ep,errep);
  }
  if (flgdeb<2) printf("\n Tot.Epoch %5ld     Aver.q.err. %7.4f ",ep,errep);
  free(vinp);free(vout);free(vdat);
  fclose(fp);
  return errep;
}



learn(nr,verr)
int nr;
float verr[];
{
 LONG i,nl,k;
 int maxliv;
 struct nodo far *nodo;
 struct livello far *liv;
 if (nr > totr) {errmess(CREARETE);fine();}
 nodo=(r+nr)->nodo;
 maxliv=(r+nr)->maxliv;
 liv=(r+nr)->liv;
 for (i=(liv+maxliv)->sn; i<=(liv+maxliv)->en; i++)
   { k=i-(liv+maxliv)->sn+1; (*(nodo+i)).inp = verr[k];}
 backprop(nr,0,maxliv);
 return 0;
}

backprop(int nr,int liva,int livb)
{
 LONG nl,i;
 LONG strn,stpn;
 struct nodo far *nodo;
 struct livello far *liv;
 if (nr > totr) {errmess(CREARETE);fine();}
 nodo=(r+nr)->nodo;
 liv=(r+nr)->liv;
 for (nl=livb ;nl>=liva; nl--)
   {strn=(liv+nl)->sn;stpn=(liv+nl)->en;ebp(nr,strn,stpn);}
 for (nl=livb ;nl>=liva; nl--)
   {for (i=(liv+nl)->sn; i<=(liv+nl)->en; i++) {(*(nodo+i)).inp = 0;}}
 return 0;
}

backproperr(int nr,int liva,int livb)
{
 LONG nl,i;
 LONG strn,stpn;
 struct nodo far *nodo;
 struct livello far *liv;
 if (nr > totr) {errmess(CREARETE);fine();}
 nodo=(r+nr)->nodo;
 liv=(r+nr)->liv;
 for (nl=livb ;nl>=liva; nl--)
   {strn=(liv+nl)->sn;stpn=(liv+nl)->en;ebp(nr,strn,stpn);}
 for (nl=livb ;nl>=liva; nl--)
   {for (i=(liv+nl)->sn; i<=(liv+nl)->en; i++) {(*(nodo+i)).inp = 0;}}
 return 0;
}

cancerr(int nr,int liva,int livb)
{
 LONG nl,i;
 LONG strn,stpn;
 struct nodo far *nodo;
 struct livello far *liv;
 if (nr > totr) {errmess(CREARETE);fine();}
 nodo=(r+nr)->nodo;
 liv=(r+nr)->liv;
 for (nl=livb ;nl>=liva; nl--)
   {for (i=(liv+nl)->sn; i<=(liv+nl)->en; i++) {(*(nodo+i)).inp = 0;}}
 return 0;
}

/******************************   MOTORE  ***********************************/

void motore(nr,strn,stpn)
int nr;
LONG strn,stpn;
{
  LONG nn; LONG h; LONG i; LONG cc;
  float b;
  struct nodo    far *nodo;
  struct nodo    far *nodonn;
  struct coll    far *collnn;
/*
  if (strn == 0) strn = 1;
  if (stpn  == 0) stpn  = (r+nr)->d1;
*/
    for(nn=strn; nn<=stpn; nn++)
    {
      nodo = (r+nr)->nodo;
      nodonn = nodo+nn;
      if ((*nodonn).funz != 0)   (*((*nodonn).funz))(nr,nn,0,&b);
      if ((*nodonn).azione != 0) (*((*nodonn).azione))(nr,nn);
      collnn = (*nodonn).coll;
      for (h=0; h<(*nodonn).ncoll; h++)
      {
	i=(*(collnn+h)).nodo;
	if (i != 0)
	{ (*(nodo+i)).inp=(*(nodo+i)).inp +
		    ((*nodonn).stato * (*(collnn+h)).peso); }
      }
    }
}
/*-*/
/************************* ERROR BACK PROPAGATION *****************************/

void ebp(nr,strn,stpn)
int nr;
LONG strn,stpn;
{
  int ret;
  LONG nn; LONG h; LONG i; LONG cc;
  float dd, dpeso, peso, erri, errnn, dfuni, dp,dfunn,ddnn,dbias,bias,db;
  struct nodo    far *nodo;
  struct nodo    far *nodonn;
  struct coll    far *collnn;
/*
  if (strn == 0) strn = 1;
  if (stpn  == 0) stpn  = (r+nr)->d1;
*/
    for(nn=strn; nn<=stpn; nn++)
    {
      nodo = (r+nr)->nodo;
      nodonn = nodo+nn;
      collnn = (*nodonn).coll;
      errnn = 0;
      for (h=0; h<(*nodonn).ncoll; h++)
	 {
	  i=(*(collnn+h)).nodo; peso=(*(collnn+h)).peso;dp=(*(collnn+h)).dp;
	  if ((i != 0) && ((*(nodo+i)).inp != 0))
	  {
	  erri = (*(nodo+i)).inp;
	  (*((*(nodo+i)).funz))(nr,i,1,&dfuni);
	  dd = (erri * dfuni)   ;
	  errnn = errnn + (dd * peso) ;
	  dpeso = - ((epsl * dd) * ((*nodonn).stato ));
	  dpeso=dpeso+(dp*alfa); peso=peso+dpeso; if (peso == 0) peso=.000001;
	  (*(collnn+h)).peso = peso ; (*(collnn+h)).dp=dpeso;
	  }
	 }
	 errnn = ((*nodonn).inp) + errnn;
	 (*nodonn).inp =  errnn;

	 if (flgbias == 1)
	 {
	 bias=(*nodonn).bias;db=(*nodonn).dbias;
	 (*((*nodonn).funz))(nr,nn,1,&dfunn);
	 ddnn = (errnn * dfunn)   ;
	 dbias = - (epsl * ddnn) ;
	 dbias=dbias+(db*alfa); bias=bias+dbias;
	 (*nodonn).bias = bias ; (*nodonn).dbias=dbias;
	 }
    }
}

/*-*/


/***************************** FUNZIONI ED AZIONI *****************************/

/*****************************     FUNZIONI       *****************************/

f1(int nr,LONG nn,int f,float *b)
/* Funzione unitaria sposta semplicemente input su stato  */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = 1;return (0);}  /* derivata */
 (*(nodo+nn)).stato = (*(nodo+nn)).inp+(*(nodo+nn)).bias ;
 (*(nodo+nn)).inp = 0;
 return (0);
}

f2(int nr,LONG nn,int f,float *b)
/* Come f1 ma con memoria */
/* tempo di dimezz. pari a un ciclo */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = 1;return (0);}  /* derivata */
 (*(nodo+nn)).stato = (((*(nodo+nn)).inp)+(*(nodo+nn)).bias+((*(nodo+nn)).stato / 2));
 (*(nodo+nn)).inp = 0;
 return (0);
}



f3(int nr,LONG nn,int f,float *b)
/* Funzione sigmoide centrata sullo 0 e con valori da -1 a 1        */
/* funzione tabulata corrispondente alla formula y=(exp(x)-1)/(exp(x)+1) */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = (dsig((*(nodo+nn)).stato));return (0);}  /* derivata */
 (*(nodo+nn)).stato = sigma((*(nodo+nn)).inp+(*(nodo+nn)).bias) ;
 (*(nodo+nn)).inp = 0;
 return (0);
}

f4(int nr,LONG nn,int f,float *b)
/* Come f3 ma con memoria */
/* tempo di dimezz. pari a un ciclo */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = (dsig(((*(nodo+nn)).stato)));return (0);}  /* derivata */
 (*(nodo+nn)).stato = sigma(((*(nodo+nn)).inp)+(*(nodo+nn)).bias+ ((*(nodo+nn)).stato / 2));
 (*(nodo+nn)).inp = 0;
 return (0);
}



f5(int nr,LONG nn,int f,float *b)
/* Funzione sigmoide centrata sullo 0 ma con valori da 0 a 1 */
/* funzione tabulata corrisp. alla formula Y=1/1+exp(-x) */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = (dsig2(((*(nodo+nn)).stato)));return (0);}  /* derivata */
 (*(nodo+nn)).stato = sigma2((*(nodo+nn)).inp+(*(nodo+nn)).bias);
 (*(nodo+nn)).inp = 0;
 return (0);
}

f6(int nr,LONG nn,int f,float *b)
/* Come f5 ma con memoria */
/* tempo di dimezz. pari a un ciclo */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = (dsig2(((*(nodo+nn)).stato)));return (0);}  /* derivata */
 (*(nodo+nn)).stato = sigma2(((*(nodo+nn)).inp)+(*(nodo+nn)).bias+ ((*(nodo+nn)).stato / 2));
 (*(nodo+nn)).inp = 0;
 return (0);
}

f13(int nr,LONG nn,int f,float *b)
/* Funzione sigmoide centrata sullo 0 e con valori da -1 a 1        */
/* funzione calcolata secondo la formula y=(exp(x)-1)/(exp(x)+1) */
/* derivata in funzione dello stato : -(y+1)(y-1)/2       */
{
 double x,ex;
 float y;
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { y = (*(nodo+nn)).stato;
	      *b = -(y+1)*(y-1)/2  ;return (0);}  /* derivata */
 x = (*(nodo+nn)).inp+(*(nodo+nn)).bias ; ex = exp(x);
 (*(nodo+nn)).stato = (float)((ex-1)/(ex+1)) ;
 (*(nodo+nn)).inp = 0;
 return (0);
}

f15(int nr,LONG nn,int f,float *b)
/* Funzione sigmoide centrata sullo 0 ma con valori da 0 a 1 */
/* cioe' traslata in alto e con range dimezzato */
/* funzione calcolata secondo la formula Y=1/1+exp(-x) */
/* derivata in funzione dello stato : y(1-y) */
{
 double x,ex;
 float y;
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { y = (*(nodo+nn)).stato;
	      *b = y*(1 - y);  return (0);}   /* derivata */
 x = (*(nodo+nn)).inp+(*(nodo+nn)).bias; ex = exp(-x);
 (*(nodo+nn)).stato = (float)(1/(1+ex));
 (*(nodo+nn)).inp = 0;
 return (0);
}

/********************** RUTINES DI SERVIZIO PER LE FUNZ.***********************/

/* Trasformazione sigma non lineare normalizzata all'int. -100.. 100   */

float sigma(float x)
{
 /* valori della funz. sigmoide -100..100 per attivazione 0..599 */
 /* per attiv.  -599..0  si hanno gli stessi valori ma negativi  */
 /* cioe' se x>0 y=T(x) se x<0 y=-T(x)                           */

static float semisig[] =
{
.00,.00,.01,.01,.02,.02,.03,.03,.04,.04,.05,.05,.06,.06,.07,.07,.08,.08,.09,.09,
.10,.10,.11,.11,.12,.12,.13,.13,.14,.14,.15,.15,.16,.16,.17,.17,.18,.18,.19,.19,
.20,.20,.21,.21,.22,.22,.23,.23,.24,.24,.24,.25,.25,.26,.26,.27,.27,.28,.28,.29,
.29,.30,.30,.30,.31,.31,.32,.32,.33,.33,.34,.34,.35,.35,.35,.36,.36,.37,.37,.38,
.38,.38,.39,.39,.40,.40,.41,.41,.41,.42,.42,.43,.43,.43,.44,.44,.45,.45,.45,.46,
.46,.47,.47,.47,.48,.48,.49,.49,.49,.50,.50,.50,.51,.51,.52,.52,.52,.53,.53,.53,
.54,.54,.54,.55,.55,.55,.56,.56,.56,.57,.57,.58,.58,.58,.58,.59,.59,.59,.60,.60,
.60,.61,.61,.61,.62,.62,.62,.63,.63,.63,.64,.64,.64,.64,.65,.65,.65,.66,.66,.66,
.66,.67,.67,.67,.68,.68,.68,.68,.69,.69,.69,.69,.70,.70,.70,.70,.71,.71,.71,.71,
.72,.72,.72,.72,.73,.73,.73,.73,.74,.74,.74,.74,.74,.75,.75,.75,.75,.76,.76,.76,
.76,.76,.77,.77,.77,.77,.77,.78,.78,.78,.78,.78,.79,.79,.79,.79,.79,.80,.80,.80,
.80,.80,.80,.81,.81,.81,.81,.81,.81,.82,.82,.82,.82,.82,.82,.83,.83,.83,.83,.83,
.83,.84,.84,.84,.84,.84,.84,.84,.85,.85,.85,.85,.85,.85,.85,.86,.86,.86,.86,.86,
.86,.86,.86,.87,.87,.87,.87,.87,.87,.87,.87,.88,.88,.88,.88,.88,.88,.88,.88,.88,
.89,.89,.89,.89,.89,.89,.89,.89,.89,.89,.90,.90,.90,.90,.90,.90,.90,.90,.90,.90,
.91,.91,.91,.91,.91,.91,.91,.91,.91,.91,.91,.91,.92,.92,.92,.92,.92,.92,.92,.92,
.92,.92,.92,.92,.92,.93,.93,.93,.93,.93,.93,.93,.93,.93,.93,.93,.93,.93,.93,.93,
.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.95,.95,.95,
.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.96,.96,
.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,
.96,.96,.96,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,
.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.98,.98,.98,
.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,
.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,
.98,.98,.98,.98,.98,.98,.98,.98,.98,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99
};
 int ax; float y;
 ax = (int) (fabs(x)*100);
 if (ax > 599) {y = 1;}
 else {y= semisig[ax];}
 if (x < 0) return(-y);
 return(y);
}

/* trasformazione non lineare sigma2 normalizzata all'int. 0..1  */

float sigma2(float x)
{
 /* valori della funz. sigmoide 0..100 per attivaz.  0..511   */
 /* per attiv. -511..0 si ha 100-stessi valori                */
 /* cioe' se x>0 y=T(x) se x<0 y=100-T(x)                     */

static float semisig2[] =
{
.50,.50,.50,.51,.51,.51,.51,.52,.52,.52,.52,.53,.53,.53,.53,.54,.54,.54,.54,.55,
.55,.55,.55,.56,.56,.56,.56,.57,.57,.57,.57,.58,.58,.58,.58,.59,.59,.59,.59,.60,
.60,.60,.60,.61,.61,.61,.61,.62,.62,.62,.62,.62,.63,.63,.63,.63,.64,.64,.64,.64,
.65,.65,.65,.65,.65,.66,.66,.66,.66,.67,.67,.67,.67,.67,.68,.68,.68,.68,.69,.69,
.69,.69,.69,.70,.70,.70,.70,.70,.71,.71,.71,.71,.72,.72,.72,.72,.72,.73,.73,.73,
.73,.73,.73,.74,.74,.74,.74,.74,.75,.75,.75,.75,.75,.76,.76,.76,.76,.76,.76,.77,
.77,.77,.77,.77,.78,.78,.78,.78,.78,.78,.79,.79,.79,.79,.79,.79,.80,.80,.80,.80,
.80,.80,.81,.81,.81,.81,.81,.81,.81,.82,.82,.82,.82,.82,.82,.82,.83,.83,.83,.83,
.83,.83,.83,.84,.84,.84,.84,.84,.84,.84,.85,.85,.85,.85,.85,.85,.85,.85,.86,.86,
.86,.86,.86,.86,.86,.86,.87,.87,.87,.87,.87,.87,.87,.87,.87,.88,.88,.88,.88,.88,
.88,.88,.88,.88,.88,.89,.89,.89,.89,.89,.89,.89,.89,.89,.89,.90,.90,.90,.90,.90,
.90,.90,.90,.90,.90,.90,.91,.91,.91,.91,.91,.91,.91,.91,.91,.91,.91,.91,.92,.92,
.92,.92,.92,.92,.92,.92,.92,.92,.92,.92,.92,.92,.93,.93,.93,.93,.93,.93,.93,.93,
.93,.93,.93,.93,.93,.93,.93,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,.94,
.94,.94,.94,.94,.94,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,.95,
.95,.95,.95,.95,.95,.95,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,
.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.96,.97,.97,.97,.97,.97,.97,.97,.97,
.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,.97,
.97,.97,.97,.97,.97,.97,.97,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,
.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,
.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.98,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,
.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99,.99
};
 int ax; float y;
 ax = (int) (fabs(x)*100);
 if (ax > 539) {y = 1;}
 else {y= semisig2[ax];}
 if (x < 0) return(1-y);
 return(y);
}
/* derivata di sigma                        */

float dsig(float x)
{
 /* derivata della sigmoide -100..100 in funz. dello stato (output) */
static float tdsig[] =
{
.00,.01,.02,.03,.04,.05,.06,.07,.08,.09,.09,.10,.11,.12,.13,.14,.15,.16,.16,.17,
.18,.19,.20,.20,.21,.22,.23,.23,.24,.25,.25,.26,.27,.28,.28,.29,.30,.30,.31,.31,
.32,.33,.33,.34,.34,.35,.35,.36,.36,.37,.37,.38,.38,.39,.39,.40,.40,.41,.41,.42,
.42,.42,.43,.43,.44,.44,.44,.45,.45,.45,.45,.46,.46,.46,.47,.47,.47,.47,.48,.48,
.48,.48,.48,.49,.49,.49,.49,.49,.49,.49,.49,.50,.50,.50,.50,.50,.50,.50,.50,.50,
.50,
.50,.50,.50,.50,.50,.50,.50,.50,.50,.49,.49,.49,.49,.49,.49,.49,.49,.48,.48,.48,
.48,.48,.47,.47,.47,.47,.46,.46,.46,.45,.45,.45,.45,.44,.44,.44,.43,.43,.42,.42,
.42,.41,.41,.40,.40,.39,.39,.38,.38,.37,.37,.36,.36,.35,.35,.34,.34,.33,.33,.32,
.31,.31,.30,.30,.29,.28,.28,.27,.26,.25,.25,.24,.23,.23,.22,.21,.20,.20,.19,.18,
.17,.16,.16,.15,.14,.13,.12,.11,.10,.10,.09,.08,.07,.06,.05,.04,.03,.02,.01,.00,
};
 return((float) tdsig[(int) ((x+1)*100)]);
}

/* derivata di sigma2                       */

float dsig2(float x)
{
 /* derivata della sigmoide 0..100 in funzione dello stato (output) */
static float tdsig2[] =
{
.00,.01,.02,.03,.04,.05,.06,.07,.07,.08,.09,.10,.11,.11,.12,.13,.13,.14,.15,.15,
.16,.17,.17,.18,.18,.19,.19,.20,.20,.21,.21,.21,.22,.22,.22,.23,.23,.23,.24,.24,
.24,.24,.24,.25,.25,.25,.25,.25,.25,.25,
.25,
.25,.25,.25,.25,.25,.25,.25,.24,.24,.24,
.24,.24,.23,.23,.23,.22,.22,.22,.21,.21,.21,.20,.20,.19,.19,.18,.18,.17,.17,.16,
.15,.15,.14,.13,.13,.12,.11,.11,.10,.09,.08,.07,.07,.06,.05,.04,.03,.02,.01,.00,
};
 return((float) tdsig2[(int)(x*100)]);
}

/**************** carica le funzioni in tabella **************************/
struct tipofun
{
  char  *nomefun;
  int   far (*fun)();
}
listafun[] =
{ {"f1",f1},
  {"f2",f2},
  {"f3",f3},
  {"f4",f4},
  {"f5",f5},
  {"f6",f6},
  {"f7",f7},
  {"f8",f8},
  {"f9",f9},
  {"f10",f10},
  {"f13",f13},
  {"f15",f15},
  {"a1",a1},
  {"a2",a2},
  {"a3",a3},
  {"a4",a4},
  {"a5",a5},
  {"a6",a6} };

#define NFUN (sizeof(listafun)/sizeof(struct tipofun))

void far *carfunz (char *tok)
{
  int i; int ret;
  for (i=0;i< NFUN;i++)
  {
    ret = strcmp(tok,listafun[i].nomefun);
    if (ret == 0) break;
  }
  if (i == NFUN) return(0);
  return(listafun[i].fun);
}

char *leggefunz (int far (*fun)())
{
  int i;
  for (i=0;i< NFUN;i++)
  {
    if (fun == listafun[i].fun) break;
  }
  if (i == NFUN) return("*");
  return(listafun[i].nomefun);
}

void fine()
{
 deallocamem();
 exit(-1);
}
/*-*/
/***************************************************************************/

/*****************************************************************************/
/*                        LIBRERIA DI GESTIONE                               */
/*****************************************************************************/

rmnet(int *maxr)
{
 *maxr = totr;
 return 0;
}

wmnet(int maxr)
{
 if (maxr > totr) return -1;
 totr= maxr;
 return 0;
}

totnn(int nr, LONG *tnodi)
{
 if (nr > totr) return -1;
 *tnodi = (r+nr)->d1;
 return 0;
}

rmlay(int nr,int *liv)
{
 if (nr > totr) return -1;
 *liv = (r+nr)->maxliv;
 return 0;
}

wmlay(int nr,int liv)
{
 if (nr > totr) return -1;
 if (liv > (r+nr)->maxliv) return -1;
 (r+nr)->maxliv = liv;
 return 0;
}

rlay(int nr,int nliv,LONG *sn,LONG *en)
{
 struct livello far *liv;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 *sn = liv->sn;
 *en = liv->en;
 return 0;
}

rstatl(int nr,int nliv,float stato[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 LONG nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 if (dim < liv->en - liv->sn + 1) return -1;
 i=1;
 for (nn= liv->sn; nn<= liv->en;nn++)
     {stato[i] = (*(nodo+nn)).stato;i++;}
 return i-1;
}

wstatl(int nr,int nliv,float stato[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 LONG nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 if (dim < liv->en - liv->sn + 1) return -1;
 i=1;
 for (nn= liv->sn; nn<= liv->en;nn++)
     {(*(nodo+nn)).stato = stato[i];i++;}
 return i-1;
}

rinpl(int nr,int nliv,float inp[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 LONG nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 if (dim < liv->en - liv->sn + 1) return -1;
 i=1;
 for (nn= liv->sn; nn<= liv->en;nn++)
     {inp[i] = (*(nodo+nn)).inp;i++;}
 return i-1;
}

winpl(int nr,int nliv,float inp[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 LONG nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 if (dim < liv->en - liv->sn + 1) return -1;
 i=1;
 for (nn= liv->sn; nn<= liv->en;nn++)
     {(*(nodo+nn)).inp = inp[i];i++;}
 return i-1;
}

rerrl(int nr,int nliv,float err[],int dim)
{
 return rinpl(nr, nliv, err, dim);
}

werrl(int nr,int nliv,float err[],int dim)
{
 return winpl(nr, nliv, err, dim);
}

rbiasl(int nr,int nliv,float bias[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 LONG nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 if (dim < liv->en - liv->sn + 1) return -1;
 i=1;
 for (nn= liv->sn; nn<= liv->en;nn++)
     {bias[i] = (*(nodo+nn)).bias;i++;}
 return i-1;
}

wbiasl(int nr,int nliv,float bias[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 LONG nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 if (dim < liv->en - liv->sn + 1) return -1;
 i=1;
 for (nn= liv->sn; nn<= liv->en;nn++)
     {(*(nodo+nn)).bias = bias[i];i++;}
 return i-1;
}

rwgtl(int nr,LONG nn,int nlivp,float peso[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 struct coll    far *collnn;
 LONG h,nh,sn,en,nnp;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (nlivp > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nlivp;
 sn = liv->sn; en = liv->en;
 collnn = (*(nodo+nn)).coll ;
 nh = (*(nodo+nn)).ncoll ;
 i=1;
 for (h= 0; h<= nh;h++)
   {
     nnp = (*(collnn+h)).nodo ;
     if( nnp >= sn && nnp <= en)
       {if (i > dim) return -1; else {peso[i] = (*(collnn+h)).peso ;i++;}}
   }
 return i-1;
}

wwgtl(int nr,LONG nn,int nlivp,float peso[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 struct coll    far *collnn;
 LONG h,nh,sn,en,nnp;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (nlivp > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nlivp;
 sn = liv->sn; en = liv->en;
 collnn = (*(nodo+nn)).coll ;
 nh = (*(nodo+nn)).ncoll ;
 i=1;
 for (h= 0; h<= nh;h++)
   {
     nnp = (*(collnn+h)).nodo ;
     if( nnp >= sn && nnp <= en)
       {if (i > dim) return -1; else { (*(collnn+h)).peso = peso[i];i++;}}
   }
 return i-1;
}

rwgtil(int nr,LONG npp,int nliva,float peso[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 struct coll    far *collnn;
 LONG h,nh,sn,en,nnp,nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (nliva > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliva;
 sn = liv->sn; en = liv->en;
 i=1;
 for (nn=sn;nn<=en;nn++)
 {
   collnn = (*(nodo+nn)).coll ;
   nh = (*(nodo+nn)).ncoll ;
   for (h= 0; h<= nh;h++)
   {
     nnp = (*(collnn+h)).nodo ;
     if( nnp == npp)
       {if (i > dim) return -1; else {peso[i] = (*(collnn+h)).peso ;i++;}}
   }
 }
 return i-1;
}

wpesoil(int nr,LONG npp,int nliva,float peso[],int dim)
{
 struct livello far *liv;
 struct nodo    far *nodo;
 struct coll    far *collnn;
 LONG h,nh,sn,en,nnp,nn;
 int i;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (nliva > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliva;
 sn = liv->sn; en = liv->en;
 i=1;
 for (nn=sn;nn<=en;nn++)
 {
   collnn = (*(nodo+nn)).coll ;
   nh = (*(nodo+nn)).ncoll ;
   for (h= 0; h<= nh;h++)
   {
     nnp = (*(collnn+h)).nodo ;
     if( nnp == npp)
       {if (i > dim) return -1; else {(*(collnn+h)).peso = peso[i];i++;}}
   }
 }
 return i-1;
}

rstat(int nr,LONG nn,float *stato)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *stato = (*(nodo+nn)).stato;
 return 0;
}

rbias(int nr,LONG nn,float *sog)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *sog= (*(nodo+nn)).bias;
 return 0;
}

rinp(int nr,LONG nn,float *inp)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *inp= (*(nodo+nn)).inp;
 return 0;
}

rerr(int nr,LONG nn,float *err)
{
  return rinp(nr,nn,err);
}


rfun(int nr,LONG nn,char fun[],char az[])
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 strncpy(fun,leggefunz((*(nodo+nn)).funz),10);
 strncpy(az,leggefunz((*(nodo+nn)).azione),10);
 return 0;
}

wfun(int nr,LONG nn,char fun[],char az[])
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).funz=carfunz(fun);
 (*(nodo+nn)).azione=carfunz(az);
 return 0;
}

wstat(int nr,LONG nn,float stato)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).stato = stato;
 return 0;
}

wbias(int nr,LONG nn,float bias)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).bias = bias;
 return 0;
}

winp(int nr,LONG nn,float inp)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).inp = inp;
 return 0;
}

werr(int nr,LONG nn,float err)
{
 return winp(nr,nn,err);
}


rnconn(int nr,LONG nn,LONG *ncoll)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *ncoll= (*(nodo+nn)).ncoll;
 return 0;
}

rconn(int nr,LONG nn,LONG h,float *peso, LONG *ni)
{
 struct coll    far *collnn;
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 collnn = (*(nodo+nn)).coll ;
 *peso  = (*(collnn+h)).peso ;
 *ni    = (*(collnn+h)).peso ;
 return 0;
}

wwgt(int nr,LONG nn,LONG h,float np)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (h > (*(nodo+nn)).ncoll) return -1;
 (*((*(nodo+nn)).coll+h)).peso = np;
 return 0;
}

wnodp(int nr,LONG nn,LONG h,LONG ni)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (h > (*(nodo+nn)).ncoll) return -1;
 (*((*(nodo+nn)).coll+h)).nodo = ni;
 return 0;
}
wnconn(int nr,LONG nn,LONG ncoll)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (ncoll > (*(nodo+nn)).ncoll) return -1;
 (*(nodo+nn)).ncoll = ncoll;
 return 0;
}
/*****************************************************************************/


/*****************************************************************************/
/*                          MESSAGGI DI ERRORE                               */
/*****************************************************************************/
void errmess (int cod)
{
 switch(cod)
  {
   case NOMEM   : printf("Can't allocate memory \r\n");break;
   case NOFILEI : printf("Can't open file %s \r\n",fileinp);break;
   case NOFILEO : printf("Can't open file %s \r\n",fileout);break;
   case NODIM   : printf("Error in dimensions or no dimensions \r\n");break;
   case NONODO  : printf("Error or no values for node \r\n");break;
   case TOOCOLL : printf("Too connections (> total connections) \r\n");break;
   case NOLIV   : printf("Error or no layer's number \r\n");break;
   case TOOLIV  : printf("Layer's number  > 99 \r\n");break;
   case NOMEMV  : printf("Insufficient memory for arrays inp, out, dat \r\n");break;
   case NOFILEES: printf("Can't open file %s \r\n",fileese);break;
   case ERRESE  : printf("Error in training file  \r\n");break;
   case NOTRETE : printf("No total nets \r\n");break;
   case NOTLIV  : printf("No total layers \r\n");break;
   case NONUMR  : printf("No net number \r\n");break;
   case TOONET  : printf("Too nets ( > 1000) \r\n");break;
   case NOSTRUCT: printf("Don't still exist structure for nets descr. \r\n");break;
   case CREARETE: printf("Don't still exist net  \r\n");break;
  }
}
/*****************************************************************************/


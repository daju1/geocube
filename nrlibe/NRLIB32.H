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
/*   and produce a file of output values.                                     */
/*   Input file format : n-ple of input values (corresp. at n inp. of layer 0)*/
/*                                                                            */
/*                                                                            */
/*   Backward training :                                                      */
/*                                                                            */
/*   Basic function is <backprop> ; this function apply  the EBP rule from    */
/*   layer B to layer A .                                                     */
/*   For each node of a layer the error value is calculated on basis of error */
/*   at next layer and at the same time weigts  are corrected     .           */
/*   At end , error at layer A is loss.                                       */
/*   We can backpropagate only error without weigts correction by function    */
/*   <backproperr> instead of previous function; but in this case we must use */
/*   the function <cancerr> after, because buffers for forward and backward   */
/*   are partially coincident .                                               */
/*   For default bias is not modified , but it's possible  do it by function  */
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


# define MAX_RAND 0x7FFF

# define NULLO 0

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

 int  a1(int net,LONG nn){}
 int  a2(int net,LONG nn){}
 int  a3(int net,LONG nn){}
 int  a4(int net,LONG nn){}
 int  a5(int net,LONG nn){}
 int  a6(int net,LONG nn){}

 int  f7(int net,LONG nn,int f,float *d) {}
 int  f8(int net,LONG nn,int f,float *d) {}
 int  f9(int net,LONG nn,int f,float *d) {}
 int  f10(int net,LONG nn,int f,float *d) {}

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

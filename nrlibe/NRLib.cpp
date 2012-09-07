// NRLib.cpp: implementation of the NRLib class.
//
//////////////////////////////////////////////////////////////////////

#include "NRLib.h"
#include <time.h>
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
#include <string.h>
//#include <ctype.h>

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

static char copyright[]="C.o.py.ri.ght b.y D.a.n.i.e.l.e D.e.n.a.r.o";

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


NRLib::NRLib()
{
	fileinp = new char[250];
	fileout = new char[250];
	fileese = new char[250];

	strcpy(fileinp , "nnetsinp.dat");
	strcpy(fileout , "nnetsout.dat");
	strcpy(fileese , "nettrain.dat");
/*****************************************************************************/

	nep=1;                    /* numero epoche di addestram.  */
	minerr=0;                 /* errore minimo di convergenza */
	epsl= 0.8f;                /* cost. apprendimento          */
	alfa= 0.5f;                /* coeff. di momento            */
	randa=-0.4f;               /* estremo inf. gen. rand. pesi */
	randb=0.4f;                /* estremo sup. gen. rand. pesi */
	numr= 1;                  /* num. della rete in consideraz.*/

	flgbias=0;      /* no*/   /* flag per la correzione del bias*/
	flgdeb=2;                 /* flag visualizz. (def=mass.)  */

	flgrete=0;                /* flag di rete definita*/
	flgstrr=0;                /* flag di struttura reti definita*/
/*****************************************************************************/

	treti=0;
	//=======Example1
	tu=10;                   /* Default nets number (units)                 */
	ua=5;                    /* Default goods nets (have treaning from file)*/
	intvis=50;               /* Print average errors default interval       */
	tlife=5000;              /* Life cycles                                 */
	filetrain = new char [250];
	strcpy(filetrain, "nettrain.dat");/* Trainer file name                        */

	//=======Example1
	//=======Example2
	tgen=300;                         /* Total default generations          */
	//=======Example2

}

NRLib::~NRLib()
{
	if (fileinp) delete[] fileinp;
	if (fileout) delete[] fileout;
	if (fileese) delete[] fileese;
	if (filetrain) delete[] filetrain;
}
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

int NRLib::loadnet(char *filei)
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

int NRLib::savenet(char *fileo)
{
  LONG ncol=0;LONG nn, h;
  int nliv,nr;
//  char *leggefunz();
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

int NRLib::createallnet(int tr,int nliv,LONG vn[],char vf[][10],char va[][10])
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

int NRLib::createstruct(int tr,int vliv[])
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

int NRLib::createnet(int nr,LONG vn[],char vf[][10],char va[][10])
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

int NRLib::ininet(int nr)
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

int NRLib::copynet(int nra,int nrb)
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

int NRLib::cancnets()
{
  deallocamem();
  return 0;
}

/*************************  ROUTINES PER L'ALLOCAZIONE DELLA MEMORIA **********/

char far *NRLib::allocamem(LONG n,LONG s)
{
  char far *iseg;
  if (flgdeb>0) printf("Alloc  %d  bytes ",n*s);
# ifdef B16
    if (n*s > 0xFFFF) return(NULLO);
# endif
  iseg = (char *)ALLOCA(n,s);
  if (flgdeb>0) {if ((long)iseg != 0) printf("   starting %p\r\n",iseg);}
  return(iseg);
}

int NRLib::deallocamem()
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

int NRLib::scantok(char tok[255],FILE *fp)
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

int NRLib::poschar(char *buff,char ch)
{
  int i;
  for (i=0;i<strlen(buff);i++)
   {if (*(buff+i) == ch)  return(i);}
  return(-1);
}

int NRLib::copys(char *buff1,char *buff2,int lastpos)
{
  int i;
  for (i=0;i<=lastpos;i++) *(buff1+i) = *(buff2+i);
  *(buff1+lastpos+1) =0;
  return 0;
}

float NRLib::randab(float ra,float rb)
{
 float num;
 num = rand()&0x7FFF; num = num/MAX_RAND;
 return (num * (rb-ra) + ra);
}

/******************************************************************************/
/*                             Nucleo operativo                               */
/******************************************************************************/

/*********************** ELABORAZIONE ATTRAVERSO I LIVELLI ********************/

int NRLib::produce(int nr,char *inpdat,char *outdat)
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
  rets=(float *)calloc(ninp+1,sizeof(*vinp));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vinp=rets;
  rets=(float *)calloc(nout+1,sizeof(*vout));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vout=rets;
  rets=(float *)calloc(nout+1,sizeof(*vdat));
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


float NRLib::compute(int nr,float vinp[],float vout[],float vdat[])
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

int NRLib::propagate(int nr,int liva,int livb)
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


int NRLib::param(char *nome,char *val)
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


float NRLib::train(int nr,char *fileese)
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
  rets=(float *)calloc(ninp+1,sizeof(*vinp));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vinp=rets;
  rets=(float *)calloc(nout+1,sizeof(*vout));
  if (rets == NULLO) {errmess(NOMEMV);fine();}; vout=rets;
  rets=(float *)calloc(nout+1,sizeof(*vdat));
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



int NRLib::learn(int nr,float verr[])
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

int NRLib::backprop(int nr,int liva,int livb)
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

int NRLib::backproperr(int nr,int liva,int livb)
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

int NRLib::cancerr(int nr,int liva,int livb)
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

void NRLib::motore(int nr,LONG strn,LONG stpn)
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
      if ((*nodonn).funz != 0)   (this->*( (int (NRLib::*)(int,LONG,int,float*)) (*nodonn).funz) )(nr,nn,0,&b);
      if ((*nodonn).azione != 0) (this->*((int (NRLib::*)(int,LONG)) (*nodonn).azione))(nr,nn);
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

void NRLib::ebp(int nr,LONG strn,LONG stpn)
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
	  (this->*((int (NRLib::*)(int,LONG,int,float*))(*(nodo+i)).funz))(nr,i,1,&dfuni);
	  dd = (erri * dfuni)   ;
	  errnn = errnn + (dd * peso) ;
	  dpeso = - ((epsl * dd) * ((*nodonn).stato ));
	  dpeso=dpeso+(dp*alfa); peso=peso+dpeso; if (peso == 0) peso=.000001f;
	  (*(collnn+h)).peso = peso ; (*(collnn+h)).dp=dpeso;
	  }
	 }
	 errnn = ((*nodonn).inp) + errnn;
	 (*nodonn).inp =  errnn;

	 if (flgbias == 1)
	 {
	 bias=(*nodonn).bias;db=(*nodonn).dbias;
	 (this->*((int (NRLib::*)(int,LONG,int,float*))(*nodonn).funz))(nr,nn,1,&dfunn);
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

int NRLib::f1(int nr,LONG nn,int f,float *b)
/* Funzione unitaria sposta semplicemente input su stato  */
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (f == 1) { *b = 1;return (0);}  /* derivata */
 (*(nodo+nn)).stato = (*(nodo+nn)).inp+(*(nodo+nn)).bias ;
 (*(nodo+nn)).inp = 0;
 return (0);
}

int NRLib::f2(int nr,LONG nn,int f,float *b)
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



int NRLib::f3(int nr,LONG nn,int f,float *b)
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

int NRLib::f4(int nr,LONG nn,int f,float *b)
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



int NRLib::f5(int nr,LONG nn,int f,float *b)
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

int NRLib::f6(int nr,LONG nn,int f,float *b)
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

int NRLib::f13(int nr,LONG nn,int f,float *b)
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

int NRLib::f15(int nr,LONG nn,int f,float *b)
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

float NRLib::sigma(float x)
{
 /* valori della funz. sigmoide -100..100 per attivazione 0..599 */
 /* per attiv.  -599..0  si hanno gli stessi valori ma negativi  */
 /* cioe' se x>0 y=T(x) se x<0 y=-T(x)                           */

static float semisig[] =
{
.00f,.00f,.01f,.01f,.02f,.02f,.03f,.03f,.04f,.04f,.05f,.05f,.06f,.06f,.07f,.07f,.08f,.08f,.09f,.09f,
.10f,.10f,.11f,.11f,.12f,.12f,.13f,.13f,.14f,.14f,.15f,.15f,.16f,.16f,.17f,.17f,.18f,.18f,.19f,.19f,
.20f,.20f,.21f,.21f,.22f,.22f,.23f,.23f,.24f,.24f,.24f,.25f,.25f,.26f,.26f,.27f,.27f,.28f,.28f,.29f,
.29f,.30f,.30f,.30f,.31f,.31f,.32f,.32f,.33f,.33f,.34f,.34f,.35f,.35f,.35f,.36f,.36f,.37f,.37f,.38f,
.38f,.38f,.39f,.39f,.40f,.40f,.41f,.41f,.41f,.42f,.42f,.43f,.43f,.43f,.44f,.44f,.45f,.45f,.45f,.46f,
.46f,.47f,.47f,.47f,.48f,.48f,.49f,.49f,.49f,.50f,.50f,.50f,.51f,.51f,.52f,.52f,.52f,.53f,.53f,.53f,
.54f,.54f,.54f,.55f,.55f,.55f,.56f,.56f,.56f,.57f,.57f,.58f,.58f,.58f,.58f,.59f,.59f,.59f,.60f,.60f,
.60f,.61f,.61f,.61f,.62f,.62f,.62f,.63f,.63f,.63f,.64f,.64f,.64f,.64f,.65f,.65f,.65f,.66f,.66f,.66f,
.66f,.67f,.67f,.67f,.68f,.68f,.68f,.68f,.69f,.69f,.69f,.69f,.70f,.70f,.70f,.70f,.71f,.71f,.71f,.71f,
.72f,.72f,.72f,.72f,.73f,.73f,.73f,.73f,.74f,.74f,.74f,.74f,.74f,.75f,.75f,.75f,.75f,.76f,.76f,.76f,
.76f,.76f,.77f,.77f,.77f,.77f,.77f,.78f,.78f,.78f,.78f,.78f,.79f,.79f,.79f,.79f,.79f,.80f,.80f,.80f,
.80f,.80f,.80f,.81f,.81f,.81f,.81f,.81f,.81f,.82f,.82f,.82f,.82f,.82f,.82f,.83f,.83f,.83f,.83f,.83f,
.83f,.84f,.84f,.84f,.84f,.84f,.84f,.84f,.85f,.85f,.85f,.85f,.85f,.85f,.85f,.86f,.86f,.86f,.86f,.86f,
.86f,.86f,.86f,.87f,.87f,.87f,.87f,.87f,.87f,.87f,.87f,.88f,.88f,.88f,.88f,.88f,.88f,.88f,.88f,.88f,
.89f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.90f,.90f,.90f,.90f,.90f,.90f,.90f,.90f,.90f,.90f,
.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,
.92f,.92f,.92f,.92f,.92f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,
.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.95f,.95f,.95f,
.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.96f,.96f,
.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,
.96f,.96f,.96f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,
.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.98f,.98f,.98f,
.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,
.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,
.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f
};
 int ax; float y;
 ax = (int) (fabs(x)*100);
 if (ax > 599) {y = 1;}
 else {y= semisig[ax];}
 if (x < 0) return(-y);
 return(y);
}

/* trasformazione non lineare sigma2 normalizzata all'int. 0..1  */

float NRLib::sigma2(float x)
{
 /* valori della funz. sigmoide 0..100 per attivaz.  0..511   */
 /* per attiv. -511..0 si ha 100-stessi valori                */
 /* cioe' se x>0 y=T(x) se x<0 y=100-T(x)                     */

static float semisig2[] =
{
.50f,.50f,.50f,.51f,.51f,.51f,.51f,.52f,.52f,.52f,.52f,.53f,.53f,.53f,.53f,.54f,.54f,.54f,.54f,.55f,
.55f,.55f,.55f,.56f,.56f,.56f,.56f,.57f,.57f,.57f,.57f,.58f,.58f,.58f,.58f,.59f,.59f,.59f,.59f,.60f,
.60f,.60f,.60f,.61f,.61f,.61f,.61f,.62f,.62f,.62f,.62f,.62f,.63f,.63f,.63f,.63f,.64f,.64f,.64f,.64f,
.65f,.65f,.65f,.65f,.65f,.66f,.66f,.66f,.66f,.67f,.67f,.67f,.67f,.67f,.68f,.68f,.68f,.68f,.69f,.69f,
.69f,.69f,.69f,.70f,.70f,.70f,.70f,.70f,.71f,.71f,.71f,.71f,.72f,.72f,.72f,.72f,.72f,.73f,.73f,.73f,
.73f,.73f,.73f,.74f,.74f,.74f,.74f,.74f,.75f,.75f,.75f,.75f,.75f,.76f,.76f,.76f,.76f,.76f,.76f,.77f,
.77f,.77f,.77f,.77f,.78f,.78f,.78f,.78f,.78f,.78f,.79f,.79f,.79f,.79f,.79f,.79f,.80f,.80f,.80f,.80f,
.80f,.80f,.81f,.81f,.81f,.81f,.81f,.81f,.81f,.82f,.82f,.82f,.82f,.82f,.82f,.82f,.83f,.83f,.83f,.83f,
.83f,.83f,.83f,.84f,.84f,.84f,.84f,.84f,.84f,.84f,.85f,.85f,.85f,.85f,.85f,.85f,.85f,.85f,.86f,.86f,
.86f,.86f,.86f,.86f,.86f,.86f,.87f,.87f,.87f,.87f,.87f,.87f,.87f,.87f,.87f,.88f,.88f,.88f,.88f,.88f,
.88f,.88f,.88f,.88f,.88f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.89f,.90f,.90f,.90f,.90f,.90f,
.90f,.90f,.90f,.90f,.90f,.90f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.91f,.92f,.92f,
.92f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,.92f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,.93f,
.93f,.93f,.93f,.93f,.93f,.93f,.93f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,.94f,
.94f,.94f,.94f,.94f,.94f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,.95f,
.95f,.95f,.95f,.95f,.95f,.95f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,
.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.96f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,
.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,.97f,
.97f,.97f,.97f,.97f,.97f,.97f,.97f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,
.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,
.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.98f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,
.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f,.99f
};
 int ax; float y;
 ax = (int) (fabs(x)*100);
 if (ax > 539) {y = 1;}
 else {y= semisig2[ax];}
 if (x < 0) return(1-y);
 return(y);
}
/* derivata di sigma                        */

float NRLib::dsig(float x)
{
 /* derivata della sigmoide -100..100 in funz. dello stato (output) */
static float tdsig[] =
{
.00f,.01f,.02f,.03f,.04f,.05f,.06f,.07f,.08f,.09f,.09f,.10f,.11f,.12f,.13f,.14f,.15f,.16f,.16f,.17f,
.18f,.19f,.20f,.20f,.21f,.22f,.23f,.23f,.24f,.25f,.25f,.26f,.27f,.28f,.28f,.29f,.30f,.30f,.31f,.31f,
.32f,.33f,.33f,.34f,.34f,.35f,.35f,.36f,.36f,.37f,.37f,.38f,.38f,.39f,.39f,.40f,.40f,.41f,.41f,.42f,
.42f,.42f,.43f,.43f,.44f,.44f,.44f,.45f,.45f,.45f,.45f,.46f,.46f,.46f,.47f,.47f,.47f,.47f,.48f,.48f,
.48f,.48f,.48f,.49f,.49f,.49f,.49f,.49f,.49f,.49f,.49f,.50f,.50f,.50f,.50f,.50f,.50f,.50f,.50f,.50f,
.50f,
.50f,.50f,.50f,.50f,.50f,.50f,.50f,.50f,.50f,.49f,.49f,.49f,.49f,.49f,.49f,.49f,.49f,.48f,.48f,.48f,
.48f,.48f,.47f,.47f,.47f,.47f,.46f,.46f,.46f,.45f,.45f,.45f,.45f,.44f,.44f,.44f,.43f,.43f,.42f,.42f,
.42f,.41f,.41f,.40f,.40f,.39f,.39f,.38f,.38f,.37f,.37f,.36f,.36f,.35f,.35f,.34f,.34f,.33f,.33f,.32f,
.31f,.31f,.30f,.30f,.29f,.28f,.28f,.27f,.26f,.25f,.25f,.24f,.23f,.23f,.22f,.21f,.20f,.20f,.19f,.18f,
.17f,.16f,.16f,.15f,.14f,.13f,.12f,.11f,.10f,.10f,.09f,.08f,.07f,.06f,.05f,.04f,.03f,.02f,.01f,.00f,
};
 return((float) tdsig[(int) ((x+1)*100)]);
}

/* derivata di sigma2                       */

float NRLib::dsig2(float x)
{
 /* derivata della sigmoide 0..100 in funzione dello stato (output) */
static float tdsig2[] =
{
.00f,.01f,.02f,.03f,.04f,.05f,.06f,.07f,.07f,.08f,.09f,.10f,.11f,.11f,.12f,.13f,.13f,.14f,.15f,.15f,
.16f,.17f,.17f,.18f,.18f,.19f,.19f,.20f,.20f,.21f,.21f,.21f,.22f,.22f,.22f,.23f,.23f,.23f,.24f,.24f,
.24f,.24f,.24f,.25f,.25f,.25f,.25f,.25f,.25f,.25f,
.25f,
.25f,.25f,.25f,.25f,.25f,.25f,.25f,.24f,.24f,.24f,
.24f,.24f,.23f,.23f,.23f,.22f,.22f,.22f,.21f,.21f,.21f,.20f,.20f,.19f,.19f,.18f,.18f,.17f,.17f,.16f,
.15f,.15f,.14f,.13f,.13f,.12f,.11f,.11f,.10f,.09f,.08f,.07f,.07f,.06f,.05f,.04f,.03f,.02f,.01f,.00f,
};
 return((float) tdsig2[(int)(x*100)]);
}

/**************** carica le funzioni in tabella **************************/
	//объ€вл€ем тип указател€:
	//объ€вл€ем тип указател€:
	struct tipofun
	{
		char  *nomefun;
		pToFunc   fun;
	};

tipofun listafun[] =
{ {"f1",	(int (NRLib::*)(void))NRLib::f1},
  {"f2",	(int (NRLib::*)(void))NRLib::f2},
  {"f3",	(int (NRLib::*)(void))NRLib::f3},
  {"f4",	(int (NRLib::*)(void))NRLib::f4},
  {"f5",	(int (NRLib::*)(void))NRLib::f5},
  {"f6",	(int (NRLib::*)(void))NRLib::f6},
  {"f7",	(int (NRLib::*)(void))NRLib::f7},
  {"f8",	(int (NRLib::*)(void))NRLib::f8},
  {"f9",	(int (NRLib::*)(void))NRLib::f9},
  {"f10",	(int (NRLib::*)(void))NRLib::f10},
  {"f13",	(int (NRLib::*)(void))NRLib::f13},
  {"f15",	(int (NRLib::*)(void))NRLib::f15},
  {"a1",	(int (NRLib::*)(void))NRLib::a1},
  {"a2",	(int (NRLib::*)(void))NRLib::a2},
  {"a3",	(int (NRLib::*)(void))NRLib::a3},
  {"a4",	(int (NRLib::*)(void))NRLib::a4},
  {"a5",	(int (NRLib::*)(void))NRLib::a5},
  {"a6",	(int (NRLib::*)(void))NRLib::a6} };

#define NFUN (sizeof(listafun)/sizeof(struct tipofun))

pToFunc NRLib::carfunz (char *tok)
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

char *NRLib::leggefunz (pToFunc fun)
{
  int i;
  for (i=0;i< NFUN;i++)
  {
    if (fun == listafun[i].fun) break;
  }
  if (i == NFUN) return("*");
  return(listafun[i].nomefun);
}

void NRLib::fine()
{
 deallocamem();
 exit(-1);
}
/*-*/
/***************************************************************************/

/*****************************************************************************/
/*                        LIBRERIA DI GESTIONE                               */
/*****************************************************************************/

int NRLib::rmnet(int *maxr)
{
 *maxr = totr;
 return 0;
}

int NRLib::wmnet(int maxr)
{
 if (maxr > totr) return -1;
 totr= maxr;
 return 0;
}

int NRLib::totnn(int nr, LONG *tnodi)
{
 if (nr > totr) return -1;
 *tnodi = (r+nr)->d1;
 return 0;
}

int NRLib::rmlay(int nr,int *liv)
{
 if (nr > totr) return -1;
 *liv = (r+nr)->maxliv;
 return 0;
}

int NRLib::wmlay(int nr,int liv)
{
 if (nr > totr) return -1;
 if (liv > (r+nr)->maxliv) return -1;
 (r+nr)->maxliv = liv;
 return 0;
}

int NRLib::rlay(int nr,int nliv,LONG *sn,LONG *en)
{
 struct livello far *liv;
 if (nr > totr) return -1;
 if (nliv > (r+nr)->maxliv ) return -1;
 liv=(r+nr)->liv+nliv;
 *sn = liv->sn;
 *en = liv->en;
 return 0;
}

int NRLib::rstatl(int nr,int nliv,float stato[],int dim)
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

int NRLib::wstatl(int nr,int nliv,float stato[],int dim)
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

int NRLib::rinpl(int nr,int nliv,float inp[],int dim)
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

int NRLib::winpl(int nr,int nliv,float inp[],int dim)
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

int NRLib::rerrl(int nr,int nliv,float err[],int dim)
{
 return rinpl(nr, nliv, err, dim);
}

int NRLib::werrl(int nr,int nliv,float err[],int dim)
{
 return winpl(nr, nliv, err, dim);
}

int NRLib::rbiasl(int nr,int nliv,float bias[],int dim)
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

int NRLib::wbiasl(int nr,int nliv,float bias[],int dim)
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

int NRLib::rwgtl(int nr,LONG nn,int nlivp,float peso[],int dim)
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

int NRLib::wwgtl(int nr,LONG nn,int nlivp,float peso[],int dim)
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

int NRLib::rwgtil(int nr,LONG npp,int nliva,float peso[],int dim)
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

int NRLib::wpesoil(int nr,LONG npp,int nliva,float peso[],int dim)
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

int NRLib::rstat(int nr,LONG nn,float *stato)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *stato = (*(nodo+nn)).stato;
 return 0;
}

int NRLib::rbias(int nr,LONG nn,float *sog)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *sog= (*(nodo+nn)).bias;
 return 0;
}

int NRLib::rinp(int nr,LONG nn,float *inp)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *inp= (*(nodo+nn)).inp;
 return 0;
}

int NRLib::rerr(int nr,LONG nn,float *err)
{
  return rinp(nr,nn,err);
}


int NRLib::rfun(int nr,LONG nn,char fun[],char az[])
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 strncpy(fun,leggefunz((*(nodo+nn)).funz),10);
 strncpy(az,leggefunz((*(nodo+nn)).azione),10);
 return 0;
}

int NRLib::wfun(int nr,LONG nn,char fun[],char az[])
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).funz=carfunz(fun);
 (*(nodo+nn)).azione=carfunz(az);
 return 0;
}

int NRLib::wstat(int nr,LONG nn,float stato)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).stato = stato;
 return 0;
}

int NRLib::wbias(int nr,LONG nn,float bias)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).bias = bias;
 return 0;
}

int NRLib::winp(int nr,LONG nn,float inp)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 (*(nodo+nn)).inp = inp;
 return 0;
}

int NRLib::werr(int nr,LONG nn,float err)
{
 return winp(nr,nn,err);
}


int NRLib::rnconn(int nr,LONG nn,LONG *ncoll)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 *ncoll= (*(nodo+nn)).ncoll;
 return 0;
}

int NRLib::rconn(int nr,LONG nn,LONG h,float *peso, LONG *ni)
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

int NRLib::wwgt(int nr,LONG nn,LONG h,float np)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (h > (*(nodo+nn)).ncoll) return -1;
 (*((*(nodo+nn)).coll+h)).peso = np;
 return 0;
}

int NRLib::wnodp(int nr,LONG nn,LONG h,LONG ni)
{
 struct nodo    far *nodo;
 nodo=(r+nr)->nodo;
 if (nr > totr) return -1;
 if (nn > (r+nr)->d1) return -1;
 if (h > (*(nodo+nn)).ncoll) return -1;
 (*((*(nodo+nn)).coll+h)).nodo = ni;
 return 0;
}
int NRLib::wnconn(int nr,LONG nn,LONG ncoll)
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
void NRLib::errmess (int cod)
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


int NRLib::main(int argc, char *argv[])
{
 long t1; long t2;
 int i;int fio;
 int fun;
 char nes[20],ers[20],fbs[10],eps[20],mos[20],ras[20],rbs[20];
 fun=0;

 for (i=1;i<argc;i++)
 {
   if (strncmp(argv[i],"/fu=",4) == 0)  {fun=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/ne=",4) == 0)  {nep=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/er=",4) == 0)  {minerr=atof(argv[i]+4);continue;}
   if (strncmp(argv[i],"/fi=",4) == 0)  {strcpy(fileinp,argv[i]+4);continue;}
   if (strncmp(argv[i],"/fo=",4) == 0)  {strcpy(fileout,argv[i]+4);continue;}
   if (strncmp(argv[i],"/fe=",4) == 0)  {strcpy(fileese,argv[i]+4);continue;}
   if (strncmp(argv[i],"/nt=",4) == 0)  {numr=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/bf=",4) == 0)  {flgbias=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/h",2) == 0)    {help();end();}
   if (strncmp(argv[i],"?",1)  == 0)    {help();end();}
   if (strncmp(argv[i],"/?",2) == 0)    {help();end();}
 }
 t1=clock();

 sprintf(nes,"%d",nep);
 sprintf(ers,"%f",minerr);
 sprintf(fbs,"%d",flgbias);
 param("ne",nes);
 param("er",ers);
 param("fb",fbs);

 param("fd","0");

 switch(fun)
 {
   case 0: loadnet(fileinp);produce(numr,"","");break;
   case 1: menu();break;
   case 2: printf("\n Loading and training net %d for %d epochs",numr,nep);
	   loadnet(fileinp);
	   param("fd","1");train(numr,fileese);
	   savenet(fileout);
	   printf("\n Saved nets to file %s ",fileout);
	   break;
 }

 t2=clock();
 printf("\n Time spent: %5.2f sec.",((float)(t2-t1))/CLOCK_PS);
 cancnets();
 return 0;

}

int NRLib::menu()
{
 char sel[10];
 int ss;
 LONG sn,en;
 int nninp;
 FILE *fp;
 do
 {
 printf("\x1B[2J");
 printf("\n                NET MANAGEMENT GENERAL MENU             \n\n\n");
 if (treti > 0) printf("\n %d Nets in memory \n\n",treti);
 if (treti == 0) printf("\n No nets in memory \n\n");
 printf("\n            1 - Nets load   \n");
 printf("\n            2 - Nets create \n");
 printf("\n            3 - Compute net  %d\n",numr);
 printf("\n            4 - Train   net  %d\n",numr);
 printf("\n            5 - Nets save     \n");
 printf("\n            6 - Modify parameters \n");
 printf("\n\n\n Choose (0 = exit)  : ");
 scanf("%4s",sel);ss=atoi(sel);fflush(stdin);
 param("fd","0");
 switch(ss)
 {
   case 1: fp=fopen(fileinp,"r");if (fp == (void *)NULLO)
	   {printf("\n File %s does not exist !",fileinp);scanf("%c",&sel[0]);
	   fflush(stdin);break;}
	   fclose(fp);
	   loadnet(fileinp);rmnet(&treti);break;
   case 2: creazione();break;
   case 3: printf("\n\n Compute net %d ;",numr);
	   rlay(numr,0,&sn,&en);nninp=en-sn+1;
	   printf(" insert %d value for input ;",nninp);
	   printf(" digit Ctrl-Z for return");
	   produce(numr,"","");break;
   case 4: fp=fopen(fileese,"r");if (fp == (void *)NULLO)
	   {printf("\n File %s does not exist !",fileinp);scanf("%c",&sel[0]);
	   fflush(stdin);break;}
	   fclose(fp);
	   {param("fd","2");train(numr,fileese);
	    printf("\n\n Press <enter> for more...");
	    scanf("%c",&sel[0]);fflush(stdin);
	    break;}
   case 5: fp=fopen(fileout,"r");if (fp != (void *)NULLO)
	   {printf("\n File %s already exist, overwrite it? (n/y)",fileinp);
	   scanf("%c",&sel[0]);fflush(stdin);if (sel[0]!='y')
	   {printf("\n NOT SAVED!"); scanf("%c",&sel[0]);fflush(stdin);fclose(fp);break;}
	   fclose(fp);}
	   fp=fopen(fileout,"w");if (fp == (void *)NULLO)
	   {printf("\n Impossible to open file %s !",fileinp);scanf("%c",&sel[0]);
	   break;}
	   fclose(fp);
	   printf("\n SAVE FILE %s",fileout);
	   savenet(fileout);break;
   case 6: modpar();break;
 }
 }while (ss != 0);
 return 0;

}

int NRLib::creazione()
{
 int nliv,i,ret,cnr,nr,maxliv,strmaxliv;
 int  vliv[1000];
 LONG vn[100];
 char vf[100][10];
 char va[100][10];
 char ch;

 _rete:
 printf("\x1B[2J");
 printf("\n            DEFINITION OF ALL NETS STRUCTURE     \n\n\n\n");
 printf("\n Total nets  (max   1000) : ");
 scanf("%d",&treti);fflush(stdin);
 if (treti > 1000) goto _rete;
 printf("\n");
 printf("\n All equals nets   ? (y/n):",i);
 ret=scanf("%c",&ch);fflush(stdin);if (ret<1) return 0;
 cnr=treti;if (ch != 'n') cnr=1;
 if (cnr == 1)
 { printf("\n Last net layer     (0 -- 99) : "); }
 else
 { printf("\n Max last net layer (0 -- 99) : "); }
 scanf("%d",&nliv);fflush(stdin);
 if (nliv > 99) goto _rete;
 maxliv=nliv;
 for (nr=1;nr<=treti;nr++) vliv[nr]=maxliv;
 createstruct(treti,vliv);

 for (nr=1;nr<=cnr;nr++)
 {
 livelli:
 printf("\x1B[2J");
 printf("\n               NET DEFINITION          %d\n\n\n\n",nr);
 if (cnr != 1)
 {
 rmlay(nr,&strmaxliv);
 printf("\n Last layer   (actualy %d) : ",strmaxliv);
 scanf("%d",&nliv);fflush(stdin);
 maxliv=nliv;
 if (maxliv > strmaxliv) goto livelli;
 wmlay(nr,maxliv);
 printf("\n");
 }
 for (i=0;i<=maxliv;i++)
 {
   printf("\n Total nodes of layer %3d                      :",i);
   ret=scanf("%I",&vn[i]);fflush(stdin);if (ret<1) return 0;
   printf("\n f1 : unitary function ");
   printf("\n f3 : sigmoid positiv and negativ (f13 calculated)");
   printf("\n f5 : sigmoid only positive (f15 calculated)");
   printf("\n Activ-function of nodes of layer %3d (f1 - f15):",i);
   ret=scanf("%10s",vf[i]);fflush(stdin);if (ret<1) return 0;
/* printf("\n Action of nodes of layer         %3d :",i);     */
/* ret=scanf("%10s",va[i]);fflush(stdin);if (ret<1) return;   */
   strcpy(va[i],"0");
 }
 createnet(nr,vn,vf,va);
 }
 if (cnr == 1)
 {
   for (nr=2;nr<=treti;nr++) {createnet(nr,vn,vf,va);}
 }
 return 0;
}

int NRLib::modpar()
{
 char sel[10];
 int ss;
 char nes[20],ers[20],fbs[10],eps[20],mos[20],ras[20],rbs[20];
 do
 {
  printf("\x1B[2J");
  printf("\n               PARAMETERS               \n\n\n\n");
  printf("\n  1 - Net load  file name      : %s ",fileinp);
  printf("\n  2 - Net save  file name      : %s ",fileout);
  printf("\n  3 - Trainer file   name      : %s ",fileese);
  printf("\n  4 - Epochs                   : %d ",nep);
  printf("\n  5 - Stop on q.error          : %f ",minerr);
  printf("\n  6 - Learning coefficient     : %f ",epsl);
  printf("\n  7 - Momentum coefficient     : %f ",alfa);
  printf("\n  8 - Weigts random range      : %f %f",randa,randb);
  printf("\n  9 - Bias adjust flag  (1=yes): %d ",flgbias);
  printf("\n 10 - Net selected             : %d ",numr);
  printf("\n\n\n What modify? (0=return): ");scanf("%4s",sel);ss=atoi(sel);
  switch(ss)
  {
    case 1: printf("\n\n\nNet load file name  :");scanf("%s",fileinp);break;
    case 2: printf("\n\n\nNet save file name  :");scanf("%s",fileout);break;
    case 3: printf("\n\n\nTrainer file name   :");scanf("%s",fileese);break;
    case 4: printf("\n\n\nEpochs :");scanf("%d",&nep);
	    sprintf(nes,"%d",nep);param("ne",nes);break;
    case 5: printf("\n\n\nStop on q.err. :");scanf("%f",&minerr);
	    sprintf(ers,"%f",minerr);param("er",ers);break;
    case 6: printf("\n\n\nLearning coefficient :");scanf("%f",&epsl);
	    sprintf(eps,"%f",epsl);param("ep",eps);break;
    case 7: printf("\n\n\nMomentum coefficient :");scanf("%f",&alfa);
	    sprintf(mos,"%f",alfa);param("mo",mos);break;
    case 8: printf("\n\n\nWeigts random range  :");scanf("%f %f",&randa,&randb);
	    sprintf(ras,"%f",randa);param("ra",ras);
	    sprintf(rbs,"%f",randb);param("rb",rbs);break;
    case 9: printf("\n\n\nBias adjust flag :");scanf("%d",&flgbias);
	    sprintf(fbs,"%d",flgbias);param("fb",fbs);break;
    case 10: printf("\n\n\nNet selected  :");scanf("%d",&numr);
	     if (numr > treti) numr = treti;break;
  }
 }while (ss != 0);
 return 0;

}

int NRLib::help()
{
 printf("\n ***** INTERACTIVE PROGRAM FOR FORWARD EBP NETS MANAGEMENT *****");
 printf("\n ");
 printf("\n Tree type of functionality:");
 printf("\n - like a filter; load nets and compute 1 net from stdinp to stdout");
 printf("\n - interactive menu to manage all nets");
 printf("\n - batch net training ; load nets and train 1 net by trainer file");
 printf("\n Command syntax: ");
 printf("\n   nrebp31 [/fu=..] [/ne=..] [/er=..] [/fi=...] [/fo=...] [/fe=...]");
 printf("\n           [/nt=..] [/bf=..] [/h] [?] [/?]");
 printf("\n   fu : functionality)");
 printf("\n        0 - like a filter             (def = 0)");
 printf("\n        1 - interactive menu ");
 printf("\n        2 - batch training   ");
 printf("\n   ne : learning epoch number         (def = 1)");
 printf("\n   er : stop learning on q.error      (def = 0)");
 printf("\n   bf : bias adjust flag              (def = 0 (no))");
 printf("\n   nt : net selected                  (def = 1)");
 printf("\n   fi : nets load file name           (def = nnetsinp.dat)");
 printf("\n   fo : nets save file name           (def = nnetsout.dat)");
 printf("\n   fe : trainer file name             (def = nettrain.dat)");
 printf("\n ***************************************************************");
 printf("\n");
 return 0;

}

void NRLib::end()
{
 cancnets();
 exit(0);

}

int NRLib::example1_help()
{
 printf("\n NETS POPULATION THAT IMIT EACH OTHER \n");
 printf("\n parameters: ");
 printf("\n    /tu=.. : total nets (def = 10)");
 printf("\n    /ua=.. : goods nets (don't imit another net)(def = 5)");
 printf("\n    /tl=.. : life cycles (def = 5000)");
 printf("\n    /iv=.. : printing interval (def = 50)");
 printf("\n ");
 return 0;

}

void NRLib::example2_help()
{
 printf("\n NET TRAINING WITH GENETIC ALGORITM \n");
 printf("\n parameters: ");
 printf("\n    /tu=.. : total nets (def = 100)");
 printf("\n    /tg=.. : total generations (def = 300)");
 printf("\n ");
}

int NRLib::example1_main(int argc, char *argv[])
{
 int i;
 long sss;
			     /* Modify defaults:                            */
			     /* tu = total nets                             */
			     /* ua = number of goods nets                   */
			     /* tl = life cycles                            */
			     /* iv = print interval                         */
 for (i=1;i<argc;i++)
 {
   if (strncmp(argv[i],"/tu=",4) == 0)  {tu=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/ua=",4) == 0)  {ua=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/tl=",4) == 0)  {tlife=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/iv=",4) == 0)  {intvis=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/h",2) == 0)    {example1_help();exit(0);}
 }
 param("fd","0");            /* No verbose                                  */
 time(&sss);srand((int)sss); /* Init random seed                            */ 
 example1_initialize();               /* Create nets                                 */
 example1_evolution();                /* Nets life                                   */
 end();
 return 0;

}

int NRLib::example1_initialize()
{
 int i,j,nu;
 LONG vn[MLIV+1];
 char vf[MLIV+1][10], va[MLIV+1][10];
			     /* Init array for <createallnets> function     */
   vn[0]=NL0;strcpy(vf[0],"f1");strcpy(va[0],"0");
   vn[1]=NL1;strcpy(vf[1],"f5");strcpy(va[1],"0");
   vn[2]=NL2;strcpy(vf[2],"f5");strcpy(va[2],"0");
			     /* Nets creation                               */
 createallnet(tu,MLIV,vn,vf,va);

			     /* Assign flag for model or imitator           */
			     /* and initialize output for first move        */
 for (nu=1;nu<=tu;nu++)
    {
     if (nu <= ua) teach[nu]=1;
     for (j=1;j<=NL0;j++) {io[nu].vinp[j]=rndab(0,1);io[nu].vout[j]=rndab(0,1);};
    }
 return 0;
}

int NRLib::example1_evolution()
{
 int cl,tvis;
 tvis=0;
   for (cl=1;cl<=tlife;cl++)
   {
     example1_netlife() ;
     tvis++;if (tvis >= intvis){  example1_errshow();tvis=0;  }
   }
 return 0;
}

int NRLib::example1_netlife()
{
   int cv,nu,ret,i,j;
   static FILE *fp;
			     /* Open trainer file for input values and      */
			     /* reference output  values                    */
   if (fp == NULLL)
   {
   fp = fopen(filetrain,"r");
   if (fp == NULLL) {printf("Can't open trainer file \r\n");exit(-1);}
   }
			     /* Input values to <vinp> array                */
     ret=fscanf(fp,"%f",&vinp[1]);
     if  (ret <= 0) {rewind(fp); ret=fscanf(fp,"%f",&vinp[1]);}
     for (i=2;i<=NL0;i++)
     {
       ret=fscanf(fp,"%f",&vinp[i]);
       if  (ret <= 0)
       {printf("Error on trainer file \r\n");exit(-1);}
     }
			     /* Reference output values to <verr> array     */
     for (i=1;i<=NL2;i++)
     {
       ret=fscanf(fp,"%f",&verr[i]);
       if  (ret <= 0)
       {printf("Error on trainer file \r\n");exit(-1);}
     }

			     /* Apply input to all nets and compute output */
 for (nu=1;nu<=tu;nu++) { example1_action(nu); }

			     /* Apply EBP to all nets                      */
 for (nu=1;nu<=tu;nu++) { ebptrain(nu);  }
 return 0;
}

int NRLib::rndab(int a, int b)
{
/* Integer random value between a and b        */
  float num;
  num= rand()&0x7FFF; num=num/MAX_RAND;
  return (floor)(num*(b-a)+a+.5);
}

void NRLib::ebptrain(int nu)
{
   int um,i,x;

			     /* If unit is an imitator , errors are         */
			     /* calculated by output of another unit (model)*/
			     /* randomly choosed                            */
			     /* Else errors remain the same what was        */
			     /* calculated by reference output              */
   if ( teach[nu] != 1 )
    {
     um=rndab(1,tu);
     for (i=1;i<=NL2;i++)
       {io[nu].verr[i]=io[nu].vout[i]-io[um].vout[i];}
    }
			     /* EBP rule                                    */
   learn(nu,io[nu].verr);
}

void NRLib::example1_errshow()
{
  int i;
			     /* Print <tu> average errors                   */
  for (i=1;i<=tu;i++)
  {
     printf("%7.4f ",err[i]/intvis);err[i]=0;
  }
  printf("\n");fflush(stdout);
}

void NRLib::example1_action(int nu)
{
   int i;
   float errq;
			     /* Applay input and output reference values    */
   for (i=1;i<=NL0;i++){io[nu].vinp[i]=vinp[i];}
   for (i=1;i<=NL2;i++){io[nu].verr[i]=verr[i];}
			     /* Compute output and evaluate error           */
   errq= compute(nu,io[nu].vinp,io[nu].vout,io[nu].verr);
			     /* averege q. error in return value            */
			     /* and  errors in <verr>                       */
   err[nu]=err[nu]+errq;
   return ;
}

int NRLib::example2_main(int argc, char *argv[])
{
 int i,ge,ta;
 long sss;
 tu=100;                           /* Total default nets                 */
 for (i=1;i<argc;i++)
 {
   if (strncmp(argv[i],"/tu=",4) == 0)  {tu=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/tg=",4) == 0)  {tgen=atoi(argv[i]+4);continue;}
   if (strncmp(argv[i],"/h",2) == 0)    {help();exit(0);}
 }
 if (tu > 500) tu=500;
 bu=tu/5;                           /* Range of selection(1/5 of population)*/
 param("fd","0");                   /* No verbose                           */
 time(&sss);srand((int)sss);        /* Init random seed                     */
 example2_initialize();                      /* Create nets                          */
 example2_evolution();                       /* Nets life and evolution              */
 end();
 return 0;

}

void NRLib::example2_initialize()
{
 int i,j,nu;
 LONG vn[MLIV+1];
 char vf[MLIV+1][10], va[MLIV+1][10];
			     /* Init array for <createallnets> function     */
   vn[0]=NL0;strcpy(vf[0],"f1");strcpy(va[0],"0");
   vn[1]=NL1;strcpy(vf[1],"f5");strcpy(va[1],"0");
   vn[2]=NL2;strcpy(vf[2],"f5");strcpy(va[2],"0");

 param("ra","-1");param("rb","1"); /* modify default random weigt generation*/
			     /* Nets creation                               */
 createallnet(tu,MLIV,vn,vf,va);

 for (nu=1;nu<=tu;nu++) Un[nu].nr=nu;    /* Initialize fitness list         */

}

void NRLib::example2_evolution()
{
 int ge;
   for (ge=1;ge<=tgen;ge++)      /* Loop for <tgen> generations             */
   {
     example2_netlife() ;                 /* Test all nets                           */
     example2_errshow(ge);                /* Display best performance (min. err)     */
     example2_procreate();                /* New generation (best selected)          */
   }
}

void NRLib::example2_netlife()
{
 int cv,nu,ret,i,j,stp=0;
 float errq,fout[NL2+1];
   static FILE *fp;
			     /* Open trainer file for input values and      */
			     /* reference output  values                    */
   if (fp == NULLL)
   {
   fp = fopen(filetrain,"r");
   if (fp == NULLL) {printf("Can't open trainer file \r\n");exit(-1);}
   }

 /********** Loop for all records of trainer file */
 /* each record = 1 life step */
 while(fscanf(fp,"%f",&vinp[1]) > 0)
 {
			     /* Input values to <vinp> array                */
     for (i=2;i<=NL0;i++)
     {
       ret=fscanf(fp,"%f",&vinp[i]);
       if  (ret <= 0)
       {printf("Error on trainer file \r\n");exit(-1);}
     }
			     /* Reference output values to <fout> array     */
     for (i=1;i<=NL2;i++)
     {
       ret=fscanf(fp,"%f",&fout[i]);
       if  (ret <= 0)
       {printf("Error on trainer file \r\n");exit(-1);}
     }

     stp++;                  /* one more life step */
			     /* Apply input to all nets and compute output */
     for (nu=1;nu<=tu;nu++)
     {
       for (i=1;i<=NL2;i++) verr[i]=fout[i]; /*because verr is modified by*/
       errq=compute(nu,vinp,vout,verr);       /*compute function           */
       err[nu]=err[nu]+errq;
     }
 }
 /********** end trainer file loop = end life */
 rewind(fp);
			     /* Average quadratic error                    */
 for (nu=1;nu<=tu;nu++)  err[nu]=err[nu]/stp;

			     /* Load fitness list                          */
 for (i=1;i<=tu;i++)  {j=Un[i].nr;Un[i].err=err[j];err[j]=0;}

			     /* Sort list (first best = lowest error)      */
 listsort(Un,tu);
}

void NRLib::example2_errshow(int ge)
{
   printf("Generation %4d    Lowest error %7.4f   Net %3d \n",
   ge,Un[1].err,Un[1].nr);
}

void NRLib::example2_procreate()
{
  int i,j,nu;
  LONG in,tc,jc,node;
  float weigt;
			      /* Clone the bests <bu> nets                */
  for (i=bu+1;i<=tu;i++) copynet(Un[rndab(1,bu)].nr,Un[i].nr);

  /* Now the <tu> nets are represented by only <bu> models*/

			      /* Apply a little randomic mutation         */
  for (i=bu+1;i<=tu;i++)
  {
   nu=Un[i].nr;
   for (in=1;in<=NL0+NL1+NL2;in++)
   {
    rnconn(nu,in,&tc);
    for (jc=0;jc<tc;jc++)              /* note that link <jc> start from 0 */
	{rconn(nu,in,jc,&weigt,&node);
	 weigt=weigt+frndab(-.1,.1);
	 wwgt(nu,in,jc,weigt); }
   }
  }
  /* Now we have a new generation */
}

float NRLib::frndab(float a, float b)
{
        /* Float random between a and b */
  float num;
  num= rand()&0x7FFF; num=num/MAX_RAND;
  return (num*(b-a)+a);
}

void NRLib::listsort(struct un vet[], int dim)
{
   /* Sort in ascendig order of vet[].err*/
  int c,i,appo2;
  float appo1;
  for (c=1; c<=dim; c++)
  {
    for (i=dim;i>c;i--)
    {
    if (vet[i].err < vet[i-1].err)
    { appo1=vet[i].err; vet[i].err=vet[i-1].err; vet[i-1].err=appo1;
      appo2=vet[i].nr; vet[i].nr=vet[i-1].nr; vet[i-1].nr=appo2;   }
    }
  }
}

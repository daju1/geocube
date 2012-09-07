/****************************************************************************/
/*                                                                          */
/*                     Example 2 of NRLIB32 library use                     */
/*                                                                          */
/*  This program is an example of genetic algoritm for xor net training.    */
/*  A population of nets are tested for xor behavior. Net fitness correspond*/
/*  to inverse of mean quadratic error.                                     */
/*  After all nets are tested , they are ordered according to their fitness */
/*  (first the best or the minimum mean quadratic error).                   */
/*                                                                          */
/*  This is the first generation ; best 1/5 of population procreate and     */
/*  replace other nets (total nets is constant) .                           */
/*  On new population we apply a little random mutations to weights.        */
/*                                                                          */
/*  In this example, application of genetic algoritm is not a classical     */
/*  version, because we don't use binary alphabet for genetic string and    */
/*  we don't apply  crossover operator (sexual procreation).                */
/*                                                                          */
/*  This algoritm is repeated for more generations , and you can see that   */
/*  the net behavior improve.                                               */
/*                                                                          */
/*  This algoritm is slower than EBP , but is useful in tasks that need more*/
/*  complicated fitness evaluation than exactly answers , like ecological   */
/*  tasks.                                                                  */
/*                                                                          */
/*  You must compile this program and link it with NRLIB32.OBJ file.        */
/*  Memory model is large.                                                  */
/*                                                                          */
/****************************************************************************/



# include "nrlib32.h"                 /* Library include                    */
# include <stdio.h>
# include <stdlib.h>
# include <math.h>


# define TU 500                       /* Max number of nets                 */

# define MLIV   2                     /* Max  layer                         */
# define NL0    2                     /* Layer 0 nodes                      */
# define NL1    4                     /* Layer 1 nodes                      */
# define NL2    1                     /* Layer 2 nodes                      */

# define NULLL  0L

struct un                             /* Fitness list                       */
{
 int   nr;                            /* Net number                         */
 float err;                           /* Mean quadratic error               */
}         un[TU+1];

				      /* Buffers for net inputs and output  */
float vinp[NL0+1];
float vout[NL2+1];
float verr[NL2+1];

float err[TU+1];                      /* Buffers for net quadratic errors   */

int tu=100;                           /* Total default nets                 */

int tgen=300;                         /* Total default generations          */

int bu;                      /* Buffer for range of best nets that procreate*/

char filetrain[]="nettrain.dat";   /* Training file                      */


float frndab(float a,float b);


main(int argc, char *argv[])
{
 int i,ge,ta;
 long sss;
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
 initialize();                      /* Create nets                          */
 evolution();                       /* Nets life and evolution              */
 end();
}


initialize()
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

 for (nu=1;nu<=tu;nu++) un[nu].nr=nu;    /* Initialize fitness list         */
}


evolution()
{
 int ge;
   for (ge=1;ge<=tgen;ge++)      /* Loop for <tgen> generations             */
   {
     netlife() ;                 /* Test all nets                           */
     errshow(ge);                /* Display best performance (min. err)     */
     procreate();                /* New generation (best selected)          */
   }
}


netlife()
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
 for (i=1;i<=tu;i++)  {j=un[i].nr;un[i].err=err[j];err[j]=0;}

			     /* Sort list (first best = lowest error)      */
 listsort(un,tu);
}

errshow(int ge)
{
   printf("Generation %4d    Lowest error %7.4f   Net %3d \n",
   ge,un[1].err,un[1].nr);
}


procreate()
{
  int i,j,nu;
  LONG in,tc,jc,node;
  float weigt;
			      /* Clone the bests <bu> nets                */
  for (i=bu+1;i<=tu;i++) copynet(un[rndab(1,bu)].nr,un[i].nr);

  /* Now the <tu> nets are represented by only <bu> models*/

			      /* Apply a little randomic mutation         */
  for (i=bu+1;i<=tu;i++)
  {
   nu=un[i].nr;
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

end()
{
 cancnets();
 exit(0);
}

help()
{
 printf("\n NET TRAINING WITH GENETIC ALGORITM \n");
 printf("\n parameters: ");
 printf("\n    /tu=.. : total nets (def = 100)");
 printf("\n    /tg=.. : total generations (def = 300)");
 printf("\n ");
}


rndab(int a,int b)           /* Integer random value between a and b        */
{
  float num;
  num= rand()&0x7FFF; num=num/MAX_RAND;
  return (floor)(num*(b-a)+a+.5);
}

float frndab(float a,float b)        /* Float random between a and b */
{
  float num;
  num= rand()&0x7FFF; num=num/MAX_RAND;
  return (num*(b-a)+a);
}

listsort(struct un vet[],int dim)    /* Sort in ascendig order of vet[].err*/
{
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


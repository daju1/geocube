/****************************************************************************/
/*                                                                          */
/*                     Example of NRLIB32 library use                       */
/*                                                                          */
/*  This program make a net population live ; each net has same input ,     */
/*  but it  correct her behaviour by imitating another net random selected. */
/*  Only first <ua> nets don't choose model ; they have correct trainer     */
/*  value from a file .                                                     */
/*                                                                          */
/*  We can see that knoledge diffuse on entire population.                  */
/*                                                                          */
/*  On command line we can choose a different value for any parameeter  or  */
/*  let defaults (see help routine).                                        */
/*                                                                          */
/*  You must compile this program and link it with NRLIB32.OBJ file.        */
/*  Memory model is large.                                                  */
/*                                                                          */
/****************************************************************************/

# include "nrlib32.h"       /* Library include                             */

# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define NULLL 0L

# define TU 500              /* Max number of nets                          */
			     /* Nets definition constants:                  */
# define MLIV   2            /* Last layer                                  */
# define NL0    2            /* Layer 0 nodes                               */
# define NL1    4            /* Layer 1 nodes                               */
# define NL2    1            /* layer 2 nodes                               */



float err[TU+1];             /* Buffers for nets average quadr. errors      */

int   teach[TU+1];           /* Flag for net imitator or not                */

struct io                    /* Buffers for nets input, output and errors   */
{
  float vinp[NL0+1];         
  float vout[NL2+1];
  float verr[NL2+1];
}         io[TU+1];

float vinp[NL0+1];           /* Buffer for input move from trainer file     */
float verr[NL2+1];           /* Buffer for reference output from train. file*/


int tu=10;                   /* Default nets number (units)                 */
int ua=5;                    /* Default goods nets (have treaning from file)*/
int intvis=50;               /* Print average errors default interval       */
int tlife=5000;              /* Life cycles                                 */

char filetrain[]="nettrain.dat";/* Trainer file name                        */


main(int argc, char *argv[])
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
   if (strncmp(argv[i],"/h",2) == 0)    {help();exit(0);}
 }
 param("fd","0");            /* No verbose                                  */
 time(&sss);srand((int)sss); /* Init random seed                            */ 
 initialize();               /* Create nets                                 */
 evolution();                /* Nets life                                   */
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
			     /* Nets creation                               */
 createallnet(tu,MLIV,vn,vf,va);

			     /* Assign flag for model or imitator           */
			     /* and initialize output for first move        */
 for (nu=1;nu<=tu;nu++)
    {
     if (nu <= ua) teach[nu]=1;
     for (j=1;j<=NL0;j++) {io[nu].vinp[j]=rndab(0,1);io[nu].vout[j]=rndab(0,1);};
    }
}


evolution()
{
 int cl,tvis;
 tvis=0;
   for (cl=1;cl<=tlife;cl++)
   {
     netlife() ;
     tvis++;if (tvis >= intvis){  errshow();tvis=0;  }
   }
}



netlife()
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
 for (nu=1;nu<=tu;nu++) { action(nu); }

			     /* Apply EBP to all nets                      */
 for (nu=1;nu<=tu;nu++) { ebptrain(nu);  }

}

action(int nu)
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

ebptrain(int nu)
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


errshow()
{
  int i;
			     /* Print <tu> average errors                   */
  for (i=1;i<=tu;i++)
  {
     printf("%7.4f ",err[i]/intvis);err[i]=0;
  }
  printf("\n");fflush(stdout);
}


end()
{
 cancnets();
 exit(0);
}

help() 
{
 printf("\n NETS POPULATION THAT IMIT EACH OTHER \n");
 printf("\n parameters: ");
 printf("\n    /tu=.. : total nets (def = 10)");
 printf("\n    /ua=.. : goods nets (don't imit another net)(def = 5)");
 printf("\n    /tl=.. : life cycles (def = 5000)");
 printf("\n    /iv=.. : printing interval (def = 50)");
 printf("\n ");
}

			     /* Integer random value between a and b        */
rndab(int a,int b)
{
  float num;
  num= rand()&0x7FFF; num=num/MAX_RAND;
  return (floor)(num*(b-a)+a+.5);
}


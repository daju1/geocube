/*****************************************************************************/
/*                                                                           */
/*             INTERACTIVE PROGRAM FOR FORWARD EBP NETS MANAGEMENT           */
/*                                                                           */
/*****************************************************************************/

# include "nrlib32.h"
# include <stdio.h>
# include <stdlib.h>

char  fileinp[50]="nnetsinp.dat";
char  fileout[50]="nnetsout.dat";
char  fileese[50]="nettrain.dat";

int   nep=1;
float minerr=0;
float epsl=0.8;
float alfa=0.5;
float randa=-0.4;
float randb=0.4;
int   flgbias=0;
int   numr=1;
int   treti=0;

int   menu();
int   creazione();
int   modpar();
int   help();

# define NULLO 0

/*************************** MAIN ******************************************/


main(int argc, char *argv[])
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
   if (strncmp(argv[i],"/h",2) == 0)    {help();fine();}
   if (strncmp(argv[i],"?",1)  == 0)    {help();fine();}
   if (strncmp(argv[i],"/?",2) == 0)    {help();fine();}
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
 return;
}

menu()
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

creazione()
{
 int nliv,i,ret,cnr,nr,maxliv,strmaxliv;
 int  vliv[1000];
 LONG vn[100];
 char vf[100][10];
 char va[100][10];
 char ch;

 rete:
 printf("\x1B[2J");
 printf("\n            DEFINITION OF ALL NETS STRUCTURE     \n\n\n\n");
 printf("\n Total nets  (max   1000) : ");
 scanf("%d",&treti);fflush(stdin);
 if (treti > 1000) goto rete;
 printf("\n");
 printf("\n All equals nets   ? (y/n):",i);
 ret=scanf("%c",&ch);fflush(stdin);if (ret<1) return;
 cnr=treti;if (ch != 'n') cnr=1;
 if (cnr == 1)
 { printf("\n Last net layer     (0 -- 99) : "); }
 else
 { printf("\n Max last net layer (0 -- 99) : "); }
 scanf("%d",&nliv);fflush(stdin);
 if (nliv > 99) goto rete;
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
   ret=scanf("%I",&vn[i]);fflush(stdin);if (ret<1) return;
   printf("\n f1 : unitary function ");
   printf("\n f3 : sigmoid positiv and negativ (f13 calculated)");
   printf("\n f5 : sigmoid only positive (f15 calculated)");
   printf("\n Activ-function of nodes of layer %3d (f1 - f15):",i);
   ret=scanf("%10s",vf[i]);fflush(stdin);if (ret<1) return;
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
 return;
}


modpar()
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

help()
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
 return;
}

fine()
{
 cancnets();
 exit(0);
}

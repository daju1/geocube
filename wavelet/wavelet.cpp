// wavelet.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cparser.h"
#include "../array/src/vdouble.h"
#include "readfile.h"
static char	input_fn[128] = "";
static char	output_coef_fn[128] = "wav_coef.txt";
static char	output_recon_fn[128] = "wav_reconstr.txt";
static int 
		idelimID = 0,
		odelimID = 0,
		ntcol = -1,
		ncol = -1,
		wf,
		wOrder,
		wOrderBiorthogonalDecomposition,
		maxLevel;

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

int error(int errno)
{
	if (errno > 0)
		printf( "nnerror %d: %s\n", errno, errtbl[errno-1].errmsg );
	else
		printf( "nnerror %d\n", errno);
	exit (errno);
}

int	usage( )
{
	printf( "%s %s - by %s\n", PROGNAME, VERSION, AUTHOR );
	printf( "Copyright (c) 2007 All Rights Reserved. %s\n\n", DATE );
	printf( "Description: discrete waveled decomposition and reconstruction\n");
	printf( "Usage: %s @file -i=# -ncol=# {ocoef=#} {-orecon=#} -idelimID=#\n", PROGNAME);
	printf( "-wf=# -worder=# {-worder2=#} -maxlevel=#\n" );
	printf( "Example: " );
	printf( "creating wavelet reconstruction file with coiflet order 3 maxlevel 5\n");
	printf( "%s -i=infile.txt -orecon=recon.txt -wf=3 -worder=3 -maxlevel=5", PROGNAME );
	printf( "Where:\n" );
	printf( "-i=         filename of input file\n" );
	printf( "-ncol=      number of colomn to use on wavelet handling\n" );
	printf( "-ntcol=     number of colomn which is X or TIME coordinate\n" );
	printf( "            first colomn have number=0\n" );
	printf( "-ocoef=     filename of output file with wavelet coefficients\n" );
	printf( "-orecon=    filename of output file with wavelet reconstruction\n" );
	printf( "-idelimID=  identificator of delimiter in the input file\n" );
	printf( "-odelimID=  identificator of delimiter in the output file\n" );
	printf( "            0->tabulation 1->space 2->\',\' 3->\';\'\n" );
	printf( "-wf=        wavelet filter type\n" );
	printf( "-worder=    wavelet filter order\n" );
	printf( "-worder2=   wavelet filter second order (only for biortogonal filter)\n" );
	printf( "-maxlevel=  maximal level of discrete wavelet decomposition\n\n" );
	printf( " Suppotrted wavelet types are:\n");
	printf( " wf         wavelet name           supported orders:\n");
	printf( " 0          HAAR                       1\n");
	printf( " 1          DAUBECHIES               1 - 10\n");
	printf( " 2          SYMLETS                  1 - 8\n");
	printf( " 3          COIFLETS                 1 - 5\n");
	printf( " 4          BIORTOGONAL  1(1-3), 2(1-4), 3(1-5), 4, 5, 6\n");
	printf( " 5          MY_BIORTOGONAL           1 - 3\n");
	printf( " 6          BIORTOGONAL_NONSTANDART  1 - 2\n");
	printf( " 7          DISCRETE_MEYER             1\n");
	exit (0);
}

int	parse( )
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
			case CMD_INPUT:
				strcpy( input_fn, rest );
printf("input file = %s\n", input_fn);
				break;
			case CMD_OUTPUT_COEF:
				strcpy( output_coef_fn, rest );
printf("output_coef file = %s\n", output_coef_fn);
				break;
			case CMD_OUTPUT_RECON:
				strcpy( output_recon_fn, rest );
printf("output_recon file = %s\n", output_recon_fn);
				break;
			case CMD_WAV_FILTER:
				wf = resti;
printf("wf = %d\n", wf);
				break;
			case CMD_WAV_ORDER:
				wOrder = resti;
printf("wOrder = %d\n", wOrder);
			case CMD_WAV_ORDER2:
				wOrderBiorthogonalDecomposition = resti;
printf("wOrderBiorthogonalDecomposition = %d\n", wOrderBiorthogonalDecomposition);
				break;
			case CMD_MAXLEVEL:
				maxLevel= resti;
printf("maxLevel = %d\n", maxLevel);
				break;
			case CMD_NCOL:
				ncol = resti;
printf("ncol = %d\n", ncol);
				break;
			case CMD_NTCOL:
				ntcol = resti;
printf("ntcol = %d\n", ntcol);
				break;
			case CMD_IDELIMID:
				idelimID = resti;
printf("idelimID = %d\n", idelimID);
				break;
			case CMD_ODELIMID:
				odelimID = resti;
printf("odelimID = %d\n", odelimID);
				break;
			case CMD_TOLER:
//				TOLER = atof( rest );
				break;
			case CMD_REPORT:
//				report = resti;
				break;
			case CMD_TIMER:
//				timer = 1;
				break;
			case CMD_TDUMP:
//				tdump = restl;
				break;
			case CMD_WPOS:
//				UB = atof(rest);
				break;
			case CMD_WNEG:
//				LB = atof(rest);
				break;
			case CMD_COMMENT:
				break;
			case CMD_NULL:
				printf( "%s: unknown command [%s]\n", PROGNAME, rest );
				exit (2);
				break;
			}
		}
/*		if (hiddencnt < totalhidden)
			{
			error( NN2MANYHIDDEN );
			}
*/
	return 0;
}
void print_param()
{
	printf("\n");
	printf("input file = %s\n", input_fn);
	printf("output_coef file = %s\n", output_coef_fn);
	printf("output_recon file = %s\n", output_recon_fn);
	printf("wf = %d\n", wf);
	printf("wOrder = %d\n", wOrder);
	printf("wOrderBiorthogonalDecomposition = %d\n", wOrderBiorthogonalDecomposition);
	printf("maxLevel = %d\n", maxLevel);
	printf("ncol = %d\n", ncol);
	printf("ntcol = %d\n", ntcol);
	printf("idelimID = %d\n", idelimID);
	printf("odelimID = %d\n", odelimID);
	fflush(stdout);

}

int main(int argc, char* argv[])
{
	printf("main\n");
	fflush(stdout);
	if (argc < 2)
		{
		usage();
		}
	else
		{
		cmdinit( argc, argv );
		parse();
		}

	print_param();

	vdouble vt;
	Vector<vdouble> vv;
	vdouble *input_vector, *input_t;

	input_vector = NULL;
	input_t      = NULL;


	if (ReadInputFile(input_fn, vv, GetDelimiterFromID(idelimID)) == 0)
	{
		if (ncol > 0 && ncol < vv.Size())
			input_vector = &vv[ncol];
		if (ntcol > 0 && ntcol < vv.Size())
			input_t = &vv[ntcol];

		
		Vector<Vector<int> > 
			vtau_s_ind, 
			vtau_d_ind, 
			vtau_S_ind, 
			vtau_F_ind;

		Vector<vdouble> vtau_s;
		Vector<vdouble> vs; // контейнер дл€ хранени€ s- коэффициентов на каждом уровне декомпозиции
		Vector<vdouble> vtau_d;
		Vector<vdouble> vd; // контейнер дл€ хранени€ d- коэффициентов на каждом уровне декомпозиции
		Vector<vdouble> vtau_S;
		Vector<vdouble> vSlow; // контейнер дл€ хранени€ низкочастотной составл€ющей сигнала на каждом уровне разложени€
		Vector<vdouble> vtau_F;
		Vector<vdouble> vFast; // контейнер дл€ хранени€ высокочастотных составл€ющих сигнала, отделЄнных на каждом уровне разложени€

		if(input_vector && input_vector->WaveletDecomposition(input_t,
			wf, // флаг вейвлета
		  wOrder, // пор€док вейвлета
		  wOrderBiorthogonalDecomposition,
		  maxLevel, // максимальный уровенть разложени€
		  vtau_s_ind,
		  vtau_s,
		  vs, // контейнер дл€ хранени€ s- коэффициентов на каждом уровне декомпозиции
		  vtau_d_ind, 
		  vtau_d,
		  vd, // контейнер дл€ хранени€ d- коэффициентов на каждом уровне декомпозиции
		  vtau_S_ind,
		  vtau_S,
		  vSlow, // контейнер дл€ хранени€ низкочастотной составл€ющей сигнала на каждом уровне разложени€
		  vtau_F_ind,
		  vtau_F,
		  vFast)) // контейнер дл€ хранени€ высокочастотных составл€ющих сигнала, отделЄнных на каждом уровне разложени€
		{
			printf("WaveletDecomposition was calculated\n","",2);
			Vector <int> rS_ind, rF_ind;
			rS_ind.resize(vtau_S_ind.Size());
			rF_ind.resize(vtau_F_ind.Size());

			int odelim = GetDelimiterFromID(odelimID);
			FILE *stream;

			// open the file
			if ((stream = fopen(output_recon_fn,"wt")) == NULL)
			{
				MessageBox(0, "Cannot open output file.\n", "Import", 
					MB_OK | MB_ICONINFORMATION);
				return -1;
			}
			// инициализаци€ массива текущих индексов
			if (input_vector && input_vector->Length() > 0)
			{
				for (int c = 0; c < vtau_S_ind.Size(); c++)
				{
					if (vtau_S_ind[c].Size() > 0)
						rS_ind[c] = 0;
					else
						rS_ind[c] = -1;
				}
				for (int c = 0; c < vtau_F_ind.Size(); c++)
				{
					if (vtau_F_ind[c].Size() > 0)
						rF_ind[c] = 0;
					else
						rF_ind[c] = -1;
				}
			}
#define TEST_WAV 1
#if TEST_WAV
			Vector<int> indexesS,indexesF;
			indexesS.resize(vtau_S_ind.Size());
			indexesF.resize(vtau_F_ind.Size());
#endif /*TEST_WAV*/
			for (int row = 0; row < input_vector->Length(); row++)
			{
				for (int c1 = 0; c1 < vv.Size(); c1++)
				{
					fprintf(stream, "%f%c", vv[c1][row], odelim);
				}
				
				for (int c2 = 0; c2 < vtau_S_ind.Size(); c2++)
				{
					int r = rS_ind[c2];
					int ind;
					if (r > -1 && r < vtau_S_ind[c2].Size() )
					{ 
						ind = vtau_S_ind[c2][r];
						if (ind == row  && ind < vSlow[c2].Length())
						{
#if TEST_WAV
							indexesS[c2]=ind;
#endif /*TEST_WAV*/
							fprintf(stream, "%d%c", ind, odelim);
							fprintf(stream, "%f%c", vSlow[c2][ind], odelim);
							rS_ind[c2] = r+1;
						}
						else
						{
#if TEST_WAV
							indexesS[c2]=-1;
#endif /*TEST_WAV*/
							fprintf(stream, "%c", odelim);
						}
					}
					else
					{
#if TEST_WAV
						indexesS[c2]=-1;
#endif /*TEST_WAV*/
						fprintf(stream, "%c", odelim);
					}
				}
				for (int c3 = 0; c3 < vtau_F_ind.Size(); c3++)
				{
					int r = rF_ind[c3];
					int ind;
					if (r > -1 && r < vtau_F_ind[c3].Size() )
					{ 
						ind = vtau_F_ind[c3][r];
						if (ind == row  && ind < vFast[c3].Length())
						{
#if TEST_WAV
							indexesF[c3]=ind;
#endif /*TEST_WAV*/
							fprintf(stream, "%f%c", vFast[c3][ind], odelim);
							rF_ind[c3] = r+1;
						}
						else
						{
#if TEST_WAV
							indexesF[c3]=-1;
#endif /*TEST_WAV*/
							fprintf(stream, "%c", odelim);
						}
					}
					else
					{
#if TEST_WAV
						indexesF[c3]=-1;
#endif /*TEST_WAV*/
						fprintf(stream, "%c", odelim);
					}
				}
#if TEST_WAV
				double sumFast = 0.0;
				for (int c = indexesF.Size()-1; c >=0 ; c--)
				{
					if (indexesF[c] > -1)
					{
						sumFast += vFast[c][indexesF[c]];
					}
				}
				fprintf(stream, "%f%c", sumFast, odelim);
				int c = indexesF.Size()-1;
				if (indexesS[c] > -1)
				{
					sumFast += vSlow[c][indexesS[c]];
				}
				fprintf(stream, "%f%c", sumFast, odelim);
#endif /*TEST_WAV*/

				fprintf(stream, "\n");
			}
			fclose(stream);

		}
		else
		{
			printf("WaveletDecomposition was not calculated\ninput_vector = %x ncol = %d\n", input_vector, ncol);
		}
	}
	else
	{
		printf("input file %s was not read", input_fn);
	}

	return 0;
}


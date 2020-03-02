#include "StdAfx.h"
#include "wav.h"
#include "Vdouble.h"


void WaveletFilters(int wf, // флаг типа вейвлетов
	int order, // порядоак вейвлета
	int orderBiorthogonalDecomposition,
	int& nd1, int& nd2, vdouble& d_h,
	int& ngd1, int& ngd2, vdouble& d_g,
	int& nr1, int& nr2, vdouble& r_h, 
	int& ngr1, int& ngr2,vdouble& r_g,
	int& n00, double& m00)
{
	/*
	menuauxiliar1=['wx=menu(' '''' 'auxiliar filter order:' ''''];
	for i=1:35
	menuauxiliar1=[menuauxiliar1 ',' '''' int2str(10+i) ''''];
	end;
	menuauxiliar1=[menuauxiliar1 ');'];
	menuauxiliar2=[menuauxiliar1(1:32) ',' '''' '9' '''' ',' '''' '10' ''''  menuauxiliar1(33:end)];
   */

	n00=0; m00=0;

	if (wf<5) 
	{
		nd1=0; nr1=nd1; ngr1=nr1; ngd1=nd1; 
	}

	if (wf==WF_HAAR)
	{
		m00=0.5;   
		nd2=1; nr2=1; ngd2=nr2; ngr2=nd2;
		double dh[]={0.5, 0.5}; 
		d_h = vdouble(dh,2);
		r_h = d_h;
		double dg[]={0.5, -0.5}; 
		d_g = vdouble(dg,2);
		r_g = d_g;
	}
	if (wf==WF_DAUBECHIES)
	{
		// daubechies order :
		//  '1','2','3','4','5','6','7','8',
		//	'9','10','11--45'  
		nd2=2*order-1; nr2=nd2; ngd2=nr2; ngr2=nd2;
	 
		switch (order)
		{
		case 1:
			{
				m00=0.5;
				double dh[] = {0.5, 0.5};
				d_h = vdouble(dh,2);
			}
			break;
		case 2:
			{
				double dh[] =
				{
					0.34150635094622,   0.59150635094587,   0.15849364905378,  -0.09150635094587
				};
				d_h = vdouble(dh, 4);

				d_h[0] = 1.0 / 4.0 / (2.0) * (1.0 + sqrt(3.0));
				d_h[1] = 1.0 / 4.0 / (2.0) * (3.0 + sqrt(3.0));
				d_h[2] = 1.0 / 4.0 / (2.0) * (3.0 - sqrt(3.0));
				d_h[3] = 1.0 / 4.0 / (2.0) * (1.0 - sqrt(3.0));
				n00=1; m00=0.70;
			}
			break;
		case 3:
			{
				double dh[] =
				{
					0.23523360389270,   0.57055845791731,   0.32518250026371,  -0.09546720778426, 
					-0.06041610415535,   0.02490874986589
				};
				d_h = vdouble(dh,6);
				n00=1; m00=0.65;
			}
			break;
		case 4:
			{
				double dh[] =
				{
					0.16290171402562,   0.50547285754565,   0.44610006912319,  -0.01978751311791,
					-0.13225358368437,   0.02180815023739,   0.02325180053556,  -0.00749349466513
				};
				d_h = vdouble(dh,8);
				n00=1; m00=0.74;
			}
			break;
		case 5:
			{
				double dh[] =
				{
					0.11320949129173,   0.42697177135271,   0.51216347213016,   0.09788348067375,
					-0.17132835769133,  -0.02280056594205,   0.05485132932108,  -0.00441340005433,
					-0.00889593505093,   0.00235871396920
				};
				n00=1; m00=0.8;
				d_h = vdouble(dh,10);
			}
			break;
		case 6:
			{
				double dh[] =
				{
					0.07887121600143,   0.34975190703757,   0.53113187994121,   0.22291566146505,
					-0.15999329944587,  -0.09175903203003,   0.06894404648720,   0.01946160485396,
					-0.02233187416548,   0.00039162557603,   0.00337803118151,  -0.00076176690258
				};
				n00=2; m00=1.1;
				d_h = vdouble(dh,12);
			}
			break;
		case 7:
			{
				double dh[] =
				{
					0.05504971537285,   0.28039564181304,   0.51557424581833,   0.33218624110566,
					-0.10175691123173,  -0.15841750564054,   0.05042323250485,   0.05700172257986,
					-0.02689122629486,  -0.01171997078235,   0.00887489618962,   0.00030375749776,
					-0.00127395235906,  0.00025011342658
				};
				n00=2; m00=1.1;
				d_h = vdouble(dh,14);
			}
			break;
		case 8:
			{
				double dh[] =
				{
					0.03847781105406,   0.22123362357624,   0.47774307521438,   0.41390826621166,
					-0.01119286766665,  -0.20082931639111,   0.00033409704628,   0.09103817842345,
					-0.01228195052300,  -0.03117510332533,   0.00988607964808,   0.00618442240954,
					-0.00344385962813,  -0.00027700227421,   0.00047761485533,  -0.00008306863060
				};
				n00=2; m00=1.2;
				d_h = vdouble(dh,16);
			}
			break;
		case 9:
			{
				double dh[] =
				{
					0.02692517479416,   0.17241715192471,   0.42767453217028,   0.46477285717278,
					0.09418477475112,  -0.20737588089628,  -0.06847677451090,   0.10503417113714,
					0.02172633772990,  -0.04782363205882,   0.00017744640673,   0.01581208292614,
					-0.00333981011324,  -0.00302748028715,   0.00130648364018,   0.00016290733601,
					-0.00017816487955,   0.00002782275679
				};
				n00=2; m00=1.15;
				d_h = vdouble(dh,18);
			}
			break;
		case 10:
			{
				double dh[] =
				{
					0.01885857879640,   0.13306109139687,   0.37278753574266,   0.48681405536610,
					0.19881887088440,  -0.17666810089647,  -0.13855493935993,   0.09006372426666,
					0.06580149355070,  -0.05048328559801,  -0.02082962404385,   0.02348490704841,
					0.00255021848393,  -0.00758950116768,   0.00098666268244,   0.00140884329496,
					-0.00048497391996,  -0.00008235450295,   0.00006617718320,  -0.00000937920789
				};
				n00=3; m00=1.2;
				d_h = vdouble(dh,20);
			}
			break;
		default:
			{
				/*
				//eval(menuauxiliar1); wx=wx+10; // порядок вейвлета
				dh=dbaux(wx);
				ch=cumsum(dh);ch=ch(1:end-1);
				ch1=fliplr(cumsum(fliplr(dh)));ch1=ch1(1:end-1);
				n00=max(find(ch<=ch1))+1;
				%n00=find(abs(dh)==max(abs(dh)));
				m00=0.5;
				nd2=2*wx-1; nr2=nd2; ngd2=nr2; ngr2=nd2;
				end;
				*/
			}
		}
//		d_h *= sqrt(2.0);
		r_h = d_h;
		vdouble ldg = dsequence((double)nd1, 1.0, (double)nd2);
		vdouble sigdg=pow(-1.0,ldg);
		d_g=sigdg*fliplr(d_h);
		r_g = d_g;
	}

	if (wf==WF_SYMLETS)
	{
		// 'symlets order','1','2','3','4','5','6','7','8','9--45'); 
		nd2=2*order-1; nr2=nd2; ngd2=nr2; ngr2=nd2;   
		switch (order)
		{
		case 1:
			{
				double dh[] =
				{
					0.50000000000000,   0.50000000000000
				};
				n00=1;// ???
				m00=0.5;
				d_h = vdouble(dh,2);
			}
			break;
		case 2:
			{
				double dh[] =
				{
					0.34150635094622,   0.59150635094587,   0.15849364905378,  -0.09150635094587
				};
				n00=1; m00=0.70;
				d_h = vdouble(dh,4);
			}
			break;
		case 3:
			{
				double dh[] =
				{
					0.23523360389270,   0.57055845791731,   0.32518250026371,  -0.09546720778426,
					-0.06041610415535,   0.02490874986589 
				};
				n00=1;m00=0.65;
				d_h = vdouble(dh,6);
			}
			break;
		case 4:
			{
				double dh[] =
				{
					0.02278517294800,  -0.00891235072085,  -0.07015881208950,   0.21061726710200,
					0.56832912170500,   0.35186953432800,  -0.02095548256255,  -0.05357445070900
				};
				n00=2; m00=0.8;
				d_h = vdouble(dh,8);
			}
			break;
		case 5:
			{
				double dh[] =
				{
					0.01381607647893,  -0.01492124993438,  -0.12397568130675,   0.01173946156807,
					0.44829082419092,   0.51152648344605,   0.14099534842729,  -0.02767209305836,
					0.02087343221079,   0.01932739797744
				};
				n00=4; m00=0.9; 
				d_h = vdouble(dh,10);
			}
			break;
		case 6:
			{
				double dh[] =
				{
					-0.00551593375469,   0.00124996104639,   0.03162528132994,  -0.01489187564922,
					-0.05136248493090,   0.23895218566605,   0.55694639196396,   0.34722898647835,
					-0.03416156079324,  -0.08343160770584,   0.00246830618592,   0.01089235016328
				};
				n00=5; m00=0.9;
				d_h = vdouble(dh,12);
			}
			break;
		case 7:
			{
				double dh[] =
				{
					0.00726069738101,   0.00283567134288,  -0.07623193594814,  -0.09902835340368,
					0.20409196986287,   0.54289135490599,   0.37908130098269,   0.01233282974432,
					-0.03503914561106,   0.04800738396784,   0.02157772629104,  -0.00893521582557,
					-0.00074061295730,   0.00189632926710
				};
				n00=5; m00=1.0;
				d_h = vdouble(dh,14);
			}
			break;
		case 8:
			{
				double dh[] =
				{
					0.00133639669640,  -0.00021419715012,  -0.01057284326418,   0.00269319437688,
					0.03474523295559,  -0.01924676063167,  -0.03673125438038,   0.25769933518654,
					0.54955331526901,   0.34037267359439,  -0.04332680770282,  -0.10132432764282,
					0.00537930587524,   0.02241181152181,  -0.00038334544811,  -0.00239172925575
				};
				n00=5; m00=1.15;
				d_h = vdouble(dh,16);
			}
			break;
		default:
			{
				/*
				otherwise
				eval(menuauxiliar2); wx=wx+8;   
				dh=symaux(wx);
				ch=cumsum(dh);ch=ch(1:end-1);
				ch1=fliplr(cumsum(fliplr(dh)));ch1=ch1(1:end-1);
				n00=max(find(ch<=ch1))+1;
				m00=0.5;
				nd2=2*wx-1; nr2=nd2; ngd2=nr2; ngr2=nd2;
				end;*/
			}
		}
//		d_h *= sqrt(2.0);
		r_h = d_h;
		vdouble ldg = dsequence((double)nd1, 1.0, (double)nd2);
		vdouble sigdg=pow(-1.0,ldg);
		d_g=sigdg*fliplr(d_h);
		r_g = d_g;
	}
	if (wf == WF_COIFLETS)
	{
		// 'coiflets order','1','2','3','4','5'
		nd2=6*order-1; nr2=nd2; ngd2=nr2; ngr2=nd2;
		switch (order)
		{
		case 1:
			{
				double dh[] =
				{
					-0.05142972847100,   0.23892972847100,   0.60285945694200,   0.27214054305800,
					-0.05142972847100,  -0.01107027152900 
				};
				n00=2; m00=0.9;
				d_h = vdouble(dh,6);
			}
			break;
		case 2:
			{
				double dh[] =
				{
					0.01158759673900,  -0.02932013798000,  -0.04763959031000,   0.27302104653500,
					0.57468239385700,   0.29486719369600,  -0.05408560709200,  -0.04202648046100,
					0.01674441016300,   0.00396788361300,  -0.00128920335600,  -0.00050950539900
				};
				n00=4;m00=0.8;
				d_h = vdouble(dh,12);
			}
			break;
		case 3:
			{
				double dh[] =
				{
					-0.00268241867100,   0.00550312670900,   0.01658356047900,  -0.04650776447900,
					-0.04322076356000,   0.28650333527400,   0.56128525687000,   0.30298357177300,
					-0.05077014075500,  -0.05819625076200,   0.02443409432100,   0.01122924096200,
					-0.00636960101100,  -0.00182045891600,   0.00079020510100,   0.00032966517400,
					-0.00005019277500,  -0.00002446573400
				};
				n00=5; m00=0.9;
				d_h = vdouble(dh,18);
			}
			break;
		case 4:
			{
				double dh[] =
				{
					0.00063096104600,  -0.00115222485200,  -0.00519452402600,   0.01136245924400,
					0.01886723537800,  -0.05746423442900,  -0.03965264851700,   0.29366739089500,
					0.55312645256200,   0.30715732619800,  -0.04711273886500,  -0.06803812705100,
					0.02781364015300,   0.01773583743800,  -0.01075631851700,  -0.00400101288600,
					0.00265266594600,   0.00089559452900,  -0.00041650057100,  -0.00018382976900,
					0.00004408035400,   0.00002208285700,  -0.00000230494200,  -0.00000126217500
				};
				n00=7; m00=0.7;
				d_h = vdouble(dh,24);
			}
			break;
		case 5:
			{
				double dh[] =
				{
					-0.00014996380000,   0.00025356120000,   0.00154024570000,  -0.00294111080000,
					-0.00716378190000,   0.01655206640000,   0.01991780430000,  -0.06499726280000,
					-0.03680007360000,   0.29809232350000,   0.54750542940000,   0.30970684900000,
					-0.04386605080000,  -0.07465223890000,   0.02919587950000,   0.02311077700000,
					-0.01397368790000,  -0.00648009000000,   0.00478300140000,   0.00172065470000,
					-0.00117582220000,  -0.00045122700000,   0.00021372980000,   0.00009937760000,
					-0.00002923210000,  -0.00001507200000,   0.00000264080000,   0.00000145930000,
					-0.00000011840000,  -0.00000006730000
				};
				n00=9; m00=0.8;
				d_h = vdouble(dh,30);
			}
		}
//		d_h *= sqrt(2.0);
		r_h = d_h;
		vdouble ldg = dsequence((double)nd1, 1.0, (double)nd2);
		vdouble sigdg=pow(-1.0,ldg);
		d_g=sigdg*fliplr(d_h);
		r_g = d_g;
	}
	if (wf == WF_BIORTOGONAL)
	{
		  //rf=menu('reconstruction filter order','1 at (1 3 5)',....
		  //'2 at (2 4 6 8)','3 at (1 3 5 7 9)','4 at 4','5 at 5',...
		  //'6 at 8');
		switch (order)
		{
		case 1 :
			{
				m00=0.5;nr1=0; nr2=1; 
				double rh[] = {0.5, 0.5};
				r_h = vdouble(rh,2);
				//df=menu('decomposition filter order','1','3','5');
				nd1=2*(orderBiorthogonalDecomposition-1);
				nd2=2*orderBiorthogonalDecomposition-1; 
				ngd1=nr1;ngd2=nr2;
				ngr1=nd1;ngr2=nd2;
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						d_h=r_h;
					}
					break;
				case 2:
					{
						m00=0.5;
						double dh[] = {-1./16., 1./16., 1./2., 1./2., 1./16., -1./16.};
						d_h = vdouble(dh,6);
					}
					break;
				case 3:
					{
						m00=0.5;
						//dh=[3/256 -3/256 -11/128 11/128 1/2];
						//dh= [dh fliplr(dh)];
						double dh[] = {3./256., -3./256., -11./128., 11./128., 1./2.,
							1./2., 11./128., -11./128., -3./256., 3./256.};
						d_h = vdouble(dh,10);
					}
					break;
				}
				//ldg=-nr1:nr2; lrg=-nd1:nd2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=sigdg.*rh; rg=sigrg.*dh;
				vdouble ldg = dsequence((double)(-nr1), 1.0, (double)nr2);
				vdouble lrg = dsequence((double)(-nd1), 1.0, (double)nd2);
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=sigdg*r_h; r_g=sigrg*d_h;
			}
			break;
		case 2 :
			{
				m00=0.5;
				nr1=1; nr2=1; 
				double rh[] = {0.25, 0.5, 0.25};
				r_h = vdouble(rh,3);
				//df=menu('decomposition filter order','2','4','6','8');
				nd1=2*orderBiorthogonalDecomposition; 
				nd2=2*orderBiorthogonalDecomposition; 
				ngd1=nr1-1; ngd2=nr2+1; ngr1=nd1-1; ngr2=nd2+1;
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						double dh[] = {-1./8., 1./4., 3./4., 1./4., -1./8.};
						d_h = vdouble(dh,5);
					}
					break;
				case 2:
					{
						//dh=[3/128 -3/64 -1/8 19/64];
						//dh= [dh 45/64 fliplr(dh)];
						double dh[] = {3./128., -3./64., -1./8., 19./64.,
							45./64., 
							19./64., -1./8., -3./64., 3./128.};
						d_h = vdouble(dh,9);
					}
					break;
				case 3:
					{
						//dh=[-5/1024 5/512 17/512 -39/512 -123/1024 81/256];
						//dh = [dh 175/256 fliplr(dh)];
						double dh [] = {
							-5./1024., 5./512., 17./512., -39./512., -123./1024., 81./256.,
								175./256.,
								81./256., -123./1024., -39./512., 17./512., 5./512., -5./1024.};
						d_h = vdouble(dh,13);
					}
					break;
				case 4:
					{
						//dh=[35 -70 -300 670 1228 -3126 -3796 10718];
						//dh = [dh 22050 fliplr(dh)]/(2^15);
						double dh[] = {35., -70., -300., 670., 1228., -3126., -3796., 10718.,
							22050.,
							10718., -3796., -3126., 1228., 670., -300., -70., 35.};
						double pw = pow(2.0, 15.0);
						d_h = vdouble(dh, 17) / pw;
					}
					break;
				}
				//ldg=(1-nr1):(nr2+1); lrg=(1-nd1):(nd2+1); 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)(1-nr1), 1.0, (double)(1+nr2));
				vdouble lrg = dsequence((double)(1-nd1), 1.0, (double)(1+nd2));
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		case 3 :
			{
				m00=0.5;
				nr1=1; nr2=2;
				//rh=[1 3 3 1]/8;
				double rh[] = {1., 3., 3., 1.};
				r_h = vdouble(rh,4);
				r_h /= 8.;
				//df=menu('decomposition filter order','1','3','5','7','9');
				nd1=2*orderBiorthogonalDecomposition-1; nd2=2*orderBiorthogonalDecomposition; ngd1=nr1; ngd2=nr2; ngr1=nd1; ngr2=nd2;
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						//dh=[-1 3 3 -1]/4;
						double dh[] = {-1., 3., 3., -1.};
						d_h = vdouble(dh,4);
						d_h /= 4.;
					}
					break;
				case 2:
					{
						//dh=[3 -9 -7 45]/64;
						//dh=[dh fliplr(dh)];
						double dh[] = {3., -9., -7., 45., 45., -7., -9., 3.};
						d_h = vdouble(dh,8);
						d_h /= 64.;
					}
					break;
				case 3:
					{
						//dh= [-5 15 19 -97 -26 350]/512;
						//dh=[dh fliplr(dh)];
						double dh[] = {-5., 15., 19., -97., -26., 350.,
							350., -26., -97., 19., 15., -5};
						d_h = vdouble(dh,12);
						d_h /= 512.;
					}
					break;
				case 4:
					{
						//dh= [35 -105 -195 865 363 -3489 -307 11025]/(2^14);
						//dh=[dh fliplr(dh)];
						double dh[] = {35., -105., -195., 865., 363., -3489., -307., 11025.,
							11025., -307., -3489., 363., 865., -195., -105., 35.};
						double pw = pow(2.0, 14.0);
						d_h = vdouble(dh,16) / pw;
					}
					break;
				case 5:
					{
						//dh= [-63 189 469 -1911 -1308 9188 1140 -29676 190 87318]/(2^17);
						//dh=[dh fliplr(dh)];
						double dh[] = {-63., 189., 469., -1911., -1308., 9188., 1140., -29676., 190., 87318.,
							87318., 190., -29676., 1140., 9188., -1308., -1911., 469., 189., -63.};
						double pw = pow(2.0, 17.0);
						d_h = vdouble(dh,20) / pw;
					}
					break;
				}
				//ldg=-nr1:nr2; lrg=-nd1:nd2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=sigdg.*rh; rg=sigrg.*dh;
				vdouble ldg = dsequence((double)(-nr1), 1.0, (double)(nr2));
				vdouble lrg = dsequence((double)(-nd1), 1.0, (double)(nd2));
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=sigdg*r_h; r_g=sigrg*d_h;
			}
			break;
		case 4:
			{
				m00=0.5;   
				nr1=4; nr2=4;nd1=nr1; nd2=nr2;ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
				//rh = [0,-.045635881557,-.028771763114,.295635881557];
				//rh = [rh .557543526229 fliplr(rh)];
				//dh = [.026748757411,-.016864118443,-.078223266529,.266864118443];
				//dh = [dh .602949018236 fliplr(dh)];
				double rh[] = {0., -.045635881557, -.028771763114, .295635881557,
					.557543526229,
						.295635881557, -.028771763114, -.045635881557, 0.};
				double dh[] = {.026748757411, -.016864118443, -.078223266529, .266864118443,
					.602949018236,
					.66864118443, -.078223266529, -.016864118443, .026748757411};
				r_h = vdouble(rh,9);
				d_h = vdouble(dh,9);

				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)(-ngd1), 1.0, (double)(ngd2));
				vdouble lrg = dsequence((double)(-ngr1), 1.0, (double)(ngr2));
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		case 5 :
			{
				m00=0.5;   
				nr1=5; nr2=5;nd1=nr1; nd2=nr2;ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
				//rh = [.009515330511, -.001905629356, -.096666153049,...
				//		-.066117805605, .337150822538];
				//rh = [rh .636046869922 fliplr(rh)];
				//dh = [0,.028063009296,.005620161515,-.038511714155,.244379838485];
				//dh = [dh .520897409718 fliplr(dh)];
				double rh[] = {.009515330511, -.001905629356, -.096666153049,
					-.066117805605, .337150822538,
					.636046869922,
					.337150822538, -.066117805605, 
					-.096666153049, -.001905629356, .009515330511};

				double dh[] = {0., .028063009296, .005620161515,
					-.038511714155, .244379838485,
					 .520897409718, 
					.244379838485, -.038511714155, 
					.005620161515, .028063009296, 0.};
				r_h = vdouble(rh,11);
				d_h = vdouble(dh,11);
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)(-ngd1), 1.0, (double)(ngd2));
				vdouble lrg = dsequence((double)(-ngr1), 1.0, (double)(ngr2));
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		case 6:
			{
				m00=0.5;
				nr1=5; nr2=5;nd1=8; nd2=8;ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
				//rh = [...
				//			-0.01020092218704  ...
				//			-0.01023007081937  0.05566486077996  0.02854447171515  -0.29546393859292 ...
				//		 ];
				//rh = [rh -0.53662880179157 fliplr(rh)]; rh=-rh;
				//dh = [...
				//			0.00134974786501 -0.00135360470301 -0.01201419666708   0.00843901203981 ...
				//			0.03516647330654 -0.05463331368252 -0.06650990062484   0.29754790634571 ...
				//		 ];
				//dh = [dh 0.58401575224075 fliplr(dh)];
				double rh[] = {
					-0.01020092218704, 
					-0.01023007081937,  0.05566486077996,  0.02854447171515,  -0.29546393859292,
					-0.53662880179157,
					-0.29546393859292, 0.02854447171515, 0.05566486077996, -0.01023007081937,
					-0.01020092218704};

				double dh[] = {
							0.00134974786501, -0.00135360470301, -0.01201419666708,  0.00843901203981,
							0.03516647330654, -0.05463331368252, -0.06650990062484,  0.29754790634571,
							0.58401575224075,
							0.29754790634571, -0.06650990062484, -0.05463331368252,  0.03516647330654,
							0.00843901203981, -0.01201419666708, -0.00135360470301,  0.00134974786501};
				r_h = -vdouble(rh,11);
				d_h = vdouble(dh,17);
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)(-ngd1), 1.0, (double)(ngd2));
				vdouble lrg = dsequence((double)(-ngr1), 1.0, (double)(ngr2));
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		}
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if (wf == WF_MY_BIORTOGONAL)
	{
		//cdf=menu('cdf filters order','(5.3)','(7.5)','(9.7)');
		switch (order)
		{
		case 1   :
			{
				nr1=1;nr2=nr1;
				nd1=2; nd2=nd1;
				ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
				double rh[] = {0.25, 0.5, 0.25}; 
				double dh[] = {-0.125, 0.25, 0.75, 0.25, -0.125};
				r_h = vdouble(rh,3);
				d_h = vdouble(dh,5);
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;

				vdouble ldg = dsequence((double)-ngd1, 1.0, (double)ngd2);
				vdouble lrg = dsequence((double)-ngr1, 1.0, (double)ngr2);
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		case 2:
			{
				
				nr1=2;nr2=nr1;
				nd1=3; nd2=nd1;
				ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
				double rh[] = {0.0625, 0.25, 0.375, 0.25, 0.0625};
				double dh[] = {0.09375, -0.375, 0.15625, 1.25, 0.15625, -0.375, 0.09375};
				r_h = vdouble(rh,5);
				d_h = vdouble(dh,7);
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2;
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;

				vdouble ldg = dsequence((double)-ngd1, 1.0, (double)ngd2);
				vdouble lrg = dsequence((double)-ngr1, 1.0, (double)ngr2);
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		case 3:
			{
				nr1=3;nr2=nr1;
				nd1=4; nd2=nd1;
				ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
				double rh[] = {-0.04563588156, -0.02877176311, 0.2956358816, 0.5575435262,
								0.2956358816, -0.02877176311, -0.04563588156};
				double dh[] = {0.02674875741, -0.01686411844, -0.07822326653, 0.2668641184,
								0.6029490182, 0.2668641184, -0.07822326653, -0.01686411844,
								0.02674875741};
				r_h = vdouble(rh,7);
				d_h = vdouble(dh,9);
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2;
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)-ngd1, 1.0, (double)ngd2);
				vdouble lrg = dsequence((double)-ngr1, 1.0, (double)ngr2);
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		}
	}
	//******************************************
	if (wf==WF_BIORTOGONAL_NONSTANDART)
	{
		// cdf=menu('cdf filters order','(9.7) at 4.2','(9.7) at 2.2');
		switch (order)
		{
			
		case 1 :
			{
				nr1=3;nr2=nr1; 
				nd1=4; nd2=nd1; 
				ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1;
								
				double rh[] =
				{
					-0.04703432274, -0.03156864547, 0.2970343227, 0.5631372909,
					0.2970343227, -0.03156864547, -0.04703432274
				};
				double dh[] =
				{
					0.02830723268, -0.01899933795, -0.07459296388,  0.2689993379,
					0.5925714624 ,  0.2689993379 , -0.07459296388, -0.01899933795,
					0.02830723268
				};
				r_h = vdouble(rh,7);
				d_h = vdouble(dh,9);
						
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2; 
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)-ngd1, 1.0, (double)ngd2);
				vdouble lrg = dsequence((double)-ngr1, 1.0, (double)ngr2);
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		case 2 :
			{
				
				nr1=3;nr2=nr1; 
				nd1=4; nd2=nd1; 
				ngd1=nr1-1; ngd2=nr2+1;
				ngr1=nd1-1; ngr2=nd2+1; 
				
				double rh[] = 
				{
					-0.1712400171, 0.1895215559,  0.4212400171, 0.1209568883,
					0.4212400171 , 0.1895215559, -0.1712400171
				};
				double dh[] =
				{
					-0.09356626053, -0.1035553697, 0.6093342598,  0.3535553697,
					-0.5315359985 ,  0.3535553697, 0.6093342598, -0.1035553697,
					-0.09356626053
				};
				r_h = vdouble(rh,7);
				d_h = vdouble(dh,9);
				//ldg=-ngd1:ngd2; lrg=-ngr1:ngr2;
				//sigdg=(-1).^ldg; sigrg=(-1).^lrg;
				//dg=-sigdg.*rh; rg=-sigrg.*dh;
				vdouble ldg = dsequence((double)-ngd1, 1.0, (double)ngd2);
				vdouble lrg = dsequence((double)-ngr1, 1.0, (double)ngr2);
				vdouble sigdg=pow(-1.0,ldg);
				vdouble sigrg=pow(-1.0,lrg);
				d_g=-sigdg*r_h; r_g=-sigrg*d_h;
			}
			break;
		}
	}
	if (wf == WF_DISCRETE_MEYER)
	{
		n00=30; m00=0.5;  
		double dg[] =
		{
			0.0000000e+000,  1.0100000e-012,  8.5194596e-009,  1.1119450e-008, -1.0798820e-008, -6.0669757e-008, -1.0866517e-007, -8.2006807e-008,
			1.1783004e-007,  5.5063406e-007,  1.1307947e-006,  1.4895492e-006,  7.3675729e-007, -3.2054419e-006, -1.6312700e-005, -6.5543059e-005, -6.0115023e-004,
			2.7046721e-003,  2.2025341e-003, -6.0458141e-003, -6.3877183e-003,  1.1061496e-002,  1.5270015e-002, -1.7423434e-002, -3.2130794e-002,  2.4348746e-002,
			6.3739024e-002, -3.0655092e-002, -1.3284520e-001,  3.5087556e-002,  4.4459300e-001, -7.4458559e-001,  4.4459300e-001,  3.5087556e-002, -1.3284520e-001,
			-3.0655092e-002,  6.3739024e-002,  2.4348746e-002, -3.2130794e-002, -1.7423434e-002,  1.5270015e-002,  1.1061496e-002, -6.3877183e-003, -6.0458141e-003,
			2.2025341e-003,  2.7046721e-003, -6.0115023e-004, -6.5543059e-005, -1.6312700e-005, -3.2054419e-006,  7.3675729e-007,  1.4895492e-006,  1.1307947e-006,
			5.5063406e-007,  1.1783004e-007, -8.2006807e-008, -1.0866517e-007, -6.0669757e-008, -1.0798820e-008,  1.1119450e-008,  8.5194596e-009,  1.0100000e-012
		};
		d_g = vdouble(dg,62);
		double dh[] =
		{
			-1.0100000e-012,  8.5194596e-009, -1.1119450e-008, -1.0798820e-008,  6.0669757e-008, -1.0866517e-007,  8.2006807e-008,  1.1783004e-007, -5.5063406e-007,
			1.1307947e-006, -1.4895492e-006,  7.3675729e-007,  3.2054419e-006, -1.6312700e-005,  6.5543059e-005, -6.0115023e-004, -2.7046721e-003,  2.2025341e-003,
			6.0458141e-003, -6.3877183e-003, -1.1061496e-002,  1.5270015e-002,  1.7423434e-002, -3.2130794e-002, -2.4348746e-002,  6.3739024e-002,  3.0655092e-002,
			-1.3284520e-001, -3.5087556e-002,  4.4459300e-001,  7.4458559e-001,  4.4459300e-001, -3.5087556e-002, -1.3284520e-001,  3.0655092e-002,  6.3739024e-002,
			-2.4348746e-002, -3.2130794e-002,  1.7423434e-002,  1.5270015e-002, -1.1061496e-002, -6.3877183e-003,  6.0458141e-003,  2.2025341e-003, -2.7046721e-003,
			-6.0115023e-004,  6.5543059e-005, -1.6312700e-005,  3.2054419e-006,  7.3675729e-007, -1.4895492e-006,  1.1307947e-006, -5.5063406e-007,  1.1783004e-007,
			8.2006807e-008, -1.0866517e-007,  6.0669757e-008, -1.0798820e-008, -1.1119450e-008,  8.5194596e-009, -1.0100000e-012,  0.0000000e+000
		};
		d_h = vdouble(dh,62);
//		d_h *= sqrt(2.0);
		d_h = d_h / d_h.Sum(); 
		d_g = -d_g / (d_h.Sum()*sqrt(2.0));
		nd1=0;nr1=0; ngd1=0;ngr1=0;
		nd2=d_h.Length() - 1; ngd2=nd2; nr2=nd2; ngr2=nd2;
		r_g=d_g; r_h=d_h;
	}

	/*
	if length(rg)>length(dg)
	ds=(length(rg)-length(dg))/2;
	n0=length(rg); rg1=rg(ds+1:n0-ds);
	%sum(dg.*rg1) 
	if sum(rg1.*dg)<0 rg=-rg;
	   sum(rg1.*dg)
	   disp('signum of rg another');
	end;
	else 
	ds=(length(dg)-length(rg))/2;
	n0=length(dg); dg1=dg(ds+1:n0+ds);
	%sum(rg.*dg1) 
	if sum(rg.*dg1)<0 dg=-dg;
	   sum(rg.*dg1) 
	   disp('signum of dg another');
	end;
	end;
	*/
}

void WaveletNames(int wf, // флаг типа вейвлетов
	int order, // порядоак вейвлета
	int orderBiorthogonalDecomposition,
	char * name)
{


	if (wf==WF_HAAR)
	{
		strcpy(name, "Haar");
	}
	if (wf==WF_DAUBECHIES)
	{
		sprintf(name, "daubechy order = %d", order);
	}
	if (wf==WF_SYMLETS)
	{
		sprintf(name, "symlet order = %d", order);
	}
	if (wf == WF_COIFLETS)
	{
		sprintf(name, "coiflet order = %d", order);
	}
	if (wf == WF_BIORTOGONAL)
	{
		  //rf=menu('reconstruction filter order','1 at (1 3 5)',....
		  //'2 at (2 4 6 8)','3 at (1 3 5 7 9)','4 at 4','5 at 5',...
		  //'6 at 8');
		int suborder;
		switch (order)
		{
		case 1 :
			{
				//df=menu('decomposition filter order','1','3','5');
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						suborder = 1;
					}
					break;
				case 2:
					{
						suborder = 3;
					}
					break;
				case 3:
					{
						suborder = 5;
					}
					break;
				}
				sprintf(name, "Biorthogonal order = %d at %d", order, suborder);
			}
			break;
		case 2 :
			{
				//df=menu('decomposition filter order','2','4','6','8');
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						suborder = 2;
					}
					break;
				case 2:
					{
						suborder = 4;
					}
					break;
				case 3:
					{
						suborder = 6;
					}
					break;
				case 4:
					{
						suborder = 8;
					}
					break;
				}
				sprintf(name, "Biorthogonal order = %d at %d", order, suborder);
			}
			break;
		case 3 :
			{
				//df=menu('decomposition filter order','1','3','5','7','9');
				switch (orderBiorthogonalDecomposition )
				{
				case 1:
					{
						suborder = 1;
					}
					break;
				case 2:
					{
						suborder = 3;
					}
					break;
				case 3:
					{
						suborder = 5;
					}
					break;
				case 4:
					{
						suborder = 7;
					}
					break;
				case 5:
					{
						suborder = 9;
					}
					break;
				}
				sprintf(name, "Biorthogonal order = %d at %d", order, suborder);
			}
			break;
		case 4:
			{
				sprintf(name, "Biorthogonal order = %d", order);
			}
			break;
		case 5 :
			{
				sprintf(name, "Biorthogonal order = %d", order);
			}
			break;
		case 6:
			{
				sprintf(name, "Biorthogonal order = %d", order);
			}
			break;
		}
	}
	//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
	if (wf == WF_MY_BIORTOGONAL)
	{
		//cdf=menu('cdf filters order','(5.3)','(7.5)','(9.7)');
		switch (order)
		{
		case 1   :
			{
				sprintf(name, "cdf filter order = (5.3)");
			}
			break;
		case 2:
			{
				sprintf(name, "cdf filter order = (7.5)");
			}
			break;
		case 3:
			{
				sprintf(name, "cdf filter order = (9.7)");
			}
			break;
		}
	}
	//******************************************
	if (wf==WF_BIORTOGONAL_NONSTANDART)
	{
		// cdf=menu('cdf filters order','(9.7) at 4.2','(9.7) at 2.2');
		switch (order)
		{
			
		case 1 :
			{
				sprintf(name, "cdf filter order = (9.7) at 4.2");
			}
			break;
		case 2 :
			{
				sprintf(name, "cdf filter order = (9.7) at 2.2");
			}
			break;
		}
	}
	if (wf == WF_DISCRETE_MEYER)
	{
		sprintf(name, "discrete Meyer");
	}
}

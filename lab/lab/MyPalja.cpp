// MyPalja.cpp: implementation of the MyPalja class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "MyPalja.h"
#include "../../excel_connect/src/MyExcel.h"

#include "SetObject.h"
#include "SetKT.h"

//#include "SetLito0.h"
#include "SetLito.h"

#include "SetPtPalja.h"
#include "SetPalja1.h"
#include "SetPtStZond.h"
#include "SetStZond.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

long GetTypeGrunt(bool pck, bool bUnEdited, CDatabase * database, long ID_OBJ, long ID_KT, double H, long & ID_IGE);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
void DeleteEndZeros(CString & str);

MyPalja::MyPalja(CDatabase * database, SurfDoc * doc)
{
	this->p_database = database;
	m_well.InitDoc(doc);
	this->ID_KT = -1;
	this->ID_OBJ = -1;
	typ_zond = -1;
	ustje = -DBL_MAX;
	ustje_defined = false;
}

MyPalja::~MyPalja()
{

}
bool GetUstanovka(CDatabase * database, 
				  long id_ust, 

				  CString & ust_name,
				  long & typ_zond,
				  long & n_shema,

				  double & Kg,
				  double & Kf,

				  double & Bg,
				  double & Bf,

				  double & shtanga_d
				  );

void MyPalja::InitWell()
{	
	//bUnEdited = true;
	SetLito setLito0(true, this->p_database);
	setLito0.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setLito0.m_strSort.Format("");
	if ( !setLito0.Open(CRecordset::dynaset) )
		return;


	if (!setLito0.IsBOF()) 
	{
		setLito0.MoveFirst( );
		while(!setLito0.IsEOF()) 
		{
			this->m_well.Lito0(setLito0.m_ID_IGE, 
				setLito0.m_H0, 
				setLito0.m_H1);

			setLito0.MoveNext();
		}
	}

	SetLito setLito(false, this->p_database);
	setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setLito.m_strSort.Format("");
	if ( !setLito.Open(CRecordset::dynaset) )
		return;


	if (!setLito.IsBOF()) 
	{
		setLito.MoveFirst( );
		while(!setLito.IsEOF()) 
		{
			this->m_well.Lito(setLito.m_ID_IGE, 
				setLito.m_H0, 
				setLito.m_H1);

			setLito.MoveNext();
		}
	}

	this->m_well.ApplyLito_well_ige_podoshva();
	this->m_well.ApplyLito_well_lito_podoshva();

	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setKT.m_strSort.Format("");
	if ( !setKT.Open(CRecordset::dynaset) )
		return;

	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		if(!setKT.IsEOF()) 
		{
			ustje = setKT.m_Z;
			ustje_defined = true;
			double zaboj = setKT.m_Z;
			this->m_well.WellInit(ID_KT, setKT.m_NAZVA, setKT.m_ID_TYP, setKT.m_X, setKT.m_Y, ustje, zaboj, setKT.m_ID_BUR, setKT.m_D_BUR, "");
		}
	}
	
	SetPtStZond setPtStZond(this->p_database);
	setPtStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPtStZond.m_strSort.Format("");
	if ( !setPtStZond.Open(CRecordset::dynaset) )
		return;

	if (!setPtStZond.IsBOF()) 
	{
		setPtStZond.MoveFirst( );
		if(!setPtStZond.IsEOF()) 
		{
			CString ust_name;
			long n_shema;
			double  Kg, Kf, Bg, Bf;
			double shtanga_d;
			
			GetUstanovka(this->p_database,
				setPtStZond.m_ID_UST, 
				ust_name,
				typ_zond,
				n_shema,
				Kg,Kf,Bg,Bf,  
				shtanga_d);

			this->m_well.AddPtStZond(setPtStZond.m_ID_UST,
				setPtStZond.m_GLYB,
				ust_name,
				typ_zond,
				n_shema,
				Kg, Kf, Bg, Bf, shtanga_d);
		}
	}



	SetStZond setStZond(this->p_database);
	setStZond.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setStZond.m_strSort.Format("NPP");
	if ( !setStZond.Open(CRecordset::dynaset) )
		return;


	if (!setStZond.IsBOF()) 
	{
		setStZond.MoveFirst( );
		while(!setStZond.IsEOF()) 
		{
			double H  = setStZond.m_H;
			//для вычислений несущей способности свай тип грунта берём из редактируемой лито-колонки
			long ID_IGE;
			bool bUnEdited = false;
			long TYPGR = GetTypeGrunt(false, bUnEdited, this->p_database, ID_OBJ, ID_KT, H, ID_IGE);
			
			this->m_well.AddStZond(setStZond.m_NPP, 
				TYPGR, //setStZond.m_TYPGR, //Надо динамически заполнять это поле
				setStZond.m_H, 
				setStZond.m_q0, 
				setStZond.m_f0, 
				setStZond.m_dH, 
				setStZond.m_fsr, 
				setStZond.m_bSTAT,
				setStZond.m_ID_IGE,
				setStZond.m_pck				
				);

			setStZond.MoveNext();
		}
	}

	SetPtPalja setPtPalja(this->p_database);
	setPtPalja.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPtPalja.m_strSort.Format("");
	if ( !setPtPalja.Open(CRecordset::dynaset) )
		return;

	if (!setPtPalja.IsBOF()) 
	{
		setPtPalja.MoveFirst( );
		if(!setPtPalja.IsEOF()) 
		{
			this->m_well.PtPalja(setPtPalja.m_ID_TYP,
				setPtPalja.m_Pereriz_X,
				setPtPalja.m_Pereriz_Y,
				setPtPalja.m_A,
				setPtPalja.m_u,
				setPtPalja.m_GLYB,
				setPtPalja.m_RsA,
				setPtPalja.m_fhu,
				setPtPalja.m_PZ,
				setPtPalja.m_ID_SNIP,
				setPtPalja.m_Fu);
		}
	}

	SetPalja setPalja(this->p_database);
	setPalja.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPalja.m_strSort.Format("H");
	if ( !setPalja.Open(CRecordset::dynaset) )
		return;


	if (!setPalja.IsBOF()) 
	{
		setPalja.MoveFirst( );
		while(!setPalja.IsEOF()) 
		{
			this->m_well.Palja(setPalja.m_H, 
				setPalja.m_qc, 
				setPalja.m_beta1, 
				setPalja.m_Rs, 
				setPalja.m_fs, 
				setPalja.m_beta2, 
				setPalja.m_f,
				setPalja.m_RsA, 
				setPalja.m_fhu,
				setPalja.m_Fu
				);

			setPalja.MoveNext();
		}
	}

}
void MyPalja::DeleteFromDB()
{
	SetPtPalja setPtPalja(this->p_database);
	setPtPalja.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPtPalja.m_strSort.Format("");
	if ( !setPtPalja.Open(CRecordset::dynaset) )
		return;

	if (!setPtPalja.IsBOF()) 
	{
		setPtPalja.MoveFirst( );
		while(!setPtPalja.IsEOF()) 
		{
			setPtPalja.Delete();
			setPtPalja.MoveNext();
		}
	}

	SetPalja setPalja(this->p_database);
	setPalja.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPalja.m_strSort.Format("H");
	if ( !setPalja.Open(CRecordset::dynaset) )
		return;


	if (!setPalja.IsBOF()) 
	{
		setPalja.MoveFirst( );
		while(!setPalja.IsEOF()) 
		{
			setPalja.Delete();
			setPalja.MoveNext();
		}
	}
}

void MyPalja::SaveToDB()
{
	SetPtPalja setPtPalja(this->p_database);
	setPtPalja.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPtPalja.m_strSort.Format("");
	if ( !setPtPalja.Open(CRecordset::dynaset) )
		return;

	if (this->m_well.m_palja.data2_filled) 
	{
		setPtPalja.AddNewRow(ID_OBJ, ID_KT, 
			this->m_well.m_palja.data2.id_typ,
			this->m_well.m_palja.data2.pereriz_x,
			this->m_well.m_palja.data2.pereriz_y,
			this->m_well.m_palja.data2.A,
			this->m_well.m_palja.data2.u,
			this->m_well.m_palja.data2.glyb,
			this->m_well.m_palja.data2.RsA,
			this->m_well.m_palja.data2.fhu,
			this->m_well.m_palja.data2.pz,
			this->m_well.m_palja.data2.id_snip,
			this->m_well.m_palja.data2.Fu);
	}

	SetPalja setPalja(this->p_database);
	setPalja.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setPalja.m_strSort.Format("H");
	if ( !setPalja.Open(CRecordset::dynaset) )
		return;


	for (vector<PaljaData1>::iterator it = this->m_well.m_palja.data1.begin();
		it != this->m_well.m_palja.data1.end(); it++) 
	{
		setPalja.AddNewRow(ID_OBJ, ID_KT, 
			(*it).h, 
			(*it).qc, 
			(*it).beta1, 
			(*it).Rs, 
			(*it).fs, 
			(*it).beta2, 
			(*it).f,
			(*it).RsA, 
			(*it).fhu,
			(*it).Fu
			);
	}
}
void MyPalja::Passport_KT(MyExcel & m_excel, const char * suffix)
{
	char S[64];
	SetObject setObject(this->p_database);
	setObject.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setObject.m_strSort.Format("");
	if ( !setObject.Open(CRecordset::dynaset) )
		return;

	if (!setObject.IsBOF()) 
	{
		setObject.MoveFirst( );
		if(!setObject.IsEOF()) 
		{
			sprintf(S, "CONTRACT%s", suffix);
			ExcelRange_SetValue(m_excel, S, COleVariant(setObject.m_CONTRACT));
			sprintf(S, "OBJECT%s", suffix);
			ExcelRange_SetValue(m_excel, S, COleVariant(setObject.m_NAZVA));
		}
	}

	SetKT setKT(this->p_database);
	setKT.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
	setKT.m_strSort.Format("");
	if ( !setKT.Open(CRecordset::dynaset) )
		return;

	if (!setKT.IsBOF()) 
	{
		setKT.MoveFirst( );
		if(!setKT.IsEOF()) 
		{
			sprintf(S, "KT%s", suffix);
			ExcelRange_SetValue(m_excel, S, COleVariant(setKT.m_NAZVA));
		}
	}
}
void MyPalja::Passport_Table(MyExcel & m_excel, int fr)
{
	char S[32];

	if (this->m_well.m_palja.data2_filled) 
	{		
		CString s = "";
		CString sr = "";
		switch (this->m_well.m_palja.data2.id_typ)
		{
		case 1:
			{
				s = "Круглая";

			}
			break;
		case 2:
			{
				s = "Квадратная";
			}
			break;
		case 3:
			{
				s = "Прямоугольная";
			}
			break;
		}
		switch (this->m_well.m_palja.data2.id_typ)
		{
		case 1:
			{
				CString sx;
				sx.Format("%f", 100 * this->m_well.m_palja.data2.pereriz_x);
				DeleteEndZeros(sx);
				sr.Format("%s см", sx);

			}
			break;
		case 2:
		case 3:
			{
				CString sx, sy;
				sx.Format("%f", 100 * this->m_well.m_palja.data2.pereriz_x);
				DeleteEndZeros(sx);
				sy.Format("%f", 100 * this->m_well.m_palja.data2.pereriz_y);
				DeleteEndZeros(sy);
				sr.Format("%sx%s см", sx, sy);
			}
			break;
		}
		ExcelRange_SetValue(m_excel, "TYPPALJA", COleVariant(s));
		ExcelRange_SetValue(m_excel, "ROZMIR", COleVariant(sr));
		
		s.Format("%f",  this->m_well.m_palja.data2.pz);
		DeleteEndZeros(s);
		ExcelRange_SetValue(m_excel, "ROSTVERK_A", COleVariant(s));

		s.Format("%f",  this->ustje - this->m_well.m_palja.data2.pz);
		DeleteEndZeros(s);
		ExcelRange_SetValue(m_excel, "ROSTVERK_H", COleVariant(s));

		ExcelRange_SetValue(m_excel, "ZOND_TYP", 
			COleVariant(this->m_well.m_stat_zond.data2.typ_zond));

		
		/*setPtPalja.AddNewRow(ID_OBJ, ID_KT, 
			this->m_well.m_palja.data2.id_typ,
			this->m_well.m_palja.data2.pereriz_x,
			this->m_well.m_palja.data2.pereriz_y,
			this->m_well.m_palja.data2.A,
			this->m_well.m_palja.data2.u,
			this->m_well.m_palja.data2.glyb,
			this->m_well.m_palja.data2.RsA,
			this->m_well.m_palja.data2.fhu,
			this->m_well.m_palja.data2.pz,
			this->m_well.m_palja.data2.id_snip,
			this->m_well.m_palja.data2.Fu);*/
	}
	char c, fc = 'A';
	int i = 0;
	for (vector<PaljaData1>::iterator it = this->m_well.m_palja.data1.begin();
		it != this->m_well.m_palja.data1.end(); it++, i++) 
	{
		c = fc;

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant(this->m_well.m_palja.data2.pz - (*it).h), true);

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).h), true);

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).qc), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).beta1), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).Rs), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).fs), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).beta2), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).f), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).RsA), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).fhu), true);									

		sprintf(S, "%c%d", c++, fr+i);
		ExcelRange_SetValue(m_excel, S, COleVariant((*it).Fu), true);									
	}
}




void MyPalja::Passport(const char * fn)
{
	char file0[4098];
	char file[4098];

	switch (BaseLab::PassportLanguage)
	{
	case BaseLab::language::russian:
		{
			sprintf(file, "%s_Pasport_PaljaR2.xls", fn);
			sprintf(file0, "%s\\Pasport_PaljaR2.xls", Laboratory::FormsDir.c_str());
		}
		break;
	case BaseLab::language::ukrainian:
		{
			sprintf(file, "%s_Pasport_Palja2.xls", fn);
			sprintf(file0, "%s\\Pasport_Palja2.xls", Laboratory::FormsDir.c_str());
		}
		break;
	}
	CopyFile(file0, file, FALSE); 
				

	MyExcel m_excel;
	m_excel.ExcelOleLoad();
	if (m_excel.IsApplicationDispatch())
	{
		try
		{
			m_excel.ExcelOleExecute(file);

			int fr = 19;

			this->Passport_KT(m_excel, "");
			this->Passport_Table(m_excel, fr);

			m_excel.m_workbook.Save();
		}
		catch (CException* pe)
		{
			// catch errors from WinINet 
			TCHAR szErr[4098]; 
			pe->GetErrorMessage(szErr, 4098); 
			AfxMessageBox(szErr);
			pe->Delete();
		}
		m_excel.ExcelOleRelease();
	}
	else
	{
		printf("!!!!! m_excel.IsApplicationDispatch()\n");
		AfxMessageBox("!!!!! m_excel.IsApplicationDispatch()\n");
	}
}
bool FindMeanPCK(StatZond & stat_zond, double glubina_ot_ustja, double d, double & mean_pck, long id_method);
double GetBeta1(double qs, long id_snip);
void Well_3D::CalcPalja(long id_typ, double pereriz_x, double pereriz_y, 
						double glubina_rostverka,
						long id_snip, bool razbivka_na_tolschi, long typ_grunt_1_zond_type, long id_method_FindMeanPCK, double step)
{
	this->m_palja.data1.clear();
	this->m_palja.data1_filled = false;

	if (glubina_rostverka < 0.0)
		glubina_rostverka = 0.0;

	double A;
	double u;
	double d; //диаметр, ширина или большая сторона сечения сваи

	if (
		id_typ == 1)
	{

		double r = 
			//this->m_palja.data2.
			pereriz_x;
		d = 2.0 * r;

		A = PI * r * r;
		u = 2.0 * PI * r;			
	}
	else
	{
		d = max(
			pereriz_x, 
			pereriz_y);
		A = 
			pereriz_x * 
			pereriz_y;
		u = 2.0 * (
			pereriz_x + 
			pereriz_y);

	}		

	CPoint3 ustje;
	if (this->GetUstje(ustje))
	{
		double max_palja_h_ot_ustja = m_stat_zond.data2.glyb - 4 * d;
		double pz = ustje.z - glubina_rostverka;
		double glyb = 0.0;
		double Fhu = 0.0;
		double RsA = 0.0;
		double Fu = 0.0;
		double max_palja_h_ot_rostverka = max_palja_h_ot_ustja - glubina_rostverka;
		bool go = true;
		double dh;
		for (double glubina_ot_rostverka = step; 
			glubina_ot_rostverka <= max_palja_h_ot_rostverka; 
			glubina_ot_rostverka += dh)
		{

			double glubina_ot_ustja = glubina_ot_rostverka + glubina_rostverka;
			double mean_pck;

			if (FindMeanPCK(this->m_stat_zond, glubina_ot_ustja, d, mean_pck, id_method_FindMeanPCK))
			{
				// Л.Г.Мариупольский 
				// Исследования грунтов для проектирования свайных фундаментов
				// Москва, Стройиздат, 1989
				double qc = mean_pck;		


				double beta1 = GetBeta1(qc, id_snip);
				double Rs = beta1 * qc; // (4.7) стр.60
				double RA = 1000.*Rs*A;

				double fh;
				double beta2, fs;
				
				if(this->FindIntegralPCB(glubina_rostverka, glubina_ot_ustja, fh, id_snip, razbivka_na_tolschi,typ_grunt_1_zond_type, beta2, fs))
				{
					double h = glyb = glubina_ot_rostverka;

					Fu = 0.0;
					switch (id_snip)
					{
					case 1:
						{
							Fu = RA + fh * u; //(4.6) стр.59
						}
						break;
					case 2:
						{
							Fu = 0.4 * RA + 0.8 * fh * u; //(4.6) стр.59
						}
						break;
					}

					Fhu = fh * u;
					RsA = RA;
					double f = fh / h;

					this->Palja(h, qc, beta1, Rs, fs, beta2, f, RsA, Fhu, Fu);
				}
			}

			dh = (max_palja_h_ot_rostverka - glubina_ot_rostverka > step ? step : max_palja_h_ot_rostverka - glubina_ot_rostverka);

			if (dh < 1.0e-8)
				break;
		}

		this->PtPalja(id_typ, pereriz_x, pereriz_y, A, u, glyb, RsA, Fhu, pz, id_snip, Fu);
	}
}

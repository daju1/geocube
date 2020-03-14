//prop_value.h
#pragma once
#if defined (_MSC_VER) && !defined (QT_PROJECT) && !defined (QT_VERSION)
#include <windows.h>
#endif
#include <string>
#include <vector>
#include <map>
using namespace std;

struct GranVyprobData1
{
	long id_gran;
	string gran_name;
	double min_d;
	double max_d;
	double val;
	GranVyprobData1(long idgran, const char * granname, double v)
	{
		id_gran = idgran;
		gran_name = granname;
		val = v;
		min_d = -DBL_MAX;
		max_d = DBL_MAX;
		this->CalcMinMaxD();
	}
	void CalcMinMaxD()
	{
		char s[64];
		sprintf_s(s, 64, gran_name.c_str());
		char * p_ = strchr(s, '-');
		char * pl = strchr(s, '<');

		if (pl)
		{
			min_d = -DBL_MAX;
			max_d = atof(pl+1);
		}
		else if (p_)
		{
			min_d = atof(s);
			max_d = atof(p_+1);
			if (max_d < min_d)
				max_d = DBL_MAX;
		}
	}
	bool operator>(GranVyprobData1& dt)
	{
		return min_d > dt.min_d && max_d > dt.max_d;
	}
	bool operator<(GranVyprobData1& dt)
	{
		return min_d < dt.min_d && max_d < dt.max_d;
	}
};
struct GranVyprobData2
{
	long id_methoh;//просев 1 или ареометрич 2
	string soil_class;

	GranVyprobData2()
	{
		id_methoh = -1;
		soil_class = "";
	}
};

struct GranVyprob
{
	vector<GranVyprobData1> data1;
	GranVyprobData2 data2;

	bool data1_filled;
	bool data2_filled;

	GranVyprob()
	{
		data1_filled = false;
		data2_filled = false;
	}
	GranVyprob(GranVyprobData1 data)
	{
		data1_filled = true;
		data2_filled = false;
		data1.push_back(data);
	}	
	GranVyprob(GranVyprobData2 data)
	{
		data1_filled = false;
		data2_filled = true;
		data2 = data;
	}
	void Add(GranVyprobData1 data)
	{
		data1_filled = true;
		data1.push_back(data);
	}	
	void AddGranular(long id_gran, const char * gran_name, double val)
	{
		GranVyprobData1 data(id_gran, gran_name, val);
		this->Add(data);
	}
	void Add(GranVyprobData2 data)
	{
		data2_filled = true;
		data2 = data;
	}
	string GetDescription()
	{
		string str;
		for (vector<GranVyprobData1>::iterator it = data1.begin();
			it != data1.end(); it++)
		{
			char s[64];
			sprintf_s(s, 64, "%s\t%f\n", (*it).gran_name.c_str(), (*it).val);
			str += s;
		}
		return str;
	}
	void FillGranContentMap(map<long, GranVyprobData1> & gran_content)
	{
		for (vector<GranVyprobData1>::iterator it = data1.begin();
			it != data1.end(); it++)
		{
			gran_content.insert(map<long, GranVyprobData1>::value_type((*it).id_gran, (*it)));
		}
	}
};

struct ZrizVyprobData1
{
	long id_kolca;
	double sigma;
	double tau;
	double w_do;
	double ro_do;
	double w_po_upl;
	double ro_po_upl;
	double w_after;
	double ro_after;
	unsigned char bStat;
};
struct ZrizVyprobData0
{
	long id_kolca;
	long id_phys_vyprob;
	double h; 
	double d; 
	double dh_po_upl;
	double m_kolca;
	double m_grunta;
	double m_grunta_zamoch;
	double m_grunta_posle_uplot;
	double m_grunta_posle;
	double m_grunta_vysush;
};
struct ZrizVyprobData2
{
	long id_hid;
	long id_shema;
	long id_stan;
	double tgfi;
	double c;
	double d;
	double h;
	unsigned char bStat;
};

struct ZrizVyprob
{
	vector<ZrizVyprobData1> data1;
	vector<ZrizVyprobData0> data0;
	ZrizVyprobData2 data2;

	bool data1_filled;
	bool data0_filled;
	bool data2_filled;

	ZrizVyprob()
	{
		data1_filled = false;
		data0_filled = false;
		data2_filled = false;
	}
	ZrizVyprob(ZrizVyprobData1 data)
	{
		data1_filled = true;
		data0_filled = false;
		data2_filled = false;
		data1.push_back(data);
	}	
	ZrizVyprob(ZrizVyprobData0 data)
	{
		data1_filled = false;
		data0_filled = true;
		data2_filled = false;
		data0.push_back(data);
	}	
	ZrizVyprob(ZrizVyprobData2 data)
	{
		data1_filled = false;
		data0_filled = false;
		data2_filled = true;
		data2 = data;
	}
	void Add(ZrizVyprobData1 data)
	{
		data1_filled = true;
		data1.push_back(data);
	}	
	void Add(ZrizVyprobData0 data)
	{
		data0_filled = true;
		data0.push_back(data);
	}	
	void Add(ZrizVyprobData2 data)
	{
		data2_filled = true;
		data2 = data;
	}
};
struct Zriz
{
	map<long, ZrizVyprob> vyprob;

	Zriz()
	{
		vyprob.clear();
	}
	Zriz(long id_vyprob, ZrizVyprob val)
	{
		vyprob.clear();
		vyprob.insert(map<long, ZrizVyprob>::value_type(id_vyprob, val));
	}
	void Add(long id_vyprob, ZrizVyprob val)
	{
		map<long, ZrizVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, ZrizVyprob>::value_type(id_vyprob, val));
		}
		else
		{
			(*found).second = val;
		}
	}
	void Add(long id_vyprob, ZrizVyprobData1 data)
	{
		map<long, ZrizVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, ZrizVyprob>::value_type(id_vyprob, ZrizVyprob(data)));
		}
		else
		{
			(*found).second.Add(data);
		}
	}
	void Add(long id_vyprob, ZrizVyprobData0 data)
	{
		map<long, ZrizVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, ZrizVyprob>::value_type(id_vyprob, ZrizVyprob(data)));
		}
		else
		{
			(*found).second.Add(data);
		}
	}
	void Add(long id_vyprob, ZrizVyprobData2 data)
	{
		map<long, ZrizVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, ZrizVyprob>::value_type(id_vyprob, ZrizVyprob(data)));
		}
		else
		{
			(*found).second.data2 = data;
			(*found).second.data2_filled = true;
		}
	}
};

struct CompressVyprobData1
{
	double sigma;
	double dh1;
	double dh2;
	unsigned char voda;
	unsigned char bStat;
};
struct CompressVyprobData0
{
	long id_kolca;
	long id_phys_vyprob;
	double h; 
	double d;
	double m_kolca;
	double m_grunta;
	double m_grunta_zamoch;
	double m_grunta_posle;
	double m_grunta_vysush;
};
struct CompressVyprobData2
{
	double h, d, es_l1, es_r1, es_l2, es_r2;
	double nju, nju_z;
	double m01, E1, m02, E2;
	double m01v, E1v, m02v, E2v;
	unsigned char id_method, bStat, bStatV;
};
struct CompressVyprob
{
	vector<CompressVyprobData1> data1;
	vector<CompressVyprobData0> data0;
	CompressVyprobData2 data2;

	bool data1_filled;
	bool data0_filled;
	bool data2_filled;


	CompressVyprob()
	{
		data1_filled = false;
		data0_filled = false;
		data2_filled = false;
	}
	CompressVyprob(CompressVyprobData1 data)
	{
		data1_filled = true;
		data0_filled = false;
		data2_filled = false;
		data1.push_back(data);
	}
	CompressVyprob(CompressVyprobData0 data)
	{
		data1_filled = false;
		data0_filled = true;
		data2_filled = false;
		data0.push_back(data);
	}
	CompressVyprob(CompressVyprobData2 data)
	{
		data1_filled = false;
		data0_filled = false;
		data2_filled = true;
		data2 = data;
	}
	void Add(CompressVyprobData1 data)
	{
		data1_filled = true;
		data1.push_back(data);
	}	
	void Add(CompressVyprobData0 data)
	{
		data0_filled = true;
		data0.push_back(data);
	}	
	void Add(CompressVyprobData2 data)
	{
		data2_filled = true;
		data2 = data;
	}
};

struct Compress
{
	map<long, CompressVyprob> vyprob;

	Compress()
	{
		vyprob.clear();
	}
	Compress(long id_vyprob, CompressVyprob val)
	{
		vyprob.clear();
		vyprob.insert(map<long, CompressVyprob>::value_type(id_vyprob, val));
	}
	void Add(long id_vyprob, CompressVyprob val)
	{
		map<long, CompressVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, CompressVyprob>::value_type(id_vyprob, val));
		}
		else
		{
			(*found).second = val;
		}
	}
	void Add(long id_vyprob, CompressVyprobData1 data)
	{
		map<long, CompressVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, CompressVyprob>::value_type(id_vyprob, CompressVyprob(data)));
		}
		else
		{
			(*found).second.Add(data);
		}
	}
	void Add(long id_vyprob, CompressVyprobData0 data)
	{
		map<long, CompressVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, CompressVyprob>::value_type(id_vyprob, CompressVyprob(data)));
		}
		else
		{
			(*found).second.Add(data);
		}
	}
	void Add(long id_vyprob, CompressVyprobData2 data)
	{
		map<long, CompressVyprob>::iterator found = vyprob.find(id_vyprob);

		if (found == vyprob.end())
		{
			vyprob.insert(map<long, CompressVyprob>::value_type(id_vyprob, CompressVyprob(data)));
		}
		else
		{
			(*found).second.data2 = data;
			(*found).second.data2_filled = true;
		}
	}
};


struct PropValue
{
	long id_param;
	string param_name;

	map<long, double> vyprob;
	PropValue(long idparam, const char * paramname, long id_vyprob, double val)
	{
		id_param = idparam;
		param_name = paramname;
		vyprob.clear();
		vyprob.insert(map<long, double>::value_type(id_vyprob, val));
	}
	void AddPropValue(long id_vyprob, double val)
	{
		vyprob.insert(map<long, double>::value_type(id_vyprob, val));
	}
	bool GetValue(double & val, long id_vyprob)
	{
		val = 0.0;
		map<long, double>::iterator it = vyprob.find(id_vyprob);
		if (it != vyprob.end())
		{
			val = (*it).second;		
			return true;// test only!!!!
		}
		return false;
	}
#if 1
	// test only!!!!
	bool GetValue_(double & val)
	{
		val = 0.0;
		int n = 0;
		for (map<long, double>::iterator it = vyprob.begin();
			it != vyprob.end(); it++)
		{
			val += (*it).second;
			n++;
			
			return true;// test only!!!!
		}
		if (n)
		{
			val /= n;
			return true;
		}
		return false;
	}
#else
	bool GetValue(double & val)
	{
		val = 0.0;
		int n = 0;
		for (map<long, double>::iterator it = vyprob.begin();
			it != vyprob.end(); it++)
		{
			val += (*it).second;
			n++;
		}
		if (n)
		{
			val /= n;
			return true;
		}
		return false;
	}
#endif
};

struct StatZond;

struct StatZondData1
{
	StatZond * pStatZond;
	long npp;
	long typgr;
	double h;
	double q0;
	double f0; 
	double dh;
	double fsr; 
	unsigned char bStat;
	long id_ige;
	double pck;

	double GetPCK();
	double GetPCB();
	double GetQs();

	void Init(
		long _npp, 
		long _typgr,
		double _h, 
		double _q0, 
		double _f0,
		double _dh, 
		double _fsr, 
		unsigned char _bStat)
	{	
		this->npp = _npp;
		this->typgr = _typgr;
		this->h = _h;
		this->q0 = _q0;
		this->f0 = _f0;
		this->dh = _dh;
		this->fsr = _fsr;
		this->bStat = _bStat;
	}
};
struct StatZondData2
{
	long id_ust;
	double glyb;

	string ust_name;
	long typ_zond;
	long n_shema;
	double Kg;
	double Kf;
	double Bg;
	double Bf;

	double shtanga_d;

	double nach_glyb;

	StatZondData2()
	{
		id_ust = -1;
		typ_zond = 0;
		ust_name = "";
		Kg = 0.0;
		Kf = 0.0;
		Bg = 0.0;
		Bf = 0.0;

		glyb = 0.0;
		nach_glyb = 0.0;
		n_shema = -1;

		shtanga_d = 0.036;
		//shtanga_d = 0.0357;
	}

	bool ParseUstName()
	{
		if (strcmp (ust_name.c_str(), "С-832(Піка-15)"))
		{
			id_ust = 1;
			typ_zond = 2;
		}
		else if (strcmp (ust_name.c_str(), "С-979-1"))
		{
			id_ust = 2;
			typ_zond = 1;
		}
		else if (strcmp (ust_name.c_str(), "С-979-2"))
		{
			id_ust = 3;
			typ_zond = 1;
		}
		else if (strcmp (ust_name.c_str(), "С-59"))
		{
			id_ust = 4;
			typ_zond = 1;
		}
		else if (strcmp (ust_name.c_str(), "Пика-15"))
		{
			id_ust = 5;
			typ_zond = 2;
		}
		else if (strcmp (ust_name.c_str(), "832-5"))
		{
			id_ust = 1;
			typ_zond = 2;
		}
		else if (strcmp (ust_name.c_str(), "979"))
		{
			id_ust = 2;
			typ_zond = 1;
		}
		else if (strcmp (ust_name.c_str(), "979-1"))
		{
			id_ust = 2;
			typ_zond = 1;
		}
		else if (strcmp (ust_name.c_str(), "979-2"))
		{
			id_ust = 3;
			typ_zond = 1;
		}
		else if (strcmp (ust_name.c_str(), "59"))
		{
			id_ust = 4;
			typ_zond = 1;
		}
		else
		{
			return false;
		}
		return true;
	}
};

struct StatZond
{
	vector<StatZondData1> data1;
	StatZondData2 data2;

	bool data1_filled;
	bool data2_filled;

	void Init(const StatZond& ob)
	{    
		this->data2_filled = ob.data2_filled;
		this->data1_filled = ob.data1_filled;
		this->data2 = ob.data2;
		this->data1 = ob.data1;

		for (vector<StatZondData1>::iterator it = this->data1.begin();
			it != this->data1.end(); it++)
		{
			(*it).pStatZond = this;
		}

	}
	StatZond& operator=(const StatZond& ob)
	{
		if (this == &ob)
			return *this;
		this->Init(ob);
		return *this;
	}
	StatZond(const StatZond& ob)
	{
		this->Init(ob);
	}

	StatZond()
	{
		data1_filled = false;
		data2_filled = false;
	}
	StatZond(StatZondData1 data)
	{
		data.pStatZond = this;
		data1_filled = true;
		data2_filled = false;
		data1.push_back(data);
	}	
	StatZond(StatZondData2 data)
	{
		data1_filled = false;
		data2_filled = true;
		data2 = data;
	}
	void Add(StatZondData1 data)
	{
		data.pStatZond = this;
		data1_filled = true;
		data1.push_back(data);
	}	
	void Add(StatZondData2 data)
	{
		data2_filled = true;
		data2 = data;
	}
	bool GetQs(double h, double & Qs);
};

struct PCK2FizParamsData
{
	long id_calc_param;
	string calc_param;
	string desc;
};

struct PCK2FizParams
{
	vector<PCK2FizParamsData> datas;
	void Add(PCK2FizParamsData data)
	{
		datas.push_back(data);
	}
};


struct PCK2FizResultsData
{
	long npp;
	long id_calc_param;
	double param;
};

struct PCK2FizResult
{
	map<long, PCK2FizResultsData> datas;
	PCK2FizResult(PCK2FizResultsData data)
	{
		this->Add(data.npp, data);
	}
	void Add(long npp, PCK2FizResultsData val)
	{
		map<long, PCK2FizResultsData>::iterator found = datas.find(npp);

		if (found == datas.end())
		{
			datas.insert(map<long, PCK2FizResultsData>::value_type(npp, PCK2FizResultsData(val)));
		}
		else
		{
			(*found).second = val;
		}
	}
};
struct PCK2FizResults
{
	map<long, PCK2FizResult> datas;
	void Add(long id_calc_param, PCK2FizResultsData val)
	{
		map<long, PCK2FizResult>::iterator found = datas.find(id_calc_param);

		if (found == datas.end())
		{
			datas.insert(map<long, PCK2FizResult>::value_type(id_calc_param, PCK2FizResult(val)));
		}
		else
		{
			(*found).second.Add(val.npp, val);
		}
	}
};

struct ige_data
{
	long id_ige, id_gr;
	string ige;
	double mk, mkz;
	string strat, desc0;
};
struct grunt_data
{
	long id_gr;
	string nazva_u, nazva_r;
	long typgr, typgr_pck, id_normatyv, id_grcons, id_uklad, id_nju, id_grmain, id_umpoz, id_genezis;
};
struct IGE_Data
{
	ige_data ige;
	grunt_data grunt;
	bool ige_filled;
	bool grunt_filled;

	IGE_Data()
	{
		ige_filled = false;
		grunt_filled = false;
	}
	void Add(ige_data ig)
	{
		ige = ig;
		ige_filled = true;
	}	
	void Add(grunt_data gr)
	{
		grunt_filled = true;
		grunt = gr;
	}
};
struct db_IGE
{
	vector<IGE_Data> data;

	void Add(ige_data ig)
	{
		bool found = false;
		for (vector<IGE_Data>::iterator it = data.begin();
			it != data.end(); it++)
		{
			if ((*it).grunt_filled && (*it).grunt.id_gr == ig.id_gr)
			{
				found = true;
				(*it).Add(ig);
			}
		}	

		if (!found)
		{
			data.push_back(IGE_Data());
			data.back().Add(ig);
		}
	}	
	void Add(grunt_data gr)
	{
		bool found = false;
		for (vector<IGE_Data>::iterator it = data.begin();
			it != data.end(); it++)
		{
			if ((*it).ige_filled && (*it).ige.id_gr == gr.id_gr)
			{
				found = true;
				(*it).Add(gr);
			}
		}
		if (!found)
		{
			data.push_back(IGE_Data());
			data.back().Add(gr);
		}
	}
};
struct genezis_data
{
	long id_genezis;
	string nazva_u, nazva_r;
	long id_normatyv;
	long id_grmain;
	string index;
	BYTE r, g, b;
};
struct db_Genezis
{
	map<long, genezis_data> data1;
	void Add(long id_genezis, genezis_data data)
	{
		data1.insert(map<long, genezis_data>::value_type(id_genezis, data));
	}	
};

struct umpoz_data
{
	long id_umpoz;
	string umpoz, hatchacad;
	double angle, scale;
};
struct db_UmPoz
{
	map<long, umpoz_data> data1;
	void Add(long id_umpoz, umpoz_data data)
	{
		data1.insert(map<long, umpoz_data>::value_type(id_umpoz, data));
	}	
};

struct db_rozrizy_data
{
	long id_rozriz; 
	string nomer;
	BYTE has_dxf;
	string fn_dxf;
	BYTE acad_yscale_loaded;
	double z1w, y1a, z2w, y2a;
};
struct db_rozriz_data
{
	long id_rozriz; 
	long npp; 
	long id_kt;
	double dxf_x;
};
struct DB_rozriz
{
	db_rozrizy_data name;
	bool name_filled;
	map<long, db_rozriz_data> kt_points;

	DB_rozriz(db_rozrizy_data val)
	{
		kt_points.clear();
		name = val;
		name_filled = true;
	}
	DB_rozriz(long npp, db_rozriz_data val)
	{
		kt_points.clear();
		kt_points.insert(map<long, db_rozriz_data>::value_type(npp, val));
		name_filled = false;
	}
	void Add(long npp, db_rozriz_data val)
	{
		map<long, db_rozriz_data>::iterator found = kt_points.find(npp);

		if (found == kt_points.end())
		{
			kt_points.insert(map<long, db_rozriz_data>::value_type(npp, val));
		}
		else
		{
			(*found).second = val;
		}
	}
	void Add(db_rozrizy_data val)
	{
		this->name = val;
		this->name_filled = true;
	}
};
struct DB_rozrizy
{
	map<long, DB_rozriz> rozrizy;
	DB_rozrizy()
	{
		rozrizy.clear();
	}
	void Add(long id_rozriz, db_rozrizy_data val)
	{
		map<long, DB_rozriz>::iterator found = rozrizy.find(id_rozriz);

		if (found == rozrizy.end())
		{
			rozrizy.insert(map<long, DB_rozriz>::value_type(id_rozriz, DB_rozriz(val)));
		}
		else
		{
			(*found).second.Add(val);
		}
	}
	void Add(long id_rozriz, db_rozriz_data val)
	{
		map<long, DB_rozriz>::iterator found = rozrizy.find(id_rozriz);

		if (found == rozrizy.end())
		{
			rozrizy.insert(map<long, DB_rozriz>::value_type(id_rozriz, DB_rozriz(val.npp, val)));
		}
		else
		{
			(*found).second.Add(val.npp, val);
		}
	}
};
struct db_voda_data
{
	long horizont;
	double hv_z; 
	double hv_v;
	SYSTEMTIME dv;
};

struct DB_Voda
{
	vector<db_voda_data> data1;
	bool data_filled;
	DB_Voda()
	{
		data_filled = false;
	}
	void Add(db_voda_data data)
	{
		data_filled = true;
		data1.push_back(data);
	}
};
struct db_lito_data
{
	long id_ige;
	double h0;
	double h1;
};

struct DB_Lito
{
	vector<db_lito_data> data1;
	bool data_filled;
	DB_Lito()
	{
		data_filled = false;
	}
	void Add(db_lito_data data)
	{
		data_filled = true;
		data1.push_back(data);
	}
};

struct PaljaData1
{
	double h;
	double qc; double beta1; double Rs; double fs; double beta2; double f;
	double RsA;
	double fhu;
	double Fu;
};
struct PaljaData2
{
	long id_typ;
	double pereriz_x;
	double pereriz_y;
	double A;
	double u;
	double glyb;
	double RsA;
	double fhu;
	double pz;
	long id_snip;
	double Fu;

	double rostverk;

	PaljaData2()
	{
		id_typ = 2;

		pereriz_x = 0.25;
		pereriz_y = 0.25;
	}
};

struct APalja
{
	vector<PaljaData1> data1;
	PaljaData2 data2;

	bool data1_filled;
	bool data2_filled;

	APalja()
	{
		data1_filled = false;
		data2_filled = false;
	}
	APalja(PaljaData1 data)
	{
		data1_filled = true;
		data2_filled = false;
		data1.push_back(data);
	}	
	APalja(PaljaData2 data)
	{
		data1_filled = false;
		data2_filled = true;
		data2 = data;
	}
	void Add(PaljaData1 data)
	{
		data1_filled = true;
		data1.push_back(data);
	}	
	void Add(PaljaData2 data)
	{
		data2_filled = true;
		data2 = data;
	}
};

struct db_griddata_item
{
	long id_surf;
	long id_point;
	double x, y, z;
};
struct db_griddata_surfaces_item
{
	long id_surf;
	string nazva;
	BYTE podoshva;
	BYTE r, g, b;
	short z_flag;
	long id_umpoz;
	long id_ige;
};
struct db_griddata_surf
{
	map<long, db_griddata_item> data1;
	db_griddata_surfaces_item data2;
	bool data2_filled;
	db_griddata_surf(db_griddata_surfaces_item val)
	{
		data1.clear();
		data2 = val;
		data2_filled = true;
	}
	db_griddata_surf(long id_point, db_griddata_item val)
	{
		data1.clear();
		data1.insert(map<long, db_griddata_item>::value_type(id_point, val));
		data2_filled = false;
	}
	void Add(long id_point, db_griddata_item val)
	{
		map<long, db_griddata_item>::iterator found = data1.find(id_point);

		if (found == data1.end())
		{
			data1.insert(map<long, db_griddata_item>::value_type(id_point, val));
		}
		else
		{
			(*found).second = val;
		}
	}
	void Add(db_griddata_surfaces_item val)
	{
		this->data2 = val;
		this->data2_filled = true;
	}
};
struct db_griddata
{
	map<long, db_griddata_surf> datas;
	void Add(long id_surf, db_griddata_surfaces_item val)
	{
		map<long, db_griddata_surf>::iterator found = datas.find(id_surf);

		if (found == datas.end())
		{
			datas.insert(map<long, db_griddata_surf>::value_type(id_surf, db_griddata_surf(val)));
		}
		else
		{
			(*found).second.Add(val);
		}
	}
	void Add(long id_surf, db_griddata_item val)
	{
		map<long, db_griddata_surf>::iterator found = datas.find(id_surf);

		if (found == datas.end())
		{
			datas.insert(map<long, db_griddata_surf>::value_type(id_surf, db_griddata_surf(val.id_point, val)));
		}
		else
		{
			(*found).second.Add(val.id_point, val);
		}
	}
};

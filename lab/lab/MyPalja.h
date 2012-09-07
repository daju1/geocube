// MyPalja.h: interface for the MyPalja class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MYPALJA_H__1B776FBA_E163_4CCE_BD24_425A62C33B1A__INCLUDED_)
#define AFX_MYPALJA_H__1B776FBA_E163_4CCE_BD24_425A62C33B1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../../surfdoc/src/well_3d.h"

class MyPalja  
{
	CDatabase * p_database;
///	SurfDoc * p_SurfDoc;
public:
	CString KT_nazva;
	bool ustje_defined;
	double ustje;
	Well_3D m_well;
	long ID_OBJ, ID_KT;
	long typ_zond;
	void InitWell();
	void DeleteFromDB();
	void SaveToDB();

	void Passport_KT(MyExcel & m_excel, const char * suffix);
	void Passport_Table(MyExcel & m_excel, int fr);

	void Passport(const char * fn);

	MyPalja(CDatabase * database, SurfDoc * doc);
	virtual ~MyPalja();

};

#endif // !defined(AFX_MYPALJA_H__1B776FBA_E163_4CCE_BD24_425A62C33B1A__INCLUDED_)

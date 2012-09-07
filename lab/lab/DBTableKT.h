// DBTableKT.h: interface for the DBTableKT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DBTABLEKT_H__49CD9AC1_8D31_4147_92E1_722A52531081__INCLUDED_)
#define AFX_DBTABLEKT_H__49CD9AC1_8D31_4147_92E1_722A52531081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "DBTable.h"

#include "../../surfdoc/src/wellelement.h"

class DBTableKT : public DBTable  
{
public:

	wells_draw_list_item * m_wdli_podoshva_lito;
	wells_draw_list_item * m_wdli_podoshva_ige;
	wells_draw_list_item * m_wdli_hydro;

	DBTableKT(const char * tbnm);
	virtual ~DBTableKT();
	virtual void EnumCallBack(CRecordset * pRecordset);

};

#endif // !defined(AFX_DBTABLEKT_H__49CD9AC1_8D31_4147_92E1_722A52531081__INCLUDED_)

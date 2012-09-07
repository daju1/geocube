#include "stdafx.h"
#include "DBTable.h"




DBTable::DBTable(const char * tbnm)
{
	lab_doc = NULL;
	p_database = NULL;
	m_table_name = tbnm;
	m_pRecordset = NULL;
}

void DBTable::Init(CLabDoc * doc, CDatabase * database)
{
	lab_doc = doc;
	p_database = database;

}
DBTable::~DBTable()
{

}
void DBTable::Enum(CString where, CString order_by)
{
	EnumRecordset(where, order_by);
}
void DBTable::EnumRecordset(CString where, CString order_by)
{
	if (p_database)
	{	
		CString strQuery;
		strQuery.Format("select * from [%s]", m_table_name.GetBuffer(m_table_name.GetLength()));		

		m_pRecordset = new CRecordset(p_database);
		try {
			m_pRecordset->m_strFilter = where;
			m_pRecordset->m_strSort = order_by;
			m_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly);
		}
		catch (CDBException* pe) {
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return;
		}

		this->EnumItems(m_pRecordset);
		m_pRecordset->Close();
		delete m_pRecordset;
	}
}

void DBTable::EnumItems(CRecordset * pRecordset)
{		
	if (!pRecordset->IsBOF())
	{
		pRecordset->MoveFirst();
		while(!pRecordset->IsEOF()) {
			this->EnumCallBack(pRecordset);
			pRecordset->MoveNext(); // to validate record count
		}
	}
}
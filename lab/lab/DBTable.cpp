#include "stdafx.h"
#include "DBTable.h"
#include "logger/Logger.h"




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
   INFOFMT("DBTable::Enum() m_table_name=%s where = %s order_by = %s",
      % (const char *)m_table_name
      % (const char *)where
      % (const char *)order_by
      );
	EnumRecordset(where, order_by);
   INFOFMT("DBTable::Enum() end m_table_name=%s where = %s order_by = %s",
      % (const char *)m_table_name
      % (const char *)where
      % (const char *)order_by
      );
}
void DBTable::EnumRecordset(CString where, CString order_by)
{
	if (p_database)
	{	
		CString strQuery;
		strQuery.Format("select * from [%s]", m_table_name.GetBuffer(m_table_name.GetLength()));		
      INFOFMT("strQuery=%s",
         % (const char *)strQuery
         );

		m_pRecordset = new CRecordset(p_database);
		try {
			m_pRecordset->m_strFilter = where;
			m_pRecordset->m_strSort = order_by;
      INFO("pre m_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly)");
			m_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly);
		}
		catch (CDBException* pe) {
      INFOFMT("m_pRecordset->Open() catch (CDBException* pe) pe->m_strError = %s",
         % (const char *)pe->m_strError
         );
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return;
		}

      INFO("pre EnumItems");
		this->EnumItems(m_pRecordset);
      INFO("post EnumItems");
		m_pRecordset->Close();
      INFO("post m_pRecordset->Close()");
		delete m_pRecordset;
      INFO("post delete m_pRecordset");
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
#pragma once
class CLabDoc;
class DBTable
{

	CRecordset* m_pRecordset;
	CString m_table_name;		
protected:
	CDatabase * p_database;
	CLabDoc * lab_doc;

	void EnumRecordset(CString where, CString order_by);
	void EnumItems(CRecordset * pRecordset);
public:
	DBTable(const char * tbnm);
	void Init(CLabDoc * doc, CDatabase * db);
	~DBTable();

	void Enum(CString where, CString order_by);
	virtual void EnumCallBack(CRecordset * pRecordset) = 0;
};


// Authors.H : Declaration of the CAuthors class

#ifndef __AUTHORS_H_
#define __AUTHORS_H_

class CAuthorsAccessor
{
public:
	LONG m_AuID;
	TCHAR m_Author[51];
	SHORT m_YearBorn;

BEGIN_COLUMN_MAP(CAuthorsAccessor)
	COLUMN_ENTRY(1, m_AuID)
	COLUMN_ENTRY(2, m_Author)
	COLUMN_ENTRY(3, m_YearBorn)
END_COLUMN_MAP()


	// You may wish to call this function if you are inserting a record and wish to
	// initialize all the fields, if you are not going to explicitly set all of them.
	void ClearRecord()
	{
		memset(this, 0, sizeof(*this));
	}
};

class CAuthors : public CTable<CAccessor<CAuthorsAccessor> >
{
public:
	HRESULT Open()
	{
		HRESULT		hr;

		hr = OpenDataSource();
		if (FAILED(hr))
			return hr;

		return OpenRowset();
	}
	HRESULT OpenDataSource()
	{
		HRESULT		hr;
		CDataSource db;
		CDBPropSet	dbinit(DBPROPSET_DBINIT);

		dbinit.AddProperty(DBPROP_AUTH_CACHE_AUTHINFO, true);
		dbinit.AddProperty(DBPROP_AUTH_ENCRYPT_PASSWORD, false);
		dbinit.AddProperty(DBPROP_AUTH_MASK_PASSWORD, false);
		dbinit.AddProperty(DBPROP_AUTH_PASSWORD, OLESTR(""));
		dbinit.AddProperty(DBPROP_AUTH_PERSIST_ENCRYPTED, false);
		dbinit.AddProperty(DBPROP_AUTH_PERSIST_SENSITIVE_AUTHINFO, false);
		dbinit.AddProperty(DBPROP_AUTH_USERID, OLESTR("Admin"));
		dbinit.AddProperty(DBPROP_INIT_DATASOURCE, OLESTR("C:\\Biblio.mdb"));
		dbinit.AddProperty(DBPROP_INIT_MODE, (long)16);
		dbinit.AddProperty(DBPROP_INIT_PROMPT, (short)4);
		dbinit.AddProperty(DBPROP_INIT_PROVIDERSTRING, OLESTR(";COUNTRY=0;CP=1252;LANGID=0x0409"));
		dbinit.AddProperty(DBPROP_INIT_LCID, (long)1033);
		hr = db.Open(_T("Microsoft.Jet.OLEDB.3.51"), &dbinit);
		if (FAILED(hr))
			return hr;

		return m_session.Open(db);
	}
	HRESULT OpenRowset()
	{
		return CTable<CAccessor<CAuthorsAccessor> >::Open(m_session, _T("Authors"));
	}
	CSession	m_session;
};

#endif // __AUTHORS_H_

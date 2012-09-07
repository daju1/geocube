// Machine generated IDispatch wrapper class(es) created with ClassWizard
// AutoDriver.h
/////////////////////////////////////////////////////////////////////////////
// IEx25bAuto wrapper class

class IEx25bAuto : public COleDispatchDriver
{
public:
	IEx25bAuto() {}		// calls COleDispatchDriver default constructor
	IEx25bAuto(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IEx25bAuto(const IEx25bAuto& dispatchSrc) : 
	    COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	long GetLongData();
	void SetLongData(long);
	VARIANT GetTextData();
	void SetTextData(const VARIANT&);

// Operations
public:
	BOOL DisplayDialog();
};

// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IWorkBookConnect wrapper class

class IWorkBookConnect : public COleDispatchDriver
{
public:
	IWorkBookConnect() {}		// Calls COleDispatchDriver default constructor
	IWorkBookConnect(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IWorkBookConnect(const IWorkBookConnect& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void BindToEvents(LPDISPATCH workbook);
};

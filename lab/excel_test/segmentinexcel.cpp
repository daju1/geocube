// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "segmentinexcel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IWorkBookConnect properties

/////////////////////////////////////////////////////////////////////////////
// IWorkBookConnect operations

void IWorkBookConnect::BindToEvents(LPDISPATCH workbook)
{
	static BYTE parms[] =
		VTS_DISPATCH;
	InvokeHelper(0x60020000, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 workbook);
}

// Machine generated IDispatch wrapper class(es) created with ClassWizard
// AutoDriver.cpp

#include "stdafx.h"
#include "autoDriver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IEx25bAuto properties

long IEx25bAuto::GetLongData()
{
	long result;
	GetProperty(0x1, VT_I4, (void*)&result);
	return result;
}

void IEx25bAuto::SetLongData(long propVal)
{
	SetProperty(0x1, VT_I4, propVal);
}

VARIANT IEx25bAuto::GetTextData()
{
	VARIANT result;
	GetProperty(0x2, VT_VARIANT, (void*)&result);
	return result;
}

void IEx25bAuto::SetTextData(const VARIANT& propVal)
{
	SetProperty(0x2, VT_VARIANT, &propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IEx25bAuto operations

BOOL IEx25bAuto::DisplayDialog()
{
	BOOL result;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

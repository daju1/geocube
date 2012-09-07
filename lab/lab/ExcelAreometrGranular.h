// ExcelAreometrGranular.h: interface for the ExcelAreometrGranular class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AREOMETRGRANULAREXCEL_H__793BF4F5_C967_4D91_BB18_D12EDBD0461B__INCLUDED_)
#define AFX_AREOMETRGRANULAREXCEL_H__793BF4F5_C967_4D91_BB18_D12EDBD0461B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelAreometrGranular : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelAreometrGranular();
	virtual ~ExcelAreometrGranular();

};

#endif // !defined(AFX_AREOMETRGRANULAREXCEL_H__793BF4F5_C967_4D91_BB18_D12EDBD0461B__INCLUDED_)

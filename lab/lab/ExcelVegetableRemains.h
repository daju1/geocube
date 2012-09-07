// ExcelVegetableRemains.h: interface for the ExcelVegetableRemains class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VEGETABLEREMAINSEXCEL_H__F199518E_7AB3_4803_8F05_612B9055C7A6__INCLUDED_)
#define AFX_VEGETABLEREMAINSEXCEL_H__F199518E_7AB3_4803_8F05_612B9055C7A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelVegetableRemains : public BaseExcel  
{
	virtual bool virCompute(bool = false);
	virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelVegetableRemains();
	virtual ~ExcelVegetableRemains();

};

#endif // !defined(AFX_VEGETABLEREMAINSEXCEL_H__F199518E_7AB3_4803_8F05_612B9055C7A6__INCLUDED_)

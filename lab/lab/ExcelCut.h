// utExcel.h: interface for the ExcelCut class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTEXCEL_H__3275D3F6_08F6_429F_B08A_9C10BEBE39D2__INCLUDED_)
#define AFX_UTEXCEL_H__3275D3F6_08F6_429F_B08A_9C10BEBE39D2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "BaseExcel.h"

class ExcelCut : public BaseExcel  
{
	virtual bool virCompute(bool toSavetoDB);
	virtual bool virFill();
	//virtual void virSaveToDB();
	virtual void InitExt();
public:
	ExcelCut();
	virtual ~ExcelCut();

};

#endif // !defined(AFX_UTEXCEL_H__3275D3F6_08F6_429F_B08A_9C10BEBE39D2__INCLUDED_)

// Net.h: interface for the CNet class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NET_H__D3D17400_4350_4311_8DF0_A5D3E10B5604__INCLUDED_)
#define AFX_NET_H__D3D17400_4350_4311_8DF0_A5D3E10B5604__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"

// ------------------------------------------------------------
// CNet class
//
class CNet
{
protected:
	ulong		m_rang;
	CLayer**	m_layers;
	bool		m_layersOwner;

protected:
	virtual ulong alloc(ulong rang, bool bOwner = true);
	virtual void  free();

public:
	CNet();
	CNet(ulong rang, bool bOwner = true);
	virtual ~CNet();

	// rang
	ulong GetRang()
		{ return m_rang; };
	virtual ulong Init(ulong rang, bool bOwner = true);

	// layer
	CLayer* GetLayer(ulong n);
	ulong   SetLayer(ulong n, CLayer* layer);
	CLayer* GetLastLayer();
	CLayer* GetFirstLayer();

	// inputs
	void SetInputs(float* inputs);

	// propagate
	virtual void Propagate(void);

	//
	void  Randomize(float range, float dec = 0);
	void  RandInit(float * minimum, float * maximum);
	void  MidInit(float * minimum, float * maximum);
	void  BiasInit(float bias);


	// save/load
	virtual int Save(TCHAR* szFile);
	virtual int Load(TCHAR* szFile);
};

#endif // !defined(AFX_NET_H__D3D17400_4350_4311_8DF0_A5D3E10B5604__INCLUDED_)

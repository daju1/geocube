// NetKohonen.h: interface for the CNetKohonen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETKOHONEN_H__B2FEE858_5E87_4E45_A954_C26DCE943466__INCLUDED_)
#define AFX_NETKOHONEN_H__B2FEE858_5E87_4E45_A954_C26DCE943466__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LayerKohonen.h"
#include "Net.h"

// ------------------------------------------------------------
// CNetKohonen class
//
class CNetKohonen : public CNet
{
protected:
	float	m_learnRate;
	ulong	m_layerRang;

	float*	m_dist;

protected:
	virtual ulong alloc(ulong rang, bool bOwner = true);
	virtual ulong allocEx(ulong inputs, ulong layerRang);
	virtual void  free();

	virtual ulong Init(ulong rang, bool bOwner = true)
		{ return CNet::Init(rang, bOwner); };

public:
	CNetKohonen();
	CNetKohonen(ulong inputs, ulong layerRang);
	virtual ~CNetKohonen();

	// rang
	virtual ulong InitEx(ulong inputs, ulong layerRang);

	// learn rate
	float GetLearnRate()
		{ return m_learnRate; };
	void  SetLearnRate(float learnRate)
		{ m_learnRate = learnRate; };

	// gaussian distance
	float GetGaussianDistance(float cx, float cy, float wx, float wy);
	float GetGaussianDistance(int i, int j);

	// layer
	CLayerKohonen* GetLayer(ulong n)
		{ return (CLayerKohonen*) CNet::GetLayer(n); };

	// learn
	float LearnGaussian();
};

#endif // !defined(AFX_NETKOHONEN_H__B2FEE858_5E87_4E45_A954_C26DCE943466__INCLUDED_)

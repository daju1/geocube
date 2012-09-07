// LayerKohonen.h: interface for the CLayerKohonen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYERKOHONEN_H__27D788A1_C336_4DD5_8FA2_1520BBFA9038__INCLUDED_)
#define AFX_LAYERKOHONEN_H__27D788A1_C336_4DD5_8FA2_1520BBFA9038__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"
#include "NeuronKohonen.h"

class CNetKohonen;

// ------------------------------------------------------------
// CLayerBP class
//
class CLayerKohonen : public CLayer
{
friend CNetKohonen;

protected:
	int		m_dx;
	int		m_dy;

protected:
	virtual ulong alloc(ulong rang, bool bOwner = true);
	virtual ulong allocEx(ulong rang, ulong neuronsRang);

	virtual ulong Init(ulong rang, bool bOwner = true)
		{ return CLayer::Init(rang, bOwner); };

public:
	CLayerKohonen();
	CLayerKohonen(ulong rang, ulong neuronsRang);

	void Propagate();

	// rang
	virtual ulong InitEx(ulong rang, ulong neuronsRang);

	// neuron
	CNeuronKohonen* GetNeuron(ulong n)
		{ return (CNeuronKohonen*) CLayer::GetNeuron(n); };

	BOOL  SetDimension(int  dx, int  dy);
	void  GetDimension(int* dx, int* dy);

	ulong GetMinDistanceIndex();
	ulong GetMinEuclideanDistanceIndex();
	ulong GetMaxAxonIndex();
};

#endif // !defined(AFX_LAYERKOHONEN_H__27D788A1_C336_4DD5_8FA2_1520BBFA9038__INCLUDED_)

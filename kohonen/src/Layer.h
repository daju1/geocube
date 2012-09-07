// Layer.h: interface for the CLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYER_H__8B2E241F_DC5B_45A6_8BA5_38E9463E9744__INCLUDED_)
#define AFX_LAYER_H__8B2E241F_DC5B_45A6_8BA5_38E9463E9744__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Neuron.h"

class CNet;

// ------------------------------------------------------------
// CLayer class
//
class CLayer  
{
friend CNet;

protected:
	ulong		m_rang;
	CNeuron**	m_neurons;
	bool		m_neuronsOwner;

protected:
	virtual ulong alloc(ulong rang, bool bOwner = TRUE);
	virtual void  free();

public:
	CLayer();
	CLayer(ulong rang, bool bOwner = true);
	virtual ~CLayer();

	// rang
	ulong GetRang()
		{ return m_rang; };
	virtual ulong Init(ulong rang, bool bOwner = true);

	// neuron
	CNeuron* GetNeuron(ulong n);
	ulong    SetNeuron(ulong n, CNeuron* neuron);
	ulong    GetMaxAxonIndex();

	// inputs
	void SetInputs(float* inputs);

	// propagate
	virtual void Propagate(void);
	void CalcAxons();

	//
	void  Randomize(float range, float dec = 0);
	void  RandInit(float * minimum, float * maximum);
	void  MidInit(float * minimum, float * maximum);
	void  BiasInit(float bias);

	// debug
	virtual void TraceSynapses();
	virtual void TraceAxons();

};

#endif // !defined(AFX_LAYER_H__8B2E241F_DC5B_45A6_8BA5_38E9463E9744__INCLUDED_)

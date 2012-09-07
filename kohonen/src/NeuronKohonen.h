// NeuronKohonen.h: interface for the CNeuronKohonen class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEURONKOHONEN_H__D72658ED_B7C3_47B3_BED5_4BE0BDB75B99__INCLUDED_)
#define AFX_NEURONKOHONEN_H__D72658ED_B7C3_47B3_BED5_4BE0BDB75B99__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Neuron.h"

class CLayerKohonen;
class CNetKohonen;

// ------------------------------------------------------------
// CNeuronKohonen class
//
class CNeuronKohonen : public CNeuron
{
friend CLayerKohonen;
friend CNetKohonen;

public:
	CNeuronKohonen();
	CNeuronKohonen(ulong rang);

	float GetDistance();
	float GetEuclideanDistance();
	float m_axonKohonen;
	float CalcAxonKohonen()
		{ m_axonKohonen = m_bias - GetEuclideanDistance(); 
		  return m_axonKohonen;};
	float GetAxonKohonen()
		{ return m_axonKohonen; };
};

#endif // !defined(AFX_NEURONKOHONEN_H__D72658ED_B7C3_47B3_BED5_4BE0BDB75B99__INCLUDED_)

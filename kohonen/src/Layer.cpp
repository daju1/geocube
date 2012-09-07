// Layer.cpp: implementation of the CLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "stdafx.h"
#include "Layer.h"
#include "float.h"
/*
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Layer Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------
// CLayer constructor
//
CLayer::CLayer() : m_neurons(NULL), m_rang(0)
{
}

CLayer::CLayer(ulong rang, bool bOwner)
{
	alloc(rang, bOwner);
}



// ------------------------------------------------------------
// CLayer destructor
//
CLayer::~CLayer()
{
	free();
}



// ------------------------------------------------------------
// Allocate layer
//
ulong CLayer::alloc(ulong rang, bool bOwner)
{
	ulong	i;

	// alloc array for neurons
	m_neurons = new CNeuron* [rang];

	if (m_neurons)
	{
		for (i = 0; i < rang; i++)
			m_neurons[i] = NULL;

		m_rang			= rang;
		m_neuronsOwner	= bOwner;

		if (bOwner)
		{
			for (i = 0; i < rang; i++)
			{
				m_neurons[i] = new CNeuron;
			}
		}
		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Deallocate layer
//
void CLayer::free()
{
	ulong	i;

	if (m_neurons)
	{
		if (m_neuronsOwner)
			for (i = 0; i < m_rang; i++)
				delete m_neurons[i];

		delete [] m_neurons;

		m_neurons	= NULL;
		m_rang		= 0;
	}
}



// ------------------------------------------------------------
// Init layer: free old, alloc new
//
ulong CLayer::Init(ulong rang, bool bOwner)
{
	free();
	return alloc(rang, bOwner);
}



// ------------------------------------------------------------
// Get neuron
//
CNeuron* CLayer::GetNeuron(ulong n)
{
	if (n < m_rang)
		return m_neurons[n];

	return NULL;
}



// ------------------------------------------------------------
// Set neuron
//
ulong CLayer::SetNeuron(ulong n, CNeuron *neuron)
{
	if ((n < m_rang) && (!m_neuronsOwner))
	{
		m_neurons[n] = neuron;
		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Set inpus of the layer
//
void CLayer::SetInputs(float* inputs)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
	{
		m_neurons[i]->SetInputs(inputs);
	}
}



// ------------------------------------------------------------
// Get index of neuron with MAX axon
//
ulong CLayer::GetMaxAxonIndex()
{
	ulong	i, m = 0;
	float	f, max = FLT_MIN;

	for (i = 0; i < m_rang; i++)
	{
		f = m_neurons[i]->GetAxon();

		if (f > max)
		{
			max	= f;
			m	= i;
		}
	}
	return m;
}



// ------------------------------------------------------------
// propagate
//
void CLayer::Propagate()
{
	ulong	i;

	// propagate neurons
	for (i = 0; i < m_rang; i++)
	{
		if (m_neurons[i])
			m_neurons[i]->Propagate();
	}
	// calculate neurons axons
	for (i = 0; i < m_rang; i++)
	{
		if (m_neurons[i])
			m_neurons[i]->CalcAxon();
	}
}



// ------------------------------------------------------------
// randomize synapses
//
void CLayer::Randomize(float range, float dec)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_neurons[i]->Randomize(range, dec);
}

void CLayer::RandInit(float * minimum, float * maximum)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_neurons[i]->RandInit(minimum, maximum);

}

void CLayer::MidInit(float * minimum, float * maximum)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_neurons[i]->MidInit(minimum, maximum);
}

void CLayer::BiasInit(float bias)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_neurons[i]->BiasInit(bias);
}



// ------------------------------------------------------------
// --- D E B U G ----------------------------------------------
// ------------------------------------------------------------

// ------------------------------------------------------------
// Trace neurons synapses
//
void CLayer::TraceSynapses()
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		if (m_neurons[i])
		{
			TRACE(_T("neuron %d\n"), i);
			m_neurons[i]->TraceSynapses();
		}
}



// ------------------------------------------------------------
// Trace axon
//
void CLayer::TraceAxons()
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		if (m_neurons[i])
		{
			TRACE(_T("neuron %d\n"), i);
			m_neurons[i]->TraceAxon();
		}
}

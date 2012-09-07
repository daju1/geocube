// Neuron.cpp: implementation of the CNeuron class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "stdafx.h"
#include "Neuron.h"

#include <math.h>

/*#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
ulong CNeuron::s_typeDefault	= SIGMOID_HYPERTAN;
float CNeuron::s_stateFactor	= 1.0f;
float CNeuron::s_alfa			= 1.0f;		// 2.0f for SIGMOID_ALFA

//////////////////////////////////////////////////////////////////////
// Neuron Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------
// CNeuron constructor
//
CNeuron::CNeuron() : m_synapses(NULL), m_inputs(NULL), m_rang(0)
{
}

CNeuron::CNeuron(ulong rang) : m_synapses(NULL), m_inputs(NULL), m_rang(0)
{
	alloc(rang);
}



// ------------------------------------------------------------
// CNeuron destructor
//
CNeuron::~CNeuron()
{
	free();
}



// ------------------------------------------------------------
// Allocate neuron
//
ulong CNeuron::alloc(ulong rang)
{
	ulong	i;

	// alloc synapses
	m_synapses	= new float [rang];
	// alloc inputs
	m_inputs	= new float* [rang];

	if ((m_synapses != NULL) && (m_inputs != NULL))
	{
		for (i = 0; i < rang; i++)
		{
			m_synapses[i]	= 0;
			m_inputs[i]		= NULL;
		}

		m_rang = rang;
		m_type = s_typeDefault;

		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Deallocate neuron
//
void CNeuron::free()
{
	// delete synapses array
	if (m_synapses)
	{
		delete [] m_synapses;
		m_synapses = NULL;
	}
	// delete inputs array
	if (m_inputs)
	{
		delete [] m_inputs;
		m_inputs = NULL;
	}
	m_rang = 0;
}



// ------------------------------------------------------------
// Init neuron: free old, alloc new
//
ulong CNeuron::Init(ulong rang)
{
	free();
	return alloc(rang);
}



// ------------------------------------------------------------
// Get synapse
//
float CNeuron::GetSynapse(ulong n)
{
	return (n < m_rang) ? m_synapses[n] : 0;
}



// ------------------------------------------------------------
// Set synapse
//
void CNeuron::SetSynapse(ulong n, float synapse)
{
	if (n < m_rang)
		m_synapses[n] = synapse;
}



// ------------------------------------------------------------
// Set input
//
void CNeuron::SetInput(ulong n, float* input)
{
	if (n < m_rang)
		m_inputs[n] = input;
}



// ------------------------------------------------------------
// Set all inputs
//
void CNeuron::SetInputs(float* inputs)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_inputs[i] = &inputs[i];
}



// ------------------------------------------------------------
// Sigmoid 
//
float CNeuron::Sigmoid()
{
	switch (m_type)
	{
	case SIGMOID_ORIGINAL:
		return (float) (-0.5 + 1. / (1 + exp(-s_alfa * m_state)));

	case SIGMOID_HYPERTAN:
		return (float) (0.5 * tanh(s_alfa * m_state));

	default:
		return 0;
	}
}



// ------------------------------------------------------------
// derivative Sigmoid 
//
float CNeuron::dSigmoid()
{
	switch (m_type)
	{
	case SIGMOID_ORIGINAL:
		return (float) (s_alfa * (0.25 - m_axon * m_axon));

	case SIGMOID_HYPERTAN:
		return (float) (s_alfa * (1. - (m_axon * m_axon)));

	default:
		return 1;
	}
}



// ------------------------------------------------------------
// propagate
//
void CNeuron::Propagate()
{
	ulong	i;

	m_state = 0;

	for (i = 0; i < m_rang; i++)
		m_state += (*m_inputs[i]) * (m_synapses[i]);

	m_state *= s_stateFactor;
}



// ------------------------------------------------------------
// randomize synapses
//
void CNeuron::Randomize(float range, float dec)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_synapses[i] = (float) (range * ((float) rand() / RAND_MAX) - dec);

}

void CNeuron::RandInit(float * minimum, float * maximum)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_synapses[i] = minimum[i] + (float) ( (maximum[i]-minimum[i]) * ((float) rand() / RAND_MAX));

}

void CNeuron::MidInit(float * minimum, float * maximum)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_synapses[i] = 0.5 * (minimum[i] + maximum[i]);

}


// ------------------------------------------------------------
// --- D E B U G ----------------------------------------------
// ------------------------------------------------------------

// ------------------------------------------------------------
// Trace synapses
//
void CNeuron::TraceSynapses()
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		TRACE(_T("synapses %d - %g\n"), i, m_synapses[i]);
}



// ------------------------------------------------------------
// Trace axon
//
void CNeuron::TraceAxon()
{
	TRACE(_T("axon - %g\n"), m_axon);
}

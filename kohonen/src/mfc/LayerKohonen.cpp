// LayerKohonen.cpp: implementation of the CLayerKohonen class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "LayerKohonen.h"
#include "math.h"
#include "float.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// LayerKohonen Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------
// CLayerKohonen constructor
//
CLayerKohonen::CLayerKohonen()
{

}

CLayerKohonen::CLayerKohonen(ulong rang, ulong neuronsRang)
{
	allocEx(rang, neuronsRang);
}



// ------------------------------------------------------------
// Allocate layer
//
ulong CLayerKohonen::alloc(ulong rang, bool bOwner)
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
		m_dx			= rang;
		m_dy			= 1;

		if (bOwner)
		{
			for (i = 0; i < rang; i++)
			{
				m_neurons[i] = new CNeuronKohonen;
			}
		}
		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Allocate layer
//
ulong CLayerKohonen::allocEx(ulong rang, ulong neuronsRang)
{
	ulong	i, r;

	if ((r = alloc(rang, true)) == 0)
	{
		for (i = 0; i < rang; i++)
		{
			m_neurons[i]->Init(neuronsRang);
		}
	}
	return r;
}



// ------------------------------------------------------------
// Init layer: free old, alloc new
//
ulong CLayerKohonen::InitEx(ulong rang, ulong neuronsRang)
{
	free();
	return allocEx(rang, neuronsRang);
}



// ------------------------------------------------------------
// Set dimension
//
BOOL CLayerKohonen::SetDimension(int dx, int dy)
{
	if ((ulong) (dx * dy) == m_rang)
	{
		m_dx = dx;
		m_dy = dy;
		return TRUE;
	}
	return FALSE;
}



// ------------------------------------------------------------
// Get dimension
//
void CLayerKohonen::GetDimension(int* dx, int* dy)
{
	if (dx)
		*dx = m_dx;
	if (dy)
		*dy = m_dy;
}



// ------------------------------------------------------------
// Get index of neuron with MIN distance
//
ulong CLayerKohonen::GetMinDistanceIndex()
{
	ulong	i, m = 0;
	float	f, min = FLT_MAX;

	for (i = 0; i < m_rang; i++)
	{
		f = ((CNeuronKohonen*) m_neurons[i])->GetDistance();

		if (f < min)
		{
			min	= f;
			m	= i;
		}
	}
	return m;
}


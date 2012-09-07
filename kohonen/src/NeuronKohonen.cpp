// NeuronKohonen.cpp: implementation of the CNeuronKohonen class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "stdafx.h"
#include "NeuronKohonen.h"

#include <math.h>

/*#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/

//////////////////////////////////////////////////////////////////////
// NeuronKohonen Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------
// CNeuronKohonen constructor
//
CNeuronKohonen::CNeuronKohonen()
{
}

CNeuronKohonen::CNeuronKohonen(ulong rang) : CNeuron(rang)
{
}



// ------------------------------------------------------------
// count the distance
//
float CNeuronKohonen::GetDistance()
{
	ulong	i;
	float	s = 0.0f;

	for (i = 0; i < m_rang; i++)
		s += (float) fabs(*m_inputs[i] - m_synapses[i]);

	return s;
}
float CNeuronKohonen::GetEuclideanDistance()
{
	ulong	i;
	float	s = 0.0f;

	for (i = 0; i < m_rang; i++)
		s += (float) (*m_inputs[i] - m_synapses[i])*(*m_inputs[i] - m_synapses[i]);

	return sqrt(s);
}


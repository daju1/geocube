// NetKohonen.cpp: implementation of the CNetKohonen class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "stdafx.h"
#include "NetKohonen.h"
#include "../../array/src/matrixes.h"
#include <math.h>

/*#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/

//////////////////////////////////////////////////////////////////////
// NetKohonen Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------
// CNetKohonen constructor
//
CNetKohonen::CNetKohonen() : m_dist(NULL)
{

}

CNetKohonen::CNetKohonen(ulong inputs, ulong layerRang)
{
	allocEx(inputs, layerRang);
}



// ------------------------------------------------------------
// CNetKohonen constructor
//
CNetKohonen::~CNetKohonen()
{
	free();
}



// ------------------------------------------------------------
// Allocate net - construct only layers (for Load)
//
ulong CNetKohonen::alloc(ulong rang, bool bOwner)
{
	ulong	i;

	// alloc array for net
	m_layers = new CLayer* [rang];

	if (m_layers)
	{
		for (i = 0; i < rang; i++)
			m_layers[i] = NULL;

		m_rang			= rang;		// net rang
		m_layersOwner	= bOwner;
		m_learnRate		= 0.1f;		// default learn rate

		if (bOwner)
		{
			for (i = 0; i < rang; i++)
			{
				m_layers[i] = new CLayerKohonen;
			}
		}

		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Allocate net
//
ulong CNetKohonen::allocEx(ulong inputs, ulong layerRang)
{
	ulong	r;

	// alloc only one layer
	if ((r = alloc(1)) == 0)
	{
		m_layerRang = layerRang;

		// init first layer
		((CLayerKohonen*) m_layers[0])->InitEx(layerRang, inputs);

		// alloc memory for distances
		m_dist = new float[m_layerRang];

		float	da		= 3.14159f * 2.0f / (float) m_layerRang;
		float	alpha	= da;
		float	dx, dy;
		ulong	i;

		// first distance = 0
		m_dist[0] = 0.0f;

		// calc other distances
		for (i = 1; i < m_layerRang; i++)
		{
			dx = 0.5f * (float) cos(alpha) - 0.5f;
			dy = 0.5f * (float) sin(alpha);

			m_dist[i] = dx * dx + dy * dy;

			alpha += da;
		}
	}
	return r;
}



// ------------------------------------------------------------
// free
//
void CNetKohonen::free()
{
	if (m_dist)
	{
		delete [] m_dist;
		m_dist = NULL;
	}

	CNet::free();
}



// ------------------------------------------------------------
// Init net: free old, alloc new
//
ulong CNetKohonen::InitEx(ulong inputs, ulong layerRang)
{
	free();
	return allocEx(inputs, layerRang);
}



// ------------------------------------------------------------
// Get gaussian distance (i, k) = exp(-dist(i-k)^2 / 2 * lambda^2)
//    cx, cy - indexes of a neuron
//    wx, wy - indexes of a winner neuron
//
float CNetKohonen::GetGaussianDistance(float cx, float cy, float wx, float wy)
{
	float	dx = cx - wx;
	float	dy = cy - wy;
	float	di = dx * dx + dy * dy;		// (float) sqrt(dx * dx + dy * dy);

	if (m_learnRateDistance != 0.f)
		return (float) exp(-di / (2 * m_learnRateDistance * m_learnRateDistance));
	else
		return di == 0.f ? 1.f : 0.f;
}


float CNetKohonen::GetGaussianDistance(int i, int j)
{
	int		n = abs(i - j);
	float	di = m_dist[n];

	if (m_learnRateDistance != 0.f)
		return (float) exp(-di / (2 * m_learnRateDistance * m_learnRateDistance));
	else
		return di == 0.f ? 1.f : 0.f;
}



// ------------------------------------------------------------
// learn with gaussian
//
float CNetKohonen::LearnGaussian()
{
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	int				winner, dx, dy, x, y;
	float			g, d, ase = 0;
	float			nx, ny, cx, cy;

	ulong			i, k;

	// get first layer
	layer = (CLayerKohonen*) m_layers[0];

	// winner
	// winner = layer->GetMinDistanceIndex();
	winner = layer->GetMinEuclideanDistanceIndex();

	// dimension
	layer->GetDimension(&dx, &dy);

	if (dy != 1)
	{
		// Kohonen layer is a rectangle
		x = winner % dx;
		y = winner / dx;

		nx = (float) x / (float) dx;
		ny = (float) y / (float) dy;

		// walk through all neurons of the layer
		for (i = 0; i < layer->m_rang; i++)
		{
			neuron = layer->GetNeuron(i);

			cx	= (float) (i % dx) / (float) dx;
			cy	= (float) (i / dx) / (float) dy;
			g	= GetGaussianDistance(cx, cy, nx, ny);

			// walk throgh all synapses of the neuron
			for (k = 0; k < neuron->GetRang(); k++)
			{
				d = g * (*neuron->m_inputs[k] - neuron->m_synapses[k]);
				neuron->m_synapses[k] += m_learnRate * d;
				ase += d * d;
			}
		}
	}
	else
	{
		// walk through all neurons of the layer
		for (i = 0; i < layer->m_rang; i++)
		{
			neuron = layer->GetNeuron(i);

			g = GetGaussianDistance(winner, i);
			//printf ("g = %f i = %d\n", g,i);

			// walk throgh all synapses of the neuron
			for (k = 0; k < neuron->GetRang(); k++)
			{
				d = g * (*neuron->m_inputs[k] - neuron->m_synapses[k]);
				neuron->m_synapses[k] += m_learnRate * d;
				ase += d * d;
			}
		}
	}

	return ase;
}


float CNetKohonen::LearningGaussian(ulong nparam, ulong ncities, double ** points, bool add_noise)
{
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	int				winner, dx, dy, x, y;
	float			g, ase = 0;
	float			nx, ny, cx, cy;

	layer			= (CLayerKohonen*) m_layers[0];
	int				neurons	= layer->m_rang;

	ulong			I, i, j, k;
	float*			in = new float [nparam];
	double **		dw = AllocDoubleMat(neurons, nparam);
		
	float			noise		= 0.05f;

	for (i = 0; i < neurons; i++)
	{
		for ( j = 0; j < nparam; j++)
		{
			//memset(dw[j], 0, neurons );
			dw[i][j] = 0.0;
		}
	}

	// get first layer
	for (I = 0; I < ncities; I++)
	{
		for ( j = 0; j < nparam; j++)
		{
			in[j] = points[j][I];
			if (add_noise)
				in[j] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);
		}
		// set net inputs
		SetInputs(in);
		Propagate();

		// winner
		// winner = layer->GetMinDistanceIndex();
		winner = layer->GetMinEuclideanDistanceIndex();

		// dimension
		layer->GetDimension(&dx, &dy);

		if (dy != 1)
		{
			// Kohonen layer is a rectangle
			x = winner % dx;
			y = winner / dx;

			nx = (float) x / (float) dx;
			ny = (float) y / (float) dy;

			// walk through all neurons of the layer
			for (i = 0; i < layer->m_rang; i++)
			{
				neuron = layer->GetNeuron(i);

				cx	= (float) (i % dx) / (float) dx;
				cy	= (float) (i / dx) / (float) dy;
				g	= GetGaussianDistance(cx, cy, nx, ny);

				// walk throgh all synapses of the neuron
				for (k = 0; k < neuron->GetRang(); k++)
				{
					dw[i][k] += g * (*neuron->m_inputs[k] - neuron->m_synapses[k]);
				}
			}
		}
		else
		{
			// walk through all neurons of the layer
			for (i = 0; i < layer->m_rang; i++)
			{
				neuron = layer->GetNeuron(i);

				g = GetGaussianDistance(winner, i);

				// walk throgh all synapses of the neuron
				for (k = 0; k < neuron->GetRang(); k++)
				{
					dw[i][k] += g * (*neuron->m_inputs[k] - neuron->m_synapses[k]);
				}
			}
		}
	}
	for (i = 0; i < neurons; i++)
	{
		neuron = layer->GetNeuron(i);
		// walk throgh all synapses of the neuron
		for (k = 0; k < neuron->GetRang(); k++)
		{
			neuron->m_synapses[k] += m_learnRate * dw[i][k] / neurons;
			ase += dw[i][k] * dw[i][k];
		}
	}

	return ase;
}

int CNetKohonen::GetGaussianWinner()
{
	CLayerKohonen*	layer;
	int				winner;

	// get first layer
	layer = (CLayerKohonen*) m_layers[0];

	// winner
	winner = layer->GetMinDistanceIndex();

	return winner;
}
// ------------------------------------------------------------
// learn with conscience
//
float CNetKohonen::LearningConscience(ulong nparam, ulong ncities, double ** points, bool add_noise)
{
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	int				winner;
	float			ase = 0, a, b, db, c;
	layer = (CLayerKohonen*) m_layers[0];
	int				neurons	= layer->m_rang;

	ulong			i, j, k;
	float*			in = new float [nparam];
	double **		dw = AllocDoubleMat(neurons, nparam);
		
	float			noise		= 0.05f;


	for (i = 0; i < neurons; i++)
	{
		for ( j = 0; j < nparam; j++)
		{
			//memset(dw[j], 0, neurons );
			dw[i][j] = 0.0;
		}
	}

	// get first layer
	for (i = 0; i < ncities; i++)
	{
		for ( j = 0; j < nparam; j++)
		{
			in[j] = points[j][i];
			if (add_noise)
				in[j] += (((float) rand() / (float) RAND_MAX) * noise - noise / 2);
		}
		// set net inputs
		SetInputs(in);
		Propagate();

		// winner
		winner = layer->GetMaxAxonIndex();

		neuron = layer->GetNeuron(winner);

		// walk throgh all synapses of the neuron
		for (k = 0; k < neuron->GetRang(); k++)
		{
			dw[winner][k] += (*neuron->m_inputs[k] - neuron->m_synapses[k]);
		}
	}
	for (i = 0; i < neurons; i++)
	{
		neuron = layer->GetNeuron(i);
		// walk throgh all synapses of the neuron
		for (k = 0; k < neuron->GetRang(); k++)
		{
			neuron->m_synapses[k] += m_learnRate * dw[i][k] / neurons;
			ase += dw[i][k] * dw[i][k];
		}
	}

	// walk through all neurons of the layer
	for (i = 0; i < layer->m_rang; i++)
	{
		neuron = layer->GetNeuron(i);
		b = neuron->GetBias();
		a = neuron->GetAxonKohonen();
		// bias -> consciense
		c = exp(1.0 - log(b));
		// update consciense
		c = (1.0 - m_learnRateConscience) * c + m_learnRateConscience * a;
		// consciense -> db
		if (c > 0.0)
			db = exp(1.0 - log(c)) - b;
		else 
			db = 0.0;
		neuron->SetBias(b+db);
	}

	delete [] in;
	FreeDoubleMat(dw);
	return ase;
}
float CNetKohonen::LearnConscience()
{
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	int				winner;
	float			d, ase = 0, a, b, db, c;

	ulong			i, k;

	// get first layer
	layer = (CLayerKohonen*) m_layers[0];

	// winner
	winner = layer->GetMaxAxonIndex();

	neuron = layer->GetNeuron(winner);

	// walk throgh all synapses of the neuron
	for (k = 0; k < neuron->GetRang(); k++)
	{
		d = (*neuron->m_inputs[k] - neuron->m_synapses[k]);
		neuron->m_synapses[k] += m_learnRate * d;
		ase += d * d;
	}

	// walk through all neurons of the layer
	for (i = 0; i < layer->m_rang; i++)
	{
		neuron = layer->GetNeuron(i);
		b = neuron->GetBias();
		a = neuron->GetAxonKohonen();
		// bias -> consciense
		c = exp(1.0 - log(b));
		// update consciense
		c = (1.0 - m_learnRateConscience) * c + m_learnRateConscience * a;
		// consciense -> db
		if (c > 0.0)
			db = exp(1.0 - log(c)) - b;
		else 
			db = 0.0;
		neuron->SetBias(b+db);
	}

	return ase;
}

int CNetKohonen::GetConscienceWinner()
{
	CLayerKohonen*	layer;
	int				winner;

	// get first layer
	layer = (CLayerKohonen*) m_layers[0];

	// winner
	winner = layer->GetMaxAxonIndex();

	return winner;
}
// ------------------------------------------------------------
// learn with gaussian
//
float CNetKohonen::LearnGaussianConscience()
{
	CLayerKohonen*	layer;
	CNeuronKohonen*	neuron;
	int				winner, dx, dy, x, y;
	float			g, d, ase = 0;
	float			nx, ny, cx, cy;

	ulong			i, k;

	float			a, b, db, c;
	// get first layer
	layer = (CLayerKohonen*) m_layers[0];

	// winner
	// winner = layer->GetMinDistanceIndex();
	winner = layer->GetMaxAxonIndex();

	// dimension
	layer->GetDimension(&dx, &dy);

	if (dy != 1)
	{
		// Kohonen layer is a rectangle
		x = winner % dx;
		y = winner / dx;

		nx = (float) x / (float) dx;
		ny = (float) y / (float) dy;

		// walk through all neurons of the layer
		for (i = 0; i < layer->m_rang; i++)
		{
			neuron = layer->GetNeuron(i);

			cx	= (float) (i % dx) / (float) dx;
			cy	= (float) (i / dx) / (float) dy;
			g	= GetGaussianDistance(cx, cy, nx, ny);

			// walk throgh all synapses of the neuron
			for (k = 0; k < neuron->GetRang(); k++)
			{
				d = g * (*neuron->m_inputs[k] - neuron->m_synapses[k]);
				neuron->m_synapses[k] += m_learnRate * d;
				ase += d * d;
			}
		}
	}
	else
	{
		// walk through all neurons of the layer
		for (i = 0; i < layer->m_rang; i++)
		{
			neuron = layer->GetNeuron(i);

			g = GetGaussianDistance(winner, i);

			// walk throgh all synapses of the neuron
			for (k = 0; k < neuron->GetRang(); k++)
			{
				d = g * (*neuron->m_inputs[k] - neuron->m_synapses[k]);
				neuron->m_synapses[k] += m_learnRate * d;
				ase += d * d;
			}
		}
	}
	// walk through all neurons of the layer
	for (i = 0; i < layer->m_rang; i++)
	{
		neuron = layer->GetNeuron(i);
		b = neuron->GetBias();
		a = neuron->GetAxonKohonen();
		// bias -> consciense
		c = exp(1.0 - log(b));
		// update consciense
		c = (1.0 - m_learnRateConscience) * c + m_learnRateConscience * a;
		// consciense -> db
		if (c > 0.0)
			db = exp(1.0 - log(c)) - b;
		else 
			db = 0.0;
		neuron->SetBias(b+db);
	}

	return ase;
}

int CNetKohonen::GetGaussianConscienceWinner()
{
	CLayerKohonen*	layer;
	int				winner;

	// get first layer
	layer = (CLayerKohonen*) m_layers[0];

	// winner
	winner = layer->GetMaxAxonIndex();

	return winner;
}
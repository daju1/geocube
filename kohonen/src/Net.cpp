// Net.cpp: implementation of the CNet class.
//
//////////////////////////////////////////////////////////////////////

#include "../stdafx.h"
#include "stdafx.h"
#include "Net.h"

/*#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
*/
//////////////////////////////////////////////////////////////////////
// Net Class
//////////////////////////////////////////////////////////////////////

// ------------------------------------------------------------
// CNet constructor
//
CNet::CNet() : m_layers(NULL), m_rang(0)
{
}

CNet::CNet(ulong rang, bool bOwner)
{
	alloc(rang, bOwner);
}



// ------------------------------------------------------------
// CNet destructor
//
CNet::~CNet()
{
	free();
}



// ------------------------------------------------------------
// Allocate net
//
ulong CNet::alloc(ulong rang, bool bOwner)
{
	ulong	i;

	// alloc array for net
	m_layers = new CLayer* [rang];

	if (m_layers)
	{
		for (i = 0; i < rang; i++)
			m_layers[i] = NULL;

		m_rang			= rang;
		m_layersOwner	= bOwner;

		if (bOwner)
			for (i = 0; i < rang; i++)
			{
				m_layers[i] = new CLayer;
			}

		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Deallocate net
//
void CNet::free()
{
	ulong	i;

	if (m_layers)
	{
		if (m_layersOwner)
			for (i = 0; i < m_rang; i++)
				delete m_layers[i];

		delete [] m_layers;

		m_layers	= NULL;
		m_rang		= 0;
	}
}



// ------------------------------------------------------------
// Init net: free old, alloc new
//
ulong CNet::Init(ulong rang, bool bOwner)
{
	free();
	return alloc(rang, bOwner);
}



// ------------------------------------------------------------
// Get layer
//
CLayer* CNet::GetLayer(ulong n)
{
	return (n < m_rang) ? m_layers[n] : NULL;
}



// ------------------------------------------------------------
// Get last layer
//
CLayer* CNet::GetLastLayer()
{
	return (m_rang > 0) ? m_layers[m_rang - 1] : NULL;
}



// ------------------------------------------------------------
// Get first layer
//
CLayer* CNet::GetFirstLayer()
{
	return (m_rang > 0) ? m_layers[0] : NULL;
}



// ------------------------------------------------------------
// Set layer
//
ulong CNet::SetLayer(ulong n, CLayer *layer)
{
	if ((n < m_rang) && (!m_layersOwner))
	{
		m_layers[n] = layer;
		return 0;
	}
	return 1;
}



// ------------------------------------------------------------
// Set inputs of the net
//
void CNet::SetInputs(float* inputs)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
	{
		m_layers[i]->SetInputs(inputs);
	}
}



// ------------------------------------------------------------
// propagate
//
void CNet::Propagate()
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		if (m_layers[i])
			m_layers[i]->Propagate();
}



// ------------------------------------------------------------
// randomize synapses
//
void CNet::Randomize(float range, float dec)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_layers[i]->Randomize(range, dec);
}


void CNet::RandInit(float * minimum, float * maximum)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_layers[i]->RandInit(minimum, maximum);

}

void CNet::MidInit(float * minimum, float * maximum)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_layers[i]->MidInit(minimum, maximum);

}

void CNet::BiasInit(float bias)
{
	ulong	i;

	for (i = 0; i < m_rang; i++)
		m_layers[i]->BiasInit(bias);

}


// ------------------------------------------------------------
// save net to file
//
int CNet::Save(TCHAR* szFile)
{
	FILE*		fp;
	CLayer*		layer;
	CNeuron*	neuron;
	ulong		i, j, k;

	// open file
	if ((fp = _tfopen(szFile, _T("w"))) == NULL)
		return 1;

	// save net's rang
	_ftprintf(fp, _T("%u\n"), m_rang);

	// save all layers
	for (i = 0; i < m_rang; i++)
	{
		layer = m_layers[i];

		// save layer's rang
		_ftprintf(fp, _T("> %u\n"), layer->m_rang);

		// save all neurons
		for (j = 0; j < layer->m_rang; j++)
		{
			neuron = layer->m_neurons[j];

			// save neuron's rang
			_ftprintf(fp, _T(">> %u\n"), neuron->m_rang);

			// save all synapses
			for (k = 0; k < neuron->m_rang; k++)
				_ftprintf(fp, _T(">= %g\n"), neuron->m_synapses[k]);
		}
	}

	fclose(fp);

	return 0;
}



// ------------------------------------------------------------
// load net from file
//
int CNet::Load(TCHAR *szFile)
{
	FILE*			fp;
	CLayer*			layer;
	CNeuron*		neuron;
	unsigned		i, j, k;
	unsigned		netRang, layerRang, neuronRang;

	// open file
	if ((fp = _tfopen(szFile, _T("r"))) == NULL)
		return 1;

	// load net's rang
	_ftscanf(fp, _T("%u\n"), &netRang);

	// construct net
	Init(netRang);

	// load all layers
	for (i = 0; i < netRang; i++)
	{
		// load layer's rang
		_ftscanf(fp, _T("> %u\n"), &layerRang);

		layer = m_layers[i];
		layer->Init(layerRang);

		// load all neurons
		for (j = 0; j < layerRang; j++)
		{
			// load neurons's rang
			_ftscanf(fp, _T(">> %u\n"), &neuronRang);

			neuron = layer->m_neurons[j];
			neuron->Init(neuronRang);

			// load all synapses
			for (k = 0; k < neuronRang; k++)
			{
				_ftscanf(fp, _T(">= %f\n"), &(neuron->m_synapses[k]));
			}
		}
	}

	// close file
	fclose(fp);

	return 0;
}

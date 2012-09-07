// Neuron.h: interface for the CNeuro class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NEURON_H__7F547A3E_BBC4_4B0A_90E8_4D5F88FA54D1__INCLUDED_)
#define AFX_NEURON_H__7F547A3E_BBC4_4B0A_90E8_4D5F88FA54D1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned long	ulong;

// sigmoid types
#define SIGMOID_ORIGINAL	0
#define SIGMOID_HYPERTAN	1

class CNet;

// ------------------------------------------------------------
// CNeuron class
//
class CNeuron
{
friend CNet;

private:
	static ulong	s_typeDefault;
	static float	s_stateFactor;
	static float	s_alfa;

protected:
	ulong		m_type;
	ulong		m_rang;
	float		m_state;
	float		m_bias;
	float**		m_inputs;
	float*		m_synapses;

public:
	float		m_axon;

protected:
	virtual ulong alloc(ulong rang);
	virtual void  free();

public:
	CNeuron();
	CNeuron(ulong rang);
	virtual ~CNeuron();

	// default type
	static ulong GetDefaultType()
		{ return s_typeDefault; };
	static void  SetDefaultType(ulong type)
		{ s_typeDefault = type; };
	// state facor
	static float GetStateFactor()
		{ return s_stateFactor; };
	static void  SetStateFactor(float factor)
		{ s_stateFactor = factor; };
	// alfa
	static float GetAlfa()
		{ return s_alfa; };
	static void  SetAlfa(float alfa)
		{ s_alfa = alfa; };

	// type
	ulong GetType()
		{ return m_type; };
	ulong SetType(ulong type)
		{ m_type = type; };
	// rang
	ulong GetRang()
		{ return m_rang; };
	virtual ulong Init(ulong rang);

	// synapses
	float GetSynapse(ulong n);
	void  SetSynapse(ulong n, float synapse);

	// axon
	float GetAxon()
		{ return m_axon; };
	float GetBias()
		{ return m_bias; };
	void SetBias(float b)
		{ m_bias = b; };

	// inputs
	void SetInput(ulong n, float* input);
	void SetInputs(float* inputs);

	// sigmoid
	virtual float Sigmoid(void);
	virtual float dSigmoid(void);

	// propagate
	virtual void Propagate(void);
	void CalcAxon()
		{ m_axon = Sigmoid(); };

	//
	void Randomize(float range, float dec = 0);
	void RandInit(float * minimum, float * maximum);
	void MidInit(float * minimum, float * maximum);
	void BiasInit(float bias)
	{	m_bias = bias;	}


	// debug
	virtual void TraceSynapses();
	virtual void TraceAxon();
};

#endif // !defined(AFX_NEURON_H__7F547A3E_BBC4_4B0A_90E8_4D5F88FA54D1__INCLUDED_)

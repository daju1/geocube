#pragma once 

#include <windows.h>
#include "SoilDescriptionPtr.h"

#include <map>
#include <vector>
using namespace std;

class LabElement
{
public:
	enum type
	{
		undivided = 0,
		with_undefined_svyaznost,
		nesvyaznye,
		svyaznye
	};

	LabElement(LabElement::type tp);
	virtual ~LabElement();
	vector<SoilDescriptionPtr> vsdp;

	LabElement::type m_type;

	static const char * LabElementTypeToString(LabElement::type tp);

};

class LabElements
{
public:
	vector<LabElement> vle;
	
	void Init(vector<SoilDescription> & vsd);

};
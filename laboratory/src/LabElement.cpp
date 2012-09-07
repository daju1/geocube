
#include "LabElement.h"
#include "Lab.h"

LabElement::LabElement(LabElement::type tp)
{
	this->m_type = tp;
}
LabElement::~LabElement()
{
}
	
const char * LabElement::LabElementTypeToString(LabElement::type tp)
{
	switch(tp)
	{
	case LabElement::type::undivided:
		return "������������";
	case LabElement::type::with_undefined_svyaznost:
		return "� ������������� ����������";
	case LabElement::type::nesvyaznye:
		return "���������";
	case LabElement::type::svyaznye:
		return "�������";
	}
}

void LabElements::Init(vector<SoilDescription> & vsd)
{
	this->vle.clear();
	this->vle.push_back(LabElement(LabElement::type::undivided));

	for (vector<SoilDescription>::iterator it = vsd.begin();
		it != vsd.end(); it++)
	{
		this->vle.back().vsdp.push_back(SoilDescriptionPtr(&(*it)));
	}
}

#include "stdafx.h"
#include ".\layer.h"
#include ".\archive.h"

Layer::Layer(void)
{
	this->bChecked	= true;
	this->id		= -1;
	this->name		= "default layer";
}

Layer::Layer(int _id)
{
	this->bChecked	= true;
	this->id		= _id;
	this->name		= "";
}
Layer::Layer(int _id, string s)
{
	this->bChecked	= true;
	this->id		= _id;
	this->name		= s;
}

Layer::~Layer(void)
{

}

void Layer::SetName(string s)
{
	name = s.c_str();
}

Archive& operator <<(Archive& ar, Layer& layer)
{
	ar << layer.bChecked;
	ar << layer.id;
	ar << layer.name;
	return ar;
}

Archive& operator >>(Archive& ar, Layer& layer)
{
	ar >> layer.bChecked;
	ar >> layer.id;
	ar >> layer.name;
	return ar;
}
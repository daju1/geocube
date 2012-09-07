#pragma once

#include <string>
using namespace std ;

class Archive;

class Layer
{
	friend Archive& operator <<(Archive& ar, Layer& layer);
	friend Archive& operator >>(Archive& ar, Layer& layer);

	string name;
	int id;
public:
	bool bChecked;
	int GetID(){return id;}
	string GetName(){return name;}
	void SetName(string s);

	Layer(void);
	Layer(int _id);
	Layer(int _id, string s);

	virtual ~Layer(void);
};

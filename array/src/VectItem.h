// VectItem.h: interface for the CVectItem class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTITEM_H__56D40E3E_9B18_4C13_B123_2517F9725EFD__INCLUDED_)
#define AFX_VECTITEM_H__56D40E3E_9B18_4C13_B123_2517F9725EFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
//#include "raporto.h"

#if defined (_MSC_VER)
#include "../../surfdoc/src/Object.h"
#endif

template <class T> class vectItem
{
public:
	int GetIndex();
	vectItem<T> *	next;
	vectItem<T> *	pre;

	size_t			n;
	size_t			m_len;
	size_t index;

	T*			msg_data;


	vectItem(T* msg, size_t len, size_t _index)
	{
		this->m_len	= len;
		this->n		= len*sizeof(T);
		index = _index;

		this->msg_data = new T [len];

		if (this->msg_data)
		{
			for (size_t i = 0; i < len; i ++)
			{
				msg_data[i] = msg[i];//call operator= for overrided objects
			}
			this->next = NULL;
			this->pre  = NULL;

		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in vectItem", 0);
		}
	}

	vectItem(size_t len, size_t _index)
	{
		this->m_len	= len;
		this->n		= len*sizeof(T);
		index = _index;
		
		this->msg_data = new T [len];
		if (this->msg_data)
		{
			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in vectItem",0);
		}
	}

	~vectItem(void)
	{
		if(this->msg_data) delete [] (this->msg_data);
	}
};

#if defined (_MSC_VER)
#if 1
template <class T> class ObjectItem
{
public:
	int GetIndex();
	ObjectItem<T> *	next;
	ObjectItem<T> *	pre;

	size_t			n;
	size_t			m_len;
	Object::object_type ob_type;

	size_t index;

	T*			msg_data;// T = class Object
	//void*			msg_data;// T = class Object
	//T* operator->();

	ObjectItem(T* msg, size_t len, size_t _index)
	{
		this->m_len		= len;
		this->n			= len*sizeof(T);
		this->ob_type	= msg->GetObjectType();

		index = _index;

		//this->msg_data = reinterpret_cast<T*> (T::operator new[] (this->m_len, this->ob_type));
		this->msg_data = reinterpret_cast<T*> (T::operator new (sizeof(T),this->ob_type));
		if (this->msg_data)
		{
			/*for (size_t i = 0; i < len; i ++)
			{
				(reinterpret_cast<T*>(msg_data))[i] = msg[i];
			}*/

			*(reinterpret_cast<T*>(msg_data)) = *msg;


			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in ObjectItem", 0);
		}
	}

	ObjectItem(size_t len, size_t _index, Object::object_type type)
	{
		this->m_len		= len;
		this->n			= len*sizeof(T);
		this->ob_type	= type;

		index = _index;
		
		//this->msg_data = reinterpret_cast<T*> (T::operator new[] (this->m_len, this->ob_type));
		this->msg_data = reinterpret_cast<T*> (T::operator new (sizeof(T),this->ob_type));

		if (this->msg_data)
		{
			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in ObjectItem", 0);
		}
	}

	ObjectItem(size_t len, size_t _index)
	{
		this->m_len		= len;
		this->n			= len*sizeof(T);
		this->ob_type	= Object::object_type::undefined;

		index = _index;
		
		//this->msg_data = reinterpret_cast<T*> (T::operator new[] (this->m_len, this->ob_type));
		this->msg_data = reinterpret_cast<T*> (T::operator new (sizeof(T),this->ob_type));

		if (this->msg_data)
		{
			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in ObjectItem", 0);
		}
	}

	~ObjectItem(void)
	{
		/*for (size_t i = 0; i < this->m_len; i ++)
		{
			(reinterpret_cast<T*>(msg_data))[i].OnDestroy();
		}*/
		if(this->msg_data)
		{
			this->msg_data->SetLayer(NULL);
//#ifdef _DEBUG
//			HeapFree(GetProcessHeap(), 0, this->msg_data);
//#else
			T::operator delete (this->msg_data, this->ob_type);
			this->msg_data = NULL;
			//T::operator delete[] (this->msg_data, this->ob_type);
			//T::operator delete[] (dynamic_cast<void*>(this->msg_data), this->ob_type);
//#endif
		}
	}
};





#else
template <class T> class ObjectItem
{
public:
	int GetIndex();
	ObjectItem<T> *	next;
	ObjectItem<T> *	pre;

	size_t			n;
	size_t			m_len;
	Object::object_type ob_type;

	size_t index;

	T*			msg_data;// T = class Object
	//void*			msg_data;// T = class Object
	//T* operator->();

	ObjectItem(T* msg, size_t len, size_t _index)
	{
		this->m_len		= len;
		this->n			= len*sizeof(T);
		this->ob_type	= msg->GetObjectType();

		index = _index;

		this->msg_data = reinterpret_cast<T*> (T::operator new[] (this->m_len, this->ob_type));
		if (this->msg_data)
		{
			for (size_t i = 0; i < len; i ++)
			{
				(reinterpret_cast<T*>(msg_data))[i] = msg[i];
			}
			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in ObjectItem", 0);
		}
	}

	ObjectItem(size_t len, size_t _index, Object::object_type type)
	{
		this->m_len		= len;
		this->n			= len*sizeof(T);
		this->ob_type	= type;

		index = _index;
		
		this->msg_data = reinterpret_cast<T*> (T::operator new[] (this->m_len, this->ob_type));

		if (this->msg_data)
		{
			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in ObjectItem", 0);
		}
	}

	ObjectItem(size_t len, size_t _index)
	{
		this->m_len		= len;
		this->n			= len*sizeof(T);
		this->ob_type	= Object::object_type::undefined;

		index = _index;
		
		this->msg_data = reinterpret_cast<T*> (T::operator new[] (this->m_len, this->ob_type));

		if (this->msg_data)
		{
			this->next = NULL;
			this->pre  = NULL;
		}
		else
		{
			char str[255];
			sprintf(str, "size_t size = %d, int _index = %d", len*sizeof(T), _index);
			MessageBox(0, str, "Error of memory allocate in ObjectItem", 0);
		}
	}

	~ObjectItem(void)
	{
		/*for (size_t i = 0; i < this->m_len; i ++)
		{
			(reinterpret_cast<T*>(msg_data))[i].OnDestroy();
		}*/
		if(this->msg_data)
		{
//#ifdef _DEBUG
//			HeapFree(GetProcessHeap(), 0, this->msg_data);
//#else
			T::operator delete[] (this->msg_data, this->ob_type);
			//T::operator delete[] (reinterpret_cast<void*>(this->msg_data), this->ob_type);
//#endif
		}
	}
};


#endif
#endif
#endif // !defined(AFX_VECTITEM_H__56D40E3E_9B18_4C13_B123_2517F9725EFD__INCLUDED_)

//#include "stdafx.h"
//#include "VectItem.h"

#if !defined(_vect333_h)
#define _vect333_h

#include "VectItem.h"
//#include "raporto.h"
//#define WriteRaporto NULL
#define VECT_IN_TWO_FILES 0

/*
#ifdef COMMON_RAPORT
extern void WriteRaportoB(LPCTSTR s);
#else
extern void WriteRaportoA(LPCTSTR file, LPCTSTR s);
#endif
*/
class Archive;
#ifdef _MSC_VER
#define VECT_WITH_CRITICAL_SECTION 1
#else
#define VECT_WITH_CRITICAL_SECTION 0
#endif
template <class T, class VITEM = vectItem<T> > class vect
{
	bool created;
	//====== Данные класса 
#if VECT_WITH_CRITICAL_SECTION
	CRITICAL_SECTION CriticalSection;
#endif
	VITEM*	first;
	VITEM*	last;
	VITEM*	current;
	VITEM*	current_i;

	size_t count;		// Размер массива
	bool vectCheck;		// Флаг отметки
	long vectData;		// Данные, связанные с вектором

	int i_msg, i_vect;

	vect* first_vect;
	vect* last_vect;
	vect* current_vect;
	vect* current_vect_i;
	vect* pre_vect;
	vect* next_vect;

	size_t count_vect;		// Размер массива
	size_t index_vect;
	//====== Методы класса
public:
	vect()
	{
		created = false;
#if !VECT_WITH_CRITICAL_SECTION
		OnCreate(0);
#endif
	}
	void OnCreate(size_t _index_vect = 0)
	{
#if VECT_WITH_CRITICAL_SECTION
		if (!created)
			InitializeCriticalSection(&CriticalSection); 
#endif
		first			= NULL;
		last			= NULL;
		current			= NULL;
		current_i		= NULL;
		count			= 0;
		vectCheck		= true;
		vectData		= -1;

		first_vect		= NULL;
		last_vect		= NULL;
		current_vect	= NULL;
		current_vect_i	= NULL;
		count_vect		= 0;
		pre_vect		= NULL;
		next_vect		= NULL;
		index_vect		= _index_vect;
		i_msg			= 0;
		i_vect			= 0;

		created = true;

	}

	size_t AddMsg(T* msg)
	{
		size_t retCount;
		VITEM * pnew;
		VITEM * temp;
		size_t index = count;


#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif

		pnew = new VITEM(msg, 1, index);

		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}
		// Critical section
		if(this->first == NULL)
		{
			this->first				= pnew;
			this->current			= pnew;
			this->current_i			= pnew;
			this->last				= pnew;
		}
		else
		{
			if(this->last)
			{
				temp = this->last;
				this->last->next	= pnew;
				this->last			= this->last->next;//pnew
				this->last->pre		= temp;
			}
		}
		retCount = size_t(++count);

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
	size_t AddMsg(T* msg, size_t len)
	{
		size_t retCount;

		VITEM* pnew;
		VITEM* temp;
		size_t index = count;

#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		pnew = new VITEM(msg, len, index);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}
		// Critical section
		if(this->first == NULL)
		{
			this->first				= pnew;
			this->current			= pnew;
			this->current_i			= pnew;
			this->last				= pnew;
		}
		else
		{
			if(this->last)
			{
				temp = this->last;
				this->last->next	= pnew;
				this->last			= this->last->next;//pnew
				this->last->pre		= temp;
			}
		}
		retCount = size_t(++count);

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
	size_t AddMsg(size_t len)
	{
		size_t retCount;

		VITEM* pnew;
		VITEM* temp;
		size_t index = count;

#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		pnew = new VITEM(len, index);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}
		// Critical section
		if(this->first == NULL)
		{
			this->first				= pnew;
			this->current			= pnew;
			this->current_i			= pnew;
			this->last				= pnew;
		}
		else
		{
			if(this->last)
			{
				temp = this->last;
				this->last->next	= pnew;
				this->last			= this->last->next;//pnew
				this->last->pre		= temp;
			}
		}
		retCount = size_t(++count);

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
#if defined (_MSC_VER)
	size_t AddMsg(size_t len, Object::object_type ob_type)
	{
		size_t retCount;

		VITEM* pnew;
		VITEM* temp;
		size_t index = count;

#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		pnew = new VITEM(len, index, ob_type);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}
		// Critical section
		if(this->first == NULL)
		{
			this->first				= pnew;
			this->current			= pnew;
			this->current_i			= pnew;
			this->last				= pnew;
		}
		else
		{
			if(this->last)
			{
				temp = this->last;
				this->last->next	= pnew;
				this->last			= this->last->next;//pnew
				this->last->pre		= temp;
			}
		}
		retCount = size_t(++count);

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
#endif
	size_t CreateNewVect()
	{
		size_t retCount_vect;

		vect* pnew_vect;
		vect* temp_vect;
		size_t index_vect = count_vect;

#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif

		pnew_vect = new vect();
		if(!pnew_vect)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}
		pnew_vect->OnCreate(index_vect);

		// Critical section
		if(this->first_vect == NULL)
		{
			this->first_vect				= pnew_vect;
			this->current_vect				= pnew_vect;
			this->current_vect_i			= pnew_vect;
			this->last_vect					= pnew_vect;
		}
		else
		{
			if(this->last_vect)
			{
				temp_vect					= this->last_vect;
				this->last_vect->next_vect	= pnew_vect;
				this->last_vect				= this->last_vect->next_vect;
				this->last_vect->pre_vect	= temp_vect;
			}
		}
		retCount_vect = size_t(++count_vect);
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount_vect;
	}
	size_t AddMsgToLastVect(T * msg)
	{
		size_t retCount;


#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		if(!this->last_vect)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}

		VITEM* pnew;
		VITEM* temp;
		size_t index = this->last_vect->count;

		pnew = new VITEM(msg, 1, index);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}


		// Critical section
		if(this->last_vect->first == NULL)
		{
			this->last_vect->first				= pnew;
			this->last_vect->current			= pnew;
			this->last_vect->current_i			= pnew;
			this->last_vect->last				= pnew;
		}
		else
		{
			if(this->last_vect->last)
			{
				temp = this->last_vect->last;

				this->last_vect->last->next		= pnew;
				this->last_vect->last			= this->last_vect->last->next;

				this->last_vect->last->pre		= temp;
			}
		}
		retCount = size_t(++(this->last_vect->count));

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
	size_t AddMsgToLastVect(T * msg, size_t len)
	{
		size_t retCount;


#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif

		if(!this->last_vect)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}

		VITEM* pnew;
		VITEM* temp;
		size_t index = this->last_vect->count;

		pnew = new VITEM(msg, len, index);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}


		// Critical section
		if(this->last_vect->first == NULL)
		{
			this->last_vect->first				= pnew;
			this->last_vect->current			= pnew;
			this->last_vect->current_i			= pnew;
			this->last_vect->last				= pnew;
		}
		else
		{
			if(this->last_vect->last)
			{
				temp = this->last_vect->last;

				this->last_vect->last->next		= pnew;
				this->last_vect->last			= this->last_vect->last->next;

				this->last_vect->last->pre		= temp;
			}
		}
		retCount = size_t(++(this->last_vect->count));

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
	size_t AddMsgToLastVect(size_t len)
	{
		size_t retCount;


#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		if(!this->last_vect)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}

		VITEM* pnew;
		VITEM* temp;
		size_t index = this->last_vect->count;

		pnew = new VITEM(len, index);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}


		// Critical section
		if(this->last_vect->first == NULL)
		{
			this->last_vect->first				= pnew;
			this->last_vect->current			= pnew;
			this->last_vect->current_i			= pnew;
			this->last_vect->last				= pnew;
		}
		else
		{
			if(this->last_vect->last)
			{
				temp = this->last_vect->last;

				this->last_vect->last->next		= pnew;
				this->last_vect->last			= this->last_vect->last->next;

				this->last_vect->last->pre		= temp;
			}
		}
		retCount = size_t(++(this->last_vect->count));

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
	size_t AddMsgToIndexedVect(size_t i, T * msg)
	{
		size_t retCount;


#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif

		vect* pTemp;
		int index_vect = 0;
		current_vect = first_vect;

		while(current_vect && current_vect->next_vect && index_vect < i)
		{
			index_vect++;
			pTemp = current_vect->next_vect;
			if(pTemp)
				current_vect = pTemp;
			else
			{
#if VECT_WITH_CRITICAL_SECTION
				LeaveCriticalSection(&CriticalSection);
#endif
				return -1;
			}
		}

		if(!this->current_vect)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}

		VITEM* pnew;
		VITEM* temp;
		size_t index = this->current_vect->count;

		pnew = new VITEM(msg, 1, index);
		if(!pnew)
		{
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return -1;
		}


		// Critical section
		if(this->current_vect->first == NULL)
		{
			this->current_vect->first				= pnew;
			this->current_vect->current				= pnew;
			this->current_vect->current_i			= pnew;
			this->current_vect->last				= pnew;
		}
		else
		{
			if(this->current_vect->last)
			{
				temp = this->current_vect->last;

				this->current_vect->last->next		= pnew;
				this->current_vect->last			= this->current_vect->last->next;

				this->current_vect->last->pre		= temp;
			}
		}
		retCount = size_t(++(this->current_vect->count));

#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
 		return retCount;
	}
	size_t vectCheckedSize()
	{
		size_t g = 0;
		if (this->SetCurrentVectOnFirst())
		{
			do
			{
				if (this->GetCurrentVect().GetVectorCheck())
				{
					g++;
				}
			}
			// Перемещаем текущий внутренний вектор
			while(this->IncrementCurrentVect());
		}
		return g;
	}
	size_t vectSize()// Возвращает длину вектора
	{
		return count_vect;
	}  
	size_t msgSize()// Возвращает длину вектора
	{
		return count;
	}  
	~vect() 
	{	
		OnDestroy();
	}
	long GetVectorData()
	{
		return vectData;
	}
	void SetVectorData(long data)
	{
		vectData = data;
	}
	bool GetVectorCheck()
	{
		return vectCheck;
	}
	void SetVectorCheck(bool check)
	{
		vectCheck = check;
	}
	int GetCurrentMsgIndex()
	{
		if(current)
			return current->index;
		else
			return -1;
	}
	int GetCurrentVectIndex()
	{
		if(current_vect)
			return current_vect->index_vect;
		else
			return -1;
	}
	T& GetPreCurrentMsg()
	{
		if (current && current->pre)
			return *(reinterpret_cast<T*>(current->pre->msg_data));
		else
		{
			MessageBox(0,"!current->pre","GetPreCurrentMsg",0);
			return *(reinterpret_cast<T*>(current->pre->msg_data));
		}
	}
	T& GetCurrentMsg()
	{
		return *(reinterpret_cast<T*>(current->msg_data));
	}
	size_t GetCurrentMsgLen() const 
	{
		if (current)
			return (current->m_len);
		else
			return 0;
	}
	T* GetCurrentMsgPtr() const 
	{
		return reinterpret_cast<T*>(current->msg_data);
	}
	void SetCurrentMsg(T* msg)
	{
		if (current)
		{
			for (size_t i = 0; i < current->m_len; i ++)
			{
				current->msg_data[i] = msg[i];
			}
		}
	}
	T& GetNextCurrentMsg()
	{
		if (current && current->next && current->next->msg_data)
			return *(reinterpret_cast<T*>(current->next->msg_data));
		else
		{
			MessageBox(0,"!current->next","GetNextCurrentMsg",0);
			return *(reinterpret_cast<T*>(current->next->msg_data));
		}
	}
	T& GetFirstMsg()
	{
		if (first && first->msg_data)
			return *(reinterpret_cast<T*>(first->msg_data));
		else
		{
			MessageBox(0,"!first && first->msg_data","GetFirstMsg",0);
			return *(reinterpret_cast<T*>(first->msg_data));
		}
	}
	T& GetSecondMsg()
	{
		if (first && first->next && first->next->msg_data)
			return *(reinterpret_cast<T*>(first->next->msg_data));
		else
		{
			MessageBox(0,"!first->next","GetSecondMsg",0);
			return *(reinterpret_cast<T*>(first->next->msg_data));
		}
	}
	T& GetPreLastMsg()
	{
		if (last && last->pre && last->pre->msg_data)
			return *(reinterpret_cast<T*>(last->pre->msg_data));
		else
		{
			MessageBox(0,"!last->pre","GetPreLastMsg",0);
			return *(reinterpret_cast<T*>(last->pre->msg_data));
		}
	}
	T& GetLastMsg()
	{
		if (last && last->msg_data)
			return *(reinterpret_cast<T*>(last->msg_data));
		else
		{
			MessageBox(0,"!last && last->msg_data","GetLastMsg",0);
			return *(reinterpret_cast<T*>(last->msg_data));
		}
	}
	T* GetLastMsgPtr()
	{
		return (reinterpret_cast<T*>(last->msg_data));
	}
	vect& GetCurrentVect() 
	{
//WriteRaporto("GetCurrentVect()\n");
		return *current_vect;
	}
	vect& GetFirstVect()
	{
		return *first_vect;
	}
	vect& GetLastVect() 
	{
		return *last_vect;
	}
#if 0
	T* operator [](int i) 
	{ 
#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		CVectItem* pTemp;
		if(i_msg < i)
		{
			while(current_i && current_i->next && i_msg < i)
			{
				i_msg++;
				pTemp = current_i->next;
				if(pTemp)
					current_i = pTemp;
			}
		}
		else
		{
			if (i_msg > i)
			{
				while(current_i && current_i->pre && i_msg > i)
				{
					i_msg--;
					pTemp = current_i->pre;
					if(pTemp)
						current_i = pTemp;
				}
			}
		}
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
		return (T*)(current_i->msg_data); 
	}
	vect* operator ()(int i) 
	{ 
#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		vect* pTemp;
		//int index = 0;
		//current_vect = first_vect;
		if(i_vect < i)
		{
			while(current_vect_i && current_vect_i->next_vect && i_vect < i)
			{
				i_vect++;
				pTemp = current_vect_i->next_vect;
				if(pTemp)
					current_vect_i = pTemp;
			}
		}
		else
		{
			if(i_vect > i)
			{
				while(current_vect_i && current_vect_i->pre_vect && i_vect > i)
				{
					i_vect--;
					pTemp = current_vect_i->pre_vect;
					if(pTemp)
						current_vect_i = pTemp;
				}
			}
		}
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
		return current_vect; 
	}
#else
	T* operator [](int i) 
	{ 
#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		VITEM* pTemp;
		int index = 0;
		current = first;

		while(current && current->next && index < i)
		{
			index++;
			pTemp = current->next;
			if(pTemp)
				current = pTemp;
		}
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
		return (T*)(current->msg_data); 
	}
	vect* operator ()(int i) 
	{ 
#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		vect* pTemp;
		int index = 0;
		current_vect = first_vect;

		while(current_vect && current_vect->next_vect && index < i)
		{
			index++;
			pTemp = current_vect->next_vect;
			if(pTemp)
				current_vect = pTemp;
		}
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
		return current_vect; 
	}
#endif
	bool SetCurrentMsgOnLast()
	{
		if( (this->last == NULL) )
		{
			current = NULL;
			return false;
		}
		else
		{
			current=last;
			if (current->msg_data == NULL)
			{
				return false;
			}
			return true;
		}
	}
	bool SetCurrentMsgOnFirst()
	{
		if( this->first == NULL )
		{
			current = NULL;
			return false;
		}
		else
		{
			current=first;
			if (current->msg_data == NULL)
			{
				return false;
			}
			return true;
		}
	}
	bool SetCurrentVectOnFirst()
	{
		if( this->first_vect == NULL )
		{
			current_vect = NULL;
			return false;
		}
		else
		{
			this->current_vect=this->first_vect;
			return true;
		}
	}
	bool DecrementCurrentMsg() 
	{
		if (this->current && this->current->pre)
		{
			this->current = this->current->pre;
			return true;
		}
		return false;
	}
	bool IncrementCurrentMsg() 
	{
		if (this->current && this->current->next)
		{
			this->current = this->current->next;
			return true;
		}
		return false;
	}
	bool IncrementCurrentVect(bool toSetOnfirstBeforeIncrement = true) 
	{
		if (this->current_vect)
		{
			if(toSetOnfirstBeforeIncrement)
			{
				this->current_vect->SetCurrentMsgOnFirst();
				this->current_vect->SetCurrentVectOnFirst();
			}

			if( this->current_vect->next_vect == NULL )
			{
				return false;
			}
			else
			{
				this->current_vect=this->current_vect->next_vect;
				return true;
			}
		}
		else
			return false;
	}
	bool CopyCurrentMsgToLast(T *dest)
	{
		if( (this->current == NULL) )
		{
			current=NULL;
			ZeroMemory(dest, sizeof(T));
			return false;
		}
		else
		{
			CopyMemory(dest, this->current->msg_data, sizeof(T));
			this->current=this->current->next;
			return true;
		}
	}
	bool CopyCurrentVectMsgToLast(T *dest)
	{
		if( (this->current_vect == NULL) )
		{
			return false;
		}
		else
		{
			if( (this->current_vect->current == NULL) )
			{
				ZeroMemory(dest, sizeof(T));
				return false;
			}
			else
			{
				CopyMemory(dest, this->current_vect->current->msg_data, sizeof(T));
				this->current_vect->current = this->current_vect->current->next;
				return true;
			}
		}
	}
	bool CopyFirstMsgWithDelete(T *dest)
	{
		if( (this->first == NULL) )
		{
			current=NULL;
			current_i=NULL;
			ZeroMemory(dest, sizeof(T));
			return false;
		}
		else
		{
			CopyMemory(dest, this->first->msg_data, sizeof(T));
			current=first;
			current_i=first;
			i_msg = 0;
			this->Delete();
			return true;
		}
	}
	bool emptyMsg()
	{
		return count == 0 ? true : false;
	}
	bool emptyVect()
	{
		return count_vect == 0 ? true : false;
	}
	bool EraseFirstMsg()
	{
		return Delete();
	}
	bool EraseLastMsg()
	{
		VITEM*	pold;
		VITEM*	pold_pre;

		if(this->last == NULL) return false;

		pold = this->last;
		pold_pre = this->last->pre;
		
		if(pold_pre)
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			this->last = pold_pre;
			this->last->next = NULL;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
		}
		else
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			this->last  = NULL;
			this->first = NULL;
			this->current = NULL;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return false;
		}

		return true;
	}
	bool EraseCurrentMsg()
	{
		VITEM*	pold;
		VITEM*	pold_pre;
		VITEM*	pold_next;

		if(this->current == NULL) return false;

		pold = this->current;
		pold_pre = this->current->pre;
		pold_next = this->current->next;
		if(pold_pre && pold_next)
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			pold_pre->next = pold_next;
			pold_next->pre = pold_pre;
			this->current = pold_next;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return true;
		}

		if(pold_pre && pold_next == NULL)
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			pold_pre->next = pold_next;
			this->current = NULL;
			this->last = pold_pre;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return false;
		}

		if(pold_pre == NULL && pold_next == NULL)
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			this->current = NULL;
			this->first = NULL;
			this->last = NULL;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return false;
		}

		if(pold_pre == NULL && pold_next)
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			pold_next->pre = NULL;
			this->current = pold_next;
			this->first = pold_next;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return true;
		}

		return false;
	}
	bool CheckCurrentMsg()
	{
		return current != NULL && current->msg_data != NULL;
	}
	bool Delete()
	{
		VITEM*	pold;

		if(this->first == NULL) return false;

		pold = this->first;
		
		if(this->ReadNext(this->first))
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->count--;
			if (pold) delete pold;
			this->first->pre = NULL;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
		}
		else
		{
#if VECT_WITH_CRITICAL_SECTION
			EnterCriticalSection(&CriticalSection);
#endif
			this->first = NULL;
			this->current = NULL;
			this->current_i = NULL;
			this->last  = NULL;
			this->count--;

			if (pold) delete pold;
			this->first->pre = NULL;
#if VECT_WITH_CRITICAL_SECTION
			LeaveCriticalSection(&CriticalSection);
#endif
			return false;
		}

		return true;
	}
	bool ReadNext(VITEM* & _current)
	{
		if(_current == NULL)
		{
			current = NULL;
			current_i = NULL;
			return false;
		}

		if(_current->next)
		{
			_current = _current->next;
			current = _current;
			//current_i = _current;

			return true;
		}

		return false;
	}
	bool ReadNextVect(vect* & _current_vect)
	{
		if(_current_vect == NULL)
		{
			current_vect = NULL;
			current_vect_i = NULL;
			return false;
		}

		if(_current_vect->next_vect)
		{
			_current_vect = _current_vect->next_vect;
			current_vect = _current_vect;
			//current_vect_i = _current_vect;
			return true;
		}
		return false;
	}
	void clearMsg()
	{
#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		VITEM*	pold;

		while(this->first != NULL) 
		{
			pold = this->first;
			
			if(this->ReadNext(this->first))
			{
				this->count--;
			}
			else
			{
				this->first		= NULL;
				this->current	= NULL;
				this->current_i	= NULL;
				this->last		= NULL;
				this->count--;
			}
			if (pold)
			{
				delete pold;
			}
		}
		this->first		= NULL;
		this->current	= NULL;
		this->current_i	= NULL;
		this->last		= NULL;

		//this->max_count	= 1000;
		this->count		= 0;
		//this->start		= FALSE;
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
	}
	void clear()
	{
		clearVect();
		clearMsg();
	}
	void clearVect()
	{
#if VECT_WITH_CRITICAL_SECTION
		EnterCriticalSection(&CriticalSection);
#endif
		vect*	pold_vect;


		while(this->first_vect != NULL) 
		{
			pold_vect = this->first_vect;
			
			if(this->ReadNextVect(this->first_vect))
			{
				this->count_vect--;
			}
			else
			{
				this->first_vect	= NULL;
				this->current_vect	= NULL;
				this->current_vect_i= NULL;
				this->last_vect		= NULL;
				this->count_vect--;
			}
			if (pold_vect)
			{
				pold_vect->clearMsg();
				pold_vect->clearVect();
				delete pold_vect;
			}
		}
		this->first_vect	= NULL;
		this->current_vect	= NULL;
		this->current_vect_i= NULL;
		this->last_vect		= NULL;

		//this->max_count	= 1000;
		this->count_vect		= 0;
		//this->start		= FALSE;
#if VECT_WITH_CRITICAL_SECTION
		LeaveCriticalSection(&CriticalSection);
#endif
	}
	void OnDestroy()
	{
		clear();
		// Release resources used by the critical section object.
#if VECT_WITH_CRITICAL_SECTION
		DeleteCriticalSection(&CriticalSection);
#endif
		created = false;
	}
	void Init(vect& ob) 
	{
		this->OnCreate();
		this->clear();
		if (ob.SetCurrentMsgOnFirst())
		{
			do
			{
				size_t len = ob.GetCurrentMsgLen();
				T* ptr = ob.GetCurrentMsgPtr();
				this->AddMsg(len);
				T* pt2 = this->GetLastMsgPtr();
				for( size_t i = 0; i < len; i++)
				{
					pt2[i] = ptr[i]; // вызов перегруженных операторов= для вложенных объектов T
				}
			}
			while(ob.IncrementCurrentMsg());
		}
		if ( ob.SetCurrentVectOnFirst())
		{
			do
			{
				this->CreateNewVect();
				this->GetLastVect().Init(ob.GetCurrentVect());
			}
			while (ob.IncrementCurrentVect());
		}
	}

	vect(const vect& ob)
	{
		this->Init((vect&)ob);
	}

	vect& operator=(const vect& ob)
	{
		if (this == &ob)
			return *this;

		this->Init((vect&)ob);

		return *this;
	}
};

template <class T> Archive& operator <<(Archive& ar, vect<T, vectItem<T> >& v)
{
//printf("Archive& operator <<(Archive& ar, vect<T, vectItem<T> >& v)\n");
	// метка старта вектора заносим в архив
	DWORD start_of_vector	= 0xabcd1234;

	ar << start_of_vector;
	// заносим в архив число элементов вектора
	ar << v.msgSize();
	// и если наш вектор не пуст
	if ( v.SetCurrentMsgOnFirst())
	{
		// то для каждого элемента вектора
		do
		{
			T* ptr = v.GetCurrentMsgPtr();
			size_t len = v.GetCurrentMsgLen();
			// заносим в архив длину каждого элемента вектора
			ar << len;
			// а затем в цикле
			for(size_t i = 0; i < len; i++)
			{
				// заносим каждый объект из текущего элемента вектора				
				ar << ptr[i];
			}
		}
		while(v.IncrementCurrentMsg());
	}
	// теперь заносим в архив число вложенных векторов
	ar << v.vectSize();
	// и если вложенные вектора существуют
	if (v.SetCurrentVectOnFirst())
	{
		// то для каждого вложенного вектора
		do
		{
			// рекурсивно вызываем (этот же) оператор сохранения в архив
			ar << v.GetCurrentVect();
		}
		while(v.IncrementCurrentVect());
	}
	// метка конца вектора
	DWORD end_of_vector		= 0x4321dcba;
	ar << end_of_vector;
	return ar;
}
template <class T> Archive& operator >>(Archive& ar, vect<T, vectItem<T> >& v)
{
//printf("Archive& operator >>(Archive& ar, vect<T, vectItem<T> >& v)\n");
	// метка старта вектора
	DWORD start_of_vector;
	ar >> start_of_vector;
	if (start_of_vector	!= 0xabcd1234)
	{
		printf("Error of reading of start of vect from archive:\nstart_of_vector(%x) != 0xabcd1234", start_of_vector);
		throw "Error of reading of start of vect from archive";
	}
	// очищаем вектор если это не импорт
	if(!Archive::OpenFileAsImport)
		v.clear();
	// число элементов вектора
	size_t msgSize;
	ar >> msgSize;
	for (size_t i = 0; i < msgSize; i++)
	{
		// для каждого элемента вектора
		size_t len;
		// длину каждого элемента вектора
		ar >> len;
		v.AddMsg(len);
		T* ptr = v.GetLastMsgPtr();
		// а затем в цикле
		for(size_t i = 0; i < len; i++)
		{
			// каждый объект из текущего элемента вектора				
			ar >> ptr[i];
		}
	}
	// число вложенных векторов
	size_t vectSize;
	ar >> vectSize;
	for (size_t j = 0; j < vectSize; j++)
	{
		v.CreateNewVect();
		// рекурсивно вызываем (этот же) оператор сохранения в архив
		ar >> v.GetLastVect();
	}
	// метка конца вектора
	DWORD end_of_vector		= 0x4321dcba;
	ar >> end_of_vector;
	if (end_of_vector != 0x4321dcba)
	{
		printf("Error of reading of end of vect from archive:\nend_of_vector(%x) != 0x4321dcba", start_of_vector);
		throw "Error of reading of end of vect from archive";
	}
	//printf("Archive& operator >>(Archive& ar, vect<T, VITEM>& v) end\n");
	return ar;

}
#if defined (_MSC_VER)
template <class T> Archive& operator <<(Archive& ar, vect<T, ObjectItem<T> >& v)
{
//printf("Archive& operator <<(Archive& ar, vect<T, ObjectItem<T> >& v)\n");
	// метка старта вектора заносим в архив
	DWORD start_of_vector	= 0xabcd1234;

	ar << start_of_vector;
	// заносим в архив число элементов вектора
	ar << v.msgSize();
	// и если наш вектор не пуст
	if ( v.SetCurrentMsgOnFirst())
	{
		// то для каждого элемента вектора
		do
		{
			T* ptr = v.GetCurrentMsgPtr();
			size_t len = v.GetCurrentMsgLen();
			// заносим в архив длину каждого элемента вектора
			ar << len;

			Object::object_type type = ptr->GetObjectType();
			int ob_type = type;
			ar << ob_type;

			// а затем в цикле
			for(size_t i = 0; i < len; i++)
			{
				// заносим каждый объект из текущего элемента вектора				
				ar << ptr[i];
			}
		}
		while(v.IncrementCurrentMsg());
	}
	// теперь заносим в архив число вложенных векторов
	ar << v.vectSize();
	// и если вложенные вектора существуют
	if (v.SetCurrentVectOnFirst())
	{
		// то для каждого вложенного вектора
		do
		{
			// рекурсивно вызываем (этот же) оператор сохранения в архив
			ar << v.GetCurrentVect();
		}
		while(v.IncrementCurrentVect());
	}
	// метка конца вектора
	DWORD end_of_vector		= 0x4321dcba;
	ar << end_of_vector;
	return ar;
}
template <class T> Archive& operator >>(Archive& ar, vect<T, ObjectItem<T> >& v)
{
//printf("Archive& operator >>(Archive& ar, vect<T, ObjectItem<T> >& v)\n");
	// метка старта вектора
	DWORD start_of_vector;
	ar >> start_of_vector;
	if (start_of_vector	!= 0xabcd1234)
	{
		printf("Error of reading of start of vect from archive:\nstart_of_vector(%x) != 0xabcd1234", start_of_vector);
		throw "Error of reading of start of vect from archive";
	}
	// очищаем вектор если это не импорт
	if(!Archive::OpenFileAsImport)
		v.clear();
	// число элементов вектора
	size_t msgSize;
	ar >> msgSize;
	for (size_t i = 0; i < msgSize; i++)
	{
		// для каждого элемента вектора
		size_t len;
		// длину каждого элемента вектора
		ar >> len;

		Object::object_type type;
		int ob_type;
		ar >> ob_type;
		type = (Object::object_type)ob_type ;


		v.AddMsg(len, type);
		T* ptr = v.GetLastMsgPtr();
		// а затем в цикле
		for(size_t i = 0; i < len; i++)
		{
			// каждый объект из текущего элемента вектора				
			ar >> ptr[i];
		}
	}
	// число вложенных векторов
	size_t vectSize;
	ar >> vectSize;
	for (size_t j = 0; j < vectSize; j++)
	{
		v.CreateNewVect();
		// рекурсивно вызываем (этот же) оператор сохранения в архив
		ar >> v.GetLastVect();
	}
	// метка конца вектора
	DWORD end_of_vector		= 0x4321dcba;
	ar >> end_of_vector;
	if (end_of_vector != 0x4321dcba)
	{
		printf("Error of reading of end of vect from archive:\nend_of_vector(%x) != 0x4321dcba", start_of_vector);
		throw "Error of reading of end of vect from archive";
	}
	//printf("Archive& operator >>(Archive& ar, vect<T, VITEM>& v) end\n");
	return ar;

}
#endif

#endif

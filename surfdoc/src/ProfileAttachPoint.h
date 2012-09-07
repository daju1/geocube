#ifndef _PROFILE_ATTACH_POINT__H_
#define _PROFILE_ATTACH_POINT__H_
//ProfileAttachPoint.h
struct ProfileAttachPoint	// точка привязки профиля к карте
							// массив таких точек привязки 
							// необходим для функции перевода
							// горизонтальной координаты профиля xProfile
							// в координаты карты xMap yMap
{
	double 
		xMap, 
		yMap, 
		xProfile;
	bool 
		bAttached;		// флаг привязки горизонтальной координаты профиля
};

#endif /*_PROFILE_ATTACH_POINT__H_*/
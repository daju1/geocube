#ifndef _PROFILE_ATTACH_POINT__H_
#define _PROFILE_ATTACH_POINT__H_
//ProfileAttachPoint.h
struct ProfileAttachPoint	// ����� �������� ������� � �����
							// ������ ����� ����� �������� 
							// ��������� ��� ������� ��������
							// �������������� ���������� ������� xProfile
							// � ���������� ����� xMap yMap
{
	double 
		xMap, 
		yMap, 
		xProfile;
	bool 
		bAttached;		// ���� �������� �������������� ���������� �������
};

#endif /*_PROFILE_ATTACH_POINT__H_*/
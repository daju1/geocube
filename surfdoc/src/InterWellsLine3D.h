#pragma once
#include "line3d.h"

class InterWellsLine3D : public Line3D
{
public:
	// ���������� ������ ���� � �������� ���������
	double tolsch_deviation;
	// ���������� ������ ���� � �������� ���������
	// �������� ������� ������� ���� � ����������� �� �������� � ��������
	double glub_deviation;
	// �������� ������� ������� ���� � ����������� X
	double glub_deviation_x;
	double delta_x; //
	// �������� ������� ������� ���� � ����������� Y
	double glub_deviation_y;
	double delta_y; //

	InterWellsLine3D(SurfDoc * pSurfDoc);
	InterWellsLine3D(void);
	virtual ~InterWellsLine3D(void);

	void OnCreate(void);
	virtual HTREEITEM AddItem_ToTree(HWND hwndTV, HTREEITEM h1, const char * s = "");

	/*virtual*/ DWORD Serialize(Archive& ar);
	friend Archive& operator <<(Archive& ar, InterWellsLine3D& line);
	friend Archive& operator >>(Archive& ar, InterWellsLine3D& line);
};
LRESULT CALLBACK DlgProcInterWellsLineToPaint( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );

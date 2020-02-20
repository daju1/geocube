#pragma once
#include "Line3D.h"

class InterWellsLine3D : public Line3D
{
public:
	// отклонение толщин слоёв в соседних скважинах
	double tolsch_deviation;
	// отклонение глубин слоёв в соседних скважинах
	// тангненс наклона подошвы слоя в направлении от скважине к скважине
	double glub_deviation;
	// тангненс наклона подошвы слоя в направлении X
	double glub_deviation_x;
	double delta_x; //
	// тангненс наклона подошвы слоя в направлении Y
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

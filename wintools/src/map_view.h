#ifndef MAP_VIEWS_H
#define MAP_VIEWS_H






class map_view
{
protected:
	Object * m_ob;

	fGL x_center; 
	fGL y_center;
	fGL zoom_x;
	fGL zoom_y;
	
	int m_nCurVertPos;
	int m_nCurHorzPos;

	f64 maxx;
	f64 minx;

	f64 maxy;
	f64 miny;

	float _x_scale; 
	float _y_scale; 
	
	float _x0; 
	float _y0;	
	
public:
	map_view(Object * ob);
	virtual ~map_view();

	fGL lines_points_radius;

	void MouseWhell(float yDelta, float x, float y);

	void ConvertFromScreenToWorld(float x, float y, double & X, double & Y );
	void ConvertFromWorldToScreen(double X, double Y, float & x, float & y );
	float GetYScale();
	float GetXScale();

	const float get_x_scale() const {return _x_scale;}
	const float get_y_scale() const {return _y_scale;}

	void PreConvertingFromWorldToScreen();
	void ConvertingFromWorldToScreen(double X, double Y, float & x, float & y);

	void VScroll( HWND hWnd, WORD wScroll );
	void HScroll( HWND hWnd, WORD wScroll );

	virtual void UpdateExtremums(void);
	virtual void Update(bool) = 0;			// virtual
			
	bool calc_select_line(int mouse_x, int mouse_y, CPoint3& p3);
		
	Object * GetObject() {return m_ob;}

};

#endif

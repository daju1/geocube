// MTOOLS.H : mouse tool classes.

// Copyright (C) 1998 Tommi Hassinen, Jarno Huuskonen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/

#ifndef MTOOLS_H
#define MTOOLS_H

//#include "appconfig.h"

class mouse_tool;

class draw_tool;
class erase_tool;
class select_tool;
class zoom_tool;
class clipping_tool;
class translate_xy_tool;
class translate_z_tool;
class orbit_xy_tool;
class orbit_z_tool;
class rotate_xy_tool;
class rotate_z_tool;
class measure_tool;

// there is much repeat in these final tool classes (xy- and z-cases almost identical)...
// however, it's not known how much changes are needed here, so it's safest to keep it that way.

// yep. but the mouse is a 2-dimensional gadget... guess it's easiest to just use xy/z division.
// yep. but the mouse is a 2-dimensional gadget... guess it's easiest to just use xy/z division.
// yep. but the mouse is a 2-dimensional gadget... guess it's easiest to just use xy/z division.

/*################################################################################################*/

class ogl_view;		// views.h
class gdiplus_view;		// views.h

#include "camera.h"

/*################################################################################################*/

class mouse_tool
{
	public:
	
	dummy_object * ref_to_object;
	
	static transformer tool_transformer;
	static i32s latest_x; static i32s latest_y;
	
	static fGL ang_sensitivity;
	static fGL dist_sensitivity;
	
	public:
	
	enum state { Up, Down, DblClk, Unknown };
	enum button { Left, Middle, Right, None };
	
	mouse_tool(void);
	virtual ~mouse_tool(void);
	
	virtual const char * GetToolName(void) = 0;
	
	virtual void ButtonEvent(ogl_view *, i32s, i32s) = 0;
	virtual void MotionEvent(ogl_view *, i32s, i32s) = 0;
};

/*################################################################################################*/

class draw_tool : public mouse_tool
{
	protected:
	
	public:
	
	draw_tool(void) : mouse_tool() { }
	~draw_tool(void) { }
	
	enum what_to_draw { Griddata, Spheres, Line, Polygon, Profile, Rect, Cube, No_draw };

	const char * GetToolName(void) { return "Draw"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class erase_tool : public mouse_tool
{
	protected:
	
	public:

	enum what_to_erase { Griddata, Spheres, Line, Lines_point, Polygon, Polygones_point, Rect, Cube, No_erase };
	
	erase_tool(void) : mouse_tool() { }
	~erase_tool(void) { }
	
	const char * GetToolName(void) { return "Erase"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class edit_tool : public mouse_tool
{
	protected:
	
	public:

	enum what_to_edit { 
		Spheres, 
		Line, 
		Lines_connect,
		//Line_by_moving_existing_point, 
		//Line_by_add_new_point, 
		Line_cut_by_select_and_double_point, 
		Line_cut_by_select_and_delete_bond,
		Line_cut_by_double_new_point_on_bond,
		Lines_point, 
		Polygon, Polygones_point, Rect, Cube, No_edit };
	
	edit_tool(void) : mouse_tool() { }
	~edit_tool(void) { }
	
	const char * GetToolName(void) { return "Edit"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class select_tool : public mouse_tool
{
	protected:
	
	public:
	
	select_tool(void) : mouse_tool() { }
	~select_tool(void) { }
	
	const char * GetToolName(void) { return "Select"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
	
	enum select_mode { Object, Objects_with_the_same_ID, Objects_with_the_same_name, point_of_primitive, edge_or_line, triangle, quad, polygon };
};

/*################################################################################################*/

class zoom_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	
	public:
	
	zoom_tool(void) : mouse_tool() { }
	~zoom_tool(void) { }
	
	const char * GetToolName(void) { return "Zoom"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class clipping_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	
	public:
	
	clipping_tool(void) : mouse_tool() { }
	~clipping_tool(void) { }
	
	const char * GetToolName(void) { return "Clipping"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class translate_xy_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const obj_loc_data * tdata;
	
	public:
	
	translate_xy_tool(void) : mouse_tool() { }
	~translate_xy_tool(void) { }
	
	const char * GetToolName(void) { return "Translate XY"; }	// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class translate_z_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const obj_loc_data * tdata;
	
	public:
	
	translate_z_tool(void) : mouse_tool() { }
	~translate_z_tool(void) { }
	
	const char * GetToolName(void) { return "Translate Z"; }	// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
	
};

/*################################################################################################*/

class orbit_xy_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	orbit_xy_tool(void) : mouse_tool() { }
	~orbit_xy_tool(void) { }
	
	const char * GetToolName(void) { return "Orbit XY"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class orbit_z_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	orbit_z_tool(void) : mouse_tool() { }
	~orbit_z_tool(void) { }
	
	const char * GetToolName(void) { return "Orbit Z"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class rotate_xy_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	rotate_xy_tool(void) : mouse_tool() { }
	~rotate_xy_tool(void) { }
	
	const char * GetToolName(void) { return "Rotate XY"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class rotate_z_tool : public mouse_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	rotate_z_tool(void) : mouse_tool() { }
	~rotate_z_tool(void) { }
	
	const char * GetToolName(void) { return "Rotate Z"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class measure_tool : public mouse_tool
{
	protected:
	
	public:
	
	measure_tool(void) : mouse_tool() { }
	~measure_tool(void) { }
	
	const char * GetToolName(void) { return "Measure"; }		// virtual
	
	void ButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void MotionEvent(ogl_view *, i32s, i32s);		// virtual

	enum measure_mode { Atom, Bond, Angle, Torsion };
};

/*################################################################################################*/


class key_tool
{
	public:
	
	dummy_object * ref_to_object;
	
	static transformer tool_transformer;
	static i32s latest_x; static i32s latest_y;
	
	static fGL ang_sensitivity;
	static fGL dist_sensitivity;
	static int speed;
	
	public:

	bool m_bShiftPressed;
	bool m_bCtrlPressed;
	
	enum key_state { KeyUp, KeyDown, KeyUnknown };
	enum key { 
		keyA = 1,
		keyB,
		keyC,
		keyD,
		keyE,
		keyF,
		keyG,
		keyH,
		keyI,
		keyJ,
		keyK,
		keyL,
		keyM,
		keyN,
		keyO,
		keyP,
		keyQ,
		keyR,
		keyS,
		keyT,
		keyU,
		keyW,
		keyX,
		keyY,
		keyZ,
		keyUp, keyDown, keyLeft, keyRight, keySpace,
		keyHome, keyEnd, keyPageUp, keyPageDown, 
		keyInsert, keyDelete, 
		keyTab, keyEnter, 
		keyShift, keyCtrl,
		/*key1, key2, key3, key4, key5, key6, key7, key8, key9, key0,*/
		keyNone };
	
	key_tool(void);
	virtual ~key_tool(void);
	
	virtual const char * GetToolName(void) = 0;
	
	virtual void KeyButtonEvent(ogl_view *, i32s, i32s) = 0;
	virtual void KeyMotionEvent(ogl_view *, i32s, i32s) = 0;


};


class key_zoom_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	
	public:
	
	key_zoom_tool(void) : key_tool() { }
	~key_zoom_tool(void) { }
	
	const char * GetToolName(void) { return "Key Zoom"; }		// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

class key_clipping_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	
	public:
	
	key_clipping_tool(void) : key_tool() { }
	~key_clipping_tool(void) { }
	
	const char * GetToolName(void) { return "Key Clipping"; }		// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

/*################################################################################################*/

class key_translate_xy_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const obj_loc_data * tdata;
	
	public:
	
	key_translate_xy_tool(void) : key_tool() { }
	~key_translate_xy_tool(void) { }
	
	const char * GetToolName(void) { return "Key Translate XY"; }	// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class key_translate_z_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const obj_loc_data * tdata;
	
	public:
	
	key_translate_z_tool(void) : key_tool() { }
	~key_translate_z_tool(void) { }
	
	const char * GetToolName(void) { return "Key Translate Z"; }	// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class key_orbit_xy_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	key_orbit_xy_tool(void) : key_tool() { }
	~key_orbit_xy_tool(void) { }
	
	const char * GetToolName(void) { return "Key Orbit XY"; }		// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class key_orbit_z_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	key_orbit_z_tool(void) : key_tool() { }
	~key_orbit_z_tool(void) { }
	
	const char * GetToolName(void) { return "Key Orbit Z"; }		// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class key_rotate_xy_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	key_rotate_xy_tool(void) : key_tool() { }
	~key_rotate_xy_tool(void) { }
	
	const char * GetToolName(void) { return "Key Rotate XY"; }		// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/

class key_rotate_z_tool : public key_tool
{
	private:
	
	i32s render;
	bool accumulate;
	bool local_object;
	
	const camera * rdata;
	
	public:
	
	key_rotate_z_tool(void) : key_tool() { }
	~key_rotate_z_tool(void) { }
	
	const char * GetToolName(void) { return "Key Rotate Z"; }		// virtual
	
	void KeyButtonEvent(ogl_view *, i32s, i32s);		// virtual
	void KeyMotionEvent(ogl_view *, i32s, i32s);		// virtual
};

/*################################################################################################*/


#endif	// MTOOLS_H

// eof

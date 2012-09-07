// MTOOLS.CPP

// Copyright (C) 1998 Tommi Hassinen, Jarno Huuskonen.

// This program is free software; you can redistribute it and/or modify it
// under the terms of the license (GNU GPL) which comes with this package.

/*################################################################################################*/
#include "stdafx.h"

#include "gdiplus_mtools.h"	// config.h is here -> we get ENABLE-macros here...
#include "win32_map_views.h"

#include "project.h"
#include "views.h"

#include "appdefine.h"

/*################################################################################################*/

transformer mouse_gdiplus_tool::tool_transformer = transformer();
i32s mouse_gdiplus_tool::latest_x = NOT_DEFINED; i32s mouse_gdiplus_tool::latest_y = NOT_DEFINED;
fGL mouse_gdiplus_tool::ang_sensitivity = 180.0; fGL mouse_gdiplus_tool::dist_sensitivity = 2.0;

mouse_gdiplus_tool::mouse_gdiplus_tool(void)
{
}

mouse_gdiplus_tool::~mouse_gdiplus_tool(void)
{
}

/*################################################################################################*/

void draw_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
//printf("draw_gdiplus_tool::ButtonEvent(gdiplus_view * gv, i32s x = %d, i32s y = %d)\n", x,y);
	latest_x = x; latest_y = y;
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL) gv->cam->RenderWindow(gv, camera::Draw, x, y);
#endif
	gdiplus_map_view * gmv = dynamic_cast<gdiplus_map_view *>(oglv);
	if (gmv != NULL) gmv->GetProject()->GDIplusDrawEvent(gmv/*, name_vector*/);
}

void draw_gdiplus_tool::MotionEvent(gdiplus_view * gv, i32s x, i32s y)
{
//printf("draw_gdiplus_tool::MotionEvent(gdiplus_view * gv, i32s x = %d, i32s y = %d)\n", x,y);
	latest_x = x;
	latest_y = y;

	gdiplus_map_view * gmv = dynamic_cast<gdiplus_map_view *>(gv);
	if (gmv != NULL) gmv->GetProject()->GDIplusDrawMotionEvent(gmv);
	
}
bool draw_gdiplus_tool::KeyButtonEvent(gdiplus_view * gv, i32s x, i32s y)
{
	gdiplus_map_view * gmv = dynamic_cast<gdiplus_map_view *>(gv);
	if (gmv != NULL) gmv->GetProject()->GDIplusDrawKeyButtonEvent(gmv);

	
	//latest_x = x;
	//latest_y = y;

	return true;
}


/*################################################################################################*/

void erase_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
	latest_x = x; latest_y = y;
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL) gv->cam->RenderWindow(gv, camera::Erase, x, y);
#endif
	gdiplus_map_view * gmv = dynamic_cast<gdiplus_map_view *>(oglv);
	if (gmv != NULL) gmv->GetProject()->GDIplusEraseEvent(gmv/*, name_vector*/);
}

void erase_gdiplus_tool::MotionEvent(gdiplus_view *, i32s, i32s)
{
}

/*################################################################################################*/

void edit_gdiplus_tool::ButtonEvent(gdiplus_view * gv, i32s x, i32s y)
{
//printf("void edit_gdiplus_tool::ButtonEvent(gdiplus_view * gv, i32s x = %d, i32s y = %d)\n", x,y);
	latest_x = x; latest_y = y;
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL) gv->cam->RenderWindow(gv, camera::Edit, x, y);
#endif
	gdiplus_map_view * gmv = dynamic_cast<gdiplus_map_view *>(gv);
	if (gmv != NULL) gmv->GetProject()->GDIplusEditEvent(gmv/*, name_vector*/);
}

void edit_gdiplus_tool::MotionEvent(gdiplus_view * gv, i32s x, i32s y)
{
	latest_x = x;
	latest_y = y;
	gdiplus_map_view * gmv = dynamic_cast<gdiplus_map_view *>(gv);
	//if (gv != NULL) gv->cam->RenderWindow(gv, camera::Edit, x, y);
	if (gmv != NULL) gmv->GetProject()->GDIplusEditMotionEvent(gmv/*, name_vector*/);

}

/*################################################################################################*/

void select_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
	latest_x = x; latest_y = y;
	if (gdiplus_view::state != mouse_gdiplus_tool::Down) return;
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL) gv->cam->RenderWindow(gv, camera::Select, x, y);
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
}

void select_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
}

/*################################################################################################*/

void zoom_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gv->quick_update && gv && gv->GetProject() && gv->cam)
		{
			if (gdiplus_view::state == mouse_gdiplus_tool::Down)
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			else
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				gv->GetProject()->UpdateGraphicsViews(gv->cam);
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void zoom_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL dist[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && gv->cam)
		{
			dist[2] = dist_sensitivity * gv->range[1] * (fGL) (latest_y - y) / (fGL) gv->size[1];
			gv->cam->TranslateObject(dist, gv->cam->GetLocData());
			gv->cam->focus += dist[2];
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else gv->GetProject()->UpdateGraphicsViews(gv->cam);
		}
	}
#endif

#if 0
	if (oglv)
	{
		oglv->zoom_x /= sqrt(2.0);
		oglv->zoom_y /= sqrt(2.0);
		oglv->VScroll( hWnd, -1 );                    
		oglv->HScroll( hWnd, -1 );
		//###############################
		RECT rect;
		GetClientRect(hWnd,&rect);
		InvalidateRect(hWnd,&rect, true);
	}
#endif
	
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->ZoomEvent(latest_y - y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void clipping_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gv->quick_update && gv && gv->GetProject() && gv->cam)
		{
			if (gdiplus_view::state == mouse_gdiplus_tool::Down)
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			else
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				gv->GetProject()->UpdateGraphicsViews(gv->cam);
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void clipping_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gv && gv->GetProject() && gv->cam)
		{
			gv->cam->clipping += (fGL) (latest_y - y) / (fGL) gv->size[1];
			if (gv->cam->clipping < 0.01) gv->cam->clipping = 0.01;
			if (gv->cam->clipping > 0.99) gv->cam->clipping = 0.99;
			
			cout << "clipping = " << gv->cam->clipping << " = ";
			cout << (gv->cam->clipping * (2.0 * gv->cam->focus)) << " nm." << endl;
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else gv->GetProject()->UpdateGraphicsViews(gv->cam);
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->ZoomEvent(latest_y - y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void translate_xy_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
printf("translate_xy_gdiplus_tool::ButtonEvent x = %d y = %d\n",x,y);
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			
			if (gdiplus_view::ctrl_down) tdata = ref_to_object->GetLocData();
			else tdata = gv->cam->GetLocData();
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void translate_xy_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
//printf("translate_xy_gdiplus_tool::MotionEvent x = %d y = %d\n",x,y);
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL dist[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object && tdata)
		{
			dist[0] = dist_sensitivity * gv->range[0] * (fGL) (latest_x - x) / (fGL) gv->size[0];
			dist[1] = dist_sensitivity * gv->range[1] * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ref_to_object->TranslateObject(dist, tdata);
			
			if (gv->quick_update)
			{
				gv->GetProject()->UpdateGraphicsView(gv);
			}
			else
			{
				if (local_object)
				{
					gv->GetProject()->UpdateGraphicsViews(gv->cam);
				}
				else 
				{
					gv->GetProject()->UpdateAllMapViews();
				}
			}
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->TransEvent(latest_y - y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void translate_z_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
printf("translate_z_gdiplus_tool::ButtonEvent x = %d y = %d gv = %x\n",x,y, gv);
	if (gv != NULL)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			
			if (gdiplus_view::ctrl_down) tdata = ref_to_object->GetLocData();
			else tdata = gv->cam->GetLocData();
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void translate_z_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
//printf("translate_z_gdiplus_tool::MotionEvent x = %d y = %d gv = %x\n",x,y, gv);
	if (gv != NULL)
	{
//printf("translate_z_gdiplus_tool::MotionEvent gv != NULL\n");
		fGL dist[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object && tdata)
		{
//printf("translate_z_gdiplus_tool::MotionEvent (gv && gv->GetProject() && ref_to_object && tdata)\n");
			dist[2] = dist_sensitivity * gv->range[1] * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ref_to_object->TranslateObject(dist, tdata);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void orbit_xy_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
			
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void orbit_xy_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[0] = ang_sensitivity * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ang[1] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->OrbitObject(ang, * rdata, 0);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void orbit_z_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void orbit_z_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[2] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->OrbitObject(ang, * rdata, 1);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void rotate_xy_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void rotate_xy_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[0] = ang_sensitivity * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ang[1] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->RotateObject(ang, * rdata);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void rotate_z_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::state == mouse_gdiplus_tool::Down)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void rotate_z_gdiplus_tool::MotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[2] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->RotateObject(ang, * rdata);
		
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

// the operating principle here is the same as in select_gdiplus_tool above...

void measure_gdiplus_tool::ButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
	latest_x = x; latest_y = y;
	if (gdiplus_view::state != mouse_gdiplus_tool::Down) return;
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL) gv->cam->RenderWindow(gv, camera::Measure, x, y);
#endif
}

void measure_gdiplus_tool::MotionEvent(gdiplus_view *, i32s, i32s)
{
}

/*################################################################################################*/
/*################################################################################################*/

transformer key_gdiplus_tool::tool_transformer = transformer();
i32s key_gdiplus_tool::latest_x = NOT_DEFINED; i32s key_gdiplus_tool::latest_y = NOT_DEFINED;
fGL key_gdiplus_tool::ang_sensitivity = 180.0; fGL key_gdiplus_tool::dist_sensitivity = 2.0;

int key_gdiplus_tool::speed = 25;

key_gdiplus_tool::key_gdiplus_tool(void)
{
	m_bShiftPressed = false;
	m_bCtrlPressed = false;
}

key_gdiplus_tool::~key_gdiplus_tool(void)
{
}

/*################################################################################################*/

void key_zoom_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
//printf("zoom_key_gdiplus_tool::KeyButtonEvent x = %d y = %d\n",x,y);
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gv->quick_update && gv && gv->GetProject() && gv->cam)
		{
			if (gdiplus_view::state == mouse_gdiplus_tool::Down)
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			else
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				gv->GetProject()->UpdateGraphicsViews(gv->cam);
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void key_zoom_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
//printf("zoom_key_gdiplus_tool::KeyMotionEvent x = %d y = %d\n",x,y);
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL dist[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && gv->cam)
		{
			dist[2] = dist_sensitivity * gv->range[1] * (fGL) (latest_y - y) / (fGL) gv->size[1];
			gv->cam->TranslateObject(dist, gv->cam->GetLocData());
			gv->cam->focus += dist[2];
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else gv->GetProject()->UpdateGraphicsViews(gv->cam);
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->ZoomEvent(latest_y - y);
	
	latest_x = x;
	latest_y = y;
}
/*################################################################################################*/

void key_clipping_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gv->quick_update && gv && gv->GetProject() && gv->cam)
		{
			if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			else
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				gv->GetProject()->UpdateGraphicsViews(gv->cam);
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void key_clipping_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gv && gv->GetProject() && gv->cam)
		{
			gv->cam->clipping += (fGL) (latest_y - y) / (fGL) gv->size[1];
			if (gv->cam->clipping < 0.01) gv->cam->clipping = 0.01;
			if (gv->cam->clipping > 0.99) gv->cam->clipping = 0.99;
			
			cout << "clipping = " << gv->cam->clipping << " = ";
			cout << (gv->cam->clipping * (2.0 * gv->cam->focus)) << " nm." << endl;
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else gv->GetProject()->UpdateGraphicsViews(gv->cam);
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->ZoomEvent(latest_y - y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void key_translate_xy_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
//printf("key_translate_xy_gdiplus_tool::KeyButtonEvent x = %d y = %d\n",x,y);
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object)
				{
					ref_to_object->BeginTransformation();
				}
			}
			
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			
			if (gdiplus_view::ctrl_down)
			{
				tdata = ref_to_object->GetLocData();
			}
			else
			{
				tdata = gv->cam->GetLocData();
			}
		}
		else
		{
			if (ref_to_object)
			{
				ref_to_object->EndTransformation();
			}
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void key_translate_xy_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
//printf("key_translate_xy_gdiplus_tool::KeyMotionEvent oglv = 0x%08x x = %d y = %d\n",oglv,x,y);
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL dist[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object && tdata)
		{
			dist[0] = dist_sensitivity * gv->range[0] * (fGL) (latest_x - x) / (fGL) gv->size[0];
			dist[1] = dist_sensitivity * gv->range[1] * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ref_to_object->TranslateObject(dist, tdata);
			
			if (gv->quick_update)
			{
				gv->GetProject()->UpdateGraphicsView(gv);
			}
			else
			{
				if (local_object)
				{
					gv->GetProject()->UpdateGraphicsViews(gv->cam);
				}
				else
				{
					gv->GetProject()->UpdateAllMapViews();
				}
			}
		}
	}
#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->TransEvent(latest_y - y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void key_translate_z_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			// if CTRL is down, use object's own direction, not that of camera's !!!!!!!!!
			
			if (gdiplus_view::ctrl_down) tdata = ref_to_object->GetLocData();
			else tdata = gv->cam->GetLocData();
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

void key_translate_z_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL dist[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object && tdata)
		{
			dist[2] = dist_sensitivity * gv->range[1] * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ref_to_object->TranslateObject(dist, tdata);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}
#endif
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void key_orbit_xy_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
			
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void key_orbit_xy_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[0] = ang_sensitivity * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ang[1] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->OrbitObject(ang, * rdata, 0);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void key_orbit_z_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void key_orbit_z_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[2] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->OrbitObject(ang, * rdata, 1);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void key_rotate_xy_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void key_rotate_xy_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[0] = ang_sensitivity * (fGL) (latest_y - y) / (fGL) gv->size[1];
			ang[1] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->RotateObject(ang, * rdata);
			
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/

void key_rotate_z_gdiplus_tool::KeyButtonEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		if (gdiplus_view::key_state == key_gdiplus_tool::key_state::KeyDown)
		{
			if (gv->quick_update)		// if quick, change the rendering params...
			{
				render = gv->render;
				accumulate = gv->accumulate;
				
				gv->render = RENDER_WIREFRAME;
				gv->accumulate = false;
			}
			
			if (!gdiplus_view::shift_down)
			{
				ref_to_object = gv->cam; local_object = true;
			}
			else
			{
				ref_to_object = gv->GetProject()->selected_object;
				
				i32s index = gv->GetProject()->IsLight(ref_to_object);
				local_object = (index != NOT_DEFINED && gv->GetProject()->light_vector[index]->owner == gv->cam);
				
				if (!ref_to_object && gdiplus_view::shift_down)
				{
					tool_transformer.Init(gv->GetProject());
					ref_to_object = (& tool_transformer);
				}
				
				if (ref_to_object) ref_to_object->BeginTransformation();
			}
			
			rdata = gv->cam;
		}
		else
		{
			if (ref_to_object) ref_to_object->EndTransformation();
			
			if (gv->quick_update)		// if quick, put back original params and update...
			{
				gv->render = render;
				gv->accumulate = accumulate;
				
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

void key_rotate_z_gdiplus_tool::KeyMotionEvent(gdiplus_view * oglv, i32s x, i32s y)
{
#if 0
	graphics_view * gv = dynamic_cast<graphics_view *>(oglv);
	if (gv != NULL)
	{
		fGL ang[3] = { 0.0, 0.0, 0.0 };
		if (gv && gv->GetProject() && ref_to_object)
		{
			ang[2] = ang_sensitivity * (fGL) (x - latest_x) / (fGL) gv->size[0];
			ref_to_object->RotateObject(ang, * rdata);
		
			if (gv->quick_update) gv->GetProject()->UpdateGraphicsView(gv);
			else
			{
				if (local_object) gv->GetProject()->UpdateGraphicsViews(gv->cam);
				else gv->GetProject()->UpdateAllMapViews();
			}
		}
	}

#endif
	plotting_view * pv = dynamic_cast<plotting_view *>(oglv);
	if (pv != NULL) pv->UserEvent(x, y);
	
	latest_x = x;
	latest_y = y;
}

/*################################################################################################*/


// eof

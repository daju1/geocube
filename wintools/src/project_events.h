


void project::MyEditEvent(my_view * gv NAMES/*, vector<iGLu> & names*/)
{
printf("project::MyEditEvent\n");
	if (my_view::button == mouse_my_tool::Right) return;	// the right button is for popup menus...
printf("project::MyEditEvent 1\n");

	i32s mouse[2] =
	{
		gv->current_my_tool->latest_x,
		gv->current_my_tool->latest_y
	};
	static CPoint3 * edit_point = NULL;
	static bool to_edit = false;
//	double epsilon = 0.000001;

	if (my_view::what_to_edit == edit_my_tool::what_to_edit::Line)
	{
printf("if (my_view::what_to_edit == edit_my_tool::what_to_edit::Line)\n");
		//if (my_view::what_to_edit == edit_my_tool::what_to_edit::Line_by_moving_existing_point)
		//{
		printf("edit_my_tool::Line\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		my_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (my_view::state == mouse_my_tool::state::Down)
		{		
printf("if (my_view::state == mouse_my_tool::state::Down)\n");
			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{
printf("if (calc_select_line\n");
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
				{
printf("if (this->IsSelected\n");
					my_view::what_selected.PrintInfo();
					// если режим отображения линий с шариками - то меняем этот режим на тонкие без шариков
					if (old_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
					{
						Line3D::s_line3d_draw_mode = Line3D::line3d_draw_mode::as_thing_lines;
						// теперь мы должны перерисовать выбранный объект в новом режиме
						if(my_view::what_selected.GetObject())
						{
							my_view::what_selected.GetObject()->ReDraw();
							UpdateAllViews();
						}					
					}		
					//снова ищем точку пересечения указателя мыши с объектами Open GL
					if(gv->calc_select_line(mouse[0], mouse[1], pt3))
					{
printf("if(calc_select_line 2\n");
						// и если мы опять попали мышью по объекту
						if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
						{
printf("if (this->IsSelected 2\n");
							my_view::what_selected.PrintInfo();
							if( my_view::what_selected.m_selected_objects_element_type 
								== WhatSelected::selected_objects_element_type::sel_point
								&& my_view::what_selected.GetObject())
							{	
printf("if (m_selected_objects_element_type == sel_point\n");
								if(my_view::what_selected.GetObject()->IsPrimitive3())
								{
printf("if (this->IsPrimitive3()\n");
									Primitive3D<CPoint3> * primitive3 
										= dynamic_cast<Primitive3D<CPoint3>*>
										(my_view::what_selected.GetObject());

									if (primitive3)
									{
printf("if (primitive3)\n");
										if (my_view::what_selected.GetIndex() > -1 
											&& 
											my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
										{
printf("if GetIndex() CPOINT3_FLAG_HIDE\n");
											edit_point = &primitive3->GetViewPoint(my_view::what_selected.GetIndex());
											
											CPoint3& ptd = primitive3->GetDocumentPoint(my_view::what_selected.GetIndex());
											// HIDE POINT - включаем 3-й бит 
											// в пользовательских данных point 
											ptd.flag |= CPOINT3_FLAG_HIDE;
											my_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
											Line3D::s_line3d_draw_mode = old_line3d_draw_mode;

printf("pre ReDraw %s\n", Object::ObjectTypeToString(my_view::what_selected.GetObject()->GetObjectType()));

											my_view::what_selected.GetObject()->ReDraw();
											UpdateAllViews();
											return;
										}
									}
								}
							}
						}
					}
					// если режим отображения линий с шариками - то меняем этот режим 
					if (old_line3d_draw_mode == Line3D::line3d_draw_mode::as_lines_with_spheres)
					{
						Line3D::s_line3d_draw_mode = old_line3d_draw_mode;
						// теперь мы должны перерисовать выбранный объект в новом режиме
						if(my_view::what_selected.GetObject())
						{
							my_view::what_selected.GetObject()->ReDraw();
							UpdateAllViews();
						}					
					}				
				}
			}
		}
		if (my_view::state == mouse_my_tool::state::Up)
		{
printf("edit_my_tool::Line Up\n");
			if( my_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_point
				&& my_view::what_selected.GetObject())
			{
				if (edit_point)
				{
					if(my_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(my_view::what_selected.GetObject());

						if (primitive3)
						{
							if (my_view::what_selected.GetIndex() > -1 
								&& 
								my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}
								
								if(gv->calc_select_line(mouse[0], mouse[1], pt3))
								{
									*edit_point = pt3;
									primitive3->ZoomInv(my_view::what_selected.GetIndex(),
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
											m_xd_zoom_center,
											m_yd_zoom_center,
											m_zd_zoom_center);

									this->CorrectDrawingPoint(my_view::what_selected.GetObject(), 
										my_view::what_selected.GetIndex());

								}

								CPoint3& ptd = primitive3->GetDocumentPoint(my_view::what_selected.GetIndex());
								// UN HIDE POINT - выключаем 3-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE;
								my_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;

								my_view::what_selected.GetObject()->ReDraw();

								Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}
		//if (my_view::what_to_edit == edit_my_tool::what_to_edit::Line_by_add_new_point)
		//{
		printf("edit_my_tool::Line_by_add_new_point\n");
		my_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;


		// при нажатии кнопки мыши
		if (my_view::state == mouse_my_tool::state::Down)
		{
			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
				{
					my_view::what_selected.PrintInfo();
					if( my_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_line
						&& my_view::what_selected.GetObject())
					{	
						if(my_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(my_view::what_selected.GetObject());

							if (primitive3)
							{
								if (my_view::what_selected.GetIndex() > -1 
									&& 
									my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									printf("to_edit = true\n");
									to_edit = true;
									//edit_point = &primitive3->GetViewPoint(my_view::what_selected.GetIndex());
									
									CPoint3& ptd = primitive3->GetDocumentPoint(my_view::what_selected.GetIndex());
									// HIDE LINE - включаем 4-й бит 
									// в пользовательских данных point 
									ptd.flag |= CPOINT3_FLAG_HIDE_LINE;
									my_view::what_selected.GetObject()->m_lParam |= OBJECT_FLAG_THING_BIT;
									//Line3D::s_line3d_draw_mode = old_line3d_draw_mode;


									my_view::what_selected.GetObject()->ReDraw();
									UpdateAllViews();
									return;
								}
							}
						}
					}
				}
			}
		}
		if (my_view::state == mouse_my_tool::state::Up)
		{
			if( my_view::what_selected.m_selected_objects_element_type 
				== WhatSelected::selected_objects_element_type::sel_line
				&& my_view::what_selected.GetObject())
			{
				if (to_edit)
				{
					if(my_view::what_selected.GetObject()->IsPrimitive3())
					{
						Primitive3D<CPoint3> * primitive3 
							= dynamic_cast<Primitive3D<CPoint3>*>
							(my_view::what_selected.GetObject());

						if (primitive3)
						{
							if (my_view::what_selected.GetIndex() > -1 
								&& 
								my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
							{
								bool can_disable_depth_test = Object::CanDisableDepthTest();
								if (can_disable_depth_test)
								{
									Object::CanDisableDepthTest(false);
									UpdateAllViews(true);
								}
								if(gv->calc_select_line(mouse[0], mouse[1], pt3))
								{
									printf("insert\n");
									//*edit_point = pt3;
									primitive3->Insert(my_view::what_selected.GetIndex()+1,pt3);
									primitive3->ZoomInv(my_view::what_selected.GetIndex()+1,
										this->m_zoomX, this->m_zoomY, this->m_zoomZ,
											m_xd_zoom_center,
											m_yd_zoom_center,
											m_zd_zoom_center);

									this->CorrectDrawingPoint(my_view::what_selected.GetObject(), 
										my_view::what_selected.GetIndex());
								}

								CPoint3& ptd = primitive3->GetDocumentPoint(my_view::what_selected.GetIndex());
								// UN HIDE LINE - выключаем 4-й бит 
								// в пользовательских данных point
								ptd.flag &= ~CPOINT3_FLAG_HIDE_LINE;
								my_view::what_selected.GetObject()->m_lParam &= ~OBJECT_FLAG_THING_BIT;

								my_view::what_selected.GetObject()->ReDraw();
								Object::CanDisableDepthTest(can_disable_depth_test);
								UpdateAllViews();
							}
						}
					}
				}
			}
		}
		//}


	}

	/*if (my_view::what_to_edit == edit_my_tool::Line_cut_by_double_new_point_on_bond)
	{
		printf("edit_my_tool::Line_cut_by_double_new_point_on_bond\n");
	}*/
	if (my_view::what_to_edit == edit_my_tool::Line_cut_by_select_and_delete_bond)
	{
		printf("edit_my_tool::Line_cut_by_select_and_delete_bond\n");

		my_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_line;

		CPoint3 pt3;

		// при нажатии кнопки мыши
		if (my_view::state == mouse_my_tool::state::Down)
		{
			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
				{
					my_view::what_selected.PrintInfo();
					if( my_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_line
						&& my_view::what_selected.GetObject())
					{	
						if(my_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(my_view::what_selected.GetObject());

							if (primitive3)
							{
								if (my_view::what_selected.GetIndex() > -1 
									&& 
									my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									printf("to_edit = true\n");

									if (my_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(my_view::what_selected.GetObject());
										if (pob && my_view::what_selected.GetObject()->GetObjectList() && my_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (my_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(my_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												if (my_view::what_selected.GetIndex() > 0)
												{
													//----------------------------------------
													Line3D line(this);
													pvect->AddMsg(&line);
													for (unsigned int i = 0; 
														i <= my_view::what_selected.GetIndex() && 
														i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(my_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(my_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().SetLayer(my_view::what_selected.GetObject()->GetLayer());
													pvect->GetLastMsg().Select(false);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												if (pob->GetPointsNumber() - (my_view::what_selected.GetIndex()+1) > 1)
												{
													//----------------------------------------
													Line3D line2(this);
													pvect->AddMsg(&line2);
													for (unsigned int i = my_view::what_selected.GetIndex()+1; i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(my_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(my_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().SetLayer(my_view::what_selected.GetObject()->GetLayer());

													pvect->GetLastMsg().Select(false);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												my_view::what_selected.GetObject()->GetObjectList()->Init(*pvect, my_view::what_selected.GetObject()->GetObjectList()->GetParent());

												my_view::what_selected.GetObject()->m_bChecked = false;
												TreeView_MySetCheckState(this->hwndTV, 
													my_view::what_selected.GetObject()->myTreeItem, 
													my_view::what_selected.GetObject()->m_bChecked);
					
																		
												my_view::what_selected.
													EraseSelectedObject<Line3D>
													(hwndTV,Object::object_type::line3d);
						
												UpdateAllViews();
												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (my_view::what_to_edit == edit_my_tool::Line_cut_by_select_and_double_point)
	{
		printf("edit_my_tool::Line_cut_by_select_and_double_point\n");
		my_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;

		// при нажатии кнопки мыши
		if (my_view::state == mouse_my_tool::state::Down)
		{
			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
				{
					my_view::what_selected.PrintInfo();
					if( my_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& my_view::what_selected.GetObject())
					{	
						if(my_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(my_view::what_selected.GetObject());

							if (primitive3)
							{
								if (my_view::what_selected.GetIndex() > -1 
									&& 
									my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									printf("to_edit = true\n");

									if (my_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(my_view::what_selected.GetObject());
										if (pob && my_view::what_selected.GetObject()->GetObjectList() && my_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (my_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(my_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												if (my_view::what_selected.GetIndex() > 0)
												{
													//----------------------------------------
													Line3D line(this);
													pvect->AddMsg(&line);
													for (unsigned int i = 0; 
														i <= my_view::what_selected.GetIndex() && 
														i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(my_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(my_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().Select(true);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												if (pob->GetPointsNumber() - (my_view::what_selected.GetIndex()+1) > 1)
												{
													//----------------------------------------
													Line3D line2(this);
													pvect->AddMsg(&line2);
													for (unsigned int i = my_view::what_selected.GetIndex()+1; i < pob->GetPointsNumber(); i++)
														pvect->GetLastMsg().PushBack(pob->GetDocumentPoint(i));
													pvect->GetLastMsg().Zoom(this->m_zoomX, this->m_zoomY, this->m_zoomZ,
																			m_xd_zoom_center,
																			m_yd_zoom_center,
																			m_zd_zoom_center);
													pvect->GetLastMsg().SetColor(my_view::what_selected.GetObject()->GetColor());
													pvect->GetLastMsg().SetName(my_view::what_selected.GetObject()->GetName());
													pvect->GetLastMsg().Select(false);
													pvect->GetLastMsg().Draw();
													pvect->GetLastMsg().AddItem_ToTree(hwndTV, pob->parentTreeItem);
													//----------------------------------------
												}
												my_view::what_selected.GetObject()->GetObjectList()->Init(*pvect, my_view::what_selected.GetObject()->GetObjectList()->GetParent());

												my_view::what_selected.GetObject()->m_bChecked = false;
												TreeView_MySetCheckState(this->hwndTV, 
													my_view::what_selected.GetObject()->myTreeItem, 
													my_view::what_selected.GetObject()->m_bChecked);

																		
												my_view::what_selected.
													EraseSelectedObject<Line3D>
													(hwndTV,Object::object_type::line3d);
						
					
												UpdateAllViews();
												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}



	if (my_view::what_to_edit == edit_my_tool::what_to_edit::Lines_connect)
	{
		printf("edit_my_tool::Line_connect\n");
		Line3D::line3d_draw_mode old_line3d_draw_mode = Line3D::s_line3d_draw_mode;
		my_view::what_selected.m_what_to_select = 
			WhatSelected::selected_objects_element_type::sel_point;

		CPoint3 pt3;
		// при нажатии кнопки мыши
		if (my_view::state == mouse_my_tool::state::Down)
		{
//printf("edit_my_tool::Line_connect Down\n");
			this->connect_lines[0] = NULL;
			this->connect_vect_lines[0] = NULL;
			this->connect_lines_ind[0] = -1;

			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
				{
					my_view::what_selected.PrintInfo();
					if( my_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& my_view::what_selected.GetObject())
					{	
						if(my_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(my_view::what_selected.GetObject());

							if (primitive3)
							{
								if (my_view::what_selected.GetIndex() > -1 
									&& 
									my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									//printf("to_edit = true\n");

									if (my_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(my_view::what_selected.GetObject());
										this->connect_lines[0] = pob;

										if (pob && my_view::what_selected.GetObject()->GetObjectList() && my_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (my_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(my_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[0] = pvect;
												this->connect_lines_ind[0] = my_view::what_selected.GetIndex();



												return;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
		if (my_view::state == mouse_my_tool::state::Up)
		{
//printf("edit_my_tool::Line_connect Up\n");
			this->connect_lines[1] = NULL;
			this->connect_vect_lines[1] = NULL;
			this->connect_lines_ind[1] = -1;

			if(gv->calc_select_line(mouse[0], mouse[1], pt3))
			{				
				// если мы попали мышью по объекту
				if (this->IsSelected(pt3,this->m_sphere_radius,my_view::what_selected))
				{
					my_view::what_selected.PrintInfo();
					if( my_view::what_selected.m_selected_objects_element_type 
						== WhatSelected::selected_objects_element_type::sel_point
						&& my_view::what_selected.GetObject())
					{	
						if(my_view::what_selected.GetObject()->IsPrimitive3())
						{
							Primitive3D<CPoint3> * primitive3 
								= dynamic_cast<Primitive3D<CPoint3>*>
								(my_view::what_selected.GetObject());

							if (primitive3)
							{
								if (my_view::what_selected.GetIndex() > -1 
									&& 
									my_view::what_selected.GetIndex() < (int)primitive3->GetPointsNumber())
								{
									printf("to_edit = true\n");

									if (my_view::what_selected.GetObject()->GetObjectType() == Object::object_type::line3d)
									{
										Line3D * pob = dynamic_cast<Line3D*>(my_view::what_selected.GetObject());
										this->connect_lines[1] = pob;

										if (pob && my_view::what_selected.GetObject()->GetObjectList() && my_view::what_selected.GetObject()->GetObjectList()->GetContainer())
										{
											if (my_view::what_selected.GetObject()->GetObjectList()->GetContainerType() == Object::container_type::container_vect)
											{
												vect<Line3D> * pvect = reinterpret_cast<vect<Line3D> *>(my_view::what_selected.GetObject()->GetObjectList()->GetContainer());
												this->connect_vect_lines[1] = pvect;
												this->connect_lines_ind[1] = my_view::what_selected.GetIndex();


												
											}
										}
									}
								}
							}
						}
					}
				}
			}
/*printf("edit_my_tool::Line_connect 2\n");//*/
printf("this->connect_lines[0] 0x%08x\n"
		"this->connect_vect_lines[0] 0x%08x\n"
		"this->connect_lines_ind[0] %d\n"
		,
				this->connect_lines[0],
				this->connect_vect_lines[0],
				this->connect_lines_ind[0]
				);
printf("this->connect_lines[1] 0x%08x\n"
		"this->connect_vect_lines[1] 0x%08x\n"
		"this->connect_lines_ind[1] %d\n"
		,
				this->connect_lines[1],
				this->connect_vect_lines[1],
				this->connect_lines_ind[1]
				);//*/

			if (this->connect_lines[0] && this->connect_lines[1] &&
				this->connect_vect_lines[0] && this->connect_vect_lines[1])
			{
//printf("edit_my_tool::Line_connect 3\n");
				if (this->connect_lines[0] == this->connect_lines[1])
				{		
					if(
						(this->connect_lines_ind[0] == 0 && this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						||
						(this->connect_lines_ind[1] == 0 && this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						)
					{
						if(this->connect_lines[0]->GetPointsNumber() > 2)
						{
							this->connect_lines[0]->PushBack(this->connect_lines[0]->GetDocumentPoint(0));
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
						}
					}
				}
				if (this->connect_lines[0] != this->connect_lines[1])
				{
//printf("edit_my_tool::Line_connect 4\n");
					if(
						(this->connect_lines_ind[0] == 0 || this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1)
						&&
						(this->connect_lines_ind[1] == 0 || this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						)
					{
//printf("edit_my_tool::Line_connect 5\n");
						// нулевую линию сливаем к первой

						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = 0; i < (int)this->connect_lines[0]->GetPointsNumber(); i++)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}

							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_my_tool::Line_connect 6\n");
							return;

						}						
						
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == this->connect_lines[1]->GetPointsNumber()-1)
						{
							for (int i = (int)this->connect_lines[0]->GetPointsNumber()-1; i >=0; i--)
							{
								this->connect_lines[1]->PushBack(this->connect_lines[0]->GetDocumentPoint(i));
							}
							this->connect_lines[1]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[1]->ReDraw();
							// удалить нулевую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[0], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_my_tool::Line_connect 7\n");
							return;
						}
						// первую линию сливаем к нулевой 
						if (this->connect_lines_ind[0] == this->connect_lines[0]->GetPointsNumber()-1 && 
							this->connect_lines_ind[1] == 0)
						{
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
//printf("edit_my_tool::Line_connect 8\n");
							return;
						}						
						
						if (this->connect_lines_ind[0] == 0 && 
							this->connect_lines_ind[1] == 0)
						{
							this->connect_lines[0]->Reverse();
							for (int i = 0; i < (int)this->connect_lines[1]->GetPointsNumber(); i++)
							{
								this->connect_lines[0]->PushBack(this->connect_lines[1]->GetDocumentPoint(i));
							}
							this->connect_lines[0]->Zoom(m_zoomX,m_zoomY,m_zoomZ,m_xd_zoom_center,m_yd_zoom_center,m_zd_zoom_center);
							this->connect_lines[0]->ReDraw();
							// удалить первую линию
							EraseObject<Line3D>(hwndTV, this->connect_lines[1], Object::object_type::line3d);
							UpdateAllViews();
//printf("edit_my_tool::Line_connect 9\n");
							return;
						}
						
					}
				}
			}
		}


	}


	to_edit = false;
	edit_point = NULL;
}






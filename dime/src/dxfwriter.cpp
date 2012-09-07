
#include "../stdafx.h"
#include "../surfdoc/src/object.h"
#include "../surfdoc/src/line3d.h"
#include "../surfdoc/src/layer.h"
#include "../surfdoc/src/surfdoc.h"
#include "../surfdoc/src/CrdTranslator.h"

#include <dime/dxfwriter.h>

// DIME: needed include files.
#include <dime/Model.h>
#include <dime/sections/EntitiesSection.h>
#include <dime/sections/TablesSection.h>
#include <dime/sections/BlocksSection.h>
#include <dime/tables/LayerTable.h>
#include <dime/tables/Table.h>
#include <dime/entities/3DFace.h>
#include <dime/entities/Solid.h>
#include <dime/entities/Line.h>
#include <dime/entities/Block.h>
#include <dime/entities/Insert.h>
#include <dime/entities/UnknownEntity.h>
#include <dime/Output.h>
#include <dime/util/Linear.h>
static void
add_layer(const char * name, int colnum, dimeModel * model, dimeTable * layers)
{
  dimeLayerTable * layer = new dimeLayerTable;
  layer->setLayerName(name, NULL);
  layer->setColorNumber(colnum); // the color numbers are defined in dime/Layer.cpp.

  // need to set some extra records so that AutoCAD will stop
  // complaining
  dimeParam param;
  param.string_data = "CONTINUOUS";
  layer->setRecord(6, param);
  param.int16_data = 64;
  layer->setRecord(70, param);
  layer->registerLayer(model); // important, register layer in model
  layers->insertTableEntry(layer);
}


/* Output a line */
void print_line(Line3D * line3D, dimeModel * model, dimeBlock * block, CrdTranslator * translator)
{
	const char * layername = 
		line3D->GetLayer() ? line3D->GetLayer()->GetName().c_str() : 
	line3D->m_pSurfDoc ? line3D->m_pSurfDoc->m_defaut_layer.GetName().c_str() : "0";
	const dimeLayer * layer = model->getLayer(layername);
	// create three dimeLine entities to represent the triangle
	for (size_t i = 0; i < line3D->GetPointsNumber()-1; i++) 
	{
		// DIME: create a LINE entity
		dimeLine * line = new dimeLine;
		if (layer) 
		{
			line->setLayer(layer);
		}
		
		line->setColorNumber(dimeLayer::RGBToColor(line3D->GetColor()));
		
		dimeVec3f v[2];

		if (translator)
		{
			translator->DoTranslation(
				line3D->GetDocumentPoint(i).x,
				line3D->GetDocumentPoint(i).y,
				line3D->GetDocumentPoint(i).z,
				v[0].x,
				v[0].y,
				v[0].z);

			translator->DoTranslation(
				line3D->GetDocumentPoint(i+1).x,
				line3D->GetDocumentPoint(i+1).y,
				line3D->GetDocumentPoint(i+1).z,
				v[1].x,
				v[1].y,
				v[1].z);
		}
		else
		{		
			v[0].x = line3D->GetDocumentPoint(i).x;
			v[0].y = line3D->GetDocumentPoint(i).y;
			v[0].z = line3D->GetDocumentPoint(i).z;
			
			v[1].x = line3D->GetDocumentPoint(i+1).x;
			v[1].y = line3D->GetDocumentPoint(i+1).y;
			v[1].z = line3D->GetDocumentPoint(i+1).z;
		}
		
		line->setCoords(0, v[0]);
		line->setCoords(1, v[1]);
		
		// DIME: create unique handle for the entity (needed to load the file into AutoCAD)
		
		const int BUFSIZE = 1024;
		char buf[BUFSIZE];
		const char * handle = model->getUniqueHandle(buf, BUFSIZE);
		
		dimeParam param;
		param.string_data = handle;
		line->setRecord(5, param);
		
		// DIME: add entity to model
		if (block) 
		{
			block->insertEntity(line);
		}
		else 
		{
			model->addEntity(line);
		}
	}
}

struct ptLayer
{
	Layer *pLayer;
	int colnum;
};
void Fill_UsedLayersPtrVector(Object * pOb, WPARAM, LPARAM, void * p)
{
	if (pOb && p)
	{
		Layer *pLayer = pOb->GetLayer();
		vector<ptLayer> * p_used_layers = reinterpret_cast<vector<ptLayer> *>(p);
		if (p_used_layers)
		{
			// find layer
			bool found = false;
			for(vector<ptLayer>::iterator it = p_used_layers->begin();
				it != p_used_layers->end(); it++)
			{
				if (pLayer == (*it).pLayer)
				{
					found = true;
					break;
				}
			}
			if (!found)
			{
				ptLayer ptlayer;
				ptlayer.pLayer = pLayer;
				ptlayer.colnum = dimeLayer::RGBToColor(pOb->GetColor());
				p_used_layers->push_back(ptlayer);
			}
		}
	}
}

bool save_as_dxf(Object * ob, char * outfile, bool useblock, CrdTranslator * translator)
{

  // DIME: create dime model
  dimeModel model;

  // DIME: only needed if you need your object to be in a layer
  {
    // DIME: add tables section (needed for layers).
    dimeTablesSection * tables = new dimeTablesSection;
    model.insertSection(tables);
    
    // DIME: set up a layer table to store our layers
    dimeTable * layers = new dimeTable(NULL);
    
    // DIME: set up our layers
	bool use_all_surfdoc_layers = false;
	if (use_all_surfdoc_layers)
	{
		if (ob->m_pSurfDoc)
		{   
			add_layer(ob->m_pSurfDoc->m_defaut_layer.GetName().c_str(), 7, &model, layers);	
			for (map<int, Layer>::iterator i_layer = ob->m_pSurfDoc->m_layers.begin(); 
				i_layer != ob->m_pSurfDoc->m_layers.end(); i_layer++)
			{
				add_layer((*i_layer).second.GetName().c_str(), 7, &model, layers);
			}
		}
	}
	else
	{
		vector<ptLayer> used_layers;
		ob->EnumObjects(0, 0, (void*) &used_layers, 
			&Object::ReturnTrue,
			Fill_UsedLayersPtrVector);

		for(vector<ptLayer>::iterator it = used_layers.begin();
				it != used_layers.end(); it++)
		{
			add_layer((*it).pLayer->GetName().c_str(), (*it).colnum, &model, layers);
		}
	}		


    // DIME: insert the layer in the table
    tables->insertTable(layers); 
  }

  // DIME: only needed if you want to create the sphere as a BLOCK
  dimeBlock * block = NULL;
  if (useblock) {
    dimeBlocksSection * blocks = new dimeBlocksSection;
    model.insertSection(blocks);
    block = new dimeBlock(NULL);
    block->setName("MyBlock");
    blocks->insertBlock(block);
  }

  // DIME: add the entities section.
  dimeEntitiesSection * entities = new dimeEntitiesSection;
  model.insertSection(entities);

 
  /* Print out resulting approximation */
  //ob->print_object(maxlevel, model, LAYERNAME1, block);
  bool status = ob->SaveAsDxf(&model, block, translator);

  if (block) {
    dimeInsert * insert = new dimeInsert;
    insert->setBlock(block);
    model.addEntity(insert);
  }

  if (!status)
  {
	  char str[1048];
	  sprintf(str, 
		  "this object (type = %s name = %s)\n"
		  "does not saved into dxf file %s\n", 
		  Object::ObjectTypeToString(ob->GetObjectType()),
		  ob->GetName().c_str(), outfile);
	  MessageBox(0,str, "save_as_dxf(Object * ob, char * outfile)", MB_OK | MB_ICONEXCLAMATION);
	  return false;
  }

  // DIME: initialize output file
  dimeOutput out;
  if (!outfile || !out.setFilename(outfile)) {
    out.setFileHandle(stdout);
  }
  // DIME: write the model to file  
  model.write(&out);

  return status;
}

bool cutline_save_as_dxf_razrez(SurfDoc * doc, char * outfile, bool useblock, SSaveProfData * sprData,
								double a, double b, double c, double d,
								double minX, double minY, double minZ,
								double maxX, double maxY, double maxZ
								)
{

  // DIME: create dime model
  dimeModel model;

  // DIME: only needed if you need your object to be in a layer
  {
    // DIME: add tables section (needed for layers).
    dimeTablesSection * tables = new dimeTablesSection;
    model.insertSection(tables);
    
    // DIME: set up a layer table to store our layers
    dimeTable * layers = new dimeTable(NULL);
    
    // DIME: set up our layers
	bool use_all_surfdoc_layers = true;
	if (use_all_surfdoc_layers)
	{
		if (doc)
		{   
			add_layer(doc->m_defaut_layer.GetName().c_str(), 7, &model, layers);	
			for (map<int, Layer>::iterator i_layer = doc->m_layers.begin(); 
				i_layer != doc->m_layers.end(); i_layer++)
			{
				add_layer((*i_layer).second.GetName().c_str(), 7, &model, layers);
			}
		}
	}
	/*else
	{
		vector<ptLayer> used_layers;
		ob->EnumObjects(0, 0, (void*) &used_layers, 
			&Object::ReturnTrue,
			Fill_UsedLayersPtrVector);

		for(vector<ptLayer>::iterator it = used_layers.begin();
				it != used_layers.end(); it++)
		{
			add_layer((*it).pLayer->GetName().c_str(), (*it).colnum, &model, layers);
		}
	}	*/	


    // DIME: insert the layer in the table
    tables->insertTable(layers); 
  }

  // DIME: only needed if you want to create the sphere as a BLOCK
  dimeBlock * block = NULL;
  if (useblock) {
    dimeBlocksSection * blocks = new dimeBlocksSection;
    model.insertSection(blocks);
    block = new dimeBlock(NULL);
    block->setName("MyBlock");
    blocks->insertBlock(block);
  }

  // DIME: add the entities section.
  dimeEntitiesSection * entities = new dimeEntitiesSection;
  model.insertSection(entities);

 
  /* Print out resulting approximation */
  //ob->print_object(maxlevel, model, LAYERNAME1, block);
  bool status = doc->CutlineSaveAsDxfRazres(&model, block, *sprData, a, b, c, d,
								minX, minY, minZ,
								maxX, maxY, maxZ);

  if (block) {
    dimeInsert * insert = new dimeInsert;
    insert->setBlock(block);
    model.addEntity(insert);
  }

  if (!status)
  {
	  char str[1048];
	  sprintf(str, 
		  "this object (type = %s name = %s)\n"
		  "does not saved into dxf file %s\n", 
		  Object::ObjectTypeToString(doc->GetObjectType()),
		  doc->GetName().c_str(), outfile);
	  MessageBox(0,str, "save_as_dxf(Object * ob, char * outfile)", MB_OK | MB_ICONEXCLAMATION);
	  return false;
  }

  // DIME: initialize output file
  dimeOutput out;
  if (!outfile || !out.setFilename(outfile)) {
    out.setFileHandle(stdout);
  }
  // DIME: write the model to file  
  model.write(&out);

  return status;
}

void print_solid_triangle(TRIA & tria, VERT * vert, dimeModel & model, const dimeLayer * layer,
                    dimeBlock * block, COLORREF c)
{
  // filled, create dime3DFace
//  int i;

  // DIME: create a 3DFACE entity, and set it to contain a triangle
  dimeSolid * face = new dimeSolid;
  if (layer) {
    face->setLayer(layer);
  }
  dimeVec3f v[3];

/*
  for (i = 0; i < 3; i++) {
    v[i].x = t->pt[i].x;
    v[i].y = t->pt[i].y;
    v[i].z = t->pt[i].z;
  }
*/

  v[0].x = vert[tria.i1].v.x;
  v[0].y = vert[tria.i1].v.y;
  v[0].z = vert[tria.i1].v.z;

  v[1].x = vert[tria.i2].v.x;
  v[1].y = vert[tria.i2].v.y;
  v[1].z = vert[tria.i2].v.z;

  v[2].x = vert[tria.i3].v.x;
  v[2].y = vert[tria.i3].v.y;
  v[2].z = vert[tria.i3].v.z;


  face->setTriangle(v[0], v[1], v[2]);

  face->setColorNumber(dimeLayer::RGBToColor(c));

  // DIME: create a unique handle for this entity.
  const int BUFSIZE = 1024;
  char buf[BUFSIZE];
  const char * handle = model.getUniqueHandle(buf, BUFSIZE);
  
  dimeParam param;
  param.string_data = handle;
  face->setRecord(5, param);

  // DIME: add entity to model
  if (block) {
    block->insertEntity(face);
  }
  else {
    model.addEntity(face);
  }
}

void print_filled_triangle(TRIA & tria, VERT * vert, dimeModel & model, const dimeLayer * layer,
                    dimeBlock * block, COLORREF c)
{
  // filled, create dime3DFace
//  int i;

  // DIME: create a 3DFACE entity, and set it to contain a triangle
  dime3DFace * face = new dime3DFace;
  if (layer) {
    face->setLayer(layer);
  }
  dimeVec3f v[3];

/*
  for (i = 0; i < 3; i++) {
    v[i].x = t->pt[i].x;
    v[i].y = t->pt[i].y;
    v[i].z = t->pt[i].z;
  }
*/

  v[0].x = vert[tria.i1].v.x;
  v[0].y = vert[tria.i1].v.y;
  v[0].z = vert[tria.i1].v.z;

  v[1].x = vert[tria.i2].v.x;
  v[1].y = vert[tria.i2].v.y;
  v[1].z = vert[tria.i2].v.z;

  v[2].x = vert[tria.i3].v.x;
  v[2].y = vert[tria.i3].v.y;
  v[2].z = vert[tria.i3].v.z;


  face->setTriangle(v[0], v[1], v[2]);

  face->setColorNumber(dimeLayer::RGBToColor(c));

  // DIME: create a unique handle for this entity.
  const int BUFSIZE = 1024;
  char buf[BUFSIZE];
  const char * handle = model.getUniqueHandle(buf, BUFSIZE);
  
  dimeParam param;
  param.string_data = handle;
  face->setRecord(5, param);

  // DIME: add entity to model
  if (block) {
    block->insertEntity(face);
  }
  else {
    model.addEntity(face);
  }
}

#include "..\..\surfdoc\src\iso.h"
bool IzoSurface_save_as_3D_dxf(const char * outfile, bool useblock, 
							   const char * layername,
							   double isolevel, Grid4 * cube, COLORREF c, bool view)
{

  // DIME: create dime model
  dimeModel model;

  const dimeLayer * layer = NULL;

  // DIME: only needed if you need your object to be in a layer
  {
    // DIME: add tables section (needed for layers).
    dimeTablesSection * tables = new dimeTablesSection;
    model.insertSection(tables);
    
    // DIME: set up a layer table to store our layers
    dimeTable * layers = new dimeTable(NULL);

	;
    
    // DIME: set up our layers
	add_layer(layername, dimeLayer::RGBToColor(c), &model, layers);


    // DIME: insert the layer in the table
    tables->insertTable(layers); 
	 
	layer = model.getLayer(layername);

  }

  // DIME: only needed if you want to create the sphere as a BLOCK
  dimeBlock * block = NULL;
  if (useblock) {
    dimeBlocksSection * blocks = new dimeBlocksSection;
    model.insertSection(blocks);
    block = new dimeBlock(NULL);
    block->setName("MyBlock");
    blocks->insertBlock(block);
  }

  // DIME: add the entities section.
  dimeEntitiesSection * entities = new dimeEntitiesSection;
  model.insertSection(entities);
	

 
  /* Print out resulting approximation */  
  bool status =  DrawIzoSurfaceToDxf(model, layer, block, isolevel, cube, c, view);

  if (block) {
    dimeInsert * insert = new dimeInsert;
    insert->setBlock(block);
    model.addEntity(insert);
  }
/*
  if (!status)
  {
	  char str[1048];
	  sprintf(str, 
		  "this object (type = %s name = %s)\n"
		  "does not saved into dxf file %s\n", 
		  Object::ObjectTypeToString(doc->GetObjectType()),
		  doc->GetName().c_str(), outfile);
	  MessageBox(0,str, "save_as_dxf(Object * ob, char * outfile)", MB_OK | MB_ICONEXCLAMATION);
	  return false;
  }*/

  // DIME: initialize output file
  dimeOutput out;
  if (!outfile || !out.setFilename(outfile)) {
    out.setFileHandle(stdout);
  }
  // DIME: write the model to file  
  model.write(&out);

  return status;
}
// DIME: needed include files.
class dimeModel;
class dimeTable;
class dimeLayer;
class dimeBlock;
class Object;
class Line3D;
class SSaveProfData;
class CrdTranslator;


static void
add_layer(const char * name, int colnum, dimeModel * model, dimeTable * layers);
/* Output a line */
void print_line(Line3D * line3D, dimeModel * model, dimeBlock * block, CrdTranslator * translator);
bool save_as_dxf(Object * ob, char * outfile, bool useblock, CrdTranslator * translator);
bool cutline_save_as_dxf_razrez(
#if defined (_MSC_VER) && !defined (QT_PROJECT)
        SurfDoc * doc,
#endif
                                char * outfile, bool useblock, SSaveProfData * sprData,
								double a, double b, double c, double d,
								double minX, double minY, double minZ,
								double maxX, double maxY, double maxZ);
void print_filled_triangle(TRIA & tria, VERT * vert, dimeModel & model, const dimeLayer * layer,
                    dimeBlock * block, COLORREF c);
void print_solid_triangle(TRIA & tria, VERT * vert, dimeModel & model, const dimeLayer * layer,
                    dimeBlock * block, COLORREF c);
bool IzoSurface_save_as_3D_dxf(const char * outfile, bool useblock, 
							   const char * layername,
							   double isolevel, Grid4 * cube, COLORREF c, bool view);

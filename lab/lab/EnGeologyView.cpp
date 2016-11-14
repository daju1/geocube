// EnGeologyView.cpp: implementation of the CEnGeologyView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "lab.h"
#include "EnGeologyView.h"

#include "ObjectDialog.h"
#include "DlgProbGrunt.h"
#include "DlgLanguage.h"
#include "DlgProbGr_DblClickMode.h"
#include "DlgStatZond.h"
#include "DlgPalja.h"
#include "DlgPCK2Fiz.h"
#include "DlgZondUstParam.h"
#include "DlgCopyGrunty.h"
#include "DlgIGEList.h"



#include "SetObject.h"
#include "SetKt.h"
#include "SetFizMeh.h"
#include "SetFizMehParam.h"
#include "SetCilce.h"
#include "SetCilce0.h"
#include "SetCompress.h"
//#include "SetIGE0.h"
//#include "SetLito0.h"
#include "SetIGE.h"
#include "SetLito.h"
#include "SetPalja1.h"
#include "SetPtPalja.h"
#include "SetStZond.h"
#include "SetPtStZond.h"
#include "SetZriz0.h"
#include "SetZriz.h"
#include "SetZriz_tbl.h"
#include "SetGranular.h"
#include "SetGrunty.h"
#include "SetProbGr.h"
#include "SetPres.h"
#include "SetPress_tbl.h"
#include "SetShtamp.h"
#include "SetShtamp_detail.h"
#include "SetChemVD.h"
#include "SetChemVD_tbl.h"
#include "SetConsObj.h"
#include "SetVoda.h"
#include "SetPolygons.h"
#include "SetFundament.h"
#include "SetFundament_tbl.h"
#include "SetT_P.h"
#include "SetT_V.h"
#include "SetWopt.h"
#include "SetWopt_tbl.h"
#include "SetRozriz.h"
#include "SetRozrizy1.h"
#include "SetPCK2FizResults.h"
#include "SetPCK2Fiz_CalcMode.h"


#include "SetGeoTables.h"


#include "../geocube_module/wells_draw_list_item_draw_mode_2d.h"


#include "../../surfdoc/src/wellelement.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CEnGeologyView::str_kt_list_order_by = "ID_KT";
CString CEnGeologyView::str_kt_list_where = "ID_OBJ = -1";

void DaoErrorMsg(CDaoException* e);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
IMPLEMENT_DYNCREATE(CEnGeologyView, CFormView)


BEGIN_MESSAGE_MAP(CEnGeologyView, CFormView)
	//{{AFX_MSG_MAP(CEnGeologyView)
	ON_WM_DRAWITEM()
	ON_COMMAND(ID_FILE_NEW, OnFileNewObject)
	ON_COMMAND(ID_FILE_DELETEOBJECT, OnFileDeleteObject)
	ON_UPDATE_COMMAND_UI(ID_FILE_DELETEOBJECT, OnUpdateFileDeleteObject)
	ON_COMMAND(ID_PROBGR_NEWLABNUMBER, OnProbgrNewlabnumber)
	ON_UPDATE_COMMAND_UI(ID_PROBGR_NEWLABNUMBER, OnUpdateProbgrNewlabnumber)
	ON_COMMAND(ID_KT_KTLIST_LOADFORM_NEW, OnKtKtlistLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_LOADFORM_NEW, OnUpdateKtKtlistLoadformNew)
	ON_COMMAND(ID_KT_KTLIST_LOADFORM_EXISTING, OnKtKtlistLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_LOADFORM_EXISTING, OnUpdateKtKtlistLoadformExisting)
	ON_COMMAND(ID_KT_KTLIST_SAVETODB, OnKtKtlistSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_SAVETODB, OnUpdateKtKtlistSavetodb)
	ON_COMMAND(ID_KT_KTLIST_DISCONNECTEXCEL, OnKtKtlistDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_DISCONNECTEXCEL, OnUpdateKtKtlistDisconnectexcel)
	ON_COMMAND(ID_OBJECTS_IMPORTOBJECT, OnObjectsImportobject)
	ON_COMMAND(ID_PROBGR_PASPORT_ALLPOSSIBLE, OnProbgrPasportAllpossible)
	ON_COMMAND(ID_PROBGR_SOILNAME, OnProbgrSoilname)
	ON_COMMAND(ID_PROBGR_PASPORT_LANGUAGE, OnProbgrPasportLanguage)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_COMMAND(ID_PROBYGRUNTA_DBLCLICKMODE, OnProbygruntaDblclickmode)
	ON_COMMAND(ID_PROBGR_CLASSIFICATION, OnProbgrClassification)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_COMPRESS, OnRclickListCompress)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_COMPRESS, OnKeydownListCompress)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_ZRIZ, OnRclickListZriz)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_ZRIZ, OnKeydownListZriz)
	ON_COMMAND(ID_ARCHIVE_LABORATORY_LOADFORM_NEW, OnArchiveLaboratoryLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_LABORATORY_LOADFORM_NEW, OnUpdateArchiveLaboratoryLoadformNew)
	ON_COMMAND(ID_ARCHIVE_LABORATORY_FILL, OnArchiveLaboratoryFill)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_LABORATORY_FILL, OnUpdateArchiveLaboratoryFill)
	ON_COMMAND(ID_ARCHIVE_LABORATORY_SAVETODB, OnArchiveLaboratorySavetodb)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_LABORATORY_SAVETODB, OnUpdateArchiveLaboratorySavetodb)
	ON_COMMAND(ID_ARCHIVE_LABORATORY_DISCONNECTEXCEL, OnArchiveLaboratoryDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_LABORATORY_DISCONNECTEXCEL, OnUpdateArchiveLaboratoryDisconnectexcel)
	ON_COMMAND(ID_ARCHIVE_LABORATORY_LOADFORM_EXISTING, OnArchiveLaboratoryLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_LABORATORY_LOADFORM_EXISTING, OnUpdateArchiveLaboratoryLoadformExisting)
	ON_COMMAND(ID_KT_KTLIST_FILL, OnKtKtlistFill)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_FILL, OnUpdateKtKtlistFill)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_LOADFORM_NEW, OnArchiveCompressionLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_LOADFORM_NEW, OnUpdateArchiveCompressionLoadformNew)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_LOADFORM_EXISTING, OnArchiveCompressionLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_LOADFORM_EXISTING, OnUpdateArchiveCompressionLoadformExisting)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_FILL, OnArchiveCompressionFill)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_FILL, OnUpdateArchiveCompressionFill)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_SAVETODB, OnArchiveCompressionSavetodb)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_SAVETODB, OnUpdateArchiveCompressionSavetodb)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_DISCONNECTEXCEL, OnArchiveCompressionDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_DISCONNECTEXCEL, OnUpdateArchiveCompressionDisconnectexcel)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_FILL2, OnArchiveCompressionFill2)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_FILL2, OnUpdateArchiveCompressionFill2)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_FILLALLLABN, OnArchiveCompressionFillalllabn)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_FILLALLLABN, OnUpdateArchiveCompressionFillalllabn)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_FILLALLLABN2, OnArchiveCompressionFillalllabn2)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_FILLALLLABN2, OnUpdateArchiveCompressionFillalllabn2)
	ON_COMMAND(ID_ARCHIVE_COMPRESSION_FILL_ALLLABN_IF2THEN2, OnArchiveCompressionFillAlllabnIf2then2)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_COMPRESSION_FILL_ALLLABN_IF2THEN2, OnUpdateArchiveCompressionFillAlllabnIf2then2)
	ON_COMMAND(ID_ARCHIVE_CUT_LOADFORM_NEW, OnArchiveCutLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_LOADFORM_NEW, OnUpdateArchiveCutLoadformNew)
	ON_COMMAND(ID_ARCHIVE_CUT_LOADFORM_EXISTING, OnArchiveCutLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_LOADFORM_EXISTING, OnUpdateArchiveCutLoadformExisting)
	ON_COMMAND(ID_ARCHIVE_CUT_FILL_CUT, OnArchiveCutFillCut)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_FILL_CUT, OnUpdateArchiveCutFillCut)
	ON_COMMAND(ID_ARCHIVE_CUT_FILL_ALLLABN, OnArchiveCutFillAlllabn)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_FILL_ALLLABN, OnUpdateArchiveCutFillAlllabn)
	ON_COMMAND(ID_ARCHIVE_CUT_SAVETODB, OnArchiveCutSavetodb)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_SAVETODB, OnUpdateArchiveCutSavetodb)
	ON_COMMAND(ID_ARCHIVE_CUT_DISCONNECTEXCEL, OnArchiveCutDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_DISCONNECTEXCEL, OnUpdateArchiveCutDisconnectexcel)
	ON_COMMAND(ID_ARCHIVE_CUT_FILL_ALLLABN2, OnArchiveCutFillAlllabn2)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_FILL_ALLLABN2, OnUpdateArchiveCutFillAlllabn2)
	ON_COMMAND(ID_ARCHIVE_GRAN_LOADFORM_NEW, OnArchiveGranLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_GRAN_LOADFORM_NEW, OnUpdateArchiveGranLoadformNew)
	ON_COMMAND(ID_ARCHIVE_GRAN_LOADFORM_EXISTING, OnArchiveGranLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_GRAN_LOADFORM_EXISTING, OnUpdateArchiveGranLoadformExisting)
	ON_COMMAND(ID_ARCHIVE_GRAN_FILL_GRAN, OnArchiveGranFillGran)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_GRAN_FILL_GRAN, OnUpdateArchiveGranFillGran)
	ON_COMMAND(ID_ARCHIVE_GRAN_FILL_ALLLABN, OnArchiveGranFillAlllabn)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_GRAN_FILL_ALLLABN, OnUpdateArchiveGranFillAlllabn)
	ON_COMMAND(ID_ARCHIVE_GRAN_SAVETODB, OnArchiveGranSavetodb)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_GRAN_SAVETODB, OnUpdateArchiveGranSavetodb)
	ON_COMMAND(ID_ARCHIVE_GRAN_DISCONNECTEXCEL, OnArchiveGranDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_GRAN_DISCONNECTEXCEL, OnUpdateArchiveGranDisconnectexcel)
	ON_COMMAND(ID_EXCEL_KILL, OnExcelKill)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_GRANULAR, OnRclickListGranular)
	ON_COMMAND(ID_OBJECTS_SETNABORGRUNTOV, OnObjectsSetnaborgruntov)
	ON_COMMAND(ID_KT_STATZOND, OnKtStatzond)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND, OnUpdateKtStatzond)
	ON_COMMAND(ID_KT_PALJA, OnKtPalja)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA, OnUpdateKtPalja)
	ON_COMMAND(ID_KT_STATZOND_LOADFORM_NEW, OnKtStatzondLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND_LOADFORM_NEW, OnUpdateKtStatzondLoadformNew)
	ON_COMMAND(ID_KT_STATZOND_LOADFORM_EXISTING, OnKtStatzondLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND_LOADFORM_EXISTING, OnUpdateKtStatzondLoadformExisting)
	ON_COMMAND(ID_KT_STATZOND_FILL, OnKtStatzondFill)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND_FILL, OnUpdateKtStatzondFill)
	ON_COMMAND(ID_KT_STATZOND_SAVETODB, OnKtStatzondSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND_SAVETODB, OnUpdateKtStatzondSavetodb)
	ON_COMMAND(ID_KT_STATZOND_DISCONNECTEXCEL, OnKtStatzondDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND_DISCONNECTEXCEL, OnUpdateKtStatzondDisconnectexcel)
	ON_COMMAND(ID_KT_PALJA_LOADFORM_NEW, OnKtPaljaLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA_LOADFORM_NEW, OnUpdateKtPaljaLoadformNew)
	ON_COMMAND(ID_KT_PALJA_LOADFORM_EXISTING, OnKtPaljaLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA_LOADFORM_EXISTING, OnUpdateKtPaljaLoadformExisting)
	ON_COMMAND(ID_KT_PALJA_FILL, OnKtPaljaFill)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA_FILL, OnUpdateKtPaljaFill)
	ON_COMMAND(ID_KT_PALJA_COMPUTE, OnKtPaljaCompute)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA_COMPUTE, OnUpdateKtPaljaCompute)
	ON_COMMAND(ID_KT_PALJA_SAVETODB, OnKtPaljaSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA_SAVETODB, OnUpdateKtPaljaSavetodb)
	ON_COMMAND(ID_KT_PALJA_DISCONNECTEXCEL, OnKtPaljaDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_PALJA_DISCONNECTEXCEL, OnUpdateKtPaljaDisconnectexcel)
	ON_COMMAND(ID_KT_STATZOND_COMPUTE, OnKtStatzondCompute)
	ON_UPDATE_COMMAND_UI(ID_KT_STATZOND_COMPUTE, OnUpdateKtStatzondCompute)
	ON_COMMAND(ID_KT_ZONDUSTPARAM, OnKtZondustparam)
	ON_COMMAND(ID_OBJECTS_COPYGRUNTY, OnObjectsCopygrunty)
	ON_COMMAND(ID_ARCHIVE_CUT_FILL_CUTAS2COLOMNS, OnArchiveCutFillCutas2colomns)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_FILL_CUTAS2COLOMNS, OnUpdateArchiveCutFillCutas2colomns)
	ON_COMMAND(ID_ARCHIVE_CUT_FILL_ALLLABNAS2COLOMNS, OnArchiveCutFillAlllabnas2colomns)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CUT_FILL_ALLLABNAS2COLOMNS, OnUpdateArchiveCutFillAlllabnas2colomns)
	ON_COMMAND(ID_KT_ALLPALJA, OnKtAllpalja)
	ON_COMMAND(ID_ARCHIVE_DELETEALLCUTS, OnArchiveDeleteallcuts)
	ON_COMMAND(ID_ARCHIVE_DELETEALLCOMPRESSIONS, OnArchiveDeleteallcompressions)
	ON_COMMAND(ID_KT_ROZRIZLIST_LOADFORM_NEW, OnKtRozrizlistLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_ROZRIZLIST_LOADFORM_NEW, OnUpdateKtRozrizlistLoadformNew)
	ON_COMMAND(ID_KT_ROZRIZLIST_LOADFORM_EXISTING, OnKtRozrizlistLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_ROZRIZLIST_LOADFORM_EXISTING, OnUpdateKtRozrizlistLoadformExisting)
	ON_COMMAND(ID_KT_ROZRIZLIST_FILL, OnKtRozrizlistFill)
	ON_UPDATE_COMMAND_UI(ID_KT_ROZRIZLIST_FILL, OnUpdateKtRozrizlistFill)
	ON_COMMAND(ID_KT_ROZRIZLIST_SAVETODB, OnKtRozrizlistSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_ROZRIZLIST_SAVETODB, OnUpdateKtRozrizlistSavetodb)
	ON_COMMAND(ID_KT_ROZRIZLIST_DISCONNECTEXCEL, OnKtRozrizlistDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_ROZRIZLIST_DISCONNECTEXCEL, OnUpdateKtRozrizlistDisconnectexcel)
	ON_COMMAND(ID_ARCHIVE_DELETEALLGRANULARS, OnArchiveDeleteallgranulars)
	ON_COMMAND(ID_ARCHIVE_DELETEALLFIZMEH, OnArchiveDeleteallfizmeh)
	ON_NOTIFY(LVN_KEYDOWN, IDC_LIST_EN_GEO_OBJECTS, OnKeydownListEnGeoObjects)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_EN_GEO_OBJECTS, OnItemchangedListEnGeoObjects)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_KT, OnItemchangedListKt)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_SOIL, OnItemchangedListSoil)
	ON_COMMAND(ID_KT_PCK2FIZ, OnKtPck2fiz)
	ON_COMMAND(ID_KT_TSZLIST_LOADFORM_NEW, OnKtTszlistLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_TSZLIST_LOADFORM_NEW, OnUpdateKtTszlistLoadformNew)
	ON_COMMAND(ID_KT_TSZLIST_LOADFORM_EXISTING, OnKtTszlistLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_TSZLIST_LOADFORM_EXISTING, OnUpdateKtTszlistLoadformExisting)
	ON_COMMAND(ID_KT_TSZLIST_FILL, OnKtTszlistFill)
	ON_UPDATE_COMMAND_UI(ID_KT_TSZLIST_FILL, OnUpdateKtTszlistFill)
	ON_COMMAND(ID_KT_TSZLIST_SAVETODB, OnKtTszlistSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_TSZLIST_SAVETODB, OnUpdateKtTszlistSavetodb)
	ON_COMMAND(ID_KT_TSZLIST_DISCONNECTEXCEL, OnKtTszlistDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_TSZLIST_DISCONNECTEXCEL, OnUpdateKtTszlistDisconnectexcel)
	ON_COMMAND(ID_KT_DXFROZRIZLIST_LOADFORM_NEW, OnKtDxfrozrizlistLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_DXFROZRIZLIST_LOADFORM_NEW, OnUpdateKtDxfrozrizlistLoadformNew)
	ON_COMMAND(ID_KT_DXFROZRIZLIST_LOADFORM_EXISTING, OnKtDxfrozrizlistLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_DXFROZRIZLIST_LOADFORM_EXISTING, OnUpdateKtDxfrozrizlistLoadformExisting)
	ON_COMMAND(ID_KT_DXFROZRIZLIST_FILL, OnKtDxfrozrizlistFill)
	ON_UPDATE_COMMAND_UI(ID_KT_DXFROZRIZLIST_FILL, OnUpdateKtDxfrozrizlistFill)
	ON_COMMAND(ID_KT_DXFROZRIZLIST_SAVETODB, OnKtDxfrozrizlistSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_DXFROZRIZLIST_SAVETODB, OnUpdateKtDxfrozrizlistSavetodb)
	ON_COMMAND(ID_KT_DXFROZRIZLIST_DISCONNECTEXCEL, OnKtDxfrozrizlistDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_DXFROZRIZLIST_DISCONNECTEXCEL, OnUpdateKtDxfrozrizlistDisconnectexcel)
	ON_COMMAND(ID_KT_HYDROLIST_LOADFORM_NEW, OnKtHydrolistLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_KT_HYDROLIST_LOADFORM_NEW, OnUpdateKtHydrolistLoadformNew)
	ON_COMMAND(ID_KT_HYDROLIST_LOADFORM_EXISTING, OnKtHydrolistLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_KT_HYDROLIST_LOADFORM_EXISTING, OnUpdateKtHydrolistLoadformExisting)
	ON_COMMAND(ID_KT_HYDROLIST_SAVETODB, OnKtHydrolistSavetodb)
	ON_UPDATE_COMMAND_UI(ID_KT_HYDROLIST_SAVETODB, OnUpdateKtHydrolistSavetodb)
	ON_COMMAND(ID_KT_HYDROLIST_DISCONNECTEXCEL, OnKtHydrolistDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_KT_HYDROLIST_DISCONNECTEXCEL, OnUpdateKtHydrolistDisconnectexcel)
	ON_COMMAND(ID_KT_KTLIST_SAVEANDRENAME, OnKtKtlistSaveandrename)
	ON_UPDATE_COMMAND_UI(ID_KT_KTLIST_SAVEANDRENAME, OnUpdateKtKtlistSaveandrename)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_DB_TABLES, OnItemchangedListDbTables)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_IGE, OnRclickListIge)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST_IGE, OnItemchangedListIge)
	ON_COMMAND(ID_PROBGR_IGEAUTOFILL, OnProbgrIgeautofill)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST_KT, OnColumnclickListKt)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_SOIL, OnRclickListSoil)
	ON_COMMAND(ID_VIEW_PROPERTYWINDOWWITH_PLOT, OnViewPropertywindowwithPlot)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOWWITH_PLOT, OnUpdateViewPropertywindowwithPlot)
	ON_COMMAND(ID_VIEW_PROPERTYWINDOWWITH_RESULTS, OnViewPropertywindowwithResults)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOWWITH_RESULTS, OnUpdateViewPropertywindowwithResults)
	ON_COMMAND(ID_VIEW_PROPERTYWINDOWWITH_LABNUMBERTRIALLIST, OnViewPropertywindowwithLabnumbertriallist)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOWWITH_LABNUMBERTRIALLIST, OnUpdateViewPropertywindowwithLabnumbertriallist)
	ON_COMMAND(ID_VIEW_PROPERTYWINDOWWITH_NORMATIVES, OnViewPropertywindowwithNormatives)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOWWITH_NORMATIVES, OnUpdateViewPropertywindowwithNormatives)
	ON_COMMAND(ID_VIEW_PROPERTYWINDOWWITH_CORRELATION, OnViewPropertywindowwithCorrelation)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOWWITH_CORRELATION, OnUpdateViewPropertywindowwithCorrelation)
	ON_COMMAND(ID_VIEW_PROPERTYWINDOWWITH_NORMATIVESBYALLEXPERIENCES, OnViewPropertywindowwithNormativesbyallexperiences)
	ON_UPDATE_COMMAND_UI(ID_VIEW_PROPERTYWINDOWWITH_NORMATIVESBYALLEXPERIENCES, OnUpdateViewPropertywindowwithNormativesbyallexperiences)
	ON_UPDATE_COMMAND_UI(ID_PROBGR_PASPORT_OTNOSITDEFONGRAPH, OnUpdateProbgrPasportOtnositdefongraph)
	ON_COMMAND(ID_PROBGR_PASPORT_OTNOSITDEFONGRAPH, OnProbgrPasportOtnositdefongraph)
	ON_COMMAND(ID_OBJECTS_NABORIGE, OnObjectsNaborige)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_NEW, OnProbygruntaLabnumbersLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_NEW, OnUpdateProbygruntaLabnumbersLoadformNew)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_EXISTING, OnProbygruntaLabnumbersLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_LOADFORM_EXISTING, OnUpdateProbygruntaLabnumbersLoadformExisting)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_FILL, OnProbygruntaLabnumbersFill)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_FILL, OnUpdateProbygruntaLabnumbersFill)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_SAVETODB, OnProbygruntaLabnumbersSavetodb)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_SAVETODB, OnUpdateProbygruntaLabnumbersSavetodb)
	ON_COMMAND(ID_PROBYGRUNTA_LABNUMBERS_DISCONNECTEXCEL, OnProbygruntaLabnumbersDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_PROBYGRUNTA_LABNUMBERS_DISCONNECTEXCEL, OnUpdateProbygruntaLabnumbersDisconnectexcel)
	ON_COMMAND(ID_PROBGR_EXCLUDEDTRIALLIST, OnProbgrExcludedtriallist)
	ON_COMMAND(ID_PROBGR_SOILAUTONAMES, OnProbgrSoilautonames)
	ON_COMMAND(ID_EXCEL_TODISSCONNECTWHENLOADFORM_G, OnExcelTodissconnectwhenloadform)
	ON_UPDATE_COMMAND_UI(ID_EXCEL_TODISSCONNECTWHENLOADFORM_G, OnUpdateExcelTodissconnectwhenloadformG)
	ON_COMMAND(ID_EXCEL_AUTOMATICSAVEWHENDISCONNECT, OnExcelAutomaticsavewhendisconnect)
	ON_UPDATE_COMMAND_UI(ID_EXCEL_AUTOMATICSAVEWHENDISCONNECT, OnUpdateExcelAutomaticsavewhendisconnect)
	ON_COMMAND(ID_FILE_3D, OnFile3d)
	ON_UPDATE_COMMAND_UI(ID_FILE_3D, OnUpdateFile3d)
	ON_COMMAND(ID_ARCHIVE_CASPGEO_LOADFORM_NEW, OnArchiveCaspgeoLoadformNew)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CASPGEO_LOADFORM_NEW, OnUpdateArchiveCaspgeoLoadformNew)
	ON_COMMAND(ID_ARCHIVE_CASPGEO_LOADFORM_EXISTING, OnArchiveCaspgeoLoadformExisting)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CASPGEO_LOADFORM_EXISTING, OnUpdateArchiveCaspgeoLoadformExisting)
	ON_COMMAND(ID_ARCHIVE_CASPGEO_FILL, OnArchiveCaspgeoFill)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CASPGEO_FILL, OnUpdateArchiveCaspgeoFill)
	ON_COMMAND(ID_ARCHIVE_CASPGEO_SAVETODB, OnArchiveCaspgeoSavetodb)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CASPGEO_SAVETODB, OnUpdateArchiveCaspgeoSavetodb)
	ON_COMMAND(ID_ARCHIVE_CASPGEO_DISCONNECTEXCEL, OnArchiveCaspgeoDisconnectexcel)
	ON_UPDATE_COMMAND_UI(ID_ARCHIVE_CASPGEO_DISCONNECTEXCEL, OnUpdateArchiveCaspgeoDisconnectexcel)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview)
END_MESSAGE_MAP()



CEnGeologyView::CEnGeologyView() : CFormView(CEnGeologyView::IDD) 
{
	m_EnGeoObjectsList.m_geo_view = this;
	m_DataBaseTablesList.m_geo_view = this;
	m_KTList.m_geo_view = this;
	m_IGEList.m_geo_view = this;
	m_LithoList.m_geo_view = this;
	m_VodaList.m_geo_view = this;
	m_TSZList.m_geo_view = this;
	m_PaljaList.m_geo_view = this;
	m_ListView.m_geo_view = this;
	m_SoilsList.m_geo_view = this;
	m_ZrizList.m_geo_view = this;
	m_CompressList.m_geo_view = this;
	m_FizMehList.m_geo_view = this;
	m_GranularList.m_geo_view = this;
//	m_PropList.m_geo_view = this;

	this->m_nCompItem = -1;
	this->m_nCutItem  = -1;
	this->m_nObjectItem = -1;
	//this->m_nIGEItem = -1;
	this->m_ID_IGE = -1;

	this->to_draw = true;
}

CEnGeologyView::~CEnGeologyView()
{

}
void CEnGeologyView::DisconnectAllExcels()
{
	OnKtKtlistDisconnectexcel();
	OnKtHydrolistDisconnectexcel();
	OnKtRozrizlistDisconnectexcel();
	OnKtDxfrozrizlistDisconnectexcel();

	OnKtStatzondDisconnectexcel();
	OnKtTszlistDisconnectexcel();

	OnProbygruntaLabnumbersDisconnectexcel();

	OnArchiveLaboratoryDisconnectexcel();
	OnArchiveCompressionDisconnectexcel();
	OnArchiveCutDisconnectexcel();
	OnArchiveGranDisconnectexcel();
}
void CEnGeologyView::PostNcDestroy() 
{
	// TODO: Add your specialized code here and/or call the base class
	DisconnectAllExcels();
	
	CFormView::PostNcDestroy();
}


void CEnGeologyView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CEnGeologyView)
	DDX_Control(pDX, IDC_LIST_ZRIZ, m_ZrizList);
	DDX_Control(pDX, IDC_LIST_PROP, m_FizMehList);
	DDX_Control(pDX, IDC_LIST_COMPRESS, m_CompressList);
	DDX_Control(pDX, IDC_LIST_GRANULAR, m_GranularList);
	DDX_Control(pDX, IDC_LIST_SOIL, m_SoilsList);
	DDX_Control(pDX, IDC_LIST_VIEW, m_ListView);
	DDX_Control(pDX, IDC_LIST_KT, m_KTList);
	DDX_Control(pDX, IDC_LIST_IGE, m_IGEList);
	DDX_Control(pDX, IDC_LIST_LITHO, m_LithoList);
	DDX_Control(pDX, IDC_LIST_VODA, m_VodaList);
	DDX_Control(pDX, IDC_LIST_TSZ, m_TSZList);
	DDX_Control(pDX, IDC_LIST_PALJA, m_PaljaList);
	DDX_Control(pDX, IDC_LIST_DB_TABLES, m_DataBaseTablesList);
	DDX_Control(pDX, IDC_LIST_EN_GEO_OBJECTS, m_EnGeoObjectsList);
	//}}AFX_DATA_MAP
}

BOOL CEnGeologyView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}


void CEnGeologyView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	ResizeParentToFit();

//	this->m_EnGeoObjectsList.OnInitialUpdate();

	this->m_EnGeoObjectsList.OnInitCtrl();
	this->m_DataBaseTablesList.OnInitCtrl();
	this->m_KTList.OnInitCtrl();
	this->m_IGEList.OnInitCtrl();
	this->m_LithoList.OnInitCtrl();
	this->m_VodaList.OnInitCtrl();
	this->m_TSZList.OnInitCtrl();
	this->m_PaljaList.OnInitCtrl();
	this->m_ListView.OnInitCtrl();
	this->m_SoilsList.OnInitCtrl();
	this->m_FizMehList.OnInitCtrl();
	this->m_CompressList.OnInitCtrl();
	this->m_ZrizList.OnInitCtrl();
	this->m_GranularList.OnInitCtrl();

	CLabDoc * lab_doc = this->GetDocument();
	if (lab_doc)
	{
		lab_doc->FirstOdbcConnect();

		this->m_DBTableCilce0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableCilce.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableCompress.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableZriz0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableZriz.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableZriz_tbl.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableProp.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGranular.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSoils.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableKT.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableRozrizy.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableRozriz.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableLito0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableIGE0.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableLito.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableIGE.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGrunty.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableVoda.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGenezis.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableUmPoz.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableCubeSize.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGridDataUsedAlg.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableGridData.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableGridDataSurfaces.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableSurfIgeMapping.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSurfLitoMapping.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTableSurfacesOrder.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSurfacesBlankOrder.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableSurfacesBlankFunctions.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTablePCK2Fiz_Params.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTablePCK2Fiz_Results.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTablePtStZond.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTableStZond.Init(lab_doc, &lab_doc->m_database);

		this->m_DBTablePtPalja.Init(lab_doc, &lab_doc->m_database);
		this->m_DBTablePalja.Init(lab_doc, &lab_doc->m_database);
	}

	this->m_excel_palja.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_stat_zond.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_stat_zond_output.output = true;
	this->m_excel_stat_zond_output.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_ktlist.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_labnlist.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_hydro_list.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_dxf_rozriz_list.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_rozriz_list.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_tsz_list.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_casp_geo_archive.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_lab_archive.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_compression_archive.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_cut_archive.Init(this, lab_doc, &lab_doc->m_database);
	this->m_excel_gran_archive.Init(this, lab_doc, &lab_doc->m_database);	
}

/////////////////////////////////////////////////////////////////////////////
// CLabView printing

BOOL CEnGeologyView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CEnGeologyView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CEnGeologyView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CEnGeologyView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

#ifdef _DEBUG
void CEnGeologyView::AssertValid() const
{
	CFormView::AssertValid();
}

void CEnGeologyView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CEnGeologyDoc* CEnGeologyView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CEnGeologyDoc)));
	//return (CLabDoc*)m_pDocument;

	return dynamic_cast<CEnGeologyDoc*>(m_pDocument);

}
#endif //_DEBUG
CLabDoc * CEnGeologyView::GetLabDoc()
{
	return this->GetDocument();
}

void CEnGeologyView::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	switch(nIDCtl)
	{
	case IDC_LIST_ZRIZ:
		this->m_ZrizList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_COMPRESS:
		this->m_CompressList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_PROP:
		this->m_FizMehList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_GRANULAR:
		this->m_GranularList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_SOIL:
		this->m_SoilsList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_VIEW:
		this->m_ListView.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_KT:
		this->m_KTList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_IGE:
		this->m_IGEList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_LITHO:
		this->m_LithoList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_VODA:
		this->m_VodaList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_TSZ:
		this->m_TSZList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_PALJA:
		this->m_PaljaList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_DB_TABLES:
		this->m_DataBaseTablesList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	case IDC_LIST_EN_GEO_OBJECTS:
		this->m_EnGeoObjectsList.OnDrawItem(nIDCtl, lpDrawItemStruct);
		break;
	}
}

bool GetObjectName(CDatabase * database, long id_obj, CString & contract, CString & object_name)
{
	CString strQuery;
	strQuery.Format("select * from [Objects]");	

	CString where;
	where.Format("ID_OBJ = %ld", id_obj);

	CRecordset * _pRecordset = new CRecordset(database);


	try {
		_pRecordset->m_strFilter = where;
		_pRecordset->Open(CRecordset::dynaset, strQuery, CRecordset::readOnly);
	}
	catch (CDBException* pe) {
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		_pRecordset->Close();
		delete _pRecordset;
		return false;
	}

	if (!_pRecordset->IsBOF())
	{
		_pRecordset->MoveFirst();
		
		CDBVariant _var1; // must declare this inside the loop
		_pRecordset->GetFieldValue("NAZVA", _var1);
		object_name = CMyListCtrl::GetFieldString(_var1);

		CDBVariant _var2; // must declare this inside the loop
		_pRecordset->GetFieldValue("CONTRACT", _var2);
		contract = CMyListCtrl::GetFieldString(_var2);
	}
	

	_pRecordset->Close();

	delete _pRecordset;

	return true;
}

void CEnGeologyView::EnableObjectList(BOOL bEnable)
{
	this->m_EnGeoObjectsList.EnableWindow(bEnable);
}
int CEnGeologyView::GetObjectItem()
{
	return this->m_EnGeoObjectsList.GetSelected();
}
int CEnGeologyView::GetIGEItem()
{
	return this->m_IGEList.GetSelected();
}

int CEnGeologyView::GetKTItem()
{
	return this->m_KTList.GetSelected();
}
int CEnGeologyView::GetProbGrItem()
{
	return this->m_SoilsList.GetSelected();
}
#include "./../wintools/src/winsurf.h"

void CEnGeologyView::OnFile3d() 
{
	int nObItem = this->GetObjectItem();

	if (nObItem > -1)
	{
		if (!this->GetDocument()->dll_w_project)
			this->GetDocument()->dll_w_project = new dll_win_project(this->GetDocument());

		if (this->GetDocument()->dll_w_project)
		{
			if (!this->GetDocument()->dll_w_project->Have_WinProject_Window())
			{
				if (this->GetDocument()->dll_w_project->dll_WinSurf())
				{
					this->ObjectsInsertto3d();
					StartWinSurfLoop();
				}
			}
			else
			{
				if (this->m_nObjectItem != nObItem)
				{
					this->GetDocument()->dll_w_project->delete_Window_WinProject();
					if (this->GetDocument()->dll_w_project->dll_WinSurf())
					{
						this->ObjectsInsertto3d();
						StartWinSurfLoop();
					}
				}
			}
		}
	}
	else
	{
		MessageBox("Не выбран объект");
	}
}	
bool CEnGeologyView::DefineZoom(long ID_OBJ)
{
	try
	{
		SetObject setObject(&this->GetLabDoc()->m_database);
		setObject.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		if ( !setObject.Open(CRecordset::dynaset) )
			return false;


		if (!setObject.IsBOF()) 
		{
			setObject.MoveFirst();
			if(!setObject.IsEOF()) 
			{
				if (this->GetDocument() && this->GetDocument()->dll_w_project)
				{
					this->GetDocument()->dll_w_project->DefineZoom(setObject.m_zoomCoefXYZ, setObject.m_zoomCoefXY);
				}			
			}
		}
	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return false;
	}
}
void CEnGeologyView::ObjectsInsertto3d() 
{
	int nItem = this->GetObjectItem();

	if (nItem > -1)
	{
		if (this->GetDocument())
		{
			bool use_compression3 = false;
			//if (IDYES == ::MessageBox(0, "Вы хотите загрузить компрессионные испытания\n в природном и заданном состоянии\n на один график?", 
			//	"Загрузка файла LAB", MB_YESNO))
			//{
				use_compression3 = true;
			//}

			long id_obj;
			CString contract;
			CString object_name;
					
			CString where;

			wells_draw_list_item * wdli_podoshva_lito = NULL;
			wells_draw_list_item * wdli_podoshva_ige = NULL;
			wells_draw_list_item * wdli_hydro = NULL;

			bool fill_well_colomn = true;

			if (fill_well_colomn)
			{
				bool podoshva = false;
				bool hydro = false;

				// проверка наличия подошв IGE и гидропроявлений в базе
				/*
				for( vector<int>::iterator iter_types_col = lpDrillsDlgMem->types_of_colomns->begin(); 
					iter_types_col != lpDrillsDlgMem->types_of_colomns->end(); iter_types_col++)
				{
					switch (*iter_types_col)
					{
					case WELL_COLOMN_TYPE_0:// this colomn not used
						break;
					case WELL_COLOMN_TYPE_1: //well ID value
						break;
					case WELL_COLOMN_TYPE_X://X
						break;
					case WELL_COLOMN_TYPE_Y://Y
						break;
					case WELL_COLOMN_TYPE_4://ustje altitude
						break;
					case WELL_COLOMN_TYPE_5://sloi podoshva altitude WellColomn * w_colomn = this->AddWellColomn(WellElement::type::IGE_podoshva);w_colomn->check_draw = true;w_colomn->draw_width = 4.f;
					case WELL_COLOMN_TYPE_6://sloi podoshva glubina
						podoshva = true;
						break;
					case WELL_COLOMN_TYPE_7://zaboj altitude
						break;
					case WELL_COLOMN_TYPE_8://zaboj glubina
						break;
					case WELL_COLOMN_TYPE_9:// karotazh
						break;
					case WELL_COLOMN_TYPE_10: //WellElement::type::hydro_projavlenie
					case WELL_COLOMN_TYPE_11: //WellElement::type::hydro_projavlenie
						hydro = true;
						break;
					}
				}
				*/
				hydro = true;	
				podoshva = true;
				if (podoshva)
				{
					wdli_podoshva_lito = this->GetDocument()->dll_w_project->AddWellsDraw(WellElement::type::litho_podoshva, true, 30.f, false, draw_mode_2d_right);
					wdli_podoshva_ige = this->GetDocument()->dll_w_project->AddWellsDraw(WellElement::type::IGE_podoshva, true, 20.f, false, draw_mode_2d_left);
				}
				if (hydro) wdli_hydro = this->GetDocument()->dll_w_project->AddWellsDraw(WellElement::type::hydro_projavlenie, true, 60.f, true, draw_mode_2d_both);
			}


			//Загрузка скважин
			ATable * ObjectsTable = this->GetDocument()->m_tables[table_key_Objects];
			if(ObjectsTable)
			{
				CDBVariant var;
				CODBCFieldInfo fi;
				if(ObjectsTable->m_pRecordset)
				{
					ObjectsTable->m_pRecordset->SetAbsolutePosition(nItem+1);
					ObjectsTable->m_pRecordset->GetFieldValue(short(0), var);
					ObjectsTable->m_pRecordset->GetODBCFieldInfo(short(0), fi);
					
					id_obj = var.m_lVal;

					DefineZoom(id_obj);

					where.Format("%s = %d", fi.m_strName, id_obj);
					where.Format("ID_OBJ = %d", id_obj);

					//AfxMessageBox(where); // "ID_OBJ = 2"
					GetObjectName(&this->GetDocument()->m_database, id_obj, contract, object_name);


					CString order_by;
					order_by.Format("ID_TYP, ID_KT, DTBUR");
					order_by.Format("NAZVA");

					this->m_DBTableKT.m_wdli_podoshva_lito = wdli_podoshva_lito;
					this->m_DBTableKT.m_wdli_podoshva_ige = wdli_podoshva_ige;
					this->m_DBTableKT.m_wdli_hydro = wdli_hydro;
					
				
					this->m_DBTableKT.Enum(where, order_by); 
					//this->lab_doc->dll_w_project->AddWell(id_kt, nazva, kt_idtyp, X, Y, Z, Z, id_bur, d_bur, dtbur.GetBuffer(dtbur.GetLength()));


					if (this->GetDocument()->dll_w_project)
					{
						if(to_draw) this->GetDocument()->dll_w_project->DrawWells();
					}
				}
			}

			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->Set_ID_OBJ(id_obj);
			}

			CString order_by = "";
			order_by = "";

			if (this->to_draw)
			{
				// Загружаем гриддату
				this->m_DBTableGridDataSurfaces.Enum(where, order_by);
				this->m_DBTableGridData.Enum(where, order_by);

				if (this->GetDocument()->dll_w_project)
				{
					this->GetDocument()->dll_w_project->ApplyGridData();
				}

				//гриддату мы загрузили перед лито колонкой,
				//потому что инициализация литоколонки требует инициализации ссылок на гриддату
				//которые ищутся алгоритмом поиска по массиву гриддаты координатам её точек
			}

			// загрузка геоинженерных элементов

			// Нужны колонки: геологическая и геотехническая 
			// которые в сумме дадут инженерно-геологическую


			// литологическая колонка - не корректируется вручную на разрезе
			// служит для сохранения данных бурения
			this->m_DBTableLito0.Enum(where, order_by);
			this->m_DBTableIGE0.Enum(where, order_by);
			// инженерно-геологическая колонка
			// коррректируется на разрезах
			this->m_DBTableLito.Enum(where, order_by);
			this->m_DBTableIGE.Enum(where, order_by);
			this->m_DBTableGrunty.Enum(where, order_by);
			this->m_DBTableGenezis.Enum("", "ID_GENEZIS");
			this->m_DBTableUmPoz.Enum("", "ID_UMPOZ");


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ApplyLito();
			}

			this->m_DBTableVoda.Enum(where, order_by);

			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ApplyVoda();
			}

			if (this->to_draw)
			{
				// размер куба 
				this->m_DBTableCubeSize.Enum(where, order_by);

				this->m_DBTableSurfIgeMapping.Enum(where, order_by);
				this->m_DBTableSurfLitoMapping.Enum(where, order_by);

				// устанавливаем порядок перечисления поверхностей
				this->m_DBTableSurfacesOrder.Enum(where, "NPP");
				this->m_DBTableSurfacesBlankOrder.Enum(where, "NPP");
				this->m_DBTableSurfacesBlankFunctions.Enum(where, "ID_SURF_OBJ, ID_SURF_PARAM");

				if (this->GetDocument()->dll_w_project)
					this->GetDocument()->dll_w_project->MySurfer_skip_next_alert();

				//и по заданныи алгоритмам формируем поверхности 
				this->m_DBTableGridDataUsedAlg.Enum(where, "ID_SURF");

				if (this->GetDocument()->dll_w_project)
					this->GetDocument()->dll_w_project->MySurfer_set_next_alert();

				if (this->GetDocument()->dll_w_project)
				{
					//имена поверхностей прописываем в списках перечисления поверхностей
					//ищем по построенным поверхностям
					this->GetDocument()->dll_w_project->ApplySurfacesOrder();
				}

				// обрезаем поверхности в соответствие с пордком автобланкования
				if (this->GetDocument()->dll_w_project)
				{
					this->GetDocument()->dll_w_project->SurfacesAutoBlank();
				}
			}
			// загрузка колонки лабораторных анализов


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->AddNewWellColomn_LaboratoryAnalizes_FromDB(id_obj, contract, object_name);
			}


			//Загрузка лабораторных номеров


			this->m_DBTableSoils.Enum(where, order_by);


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->AddNewWellColomn_LaboratoryAnalizes_FromDB_2();
			}


			// 


			order_by = "";

			this->m_DBTableGranular.Enum(where, order_by);


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ApplyGranular();
			}


			order_by = "";

			this->m_DBTableProp.Enum(where, order_by);


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ApplyProps();
			}


			order_by = "";
			this->m_DBTableZriz_tbl.Enum(where, order_by);
			this->m_DBTableZriz.Enum(where, order_by);
			this->m_DBTableZriz0.Enum(where, order_by);


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ApplyZriz();
			}



			order_by = "";
			this->m_DBTableCilce0.Enum(where, order_by);
			this->m_DBTableCilce.Enum(where, order_by);
			this->m_DBTableCompress.Enum(where, order_by);


			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ApplyCompress(use_compression3);
			}






			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->ParseTrialIndications();
			}




			if (this->to_draw)
			{
				order_by = "";
				this->m_DBTablePCK2Fiz_Params.Enum("", order_by);
				this->m_DBTablePCK2Fiz_Results.Enum(where, order_by);
				this->m_DBTablePtStZond.Enum(where, order_by);
				this->m_DBTableStZond.Enum(where, order_by);


				if (this->GetDocument()->dll_w_project)
				{
					this->GetDocument()->dll_w_project->ApplyStZond();
				}



				order_by = "";
				this->m_DBTablePtPalja.Enum(where, order_by);
				this->m_DBTablePalja.Enum(where, order_by);


				if (this->GetDocument()->dll_w_project)
				{
					this->GetDocument()->dll_w_project->ApplyPalja();
				}

				order_by = "";
				this->m_DBTableRozrizy.Enum(where, order_by);
				this->m_DBTableRozriz.Enum(where, order_by);


				if (this->GetDocument()->dll_w_project)
				{
					if(this->to_draw) this->GetDocument()->dll_w_project->ApplyRozriz();
				}

			}

			double _pressure_interval_01_02_0 = 0.1;

			if (this->GetDocument()->dll_w_project)
			{
				this->GetDocument()->dll_w_project->AfterExportFromDB(_pressure_interval_01_02_0);
			}

			m_nObjectItem = nItem;
		}
	}
}

void CEnGeologyView::OnFileNewObject() 
{
	CDlgObject dialog(this, this->GetDocument(), true);
	dialog.DoModal();
}

void CEnGeologyView::OnFileOpen() 
{
	CDlgObject dialog(this, this->GetDocument(), false);
	dialog.DoModal();
}

void CEnGeologyView::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	int nItem = this->GetObjectItem();
    pCmdUI->Enable(nItem > -1);		
}


void CEnGeologyView::UpdateObjectsListCtrl(CString where, CString order_by)
{
	this->m_EnGeoObjectsList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Objects], where, order_by);
}
void CEnGeologyView::UpdateProbGruntListCtrl(CString where, CString order_by)
{
	this->m_SoilsList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_ProbGr], where, order_by);
}
void CEnGeologyView::UpdateLitoListCtrl(CString where, CString order_by)
{
	this->m_LithoList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Litho], where, order_by);
}
void CEnGeologyView::UpdateKTListCtrl(CString where, CString order_by)
{
	this->m_KTList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_KT], where, order_by);
}
void CEnGeologyView::UpdateIGEListCtrl(CString where, CString order_by)
{
	this->m_IGEList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_IGE], where, order_by);
}
void CEnGeologyView::UpdateVodaListCtrl(CString where, CString order_by)
{
	this->m_VodaList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Voda], where, order_by);
}
void CEnGeologyView::UpdateTSZListCtrl(CString where, CString order_by)
{
	this->m_TSZList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_TSZ], where, order_by);
}
void CEnGeologyView::UpdatePaljaListCtrl(CString where, CString order_by)
{
	this->m_PaljaList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Palja], where, order_by);
}

void CEnGeologyView::UpdateCompressListCtrl(CString where, CString order_by)
{
	this->m_CompressList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Compress], where, order_by);
}
void CEnGeologyView::UpdateCutListCtrl(CString where, CString order_by)
{
	this->m_ZrizList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Zriz], where, order_by);
}
void CEnGeologyView::UpdateFizMehListCtrl(CString where, CString order_by)
{
	this->m_FizMehList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_FizMeh], where, order_by);
}
void CEnGeologyView::UpdateGranularListCtrl(CString where, CString order_by)
{
	this->m_GranularList.Fill_Ctrl_List(this->GetDocument()->m_tables[table_key_Granular], where, order_by);
}
void DeleteObjectRelatedDataFrom(CRecordset * set, long ID_OBJ)
{
	// удаляем связанные с данным объектом данные из других таблиц
	set->m_strFilter.Format("ID_OBJ = %d", ID_OBJ);

	if (set->Open(CRecordset::dynaset) )
	{
		while ( !set->IsEOF( ) )
		{
			set->Delete( );
			set->MoveNext( );
		}
	}
}

void DeleteFilterRelatedDataFrom(CRecordset * set, CString filter)
{
	// удаляем связанные с данным объектом данные из других таблиц
	set->m_strFilter = filter;

	if (set->Open(CRecordset::dynaset) )
	{
		while ( !set->IsEOF( ) )
		{
			set->Delete( );
			set->MoveNext( );
		}
	}
}
bool g_OnFileDeleteObject(int nItem, CDatabase * database) 
{
	if (nItem > -1)
	{

		try
		{
			long ID_OBJ = -1;
#if 1
			if (true)
			{
#endif
				SetObject setObject(database);
				if ( !setObject.Open(CRecordset::dynaset) )
					return false;
				setObject.SetAbsolutePosition(nItem+1);

				ID_OBJ = setObject.m_ID_OBJ;

				char str[1024];
				sprintf(str, 
					"Вы действительно хотите удалить объект\n"
					"ID_OBJ = %d\n"
					"CONTRACT = %s\n"
					"NAZVA = %s", 
					ID_OBJ, 
					setObject.m_CONTRACT, 
					setObject.m_NAZVA);
	            
				if (IDYES != MessageBox(0, str, "DeleteObjectRelatedDataFrom", MB_YESNO))
					return false;
#if 1

				//setObject.Close();
			}



			CString m_dao_strConnect_1;
			m_dao_strConnect_1.Format(";PWD=%s\0", CLabDoc::s_strDBPassword);
			CDaoDatabase m_dao_database_1;
			try {
				// nonexclusive, no read-only
				m_dao_database_1.Open(
					CLabDoc::s_strDatabase, 
					FALSE, FALSE, m_dao_strConnect_1);
			}
			catch (CDaoException* e) {
				::DaoErrorMsg(e);
				e->Delete();
				return false;
			}

			SetGeoTables setGeoTables(database);
			if (!setGeoTables.Open())
			{
				return false;
			}
			if (!setGeoTables.IsBOF()) 
			{
				setGeoTables.MoveFirst( );
				while(!setGeoTables.IsEOF()) 
				{
					long ID = setGeoTables.m_ID;
					CString table_nazva = setGeoTables.m_NAZVA;
					//MessageBox(table_nazva, "table_nazva", 0);

					if (true)
					{
						// таблица - приёмник
						CString m_strQuery_1;
						m_strQuery_1.Format("select * from [%s]", table_nazva);

						CDaoRecordset* m_pRecordset_1;					
						m_pRecordset_1 = new CDaoRecordset(&m_dao_database_1);

						try {
							m_pRecordset_1->m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
							m_pRecordset_1->Open(dbOpenDynaset, m_strQuery_1, dbInconsistent);
						}
						catch (CDaoException* pe) {
							::DaoErrorMsg(pe);
							pe->Delete();
							delete m_pRecordset_1;
							return false;
						}

						// перебираем строки (записи) в таблице - источнике
						if (!m_pRecordset_1->IsBOF())
						{
							m_pRecordset_1->MoveFirst();
							while (!m_pRecordset_1->IsEOF())
							{      
								// обавляем строку (запись) в таблицу приёмник
								m_pRecordset_1->Delete();								
								m_pRecordset_1->MoveNext();
							}
						}
						m_pRecordset_1->Close();
						delete m_pRecordset_1;

					}
					setGeoTables.MoveNext(); // to validate record count
				}
			}
			m_dao_database_1.Close();
#else
			// удаляем связанные с данным объектом данные из других таблиц
			SetKT setKT(database);
			DeleteObjectRelatedDataFrom(&setKT, ID_OBJ);

			SetFizMeh setFizMeh(database);
			DeleteObjectRelatedDataFrom(&setFizMeh, ID_OBJ);

			SetFizMehParam setFizMehParam(database);
			DeleteObjectRelatedDataFrom(&setFizMehParam, ID_OBJ);

			SetCilce setCilce(database);
			DeleteObjectRelatedDataFrom(&setCilce, ID_OBJ);

			SetCilce0 setCilce0(database);
			DeleteObjectRelatedDataFrom(&setCilce0, ID_OBJ);

			SetZriz0 setZriz0(database);
			DeleteObjectRelatedDataFrom(&setZriz0, ID_OBJ);

			SetCompress setCompress(database);
			DeleteObjectRelatedDataFrom(&setCompress, ID_OBJ);

			bool bUnEdited = true; 

			SetIGE setIGE0(bUnEdited, database);
			DeleteObjectRelatedDataFrom(&setIGE0, ID_OBJ);

			SetLito0 setLito0(bUnEdited, database);
			DeleteObjectRelatedDataFrom(&setLito0, ID_OBJ);

			bUnEdited = false; 
			
			SetIGE setIGE(database);
			DeleteObjectRelatedDataFrom(&setIGE, ID_OBJ);

			SetLito setLito(database);
			DeleteObjectRelatedDataFrom(&setLito, ID_OBJ);

			SetPalja setPalja(database);
			DeleteObjectRelatedDataFrom(&setPalja, ID_OBJ);

			SetPtPalja setPtPalja(database);
			DeleteObjectRelatedDataFrom(&setPtPalja, ID_OBJ);

			SetStZond setStZond(database);
			DeleteObjectRelatedDataFrom(&setStZond, ID_OBJ);

			SetPtStZond setPtStZond(database);
			DeleteObjectRelatedDataFrom(&setPtStZond, ID_OBJ);

			SetZriz setZriz(database);
			DeleteObjectRelatedDataFrom(&setZriz, ID_OBJ);

			SetZriz_tbl setZriz_tbl(database);
			DeleteObjectRelatedDataFrom(&setZriz_tbl, ID_OBJ);

			SetGranular setGranular(database);
			DeleteObjectRelatedDataFrom(&setGranular, ID_OBJ);

			SetGrunty setGrunty(database);
			DeleteObjectRelatedDataFrom(&setGrunty, ID_OBJ);

			SetProbGr setProbGr(database);
			DeleteObjectRelatedDataFrom(&setProbGr, ID_OBJ);

			SetPres setPres(database);
			DeleteObjectRelatedDataFrom(&setPres, ID_OBJ);

			SetPress_tbl setPress_tbl(database);
			DeleteObjectRelatedDataFrom(&setPress_tbl, ID_OBJ);

			SetShtamp setShtamp(database);
			DeleteObjectRelatedDataFrom(&setShtamp, ID_OBJ);

			SetShtamp_detail setShtamp_detail(database);
			DeleteObjectRelatedDataFrom(&setShtamp_detail, ID_OBJ);

			SetChemVD setChemVD(database);
			DeleteObjectRelatedDataFrom(&setChemVD, ID_OBJ);

			SetChemVD_tbl setChemVD_tbl(database);
			DeleteObjectRelatedDataFrom(&setChemVD_tbl, ID_OBJ);

			SetConsObj setConsObj(database);
			DeleteObjectRelatedDataFrom(&setConsObj, ID_OBJ);

			SetVoda setVoda(database);
			DeleteObjectRelatedDataFrom(&setVoda, ID_OBJ);

			SetPolygons setPolygons(database);
			DeleteObjectRelatedDataFrom(&setPolygons, ID_OBJ);

			SetFundament setFundament(database);
			DeleteObjectRelatedDataFrom(&setFundament, ID_OBJ);

			SetFundament_tbl setFundament_tbl(database);
			DeleteObjectRelatedDataFrom(&setFundament_tbl, ID_OBJ);

			SetT_P setT_P(database);
			DeleteObjectRelatedDataFrom(&setT_P, ID_OBJ);

			SetT_V setT_V(database);
			DeleteObjectRelatedDataFrom(&setT_V, ID_OBJ);

			SetWopt setWopt(database);
			DeleteObjectRelatedDataFrom(&setWopt, ID_OBJ);

			SetWopt_tbl setWopt_tbl(database);
			DeleteObjectRelatedDataFrom(&setWopt_tbl, ID_OBJ);

			SetRozriz setRozriz(database);
			DeleteObjectRelatedDataFrom(&setRozriz, ID_OBJ);

			SetRozrizy setRozrizy(database);
			DeleteObjectRelatedDataFrom(&setRozrizy, ID_OBJ);

			SetPCK2FizResults setPCK2FizResults(database);
			DeleteObjectRelatedDataFrom(&setPCK2FizResults, ID_OBJ);

			SetPCK2Fiz_CalcMode setPCK2Fiz_CalcMode(database);
			DeleteObjectRelatedDataFrom(&setPCK2Fiz_CalcMode, ID_OBJ);





			setObject.Delete();

			/*
ID	NAZVA
0	Objects//
1	KT //
2	Grunty//
3	FizMeh//
4	FizMehParam//
5	IGE//
6	Voda//
7	ProbGr//
8	StZond//
9	PtStZond//
10	Palja//
11	PtPalja//
12	Lito//
13	ConsObj//
14	Granular//
15	Cilce//
16	Compress//
17	Zriz//
18	Zriz_tbl//
19	Shtamp//
20	Shtamp_Detail//
21	Rozriz
22	T_V//
23	T_P//
24	Polygons//
25	Pres//
26	Pres_tbl//
27	Wopt
28	Wopt_tbl
29	ChemVD//
30	ChemVD_tbl//
31	Fundament//
32	Fundament_tbl//
*/

#endif
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return false;
		}
		return true;
	}
	return false;
}
void CEnGeologyView::OnFileDeleteObject() 
{
	int nItem = this->GetObjectItem();
	if (g_OnFileDeleteObject(nItem, &this->GetDocument()->m_database))
	{
		this->UpdateObjectsListCtrl("","");
		this->UpdateKTListCtrl("ID_OBJ = -1","");
		this->UpdateProbGruntListCtrl("ID_OBJ = -1","");
	}
}

void CEnGeologyView::OnUpdateFileDeleteObject(CCmdUI* pCmdUI) 
{
	int nItem = GetObjectItem();
    pCmdUI->Enable(nItem > -1);	
}

void CEnGeologyView::OnProbgrNewlabnumber() 
{
	CDlgProbGrunt dialog(this, this->GetDocument(), true);
	dialog.is_geo = true;
	dialog.i_kt = GetKTItem();
	dialog.DoModal();
}

void CEnGeologyView::OnUpdateProbgrNewlabnumber(CCmdUI* pCmdUI) 
{
	int nItem = this->GetObjectItem();
    pCmdUI->Enable(nItem > -1);	
}
bool CEnGeologyView::GetSetProbGrFilterStr(long ID_OBJ, CString & strFilter)
{
	switch (m_soil_list_type)
	{
	case soil_list_type::by_kt:
		{
			int nKTItem = this->GetKTItem();
			if (nKTItem < 0)
			{
				AfxMessageBox("Не выбрана KT");
				return false;
			}
			SetKT setKT(&this->GetLabDoc()->m_database);
			setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
			setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
			if ( !setKT.Open(CRecordset::dynaset) )
				return false;
			setKT.SetAbsolutePosition(nKTItem + 1);        
			long ID_KT = setKT.m_ID_KT;
	
			strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
			return true;

		}
		break;
	case soil_list_type::by_ige:
		{
			int nIGEItem = this->GetIGEItem();
			if (nIGEItem < 0)
			{
				AfxMessageBox("Не выбрана IGE");
				return false;
			}
			bool bUnEdited = false;	
			SetIGE setIGE(bUnEdited, &this->GetLabDoc()->m_database);
			setIGE.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
			setIGE.m_strSort.Format("ID_IGE");
			if ( !setIGE.Open(CRecordset::dynaset) )
				return false;
			setIGE.SetAbsolutePosition(nIGEItem + 1);        
			long ID_IGE = setIGE.m_ID_IGE;

			strFilter.Format("ID_OBJ = %d and ID_IGE = %d", ID_OBJ, ID_IGE);
			return true;

		}
		break;
	}

}

void CEnGeologyView::OnKtKtlistLoadformNew() 
{
	m_excel_ktlist.LoadFormNew(m_ObjectNazva);	
	m_excel_ktlist.Fill();	
}

void CEnGeologyView::OnUpdateKtKtlistLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnKtKtlistLoadformExisting() 
{
	m_excel_ktlist.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtKtlistLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtKtlistFill() 
{
	//m_excel_ktlist.Fill();	
}

void CEnGeologyView::OnUpdateKtKtlistFill(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateFill(pCmdUI, false);	
}

void CEnGeologyView::OnKtKtlistSavetodb() 
{
	m_excel_ktlist.to_rename_kt = false;
	m_excel_ktlist.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtKtlistSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtKtlistSaveandrename() 
{
	m_excel_ktlist.to_rename_kt = true;
	m_excel_ktlist.SaveToDB();		
}

void CEnGeologyView::OnUpdateKtKtlistSaveandrename(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateSaveToDB(pCmdUI);		
}

void CEnGeologyView::OnKtKtlistDisconnectexcel() 
{
	m_excel_ktlist.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtKtlistDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_ktlist.UpdateDisconnectExcel(pCmdUI);	
}

void CEnGeologyView::OnObjectsImportobject() 
{
	this->GetDocument()->ImportObject();
	this->UpdateObjectsListCtrl("","");	
}

void CEnGeologyView::OnProbgrPasportAllpossible() 
{
	this->ProbgrPasportAllpossible();
}

void CEnGeologyView::OnProbgrSoilname() 
{
	this->ProbgrSoilname();
}


void CEnGeologyView::OnProbgrPasportLanguage() 
{
	CDlgLanguage dialog;
	dialog.DoModal();	
}

void CEnGeologyView::OnProbygruntaDblclickmode() 
{
	CDlgProbGr_DblClickMode dialog;
	dialog.DoModal();	
}

void CEnGeologyView::OnProbgrClassification() 
{
	this->ProbgrClassification();
}
bool g_DeleteCompression(CLabView * lab_view, int nObjectItem, int nSoilsItem, int nCompressionItem, CDatabase * database);
void CEnGeologyView::OnKeydownListCompress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			int nCompressionItem = m_CompressList.GetSelected();
			int nSoilsItem = m_SoilsList.GetSelected();
			int nObjectItem = this->GetObjectItem();
			
			if (g_DeleteCompression(this, nObjectItem, nSoilsItem, nCompressionItem, &this->GetDocument()->m_database))
			{
			}

		}
		break;
	}
	
	*pResult = 0;
}

void CEnGeologyView::OnRclickListCompress(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;

	m_nCompItem = r;

	CPoint point = lpnmitem->ptAction;

	this->m_CompressList.ClientToScreen(&point);

	int compr_type = this->GetCompressType(m_nCompItem);

	CMenu menu;
	menu.CreatePopupMenu();
	switch(compr_type)
	{
	case 3:
	case 2:
		{
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT, "Паспорт (старый)");
			//menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT2AS1, "Паспорт каждого кольца отдельно");
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASSPORT2ASMEAN, "Паспорт 2 кривых с усреднёнными физсвойствами");
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT2ASDIFFVYPROB, "Паспорт 2 кривых с отдельными физсвойствами");
		}
		break;
	case 1:
		{
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT, "Паспорт (старый)");
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASSPORT1, "Паспорт 1 кривой");
		}
		break;	
	default:
		{
			menu.AppendMenu(MF_STRING, ID_COMPRESSION_PASPORT, "Паспорт (старый)");
		}
		break;
	}


	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);

	
	*pResult = 0;
}
void CEnGeologyView::OnRclickListSoil(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;
	m_nSoilItem = r;

	CPoint point = lpnmitem->ptAction;
	this->m_SoilsList.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_SOIL_PROPERTYWINDOW, "Окно свойств");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}


BOOL CEnGeologyView::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo) 
{
	if (pHandlerInfo == NULL)
	{
		switch (nID)
		{
		case ID_COMPRESSION_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 0);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_COMPRESSION_PASSPORT1:
		case ID_COMPRESSION_PASPORT2AS1:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 1);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_COMPRESSION_PASSPORT2ASMEAN:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 2);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_COMPRESSION_PASPORT2ASDIFFVYPROB:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCompress(this->m_nCompItem, 3);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_LABLAYER_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->LabLayerNormatives(0, this->m_ID_IGE);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;	
		case ID_LABLAYER_PASPORTNORMATIVES1:
		case ID_LABLAYER_PASPORTNORMATIVES2:
		case ID_LABLAYER_PASPORTNORMATIVES3:
			{
				if (nCode == CN_COMMAND)
				{
					this->LabLayerNormatives(nID - ID_LABLAYER_PASPORTNORMATIVES1 + 1, this->m_ID_IGE);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;	
		case ID_LABLAYER_CHASTNYE:
			{
				if (nCode == CN_COMMAND)
				{
					this->LabLayerChastnye(this->m_ID_IGE);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_LABLAYER_PROPERTYWINDOW:
			{
				if (nCode == CN_COMMAND)
				{
					this->LabLayerPropertyWindow(this->m_ID_IGE);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_SOIL_PROPERTYWINDOW:
			{
				if (nCode == CN_COMMAND)
				{
					this->SoilPropertyWindow(this->m_nSoilItem);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;

		case ID_CUT_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCut(this->m_nCutItem, 0);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_CUT_PASSPORTNEW:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportCut(this->m_nCutItem, 1);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_GRANULAR_PASPORT:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportGranular(0);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		case ID_GRANULAR_PASSPORTNEW:
			{
				if (nCode == CN_COMMAND)
				{
					this->ProbgrPasportGranular(1);
				}
				else if (nCode == CN_UPDATE_COMMAND_UI)
				{
					CCmdUI* pCmdUI = (CCmdUI*)pExtra;
					pCmdUI->SetCheck(1);
					pCmdUI->Enable(TRUE);
				}
			}
			break;
		}
	}
	
	return CFormView::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}

void CEnGeologyView::OnRclickListZriz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;
	m_nCutItem = r;

	CPoint point = lpnmitem->ptAction;
	this->m_ZrizList.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_CUT_PASPORT, "Паспорт (старый)");
	menu.AppendMenu(MF_STRING, ID_CUT_PASSPORTNEW, "Паспорт");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}
void CEnGeologyView::OnRclickListIge(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	int r = lpnmitem->iItem;
	int c = lpnmitem->iSubItem;
	//m_nIGEItem = r;

	UpdateIGERelatedLists(r);// m_ID_IGE



	CPoint point;

	point = lpnmitem->ptAction;
	this->m_IGEList.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_LABLAYER_PROPERTYWINDOW, "Окно свойств");
	menu.AppendMenu(MF_STRING, ID_LABLAYER_PASPORT, "Нормативные значения");
	menu.AppendMenu(MF_STRING, ID_LABLAYER_PASPORTNORMATIVES1, "Нормативные одним файлом");
	menu.AppendMenu(MF_STRING, ID_LABLAYER_PASPORTNORMATIVES2, "Нормативные без единой совокупности опытов");
	menu.AppendMenu(MF_STRING, ID_LABLAYER_PASPORTNORMATIVES3, "Нормативные по единой совокупности опытов");
	menu.AppendMenu(MF_STRING, ID_LABLAYER_CHASTNYE, "Частные значения");
	
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}
bool g_DeleteCut(CLabView * lab_view, int nObjectItem, int nSoilsItem, int nCutItem, CDatabase * database);

void CEnGeologyView::OnKeydownListZriz(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;

	switch(pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			int nCutItem = m_ZrizList.GetSelected();
			int nSoilsItem = m_SoilsList.GetSelected();
			int nObjectItem = this->GetObjectItem();
			
			if (g_DeleteCut(this, nObjectItem, nSoilsItem, nCutItem, &this->GetDocument()->m_database))
			{
			}

		}
		break;
	}
	
	*pResult = 0;
}


void CEnGeologyView::OnArchiveCaspgeoLoadformNew() 
{
	m_excel_casp_geo_archive.LoadFormNew(m_ObjectNazva);	
	m_excel_casp_geo_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCaspgeoLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_casp_geo_archive.UpdateLoadFormNew(pCmdUI);		
}

void CEnGeologyView::OnArchiveCaspgeoLoadformExisting() 
{
	m_excel_casp_geo_archive.LoadFormExisting();		
}

void CEnGeologyView::OnUpdateArchiveCaspgeoLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_casp_geo_archive.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnArchiveCaspgeoFill() 
{
	//m_excel_casp_geo_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCaspgeoFill(CCmdUI* pCmdUI) 
{
	m_excel_casp_geo_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveCaspgeoSavetodb() 
{
	m_excel_casp_geo_archive.SaveToDB();	
}

void CEnGeologyView::OnUpdateArchiveCaspgeoSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_casp_geo_archive.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnArchiveCaspgeoDisconnectexcel() 
{
	m_excel_casp_geo_archive.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateArchiveCaspgeoDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_casp_geo_archive.UpdateDisconnectExcel(pCmdUI);	
}


void CEnGeologyView::OnArchiveLaboratoryLoadformNew() 
{
	m_excel_lab_archive.LoadFormNew(m_ObjectNazva);	
	m_excel_lab_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveLaboratoryLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_lab_archive.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnArchiveLaboratoryLoadformExisting() 
{
	m_excel_lab_archive.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateArchiveLaboratoryLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_lab_archive.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnArchiveLaboratoryFill() 
{
	//m_excel_lab_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveLaboratoryFill(CCmdUI* pCmdUI) 
{
	m_excel_lab_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveLaboratorySavetodb() 
{
	m_excel_lab_archive.SaveToDB();	
}

void CEnGeologyView::OnUpdateArchiveLaboratorySavetodb(CCmdUI* pCmdUI) 
{
	m_excel_lab_archive.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnArchiveLaboratoryDisconnectexcel() 
{
	m_excel_lab_archive.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateArchiveLaboratoryDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_lab_archive.UpdateDisconnectExcel(pCmdUI);	
}

void CEnGeologyView::OnArchiveCompressionLoadformNew() 
{
	m_excel_compression_archive.LoadFormNew(m_ObjectNazva);	
}

void CEnGeologyView::OnUpdateArchiveCompressionLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnArchiveCompressionLoadformExisting() 
{
	m_excel_compression_archive.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateArchiveCompressionLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnArchiveCompressionFill() 
{
	m_excel_compression_archive.m_to_fill_all_lab_numbers = false;
	m_excel_compression_archive.m_to_fill_all_lab_numbers_as_2_vyprob = false;

	m_excel_compression_archive.save_different_vyprob = false;	
	m_excel_compression_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCompressionFill(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveCompressionFill2() 
{
	m_excel_compression_archive.m_to_fill_all_lab_numbers = false;
	m_excel_compression_archive.m_to_fill_all_lab_numbers_as_2_vyprob = false;
	m_excel_compression_archive.save_different_vyprob = true;	
	m_excel_compression_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCompressionFill2(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveCompressionFillalllabn() 
{
	m_excel_compression_archive.m_to_fill_all_lab_numbers = true;
	m_excel_compression_archive.m_to_fill_all_lab_numbers_as_2_vyprob = false;
	m_excel_compression_archive.save_different_vyprob = false;	
	m_excel_compression_archive.Fill();		
}

void CEnGeologyView::OnUpdateArchiveCompressionFillalllabn(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateFill(pCmdUI, true);		
}

void CEnGeologyView::OnArchiveCompressionFillalllabn2() 
{
	m_excel_compression_archive.m_to_fill_all_lab_numbers = true;
	m_excel_compression_archive.m_to_fill_all_lab_numbers_as_2_vyprob = true;
	m_excel_compression_archive.save_different_vyprob = true;	
	m_excel_compression_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCompressionFillalllabn2(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateFill(pCmdUI, true);		
}

void CEnGeologyView::OnArchiveCompressionFillAlllabnIf2then2() 
{
	m_excel_compression_archive.m_to_fill_all_lab_numbers = true;
	m_excel_compression_archive.m_to_fill_all_lab_numbers_as_2_vyprob = false;
	m_excel_compression_archive.save_different_vyprob = true;	
	m_excel_compression_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCompressionFillAlllabnIf2then2(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateFill(pCmdUI, true);		
}

void CEnGeologyView::OnArchiveCompressionSavetodb() 
{
	m_excel_compression_archive.save_different_vyprob = false;	
	m_excel_compression_archive.m_to_save_also_physical = 
		IDYES == MessageBox("Сохранять ли также и физ.свойства из архивной таблицы компрессии?","Сохранение архивных данных компрессии", MB_YESNO);
	m_excel_compression_archive.SaveToDB();	
}

void CEnGeologyView::OnUpdateArchiveCompressionSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateSaveToDB(pCmdUI);	
}




void CEnGeologyView::OnArchiveCompressionDisconnectexcel() 
{
	m_excel_compression_archive.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateArchiveCompressionDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_compression_archive.UpdateDisconnectExcel(pCmdUI);	
}






void CEnGeologyView::OnArchiveCutLoadformNew() 
{
	m_excel_cut_archive.LoadFormNew(m_ObjectNazva);	
}

void CEnGeologyView::OnUpdateArchiveCutLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnArchiveCutLoadformExisting() 
{
	m_excel_cut_archive.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateArchiveCutLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnArchiveCutFillCut() 
{
	//Срез
	m_excel_cut_archive.m_to_fill_all_lab_numbers = false;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_2_colomns = false;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_3_vyprob = false;
	m_excel_cut_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCutFillCut(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveCutFillAlllabn() 
{
	// Все лабораторные номера
	m_excel_cut_archive.m_to_fill_all_lab_numbers = true;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_2_colomns = false;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_3_vyprob = false;
	m_excel_cut_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCutFillAlllabn(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateFill(pCmdUI, true);	
}


void CEnGeologyView::OnArchiveCutFillAlllabn2() 
{
	//Все лаб.номера как 3 колонки
	m_excel_cut_archive.m_to_fill_all_lab_numbers = true;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_2_colomns = false;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_3_vyprob = true;
	m_excel_cut_archive.Fill();	
}



void CEnGeologyView::OnArchiveCutFillCutas2colomns() 
{
	// Срез как 2 колонки
	m_excel_cut_archive.m_to_fill_all_lab_numbers = false;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_2_colomns = true;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_3_vyprob = false;
	m_excel_cut_archive.Fill();	
	
}

void CEnGeologyView::OnUpdateArchiveCutFillCutas2colomns(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveCutFillAlllabnas2colomns() 
{
	// Все лаб.номера как 2 колонки
	m_excel_cut_archive.m_to_fill_all_lab_numbers = true;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_2_colomns = true;
	m_excel_cut_archive.m_to_fill_all_lab_numbers_as_3_vyprob = false;
	m_excel_cut_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveCutFillAlllabnas2colomns(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateFill(pCmdUI, true);	
}


void CEnGeologyView::OnUpdateArchiveCutFillAlllabn2(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveCutSavetodb() 
{
	m_excel_cut_archive.m_to_save_also_physical = IDYES == MessageBox("Сохранять ли также и физ.свойства из архивной таблицы среза?","Сохранение архивных данных среза", MB_YESNO);

	m_excel_cut_archive.SaveToDB();	
}

void CEnGeologyView::OnUpdateArchiveCutSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnArchiveCutDisconnectexcel() 
{
	m_excel_cut_archive.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateArchiveCutDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_cut_archive.UpdateDisconnectExcel(pCmdUI);	
}


void CEnGeologyView::OnArchiveGranLoadformNew() 
{
	m_excel_gran_archive.LoadFormNew(m_ObjectNazva);	
}

void CEnGeologyView::OnUpdateArchiveGranLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_gran_archive.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnArchiveGranLoadformExisting() 
{
	m_excel_gran_archive.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateArchiveGranLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_gran_archive.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnArchiveGranFillGran() 
{
	m_excel_gran_archive.m_to_fill_all_lab_numbers = false;
	m_excel_gran_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveGranFillGran(CCmdUI* pCmdUI) 
{
	m_excel_gran_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveGranFillAlllabn() 
{
	m_excel_gran_archive.m_to_fill_all_lab_numbers = true;
	m_excel_gran_archive.Fill();	
}

void CEnGeologyView::OnUpdateArchiveGranFillAlllabn(CCmdUI* pCmdUI) 
{
	m_excel_gran_archive.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnArchiveGranSavetodb() 
{
	m_excel_gran_archive.SaveToDB();	
}

void CEnGeologyView::OnUpdateArchiveGranSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_gran_archive.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnArchiveGranDisconnectexcel() 
{
	m_excel_gran_archive.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateArchiveGranDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_gran_archive.UpdateDisconnectExcel(pCmdUI);	
}
#include <windows.h>
#include <stdio.h>
#include "psapi.h"

bool PrintProcessNameAndID_and_TerminateExcel( DWORD processID )
{
    char szProcessName[MAX_PATH] = "unknown";

    // Get a handle to the process.
    HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION |
                                   PROCESS_VM_READ | PROCESS_TERMINATE,
                                   FALSE, processID );

    // Get the process name.
    if (NULL != hProcess )
    {
        HMODULE hMod;
        DWORD cbNeeded;

        if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), 
             &cbNeeded) )
        {
            GetModuleBaseName( hProcess, hMod, szProcessName, 
                               sizeof(szProcessName) );
        }
        else return false;
    }
    else return false;

    // Print the process name and identifier.
    printf( "%s (Process ID: %u)\n", szProcessName, processID );

	bool res = false;
	if (!strnicmp(szProcessName, "Excel.exe", 9))
	{
		TerminateProcess(hProcess, 0);
		res = true;
	}
    CloseHandle( hProcess );
	return res;
}

void enum_all_processes_and_TerminateExcel( )
{
    // Get the list of process identifiers.
    DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
    if ( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ) )
        return;

    // Calculate how many process identifiers were returned.
    cProcesses = cbNeeded / sizeof(DWORD);

    // Print the name and process identifier for each process.
    for ( i = 0; i < cProcesses; i++ )
        if (PrintProcessNameAndID_and_TerminateExcel( aProcesses[i] ))
			return;
}
void CEnGeologyView::OnExcelKill() 
{
	if (IDYES == AfxMessageBox("Вы уверены, что хотите завершить процессы Excel?", MB_YESNO, 0))
		enum_all_processes_and_TerminateExcel( );	
}

void CEnGeologyView::OnRclickListGranular(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LPNMITEMACTIVATE lpnmitem = (LPNMITEMACTIVATE) pNMHDR;

	CPoint point = lpnmitem->ptAction;
	this->m_GranularList.ClientToScreen(&point);

	CMenu menu;
	menu.CreatePopupMenu();
	menu.AppendMenu(MF_STRING, ID_GRANULAR_PASPORT, "Паспорт (старый)");
	menu.AppendMenu(MF_STRING, ID_GRANULAR_PASSPORTNEW, "Паспорт");
	menu.TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
	
	*pResult = 0;
}
#include "DlgNaborGruntovSetting.h"

void CEnGeologyView::OnObjectsSetnaborgruntov() 
{
	CDlgNaborGruntovSetting dialog(this, this->GetDocument(), &this->GetLabDoc()->m_database);
	dialog.DoModal();
}

void CEnGeologyView::OnKtStatzond() 
{
	CDlgStatZond dialog(this, this->GetLabDoc(), &this->GetLabDoc()->m_database);
	dialog.DoModal();	
}

void CEnGeologyView::OnUpdateKtStatzond(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CEnGeologyView::OnKtPalja() 
{
	CDlgPalja dialog(this, this->GetLabDoc(), &this->GetLabDoc()->m_database, false);
	dialog.DoModal();		
}

void CEnGeologyView::OnUpdateKtPalja(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CEnGeologyView::OnKtStatzondLoadformNew() 
{
	int nObItem = this->GetObjectItem();

	if (nObItem < 0)
	{
		AfxMessageBox("Не выбрано ни одного объекта");
		return;
	}

	int nKTItem = this->GetKTItem();

	if (nKTItem < 0)
	{
		AfxMessageBox("Не выбрано ни одной KT");
		return;
	}


	try
	{
		SetObject setObject(&this->GetLabDoc()->m_database);

		if ( !setObject.Open(CRecordset::dynaset) )
			return;

		setObject.SetAbsolutePosition(nObItem + 1);        
		long ID_OBJ = setObject.m_ID_OBJ;
			
		SetKT setKT(&this->GetLabDoc()->m_database);
		setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
		setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
		if ( !setKT.Open(CRecordset::dynaset) )
			return;

		setKT.SetAbsolutePosition(nKTItem + 1);        
		long ID_KT = setKT.m_ID_KT;
		//CString nazva = setObject.m_NAZVA + " " + setKT.m_NAZVA;
		CString nazva = setKT.m_NAZVA;

		m_excel_stat_zond.LoadFormNew(nazva);	
		m_excel_stat_zond.Fill();	

	}
	catch (CDBException* pe) 
	{
		AfxMessageBox(pe->m_strError);
		pe->Delete();
		return;
	}
}

void CEnGeologyView::OnUpdateKtStatzondLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_stat_zond.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnKtStatzondLoadformExisting() 
{
	m_excel_stat_zond.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtStatzondLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_stat_zond.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtStatzondFill() 
{
	m_excel_stat_zond.Fill();	
}

void CEnGeologyView::OnUpdateKtStatzondFill(CCmdUI* pCmdUI) 
{
	m_excel_stat_zond.UpdateFill(pCmdUI, false);	
}

void CEnGeologyView::OnKtStatzondCompute() 
{
	m_excel_stat_zond.Compute();	
}

void CEnGeologyView::OnUpdateKtStatzondCompute(CCmdUI* pCmdUI) 
{
	m_excel_stat_zond.UpdateCompute(pCmdUI);	
}

void CEnGeologyView::OnKtStatzondSavetodb() 
{
	m_excel_stat_zond.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtStatzondSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_stat_zond.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtStatzondDisconnectexcel() 
{
	m_excel_stat_zond.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtStatzondDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_stat_zond.UpdateDisconnectExcel(pCmdUI);	
}

void CEnGeologyView::OnKtPaljaLoadformNew() 
{
	m_excel_palja.LoadFormNew(m_ObjectNazva);	
	m_excel_palja.Fill();	
}

void CEnGeologyView::OnUpdateKtPaljaLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_palja.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnKtPaljaLoadformExisting() 
{
	m_excel_palja.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtPaljaLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_palja.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtPaljaFill() 
{
	//m_excel_palja.Fill();	
}

void CEnGeologyView::OnUpdateKtPaljaFill(CCmdUI* pCmdUI) 
{
	m_excel_palja.UpdateFill(pCmdUI, false);	
}

void CEnGeologyView::OnKtPaljaCompute() 
{
	m_excel_palja.Compute();	
}

void CEnGeologyView::OnUpdateKtPaljaCompute(CCmdUI* pCmdUI) 
{
	m_excel_palja.UpdateCompute(pCmdUI);	
}

void CEnGeologyView::OnKtPaljaSavetodb() 
{
	m_excel_palja.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtPaljaSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_palja.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtPaljaDisconnectexcel() 
{
	m_excel_palja.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtPaljaDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_palja.UpdateDisconnectExcel(pCmdUI);	
}


void CEnGeologyView::OnKtZondustparam() 
{
	CDlgZondUstParam dialog(this, this->GetLabDoc(), &this->GetLabDoc()->m_database);
	dialog.DoModal();		
	
}

void CEnGeologyView::OnObjectsCopygrunty() 
{
	DlgCopyGrunty dialog(this, this->GetLabDoc(), &this->GetLabDoc()->m_database);
	dialog.DoModal();		
}

void CEnGeologyView::OnKtAllpalja() 
{
	CDlgPalja dialog(this, this->GetLabDoc(), &this->GetLabDoc()->m_database, true);
	dialog.DoModal();		
	
}
bool g_OnFileDeleteCompressions(int nItem, CDatabase * database) 
{
	// прообраз функции - g_OnFileDeleteObject
	if (nItem > -1)
	{
		try
		{
			long ID_OBJ = -1;

				SetObject setObject(database);
				if ( !setObject.Open(CRecordset::dynaset) )
					return false;
				setObject.SetAbsolutePosition(nItem+1);

				ID_OBJ = setObject.m_ID_OBJ;

				char str[1024];
				sprintf(str, 
					"Вы действительно хотите удалить все Компрессии из объекта\n"
					"ID_OBJ = %d\n"
					"CONTRACT = %s\n"
					"NAZVA = %s", 
					ID_OBJ, 
					setObject.m_CONTRACT, 
					setObject.m_NAZVA);
	            
				if (IDYES != MessageBox(0, str, "DeleteObjectRelatedDataFrom", MB_YESNO))
					return false;

			// удаляем связанные с данным объектом данные из других таблиц
			SetCilce setCilce(database);
			DeleteObjectRelatedDataFrom(&setCilce, ID_OBJ);

			SetCilce0 setCilce0(database);
			DeleteObjectRelatedDataFrom(&setCilce0, ID_OBJ);

			SetCompress setCompress(database);
			DeleteObjectRelatedDataFrom(&setCompress, ID_OBJ);
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return false;
		}
		return true;
	}
	return false;
}

bool g_OnFileDeleteCuts(int nItem, CDatabase * database) 
{
	// прообраз функции - g_OnFileDeleteObject
	if (nItem > -1)
	{
		try
		{
			long ID_OBJ = -1;

				SetObject setObject(database);
				if ( !setObject.Open(CRecordset::dynaset) )
					return false;
				setObject.SetAbsolutePosition(nItem+1);

				ID_OBJ = setObject.m_ID_OBJ;

				char str[1024];
				sprintf(str, 
					"Вы действительно хотите удалить все Срезы из объекта\n"
					"ID_OBJ = %d\n"
					"CONTRACT = %s\n"
					"NAZVA = %s", 
					ID_OBJ, 
					setObject.m_CONTRACT, 
					setObject.m_NAZVA);
	            
				if (IDYES != MessageBox(0, str, "DeleteObjectRelatedDataFrom", MB_YESNO))
					return false;

			// удаляем связанные с данным объектом данные из других таблиц

			SetZriz0 setZriz0(database);
			DeleteObjectRelatedDataFrom(&setZriz0, ID_OBJ);

			SetZriz setZriz(database);
			DeleteObjectRelatedDataFrom(&setZriz, ID_OBJ);

			SetZriz_tbl setZriz_tbl(database);
			DeleteObjectRelatedDataFrom(&setZriz_tbl, ID_OBJ);
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return false;
		}
		return true;
	}
	return false;
}

bool g_OnFileDeleteGranulars(int nItem, CDatabase * database) 
{
	// прообраз функции - g_OnFileDeleteObject
	if (nItem > -1)
	{
		try
		{
			long ID_OBJ = -1;

				SetObject setObject(database);
				if ( !setObject.Open(CRecordset::dynaset) )
					return false;
				setObject.SetAbsolutePosition(nItem+1);

				ID_OBJ = setObject.m_ID_OBJ;

				char str[1024];
				sprintf(str, 
					"Вы действительно хотите удалить все Грансоставы из объекта\n"
					"ID_OBJ = %d\n"
					"CONTRACT = %s\n"
					"NAZVA = %s", 
					ID_OBJ, 
					setObject.m_CONTRACT, 
					setObject.m_NAZVA);
	            
				if (IDYES != MessageBox(0, str, "DeleteObjectRelatedDataFrom", MB_YESNO))
					return false;

			// удаляем связанные с данным объектом данные из других таблиц

			SetGranular setGranular(database);
			DeleteObjectRelatedDataFrom(&setGranular, ID_OBJ);
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return false;
		}
		return true;
	}
	return false;
}

bool g_OnFileDeleteFizMeh(int nItem, CDatabase * database) 
{
	// прообраз функции - g_OnFileDeleteObject
	if (nItem > -1)
	{
		try
		{
			long ID_OBJ = -1;

				SetObject setObject(database);
				if ( !setObject.Open(CRecordset::dynaset) )
					return false;
				setObject.SetAbsolutePosition(nItem+1);

				ID_OBJ = setObject.m_ID_OBJ;

				char str[1024];
				sprintf(str, 
					"Вы действительно хотите удалить все FizMeh из объекта\n"
					"ID_OBJ = %d\n"
					"CONTRACT = %s\n"
					"NAZVA = %s", 
					ID_OBJ, 
					setObject.m_CONTRACT, 
					setObject.m_NAZVA);
	            
				if (IDYES != MessageBox(0, str, "DeleteObjectRelatedDataFrom", MB_YESNO))
					return false;

			// удаляем связанные с данным объектом данные из других таблиц

			SetFizMeh setFizMeh(database);
			DeleteObjectRelatedDataFrom(&setFizMeh, ID_OBJ);
		}
		catch (CDBException* pe) 
		{
			AfxMessageBox(pe->m_strError);
			pe->Delete();
			return false;
		}
		return true;
	}
	return false;
}

void CEnGeologyView::OnArchiveDeleteallcuts() 
{
	int nItem = this->GetObjectItem();
	if (g_OnFileDeleteCuts(nItem, &this->GetDocument()->m_database))
	{
		//this->UpdateObjectsListCtrl("","");
		//this->UpdateKTListCtrl("ID_OBJ = -1","");
		//this->UpdateProbGruntListCtrl("ID_OBJ = -1","");
		//this->UpdateFizMehListCtrl("ID_OBJ = -1","");
		//this->UpdateGranularListCtrl("ID_OBJ = -1","");
		//this->UpdateCompressListCtrl("ID_OBJ = -1","");
		this->UpdateCutListCtrl("ID_OBJ = -1","");
	}	
}

void CEnGeologyView::OnArchiveDeleteallcompressions() 
{
	int nItem = this->GetObjectItem();
	if (g_OnFileDeleteCompressions(nItem, &this->GetDocument()->m_database))
	{
		//this->UpdateObjectsListCtrl("","");
		//this->UpdateKTListCtrl("ID_OBJ = -1","");
		//this->UpdateProbGruntListCtrl("ID_OBJ = -1","");
		//this->UpdateFizMehListCtrl("ID_OBJ = -1","");
		//this->UpdateGranularListCtrl("ID_OBJ = -1","");
		this->UpdateCompressListCtrl("ID_OBJ = -1","");
		//this->UpdateCutListCtrl("ID_OBJ = -1","");
	}
}

void CEnGeologyView::OnArchiveDeleteallgranulars() 
{
	int nItem = this->GetObjectItem();
	if (g_OnFileDeleteGranulars(nItem, &this->GetDocument()->m_database))
	{
		//this->UpdateObjectsListCtrl("","");
		//this->UpdateKTListCtrl("ID_OBJ = -1","");
		//this->UpdateProbGruntListCtrl("ID_OBJ = -1","");
		//this->UpdateFizMehListCtrl("ID_OBJ = -1","");
		this->UpdateGranularListCtrl("ID_OBJ = -1","");
		//this->UpdateCompressListCtrl("ID_OBJ = -1","");
		//this->UpdateCutListCtrl("ID_OBJ = -1","");
	}
}

void CEnGeologyView::OnArchiveDeleteallfizmeh() 
{
	int nItem = this->GetObjectItem();
	if (g_OnFileDeleteFizMeh(nItem, &this->GetDocument()->m_database))
	{
		//this->UpdateObjectsListCtrl("","");
		//this->UpdateKTListCtrl("ID_OBJ = -1","");
		//this->UpdateProbGruntListCtrl("ID_OBJ = -1","");
		this->UpdateFizMehListCtrl("ID_OBJ = -1","");
		//this->UpdateGranularListCtrl("ID_OBJ = -1","");
		//this->UpdateCompressListCtrl("ID_OBJ = -1","");
		//this->UpdateCutListCtrl("ID_OBJ = -1","");
	}
}

void CEnGeologyView::OnKtRozrizlistLoadformNew() 
{
	this->m_excel_rozriz_list.LoadFormNew(m_ObjectNazva);	
	this->m_excel_rozriz_list.Fill();	
}

void CEnGeologyView::OnUpdateKtRozrizlistLoadformNew(CCmdUI* pCmdUI) 
{
	this->m_excel_rozriz_list.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnKtRozrizlistLoadformExisting() 
{
	this->m_excel_rozriz_list.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtRozrizlistLoadformExisting(CCmdUI* pCmdUI) 
{
	this->m_excel_rozriz_list.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtRozrizlistFill() 
{
	//this->m_excel_rozriz_list.Fill();	
}

void CEnGeologyView::OnUpdateKtRozrizlistFill(CCmdUI* pCmdUI) 
{
	this->m_excel_rozriz_list.UpdateFill(pCmdUI, false);	
}

void CEnGeologyView::OnKtRozrizlistSavetodb() 
{
	this->m_excel_rozriz_list.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtRozrizlistSavetodb(CCmdUI* pCmdUI) 
{
	this->m_excel_rozriz_list.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtRozrizlistDisconnectexcel() 
{
	this->m_excel_rozriz_list.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtRozrizlistDisconnectexcel(CCmdUI* pCmdUI) 
{
	this->m_excel_rozriz_list.UpdateDisconnectExcel(pCmdUI);	
}

void CEnGeologyView::UpdateObjectRelatedLists(int iItem)
{
	int nObItem = iItem;
	int pos = nObItem + 1;

	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(pos);        
	m_ID_OBJ = setObject.m_ID_OBJ;
	m_ObjectNazva = setObject.m_NAZVA;

	CString where;
	where.Format("ID_OBJ = %d", m_ID_OBJ);

	CEnGeologyView::str_kt_list_where = where;

	UpdateKTListCtrl(where, CEnGeologyView::str_kt_list_order_by);
	UpdateIGEListCtrl(where, "ID_IGE");

	UpdateLitoListCtrl			("ID_OBJ = -1", "");
	UpdateProbGruntListCtrl		("ID_OBJ = -1", "");
	UpdateFizMehListCtrl		("ID_OBJ = -1", "");
	UpdateVodaListCtrl			("ID_OBJ = -1", "");
	UpdateTSZListCtrl			("ID_OBJ = -1", "");
	UpdatePaljaListCtrl			("ID_OBJ = -1", "");
	UpdateGranularListCtrl		("ID_OBJ = -1", "");
	UpdateCutListCtrl			("ID_OBJ = -1", "");
	UpdateCompressListCtrl		("ID_OBJ = -1", "");
}


void CEnGeologyView::UpdateKTRelatedLists(int iItem)
{
	int nObItem = this->GetObjectItem();
	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;


	int nKTItem = iItem;
	SetKT setKT(&this->GetLabDoc()->m_database);
	setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
	if ( !setKT.Open(CRecordset::dynaset) )
		return;
	setKT.SetAbsolutePosition(nKTItem + 1);        
	long ID_KT = setKT.m_ID_KT;

	int nPrGrItem = this->GetProbGrItem();

	m_soil_list_type = soil_list_type::by_kt;


	CString where;
	where.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);


	UpdateLitoListCtrl			(where, "H1");
	UpdateProbGruntListCtrl		(where, "ID_KT, ID_PROB");
	UpdateVodaListCtrl			(where, "");
	UpdateTSZListCtrl			(where, "");
	UpdatePaljaListCtrl			(where, "");

	UpdateFizMehListCtrl		("ID_OBJ = -1", "");
	UpdateGranularListCtrl		("ID_OBJ = -1", "");
	UpdateCutListCtrl			("ID_OBJ = -1", "");
	UpdateCompressListCtrl		("ID_OBJ = -1", "");
}
void CEnGeologyView::UpdateIGERelatedLists(int iItem)
{
	int nObItem = this->GetObjectItem();
	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	m_ID_OBJ = setObject.m_ID_OBJ;


	int nIGEItem = iItem;
	bool bUnEdited = false;	
	SetIGE setIGE(bUnEdited, &this->GetLabDoc()->m_database);
	setIGE.m_strFilter.Format("ID_OBJ = %d", m_ID_OBJ);
	setIGE.m_strSort.Format("ID_IGE");
	if ( !setIGE.Open(CRecordset::dynaset) )
		return;
	setIGE.SetAbsolutePosition(nIGEItem + 1);        
	m_ID_IGE = setIGE.m_ID_IGE;

	m_soil_list_type = soil_list_type::by_ige;


	CString where;
	where.Format("ID_OBJ = %d and ID_IGE = %d", m_ID_OBJ, m_ID_IGE);

	UpdateLitoListCtrl			("ID_OBJ = -1", "");

	UpdateProbGruntListCtrl		(where, "ID_KT, ID_PROB");


	UpdateVodaListCtrl			("ID_OBJ = -1", "");
	UpdateTSZListCtrl			("ID_OBJ = -1", "");
	UpdatePaljaListCtrl			("ID_OBJ = -1", "");


	UpdateFizMehListCtrl		("ID_OBJ = -1", "");
	UpdateGranularListCtrl		("ID_OBJ = -1", "");
	UpdateCutListCtrl			("ID_OBJ = -1", "");
	UpdateCompressListCtrl		("ID_OBJ = -1", "");
}
void CEnGeologyView::UpdateSoilRelatedLists(int iItem)
{
	int nObItem = this->GetObjectItem();
	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;


	long ID_KT = -1;
	long ID_PROB = -1;
	switch (m_soil_list_type)
	{
	case soil_list_type::by_kt:
		{
			int nKTItem = this->GetKTItem();
			SetKT setKT(&this->GetLabDoc()->m_database);
			setKT.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
			setKT.m_strSort.Format(CEnGeologyView::str_kt_list_order_by);
			if ( !setKT.Open(CRecordset::dynaset) )
				return;
			setKT.SetAbsolutePosition(nKTItem + 1);        
			ID_KT = setKT.m_ID_KT;

			int nProbGrItem = iItem;
			SetProbGr setProbGr(&this->GetLabDoc()->m_database);
			setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
			setProbGr.m_strSort.Format("ID_KT, ID_PROB");
			if ( !setProbGr.Open(CRecordset::dynaset) )
				return;
			setProbGr.SetAbsolutePosition(nProbGrItem + 1);        
			ID_PROB = setProbGr.m_ID_PROB;

		}
		break;
	case soil_list_type::by_ige:
		{
			int nIGEItem = this->GetIGEItem();
			bool bUnEdited = false;	
			SetIGE setIGE(bUnEdited, &this->GetLabDoc()->m_database);
			setIGE.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
			setIGE.m_strSort.Format("ID_IGE");
			if ( !setIGE.Open(CRecordset::dynaset) )
				return;
			setIGE.SetAbsolutePosition(nIGEItem + 1);        
			long ID_IGE = setIGE.m_ID_IGE;

			int nProbGrItem = iItem;
			SetProbGr setProbGr(&this->GetLabDoc()->m_database);
			setProbGr.m_strFilter.Format("ID_OBJ = %d and ID_IGE = %d", ID_OBJ, ID_IGE);
			setProbGr.m_strSort.Format("ID_KT, ID_PROB");
			if ( !setProbGr.Open(CRecordset::dynaset) )
				return;
			setProbGr.SetAbsolutePosition(nProbGrItem + 1);        
			ID_PROB = setProbGr.m_ID_PROB;
			ID_KT = setProbGr.m_ID_KT;

		}
		break;
	}

	CString where;
	where.Format("ID_OBJ = %d and ID_KT = %d and ID_PROB = %d", ID_OBJ, ID_KT, ID_PROB);

	UpdateFizMehListCtrl		(where, "");
	UpdateGranularListCtrl		(where, "");
	UpdateCutListCtrl			(where, "");
	UpdateCompressListCtrl		(where, "");

}





void CEnGeologyView::UpdateDBTablesRelatedLists(int iItem)
{		
	int r = iItem;		
	this->m_ListView.DeleteAllItemsAndColomns();
#if 0
	this->GetDocument()->m_tables.insert(map<CString, ATable *>::value_type(names[r], new ATable(this->m_geo_view->GetDocument(), names[r])));
	this->m_ListView.Fill_Ctrl_List(this->GetDocument()->m_tables[names[r]], "", "");
 
#else

	ATable * a_table = new ATable(this->GetDocument(), m_DataBaseTablesList.names[r]);
	this->m_ListView.Fill_Ctrl_List(a_table, "", "");
	delete a_table;
#endif
}





void CEnGeologyView::OnKeydownListEnGeoObjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	LV_KEYDOWN* pLVKeyDow = (LV_KEYDOWN*)pNMHDR;
	switch(pLVKeyDow->wVKey)
	{
	case VK_DELETE:
		{
			int nCompressionItem = m_CompressList.GetSelected();
			int nSoilsItem = m_SoilsList.GetSelected();
			int nObjectItem = this->GetObjectItem();
			
			if (g_OnFileDeleteObject(nObjectItem, &this->GetDocument()->m_database))
			{
			}

		}
		break;
	}
	
	*pResult = 0;
}










void CEnGeologyView::OnItemchangedListEnGeoObjects(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->uNewState)
	{
		this->UpdateObjectRelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}
void CEnGeologyView::OnItemchangedListIge(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if (pNMListView->uNewState)
	{
		this->UpdateIGERelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}

void CEnGeologyView::OnItemchangedListKt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState)
	{
		this->UpdateKTRelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}

void CEnGeologyView::OnItemchangedListSoil(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState)
	{
		this->UpdateSoilRelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}

void CEnGeologyView::OnItemchangedListDbTables(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	if (pNMListView->uNewState)
	{
		this->UpdateDBTablesRelatedLists(pNMListView->iItem);
	}
	
	*pResult = 0;
}

void CEnGeologyView::OnKtPck2fiz() 
{
	CDlgPCK2Fiz dialog(this, this->GetLabDoc(), &this->GetLabDoc()->m_database, true);
	dialog.DoModal();			
}

void CEnGeologyView::OnKtTszlistLoadformNew() 
{
	m_excel_tsz_list.LoadFormNew(m_ObjectNazva);	
	m_excel_tsz_list.Fill();	
}

void CEnGeologyView::OnUpdateKtTszlistLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_tsz_list.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnKtTszlistLoadformExisting() 
{
	m_excel_tsz_list.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtTszlistLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_tsz_list.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtTszlistFill() 
{
	m_excel_tsz_list.Fill();	
}

void CEnGeologyView::OnUpdateKtTszlistFill(CCmdUI* pCmdUI) 
{
	m_excel_tsz_list.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnKtTszlistSavetodb() 
{
	m_excel_tsz_list.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtTszlistSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_tsz_list.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtTszlistDisconnectexcel() 
{
	m_excel_tsz_list.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtTszlistDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_tsz_list.UpdateDisconnectExcel(pCmdUI);	
}

void CEnGeologyView::OnKtDxfrozrizlistLoadformNew() 
{
	this->m_excel_dxf_rozriz_list.LoadFormNew(m_ObjectNazva);	
	this->m_excel_dxf_rozriz_list.Fill();	
}

void CEnGeologyView::OnUpdateKtDxfrozrizlistLoadformNew(CCmdUI* pCmdUI) 
{
	this->m_excel_dxf_rozriz_list.UpdateLoadFormNew(pCmdUI);
	
}

void CEnGeologyView::OnKtDxfrozrizlistLoadformExisting() 
{
	this->m_excel_dxf_rozriz_list.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtDxfrozrizlistLoadformExisting(CCmdUI* pCmdUI) 
{
	this->m_excel_dxf_rozriz_list.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtDxfrozrizlistFill() 
{
	//this->m_excel_dxf_rozriz_list.Fill();	
}

void CEnGeologyView::OnUpdateKtDxfrozrizlistFill(CCmdUI* pCmdUI) 
{
	this->m_excel_dxf_rozriz_list.UpdateFill(pCmdUI, true);	
}

void CEnGeologyView::OnKtDxfrozrizlistSavetodb() 
{
	this->m_excel_dxf_rozriz_list.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtDxfrozrizlistSavetodb(CCmdUI* pCmdUI) 
{
	this->m_excel_dxf_rozriz_list.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtDxfrozrizlistDisconnectexcel() 
{
	this->m_excel_dxf_rozriz_list.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtDxfrozrizlistDisconnectexcel(CCmdUI* pCmdUI) 
{
	this->m_excel_dxf_rozriz_list.UpdateDisconnectExcel(pCmdUI);	
}

void CEnGeologyView::OnKtHydrolistLoadformNew() 
{
	m_excel_hydro_list.LoadFormNew(m_ObjectNazva);	
	m_excel_hydro_list.Fill();		
}

void CEnGeologyView::OnUpdateKtHydrolistLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_hydro_list.UpdateLoadFormNew(pCmdUI);	
}

void CEnGeologyView::OnKtHydrolistLoadformExisting() 
{
	m_excel_hydro_list.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateKtHydrolistLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_hydro_list.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnKtHydrolistSavetodb() 
{
	m_excel_hydro_list.SaveToDB();	
}

void CEnGeologyView::OnUpdateKtHydrolistSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_hydro_list.UpdateSaveToDB(pCmdUI);	
}

void CEnGeologyView::OnKtHydrolistDisconnectexcel() 
{
	m_excel_hydro_list.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateKtHydrolistDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_hydro_list.UpdateDisconnectExcel(pCmdUI);	
}

#include ".\..\wintools\src\win32_project.h"

void CEnGeologyView::LabLayerNormatives(int type, long id_ige) 
{
	int nObItem = this->GetObjectItem();

	CEnGeologyDoc* doc = this->GetDocument();
	if (doc)
	{
		if (!doc->dll_w_project)
			doc->dll_w_project = new dll_win_project(this->GetDocument());

		if (!doc->dll_w_project->Have_WinProject_WindowLess())
		{
			doc->dll_w_project->CreateWindowLess_WinProject();
			this->to_draw = false;
			ObjectsInsertto3d();
			this->to_draw = true;
		}
		else
		{
			if (this->m_nObjectItem != nObItem)
			{
				doc->dll_w_project->ReCreateWindowLess_WinProject();
				this->to_draw = false;
				ObjectsInsertto3d();
				this->to_draw = true;
			}
		}

		doc->dll_w_project->SetWindowLess_WinProject();

		doc->dll_w_project->LabLayerNormatives(type, id_ige);
		//size_t nLayers = doc->dll_w_project->w_project->m_laboratory.m_layers.size();
//		if (nItem >= 0 && nItem < nLayers)
//			doc->dll_w_project->w_project->m_laboratory.m_layers.operator [](nItem)->Passport();
	}
}
void CEnGeologyView::LabLayerChastnye(long id_ige) 
{
	int nObItem = this->GetObjectItem();

	CEnGeologyDoc* doc = this->GetDocument();
	if (doc)
	{
		if (!doc->dll_w_project)
			doc->dll_w_project = new dll_win_project(this->GetDocument());

		if (!doc->dll_w_project->Have_WinProject_WindowLess())
		{
			doc->dll_w_project->CreateWindowLess_WinProject();
			this->to_draw = false;
			ObjectsInsertto3d();
			this->to_draw = true;
		}
		else
		{
			if (this->m_nObjectItem != nObItem)
			{
				doc->dll_w_project->ReCreateWindowLess_WinProject();
				this->to_draw = false;
				ObjectsInsertto3d();
				this->to_draw = true;
			}
		}

		doc->dll_w_project->SetWindowLess_WinProject();

		doc->dll_w_project->LabLayerChastnye(id_ige);

		//size_t nLayers = doc->dll_w_project->w_project->m_laboratory.m_layers.size();
//		if (nItem >= 0 && nItem < nLayers)
//			doc->dll_w_project->w_project->m_laboratory.m_layers.operator [](nItem)->Passport();
	}
}

void CEnGeologyView::LabLayerPropertyWindow(long id_ige) 
{
	int nObItem = this->GetObjectItem();

	CEnGeologyDoc* doc = this->GetDocument();
	if (doc)
	{
		if (!doc->dll_w_project)
			doc->dll_w_project = new dll_win_project(this->GetDocument());

		if (!doc->dll_w_project->Have_WinProject_WindowLess())
		{
			doc->dll_w_project->CreateWindowLess_WinProject();
			this->to_draw = false;
			ObjectsInsertto3d();
			this->to_draw = true;
		}
		else
		{
			if (this->m_nObjectItem != nObItem)
			{
				doc->dll_w_project->ReCreateWindowLess_WinProject();
				this->to_draw = false;
				ObjectsInsertto3d();
				this->to_draw = true;
			}
		}

		doc->dll_w_project->SetWindowLess_WinProject();

		long x = CLabView::property_window_pt.x;
		long y = CLabView::property_window_pt.y; 

		if (x < 0)	x = 0;
		if (y < 0)	y = 0;

		HWND hWndParent = this->m_hWnd;//hInst;
		doc->dll_w_project->LabLayerPropertyWindow(hWndParent, id_ige, x, y);
/*
		size_t nLayers = doc->dll_w_project->w_project->m_laboratory.m_layers.size();
		if (nItem >= 0 && nItem < nLayers)
		{
			this->PropertyWindow(
				doc->dll_w_project->w_project->Get_LabNumber_context_with_results(),
				hWndParent, 
				doc->dll_w_project->w_project->m_laboratory.m_layers.operator [](nItem));
		}*/
	}
}
void CEnGeologyView::OnProbgrExcludedtriallist() 
{
	int nObItem = this->GetObjectItem();

	CEnGeologyDoc* doc = this->GetDocument();
	if (doc)
	{
		if (!doc->dll_w_project)
			doc->dll_w_project = new dll_win_project(this->GetDocument());

		if (!doc->dll_w_project->Have_WinProject_WindowLess())
		{
			doc->dll_w_project->CreateWindowLess_WinProject();
			this->to_draw = false;
			ObjectsInsertto3d();
			this->to_draw = true;
		}
		else
		{
			if (this->m_nObjectItem != nObItem)
			{
				doc->dll_w_project->ReCreateWindowLess_WinProject();
				this->to_draw = false;
				ObjectsInsertto3d();
				this->to_draw = true;
			}
		}

		doc->dll_w_project->SetWindowLess_WinProject();

		HWND hWndParent = this->m_hWnd;
		doc->dll_w_project->LabExcludedList(hWndParent);
	}	
}

CString GetKTName(CDatabase * database, long id_obj, long id_kt);
void CEnGeologyView::OnProbgrIgeautofill() 
{
	int nObItem = this->GetObjectItem();
	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;

	CString str, str_list, str_undet, s;

	int det = 0, undet = 0;

	SetProbGr setProbGr(&this->GetLabDoc()->m_database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return;
	if (!setProbGr.IsBOF()) 
	{
		setProbGr.MoveFirst();
		while(!setProbGr.IsEOF()) 
		{
			long ID_KT = setProbGr.m_ID_KT;
			double H = setProbGr.m_H;
			long ID_IGE = setProbGr.m_ID_IGE;

			bool ige_determined = false;

			if (true)
			{
				SetLito setLito(false, &this->GetLabDoc()->m_database);
				setLito.m_strFilter.Format("ID_OBJ = %d and ID_KT = %d", ID_OBJ, ID_KT);
				setLito.m_strSort.Format("");
				if ( !setLito.Open(CRecordset::dynaset) )
					return;

				if (!setLito.IsBOF()) 
				{
					setLito.MoveFirst( );
					while(!setLito.IsEOF()) 
					{
						if (H > setLito.m_H0 && H <= setLito.m_H1)
						{
							setProbGr.Edit();
							setProbGr.m_ID_IGE = setLito.m_ID_IGE;
							setProbGr.Update();
							ige_determined = true;
							det++;
							break;
						}
						setLito.MoveNext();
					}
				}

				if (!ige_determined)
				{
					undet++;
					s.Format("скважина %s глубина %0.1f\n", 
						GetKTName(&this->GetLabDoc()->m_database, ID_OBJ, ID_KT),
						H);
					str_undet += s;
				}
			}
			setProbGr.MoveNext();
		}
	}	

	UINT nType;
	if (!undet)
	{
		nType = MB_OK;
		str.Format("На основе разбивки скважин\n"
			"для объекта %s контракт %s\n"
			"было заполено ИГЭ для %d проб грунта", 
			setObject.m_NAZVA, setObject.m_CONTRACT, det);
	}
	else
	{
		nType = MB_YESNO;
		str_list.Format("На основе разбивки скважин\n"
			"для объекта %s контракт %s\n"
			"было заполено ИГЭ для %d проб грунта\n"
			"Нижеследующие %d проб грунта оказались с неопределённым ИГЭ:\n"
			"%s\n",
			setObject.m_NAZVA, setObject.m_CONTRACT, det, undet, str_undet);

		str.Format(
			"%s\n"
			"Вы хотите записать этот список в текстовый файл?", 
			str_list);
	}
	if (IDYES == AfxMessageBox(str, nType))
	{
		TCHAR filter[4098];
		wsprintf(filter, TEXT("txt"));
		CFileDialog dlg(FALSE, filter);
		if (dlg.DoModal() == IDCANCEL) return;
		CString path = dlg.GetPathName();

		FILE * txt = fopen(path, "wt");
		if (txt)
		{
			fprintf(txt, "%s\n", str_list);
			fclose(txt);
		}
	}
}

void CEnGeologyView::OnColumnclickListKt(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	switch(pNMListView->iSubItem)
	{
	case 0:
		{
			CEnGeologyView::str_kt_list_order_by = "ID_KT";
			this->UpdateKTListCtrl(CEnGeologyView::str_kt_list_where, CEnGeologyView::str_kt_list_order_by);
		}
		break;
	case 1:
		{
			CEnGeologyView::str_kt_list_order_by = "NAZVA";
			this->UpdateKTListCtrl(CEnGeologyView::str_kt_list_where, CEnGeologyView::str_kt_list_order_by);
		}
		break;
	}
	*pResult = 0;
}


void CEnGeologyView::OnViewPropertywindowwithPlot() 
{
	// Здесь мы изменяем значение статических членов в простанстве адресов модуля lab.exe
	if (Laboratory::context_with_plot)
	{
		Laboratory::context_with_plot = false;
	}
	else
	{
		Laboratory::context_with_plot = true; 
	}
	// А здесь мы изменяем значение статических членов в простанстве адресов модуля dll
	if (this->GetDocument()->dll_w_project)
	{
		this->GetDocument()->dll_w_project->OnViewPropertywindowwithPlot();
		this->ReCreatePropertyWindow(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());
	}
}

void CEnGeologyView::OnUpdateViewPropertywindowwithPlot(CCmdUI* pCmdUI) 
{
	if (this->GetDocument()->dll_w_project)
	{
		pCmdUI->SetCheck(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());	
	}
}

void CEnGeologyView::OnViewPropertywindowwithResults() 
{
	// Здесь мы изменяем значение статических членов в простанстве адресов модуля lab.exe
	/*if (LabNumber::context_with_results)
	{
		LabNumber::context_with_results = false;
	}
	else
	{
		LabNumber::context_with_results = true; 
	}*/
	// А здесь мы изменяем значение статических членов в простанстве адресов модуля dll
	if (this->GetDocument()->dll_w_project)
	{
		this->GetDocument()->dll_w_project->OnViewPropertywindowwithResults();
		this->ReCreatePropertyWindow(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());
	}
}

void CEnGeologyView::OnUpdateViewPropertywindowwithResults(CCmdUI* pCmdUI) 
{
	if (this->GetDocument()->dll_w_project)
	{
		pCmdUI->SetCheck(this->GetDocument()->dll_w_project->Get_LabNumber_context_with_results());	
	}
}

void CEnGeologyView::OnViewPropertywindowwithLabnumbertriallist() 
{
	// Здесь мы изменяем значение статических членов в простанстве адресов модуля lab.exe
	/*if (LabLayer::context_with_lab_number_trial_list)
	{
		LabLayer::context_with_lab_number_trial_list = false;
	}
	else
	{
		LabLayer::context_with_lab_number_trial_list = true; 
	}*/
	// А здесь мы изменяем значение статических членов в простанстве адресов модуля dll
	if (this->GetDocument()->dll_w_project)
	{
		this->GetDocument()->dll_w_project->OnViewPropertywindowwithLabnumbertriallist();
		this->ReCreatePropertyWindow(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());
	}
}

void CEnGeologyView::OnUpdateViewPropertywindowwithLabnumbertriallist(CCmdUI* pCmdUI) 
{
	if (this->GetDocument()->dll_w_project)
	{
		pCmdUI->SetCheck(this->GetDocument()->dll_w_project->Get_LabLayer_context_with_lab_number_trial_list());	
	}
}

void CEnGeologyView::OnViewPropertywindowwithNormatives() 
{
	// Здесь мы изменяем значение статических членов в простанстве адресов модуля lab.exe
	/*if (LabLayer::context_with_normatives)
	{
		LabLayer::context_with_normatives = false;
	}
	else
	{
		LabLayer::context_with_normatives = true; 
	}*/
	// А здесь мы изменяем значение статических членов в простанстве адресов модуля dll
	if (this->GetDocument()->dll_w_project)
	{
		this->GetDocument()->dll_w_project->OnViewPropertywindowwithNormatives();
		this->ReCreatePropertyWindow(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());
	}
}

void CEnGeologyView::OnUpdateViewPropertywindowwithNormatives(CCmdUI* pCmdUI) 
{
	if (this->GetDocument()->dll_w_project)
	{
		pCmdUI->SetCheck(this->GetDocument()->dll_w_project->Get_LabLayer_context_with_normatives());	
	}
}

void CEnGeologyView::OnViewPropertywindowwithCorrelation() 
{
	// Здесь мы изменяем значение статических членов в простанстве адресов модуля lab.exe
	/*if (LabLayer::context_with_korrelation)
	{
		LabLayer::context_with_korrelation = false;
	}
	else
	{
		LabLayer::context_with_korrelation = true; 
	}*/
	// А здесь мы изменяем значение статических членов в простанстве адресов модуля dll
	if (this->GetDocument()->dll_w_project)
	{
		this->GetDocument()->dll_w_project->OnViewPropertywindowwithCorrelation();
		this->ReCreatePropertyWindow(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());
	}
}

void CEnGeologyView::OnUpdateViewPropertywindowwithCorrelation(CCmdUI* pCmdUI) 
{
	if (this->GetDocument()->dll_w_project)
	{
		pCmdUI->SetCheck(this->GetDocument()->dll_w_project->Get_LabLayer_context_with_korrelation());	
	}
}

void CEnGeologyView::OnViewPropertywindowwithNormativesbyallexperiences() 
{
	// Здесь мы изменяем значение статических членов в простанстве адресов модуля lab.exe
	/*if (LabLayer::context_with_normatives_by_all_experiences)
	{
		LabLayer::context_with_normatives_by_all_experiences = false;
	}
	else
	{
		LabLayer::context_with_normatives_by_all_experiences = true; 
	}*/
	// А здесь мы изменяем значение статических членов в простанстве адресов модуля dll
	if (this->GetDocument()->dll_w_project)
	{
		this->GetDocument()->dll_w_project->OnViewPropertywindowwithNormativesbyallexperiences();
		this->ReCreatePropertyWindow(this->GetDocument()->dll_w_project->Get_Laboratory_context_with_plot());
	}
}

void CEnGeologyView::OnUpdateViewPropertywindowwithNormativesbyallexperiences(CCmdUI* pCmdUI) 
{
	if (this->GetDocument()->dll_w_project)
	{
		pCmdUI->SetCheck(this->GetDocument()->dll_w_project->Get_LabLayer_context_with_normatives_by_all_experiences());	
	}
}

void CEnGeologyView::OnUpdateProbgrPasportOtnositdefongraph(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable();
	pCmdUI->SetCheck(otnosit_def_on_graph);		
}

void CEnGeologyView::OnProbgrPasportOtnositdefongraph() 
{
	if (otnosit_def_on_graph)
		otnosit_def_on_graph = false;
	else
		otnosit_def_on_graph = true;	
}

void CEnGeologyView::OnObjectsNaborige() 
{
	DlgIGEList dialog(this, this->GetDocument(), &this->GetLabDoc()->m_database);
	dialog.DoModal();
	
}

void CEnGeologyView::OnProbygruntaLabnumbersLoadformNew() 
{
	m_excel_labnlist.LoadFormNew(m_ObjectNazva);	
	m_excel_labnlist.Fill();	
	
}

void CEnGeologyView::OnUpdateProbygruntaLabnumbersLoadformNew(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateLoadFormNew(pCmdUI);		
}

void CEnGeologyView::OnProbygruntaLabnumbersLoadformExisting() 
{
	m_excel_labnlist.LoadFormExisting();	
}

void CEnGeologyView::OnUpdateProbygruntaLabnumbersLoadformExisting(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateLoadFormExisting(pCmdUI);	
}

void CEnGeologyView::OnProbygruntaLabnumbersFill() 
{
	m_excel_labnlist.Fill();	
}

void CEnGeologyView::OnUpdateProbygruntaLabnumbersFill(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateFill(pCmdUI, false);		
}

void CEnGeologyView::OnProbygruntaLabnumbersSavetodb() 
{
	m_excel_labnlist.SaveToDB();	
}

void CEnGeologyView::OnUpdateProbygruntaLabnumbersSavetodb(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateSaveToDB(pCmdUI);	
}





void CEnGeologyView::OnProbygruntaLabnumbersDisconnectexcel() 
{
	m_excel_labnlist.DisconnectExcel();	
}

void CEnGeologyView::OnUpdateProbygruntaLabnumbersDisconnectexcel(CCmdUI* pCmdUI) 
{
	m_excel_labnlist.UpdateDisconnectExcel(pCmdUI);		
}


bool FillLabNumber(LabNumber * lab_number, CDatabase * database, 
				   long ID_OBJ, long ID_KT, long ID_GR, long ID_PROB, long LAB_N, double H, long ID_KODPROB, CString & grunt_name, long id_ige,
				   bool add_fizmeh_from_db, bool add_granular_from_db, bool add_cut_from_db, int nCutItem, bool add_compress_from_db, int nCompItem, bool add_stat_zond_from_db);
void CEnGeologyView::OnProbgrSoilautonames() 
{
	int nObItem = this->GetObjectItem();
	SetObject setObject(&this->GetLabDoc()->m_database);
	if ( !setObject.Open(CRecordset::dynaset) )
		return;
	setObject.SetAbsolutePosition(nObItem + 1);        
	long ID_OBJ = setObject.m_ID_OBJ;

	double _pressure_interval_01_02_0 = 0.1;

	Laboratory * lab = new Laboratory(NULL, _pressure_interval_01_02_0);
	lab->id_obj = ID_OBJ;
	lab->contract = (LPCSTR)setObject.m_CONTRACT;
	lab->object_name = (LPCSTR)setObject.m_NAZVA;
	LabLayer * lab_layer = new LabLayer(lab, "DataBase");

	SetProbGr setProbGr(&this->GetLabDoc()->m_database);
	setProbGr.m_strFilter.Format("ID_OBJ = %d", ID_OBJ);
	setProbGr.m_strSort.Format("ID_KT, ID_PROB");
	if ( !setProbGr.Open(CRecordset::dynaset) )
		return;
	if (!setProbGr.IsBOF()) 
	{
		setProbGr.MoveFirst();
		while(!setProbGr.IsEOF()) 
		{
			long ID_KT = setProbGr.m_ID_KT;
			double H = setProbGr.m_H;
			long ID_IGE = setProbGr.m_ID_IGE;
			long LAB_N = setProbGr.m_LAB_N;
			long ID_PROB = setProbGr.m_ID_PROB;
			long ID_KODPROB = setProbGr.m_ID_KODPROB;
			long ID_GR = setProbGr.m_ID_GR;
			CString grunt_name = setProbGr.m_GRUNT_NAME;
					
			LabNumber * lab_number = new LabNumber(lab_layer);

			bool add_cut_from_db = true;
			bool add_compress_from_db = true;
			int nCutItem = 0;
			int nCompItem = 0;
			bool add_stat_zond_from_db = false;

			bool add_fizmeh_from_db = true;
			bool add_granular_from_db = true;
			
			if (FillLabNumber(lab_number, &this->GetLabDoc()->m_database, 
				ID_OBJ, ID_KT, ID_GR, ID_PROB, LAB_N, H, ID_KODPROB, grunt_name, ID_IGE, 
				add_fizmeh_from_db, add_granular_from_db, add_cut_from_db, nCutItem, add_compress_from_db, nCompItem, add_stat_zond_from_db))
			{
				lab_number->ReCalcProperties(false);
				CString name = lab_number->GetSoilDescription(false).c_str();

				setProbGr.Edit();
				setProbGr.m_GRUNT_NAME = name;
				setProbGr.Update();			
			}

			delete lab_number;

			setProbGr.MoveNext();
		}
	}		
}





void CEnGeologyView::OnExcelTodissconnectwhenloadform() 
{
	if (BaseExcel::to_disconnect_exels_when_load_form)
	{
		BaseExcel::to_disconnect_exels_when_load_form = false;
	}
	else
	{
		BaseExcel::to_disconnect_exels_when_load_form = true;
	}
}


void CEnGeologyView::OnUpdateExcelTodissconnectwhenloadformG(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(BaseExcel::to_disconnect_exels_when_load_form);	
}

void CEnGeologyView::OnExcelAutomaticsavewhendisconnect() 
{
	if (BaseExcel::to_automatic_save_when_disconnect)
	{
		BaseExcel::to_automatic_save_when_disconnect = false;
	}
	else
	{
		BaseExcel::to_automatic_save_when_disconnect = true;
	}	
}

void CEnGeologyView::OnUpdateExcelAutomaticsavewhendisconnect(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(BaseExcel::to_automatic_save_when_disconnect);	
}



void CEnGeologyView::OnUpdateFile3d(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}


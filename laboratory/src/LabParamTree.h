// LabTrialsTree.h
#pragma once


HWND CreateATreeView_LabParam(HWND hwndParent, Laboratory * lab);

LRESULT CALLBACK DlgProcLabParamTree(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProcLaboratoryParamTree(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

HTREEITEM AddParamToTree(HWND hwndTV, LPSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
HTREEITEM AddParamToTree(HWND hwndTV, LPSTR lpszItem, LabParam * lab_param, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);

BOOL TreeView_SetCheckState3(HWND hwndTreeView, HTREEITEM hItem, bool * fCheck);
BOOL TreeView_GetCheckState3(HWND hwndTreeView, HTREEITEM hItem);

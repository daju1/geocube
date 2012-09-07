// LabTrialsTree.h
#pragma once


HWND CreateATreeView(HWND hwndParent, Laboratory * lab);

LRESULT CALLBACK DlgProcLabTrialTree(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK DlgProcLaboratoryTrialTree(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);
HTREEITEM AddItemToTree(HWND hwndTV, LPSTR lpszItem, LabObject * lab_object, HTREEITEM hParent = TVI_ROOT, HTREEITEM hInsertAfter = TVI_LAST);

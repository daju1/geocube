LRESULT CALLBACK DlgProcParentTab( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
HWND TabCreate(HWND hwnd) ;

BOOL CALLBACK DlgProcTabChild1( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );
BOOL CALLBACK DlgProcTabChild2( HWND hDlg, UINT uMsg,
                              WPARAM wParam, LPARAM lParam );

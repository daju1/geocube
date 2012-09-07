class _ListViewTab_
{
	char tmp_str[1024];
	friend int CALLBACK WndProcListViewTab(HWND hList, UINT message, WPARAM wParam, LPARAM lParam);

	int x; 
	int y; 
    TEXTMETRIC tm; 
    HDC hdcMem; 

	HWND hList;
	HWND hWndEdit;
	HWND hWndComboBox;

	HWND hWndParent;

	vector<string>			* headers;
	vector<vector<string> >	* items;
	vector<vector<bool*> >	* checkings;
#if !USE_LISTVIEW_STANDART 
	vector<vector<int> >	* editings;
#endif
	size_t rows, cols;
	int edit_r, edit_c;

	static HWND CreateListView (HWND hWndParent, LPVOID lpParam, double xpart0, double xpart_end, double ypart0, double ypart_end) ;
	static BOOL InitListViewImageLists(HWND hWndListView);
	BOOL InitListViewColumns(HWND hWndListView, vector<string> * headers, bool add_combo);


public:
	size_t Rows(){return rows;}
	size_t Cols(){return cols;}
	HWND GetWnd(){return hList;}
	bool OnNotify(LPARAM lParam);

#if !USE_LISTVIEW_STANDART 
	void OnDrawItem(LPDRAWITEMSTRUCT lpdis);
	void OnEndEdit();
#endif

	_ListViewTab_();

	bool Init(HWND hWndParent, LPVOID lpParam, double xpart0, double xpart_end, double ypart0, double ypart_end, bool use_check_boxes = true);
	virtual ~_ListViewTab_(void);
	void UpdateView(void);
	//void resize(size_t r, size_t c);
	void SetCols(size_t c);
	void SetHeaderString(size_t c, string s);
	void SetItemString(size_t r, size_t c, string s);
	string GetItemString(size_t r, size_t c);
	void SetColumnWidth(size_t c, int cx);
	int GetColumnWidth(size_t c, int cx);
	void AddRow(LPARAM lParam/* = 0*/, bool* pbChecked/* = NULL*/);
#if !USE_LISTVIEW_STANDART 
	void AddRow(LPARAM lParam,  vector<int> & ColomnsEditing, vector <bool*> & vpbColomnsChecked);
#endif
	void EraseRow(size_t r);
	void clear();
	void DeleteRows();

	LPARAM GetLParam(size_t r);

	void MoveItemUp(int context_menu_item);
	void MoveItemDown(int context_menu_item);

	HWND GetWndParent(){return hWndParent;}


};

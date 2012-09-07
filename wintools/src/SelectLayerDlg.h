//SelectLayerDlg.h

#ifndef SELECT_LAYER_DIALOG_H
#define SELECT_LAYER_DIALOG_H

class SurfDoc;

class select_layer_dialog
{
	friend BOOL CALLBACK DlgProcSelectLayer(HWND, UINT, WPARAM, LPARAM);
	private:
	
	static SurfDoc * doc;
	//static graphics_view * gv;
	
	static HWND hDlg;	
	//static HWND entry;
	//bool to_process_command;
	bool ok_pressed;
	
	public:
	char command[512];
	select_layer_dialog(SurfDoc *, const char *);

	virtual ~select_layer_dialog(void);
	bool WasOk(){return this->ok_pressed;}


	
	void ComboHandler(HWND hCombo);
	void OkButtonHandler(HWND hCombo, HWND hEdit);
	void CancelButtonHandler();

	void OnInitDialog(void);
};

#endif

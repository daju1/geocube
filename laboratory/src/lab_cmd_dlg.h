
class lab_cmd_dlg
{
	friend BOOL CALLBACK DlgProc_Command(HWND, UINT, WPARAM, LPARAM);
	private:
	
	
	static HWND dialog;	
	static HWND entry;
	bool to_process_command;
	bool ok_pressed;
	
	public:
	char command[512];
	lab_cmd_dlg(const char *);
	lab_cmd_dlg(const char *, bool);

	virtual ~lab_cmd_dlg(void);
	bool WasOk(){return this->ok_pressed;}


	
	
	void OkButtonHandler(HWND);
};
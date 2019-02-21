#ifndef FRAME_H_
#define FRAME_H_

#include "Headers.h"

class ImageTab;

class Frame : public wxFrame
{
	wxNotebook* notebook;
	ImageTab* imageTab;

	wxString filePath;

	wxMenuBar* menuBar;
	wxMenu* fileMenu;
	
	wxTextCtrl* log_textctrl;
	wxLogTextCtrl* logger;

	public:
		Frame();

		void OnNew(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnSave(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnReopen(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);

};

#endif // !FRAME_H_
#include "Headers.h"

class ImageTab;

class Frame : public wxFrame
{
	wxNotebook* notebook;
	ImageTab* imageTab;

	wxString filePath;

	wxMenuBar* menuBar;
	wxMenu* fileMenu;
	



	public:
		Frame();

		void OnNew(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnSave(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnReopen(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);

};
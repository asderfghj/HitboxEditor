#ifndef FRAME_H_
#define FRAME_H_

#include "Headers.h"

class ImageTab;
class HitboxTab;

class Frame : public wxFrame
{
	wxNotebook* notebook;
	ImageTab* imageTab;
	HitboxTab* hitboxTab;

	wxString filePath;

	wxMenuBar* menuBar;
	wxMenu* fileMenu;
	
	wxTextCtrl* log_textctrl;
	wxLogTextCtrl* logger;

	ImagesContainer* imagesContainer;

	public:
		Frame();

		void OnNew(wxCommandEvent& event);
		void OnQuit(wxCommandEvent& event);
		void OnSave(wxCommandEvent& event);
		void OnSaveAs(wxCommandEvent& event);
		void OnReopen(wxCommandEvent& event);
		void OnOpen(wxCommandEvent& event);
		ImagesContainer* getImagesContainer();
		void ImageAdded(wxString _imageName);
		void ImageRemoved(wxString _imageName);
};

#endif // !FRAME_H_
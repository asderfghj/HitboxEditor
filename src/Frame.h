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
	
	wxTextCtrl* log_textctrl;
	wxLogTextCtrl* logger;

	ImagesContainer* imagesContainer;

	public:
		Frame();

		ImagesContainer* getImagesContainer();
		void ImageAdded(wxString _imageName);
		void ImageRemoved(wxString _imageName);
};

#endif // !FRAME_H_
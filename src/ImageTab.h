#ifndef IMAGETAB_H_
#define IMAGETAB_H_
#include "Headers.h"

class ImageTab : public wxPanel
{
	Frame* parent;
	wxListBox* imagesbox;
	wxScrolledWindow* imageContainer;
	wxStaticBitmap* image;
	wxButton* addButton;
	wxButton* removeButton;
	std::vector<std::shared_ptr<Image>> images;

public:
	ImageTab(Frame* parent, wxNotebook* guiParent);

	void onAddClicked(wxCommandEvent& event);
	void onRemoveClicked(wxCommandEvent& event);
	void onListBoxClicked(wxCommandEvent& event);

	void resizeContainer();
	Image* getImage(wxString name);
	Image* tryGetImage(wxString name);

};

#endif
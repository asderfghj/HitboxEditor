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

public:
	ImageTab(Frame* parent, wxNotebook* guiParent);

	void onAddClicked(wxCommandEvent& event);
	void onRemoveClicked(wxCommandEvent& event);
	void onListBoxClicked(wxCommandEvent& event);

	void resizeContainer();
	Image* getImage(wxString name);

};

#endif
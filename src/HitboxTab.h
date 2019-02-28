#ifndef HITBOXTAB_H_
#define HITBOXTAB_H_
#include "Headers.h"

class CanvasView;

class HitboxTab : public wxPanel
{
	Frame* parent;
	wxListBox* imagesBox;
	wxListBox* hitboxesBox;
	//wxStaticBitmap* displayImage;
	Canvas* imageContainer;
	CanvasView* canvasView;
	wxSpinCtrlDouble* posXDisplay;
	wxSpinCtrlDouble* posYDisplay;
	wxSpinCtrlDouble* WidthDisplay;
	wxSpinCtrlDouble* HeightDisplay;
	wxButton* addHitboxButton;
	wxButton* addHurtboxButton;
	wxButton* removeButton;


public:
	HitboxTab(Frame* parent, wxNotebook* guiParent);
	void AddEntry(wxString _imageName);
	void RemoveEntry(wxString _imageName);
	void OnImageBoxClick(wxCommandEvent& event);
	void resizeContainer();
	Image* getImage(wxString name);
	void onAddHitboxClicked(wxCommandEvent& event);
	void onAddHurtboxClicked(wxCommandEvent& event);
	void onRemoveClicked(wxCommandEvent& event);
	Image* getCurrentlySelectedImage();
};



#endif
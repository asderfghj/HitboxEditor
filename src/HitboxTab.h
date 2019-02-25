#ifndef HITBOXTAB_H_
#define HITBOXTAB_H_
#include "Headers.h"


class HitboxTab : public wxPanel
{
	Frame* parent;
	wxListBox* imagesBox;
	wxListBox* hitboxesBox;
	wxStaticBitmap* displayImage;
	wxScrolledWindow* imageContainer;
	wxSpinCtrlDouble* posXDisplay;
	wxSpinCtrlDouble* posYDisplay;
	wxSpinCtrlDouble* WidthDisplay;
	wxSpinCtrlDouble* HeightDisplay;

public:
	HitboxTab(Frame* parent, wxNotebook* guiParent);
	/*void UpdateContainer();//need to link this to opening the tab
	void SetFocus() override;
	*/

};








#endif
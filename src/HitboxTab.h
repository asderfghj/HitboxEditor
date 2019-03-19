#ifndef HITBOXTAB_H_
#define HITBOXTAB_H_
#include "Headers.h"

class CanvasView;
class hitbox;

class HitboxTab : public wxPanel
{
	Frame* parent;
	wxListBox* imagesBox;
	wxListBox* hitboxesBox;
	//wxStaticBitmap* displayImage;
	Canvas* imageContainer;
	CanvasView* canvasView;
	wxButton* removeButton;
	wxButton* exportButton;
	wxButton* importButton;
	wxSpinCtrl* PPUValue;
	/*std::vector<std::shared_ptr<hitbox>> hitboxes;
	std::vector<std::shared_ptr<hitbox>> hurtboxes;*/
	int hitboxCounter, hurtboxCounter;
	void deselectSelectedHitbox();
	std::shared_ptr<hitbox> currentlySelectedHitbox;
	nlohmann::json generateJSON();
	void ForceUpdate();
	int PPU;

public:
	HitboxTab(Frame* parent, wxNotebook* guiParent);
	void AddEntry(wxString name);
	void RemoveEntry(wxString name);
	void RemoveHitbox();
	void OnImageBoxClick(wxCommandEvent& event);
	void OnHitboxBoxClick(wxCommandEvent& event);
	void resizeContainer();
	Image* getImage(wxString name);
	void onRemoveClicked(wxCommandEvent& event);
	Image* getCurrentlySelectedImage();
	void addHitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, bool _isHurtbox);
	//void addHurtbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY);
	std::shared_ptr<hitbox> getHitbox(int _index);
	std::shared_ptr<hitbox> getHitbox(wxString _ID);
	int getHitboxArraySize();
	std::shared_ptr<hitbox> getHurtbox(int _index);
	std::shared_ptr<hitbox> getHurtbox(wxString _ID);
	int getHurtboxArraySize();
	void onExportClicked(wxCommandEvent& event);
	void onImportClicked(wxCommandEvent& event);
	void onSpinValChanged(wxSpinEvent& event);
};



#endif
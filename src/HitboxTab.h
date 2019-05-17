#ifndef HITBOXTAB_H_
#define HITBOXTAB_H_

#include <wx/notebook.h>
#include<nlohmann/json.hpp>


class Canvas;
class CanvasView;
class hitbox;
class Frame;
struct Image;

/**
* The class for the hitbox tab
*/
class HitboxTab : public wxPanel
{
	Frame* parent;
	wxListBox* imagesBox;
	wxListBox* hitboxesBox;
	Canvas* imageContainer;
	CanvasView* canvasView;
	wxButton* removeButton;
	wxButton* exportButton;
	wxButton* importButton;
	wxSpinCtrl* PPUValue;
	int hitboxCounter, hurtboxCounter;
	void deselectSelectedHitbox();
	std::shared_ptr<hitbox> currentlySelectedHitbox;
	nlohmann::json generateJSON();//Generates the json from the hitboxes on the currently selected image
	void ForceUpdate();//updates the hitbox listboxe when the image is changed.
	int PPU;

public:
	HitboxTab(Frame* parent, wxNotebook* guiParent);
	void AddEntry(wxString name);//adds a new entry to the images box. Done automatically when an image is added in the images tab
	void RemoveEntry(wxString name);//removes an entry from the images box. Done automatically when an image is removed in the images tab
	void RemoveHitbox();//deletes the hitbox from the listbox and removes any references to it.
	void OnImageBoxClick(wxCommandEvent& event);//event when the image listbox is clicked
	void OnHitboxBoxClick(wxCommandEvent& event);//event when the hitbox listbox is clicked
	void resizeContainer();//re-centers the image in the canvas.
	Image* getImage(wxString name);
	void onRemoveClicked(wxCommandEvent& event);
	Image* getCurrentlySelectedImage();
	void addHitbox(float _cX, float _cY, float _iX, float _iY, float _w, float _h, float _oX, float _oY, bool _isHurtbox);
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

#endif // !HITBOXTAB_H_